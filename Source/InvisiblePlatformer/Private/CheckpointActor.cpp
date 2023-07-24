// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointActor.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "CheckpointSubsystem.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ACheckpointActor::ACheckpointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(FName("SpawnPoint"));
	SetRootComponent(SpawnPoint);

	CheckpointArea = CreateDefaultSubobject<UBoxComponent>(FName("CheckpointArea"));
	CheckpointArea->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACheckpointActor::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		CheckpointArea->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointActor::OverlapBegin);
	}
	
}

// Called every frame
void ACheckpointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpointActor::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* Pawn = Cast<APawn>(OtherActor);
	if (!Pawn) return;
	APlayerController* PC = Pawn->GetController<APlayerController>();
	if (!PC) return;
	if (!GetCheckpointSystem()) return;

	GetCheckpointSystem()->UpdateCheckpoint(PC, SpawnPoint, Priority);
}

UCheckpointSubsystem* ACheckpointActor::GetCheckpointSystem()
{
	if (!CheckpointSystem)
	{
		CheckpointSystem = GetWorld()->GetGameInstance()->GetSubsystem<UCheckpointSubsystem>();
	}
	return CheckpointSystem;
}