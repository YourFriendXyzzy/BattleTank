// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed) {
	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f : Barrel Elevate called at speed: %f"), Time, RelativeSpeed);

	auto CRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = CRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	auto Elevation = FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}