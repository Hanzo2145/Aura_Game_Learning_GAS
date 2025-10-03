// Copyright Anas Hanzo Al-Juboori


#include "Actor/AuraEnemySpawnVolume.h"

#include "Components/BoxComponent.h"
#include "Interaction/PlayerInterface.h"


AAuraEnemySpawnVolume::AAuraEnemySpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Box = CreateDefaultSubobject<UBoxComponent>(FName("Box"));
	SetRootComponent(Box);
	Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Box->SetCollisionObjectType(ECC_WorldStatic);
	Box->SetCollisionResponseToAllChannels(ECR_Ignore);
	Box->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AAuraEnemySpawnVolume::LoadActor_Implementation()
{
	if (bReached)
	{
		Destroy();
	}
}

void AAuraEnemySpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &AAuraEnemySpawnVolume::OnBoxOverlap);
}

void AAuraEnemySpawnVolume::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UPlayerInterface>()) return;
	
	if (bSaveThisActor) bReached = true;

	for (AAuraEnemySpawnPoint* SpawnPoint : SpawnPoints)
	{
		if (IsValid(SpawnPoint))
		{
			SpawnPoint->SpawnEnemy(EnemiesToSpawn);
		}
	}
	Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


