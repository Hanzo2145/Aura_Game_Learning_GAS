// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "Character/AruraCharacterBase.h"
#include "AuraCharacter.generated.h"

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
private:
	void InitAbilityActorInfo();
};
