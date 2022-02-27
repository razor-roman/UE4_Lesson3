// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;
class ATankPlayerController;
class ACannon;

UCLASS()
class TANKOGEDDON_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankPawn();

protected:
	//mesh
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
	UBoxComponent* BoxComponent;
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite,Category="Components")
	UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite,Category="Components")
	UStaticMeshComponent* TurretMesh;
	//USpring
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite,Category="Components")
	USpringArmComponent* SpringARm;
	//Camera
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite,Category="Components")
	UCameraComponent* Camera;
	//Cannon
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent * CannonSetupPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Cannon")
	TSubclassOf<ACannon> CannonClass;
	UPROPERTY()
	ACannon * Cannon;
	void SetupCannon();


	
	//var
	float MoveSpeed = 100;
	float TargetForwardAxisVaue;
	float PitchValue;
	float YawValue;
	float RollValue;
	UPROPERTY(EditInstanceOnly,BlueprintReadWrite,Category="Movement|Speed")
	float InterpolationKey = 0.1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Speed")
	float TurretRotationInterpolationKey = 0.5f;

	float TargetForwardAxisValue;
	float TargetRightAxisValue;
	float CurrentRightAxisValue;

	UPROPERTY()
	ATankPlayerController* TankController;
	
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void Fire();
	void FireSpecial();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void MoveForward(float AxisValue);
	void RotateLeft(float AxisValue);
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
