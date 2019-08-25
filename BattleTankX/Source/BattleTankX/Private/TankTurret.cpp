// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed) {

	auto CRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = CRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;

	//auto Rotation = FMath::Clamp(RawNewRotation, MaxRotationalDegrees, MinRotationalDegrees);

	SetRelativeRotation(FRotator(0, Rotation, 0));
}