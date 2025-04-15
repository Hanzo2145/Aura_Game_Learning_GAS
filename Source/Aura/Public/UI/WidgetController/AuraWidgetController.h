// Copyright Anas Hanzo Al-Juboori

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

/*
 * this is a struct that allow us to set the 4 Variables that we created
*	 * 1. Info from the player Controller
	 * 2. Info from Player State
	 * 3. Info from Ability System Component
	 * 4. Info from Attribute set
 */
USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()


	// the job of this Struct is to set the values of PlayerController, PlayerState, AbilitySystemComponenet, and AttributeSet
	FWidgetControllerParams() {}
	// in this Constructor we are setting these values
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
	: PlayerController(PC), PlayerState(PS), ABilitySystemComponent(ASC), AttributeSet(AS){}


	// we need to declare the Values and create Variable of the 4 types so can set them in the constructor
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> ABilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
};
/**
 * 
 */
UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()
public:
	/*
	 * Functions Declarations
	 */
	
	// this function is used to set the values of the 4 variables that we created in the constructor
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);
	virtual void BroadcastInitialValues();
	virtual void BindCallbacksToDependancies();
protected:

	/*Variables Declarations*/

	/*in this controller we need 4 different type of info that allows the controller to share the data from
	 * 1. Info from the player Controller
	 * 2. Info from Player State
	 * 3. Info from Ability System Component
	 * 4. Info from Attribute set
	 */
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;
};
