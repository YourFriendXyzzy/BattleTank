// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"
 //forward declaration 
class UTankBarrel; // Holds barrel's properties

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKX_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()




protected:
	

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();
	//called when tank aims
	void AimAt(FVector HitLocation, float LaunchSpeed);
	//ref to barrel
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	//TODO add set turret ref

private:	
	UTankBarrel* Barrel = nullptr;
	void MoveBarrelTowards(FVector AimDirection);


};
