// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinHUD.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/TextBlock.h"


void UCoinHUD::InitializeHUD(AEndlessRunnerGameModeBase* RunGameMode)
{
	if(RunGameMode)
	{
		CoinsCount->SetText(FText::AsNumber(0));


		RunGameMode->OnCoinsCountChanged.AddDynamic(this, &UCoinHUD::SetCoinsCount);
	}	
}

void UCoinHUD::SetCoinsCount(const int32 Count)
{
	CoinsCount->SetText(FText::AsNumber(Count));
}
