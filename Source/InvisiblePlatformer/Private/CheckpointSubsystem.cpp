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
	Pawn->SetActorLocation(SpawnPoint->Transform.GetLocation());
	PlayerController->SetControlRotation(SpawnPoint->Transform.GetRotation().Rotator());
}

void UCheckpointSubsystem::UpdateCheckpoint(APlayerController* PlayerController, FTransform Transform, int Priority)
{
	FCheckPoint* CurrentSpawnPoint = CurrentSpawnPoints.Find(PlayerController);
	if (Priority < (CurrentSpawnPoint ? CurrentSpawnPoint->Priority : 0)) return;

	FCheckPoint NewSpawnPoint;
	NewSpawnPoint.Priority = Priority;
	NewSpawnPoint.Transform = Transform;
	CurrentSpawnPoints.Add(PlayerController, NewSpawnPoint);
}

void UCheckpointSubsystem::RespawnAllPlayers()
{
	for (TPair<APlayerController*, FCheckPoint> Point : CurrentSpawnPoints)
	{
		RespawnPlayer(Point.Key);
	}
}