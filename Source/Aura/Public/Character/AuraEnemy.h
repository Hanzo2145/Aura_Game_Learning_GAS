// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "Character/AruraCharacterBase.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "Interaction/EnemyInterface.h"
#include "Interaction/HighlightInterface.h"
#include "AuraEnemy.generated.h"

class AAuraAIController;
class UWidgetComponent;
class UBehaviorTree;

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAruraCharacterBase, public IEnemyInterface, public IHighlightInterface
{
	GENERATED_BODY()
public:
	AAuraEnemy();
	/* Highlight Interface */
	virtual void HighlightActor_Implementation() override;
	virtual void UnHighlightActor_Implementation() override;
	virtual void SetMoveToLocation_Implementation(FVector& OutDestination) override;
	/* end Highlight Interface */
	
	/* Enemy Interface */
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;
	/* end Enemy Interface */
	
	/*
	 * Functions Declarations
	 */
	void HitReactTagChanged(const FGameplayTag CallBackTag, int32 NewCount);
	virtual void Die(const FVector& DeathImpulse) override;
	virtual void PossessedBy(AController* NewController) override;
	void SetEnemyLevel(int32 InLevel) { Level = InLevel; }
	
	/*
	 * Variables Declarations 
	 */
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float LifeSpan = 5.f;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	TObjectPtr<AActor> CombatTarget;
	
protected:
	/*
	 * Functions Declarations
	 */
	virtual  void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;
	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;

	/* Combat Interface*/

	virtual int32 GetPlayerLevel_Implementation() override;
	
	/* Combat Interface*/


	/*
	 * Variables Declarations 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditDefaultsOnly, Category= "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AAuraAIController> AuraAIController;
};
