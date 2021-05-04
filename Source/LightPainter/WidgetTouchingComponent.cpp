// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetTouchingComponent.h"

void UWidgetTouchingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsOverInteractableWidget() && !bIsClicked)
	{
		PressPointerKey(EKeys::LeftMouseButton);
		bIsClicked = true;
		UE_LOG(LogTemp, Warning, TEXT("Pressed."))
	}
	if(!IsOverInteractableWidget() && bIsClicked)
	{
		ReleasePointerKey(EKeys::LeftMouseButton);
		bIsClicked = false;
		UE_LOG(LogTemp, Warning, TEXT("Released"));

	}
}