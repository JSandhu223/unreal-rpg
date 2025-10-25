


#include "UI/WidgetController/OverlayWidgetController.h"


void UOverlayWidgetController::BroadcastInitialValues()
{
	// TODO: broadcast the value of the health attribute instead of hardcoding a value
	OnHealthChanged.Broadcast(100.0f);
}
