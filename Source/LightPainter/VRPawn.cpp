// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "PaintingGameMode.h"
#include "Kismet/StereoLayerFunctionLibrary.h"
#include "HandControllerBase.h"
#include "Saving/PainterSaveGame.h"
// Sets default values
AVRPawn::AVRPawn()
{
	PrimaryActorTick.bCanEverTick = false;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	SetRootComponent(VRRoot);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRRoot);

}

void AVRPawn::BeginPlay()
{
	Super::BeginPlay();
	if (RightHandControllerClass)
	{
		RightHandController = GetWorld()->SpawnActor<AHandControllerBase>(RightHandControllerClass);
		RightHandController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		RightHandController->SetOwner(this);
		RightHandController->SetHand(EControllerHand::Right);
	}

	if (LeftHandControllerClass)
	{
		LeftHandController = GetWorld()->SpawnActor<AHandControllerBase>(LeftHandControllerClass);
		LeftHandController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		LeftHandController->SetOwner(this);
		LeftHandController->SetHand(EControllerHand::Left);
	}
}

void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("RightTrigger"), EInputEvent::IE_Pressed, this, &AVRPawn::RightTriggerPressed);
	PlayerInputComponent->BindAction(TEXT("RightTrigger"), EInputEvent::IE_Released, this, &AVRPawn::RightTriggerReleased);

	//PlayerInputComponent->BindAction(TEXT("Save"), EInputEvent::IE_Released, this, &AVRPawn::Save);
	//PlayerInputComponent->BindAction(TEXT("Load"), EInputEvent::IE_Released, this, &AVRPawn::Load);
}

/*void AVRPawn::Save()
{
	APaintingGameMode* GameMode = Cast<APaintingGameMode>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;
	GameMode->Save();

	UStereoLayerFunctionLibrary::ShowSplashScreen();
	//TODO: Refactor out magic string.
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Menu"), false);
	//UStereoLayerFunctionLibrary::HideSplashScreen();
	//UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));

	//UPainterSaveGame* Painting = UPainterSaveGame::Load(CurrentSlotName);
	//if (Painting)
	//{
	//	Painting->SerializeFromWorld(GetWorld());
	//	Painting->Save();

	//}
}*/

