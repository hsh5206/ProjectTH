// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"

#include "THGameInstance.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FMultiplayerOnFindSessionsComplete, const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);

UCLASS()
class PROJECTTH_API UTHGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	FMultiplayerOnFindSessionsComplete MultiplayerOnFindSessionsComplete;

public:
	UTHGameInstance();
	virtual void Init() override;

	/** Menu */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> MainMenuWidgetClass;
	UUserWidget* MainMenuWidget;
	UFUNCTION(BlueprintCallable)
	void LoadMenu();

public:
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

	// Menu Handle
	UFUNCTION(BlueprintCallable)
	void CreateSession(int32 PlayerNum, FString Title, FString Map, FString GameMode);
	UFUNCTION(BlueprintCallable)
	void FindSessions();
	void JoinToSession(const FOnlineSessionSearchResult& SessionResults);
	void DestroySession();

	void OnCreateSessionComplete(FName SessionName, bool bSuccess);
	void OnDestroySessionComplete(FName SessionName, bool bSuccess);
	void OnFindSessionsComplete(bool bSuccesful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

private:
	// 세션 찾기 델리게이트
	FOnFindSessionsCompleteDelegate FindSessionsCompleteDelegate;
	FDelegateHandle FindSessionsCompleteDelegateHandle;
};