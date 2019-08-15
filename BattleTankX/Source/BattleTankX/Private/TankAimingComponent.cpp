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
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}

void UTankAimingComponent::Initializer(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
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
		//MoveTurretTowards(AimDirection);
	}
}



void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	if (!Barrel || !Turret) { return; }
	//figure out dif between current barral rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}
/*
void UTankAimingComponent::MoveTurretTowards(FVector AimDirection) {
	//figure out dif between current barral rotation and aim direction
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsTurretRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsTurretRotator - TurretRotator;
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s "), *AimAsBarrelRotator.ToString());


	//move baral to the right amount this frame
	//givn max elivation speed and the frame time
	 //TODO remove magic number
	Turret->Rotate(DeltaRotator.Yaw);
}*/