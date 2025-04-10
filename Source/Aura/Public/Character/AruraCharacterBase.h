// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AruraCharacterBase.generated.h"

UCLASS(Abstract)
class AURA_API AAruraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAruraCharacterBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	
};
