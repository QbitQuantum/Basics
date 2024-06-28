// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSSL.pas' rev: 34.00 (Windows)

#ifndef IdsslHPP
#define IdsslHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdGlobal.hpp>
#include <IdIOHandler.hpp>
#include <IdIOHandlerSocket.hpp>
#include <IdIOHandlerStack.hpp>
#include <IdScheduler.hpp>
#include <IdServerIOHandler.hpp>
#include <IdYarn.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idssl
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdSSLIOHandlerSocketBase;
class DELPHICLASS TIdServerIOHandlerSSLBase;
class DELPHICLASS TIdSSLRegEntry;
class DELPHICLASS TIdSSLRegistry;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdSSLIOHandlerSocketBase : public Idiohandlerstack::TIdIOHandlerStack
{
	typedef Idiohandlerstack::TIdIOHandlerStack inherited;
	
protected:
	bool fPassThrough;
	bool fIsPeer;
	System::UnicodeString FURIToCheck;
	virtual void __fastcall InitComponent();
	virtual int __fastcall RecvEnc(Idglobal::TIdBytes &ABuffer) = 0 ;
	virtual int __fastcall SendEnc(const Idglobal::TIdBytes ABuffer, const int AOffset, const int ALength) = 0 ;
	virtual int __fastcall ReadDataFromSource(Idglobal::TIdBytes &VBuffer);
	virtual int __fastcall WriteDataToTarget(const Idglobal::TIdBytes ABuffer, const int AOffset, const int ALength);
	virtual void __fastcall SetPassThrough(const bool AValue);
	virtual void __fastcall SetURIToCheck(const System::UnicodeString AValue);
	
public:
	virtual TIdSSLIOHandlerSocketBase* __fastcall Clone() = 0 ;
	virtual void __fastcall StartSSL() = 0 ;
	__property bool PassThrough = {read=fPassThrough, write=SetPassThrough, nodefault};
	__property bool IsPeer = {read=fIsPeer, write=fIsPeer, nodefault};
	__property System::UnicodeString URIToCheck = {read=FURIToCheck, write=SetURIToCheck};
public:
	/* TIdIOHandlerSocket.Destroy */ inline __fastcall virtual ~TIdSSLIOHandlerSocketBase() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdSSLIOHandlerSocketBase(System::Classes::TComponent* AOwner)/* overload */ : Idiohandlerstack::TIdIOHandlerStack(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdSSLIOHandlerSocketBase()/* overload */ : Idiohandlerstack::TIdIOHandlerStack() { }
	
};


class PASCALIMPLEMENTATION TIdServerIOHandlerSSLBase : public Idserveriohandler::TIdServerIOHandler
{
	typedef Idserveriohandler::TIdServerIOHandler inherited;
	
public:
	virtual Idiohandler::TIdIOHandler* __fastcall MakeClientIOHandler(Idyarn::TIdYarn* ATheThread)/* overload */;
	HIDESBASE virtual TIdSSLIOHandlerSocketBase* __fastcall MakeClientIOHandler() = 0 /* overload */;
	virtual TIdSSLIOHandlerSocketBase* __fastcall MakeFTPSvrPort() = 0 ;
	virtual TIdSSLIOHandlerSocketBase* __fastcall MakeFTPSvrPasv() = 0 ;
public:
	/* TIdComponent.Destroy */ inline __fastcall virtual ~TIdServerIOHandlerSSLBase() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdServerIOHandlerSSLBase(System::Classes::TComponent* AOwner)/* overload */ : Idserveriohandler::TIdServerIOHandler(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdServerIOHandlerSSLBase()/* overload */ : Idserveriohandler::TIdServerIOHandler() { }
	
};


#ifndef _WIN64
typedef System::TMetaClass* TIdClientSSLClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TIdClientSSLClass);
#endif /* _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* TIdServerSSLClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TIdServerSSLClass);
#endif /* _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdSSLRegEntry : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
protected:
	System::UnicodeString FProductName;
	System::UnicodeString FVendor;
	System::UnicodeString FCopyright;
	System::UnicodeString FDescription;
	System::UnicodeString FURL;
	TIdClientSSLClass FClientClass;
	TIdServerSSLClass FServerClass;
	
public:
	__property System::UnicodeString ProductName = {read=FProductName, write=FProductName};
	__property System::UnicodeString Vendor = {read=FVendor, write=FVendor};
	__property System::UnicodeString Copyright = {read=FCopyright, write=FCopyright};
	__property System::UnicodeString Description = {read=FDescription, write=FDescription};
	__property System::UnicodeString URL = {read=FURL, write=FURL};
	__property TIdClientSSLClass ClientClass = {read=FClientClass, write=FClientClass};
	__property TIdServerSSLClass ServerClass = {read=FServerClass, write=FServerClass};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TIdSSLRegEntry(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdSSLRegEntry() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdSSLRegistry : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TIdSSLRegEntry* operator[](int Index) { return this->Items[Index]; }
	
protected:
	HIDESBASE TIdSSLRegEntry* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TIdSSLRegEntry* const Value);
	
public:
	__fastcall TIdSSLRegistry();
	HIDESBASE TIdSSLRegEntry* __fastcall Add();
	__property TIdSSLRegEntry* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TIdSSLRegistry() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TIdSSLRegistry* GSSLRegistry;
extern DELPHI_PACKAGE void __fastcall RegisterSSL(const System::UnicodeString AProduct, const System::UnicodeString AVendor, const System::UnicodeString ACopyright, const System::UnicodeString ADescription, const System::UnicodeString AURL, const TIdClientSSLClass AClientClass, const TIdServerSSLClass AServerClass);
}	/* namespace Idssl */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSSL)
using namespace Idssl;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdsslHPP
