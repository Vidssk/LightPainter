// Fill out your copyright notice in the Description page of Project Settings.


#include "PaintingGrid.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/SizeBox.h"

void UPaintingGrid::AddPainting(int32 PaintingIndex,FString PaintingName)
{
	if (!PaintingGrid) return;
	//UE_LOG(LogTemp, Warning, TEXT("Grid Name: %s"), *PaintingGrid->GetName());
	UPaintingGridCard* NewWidget = CreateWidget<UPaintingGridCard>(GetWorld(), GridCardClass);
	if (!NewWidget) return;
	NewWidget->SetPaintingName(PaintingName);
	USizeBox* CardContainer = Cast<USizeBox>(PaintingGrid->GetChildAt(PaintingIndex));
	if (!CardContainer) return;
	CardContainer->AddChild(NewWidget);
}


void UPaintingGrid::ClearPaintings()
{
	for (int32 i = 0; i < PaintingGrid->GetChildrenCount(); ++i)
	{
		USizeBox* CardContainer = Cast<USizeBox>(PaintingGrid->GetChildAt(i));
		if (!CardContainer) return;
		CardContainer->ClearChildren();
	}
}
void UPaintingGrid::AddPaginationDot(bool Active)
{
	if (!PaginationDots) return;
	auto Dot = CreateWidget<UPaginationDot>(GetWorld(), PaginationDotClass);
	if (!Dot) return;
	Dot->SetActive(Active);
//	PaginationDots->AddChild(Dot);
	UHorizontalBoxSlot* BoxSlot = PaginationDots->AddChildToHorizontalBox(Dot);
	BoxSlot->SetPadding(FMargin(PaginationDotPadding, 0));

}

int32 UPaintingGrid::GetNumberOfSlots() const
{
	return PaintingGrid->GetChildrenCount();
}

void UPaintingGrid::ClearPaginationDots()
{
	if (!PaginationDots) return;
	PaginationDots->ClearChildren();
}