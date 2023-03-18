// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Rooms.generated.h"

UCLASS()
class PROJECTTH_API UWidget_Rooms : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> ServerInfoClass;
	UPROPERTY(VisibleAnywhere, Category = "Widget")
	class UWidget_SessionInfo* ServerInfo;

	UFUNCTION(BlueprintCallable)
	void SelectIndex(int32 index);
	UPROPERTY(BlueprintReadOnly)
	int32 SelectedIndex = -1;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UScrollBox* SessionScroll;

protected:
	virtual bool Initialize() override;

private:
	class UTHGameInstance* GameInstance;

	/** Callbacks custom delegate from GameInstance_SessionComplete */
	void AfterFindSession(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bWasSuccessful);

};
