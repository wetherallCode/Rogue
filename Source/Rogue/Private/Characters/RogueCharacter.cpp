// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RogueCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ARogueCharacter::ARogueCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
}

void ARogueCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ARogueCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARogueCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
