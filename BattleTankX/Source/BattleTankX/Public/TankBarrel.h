// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKX_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//-1 is max downward movement and +1 is max upwards
	void Elevate(float RelativeSpeed);
	


private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 8; 

	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationDegrees = 40;

	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationDegrees = 0;
};
