// Fill out your copyright notice in the Description page of Project Settings.


#include "Frameworks/THGameInstance.h"
#include "AbilitySystemGlobals.h"
#include "OnlineSessionSettings.h"
#include "Interfaces/OnlineSessionInterface.h"

void UTHGameInstance::Init()
{
	Super::Init();

	// �۷ι� ������ ���̺� �� �±׸� �ε��Ϸ��� ������Ʈ ������ �Ϻη� �� �� ȣ��
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
