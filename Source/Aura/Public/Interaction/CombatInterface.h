// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

class UNiagaraSystem;
class UAnimMontage;

USTRUCT(BlueprintType)
struct FTaggedMontage
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* Montage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag MontageTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag SocketTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundBase* ImpactSound = nullptr;
};


// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual int32 GetPlayerLevel();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	FVector GetCombatSocketLocation(const FGameplayTag& MontageTag);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Combat")
	void UpdatingFacingTarget(const FVector& target);

	virtual void SetSpringArmlength(float SpringArmlength);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	UAnimMontage* GetHitReactMontage();

	virtual void Die() = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	bool IsDead() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	AActor* GetAvatar();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Combat")
	TArray<FTaggedMontage> GetTaggedMontages();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Effects")
	UNiagaraSystem* GetBloodEffect();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Effects")
	FTaggedMontage GetTaggedMontageByTag(const FGameplayTag& MontageTag);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	int32 GetMinionCount();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void AddToMinionCount(int32 Amount);
	
};
