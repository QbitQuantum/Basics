// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.Win.SConnect.pas' rev: 34.00 (Windows)

#ifndef Datasnap_Win_SconnectHPP
#define Datasnap_Win_SconnectHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.VarUtils.hpp>
#include <System.Variants.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <Datasnap.Win.MConnect.hpp>
#include <System.Win.ScktComp.hpp>
#include <Winapi.WinSock.hpp>
#include <Winapi.WinInet.hpp>
#include <System.Win.ComObj.hpp>
#include <Datasnap.DBClient.hpp>
#include <Data.DB.hpp>

//-- user supplied -----------------------------------------------------------
#ifndef _WIN64
#pragma link "wininet.lib"
#endif /* not _WIN64 */

namespace Datasnap
{
namespace Win
{
namespace Sconnect
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IDataBlock;
typedef System::DelphiInterface<IDataBlock> _di_IDataBlock;
__interface DELPHIINTERFACE ISendDataBlock;
typedef System::DelphiInterface<ISendDataBlock> _di_ISendDataBlock;
__interface DELPHIINTERFACE ITransport;
typedef System::DelphiInterface<ITransport> _di_ITransport;
__interface DELPHIINTERFACE IDataIntercept;
typedef System::DelphiInterface<IDataIntercept> _di_IDataIntercept;
class DELPHICLASS TDataBlock;
class DELPHICLASS EInterpreterError;
class DELPHICLASS TCustomDataBlockInterpreter;
class DELPHICLASS TDataBlockInterpreter;
class DELPHICLASS TDataDispatch;
class DELPHICLASS TTransportThread;
class DELPHICLASS TStreamedConnection;
class DELPHICLASS ESocketConnectionError;
class DELPHICLASS TSocketTransport;
class DELPHICLASS TSocketConnection;
class DELPHICLASS TWebConnection;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{CA6564C2-4683-11D1-88D4-00A0248E5091}") IDataBlock  : public System::IInterface 
{
	virtual int __stdcall GetBytesReserved() = 0 ;
	virtual void * __stdcall GetMemory() = 0 ;
	virtual int __stdcall GetSize() = 0 ;
	virtual void __stdcall SetSize(int Value) = 0 ;
	virtual System::Classes::TStream* __stdcall GetStream() = 0 ;
	virtual int __stdcall GetSignature() = 0 ;
	virtual void __stdcall SetSignature(int Value) = 0 ;
	virtual void __stdcall Clear() = 0 ;
	virtual int __stdcall Write(const void *Buffer, int Count) = 0 ;
	virtual int __stdcall Read(void *Buffer, int Count) = 0 ;
	virtual void __stdcall IgnoreStream() = 0 ;
	virtual int __stdcall InitData(void * Data, int DataLen, bool CheckLen) = 0 ;
	__property int BytesReserved = {read=GetBytesReserved};
	__property void * Memory = {read=GetMemory};
	__property int Signature = {read=GetSignature, write=SetSignature};
	__property int Size = {read=GetSize, write=SetSize};
	__property System::Classes::TStream* Stream = {read=GetStream};
};

__interface  INTERFACE_UUID("{87AD1043-470E-11D1-88D5-00A0248E5091}") ISendDataBlock  : public System::IInterface 
{
	virtual _di_IDataBlock __stdcall Send(const _di_IDataBlock Data, bool WaitForResult) = 0 ;
};

__interface  INTERFACE_UUID("{CA6564C1-4683-11D1-88D4-00A0248E5091}") ITransport  : public System::IInterface 
{
	virtual NativeUInt __stdcall GetWaitEvent() = 0 ;
	virtual bool __stdcall GetConnected() = 0 ;
	virtual void __stdcall SetConnected(bool Value) = 0 ;
	virtual _di_IDataBlock __stdcall Receive(bool WaitForInput, NativeInt Context) = 0 ;
	virtual NativeInt __stdcall Send(const _di_IDataBlock Data) = 0 ;
	__property bool Connected = {read=GetConnected, write=SetConnected};
};

__interface  INTERFACE_UUID("{B249776B-E429-11D1-AAA4-00C04FA35CFA}") IDataIntercept  : public System::IInterface 
{
	virtual void __stdcall DataIn(const _di_IDataBlock Data) = 0 ;
	virtual void __stdcall DataOut(const _di_IDataBlock Data) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDataBlock : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::Classes::TMemoryStream* FStream;
	int FReadPos;
	int FWritePos;
	bool FIgnoreStream;
	
protected:
	int __stdcall GetBytesReserved();
	void * __stdcall GetMemory();
	int __stdcall GetSize();
	void __stdcall SetSize(int Value);
	System::Classes::TStream* __stdcall GetStream();
	int __stdcall GetSignature();
	void __stdcall SetSignature(int Value);
	void __stdcall Clear();
	int __stdcall Write(const void *Buffer, int Count);
	int __stdcall Read(void *Buffer, int Count);
	void __stdcall IgnoreStream();
	int __stdcall InitData(void * Data, int DataLen, bool CheckLen);
	__property int BytesReserved = {read=GetBytesReserved, nodefault};
	__property void * Memory = {read=GetMemory};
	__property int Signature = {read=GetSignature, write=SetSignature, nodefault};
	__property int Size = {read=GetSize, write=SetSize, nodefault};
	__property System::Classes::TStream* Stream = {read=GetStream};
	
public:
	__fastcall TDataBlock();
	__fastcall virtual ~TDataBlock();
private:
	void *__IDataBlock;	// IDataBlock 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CA6564C2-4683-11D1-88D4-00A0248E5091}
	operator _di_IDataBlock()
	{
		_di_IDataBlock intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDataBlock*(void) { return (IDataBlock*)&__IDataBlock; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef System::StaticArray<int, 1> TIntArray;

typedef TIntArray *PIntArray;

typedef System::StaticArray<System::OleVariant, 1> TVariantArray;

typedef TVariantArray *PVariantArray;

enum DECLSPEC_DENUM TVarFlag : unsigned char { vfByRef, vfVariant };

typedef System::Set<TVarFlag, TVarFlag::vfByRef, TVarFlag::vfVariant> TVarFlags;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EInterpreterError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EInterpreterError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EInterpreterError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EInterpreterError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EInterpreterError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EInterpreterError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EInterpreterError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EInterpreterError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EInterpreterError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EInterpreterError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EInterpreterError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EInterpreterError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EInterpreterError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EInterpreterError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCustomDataBlockInterpreter : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual void __fastcall AddDispatch(TDataDispatch* Value) = 0 ;
	virtual void __fastcall RemoveDispatch(TDataDispatch* Value) = 0 ;
	virtual void __fastcall CallFreeObject(int DispatchIndex) = 0 ;
	virtual HRESULT __stdcall CallGetIDsOfNames(int DispatchIndex, const GUID &IID, void * Names, int NameCount, int LocaleID, void * DispIDs) = 0 ;
	virtual HRESULT __stdcall CallInvoke(int DispatchIndex, int DispID, const GUID &IID, int LocaleID, System::Word Flags, void *Params, void * VarResult, void * ExcepInfo, void * ArgErr) = 0 ;
	virtual System::OleVariant __fastcall CallGetServerList() = 0 ;
	virtual System::OleVariant __fastcall InternalCreateObject(const GUID &ClassID) = 0 ;
	virtual System::OleVariant __fastcall CreateObject(const System::UnicodeString Name) = 0 ;
	virtual int __fastcall StoreObject(const System::OleVariant &Value) = 0 ;
	virtual _di_IDispatch __fastcall LockObject(int ID) = 0 ;
	virtual void __fastcall UnlockObject(int ID, const _di_IDispatch Disp) = 0 ;
	virtual void __fastcall ReleaseObject(int ID) = 0 ;
	virtual bool __fastcall CanCreateObject(const GUID &ClassID) = 0 ;
	virtual System::OleVariant __fastcall CallCreateObject(System::UnicodeString Name) = 0 ;
	
public:
	virtual void __fastcall InterpretData(const _di_IDataBlock Data) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TCustomDataBlockInterpreter() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCustomDataBlockInterpreter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDataBlockInterpreter : public TCustomDataBlockInterpreter
{
	typedef TCustomDataBlockInterpreter inherited;
	
private:
	System::Classes::TList* FDispatchList;
	System::OleVariant FDispList;
	_di_ISendDataBlock FSendDataBlock;
	System::UnicodeString FCheckRegValue;
	void * __fastcall GetVariantPointer(const System::OleVariant &Value);
	void __fastcall CopyDataByRef(const TVarData &Source, TVarData &Dest);
	System::OleVariant __fastcall ReadArray(int VType, const _di_IDataBlock Data);
	void __fastcall WriteArray(const System::OleVariant &Value, const _di_IDataBlock Data);
	System::OleVariant __fastcall ReadVariant(/* out */ TVarFlags &Flags, const _di_IDataBlock Data);
	void __fastcall WriteVariant(const System::OleVariant &Value, const _di_IDataBlock Data);
	void __fastcall DoException(const _di_IDataBlock Data);
	
protected:
	virtual void __fastcall AddDispatch(TDataDispatch* Value);
	virtual void __fastcall RemoveDispatch(TDataDispatch* Value);
	virtual System::OleVariant __fastcall InternalCreateObject(const GUID &ClassID);
	virtual System::OleVariant __fastcall CreateObject(const System::UnicodeString Name);
	virtual int __fastcall StoreObject(const System::OleVariant &Value);
	virtual _di_IDispatch __fastcall LockObject(int ID);
	virtual void __fastcall UnlockObject(int ID, const _di_IDispatch Disp);
	virtual void __fastcall ReleaseObject(int ID);
	virtual bool __fastcall CanCreateObject(const GUID &ClassID);
	virtual void __fastcall CallFreeObject(int DispatchIndex);
	virtual HRESULT __stdcall CallGetIDsOfNames(int DispatchIndex, const GUID &IID, void * Names, int NameCount, int LocaleID, void * DispIDs);
	virtual HRESULT __stdcall CallInvoke(int DispatchIndex, int DispID, const GUID &IID, int LocaleID, System::Word Flags, void *Params, void * VarResult, void * ExcepInfo, void * ArgErr);
	virtual System::OleVariant __fastcall CallGetServerList();
	void __fastcall DoCreateObject(const _di_IDataBlock Data);
	void __fastcall DoFreeObject(const _di_IDataBlock Data);
	void __fastcall DoGetIDsOfNames(const _di_IDataBlock Data);
	void __fastcall DoInvoke(const _di_IDataBlock Data);
	virtual bool __fastcall DoCustomAction(int Action, const _di_IDataBlock Data);
	void __fastcall DoGetAppServerList(const _di_IDataBlock Data);
	void __fastcall DoGetServerList(const _di_IDataBlock Data);
	
public:
	__fastcall TDataBlockInterpreter(_di_ISendDataBlock SendDataBlock, System::UnicodeString CheckRegValue);
	__fastcall virtual ~TDataBlockInterpreter();
	virtual System::OleVariant __fastcall CallCreateObject(System::UnicodeString Name);
	virtual void __fastcall InterpretData(const _di_IDataBlock Data);
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDataDispatch : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	int FDispatchIndex;
	TCustomDataBlockInterpreter* FInterpreter;
	
protected:
	__property int DispatchIndex = {read=FDispatchIndex, nodefault};
	HRESULT __stdcall GetTypeInfoCount(/* out */ int &Count);
	HRESULT __stdcall GetTypeInfo(int Index, int LocaleID, /* out */ void *TypeInfo);
	HRESULT __stdcall GetIDsOfNames(const GUID &IID, void * Names, int NameCount, int LocaleID, void * DispIDs);
	HRESULT __stdcall Invoke(int DispID, const GUID &IID, int LocaleID, System::Word Flags, void *Params, void * VarResult, void * ExcepInfo, void * ArgErr);
	
public:
	__fastcall TDataDispatch(TCustomDataBlockInterpreter* Interpreter, int DispatchIndex);
	__fastcall virtual ~TDataDispatch();
private:
	void *__IDispatch;	// IDispatch 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {00020400-0000-0000-C000-000000000046}
	operator _di_IDispatch()
	{
		_di_IDispatch intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDispatch*(void) { return (IDispatch*)&__IDispatch; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TTransportThread : public System::Classes::TThread
{
	typedef System::Classes::TThread inherited;
	
private:
	NativeUInt FParentHandle;
	NativeUInt FSemaphore;
	_di_ITransport FTransport;
	
public:
	__fastcall virtual TTransportThread(NativeUInt AHandle, _di_ITransport Transport);
	__fastcall virtual ~TTransportThread();
#ifndef _WIN64
	__property NativeUInt Semaphore = {read=FSemaphore, nodefault};
#else /* _WIN64 */
	__property NativeUInt Semaphore = {read=FSemaphore};
#endif /* _WIN64 */
	virtual void __fastcall Execute();
};


class PASCALIMPLEMENTATION TStreamedConnection : public Datasnap::Win::Mconnect::TDispatchConnection
{
	typedef Datasnap::Win::Mconnect::TDispatchConnection inherited;
	
private:
	int FRefCount;
	NativeUInt FHandle;
	TTransportThread* FTransport;
	_di_ITransport FTransIntf;
	TCustomDataBlockInterpreter* FInterpreter;
	bool FSupportCallbacks;
	GUID FInterceptGUID;
	System::UnicodeString FInterceptName;
	NativeUInt __fastcall GetHandle();
	void __fastcall TransportTerminated(System::TObject* Sender);
	void __fastcall SetSupportCallbacks(bool Value);
	void __fastcall SetInterceptName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetInterceptGUID();
	void __fastcall SetInterceptGUID(const System::UnicodeString Value);
	
protected:
	HIDESBASE HRESULT __stdcall QueryInterface(const GUID &IID, /* out */ void *Obj);
	HIDESBASE int __stdcall _AddRef();
	HIDESBASE int __stdcall _Release();
	_di_IDataBlock __stdcall Send(const _di_IDataBlock Data, bool WaitForResult);
	virtual void __fastcall InternalOpen();
	virtual void __fastcall InternalClose();
	MESSAGE void __fastcall ThreadReceivedStream(Winapi::Messages::TMessage &Message);
	MESSAGE void __fastcall ThreadException(Winapi::Messages::TMessage &Message);
	void __fastcall WndProc(Winapi::Messages::TMessage &Message);
	virtual _di_ITransport __fastcall CreateTransport();
	virtual void __fastcall DoConnect();
	virtual void __fastcall DoDisconnect();
	virtual void __fastcall DoError(System::Sysutils::Exception* E);
	virtual TCustomDataBlockInterpreter* __fastcall GetInterpreter();
	__property TCustomDataBlockInterpreter* Interpreter = {read=GetInterpreter};
#ifndef _WIN64
	__property NativeUInt Handle = {read=GetHandle, nodefault};
#else /* _WIN64 */
	__property NativeUInt Handle = {read=GetHandle};
#endif /* _WIN64 */
	__property bool SupportCallbacks = {read=FSupportCallbacks, write=SetSupportCallbacks, default=1};
	__property System::UnicodeString InterceptGUID = {read=GetInterceptGUID, write=SetInterceptGUID};
	__property System::UnicodeString InterceptName = {read=FInterceptName, write=SetInterceptName};
	
public:
	virtual System::OleVariant __fastcall GetInterceptorList();
	virtual System::OleVariant __fastcall GetServerList();
	__fastcall virtual TStreamedConnection(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TStreamedConnection();
private:
	void *__ISendDataBlock;	// ISendDataBlock 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {87AD1043-470E-11D1-88D5-00A0248E5091}
	operator _di_ISendDataBlock()
	{
		_di_ISendDataBlock intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator ISendDataBlock*(void) { return (ISendDataBlock*)&__ISendDataBlock; }
	#endif
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ESocketConnectionError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ESocketConnectionError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ESocketConnectionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ESocketConnectionError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ESocketConnectionError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ESocketConnectionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ESocketConnectionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ESocketConnectionError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ESocketConnectionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESocketConnectionError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESocketConnectionError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESocketConnectionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESocketConnectionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ESocketConnectionError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSocketTransport : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	NativeUInt FEvent;
	System::UnicodeString FAddress;
	System::UnicodeString FHost;
	int FPort;
	System::Win::Scktcomp::TClientSocket* FClientSocket;
	System::Win::Scktcomp::TCustomWinSocket* FSocket;
	System::UnicodeString FInterceptGUID;
	_di_IDataIntercept FInterceptor;
	bool FCreateAttempted;
	bool __fastcall CheckInterceptor();
	void __fastcall InterceptIncoming(const _di_IDataBlock Data);
	void __fastcall InterceptOutgoing(const _di_IDataBlock Data);
	
protected:
	NativeUInt __stdcall GetWaitEvent();
	bool __stdcall GetConnected();
	void __stdcall SetConnected(bool Value);
	_di_IDataBlock __stdcall Receive(bool WaitForInput, NativeInt Context);
	NativeInt __stdcall Send(const _di_IDataBlock Data);
	
public:
	__fastcall TSocketTransport();
	__fastcall virtual ~TSocketTransport();
	__property System::UnicodeString Host = {read=FHost, write=FHost};
	__property System::UnicodeString Address = {read=FAddress, write=FAddress};
	__property int Port = {read=FPort, write=FPort, nodefault};
	__property System::Win::Scktcomp::TCustomWinSocket* Socket = {read=FSocket, write=FSocket};
	__property System::UnicodeString InterceptGUID = {read=FInterceptGUID, write=FInterceptGUID};
private:
	void *__ITransport;	// ITransport 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CA6564C1-4683-11D1-88D4-00A0248E5091}
	operator _di_ITransport()
	{
		_di_ITransport intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator ITransport*(void) { return (ITransport*)&__ITransport; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TSocketConnection : public TStreamedConnection
{
	typedef TStreamedConnection inherited;
	
private:
	System::UnicodeString FAddress;
	System::UnicodeString FHost;
	int FPort;
	void __fastcall SetAddress(System::UnicodeString Value);
	void __fastcall SetHost(System::UnicodeString Value);
	bool __fastcall IsHostStored();
	bool __fastcall IsAddressStored();
	
protected:
	virtual _di_ITransport __fastcall CreateTransport();
	virtual void __fastcall DoConnect();
	
public:
	__fastcall virtual TSocketConnection(System::Classes::TComponent* AOwner);
	
__published:
	__property System::UnicodeString Address = {read=FAddress, write=SetAddress, stored=IsAddressStored};
	__property System::UnicodeString Host = {read=FHost, write=SetHost, stored=IsHostStored};
	__property InterceptGUID = {default=0};
	__property InterceptName = {default=0};
	__property int Port = {read=FPort, write=FPort, default=211};
	__property SupportCallbacks = {default=1};
	__property ObjectBroker;
public:
	/* TStreamedConnection.Destroy */ inline __fastcall virtual ~TSocketConnection() { }
	
};


class PASCALIMPLEMENTATION TWebConnection : public TStreamedConnection
{
	typedef TStreamedConnection inherited;
	
private:
	System::UnicodeString FAgent;
	System::UnicodeString FUserName;
	System::UnicodeString FPassword;
	System::UnicodeString FURL;
	System::UnicodeString FURLHost;
	System::UnicodeString FURLSite;
	int FURLPort;
	int FURLScheme;
	System::UnicodeString FProxy;
	System::UnicodeString FProxyByPass;
	void *FInetRoot;
	void *FInetConnect;
	TCustomDataBlockInterpreter* FInterpreter;
	void __fastcall Check(bool Error);
	bool __fastcall IsURLStored();
	void __fastcall SetURL(const System::UnicodeString Value);
	
protected:
	virtual TCustomDataBlockInterpreter* __fastcall GetInterpreter();
	NativeUInt __stdcall GetWaitEvent();
	bool __stdcall Transport_GetConnected();
	void __stdcall Transport_SetConnected(bool Value);
	_di_IDataBlock __stdcall Receive(bool WaitForInput, NativeInt Context);
	HIDESBASE NativeInt __stdcall Send(const _di_IDataBlock Data);
	virtual void __fastcall SetConnected(bool Value);
	virtual _di_ITransport __fastcall CreateTransport();
	virtual void __fastcall DoConnect();
	__property SupportCallbacks = {default=0};
	
public:
	__fastcall virtual TWebConnection(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TWebConnection();
	
__published:
	__property System::UnicodeString Agent = {read=FAgent, write=FAgent};
	__property System::UnicodeString UserName = {read=FUserName, write=FUserName};
	__property System::UnicodeString Password = {read=FPassword, write=FPassword};
	__property System::UnicodeString URL = {read=FURL, write=SetURL, stored=IsURLStored};
	__property System::UnicodeString Proxy = {read=FProxy, write=FProxy};
	__property System::UnicodeString ProxyByPass = {read=FProxyByPass, write=FProxyByPass};
	__property ObjectBroker;
private:
	void *__ITransport;	// ITransport 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CA6564C1-4683-11D1-88D4-00A0248E5091}
	operator _di_ITransport()
	{
		_di_ITransport intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator ITransport*(void) { return (ITransport*)&__ITransport; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
static const System::Word CallSig = System::Word(0xda00);
static const System::Word ResultSig = System::Word(0xdb00);
static const System::Int8 asError = System::Int8(0x1);
static const System::Int8 asInvoke = System::Int8(0x2);
static const System::Int8 asGetID = System::Int8(0x3);
static const System::Int8 asCreateObject = System::Int8(0x4);
static const System::Int8 asFreeObject = System::Int8(0x5);
static const System::Int8 asGetServers = System::Int8(0x10);
static const System::Int8 asGetGUID = System::Int8(0x11);
static const System::Int8 asGetAppServers = System::Int8(0x12);
static const System::Int8 asSoapCommand = System::Int8(0x14);
static const System::Byte asMask = System::Byte(0xff);
static const System::Word THREAD_SENDSTREAM = System::Word(0x401);
static const System::Word THREAD_RECEIVEDSTREAM = System::Word(0x402);
static const System::Word THREAD_EXCEPTION = System::Word(0x403);
static const System::Word THREAD_SENDNOTIFY = System::Word(0x404);
static const System::Word THREAD_REPLACETRANSPORT = System::Word(0x405);
extern DELPHI_PACKAGE NativeUInt __stdcall (*WSACreateEvent)(void);
extern DELPHI_PACKAGE bool __stdcall (*WSAResetEvent)(NativeUInt hEvent);
extern DELPHI_PACKAGE bool __stdcall (*WSACloseEvent)(NativeUInt hEvent);
extern DELPHI_PACKAGE int __stdcall (*WSAEventSelect)(NativeInt s, NativeUInt hEventObject, int lNetworkEvents);
extern DELPHI_PACKAGE bool __fastcall LoadWinSock2(void);
extern DELPHI_PACKAGE void __fastcall GetPacketInterceptorList(System::Classes::TStringList* List);
}	/* namespace Sconnect */
}	/* namespace Win */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_WIN_SCONNECT)
using namespace Datasnap::Win::Sconnect;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_WIN)
using namespace Datasnap::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_Win_SconnectHPP
