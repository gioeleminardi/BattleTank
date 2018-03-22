// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


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

ATank *ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}