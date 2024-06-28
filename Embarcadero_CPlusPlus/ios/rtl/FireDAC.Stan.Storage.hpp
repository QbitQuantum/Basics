// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Stan.Storage.pas' rev: 34.00 (iOS)

#ifndef Firedac_Stan_StorageHPP
#define Firedac_Stan_StorageHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.TypInfo.hpp>
#include <System.Generics.Collections.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Util.hpp>
#include <FireDAC.Stan.Factory.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Stan
{
namespace Storage
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDStorage;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDStorage : public Firedac::Stan::Factory::TFDObject
{
	typedef Firedac::Stan::Factory::TFDObject inherited;
	
private:
	System::Classes::TList* FActions;
	int FLevel;
	bool FOwnStream;
	System::Classes::TMemoryStream* FBuff;
	Firedac::Stan::Option::TFDBottomResourceOptions* FResOpts;
	System::UnicodeString FWorkFileName;
	System::UnicodeString FOriginalFileExt;
	System::Generics::Collections::TDictionary__2<System::TObject*,System::TObject*>* FFilterObjs;
	System::Typinfo::TTypeInfo *FLastEnumTypeInfo;
	int FLastEnumValue;
	System::UnicodeString FLastEnumName;
	void __fastcall ClearDeferredActions();
	void __fastcall PerformDeferredActions();
	
protected:
	int FStreamVersion;
	Firedac::Stan::Intf::TFDStorageMode FMode;
	System::Classes::TStream* FStream;
	Firedac::Stan::Util::TFDEncoder* FEncoder;
	bool FFormat;
	System::Classes::TMemoryStream* __fastcall CheckBuffer(unsigned ASize);
	void __fastcall Hex2BinStream(const System::UnicodeString AHex, System::Classes::TMemoryStream* AStream);
	System::UnicodeString __fastcall GetCachedEnumName(System::Typinfo::PTypeInfo ATypeInfo, const int AValue);
	Firedac::Stan::Intf::TFDStorageMode __fastcall GetMode();
	int __fastcall GetStreamVersion();
	bool __fastcall GetOwnStream();
	void __fastcall SetOwnStream(bool AValue);
	virtual void __fastcall Open(System::TObject* AResOpts, System::TObject* AEncoder, const System::UnicodeString AFileName, System::Classes::TStream* AStream, Firedac::Stan::Intf::TFDStorageMode AMode);
	virtual void __fastcall Close();
	virtual bool __fastcall IsOpen();
	void __fastcall LockDeferring();
	void __fastcall UnLockDeferring();
	void __fastcall DeferAction(const System::UnicodeString APropName, const System::UnicodeString AValue, Firedac::Stan::Intf::TFDStorageDeferredAction AAction);
	bool __fastcall IsStored(Firedac::Stan::Intf::TFDStoreItem AItem);
	virtual System::UnicodeString __fastcall ReadObjectBegin(const System::UnicodeString AObjectName, Firedac::Stan::Intf::TFDStorageObjectStyle AStyle) = 0 ;
	virtual void __fastcall ReadObjectEnd(const System::UnicodeString AObjectName, Firedac::Stan::Intf::TFDStorageObjectStyle AStyle) = 0 ;
	System::TObject* __fastcall LoadObject();
	void __fastcall SaveObject(System::TObject* AObject);
	void __fastcall AddFilterObj(System::TObject* AKey, System::TObject* AFilter);
	void __fastcall RemoveFilterObj(System::TObject* AKey);
	System::TObject* __fastcall GetFilterObj(System::TObject* AKey);
	__int64 __fastcall BeginGrowthEstimation();
	void __fastcall EndGrowthEstimation(__int64 ABase, unsigned ATimes);
	
public:
	__fastcall virtual TFDStorage();
	__fastcall virtual ~TFDStorage();
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Storage */
}	/* namespace Stan */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_STAN_STORAGE)
using namespace Firedac::Stan::Storage;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_STAN)
using namespace Firedac::Stan;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Stan_StorageHPP
