// Copyright Anas Hanzo Al-Juboori


#include "AbilitySystem/Abilities/AuraFireBlast.h"

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Actor/AuraFireBall.h"

FString UAuraFireBlast::GetDescription(int32 Level)
{
	const float ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
		//Title
		"<Title>FIRE BLAST</>"

		//Level
		"\n\n<Default>Level: </><Level>%d</>"

		//ManaCost
		"\n<Small>Mana Cost: </><ManaCost>%.1f</>"

		//Cooldown
		"\n<Small>Cooldown: </><Cooldown>%0.2f</>"

		//Description
		"\n\n<Default>Launches %d </>"
		"\n<Default>fire balls in all direction, each coming back and</>"
		"<Default> exploding upon return, causing </>"

		//Damage
		"<Damage>%0.2f </><Default>radial fire Damage with a chance to burn</>"),

		//Values
		Level,
		ManaCost,
		Cooldown,
		NumFireBalls,
		ScaledDamage);
}

FString UAuraFireBlast::GetNextLevelDescription(int32 Level)
{
	const float ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	return FString::Printf(TEXT(
		//Title
		"<Title>NEXT LEVEL</>"

		//Level
		"\n\n<Default>Level: </><Level>%d</>"

		//ManaCost
		"\n<Small>Mana Cost: </><ManaCost>%.1f</>"

		//Cooldown
		"\n<Small>Cooldown: </><Cooldown>%0.2f</>"

		//Description
		"\n\n<Default>Launches %d </>"
		"\n<Default>fire balls in all direction, each coming back and</>"
		"<Default> exploding upon return, causing </>"

		//Damage
		"<Damage>%0.2f </><Default>radial fire Damage with a chance to burn</>"),

		//Values
		Level,
		ManaCost,
		Cooldown,
		NumFireBalls,
		ScaledDamage);
}

TArray<AAuraFireBall*> UAuraFireBlast::SpawnFireBalls()
{
	TArray<AAuraFireBall*> FireBalls;
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	TArray<FRotator>Rotators = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, 360.f, NumFireBalls);

	for (const FRotator& Rotator : Rotators)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(Location);
		SpawnTransform.SetRotation(Rotator.Quaternion());
		AAuraFireBall* FireBall = GetWorld()->SpawnActorDeferred<AAuraFireBall>(FireBallClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			CurrentActorInfo->PlayerController->GetPawn(),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		
		FireBall->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
		FireBall->ReturnToActor = GetAvatarActorFromActorInfo();

		FireBall->ExplosionDamageParams = MakeDamageEffectParamsFromClassDefaults();
		FireBall->SetOwner(GetAvatarActorFromActorInfo());

		FireBalls.Add(FireBall);
		FireBall->FinishSpawning(SpawnTransform);
	}
	return FireBalls;
}
