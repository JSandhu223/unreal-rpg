


#include "Character/AuraEnemy.h"


void AAuraEnemy::HighlightActor()
{
	this->GetMesh()->SetRenderCustomDepth(true);
	this->GetMesh()->SetCustomDepthStencilValue(this->StencilValue);
}

void AAuraEnemy::UnHighlightActor()
{
	this->GetMesh()->SetRenderCustomDepth(false);
}
