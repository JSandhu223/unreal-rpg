

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	virtual void HighlightActor() override;

	virtual void UnHighlightActor() override;

private:
	// This needs to be 250 to render the post process highlight around the enemy (see the 'PP_Highlight' asset)
	int32 StencilValue = 250;
};
