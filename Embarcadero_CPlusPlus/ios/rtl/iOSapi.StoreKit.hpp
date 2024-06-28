// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.StoreKit.pas' rev: 34.00 (iOS)

#ifndef Iosapi_StorekitHPP
#define Iosapi_StorekitHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.UIKit.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Storekit
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE SKPaymentTransactionObserver;
typedef System::DelphiInterface<SKPaymentTransactionObserver> _di_SKPaymentTransactionObserver;
__interface DELPHIINTERFACE SKRequestDelegate;
typedef System::DelphiInterface<SKRequestDelegate> _di_SKRequestDelegate;
__interface DELPHIINTERFACE SKProductsRequestDelegate;
typedef System::DelphiInterface<SKProductsRequestDelegate> _di_SKProductsRequestDelegate;
__interface DELPHIINTERFACE SKStoreProductViewControllerDelegate;
typedef System::DelphiInterface<SKStoreProductViewControllerDelegate> _di_SKStoreProductViewControllerDelegate;
__interface DELPHIINTERFACE SKProductClass;
typedef System::DelphiInterface<SKProductClass> _di_SKProductClass;
__interface DELPHIINTERFACE SKProduct;
typedef System::DelphiInterface<SKProduct> _di_SKProduct;
class DELPHICLASS TSKProduct;
__interface DELPHIINTERFACE SKPaymentTransactionClass;
typedef System::DelphiInterface<SKPaymentTransactionClass> _di_SKPaymentTransactionClass;
__interface DELPHIINTERFACE SKPaymentTransaction;
typedef System::DelphiInterface<SKPaymentTransaction> _di_SKPaymentTransaction;
class DELPHICLASS TSKPaymentTransaction;
__interface DELPHIINTERFACE SKProductsResponseClass;
typedef System::DelphiInterface<SKProductsResponseClass> _di_SKProductsResponseClass;
__interface DELPHIINTERFACE SKProductsResponse;
typedef System::DelphiInterface<SKProductsResponse> _di_SKProductsResponse;
class DELPHICLASS TSKProductsResponse;
__interface DELPHIINTERFACE SKStoreProductViewControllerClass;
typedef System::DelphiInterface<SKStoreProductViewControllerClass> _di_SKStoreProductViewControllerClass;
__interface DELPHIINTERFACE SKStoreProductViewController;
typedef System::DelphiInterface<SKStoreProductViewController> _di_SKStoreProductViewController;
class DELPHICLASS TSKStoreProductViewController;
__interface DELPHIINTERFACE SKRequestClass;
typedef System::DelphiInterface<SKRequestClass> _di_SKRequestClass;
__interface DELPHIINTERFACE SKRequest;
typedef System::DelphiInterface<SKRequest> _di_SKRequest;
class DELPHICLASS TSKRequest;
__interface DELPHIINTERFACE SKDownloadClass;
typedef System::DelphiInterface<SKDownloadClass> _di_SKDownloadClass;
__interface DELPHIINTERFACE SKDownload;
typedef System::DelphiInterface<SKDownload> _di_SKDownload;
class DELPHICLASS TSKDownload;
__interface DELPHIINTERFACE SKPaymentQueueClass;
typedef System::DelphiInterface<SKPaymentQueueClass> _di_SKPaymentQueueClass;
__interface DELPHIINTERFACE SKPaymentQueue;
typedef System::DelphiInterface<SKPaymentQueue> _di_SKPaymentQueue;
class DELPHICLASS TSKPaymentQueue;
__interface DELPHIINTERFACE SKPaymentClass;
typedef System::DelphiInterface<SKPaymentClass> _di_SKPaymentClass;
__interface DELPHIINTERFACE SKPayment;
typedef System::DelphiInterface<SKPayment> _di_SKPayment;
class DELPHICLASS TSKPayment;
__interface DELPHIINTERFACE SKProductsRequestClass;
typedef System::DelphiInterface<SKProductsRequestClass> _di_SKProductsRequestClass;
__interface DELPHIINTERFACE SKProductsRequest;
typedef System::DelphiInterface<SKProductsRequest> _di_SKProductsRequest;
class DELPHICLASS TSKProductsRequest;
__interface DELPHIINTERFACE SKMutablePaymentClass;
typedef System::DelphiInterface<SKMutablePaymentClass> _di_SKMutablePaymentClass;
__interface DELPHIINTERFACE SKMutablePayment;
typedef System::DelphiInterface<SKMutablePayment> _di_SKMutablePayment;
class DELPHICLASS TSKMutablePayment;
//-- type declarations -------------------------------------------------------
typedef long SKDownloadState;

typedef long SKPaymentTransactionState;

__interface  INTERFACE_UUID("{88D273EF-BD1E-4BE8-9F69-21C5A7B89953}") SKPaymentTransactionObserver  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl paymentQueue(_di_SKPaymentQueue queue, Iosapi::Foundation::_di_NSArray removedTransactions) = 0 /* overload */;
	virtual void __cdecl paymentQueue(_di_SKPaymentQueue queue, Iosapi::Foundation::_di_NSError restoreCompletedTransactionsFailedWithError) = 0 /* overload */;
	virtual void __cdecl paymentQueueUpdatedDownloads(_di_SKPaymentQueue queue, Iosapi::Foundation::_di_NSArray updatedDownloads) = 0 ;
	virtual void __cdecl paymentQueueUpdatedTransactions(_di_SKPaymentQueue queue, Iosapi::Foundation::_di_NSArray updatedTransactions) = 0 ;
	virtual void __cdecl paymentQueueRestoreCompletedTransactionsFinished(_di_SKPaymentQueue queue) = 0 ;
};

__interface  INTERFACE_UUID("{75551E3D-FE0A-439C-A2AE-44E6AFDBE137}") SKRequestDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl request(_di_SKRequest request, Iosapi::Foundation::_di_NSError didFailWithError) = 0 ;
	virtual void __cdecl requestDidFinish(_di_SKRequest request) = 0 ;
};

__interface  INTERFACE_UUID("{78F9F6B7-5F27-4FC8-A11D-4E5B546FF0A3}") SKProductsRequestDelegate  : public SKRequestDelegate 
{
	virtual void __cdecl productsRequest(_di_SKProductsRequest request, _di_SKProductsResponse didReceiveResponse) = 0 ;
};

__interface  INTERFACE_UUID("{8EA90AB3-A629-4E8E-B8DD-752B0EF06624}") SKStoreProductViewControllerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl productViewControllerDidFinish(_di_SKStoreProductViewController viewController) = 0 ;
};

__interface  INTERFACE_UUID("{428A4142-EB45-4B2A-BAF1-7CAB8194E510}") SKProductClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{CB3FB7DE-2C6D-460F-ABC8-42A9E0DD27FA}") SKProduct  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl downloadContentLengths() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl downloadContentVersion() = 0 ;
	virtual bool __cdecl isDownloadable() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl localizedDescription() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl localizedTitle() = 0 ;
	virtual Iosapi::Foundation::_di_NSDecimalNumber __cdecl price() = 0 ;
	virtual Iosapi::Foundation::_di_NSLocale __cdecl priceLocale() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl productIdentifier() = 0 ;
};

class PASCALIMPLEMENTATION TSKProduct : public Macapi::Objectivec::TOCGenericImport__2<_di_SKProductClass,_di_SKProduct>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_SKProductClass,_di_SKProduct> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TSKProduct(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_SKProductClass,_di_SKProduct>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TSKProduct() { }
	
};


__interface  INTERFACE_UUID("{63D69BB2-4E72-44CE-88D4-8CF9398DEE83}") SKPaymentTransactionClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{C10BC112-D047-4710-8384-B731322AD5D9}") SKPaymentTransaction  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl downloads() = 0 ;
	virtual Iosapi::Foundation::_di_NSError __cdecl error() = 0 ;
	virtual _di_SKPaymentTransaction __cdecl originalTransaction() = 0 ;
	virtual _di_SKPayment __cdecl payment() = 0 ;
	virtual Iosapi::Foundation::_di_NSDate __cdecl transactionDate() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl transactionIdentifier() = 0 ;
	virtual Iosapi::Foundation::_di_NSData __cdecl transactionReceipt() = 0 ;
	virtual long __cdecl transactionState() = 0 ;
};

class PASCALIMPLEMENTATION TSKPaymentTransaction : public Macapi::Objectivec::TOCGenericImport__2<_di_SKPaymentTransactionClass,_di_SKPaymentTransaction>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_SKPaymentTransactionClass,_di_SKPaymentTransaction> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TSKPaymentTransaction(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_SKPaymentTransactionClass,_di_SKPaymentTransaction>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TSKPaymentTransaction() { }
	
};


__interface  INTERFACE_UUID("{1518D722-C0B3-4DDB-9D9A-BF082598437D}") SKProductsResponseClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{BCD7691E-2AEB-4530-AAD5-8C4288573788}") SKProductsResponse  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl invalidProductIdentifiers() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl products() = 0 ;
};

class PASCALIMPLEMENTATION TSKProductsResponse : public Macapi::Objectivec::TOCGenericImport__2<_di_SKProductsResponseClass,_di_SKProductsResponse>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_SKProductsResponseClass,_di_SKProductsResponse> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TSKProductsResponse(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_SKProductsResponseClass,_di_SKProductsResponse>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TSKProductsResponse() { }
	
};


__interface  INTERFACE_UUID("{0D751D11-5154-4CCF-B91D-FC1B8CBFC752}") SKStoreProductViewControllerClass  : public Iosapi::Uikit::UIViewControllerClass 
{
	
};

__interface  INTERFACE_UUID("{AA05EA7E-AFAE-48DA-9AC7-7CD34B4EE0A7}") SKStoreProductViewController  : public Iosapi::Uikit::UIViewController 
{
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
};

class PASCALIMPLEMENTATION TSKStoreProductViewController : public Macapi::Objectivec::TOCGenericImport__2<_di_SKStoreProductViewControllerClass,_di_SKStoreProductViewController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_SKStoreProductViewControllerClass,_di_SKStoreProductViewController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TSKStoreProductViewController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_SKStoreProductViewControllerClass,_di_SKStoreProductViewController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TSKStoreProductViewController() { }
	
};


__interface  INTERFACE_UUID("{57A7603D-5A6F-4BA4-AE2D-5591CEC2DE66}") SKRequestClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{38CA6F9F-8509-43A8-8E70-A5B17B2FF95C}") SKRequest  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl cancel() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl start() = 0 ;
};

class PASCALIMPLEMENTATION TSKRequest : public Macapi::Objectivec::TOCGenericImport__2<_di_SKRequestClass,_di_SKRequest>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_SKRequestClass,_di_SKRequest> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TSKRequest(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_SKRequestClass,_di_SKRequest>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TSKRequest() { }
	
};


__interface  INTERFACE_UUID("{FCB2BA81-B727-4EE6-9B7B-BF45CDF215E5}") SKDownloadClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{77A31CCE-8CA1-445F-82CD-4A2DD494C0F4}") SKDownload  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl contentIdentifier() = 0 ;
	virtual __int64 __cdecl contentLength() = 0 ;
	virtual Iosapi::Foundation::_di_NSURL __cdecl contentURL() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl contentVersion() = 0 ;
	virtual long __cdecl downloadState() = 0 ;
	virtual Iosapi::Foundation::_di_NSError __cdecl error() = 0 ;
	virtual float __cdecl progress() = 0 ;
	virtual double __cdecl timeRemaining() = 0 ;
	virtual _di_SKPaymentTransaction __cdecl transaction() = 0 ;
};

class PASCALIMPLEMENTATION TSKDownload : public Macapi::Objectivec::TOCGenericImport__2<_di_SKDownloadClass,_di_SKDownload>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_SKDownloadClass,_di_SKDownload> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TSKDownload(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_SKDownloadClass,_di_SKDownload>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TSKDownload() { }
	
};


__interface  INTERFACE_UUID("{F44FA678-A77E-4B32-B2FE-0AB2498E64F3}") SKPaymentQueueClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual bool __cdecl canMakePayments() = 0 ;
	virtual void * __cdecl defaultQueue() = 0 ;
};

__interface  INTERFACE_UUID("{4AD59191-395F-4F52-9C1D-05E011E0AB8B}") SKPaymentQueue  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl addPayment(_di_SKPayment payment) = 0 ;
	virtual void __cdecl addTransactionObserver(void * observer) = 0 ;
	virtual void __cdecl cancelDownloads(Iosapi::Foundation::_di_NSArray downloads) = 0 ;
	virtual void __cdecl finishTransaction(_di_SKPaymentTransaction transaction) = 0 ;
	virtual void __cdecl pauseDownloads(Iosapi::Foundation::_di_NSArray downloads) = 0 ;
	virtual void __cdecl removeTransactionObserver(void * observer) = 0 ;
	virtual void __cdecl restoreCompletedTransactions() = 0 ;
	virtual void __cdecl resumeDownloads(Iosapi::Foundation::_di_NSArray downloads) = 0 ;
	virtual void __cdecl startDownloads(Iosapi::Foundation::_di_NSArray downloads) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl transactions() = 0 ;
};

class PASCALIMPLEMENTATION TSKPaymentQueue : public Macapi::Objectivec::TOCGenericImport__2<_di_SKPaymentQueueClass,_di_SKPaymentQueue>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_SKPaymentQueueClass,_di_SKPaymentQueue> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TSKPaymentQueue(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_SKPaymentQueueClass,_di_SKPaymentQueue>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TSKPaymentQueue() { }
	
};


__interface  INTERFACE_UUID("{80EE0EA9-756C-4A86-86F3-490D8E76538F}") SKPaymentClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void * __cdecl paymentWithProduct(_di_SKProduct product) = 0 ;
	virtual void * __cdecl paymentWithProductIdentifier(Iosapi::Foundation::_di_NSString identifier) = 0 ;
};

__interface  INTERFACE_UUID("{67C12FA6-A97A-4484-AF97-34DCC66F858C}") SKPayment  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl productIdentifier() = 0 ;
	virtual long __cdecl quantity() = 0 ;
	virtual Iosapi::Foundation::_di_NSData __cdecl requestData() = 0 ;
};

class PASCALIMPLEMENTATION TSKPayment : public Macapi::Objectivec::TOCGenericImport__2<_di_SKPaymentClass,_di_SKPayment>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_SKPaymentClass,_di_SKPayment> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TSKPayment(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_SKPaymentClass,_di_SKPayment>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TSKPayment() { }
	
};


__interface  INTERFACE_UUID("{91F51A78-6385-4D57-8BCD-F055F7553FBB}") SKProductsRequestClass  : public SKRequestClass 
{
	
};

__interface  INTERFACE_UUID("{083E9FED-BE5E-45C4-9975-24654345875F}") SKProductsRequest  : public SKRequest 
{
	HIDESBASE virtual void * __cdecl delegate() = 0 ;
	virtual void * __cdecl initWithProductIdentifiers(Iosapi::Foundation::_di_NSSet productIdentifiers) = 0 ;
	HIDESBASE virtual void __cdecl setDelegate(void * delegate) = 0 ;
};

class PASCALIMPLEMENTATION TSKProductsRequest : public Macapi::Objectivec::TOCGenericImport__2<_di_SKProductsRequestClass,_di_SKProductsRequest>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_SKProductsRequestClass,_di_SKProductsRequest> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TSKProductsRequest(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_SKProductsRequestClass,_di_SKProductsRequest>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TSKProductsRequest() { }
	
};


__interface  INTERFACE_UUID("{D69C31D1-4A7A-46D9-A6B8-6061A6BFACB4}") SKMutablePaymentClass  : public SKPaymentClass 
{
	
};

__interface  INTERFACE_UUID("{7387B4F4-4EF8-4D8B-BAE7-DDA8A56AAA15}") SKMutablePayment  : public SKPayment 
{
	HIDESBASE virtual Iosapi::Foundation::_di_NSString __cdecl productIdentifier() = 0 ;
	HIDESBASE virtual long __cdecl quantity() = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSData __cdecl requestData() = 0 ;
	virtual void __cdecl setProductIdentifier(Iosapi::Foundation::_di_NSString productIdentifier) = 0 ;
	virtual void __cdecl setQuantity(long quantity) = 0 ;
	virtual void __cdecl setRequestData(Iosapi::Foundation::_di_NSData requestData) = 0 ;
};

class PASCALIMPLEMENTATION TSKMutablePayment : public Macapi::Objectivec::TOCGenericImport__2<_di_SKMutablePaymentClass,_di_SKMutablePayment>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_SKMutablePaymentClass,_di_SKMutablePayment> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TSKMutablePayment(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_SKMutablePaymentClass,_di_SKMutablePayment>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TSKMutablePayment() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 SKDownloadStateActive = System::Int8(0x1);
static constexpr System::Int8 SKDownloadStateCancelled = System::Int8(0x5);
static constexpr System::Int8 SKDownloadStateFailed = System::Int8(0x4);
static constexpr System::Int8 SKDownloadStateFinished = System::Int8(0x3);
static constexpr System::Int8 SKDownloadStatePaused = System::Int8(0x2);
static constexpr System::Int8 SKDownloadStateWaiting = System::Int8(0x0);
static constexpr System::Int8 SKErrorClientInvalid = System::Int8(0x1);
static constexpr System::Int8 SKErrorPaymentCancelled = System::Int8(0x2);
static constexpr System::Int8 SKErrorPaymentInvalid = System::Int8(0x3);
static constexpr System::Int8 SKErrorPaymentNotAllowed = System::Int8(0x4);
static constexpr System::Int8 SKErrorStoreProductNotAvailable = System::Int8(0x5);
static constexpr System::Int8 SKErrorUnknown = System::Int8(0x0);
static constexpr System::Int8 SKPaymentTransactionStateFailed = System::Int8(0x2);
static constexpr System::Int8 SKPaymentTransactionStatePurchased = System::Int8(0x1);
static constexpr System::Int8 SKPaymentTransactionStatePurchasing = System::Int8(0x0);
static constexpr System::Int8 SKPaymentTransactionStateRestored = System::Int8(0x3);
#define libStoreKit u"/System/Library/Frameworks/StoreKit.framework/StoreKit"
}	/* namespace Storekit */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_STOREKIT)
using namespace Iosapi::Storekit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_StorekitHPP
