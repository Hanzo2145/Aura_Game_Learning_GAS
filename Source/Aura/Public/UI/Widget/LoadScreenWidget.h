// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API ULoadScreenWidget : public UUserWidget
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BlueprintInitializedWidget();
};
