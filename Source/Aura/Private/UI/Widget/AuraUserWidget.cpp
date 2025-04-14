// Copyright Anas Hanzo Al-Juboori


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	//we are setting the widget controller
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
