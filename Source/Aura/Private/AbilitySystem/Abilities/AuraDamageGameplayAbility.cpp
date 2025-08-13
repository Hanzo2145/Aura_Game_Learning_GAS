// Copyright Anas Hanzo Al-Juboori


#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Interaction/CombatInterface.h"

void UAuraDamageGameplayAbility::CauseDamage(AActor* TargetActor)
{
	const FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, 1);
	for (TTuple<FGameplayTag, FScalableFloat> Pair : DamageTypes)
	{
		const float DamageMagnitude = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, DamageMagnitude);
	}
	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(),
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
	
}

FTaggedMontage UAuraDamageGameplayAbility::GetRandomedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const
{
	if (TaggedMontages.Num() > 0)
	{
		const int32 RandomIndex = FMath::RandRange(0, TaggedMontages.Num() - 1);
		return TaggedMontages[RandomIndex];
	}

	return FTaggedMontage();
}
