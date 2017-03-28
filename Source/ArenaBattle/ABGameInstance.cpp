// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABGameInstance.h"

UABGameInstance::UABGameInstance()
{
	AB_LOG(Warning, TEXT("ABGameInstance Constructor"));

	/* 
	* CreateDefaultSubobject : 생성자에서만 사용 
	* CDO가 하나 더 만들어진다.
	*/
	WebConnect = CreateDefaultSubobject<UWebConnect>(TEXT("WebConnect"));
}

// Init()은 Runtime에서 가장 먼저 실행되는 함수
void UABGameInstance::Init()
{
	AB_LOG_CALLONLY(Warning);
	Super::Init();

	/* 
	* NewObject는 CreateDefaultSubobject와 달리 CDO를 생성하지 않음.
	* WebConnect의 CDO를 복제하여 사용하는 것.
	* 인자에 this로 들어간 것은 자식 관계로 생성한다는 것. 
	*/
	WebConnect2 = NewObject<UWebConnect>(this);

	UClass* ClassInfo1 = WebConnect->GetClass();
	UClass* Classinfo2 = UWebConnect::StaticClass();

	TArray<UObject*> DefaultSubobjects;
	GetDefaultSubobjects(DefaultSubobjects);
	for (const auto& Entry : DefaultSubobjects) {
		AB_LOG(Warning, TEXT("DefaultSubobject : %s"), *Entry->GetClass()->GetName());
		/* GetOuter()를 통해 부모를 알아낼 수 있다. */
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

	/* 월드에 있는 액터와 액터의 컴포넌트들을 출력 */
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
	* 월드에서 특정 타입의 액터만 찾아서 출력 
	* TActorIterator : Actor 검색 시
	* TObjectIterator : Object 검색 시 
	*/
	for (TActorIterator<AActor> It(CurrentWorld); It; ++It) 
	{
		AB_LOG(Warning, TEXT("StaticeMesh Actor : %s"), *It->GetName());
	}
}


