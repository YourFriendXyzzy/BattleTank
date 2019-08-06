// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKX_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATank* GetControlledTank() const;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	


private:
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	void AimTowardsCrosshair(); // move tank baral to aim at the crosshair
	bool GetLookDirection(FVector2D CursorLocation, FVector& LookDirection) const;
	UPROPERTY(EditAnywhere)
		float CrosshairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.3333;
	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000;
};
