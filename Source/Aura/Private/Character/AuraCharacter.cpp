// Copyright Anas Hanzo Al-Juboori


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "BlendSpaceAnalysis.h"
#include "InterchangeResult.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Chaos/SoftsSpring.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"


AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeRotation(FRotator(-40.f, 0.f, 0.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>("Camara");
	Camera->SetupAttachment(SpringArm);

	//BoxComponent
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box Component");
	BoxComponent->SetupAttachment(Camera);
	BoxComponent->SetBoxExtent(FVector(SpringArm->TargetArmLength, BoxExtent.Y, BoxExtent.Z));
	
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

int32 AAuraCharacter::GetPlayerLevel()
{
	const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetPlayerLevelVaribale();
}

void AAuraCharacter::SetSpringArmlength(float SpringArmlength)
{
	Super::SetSpringArmlength(SpringArmlength);
	SpringArm->TargetArmLength = FMath::Clamp<float>(SpringArm->TargetArmLength += SpringArmlength, MinSpringArmlength, MaxSpringArmlength);
	BoxComponent->SetBoxExtent(FVector(SpringArm->TargetArmLength, BoxExtent.Y, BoxExtent.Z));
	UE_LOG(LogTemp, Warning, TEXT("SpringArmLength is = %f"), SpringArm->TargetArmLength);
	UE_LOG(LogTemp, Warning, TEXT("BoxExtent.X is = %f"), BoxComponent->GetScaledBoxExtent().X);
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
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
