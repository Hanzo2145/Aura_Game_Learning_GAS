// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UAuraUserWidget;
/**
 * 
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	/*Function Declarations*/
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC,APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	
	/*Variables Declarations*/
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

protected:
	/*Function Declarations*/

private:
	/*Variables Declarations*/
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	
};
