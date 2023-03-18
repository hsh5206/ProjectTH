// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Widget_Rooms.h"
#include "Components/Button.h"

#include "OnlineSessionSettings.h"
#include "Components/ScrollBox.h"
#include "OnlineSubsystem.h"

#include "Widgets/Widget_SessionInfo.h"
#include "Frameworks/THGameInstance.h"

bool UWidget_Rooms::Initialize()
{
	if (!Super::Initialize()) return false;

	GameInstance = Cast<UTHGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->MultiplayerOnFindSessionsComplete.AddUObject(this, &ThisClass::AfterFindSession);
	}

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController && ServerInfoClass)
	{
		ServerInfo = CreateWidget<UWidget_SessionInfo>(GetWorld(), ServerInfoClass);
	}

	return true;
}

void UWidget_Rooms::AfterFindSession(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful)
{
	SessionScroll->ClearChildren();

	int32 index = 0;
	for (const FOnlineSessionSearchResult& SessionResult : SessionResults)
	{
		FString Title;
		SessionResult.Session.SessionSettings.Get(SETTING_SESSION_TEMPLATE_NAME, Title);
		FString MapName;
		SessionResult.Session.SessionSettings.Get(SETTING_MAPNAME, MapName);
		FString GameMode;
		SessionResult.Session.SessionSettings.Get(SETTING_GAMEMODE, GameMode);
		int32 MaxPlayerNum = SessionResult.Session.SessionSettings.NumPublicConnections;
		int32 Ping = SessionResult.PingInMs;

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				15.f,
				FColor::Green,
				FString::Printf(TEXT("%s,%s,%s %d, %d"), *Title, *MapName, *GameMode, MaxPlayerNum, Ping)
			);
		}

		UWidget_SessionInfo* Info = CreateWidget<UWidget_SessionInfo>(GetWorld(), ServerInfoClass);
		Info->SetText(Title, MapName, GameMode, MaxPlayerNum, Ping);
		Info->SearchResult = SessionResult;
		Info->SetParentAndIndex(this, index);
		SessionScroll->AddChild(Info);
		index++;
	}
}

void UWidget_Rooms::SelectIndex(int32 index)
{
	SelectedIndex = index;
}
