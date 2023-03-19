// Copyright Epic Games, Inc. All Rights Reserved.


#include "EndlessRunnerGameModeBase.h"
#include "Floor.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Coin.h"
#include "CoinHUD.h"

void AEndlessRunnerGameModeBase::BeginPlay()
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;

	GameHud = Cast<UCoinHUD>(CreateWidget(GetWorld(), GameHUDClass));

	check(GameHud);

	GameHud->InitializeHUD(this);
	GameHud->AddToViewport();
	
	CreateInitialFloorTiles();
}

void AEndlessRunnerGameModeBase::CreateInitialFloorTiles()
{
	AFloor* Tile = AddFloorTile(false);

	if (Tile) {

		LaneSwitchValues.Add(Tile->LeftLane->GetComponentLocation().Y);
		LaneSwitchValues.Add(Tile->CenterLane->GetComponentLocation().Y);
		LaneSwitchValues.Add(Tile->RightLane->GetComponentLocation().Y);
		
	}

	for (float Val : LaneSwitchValues)
	{
		UE_LOG(LogTemp, Warning, TEXT("LANE VALUE: %f"), Val);
	}

	AddFloorTile(false);
	AddFloorTile(false);

	for (int i = 0; i < NumInitialFloor; i++) {

		AddFloorTile(true);
	}
}

AFloor* AEndlessRunnerGameModeBase::AddFloorTile(bool bSpawnItems)
{
	UWorld* World = GetWorld();

	if (World) {

		AFloor* Tile = World->SpawnActor<AFloor>(FloorClass, NextSpawnPoint);

		if (Tile) {

			if (bSpawnItems) {

				Tile->SpawnItems();
			}

			NextSpawnPoint = Tile->GetAttachTranform();
		}

		return Tile;
	}
	
	return nullptr;
}


void AEndlessRunnerGameModeBase::AddCoin()
{
	CoinCount += 1;

	UE_LOG(LogTemp, Warning, TEXT("Coins: %d"), CoinCount);

	OnCoinsCountChanged.Broadcast(CoinCount);
}