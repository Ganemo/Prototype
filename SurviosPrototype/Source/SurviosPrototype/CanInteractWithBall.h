#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Ball.h"
#include "CanInteractWithBall.generated.h"

UINTERFACE(BlueprintType)
class SURVIOSPROTOTYPE_API UCanInteractWithBall : public UInterface
{
	GENERATED_BODY()
};

class SURVIOSPROTOTYPE_API ICanInteractWithBall
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "BallInteraction")
	void ContactWithBall_Begin(ABall* ball);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "BallInteraction")
	void ContactWithBall_End(ABall* ball);
};

