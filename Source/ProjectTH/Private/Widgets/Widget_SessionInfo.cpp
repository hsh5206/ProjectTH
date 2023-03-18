// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Widget_SessionInfo.h"
#include "Components/TextBlock.h"

#include "Widgets/Widget_Rooms.h"
#include "Frameworks/THGameInstance.h"

void UWidget_SessionInfo::SetText(FString& TitleName, FString& MapName, FString& GmaeMode, int32 MaxPlayerNum, int32 PingNum)
{
	Title->SetText(FText::FromString(TitleName));
	Map->SetText(FText::FromString(MapName));
	GameMode->SetText(FText::FromString(GmaeMode));
	PlayerNum->SetText(FText::FromString(FString::Printf(TEXT("%d"), MaxPlayerNum)));
	Ping->SetText(FText::FromString(FString::Printf(TEXT("%d ms"), PingNum)));
}

void UWidget_SessionInfo::SetParentAndIndex(UWidget_Rooms* Widget, int32 index)
{
	ParentWidget = Widget;
	Index = index;
}

void  UWidget_SessionInfo::JoinThisSearchResult()
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *SearchResult.Session.GetSessionIdStr());
	Cast<UTHGameInstance>(GetGameInstance())->JoinToSession(SearchResult);
}
