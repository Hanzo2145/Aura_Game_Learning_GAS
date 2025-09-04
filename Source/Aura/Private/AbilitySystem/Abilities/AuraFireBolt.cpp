// Copyright Anas Hanzo Al-Juboori


#include "AbilitySystem/Abilities/AuraFireBolt.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			//Title
			"<Title>FIRE BOLT</>"

			//Level
			"\n\n<Default>Level: </><Level>%d</>"

			//ManaCost
			"\n<Small>Mana Cost: </><ManaCost>%.1f</>"

			//Cooldown
			"\n<Small>Cooldown: </><Cooldown>%0.2f</>"

			//Description
			"\n\n<Default>Launches a bolt of fire, exploding on impact and dealing: </>"

			//Damage
			"<Damage>%d </><Default>fire Damage with a chance to burn</>"),

			//Values
			Level,
			ManaCost,
			Cooldown,
			ScaledDamage);
	}
	else
	{
		return FString::Printf(TEXT(
			//Title
			"<Title>FIRE BOLT</>"

			//Level
			"\n\n<Default>Level: </><Level>%d</>"

			//ManaCost
			"\n<Small>Mana Cost: </><ManaCost>%.1f</>"

			//Cooldown
			"\n<Small>Cooldown: </><Cooldown>%0.2f</>"

			//Description
			"\n\n<Default>Launches </>"
			"<Level>%d </>"
			"<Default>bolts of fire, exploding on impact and dealing: </>"

			//Damage
			"<Damage>%d </><Default>fire Damage with a chance to burn</>"),

			//Values
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, NumProjectiles),
			ScaledDamage);
	}

}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
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
		"\n\n<Default>Launches </>"
		"<Level>%d </>"
		"<Default>bolts of fire, exploding on impact and dealing: </>"

		//Damage
		"<Damage>%d </><Default>fire Damage with a chance to burn</>"),

		//Values
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, NumProjectiles),
		ScaledDamage);

}