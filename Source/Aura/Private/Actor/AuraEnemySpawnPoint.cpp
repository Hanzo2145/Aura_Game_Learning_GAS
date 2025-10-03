// Copyright Anas Hanzo Al-Juboori


#include "Actor/AuraEnemySpawnPoint.h"
#include "Character/AuraEnemy.h"

void AAuraEnemySpawnPoint::SpawnEnemy(TArray<FEnemyClasses> InEnemyClasses)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FEnemyClasses EnemyClass = GetRandomEnemyClass(InEnemyClasses);
	
	AAuraEnemy* Enemy = GetWorld()->SpawnActorDeferred<AAuraEnemy>(EnemyClass.EnemyClass, GetActorTransform());
	Enemy->SetEnemyLevel(EnemyClass.EnemyLevel);
	if (EnemyClass.CharacterClass == ECharacterClass::None)
	{
		GEngine->AddOnScreenDebugMessage(1 , 15.f, FColor::Magenta,
			FString::Printf(
				TEXT("The Character for %s is not Set Please Set the character class to avoid errors"),
				*Enemy->GetActorNameOrLabel()));
	}
	else
	{
		Enemy->SetCharacterClass(EnemyClass.CharacterClass);
	}
	Enemy->FinishSpawning(GetActorTransform());
	Enemy->SpawnDefaultController();
}

FEnemyClasses AAuraEnemySpawnPoint::GetRandomEnemyClass(TArray<FEnemyClasses> InEnemyClasses)
{
	if (InEnemyClasses.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(1 , 15.f, FColor::Magenta,
			FString::Printf(
				TEXT("EnemyClasses array is empty, Please Make sure to fill in EnemyClasses in side of the Aura Enemy Spawn Volume")));
		return FEnemyClasses();
	}
	int32 RandomIndex = FMath::RandRange(0 , InEnemyClasses.Num() - 1);
	return InEnemyClasses[RandomIndex];
}
