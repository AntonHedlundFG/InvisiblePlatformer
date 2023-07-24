// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointSubsystem.h"
#include "Kismet/KismetSystemLibrary.h"

bool UCheckpointSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (AActor* OuterActor = Cast<AActor>(Outer))
	{
		return OuterActor->HasAuthority();
	}
	return true;
}

void UCheckpointSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
}

void UCheckpointSubsystem::Deinitialize()
{
}



void UCheckpointSubsystem::RespawnPlayer(APlayerController* PlayerController)
{
	FCheckPoint* SpawnPoint = CurrentSpawnPoints.Find(PlayerController);
	if (!SpawnPoint) return;
	APawn* Pawn = PlayerController->GetPawn();

	if (SpawnPoint->SpawnPointComponent)
	{
		Pawn->SetActorLocation(SpawnPoint->SpawnPointComponent->GetComponentLocation());
		PlayerController->SetControlRotation(SpawnPoint->SpawnPointComponent->GetComponentRotation());
	}
	else
	{
		Pawn->SetActorLocation(SpawnPoint->SpawnPointTransform.GetLocation());
		PlayerController->SetControlRotation(SpawnPoint->SpawnPointTransform.GetRotation().Rotator());
	}

	
}

void UCheckpointSubsystem::UpdateCheckpoint(APlayerController* PlayerController, USceneComponent* SpawnPoint, int Priority)
{
	FCheckPoint* CurrentSpawnPoint = CurrentSpawnPoints.Find(PlayerController);
	if (Priority < (CurrentSpawnPoint ? CurrentSpawnPoint->Priority : 0)) return;

	FCheckPoint NewSpawnPoint;
	NewSpawnPoint.Priority = Priority;
	NewSpawnPoint.SpawnPointComponent = SpawnPoint;
	CurrentSpawnPoints.Add(PlayerController, NewSpawnPoint);
}

void UCheckpointSubsystem::UpdateCheckpointTransform(APlayerController* PlayerController, FTransform SpawnPoint, int Priority)
{
	FCheckPoint* CurrentSpawnPoint = CurrentSpawnPoints.Find(PlayerController);
	if (Priority < (CurrentSpawnPoint ? CurrentSpawnPoint->Priority : 0)) return;

	FCheckPoint NewSpawnPoint;
	NewSpawnPoint.Priority = Priority;
	NewSpawnPoint.SpawnPointTransform = SpawnPoint;
	CurrentSpawnPoints.Add(PlayerController, NewSpawnPoint);
}

void UCheckpointSubsystem::RespawnAllPlayers()
{
	for (TPair<APlayerController*, FCheckPoint> Point : CurrentSpawnPoints)
	{
		RespawnPlayer(Point.Key);
	}
}