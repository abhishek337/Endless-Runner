// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runner.generated.h"

UCLASS()
class ENDLESSRUNNER_API ARunner : public ACharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USceneComponent* SpawnPoint;

private:

	UPROPERTY(VisibleInstanceOnly)
		class AEndlessRunnerGameModeBase* RunGameMode;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Assets")
		class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MoveDownImpulse = -1000.f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
		int32 CurrentLane = 1;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
		int32 NextLane = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
		bool isPowerup = false;

	UFUNCTION(BlueprintImplementableEvent)
		void GameOver();

	UFUNCTION(BlueprintImplementableEvent, Category = "Lane")
		void ChangeLane();

	UFUNCTION(BlueprintCallable, Category = "Lane")
		void ChangeLaneUpdate(float value);

	UFUNCTION(BlueprintCallable, Category = "Lane")
		void ChangeLaneFinished();

	UFUNCTION(BlueprintCallable)
		void Death();

	UFUNCTION(BlueprintCallable)
		void setPowerup();

	UFUNCTION(BlueprintCallable)
		void resetPowerup();

	UFUNCTION(BlueprintImplementableEvent)
		void powerEffect();

	FTimerHandle TimerHandle;

	// Sets default values for this character's properties
	ARunner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void MoveRight();

	UFUNCTION()
		void MoveLeft();

	UFUNCTION()
		void MoveDown();

	UPROPERTY()
	bool bIsDead = false;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int scoreCount = 0;

	UFUNCTION()
		void AddCoin();

	UFUNCTION()
		void AddScore();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
