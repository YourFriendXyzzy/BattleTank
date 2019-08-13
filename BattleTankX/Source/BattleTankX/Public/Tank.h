// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

UCLASS()
class BATTLETANKX_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Function block ###############################################################################################################################
	
	//set what barrel is barrel
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	//set what turret is turret
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* TurretToSet);
	// lets you call fire method from blueprint to set up inputs
	UFUNCTION(BlueprintCallable, Category = Setup)
		void Fire();



	//End of Function Block ###########################################################################################################################

	//called to aim at target
	void AimAt(FVector HitLocation);

private:
	// Start of Properties #########################################################################################################################

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;
	// launch speed
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 400000; //starting value of 1000m/s
	//how long it takes to reload
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSeconds = 3;

	// End of Properties #########################################################################################################################





	// Sets default values for this pawn's properties
	ATank();
	// sets up baral pointer
	UTankBarrel* Barrel = nullptr;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//sets up last fire time for use in reload function
	double LastFireTime = 0;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//called when you aim
	UTankAimingComponent* TankAimingComponent = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = Firing)
	UTankMovementComponent* TankMovementComponent = nullptr;



};
