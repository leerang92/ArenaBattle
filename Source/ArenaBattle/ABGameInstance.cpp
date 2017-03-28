// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABGameInstance.h"

UABGameInstance::UABGameInstance()
{
	AB_LOG(Warning, TEXT("ABGameInstance Constructor"));

	/* 
	* CreateDefaultSubobject : �����ڿ����� ��� 
	* CDO�� �ϳ� �� ���������.
	*/
	WebConnect = CreateDefaultSubobject<UWebConnect>(TEXT("WebConnect"));
}

// Init()�� Runtime���� ���� ���� ����Ǵ� �Լ�
void UABGameInstance::Init()
{
	AB_LOG_CALLONLY(Warning);
	Super::Init();

	/* 
	* NewObject�� CreateDefaultSubobject�� �޸� CDO�� �������� ����.
	* WebConnect�� CDO�� �����Ͽ� ����ϴ� ��.
	* ���ڿ� this�� �� ���� �ڽ� ����� �����Ѵٴ� ��. 
	*/
	WebConnect2 = NewObject<UWebConnect>(this);

	UClass* ClassInfo1 = WebConnect->GetClass();
	UClass* Classinfo2 = UWebConnect::StaticClass();

	TArray<UObject*> DefaultSubobjects;
	GetDefaultSubobjects(DefaultSubobjects);
	for (const auto& Entry : DefaultSubobjects) {
		AB_LOG(Warning, TEXT("DefaultSubobject : %s"), *Entry->GetClass()->GetName());
		/* GetOuter()�� ���� �θ� �˾Ƴ� �� �ִ�. */
		AB_LOG(Warning, TEXT("Outer of DefaultSubobject : %s"), *Entry->GetOuter()->GetClass()->GetFullName());
	}

	if (ClassInfo1 == Classinfo2)
	{
		AB_LOG(Warning, TEXT("ClassInfo1 is same with ClassInfo2"));
	}

	for (TFieldIterator<UProperty> It(ClassInfo1); It; ++It)
	{
		AB_LOG(Warning, TEXT("Field : %s, Type : %s"), *It->GetName(), *It->GetClass()->GetName());
		//UStrProperty* StrProp = FindField<UStrProperty>(ClassInfo1, *It->GetName());
		//if (StrProp)
		//{
		//	AB_LOG(Warning, TEXT("Value = %s"), *StrProp->GetPropertyValue_InContainer(WebConnect));
		//}

		UFunction* Func1 = ClassInfo1->FindFunctionByName(TEXT("RequestToken"));
		if (Func1->ParmsSize == 0)
		{
			WebConnect->ProcessEvent(Func1, NULL);
		}
	}

	/* ���忡 �ִ� ���Ϳ� ������ ������Ʈ���� ��� */
	UWorld* CurrentWorld = GetWorld();
	for (const auto& Entry : FActorRange(CurrentWorld))
	{
		AB_LOG(Warning, TEXT("Actor : %s"), *Entry->GetName());

		TArray<UObject*> Components;
		Entry->GetDefaultSubobjects(Components);
		for (const auto& CEntry : Components) 
		{
			AB_LOG(Warning, TEXT("--Component : %s"), *CEntry->GetName());
		}
	}

	/* 
	* ���忡�� Ư�� Ÿ���� ���͸� ã�Ƽ� ��� 
	* TActorIterator : Actor �˻� ��
	* TObjectIterator : Object �˻� �� 
	*/
	for (TActorIterator<AActor> It(CurrentWorld); It; ++It) 
	{
		AB_LOG(Warning, TEXT("StaticeMesh Actor : %s"), *It->GetName());
	}
}


