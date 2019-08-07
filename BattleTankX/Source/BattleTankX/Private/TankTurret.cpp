// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed) {
	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f : Barrel Elevate called at speed: %f"), Time, RelativeSpeed);

	auto CRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = CRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;

	//auto Rotation = FMath::Clamp(RawNewRotation, MaxRotationalDegrees, MinRotationalDegrees);

	SetRelativeRotation(FRotator(0, Rotation, 0));
}