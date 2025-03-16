// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/RogueCharacter.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Characters/RogueInteractionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectiles/RogueMagicProjectile.h"

ARogueCharacter::ARogueCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true; // This allows the camera to move and not the player

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	InteractionComponent = CreateDefaultSubobject<URogueInteractionComponent>("InteractionComponent");
}

void ARogueCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ARogueCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARogueCharacter::Move(const FInputActionValue& InputActionValue)
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.f;
	ControlRotation.Roll = 0.f;

	const FVector2D MovementVector = InputActionValue.Get<FVector2d>();

	AddMovementInput(ControlRotation.Vector(), MovementVector.Y);

	const FVector RightVector = UKismetMathLibrary::GetRightVector(ControlRotation);
	AddMovementInput(RightVector, MovementVector.X);
}


void ARogueCharacter::Turn(const FInputActionValue& InputActionValue)
{
	const FVector2D TurnValue = InputActionValue.Get<FVector2D>();
	AddControllerYawInput(TurnValue.X);
	AddControllerPitchInput(TurnValue.Y);
}

void ARogueCharacter::PrimaryAttack()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	const FTransform SpawnTransform(GetControlRotation(), HandLocation);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform, SpawnParams);
}

void ARogueCharacter::Interact()
{
	GetComponentByClass<URogueInteractionComponent>()->PrimaryInteract();
}


void ARogueCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(RogueContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
		(GetController<APlayerController>()->GetLocalPlayer());

	check(Subsystem);
	Subsystem->AddMappingContext(RogueContext, 0);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARogueCharacter::Move);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ARogueCharacter::Jump);
	EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ARogueCharacter::Turn);
	EnhancedInputComponent->BindAction(PrimaryAttackAction, ETriggerEvent::Started, this, &ARogueCharacter::PrimaryAttack);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ARogueCharacter::Interact);
}
