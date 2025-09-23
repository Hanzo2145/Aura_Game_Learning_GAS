// Copyright Anas Hanzo Al-Juboori


#include "AbilitySystem/Abilities/ArcaneShards.h"

FString UArcaneShards::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			//Title
			"<Title>ARCANE SHARDS</>"

			//Level
			"\n\n<Default>Level: </><Level>%d</>"

			//ManaCost
			"\n<Small>Mana Cost: </><ManaCost>%.1f</>"

			//Cooldown
			"\n<Small>Cooldown: </><Cooldown>%0.2f</>"

			//Description
			"\n\n<Default>Summon a shard of arcane energy, causing </>"

			//Damage
			"<Damage>%d</><Default> radial Arcane damage at the shard origin, knocking back enemies</>"),

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
			"<Title>ARCANE SHARDS</>"

			//Level
			"\n\n<Default>Level: </><Level>%d</>"

			//ManaCost
			"\n<Small>Mana Cost: </><ManaCost>%.1f</>"

			//Cooldown
			"\n<Small>Cooldown: </><Cooldown>%0.2f</>"

			//Description
			"\n\n<Default>Summon </>"
			"<Level>%d </>"
			"<Default>shards of arcane energy, causing </>"

			//Damage
			"<Damage>%d </><Default>Arcane Damage at the shard origin, knocking back enemies</>"),

			//Values
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, MaxNumShards),
			ScaledDamage);
	}
}

FString UArcaneShards::GetNextLevelDescription(int32 Level)
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
		"\n\n<Default>Summon </>"
		"<Level>%d </>"
		"<Default>shards of arcane energy, causing </>"

		//Damage
		"<Damage>%d </><Default>Arcane Damage at the shard origin, knocking back enemies</>"),

		//Values
		Level,
		ManaCost,
		Cooldown,
		FMath::Min(Level, MaxNumShards),
		ScaledDamage);
}
