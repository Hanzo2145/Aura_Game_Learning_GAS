// Copyright Anas Hanzo Al-Juboori


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "Player/AuraPlayerState.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	check(AttributeInfo)
	
	for (auto& Pair : AuraAttributeSet->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
	AAuraPlayerState* AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	AttributePointsChangedDelegate.Broadcast(AuraPlayerState->GetAttributePoints());
	SpellPointsChangedDelegate.Broadcast(AuraPlayerState->GetSpellPoints());
}

void UAttributeMenuWidgetController::BindCallbacksToDeoendencies()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo)
	for (auto& Pair : AuraAttributeSet->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			}
			);
	}
	AAuraPlayerState* AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	AuraPlayerState->OnAttributePointsChangedDelegate.AddLambda(
		[this](int32 NewPoints)
		{
			AttributePointsChangedDelegate.Broadcast(NewPoints);
		}
		);
	AuraPlayerState->OnSpellPointsChangedDelegate.AddLambda(
		[this](int32 NewPoints)
		{
			SpellPointsChangedDelegate.Broadcast(NewPoints);
		}
		);
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
