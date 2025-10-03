// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"


class IHighlightInterface;
class AMagicCircle;
class UNiagaraSystem;
class UDamageTextComponent;
class UAuraInputConfig;
class AAuraHUD;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UAuraAbilitySystemComponent;
class USplineComponent;


enum class ETargetingStatus : uint8
{
	TargetingEnemy,
	TargetingNonEnemy,
	NotTargeting
};
/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	/*
	 * Functions Declarations
	 */
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

	UFUNCTION(Client, Reliable)
	void ShowDamageNumber(float DamageAmount, ACharacter* TargetCharacter, bool blockedHit, bool bCriticalHit);

	UFUNCTION(BlueprintCallable)
	void ShowMagicCircle(UMaterialInterface* DecalMaterial = nullptr);
	
	UFUNCTION(BlueprintCallable)
	void HideMagicCircle();

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:
	/*
	 * Functions Declarations
	 */
	void CursorTrace();
	UAuraAbilitySystemComponent* GetASC();
	/**
	 * Variables
	 */
	TObjectPtr<AActor> LastActor;
	TObjectPtr<AActor>ThisActor;
	FHitResult CursorHit;
	static void HighlightActor(AActor* InActor);
	static void UnHighlightActor(AActor* InActor);
	
	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;
	
	
	/*
	 * Input Action and Mapping
	 */
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	void Move(const FInputActionValue& InputActionValue);

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> ShiftAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	// the three function that we need to bind to
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	void AutoRun();
	void UpdateMagicCircleLocation();
	
	void ShiftPressed() {bShitKeyDown = true;}
	void ShiftReleased() {bShitKeyDown = false;}
	bool bShitKeyDown = false;
		
	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5f;
	bool bAutoRunning = false;
	ETargetingStatus TargetingStatus = ETargetingStatus::NotTargeting;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraSystem> ClickNiagaraSystem;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMagicCircle> MagicCircleClass;

	UPROPERTY()
	TObjectPtr<AMagicCircle> MagicCircle;
};
