// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.MLang.pas' rev: 34.00 (Windows)

#ifndef Winapi_MlangHPP
#define Winapi_MlangHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.ActiveX.hpp>

//-- user supplied -----------------------------------------------------------

#include <MLang.h>

DECLARE_DINTERFACE_TYPE(IMLangStringBufW);
DECLARE_DINTERFACE_TYPE(IMLangStringBufA);
DECLARE_DINTERFACE_TYPE(IMLangString);
DECLARE_DINTERFACE_TYPE(IMLangStringWStr);
DECLARE_DINTERFACE_TYPE(IMLangStringAStr);
DECLARE_DINTERFACE_TYPE(IMLangLineBreakConsole);
DECLARE_DINTERFACE_TYPE(IEnumCodePage);
DECLARE_DINTERFACE_TYPE(IEnumRfc1766);
DECLARE_DINTERFACE_TYPE(IEnumScript);
DECLARE_DINTERFACE_TYPE(IMLangConvertCharset);
DECLARE_DINTERFACE_TYPE(IMultiLanguage);
DECLARE_DINTERFACE_TYPE(IMultiLanguage2);
DECLARE_DINTERFACE_TYPE(IMLangCodePages);
DECLARE_DINTERFACE_TYPE(IMLangFontLink);
DECLARE_DINTERFACE_TYPE(IMLangFontLink2);
DECLARE_DINTERFACE_TYPE(IMultiLanguage3);

namespace Winapi
{
namespace Mlang
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IMLangStringBufW;
typedef System::DelphiInterface<IMLangStringBufW> _di_IMLangStringBufW;
__interface DELPHIINTERFACE IMLangStringBufA;
typedef System::DelphiInterface<IMLangStringBufA> _di_IMLangStringBufA;
__interface DELPHIINTERFACE IMLangString;
typedef System::DelphiInterface<IMLangString> _di_IMLangString;
__interface DELPHIINTERFACE IMLangStringWStr;
typedef System::DelphiInterface<IMLangStringWStr> _di_IMLangStringWStr;
__interface DELPHIINTERFACE IMLangStringAStr;
typedef System::DelphiInterface<IMLangStringAStr> _di_IMLangStringAStr;
__interface DELPHIINTERFACE IMLangLineBreakConsole;
typedef System::DelphiInterface<IMLangLineBreakConsole> _di_IMLangLineBreakConsole;
__interface DELPHIINTERFACE IEnumCodePage;
typedef System::DelphiInterface<IEnumCodePage> _di_IEnumCodePage;
__interface DELPHIINTERFACE IEnumRfc1766;
typedef System::DelphiInterface<IEnumRfc1766> _di_IEnumRfc1766;
__interface DELPHIINTERFACE IEnumScript;
typedef System::DelphiInterface<IEnumScript> _di_IEnumScript;
__interface DELPHIINTERFACE IMLangConvertCharset;
typedef System::DelphiInterface<IMLangConvertCharset> _di_IMLangConvertCharset;
__interface DELPHIINTERFACE IMultiLanguage;
typedef System::DelphiInterface<IMultiLanguage> _di_IMultiLanguage;
__interface DELPHIINTERFACE IMultiLanguage2;
typedef System::DelphiInterface<IMultiLanguage2> _di_IMultiLanguage2;
__interface DELPHIINTERFACE IMLangCodePages;
typedef System::DelphiInterface<IMLangCodePages> _di_IMLangCodePages;
__interface DELPHIINTERFACE IMLangFontLink;
typedef System::DelphiInterface<IMLangFontLink> _di_IMLangFontLink;
__interface DELPHIINTERFACE IMLangFontLink2;
typedef System::DelphiInterface<IMLangFontLink2> _di_IMLangFontLink2;
__interface DELPHIINTERFACE IMultiLanguage3;
typedef System::DelphiInterface<IMultiLanguage3> _di_IMultiLanguage3;
class DELPHICLASS CoCMLangString;
class DELPHICLASS CoCMLangConvertCharset;
class DELPHICLASS CoCMultiLanguage;
class DELPHICLASS CoCMultiLanguage2;
class DELPHICLASS CoCMultiLanguage3;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{D24ACD21-BA72-11D0-B188-00AA0038C969}") IMLangStringBufW  : public System::IInterface 
{
	virtual HRESULT __stdcall GetStatus(/* out */ int &plFlags, /* out */ int &pcchBuf) = 0 ;
	virtual HRESULT __stdcall LockBuf(int cchOffset, int cchMaxLock, /* out */ System::WideChar * &ppszBuf, /* out */ int &pcchBuf) = 0 ;
	virtual HRESULT __stdcall UnlockBuf(PWORD pszBuf, int cchOffset, int cchWrite) = 0 ;
	virtual HRESULT __stdcall Insert(int cchOffset, int cchMaxInsert, /* out */ int &pcchActual) = 0 ;
	virtual HRESULT __stdcall Delete(int cchOffset, int cchDelete) = 0 ;
};

__interface  INTERFACE_UUID("{D24ACD23-BA72-11D0-B188-00AA0038C969}") IMLangStringBufA  : public System::IInterface 
{
	virtual HRESULT __stdcall GetStatus(/* out */ int &plFlags, /* out */ int &pcchBuf) = 0 ;
	virtual HRESULT __stdcall LockBuf(int cchOffset, int cchMaxLock, /* out */ char * &ppszBuf, /* out */ int &pcchBuf) = 0 ;
	virtual HRESULT __stdcall UnlockBuf(System::PByte pszBuf, int cchOffset, int cchWrite) = 0 ;
	virtual HRESULT __stdcall Insert(int cchOffset, int cchMaxInsert, /* out */ int &pcchActual) = 0 ;
	virtual HRESULT __stdcall Delete(int cchOffset, int cchDelete) = 0 ;
};

__interface  INTERFACE_UUID("{C04D65CE-B70D-11D0-B188-00AA0038C969}") IMLangString  : public System::IInterface 
{
	virtual HRESULT __stdcall Sync(int fNoAccess) = 0 ;
	virtual HRESULT __stdcall GetLength(/* out */ int &plLen) = 0 ;
	virtual HRESULT __stdcall SetMLStr(int lDestPos, int lDestLen, const System::_di_IInterface pSrcMLStr, int lSrcPos, int lSrcLen) = 0 ;
	virtual HRESULT __stdcall GetMLStr(int lSrcPos, int lSrcLen, const System::_di_IInterface pUnkOuter, unsigned dwClsContext, GUID &piid, /* out */ System::_di_IInterface &ppDestMLStr, /* out */ int &plDestPos, /* out */ int &plDestLen) = 0 ;
};

__interface  INTERFACE_UUID("{C04D65D0-B70D-11D0-B188-00AA0038C969}") IMLangStringWStr  : public IMLangString 
{
	virtual HRESULT __stdcall SetWStr(int lDestPos, int lDestLen, System::WideChar * pszSrc, int cchSrc, /* out */ int &pcchActual, /* out */ int &plActualLen) = 0 ;
	virtual HRESULT __stdcall SetStrBufW(int lDestPos, int lDestLen, const _di_IMLangStringBufW pSrcBuf, /* out */ int &pcchActual, /* out */ int &plActualLen) = 0 ;
	virtual HRESULT __stdcall GetWStr(int lSrcPos, int lSrcLen, System::WideChar * pszDest, int cchDest, /* out */ int &pcchActual, /* out */ int &plActualLen) = 0 ;
	virtual HRESULT __stdcall GetStrBufW(int lSrcPos, int lSrcMaxLen, /* out */ _di_IMLangStringBufW &ppDestBuf, /* out */ int &plDestLen) = 0 ;
	virtual HRESULT __stdcall LockWStr(int lSrcPos, int lSrcLen, int lFlags, int cchRequest, /* out */ System::WideChar * &ppszDest, /* out */ int &pcchDest, /* out */ int &plDestLen) = 0 ;
	virtual HRESULT __stdcall UnlockWStr(System::WideChar * pszSrc, int cchSrc, /* out */ int &pcchActual, /* out */ int &plActualLen) = 0 ;
	virtual HRESULT __stdcall SetLocale(int lDestPos, int lDestLen, unsigned locale) = 0 ;
	virtual HRESULT __stdcall GetLocale(int lSrcPos, int lSrcMaxLen, /* out */ unsigned &plocale, /* out */ int &plLocalePos, /* out */ int &plLocaleLen) = 0 ;
};

__interface  INTERFACE_UUID("{C04D65D2-B70D-11D0-B188-00AA0038C969}") IMLangStringAStr  : public IMLangString 
{
	virtual HRESULT __stdcall SetAStr(int lDestPos, int lDestLen, unsigned uCodePage, char * pszSrc, int cchSrc, /* out */ int &pcchActual, /* out */ int &plActualLen) = 0 ;
	virtual HRESULT __stdcall SetStrBufA(int lDestPos, int lDestLen, unsigned uCodePage, const _di_IMLangStringBufA pSrcBuf, /* out */ int &pcchActual, /* out */ int &plActualLen) = 0 ;
	virtual HRESULT __stdcall GetAStr(int lSrcPos, int lSrcLen, unsigned uCodePageIn, /* out */ unsigned &puCodePageOut, char * pszDest, int cchDest, /* out */ int &pcchActual, /* out */ int &plActualLen) = 0 ;
	virtual HRESULT __stdcall GetStrBufA(int lSrcPos, int lSrcMaxLen, /* out */ unsigned &puDestCodePage, /* out */ _di_IMLangStringBufA &ppDestBuf, /* out */ int &plDestLen) = 0 ;
	virtual HRESULT __stdcall LockAStr(int lSrcPos, int lSrcLen, int lFlags, unsigned uCodePageIn, int cchRequest, /* out */ unsigned &puCodePageOut, /* out */ char * &ppszDest, /* out */ int &pcchDest, /* out */ int &plDestLen) = 0 ;
	virtual HRESULT __stdcall UnlockAStr(char * pszSrc, int cchSrc, /* out */ int &pcchActual, /* out */ int &plActualLen) = 0 ;
	virtual HRESULT __stdcall SetLocale(int lDestPos, int lDestLen, unsigned locale) = 0 ;
	virtual HRESULT __stdcall GetLocale(int lSrcPos, int lSrcMaxLen, /* out */ unsigned &plocale, /* out */ int &plLocalePos, /* out */ int &plLocaleLen) = 0 ;
};

__interface  INTERFACE_UUID("{F5BE2EE1-BFD7-11D0-B188-00AA0038C969}") IMLangLineBreakConsole  : public System::IInterface 
{
	virtual HRESULT __stdcall BreakLineML(const _di_IMLangString pSrcMLStr, int lSrcPos, int lSrcLen, int cMinColumns, int cMaxColumns, /* out */ int &plLineLen, /* out */ int &plSkipLen) = 0 ;
	virtual HRESULT __stdcall BreakLineW(unsigned locale, System::WideChar * pszSrc, int cchSrc, int cMaxColumns, /* out */ int &pcchLine, /* out */ int &pcchSkip) = 0 ;
	virtual HRESULT __stdcall BreakLineA(unsigned locale, unsigned uCodePage, char * pszSrc, int cchSrc, int cMaxColumns, /* out */ int &pcchLine, /* out */ int &pcchSkip) = 0 ;
};

typedef tagMIMECPINFO *PMimeCPInfo;

typedef tagMIMECPINFO TMimeCPInfo;

typedef tagMIMECSETINFO *PMimeCsetInfo;

typedef tagMIMECSETINFO TMimeCsetInfo;

__interface  INTERFACE_UUID("{275C23E3-3747-11D0-9FEA-00AA003F8646}") IEnumCodePage  : public System::IInterface 
{
	virtual HRESULT __stdcall Clone(/* out */ _di_IEnumCodePage &ppEnum) = 0 ;
	virtual HRESULT __stdcall Next(unsigned celt, /* out */ tagMIMECPINFO &rgelt, /* out */ unsigned &pceltFetched) = 0 ;
	virtual HRESULT __stdcall Reset() = 0 ;
	virtual HRESULT __stdcall Skip(unsigned celt) = 0 ;
};

typedef tagRFC1766INFO *PRFC1766Info;

typedef tagRFC1766INFO TRFC1766Info;

__interface  INTERFACE_UUID("{3DC39D1D-C030-11D0-B81B-00C04FC9B31F}") IEnumRfc1766  : public System::IInterface 
{
	virtual HRESULT __stdcall Clone(/* out */ _di_IEnumRfc1766 &ppEnum) = 0 ;
	virtual HRESULT __stdcall Next(unsigned celt, /* out */ tagRFC1766INFO &rgelt, /* out */ unsigned &pceltFetched) = 0 ;
	virtual HRESULT __stdcall Reset() = 0 ;
	virtual HRESULT __stdcall Skip(unsigned celt) = 0 ;
};

typedef System::Byte TScriptID;

typedef __int64 TScriptIDs;

typedef tagSCRIPTINFO TScriptInfo;

__interface  INTERFACE_UUID("{AE5F1430-388B-11D2-8380-00C04F8F5DA1}") IEnumScript  : public System::IInterface 
{
	virtual HRESULT __stdcall Clone(/* out */ _di_IEnumScript &ppEnum) = 0 ;
	virtual HRESULT __stdcall Next(unsigned celt, /* out */ tagSCRIPTINFO &rgelt, /* out */ unsigned &pceltFetched) = 0 ;
	virtual HRESULT __stdcall Reset() = 0 ;
	virtual HRESULT __stdcall Skip(unsigned celt) = 0 ;
};

__interface  INTERFACE_UUID("{D66D6F98-CDAA-11D0-B822-00C04FC9B31F}") IMLangConvertCharset  : public System::IInterface 
{
	virtual HRESULT __stdcall Initialize(unsigned uiSrcCodePage, unsigned uiDstCodePage, unsigned dwProperty) = 0 ;
	virtual HRESULT __stdcall GetSourceCodePage(/* out */ unsigned &puiSrcCodePage) = 0 ;
	virtual HRESULT __stdcall GetDestinationCodePage(/* out */ unsigned &puiDstCodePage) = 0 ;
	virtual HRESULT __stdcall GetProperty(/* out */ unsigned &pdwProperty) = 0 ;
	virtual HRESULT __stdcall DoConversion(void * pSrcStr, PUINT pcSrcSize, void * pDstStr, unsigned &pcDstSize) = 0 ;
	virtual HRESULT __stdcall DoConversionToUnicode(void * pSrcStr, PUINT pcSrcSize, System::WideChar * pDstStr, unsigned &pcDstSize) = 0 ;
	virtual HRESULT __stdcall DoConversionFromUnicode(System::WideChar * pSrcStr, PUINT pcSrcSize, void * pDstStr, unsigned &pcDstSize) = 0 ;
};

__interface  INTERFACE_UUID("{275C23E1-3747-11D0-9FEA-00AA003F8646}") IMultiLanguage  : public System::IInterface 
{
	virtual HRESULT __stdcall GetNumberOfCodePageInfo(/* out */ unsigned &pcCodePage) = 0 ;
	virtual HRESULT __stdcall GetCodePageInfo(unsigned uiCodePage, /* out */ tagMIMECPINFO &pCodePageInfo) = 0 ;
	virtual HRESULT __stdcall GetFamilyCodePage(unsigned uiCodePage, /* out */ unsigned &puiFamilyCodePage) = 0 ;
	virtual HRESULT __stdcall EnumCodePages(unsigned grfFlags, /* out */ _di_IEnumCodePage &ppEnumCodePage) = 0 ;
	virtual HRESULT __stdcall GetCharsetInfo(const System::WideString Charset, /* out */ tagMIMECSETINFO &pCharsetInfo) = 0 ;
	virtual HRESULT __stdcall IsConvertible(unsigned dwSrcEncoding, unsigned dwDstEncoding) = 0 ;
	virtual HRESULT __stdcall ConvertString(unsigned &pdwMode, unsigned dwSrcEncoding, unsigned dwDstEncoding, void * pSrcStr, PUINT pcSrcSize, void * pDstStr, unsigned &pcDstSize) = 0 ;
	virtual HRESULT __stdcall ConvertStringToUnicode(unsigned &pdwMode, unsigned dwEncoding, void * pSrcStr, PUINT pcSrcSize, System::WideChar * pDstStr, unsigned &pcDstSize) = 0 ;
	virtual HRESULT __stdcall ConvertStringFromUnicode(unsigned &pdwMode, unsigned dwEncoding, System::WideChar * pSrcStr, PUINT pcSrcSize, void * pDstStr, unsigned &pcDstSize) = 0 ;
	virtual HRESULT __stdcall ConvertStringReset() = 0 ;
	virtual HRESULT __stdcall GetRfc1766FromLcid(unsigned locale, /* out */ System::WideString &pbstrRfc1766) = 0 ;
	virtual HRESULT __stdcall GetLcidFromRfc1766(/* out */ unsigned &plocale, const System::WideString bstrRfc1766) = 0 ;
	virtual HRESULT __stdcall EnumRfc1766(/* out */ _di_IEnumRfc1766 &ppEnumRfc1766) = 0 ;
	virtual HRESULT __stdcall GetRfc1766Info(unsigned locale, /* out */ tagRFC1766INFO &pRfc1766Info) = 0 ;
	virtual HRESULT __stdcall CreateConvertCharset(unsigned uiSrcCodePage, unsigned uiDstCodePage, unsigned dwProperty, /* out */ _di_IMLangConvertCharset &ppMLangConvertCharset) = 0 ;
};

typedef tagDetectEncodingInfo *PDetectEncodingInfo;

typedef tagDetectEncodingInfo TDetectEncodingInfo;

typedef tagSCRIPFONTINFO *PScriptFontInfo;

typedef tagSCRIPFONTINFO TScriptFontInfo;

__interface  INTERFACE_UUID("{DCCFC164-2B38-11D2-B7EC-00C04F8F5D9A}") IMultiLanguage2  : public System::IInterface 
{
	virtual HRESULT __stdcall GetNumberOfCodePageInfo(/* out */ unsigned &pcCodePage) = 0 ;
	virtual HRESULT __stdcall GetCodePageInfo(unsigned uiCodePage, System::Word LangId, /* out */ tagMIMECPINFO &pCodePageInfo) = 0 ;
	virtual HRESULT __stdcall GetFamilyCodePage(unsigned uiCodePage, /* out */ unsigned &puiFamilyCodePage) = 0 ;
	virtual HRESULT __stdcall EnumCodePages(unsigned grfFlags, System::Word LangId, /* out */ _di_IEnumCodePage &ppEnumCodePage) = 0 ;
	virtual HRESULT __stdcall GetCharsetInfo(const System::WideString Charset, /* out */ tagMIMECSETINFO &pCharsetInfo) = 0 ;
	virtual HRESULT __stdcall IsConvertible(unsigned dwSrcEncoding, unsigned dwDstEncoding) = 0 ;
	virtual HRESULT __stdcall ConvertString(unsigned &pdwMode, unsigned dwSrcEncoding, unsigned dwDstEncoding, void * pSrcStr, PUINT pcSrcSize, void * pDstStr, unsigned &pcDstSize) = 0 ;
	virtual HRESULT __stdcall ConvertStringToUnicode(unsigned &pdwMode, unsigned dwEncoding, void * pSrcStr, PUINT pcSrcSize, System::WideChar * pDstStr, unsigned &pcDstSize) = 0 ;
	virtual HRESULT __stdcall ConvertStringFromUnicode(unsigned &pdwMode, unsigned dwEncoding, System::WideChar * pSrcStr, PUINT pcSrcSize, void * pDstStr, unsigned &pcDstSize) = 0 ;
	virtual HRESULT __stdcall ConvertStringReset() = 0 ;
	virtual HRESULT __stdcall GetRfc1766FromLcid(unsigned locale, /* out */ System::WideString &pbstrRfc1766) = 0 ;
	virtual HRESULT __stdcall GetLcidFromRfc1766(/* out */ unsigned &plocale, const System::WideString bstrRfc1766) = 0 ;
	virtual HRESULT __stdcall EnumRfc1766(System::Word LangId, /* out */ _di_IEnumRfc1766 &ppEnumRfc1766) = 0 ;
	virtual HRESULT __stdcall GetRfc1766Info(unsigned locale, System::Word LangId, /* out */ tagRFC1766INFO &pRfc1766Info) = 0 ;
	virtual HRESULT __stdcall CreateConvertCharset(unsigned uiSrcCodePage, unsigned uiDstCodePage, unsigned dwProperty, /* out */ _di_IMLangConvertCharset &ppMLangConvertCharset) = 0 ;
	virtual HRESULT __stdcall ConvertStringInIStream(unsigned &pdwMode, unsigned dwFlag, System::WideChar * lpFallBack, unsigned dwSrcEncoding, unsigned dwDstEncoding, const _di_IStream &pstmIn, const _di_IStream &pstmOut) = 0 ;
	virtual HRESULT __stdcall ConvertStringToUnicodeEx(unsigned &pdwMode, unsigned dwEncoding, void * pSrcStr, PUINT pcSrcSize, System::WideChar * pDstStr, unsigned &pcDstSize, unsigned dwFlag, System::WideChar * lpFallBack) = 0 ;
	virtual HRESULT __stdcall ConvertStringFromUnicodeEx(unsigned &pdwMode, unsigned dwEncoding, System::WideChar * pSrcStr, PUINT pcSrcSize, void * pDstStr, unsigned &pcDstSize, unsigned dwFlag, System::WideChar * lpFallBack) = 0 ;
	virtual HRESULT __stdcall DetectCodepageInIStream(unsigned dwFlag, unsigned dwPrefWinCodePage, const _di_IStream &pstmIn, PDetectEncodingInfo lpEncoding, int &pnScores) = 0 ;
	virtual HRESULT __stdcall DetectInputCodepage(unsigned dwFlag, unsigned dwPrefWinCodePage, void * pSrcStr, int &pcSrcSize, PDetectEncodingInfo lpEncoding, int &pnScores) = 0 ;
	virtual HRESULT __stdcall ValidateCodePage(unsigned uiCodePage, HWND hwnd) = 0 ;
	virtual HRESULT __stdcall GetCodePageDescription(unsigned uiCodePage, unsigned lcid, System::WideChar * lpWideCharStr, int cchWideChar) = 0 ;
	virtual HRESULT __stdcall IsCodePageInstallable(unsigned uiCodePage) = 0 ;
	virtual HRESULT __stdcall SetMimeDBSource(unsigned dwSource) = 0 ;
	virtual HRESULT __stdcall GetNumberOfScripts(/* out */ unsigned &pnScripts) = 0 ;
	virtual HRESULT __stdcall EnumScripts(unsigned dwFlags, System::Word LangId, /* out */ _di_IEnumScript &ppEnumScript) = 0 ;
	virtual HRESULT __stdcall ValidateCodePageEx(unsigned uiCodePage, HWND hwnd, unsigned dwfIODControl) = 0 ;
};

__interface  INTERFACE_UUID("{359F3443-BD4A-11D0-B188-00AA0038C969}") IMLangCodePages  : public System::IInterface 
{
	virtual HRESULT __stdcall GetCharCodePages(System::WideChar chSrc, /* out */ unsigned &pdwCodePages) = 0 ;
	virtual HRESULT __stdcall GetStrCodePages(System::WideChar * pszSrc, int cchSrc, unsigned dwPriorityCodePages, /* out */ unsigned &pdwCodePages, /* out */ int &pcchCodePages) = 0 ;
	virtual HRESULT __stdcall CodePageToCodePages(unsigned uCodePage, /* out */ unsigned &pdwCodePages) = 0 ;
	virtual HRESULT __stdcall CodePagesToCodePage(unsigned dwCodePages, unsigned uDefaultCodePage, /* out */ unsigned &puCodePage) = 0 ;
};

__interface  INTERFACE_UUID("{359F3441-BD4A-11D0-B188-00AA0038C969}") IMLangFontLink  : public IMLangCodePages 
{
	virtual HRESULT __stdcall GetFontCodePages(HDC hDC, HFONT hFont, /* out */ unsigned &pdwCodePages) = 0 ;
	virtual HRESULT __stdcall MapFont(HDC hDC, unsigned dwCodePages, HFONT hSrcFont, /* out */ HFONT &phDestFont) = 0 ;
	virtual HRESULT __stdcall ReleaseFont(HFONT hFont) = 0 ;
	virtual HRESULT __stdcall ResetFontMapping() = 0 ;
};

typedef tagUNICODERANGE *PUnicodeRange;

typedef tagUNICODERANGE TUnicodeRange;

__interface  INTERFACE_UUID("{DCCFC162-2B38-11D2-B7EC-00C04F8F5D9A}") IMLangFontLink2  : public IMLangCodePages 
{
	virtual HRESULT __stdcall GetFontCodePages(HDC hDC, HFONT hFont, /* out */ unsigned &pdwCodePages) = 0 ;
	virtual HRESULT __stdcall ReleaseFont(HFONT hFont) = 0 ;
	virtual HRESULT __stdcall ResetFontMapping() = 0 ;
	virtual HRESULT __stdcall MapFont(HDC hDC, unsigned dwCodePages, System::WideChar chSrc, /* out */ HFONT &pFont) = 0 ;
	virtual HRESULT __stdcall GetFontUnicodeRanges(HDC hDC, unsigned &puiRanges, PUnicodeRange pUranges) = 0 ;
	virtual HRESULT __stdcall GetScriptFontInfo(System::Byte sid, unsigned dwFlags, unsigned &puiFonts, PScriptFontInfo pScriptFont) = 0 ;
	virtual HRESULT __stdcall CodePageToScriptID(unsigned uiCodePage, /* out */ System::Byte &pSid) = 0 ;
};

__interface  INTERFACE_UUID("{4E5868AB-B157-4623-9ACC-6A1D9CAEBE04}") IMultiLanguage3  : public IMultiLanguage2 
{
	virtual HRESULT __stdcall DetectOutboundCodePage(unsigned dwFlags, System::WideChar * lpWideCharStr, unsigned cchWideChar, PUINT puiPreferredCodePages, unsigned nPreferredCodePages, PUINT puiDetectedCodePages, unsigned &pnDetectedCodePages, System::WideChar * lpSpecialChar) = 0 ;
	virtual HRESULT __stdcall DetectOutboundCodePageInIStream(unsigned dwFlags, const _di_IStream &pStrIn, PUINT puiPreferredCodePages, unsigned nPreferredCodePages, PUINT puiDetectedCodePages, unsigned &pnDetectedCodePages, System::WideChar * lpSpecialChar) = 0 ;
};

typedef _di_IMLangString CMLangString;

typedef _di_IMLangConvertCharset CMLangConvertCharset;

typedef _di_IMultiLanguage CMultiLanguage;

#pragma pack(push,4)
class PASCALIMPLEMENTATION CoCMLangString : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod _di_IMLangString __fastcall Create();
	__classmethod _di_IMLangString __fastcall CreateRemote(const System::UnicodeString MachineName);
public:
	/* TObject.Create */ inline __fastcall CoCMLangString() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~CoCMLangString() { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION CoCMLangConvertCharset : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod _di_IMLangConvertCharset __fastcall Create();
	__classmethod _di_IMLangConvertCharset __fastcall CreateRemote(const System::UnicodeString MachineName);
public:
	/* TObject.Create */ inline __fastcall CoCMLangConvertCharset() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~CoCMLangConvertCharset() { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION CoCMultiLanguage : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod _di_IMultiLanguage __fastcall Create();
	__classmethod _di_IMultiLanguage __fastcall CreateRemote(const System::UnicodeString MachineName);
public:
	/* TObject.Create */ inline __fastcall CoCMultiLanguage() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~CoCMultiLanguage() { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION CoCMultiLanguage2 : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod _di_IMultiLanguage2 __fastcall Create();
	__classmethod _di_IMultiLanguage2 __fastcall CreateRemote(const System::UnicodeString MachineName);
public:
	/* TObject.Create */ inline __fastcall CoCMultiLanguage2() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~CoCMultiLanguage2() { }
	
};

#pragma pack(pop)

#pragma pack(push,4)
class PASCALIMPLEMENTATION CoCMultiLanguage3 : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod _di_IMultiLanguage3 __fastcall Create();
	__classmethod _di_IMultiLanguage3 __fastcall CreateRemote(const System::UnicodeString MachineName);
public:
	/* TObject.Create */ inline __fastcall CoCMultiLanguage3() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~CoCMultiLanguage3() { }
	
};

#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
#define SID_IMLangStringBufW L"{D24ACD21-BA72-11D0-B188-00AA0038C969}"
#define SID_IMLangStringBufA L"{D24ACD23-BA72-11D0-B188-00AA0038C969}"
#define SID_IMLangString L"{C04D65CE-B70D-11D0-B188-00AA0038C969}"
#define SID_IMLangStringWStr L"{C04D65D0-B70D-11D0-B188-00AA0038C969}"
#define SID_IMLangStringAStr L"{C04D65D2-B70D-11D0-B188-00AA0038C969}"
#define SID_IMLangLineBreakConsole L"{F5BE2EE1-BFD7-11D0-B188-00AA0038C969}"
#define SID_IEnumCodePage L"{275c23e3-3747-11d0-9fea-00aa003f8646}"
#define SID_IEnumRfc1766 L"{3dc39d1d-c030-11d0-b81b-00c04fc9b31f}"
#define SID_IEnumScript L"{AE5F1430-388B-11d2-8380-00C04F8F5DA1}"
#define SID_IMLangConvertCharset L"{d66d6f98-cdaa-11d0-b822-00c04fc9b31f}"
#define SID_IMultiLanguage L"{275c23e1-3747-11d0-9fea-00aa003f8646}"
#define SID_IMultiLanguage2 L"{DCCFC164-2B38-11d2-B7EC-00C04F8F5D9A}"
#define SID_IMLangCodePages L"{359F3443-BD4A-11D0-B188-00AA0038C969}"
#define SID_IMLangFontLink L"{359F3441-BD4A-11D0-B188-00AA0038C969}"
#define SID_IMLangFontLink2 L"{DCCFC162-2B38-11d2-B7EC-00C04F8F5D9A}"
#define SID_IMultiLanguage3 L"{4e5868ab-b157-4623-9acc-6a1d9caebe04}"
extern DELPHI_PACKAGE GUID IID_IMLangStringBufW;
extern DELPHI_PACKAGE GUID IID_IMLangStringBufA;
extern DELPHI_PACKAGE GUID IID_IMLangString;
extern DELPHI_PACKAGE GUID IID_IMLangStringWStr;
extern DELPHI_PACKAGE GUID IID_IMLangStringAStr;
extern DELPHI_PACKAGE GUID IID_IMLangLineBreakConsole;
extern DELPHI_PACKAGE GUID IID_IEnumCodePage;
extern DELPHI_PACKAGE GUID IID_IEnumRfc1766;
extern DELPHI_PACKAGE GUID IID_IEnumScript;
extern DELPHI_PACKAGE GUID IID_IMLangConvertCharset;
extern DELPHI_PACKAGE GUID IID_IMultiLanguage;
extern DELPHI_PACKAGE GUID IID_IMultiLanguage2;
extern DELPHI_PACKAGE GUID IID_IMLangCodePages;
extern DELPHI_PACKAGE GUID IID_IMLangFontLink;
extern DELPHI_PACKAGE GUID IID_IMLangFontLink2;
extern DELPHI_PACKAGE GUID IID_IMultiLanguage3;
static const System::Int8 sidDefault = System::Int8(0x0);
static const System::Int8 sidMerge = System::Int8(0x1);
static const System::Int8 sidAsciiSym = System::Int8(0x2);
static const System::Int8 sidAsciiLatin = System::Int8(0x3);
static const System::Int8 sidLatin = System::Int8(0x4);
static const System::Int8 sidGreek = System::Int8(0x5);
static const System::Int8 sidCyrillic = System::Int8(0x6);
static const System::Int8 sidArmenian = System::Int8(0x7);
static const System::Int8 sidHebrew = System::Int8(0x8);
static const System::Int8 sidArabic = System::Int8(0x9);
static const System::Int8 sidDevanagari = System::Int8(0xa);
static const System::Int8 sidBengali = System::Int8(0xb);
static const System::Int8 sidGurmukhi = System::Int8(0xc);
static const System::Int8 sidGujarati = System::Int8(0xd);
static const System::Int8 sidOriya = System::Int8(0xe);
static const System::Int8 sidTamil = System::Int8(0xf);
static const System::Int8 sidTelugu = System::Int8(0x10);
static const System::Int8 sidKannada = System::Int8(0x11);
static const System::Int8 sidMalayalam = System::Int8(0x12);
static const System::Int8 sidThai = System::Int8(0x13);
static const System::Int8 sidLao = System::Int8(0x14);
static const System::Int8 sidTibetan = System::Int8(0x15);
static const System::Int8 sidGeorgian = System::Int8(0x16);
static const System::Int8 sidHangul = System::Int8(0x17);
static const System::Int8 sidKana = System::Int8(0x18);
static const System::Int8 sidBopomofo = System::Int8(0x19);
static const System::Int8 sidHan = System::Int8(0x1a);
static const System::Int8 sidEthiopic = System::Int8(0x1b);
static const System::Int8 sidCanSyllabic = System::Int8(0x1c);
static const System::Int8 sidCherokee = System::Int8(0x1d);
static const System::Int8 sidYi = System::Int8(0x1e);
static const System::Int8 sidBraille = System::Int8(0x1f);
static const System::Int8 sidRunic = System::Int8(0x20);
static const System::Int8 sidOgham = System::Int8(0x21);
static const System::Int8 sidSinhala = System::Int8(0x22);
static const System::Int8 sidSyriac = System::Int8(0x23);
static const System::Int8 sidBurmese = System::Int8(0x24);
static const System::Int8 sidKhmer = System::Int8(0x25);
static const System::Int8 sidThaana = System::Int8(0x26);
static const System::Int8 sidMongolian = System::Int8(0x27);
static const System::Int8 sidUserDefined = System::Int8(0x28);
static const System::Int8 sidLim = System::Int8(0x29);
static const System::Int8 sidFEFirst = System::Int8(0x17);
static const System::Int8 sidFELast = System::Int8(0x1a);
static const System::Int8 MLCONVCHARF_AUTODETECT = System::Int8(0x1);
static const System::Int8 MLCONVCHARF_ENTITIZE = System::Int8(0x2);
static const System::Int8 MLCONVCHARF_NCR_ENTITIZE = System::Int8(0x2);
static const System::Int8 MLCONVCHARF_NAME_ENTITIZE = System::Int8(0x4);
static const System::Int8 MLCONVCHARF_USEDEFCHAR = System::Int8(0x8);
static const System::Int8 MLCONVCHARF_NOBESTFITCHARS = System::Int8(0x10);
static const System::Int8 MLCONVCHARF_DETECTJPN = System::Int8(0x20);
static const System::Int8 MLDETECTF_MAILNEWS = System::Int8(0x1);
static const System::Int8 MLDETECTF_BROWSER = System::Int8(0x2);
static const System::Int8 MLDETECTF_VALID = System::Int8(0x4);
static const System::Int8 MLDETECTF_VALID_NLS = System::Int8(0x8);
static const System::Int8 MLDETECTF_PRESERVE_ORDER = System::Int8(0x10);
static const System::Int8 MLDETECTF_PREFERRED_ONLY = System::Int8(0x20);
static const System::Int8 MLDETECTF_FILTER_SPECIALCHAR = System::Int8(0x40);
static const System::Byte MLDETECTF_EURO_UTF8 = System::Byte(0x80);
static const System::Int8 MLDETECTCP_NONE = System::Int8(0x0);
static const System::Int8 MLDETECTCP_7BIT = System::Int8(0x1);
static const System::Int8 MLDETECTCP_8BIT = System::Int8(0x2);
static const System::Int8 MLDETECTCP_DBCS = System::Int8(0x4);
static const System::Int8 MLDETECTCP_HTML = System::Int8(0x8);
static const System::Int8 MLDETECTCP_NUMBER = System::Int8(0x10);
static const System::Int8 SCRIPTCONTF_FIXED_FONT = System::Int8(0x1);
static const System::Int8 SCRIPTCONTF_PROPORTIONAL_FONT = System::Int8(0x2);
static const int SCRIPTCONTF_SCRIPT_USER = int(0x10000);
static const int SCRIPTCONTF_SCRIPT_HIDE = int(0x20000);
static const int SCRIPTCONTF_SCRIPT_SYSTEM = int(0x40000);
static const System::Int8 MLSTR_READ = System::Int8(0x1);
static const System::Int8 MLSTR_WRITE = System::Int8(0x2);
}	/* namespace Mlang */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_MLANG)
using namespace Winapi::Mlang;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_MlangHPP
