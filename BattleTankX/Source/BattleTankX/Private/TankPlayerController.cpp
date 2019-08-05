// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"




void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Controlled Tank Found!!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller Possessing: %s"), *(ControlledTank->GetName()));
	}
	
}

//Tick
void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("tick-tock"));
	AimTowardsCrosshair();

}



ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return; }

	//get world location if linetrece through crosshair
		//if that hits landscape
			//Tell tank to aim at this point
}