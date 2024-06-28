// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Moni.RemoteBase.pas' rev: 34.00 (Windows)

#ifndef Firedac_Moni_RemotebaseHPP
#define Firedac_Moni_RemotebaseHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.SyncObjs.hpp>
#include <System.Win.ScktComp.hpp>
#include <FireDAC.Stan.Util.hpp>
#include <FireDAC.Stan.Intf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Moni
{
namespace Remotebase
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EFDMoniException;
class DELPHICLASS TFDMoniRemoteQueueItem;
class DELPHICLASS TFDMoniRemoteQueue;
class DELPHICLASS TFDMoniRemoteQueueWorker;
class DELPHICLASS TFDMoniRemoteStream;
class DELPHICLASS TFDMoniRemoteAdapterList;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EFDMoniException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EFDMoniException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EFDMoniException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EFDMoniException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EFDMoniException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EFDMoniException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EFDMoniException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EFDMoniException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EFDMoniException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EFDMoniException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EFDMoniException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EFDMoniException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EFDMoniException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EFDMoniException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TFDMoniRemoteQueueEventKind : unsigned int { ptNone, ptConnectClient, ptDisConnectClient, ptRegisterAdapter, ptUnRegisterAdapter, ptUpdateAdapter, ptNotify };

typedef System::Set<TFDMoniRemoteQueueEventKind, TFDMoniRemoteQueueEventKind::ptNone, TFDMoniRemoteQueueEventKind::ptNotify> TFDMoniRemoteQueueEventKinds;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFDMoniRemoteQueueItem : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	void __fastcall SetArg(System::PVarRec AArg);
	
public:
	unsigned FProcessID;
	unsigned FMonitorID;
	TFDMoniRemoteQueueEventKind FEvent;
	Firedac::Stan::Intf::TFDMoniEventKind FKind;
	Firedac::Stan::Intf::TFDMoniEventStep FStep;
	unsigned FHandle;
	System::UnicodeString FMessage;
	System::UnicodeString FPath;
	System::Classes::TMemoryStream* FArgs;
	void *FProc;
	unsigned FTime;
	__fastcall TFDMoniRemoteQueueItem();
	__fastcall virtual ~TFDMoniRemoteQueueItem();
	void __fastcall SetArgs(const System::TVarRec *AArgs, const int AArgs_High)/* overload */;
	void __fastcall SetArgs(const System::Variant &AArgs)/* overload */;
	System::Variant __fastcall GetArgs();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TFDMoniRemoteQueue : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Classes::TList* FList;
	TFDMoniRemoteQueueWorker* FThread;
	System::Classes::TNotifyEvent FOnPostItem;
	System::Syncobjs::TCriticalSection* FQueueCriticalSection;
	int __fastcall GetCount();
	
public:
	__fastcall TFDMoniRemoteQueue(TFDMoniRemoteQueueWorker* AThread);
	__fastcall virtual ~TFDMoniRemoteQueue();
	TFDMoniRemoteQueueItem* __fastcall GetItem();
	TFDMoniRemoteQueueEventKind __fastcall GetNextEvent();
	void __fastcall PostItem(TFDMoniRemoteQueueItem* AItem);
	void __fastcall Clear();
	__property int Count = {read=GetCount, nodefault};
	__property System::Classes::TNotifyEvent OnPostItem = {read=FOnPostItem, write=FOnPostItem};
};


class PASCALIMPLEMENTATION TFDMoniRemoteQueueWorker : public System::Classes::TThread
{
	typedef System::Classes::TThread inherited;
	
private:
	System::Syncobjs::TEvent* FItemAvailableEvent;
	
protected:
	virtual void __fastcall DoAction() = 0 ;
	virtual TFDMoniRemoteQueue* __fastcall GetQueue() = 0 ;
	virtual void __fastcall Execute();
	
public:
	__fastcall TFDMoniRemoteQueueWorker();
	__fastcall virtual ~TFDMoniRemoteQueueWorker();
	void __fastcall AbortProcessing();
	void __fastcall Signal();
};


enum DECLSPEC_DENUM TFDMoniRemoteStreamOpenMode : unsigned int { omRead, omWrite };

typedef unsigned TFDMoniRemoteStreamBlockID;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFDMoniRemoteStream : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Win::Scktcomp::TCustomWinSocket* FConnection;
	System::Classes::TMemoryStream* FBuffer;
	int FBlockLevel;
	TFDMoniRemoteStreamOpenMode FMode;
	Firedac::Stan::Util::TFDEncoder* FEncoder;
	void __fastcall WriteBytes(const void *ABuff, int ALen);
	void __fastcall WriteValueHeader(const System::UnicodeString AParamName, char AType);
	void __fastcall ReadBytes(void *ABuff, int ALen);
	void __fastcall ReadValueHeader(const System::UnicodeString AParamName, char AType);
	void __fastcall ReceiveBuffer();
	void __fastcall SendBuffer();
	
public:
	void __fastcall Open(System::Win::Scktcomp::TCustomWinSocket* AConnection, TFDMoniRemoteStreamOpenMode AMode);
	void __fastcall Close();
	bool __fastcall IsOpen();
	void __fastcall WriteBeginBlock(unsigned AID);
	void __fastcall WriteEndBlock();
	void __fastcall WriteString(const System::UnicodeString AParamName, const System::UnicodeString AValue);
	void __fastcall WriteBlob(const System::UnicodeString AParamName, System::Classes::TMemoryStream* AValue);
	void __fastcall WriteBoolean(const System::UnicodeString AParamName, bool AValue);
	void __fastcall WriteInteger(const System::UnicodeString AParamName, int AValue);
	void __fastcall WriteLongWord(const System::UnicodeString AParamName, unsigned AValue);
	void __fastcall WriteFloat(const System::UnicodeString AParamName, double AValue);
	void __fastcall WriteDate(const System::UnicodeString AParamName, System::TDateTime AValue);
	void __fastcall ReadBeginBlock(unsigned AID);
	void __fastcall ReadEndBlock();
	bool __fastcall IsEndBlock();
	System::UnicodeString __fastcall ReadString(const System::UnicodeString AParamName);
	void __fastcall ReadBlob(const System::UnicodeString AParamName, System::Classes::TMemoryStream* AValue);
	bool __fastcall ReadBoolean(const System::UnicodeString AParamName);
	int __fastcall ReadInteger(const System::UnicodeString AParamName);
	unsigned __fastcall ReadLongWord(const System::UnicodeString AParamName);
	double __fastcall ReadFloat(const System::UnicodeString AParamName);
	System::TDateTime __fastcall ReadDate(const System::UnicodeString AParamName);
public:
	/* TObject.Create */ inline __fastcall TFDMoniRemoteStream() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TFDMoniRemoteStream() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFDMoniRemoteAdapterList : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Firedac::Stan::Intf::TFDStringList* FList;
	int __fastcall GetCount();
	System::UnicodeString __fastcall GetPath(int AIndex);
	unsigned __fastcall GetHandle(int AIndex);
	
public:
	__fastcall TFDMoniRemoteAdapterList();
	__fastcall virtual ~TFDMoniRemoteAdapterList();
	void __fastcall Clear();
	int __fastcall IndexOf(unsigned AHandle);
	System::UnicodeString __fastcall FindByHandle(unsigned AHandle);
	unsigned __fastcall FindByPath(const System::UnicodeString APath);
	void __fastcall AddAdapter(const System::UnicodeString APath, unsigned AHandle);
	void __fastcall RemoveAdapter(unsigned AHandle);
	__property int Count = {read=GetCount, nodefault};
	__property System::UnicodeString Paths[int AIndex] = {read=GetPath};
	__property unsigned Handles[int AIndex] = {read=GetHandle};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE int C_FD_Mon_PacketVersion;
extern DELPHI_PACKAGE int C_FD_Mon_PacketBodyBlockID;
extern DELPHI_PACKAGE System::UnicodeString S_FD_MsgVersion;
extern DELPHI_PACKAGE System::UnicodeString S_FD_MsgEvent;
extern DELPHI_PACKAGE System::UnicodeString S_FD_MsgProcessId;
extern DELPHI_PACKAGE System::UnicodeString S_FD_MsgMonitorId;
extern DELPHI_PACKAGE System::UnicodeString S_FD_MsgText;
extern DELPHI_PACKAGE System::UnicodeString S_FD_MsgArgs;
extern DELPHI_PACKAGE System::UnicodeString S_FD_MsgAdapterHandle;
extern DELPHI_PACKAGE System::UnicodeString S_FD_MsgNotifyKind;
extern DELPHI_PACKAGE System::UnicodeString S_FD_MsgNotifyStep;
extern DELPHI_PACKAGE System::UnicodeString S_FD_MsgTime;
extern DELPHI_PACKAGE bool __fastcall FDMoniRemoteIsLocalHost(const System::UnicodeString AIP);
}	/* namespace Remotebase */
}	/* namespace Moni */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_MONI_REMOTEBASE)
using namespace Firedac::Moni::Remotebase;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_MONI)
using namespace Firedac::Moni;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Moni_RemotebaseHPP
