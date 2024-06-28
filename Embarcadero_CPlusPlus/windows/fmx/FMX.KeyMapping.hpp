// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.KeyMapping.pas' rev: 34.00 (Windows)

#ifndef Fmx_KeymappingHPP
#define Fmx_KeymappingHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <System.UITypes.hpp>
#include <FMX.Types.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Keymapping
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IFMXKeyMappingService;
typedef System::DelphiInterface<IFMXKeyMappingService> _di_IFMXKeyMappingService;
class DELPHICLASS TKeyMapping;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{8908B4A3-0214-42EE-B912-0F94C2F30A1C}") IFMXKeyMappingService  : public System::IInterface 
{
	virtual bool __fastcall RegisterKeyMapping(const System::Word PlatformKey, const System::Word VirtualKey, const Fmx::Types::TKeyKind KeyKind) = 0 ;
	virtual bool __fastcall UnregisterKeyMapping(const System::Word PlatformKey) = 0 ;
	virtual System::Word __fastcall PlatformKeyToVirtualKey(const System::Word PlatformKey, Fmx::Types::TKeyKind &KeyKind) = 0 ;
	virtual System::Word __fastcall VirtualKeyToPlatformKey(const System::Word VirtualKey) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TKeyMapping : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	struct DECLSPEC_DRECORD TVirtualKeyInfo
	{
	public:
		System::Word VirtualKey;
		Fmx::Types::TKeyKind KeyKind;
	};
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
	
private:
	System::Generics::Collections::TDictionary__2<System::Word,TVirtualKeyInfo>* FPlatformToVirtualMap;
	System::Generics::Collections::TDictionary__2<System::Word,System::Word>* FVirtualToPlatformMap;
	void __fastcall AddArray(const System::Word *A, const int A_High, Fmx::Types::TKeyKind Kind);
	void __fastcall RegisterVirtualKeys();
	
public:
	__fastcall TKeyMapping();
	__fastcall virtual ~TKeyMapping();
	bool __fastcall RegisterKeyMapping(const System::Word PlatformKey, const System::Word VirtualKey, const Fmx::Types::TKeyKind KeyKind);
	bool __fastcall UnregisterKeyMapping(const System::Word PlatformKey);
	System::Word __fastcall PlatformKeyToVirtualKey(const System::Word PlatformKey, Fmx::Types::TKeyKind &KeyKind);
	System::Word __fastcall VirtualKeyToPlatformKey(const System::Word VirtualKey);
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool __fastcall RegisterKeyMapping _DEPRECATED_ATTRIBUTE1("Use IFMXKeyMappingService.RegisterKeyMapping") (const System::Word PlatformKey, const System::Word VirtualKey, const Fmx::Types::TKeyKind KeyKind);
extern DELPHI_PACKAGE bool __fastcall UnregisterKeyMapping _DEPRECATED_ATTRIBUTE1("Use IFMXKeyMappingService.UnregisterKeyMapping") (const System::Word PlatformKey);
extern DELPHI_PACKAGE System::Word __fastcall PlatformKeyToVirtualKey _DEPRECATED_ATTRIBUTE1("Use IFMXKeyMappingService.PlatformKeyToVirtualKey") (const System::Word PlatformKey, Fmx::Types::TKeyKind &KeyKind);
}	/* namespace Keymapping */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_KEYMAPPING)
using namespace Fmx::Keymapping;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_KeymappingHPP
