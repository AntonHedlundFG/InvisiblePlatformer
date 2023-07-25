// Copyright Epic Games, Inc. All Rights Reserved.


#include "InvisiblePlatformerGameModeBase.h"
#include "GameFramework/PlayerStart.h"
#include "EngineUtils.h"
#include "CheckpointSubsystem.h"

AActor* AInvisiblePlatformerGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	AActor* FoundPlayerStart = nullptr;
	
	//Loop through all PlayerStarts to find one whose tag contains the number of
	//the player to be spawned (1, then 2).
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		APlayerStart* PlayerStart = *It;
		if (PlayerStart->PlayerStartTag.ToString().Contains(FString::FromInt(NextPlayerNumberToSpawn)))
		{
			FoundPlayerStart = PlayerStart;
			break;
		}
	}
	NextPlayerNumberToSpawn++;

	//If we fail to find a PlayerStart above, simply return a PlayerStart using normal
	//GameMode functionality.
	if (!FoundPlayerStart)
	{
		FoundPlayerStart = Super::ChoosePlayerStart_Implementation(Player);
	}

	//If everything has failed, simply return nullptr.
	if (!FoundPlayerStart)
	{
		return nullptr;
	}

	//Assign the spawnpoint as the players starting checkpoint
	if (UCheckpointSubsystem* CPSS = GetGameInstance()->GetSubsystem<UCheckpointSubsystem>())
	{
		CPSS->UpdateCheckpointTransform(Cast<APlayerController>(Player), FoundPlayerStart->GetTransform(), 0);
	}
	

	return FoundPlayerStart;
}