// Copyright Anas Hanzo Al-Juboori


#include "Character/AruraCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Debuff/DebuffNiagaraComponent.h"
#include "AbilitySystem/Passive/PassiveNiagaraComponent.h"
#include "Aura/Aura.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

AAruraCharacterBase::AAruraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	BurnDebuffComponent = CreateDefaultSubobject<UDebuffNiagaraComponent>("BurnDebuff");
	BurnDebuffComponent->SetupAttachment(GetRootComponent());
	BurnDebuffComponent->DebuffTag = FAuraGameplayTags::Get().Debuff_Burn;

	StunDebuffComponent = CreateDefaultSubobject<UDebuffNiagaraComponent>("StunDebuff");
	StunDebuffComponent->SetupAttachment(GetRootComponent());
	StunDebuffComponent->DebuffTag = FAuraGameplayTags::Get().Debuff_Stun;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon Mesh");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Effects
	EffectAttachComponent = CreateDefaultSubobject<USceneComponent>("EffectAttach");
	EffectAttachComponent->SetupAttachment(GetRootComponent());

	HaloOfProtectionNiagaraComponent = CreateDefaultSubobject<UPassiveNiagaraComponent>("Halo Of Protection");
	HaloOfProtectionNiagaraComponent->SetupAttachment(EffectAttachComponent);

	LifeSiphonNiagaraComponent = CreateDefaultSubobject<UPassiveNiagaraComponent>("Life Siphon");
	LifeSiphonNiagaraComponent->SetupAttachment(EffectAttachComponent);

	ManaSiphonNiagaraComponent = CreateDefaultSubobject<UPassiveNiagaraComponent>("Mana Siphon");
	ManaSiphonNiagaraComponent->SetupAttachment(EffectAttachComponent);
	
}

void AAruraCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	EffectAttachComponent->SetWorldRotation(FRotator::ZeroRotator);
}

void AAruraCharacterBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AAruraCharacterBase, bIsStunned);
	DOREPLIFETIME(AAruraCharacterBase, bIsBurned);
	DOREPLIFETIME(AAruraCharacterBase, bIsBeingShocked);
}

UAbilitySystemComponent* AAruraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAnimMontage* AAruraCharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

void AAruraCharacterBase::Die(const FVector& DeathImpulse)
{
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MulticastHandleDeath(DeathImpulse);
}

FOnDeathSignature& AAruraCharacterBase::GetOnDeathDelegate()
{
	return OnDeathDelegate;
}

void AAruraCharacterBase::MulticastHandleDeath_Implementation(const FVector& DeathImpulse)
{
	
	//PLay Sound at location
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation(), GetActorRotation());
	
	//Behavior for the Weapon
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Weapon->AddImpulse(DeathImpulse * 0.1f, NAME_None, true);

	//Behavior for the Mesh
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	GetMesh()->AddImpulse(DeathImpulse, NAME_None, true);

	//Behavior for the Capsule
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Dissolve();
	bDead = true;
	BurnDebuffComponent->Deactivate();
	StunDebuffComponent->Deactivate();
	
	OnDeathDelegate.Broadcast(this);
}

void AAruraCharacterBase::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bIsStunned = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bIsStunned ? 0.f : BaseWalkSpeed;
}

void AAruraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAruraCharacterBase::InitAbilityActorInfo()
{
}

void AAruraCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void AAruraCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttribute, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttribute, 1.f);
	ApplyEffectToSelf(DefaultVitalAttribute, 1.f);
}

FVector AAruraCharacterBase::GetCombatSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_Weapon) && IsValid(Weapon))
	{
		return Weapon->GetSocketLocation(WeaponTipSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_RightHand))
	{
		return GetMesh()->GetSocketLocation(RightHandSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_LeftHand))
	{
		return GetMesh()->GetSocketLocation(LeftHandSocketName);
	}
	if (MontageTag.MatchesTagExact(GameplayTags.CombatSocket_Tail))
	{
		return GetMesh()->GetSocketLocation(TailSocketName);
	}
	return FVector();
}

bool AAruraCharacterBase::IsDead_Implementation() const
{
	return bDead;
}

AActor* AAruraCharacterBase::GetAvatar_Implementation()
{
	return this;
}

TArray<FTaggedMontage> AAruraCharacterBase::GetTaggedMontages_Implementation()
{
	return AttackMontages;
}

UNiagaraSystem* AAruraCharacterBase::GetBloodEffect_Implementation()
{
	return BloodEffect;
}

FTaggedMontage AAruraCharacterBase::GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag)
{
	for (FTaggedMontage TaggedMontage : AttackMontages)
	{
		if (TaggedMontage.MontageTag == MontageTag)
		{
			return TaggedMontage;
		}
	}
	return FTaggedMontage();
}

int32 AAruraCharacterBase::GetMinionCount_Implementation()
{
	return MinionCount;
}

void AAruraCharacterBase::AddToMinionCount_Implementation(int32 Amount)
{
	MinionCount += Amount;
}

ECharacterClass AAruraCharacterBase::GetCharacterClass_Implementation()
{
	return CharacterClass;
}

FOnASCRegistered& AAruraCharacterBase::GetOnAscRegisteredDelegate()
{
	return OnAscRegistered;
}

USkeletalMeshComponent* AAruraCharacterBase::GetWeapon_Implementation()
{
	return Weapon;
}

void AAruraCharacterBase::SetIsBeingShocked_Implementation(bool bInShock)
{
	bIsBeingShocked = bInShock;
}

bool AAruraCharacterBase::IsBeingShocked_Implementation() const
{
	return bIsBeingShocked;
}


void AAruraCharacterBase::Dissolve()
{
	if (IsValid(DissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(DissolveMaterialInstance, this);
		GetMesh()->SetMaterial(0, DynamicMatInst);
		StartDissolveTimeline(DynamicMatInst);
	}
	if (IsValid(WeaponDissolveMaterialInstance))
	{
		UMaterialInstanceDynamic* DynamicMatInst = UMaterialInstanceDynamic::Create(WeaponDissolveMaterialInstance, this);
		Weapon->SetMaterial(0, DynamicMatInst);
		WeaponStartDissolveTimeline(DynamicMatInst);
	}
}

void AAruraCharacterBase::AddCharacterAbilities()
{
	UAuraAbilitySystemComponent* AuraASC = CastChecked<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	AuraASC->AddCharacterAbilities(StartupAbilities);
	AuraASC->AddCharacterPassiveAbilities(StartupPassiveAbilities);
}

void AAruraCharacterBase::OnRep_Stunned()
{
	
}

void AAruraCharacterBase::OnRep_Burned()
{
}

