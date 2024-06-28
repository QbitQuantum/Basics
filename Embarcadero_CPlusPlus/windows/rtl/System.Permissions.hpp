// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Permissions.pas' rev: 34.00 (Windows)

#ifndef System_PermissionsHPP
#define System_PermissionsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Permissions
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EPermissionException;
__interface DELPHIINTERFACE TRequestPermissionsResultProc;
typedef System::DelphiInterface<TRequestPermissionsResultProc> _di_TRequestPermissionsResultProc;
__interface DELPHIINTERFACE TDisplayRationaleProc;
typedef System::DelphiInterface<TDisplayRationaleProc> _di_TDisplayRationaleProc;
class DELPHICLASS TPermissionsService;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EPermissionException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EPermissionException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EPermissionException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EPermissionException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EPermissionException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EPermissionException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EPermissionException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EPermissionException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EPermissionException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EPermissionException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EPermissionException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EPermissionException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EPermissionException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EPermissionException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum class DECLSPEC_DENUM TPermissionStatus : unsigned char { Granted, Denied, PermanentlyDenied };

#ifndef _WIN64
typedef System::DynamicArray<System::UnicodeString> _dt_System_Permissions_1;
typedef System::DynamicArray<TPermissionStatus> _dt_System_Permissions_2;
typedef void __fastcall (__closure *TRequestPermissionsResultEvent)(System::TObject* Sender, const _dt_System_Permissions_1 APermissions, const _dt_System_Permissions_2 AGrantResults);
#else /* _WIN64 */
typedef void __fastcall (__closure *TRequestPermissionsResultEvent)(System::TObject* Sender, const System::TArray__1<System::UnicodeString> APermissions, const System::TArray__1<TPermissionStatus> AGrantResults);
#endif /* _WIN64 */

__interface TRequestPermissionsResultProc  : public System::IInterface 
{
#ifndef _WIN64
	virtual void __fastcall Invoke(const System::DynamicArray<System::UnicodeString> APermissions, const System::DynamicArray<TPermissionStatus> AGrantResults) = 0 ;
#else /* _WIN64 */
	virtual void __fastcall Invoke(const System::TArray__1<System::UnicodeString> APermissions, const System::TArray__1<TPermissionStatus> AGrantResults) = 0 ;
#endif /* _WIN64 */
};

#ifndef _WIN64
typedef System::DynamicArray<System::UnicodeString> _dt_System_Permissions_3;
typedef void __fastcall (__closure *TDisplayRationaleEvent)(System::TObject* Sender, const _dt_System_Permissions_3 APermissions, const System::Sysutils::_di_TProc APostRationaleProc);
#else /* _WIN64 */
typedef void __fastcall (__closure *TDisplayRationaleEvent)(System::TObject* Sender, const System::TArray__1<System::UnicodeString> APermissions, const System::Sysutils::_di_TProc APostRationaleProc);
#endif /* _WIN64 */

__interface TDisplayRationaleProc  : public System::IInterface 
{
#ifndef _WIN64
	virtual void __fastcall Invoke(const System::DynamicArray<System::UnicodeString> APermissions, const System::Sysutils::_di_TProc APostRationaleProc) = 0 ;
#else /* _WIN64 */
	virtual void __fastcall Invoke(const System::TArray__1<System::UnicodeString> APermissions, const System::Sysutils::_di_TProc APostRationaleProc) = 0 ;
#endif /* _WIN64 */
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TPermissionsService : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static TPermissionsService* __fastcall GetDefaultService();
	
protected:
	static TPermissionsService* FDefaultService;
	__fastcall virtual TPermissionsService();
	
private:
	// __classmethod void __fastcall UnInitialize@();
	
public:
	virtual bool __fastcall IsPermissionGranted(const System::UnicodeString APermission);
#ifndef _WIN64
	virtual bool __fastcall IsEveryPermissionGranted(const System::DynamicArray<System::UnicodeString> APermissions);
	virtual void __fastcall RequestPermissions(const System::DynamicArray<System::UnicodeString> APermissions, const TRequestPermissionsResultEvent AOnRequestPermissionsResult, TDisplayRationaleEvent AOnDisplayRationale = 0x0)/* overload */;
	virtual void __fastcall RequestPermissions(const System::DynamicArray<System::UnicodeString> APermissions, const _di_TRequestPermissionsResultProc AOnRequestPermissionsResult, _di_TDisplayRationaleProc AOnDisplayRationale = _di_TDisplayRationaleProc())/* overload */;
#else /* _WIN64 */
	virtual bool __fastcall IsEveryPermissionGranted(const System::TArray__1<System::UnicodeString> APermissions);
	virtual void __fastcall RequestPermissions(const System::TArray__1<System::UnicodeString> APermissions, const TRequestPermissionsResultEvent AOnRequestPermissionsResult, TDisplayRationaleEvent AOnDisplayRationale = 0x0)/* overload */;
	virtual void __fastcall RequestPermissions(const System::TArray__1<System::UnicodeString> APermissions, const _di_TRequestPermissionsResultProc AOnRequestPermissionsResult, _di_TDisplayRationaleProc AOnDisplayRationale = _di_TDisplayRationaleProc())/* overload */;
#endif /* _WIN64 */
	/* static */ __property TPermissionsService* DefaultService = {read=GetDefaultService};
	
private:
	// __classmethod void __fastcall Create@();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TPermissionsService() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* TPermissionsServiceClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TPermissionsServiceClass);
#endif /* _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TPermissionsServiceClass PermissionsServiceClass;
extern DELPHI_PACKAGE TPermissionsService* __fastcall PermissionsService(void);
}	/* namespace Permissions */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_PERMISSIONS)
using namespace System::Permissions;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_PermissionsHPP
