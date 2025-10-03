// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "AuraEnemySpawnPoint.h"
#include "GameFramework/Actor.h"
#include "Interaction/SaveInterface.h"
#include "AuraEnemySpawnVolume.generated.h"


class AAuraEnemy;
class UBoxComponent;



UCLASS()
class AURA_API AAuraEnemySpawnVolume : public AActor, public ISaveInterface
{
	GENERATED_BODY()
	
public:	
	AAuraEnemySpawnVolume();

	/*Save Interface*/
	virtual void LoadActor_Implementation() override;
	/*END Save Interface*/

	UPROPERTY(BlueprintReadOnly, SaveGame)
	bool bReached = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, SaveGame, Category= "Save Game")
	bool bSaveThisActor = false;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	TArray<AAuraEnemySpawnPoint*> SpawnPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Class")
	TArray<FEnemyClasses> EnemiesToSpawn;
	
private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> Box;

};
