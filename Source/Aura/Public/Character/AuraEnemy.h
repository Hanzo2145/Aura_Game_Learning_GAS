// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "Character/AruraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAruraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();
	/* Enemy Interface */
	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;
	/* end Enemy Interface */
protected:
	/*
	 * Functions Declarations
	 */
	virtual  void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

	/* Combat Interface*/

	virtual int32 GetPlayerLevel() override;
	
	/* Combat Interface*/


	/*
	 * Variables Declarations 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

private:

	
};
