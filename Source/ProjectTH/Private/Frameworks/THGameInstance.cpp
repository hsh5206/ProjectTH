// Fill out your copyright notice in the Description page of Project Settings.


#include "Frameworks/THGameInstance.h"
#include "AbilitySystemGlobals.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

void UTHGameInstance::Init()
{
	Super::Init();

	// 글로벌 데이터 테이블 및 태그를 로드하려면 프로젝트 설정의 일부로 한 번 호출
	UAbilitySystemGlobals::Get().InitGlobalData();

	/** Online Subsystem */
	OSS = IOnlineSubsystem::Get();
	if (OSS)
	{
		UE_LOG(LogTemp, Warning, TEXT("OSS : %s"), *OSS->GetSubsystemName().ToString());
		SessionInterface = OSS->GetSessionInterface();
		SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &ThisClass::OnCreateSessionComplete);
	}
	
}

void UTHGameInstance::Host()
{
	/** Create Session */
	if (OSS)
	{
		
		if (SessionInterface.IsValid())
		{
			FOnlineSessionSettings SessionSettings;
			SessionInterface->CreateSession(0, TEXT("Session Game"), SessionSettings);
		}
	}
}

void UTHGameInstance::OnCreateSessionComplete(FName SessionName, bool bSuccess)
{
	if (bSuccess)
	{
		/** ServerTravel */

	}
}
