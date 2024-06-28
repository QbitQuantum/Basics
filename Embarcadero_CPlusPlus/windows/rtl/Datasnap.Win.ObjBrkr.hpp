// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.Win.ObjBrkr.pas' rev: 34.00 (Windows)

#ifndef Datasnap_Win_ObjbrkrHPP
#define Datasnap_Win_ObjbrkrHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Datasnap.Win.MConnect.hpp>
#include <System.Classes.hpp>
#include <System.Variants.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Win
{
namespace Objbrkr
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EBrokerException;
class DELPHICLASS TServerItem;
class DELPHICLASS TServerCollection;
class DELPHICLASS TSimpleObjectBroker;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EBrokerException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBrokerException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBrokerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBrokerException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBrokerException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBrokerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBrokerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBrokerException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBrokerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBrokerException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBrokerException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBrokerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBrokerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBrokerException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TServerItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	bool FEnabled;
	System::UnicodeString FComputerName;
	bool FHasFailed;
	int FPort;
	
protected:
	virtual System::UnicodeString __fastcall GetDisplayName();
	
public:
	__fastcall virtual TServerItem(System::Classes::TCollection* AOwner);
	__property bool HasFailed = {read=FHasFailed, write=FHasFailed, nodefault};
	
__published:
	__property System::UnicodeString ComputerName = {read=FComputerName, write=FComputerName};
	__property int Port = {read=FPort, write=FPort, default=211};
	__property bool Enabled = {read=FEnabled, write=FEnabled, default=1};
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TServerItem() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TServerCollection : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TServerItem* operator[](int Index) { return this->Items[Index]; }
	
private:
	HIDESBASE TServerItem* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TServerItem* Value);
	
public:
	__fastcall TServerCollection(System::Classes::TComponent* AOwner);
	System::UnicodeString __fastcall GetBalancedName();
	System::UnicodeString __fastcall GetNextName();
	TServerItem* __fastcall FindServer(const System::UnicodeString ComputerName);
	__property TServerItem* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TServerCollection() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TSimpleObjectBroker : public Datasnap::Win::Mconnect::TCustomObjectBroker
{
	typedef Datasnap::Win::Mconnect::TCustomObjectBroker inherited;
	
private:
	TServerCollection* FServers;
	bool FLoadBalanced;
	void __fastcall SetServers(TServerCollection* Value);
	bool __fastcall IsServersStored();
	System::UnicodeString __fastcall GetNextComputer();
	System::OleVariant __fastcall GetServerData();
	void __fastcall SetServerData(const System::OleVariant &Value);
	
public:
	__fastcall virtual TSimpleObjectBroker(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TSimpleObjectBroker();
	void __fastcall SaveToStream(System::Classes::TStream* Stream);
	void __fastcall LoadFromStream(System::Classes::TStream* Stream);
	__property System::OleVariant ServerData = {read=GetServerData, write=SetServerData};
	virtual void __fastcall SetConnectStatus(System::UnicodeString ComputerName, bool Success);
	virtual System::UnicodeString __fastcall GetComputerForGUID(const GUID &GUID);
	virtual System::UnicodeString __fastcall GetComputerForProgID(const void *ProgID);
	virtual int __fastcall GetPortForComputer(const System::UnicodeString ComputerName);
	
__published:
	__property TServerCollection* Servers = {read=FServers, write=SetServers, stored=IsServersStored};
	__property bool LoadBalanced = {read=FLoadBalanced, write=FLoadBalanced, default=0};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Objbrkr */
}	/* namespace Win */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_WIN_OBJBRKR)
using namespace Datasnap::Win::Objbrkr;
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
#endif	// Datasnap_Win_ObjbrkrHPP
