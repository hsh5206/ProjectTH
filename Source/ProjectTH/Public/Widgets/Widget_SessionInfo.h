// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "Widget_SessionInfo.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTH_API UWidget_SessionInfo : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnlineSessionSearchResult SearchResult;
	UFUNCTION(BlueprintCallable)
	void JoinThisSearchResult();

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Title;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Map;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* GameMode;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerNum;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Ping;

	UPROPERTY(BlueprintReadOnly)
	class UWidget_Rooms* ParentWidget;
	UPROPERTY(BlueprintReadOnly)
	int32 Index;
	void SetParentAndIndex(UWidget_Rooms* Widget, int32 index);

	void SetText(FString& TitleName, FString& MapName, FString& GmaeMode, int32 MaxPlayerNum, int32 PingNum);
};
