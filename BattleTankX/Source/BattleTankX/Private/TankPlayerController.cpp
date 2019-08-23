// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"




void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent) {
		FoundAimingComponent(AimingComponent);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("PLAYER CONTROLLER CANT FIND AIMING COMPONENT"));
		
	}
}

//Tick
void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();

}


ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return; }
	
	FVector HitLocation; //Out Parameter
	if (GetSightRayHitLocation(HitLocation)) { // Has "side-effect", is going to line trace
		GetControlledTank()->AimAt(HitLocation);
			//TODO Tell Controlled Tank To aim at this point
	}
}

// Get world location of linetrace through crosshair.true if hits landscape
 bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
	 // Find crosshair position
	 int32 ViewportSizeX, ViewportSizeY;
	 GetViewportSize(ViewportSizeX, ViewportSizeY);

	 auto CursorLocation = FVector2D((ViewportSizeX * CrosshairXLocation), (ViewportSizeY * CrosshairYLocation));
	 
	 //De-Project screen position of crosshair to world direction
	 FVector LookDirection;
	 if (GetLookDirection(CursorLocation, LookDirection)) {
		 //Line trace along that (look direction), see what we hit (within range)
		 GetLookVectorHitLocation(LookDirection, HitLocation);
	 }
	 
	return true;
}


 bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	 
	 FHitResult HitResult;
	 auto StartLocation = PlayerCameraManager->GetCameraLocation();
	 auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	 if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation,ECollisionChannel::ECC_Visibility)){
		 HitLocation = HitResult.Location;//set hit location and return true
		 return true;
		 }
		 HitLocation = FVector(0);
		return false; //line trace didnt work
 }

 bool ATankPlayerController::GetLookDirection(FVector2D CursorLocation, FVector& LookDirection) const {
	 FVector CameraWorldLocation; // For discarding
	return DeprojectScreenPositionToWorld(CursorLocation.X, CursorLocation.Y, CameraWorldLocation, LookDirection);
 }