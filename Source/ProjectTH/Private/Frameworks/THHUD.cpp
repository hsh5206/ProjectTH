// Fill out your copyright notice in the Description page of Project Settings.


#include "Frameworks/THHUD.h"

#include "Widgets/Widget_BaseUI.h"
#include "Characters/BaseHero.h"
#include "DataAssets/HeroData.h"

void ATHHUD::BeginPlay()
{
	Super::BeginPlay();

	if (BaseUIClass)
	{
		BaseUI = CreateWidget<UWidget_BaseUI>(GetOwningPlayerController(), BaseUIClass);
		BaseUI->AddToViewport();
	}

	if (ABaseHero* Hero = Cast<ABaseHero>(GetOwningPawn()))
	{
		if (Hero->HeroData && Hero->HeroData->CrossHairClass)
		{
			CrossHair = CreateWidget(GetOwningPlayerController(), Hero->HeroData->CrossHairClass);
			CrossHair->AddToViewport();
		}
	}
}