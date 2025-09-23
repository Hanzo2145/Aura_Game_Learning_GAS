// Copyright Anas Hanzo Al-Juboori


#include "AbilitySystem/Abilities/Electrocute.h"

FString UElectrocute::GetDescription(int32 Level)
{
	const float ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			//Title
			"<Title>ELECTROCUTE</>"

			//Level
			"\n\n<Default>Level: </><Level>%d</>"

			//ManaCost
			"\n<Small>Mana Cost: </><ManaCost>%.1f</>"

			//Cooldown
			"\n<Small>Cooldown: </><Cooldown>%0.2f</>"

			//Description
			"\n\n<Default>Emits a beam of lightning, connecting with the target, repeatedly causing </>"

			//Damage
			"<Damage>%0.2f</><Default> lighting Damage with a chance to STUN</>"),

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
			"<Title>ELECTROCUTE</>"

			//Level
			"\n\n<Default>Level: </><Level>%d</>"

			//ManaCost
			"\n<Small>Mana Cost: </><ManaCost>%.1f</>"

			//Cooldown
			"\n<Small>Cooldown: </><Cooldown>%0.2f</>"

			//Description
			"\n\n<Default>Emits a beam of lightning propagating to </>"
			"<Level>%d </>"
			"<Default>additional targets nearby, causing </>"

			//Damage
			"<Damage>%0.2f </><Default>lightning Damage with a chance to STUN</>"),

			//Values
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, MaxNumShockTargets - 1),
			ScaledDamage);
	}
}

FString UElectrocute::GetNextLevelDescription(int32 Level)
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
			"\n\n<Default>Emits a beam of lightning propagating to </>"
			"<Level>%d </>"
			"<Default>additional targets nearby, causing </>"

			//Damage
			"<Damage>%0.2f </><Default>lightning Damage with a chance to STUN</>"),

			//Values
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, MaxNumShockTargets - 1),
			ScaledDamage);
}
