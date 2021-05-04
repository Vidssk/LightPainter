// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/StereoLayerFunctionLibrary.h"
#include "Saving/PainterSaveGame.h"

void APaintingGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	SlotName = UGameplayStatics::ParseOption(Options, "SlotName");
	UE_LOG(LogTemp, Warning, TEXT("SlotName: %s"), *SlotName);
}

void APaintingGameMode::BeginPlay()
{
	Super::BeginPlay();
	Load();
	UStereoLayerFunctionLibrary::HideSplashScreen();
}

void APaintingGameMode::Save()
{
	UPainterSaveGame* Painting = UPainterSaveGame::Load(SlotName);
	if (!Painting) return;
	Painting->SerializeFromWorld(GetWorld());
	Painting->Save();

}

void APaintingGameMode::Load()
{
	UPainterSaveGame* Painting = UPainterSaveGame::Load(SlotName);
	if (Painting)
	{
		Painting->DeserializeToWorld(GetWorld());
		//UE_LOG(LogTemp, Warning, TEXT("Painting State %s"), *Painting->GetState());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Slot Not Found,: %s"), *SlotName);
	}
}

void APaintingGameMode::SaveAndQuit()
{
	Save();

	UStereoLayerFunctionLibrary::ShowSplashScreen();
	//TODO: Refactor out magic string.
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Menu"));
}