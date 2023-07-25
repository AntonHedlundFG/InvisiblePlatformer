// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InvisiblePlatformerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class INVISIBLEPLATFORMER_API AInvisiblePlatformerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	
protected:
	UPROPERTY()
	int NextPlayerNumberToSpawn = 1;

};
