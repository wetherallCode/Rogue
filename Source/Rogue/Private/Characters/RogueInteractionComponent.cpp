// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RogueInteractionComponent.h"

#include "Interfaces/RogueGameplayInterface.h"

// Sets default values for this component's properties
URogueInteractionComponent::URogueInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URogueInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void URogueInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URogueInteractionComponent::PrimaryInteract()
{
	APawn* Owner = GetOwner<APawn>();

	FVector EyeLocation;
	FRotator EyeRotation;
	Owner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	const FVector End { EyeLocation + EyeRotation.Vector() * 1000 };

	FCollisionObjectQueryParams ObjectQueryParams;

	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	TArray<FHitResult> Hits;
	float SphereRadius { 30.f };
	FCollisionShape Shape;
	Shape.SetSphere(SphereRadius);


	const FCollisionQueryParams QueryParams;
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);


	for (FHitResult Hit : Hits)
	{
		AActor* HitActor { Hit.GetActor() };
		if (HitActor && HitActor->Implements<URogueGameplayInterface>())
		{
			IRogueGameplayInterface::Execute_Interact(HitActor, Owner);
		}
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, SphereRadius, 8, bBlockingHit ? FColor::Green : FColor::Red, false, 2.f,
		                0, 1.f);
		break;
	}

	DrawDebugLine(GetWorld(), EyeLocation, End, bBlockingHit ? FColor::Green : FColor::Red, false, 2.f, 0, 1);
}
