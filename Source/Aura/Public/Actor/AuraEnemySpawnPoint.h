// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "Character/AruraCharacterBase.h"
#include "Engine/TargetPoint.h"
#include "AuraEnemySpawnPoint.generated.h"



class AAuraEnemy;


USTRUCT(BlueprintType)
struct FEnemyClasses
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy Classes")
	TSubclassOf<AAuraEnemy> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy Classes")
	ECharacterClass CharacterClass = ECharacterClass::None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy Classes")
	int32 EnemyLevel = 1;
};
/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemySpawnPoint : public ATargetPoint
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void SpawnEnemy(TArray<FEnemyClasses> InEnemyClasses);

private:
	static FEnemyClasses GetRandomEnemyClass(TArray<FEnemyClasses> InEnemyClasses);
};
