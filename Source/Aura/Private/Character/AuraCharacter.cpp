


#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"


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

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the SERVER
	this->InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the CLIENT
	this->InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	// The player state is the owner, but the character is the avatar
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);

	// Since we have the player state, we can set this character's inherited fields
	this->AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	this->AttributeSet = AuraPlayerState->GetAttributeSet();
}
