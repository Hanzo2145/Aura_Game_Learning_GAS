// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "Character/AruraCharacterBase.h"
#include "Interaction/PlayerInterface.h"
#include "AuraCharacter.generated.h"

class UNiagaraComponent;
class UCameraComponent;
class UBoxComponent;
class USpringArmComponent;
class AAuraHUD;
class AAuraPlayerState;
/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAruraCharacterBase, public IPlayerInterface
{
	GENERATED_BODY()
public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void OnRep_Stunned() override;
	virtual void OnRep_Burned() override;

	/* Combat Interface*/
	virtual int32 GetPlayerLevel_Implementation() override;
	virtual void SetSpringArmlength(float SpringArmlength) override;
	/* /Combat Interface*/

	/* player Interface*/
	virtual void AddToXP_Implementation(int32 InXP) override;
	virtual void LevelUp_Implementation() override;
	virtual int32 GetXP_Implementation() const override;
	virtual int32 FindLevelForXP_Implementation(const int32 InXP) override;
	virtual int32 GetAttributesPointsRewards_Implementation(const int32 InLevel) const override;
	virtual int32 GetSpellPointsRewards_Implementation(const int32 InLevel) const override;
	virtual void AddToPlayerLevel_Implementation(const int32 InPlayerLevel) override;
	virtual void AddToAttributesPoints_Implementation(const int32 InAttributesPoints) override;
	virtual void AddToSpellPoints_Implementation(const int32 InSpellPoints) override;
	virtual int32 GetAttributesPoints_Implementation() const override;
	virtual int32 GetSpellPoints_Implementation() const override;
	/* End player Interface*/


	/*
	 * Variables Declarations
	 */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent> LevelUpNiagaraComponent;

protected:
	/*
	 * Functions Declarations
	 */
	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;
	

private:
	virtual void InitAbilityActorInfo() override;

	/*
	 * Variables Declarations
	 */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings")
	float MaxSpringArmlength = 1200.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings")
	float MinSpringArmlength = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings")
	FVector BoxExtent = FVector(0.f, 30.f, 140.f);

	AAuraPlayerState* GetAuraPlayerState() const;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastLevelUpParticles() const;
};
