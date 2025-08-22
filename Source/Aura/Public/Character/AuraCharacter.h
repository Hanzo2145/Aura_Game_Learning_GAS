// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "Character/AruraCharacterBase.h"
#include "AuraCharacter.generated.h"

class UCameraComponent;
class UBoxComponent;
class USpringArmComponent;
class AAuraHUD;
class AAuraPlayerState;
/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAruraCharacterBase
{
	GENERATED_BODY()
public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/* Combat Interface*/
	virtual int32 GetPlayerLevel() override;
	virtual void SetSpringArmlength(float SpringArmlength) override;
	/* /Combat Interface*/

private:
	virtual void InitAbilityActorInfo() override;

	/*
	 * Variables Declarations
	 */
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings")
	float MaxSpringArmlength = 1200.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings")
	float MinSpringArmlength = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Settings")
	FVector BoxExtent = FVector(0.f, 30.f, 140.f);
};
