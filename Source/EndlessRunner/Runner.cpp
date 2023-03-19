// Fill out your copyright notice in the Description page of Project Settings.


#include "Runner.h"
#include "EndlessRunnerGameModeBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARunner::ARunner()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = 400.f;
	CameraArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	SpawnPoint->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARunner::BeginPlay()
{
	Super::BeginPlay();
	
	RunGameMode = Cast<AEndlessRunnerGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	check(RunGameMode);
}

void ARunner::AddCoin()
{
	RunGameMode->AddCoin();
}

void ARunner::AddScore()
{
	scoreCount += 1;

	UE_LOG(LogTemp, Warning, TEXT("Score : %d"), scoreCount);
}

// Called every frame
void ARunner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator ControlRot = GetControlRotation();

	ControlRot.Roll = 0.f;
	ControlRot.Pitch = 0.f;

	AddMovementInput(ControlRot.Vector());

}

// Called to bind functionality to input
void ARunner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping); 

	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ARunner::MoveRight);
	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &ARunner::MoveLeft);
	PlayerInputComponent->BindAction("MoveDown", IE_Pressed, this, &ARunner::MoveDown);

}


void ARunner::ChangeLaneUpdate(const float value)
{
	FVector Location = GetCapsuleComponent()->GetComponentLocation();
	Location.Y = FMath::Lerp(RunGameMode->LaneSwitchValues[CurrentLane], RunGameMode->LaneSwitchValues[NextLane], value);
	SetActorLocation(Location);
	
}

void ARunner::ChangeLaneFinished()
{
	CurrentLane = NextLane;
}

void ARunner::MoveRight()
{
	NextLane = FMath::Clamp(CurrentLane + 1, 0, 2);
	ChangeLane();

	//UE_LOG(LogTemp, Warning, TEXT("Move Right Pressed"));
}

void ARunner::MoveLeft()
{
	NextLane = FMath::Clamp(CurrentLane - 1, 0, 2);
	ChangeLane();

	//UE_LOG(LogTemp, Warning, TEXT("Move Left Pressed"));
}

void ARunner::MoveDown()
{
	static FVector Impulse = FVector(0, 0, MoveDownImpulse);
	GetCharacterMovement()->AddImpulse(Impulse, true);
	//UE_LOG(LogTemp, Warning, TEXT("Move Down Pressed"));
}

void ARunner::Death()
{
	if (!bIsDead) {
		UE_LOG(LogTemp, Warning, TEXT("Character Died!"));
	
		const FVector Location = GetActorLocation();

		UWorld* World = GetWorld();


		if (World)
		{
			bIsDead = true;
			DisableInput(nullptr);

			if (DeathSound)
			{
				UGameplayStatics::PlaySoundAtLocation(World, DeathSound, Location);
			}

			GetMesh()->SetVisibility(false);

			GameOver();
		}
	}
}

void ARunner::setPowerup()
{
	if (!isPowerup) {
		isPowerup = true;
		UE_LOG(LogTemp, Warning, TEXT("Power Up"));
		powerEffect();
		
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
				resetPowerup();
			}, 5, false);
	}
}

void ARunner::resetPowerup() 
{
	isPowerup = false;
	UE_LOG(LogTemp, Warning, TEXT("Reset Power Up"));
}