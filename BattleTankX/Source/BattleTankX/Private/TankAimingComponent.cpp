// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	if (!Barrel) { return; }
	
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	if (UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	)) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim Solution Found"), Time);
	}
	else {
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No Aim Solution Found"),Time);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) {
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	//figure out dif between current barral rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsBarrelRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsBarrelRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s "), *AimAsBarrelRotator.ToString());


	//move baral to the right amount this frame
	//givn max elivation speed and the frame time
	Barrel->Elevate(DeltaRotator.Pitch); //TODO remove magic number
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection) {
	//figure out dif between current barral rotation and aim direction
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsTurretRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsTurretRotator - TurretRotator;
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s "), *AimAsBarrelRotator.ToString());


	//move baral to the right amount this frame
	//givn max elivation speed and the frame time
	Turret->Rotate(DeltaRotator.Yaw); //TODO remove magic number
}