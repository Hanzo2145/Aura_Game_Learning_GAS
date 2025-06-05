// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "Character/AruraCharacterBase.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;
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

	/*
	 * Variables Declarations 
	 */
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
protected:
	/*
	 * Functions Declarations
	 */
	virtual  void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	/* Combat Interface*/

	virtual int32 GetPlayerLevel() override;
	
	/* Combat Interface*/


	/*
	 * Variables Declarations 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::None;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	TObjectPtr<UWidgetComponent> HealthBar;

private:

	
};
