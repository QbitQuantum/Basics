// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Win.ShareContract.pas' rev: 34.00 (Windows)

#ifndef System_Win_SharecontractHPP
#define System_Win_SharecontractHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Win.WinRT.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.WinRT.hpp>
#include <Winapi.Foundation.Types.hpp>
#include <Winapi.ApplicationModel.DataTransfer.hpp>
#include <Winapi.Storage.hpp>
#include <Winapi.Storage.Streams.hpp>
#include <Winapi.CommonTypes.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------
using namespace Winapi::Applicationmodel::Datatransfer;

namespace System
{
namespace Win
{
namespace Sharecontract
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EShareContractException;
class DELPHICLASS TShareContract;
class DELPHICLASS TIterableStorageItems;
class DELPHICLASS TIteratorStorageItems;
class DELPHICLASS TOperationCompleted;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EShareContractException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EShareContractException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EShareContractException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EShareContractException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EShareContractException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EShareContractException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EShareContractException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EShareContractException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EShareContractException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EShareContractException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EShareContractException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EShareContractException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EShareContractException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EShareContractException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef void __fastcall (__closure *TApplicationChosenEvent)(System::TObject* const Sender, const Winapi::Applicationmodel::Datatransfer::_di_IDataTransferManager AManager, const Winapi::Applicationmodel::Datatransfer::_di_ITargetApplicationChosenEventArgs Args);

typedef void __fastcall (__closure *TTransferDataEvent)(System::TObject* const Sender, const Winapi::Commontypes::_di_IDataProviderRequest ARequest);

typedef void __fastcall (__closure *TProcessMessagesProc)(void);

class PASCALIMPLEMENTATION TShareContract : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	class DELPHICLASS TDataTransferEventHandler;
#ifndef _WIN64
	#pragma pack(push,4)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TDataTransferEventHandler : public System::Win::Winrt::TInspectableObject
	{
		typedef System::Win::Winrt::TInspectableObject inherited;
		
	private:
		TShareContract* FOwner;
		HRESULT __safecall Invoke(Winapi::Applicationmodel::Datatransfer::_di_IDataTransferManager sender, Winapi::Applicationmodel::Datatransfer::_di_IDataRequestedEventArgs args);
		
	public:
		__fastcall TDataTransferEventHandler(TShareContract* const AOwner);
		__fastcall virtual ~TDataTransferEventHandler();
private:
		void *__TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs;	// Winapi::Applicationmodel::Datatransfer::TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs 
		
public:
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {041062FC-4655-55C7-A13F-1153F9CA6E51}
		operator Winapi::Applicationmodel::Datatransfer::_di_TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs()
		{
			Winapi::Applicationmodel::Datatransfer::_di_TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator Winapi::Applicationmodel::Datatransfer::TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs*(void) { return (Winapi::Applicationmodel::Datatransfer::TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs*)&__TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs; }
		#endif
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {EC6F9CC8-46D0-5E0E-B4D2-7D7773AE37A0}
		operator Winapi::Applicationmodel::Datatransfer::_di_TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs_Delegate_Base()
		{
			Winapi::Applicationmodel::Datatransfer::_di_TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs_Delegate_Base intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator Winapi::Applicationmodel::Datatransfer::TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs_Delegate_Base*(void) { return (Winapi::Applicationmodel::Datatransfer::TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs_Delegate_Base*)&__TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs; }
		#endif
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	class DELPHICLASS TAppChosenEventHandler;
#ifndef _WIN64
	#pragma pack(push,4)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TAppChosenEventHandler : public System::Win::Winrt::TInspectableObject
	{
		typedef System::Win::Winrt::TInspectableObject inherited;
		
	private:
		TShareContract* FOwner;
		HRESULT __safecall Invoke(Winapi::Applicationmodel::Datatransfer::_di_IDataTransferManager sender, Winapi::Applicationmodel::Datatransfer::_di_ITargetApplicationChosenEventArgs args);
		
	public:
		__fastcall TAppChosenEventHandler(TShareContract* const AOwner);
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TAppChosenEventHandler() { }
		
private:
		void *__TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs;	// Winapi::Applicationmodel::Datatransfer::TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs 
		
public:
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {A3639038-7CA2-5BF9-9657-DDBB0B7C6142}
		operator Winapi::Applicationmodel::Datatransfer::_di_TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs()
		{
			Winapi::Applicationmodel::Datatransfer::_di_TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator Winapi::Applicationmodel::Datatransfer::TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs*(void) { return (Winapi::Applicationmodel::Datatransfer::TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs*)&__TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs; }
		#endif
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {C4AC1BA2-7851-5A44-BC8D-3D7C713F1F41}
		operator Winapi::Applicationmodel::Datatransfer::_di_TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs_Delegate_Base()
		{
			Winapi::Applicationmodel::Datatransfer::_di_TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs_Delegate_Base intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator Winapi::Applicationmodel::Datatransfer::TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs_Delegate_Base*(void) { return (Winapi::Applicationmodel::Datatransfer::TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs_Delegate_Base*)&__TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs; }
		#endif
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	class DELPHICLASS TDataProviderHandler;
#ifndef _WIN64
	#pragma pack(push,4)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TDataProviderHandler : public System::Win::Winrt::TInspectableObject
	{
		typedef System::Win::Winrt::TInspectableObject inherited;
		
	private:
		TShareContract* FOwner;
		HRESULT __safecall Invoke(Winapi::Commontypes::_di_IDataProviderRequest request);
		
	public:
		__fastcall TDataProviderHandler(TShareContract* const AOwner);
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TDataProviderHandler() { }
		
private:
		void *__DataProviderHandler;	// Winapi::Commontypes::DataProviderHandler 
		
public:
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {E7ECD720-F2F4-4A2D-920E-170A2F482A27}
		operator Winapi::Commontypes::_di_DataProviderHandler()
		{
			Winapi::Commontypes::_di_DataProviderHandler intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator Winapi::Commontypes::DataProviderHandler*(void) { return (Winapi::Commontypes::DataProviderHandler*)&__DataProviderHandler; }
		#endif
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	class DELPHICLASS TCompletedHandler;
#ifndef _WIN64
	#pragma pack(push,4)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TCompletedHandler : public System::Win::Winrt::TInspectableObject
	{
		typedef System::Win::Winrt::TInspectableObject inherited;
		
	private:
		Winapi::Commontypes::AsyncStatus FStatus;
		Winapi::Commontypes::AsyncStatus __fastcall GetAsyncStatus();
		
	public:
		HRESULT __safecall Invoke(Winapi::Commontypes::_di_IAsyncOperation_1__IStorageFile asyncInfo, Winapi::Commontypes::AsyncStatus aasyncStatus);
		__property Winapi::Commontypes::AsyncStatus Status = {read=GetAsyncStatus, nodefault};
	public:
		/* TObject.Create */ inline __fastcall TCompletedHandler() : System::Win::Winrt::TInspectableObject() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TCompletedHandler() { }
		
private:
		void *__AsyncOperationCompletedHandler_1__IStorageFile;	// Winapi::Commontypes::AsyncOperationCompletedHandler_1__IStorageFile 
		
public:
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {1247300D-7973-53D5-889F-5279D9322114}
		operator Winapi::Commontypes::_di_AsyncOperationCompletedHandler_1__IStorageFile()
		{
			Winapi::Commontypes::_di_AsyncOperationCompletedHandler_1__IStorageFile intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator Winapi::Commontypes::AsyncOperationCompletedHandler_1__IStorageFile*(void) { return (Winapi::Commontypes::AsyncOperationCompletedHandler_1__IStorageFile*)&__AsyncOperationCompletedHandler_1__IStorageFile; }
		#endif
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {E521C894-2C26-5946-9E61-2B5E188D01ED}
		operator Winapi::Commontypes::_di_AsyncOperationCompletedHandler_1__IStorageFile_Delegate_Base()
		{
			Winapi::Commontypes::_di_AsyncOperationCompletedHandler_1__IStorageFile_Delegate_Base intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator Winapi::Commontypes::AsyncOperationCompletedHandler_1__IStorageFile_Delegate_Base*(void) { return (Winapi::Commontypes::AsyncOperationCompletedHandler_1__IStorageFile_Delegate_Base*)&__AsyncOperationCompletedHandler_1__IStorageFile; }
		#endif
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
private:
	static TProcessMessagesProc FProcessMessages;
	static System::UnicodeString FBasePath;
	TTransferDataEvent FOnTransferImage;
	TApplicationChosenEvent FOnAppChosen;
	System::UnicodeString FPackageName;
	System::UnicodeString FContentSourceWebLink;
	System::UnicodeString FContentSourceApplicationLink;
	System::UnicodeString FImageFile;
	System::UnicodeString FIconFile;
	System::UnicodeString FWebAddress;
	System::UnicodeString FApplicationName;
	System::UnicodeString FDescription;
	System::UnicodeString FDataTitle;
	System::UnicodeString FDataText;
	System::UnicodeString FLogoFile;
	System::UnicodeString FRtfText;
	System::UnicodeString FHTML;
	System::Classes::TStrings* FFileList;
	void __fastcall DoTransferImage(const Winapi::Commontypes::_di_IDataProviderRequest ARequest);
	void __fastcall DoAppChosen(Winapi::Applicationmodel::Datatransfer::_di_IDataTransferManager sender, Winapi::Applicationmodel::Datatransfer::_di_ITargetApplicationChosenEventArgs args);
	static void __fastcall SetProcessMessages(const TProcessMessagesProc Value);
	
protected:
	NativeUInt FWindowHandle;
	Winapi::Applicationmodel::Datatransfer::_di_IDataTransferManager FTransferManager;
	Winapi::Commontypes::EventRegistrationToken FSharingRequested;
	Winapi::Commontypes::EventRegistrationToken FTargetAppRequested;
	Winapi::Applicationmodel::Datatransfer::_di_TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs FDataRequestedHandlerIntf;
	Winapi::Applicationmodel::Datatransfer::_di_TypedEventHandler_2__IDataTransferManager__ITargetApplicationChosenEventArgs FAppChosenHandlerIntf;
	Winapi::Commontypes::_di_DataProviderHandler FImageDataProvider;
	
private:
	__classmethod void __fastcall ProcessMessages();
	
public:
	__fastcall TShareContract(HWND AWinHandle);
	__fastcall virtual ~TShareContract();
	void __fastcall InitSharing();
	/* static */ __property TProcessMessagesProc OnProcessMessages = {read=FProcessMessages, write=SetProcessMessages};
	/* static */ __property System::UnicodeString BasePath = {read=FBasePath, write=FBasePath};
	static Winapi::Commontypes::_di_IRandomAccessStreamReference __fastcall FileNameToStream(const System::UnicodeString AFileName);
	__property System::UnicodeString ApplicationName = {read=FApplicationName, write=FApplicationName};
	__property System::UnicodeString ContentSourceWebLink = {read=FContentSourceWebLink, write=FContentSourceWebLink};
	__property System::UnicodeString ContentSourceApplicationLink = {read=FContentSourceApplicationLink, write=FContentSourceApplicationLink};
	__property System::UnicodeString DataText = {read=FDataText, write=FDataText};
	__property System::UnicodeString DataTitle = {read=FDataTitle, write=FDataTitle};
	__property System::UnicodeString Description = {read=FDescription, write=FDescription};
	__property System::UnicodeString IconFile = {read=FIconFile, write=FIconFile};
	__property System::UnicodeString ImageFile = {read=FImageFile, write=FImageFile};
	__property System::UnicodeString LogoFile = {read=FLogoFile, write=FLogoFile};
	__property System::UnicodeString PackageName = {read=FPackageName, write=FPackageName};
	__property System::UnicodeString WebAddress = {read=FWebAddress, write=FWebAddress};
	__property System::UnicodeString RtfText = {read=FRtfText, write=FRtfText};
	__property System::UnicodeString HTML = {read=FHTML, write=FHTML};
	__property System::Classes::TStrings* FileList = {read=FFileList, write=FFileList};
	__property TTransferDataEvent OnTransferImage = {read=FOnTransferImage, write=FOnTransferImage};
	__property TApplicationChosenEvent OnAppChosen = {read=FOnAppChosen, write=FOnAppChosen};
	__property Winapi::Applicationmodel::Datatransfer::_di_TypedEventHandler_2__IDataTransferManager__IDataRequestedEventArgs OnDataRequest = {read=FDataRequestedHandlerIntf, write=FDataRequestedHandlerIntf};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIterableStorageItems : public System::Win::Winrt::TInspectableObject
{
	typedef System::Win::Winrt::TInspectableObject inherited;
	
private:
	System::Generics::Collections::TList__1<Winapi::Commontypes::_di_IStorageItem>* FItems;
	
public:
	__fastcall TIterableStorageItems();
	HRESULT __safecall First(Winapi::Commontypes::_di_IIterator_1__IStorageItem &__First_result);
	void __fastcall Add(Winapi::Commontypes::_di_IStorageItem AItem);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIterableStorageItems() { }
	
private:
	void *__IIterable_1__IStorageItem;	// Winapi::Commontypes::IIterable_1__IStorageItem 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {BB8B8418-65D1-544B-B083-6D172F568C73}
	operator Winapi::Commontypes::_di_IIterable_1__IStorageItem()
	{
		Winapi::Commontypes::_di_IIterable_1__IStorageItem intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Winapi::Commontypes::IIterable_1__IStorageItem*(void) { return (Winapi::Commontypes::IIterable_1__IStorageItem*)&__IIterable_1__IStorageItem; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIteratorStorageItems : public System::Win::Winrt::TInspectableObject
{
	typedef System::Win::Winrt::TInspectableObject inherited;
	
private:
	System::Generics::Collections::TList__1<Winapi::Commontypes::_di_IStorageItem>* FList;
	int FIndex;
	
public:
	__fastcall TIteratorStorageItems(System::Generics::Collections::TList__1<Winapi::Commontypes::_di_IStorageItem>* AItems);
	HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PIStorageItem items, unsigned &__GetMany_result);
	HRESULT __safecall MoveNext(bool &__MoveNext_result);
	HRESULT __safecall get_Current(Winapi::Commontypes::_di_IStorageItem &__get_Current_result);
	HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TIteratorStorageItems() { }
	
private:
	void *__IIterator_1__IStorageItem;	// Winapi::Commontypes::IIterator_1__IStorageItem 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {05B487C2-3830-5D3C-98DA-25FA11542DBD}
	operator Winapi::Commontypes::_di_IIterator_1__IStorageItem()
	{
		Winapi::Commontypes::_di_IIterator_1__IStorageItem intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Winapi::Commontypes::IIterator_1__IStorageItem*(void) { return (Winapi::Commontypes::IIterator_1__IStorageItem*)&__IIterator_1__IStorageItem; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOperationCompleted : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Winapi::Commontypes::_di_IStorageFile FResult;
	void __fastcall SetResult(const Winapi::Commontypes::_di_IStorageFile Value);
	
public:
	__fastcall TOperationCompleted();
	HRESULT __safecall Invoke(Winapi::Commontypes::_di_IAsyncOperation_1__IStorageFile AAsyncInfo, Winapi::Commontypes::AsyncStatus aasyncStatus);
	__property Winapi::Commontypes::_di_IStorageFile Result = {read=FResult, write=SetResult};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TOperationCompleted() { }
	
private:
	void *__AsyncOperationCompletedHandler_1__IStorageFile;	// Winapi::Commontypes::AsyncOperationCompletedHandler_1__IStorageFile 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E521C894-2C26-5946-9E61-2B5E188D01ED}
	operator Winapi::Commontypes::_di_AsyncOperationCompletedHandler_1__IStorageFile_Delegate_Base()
	{
		Winapi::Commontypes::_di_AsyncOperationCompletedHandler_1__IStorageFile_Delegate_Base intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Winapi::Commontypes::AsyncOperationCompletedHandler_1__IStorageFile_Delegate_Base*(void) { return (Winapi::Commontypes::AsyncOperationCompletedHandler_1__IStorageFile_Delegate_Base*)&__AsyncOperationCompletedHandler_1__IStorageFile; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1247300D-7973-53D5-889F-5279D9322114}
	operator Winapi::Commontypes::_di_AsyncOperationCompletedHandler_1__IStorageFile()
	{
		Winapi::Commontypes::_di_AsyncOperationCompletedHandler_1__IStorageFile intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Winapi::Commontypes::AsyncOperationCompletedHandler_1__IStorageFile*(void) { return (Winapi::Commontypes::AsyncOperationCompletedHandler_1__IStorageFile*)&__AsyncOperationCompletedHandler_1__IStorageFile; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Sharecontract */
}	/* namespace Win */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_WIN_SHARECONTRACT)
using namespace System::Win::Sharecontract;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_WIN)
using namespace System::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Win_SharecontractHPP
