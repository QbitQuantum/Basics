// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXClassRegistry.pas' rev: 34.00 (iOS)

#ifndef Data_DbxclassregistryHPP
#define Data_DbxclassregistryHPP

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
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxclassregistry
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TClassRegistryObject;
class DELPHICLASS EClassRegistryError;
class DELPHICLASS TClassRegistryPackageItem;
class DELPHICLASS TClassRegistry;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TClassRegistryObject : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall virtual TClassRegistryObject();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TClassRegistryObject() { }
	
};


class PASCALIMPLEMENTATION EClassRegistryError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EClassRegistryError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EClassRegistryError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EClassRegistryError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EClassRegistryError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EClassRegistryError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EClassRegistryError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EClassRegistryError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EClassRegistryError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EClassRegistryError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EClassRegistryError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EClassRegistryError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EClassRegistryError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EClassRegistryError() { }
	
};


class PASCALIMPLEMENTATION TClassRegistryPackageItem : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FPackageName;
	NativeUInt FPackageHandle;
	
protected:
	__fastcall TClassRegistryPackageItem(System::UnicodeString PackageName);
	
public:
	__fastcall virtual ~TClassRegistryPackageItem();
};


class PASCALIMPLEMENTATION TClassRegistry : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Classes::TThreadList* FLock;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::TClass>* FClasses;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,TClassRegistryPackageItem*>* FPackages;
	bool FCanDestroy;
	static TClassRegistry* ClassRegistry;
	
public:
	__fastcall TClassRegistry();
	__fastcall virtual ~TClassRegistry();
	__classmethod TClassRegistry* __fastcall GetClassRegistry();
	void __fastcall RegisterPackageClass(System::UnicodeString ClassName, System::UnicodeString PackageName);
	void __fastcall RegisterClass(System::UnicodeString ClassName, System::TClass ObjectClass);
	void __fastcall RegisterRegistryClass(System::UnicodeString ClassName, System::TClass RegistryClass);
	void __fastcall UnregisterClass(System::UnicodeString ClassName);
	bool __fastcall HasClass(System::UnicodeString ClassName);
	System::TObject* __fastcall CreateInstance(System::UnicodeString ClassName);
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxclassregistry */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXCLASSREGISTRY)
using namespace Data::Dbxclassregistry;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxclassregistryHPP
