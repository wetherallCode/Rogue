// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/RogueExplodingBarrel.h"

#include "PhysicsEngine/RadialForceComponent.h"

ARogueExplodingBarrel::ARogueExplodingBarrel()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Barrel");
	SetRootComponent(StaticMeshComponent);

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForceComponent->SetupAttachment(StaticMeshComponent);

	RadialForceComponent->ImpulseStrength = 2000.f;
	RadialForceComponent->bImpulseVelChange = true;
	RadialForceComponent->Radius = 700.f;
}

void ARogueExplodingBarrel::BeginPlay()
{
	Super::BeginPlay();
}

void ARogueExplodingBarrel::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	RadialForceComponent->FireImpulse();
}


void ARogueExplodingBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
