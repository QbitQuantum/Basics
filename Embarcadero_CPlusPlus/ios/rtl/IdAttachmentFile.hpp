// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdAttachmentFile.pas' rev: 34.00 (iOS)

#ifndef IdattachmentfileHPP
#define IdattachmentfileHPP

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

//-- user supplied -----------------------------------------------------------

namespace Idattachmentfile
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdAttachmentFile;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdAttachmentFile : public Idattachment::TIdAttachment
{
	typedef Idattachment::TIdAttachment inherited;
	
protected:
	System::Classes::TFileStream* FTempFileStream;
	System::UnicodeString FStoredPathName;
	bool FFileIsTempFile;
	bool FAttachmentBlocked;
	
public:
	__fastcall TIdAttachmentFile(Idmessageparts::TIdMessageParts* Collection, const System::UnicodeString AFileName);
	__fastcall virtual ~TIdAttachmentFile();
	virtual System::Classes::TStream* __fastcall OpenLoadStream();
	virtual void __fastcall CloseLoadStream();
	virtual System::Classes::TStream* __fastcall PrepareTempStream();
	virtual void __fastcall FinishTempStream();
	virtual void __fastcall SaveToFile(const System::UnicodeString FileName);
	__property bool FileIsTempFile = {read=FFileIsTempFile, write=FFileIsTempFile, nodefault};
	__property System::UnicodeString StoredPathName = {read=FStoredPathName, write=FStoredPathName};
	__property bool AttachmentBlocked = {read=FAttachmentBlocked, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idattachmentfile */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDATTACHMENTFILE)
using namespace Idattachmentfile;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdattachmentfileHPP
