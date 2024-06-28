// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.MsInkAut.pas' rev: 34.00 (Windows)

#ifndef Winapi_MsinkautHPP
#define Winapi_MsinkautHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.TpcShrd.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.ActiveX.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

#include "msinkaut.h"

DECLARE_DINTERFACE_TYPE(IInkRectangle);
DECLARE_DINTERFACE_TYPE(IInkExtendedProperty);
DECLARE_DINTERFACE_TYPE(IInkExtendedProperties);
DECLARE_DINTERFACE_TYPE(IInkDrawingAttributes);
DECLARE_DINTERFACE_TYPE(IInkTransform);
DECLARE_DINTERFACE_TYPE(IInkGesture);
DECLARE_DINTERFACE_TYPE(IInkCursor);
DECLARE_DINTERFACE_TYPE(IInkCursors);
DECLARE_DINTERFACE_TYPE(IInkCursorButton);
DECLARE_DINTERFACE_TYPE(IInkCursorButtons);
DECLARE_DINTERFACE_TYPE(IInkTablet);
DECLARE_DINTERFACE_TYPE(IInkTablet2);
DECLARE_DINTERFACE_TYPE(IInkTablet3);
DECLARE_DINTERFACE_TYPE(IInkTablets);
DECLARE_DINTERFACE_TYPE(IInkStrokeDisp);
DECLARE_DINTERFACE_TYPE(IInkStrokes);
DECLARE_DINTERFACE_TYPE(IInkCustomStrokes);
DECLARE_DINTERFACE_TYPE(_IInkStrokesEvents);
DECLARE_DINTERFACE_TYPE(IInkDisp);
DECLARE_DINTERFACE_TYPE(_IInkEvents);
DECLARE_DINTERFACE_TYPE(IInkRenderer);
DECLARE_DINTERFACE_TYPE(IInkCollector);
DECLARE_DINTERFACE_TYPE(_IInkCollectorEvents);
DECLARE_DINTERFACE_TYPE(IInkOverlay);
DECLARE_DINTERFACE_TYPE(_IInkOverlayEvents);
DECLARE_DINTERFACE_TYPE(IInkPicture);
DECLARE_DINTERFACE_TYPE(_IInkPictureEvents);
DECLARE_DINTERFACE_TYPE(IInkRecognizer);
DECLARE_DINTERFACE_TYPE(IInkRecognizer2);
DECLARE_DINTERFACE_TYPE(IInkRecognizers);
DECLARE_DINTERFACE_TYPE(_IInkRecognitionEvents);
DECLARE_DINTERFACE_TYPE(IInkRecognizerContext);
DECLARE_DINTERFACE_TYPE(IInkRecognizerContext2);
DECLARE_DINTERFACE_TYPE(IInkRecognitionResult);
DECLARE_DINTERFACE_TYPE(IInkRecognitionAlternate);
DECLARE_DINTERFACE_TYPE(IInkRecognitionAlternates);
DECLARE_DINTERFACE_TYPE(IInkRecognizerGuide);
DECLARE_DINTERFACE_TYPE(IInkWordList);
DECLARE_DINTERFACE_TYPE(IInkWordList2);
DECLARE_DINTERFACE_TYPE(IInk);
DECLARE_DINTERFACE_TYPE(IInkLineInfo);
DECLARE_DINTERFACE_TYPE(ISketchInk);

namespace Winapi
{
namespace Msinkaut
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef INKMETRIC TInkMetric;

typedef INKMETRIC *PInkMetric;

typedef _InkRecoGuide TInkRecoGuide;

typedef _InkRecoGuide *PInkRecoGuide;

//-- var, const, procedure ---------------------------------------------------
#define SID_IInkRectangle L"{9794FF82-6071-4717-8A8B-6AC7C64A686E}"
#define SID_IInkExtendedProperty L"{DB489209-B7C3-411D-90F6-1548CFFF271E}"
#define SID_IInkExtendedProperties L"{89F2A8BE-95A9-4530-8B8F-88E971E3E25F}"
#define SID_IInkDrawingAttributes L"{BF519B75-0A15-4623-ADC9-C00D436A8092}"
#define SID_IInkTransform L"{615F1D43-8703-4565-88E2-8201D2ECD7B7}"
#define SID_IInkGesture L"{3BDC0A97-04E5-4e26-B813-18F052D41DEF}"
#define SID_IInkCursor L"{AD30C630-40C5-4350-8405-9C71012FC558}"
#define SID_IInkCursors L"{A248C1AC-C698-4e06-9E5C-D57F77C7E647}"
#define SID_IInkCursorButton L"{85EF9417-1D59-49b2-A13C-702C85430894}"
#define SID_IInkCursorButtons L"{3671CC40-B624-4671-9FA0-DB119D952D54}"
#define SID_IInkTablet L"{2DE25EAA-6EF8-42d5-AEE9-185BC81B912D}"
#define SID_IInkTablet2 L"{90c91ad2-fa36-49d6-9516-ce8d570f6f85}"
#define SID_IInkTablet3 L"{7e313997-1327-41dd-8ca9-79f24be17250}"
#define SID_IInkTablets L"{112086D9-7779-4535-A699-862B43AC1863}"
#define SID_IInkStrokeDisp L"{43242FEA-91D1-4a72-963E-FBB91829CFA2}"
#define SID_IInkStrokes L"{F1F4C9D8-590A-4963-B3AE-1935671BB6F3}"
#define SID_IInkCustomStrokes L"{7E23A88F-C30E-420f-9BDB-28902543F0C1}"
#define SID__IInkStrokesEvents L"{F33053EC-5D25-430a-928F-76A6491DDE15}"
#define SID_IInkDisp L"{9D398FA0-C4E2-4fcd-9973-975CAAF47EA6}"
#define SID__IInkEvents L"{427B1865-CA3F-479a-83A9-0F420F2A0073}"
#define SID_IInkRenderer L"{E6257A9C-B511-4f4c-A8B0-A7DBC9506B83}"
#define SID_IInkCollector L"{F0F060B5-8B1F-4a7c-89EC-880692588A4F}"
#define SID__IInkCollectorEvents L"{11A583F2-712D-4fea-ABCF-AB4AF38EA06B}"
#define SID_IInkOverlay L"{b82a463b-c1c5-45a3-997c-deab5651b67a}"
#define SID__IInkOverlayEvents L"{31179b69-e563-489e-b16f-712f1e8a0651}"
#define SID_IInkPicture L"{e85662e0-379a-40d7-9b5c-757d233f9923}"
#define SID__IInkPictureEvents L"{60ff4fee-22ff-4484-acc1-d308d9cd7ea3}"
#define SID_IInkRecognizer L"{782BF7CF-034B-4396-8A32-3A1833CF6B56}"
#define SID_IInkRecognizer2 L"{6110118A-3A75-4ad6-B2AA-04B2B72BBE65}"
#define SID_IInkRecognizers L"{9CCC4F12-B0B7-4a8b-BF58-4AECA4E8CEFD}"
#define SID__IInkRecognitionEvents L"{17BCE92F-2E21-47FD-9D33-3C6AFBFD8C59}"
#define SID_IInkRecognizerContext L"{C68F52F9-32A3-4625-906C-44FC23B40958}"
#define SID_IInkRecognizerContext2 L"{D6F0E32F-73D8-408e-8E9F-5FEA592C363F}"
#define SID_IInkRecognitionResult L"{3BC129A8-86CD-45ad-BDE8-E0D32D61C16D}"
#define SID_IInkRecognitionAlternate L"{B7E660AD-77E4-429b-ADDA-873780D1FC4A}"
#define SID_IInkRecognitionAlternates L"{286A167F-9F19-4c61-9D53-4F07BE622B84}"
#define SID_IInkRecognizerGuide L"{D934BE07-7B84-4208-9136-83C20994E905}"
#define SID_IInkWordList L"{76BA3491-CB2F-406b-9961-0E0C4CDAAEF2}"
#define SID_IInkWordList2 L"{14542586-11BF-4f5f-B6E7-49D0744AAB6E}"
#define SID_IInk L"{03F8E511-43A1-11D3-8BB6-0080C7D6BAD5}"
#define SID_IInkLineInfo L"{9C1C5AD6-F22F-4DE4-B453-A2CC482E7C33}"
#define SID_ISketchInk L"{B4563688-98EB-4646-B279-44DA14D45748}"
}	/* namespace Msinkaut */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_MSINKAUT)
using namespace Winapi::Msinkaut;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_MsinkautHPP
