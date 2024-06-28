// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.InAppPurchase.pas' rev: 34.00 (Android)

#ifndef Fmx_InapppurchaseHPP
#define Fmx_InapppurchaseHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Inapppurchase
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EIAPException;
class DELPHICLASS EIAPNotSetup;
class DELPHICLASS EIAPNoLicenseKey;
class DELPHICLASS TProduct;
class DELPHICLASS TIAPProductList;
__interface DELPHIINTERFACE IFMXInAppPurchaseService;
typedef System::DelphiInterface<IFMXInAppPurchaseService> _di_IFMXInAppPurchaseService;
__interface DELPHIINTERFACE IInAppPurchaseCallbacks;
typedef System::DelphiInterface<IInAppPurchaseCallbacks> _di_IInAppPurchaseCallbacks;
class DELPHICLASS TCustomInAppPurchase;
class DELPHICLASS TInAppPurchase;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIAPException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EIAPException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EIAPException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIAPException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIAPException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIAPException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIAPException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIAPException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIAPException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIAPException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIAPException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIAPException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIAPException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIAPException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIAPNotSetup : public EIAPException
{
	typedef EIAPException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EIAPNotSetup(const System::UnicodeString Msg) : EIAPException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EIAPNotSetup(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIAPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIAPNotSetup(NativeUInt Ident)/* overload */ : EIAPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIAPNotSetup(System::PResStringRec ResStringRec)/* overload */ : EIAPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIAPNotSetup(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIAPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIAPNotSetup(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIAPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIAPNotSetup(const System::UnicodeString Msg, int AHelpContext) : EIAPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIAPNotSetup(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIAPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIAPNotSetup(NativeUInt Ident, int AHelpContext)/* overload */ : EIAPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIAPNotSetup(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIAPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIAPNotSetup(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIAPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIAPNotSetup(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIAPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIAPNotSetup() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIAPNoLicenseKey : public EIAPException
{
	typedef EIAPException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EIAPNoLicenseKey(const System::UnicodeString Msg) : EIAPException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EIAPNoLicenseKey(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIAPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIAPNoLicenseKey(NativeUInt Ident)/* overload */ : EIAPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIAPNoLicenseKey(System::PResStringRec ResStringRec)/* overload */ : EIAPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIAPNoLicenseKey(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIAPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIAPNoLicenseKey(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIAPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIAPNoLicenseKey(const System::UnicodeString Msg, int AHelpContext) : EIAPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIAPNoLicenseKey(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIAPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIAPNoLicenseKey(NativeUInt Ident, int AHelpContext)/* overload */ : EIAPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIAPNoLicenseKey(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIAPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIAPNoLicenseKey(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIAPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIAPNoLicenseKey(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIAPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIAPNoLicenseKey() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::DynamicArray<__int64> TDownloadLengths;

class PASCALIMPLEMENTATION TProduct : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FProductID;
	double FPrice;
	System::UnicodeString FLocalizedPrice;
	System::UnicodeString FLocalizedTitle;
	System::UnicodeString FLocalizedDescription;
	bool FDownloadable;
	TDownloadLengths FDownloadContentLengths;
	System::UnicodeString FDownloadContentVersion;
	
public:
	static constexpr System::Int8 PriceNotAvailable = System::Int8(-1);
	
	__fastcall TProduct(const System::UnicodeString ProductID, double Price, const System::UnicodeString LocalizedPrice, const System::UnicodeString LocalizedTitle, const System::UnicodeString LocalizedDescription, bool Downloadable, const TDownloadLengths DownloadContentLengths, System::UnicodeString DownloadContentVersion);
	__property System::UnicodeString ProductID = {read=FProductID};
	__property double Price = {read=FPrice};
	__property System::UnicodeString LocalizedPrice = {read=FLocalizedPrice};
	__property System::UnicodeString LocalizedTitle = {read=FLocalizedTitle};
	__property System::UnicodeString LocalizedDescription = {read=FLocalizedDescription};
	__property bool Downloadable = {read=FDownloadable, nodefault};
	__property TDownloadLengths DownloadContentLengths = {read=FDownloadContentLengths};
	__property System::UnicodeString DownloadContentVersion = {read=FDownloadContentVersion};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TProduct() { }
	
};


enum class DECLSPEC_DENUM TFailureKind : unsigned char { ProductsRequest, Purchase };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIAPProductList : public System::Generics::Collections::TList__1<TProduct*>
{
	typedef System::Generics::Collections::TList__1<TProduct*> inherited;
	
public:
	/* {System_Generics_Collections}TList<FMX_InAppPurchase_TProduct>.Create */ inline __fastcall TIAPProductList()/* overload */ : System::Generics::Collections::TList__1<TProduct*>() { }
	/* {System_Generics_Collections}TList<FMX_InAppPurchase_TProduct>.Create */ inline __fastcall TIAPProductList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TProduct*> > AComparer)/* overload */ : System::Generics::Collections::TList__1<TProduct*>(AComparer) { }
	/* {System_Generics_Collections}TList<FMX_InAppPurchase_TProduct>.Create */ inline __fastcall TIAPProductList(System::Generics::Collections::TEnumerable__1<TProduct*>* const Collection)/* overload */ : System::Generics::Collections::TList__1<TProduct*>(Collection) { }
	/* {System_Generics_Collections}TList<FMX_InAppPurchase_TProduct>.Destroy */ inline __fastcall virtual ~TIAPProductList() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef void __fastcall (__closure *TIAPProductsRequestResponseEvent)(System::TObject* Sender, TIAPProductList* const Products, System::Classes::TStrings* const InvalidProductIDs);

typedef void __fastcall (__closure *TIAPVerifyPayloadEvent)(System::TObject* Sender, const System::UnicodeString Payload, bool &PayloadOk);

typedef void __fastcall (__closure *TIAPDownloadProgressEvent)(System::TObject* Sender, const System::UnicodeString ProductID, const System::UnicodeString ContentID, double TimeRemaining, float Progress);

typedef void __fastcall (__closure *TIAPDownloadCompletedEvent)(System::TObject* Sender, const System::UnicodeString ProductID, const System::UnicodeString ContentID, const System::UnicodeString FilePath);

typedef void __fastcall (__closure *TIAPPurchaseCompletedEvent)(System::TObject* Sender, const System::UnicodeString ProductID, bool NewTransaction);

typedef void __fastcall (__closure *TIAPRecordTransactionEvent)(System::TObject* Sender, const System::UnicodeString ProductID, const System::UnicodeString TransactionID, System::TDateTime TransactionDate);

typedef void __fastcall (__closure *TIAPConsumeCompletedEvent)(System::TObject* Sender, const System::UnicodeString ProductID);

typedef void __fastcall (__closure *TIAPConsumeFailedEvent)(System::TObject* Sender, const System::UnicodeString ProductID, const System::UnicodeString ErrorMessage);

typedef void __fastcall (__closure *TIAPErrorEvent)(System::TObject* Sender, TFailureKind ErrorKind, const System::UnicodeString ErrorMessage);

__interface  INTERFACE_UUID("{D49D5CE3-136A-47A7-8243-FD929AD0FF29}") IFMXInAppPurchaseService  : public System::IInterface 
{
	virtual void __fastcall AddComponent(TCustomInAppPurchase* const Component) = 0 ;
	virtual void __fastcall RemoveComponent(TCustomInAppPurchase* const Component) = 0 ;
	virtual void __fastcall SetupInAppPurchase(TCustomInAppPurchase* Component) = 0 ;
	virtual bool __fastcall CanMakeInAppPurchases() = 0 ;
	virtual void __fastcall QueryProducts(System::Classes::TStrings* const ProductIDs) = 0 ;
	virtual bool __fastcall IsProductPurchased(const System::UnicodeString ProductID) = 0 ;
	virtual void __fastcall PurchaseProduct(const System::UnicodeString ProductID) = 0 ;
	virtual void __fastcall ConsumeProduct(const System::UnicodeString ProductID) = 0 ;
	virtual void __fastcall ConsumeProducts(System::Classes::TStrings* const ProductIDs) = 0 ;
	virtual void __fastcall RestorePurchasedProducts() = 0 ;
	virtual System::UnicodeString __fastcall GetApplicationLicenseKey() = 0 ;
	virtual void __fastcall SetApplicationLicenseKey(const System::UnicodeString Value) = 0 ;
	__property System::UnicodeString ApplicationLicenseKey = {read=GetApplicationLicenseKey, write=SetApplicationLicenseKey};
	virtual System::UnicodeString __fastcall GetTransactionPayload() = 0 ;
	virtual void __fastcall SetTransactionPayload(const System::UnicodeString Value) = 0 ;
	__property System::UnicodeString TransactionPayload = {read=GetTransactionPayload, write=SetTransactionPayload};
};

__interface  INTERFACE_UUID("{855557FC-1EE0-4295-8CFD-819D4BF21808}") IInAppPurchaseCallbacks  : public System::IInterface 
{
	virtual void __fastcall DoSetupComplete() = 0 ;
	virtual void __fastcall DoProductsRequestResponse(TIAPProductList* const Products, System::Classes::TStrings* const InvalidProductIDs) = 0 ;
	virtual void __fastcall DoError(TFailureKind FailureKind, const System::UnicodeString ErrorMessage) = 0 ;
	virtual void __fastcall DoVerifyPayload(const System::UnicodeString Payload, bool &PayloadOk) = 0 ;
	virtual void __fastcall DoPurchaseCompleted(const System::UnicodeString ProductID, bool NewTransaction) = 0 ;
	virtual void __fastcall DoRecordTransaction(const System::UnicodeString ProductID, const System::UnicodeString TransactionID, System::TDateTime TransactionDate) = 0 ;
	virtual void __fastcall DoDownloadProgress(const System::UnicodeString ProductID, const System::UnicodeString ContentID, double TimeRemaining, float Progress) = 0 ;
	virtual void __fastcall DoDownloadCompleted(const System::UnicodeString ProductID, const System::UnicodeString ContentID, const System::UnicodeString FilePath) = 0 ;
	virtual void __fastcall DoConsumeCompleted(const System::UnicodeString ProductID) = 0 ;
	virtual void __fastcall DoConsumeFailed(const System::UnicodeString ProductID, const System::UnicodeString ErrorMessage) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCustomInAppPurchase : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::Classes::TStrings* FProductIDs;
	bool FIsSetupComplete;
	_di_IFMXInAppPurchaseService FInAppPurchaseService;
	System::Classes::TNotifyEvent FOnSetupComplete;
	TIAPProductsRequestResponseEvent FOnProductsRequestResponse;
	TIAPErrorEvent FOnError;
	TIAPVerifyPayloadEvent FOnVerifyPayload;
	TIAPDownloadProgressEvent FOnDownloadProgress;
	TIAPDownloadCompletedEvent FOnDownloadCompleted;
	TIAPPurchaseCompletedEvent FOnPurchaseCompleted;
	TIAPRecordTransactionEvent FOnRecordTransaction;
	TIAPConsumeCompletedEvent FOnConsumeCompleted;
	TIAPConsumeFailedEvent FOnConsumeFailed;
	void __fastcall CheckInAppPurchaseIsSetup();
	void __fastcall SetProductIDs(System::Classes::TStrings* const Value);
	System::UnicodeString __fastcall GetApplicationLicenseKey();
	void __fastcall SetApplicationLicenseKey(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetTransactionPayload();
	void __fastcall SetTransactionPayload(const System::UnicodeString Value);
	
protected:
	void __fastcall DoSetupComplete();
	void __fastcall DoProductsRequestResponse(TIAPProductList* const Products, System::Classes::TStrings* const InvalidProductIDs);
	void __fastcall DoError(TFailureKind FailureKind, const System::UnicodeString ErrorMessage);
	void __fastcall DoVerifyPayload(const System::UnicodeString Payload, bool &PayloadOk);
	void __fastcall DoPurchaseCompleted(const System::UnicodeString ProductID, bool NewTransaction);
	void __fastcall DoRecordTransaction(const System::UnicodeString ProductID, const System::UnicodeString TransactionID, System::TDateTime TransactionDate);
	void __fastcall DoDownloadProgress(const System::UnicodeString ProductID, const System::UnicodeString ContentID, double TimeRemaining, float Progress);
	void __fastcall DoDownloadCompleted(const System::UnicodeString ProductID, const System::UnicodeString ContentID, const System::UnicodeString FilePath);
	void __fastcall DoConsumeCompleted(const System::UnicodeString ProductID);
	void __fastcall DoConsumeFailed(const System::UnicodeString ProductID, const System::UnicodeString ErrorMessage);
	virtual HRESULT __stdcall QueryInterface(const GUID IID, /* out */ void *Obj);
	
public:
	__fastcall virtual TCustomInAppPurchase(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomInAppPurchase();
	void __fastcall SetupInAppPurchase();
	bool __fastcall CanMakeInAppPurchases();
	void __fastcall QueryProducts();
	bool __fastcall IsProductPurchased(const System::UnicodeString ProductID);
	void __fastcall PurchaseProduct(const System::UnicodeString ProductID);
	void __fastcall ConsumeProduct(const System::UnicodeString ProductID);
	void __fastcall ConsumeProducts(System::Classes::TStrings* const ProductIDs);
	void __fastcall RestorePurchasedProducts();
	__property System::UnicodeString ApplicationLicenseKey = {read=GetApplicationLicenseKey, write=SetApplicationLicenseKey};
	__property System::UnicodeString TransactionPayload = {read=GetTransactionPayload, write=SetTransactionPayload};
	__property System::Classes::TStrings* ProductIDs = {read=FProductIDs, write=SetProductIDs};
	__property bool IsSetupComplete = {read=FIsSetupComplete, nodefault};
	__property System::Classes::TNotifyEvent OnSetupComplete = {read=FOnSetupComplete, write=FOnSetupComplete};
	__property TIAPProductsRequestResponseEvent OnProductsRequestResponse = {read=FOnProductsRequestResponse, write=FOnProductsRequestResponse};
	__property TIAPErrorEvent OnError = {read=FOnError, write=FOnError};
	__property TIAPVerifyPayloadEvent OnVerifyPayload = {read=FOnVerifyPayload, write=FOnVerifyPayload};
	__property TIAPDownloadProgressEvent OnDownloadProgress = {read=FOnDownloadProgress, write=FOnDownloadProgress};
	__property TIAPDownloadCompletedEvent OnDownloadCompleted = {read=FOnDownloadCompleted, write=FOnDownloadCompleted};
	__property TIAPPurchaseCompletedEvent OnPurchaseCompleted = {read=FOnPurchaseCompleted, write=FOnPurchaseCompleted};
	__property TIAPRecordTransactionEvent OnRecordTransaction = {read=FOnRecordTransaction, write=FOnRecordTransaction};
	__property TIAPConsumeCompletedEvent OnConsumeCompleted = {read=FOnConsumeCompleted, write=FOnConsumeCompleted};
	__property TIAPConsumeFailedEvent OnConsumeFailed = {read=FOnConsumeFailed, write=FOnConsumeFailed};
private:
	void *__IInAppPurchaseCallbacks;	// IInAppPurchaseCallbacks 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {855557FC-1EE0-4295-8CFD-819D4BF21808}
	operator _di_IInAppPurchaseCallbacks()
	{
		_di_IInAppPurchaseCallbacks intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IInAppPurchaseCallbacks*(void) { return (IInAppPurchaseCallbacks*)&__IInAppPurchaseCallbacks; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TInAppPurchase : public TCustomInAppPurchase
{
	typedef TCustomInAppPurchase inherited;
	
__published:
	__property ApplicationLicenseKey = {default=0};
	__property ProductIDs;
	__property OnProductsRequestResponse;
	__property OnError;
	__property OnVerifyPayload;
	__property OnDownloadProgress;
	__property OnDownloadCompleted;
	__property OnPurchaseCompleted;
	__property OnRecordTransaction;
	__property OnConsumeCompleted;
	__property OnConsumeFailed;
public:
	/* TCustomInAppPurchase.Create */ inline __fastcall virtual TInAppPurchase(System::Classes::TComponent* AOwner) : TCustomInAppPurchase(AOwner) { }
	/* TCustomInAppPurchase.Destroy */ inline __fastcall virtual ~TInAppPurchase() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Inapppurchase */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_INAPPPURCHASE)
using namespace Fmx::Inapppurchase;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_InapppurchaseHPP
