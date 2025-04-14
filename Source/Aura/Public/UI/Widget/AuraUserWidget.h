// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/*Function Declarations*/
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);


	/*Variables Declarations*/
	
	/* creating a widget controller this way the widget knows who is the controller,
	 * but the controller doesn't care who is the widget*/
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:

	/* when we start the game we want to set the controller of the widget*/
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
