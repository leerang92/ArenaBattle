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

void UABGameInstance::RequestTokenComplete(const FString & Token)
{
	AB_LOG(Warning, TEXT("Token1 : %s"), *Token);
}

void UABGameInstance::RequestTokenComplete2(const FString & Token)
{
	AB_LOG(Warning, TEXT("Token2 : %s"), *Token);
}

// Init()은 Runtime에서 가장 먼저 실행되는 함수
void UABGameInstance::Init()
{
	AB_LOG_CALLONLY(Warning);
	Super::Init();

	FString PackageName = TEXT("/Temp/SavedWebConnection");
	UPackage* NewPackage = CreatePackage(nullptr, *PackageName);
	WebConnectionNew = NewObject<UWebConnect>(NewPackage);
	FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());

	WebConnectionNew->Host = TEXT("127.0.0.7");
	WebConnectionNew->URI = TEXT("/");
	if (UPackage::SavePackage(NewPackage, WebConnectionNew, RF_Standalone, *PackageFileName))
	{
		UPackage* SavedPackage = ::LoadPackage(NULL, *PackageFileName, LOAD_None);
		TArray<UObject *> ObjectsInPackage;
		GetObjectsWithOuter(SavedPackage, ObjectsInPackage, false);
		for (const auto& EachObject : ObjectsInPackage)
		{
			UWebConnect* WebConnectionFromFile = Cast<UWebConnect>(EachObject);
			if (WebConnectionFromFile)
			{
				AB_LOG(Warning, TEXT("WebConnection From File : Host %s , URI %s"), *WebConnectionFromFile->Host, *WebConnectionFromFile->URI);
			}
		}
	}

	//WebConnectionNew = NewObject<UWebConnect>(this);
	//WebConnectionNew->Host = TEXT("127.0.0.7");
	//WebConnectionNew->URI = TEXT("/");

	//FString FullPath = FString::Printf(TEXT("%s%s"), *FPaths::GameSavedDir(), TEXT("WebConnection.txt"));
	//FArchive* ArWriter = IFileManager::Get().CreateFileWriter(*FullPath);
	//if (ArWriter)
	//{
	//	/**ArWriter << WebConnectionNew->Host;
	//	*ArWriter << WebConnectionNew->URI;*/
	//	*ArWriter << *WebConnectionNew;
	//	ArWriter->Close();
	//	delete ArWriter;
	//	ArWriter = NULL;
	//}

	//TSharedPtr<FArchive> FileReader = MakeShareable(IFileManager::Get().CreateFileReader(*FullPath));
	//if (FileReader.IsValid())
	//{
	//	//FString Host;
	//	//FString URI;
	//	//*FileReader.Get() << Host;
	//	//*FileReader.Get() << URI;
	//	UWebConnect* WebConnectionFromFile = NewObject<UWebConnect>(this);
	//	*FileReader.Get() << *WebConnectionFromFile;
	//	FileReader->Close();
	//	AB_LOG(Warning, TEXT("WebConnection From File : Host %s , URI %s"), *WebConnectionFromFile->Host, *WebConnectionFromFile->URI);
	//	//AB_LOG(Warning, TEXT("WebConnection : Host %s , URI %s"), *Host, *URI);
	//}

	//FHouse* HouseNew = new FHouse();
	//WebConnect->TokenCompleteDelegate.AddDynamic(this, &UABGameInstance::RequestTokenComplete);
	//WebConnect->TokenCompleteDelegate.AddDynamic(this, &UABGameInstance::RequestTokenComplete2);
	//WebConnect->TokenCompleteDelegate.AddRaw(HouseNew, &FHouse::RequestTokenComplete);
	//WebConnect->RequestToken(TEXT("destiny"));

	///* 
	//* NewObject는 CreateDefaultSubobject와 달리 CDO를 생성하지 않음.
	//* WebConnect의 CDO를 복제하여 사용하는 것.
	//* 인자에 this로 들어간 것은 자식 관계로 생성한다는 것. 
	//*/
	//WebConnect2 = NewObject<UWebConnect>(this);

	//UClass* ClassInfo1 = WebConnect->GetClass();
	//UClass* Classinfo2 = UWebConnect::StaticClass();

	//TArray<UObject*> DefaultSubobjects;
	//GetDefaultSubobjects(DefaultSubobjects);
	//for (const auto& Entry : DefaultSubobjects) {
	//	AB_LOG(Warning, TEXT("DefaultSubobject : %s"), *Entry->GetClass()->GetName());
	//	/* GetOuter()를 통해 부모를 알아낼 수 있다. */
	//	AB_LOG(Warning, TEXT("Outer of DefaultSubobject : %s"), *Entry->GetOuter()->GetClass()->GetFullName());
	//}

	//if (ClassInfo1 == Classinfo2)
	//{
	//	AB_LOG(Warning, TEXT("ClassInfo1 is same with ClassInfo2"));
	//}

	//for (TFieldIterator<UProperty> It(ClassInfo1); It; ++It)
	//{
	//	AB_LOG(Warning, TEXT("Field : %s, Type : %s"), *It->GetName(), *It->GetClass()->GetName());
	//	//UStrProperty* StrProp = FindField<UStrProperty>(ClassInfo1, *It->GetName());
	//	//if (StrProp)
	//	//{
	//	//	AB_LOG(Warning, TEXT("Value = %s"), *StrProp->GetPropertyValue_InContainer(WebConnect));
	//	//}

	//	UFunction* Func1 = ClassInfo1->FindFunctionByName(TEXT("RequestToken"));
	//	if (Func1->ParmsSize == 0)
	//	{
	//		WebConnect->ProcessEvent(Func1, NULL);
	//	}
	//}

	///* 월드에 있는 액터와 액터의 컴포넌트들을 출력 */
	//UWorld* CurrentWorld = GetWorld();
	//for (const auto& Entry : FActorRange(CurrentWorld))
	//{
	//	AB_LOG(Warning, TEXT("Actor : %s"), *Entry->GetName());

	//	TArray<UObject*> Components;
	//	Entry->GetDefaultSubobjects(Components);
	//	for (const auto& CEntry : Components) 
	//	{
	//		AB_LOG(Warning, TEXT("--Component : %s"), *CEntry->GetName());
	//	}
	//}

	///* 
	//* 월드에서 특정 타입의 액터만 찾아서 출력 
	//* TActorIterator : Actor 검색 시
	//* TObjectIterator : Object 검색 시 
	//*/
	//for (TActorIterator<AActor> It(CurrentWorld); It; ++It) 
	//{
	//	AB_LOG(Warning, TEXT("StaticeMesh Actor : %s"), *It->GetName());
	//}

	///* 기본 포인터 */
	//AB_LOG(Warning, TEXT("****** 1단계 ******"));
	//FHouse* NewHouseAddress = new FHouse();
	//AB_LOG(Warning, TEXT("집을 새로 지었습니다. 내집크기 : %d"), NewHouseAddress->Size);
	//if (NewHouseAddress)
	//{
	//	delete NewHouseAddress;
	//	AB_LOG(Warning, TEXT("내가 직접 집을 철거했습니다. 집크기 : %d"), NewHouseAddress->Size);
	//	NewHouseAddress = nullptr;
	//}

	///** 유니크 포인터
	//* 단독 소유만 가능
	//*/
	//AB_LOG(Warning, TEXT("****** 2단계 ******"));
	//NewHouseAddress = new FHouse();
	//NewHouseAddress->Size = 100;
	//AB_LOG(Warning, TEXT("집을 다시 지었습니다. 집크기 : %d"), NewHouseAddress->Size);
	//{
	//	// 유니크 포인터 선언
	//	TUniquePtr<FHouse> MyHouseDeed = TUniquePtr<FHouse>(NewHouseAddress);
	//	if (MyHouseDeed.IsValid())
	//	{
	//		AB_LOG(Warning, TEXT("이 집은 제 단독소유 주택입니다. 내집크기 : %d"), MyHouseDeed->Size);
	//	}

	//	/** MoveTemp()를 사용하여 소유권을 이전
	//	* 기존에 MyHouseDeed은 소유권을 잃음 (더 이상 유효하지 않음).
	//	*/
	//	//TUniquePtr<FHouse> FriendsHouseDeed = MyHouseDeed;  // 컴파일 에러! 단독 소유만 가능
	//	TUniquePtr<FHouse> FriendsHouseDeed = MoveTemp(MyHouseDeed); // 집은 그대로 두고 집주인만 변경
	//	if (!MyHouseDeed.IsValid())
	//	{
	//		AB_LOG(Warning, TEXT("친구에게 집을 팔았습니다. 친구집크기 : %d"), FriendsHouseDeed->Size);
	//	}
	//}
	////NewHouseAddress는 자동으로 메모리 해제
	//AB_LOG(Warning, TEXT("집문서가 사라져서 집은 자동으로 철거되었습니다. 집크기 : %d"), NewHouseAddress->Size);

	///** 공유 포인터 
	//* 공동 소유가 가능
	//*/
	//AB_LOG(Warning, TEXT("****** 3단계 ******"));
	//NewHouseAddress = new FHouse();
	//NewHouseAddress->Size = 150.0f;
	//AB_LOG(Warning, TEXT("집을 또 다시 지었습니다. 집크기 : %d"), NewHouseAddress->Size);
	//{
	//	TSharedPtr<FHouse> MyHouseDeed = MakeShareable(NewHouseAddress); // 만들어진 집을 차후에 등록
	//	if (MyHouseDeed.IsValid())
	//	{
	//		AB_LOG(Warning, TEXT("공동 소유 가능한 집이 되었습니다. 내집크기 : %d"), MyHouseDeed->Size);
	//		if (MyHouseDeed.IsUnique())
	//		{
	//			AB_LOG(Warning, TEXT("현재는 혼자 소유하고 있습니다. 내집크기 : %d"), MyHouseDeed->Size);
	//		}
	//	}

	//	TSharedPtr<FHouse> FriendsHouseDeed = MyHouseDeed;
	//	if (!FriendsHouseDeed.IsUnique())
	//	{
	//		AB_LOG(Warning, TEXT("친구와 집을 나눠가지게 되었습니다. 친구집크기 : %d"), FriendsHouseDeed->Size);
	//	}

	//	MyHouseDeed.Reset(); // 내가 집 소유권을 포기함
	//	if (FriendsHouseDeed.IsUnique())
	//	{
	//		AB_LOG(Warning, TEXT("이제 친구만 집을 소유하고 있습니다. 친구집크기 : %d"), FriendsHouseDeed->Size);
	//	}

	//	AB_LOG(Warning, TEXT("집은 아직 그대로 있습니다. 집크기 : %d"), NewHouseAddress->Size);
	//}

	//AB_LOG(Warning, TEXT("집은 자동 철거되었습니다. 집크기 : %d"), NewHouseAddress->Size);

	///* 순환 참조 문제 
	//* 두 개의 포인터를 서로 공유 했을 시, 자동으로 메모리 해제가 안될 수 있다.
	//*/
	//AB_LOG(Warning, TEXT("****** 4단계 ******"));
	//NewHouseAddress = new FHouse();
	//NewHouseAddress->Size = 200.0f;
	//AB_LOG(Warning, TEXT("집을 한번 더 다시 지었습니다. 첫번째집크기 : %d"), NewHouseAddress->Size);

	//FHouse* NewHouseAddress2 = new FHouse();
	//NewHouseAddress2->Size = 250.0f;
	//AB_LOG(Warning, TEXT("친구도 집을 직접 지었습니다. 두번째집크기 : %d"), NewHouseAddress2->Size);

	//{
	//	// 공유 포인터 생성
	//	TSharedPtr<FHouse> MyHouseDeed = MakeShareable(NewHouseAddress);
	//	AB_LOG(Warning, TEXT("내 집은 내가 소유합니다. 내집크기 : %d"), MyHouseDeed->Size);
	//	TSharedPtr<FHouse> FriendsHouseDeed = MakeShareable(NewHouseAddress2);
	//	AB_LOG(Warning, TEXT("친구 집은 친구가 소유합니다. 친구집크기 : %d"), FriendsHouseDeed->Size);

	//	// 두 개의 포인터가 서로의 포인터를 정의함.
	//	MyHouseDeed->OthersDeed = FriendsHouseDeed;
	//	AB_LOG(Warning, TEXT("친구 집을 공동 소유하고 문서를 내 집에 보관합니다. 친구집크기 : %d"), MyHouseDeed->OthersDeed->Size);
	//	FriendsHouseDeed->OthersDeed = MyHouseDeed;
	//	AB_LOG(Warning, TEXT("친구도 내 집을 공동 소유하고 문서를 자기 집에 보관합니다. 내집크기 : %d"), FriendsHouseDeed->OthersDeed->Size);
	//}
	//// 자동으로 메모리 해제가 안됨
	//AB_LOG(Warning, TEXT("집문서가 사라져도 내가 지은 집이 자동 철거되지 않습니다. 첫번째집크기 : %d"), NewHouseAddress->Size);
	//AB_LOG(Warning, TEXT("친구가 지은 집도 자동 철거되지 않습니다. 두번째집크기 : %d"), NewHouseAddress2->Size);

	//// 강제로 메모리 해제 후, 나머지 포인터가 자동으로 메모리 해제가 이루어짐.
	//NewHouseAddress->OthersDeed.Reset();
	//AB_LOG(Warning, TEXT("친구가 지은 집을 수동으로 철거했습니다. 집주소가 남아있어서 다행입니다. 두번째집크기 : %d"), NewHouseAddress2->Size);
	//AB_LOG(Warning, TEXT("이제서야 내가 지은 집도 자동 철거됩니다. 첫번째집크기 : %d"), NewHouseAddress->Size);

	///** 약 포인터
	//* 실제로 포인터를 가지고 있지 않지만 접근은 가능함.
	//* 레퍼런스 카운터가 증가하지 X
	//*/
	//AB_LOG(Warning, TEXT("****** 5단계 ******"));
	//NewHouseAddress = new FHouse();
	//NewHouseAddress->Size = 300.0f;
	//AB_LOG(Warning, TEXT("이제 마지막으로 집을 짓습니다. 첫번째집크기 : %d"), NewHouseAddress->Size);

	//NewHouseAddress2 = new FHouse();
	//NewHouseAddress2->Size = 350.0f;
	//AB_LOG(Warning, TEXT("친구도 집을 다시 지었습니다. 두번째집크기 : %d"), NewHouseAddress2->Size);

	//{
	//	TSharedPtr<FHouse> MyHouseDeed = MakeShareable(NewHouseAddress);
	//	AB_LOG(Warning, TEXT("내 집은 내가 소유합니다. 내집크기 : %d"), MyHouseDeed->Size);
	//	TSharedPtr<FHouse> FriendsHouseDeed = MakeShareable(NewHouseAddress2);
	//	AB_LOG(Warning, TEXT("친구 집은 친구가 소유합니다. 친구집크기 : %d"), FriendsHouseDeed->Size);

	//	// 공유 포인터에 정의
	//	MyHouseDeed->OthersDeed = FriendsHouseDeed;
	//	AB_LOG(Warning, TEXT("친구 집을 공동 소유하고 문서를 내 집에 보관합니다. 친구집크기 : %d"), MyHouseDeed->OthersDeed->Size);
	//	// 약 포인터에 정의
	//	FriendsHouseDeed->AccessHouse = MyHouseDeed;
	//	AB_LOG(Warning, TEXT("친구가 내 집 정보를 열람합니다. 내집크기 : %d"), FriendsHouseDeed->AccessHouse.Pin()->Size);
	//}

	//AB_LOG(Warning, TEXT("내가 지은 집은 자동 철거됩니다. 첫번째집크기 : %d"), NewHouseAddress->Size);
	//AB_LOG(Warning, TEXT("친구가 지은 집도 자동 철거됩니다. 두번째집크기 : %d"), NewHouseAddress2->Size);

	//// 6단계
	///* 언리얼 가비지 컬렉션을 통해 메모리 해제 */
	//AB_LOG(Warning, TEXT("****** 6단계 ******"));
	//WebConnect2 = NewObject<UWebConnect>();
	//WebConnect2->Host = TEXT("127.0.0.1");
	////WebConnectionNew->AddToRoot();
	//WebConnect2->ConditionalBeginDestroy();
	////GetWorld()->ForceGarbageCollection(true);
	//GetWorld()->GetTimerManager().SetTimer(ObjectCheckTimer, this, &UABGameInstance::CheckUObjectAlive, 1.0f, true);

}

void UABGameInstance::CheckUObjectAlive()
{
	if (!WebConnect2)
	{
		AB_LOG(Warning, TEXT("언리얼오브젝트가 널입니다."));
		return;
	}

	if (!WebConnect2->IsValidLowLevel())
	{
		AB_LOG(Warning, TEXT("언리얼오브젝트가 유효하지 않습니다."));
		return;
	}

	AB_LOG(Warning, TEXT("언리얼오브젝트가 아직 살아있습니다. : %s"), *WebConnect2->Host);
}


