// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Net.Socket.pas' rev: 34.00 (Windows)

#ifndef System_Net_SocketHPP
#define System_Net_SocketHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Winapi.Winsock2.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Net
{
namespace Socket
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS ESocketError;
struct TIPAddress;
struct TNetEndpoint;
struct TFDSet;
class DELPHICLASS TSocket;
class DELPHICLASS TSocketStream;
//-- type declarations -------------------------------------------------------
typedef NativeUInt TSocketHandle;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ESocketError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ESocketError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ESocketError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ESocketError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ESocketError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ESocketError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ESocketError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ESocketError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ESocketError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESocketError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESocketError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESocketError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESocketError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ESocketError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum class DECLSPEC_DENUM TSocketType : unsigned char { TCP, UDP, RAW, RDM, SEQ };

enum class DECLSPEC_DENUM TSocketFlag : unsigned char { OOB, PEEK, DONTROUTE, WAITALL };

typedef System::Set<TSocketFlag, _DELPHI_SET_ENUMERATOR(TSocketFlag::OOB), _DELPHI_SET_ENUMERATOR(TSocketFlag::WAITALL)> TSocketFlags;

enum class DECLSPEC_DENUM TSocketState : unsigned char { Connected, Client, Listening };

typedef System::Set<TSocketState, _DELPHI_SET_ENUMERATOR(TSocketState::Connected), _DELPHI_SET_ENUMERATOR(TSocketState::Listening)> TSocketStates;

struct DECLSPEC_DRECORD TIPAddress
{
private:
	in_addr FAddr;
	static TIPAddress __fastcall GetLocalHost();
	static TIPAddress __fastcall GetBroadcast();
	static TIPAddress __fastcall GetAny();
	static unsigned __fastcall OctetsToN(const System::Byte B1, const System::Byte B2, const System::Byte B3, const System::Byte B4);
	System::UnicodeString __fastcall GetAddress();
	
public:
	static TIPAddress __fastcall Create(const System::UnicodeString Name)/* overload */;
	static TIPAddress __fastcall Create(const unsigned Address)/* overload */;
	static TIPAddress __fastcall Create(const System::Byte B1, const System::Byte B2, const System::Byte B3, const System::Byte B4)/* overload */;
	static TIPAddress __fastcall Create(const TIPAddress Address, TIPAddress Mask)/* overload */;
	static TIPAddress __fastcall Create(const in_addr Address)/* overload */;
	static TIPAddress __fastcall LookupName(const System::UnicodeString Name);
	static TIPAddress __fastcall LookupAddress(const System::UnicodeString Address);
	__fastcall operator in_addr();
	__property in_addr Addr = {read=FAddr};
	__property System::UnicodeString Address = {read=GetAddress};
	/* static */ __property TIPAddress Any = {read=GetAny};
	/* static */ __property TIPAddress LocalHost = {read=GetLocalHost};
	/* static */ __property TIPAddress Broadcast = {read=GetBroadcast};
};


struct DECLSPEC_DRECORD TNetEndpoint
{
private:
	sockaddr_in FEndPoint;
	TIPAddress __fastcall GetAddress();
	System::Word __fastcall GetFamily();
	System::Word __fastcall GetPort();
	void __fastcall SetAddress(const TIPAddress Address)/* overload */;
	void __fastcall SetFamily(const System::Word Family);
	void __fastcall SetPort(const System::Word Port)/* overload */;
	static void __fastcall SetSize(TNetEndpoint &Endpoint);
	
public:
	static TNetEndpoint __fastcall Create(const System::UnicodeString Name, const System::UnicodeString Service, TSocketType SocketType = (TSocketType)(0x0))/* overload */;
	static TNetEndpoint __fastcall Create(const unsigned Address, const System::Word Port)/* overload */;
	static TNetEndpoint __fastcall Create(const System::Byte B1, const System::Byte B2, const System::Byte B3, const System::Byte B4, const System::Word Port)/* overload */;
	static TNetEndpoint __fastcall Create(const TIPAddress Address, const System::UnicodeString Service, TSocketType SocketType = (TSocketType)(0x0))/* overload */;
	static TNetEndpoint __fastcall Create(const TIPAddress Address, const System::Word Port)/* overload */;
	static TNetEndpoint __fastcall Create(const System::Word Family, const System::UnicodeString Name, const System::UnicodeString Service, TSocketType SocketType = (TSocketType)(0x0))/* overload */;
	static TNetEndpoint __fastcall Create(const System::Word Family, const unsigned Address, const System::Word Port)/* overload */;
	static TNetEndpoint __fastcall Create(const System::Word Family, const System::Byte B1, const System::Byte B2, const System::Byte B3, const System::Byte B4, const System::Word Port)/* overload */;
	static TNetEndpoint __fastcall Create(const System::Word Family, const TIPAddress Address, const System::UnicodeString Service, TSocketType SocketType = (TSocketType)(0x0))/* overload */;
	static TNetEndpoint __fastcall Create(const System::Word Family, const TIPAddress Address, const System::Word Port)/* overload */;
	static TNetEndpoint __fastcall Create(const sockaddr_in &Endpoint)/* overload */;
	__fastcall operator sockaddr_in();
	__fastcall operator sockaddr();
	static TNetEndpoint __fastcall _op_Implicit(const sockaddr_in &Endpoint);
	static TNetEndpoint __fastcall _op_Implicit(const sockaddr &Endpoint);
	static System::Word __fastcall LookupService(const System::UnicodeString Service, TSocketType SocketType = (TSocketType)(0x0));
	void __fastcall SetAddress(const System::UnicodeString Address)/* overload */;
	void __fastcall SetAddress(const unsigned Address)/* overload */;
	void __fastcall SetAddress(const System::Byte B1, const System::Byte B2, const System::Byte B3, const System::Byte B4)/* overload */;
	void __fastcall SetPort(const System::UnicodeString Service, TSocketType SocketType = (TSocketType)(0x0))/* overload */;
	__property TIPAddress Address = {read=GetAddress, write=SetAddress};
	__property System::Word Family = {read=GetFamily, write=SetFamily};
	__property System::Word Port = {read=GetPort, write=SetPort};
	
	TNetEndpoint& operator =(const sockaddr_in &Endpoint) { *this = TNetEndpoint::_op_Implicit(Endpoint); return *this; }
	TNetEndpoint& operator =(const sockaddr &Endpoint) { *this = TNetEndpoint::_op_Implicit(Endpoint); return *this; }
};


typedef TFDSet *PFDSet;

struct DECLSPEC_DRECORD TFDSet
{
private:
	fd_set FFDSet;
	static TFDSet __fastcall CreateNew(TSocket* const *Sockets, const int Sockets_High)/* overload */;
	void __fastcall ValidateHandle(TSocket* const ASocket);
	Winapi::Winsock2::PFdSet __fastcall GetFdSet();
	int __fastcall GetMaxFd();
	void __fastcall Set(const NativeUInt AHandle)/* overload */;
	void __fastcall Clear(const NativeUInt AHandle)/* overload */;
	bool __fastcall IsSet(const NativeUInt AHandle)/* overload */;
	
public:
	static TFDSet __fastcall Create()/* overload */;
	static TFDSet __fastcall Create(TSocket* const *Sockets, const int Sockets_High)/* overload */;
	static TFDSet __fastcall Create(TSocket* const Socket)/* overload */;
	void __fastcall Set(TSocket* const ASocket)/* overload */;
	void __fastcall Clear(TSocket* const ASocket)/* overload */;
	void __fastcall Zero();
	bool __fastcall IsSet(TSocket* const ASocket)/* overload */;
	__fastcall operator PFDSet();
	__property Winapi::Winsock2::PFdSet FdSet = {read=GetFdSet};
	__property int MaxFd = {read=GetMaxFd};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSocket : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef int TSockSize;
	
	typedef System::Set<TSocketType, _DELPHI_SET_ENUMERATOR(TSocketType::TCP), _DELPHI_SET_ENUMERATOR(TSocketType::SEQ)> TSocketTypes;
	
	
protected:
	class DELPHICLASS TSocketAsyncResult;
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TSocketAsyncResult : public System::Classes::TBaseAsyncResult
	{
		typedef System::Classes::TBaseAsyncResult inherited;
		
	private:
		System::Classes::_di_TAsyncCallback FAsyncCallback;
		System::Classes::TAsyncProcedureEvent FAsyncCallbackEvent;
		TSocket* __fastcall GetSocket();
		
	protected:
		virtual void __fastcall Complete();
		virtual void __fastcall Schedule();
		__fastcall TSocketAsyncResult(System::TObject* const AContext, const System::Classes::_di_TAsyncCallback AAsyncCallback, System::Classes::TAsyncProcedureEvent AAsyncCallbackEvent);
		__property TSocket* Socket = {read=GetSocket};
	public:
		/* TBaseAsyncResult.Destroy */ inline __fastcall virtual ~TSocketAsyncResult() { }
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	class DELPHICLASS TSocketReceiveAsyncResult;
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TSocketReceiveAsyncResult : public TSocket::TSocketAsyncResult
	{
		typedef TSocket::TSocketAsyncResult inherited;
		
	private:
#ifndef _WIN64
		System::DelphiInterface<System::Sysutils::TFunc__1<System::DynamicArray<System::Byte> > > FBytesFunc;
		System::DynamicArray<System::Byte> FResult;
		System::DynamicArray<System::Byte> __fastcall GetResultBytes();
#else /* _WIN64 */
		System::DelphiInterface<System::Sysutils::TFunc__1<System::TArray__1<System::Byte> > > FBytesFunc;
		System::TArray__1<System::Byte> FResult;
		System::TArray__1<System::Byte> __fastcall GetResultBytes();
#endif /* _WIN64 */
		System::UnicodeString __fastcall GetResultString();
		
	protected:
		virtual void __fastcall AsyncDispatch();
#ifndef _WIN64
		__fastcall TSocketReceiveAsyncResult(System::TObject* const AContext, const System::DelphiInterface<System::Sysutils::TFunc__1<System::DynamicArray<System::Byte> > > ABytesFunc, const System::Classes::_di_TAsyncCallback AAsyncCallback, System::Classes::TAsyncProcedureEvent AAsyncCallbackEvent);
		__property System::DynamicArray<System::Byte> ResultBytes = {read=GetResultBytes};
#else /* _WIN64 */
		__fastcall TSocketReceiveAsyncResult(System::TObject* const AContext, const System::DelphiInterface<System::Sysutils::TFunc__1<System::TArray__1<System::Byte> > > ABytesFunc, const System::Classes::_di_TAsyncCallback AAsyncCallback, System::Classes::TAsyncProcedureEvent AAsyncCallbackEvent);
		__property System::TArray__1<System::Byte> ResultBytes = {read=GetResultBytes};
#endif /* _WIN64 */
		__property System::UnicodeString ResultString = {read=GetResultString};
	public:
		/* TBaseAsyncResult.Destroy */ inline __fastcall virtual ~TSocketReceiveAsyncResult() { }
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	class DELPHICLASS TSocketReceiveFromAsyncResult;
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TSocketReceiveFromAsyncResult : public TSocket::TSocketAsyncResult
	{
		typedef TSocket::TSocketAsyncResult inherited;
		
		
	protected:
		__interface DELPHIINTERFACE TReceiveFromFunc;
		typedef System::DelphiInterface<TReceiveFromFunc> _di_TReceiveFromFunc;
		__interface TReceiveFromFunc  : public System::IInterface 
		{
#ifndef _WIN64
			virtual System::DynamicArray<System::Byte> __fastcall Invoke(/* out */ TNetEndpoint &NetEndpoint) = 0 ;
#else /* _WIN64 */
			virtual System::TArray__1<System::Byte> __fastcall Invoke(/* out */ TNetEndpoint &NetEndpoint) = 0 ;
#endif /* _WIN64 */
		};
		
		
	private:
		_di_TReceiveFromFunc FReceiveFromFunc;
#ifndef _WIN64
		System::DynamicArray<System::Byte> FResult;
#else /* _WIN64 */
		System::TArray__1<System::Byte> FResult;
#endif /* _WIN64 */
		TNetEndpoint FNetEndpoint;
#ifndef _WIN64
		System::DynamicArray<System::Byte> __fastcall GetResultBytes();
#else /* _WIN64 */
		System::TArray__1<System::Byte> __fastcall GetResultBytes();
#endif /* _WIN64 */
		System::UnicodeString __fastcall GetResultString();
		
	protected:
		virtual void __fastcall AsyncDispatch();
		__fastcall TSocketReceiveFromAsyncResult(System::TObject* const AContext, const _di_TReceiveFromFunc AReceiveFromFunc, const System::Classes::_di_TAsyncCallback AAsyncCallback, System::Classes::TAsyncProcedureEvent AAsyncCallbackEvent);
#ifndef _WIN64
		__property System::DynamicArray<System::Byte> ResultBytes = {read=GetResultBytes};
#else /* _WIN64 */
		__property System::TArray__1<System::Byte> ResultBytes = {read=GetResultBytes};
#endif /* _WIN64 */
		__property System::UnicodeString ResultString = {read=GetResultString};
		__property TNetEndpoint NetEndpoint = {read=FNetEndpoint};
	public:
		/* TBaseAsyncResult.Destroy */ inline __fastcall virtual ~TSocketReceiveFromAsyncResult() { }
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	class DELPHICLASS TSocketSendAsyncResult;
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TSocketSendAsyncResult : public TSocket::TSocketAsyncResult
	{
		typedef TSocket::TSocketAsyncResult inherited;
		
	private:
		System::DelphiInterface<System::Sysutils::TFunc__1<int> > FFunc;
		int FResult;
		int __fastcall GetResult();
		
	protected:
		virtual void __fastcall AsyncDispatch();
		__fastcall TSocketSendAsyncResult(System::TObject* const AContext, const System::DelphiInterface<System::Sysutils::TFunc__1<int> > AFunc, const System::Classes::_di_TAsyncCallback AAsyncCallback, System::Classes::TAsyncProcedureEvent AAsyncCallbackEvent);
		__property int Result = {read=GetResult, nodefault};
	public:
		/* TBaseAsyncResult.Destroy */ inline __fastcall virtual ~TSocketSendAsyncResult() { }
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	class DELPHICLASS TSocketAcceptAsyncResult;
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TSocketAcceptAsyncResult : public TSocket::TSocketAsyncResult
	{
		typedef TSocket::TSocketAsyncResult inherited;
		
	private:
		System::DelphiInterface<System::Sysutils::TFunc__1<TSocket*> > FFunc;
		TSocket* FResult;
		TSocket* __fastcall GetResult();
		
	protected:
		virtual void __fastcall AsyncDispatch();
		__fastcall TSocketAcceptAsyncResult(System::TObject* const AContext, const System::DelphiInterface<System::Sysutils::TFunc__1<TSocket*> > AFunc, const System::Classes::_di_TAsyncCallback AAsyncCallback, System::Classes::TAsyncProcedureEvent AAsyncCallbackEvent);
		__property TSocket* Result = {read=GetResult};
	public:
		/* TBaseAsyncResult.Destroy */ inline __fastcall virtual ~TSocketAcceptAsyncResult() { }
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	class DELPHICLASS TSocketConnectResult;
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TSocketConnectResult : public TSocket::TSocketAsyncResult
	{
		typedef TSocket::TSocketAsyncResult inherited;
		
	private:
		System::Sysutils::_di_TProc FProc;
		
	protected:
		virtual void __fastcall AsyncDispatch();
		__fastcall TSocketConnectResult(System::TObject* const AContext, const System::Sysutils::_di_TProc AProc, const System::Classes::_di_TAsyncCallback AAsyncCallback, System::Classes::TAsyncProcedureEvent AAsyncCallbackEvent);
	public:
		/* TBaseAsyncResult.Destroy */ inline __fastcall virtual ~TSocketConnectResult() { }
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
private:
	NativeUInt FSocket;
	TSocketStates FState;
	sockaddr_in FAddr;
	TSocketType FSockType;
	System::Sysutils::TEncoding* FEncoding;
	TNetEndpoint __fastcall GetEndpoint();
	System::UnicodeString __fastcall GetLocalHost();
	System::UnicodeString __fastcall GetLocalAddress();
	int __fastcall GetLocalPort();
	TNetEndpoint __fastcall GetLocalEndpoint();
	System::UnicodeString __fastcall GetRemoteHost();
	System::UnicodeString __fastcall GetRemoteAddress();
	int __fastcall GetRemotePort();
	TNetEndpoint __fastcall GetRemoteEndpoint();
	void __fastcall ValidSocketTypes(TSocketTypes SocketTypes);
	int __fastcall InternalConvertFlags(TSocketFlags Flags);
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
protected:
	virtual TSocket* __fastcall GetClientSocket(NativeUInt Handle, const sockaddr_in &Addr);
	virtual NativeUInt __fastcall CreateSocket();
	virtual void __fastcall DoBind();
	virtual void __fastcall DoConnect();
	virtual void __fastcall DoListen(int QueueSize = 0xffffffff);
	sockaddr_in __fastcall InitSocket(const System::UnicodeString Name, const System::UnicodeString Address, const System::UnicodeString Service, System::Word Port, bool Client, bool Broadcast = false);
	int __fastcall ConvertFlags(TSocketFlags Flags);
	System::Types::TWaitResult __fastcall WaitForData(unsigned ATimeout = (unsigned)(0xffffffff));
	__fastcall TSocket(NativeUInt ASocket, const sockaddr_in &AAddr, System::Sysutils::TEncoding* const AEncoding)/* overload */;
	
public:
	__fastcall TSocket(TSocketType ASockType, System::Sysutils::TEncoding* const AEncoding)/* overload */;
	__fastcall virtual ~TSocket();
	TSocket* __fastcall Accept(unsigned Timeout = (unsigned)(0xffffffff));
	System::Types::_di_IAsyncResult __fastcall BeginAccept(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, unsigned Timeout = (unsigned)(0xffffffff))/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginAccept(const System::Classes::_di_TAsyncCallback AsyncCallback, unsigned Timeout = (unsigned)(0xffffffff))/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginAccept(unsigned Timeout = (unsigned)(0xffffffff))/* overload */;
	TSocket* __fastcall EndAccept(const System::Types::_di_IAsyncResult AAsyncResult);
	void __fastcall Bind(const TNetEndpoint &Endpoint)/* overload */;
	void __fastcall Bind(System::Word Port)/* overload */;
	void __fastcall Close()/* overload */;
	void __fastcall Close(bool ForceClosed)/* overload */;
	void __fastcall Listen(const System::UnicodeString Address, const System::UnicodeString Service, System::Word Port, int QueueSize = 0xffffffff)/* overload */;
	void __fastcall Listen(const TNetEndpoint &Endpoint, int QueueSize = 0xffffffff)/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginConnect(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString Name, const System::UnicodeString Address, const System::UnicodeString Service, System::Word Port)/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginConnect(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const TNetEndpoint &Endpoint)/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginConnect(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString Name, const System::UnicodeString Address, const System::UnicodeString Service, System::Word Port)/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginConnect(const System::Classes::_di_TAsyncCallback AsyncCallback, const TNetEndpoint &Endpoint)/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginConnect(const System::UnicodeString Name, const System::UnicodeString Address, const System::UnicodeString Service, System::Word Port)/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginConnect(const TNetEndpoint &Endpoint)/* overload */;
	void __fastcall EndConnect(const System::Types::_di_IAsyncResult AAsyncResult);
	void __fastcall Connect(const System::UnicodeString Name, const System::UnicodeString Address, const System::UnicodeString Service, System::Word Port)/* overload */;
	void __fastcall Connect(const TNetEndpoint &EndPoint)/* overload */;
	void __fastcall ListenBroadcast(const TNetEndpoint &Endpoint)/* overload */;
	void __fastcall ListenBroadcast(System::Word Port)/* overload */;
	void __fastcall OpenBroadcast(const TNetEndpoint &Endpoint)/* overload */;
	void __fastcall OpenBroadcast(System::Word Port)/* overload */;
	TIPAddress __fastcall LookupName(const System::UnicodeString name);
	int __fastcall LookupService(const System::UnicodeString service);
	System::Types::_di_IAsyncResult __fastcall BeginReceive(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, int Count, TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginReceive(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginReceive(const System::Classes::_di_TAsyncCallback AsyncCallback, int Count, TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginReceive(const System::Classes::_di_TAsyncCallback AsyncCallback, TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginReceive(int Count, TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginReceive(TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::UnicodeString __fastcall EndReceiveString(const System::Types::_di_IAsyncResult AAsyncResult);
#ifndef _WIN64
	System::DynamicArray<System::Byte> __fastcall EndReceiveBytes(const System::Types::_di_IAsyncResult AAsyncResult);
#else /* _WIN64 */
	System::TArray__1<System::Byte> __fastcall EndReceiveBytes(const System::Types::_di_IAsyncResult AAsyncResult);
#endif /* _WIN64 */
	int __fastcall ReceiveLength();
	int __fastcall Receive(void *Buf, int Count, int Flags)/* overload */;
	int __fastcall Receive(void *Buf, int Count, TSocketFlags Flags = TSocketFlags() )/* overload */;
#ifndef _WIN64
	System::DynamicArray<System::Byte> __fastcall Receive(int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
	int __fastcall Receive(/* out */ System::DynamicArray<System::Byte> &Bytes, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
#else /* _WIN64 */
	System::TArray__1<System::Byte> __fastcall Receive(int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
	int __fastcall Receive(/* out */ System::TArray__1<System::Byte> &Bytes, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
#endif /* _WIN64 */
	int __fastcall Receive(System::Byte *Bytes, const int Bytes_High, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::UnicodeString __fastcall ReceiveString(TSocketFlags Flags = TSocketFlags() );
	System::Types::_di_IAsyncResult __fastcall BeginSend(const System::UnicodeString S, const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, TSocketFlags Flags = TSocketFlags() )/* overload */;
#ifndef _WIN64
	System::Types::_di_IAsyncResult __fastcall BeginSend(const System::DynamicArray<System::Byte> B, const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
#else /* _WIN64 */
	System::Types::_di_IAsyncResult __fastcall BeginSend(const System::TArray__1<System::Byte> B, const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
#endif /* _WIN64 */
	System::Types::_di_IAsyncResult __fastcall BeginSend(const System::UnicodeString S, const System::Classes::_di_TAsyncCallback AsyncCallback, TSocketFlags Flags = TSocketFlags() )/* overload */;
#ifndef _WIN64
	System::Types::_di_IAsyncResult __fastcall BeginSend(const System::DynamicArray<System::Byte> B, const System::Classes::_di_TAsyncCallback AsyncCallback, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
#else /* _WIN64 */
	System::Types::_di_IAsyncResult __fastcall BeginSend(const System::TArray__1<System::Byte> B, const System::Classes::_di_TAsyncCallback AsyncCallback, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
#endif /* _WIN64 */
	System::Types::_di_IAsyncResult __fastcall BeginSend(const System::UnicodeString S, TSocketFlags Flags = TSocketFlags() )/* overload */;
#ifndef _WIN64
	System::Types::_di_IAsyncResult __fastcall BeginSend(const System::DynamicArray<System::Byte> B, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
#else /* _WIN64 */
	System::Types::_di_IAsyncResult __fastcall BeginSend(const System::TArray__1<System::Byte> B, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
#endif /* _WIN64 */
	int __fastcall EndSend(const System::Types::_di_IAsyncResult AAsyncResult);
	int __fastcall Send(const void *Buf, int Count, int Flags)/* overload */;
	int __fastcall Send(const void *Buf, int Count, TSocketFlags Flags = TSocketFlags() )/* overload */;
	int __fastcall Send(const System::UnicodeString S, TSocketFlags Flags = TSocketFlags() )/* overload */;
#ifndef _WIN64
	int __fastcall Send(const System::DynamicArray<System::Byte> B, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
#else /* _WIN64 */
	int __fastcall Send(const System::TArray__1<System::Byte> B, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
#endif /* _WIN64 */
	int __fastcall Send(const System::Byte *B, const int B_High, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginReceiveFrom(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, int Count, TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginReceiveFrom(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginReceiveFrom(const System::Classes::_di_TAsyncCallback AsyncCallback, int Count, TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginReceiveFrom(const System::Classes::_di_TAsyncCallback AsyncCallback, TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginReceiveFrom(int Count, TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginReceiveFrom(TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::UnicodeString __fastcall EndReceiveStringFrom(const System::Types::_di_IAsyncResult AAsyncResult, /* out */ TNetEndpoint &AEndPoint)/* overload */;
#ifndef _WIN64
	System::DynamicArray<System::Byte> __fastcall EndReceiveBytesFrom(const System::Types::_di_IAsyncResult AAsyncResult, /* out */ TNetEndpoint &AEndPoint)/* overload */;
#else /* _WIN64 */
	System::TArray__1<System::Byte> __fastcall EndReceiveBytesFrom(const System::Types::_di_IAsyncResult AAsyncResult, /* out */ TNetEndpoint &AEndPoint)/* overload */;
#endif /* _WIN64 */
	System::UnicodeString __fastcall EndReceiveStringFrom(const System::Types::_di_IAsyncResult AAsyncResult)/* overload */;
#ifndef _WIN64
	System::DynamicArray<System::Byte> __fastcall EndReceiveBytesFrom(const System::Types::_di_IAsyncResult AAsyncResult)/* overload */;
#else /* _WIN64 */
	System::TArray__1<System::Byte> __fastcall EndReceiveBytesFrom(const System::Types::_di_IAsyncResult AAsyncResult)/* overload */;
#endif /* _WIN64 */
	int __fastcall ReceiveFrom(void *Buf, int Count, int Flags)/* overload */;
	int __fastcall ReceiveFrom(void *Buf, int Count, TSocketFlags Flags = TSocketFlags() )/* overload */;
#ifndef _WIN64
	System::DynamicArray<System::Byte> __fastcall ReceiveFrom(int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
	int __fastcall ReceiveFrom(/* out */ System::DynamicArray<System::Byte> &Bytes, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
#else /* _WIN64 */
	System::TArray__1<System::Byte> __fastcall ReceiveFrom(int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
	int __fastcall ReceiveFrom(/* out */ System::TArray__1<System::Byte> &Bytes, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
#endif /* _WIN64 */
	int __fastcall ReceiveFrom(System::Byte *Bytes, const int Bytes_High, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
	int __fastcall ReceiveFrom(void *Buf, int Count, /* out */ TNetEndpoint &Endpoint, int Flags)/* overload */;
	int __fastcall ReceiveFrom(void *Buf, int Count, /* out */ TNetEndpoint &Endpoint, TSocketFlags Flags = TSocketFlags() )/* overload */;
#ifndef _WIN64
	System::DynamicArray<System::Byte> __fastcall ReceiveFrom(/* out */ TNetEndpoint &Endpoint, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
	int __fastcall ReceiveFrom(/* out */ System::DynamicArray<System::Byte> &Bytes, /* out */ TNetEndpoint &Endpoint, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
#else /* _WIN64 */
	System::TArray__1<System::Byte> __fastcall ReceiveFrom(/* out */ TNetEndpoint &Endpoint, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
	int __fastcall ReceiveFrom(/* out */ System::TArray__1<System::Byte> &Bytes, /* out */ TNetEndpoint &Endpoint, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
#endif /* _WIN64 */
	int __fastcall ReceiveFrom(System::Byte *Bytes, const int Bytes_High, /* out */ TNetEndpoint &Endpoint, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::UnicodeString __fastcall ReceiveStringFrom(TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::UnicodeString __fastcall ReceiveStringFrom(/* out */ TNetEndpoint &Endpoint, TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginSendTo(const System::UnicodeString S, const System::Classes::_di_TAsyncCallback AsyncCallback, TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginSendTo(const System::UnicodeString S, const TNetEndpoint &Endpoint, const System::Classes::_di_TAsyncCallback AsyncCallback, TSocketFlags Flags = TSocketFlags() )/* overload */;
#ifndef _WIN64
	System::Types::_di_IAsyncResult __fastcall BeginSendTo(const System::DynamicArray<System::Byte> B, const System::Classes::_di_TAsyncCallback AsyncCallback, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginSendTo(const System::DynamicArray<System::Byte> B, const TNetEndpoint &Endpoint, const System::Classes::_di_TAsyncCallback AsyncCallback, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
#else /* _WIN64 */
	System::Types::_di_IAsyncResult __fastcall BeginSendTo(const System::TArray__1<System::Byte> B, const System::Classes::_di_TAsyncCallback AsyncCallback, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginSendTo(const System::TArray__1<System::Byte> B, const TNetEndpoint &Endpoint, const System::Classes::_di_TAsyncCallback AsyncCallback, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
#endif /* _WIN64 */
	System::Types::_di_IAsyncResult __fastcall BeginSendTo(const System::UnicodeString S, const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginSendTo(const System::UnicodeString S, const TNetEndpoint &Endpoint, const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, TSocketFlags Flags = TSocketFlags() )/* overload */;
#ifndef _WIN64
	System::Types::_di_IAsyncResult __fastcall BeginSendTo(const System::DynamicArray<System::Byte> B, const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginSendTo(const System::DynamicArray<System::Byte> B, const TNetEndpoint &Endpoint, const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
#else /* _WIN64 */
	System::Types::_di_IAsyncResult __fastcall BeginSendTo(const System::TArray__1<System::Byte> B, const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginSendTo(const System::TArray__1<System::Byte> B, const TNetEndpoint &Endpoint, const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
#endif /* _WIN64 */
	System::Types::_di_IAsyncResult __fastcall BeginSendTo(const System::UnicodeString S, TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginSendTo(const System::UnicodeString S, const TNetEndpoint &Endpoint, TSocketFlags Flags = TSocketFlags() )/* overload */;
#ifndef _WIN64
	System::Types::_di_IAsyncResult __fastcall BeginSendTo(const System::DynamicArray<System::Byte> B, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginSendTo(const System::DynamicArray<System::Byte> B, const TNetEndpoint &Endpoint, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
#else /* _WIN64 */
	System::Types::_di_IAsyncResult __fastcall BeginSendTo(const System::TArray__1<System::Byte> B, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginSendTo(const System::TArray__1<System::Byte> B, const TNetEndpoint &Endpoint, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
#endif /* _WIN64 */
	int __fastcall EndSendTo(const System::Types::_di_IAsyncResult AAsyncResult);
	int __fastcall SendTo(const void *Buf, int Count, int Flags)/* overload */;
	int __fastcall SendTo(const void *Buf, int Count, TSocketFlags Flags = TSocketFlags() )/* overload */;
	int __fastcall SendTo(const System::UnicodeString S, TSocketFlags Flags = TSocketFlags() )/* overload */;
	int __fastcall SendTo(const System::Byte *B, const int B_High, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
	int __fastcall SendTo(const void *Buf, int Count, const TNetEndpoint &Endpoint, int Flags)/* overload */;
	int __fastcall SendTo(const void *Buf, int Count, const TNetEndpoint &Endpoint, TSocketFlags Flags = TSocketFlags() )/* overload */;
	int __fastcall SendTo(const System::UnicodeString S, const TNetEndpoint &Endpoint, TSocketFlags Flags = TSocketFlags() )/* overload */;
	int __fastcall SendTo(const System::Byte *B, const int B_High, const TNetEndpoint &Endpoint, int Offset = 0x0, int Count = 0xffffffff, TSocketFlags Flags = TSocketFlags() )/* overload */;
	static System::Types::TWaitResult __fastcall Select(const PFDSet CheckRead, const PFDSet CheckWrite, const PFDSet CheckError, __int64 Microseconds);
	__property System::UnicodeString LocalHost = {read=GetLocalHost};
	__property System::UnicodeString LocalAddress = {read=GetLocalAddress};
	__property int LocalPort = {read=GetLocalPort, nodefault};
	__property TNetEndpoint LocalEndpoint = {read=GetLocalEndpoint};
	__property System::UnicodeString RemoteHost = {read=GetRemoteHost};
	__property System::UnicodeString RemoteAddress = {read=GetRemoteAddress};
	__property int RemotePort = {read=GetRemotePort, nodefault};
	__property TNetEndpoint RemoteEndpoint = {read=GetRemoteEndpoint};
	__property TNetEndpoint Endpoint = {read=GetEndpoint};
	__property System::Sysutils::TEncoding* Encoding = {read=FEncoding, write=FEncoding};
#ifndef _WIN64
	__property NativeUInt Handle = {read=FSocket, nodefault};
#else /* _WIN64 */
	__property NativeUInt Handle = {read=FSocket};
#endif /* _WIN64 */
	__property TSocketType SocketType = {read=FSockType, nodefault};
	__property TSocketStates State = {read=FState, nodefault};
	__property sockaddr_in Addr = {read=FAddr};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSocketStream : public System::Classes::TStream
{
	typedef System::Classes::TStream inherited;
	
private:
	TSocket* FSocket;
	bool FOwnsSocket;
	
public:
	__fastcall TSocketStream(TSocket* const ASocket, bool AOwnsSocket);
	__fastcall virtual ~TSocketStream();
	virtual int __fastcall Read(void *Buffer, int Count)/* overload */;
	virtual int __fastcall Write(const void *Buffer, int Count)/* overload */;
	/* Hoisted overloads: */
	
public:
#ifndef _WIN64
	inline int __fastcall  Read(System::DynamicArray<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Read(Buffer, Offset, Count); }
	inline int __fastcall  Read(System::DynamicArray<System::Byte> &Buffer, int Count){ return System::Classes::TStream::Read(Buffer, Count); }
	inline int __fastcall  Write(const System::DynamicArray<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Write(Buffer, Offset, Count); }
	inline int __fastcall  Write(const System::DynamicArray<System::Byte> Buffer, int Count){ return System::Classes::TStream::Write(Buffer, Count); }
#else /* _WIN64 */
	inline int __fastcall  Read(System::TArray__1<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Read(Buffer, Offset, Count); }
	inline int __fastcall  Read(System::TArray__1<System::Byte> &Buffer, int Count){ return System::Classes::TStream::Read(Buffer, Count); }
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Write(Buffer, Offset, Count); }
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Count){ return System::Classes::TStream::Write(Buffer, Count); }
#endif /* _WIN64 */
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#ifndef _WIN64
static const unsigned InvalidSocket = unsigned(0xffffffff);
#else /* _WIN64 */
static const unsigned __int64 InvalidSocket = 0xffffffffffffffffULL;
#endif /* _WIN64 */
static const unsigned InAddrAny = unsigned(0x0);
static const unsigned InAddrBroadcast = unsigned(0xffffffff);
static const int InAddrLoopback = int(0x7f000001);
}	/* namespace Socket */
}	/* namespace Net */
}	/* namespace System */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Net_SocketHPP
