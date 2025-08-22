// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStateChange, int32 /*StateValue*/);
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AAuraPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
	
	FOnPlayerStateChange OnXPChangedDelegate;
	FOnPlayerStateChange OnLevelChangedDelegate;

	/*Private Getters*/
	FORCEINLINE int32 GetPlayerLevelVaribale() const { return Level; }
	FORCEINLINE int32 GetXP() const { return XP; }

	void SetXP(int32 InXP);
	void SetLevel(int32 InLevel);
	void AddToXP(int32 InXP);
	void AddToLevel(int32 InLevel);

	

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:
	
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	int32 Level = 1;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_XP)
	int32 XP = 1;

	UFUNCTION()
	void OnRep_XP(int32 OldXP);
};
