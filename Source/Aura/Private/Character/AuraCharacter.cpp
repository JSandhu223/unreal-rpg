


#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


AAuraCharacter::AAuraCharacter()
{
	UCharacterMovementComponent* MovementComp = this->GetCharacterMovement();
	MovementComp->bOrientRotationToMovement = true;
	MovementComp->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	MovementComp->bConstrainToPlane = true;
	MovementComp->bSnapToPlaneAtStart = true;

	this->bUseControllerRotationPitch = false;
	this->bUseControllerRotationRoll = false;
	this->bUseControllerRotationYaw = false;
}
