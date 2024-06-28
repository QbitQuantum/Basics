// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.Internal.EncodingUtils.pas' rev: 34.00 (Windows)

#ifndef Xml_Internal_EncodingutilsHPP
#define Xml_Internal_EncodingutilsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Internal
{
namespace Encodingutils
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TEncodingInfo;
class DELPHICLASS TEncodingInfoAscii;
class DELPHICLASS TEncodingInfoIsoLatin1;
class DELPHICLASS TEncodingInfoIsoLatin2;
class DELPHICLASS TEncodingInfoIsoLatin3;
class DELPHICLASS TEncodingInfoIsoLatin4;
class DELPHICLASS TEncodingInfoIsoLatinCyrillic;
class DELPHICLASS TEncodingInfoIsoLatinArabic;
class DELPHICLASS TEncodingInfoIsoLatinGreek;
class DELPHICLASS TEncodingInfoIsoLatinHebrew;
class DELPHICLASS TEncodingInfoIsoLatin5;
class DELPHICLASS TEncodingInfoIsoLatin6;
class DELPHICLASS TEncodingInfoIsoTextComm;
class DELPHICLASS TEncodingInfoHalfWidthKatakana;
class DELPHICLASS TEncodingInfoJISEncoding;
class DELPHICLASS TEncodingInfoShiftJIS;
class DELPHICLASS TEncodingInfoEUCPPkdFmtJapanese;
class DELPHICLASS TEncodingInfoEUCFixWidJapanese;
class DELPHICLASS TEncodingInfoISO4UnitedKingdom;
class DELPHICLASS TEncodingInfoISO11SwedishForNames;
class DELPHICLASS TEncodingInfoISO15Italian;
class DELPHICLASS TEncodingInfoISO17Spanish;
class DELPHICLASS TEncodingInfoISO21German;
class DELPHICLASS TEncodingInfoISO60DanishNorwegian;
class DELPHICLASS TEncodingInfoISO69French;
class DELPHICLASS TEncodingInfoISO10646UTF1;
class DELPHICLASS TEncodingInfoISO646basic1983;
class DELPHICLASS TEncodingInfoInvariant;
class DELPHICLASS TEncodingInfoISO2Int1RefVersion;
class DELPHICLASS TEncodingInfoNATSSEFI;
class DELPHICLASS TEncodingInfoNATSSEFIADD;
class DELPHICLASS TEncodingInfoNATSDANO;
class DELPHICLASS TEncodingInfoNATSDANOADD;
class DELPHICLASS TEncodingInfoISO10Swedish;
class DELPHICLASS TEncodingInfoKSC56011987;
class DELPHICLASS TEncodingInfoISO2022KR;
class DELPHICLASS TEncodingInfoEUCKR;
class DELPHICLASS TEncodingInfoISO2022JP;
class DELPHICLASS TEncodingInfoISO2022JP2;
class DELPHICLASS TEncodingInfoISO13JISC6220jp;
class DELPHICLASS TEncodingInfoISO14JISC6220ro;
class DELPHICLASS TEncodingInfoISO16Portuguese;
class DELPHICLASS TEncodingInfoISO18Greek7Old;
class DELPHICLASS TEncodingInfoISO19LatinGreek;
class DELPHICLASS TEncodingInfoISO25French;
class DELPHICLASS TEncodingInfoISO27LatinGreek1;
class DELPHICLASS TEncodingInfoISO5427Cyrillic;
class DELPHICLASS TEncodingInfoISO42JISC62261978;
class DELPHICLASS TEncodingInfoISO47BSViewdata;
class DELPHICLASS TEncodingInfoISO49INIS;
class DELPHICLASS TEncodingInfoISO50INIS8;
class DELPHICLASS TEncodingInfoISO51INISCyrillic;
class DELPHICLASS TEncodingInfoISO5427Cyrillic1981;
class DELPHICLASS TEncodingInfoISO5428Greek;
class DELPHICLASS TEncodingInfoISO57GB1988;
class DELPHICLASS TEncodingInfoISO58GB231280;
class DELPHICLASS TEncodingInfoISO61Norwegian2;
class DELPHICLASS TEncodingInfoISO70VideotexSupp1;
class DELPHICLASS TEncodingInfoISO84Portuguese2;
class DELPHICLASS TEncodingInfoISO85Spanish2;
class DELPHICLASS TEncodingInfoISO86Hungarian;
class DELPHICLASS TEncodingInfoISO87JISX0208;
class DELPHICLASS TEncodingInfoISO88Greek7;
class DELPHICLASS TEncodingInfoISO89ASMO449;
class DELPHICLASS TEncodingInfoISO90;
class DELPHICLASS TEncodingInfoISO91JISC62291984a;
class DELPHICLASS TEncodingInfoISO92JISC62991984b;
class DELPHICLASS TEncodingInfoISO93JIS62291984badd;
class DELPHICLASS TEncodingInfoISO94JIS62291984hand;
class DELPHICLASS TEncodingInfoISO95JIS62291984handadd;
class DELPHICLASS TEncodingInfoISO96JISC62291984kana;
class DELPHICLASS TEncodingInfoISO2033;
class DELPHICLASS TEncodingInfoISO99NAPLPS;
class DELPHICLASS TEncodingInfoISO102T617bit;
class DELPHICLASS TEncodingInfoISO103T618bit;
class DELPHICLASS TEncodingInfoISO111ECMACyrillic;
class DELPHICLASS TEncodingInfoISO121Canadian1;
class DELPHICLASS TEncodingInfoISO122Canadian2;
class DELPHICLASS TEncodingInfoISO123CSAZ24341985gr;
class DELPHICLASS TEncodingInfoISO88596E;
class DELPHICLASS TEncodingInfoISO88596I;
class DELPHICLASS TEncodingInfoISO128T101G2;
class DELPHICLASS TEncodingInfoISO88598E;
class DELPHICLASS TEncodingInfoISO88598I;
class DELPHICLASS TEncodingInfoISO139CSN369103;
class DELPHICLASS TEncodingInfoISO141JUSIB1002;
class DELPHICLASS TEncodingInfoISO143IECP271;
class DELPHICLASS TEncodingInfoISO146Serbian;
class DELPHICLASS TEncodingInfoISO147Macedonian;
class DELPHICLASS TEncodingInfoISO150GreekCCITT;
class DELPHICLASS TEncodingInfoISO151Cuba;
class DELPHICLASS TEncodingInfoISO6937Add;
class DELPHICLASS TEncodingInfoISO153GOST1976874;
class DELPHICLASS TEncodingInfoISO8859Supp;
class DELPHICLASS TEncodingInfoISO10367Box;
class DELPHICLASS TEncodingInfoISO158Lap;
class DELPHICLASS TEncodingInfoISO159JISX02121990;
class DELPHICLASS TEncodingInfoISO646Danish;
class DELPHICLASS TEncodingInfoUSDK;
class DELPHICLASS TEncodingInfoDKUS;
class DELPHICLASS TEncodingInfoKSC5636;
class DELPHICLASS TEncodingInfoUnicode11UTF7;
class DELPHICLASS TEncodingInfoISO2022CN;
class DELPHICLASS TEncodingInfoISO2022CNEXT;
class DELPHICLASS TEncodingInfoUTF8;
class DELPHICLASS TEncodingInfoISO885913;
class DELPHICLASS TEncodingInfoIsoLatin8;
class DELPHICLASS TEncodingInfoIsoLatin9;
class DELPHICLASS TEncodingInfoIsoLatin10;
class DELPHICLASS TEncodingInfoGBK;
class DELPHICLASS TEncodingInfoGB18030;
class DELPHICLASS TEncodingInfoOSD_EBCDIC_DF04_15;
class DELPHICLASS TEncodingInfoOSD_EBCDIC_DF03_IRV;
class DELPHICLASS TEncodingInfoOSD_EBCDIC_DF04_1;
class DELPHICLASS TEncodingInfoISO115481;
class DELPHICLASS TEncodingInfoKZ1048;
class DELPHICLASS TEncodingInfoUCS2;
class DELPHICLASS TEncodingInfoUCS4;
class DELPHICLASS TEncodingInfoUnicodeASCII;
class DELPHICLASS TEncodingInfoUnicodeLatin1;
class DELPHICLASS TEncodingInfoISO10646J1;
class DELPHICLASS TEncodingInfoUnicodeIBM1261;
class DELPHICLASS TEncodingInfoUnicodeIBM1268;
class DELPHICLASS TEncodingInfoUnicodeIBM1276;
class DELPHICLASS TEncodingInfoUnicodeIBM1264;
class DELPHICLASS TEncodingInfoUnicodeIBM1265;
class DELPHICLASS TEncodingInfoUnicode11;
class DELPHICLASS TEncodingInfoSCSU;
class DELPHICLASS TEncodingInfoUTF7;
class DELPHICLASS TEncodingInfoUTF16BE;
class DELPHICLASS TEncodingInfoUTF16LE;
class DELPHICLASS TEncodingInfoUTF16;
class DELPHICLASS TEncodingInfoCESU8;
class DELPHICLASS TEncodingInfoUTF32;
class DELPHICLASS TEncodingInfoUTF32BE;
class DELPHICLASS TEncodingInfoUTF32LE;
class DELPHICLASS TEncodingInfoBOCU1;
class DELPHICLASS TEncodingInfoWindows30Latin1;
class DELPHICLASS TEncodingInfoWindows31Latin1;
class DELPHICLASS TEncodingInfoWindows31Latin2;
class DELPHICLASS TEncodingInfoWindows31Latin5;
class DELPHICLASS TEncodingInfoHPRoman8;
class DELPHICLASS TEncodingInfoAdobeStandardEncoding;
class DELPHICLASS TEncodingInfoVenturaUS;
class DELPHICLASS TEncodingInfoVenturaInternational;
class DELPHICLASS TEncodingInfoDECMCS;
class DELPHICLASS TEncodingInfoPC850Multilingual;
class DELPHICLASS TEncodingInfoPCp852;
class DELPHICLASS TEncodingInfoPC8CodePage437;
class DELPHICLASS TEncodingInfoPC8DanishNorwegian;
class DELPHICLASS TEncodingInfoPC862LatinHebrew;
class DELPHICLASS TEncodingInfoPC8Turkish;
class DELPHICLASS TEncodingInfoIBMSymbols;
class DELPHICLASS TEncodingInfoIBMThai;
class DELPHICLASS TEncodingInfoHPLegal;
class DELPHICLASS TEncodingInfoHPPiFont;
class DELPHICLASS TEncodingInfoHPMath8;
class DELPHICLASS TEncodingInfoHPPSMath;
class DELPHICLASS TEncodingInfoHPDesktop;
class DELPHICLASS TEncodingInfoVenturaMath;
class DELPHICLASS TEncodingInfoMicrosoftPublishing;
class DELPHICLASS TEncodingInfoWindows31J;
class DELPHICLASS TEncodingInfoGB2312;
class DELPHICLASS TEncodingInfoBig5;
class DELPHICLASS TEncodingInfoMacintosh;
class DELPHICLASS TEncodingInfoIBM037;
class DELPHICLASS TEncodingInfoIBM038;
class DELPHICLASS TEncodingInfoIBM273;
class DELPHICLASS TEncodingInfoIBM274;
class DELPHICLASS TEncodingInfoIBM275;
class DELPHICLASS TEncodingInfoIBM277;
class DELPHICLASS TEncodingInfoIBM278;
class DELPHICLASS TEncodingInfoIBM280;
class DELPHICLASS TEncodingInfoIBM281;
class DELPHICLASS TEncodingInfoIBM284;
class DELPHICLASS TEncodingInfoIBM285;
class DELPHICLASS TEncodingInfoIBM290;
class DELPHICLASS TEncodingInfoIBM297;
class DELPHICLASS TEncodingInfoIBM420;
class DELPHICLASS TEncodingInfoIBM423;
class DELPHICLASS TEncodingInfoIBM424;
class DELPHICLASS TEncodingInfoIBM500;
class DELPHICLASS TEncodingInfoIBM851;
class DELPHICLASS TEncodingInfoIBM855;
class DELPHICLASS TEncodingInfoIBM857;
class DELPHICLASS TEncodingInfoIBM860;
class DELPHICLASS TEncodingInfoIBM861;
class DELPHICLASS TEncodingInfoIBM863;
class DELPHICLASS TEncodingInfoIBM864;
class DELPHICLASS TEncodingInfoIBM865;
class DELPHICLASS TEncodingInfoIBM868;
class DELPHICLASS TEncodingInfoIBM869;
class DELPHICLASS TEncodingInfoIBM870;
class DELPHICLASS TEncodingInfoIBM871;
class DELPHICLASS TEncodingInfoIBM880;
class DELPHICLASS TEncodingInfoIBM891;
class DELPHICLASS TEncodingInfoIBM903;
class DELPHICLASS TEncodingInfoIBM904;
class DELPHICLASS TEncodingInfoIBM905;
class DELPHICLASS TEncodingInfoIBM918;
class DELPHICLASS TEncodingInfoIBM1026;
class DELPHICLASS TEncodingInfoIBMEBCDICATDE;
class DELPHICLASS TEncodingInfoEBCDICATDEA;
class DELPHICLASS TEncodingInfoEBCDICCAFR;
class DELPHICLASS TEncodingInfoEBCDICDKNO;
class DELPHICLASS TEncodingInfoEBCDICDKNOA;
class DELPHICLASS TEncodingInfoEBCDICFISE;
class DELPHICLASS TEncodingInfoEBCDICFISEA;
class DELPHICLASS TEncodingInfoEBCDICFR;
class DELPHICLASS TEncodingInfoEBCDICIT;
class DELPHICLASS TEncodingInfoEBCDICPT;
class DELPHICLASS TEncodingInfoEBCDICES;
class DELPHICLASS TEncodingInfoEBCDICESA;
class DELPHICLASS TEncodingInfoEBCDICESS;
class DELPHICLASS TEncodingInfoEBCDICUK;
class DELPHICLASS TEncodingInfoEBCDICUS;
class DELPHICLASS TEncodingInfoUnknown8Bit;
class DELPHICLASS TEncodingInfoMnemonic;
class DELPHICLASS TEncodingInfoMnem;
class DELPHICLASS TEncodingInfoVISCII;
class DELPHICLASS TEncodingInfoVIQR;
class DELPHICLASS TEncodingInfoKOI8R;
class DELPHICLASS TEncodingInfoHZGB2312;
class DELPHICLASS TEncodingInfoIBM866;
class DELPHICLASS TEncodingInfoPC775Baltic;
class DELPHICLASS TEncodingInfoKOI8U;
class DELPHICLASS TEncodingInfoIBM00858;
class DELPHICLASS TEncodingInfoIBM00924;
class DELPHICLASS TEncodingInfoIBM01140;
class DELPHICLASS TEncodingInfoIBM01141;
class DELPHICLASS TEncodingInfoIBM01142;
class DELPHICLASS TEncodingInfoIBM01143;
class DELPHICLASS TEncodingInfoIBM01144;
class DELPHICLASS TEncodingInfoIBM01145;
class DELPHICLASS TEncodingInfoIBM01146;
class DELPHICLASS TEncodingInfoIBM01147;
class DELPHICLASS TEncodingInfoIBM01148;
class DELPHICLASS TEncodingInfoIBM01149;
class DELPHICLASS TEncodingInfoBig5HKSCS;
class DELPHICLASS TEncodingInfoIBM1047;
class DELPHICLASS TEncodingInfoPTCP154;
class DELPHICLASS TEncodingInfoAmiga1251;
class DELPHICLASS TEncodingInfoKOI7switched;
class DELPHICLASS TEncodingInfoBRF;
class DELPHICLASS TEncodingInfoTSCII;
class DELPHICLASS TEncodingInfoWindows1250;
class DELPHICLASS TEncodingInfoWindows1251;
class DELPHICLASS TEncodingInfoWindows1252;
class DELPHICLASS TEncodingInfoWindows1253;
class DELPHICLASS TEncodingInfoWindows1254;
class DELPHICLASS TEncodingInfoWindows1255;
class DELPHICLASS TEncodingInfoWindows1256;
class DELPHICLASS TEncodingInfoWindows1257;
class DELPHICLASS TEncodingInfoWindows1258;
class DELPHICLASS TEncodingInfoTIS620;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfo : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	__classmethod virtual void __fastcall Error();
	
public:
	virtual __classmethod System::UnicodeString __fastcall Alias(int I) = 0 ;
	virtual __classmethod int __fastcall AliasCount() = 0 ;
	virtual __classmethod System::UnicodeString __fastcall Name() = 0 ;
	virtual __classmethod int __fastcall MIBenum() = 0 ;
	virtual __classmethod System::UnicodeString __fastcall PreferredMIMEName() = 0 ;
public:
	/* TObject.Create */ inline __fastcall TEncodingInfo() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfo() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoAscii : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoAscii() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoAscii() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIsoLatin1 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIsoLatin1() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIsoLatin1() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIsoLatin2 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIsoLatin2() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIsoLatin2() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIsoLatin3 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIsoLatin3() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIsoLatin3() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIsoLatin4 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIsoLatin4() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIsoLatin4() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIsoLatinCyrillic : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIsoLatinCyrillic() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIsoLatinCyrillic() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIsoLatinArabic : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIsoLatinArabic() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIsoLatinArabic() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIsoLatinGreek : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIsoLatinGreek() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIsoLatinGreek() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIsoLatinHebrew : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIsoLatinHebrew() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIsoLatinHebrew() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIsoLatin5 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIsoLatin5() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIsoLatin5() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIsoLatin6 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIsoLatin6() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIsoLatin6() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIsoTextComm : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIsoTextComm() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIsoTextComm() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoHalfWidthKatakana : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoHalfWidthKatakana() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoHalfWidthKatakana() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoJISEncoding : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoJISEncoding() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoJISEncoding() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoShiftJIS : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoShiftJIS() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoShiftJIS() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoEUCPPkdFmtJapanese : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoEUCPPkdFmtJapanese() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoEUCPPkdFmtJapanese() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoEUCFixWidJapanese : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoEUCFixWidJapanese() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoEUCFixWidJapanese() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO4UnitedKingdom : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO4UnitedKingdom() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO4UnitedKingdom() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO11SwedishForNames : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO11SwedishForNames() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO11SwedishForNames() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO15Italian : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO15Italian() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO15Italian() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO17Spanish : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO17Spanish() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO17Spanish() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO21German : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO21German() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO21German() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO60DanishNorwegian : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO60DanishNorwegian() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO60DanishNorwegian() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO69French : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO69French() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO69French() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO10646UTF1 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO10646UTF1() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO10646UTF1() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO646basic1983 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO646basic1983() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO646basic1983() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoInvariant : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoInvariant() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoInvariant() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO2Int1RefVersion : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO2Int1RefVersion() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO2Int1RefVersion() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoNATSSEFI : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoNATSSEFI() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoNATSSEFI() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoNATSSEFIADD : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoNATSSEFIADD() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoNATSSEFIADD() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoNATSDANO : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoNATSDANO() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoNATSDANO() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoNATSDANOADD : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoNATSDANOADD() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoNATSDANOADD() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO10Swedish : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO10Swedish() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO10Swedish() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoKSC56011987 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoKSC56011987() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoKSC56011987() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO2022KR : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO2022KR() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO2022KR() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoEUCKR : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoEUCKR() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoEUCKR() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO2022JP : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO2022JP() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO2022JP() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO2022JP2 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO2022JP2() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO2022JP2() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO13JISC6220jp : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO13JISC6220jp() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO13JISC6220jp() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO14JISC6220ro : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO14JISC6220ro() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO14JISC6220ro() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO16Portuguese : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO16Portuguese() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO16Portuguese() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO18Greek7Old : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO18Greek7Old() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO18Greek7Old() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO19LatinGreek : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO19LatinGreek() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO19LatinGreek() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO25French : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO25French() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO25French() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO27LatinGreek1 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO27LatinGreek1() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO27LatinGreek1() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO5427Cyrillic : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO5427Cyrillic() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO5427Cyrillic() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO42JISC62261978 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO42JISC62261978() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO42JISC62261978() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO47BSViewdata : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO47BSViewdata() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO47BSViewdata() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO49INIS : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO49INIS() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO49INIS() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO50INIS8 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO50INIS8() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO50INIS8() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO51INISCyrillic : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO51INISCyrillic() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO51INISCyrillic() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO5427Cyrillic1981 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO5427Cyrillic1981() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO5427Cyrillic1981() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO5428Greek : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO5428Greek() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO5428Greek() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO57GB1988 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO57GB1988() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO57GB1988() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO58GB231280 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO58GB231280() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO58GB231280() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO61Norwegian2 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO61Norwegian2() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO61Norwegian2() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO70VideotexSupp1 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO70VideotexSupp1() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO70VideotexSupp1() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO84Portuguese2 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO84Portuguese2() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO84Portuguese2() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO85Spanish2 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO85Spanish2() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO85Spanish2() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO86Hungarian : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO86Hungarian() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO86Hungarian() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO87JISX0208 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO87JISX0208() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO87JISX0208() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO88Greek7 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO88Greek7() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO88Greek7() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO89ASMO449 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO89ASMO449() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO89ASMO449() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO90 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO90() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO90() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO91JISC62291984a : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO91JISC62291984a() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO91JISC62291984a() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO92JISC62991984b : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO92JISC62991984b() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO92JISC62991984b() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO93JIS62291984badd : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO93JIS62291984badd() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO93JIS62291984badd() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO94JIS62291984hand : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO94JIS62291984hand() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO94JIS62291984hand() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO95JIS62291984handadd : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO95JIS62291984handadd() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO95JIS62291984handadd() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO96JISC62291984kana : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO96JISC62291984kana() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO96JISC62291984kana() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO2033 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO2033() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO2033() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO99NAPLPS : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO99NAPLPS() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO99NAPLPS() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO102T617bit : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO102T617bit() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO102T617bit() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO103T618bit : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO103T618bit() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO103T618bit() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO111ECMACyrillic : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO111ECMACyrillic() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO111ECMACyrillic() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO121Canadian1 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO121Canadian1() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO121Canadian1() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO122Canadian2 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO122Canadian2() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO122Canadian2() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO123CSAZ24341985gr : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO123CSAZ24341985gr() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO123CSAZ24341985gr() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO88596E : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO88596E() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO88596E() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO88596I : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO88596I() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO88596I() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO128T101G2 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO128T101G2() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO128T101G2() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO88598E : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO88598E() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO88598E() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO88598I : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO88598I() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO88598I() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO139CSN369103 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO139CSN369103() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO139CSN369103() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO141JUSIB1002 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO141JUSIB1002() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO141JUSIB1002() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO143IECP271 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO143IECP271() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO143IECP271() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO146Serbian : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO146Serbian() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO146Serbian() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO147Macedonian : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO147Macedonian() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO147Macedonian() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO150GreekCCITT : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO150GreekCCITT() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO150GreekCCITT() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO151Cuba : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO151Cuba() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO151Cuba() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO6937Add : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO6937Add() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO6937Add() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO153GOST1976874 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO153GOST1976874() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO153GOST1976874() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO8859Supp : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO8859Supp() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO8859Supp() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO10367Box : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO10367Box() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO10367Box() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO158Lap : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO158Lap() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO158Lap() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO159JISX02121990 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO159JISX02121990() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO159JISX02121990() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO646Danish : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO646Danish() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO646Danish() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoUSDK : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoUSDK() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoUSDK() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoDKUS : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoDKUS() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoDKUS() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoKSC5636 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoKSC5636() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoKSC5636() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoUnicode11UTF7 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoUnicode11UTF7() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoUnicode11UTF7() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO2022CN : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO2022CN() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO2022CN() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO2022CNEXT : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO2022CNEXT() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO2022CNEXT() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoUTF8 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoUTF8() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoUTF8() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO885913 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO885913() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO885913() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIsoLatin8 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIsoLatin8() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIsoLatin8() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIsoLatin9 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIsoLatin9() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIsoLatin9() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIsoLatin10 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIsoLatin10() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIsoLatin10() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoGBK : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoGBK() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoGBK() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoGB18030 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoGB18030() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoGB18030() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoOSD_EBCDIC_DF04_15 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoOSD_EBCDIC_DF04_15() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoOSD_EBCDIC_DF04_15() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoOSD_EBCDIC_DF03_IRV : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoOSD_EBCDIC_DF03_IRV() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoOSD_EBCDIC_DF03_IRV() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoOSD_EBCDIC_DF04_1 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoOSD_EBCDIC_DF04_1() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoOSD_EBCDIC_DF04_1() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO115481 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO115481() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO115481() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoKZ1048 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoKZ1048() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoKZ1048() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoUCS2 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoUCS2() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoUCS2() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoUCS4 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoUCS4() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoUCS4() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoUnicodeASCII : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoUnicodeASCII() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoUnicodeASCII() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoUnicodeLatin1 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoUnicodeLatin1() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoUnicodeLatin1() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoISO10646J1 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoISO10646J1() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoISO10646J1() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoUnicodeIBM1261 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoUnicodeIBM1261() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoUnicodeIBM1261() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoUnicodeIBM1268 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoUnicodeIBM1268() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoUnicodeIBM1268() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoUnicodeIBM1276 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoUnicodeIBM1276() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoUnicodeIBM1276() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoUnicodeIBM1264 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoUnicodeIBM1264() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoUnicodeIBM1264() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoUnicodeIBM1265 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoUnicodeIBM1265() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoUnicodeIBM1265() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoUnicode11 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoUnicode11() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoUnicode11() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoSCSU : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoSCSU() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoSCSU() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoUTF7 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoUTF7() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoUTF7() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoUTF16BE : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoUTF16BE() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoUTF16BE() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoUTF16LE : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoUTF16LE() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoUTF16LE() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoUTF16 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoUTF16() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoUTF16() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoCESU8 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoCESU8() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoCESU8() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoUTF32 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoUTF32() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoUTF32() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoUTF32BE : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoUTF32BE() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoUTF32BE() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoUTF32LE : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoUTF32LE() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoUTF32LE() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoBOCU1 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoBOCU1() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoBOCU1() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoWindows30Latin1 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoWindows30Latin1() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoWindows30Latin1() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoWindows31Latin1 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoWindows31Latin1() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoWindows31Latin1() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoWindows31Latin2 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoWindows31Latin2() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoWindows31Latin2() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoWindows31Latin5 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoWindows31Latin5() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoWindows31Latin5() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoHPRoman8 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoHPRoman8() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoHPRoman8() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoAdobeStandardEncoding : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoAdobeStandardEncoding() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoAdobeStandardEncoding() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoVenturaUS : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoVenturaUS() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoVenturaUS() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoVenturaInternational : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoVenturaInternational() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoVenturaInternational() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoDECMCS : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoDECMCS() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoDECMCS() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoPC850Multilingual : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoPC850Multilingual() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoPC850Multilingual() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoPCp852 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoPCp852() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoPCp852() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoPC8CodePage437 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoPC8CodePage437() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoPC8CodePage437() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoPC8DanishNorwegian : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoPC8DanishNorwegian() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoPC8DanishNorwegian() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoPC862LatinHebrew : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoPC862LatinHebrew() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoPC862LatinHebrew() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoPC8Turkish : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoPC8Turkish() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoPC8Turkish() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBMSymbols : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBMSymbols() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBMSymbols() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBMThai : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBMThai() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBMThai() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoHPLegal : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoHPLegal() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoHPLegal() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoHPPiFont : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoHPPiFont() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoHPPiFont() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoHPMath8 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoHPMath8() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoHPMath8() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoHPPSMath : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoHPPSMath() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoHPPSMath() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoHPDesktop : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoHPDesktop() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoHPDesktop() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoVenturaMath : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoVenturaMath() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoVenturaMath() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoMicrosoftPublishing : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoMicrosoftPublishing() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoMicrosoftPublishing() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoWindows31J : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoWindows31J() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoWindows31J() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoGB2312 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoGB2312() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoGB2312() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoBig5 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoBig5() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoBig5() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoMacintosh : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoMacintosh() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoMacintosh() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM037 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM037() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM037() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM038 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM038() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM038() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM273 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM273() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM273() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM274 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM274() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM274() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM275 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM275() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM275() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM277 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM277() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM277() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM278 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM278() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM278() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM280 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM280() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM280() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM281 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM281() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM281() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM284 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM284() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM284() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM285 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM285() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM285() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM290 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM290() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM290() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM297 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM297() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM297() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM420 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM420() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM420() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM423 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM423() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM423() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM424 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM424() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM424() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM500 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM500() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM500() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM851 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM851() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM851() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM855 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM855() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM855() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM857 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM857() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM857() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM860 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM860() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM860() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM861 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM861() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM861() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM863 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM863() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM863() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM864 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM864() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM864() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM865 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM865() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM865() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM868 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM868() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM868() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM869 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM869() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM869() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM870 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM870() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM870() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM871 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM871() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM871() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM880 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM880() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM880() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM891 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM891() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM891() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM903 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM903() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM903() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM904 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM904() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM904() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM905 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM905() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM905() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM918 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM918() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM918() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM1026 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM1026() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM1026() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBMEBCDICATDE : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBMEBCDICATDE() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBMEBCDICATDE() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoEBCDICATDEA : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoEBCDICATDEA() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoEBCDICATDEA() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoEBCDICCAFR : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoEBCDICCAFR() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoEBCDICCAFR() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoEBCDICDKNO : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoEBCDICDKNO() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoEBCDICDKNO() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoEBCDICDKNOA : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoEBCDICDKNOA() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoEBCDICDKNOA() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoEBCDICFISE : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoEBCDICFISE() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoEBCDICFISE() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoEBCDICFISEA : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoEBCDICFISEA() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoEBCDICFISEA() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoEBCDICFR : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoEBCDICFR() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoEBCDICFR() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoEBCDICIT : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoEBCDICIT() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoEBCDICIT() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoEBCDICPT : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoEBCDICPT() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoEBCDICPT() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoEBCDICES : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoEBCDICES() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoEBCDICES() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoEBCDICESA : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoEBCDICESA() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoEBCDICESA() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoEBCDICESS : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoEBCDICESS() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoEBCDICESS() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoEBCDICUK : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoEBCDICUK() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoEBCDICUK() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoEBCDICUS : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoEBCDICUS() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoEBCDICUS() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoUnknown8Bit : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoUnknown8Bit() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoUnknown8Bit() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoMnemonic : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoMnemonic() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoMnemonic() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoMnem : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoMnem() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoMnem() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoVISCII : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoVISCII() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoVISCII() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoVIQR : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoVIQR() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoVIQR() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoKOI8R : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoKOI8R() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoKOI8R() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoHZGB2312 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoHZGB2312() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoHZGB2312() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM866 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM866() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM866() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoPC775Baltic : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoPC775Baltic() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoPC775Baltic() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoKOI8U : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoKOI8U() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoKOI8U() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM00858 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM00858() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM00858() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM00924 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM00924() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM00924() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM01140 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM01140() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM01140() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM01141 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM01141() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM01141() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM01142 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM01142() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM01142() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM01143 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM01143() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM01143() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM01144 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM01144() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM01144() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM01145 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM01145() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM01145() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM01146 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM01146() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM01146() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM01147 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM01147() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM01147() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM01148 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM01148() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM01148() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM01149 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM01149() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM01149() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoBig5HKSCS : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoBig5HKSCS() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoBig5HKSCS() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoIBM1047 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoIBM1047() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoIBM1047() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoPTCP154 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoPTCP154() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoPTCP154() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoAmiga1251 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoAmiga1251() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoAmiga1251() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoKOI7switched : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoKOI7switched() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoKOI7switched() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoBRF : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoBRF() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoBRF() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoTSCII : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoTSCII() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoTSCII() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoWindows1250 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoWindows1250() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoWindows1250() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoWindows1251 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoWindows1251() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoWindows1251() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoWindows1252 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoWindows1252() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoWindows1252() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoWindows1253 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoWindows1253() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoWindows1253() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoWindows1254 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoWindows1254() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoWindows1254() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoWindows1255 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoWindows1255() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoWindows1255() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoWindows1256 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoWindows1256() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoWindows1256() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoWindows1257 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoWindows1257() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoWindows1257() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoWindows1258 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoWindows1258() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoWindows1258() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEncodingInfoTIS620 : public TEncodingInfo
{
	typedef TEncodingInfo inherited;
	
public:
	__classmethod virtual System::UnicodeString __fastcall Alias(int I);
	__classmethod virtual int __fastcall AliasCount();
	__classmethod virtual System::UnicodeString __fastcall Name();
	__classmethod virtual int __fastcall MIBenum();
	__classmethod virtual System::UnicodeString __fastcall PreferredMIMEName();
public:
	/* TObject.Create */ inline __fastcall TEncodingInfoTIS620() : TEncodingInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEncodingInfoTIS620() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* TEncodingInfoClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TEncodingInfoClass);
#endif /* _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::StaticArray<TEncodingInfoClass, 254> Encodings;
}	/* namespace Encodingutils */
}	/* namespace Internal */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_INTERNAL_ENCODINGUTILS)
using namespace Xml::Internal::Encodingutils;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_INTERNAL)
using namespace Xml::Internal;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML)
using namespace Xml;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Xml_Internal_EncodingutilsHPP
