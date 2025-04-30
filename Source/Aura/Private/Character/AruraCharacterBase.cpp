// Copyright Anas Hanzo Al-Juboori


#include "Character/AruraCharacterBase.h"

AAruraCharacterBase::AAruraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon Mesh");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

UAbilitySystemComponent* AAruraCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAruraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAruraCharacterBase::InitAbilityActorInfo()
{
}

