// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "AuraAbilityTypes.h"
#include "GameFramework/Actor.h"
#include "AuraProjectile.generated.h"

struct FDamageEffectParams;
class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;

UCLASS()
class AURA_API AAuraProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	/*
	 * <Function Declarations 
	 */
	AAuraProjectile();
	
	
	/*
	 * <Variables Declaration
	 */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	/*Variables Declarations*/
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FDamageEffectParams DamageEffectParams;

	UPROPERTY()
	TObjectPtr<USceneComponent> HomingTargetSceneComponent;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	virtual void OnHit();

	virtual void Destroyed() override;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool IsValidOverlap(AActor* OtherActor);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> Sphere;

	// this bool will check to see if we spawned an effect and played the sound.
	bool bHit = false;

	//this Variable will allow us to remove the sound once we hit something or the actor gets destroyed 
	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSoundComponenet;
private:
	/*
	 * <Variables Declaration
	 */
	// Niagara System For when the PLayer Hit Something
	UPROPERTY(EditAnywhere,  Category = Projectile)
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	//Sound For when the Player Hit something
	UPROPERTY(EditAnywhere,  Category = Projectile)
	TObjectPtr<USoundBase> ImpactSound;

	//Play Sound when the Projectile Is created and it is looping.
	UPROPERTY(EditAnywhere,  Category = Projectile)
	TObjectPtr<USoundBase> LoopingSound;
	
	//float to set the life span of the projectile.
	UPROPERTY(EditAnywhere,  Category = Projectile)
	float LifeSpan = 15.f;
};
