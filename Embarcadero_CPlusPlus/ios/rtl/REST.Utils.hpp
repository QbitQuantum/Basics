// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Utils.pas' rev: 34.00 (iOS)

#ifndef Rest_UtilsHPP
#define Rest_UtilsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Character.hpp>

//-- user supplied -----------------------------------------------------------
namespace Rest
{
namespace Utils
{
  _INIT_UNIT(Rest_Utils);
}	/* namespace Utils */
}	/* namespace Rest */

namespace Rest
{
namespace Utils
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TRESTFindDefaultComponent;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TRESTFindDefaultComponent : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	template<typename T> __classmethod T __fastcall FindDefaultT(System::Classes::TComponent* AComp);
	template<typename T> __classmethod T __fastcall FindDefaultIntfT(System::Classes::TComponent* AComp);
	template<typename T> __classmethod void __fastcall FindAllT(System::Classes::TComponent* AComp, System::DelphiInterface<System::Sysutils::TProc__1<T> > ACallback)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TRESTFindDefaultComponent() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TRESTFindDefaultComponent() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString __fastcall URIEncode(const System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall RESTComponentIsDesigning(System::Classes::TComponent* AComp);
extern DELPHI_PACKAGE void __fastcall ExtractURLSegmentNames(const System::UnicodeString AUrl, System::Classes::TStrings* AParams);
extern DELPHI_PACKAGE void __fastcall ExtractGetParams(const System::UnicodeString AUrl, System::Classes::TStrings* &AParams);
}	/* namespace Utils */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_UTILS)
using namespace Rest::Utils;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST)
using namespace Rest;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Rest_UtilsHPP
