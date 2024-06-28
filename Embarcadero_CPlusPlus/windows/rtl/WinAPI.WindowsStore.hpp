// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'WinAPI.WindowsStore.pas' rev: 34.00 (Windows)

#ifndef Winapi_WindowsstoreHPP
#define Winapi_WindowsstoreHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.TimeSpan.hpp>
#include <System.Win.WinRT.hpp>
#include <Winapi.WinRT.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.CommonTypes.hpp>
#include <WinAPI.WinRT.Utils.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Windowsstore
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAppLicense;
class DELPHICLASS TAppProducts;
class DELPHICLASS TStoreProductKindNames;
class DELPHICLASS TWindowsStoreCore;
__interface DELPHIINTERFACE IInitializeWithWindow;
typedef System::DelphiInterface<IInitializeWithWindow> _di_IInitializeWithWindow;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TAppLicense : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	bool FIsActive;
	bool FIsTrial;
	bool FIsTrialOwnedByThisUser;
	System::UnicodeString FExtendedJsonData;
	System::TDateTime FExpirationDate;
	System::UnicodeString FSkuStoreId;
	System::Timespan::TTimeSpan FTrialTimeRemaining;
	System::UnicodeString FTrialUniqueId;
	Winapi::Commontypes::_di_IStoreAppLicense FStoreLicense;
	System::Classes::TStringList* FInfo;
	
public:
	__fastcall TAppLicense(const Winapi::Commontypes::_di_IStoreAppLicense AStoreLicense);
	__fastcall virtual ~TAppLicense();
	virtual System::UnicodeString __fastcall ToString();
	System::Classes::TStringList* __fastcall GetInfo();
	__property bool IsActive = {read=FIsActive, nodefault};
	__property bool IsTrial = {read=FIsTrial, nodefault};
	__property bool IsTrialOwnedByThisUser = {read=FIsTrialOwnedByThisUser, nodefault};
	__property System::UnicodeString ExtendedJsonData = {read=FExtendedJsonData};
	__property System::TDateTime ExpirationDate = {read=FExpirationDate};
	__property System::UnicodeString SkuStoreId = {read=FSkuStoreId};
	__property System::Timespan::TTimeSpan TrialTimeRemaining = {read=FTrialTimeRemaining};
	__property System::UnicodeString TrialUniqueId = {read=FTrialUniqueId};
	__property Winapi::Commontypes::_di_IStoreAppLicense StoreLicense = {read=FStoreLicense};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAppProducts : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	Winapi::Commontypes::_di_IStoreProduct operator[](const int Index) { return this->Products[Index]; }
	
private:
	System::Generics::Collections::TList__1<Winapi::Commontypes::_di_IStoreProduct>* FProducts;
	Winapi::Commontypes::_di_IStoreProduct __fastcall GetProducts(const int Index);
	
protected:
	void __fastcall Clear();
	void __fastcall Add(Winapi::Commontypes::_di_IStoreProduct AStoreProduct);
	
public:
	__fastcall virtual TAppProducts();
	__fastcall virtual ~TAppProducts();
	int __fastcall Count();
	bool __fastcall UserHasBought(const System::UnicodeString AInAppOfferToken);
	int __fastcall IndexOf(const System::UnicodeString AInAppOfferToken)/* overload */;
	int __fastcall IndexOf(const Winapi::Commontypes::_di_IStoreProduct AStoreProduct)/* overload */;
	__property Winapi::Commontypes::_di_IStoreProduct Products[const int Index] = {read=GetProducts/*, default*/};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum class DECLSPEC_DENUM TStoreProductKind : unsigned char { Application, Game, Consumable, UnmanagedConsumable, Durable };

typedef System::Set<TStoreProductKind, _DELPHI_SET_ENUMERATOR(TStoreProductKind::Application), _DELPHI_SET_ENUMERATOR(TStoreProductKind::Durable)> TStoreProductKinds;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TStoreProductKindNames : /*[[sealed]]*/ public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TStoreProductKindNames_Application L"Application"
	
	#define TStoreProductKindNames_Game L"Game"
	
	#define TStoreProductKindNames_Consumable L"Consumable"
	
	#define TStoreProductKindNames_UnmanagedConsumable L"UnmanagedConsumable"
	
	#define TStoreProductKindNames_Durable L"Durable"
	
public:
	/* TObject.Create */ inline __fastcall TStoreProductKindNames() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TStoreProductKindNames() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TWindowsStoreCore : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Winapi::Commontypes::_di_IStoreContext FStoreContext;
	TAppLicense* FAppLicense;
	TAppProducts* FAppProducts;
	TAppProducts* FUserCollection;
	Winapi::Winrt::Utils::TApplicationProcessMessagesProc FApplicationProcessMessages;
	void __fastcall InitStoreContext();
	TAppLicense* __fastcall GetAppLicense();
	TAppProducts* __fastcall GetAppProducts();
	TAppProducts* __fastcall GetUserCollection();
	void __fastcall ResetAppProducts(TAppProducts* &AAppProducts);
	Winapi::Commontypes::_di_IIterable_1__HSTRING __fastcall GetProductsFilter(const TStoreProductKinds ProductKinds);
	Winapi::Commontypes::_di_IStoreProduct __fastcall GetStoreProductForCurrentApp();
	
public:
	__fastcall virtual TWindowsStoreCore(const Winapi::Winrt::Utils::TApplicationProcessMessagesProc AApplicationProcessMessages);
	__fastcall virtual ~TWindowsStoreCore();
	Winapi::Commontypes::StorePurchaseStatus __fastcall PurchaseProduct(Winapi::Commontypes::_di_IStoreProduct AStoreProduct);
	Winapi::Commontypes::_di_IStoreConsumableResult __fastcall ReportConsumableFulfillment(const System::UnicodeString AProductStoreId, const unsigned AQuantity, const GUID &ATrackingId);
	Winapi::Commontypes::_di_IStoreConsumableResult __fastcall ReportUnmanagedConsumableFulfillment(const System::UnicodeString AProductStoreId, const GUID &ATrackingId);
	Winapi::Commontypes::_di_IStoreConsumableResult __fastcall GetConsumableBalanceRemaining(const Winapi::Commontypes::_di_IStoreProduct AStoreProduct);
	void __fastcall RefreshInfo();
	bool __fastcall UserHasBought(const System::UnicodeString AInAppOfferToken);
	__property TAppLicense* AppLicense = {read=GetAppLicense};
	__property TAppProducts* AppProducts = {read=GetAppProducts};
	__property TAppProducts* UserCollection = {read=GetUserCollection};
	__property Winapi::Commontypes::_di_IStoreProduct StoreProductForCurrentApp = {read=GetStoreProductForCurrentApp};
};


__interface  INTERFACE_UUID("{3E68D4BD-7135-4D10-8018-9FB6D9F33FA1}") IInitializeWithWindow  : public System::IInterface 
{
	virtual void __fastcall Initialize(HANDLE_PTR hwnd) = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Windowsstore */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_WINDOWSSTORE)
using namespace Winapi::Windowsstore;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_WindowsstoreHPP
