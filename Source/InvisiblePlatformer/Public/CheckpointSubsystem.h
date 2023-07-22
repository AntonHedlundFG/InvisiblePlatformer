// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CheckpointSubsystem.generated.h"

USTRUCT()
struct FCheckPoint
{
    GENERATED_BODY()

public:
    UPROPERTY()
    FTransform Transform;

    UPROPERTY()
    int Priority;
};

/**
 * 
 */
UCLASS()
class INVISIBLEPLATFORMER_API UCheckpointSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:

    virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    UFUNCTION(BlueprintCallable)
    void RespawnPlayer(APlayerController* PlayerController);

    UFUNCTION(BlueprintCallable)
    void RespawnAllPlayers();

    UFUNCTION(BlueprintCallable)
    void UpdateCheckpoint(APlayerController* PlayerController, FTransform Transform, int Priority);
    
protected:

    UPROPERTY()
    TMap<APlayerController*, FCheckPoint> CurrentSpawnPoints;

};
