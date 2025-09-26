// Copyright Anas Hanzo Al-Juboori


#include "UI/HUD/LoadScreenHUD.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/ViewModel/MVVM_LoadScreen.h"
#include "UI/Widget/LoadScreenWidget.h"

void ALoadScreenHUD::BeginPlay()
{
	Super::BeginPlay();

	LoadScreenViewModel = NewObject<UMVVM_LoadScreen>(this, LoadScreenViewModelClass);
	LoadScreenViewModel->InitializeLoadSlot();

	LoadScreenWidget = CreateWidget<ULoadScreenWidget>(GetWorld(), LoadScreenWidgetClass);
	LoadScreenWidget->AddToViewport();
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(GetOwningPlayerController(), LoadScreenWidget);
	GetOwningPlayerController()->bShowMouseCursor = true;
	LoadScreenWidget->BlueprintInitializedWidget();
	
	LoadScreenViewModel->LoadData();
}
