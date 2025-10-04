// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;
class USphereComponent;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};
 
UENUM(BlueprintType)
enum class EEffectRemovalPolicy: uint8
{
	RemoveOnEndOverlap,
	DoNotRemove
};


UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();

	UFUNCTION(BlueprintCallable, Category="Aura Effect Actor | Spawning")
	void SetEffectActorLevel(float InLevel);
	virtual void Tick(float DeltaTime) override;

protected:
	/**
	 * Functions Declarations
	 */
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UFUNCTION(BlueprintCallable)
	void OnOverLap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	

	/*
	 * Variables Declarations
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	bool bDestroyOnEffectApplication = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	bool bApplyEffectsToEnemies = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup Movement")
	bool bRotate = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup Movement")
	float RotationRate = 45.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup Movement")
	bool bSinusoidalMovement = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup Movement")
	float SineAmplitude = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup Movement")
	float SinePeriodConstant = 1.f; // 2 * Pie

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup Movement")
	FVector InitialLocation;

	UPROPERTY(BlueprintReadWrite)
	FVector CalculatedLocation;

	UPROPERTY(BlueprintReadWrite)
	FRotator CalculatedRotation;

	UFUNCTION(BlueprintCallable)
	void StartSinusoidalMovement();

	UFUNCTION(BlueprintCallable)
	void StartRotation();

	//Gameplay Effect Classes Variables 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	EEffectApplicationPolicy InstantEffectapplicationPolicy = EEffectApplicationPolicy::DoNotApply;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	EEffectApplicationPolicy DurationApplicationPolicy = EEffectApplicationPolicy::DoNotApply;;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	EEffectApplicationPolicy InfiniteEffectapplicationPolicy = EEffectApplicationPolicy::DoNotApply;;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	UPROPERTY()
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effects")
	float ActorLovel = 1.f;

private:

	float RunningTime = 0.f;

	void ItemMovement(float DeltaTime);

};
