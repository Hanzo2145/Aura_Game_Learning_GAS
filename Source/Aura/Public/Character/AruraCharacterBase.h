// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"
#include "GameFramework/Character.h"
#include "AruraCharacterBase.generated.h"



class UPassiveNiagaraComponent;
class UDebuffNiagaraComponent;
enum class ECharacterClass : uint8;
class UNiagaraSystem;
class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;
class UAnimMontage;

UCLASS(Abstract)
class AURA_API AAruraCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	/*Functions Declarations*/
	AAruraCharacterBase();
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	/* Combat Interface*/
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual void Die(const FVector& DeathImpulse) override;
	virtual FOnDeathSignature& GetOnDeathDelegate() override;
	virtual FVector GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag) override;
	virtual bool IsDead_Implementation() const override;
	virtual AActor* GetAvatar_Implementation() override;
	virtual TArray<FTaggedMontage> GetTaggedMontages_Implementation() override;
	virtual UNiagaraSystem* GetBloodEffect_Implementation() override;
	virtual FTaggedMontage GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag) override;
	virtual int32 GetMinionCount_Implementation() override;
	virtual void AddToMinionCount_Implementation(int32 Amount) override;
	virtual ECharacterClass GetCharacterClass_Implementation() override;
	virtual FOnASCRegistered& GetOnAscRegisteredDelegate() override;
	virtual USkeletalMeshComponent* GetWeapon_Implementation() override;
	virtual void SetIsBeingShocked_Implementation(bool bInShock) override;
	virtual bool IsBeingShocked_Implementation() const override;
	virtual FOnDamageSignature& GetOnDamageSignature() override;
	/*End Combat Interface*/
	
	FOnASCRegistered OnAscRegistered;
	FOnDeathSignature OnDeathDelegate;
	FOnDamageSignature OnDamageDelegate;
	
	UFUNCTION(NetMulticast, reliable)
	virtual void MulticastHandleDeath(const FVector& DeathImpulse);

	void SetCharacterClass(ECharacterClass InClass) { CharacterClass = InClass; }

	/*Variables Declarations*/

	UPROPERTY(EditAnywhere, Category = "Combat")
	TArray<FTaggedMontage> AttackMontages;

	UPROPERTY(ReplicatedUsing=OnRep_Stunned, BlueprintReadOnly)
	bool bIsStunned = false;

	UPROPERTY(ReplicatedUsing=OnRep_Burned, BlueprintReadOnly)
	bool bIsBurned = false;

	UPROPERTY(Replicated, BlueprintReadOnly)
	bool bIsBeingShocked = false;

	UFUNCTION()
	virtual void OnRep_Stunned();

	UFUNCTION()
	virtual void OnRep_Burned();
protected:
	
	/*Functions Declarations*/
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
	virtual void InitializeDefaultAttributes() const;
	void AddCharacterAbilities();
	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	/*Variables Declarations*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName WeaponTipSocketName;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName RightHandSocketName;

	UPROPERTY(EditAnywhere, Category = "Combat")
	FName LeftHandSocketName;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	FName TailSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	float BaseWalkSpeed = 600.f;

	/* Minions */
	int32 MinionCount = 0;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttribute;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttribute;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttribute;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Effects")
	UNiagaraSystem* BloodEffect;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Effects")
	USoundBase* DeathSound;

	UPROPERTY(BlueprintReadOnly)
	bool bDead = false;

	// Dissolve Effects

	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void StartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void WeaponStartDissolveTimeline(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> DissolveMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> WeaponDissolveMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::None;

	UPROPERTY(VisibleAnywhere, Category = "Visuals")
	TObjectPtr<UDebuffNiagaraComponent> BurnDebuffComponent;

	UPROPERTY(VisibleAnywhere, Category = "Visuals")
	TObjectPtr<UDebuffNiagaraComponent> StunDebuffComponent;

private:

	/*
	 * Variables Declaration
	 */

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupPassiveAbilities;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	TObjectPtr<UPassiveNiagaraComponent> HaloOfProtectionNiagaraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	TObjectPtr<UPassiveNiagaraComponent> LifeSiphonNiagaraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	TObjectPtr<UPassiveNiagaraComponent> ManaSiphonNiagaraComponent;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	TObjectPtr<USceneComponent> EffectAttachComponent;
	
};
