// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Macapi.OCBlocks.pas' rev: 34.00 (iOS)

#ifndef Macapi_OcblocksHPP
#define Macapi_OcblocksHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.TypInfo.hpp>

//-- user supplied -----------------------------------------------------------

namespace Macapi
{
namespace Ocblocks
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TObjCBlocks;
class DELPHICLASS TGetBlockType;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TObjCBlocks : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static System::TArray__1<System::TMethod> BlockEvents;
	static System::TArray__1<void *> EventTypes;
	static System::TArray__1<void *> Blocks;
	static int Capacity;
	static int Current;
	__classmethod int __fastcall GetBlockIndex();
	__classmethod void __fastcall Grow();
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
public:
	__classmethod void * __fastcall SetEvent(const System::TMethod &Value, const void * TypeInfo);
	__classmethod System::TMethod __fastcall GetEvent(const int Index);
	__classmethod void * __fastcall GetEventType(const int Index);
	__classmethod void __fastcall FreeBlocks(System::TObject* const Owner);
public:
	/* TObject.Create */ inline __fastcall TObjCBlocks() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TObjCBlocks() { }
	
};


class PASCALIMPLEMENTATION TGetBlockType : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::Typinfo::TTypeInfo *FTypeInfo;
	
public:
	void __fastcall XForm(void * Src, void * Dest);
	__fastcall TGetBlockType(System::Typinfo::PTypeInfo P);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TGetBlockType() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ocblocks */
}	/* namespace Macapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI_OCBLOCKS)
using namespace Macapi::Ocblocks;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI)
using namespace Macapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Macapi_OcblocksHPP
