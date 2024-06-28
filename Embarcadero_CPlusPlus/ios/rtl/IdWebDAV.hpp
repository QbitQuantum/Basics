// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdWebDAV.pas' rev: 34.00 (iOS)

#ifndef IdwebdavHPP
#define IdwebdavHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idwebdav
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdWebDAV;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdWebDAV : public Idhttp::TIdHTTP
{
	typedef Idhttp::TIdHTTP inherited;
	
public:
	void __fastcall DAVCheckIn(const System::UnicodeString AURL, const System::UnicodeString AComment);
	void __fastcall DAVCheckOut(const System::UnicodeString AURL, System::Classes::TStream* const AXMLQuery, const System::UnicodeString AComment);
	void __fastcall DAVCopy(const System::UnicodeString AURL, const System::UnicodeString DURL, System::Classes::TStream* const AResponseContent, const bool AOverWrite = true, const System::UnicodeString ADepth = u"infinity");
	void __fastcall DAVDelete(const System::UnicodeString AURL, const System::UnicodeString ALockToken);
	void __fastcall DAVLabel(const System::UnicodeString AURL, System::Classes::TStream* const AXMLQuery);
	void __fastcall DAVLock(const System::UnicodeString AURL, System::Classes::TStream* const AXMLQuery, System::Classes::TStream* const AResponseContent, const System::UnicodeString ALockToken, const System::UnicodeString ATags, const System::UnicodeString ATimeOut = u"Infinite", const bool AMustExist = false, const System::UnicodeString ADepth = u"0");
	void __fastcall DAVMove(const System::UnicodeString AURL, const System::UnicodeString DURL, System::Classes::TStream* const AResponseContent, const bool AOverWrite = true, const System::UnicodeString ADepth = u"infinity");
	void __fastcall DAVOrderPatch(const System::UnicodeString AURL, System::Classes::TStream* const AXMLQuery);
	void __fastcall DAVPropFind(const System::UnicodeString AURL, System::Classes::TStream* const AXMLQuery, System::Classes::TStream* const AResponseContent, const System::UnicodeString ADepth = u"0", const int ARangeFrom = 0xffffffff, const int ARangeTo = 0xffffffff);
	void __fastcall DAVPropPatch(const System::UnicodeString AURL, System::Classes::TStream* const AXMLQuery, System::Classes::TStream* const AResponseContent, const System::UnicodeString ADepth = u"0");
	void __fastcall DAVPut(const System::UnicodeString AURL, System::Classes::TStream* const ASource, const System::UnicodeString ALockToken);
	void __fastcall DAVReport(const System::UnicodeString AURL, System::Classes::TStream* const AXMLQuery, System::Classes::TStream* const AResponseContent);
	void __fastcall DAVSearch(const System::UnicodeString AURL, const int ARangeFrom, const int ARangeTo, System::Classes::TStream* const AXMLQuery, System::Classes::TStream* const AResponseContent, const System::UnicodeString ADepth = u"0");
	void __fastcall DAVUnCheckOut(const System::UnicodeString AURL);
	void __fastcall DAVUnLock(const System::UnicodeString AURL, const System::UnicodeString ALockToken);
	void __fastcall DAVVersionControl(const System::UnicodeString AURL);
	void __fastcall DAVMakeCollection(const System::UnicodeString AURL);
public:
	/* TIdCustomHTTP.Destroy */ inline __fastcall virtual ~TIdWebDAV() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdWebDAV(System::Classes::TComponent* AOwner)/* overload */ : Idhttp::TIdHTTP(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdWebDAV()/* overload */ : Idhttp::TIdHTTP() { }
	
};


//-- var, const, procedure ---------------------------------------------------
#define Id_HTTPMethodPropFind u"PROPFIND"
#define Id_HTTPMethodPropPatch u"PROPPATCH"
#define Id_HTTPMethodOrderPatch u"ORDERPATCH"
#define Id_HTTPMethodSearch u"SEARCH"
#define Id_HTTPMethodMKCol u"MKCOL"
#define Id_HTTPMethodMove u"MOVE"
#define Id_HTTPMethodCopy u"COPY"
#define Id_HTTPMethodCheckIn u"CHECKIN"
#define Id_HTTPMethodCheckOut u"CHECKOUT"
#define Id_HTTPMethodUnCheckOut u"UNCHECKOUT"
#define Id_HTTPMethodLock u"LOCK"
#define Id_HTTPMethodUnLock u"UNLOCK"
#define Id_HTTPMethodReport u"REPORT"
#define Id_HTTPMethodVersion u"VERSION-CONTROL"
#define Id_HTTPMethodLabel u"LABEL"
#define Id_HTTPMethodMakeCol u"MKCOL"
#define cTimeoutInfinite u"Infinite"
#define cDepthInfinity u"infinity"
}	/* namespace Idwebdav */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDWEBDAV)
using namespace Idwebdav;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdwebdavHPP
