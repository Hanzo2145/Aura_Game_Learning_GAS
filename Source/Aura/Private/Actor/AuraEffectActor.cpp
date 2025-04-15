// Copyright Anas Hanzo Al-Juboori


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Components/SphereComponent.h"


AAuraEffectActor::AAuraEffectActor()
{

	PrimaryActorTick.bCanEverTick = false;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	SetRootComponent(Mesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere Component");
	Sphere->SetupAttachment(GetRootComponent());
}

void AAuraEffectActor::OnOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO : Change this to Apply GamePlay Effect. For Now, USing ConstCast as a Hack
	if (IAbilitySystemInterface* AscInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AscInterface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		
		UAuraAttributeSet* MutableAuraAttributeSet =  const_cast<UAuraAttributeSet*>(AuraAttributeSet);
		MutableAuraAttributeSet->SetHealth(AuraAttributeSet->GetHealth() + 25.f);
		MutableAuraAttributeSet->SetMana(AuraAttributeSet->GetMana() - 15.f);
		Destroy();
	}
}

void AAuraEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnOverLap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::EndOverlap);
}

