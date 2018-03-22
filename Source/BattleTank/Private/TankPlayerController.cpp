// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	ATank *ControlledTank = GetControlledTank();
	if (ControlledTank == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Controlled Tank is null"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank is: %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank *ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; //Out Param
	if (GetSightRayHitLocation(HitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *(HitLocation.ToString()));
	}


	// Get world location with linetrace through crosshair
	// It it hits the landscape
		// Tell controlled tank to aim at this point
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	// Find the crosshair position
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	auto ScreenLocation = FVector2D(
		ViewPortSizeX*CrossHairXRelativePosition,
		ViewPortSizeY*CrossHairYRelativePosition
	);
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// Linetrace along that look direction and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
	FVector CameraWorldLocation;
	// Deproject the screen position of the crosshair to a world direction
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &OutHitLocation) const
{
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;

	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECC_Visibility)
		)
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	return false;
}
