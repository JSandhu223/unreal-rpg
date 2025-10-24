


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"


void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	// If an overlay widget controller doesn't exist, then this getter will create one
	if (this->OverlayWidgetController == nullptr)
	{
		this->OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		this->OverlayWidgetController->SetWidgetControllerParams(WCParams);
	}

	return this->OverlayWidgetController;
}