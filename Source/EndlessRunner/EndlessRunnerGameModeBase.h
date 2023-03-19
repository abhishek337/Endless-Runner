// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameModeBase.generated.h"

class AFloor;
class UUserWidget;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCoinsCountChanged,int32,CoinsCount);

UCLASS()
class ENDLESSRUNNER_API AEndlessRunnerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
    
    UPROPERTY(EditAnywhere, Category = "Config")
    TSubclassOf<UUserWidget> GameHUDClass;
    
	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<AFloor> FloorClass;

	UPROPERTY(VisibleInstanceOnly, Category="Runtime")
	class UCoinHUD* GameHud;

	UPROPERTY(EditAnywhere, Category = "Config")
		int32 NumInitialFloor = 10;

	UPROPERTY(VisibleAnywhere)
		int32 CoinCount = 0;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
		FTransform NextSpawnPoint;

	UFUNCTION(BlueprintCallable)
		void CreateInitialFloorTiles();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category="Delegates")
	FOnCoinsCountChanged OnCoinsCountChanged;

	UFUNCTION(BlueprintCallable)
	AFloor* AddFloorTile(const bool bSpawnItems);

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
		TArray<float> LaneSwitchValues;

	UFUNCTION(BlueprintCallable)
		void AddCoin();



protected:

	virtual void BeginPlay() override;

};
