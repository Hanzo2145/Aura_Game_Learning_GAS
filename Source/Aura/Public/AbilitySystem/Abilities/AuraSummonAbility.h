// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraSummonAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraSummonAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
	
public:

	/*
	 * Functions Declarations
	 */
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocations();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category= "Summoning")
	TSubclassOf<APawn> GetRandomMinionClass();


	/*
	 * Variables Declarations
	 */
	UPROPERTY(EditDefaultsOnly, Category= "Summoning")
	int32 NumMinions = 5;

	UPROPERTY(EditDefaultsOnly, Category= "Summoning")
	TArray<TSubclassOf<APawn>> MinionClasses;

	UPROPERTY(EditDefaultsOnly, Category= "Summoning")
	float MinSpawnDistance = 50.f;
	
	UPROPERTY(EditDefaultsOnly, Category= "Summoning")
	float MaxSpawnDistance = 250.f;

	UPROPERTY(EditDefaultsOnly, Category= "Summoning")
	float SpawnSpread = 90.f;
};
