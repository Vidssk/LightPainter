// Fill out your copyright notice in the Description page of Project Settings.


#include "PainterSaveGame.h"

#include "PainterSaveGameIndex.h"
#include "Kismet/GameplayStatics.h"
#include "../Stroke.h"
#include "EngineUtils.h"
#include "Misc/Guid.h"

UPainterSaveGame* UPainterSaveGame::Create()
{
	UPainterSaveGame* NewSaveGame = Cast<UPainterSaveGame>(UGameplayStatics::CreateSaveGameObject(StaticClass()));
	if(!NewSaveGame) return nullptr;
	NewSaveGame->SlotName = FGuid::NewGuid().ToString();
	if(!NewSaveGame->Save()) return nullptr;
	
	UPainterSaveGameIndex* Index = UPainterSaveGameIndex::Load();
	Index->AddSaveGame(NewSaveGame);
	Index->Save();
	return NewSaveGame;
}

bool UPainterSaveGame::Save()
{
	//print out list
	//UE_LOG(LogTemp, Warning, TEXT("Painting Index:"))
	for (FString SlotNames : UPainterSaveGameIndex::Load()->GetSlotNames())
	{

	//UE_LOG(LogTemp, Warning, TEXT("Painting name: %s"), *SlotNames);
	}
	return UGameplayStatics::SaveGameToSlot(this, SlotName, 0);
}

UPainterSaveGame* UPainterSaveGame::Load(FString SlotName)
{
	return Cast<UPainterSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
}

void UPainterSaveGame::SerializeFromWorld(UWorld* World)
{
	//Clear Array
	//Iterate over all Strokes
	//Store class type


	Strokes.Empty();
	for (TActorIterator<AStroke> StrokeItr(World); StrokeItr; ++StrokeItr)
	{
		//Todo: Serialize
		Strokes.Add(StrokeItr->SerializeToStruct());
	}
}

void UPainterSaveGame::DeserializeToWorld(UWorld* World)
{
	//Clear World
	//for all strokes
	// spawn stroke of that type
	ClearWorld(World);
	for (FStrokeState StrokeState : Strokes)
	{
		AStroke::DeserializeFromStruct(World, StrokeState);
	}
}

void UPainterSaveGame::ClearWorld(UWorld* World)
{
	for (TActorIterator<AStroke> StrokeItr(World); StrokeItr; ++StrokeItr)
	{
		StrokeItr->Destroy();
	}
}
