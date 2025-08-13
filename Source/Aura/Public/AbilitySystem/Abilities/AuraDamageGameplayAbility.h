// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraDamageGameplayAbility.generated.h"


struct FTaggedMontage;
/**
 * 
 */
UCLASS()
class AURA_API UAuraDamageGameplayAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void CauseDamage(AActor* TargetActor);

protected:
	//This is the Gameplay Effect that we are going to use to Deal damage the Characters for now
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;

	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomedMontageFromArray(const TArray<FTaggedMontage>& TaggedMontages) const;
};
