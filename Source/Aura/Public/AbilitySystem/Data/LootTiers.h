// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LootTiers.generated.h"

USTRUCT(BlueprintType)
struct FLootItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Loot Tiers | Spawning")
	TSubclassOf<AActor> LootClass;

	UPROPERTY(EditAnywhere, Category="Loot Tiers | Spawning")
	float ChanceToSpawn = 0.f;

	UPROPERTY(EditAnywhere, Category="Loot Tiers | Spawning")
	int32 MaxNumberToSpawn = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Loot Tiers | Spawning")
	bool bLootLevelOverride = true;
};
/**
 * 
 */
UCLASS()
class AURA_API ULootTiers : public UDataAsset
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, BlueprintCallable, Category= "Loot Tiers | Spawning")
	TArray<FLootItem> GetLootItems();
	
	UPROPERTY(EditDefaultsOnly, Category="Loot Tiers | Spawning")
	TArray<FLootItem> LootItems;
};
