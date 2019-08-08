// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//no need to protect pointer as is added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet) {

	Barrel = BarrelToSet;
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

void ATank::SetTurretReference(UTankTurret* TurretToSet) {
	TankAimingComponent->SetTurretReference(TurretToSet);
}


void ATank::AimAt(FVector HitLocation) {
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire() {
	if (!Barrel) { return; }

	//spawn projectile at socket on barrel
	FVector SpawnLoc = Barrel->GetSocketLocation(FName("Projectile"));
	FRotator SpawnRot = Barrel->GetSocketRotation(FName("Projectile"));
	GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SpawnLoc, SpawnRot);
	UE_LOG(LogTemp, Warning, TEXT("Firing"));
}