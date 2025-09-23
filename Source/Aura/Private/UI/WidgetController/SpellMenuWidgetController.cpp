// Copyright Anas Hanzo Al-Juboori


#include "UI/WidgetController/SpellMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Player/AuraPlayerState.h"

void USpellMenuWidgetController::BroadcastInitialValues()
{
	BroadcastAbilityInfo();
	SpellPointsChangedDelegate.Broadcast(GetAuraPlayerState()->GetSpellPoints());
}

void USpellMenuWidgetController::BindCallbacksToDependencies()
{
	GetAuraAbilitySystemComponent()->AbilityStatusChanged.AddLambda(
		[this] (const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag, int32 NewLevel)
		{
			if (SelectedAbility.Ability.MatchesTagExact(AbilityTag))
			{
				SelectedAbility.Status = StatusTag;
				bool EnableSpendPoints = false;
				bool EnableEquip = false;
				ShouldEnableButtons(StatusTag, CurrentSpellPoints, EnableSpendPoints, EnableEquip);
				FString Description;
				FString NextLevelDescription;
				GetAuraAbilitySystemComponent()->GetDiscretionByAbilityTag(AbilityTag, Description, NextLevelDescription);
				SpellGlobeSelectedDelegate.Broadcast(EnableSpendPoints, EnableEquip, Description, NextLevelDescription);
			}
			if (AbilityInfo)
			{
				FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
				Info.StatusTag = StatusTag;
				AbilityInfoDelegate.Broadcast(Info);
			}
		}
		);
	GetAuraAbilitySystemComponent()->AbilityEquipped.AddUObject(this, &USpellMenuWidgetController::OnAbilityEquipped);
	
	GetAuraPlayerState()->OnSpellPointsChangedDelegate.AddLambda(
		[this](int32 SpellPoints)
		{
			SpellPointsChangedDelegate.Broadcast(SpellPoints);
			CurrentSpellPoints = SpellPoints;
			bool EnableSpendPoints = false;
			bool EnableEquip = false;
			ShouldEnableButtons(SelectedAbility.Status, CurrentSpellPoints, EnableSpendPoints, EnableEquip);
			FString Description;
			FString NextLevelDescription;
			GetAuraAbilitySystemComponent()->GetDiscretionByAbilityTag(SelectedAbility.Ability, Description, NextLevelDescription);
			SpellGlobeSelectedDelegate.Broadcast(EnableSpendPoints, EnableEquip, Description, NextLevelDescription);
		}
		);
}

void USpellMenuWidgetController::SpendPointsButtonPressed()
{
	if (GetAuraAbilitySystemComponent())
	{
		GetAuraAbilitySystemComponent()->ServerSpendSpellPoint(SelectedAbility.Ability);
	}
	
}

void USpellMenuWidgetController::SpellGlobeSelected(const FGameplayTag& AbilityTag)
{
	if (bWaitingForEquipSelection)
	{
		const FGameplayTag SelectedAbilityType = AbilityInfo->FindAbilityInfoForTag(AbilityTag).AbilityTypeTag;
		StopWaitForEquipDelegate.Broadcast(SelectedAbilityType);
		bWaitingForEquipSelection = false;
	}
	
	
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	const int32 SpellPoints = GetAuraPlayerState()->GetSpellPoints();
	FGameplayTag AbilityStatus;

	const bool bTagVaild = AbilityTag.IsValid();
	const bool bTagNone = AbilityTag.MatchesTag(GameplayTags.Abilities_None);
	const FGameplayAbilitySpec* AbilitySpec = GetAuraAbilitySystemComponent()->GetSpecFromAbilityTag(AbilityTag);
	const bool bSpecVaild = AbilitySpec != nullptr;
	if (!bTagVaild || bTagNone || !bSpecVaild)
	{
		AbilityStatus = GameplayTags.Abilities_None;
	}
	else
	{
		AbilityStatus = GetAuraAbilitySystemComponent()->GetStatusFromSpec(*AbilitySpec);
	}

	SelectedAbility.Ability = AbilityTag;
	SelectedAbility.Status = AbilityStatus;
	bool EnableSpendPoints = false;
	bool EnableEquip = false;
	ShouldEnableButtons(AbilityStatus, SpellPoints, EnableSpendPoints, EnableEquip);
	FString Description;
	FString NextLevelDescription;
	GetAuraAbilitySystemComponent()->GetDiscretionByAbilityTag(AbilityTag, Description, NextLevelDescription);
	SpellGlobeSelectedDelegate.Broadcast(EnableSpendPoints, EnableEquip, Description, NextLevelDescription);
}

void USpellMenuWidgetController::GlobeDeselect()
{
	if (bWaitingForEquipSelection)
	{
		const FGameplayTag SelectedAbilityType = AbilityInfo->FindAbilityInfoForTag(SelectedAbility.Ability).AbilityTypeTag;
		StopWaitForEquipDelegate.Broadcast(SelectedAbilityType);
		bWaitingForEquipSelection = false;
	}
	SelectedAbility.Ability = FAuraGameplayTags::Get().Abilities_None;
	SelectedAbility.Status = FAuraGameplayTags::Get().Abilities_Status_Locked;
	SpellGlobeSelectedDelegate.Broadcast(false, false, FString(), FString());
}

void USpellMenuWidgetController::EquipButtonPressed()
{
	const FGameplayTag AbilityType =AbilityInfo->FindAbilityInfoForTag(SelectedAbility.Ability).AbilityTypeTag;
	WaitForEquipDelegate.Broadcast(AbilityType);
	bWaitingForEquipSelection = true;

	const FGameplayTag SelectedStatus = GetAuraAbilitySystemComponent()->GetStatusFromAbilityTag(SelectedAbility.Ability);
	if (SelectedStatus.MatchesTagExact(FAuraGameplayTags::Get().Abilities_Status_Equipped))
	{
		SelectedSlot = GetAuraAbilitySystemComponent()->GetSlotFromAbilityTag(SelectedAbility.Ability);
	}
}

void USpellMenuWidgetController::SpellRowGlobePressed(const FGameplayTag& SlotTag, const FGameplayTag& AbilityType)
{
	if (!bWaitingForEquipSelection) return;
	// Check selected ability against the slot's ability type.
	// (don't equip an offensive spell in a passive slot and vice versa)
	const FGameplayTag& SelectedAbilityType = AbilityInfo->FindAbilityInfoForTag(SelectedAbility.Ability).AbilityTypeTag;
	if (!SelectedAbilityType.MatchesTagExact(AbilityType)) return;

	GetAuraAbilitySystemComponent()->ServerEquipAbility(SelectedAbility.Ability, SlotTag);
}

void USpellMenuWidgetController::OnAbilityEquipped_Implementation(const FGameplayTag& AbilityTag, const FGameplayTag& Status, const FGameplayTag& Slot, const FGameplayTag& PreviousSlot)
{
	bWaitingForEquipSelection = false;

	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	
	FAuraAbilityInfo LastSlotInfo;
	LastSlotInfo.StatusTag = GameplayTags.Abilities_Status_Unlocked;
	LastSlotInfo.InputTag = PreviousSlot;
	LastSlotInfo.AbilityTag = GameplayTags.Abilities_None;
	// Broadcast empty info if PreviousSlot is a valid slot. Only if equipping an already-equipped spell
	AbilityInfoDelegate.Broadcast(LastSlotInfo);

	FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
	Info.StatusTag = Status;
	Info.InputTag = Slot;
	AbilityInfoDelegate.Broadcast(Info);

	StopWaitForEquipDelegate.Broadcast(AbilityInfo->FindAbilityInfoForTag(AbilityTag).AbilityTypeTag);
	SpellGlobeReassignedDelegate.Broadcast(AbilityTag);
	GlobeDeselect();
}

void USpellMenuWidgetController::ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoints, bool& bShouldEnableSpellPointsButton, bool& bShouldEnableEquipButton)
{
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	bShouldEnableSpellPointsButton = false;
	if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Equipped))
	{
		bShouldEnableEquipButton = true;
		if (SpellPoints > 0)
		{
			bShouldEnableSpellPointsButton = true;
		}
	}
	else if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Eligible))
	{
		if (SpellPoints > 0)
		{
			bShouldEnableSpellPointsButton = true;
		}
	}
	else if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked))
	{
		bShouldEnableEquipButton = true;
		if (SpellPoints > 0)
		{
			bShouldEnableSpellPointsButton = true;
		}
	}
}
