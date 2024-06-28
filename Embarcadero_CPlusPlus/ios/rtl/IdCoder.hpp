// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdCoder.pas' rev: 34.00 (iOS)

#ifndef IdcoderHPP
#define IdcoderHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdBaseComponent.hpp>
#include <IdGlobal.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idcoder
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdEncoder;
class DELPHICLASS TIdDecoder;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdEncoder : public Idbasecomponent::TIdBaseComponent
{
	typedef Idbasecomponent::TIdBaseComponent inherited;
	
public:
	System::UnicodeString __fastcall Encode(const System::UnicodeString AIn, Idglobal::_di_IIdTextEncoding AByteEncoding = Idglobal::_di_IIdTextEncoding())/* overload */;
	void __fastcall Encode(const System::UnicodeString AIn, System::Classes::TStrings* ADestStrings, Idglobal::_di_IIdTextEncoding AByteEncoding = Idglobal::_di_IIdTextEncoding())/* overload */;
	void __fastcall Encode(const System::UnicodeString AIn, System::Classes::TStream* ADestStream, Idglobal::_di_IIdTextEncoding AByteEncoding = Idglobal::_di_IIdTextEncoding())/* overload */;
	System::UnicodeString __fastcall Encode(System::Classes::TStream* ASrcStream, const int ABytes = 0xffffffff)/* overload */;
	void __fastcall Encode(System::Classes::TStream* ASrcStream, System::Classes::TStrings* ADestStrings, const int ABytes = 0xffffffff)/* overload */;
	virtual void __fastcall Encode(System::Classes::TStream* ASrcStream, System::Classes::TStream* ADestStream, const int ABytes = 0xffffffff) = 0 /* overload */;
	__classmethod System::UnicodeString __fastcall EncodeString(const System::UnicodeString AIn, Idglobal::_di_IIdTextEncoding AByteEncoding = Idglobal::_di_IIdTextEncoding())/* overload */;
	__classmethod void __fastcall EncodeString(const System::UnicodeString AIn, System::Classes::TStrings* ADestStrings, Idglobal::_di_IIdTextEncoding AByteEncoding = Idglobal::_di_IIdTextEncoding())/* overload */;
	__classmethod void __fastcall EncodeString(const System::UnicodeString AIn, System::Classes::TStream* ADestStream, Idglobal::_di_IIdTextEncoding AByteEncoding = Idglobal::_di_IIdTextEncoding())/* overload */;
	__classmethod System::UnicodeString __fastcall EncodeBytes(const Idglobal::TIdBytes ABytes)/* overload */;
	__classmethod void __fastcall EncodeBytes(const Idglobal::TIdBytes ABytes, System::Classes::TStrings* ADestStrings)/* overload */;
	__classmethod void __fastcall EncodeBytes(const Idglobal::TIdBytes ABytes, System::Classes::TStream* ADestStream)/* overload */;
	__classmethod System::UnicodeString __fastcall EncodeStream(System::Classes::TStream* ASrcStream, const int ABytes = 0xffffffff)/* overload */;
	__classmethod void __fastcall EncodeStream(System::Classes::TStream* ASrcStream, System::Classes::TStrings* ADestStrings, const int ABytes = 0xffffffff)/* overload */;
	__classmethod void __fastcall EncodeStream(System::Classes::TStream* ASrcStream, System::Classes::TStream* ADestStream, const int ABytes = 0xffffffff)/* overload */;
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdEncoder(System::Classes::TComponent* AOwner)/* overload */ : Idbasecomponent::TIdBaseComponent(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdEncoder()/* overload */ : Idbasecomponent::TIdBaseComponent() { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TIdEncoder() { }
	
};


_DECLARE_METACLASS(System::TMetaClass, TIdEncoderClass);

class PASCALIMPLEMENTATION TIdDecoder : public Idbasecomponent::TIdBaseComponent
{
	typedef Idbasecomponent::TIdBaseComponent inherited;
	
protected:
	System::Classes::TStream* FStream;
	
public:
	virtual void __fastcall DecodeBegin(System::Classes::TStream* ADestStream);
	virtual void __fastcall DecodeEnd();
	void __fastcall Decode(const System::UnicodeString AIn)/* overload */;
	virtual void __fastcall Decode(System::Classes::TStream* ASrcStream, const int ABytes = 0xffffffff) = 0 /* overload */;
	__classmethod System::UnicodeString __fastcall DecodeString(const System::UnicodeString AIn, Idglobal::_di_IIdTextEncoding AByteEncoding = Idglobal::_di_IIdTextEncoding());
	__classmethod Idglobal::TIdBytes __fastcall DecodeBytes(const System::UnicodeString AIn);
	__classmethod void __fastcall DecodeStream(const System::UnicodeString AIn, System::Classes::TStream* ADestStream);
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdDecoder(System::Classes::TComponent* AOwner)/* overload */ : Idbasecomponent::TIdBaseComponent(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdDecoder()/* overload */ : Idbasecomponent::TIdBaseComponent() { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TIdDecoder() { }
	
};


_DECLARE_METACLASS(System::TMetaClass, TIdDecoderClass);

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idcoder */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDCODER)
using namespace Idcoder;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdcoderHPP
