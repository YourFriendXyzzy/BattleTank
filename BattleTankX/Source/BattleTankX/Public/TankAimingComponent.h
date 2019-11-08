// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enums for aim state
UENUM()
enum class EFiringState : uint8 { Reloading, Aiming, Locked };

 //forward declaration 
class UTankBarrel; // Holds barrel's properties
class UTankTurret; // Holds Turret Properties
class AProjectile; // Holds Projectile Properties

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKX_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()


protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;



public:	
	//allows BP to call fire method
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Fire();
	
	//called to aim at target
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initializer(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	bool IsBarrelMoving();

private:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	//moves the barrel towards the target
	void MoveBarrelTowards(FVector AimDirection);

	//sets up last fire time for use in reload function
	double LastFireTime = 0;

	FVector AimDirection;

	//tick
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)override;

	//beginplay
	virtual void BeginPlay() override;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	// Start of Properties #########################################################################################################################

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	// launch speed
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000; //starting value of 1000m/s

	//how long it takes to reload
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;

	// End of Properties #########################################################################################################################

	
};
