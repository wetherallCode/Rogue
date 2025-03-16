// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "RogueCharacter.generated.h"

class URogueInteractionComponent;
class ARogueMagicProjectile;
class UCameraComponent;
class USpringArmComponent;
class UInputComponent;

UCLASS()
class ROGUE_API ARogueCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARogueCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<URogueInteractionComponent> InteractionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> TurnAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> PrimaryAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> InteractAction;

	UFUNCTION()
	void Move(const FInputActionValue& InputActionValue);


	UFUNCTION()
	void Turn(const FInputActionValue& InputActionValue);

	UFUNCTION()
	void PrimaryAttack();

	UFUNCTION()
	void Interact();

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> RogueContext;

	UPROPERTY(EditAnywhere, Category="Attack")
	TSubclassOf<ARogueMagicProjectile> ProjectileClass;
};
