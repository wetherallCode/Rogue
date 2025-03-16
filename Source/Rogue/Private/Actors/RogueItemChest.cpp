// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/RogueItemChest.h"

ARogueItemChest::ARogueItemChest()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("LidMesh");
	LidMesh->SetupAttachment(BaseMesh);
}

void ARogueItemChest::BeginPlay()
{
	Super::BeginPlay();
}

void ARogueItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(110.f, 0.f, 0.f));
}

void ARogueItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
