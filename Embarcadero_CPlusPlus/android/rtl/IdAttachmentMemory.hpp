// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdAttachmentMemory.pas' rev: 34.00 (Android)

#ifndef IdattachmentmemoryHPP
#define IdattachmentmemoryHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAttachment.hpp>
#include <IdMessageParts.hpp>
#include <IdGlobal.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idattachmentmemory
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdAttachmentMemory;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdAttachmentMemory : public Idattachment::TIdAttachment
{
	typedef Idattachment::TIdAttachment inherited;
	
protected:
	System::Classes::TStream* FDataStream;
	__int64 FDataStreamBeforeLoadPosition;
	System::UnicodeString __fastcall GetDataString();
	void __fastcall SetDataStream(System::Classes::TStream* const Value);
	void __fastcall SetDataString(const System::UnicodeString Value);
	
public:
	__fastcall virtual TIdAttachmentMemory(System::Classes::TCollection* Collection)/* overload */;
	__fastcall TIdAttachmentMemory(Idmessageparts::TIdMessageParts* Collection, System::Classes::TStream* const CopyFrom)/* overload */;
	__fastcall TIdAttachmentMemory(Idmessageparts::TIdMessageParts* Collection, const System::UnicodeString CopyFrom)/* overload */;
	__fastcall virtual ~TIdAttachmentMemory();
	__property System::Classes::TStream* DataStream = {read=FDataStream, write=SetDataStream};
	__property System::UnicodeString DataString = {read=GetDataString, write=SetDataString};
	virtual System::Classes::TStream* __fastcall OpenLoadStream();
	virtual void __fastcall CloseLoadStream();
	virtual void __fastcall FinishTempStream();
	virtual System::Classes::TStream* __fastcall PrepareTempStream();
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idattachmentmemory */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDATTACHMENTMEMORY)
using namespace Idattachmentmemory;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdattachmentmemoryHPP
