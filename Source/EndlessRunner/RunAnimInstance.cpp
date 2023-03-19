// Fill out your copyright notice in the Description page of Project Settings.


#include "RunAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runner.h"

void URunAnimInstance::NativeInitializeAnimation()
{
	if (Pawn == nullptr) {

		Pawn = TryGetPawnOwner();
	}
}

void URunAnimInstance::UpdateAnimationProperties()
{
	if (Pawn == nullptr) {

		Pawn = TryGetPawnOwner();
	}

	if (Pawn) {

		FVector Speed = Pawn->GetVelocity();
		FVector LateralSpeed = FVector(Speed.X, Speed.Y, 0.f);
		MovementSpeed = LateralSpeed.Size();

		bIsinAir = Pawn->GetMovementComponent()->IsFalling();
	}
}
