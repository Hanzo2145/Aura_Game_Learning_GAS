// Copyright Anas Hanzo Al-Juboori


#include "Character/AuraCharacter.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"
#include "NiagaraComponent.h"

AAuraCharacter::AAuraCharacter()
{
	//SpringArm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeRotation(FRotator(-40.f, 0.f, 0.0f));
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->bDoCollisionTest = false;

	//Camera
	Camera = CreateDefaultSubobject<UCameraComponent>("Camara");
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	//BoxComponent
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Component");
	BoxComponent->SetupAttachment(Camera);
	BoxComponent->SetBoxExtent(FVector(SpringArm->TargetArmLength, BoxExtent.Y, BoxExtent.Z));

	//Level Up Niagara Component
	LevelUpNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("Level Up Niagara Component");
	LevelUpNiagaraComponent->SetupAttachment(GetRootComponent());
	LevelUpNiagaraComponent->bAutoActivate = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;


	//CharacterClass
	
	CharacterClass = ECharacterClass::Elementalist;
	
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// Init Ability Actor Info for the Server
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// Init Ability Actor Info for the Client
	InitAbilityActorInfo();
}

int32 AAuraCharacter::GetPlayerLevel_Implementation()
{
	return GetAuraPlayerState()->GetPlayerLevel();
}

void AAuraCharacter::SetSpringArmlength(float SpringArmlength)
{
	Super::SetSpringArmlength(SpringArmlength);
	SpringArm->TargetArmLength = FMath::Clamp<float>(SpringArm->TargetArmLength += SpringArmlength, MinSpringArmlength, MaxSpringArmlength);
	BoxComponent->SetBoxExtent(FVector(SpringArm->TargetArmLength, BoxExtent.Y, BoxExtent.Z));
}

void AAuraCharacter::AddToXP_Implementation(int32 InXP)
{
	return GetAuraPlayerState()->AddToXP(InXP);
}

void AAuraCharacter::LevelUp_Implementation()
{
	MulticastLevelUpParticles();
}

void AAuraCharacter::MulticastLevelUpParticles_Implementation() const
{
	if (IsValid(LevelUpNiagaraComponent))
	{
		const FVector CameraLocation = Camera->GetComponentLocation();
		const FVector NiagaraSystemLocation = LevelUpNiagaraComponent->GetComponentLocation();
		const FRotator ToCameraRotation = (CameraLocation - NiagaraSystemLocation).Rotation();
		LevelUpNiagaraComponent->SetWorldRotation(ToCameraRotation);
		LevelUpNiagaraComponent->Activate(true);
	}
}

int32 AAuraCharacter::GetXP_Implementation() const
{
	return GetAuraPlayerState()->GetXP();
}

int32 AAuraCharacter::FindLevelForXP_Implementation(const int32 InXP)
{
	return GetAuraPlayerState()->LevelUpInfo->FindLevelForXP(InXP);
}

int32 AAuraCharacter::GetAttributesPointsRewards_Implementation(const int32 InLevel) const
{
	return GetAuraPlayerState()->LevelUpInfo->LevelUpInformation[InLevel].AttributePointReward;
}

int32 AAuraCharacter::GetSpellPointsRewards_Implementation(const int32 InLevel) const
{
	return GetAuraPlayerState()->LevelUpInfo->LevelUpInformation[InLevel].SpellPointReward;
}

void AAuraCharacter::AddToPlayerLevel_Implementation(const int32 InPlayerLevel)
{
	GetAuraPlayerState()->AddToLevel(InPlayerLevel);
	
	if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(GetAbilitySystemComponent()))
	{
		AuraASC->UpdateAbilityStatuses(GetAuraPlayerState()->GetPlayerLevel());
	}
}

void AAuraCharacter::AddToAttributesPoints_Implementation(const int32 InAttributesPoints)
{
	GetAuraPlayerState()->AddAttributePoints(InAttributesPoints);
}

void AAuraCharacter::AddToSpellPoints_Implementation(const int32 InSpellPoints)
{
	GetAuraPlayerState()->AddSpellPoints(InSpellPoints);
}

int32 AAuraCharacter::GetAttributesPoints_Implementation() const
{
	return GetAuraPlayerState()->GetAttributePoints();
}

int32 AAuraCharacter::GetSpellPoints_Implementation() const
{
	return GetAuraPlayerState()->GetSpellPoints();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetAuraPlayerState();
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
	AbilitySystemComponent->InitAbilityActorInfo(AuraPlayerState, this);
	Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefaultAttributes();
}

AAuraPlayerState* AAuraCharacter::GetAuraPlayerState() const
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState;
}


