// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageTextComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UDamageTextComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	/*
	 * Function Declarations
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Combat")
	void SetDamageText(float Damage, bool blockedHit, bool bCriticalHit);
};
