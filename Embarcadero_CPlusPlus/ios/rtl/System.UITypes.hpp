// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.UITypes.pas' rev: 34.00 (iOS)

#ifndef System_UitypesHPP
#define System_UitypesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------
namespace System
{
namespace Uitypes
{
  enum DECLSPEC_DENUM TFontStyle : unsigned char { fsBold, fsItalic, fsUnderline, fsStrikeOut };
  typedef System::SmallStringBase<124> TFontDataName;
  typedef System::SetBase<TFontStyle, fsBold, fsStrikeOut> TFontStylesBase;
}	/* namespace Uitypes */
}	/* namespace System */
namespace System
{
namespace Uitypes
{
  enum DECLSPEC_DENUM TCursor : short {crMin=-32768, crMax=32767};
}	/* namespace Uitypes */
}	/* namespace System */
namespace System
{
namespace Uitypes
{
  enum DECLSPEC_DENUM TColor : int {clMin=-0x7fffffff-1, clMax=0x7fffffff};
}	/* namespace Uitypes */
}	/* namespace System */

namespace System
{
namespace Uitypes
{
//-- forward type declarations -----------------------------------------------
struct TColorRec;
struct TAlphaColorRec;
struct TAlphaColorF;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TOpenOption : unsigned char { ofReadOnly, ofOverwritePrompt, ofHideReadOnly, ofNoChangeDir, ofShowHelp, ofNoValidate, ofAllowMultiSelect, ofExtensionDifferent, ofPathMustExist, ofFileMustExist, ofCreatePrompt, ofShareAware, ofNoReadOnlyReturn, ofNoTestFileCreate, ofNoNetworkButton, ofNoLongNames, ofOldStyleDialog, ofNoDereferenceLinks, ofEnableIncludeNotify, ofEnableSizing, ofDontAddToRecent, ofForceShowHidden };

typedef System::Set<TOpenOption, _DELPHI_SET_ENUMERATOR(TOpenOption::ofReadOnly), _DELPHI_SET_ENUMERATOR(TOpenOption::ofForceShowHidden)> TOpenOptions;

enum class DECLSPEC_DENUM TOpenOptionEx : unsigned char { ofExNoPlacesBar };

typedef System::Set<TOpenOptionEx, _DELPHI_SET_ENUMERATOR(TOpenOptionEx::ofExNoPlacesBar), _DELPHI_SET_ENUMERATOR(TOpenOptionEx::ofExNoPlacesBar)> TOpenOptionsEx;

enum class DECLSPEC_DENUM TDialogType : unsigned char { Standard, Directory };

enum class DECLSPEC_DENUM TPrintRange : unsigned char { prAllPages, prSelection, prPageNums };

enum class DECLSPEC_DENUM TPrintDialogOption : unsigned char { poPrintToFile, poPageNums, poSelection, poWarning, poHelp, poDisablePrintToFile };

typedef System::Set<TPrintDialogOption, _DELPHI_SET_ENUMERATOR(TPrintDialogOption::poPrintToFile), _DELPHI_SET_ENUMERATOR(TPrintDialogOption::poDisablePrintToFile)> TPrintDialogOptions;

enum class DECLSPEC_DENUM TPageSetupDialogOption : unsigned char { psoDefaultMinMargins, psoDisableMargins, psoDisableOrientation, psoDisablePagePainting, psoDisablePaper, psoDisablePrinter, psoMargins, psoMinMargins, psoShowHelp, psoWarning, psoNoNetworkButton };

typedef System::Set<TPageSetupDialogOption, _DELPHI_SET_ENUMERATOR(TPageSetupDialogOption::psoDefaultMinMargins), _DELPHI_SET_ENUMERATOR(TPageSetupDialogOption::psoNoNetworkButton)> TPageSetupDialogOptions;

enum class DECLSPEC_DENUM TPrinterKind : unsigned char { pkDotMatrix, pkHPPCL };

enum class DECLSPEC_DENUM TPageType : unsigned char { ptEnvelope, ptPaper };

enum class DECLSPEC_DENUM TPageMeasureUnits : unsigned char { pmDefault, pmMillimeters, pmInches };

enum class DECLSPEC_DENUM TMsgDlgType : unsigned char { mtWarning, mtError, mtInformation, mtConfirmation, mtCustom };

enum class DECLSPEC_DENUM TMsgDlgBtn : unsigned char { mbYes, mbNo, mbOK, mbCancel, mbAbort, mbRetry, mbIgnore, mbAll, mbNoToAll, mbYesToAll, mbHelp, mbClose };

typedef System::Set<TMsgDlgBtn, _DELPHI_SET_ENUMERATOR(TMsgDlgBtn::mbYes), _DELPHI_SET_ENUMERATOR(TMsgDlgBtn::mbClose)> TMsgDlgButtons;

enum class DECLSPEC_DENUM TCalDayOfWeek : unsigned char { dowMonday, dowTuesday, dowWednesday, dowThursday, dowFriday, dowSaturday, dowSunday, dowLocaleDefault };

enum class DECLSPEC_DENUM TBorderIcon : unsigned char { biSystemMenu, biMinimize, biMaximize, biHelp };

typedef System::Set<TBorderIcon, _DELPHI_SET_ENUMERATOR(TBorderIcon::biSystemMenu), _DELPHI_SET_ENUMERATOR(TBorderIcon::biHelp)> TBorderIcons;

enum class DECLSPEC_DENUM TWindowState : unsigned char { wsNormal, wsMinimized, wsMaximized };

enum class DECLSPEC_DENUM TEditCharCase : unsigned char { ecNormal, ecUpperCase, ecLowerCase };

_DECLARE_ARITH_TYPE_ALIAS(System::Byte, TFontCharset);

enum class DECLSPEC_DENUM TFontPitch : unsigned char { fpDefault, fpVariable, fpFixed };

enum class DECLSPEC_DENUM TFontQuality : unsigned char { fqDefault, fqDraft, fqProof, fqNonAntialiased, fqAntialiased, fqClearType, fqClearTypeNatural };

typedef System::Set<TFontStyle, _DELPHI_SET_ENUMERATOR(TFontStyle::fsBold), _DELPHI_SET_ENUMERATOR(TFontStyle::fsStrikeOut)> TFontStyles;

_DECLARE_STRING_TYPE_ALIAS(System::UnicodeString, TFontName);

enum class DECLSPEC_DENUM TCloseAction : unsigned char { caNone, caHide, caFree, caMinimize };

enum class DECLSPEC_DENUM TMouseButton : unsigned char { mbLeft, mbRight, mbMiddle };

enum class DECLSPEC_DENUM TMouseActivate : unsigned char { maDefault, maActivate, maActivateAndEat, maNoActivate, maNoActivateAndEat };

_DECLARE_ARITH_TYPE_ALIAS(short, TTabOrder);

_DECLARE_ARITH_TYPE_ALIAS(int, TModalResult);

enum class DECLSPEC_DENUM TDragMode : unsigned char { dmManual, dmAutomatic };

enum class DECLSPEC_DENUM TDragState : unsigned char { dsDragEnter, dsDragLeave, dsDragMove };

enum class DECLSPEC_DENUM TDragKind : unsigned char { dkDrag, dkDock };

enum class DECLSPEC_DENUM TAnchorKind : unsigned char { akLeft, akTop, akRight, akBottom };

typedef System::Set<TAnchorKind, _DELPHI_SET_ENUMERATOR(TAnchorKind::akLeft), _DELPHI_SET_ENUMERATOR(TAnchorKind::akBottom)> TAnchors;

enum class DECLSPEC_DENUM TScrollCode : unsigned char { scLineUp, scLineDown, scPageUp, scPageDown, scPosition, scTrack, scTop, scBottom, scEndScroll };

enum class DECLSPEC_DENUM TPrinterState : unsigned char { psNoHandle, psHandleIC, psHandleDC };

enum class DECLSPEC_DENUM TPrinterOrientation : unsigned char { poPortrait, poLandscape };

enum class DECLSPEC_DENUM TPrinterCapability : unsigned char { pcCopies, pcOrientation, pcCollation };

typedef System::Set<TPrinterCapability, _DELPHI_SET_ENUMERATOR(TPrinterCapability::pcCopies), _DELPHI_SET_ENUMERATOR(TPrinterCapability::pcCollation)> TPrinterCapabilities;

typedef unsigned TColorRef;

typedef TColor *PColor;

typedef TColorRec *PColorRec;

struct DECLSPEC_DRECORD TColorRec
{
public:
	static constexpr unsigned SystemColor = unsigned(0xff000000);
	
	static constexpr System::Int8 cSCROLLBAR = System::Int8(0x0);
	
	static constexpr System::Int8 cBACKGROUND = System::Int8(0x1);
	
	static constexpr System::Int8 cACTIVECAPTION = System::Int8(0x2);
	
	static constexpr System::Int8 cINACTIVECAPTION = System::Int8(0x3);
	
	static constexpr System::Int8 cMENU = System::Int8(0x4);
	
	static constexpr System::Int8 cWINDOW = System::Int8(0x5);
	
	static constexpr System::Int8 cWINDOWFRAME = System::Int8(0x6);
	
	static constexpr System::Int8 cMENUTEXT = System::Int8(0x7);
	
	static constexpr System::Int8 cWINDOWTEXT = System::Int8(0x8);
	
	static constexpr System::Int8 cCAPTIONTEXT = System::Int8(0x9);
	
	static constexpr System::Int8 cACTIVEBORDER = System::Int8(0xa);
	
	static constexpr System::Int8 cINACTIVEBORDER = System::Int8(0xb);
	
	static constexpr System::Int8 cAPPWORKSPACE = System::Int8(0xc);
	
	static constexpr System::Int8 cHIGHLIGHT = System::Int8(0xd);
	
	static constexpr System::Int8 cHIGHLIGHTTEXT = System::Int8(0xe);
	
	static constexpr System::Int8 cBTNFACE = System::Int8(0xf);
	
	static constexpr System::Int8 cBTNSHADOW = System::Int8(0x10);
	
	static constexpr System::Int8 cGRAYTEXT = System::Int8(0x11);
	
	static constexpr System::Int8 cBTNTEXT = System::Int8(0x12);
	
	static constexpr System::Int8 cINACTIVECAPTIONTEXT = System::Int8(0x13);
	
	static constexpr System::Int8 cBTNHIGHLIGHT = System::Int8(0x14);
	
	static constexpr System::Int8 c3DDKSHADOW = System::Int8(0x15);
	
	static constexpr System::Int8 c3DLIGHT = System::Int8(0x16);
	
	static constexpr System::Int8 cINFOTEXT = System::Int8(0x17);
	
	static constexpr System::Int8 cINFOBK = System::Int8(0x18);
	
	static constexpr System::Int8 cHOTLIGHT = System::Int8(0x1a);
	
	static constexpr System::Int8 cGRADIENTACTIVECAPTION = System::Int8(0x1b);
	
	static constexpr System::Int8 cGRADIENTINACTIVECAPTION = System::Int8(0x1c);
	
	static constexpr System::Int8 cMENUHILIGHT = System::Int8(0x1d);
	
	static constexpr System::Int8 cMENUBAR = System::Int8(0x1e);
	
	static constexpr System::Int8 cENDCOLORS = System::Int8(0x1e);
	
	static constexpr System::Int8 cDESKTOP = System::Int8(0x1);
	
	static constexpr System::Int8 c3DFACE = System::Int8(0xf);
	
	static constexpr System::Int8 c3DSHADOW = System::Int8(0x10);
	
	static constexpr System::Int8 c3DHIGHLIGHT = System::Int8(0x14);
	
	static constexpr System::Int8 c3DHILIGHT = System::Int8(0x14);
	
	static constexpr System::Int8 cBTNHILIGHT = System::Int8(0x14);
	
	static constexpr TColor SysScrollBar = TColor(-16777216);
	
	static constexpr TColor SysBackground = TColor(-16777215);
	
	static constexpr TColor SysActiveCaption = TColor(-16777214);
	
	static constexpr TColor SysInactiveCaption = TColor(-16777213);
	
	static constexpr TColor SysMenu = TColor(-16777212);
	
	static constexpr TColor SysWindow = TColor(-16777211);
	
	static constexpr TColor SysWindowFrame = TColor(-16777210);
	
	static constexpr TColor SysMenuText = TColor(-16777209);
	
	static constexpr TColor SysWindowText = TColor(-16777208);
	
	static constexpr TColor SysCaptionText = TColor(-16777207);
	
	static constexpr TColor SysActiveBorder = TColor(-16777206);
	
	static constexpr TColor SysInactiveBorder = TColor(-16777205);
	
	static constexpr TColor SysAppWorkSpace = TColor(-16777204);
	
	static constexpr TColor SysHighlight = TColor(-16777203);
	
	static constexpr TColor SysHighlightText = TColor(-16777202);
	
	static constexpr TColor SysBtnFace = TColor(-16777201);
	
	static constexpr TColor SysBtnShadow = TColor(-16777200);
	
	static constexpr TColor SysGrayText = TColor(-16777199);
	
	static constexpr TColor SysBtnText = TColor(-16777198);
	
	static constexpr TColor SysInactiveCaptionText = TColor(-16777197);
	
	static constexpr TColor SysBtnHighlight = TColor(-16777196);
	
	static constexpr TColor Sys3DDkShadow = TColor(-16777195);
	
	static constexpr TColor Sys3DLight = TColor(-16777194);
	
	static constexpr TColor SysInfoText = TColor(-16777193);
	
	static constexpr TColor SysInfoBk = TColor(-16777192);
	
	static constexpr TColor SysHotLight = TColor(-16777190);
	
	static constexpr TColor SysGradientActiveCaption = TColor(-16777189);
	
	static constexpr TColor SysGradientInactiveCaption = TColor(-16777188);
	
	static constexpr TColor SysMenuHighlight = TColor(-16777187);
	
	static constexpr TColor SysMenuBar = TColor(-16777186);
	
	static constexpr TColor SysNone = TColor(536870911);
	
	static constexpr TColor SysDefault = TColor(536870912);
	
	static constexpr TColor Aliceblue = TColor(16775408);
	
	static constexpr TColor Antiquewhite = TColor(14150650);
	
	static constexpr TColor Aqua = TColor(16776960);
	
	static constexpr TColor Aquamarine = TColor(13959039);
	
	static constexpr TColor Azure = TColor(16777200);
	
	static constexpr TColor Beige = TColor(14480885);
	
	static constexpr TColor Bisque = TColor(12903679);
	
	static constexpr TColor Black = TColor(0);
	
	static constexpr TColor Blanchedalmond = TColor(13495295);
	
	static constexpr TColor Blue = TColor(16711680);
	
	static constexpr TColor Blueviolet = TColor(14822282);
	
	static constexpr TColor Brown = TColor(2763429);
	
	static constexpr TColor Burlywood = TColor(8894686);
	
	static constexpr TColor Cadetblue = TColor(10526303);
	
	static constexpr TColor Chartreuse = TColor(65407);
	
	static constexpr TColor Chocolate = TColor(1993170);
	
	static constexpr TColor Coral = TColor(5275647);
	
	static constexpr TColor Cornflowerblue = TColor(15570276);
	
	static constexpr TColor Cornsilk = TColor(14481663);
	
	static constexpr TColor Crimson = TColor(3937500);
	
	static constexpr TColor Cyan = TColor(16776960);
	
	static constexpr TColor Darkblue = TColor(9109504);
	
	static constexpr TColor Darkcyan = TColor(9145088);
	
	static constexpr TColor Darkgoldenrod = TColor(755384);
	
	static constexpr TColor Darkgray = TColor(11119017);
	
	static constexpr TColor Darkgreen = TColor(25600);
	
	static constexpr TColor Darkgrey = TColor(11119017);
	
	static constexpr TColor Darkkhaki = TColor(7059389);
	
	static constexpr TColor Darkmagenta = TColor(9109643);
	
	static constexpr TColor Darkolivegreen = TColor(3107669);
	
	static constexpr TColor Darkorange = TColor(36095);
	
	static constexpr TColor Darkorchid = TColor(13382297);
	
	static constexpr TColor Darkred = TColor(139);
	
	static constexpr TColor Darksalmon = TColor(8034025);
	
	static constexpr TColor Darkseagreen = TColor(9419919);
	
	static constexpr TColor Darkslateblue = TColor(9125192);
	
	static constexpr TColor Darkslategray = TColor(5197615);
	
	static constexpr TColor Darkslategrey = TColor(5197615);
	
	static constexpr TColor Darkturquoise = TColor(13749760);
	
	static constexpr TColor Darkviolet = TColor(13828244);
	
	static constexpr TColor Deeppink = TColor(9639167);
	
	static constexpr TColor Deepskyblue = TColor(16760576);
	
	static constexpr TColor Dimgray = TColor(6908265);
	
	static constexpr TColor Dimgrey = TColor(6908265);
	
	static constexpr TColor Dodgerblue = TColor(16748574);
	
	static constexpr TColor Firebrick = TColor(2237106);
	
	static constexpr TColor Floralwhite = TColor(15792895);
	
	static constexpr TColor Forestgreen = TColor(2263842);
	
	static constexpr TColor Fuchsia = TColor(16711935);
	
	static constexpr TColor Gainsboro = TColor(14474460);
	
	static constexpr TColor Ghostwhite = TColor(16775416);
	
	static constexpr TColor Gold = TColor(55295);
	
	static constexpr TColor Goldenrod = TColor(2139610);
	
	static constexpr TColor Gray = TColor(8421504);
	
	static constexpr TColor Green = TColor(32768);
	
	static constexpr TColor Greenyellow = TColor(3145645);
	
	static constexpr TColor Grey = TColor(8421504);
	
	static constexpr TColor Honeydew = TColor(15794160);
	
	static constexpr TColor Hotpink = TColor(11823615);
	
	static constexpr TColor Indianred = TColor(6053069);
	
	static constexpr TColor Indigo = TColor(8519755);
	
	static constexpr TColor Ivory = TColor(15794175);
	
	static constexpr TColor Khaki = TColor(9234160);
	
	static constexpr TColor Lavender = TColor(16443110);
	
	static constexpr TColor Lavenderblush = TColor(16118015);
	
	static constexpr TColor Lawngreen = TColor(64636);
	
	static constexpr TColor Lemonchiffon = TColor(13499135);
	
	static constexpr TColor Lightblue = TColor(15128749);
	
	static constexpr TColor Lightcoral = TColor(8421616);
	
	static constexpr TColor Lightcyan = TColor(16777184);
	
	static constexpr TColor Lightgoldenrodyellow = TColor(13826810);
	
	static constexpr TColor Lightgray = TColor(13882323);
	
	static constexpr TColor Lightgreen = TColor(9498256);
	
	static constexpr TColor Lightgrey = TColor(13882323);
	
	static constexpr TColor Lightpink = TColor(12695295);
	
	static constexpr TColor Lightsalmon = TColor(8036607);
	
	static constexpr TColor Lightseagreen = TColor(11186720);
	
	static constexpr TColor Lightskyblue = TColor(16436871);
	
	static constexpr TColor Lightslategray = TColor(10061943);
	
	static constexpr TColor Lightslategrey = TColor(10061943);
	
	static constexpr TColor Lightsteelblue = TColor(14599344);
	
	static constexpr TColor Lightyellow = TColor(14745599);
	
	static constexpr TColor LtGray = TColor(12632256);
	
	static constexpr TColor MedGray = TColor(10789024);
	
	static constexpr TColor DkGray = TColor(8421504);
	
	static constexpr TColor MoneyGreen = TColor(12639424);
	
	static constexpr TColor LegacySkyBlue = TColor(15780518);
	
	static constexpr TColor Cream = TColor(15793151);
	
	static constexpr TColor Lime = TColor(65280);
	
	static constexpr TColor Limegreen = TColor(3329330);
	
	static constexpr TColor Linen = TColor(15134970);
	
	static constexpr TColor Magenta = TColor(16711935);
	
	static constexpr TColor Maroon = TColor(128);
	
	static constexpr TColor Mediumaquamarine = TColor(11193702);
	
	static constexpr TColor Mediumblue = TColor(13434880);
	
	static constexpr TColor Mediumorchid = TColor(13850042);
	
	static constexpr TColor Mediumpurple = TColor(14381203);
	
	static constexpr TColor Mediumseagreen = TColor(7451452);
	
	static constexpr TColor Mediumslateblue = TColor(15624315);
	
	static constexpr TColor Mediumspringgreen = TColor(10156544);
	
	static constexpr TColor Mediumturquoise = TColor(13422920);
	
	static constexpr TColor Mediumvioletred = TColor(8721863);
	
	static constexpr TColor Midnightblue = TColor(7346457);
	
	static constexpr TColor Mintcream = TColor(16449525);
	
	static constexpr TColor Mistyrose = TColor(14804223);
	
	static constexpr TColor Moccasin = TColor(11920639);
	
	static constexpr TColor Navajowhite = TColor(11394815);
	
	static constexpr TColor Navy = TColor(8388608);
	
	static constexpr TColor Oldlace = TColor(15136253);
	
	static constexpr TColor Olive = TColor(32896);
	
	static constexpr TColor Olivedrab = TColor(2330219);
	
	static constexpr TColor Orange = TColor(42495);
	
	static constexpr TColor Orangered = TColor(17919);
	
	static constexpr TColor Orchid = TColor(14053594);
	
	static constexpr TColor Palegoldenrod = TColor(11200750);
	
	static constexpr TColor Palegreen = TColor(10025880);
	
	static constexpr TColor Paleturquoise = TColor(15658671);
	
	static constexpr TColor Palevioletred = TColor(9662683);
	
	static constexpr TColor Papayawhip = TColor(14020607);
	
	static constexpr TColor Peachpuff = TColor(12180223);
	
	static constexpr TColor Peru = TColor(4163021);
	
	static constexpr TColor Pink = TColor(13353215);
	
	static constexpr TColor Plum = TColor(14524637);
	
	static constexpr TColor Powderblue = TColor(15130800);
	
	static constexpr TColor Purple = TColor(8388736);
	
	static constexpr TColor Red = TColor(255);
	
	static constexpr TColor Rosybrown = TColor(9408444);
	
	static constexpr TColor Royalblue = TColor(14772545);
	
	static constexpr TColor Saddlebrown = TColor(1262987);
	
	static constexpr TColor Salmon = TColor(7504122);
	
	static constexpr TColor Sandybrown = TColor(6333684);
	
	static constexpr TColor Seagreen = TColor(5737262);
	
	static constexpr TColor Seashell = TColor(15660543);
	
	static constexpr TColor Sienna = TColor(2970272);
	
	static constexpr TColor Silver = TColor(12632256);
	
	static constexpr TColor Skyblue = TColor(15453831);
	
	static constexpr TColor Slateblue = TColor(13458026);
	
	static constexpr TColor Slategray = TColor(9470064);
	
	static constexpr TColor Slategrey = TColor(9470064);
	
	static constexpr TColor Snow = TColor(16448255);
	
	static constexpr TColor Springgreen = TColor(8388352);
	
	static constexpr TColor Steelblue = TColor(11829830);
	
	static constexpr TColor Tan = TColor(9221330);
	
	static constexpr TColor Teal = TColor(8421376);
	
	static constexpr TColor Thistle = TColor(14204888);
	
	static constexpr TColor Tomato = TColor(4678655);
	
	static constexpr TColor Turquoise = TColor(13688896);
	
	static constexpr TColor Violet = TColor(15631086);
	
	static constexpr TColor Wheat = TColor(11788021);
	
	static constexpr TColor White = TColor(16777215);
	
	static constexpr TColor Whitesmoke = TColor(16119285);
	
	static constexpr TColor Yellow = TColor(65535);
	
	static constexpr TColor Yellowgreen = TColor(3329434);
	
	static constexpr TColor Null = TColor(0);
	
	static long __fastcall (*ColorToRGB)(TColor Color);
	
public:
	union
	{
		struct 
		{
			System::Byte R;
			System::Byte G;
			System::Byte B;
			System::Byte A;
		};
		struct 
		{
			System::Word HiWord;
			System::Word LoWord;
		};
		struct 
		{
			TColor Color;
		};
		
	};
};


typedef TColorRec TColors;

_DECLARE_ARITH_TYPE_ALIAS(unsigned, TAlphaColor);

typedef TAlphaColor *PAlphaColor;

typedef TAlphaColorRec *PAlphaColorRec;

struct DECLSPEC_DRECORD TAlphaColorRec
{
public:
	static constexpr TAlphaColor Alpha = TAlphaColor(0xff000000);
	
	static constexpr unsigned Aliceblue = unsigned(0xfff0f8ff);
	
	static constexpr unsigned Antiquewhite = unsigned(0xfffaebd7);
	
	static constexpr unsigned Aqua = unsigned(0xff00ffff);
	
	static constexpr unsigned Aquamarine = unsigned(0xff7fffd4);
	
	static constexpr unsigned Azure = unsigned(0xfff0ffff);
	
	static constexpr unsigned Beige = unsigned(0xfff5f5dc);
	
	static constexpr unsigned Bisque = unsigned(0xffffe4c4);
	
	static constexpr unsigned Black = unsigned(0xff000000);
	
	static constexpr unsigned Blanchedalmond = unsigned(0xffffebcd);
	
	static constexpr unsigned Blue = unsigned(0xff0000ff);
	
	static constexpr unsigned Blueviolet = unsigned(0xff8a2be2);
	
	static constexpr unsigned Brown = unsigned(0xffa52a2a);
	
	static constexpr unsigned Burlywood = unsigned(0xffdeb887);
	
	static constexpr unsigned Cadetblue = unsigned(0xff5f9ea0);
	
	static constexpr unsigned Chartreuse = unsigned(0xff7fff00);
	
	static constexpr unsigned Chocolate = unsigned(0xffd2691e);
	
	static constexpr unsigned Coral = unsigned(0xffff7f50);
	
	static constexpr unsigned Cornflowerblue = unsigned(0xff6495ed);
	
	static constexpr unsigned Cornsilk = unsigned(0xfffff8dc);
	
	static constexpr unsigned Crimson = unsigned(0xffdc143c);
	
	static constexpr unsigned Cyan = unsigned(0xff00ffff);
	
	static constexpr unsigned Darkblue = unsigned(0xff00008b);
	
	static constexpr unsigned Darkcyan = unsigned(0xff008b8b);
	
	static constexpr unsigned Darkgoldenrod = unsigned(0xffb8860b);
	
	static constexpr unsigned Darkgray = unsigned(0xffa9a9a9);
	
	static constexpr unsigned Darkgreen = unsigned(0xff006400);
	
	static constexpr unsigned Darkgrey = unsigned(0xffa9a9a9);
	
	static constexpr unsigned Darkkhaki = unsigned(0xffbdb76b);
	
	static constexpr unsigned Darkmagenta = unsigned(0xff8b008b);
	
	static constexpr unsigned Darkolivegreen = unsigned(0xff556b2f);
	
	static constexpr unsigned Darkorange = unsigned(0xffff8c00);
	
	static constexpr unsigned Darkorchid = unsigned(0xff9932cc);
	
	static constexpr unsigned Darkred = unsigned(0xff8b0000);
	
	static constexpr unsigned Darksalmon = unsigned(0xffe9967a);
	
	static constexpr unsigned Darkseagreen = unsigned(0xff8fbc8f);
	
	static constexpr unsigned Darkslateblue = unsigned(0xff483d8b);
	
	static constexpr unsigned Darkslategray = unsigned(0xff2f4f4f);
	
	static constexpr unsigned Darkslategrey = unsigned(0xff2f4f4f);
	
	static constexpr unsigned Darkturquoise = unsigned(0xff00ced1);
	
	static constexpr unsigned Darkviolet = unsigned(0xff9400d3);
	
	static constexpr unsigned Deeppink = unsigned(0xffff1493);
	
	static constexpr unsigned Deepskyblue = unsigned(0xff00bfff);
	
	static constexpr unsigned Dimgray = unsigned(0xff696969);
	
	static constexpr unsigned Dimgrey = unsigned(0xff696969);
	
	static constexpr unsigned Dodgerblue = unsigned(0xff1e90ff);
	
	static constexpr unsigned Firebrick = unsigned(0xffb22222);
	
	static constexpr unsigned Floralwhite = unsigned(0xfffffaf0);
	
	static constexpr unsigned Forestgreen = unsigned(0xff228b22);
	
	static constexpr unsigned Fuchsia = unsigned(0xffff00ff);
	
	static constexpr unsigned Gainsboro = unsigned(0xffdcdcdc);
	
	static constexpr unsigned Ghostwhite = unsigned(0xfff8f8ff);
	
	static constexpr unsigned Gold = unsigned(0xffffd700);
	
	static constexpr unsigned Goldenrod = unsigned(0xffdaa520);
	
	static constexpr unsigned Gray = unsigned(0xff808080);
	
	static constexpr unsigned Green = unsigned(0xff008000);
	
	static constexpr unsigned Greenyellow = unsigned(0xffadff2f);
	
	static constexpr unsigned Grey = unsigned(0xff808080);
	
	static constexpr unsigned Honeydew = unsigned(0xfff0fff0);
	
	static constexpr unsigned Hotpink = unsigned(0xffff69b4);
	
	static constexpr unsigned Indianred = unsigned(0xffcd5c5c);
	
	static constexpr unsigned Indigo = unsigned(0xff4b0082);
	
	static constexpr unsigned Ivory = unsigned(0xfffffff0);
	
	static constexpr unsigned Khaki = unsigned(0xfff0e68c);
	
	static constexpr unsigned Lavender = unsigned(0xffe6e6fa);
	
	static constexpr unsigned Lavenderblush = unsigned(0xfffff0f5);
	
	static constexpr unsigned Lawngreen = unsigned(0xff7cfc00);
	
	static constexpr unsigned Lemonchiffon = unsigned(0xfffffacd);
	
	static constexpr unsigned Lightblue = unsigned(0xffadd8e6);
	
	static constexpr unsigned Lightcoral = unsigned(0xfff08080);
	
	static constexpr unsigned Lightcyan = unsigned(0xffe0ffff);
	
	static constexpr unsigned Lightgoldenrodyellow = unsigned(0xfffafad2);
	
	static constexpr unsigned Lightgray = unsigned(0xffd3d3d3);
	
	static constexpr unsigned Lightgreen = unsigned(0xff90ee90);
	
	static constexpr unsigned Lightgrey = unsigned(0xffd3d3d3);
	
	static constexpr unsigned Lightpink = unsigned(0xffffb6c1);
	
	static constexpr unsigned Lightsalmon = unsigned(0xffffa07a);
	
	static constexpr unsigned Lightseagreen = unsigned(0xff20b2aa);
	
	static constexpr unsigned Lightskyblue = unsigned(0xff87cefa);
	
	static constexpr unsigned Lightslategray = unsigned(0xff778899);
	
	static constexpr unsigned Lightslategrey = unsigned(0xff778899);
	
	static constexpr unsigned Lightsteelblue = unsigned(0xffb0c4de);
	
	static constexpr unsigned Lightyellow = unsigned(0xffffffe0);
	
	static constexpr unsigned LtGray = unsigned(0xffc0c0c0);
	
	static constexpr unsigned MedGray = unsigned(0xffa0a0a0);
	
	static constexpr unsigned DkGray = unsigned(0xff808080);
	
	static constexpr unsigned MoneyGreen = unsigned(0xffc0dcc0);
	
	static constexpr unsigned LegacySkyBlue = unsigned(0xfff0caa6);
	
	static constexpr unsigned Cream = unsigned(0xfff0fbff);
	
	static constexpr unsigned Lime = unsigned(0xff00ff00);
	
	static constexpr unsigned Limegreen = unsigned(0xff32cd32);
	
	static constexpr unsigned Linen = unsigned(0xfffaf0e6);
	
	static constexpr unsigned Magenta = unsigned(0xffff00ff);
	
	static constexpr unsigned Maroon = unsigned(0xff800000);
	
	static constexpr unsigned Mediumaquamarine = unsigned(0xff66cdaa);
	
	static constexpr unsigned Mediumblue = unsigned(0xff0000cd);
	
	static constexpr unsigned Mediumorchid = unsigned(0xffba55d3);
	
	static constexpr unsigned Mediumpurple = unsigned(0xff9370db);
	
	static constexpr unsigned Mediumseagreen = unsigned(0xff3cb371);
	
	static constexpr unsigned Mediumslateblue = unsigned(0xff7b68ee);
	
	static constexpr unsigned Mediumspringgreen = unsigned(0xff00fa9a);
	
	static constexpr unsigned Mediumturquoise = unsigned(0xff48d1cc);
	
	static constexpr unsigned Mediumvioletred = unsigned(0xffc71585);
	
	static constexpr unsigned Midnightblue = unsigned(0xff191970);
	
	static constexpr unsigned Mintcream = unsigned(0xfff5fffa);
	
	static constexpr unsigned Mistyrose = unsigned(0xffffe4e1);
	
	static constexpr unsigned Moccasin = unsigned(0xffffe4b5);
	
	static constexpr unsigned Navajowhite = unsigned(0xffffdead);
	
	static constexpr unsigned Navy = unsigned(0xff000080);
	
	static constexpr unsigned Oldlace = unsigned(0xfffdf5e6);
	
	static constexpr unsigned Olive = unsigned(0xff808000);
	
	static constexpr unsigned Olivedrab = unsigned(0xff6b8e23);
	
	static constexpr unsigned Orange = unsigned(0xffffa500);
	
	static constexpr unsigned Orangered = unsigned(0xffff4500);
	
	static constexpr unsigned Orchid = unsigned(0xffda70d6);
	
	static constexpr unsigned Palegoldenrod = unsigned(0xffeee8aa);
	
	static constexpr unsigned Palegreen = unsigned(0xff98fb98);
	
	static constexpr unsigned Paleturquoise = unsigned(0xffafeeee);
	
	static constexpr unsigned Palevioletred = unsigned(0xffdb7093);
	
	static constexpr unsigned Papayawhip = unsigned(0xffffefd5);
	
	static constexpr unsigned Peachpuff = unsigned(0xffffdab9);
	
	static constexpr unsigned Peru = unsigned(0xffcd853f);
	
	static constexpr unsigned Pink = unsigned(0xffffc0cb);
	
	static constexpr unsigned Plum = unsigned(0xffdda0dd);
	
	static constexpr unsigned Powderblue = unsigned(0xffb0e0e6);
	
	static constexpr unsigned Purple = unsigned(0xff800080);
	
	static constexpr unsigned Red = unsigned(0xffff0000);
	
	static constexpr unsigned Rosybrown = unsigned(0xffbc8f8f);
	
	static constexpr unsigned Royalblue = unsigned(0xff4169e1);
	
	static constexpr unsigned Saddlebrown = unsigned(0xff8b4513);
	
	static constexpr unsigned Salmon = unsigned(0xfffa8072);
	
	static constexpr unsigned Sandybrown = unsigned(0xfff4a460);
	
	static constexpr unsigned Seagreen = unsigned(0xff2e8b57);
	
	static constexpr unsigned Seashell = unsigned(0xfffff5ee);
	
	static constexpr unsigned Sienna = unsigned(0xffa0522d);
	
	static constexpr unsigned Silver = unsigned(0xffc0c0c0);
	
	static constexpr unsigned Skyblue = unsigned(0xff87ceeb);
	
	static constexpr unsigned Slateblue = unsigned(0xff6a5acd);
	
	static constexpr unsigned Slategray = unsigned(0xff708090);
	
	static constexpr unsigned Slategrey = unsigned(0xff708090);
	
	static constexpr unsigned Snow = unsigned(0xfffffafa);
	
	static constexpr unsigned Springgreen = unsigned(0xff00ff7f);
	
	static constexpr unsigned Steelblue = unsigned(0xff4682b4);
	
	static constexpr unsigned Tan = unsigned(0xffd2b48c);
	
	static constexpr unsigned Teal = unsigned(0xff008080);
	
	static constexpr unsigned Thistle = unsigned(0xffd8bfd8);
	
	static constexpr unsigned Tomato = unsigned(0xffff6347);
	
	static constexpr unsigned Turquoise = unsigned(0xff40e0d0);
	
	static constexpr unsigned Violet = unsigned(0xffee82ee);
	
	static constexpr unsigned Wheat = unsigned(0xfff5deb3);
	
	static constexpr unsigned White = unsigned(0xffffffff);
	
	static constexpr unsigned Whitesmoke = unsigned(0xfff5f5f5);
	
	static constexpr unsigned Yellow = unsigned(0xffffff00);
	
	static constexpr unsigned Yellowgreen = unsigned(0xff9acd32);
	
	static constexpr TAlphaColor Null = TAlphaColor(0x0);
	
	__fastcall TAlphaColorRec(const TAlphaColor Color);
	static long __fastcall (*ColorToRGB)(TAlphaColor Color);
	TAlphaColorRec() {}
	
public:
	union
	{
		struct 
		{
			System::Byte B;
			System::Byte G;
			System::Byte R;
			System::Byte A;
		};
		struct 
		{
			System::Word HiWord;
			System::Word LoWord;
		};
		struct 
		{
			TAlphaColor Color;
		};
		
	};
};


typedef TAlphaColorRec TAlphaColors;

typedef TAlphaColorF *PAlphaColorF;

struct DECLSPEC_DRECORD TAlphaColorF
{
public:
	#define TAlphaColorF_Epsilon  (1.525900E-05)
	
	
private:
	static bool __fastcall SameComponent(const float Value1, const float Value2);
	static float __fastcall ClampComponent(const float Value);
	
public:
	float R;
	float G;
	float B;
	float A;
	static TAlphaColorF __fastcall Create(const float R, const float G, const float B, const float A = 1.000000E+00f)/* overload */;
	static TAlphaColorF __fastcall Create(const TAlphaColor Color)/* overload */;
	static TAlphaColorF __fastcall _op_Addition(const TAlphaColorF &Color1, const TAlphaColorF &Color2);
	static TAlphaColorF __fastcall _op_Subtraction(const TAlphaColorF &Color1, const TAlphaColorF &Color2);
	static bool __fastcall _op_Equality(const TAlphaColorF &Color1, const TAlphaColorF &Color2);
	static bool __fastcall _op_Inequality(const TAlphaColorF &Color1, const TAlphaColorF &Color2);
	static TAlphaColorF __fastcall _op_UnaryNegation(const TAlphaColorF &Color);
	static TAlphaColorF __fastcall _op_Multiply(const TAlphaColorF &Color1, const TAlphaColorF &Color2);
	static TAlphaColorF __fastcall _op_Multiply(const TAlphaColorF &Color, const float Factor);
	static TAlphaColorF __fastcall _op_Multiply(const float Factor, const TAlphaColorF &Color);
	static TAlphaColorF __fastcall _op_Division(const TAlphaColorF &Color, const float Factor);
	TAlphaColorF __fastcall PremultipliedAlpha();
	TAlphaColorF __fastcall UnpremultipliedAlpha();
	TAlphaColorF __fastcall Clamp();
	TAlphaColor __fastcall ToAlphaColor();
	
	friend TAlphaColorF operator +(const TAlphaColorF &Color1, const TAlphaColorF &Color2) { return TAlphaColorF::_op_Addition(Color1, Color2); }
	friend TAlphaColorF operator -(const TAlphaColorF &Color1, const TAlphaColorF &Color2) { return TAlphaColorF::_op_Subtraction(Color1, Color2); }
	friend bool operator ==(const TAlphaColorF &Color1, const TAlphaColorF &Color2) { return TAlphaColorF::_op_Equality(Color1, Color2); }
	friend bool operator !=(const TAlphaColorF &Color1, const TAlphaColorF &Color2) { return TAlphaColorF::_op_Inequality(Color1, Color2); }
	TAlphaColorF operator -() { return TAlphaColorF::_op_UnaryNegation(*this); }
	friend TAlphaColorF operator *(const TAlphaColorF &Color1, const TAlphaColorF &Color2) { return TAlphaColorF::_op_Multiply(Color1, Color2); }
	friend TAlphaColorF operator *(const TAlphaColorF &Color, const float Factor) { return TAlphaColorF::_op_Multiply(Color, Factor); }
	friend TAlphaColorF operator *(const float Factor, const TAlphaColorF &Color) { return TAlphaColorF::_op_Multiply(Factor, Color); }
	friend TAlphaColorF operator /(const TAlphaColorF &Color, const float Factor) { return TAlphaColorF::_op_Division(Color, Factor); }
};


_DECLARE_ARITH_TYPE_ALIAS(int, TImageIndex);

_DECLARE_STRING_TYPE_ALIAS(System::UnicodeString, TImageName);

enum class DECLSPEC_DENUM TScrollStyle : unsigned char { ssNone, ssHorizontal, ssVertical, ssBoth };

enum DECLSPEC_DENUM System_Uitypes__1 : unsigned char { ttVertical, ttHorizontal };

typedef System::Set<System_Uitypes__1, System_Uitypes__1::ttVertical, System_Uitypes__1::ttHorizontal> TTouchTracking;

//-- var, const, procedure ---------------------------------------------------
static constexpr TCursor crDefault = TCursor(0);
static constexpr TCursor crNone = TCursor(-1);
static constexpr TCursor crArrow = TCursor(-2);
static constexpr TCursor crCross = TCursor(-3);
static constexpr TCursor crIBeam = TCursor(-4);
static constexpr TCursor crSize = TCursor(-22);
static constexpr TCursor crSizeNESW = TCursor(-6);
static constexpr TCursor crSizeNS = TCursor(-7);
static constexpr TCursor crSizeNWSE = TCursor(-8);
static constexpr TCursor crSizeWE = TCursor(-9);
static constexpr TCursor crUpArrow = TCursor(-10);
static constexpr TCursor crHourGlass = TCursor(-11);
static constexpr TCursor crDrag = TCursor(-12);
static constexpr TCursor crNoDrop = TCursor(-13);
static constexpr TCursor crHSplit = TCursor(-14);
static constexpr TCursor crVSplit = TCursor(-15);
static constexpr TCursor crMultiDrag = TCursor(-16);
static constexpr TCursor crSQLWait = TCursor(-17);
static constexpr TCursor crNo = TCursor(-18);
static constexpr TCursor crAppStart = TCursor(-19);
static constexpr TCursor crHelp = TCursor(-20);
static constexpr TCursor crHandPoint = TCursor(-21);
static constexpr TCursor crSizeAll = TCursor(-22);
static constexpr System::Int8 idOK = System::Int8(0x1);
static constexpr System::Int8 idCancel = System::Int8(0x2);
static constexpr System::Int8 idAbort = System::Int8(0x3);
static constexpr System::Int8 idRetry = System::Int8(0x4);
static constexpr System::Int8 idIgnore = System::Int8(0x5);
static constexpr System::Int8 idYes = System::Int8(0x6);
static constexpr System::Int8 idNo = System::Int8(0x7);
static constexpr System::Int8 idClose = System::Int8(0x8);
static constexpr System::Int8 idHelp = System::Int8(0x9);
static constexpr System::Int8 idTryAgain = System::Int8(0xa);
static constexpr System::Int8 idContinue = System::Int8(0xb);
static constexpr System::Int8 mrNone = System::Int8(0x0);
static constexpr System::Int8 mrOk = System::Int8(0x1);
static constexpr System::Int8 mrCancel = System::Int8(0x2);
static constexpr System::Int8 mrAbort = System::Int8(0x3);
static constexpr System::Int8 mrRetry = System::Int8(0x4);
static constexpr System::Int8 mrIgnore = System::Int8(0x5);
static constexpr System::Int8 mrYes = System::Int8(0x6);
static constexpr System::Int8 mrNo = System::Int8(0x7);
static constexpr System::Int8 mrClose = System::Int8(0x8);
static constexpr System::Int8 mrHelp = System::Int8(0x9);
static constexpr System::Int8 mrTryAgain = System::Int8(0xa);
static constexpr System::Int8 mrContinue = System::Int8(0xb);
static constexpr System::Int8 mrAll = System::Int8(0xc);
static constexpr System::Int8 mrNoToAll = System::Int8(0xd);
static constexpr System::Int8 mrYesToAll = System::Int8(0xe);
static constexpr System::Int8 vkLButton = System::Int8(0x1);
static constexpr System::Int8 vkRButton = System::Int8(0x2);
static constexpr System::Int8 vkCancel = System::Int8(0x3);
static constexpr System::Int8 vkMButton = System::Int8(0x4);
static constexpr System::Int8 vkXButton1 = System::Int8(0x5);
static constexpr System::Int8 vkXButton2 = System::Int8(0x6);
static constexpr System::Int8 vkBack = System::Int8(0x8);
static constexpr System::Int8 vkTab = System::Int8(0x9);
static constexpr System::Int8 vkLineFeed = System::Int8(0xa);
static constexpr System::Int8 vkClear = System::Int8(0xc);
static constexpr System::Int8 vkReturn = System::Int8(0xd);
static constexpr System::Int8 vkShift = System::Int8(0x10);
static constexpr System::Int8 vkControl = System::Int8(0x11);
static constexpr System::Int8 vkMenu = System::Int8(0x12);
static constexpr System::Int8 vkPause = System::Int8(0x13);
static constexpr System::Int8 vkCapital = System::Int8(0x14);
static constexpr System::Int8 vkKana = System::Int8(0x15);
static constexpr System::Int8 vkHangul = System::Int8(0x15);
static constexpr System::Int8 vkJunja = System::Int8(0x17);
static constexpr System::Int8 vkFinal = System::Int8(0x18);
static constexpr System::Int8 vkHanja = System::Int8(0x19);
static constexpr System::Int8 vkKanji = System::Int8(0x19);
static constexpr System::Int8 vkConvert = System::Int8(0x1c);
static constexpr System::Int8 vkNonConvert = System::Int8(0x1d);
static constexpr System::Int8 vkAccept = System::Int8(0x1e);
static constexpr System::Int8 vkModeChange = System::Int8(0x1f);
static constexpr System::Int8 vkEscape = System::Int8(0x1b);
static constexpr System::Int8 vkSpace = System::Int8(0x20);
static constexpr System::Int8 vkPrior = System::Int8(0x21);
static constexpr System::Int8 vkNext = System::Int8(0x22);
static constexpr System::Int8 vkEnd = System::Int8(0x23);
static constexpr System::Int8 vkHome = System::Int8(0x24);
static constexpr System::Int8 vkLeft = System::Int8(0x25);
static constexpr System::Int8 vkUp = System::Int8(0x26);
static constexpr System::Int8 vkRight = System::Int8(0x27);
static constexpr System::Int8 vkDown = System::Int8(0x28);
static constexpr System::Int8 vkSelect = System::Int8(0x29);
static constexpr System::Int8 vkPrint = System::Int8(0x2a);
static constexpr System::Int8 vkExecute = System::Int8(0x2b);
static constexpr System::Int8 vkSnapshot = System::Int8(0x2c);
static constexpr System::Int8 vkInsert = System::Int8(0x2d);
static constexpr System::Int8 vkDelete = System::Int8(0x2e);
static constexpr System::Int8 vkHelp = System::Int8(0x2f);
static constexpr System::Int8 vk0 = System::Int8(0x30);
static constexpr System::Int8 vk1 = System::Int8(0x31);
static constexpr System::Int8 vk2 = System::Int8(0x32);
static constexpr System::Int8 vk3 = System::Int8(0x33);
static constexpr System::Int8 vk4 = System::Int8(0x34);
static constexpr System::Int8 vk5 = System::Int8(0x35);
static constexpr System::Int8 vk6 = System::Int8(0x36);
static constexpr System::Int8 vk7 = System::Int8(0x37);
static constexpr System::Int8 vk8 = System::Int8(0x38);
static constexpr System::Int8 vk9 = System::Int8(0x39);
static constexpr System::Int8 vkA = System::Int8(0x41);
static constexpr System::Int8 vkB = System::Int8(0x42);
static constexpr System::Int8 vkC = System::Int8(0x43);
static constexpr System::Int8 vkD = System::Int8(0x44);
static constexpr System::Int8 vkE = System::Int8(0x45);
static constexpr System::Int8 vkF = System::Int8(0x46);
static constexpr System::Int8 vkG = System::Int8(0x47);
static constexpr System::Int8 vkH = System::Int8(0x48);
static constexpr System::Int8 vkI = System::Int8(0x49);
static constexpr System::Int8 vkJ = System::Int8(0x4a);
static constexpr System::Int8 vkK = System::Int8(0x4b);
static constexpr System::Int8 vkL = System::Int8(0x4c);
static constexpr System::Int8 vkM = System::Int8(0x4d);
static constexpr System::Int8 vkN = System::Int8(0x4e);
static constexpr System::Int8 vkO = System::Int8(0x4f);
static constexpr System::Int8 vkP = System::Int8(0x50);
static constexpr System::Int8 vkQ = System::Int8(0x51);
static constexpr System::Int8 vkR = System::Int8(0x52);
static constexpr System::Int8 vkS = System::Int8(0x53);
static constexpr System::Int8 vkT = System::Int8(0x54);
static constexpr System::Int8 vkU = System::Int8(0x55);
static constexpr System::Int8 vkV = System::Int8(0x56);
static constexpr System::Int8 vkW = System::Int8(0x57);
static constexpr System::Int8 vkX = System::Int8(0x58);
static constexpr System::Int8 vkY = System::Int8(0x59);
static constexpr System::Int8 vkZ = System::Int8(0x5a);
static constexpr System::Int8 vkLWin = System::Int8(0x5b);
static constexpr System::Int8 vkRWin = System::Int8(0x5c);
static constexpr System::Int8 vkApps = System::Int8(0x5d);
static constexpr System::Int8 vkSleep = System::Int8(0x5f);
static constexpr System::Int8 vkNumpad0 = System::Int8(0x60);
static constexpr System::Int8 vkNumpad1 = System::Int8(0x61);
static constexpr System::Int8 vkNumpad2 = System::Int8(0x62);
static constexpr System::Int8 vkNumpad3 = System::Int8(0x63);
static constexpr System::Int8 vkNumpad4 = System::Int8(0x64);
static constexpr System::Int8 vkNumpad5 = System::Int8(0x65);
static constexpr System::Int8 vkNumpad6 = System::Int8(0x66);
static constexpr System::Int8 vkNumpad7 = System::Int8(0x67);
static constexpr System::Int8 vkNumpad8 = System::Int8(0x68);
static constexpr System::Int8 vkNumpad9 = System::Int8(0x69);
static constexpr System::Int8 vkMultiply = System::Int8(0x6a);
static constexpr System::Int8 vkAdd = System::Int8(0x6b);
static constexpr System::Int8 vkSeparator = System::Int8(0x6c);
static constexpr System::Int8 vkSubtract = System::Int8(0x6d);
static constexpr System::Int8 vkDecimal = System::Int8(0x6e);
static constexpr System::Int8 vkDivide = System::Int8(0x6f);
static constexpr System::Int8 vkF1 = System::Int8(0x70);
static constexpr System::Int8 vkF2 = System::Int8(0x71);
static constexpr System::Int8 vkF3 = System::Int8(0x72);
static constexpr System::Int8 vkF4 = System::Int8(0x73);
static constexpr System::Int8 vkF5 = System::Int8(0x74);
static constexpr System::Int8 vkF6 = System::Int8(0x75);
static constexpr System::Int8 vkF7 = System::Int8(0x76);
static constexpr System::Int8 vkF8 = System::Int8(0x77);
static constexpr System::Int8 vkF9 = System::Int8(0x78);
static constexpr System::Int8 vkF10 = System::Int8(0x79);
static constexpr System::Int8 vkF11 = System::Int8(0x7a);
static constexpr System::Int8 vkF12 = System::Int8(0x7b);
static constexpr System::Int8 vkF13 = System::Int8(0x7c);
static constexpr System::Int8 vkF14 = System::Int8(0x7d);
static constexpr System::Int8 vkF15 = System::Int8(0x7e);
static constexpr System::Int8 vkF16 = System::Int8(0x7f);
static constexpr System::Byte vkF17 = System::Byte(0x80);
static constexpr System::Byte vkF18 = System::Byte(0x81);
static constexpr System::Byte vkF19 = System::Byte(0x82);
static constexpr System::Byte vkF20 = System::Byte(0x83);
static constexpr System::Byte vkF21 = System::Byte(0x84);
static constexpr System::Byte vkF22 = System::Byte(0x85);
static constexpr System::Byte vkF23 = System::Byte(0x86);
static constexpr System::Byte vkF24 = System::Byte(0x87);
static constexpr System::Byte vkCamera = System::Byte(0x88);
static constexpr System::Byte vkHardwareBack = System::Byte(0x89);
static constexpr System::Byte vkNumLock = System::Byte(0x90);
static constexpr System::Byte vkScroll = System::Byte(0x91);
static constexpr System::Byte vkLShift = System::Byte(0xa0);
static constexpr System::Byte vkRShift = System::Byte(0xa1);
static constexpr System::Byte vkLControl = System::Byte(0xa2);
static constexpr System::Byte vkRControl = System::Byte(0xa3);
static constexpr System::Byte vkLMenu = System::Byte(0xa4);
static constexpr System::Byte vkRMenu = System::Byte(0xa5);
static constexpr System::Byte vkBrowserBack = System::Byte(0xa6);
static constexpr System::Byte vkBrowserForward = System::Byte(0xa7);
static constexpr System::Byte vkBrowserRefresh = System::Byte(0xa8);
static constexpr System::Byte vkBrowserStop = System::Byte(0xa9);
static constexpr System::Byte vkBrowserSearch = System::Byte(0xaa);
static constexpr System::Byte vkBrowserFavorites = System::Byte(0xab);
static constexpr System::Byte vkBrowserHome = System::Byte(0xac);
static constexpr System::Byte vkVolumeMute = System::Byte(0xad);
static constexpr System::Byte vkVolumeDown = System::Byte(0xae);
static constexpr System::Byte vkVolumeUp = System::Byte(0xaf);
static constexpr System::Byte vkMediaNextTrack = System::Byte(0xb0);
static constexpr System::Byte vkMediaPrevTrack = System::Byte(0xb1);
static constexpr System::Byte vkMediaStop = System::Byte(0xb2);
static constexpr System::Byte vkMediaPlayPause = System::Byte(0xb3);
static constexpr System::Byte vkLaunchMail = System::Byte(0xb4);
static constexpr System::Byte vkLaunchMediaSelect = System::Byte(0xb5);
static constexpr System::Byte vkLaunchApp1 = System::Byte(0xb6);
static constexpr System::Byte vkLaunchApp2 = System::Byte(0xb7);
static constexpr System::Byte vkSemicolon = System::Byte(0xba);
static constexpr System::Byte vkEqual = System::Byte(0xbb);
static constexpr System::Byte vkComma = System::Byte(0xbc);
static constexpr System::Byte vkMinus = System::Byte(0xbd);
static constexpr System::Byte vkPeriod = System::Byte(0xbe);
static constexpr System::Byte vkSlash = System::Byte(0xbf);
static constexpr System::Byte vkTilde = System::Byte(0xc0);
static constexpr System::Byte vkLeftBracket = System::Byte(0xdb);
static constexpr System::Byte vkBackslash = System::Byte(0xdc);
static constexpr System::Byte vkRightBracket = System::Byte(0xdd);
static constexpr System::Byte vkQuote = System::Byte(0xde);
static constexpr System::Byte vkPara = System::Byte(0xdf);
static constexpr System::Byte vkOem102 = System::Byte(0xe2);
static constexpr System::Byte vkIcoHelp = System::Byte(0xe3);
static constexpr System::Byte vkIco00 = System::Byte(0xe4);
static constexpr System::Byte vkProcessKey = System::Byte(0xe5);
static constexpr System::Byte vkIcoClear = System::Byte(0xe6);
static constexpr System::Byte vkPacket = System::Byte(0xe7);
static constexpr System::Byte vkAttn = System::Byte(0xf6);
static constexpr System::Byte vkCrsel = System::Byte(0xf7);
static constexpr System::Byte vkExsel = System::Byte(0xf8);
static constexpr System::Byte vkErEof = System::Byte(0xf9);
static constexpr System::Byte vkPlay = System::Byte(0xfa);
static constexpr System::Byte vkZoom = System::Byte(0xfb);
static constexpr System::Byte vkNoname = System::Byte(0xfc);
static constexpr System::Byte vkPA1 = System::Byte(0xfd);
static constexpr System::Byte vkOemClear = System::Byte(0xfe);
static constexpr System::Byte vkNone = System::Byte(0xff);
static constexpr System::Int8 sgiNoGesture = System::Int8(0x0);
static constexpr System::Int8 sgiLeft = System::Int8(0x1);
static constexpr System::Int8 sgiRight = System::Int8(0x2);
static constexpr System::Int8 sgiUp = System::Int8(0x3);
static constexpr System::Int8 sgiDown = System::Int8(0x4);
static constexpr System::Int8 sgiUpLeft = System::Int8(0x5);
static constexpr System::Int8 sgiUpRight = System::Int8(0x6);
static constexpr System::Int8 sgiDownLeft = System::Int8(0x7);
static constexpr System::Int8 sgiDownRight = System::Int8(0x8);
static constexpr System::Int8 sgiLeftUp = System::Int8(0x9);
static constexpr System::Int8 sgiLeftDown = System::Int8(0xa);
static constexpr System::Int8 sgiRightUp = System::Int8(0xb);
static constexpr System::Int8 sgiRightDown = System::Int8(0xc);
static constexpr System::Int8 sgiUpDown = System::Int8(0xd);
static constexpr System::Int8 sgiDownUp = System::Int8(0xe);
static constexpr System::Int8 sgiLeftRight = System::Int8(0xf);
static constexpr System::Int8 sgiRightLeft = System::Int8(0x10);
static constexpr System::Int8 sgiUpLeftLong = System::Int8(0x11);
static constexpr System::Int8 sgiUpRightLong = System::Int8(0x12);
static constexpr System::Int8 sgiDownLeftLong = System::Int8(0x13);
static constexpr System::Int8 sgiDownRightLong = System::Int8(0x14);
static constexpr System::Int8 sgiScratchout = System::Int8(0x15);
static constexpr System::Int8 sgiTriangle = System::Int8(0x16);
static constexpr System::Int8 sgiSquare = System::Int8(0x17);
static constexpr System::Int8 sgiCheck = System::Int8(0x18);
static constexpr System::Int8 sgiCurlicue = System::Int8(0x19);
static constexpr System::Int8 sgiDoubleCurlicue = System::Int8(0x1a);
static constexpr System::Int8 sgiCircle = System::Int8(0x1b);
static constexpr System::Int8 sgiDoubleCircle = System::Int8(0x1c);
static constexpr System::Int8 sgiSemiCircleLeft = System::Int8(0x1d);
static constexpr System::Int8 sgiSemiCircleRight = System::Int8(0x1e);
static constexpr System::Int8 sgiChevronUp = System::Int8(0x1f);
static constexpr System::Int8 sgiChevronDown = System::Int8(0x20);
static constexpr System::Int8 sgiChevronLeft = System::Int8(0x21);
static constexpr System::Int8 sgiChevronRight = System::Int8(0x22);
static constexpr System::Int8 sgiFirst = System::Int8(0x1);
static constexpr System::Int8 sgiLast = System::Int8(0x22);
static constexpr short cgiFirst = short(-512);
static constexpr System::Int8 cgiLast = System::Int8(-1);
static constexpr short rgiFirst = short(-1024);
static constexpr short rgiLast = short(-513);
static constexpr System::Word igiFirst = System::Word(0x100);
static constexpr System::Word igiLast = System::Word(0x1ff);
static constexpr System::Word igiBegin = System::Word(0x101);
static constexpr System::Word igiEnd = System::Word(0x102);
static constexpr System::Word igiZoom = System::Word(0x103);
static constexpr System::Word igiPan = System::Word(0x104);
static constexpr System::Word igiRotate = System::Word(0x105);
static constexpr System::Word igiTwoFingerTap = System::Word(0x106);
static constexpr System::Word igiPressAndTap = System::Word(0x107);
static constexpr System::Word igiLongTap = System::Word(0x108);
static constexpr System::Word igiDoubleTap = System::Word(0x109);
extern DELPHI_PACKAGE bool __fastcall IsPositiveResult(const TModalResult AModalResult);
extern DELPHI_PACKAGE bool __fastcall IsNegativeResult(const TModalResult AModalResult);
extern DELPHI_PACKAGE bool __fastcall IsAbortResult(const TModalResult AModalResult);
extern DELPHI_PACKAGE bool __fastcall IsAnAllResult(const TModalResult AModalResult);
extern DELPHI_PACKAGE TModalResult __fastcall StripAllFromResult(const TModalResult AModalResult);
}	/* namespace Uitypes */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_UITYPES)
using namespace System::Uitypes;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif

//-- user supplied -----------------------------------------------------------
#include <SystemUITypes.h> 

#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_UitypesHPP
