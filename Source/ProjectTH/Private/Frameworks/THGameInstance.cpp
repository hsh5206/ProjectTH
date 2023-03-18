// Fill out your copyright notice in the Description page of Project Settings.


#include "Frameworks/THGameInstance.h"
#include "AbilitySystemGlobals.h"
#include "Blueprint/UserWidget.h"

#include "OnlineSubsystem.h"

UTHGameInstance::UTHGameInstance()
{
	
}

void UTHGameInstance::Init()
{
	Super::Init();

	// 글로벌 데이터 테이블 및 태그를 로드하려면 프로젝트 설정의 일부로 한 번 호출
	UAbilitySystemGlobals::Get().InitGlobalData();


	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface)
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &ThisClass::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &ThisClass::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &ThisClass::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &ThisClass::OnJoinSessionComplete);

			SessionSearch = MakeShareable(new FOnlineSessionSearch());
			if (SessionSearch.IsValid())
			{
				SessionSearch->bIsLanQuery = true;
			}
		}
	}

}

void UTHGameInstance::LoadMenu()
{
	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget(this, MainMenuWidgetClass);
		MainMenuWidget->AddToViewport();

		if (APlayerController* PC = GetFirstLocalPlayerController())
		{
			FInputModeUIOnly InputMode;
			PC->SetInputMode(InputMode);

			PC->SetShowMouseCursor(true);
		}
	}
}

void UTHGameInstance::CreateSession(int32 PlayerNum, FString Title, FString Map, FString GameMode)
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;
		SessionSettings.bIsLANMatch = true;
		SessionSettings.NumPublicConnections = PlayerNum;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.Set(SETTING_SESSION_TEMPLATE_NAME, Title, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		SessionSettings.Set(SETTING_GAMEMODE, GameMode, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		SessionSettings.Set(SETTING_MAPNAME, Map, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
		SessionInterface->CreateSession(0, FName("THGame"), SessionSettings);
	}
}

void UTHGameInstance::FindSessions()
{
	if (SessionInterface.IsValid())
	{
		FindSessionsCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegate);
		UE_LOG(LogTemp, Error, TEXT("SessionSearching..."));

		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UTHGameInstance::JoinToSession(const FOnlineSessionSearchResult& SessionResults)
{
	if (SessionInterface.IsValid())
	{
		SessionInterface->JoinSession(0, FName("THGame"), SessionResults);
	}
}

void UTHGameInstance::OnCreateSessionComplete(FName SessionName, bool bSuccess)
{
	if (bSuccess)
	{
		UE_LOG(LogTemp, Error, TEXT("CreateSession Complete."));

		GetWorld()->ServerTravel("/Game/Maps/TestMap?listen");
	}
}


void UTHGameInstance::OnFindSessionsComplete(bool bSuccesful)
{
	if (bSuccesful && SessionSearch.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("SessionSearch Complete"));
		SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(FindSessionsCompleteDelegateHandle);

		if (SessionSearch->SearchResults.Num() <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("0 Sessions"));
			MultiplayerOnFindSessionsComplete.Broadcast(TArray<FOnlineSessionSearchResult>(), false);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Find Sessions"));
			MultiplayerOnFindSessionsComplete.Broadcast(SessionSearch->SearchResults, true);
		}
	}
}

void UTHGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (SessionSearch.IsValid())
	{
		FString Address;
		if (SessionInterface->GetResolvedConnectString(SessionName, Address))
		{
			APlayerController* PlayerController = GetFirstLocalPlayerController();
			if (PlayerController)
			{
				PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
			}
		}
		
	}
}

void UTHGameInstance::OnDestroySessionComplete(FName SessionName, bool bSuccess)
{

}