// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/RogueGameplayInterface.h"
#include "RogueItemChest.generated.h"

UCLASS()
class ROGUE_API ARogueItemChest : public AActor, public IRogueGameplayInterface
{
	GENERATED_BODY()

public:
	ARogueItemChest();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float TargetPitch { 110.f };

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> LidMesh;

private:
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};
