// Fill out your copyright notice in the Description page of Project Settings.


#include "Frameworks/THGameInstance.h"

#include "AbilitySystemGlobals.h"

void UTHGameInstance::Init()
{
	Super::Init();

	// �۷ι� ������ ���̺� �� �±׸� �ε��Ϸ��� ������Ʈ ������ �Ϻη� �� �� ȣ���ؾ� ��
	UAbilitySystemGlobals::Get().InitGlobalData();
}