// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.OleDlg.pas' rev: 34.00 (Windows)

#ifndef Winapi_OledlgHPP
#define Winapi_OledlgHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.CommCtrl.hpp>
#include <Winapi.ActiveX.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

#include <oledlg.h>

DECLARE_DINTERFACE_TYPE(IOleUIObjInfo)
DECLARE_DINTERFACE_TYPE(IOleUILinkInfo)

namespace Winapi
{
namespace Oledlg
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef int __stdcall (*TFNOleUIHook)(HWND Wnd, int Msg, int WParam, int LParam);

typedef tagOLEUIINSERTOBJECTA *POleUIInsertObjectA;

typedef tagOLEUIINSERTOBJECTW *POleUIInsertObjectW;

typedef POleUIInsertObjectW POleUIInsertObject;

typedef tagOLEUIINSERTOBJECTW tagOLEUIINSERTOBJECT;

typedef tagOLEUIINSERTOBJECTA TOleUIInsertObjectA;

typedef tagOLEUIINSERTOBJECTW TOleUIInsertObjectW;

typedef tagOLEUIINSERTOBJECTW TOleUIInsertObject;

typedef tagOLEUIPASTEENTRYA *POleUIPasteEntryA;

typedef tagOLEUIPASTEENTRYW *POleUIPasteEntryW;

typedef POleUIPasteEntryW POleUIPasteEntry;

typedef tagOLEUIPASTEENTRYW tagOLEUIPASTEENTRY;

typedef tagOLEUIPASTEENTRYA TOleUIPasteEntryA;

typedef tagOLEUIPASTEENTRYW TOleUIPasteEntryW;

typedef tagOLEUIPASTEENTRYW TOleUIPasteEntry;

typedef tagOLEUIPASTEENTRYW OLEUIPASTEENTRY;

typedef tagOLEUIPASTESPECIALA *POleUIPasteSpecialA;

typedef tagOLEUIPASTESPECIALW *POleUIPasteSpecialW;

typedef POleUIPasteSpecialW POleUIPasteSpecial;

typedef tagOLEUIPASTESPECIALW tagOLEUIPASTESPECIAL;

typedef tagOLEUIPASTESPECIALA TOleUIPasteSpecialA;

typedef tagOLEUIPASTESPECIALW TOleUIPasteSpecialW;

typedef tagOLEUIPASTESPECIALW TOleUIPasteSpecial;

typedef tagOLEUIEDITLINKSA *POleUIEditLinksA;

typedef tagOLEUIEDITLINKSW *POleUIEditLinksW;

typedef POleUIEditLinksW POleUIEditLinks;

typedef tagOLEUIEDITLINKSW tagOLEUIEDITLINKS;

typedef tagOLEUIEDITLINKSA TOleUIEditLinksA;

typedef tagOLEUIEDITLINKSW TOleUIEditLinksW;

typedef tagOLEUIEDITLINKSW TOleUIEditLinks;

typedef tagOLEUICHANGEICONA *POleUIChangeIconA;

typedef tagOLEUICHANGEICONW *POleUIChangeIconW;

typedef POleUIChangeIconW POleUIChangeIcon;

typedef tagOLEUICHANGEICONW tagOLEUICHANGEICON;

typedef tagOLEUICHANGEICONA TOleUIChangeIconA;

typedef tagOLEUICHANGEICONW TOleUIChangeIconW;

typedef tagOLEUICHANGEICONW TOleUIChangeIcon;

typedef tagOLEUICONVERTA *POleUIConvertA;

typedef tagOLEUICONVERTW *POleUIConvertW;

typedef POleUIConvertW POleUIConvert;

typedef tagOLEUICONVERTW tagOLEUICONVERT;

typedef tagOLEUICONVERTA TOleUIConvertA;

typedef tagOLEUICONVERTW TOleUIConvertW;

typedef tagOLEUICONVERTW TOleUIConvert;

typedef tagOLEUIBUSYA *POleUIBusyA;

typedef tagOLEUIBUSYW *POleUIBusyW;

typedef POleUIBusyW POleUIBusy;

typedef tagOLEUIBUSYW tagOLEUIBUSY;

typedef tagOLEUIBUSYA TOleUIBusyA;

typedef tagOLEUIBUSYW TOleUIBusyW;

typedef tagOLEUIBUSYW TOleUIBusy;

typedef tagOLEUIGNRLPROPSA *POleUIGnrlPropsA;

typedef tagOLEUIGNRLPROPSW *POleUIGnrlPropsW;

typedef POleUIGnrlPropsW POleUIGnrlProps;

typedef tagOLEUIGNRLPROPSW tagOLEUIGNRLPROPS;

typedef tagOLEUIGNRLPROPSA TOleUIGnrlPropsA;

typedef tagOLEUIGNRLPROPSW TOleUIGnrlPropsW;

typedef tagOLEUIGNRLPROPSW TOleUIGnrlProps;

typedef tagOLEUIGNRLPROPSW OLEUIGNRLPROPS;

typedef tagOLEUIVIEWPROPSA *POleUIViewPropsA;

typedef tagOLEUIVIEWPROPSW *POleUIViewPropsW;

typedef POleUIViewPropsW POleUIViewProps;

typedef tagOLEUIVIEWPROPSW tagOLEUIVIEWPROPS;

typedef tagOLEUIVIEWPROPSA TOleUIViewPropsA;

typedef tagOLEUIVIEWPROPSW TOleUIViewPropsW;

typedef tagOLEUIVIEWPROPSW TOleUIViewProps;

typedef tagOLEUIVIEWPROPSW OLEUIVIEWPROPS;

typedef tagOLEUILINKPROPSA *POleUILinkPropsA;

typedef tagOLEUILINKPROPSW *POleUILinkPropsW;

typedef POleUILinkPropsW POleUILinkProps;

typedef tagOLEUILINKPROPSW tagOLEUILINKPROPS;

typedef tagOLEUILINKPROPSA TOleUILinkPropsA;

typedef tagOLEUILINKPROPSW TOleUILinkPropsW;

typedef tagOLEUILINKPROPSW TOleUILinkProps;

typedef tagOLEUILINKPROPSW OLEUILINKPROPS;

typedef tagOLEUIOBJECTPROPSA *POleUIObjectPropsA;

typedef tagOLEUIOBJECTPROPSW *POleUIObjectPropsW;

typedef POleUIObjectPropsW POleUIObjectProps;

typedef tagOLEUIOBJECTPROPSW tagOLEUIOBJECTPROPS;

typedef tagOLEUIOBJECTPROPSA TOleUIObjectPropsA;

typedef tagOLEUIOBJECTPROPSW TOleUIObjectPropsW;

typedef tagOLEUIOBJECTPROPSW TOleUIObjectProps;

typedef tagOLEUIOBJECTPROPSW OLEUIOBJECTPROPS;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Oledlg */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_OLEDLG)
using namespace Winapi::Oledlg;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_OledlgHPP
