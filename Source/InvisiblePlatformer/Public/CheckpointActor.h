// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckpointActor.generated.h"

class USceneComponent;
class UBoxComponent;
class UCheckpointSubsystem;

UCLASS()
class INVISIBLEPLATFORMER_API ACheckpointActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USceneComponent> SpawnPoint;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> CheckpointArea;

	//When reaching a new checkpoint, the spawn point only changes if the new checkpoint
	//Has a Priority greater or equal to the previously reached spawnpoint.
	//Checkpoints should therefore have ascending priorities.
	UPROPERTY(EditAnywhere)
	int Priority;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UCheckpointSubsystem* GetCheckpointSystem();
	TObjectPtr<UCheckpointSubsystem> CheckpointSystem;

public:	
	// Sets default values for this actor's properties
	ACheckpointActor();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
