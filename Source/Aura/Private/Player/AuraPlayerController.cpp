


#include "Player/AuraPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Interaction/EnemyInterface.h"


AAuraPlayerController::AAuraPlayerController()
{
	this->bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	this->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();

	// DEBUG
	//UE_LOG(LogTemp, Warning, TEXT("HitActor = %s"), *CursorHit.GetActor()->GetName());

	/**
	* Line trace from cursor. There are several scenarios:
	*  (a) LastActor is null && ThisActor is null
	*    - Do nothing
	* 
	*  (b) LastActor is null, but ThisActor is valid (is an enemy interace)
	*    - This means We're hovering over ThisActor for the first time
	*    - Highlight ThisActor
	* 
	*  (c) LastActor is valid, but ThisActor is null
	*    - This means we're no longer hovering over an enemy
	*    - Unhighlight LastActor
	* 
	*  (d) LastActor AND ThisActor are valid, but LastActor != ThisActor
	*    - Unhighlight LastActor and highlight ThisActor
	* 
	*  (e) LastActor AND ThisActor are valid, and LastActor = ThisActor
	*    - Do nothing
	**/

	if (LastActor == nullptr)
	{
		// Case (b)
		if (ThisActor != nullptr)
		{
			ThisActor->HighlightActor();
		}
	}

	else
	{
		// Case (c)
		if (ThisActor == nullptr)
		{
			LastActor->UnHighlightActor();
		}

		else
		{
			// Case (d)
			if (LastActor != ThisActor)
			{
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
		}
	}
}


void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Assert that the input mapping context is set from the character blueprint BP_AuraCharacter
	check(AuraContext);
	// Add the mapping context to the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}

	// Configure cursor settings
	this->bShowMouseCursor = true;
	this->DefaultMouseCursor = EMouseCursor::Default;
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(this->InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = this->GetControlRotation();
	const FRotator YawRotation = FRotator(0.0f, Rotation.Yaw, 0.0f);

	// These are unit vector points along the specified axis
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = this->GetPawn<APawn>())
	{
		// Scale by the y-component of InputActionValue since forward and backward movement will happen along the y-axis
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
