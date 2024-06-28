// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Macapi.OCMarshal.pas' rev: 34.00 (iOS)

#ifndef Macapi_OcmarshalHPP
#define Macapi_OcmarshalHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------

namespace Macapi
{
namespace Ocmarshal
{
//-- forward type declarations -----------------------------------------------
struct TMarshalOp;
class DELPHICLASS TMarshaler;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (*TXFormProc)(void * Src, void * Dest);

typedef void __fastcall (__closure *TXFormWithContextProc)(void * Src, void * Dest);

enum DECLSPEC_DENUM TMarshalOpKind : unsigned char { moCopy, moLocalRef, moStore, moXForm, moXFormWithContext };

struct DECLSPEC_DRECORD TMarshalOp
{
private:
	TXFormWithContextProc __fastcall GetXFormContextProc();
	
public:
	TMarshalOpKind Kind;
	int Src;
	int Dest;
	System::_di_IInterface Context;
	__property TXFormWithContextProc XFormContextProc = {read=GetXFormContextProc};
	
public:
	union
	{
		struct 
		{
			void *_XFormContextProc;
		};
		struct 
		{
			TXFormProc XFormProc;
		};
		struct 
		{
			NativeInt Value;
		};
		struct 
		{
			NativeInt Offset;
		};
		struct 
		{
			int Size;
		};
		
	};
};


typedef TMarshalOp *PMarshalOp;

class PASCALIMPLEMENTATION TMarshaler : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::TArray__1<TMarshalOp> FOps;
	
public:
	__fastcall TMarshaler(System::TArray__1<TMarshalOp> Ops);
	void __fastcall Execute(void * Src, void * Dest);
	virtual System::UnicodeString __fastcall ToString();
	static void __fastcall Optimize(System::TArray__1<TMarshalOp> &Ops);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMarshaler() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ocmarshal */
}	/* namespace Macapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI_OCMARSHAL)
using namespace Macapi::Ocmarshal;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI)
using namespace Macapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Macapi_OcmarshalHPP
