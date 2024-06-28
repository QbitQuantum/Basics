// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Mapi.pas' rev: 34.00 (Windows)

#ifndef Winapi_MapiHPP
#define Winapi_MapiHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
#include <mapi.h>

namespace Winapi
{
namespace Mapi
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef MapiFileDesc *PMapiFileDesc;

typedef MapiFileDesc TMapiFileDesc;

typedef MapiFileTagExt *PMapiFileTagExt;

typedef MapiFileTagExt TMapiFileTagExt;

typedef MapiRecipDesc *PMapiRecipDesc;

typedef MapiRecipDesc TMapiRecipDesc;

typedef MapiMessage *PMapiMessage;

typedef MapiMessage TMapiMessage;

typedef unsigned __stdcall (*TFNMapiLogOn)(NativeUInt ulUIParam, char * lpszProfileName, char * lpszPassword, unsigned flFlags, unsigned ulReserved, LPLHANDLE lplhSession);

typedef TFNMapiLogOn *PFNMapiLogon;

typedef unsigned __stdcall (*TFNMapiLogOff)(NativeUInt lhSession, NativeUInt ulUIParam, unsigned flFlags, unsigned ulReserved);

typedef TFNMapiLogOff *PFNMapiLogOff;

typedef unsigned __stdcall (*TFNMapiSendMail)(NativeUInt lhSession, NativeUInt ulUIParam, MapiMessage &lpMessage, unsigned flFlags, unsigned ulReserved);

typedef TFNMapiSendMail *PFNMapiSendMail;

typedef unsigned __stdcall (*TFNMapiSendDocuments)(NativeUInt ulUIParam, char * lpszDelimChar, char * lpszFilePaths, char * lpszFileNames, unsigned ulReserved);

typedef TFNMapiSendDocuments *PFNMapiSendDocuments;

typedef unsigned __stdcall (*TFNMapiFindNext)(NativeUInt lhSession, NativeUInt ulUIParam, char * lpszMessageType, char * lpszSeedMessageID, unsigned flFlags, unsigned ulReserved, char * lpszMessageID);

typedef TFNMapiFindNext *PFNMapiFindNext;

typedef unsigned __stdcall (*TFNMapiReadMail)(NativeUInt lhSession, NativeUInt ulUIParam, char * lpszMessageID, unsigned flFlags, unsigned ulReserved, PMapiMessage &lppMessage);

typedef TFNMapiReadMail *PFNMapiReadMail;

typedef unsigned __stdcall (*TFNMapiSaveMail)(NativeUInt lhSession, NativeUInt ulUIParam, MapiMessage &lpMessage, unsigned flFlags, unsigned ulReserved, char * lpszMessageID);

typedef TFNMapiSaveMail *PFNMapiSaveMail;

typedef unsigned __stdcall (*TFNMapiDeleteMail)(NativeUInt lhSession, NativeUInt ulUIParam, char * lpszMessageID, unsigned flFlags, unsigned ulReserved);

typedef TFNMapiDeleteMail *PFNMapiDeleteMail;

typedef unsigned __stdcall (*TFNMapiFreeBuffer)(void * pv);

typedef TFNMapiFreeBuffer *PFNMapiFreeBuffer;

typedef unsigned __stdcall (*TFNMapiAddress)(NativeUInt lhSession, NativeUInt ulUIParam, char * lpszCaption, unsigned nEditFields, char * lpszLabels, unsigned nRecips, MapiRecipDesc &lpRecips, unsigned flFlags, unsigned ulReserved, PULONG lpnNewRecips, PMapiRecipDesc &lppNewRecips);

typedef TFNMapiAddress *PFNMapiAddress;

typedef unsigned __stdcall (*TFNMapiDetails)(NativeUInt lhSession, NativeUInt ulUIParam, MapiRecipDesc &lpRecip, unsigned flFlags, unsigned ulReserved);

typedef TFNMapiDetails *PFNMapiDetails;

typedef unsigned __stdcall (*TFNMapiResolveName)(NativeUInt lhSession, NativeUInt ulUIParam, char * lpszName, unsigned flFlags, unsigned ulReserved, PMapiRecipDesc &lppRecip);

typedef TFNMapiResolveName *PFNMapiResolveName;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString MAPIDLL;
extern DELPHI_PACKAGE unsigned __fastcall MapiLogOn(NativeUInt ulUIParam, char * lpszProfileName, char * lpszPassword, unsigned flFlags, unsigned ulReserved, LPLHANDLE lplhSession);
extern DELPHI_PACKAGE unsigned __fastcall MapiLogOff(NativeUInt lhSession, NativeUInt ulUIParam, unsigned flFlags, unsigned ulReserved);
extern DELPHI_PACKAGE unsigned __fastcall MapiSendMail(NativeUInt lhSession, NativeUInt ulUIParam, MapiMessage &lpMessage, unsigned flFlags, unsigned ulReserved);
extern DELPHI_PACKAGE unsigned __fastcall MapiSendDocuments(NativeUInt ulUIParam, char * lpszDelimChar, char * lpszFilePaths, char * lpszFileNames, unsigned ulReserved);
extern DELPHI_PACKAGE unsigned __fastcall MapiFindNext(NativeUInt lhSession, NativeUInt ulUIParam, char * lpszMessageType, char * lpszSeedMessageID, unsigned flFlags, unsigned ulReserved, char * lpszMessageID);
extern DELPHI_PACKAGE unsigned __fastcall MapiReadMail(NativeUInt lhSession, NativeUInt ulUIParam, char * lpszMessageID, unsigned flFlags, unsigned ulReserved, PMapiMessage &lppMessage);
extern DELPHI_PACKAGE unsigned __fastcall MapiSaveMail(NativeUInt lhSession, NativeUInt ulUIParam, MapiMessage &lpMessage, unsigned flFlags, unsigned ulReserved, char * lpszMessageID);
extern DELPHI_PACKAGE unsigned __fastcall MapiDeleteMail(NativeUInt lhSession, NativeUInt ulUIParam, char * lpszMessageID, unsigned flFlags, unsigned ulReserved);
extern DELPHI_PACKAGE unsigned __fastcall MapiFreeBuffer(void * pv);
extern DELPHI_PACKAGE unsigned __fastcall MapiAddress(NativeUInt lhSession, NativeUInt ulUIParam, char * lpszCaption, unsigned nEditFields, char * lpszLabels, unsigned nRecips, MapiRecipDesc &lpRecips, unsigned flFlags, unsigned ulReserved, PULONG lpnNewRecips, PMapiRecipDesc &lppNewRecips);
extern DELPHI_PACKAGE unsigned __fastcall MapiDetails(NativeUInt lhSession, NativeUInt ulUIParam, MapiRecipDesc &lpRecip, unsigned flFlags, unsigned ulReserved);
extern DELPHI_PACKAGE unsigned __fastcall MapiResolveName(NativeUInt lhSession, NativeUInt ulUIParam, char * lpszName, unsigned flFlags, unsigned ulReserved, PMapiRecipDesc &lppRecip);
}	/* namespace Mapi */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_MAPI)
using namespace Winapi::Mapi;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_MapiHPP
