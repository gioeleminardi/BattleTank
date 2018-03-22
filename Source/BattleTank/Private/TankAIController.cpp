// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	ATank *ControlledTank = GetControlledTank();
	if (ControlledTank == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Controlled AI Tank is null"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Controlled AI Tank is: %s"), *(ControlledTank->GetName()));
	}
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
