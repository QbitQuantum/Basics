// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdDNSCommon.pas' rev: 34.00 (Android)

#ifndef IddnscommonHPP
#define IddnscommonHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdContainers.hpp>
#include <IdException.hpp>
#include <IdGlobal.hpp>
#include <IdResourceStrings.hpp>
#include <IdResourceStringsProtocols.hpp>
#include <System.Contnrs.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iddnscommon
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EIdDNSServerSyncException;
class DELPHICLASS EIdDNSServerSettingException;
class DELPHICLASS TDNSHeader;
class DELPHICLASS TIdTextModeResourceRecord;
class DELPHICLASS TIdTextModeRRs;
class DELPHICLASS TIdRR_CName;
class DELPHICLASS TIdRR_HINFO;
class DELPHICLASS TIdRR_MB;
class DELPHICLASS TIdRR_MG;
class DELPHICLASS TIdRR_MINFO;
class DELPHICLASS TIdRR_MR;
class DELPHICLASS TIdRR_MX;
class DELPHICLASS TIdRR_NS;
class DELPHICLASS TIdRR_PTR;
class DELPHICLASS TIdRR_SOA;
class DELPHICLASS TIdRR_A;
class DELPHICLASS TIdRR_AAAA;
class DELPHICLASS TIdRR_WKS;
class DELPHICLASS TIdRR_TXT;
class DELPHICLASS TIdRR_Error;
//-- type declarations -------------------------------------------------------
typedef System::StaticArray<System::UnicodeString, 6> Iddnscommon__1;

enum DECLSPEC_DENUM TDNSQueryRecordTypes : unsigned char { DqtA, DqtNS, DqtMD, DqtMF, DqtName, DqtSOA, DqtMB, DqtMG, DqtMR, DqtNull, DqtWKS, DqtPTR, DqtHINFO, DqtMINFO, DqtMX, DqtTXT, DqtNSAP, DqtNSAP_PTR, DqtLOC, DqtIXFR, DqtAXFR, DqtSTAR, DqtAAAA };

enum DECLSPEC_DENUM TDNSServerTypes : unsigned char { stPrimary, stSecondary };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdDNSServerSyncException : public Idexception::EIdSilentException
{
	typedef Idexception::EIdSilentException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdDNSServerSyncException(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdSilentException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdDNSServerSyncException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdSilentException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdDNSServerSyncException(NativeUInt Ident)/* overload */ : Idexception::EIdSilentException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdDNSServerSyncException(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdSilentException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdDNSServerSyncException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdSilentException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdDNSServerSyncException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdSilentException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdDNSServerSyncException(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdSilentException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdDNSServerSyncException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdSilentException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdDNSServerSyncException(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdSilentException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdDNSServerSyncException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdSilentException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdDNSServerSyncException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdSilentException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdDNSServerSyncException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdSilentException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdDNSServerSyncException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIdDNSServerSettingException : public Idexception::EIdSilentException
{
	typedef Idexception::EIdSilentException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdDNSServerSettingException(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdSilentException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdDNSServerSettingException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdSilentException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdDNSServerSettingException(NativeUInt Ident)/* overload */ : Idexception::EIdSilentException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdDNSServerSettingException(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdSilentException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdDNSServerSettingException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdSilentException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdDNSServerSettingException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdSilentException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdDNSServerSettingException(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdSilentException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdDNSServerSettingException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdSilentException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdDNSServerSettingException(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdSilentException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdDNSServerSettingException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdSilentException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdDNSServerSettingException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdSilentException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdDNSServerSettingException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdSilentException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdDNSServerSettingException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDNSHeader : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Word FID;
	System::Word FBitCode;
	System::Word FQDCount;
	System::Word FANCount;
	System::Word FNSCount;
	System::Word FARCount;
	System::Word __fastcall GetAA();
	System::Word __fastcall GetOpCode();
	System::Word __fastcall GetQr();
	System::Word __fastcall GetRA();
	System::Word __fastcall GetRCode();
	System::Word __fastcall GetRD();
	System::Word __fastcall GetTC();
	void __fastcall SetAA(const System::Word Value);
	void __fastcall SetOpCode(const System::Word Value);
	void __fastcall SetQr(const System::Word Value);
	void __fastcall SetRA(const System::Word Value);
	void __fastcall SetRCode(const System::Word Value);
	void __fastcall SetRD(const System::Word Value);
	void __fastcall SetTC(const System::Word Value);
	void __fastcall SetBitCode(const System::Word Value);
	
public:
	__fastcall TDNSHeader();
	void __fastcall ClearByteCode();
	int __fastcall ParseQuery(Idglobal::TIdBytes Data);
	Idglobal::TIdBytes __fastcall GenerateBinaryHeader();
	__property System::Word ID = {read=FID, write=FID, nodefault};
	__property System::Word Qr = {read=GetQr, write=SetQr, nodefault};
	__property System::Word OpCode = {read=GetOpCode, write=SetOpCode, nodefault};
	__property System::Word AA = {read=GetAA, write=SetAA, nodefault};
	__property System::Word TC = {read=GetTC, write=SetTC, nodefault};
	__property System::Word RD = {read=GetRD, write=SetRD, nodefault};
	__property System::Word RA = {read=GetRA, write=SetRA, nodefault};
	__property System::Word RCode = {read=GetRCode, write=SetRCode, nodefault};
	__property System::Word BitCode = {read=FBitCode, write=SetBitCode, nodefault};
	__property System::Word QDCount = {read=FQDCount, write=FQDCount, nodefault};
	__property System::Word ANCount = {read=FANCount, write=FANCount, nodefault};
	__property System::Word NSCount = {read=FNSCount, write=FNSCount, nodefault};
	__property System::Word ARCount = {read=FARCount, write=FARCount, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDNSHeader() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdTextModeResourceRecord : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	Idglobal::TIdBytes FAnswer;
	System::UnicodeString FRRName;
	System::Classes::TStrings* FRRDatas;
	int FTTL;
	int FTypeCode;
	System::UnicodeString FTimeOut;
	System::UnicodeString __fastcall FormatQName(const System::UnicodeString AFullName)/* overload */;
	System::UnicodeString __fastcall FormatQName(const System::UnicodeString AName, const System::UnicodeString AFullName)/* overload */;
	System::UnicodeString __fastcall FormatQNameFull(const System::UnicodeString AFullName);
	Idglobal::TIdBytes __fastcall FormatRecord(const System::UnicodeString AFullName, const Idglobal::TIdBytes ARRData);
	void __fastcall SetRRDatas(System::Classes::TStrings* const Value);
	void __fastcall SetTTL(const int Value);
	
public:
	__fastcall TIdTextModeResourceRecord(const System::UnicodeString ARRName, int ATypeCode);
	__fastcall virtual ~TIdTextModeResourceRecord();
	__property int TypeCode = {read=FTypeCode, nodefault};
	__property System::UnicodeString RRName = {read=FRRName, write=FRRName};
	__property System::Classes::TStrings* RRDatas = {read=FRRDatas, write=SetRRDatas};
	__property int TTL = {read=FTTL, write=SetTTL, nodefault};
	__property System::UnicodeString TimeOut = {read=FTimeOut, write=FTimeOut};
	bool __fastcall ifAddFullName(System::UnicodeString AFullName, System::UnicodeString AGivenName = System::UnicodeString());
	System::UnicodeString __fastcall GetValue(const System::UnicodeString AName);
	void __fastcall SetValue(const System::UnicodeString AName, const System::UnicodeString AValue);
	int __fastcall ItemCount();
	virtual Idglobal::TIdBytes __fastcall BinQueryRecord(System::UnicodeString AFullName);
	virtual System::UnicodeString __fastcall TextRecord(System::UnicodeString AFullName);
	void __fastcall ClearAnswer();
public:
	/* TObject.Create */ inline __fastcall TIdTextModeResourceRecord() : System::TObject() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdTextModeRRs : public Idcontainers::TIdObjectList
{
	typedef Idcontainers::TIdObjectList inherited;
	
public:
	TIdTextModeResourceRecord* operator[](int Index) { return this->Items[Index]; }
	
private:
	System::Classes::TStrings* FItemNames;
	HIDESBASE TIdTextModeResourceRecord* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TIdTextModeResourceRecord* const Value);
	void __fastcall SetItemNames(System::Classes::TStrings* const Value);
	
public:
	__fastcall TIdTextModeRRs();
	__fastcall virtual ~TIdTextModeRRs();
	__property System::Classes::TStrings* ItemNames = {read=FItemNames, write=SetItemNames};
	__property TIdTextModeResourceRecord* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdRR_CName : public TIdTextModeResourceRecord
{
	typedef TIdTextModeResourceRecord inherited;
	
protected:
	System::UnicodeString __fastcall GetCName();
	void __fastcall SetCName(const System::UnicodeString Value);
	
public:
	__fastcall TIdRR_CName();
	__property System::UnicodeString CName = {read=GetCName, write=SetCName};
	virtual Idglobal::TIdBytes __fastcall BinQueryRecord(System::UnicodeString AFullName);
	virtual System::UnicodeString __fastcall TextRecord(System::UnicodeString AFullName);
public:
	/* TIdTextModeResourceRecord.CreateInit */ inline __fastcall TIdRR_CName(const System::UnicodeString ARRName, int ATypeCode) : TIdTextModeResourceRecord(ARRName, ATypeCode) { }
	/* TIdTextModeResourceRecord.Destroy */ inline __fastcall virtual ~TIdRR_CName() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdRR_HINFO : public TIdTextModeResourceRecord
{
	typedef TIdTextModeResourceRecord inherited;
	
protected:
	void __fastcall SetCPU(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetCPU();
	System::UnicodeString __fastcall GetOS();
	void __fastcall SetOS(const System::UnicodeString Value);
	
public:
	__fastcall TIdRR_HINFO();
	__property System::UnicodeString CPU = {read=GetCPU, write=SetCPU};
	__property System::UnicodeString OS = {read=GetOS, write=SetOS};
	virtual Idglobal::TIdBytes __fastcall BinQueryRecord(System::UnicodeString AFullName);
	virtual System::UnicodeString __fastcall TextRecord(System::UnicodeString AFullName);
public:
	/* TIdTextModeResourceRecord.CreateInit */ inline __fastcall TIdRR_HINFO(const System::UnicodeString ARRName, int ATypeCode) : TIdTextModeResourceRecord(ARRName, ATypeCode) { }
	/* TIdTextModeResourceRecord.Destroy */ inline __fastcall virtual ~TIdRR_HINFO() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdRR_MB : public TIdTextModeResourceRecord
{
	typedef TIdTextModeResourceRecord inherited;
	
protected:
	System::UnicodeString __fastcall GetMADName();
	void __fastcall SetMADName(const System::UnicodeString Value);
	
public:
	__fastcall TIdRR_MB();
	__property System::UnicodeString MADName = {read=GetMADName, write=SetMADName};
	virtual Idglobal::TIdBytes __fastcall BinQueryRecord(System::UnicodeString AFullName);
	virtual System::UnicodeString __fastcall TextRecord(System::UnicodeString AFullName);
public:
	/* TIdTextModeResourceRecord.CreateInit */ inline __fastcall TIdRR_MB(const System::UnicodeString ARRName, int ATypeCode) : TIdTextModeResourceRecord(ARRName, ATypeCode) { }
	/* TIdTextModeResourceRecord.Destroy */ inline __fastcall virtual ~TIdRR_MB() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdRR_MG : public TIdTextModeResourceRecord
{
	typedef TIdTextModeResourceRecord inherited;
	
protected:
	System::UnicodeString __fastcall GetMGMName();
	void __fastcall SetMGMName(const System::UnicodeString Value);
	
public:
	__fastcall TIdRR_MG();
	__property System::UnicodeString MGMName = {read=GetMGMName, write=SetMGMName};
	virtual Idglobal::TIdBytes __fastcall BinQueryRecord(System::UnicodeString AFullName);
	virtual System::UnicodeString __fastcall TextRecord(System::UnicodeString AFullName);
public:
	/* TIdTextModeResourceRecord.CreateInit */ inline __fastcall TIdRR_MG(const System::UnicodeString ARRName, int ATypeCode) : TIdTextModeResourceRecord(ARRName, ATypeCode) { }
	/* TIdTextModeResourceRecord.Destroy */ inline __fastcall virtual ~TIdRR_MG() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdRR_MINFO : public TIdTextModeResourceRecord
{
	typedef TIdTextModeResourceRecord inherited;
	
protected:
	void __fastcall SetErrorHandle_Mail(const System::UnicodeString Value);
	void __fastcall SetResponsible_Mail(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetEMail();
	System::UnicodeString __fastcall GetRMail();
	
public:
	__fastcall TIdRR_MINFO();
	__property System::UnicodeString Responsible_Mail = {read=GetRMail, write=SetResponsible_Mail};
	__property System::UnicodeString ErrorHandle_Mail = {read=GetEMail, write=SetErrorHandle_Mail};
	virtual Idglobal::TIdBytes __fastcall BinQueryRecord(System::UnicodeString AFullName);
	virtual System::UnicodeString __fastcall TextRecord(System::UnicodeString AFullName);
public:
	/* TIdTextModeResourceRecord.CreateInit */ inline __fastcall TIdRR_MINFO(const System::UnicodeString ARRName, int ATypeCode) : TIdTextModeResourceRecord(ARRName, ATypeCode) { }
	/* TIdTextModeResourceRecord.Destroy */ inline __fastcall virtual ~TIdRR_MINFO() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdRR_MR : public TIdTextModeResourceRecord
{
	typedef TIdTextModeResourceRecord inherited;
	
protected:
	System::UnicodeString __fastcall GetNewName();
	void __fastcall SetNewName(const System::UnicodeString Value);
	
public:
	__fastcall TIdRR_MR();
	__property System::UnicodeString NewName = {read=GetNewName, write=SetNewName};
	virtual Idglobal::TIdBytes __fastcall BinQueryRecord(System::UnicodeString AFullName);
	virtual System::UnicodeString __fastcall TextRecord(System::UnicodeString AFullName);
public:
	/* TIdTextModeResourceRecord.CreateInit */ inline __fastcall TIdRR_MR(const System::UnicodeString ARRName, int ATypeCode) : TIdTextModeResourceRecord(ARRName, ATypeCode) { }
	/* TIdTextModeResourceRecord.Destroy */ inline __fastcall virtual ~TIdRR_MR() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdRR_MX : public TIdTextModeResourceRecord
{
	typedef TIdTextModeResourceRecord inherited;
	
protected:
	System::UnicodeString __fastcall GetExchang();
	void __fastcall SetExchange(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetPref();
	void __fastcall SetPref(const System::UnicodeString Value);
	
public:
	__fastcall TIdRR_MX();
	__property System::UnicodeString Exchange = {read=GetExchang, write=SetExchange};
	__property System::UnicodeString Preference = {read=GetPref, write=SetPref};
	virtual Idglobal::TIdBytes __fastcall BinQueryRecord(System::UnicodeString AFullName);
	virtual System::UnicodeString __fastcall TextRecord(System::UnicodeString AFullName);
public:
	/* TIdTextModeResourceRecord.CreateInit */ inline __fastcall TIdRR_MX(const System::UnicodeString ARRName, int ATypeCode) : TIdTextModeResourceRecord(ARRName, ATypeCode) { }
	/* TIdTextModeResourceRecord.Destroy */ inline __fastcall virtual ~TIdRR_MX() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdRR_NS : public TIdTextModeResourceRecord
{
	typedef TIdTextModeResourceRecord inherited;
	
protected:
	System::UnicodeString __fastcall GetNS();
	void __fastcall SetNS(const System::UnicodeString Value);
	
public:
	__fastcall TIdRR_NS();
	__property System::UnicodeString NSDName = {read=GetNS, write=SetNS};
	virtual Idglobal::TIdBytes __fastcall BinQueryRecord(System::UnicodeString AFullName);
	virtual System::UnicodeString __fastcall TextRecord(System::UnicodeString AFullName);
public:
	/* TIdTextModeResourceRecord.CreateInit */ inline __fastcall TIdRR_NS(const System::UnicodeString ARRName, int ATypeCode) : TIdTextModeResourceRecord(ARRName, ATypeCode) { }
	/* TIdTextModeResourceRecord.Destroy */ inline __fastcall virtual ~TIdRR_NS() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdRR_PTR : public TIdTextModeResourceRecord
{
	typedef TIdTextModeResourceRecord inherited;
	
protected:
	System::UnicodeString __fastcall GetPTRName();
	void __fastcall SetPTRName(const System::UnicodeString Value);
	
public:
	__fastcall TIdRR_PTR();
	__property System::UnicodeString PTRDName = {read=GetPTRName, write=SetPTRName};
	virtual Idglobal::TIdBytes __fastcall BinQueryRecord(System::UnicodeString AFullName);
	virtual System::UnicodeString __fastcall TextRecord(System::UnicodeString AFullName);
public:
	/* TIdTextModeResourceRecord.CreateInit */ inline __fastcall TIdRR_PTR(const System::UnicodeString ARRName, int ATypeCode) : TIdTextModeResourceRecord(ARRName, ATypeCode) { }
	/* TIdTextModeResourceRecord.Destroy */ inline __fastcall virtual ~TIdRR_PTR() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdRR_SOA : public TIdTextModeResourceRecord
{
	typedef TIdTextModeResourceRecord inherited;
	
protected:
	System::UnicodeString __fastcall GetName(const System::UnicodeString CLabel);
	void __fastcall SetName(const System::UnicodeString CLabel, const System::UnicodeString Value);
	System::UnicodeString __fastcall GetMName();
	System::UnicodeString __fastcall GetRName();
	void __fastcall SetMName(const System::UnicodeString Value);
	void __fastcall SetRName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetMin();
	System::UnicodeString __fastcall GetRefresh();
	System::UnicodeString __fastcall GetRetry();
	System::UnicodeString __fastcall GetSerial();
	void __fastcall SetMin(const System::UnicodeString Value);
	void __fastcall SetRefresh(const System::UnicodeString Value);
	void __fastcall SetRetry(const System::UnicodeString Value);
	void __fastcall SetSerial(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetExpire();
	void __fastcall SetExpire(const System::UnicodeString Value);
	
public:
	__fastcall TIdRR_SOA();
	__property System::UnicodeString MName = {read=GetMName, write=SetMName};
	__property System::UnicodeString RName = {read=GetRName, write=SetRName};
	__property System::UnicodeString Serial = {read=GetSerial, write=SetSerial};
	__property System::UnicodeString Refresh = {read=GetRefresh, write=SetRefresh};
	__property System::UnicodeString Retry = {read=GetRetry, write=SetRetry};
	__property System::UnicodeString Expire = {read=GetExpire, write=SetExpire};
	__property System::UnicodeString Minimum = {read=GetMin, write=SetMin};
	virtual Idglobal::TIdBytes __fastcall BinQueryRecord(System::UnicodeString AFullName);
	virtual System::UnicodeString __fastcall TextRecord(System::UnicodeString AFullName);
public:
	/* TIdTextModeResourceRecord.CreateInit */ inline __fastcall TIdRR_SOA(const System::UnicodeString ARRName, int ATypeCode) : TIdTextModeResourceRecord(ARRName, ATypeCode) { }
	/* TIdTextModeResourceRecord.Destroy */ inline __fastcall virtual ~TIdRR_SOA() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdRR_A : public TIdTextModeResourceRecord
{
	typedef TIdTextModeResourceRecord inherited;
	
protected:
	System::UnicodeString __fastcall GetA();
	void __fastcall SetA(const System::UnicodeString Value);
	
public:
	__fastcall TIdRR_A();
	__property System::UnicodeString Address = {read=GetA, write=SetA};
	virtual Idglobal::TIdBytes __fastcall BinQueryRecord(System::UnicodeString AFullName);
	virtual System::UnicodeString __fastcall TextRecord(System::UnicodeString AFullName);
public:
	/* TIdTextModeResourceRecord.CreateInit */ inline __fastcall TIdRR_A(const System::UnicodeString ARRName, int ATypeCode) : TIdTextModeResourceRecord(ARRName, ATypeCode) { }
	/* TIdTextModeResourceRecord.Destroy */ inline __fastcall virtual ~TIdRR_A() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdRR_AAAA : public TIdTextModeResourceRecord
{
	typedef TIdTextModeResourceRecord inherited;
	
protected:
	System::UnicodeString __fastcall GetA();
	void __fastcall SetA(const System::UnicodeString Value);
	
public:
	__fastcall TIdRR_AAAA();
	__property System::UnicodeString Address = {read=GetA, write=SetA};
	virtual Idglobal::TIdBytes __fastcall BinQueryRecord(System::UnicodeString AFullName);
	virtual System::UnicodeString __fastcall TextRecord(System::UnicodeString AFullName);
public:
	/* TIdTextModeResourceRecord.CreateInit */ inline __fastcall TIdRR_AAAA(const System::UnicodeString ARRName, int ATypeCode) : TIdTextModeResourceRecord(ARRName, ATypeCode) { }
	/* TIdTextModeResourceRecord.Destroy */ inline __fastcall virtual ~TIdRR_AAAA() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdRR_WKS : public TIdTextModeResourceRecord
{
	typedef TIdTextModeResourceRecord inherited;
	
public:
	__fastcall TIdRR_WKS();
public:
	/* TIdTextModeResourceRecord.CreateInit */ inline __fastcall TIdRR_WKS(const System::UnicodeString ARRName, int ATypeCode) : TIdTextModeResourceRecord(ARRName, ATypeCode) { }
	/* TIdTextModeResourceRecord.Destroy */ inline __fastcall virtual ~TIdRR_WKS() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdRR_TXT : public TIdTextModeResourceRecord
{
	typedef TIdTextModeResourceRecord inherited;
	
protected:
	System::UnicodeString __fastcall GetTXT();
	void __fastcall SetTXT(const System::UnicodeString Value);
	
public:
	__fastcall TIdRR_TXT();
	__property System::UnicodeString TXT = {read=GetTXT, write=SetTXT};
	virtual Idglobal::TIdBytes __fastcall BinQueryRecord(System::UnicodeString AFullName);
	virtual System::UnicodeString __fastcall TextRecord(System::UnicodeString AFullName);
public:
	/* TIdTextModeResourceRecord.CreateInit */ inline __fastcall TIdRR_TXT(const System::UnicodeString ARRName, int ATypeCode) : TIdTextModeResourceRecord(ARRName, ATypeCode) { }
	/* TIdTextModeResourceRecord.Destroy */ inline __fastcall virtual ~TIdRR_TXT() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdRR_Error : public TIdTextModeResourceRecord
{
	typedef TIdTextModeResourceRecord inherited;
	
public:
	__fastcall TIdRR_Error();
public:
	/* TIdTextModeResourceRecord.CreateInit */ inline __fastcall TIdRR_Error(const System::UnicodeString ARRName, int ATypeCode) : TIdTextModeResourceRecord(ARRName, ATypeCode) { }
	/* TIdTextModeResourceRecord.Destroy */ inline __fastcall virtual ~TIdRR_Error() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
#define IdDNSServerVersion u"Indy DNSServer 20040121301"
static constexpr System::Int8 cRCodeNoError = System::Int8(0x0);
static constexpr System::Int8 cRCodeFormatErr = System::Int8(0x1);
static constexpr System::Int8 cRCodeServerErr = System::Int8(0x2);
static constexpr System::Int8 cRCodeNameErr = System::Int8(0x3);
static constexpr System::Int8 cRCodeNotImplemented = System::Int8(0x4);
static constexpr System::Int8 cRCodeRefused = System::Int8(0x5);
static constexpr System::Int8 iRCodeQueryNotImplement = System::Int8(0x0);
static constexpr System::Int8 iRCodeQueryReturned = System::Int8(0x1);
static constexpr System::Int8 iRCodeQueryOK = System::Int8(0x2);
static constexpr System::Int8 iRCodeQueryNotFound = System::Int8(0x3);
static constexpr System::Int8 iRCodeNoError = System::Int8(0x0);
static constexpr System::Int8 iRCodeFormatError = System::Int8(0x1);
static constexpr System::Int8 iRCodeServerFailure = System::Int8(0x2);
static constexpr System::Int8 iRCodeNameError = System::Int8(0x3);
static constexpr System::Int8 iRCodeNotImplemented = System::Int8(0x4);
static constexpr System::Int8 iRCodeRefused = System::Int8(0x5);
static constexpr System::Int8 iQr_Question = System::Int8(0x0);
static constexpr System::Int8 iQr_Answer = System::Int8(0x1);
static constexpr System::Int8 iAA_NotAuthoritative = System::Int8(0x0);
static constexpr System::Int8 iAA_Authoritative = System::Int8(0x1);
#define cRCodeQueryNotImplement u"NA"
#define cRCodeQueryReturned u"RC"
#define cRCodeQueryOK u"OK"
#define cRCodeQueryCacheOK u"COK"
#define cRCodeQueryNotFound u"NOTFOUND"
#define cRCodeQueryCacheFindError u"CFoundError"
#define RSDNSServerAXFRError_QuerySequenceError u"First record must be SOA!"
#define RSDNSServerSettingError_MappingHostError u"Host must be an IP address"
#define cOrigin u"$ORIGIN"
#define cInclude u"$INCLUDE"
#define cAAAA u"AAAA"
static constexpr System::WideChar cAt = (System::WideChar)(0x40);
static constexpr System::WideChar cA = (System::WideChar)(0x41);
#define cNS u"NS"
#define cMD u"MD"
#define cMF u"MF"
#define cCName u"CNAME"
#define cSOA u"SOA"
#define cMB u"MB"
#define cMG u"MG"
#define cMR u"MR"
#define cNULL u"NULL"
#define cWKS u"WKS"
#define cPTR u"PTR"
#define cHINFO u"HINFO"
#define cMINFO u"MINFO"
#define cMX u"MX"
#define cTXT u"TXT"
#define cNSAP u"NSAP"
#define cNSAP_PTR u"NSAP-PTR"
#define cLOC u"LOC"
#define cAXFR u"AXFR"
#define cIXFR u"IXFR"
#define cSTAR u"STAR"
extern DELPHI_PACKAGE Iddnscommon__1 cRCodeStrs;
static constexpr System::Int8 Class_IN = System::Int8(0x1);
static constexpr System::Int8 Class_CHAOS = System::Int8(0x3);
static constexpr System::Int8 TypeCode_A = System::Int8(0x1);
static constexpr System::Int8 TypeCode_NS = System::Int8(0x2);
static constexpr System::Int8 TypeCode_MD = System::Int8(0x3);
static constexpr System::Int8 TypeCode_MF = System::Int8(0x4);
static constexpr System::Int8 TypeCode_CName = System::Int8(0x5);
static constexpr System::Int8 TypeCode_SOA = System::Int8(0x6);
static constexpr System::Int8 TypeCode_MB = System::Int8(0x7);
static constexpr System::Int8 TypeCode_MG = System::Int8(0x8);
static constexpr System::Int8 TypeCode_MR = System::Int8(0x9);
static constexpr System::Int8 TypeCode_NULL = System::Int8(0xa);
static constexpr System::Int8 TypeCode_WKS = System::Int8(0xb);
static constexpr System::Int8 TypeCode_PTR = System::Int8(0xc);
static constexpr System::Int8 TypeCode_HINFO = System::Int8(0xd);
static constexpr System::Int8 TypeCode_MINFO = System::Int8(0xe);
static constexpr System::Int8 TypeCode_MX = System::Int8(0xf);
static constexpr System::Int8 TypeCode_TXT = System::Int8(0x10);
static constexpr System::Int8 TypeCode_RP = System::Int8(0x11);
static constexpr System::Int8 TypeCode_AFSDB = System::Int8(0x12);
static constexpr System::Int8 TypeCode_X25 = System::Int8(0x13);
static constexpr System::Int8 TypeCode_ISDN = System::Int8(0x14);
static constexpr System::Int8 TypeCode_RT = System::Int8(0x15);
static constexpr System::Int8 TypeCode_NSAP = System::Int8(0x16);
static constexpr System::Int8 TypeCode_NSAP_PTR = System::Int8(0x17);
static constexpr System::Int8 TypeCode_SIG = System::Int8(0x18);
static constexpr System::Int8 TypeCode_KEY = System::Int8(0x19);
static constexpr System::Int8 TypeCode_PX = System::Int8(0x1a);
static constexpr System::Int8 TypeCode_QPOS = System::Int8(0x1b);
static constexpr System::Int8 TypeCode_AAAA = System::Int8(0x1c);
static constexpr System::Int8 TypeCode_LOC = System::Int8(0x1d);
static constexpr System::Int8 TypeCode_NXT = System::Int8(0x1e);
static constexpr System::Int8 TypeCode_R31 = System::Int8(0x1f);
static constexpr System::Int8 TypeCode_R32 = System::Int8(0x20);
static constexpr System::Int8 TypeCode_Service = System::Int8(0x21);
static constexpr System::Int8 TypeCode_R34 = System::Int8(0x22);
static constexpr System::Int8 TypeCode_NAPTR = System::Int8(0x23);
static constexpr System::Int8 TypeCode_KX = System::Int8(0x24);
static constexpr System::Int8 TypeCode_CERT = System::Int8(0x25);
static constexpr System::Int8 TypeCode_V6Addr = System::Int8(0x26);
static constexpr System::Int8 TypeCode_DNAME = System::Int8(0x27);
static constexpr System::Int8 TypeCode_R40 = System::Int8(0x28);
static constexpr System::Int8 TypeCode_OPTIONAL = System::Int8(0x29);
static constexpr System::Byte TypeCode_IXFR = System::Byte(0xfb);
static constexpr System::Byte TypeCode_AXFR = System::Byte(0xfc);
static constexpr System::Byte TypeCode_STAR = System::Byte(0xff);
static constexpr System::Int8 TypeCode_Error = System::Int8(0x0);
extern DELPHI_PACKAGE Idglobal::TIdBytes __fastcall DomainNameToDNSStr(const System::UnicodeString ADomain);
extern DELPHI_PACKAGE Idglobal::TIdBytes __fastcall NormalStrToDNSStr(const System::UnicodeString Str);
extern DELPHI_PACKAGE Idglobal::TIdBytes __fastcall IPAddrToDNSStr(const System::UnicodeString IPAddress);
extern DELPHI_PACKAGE Idglobal::TIdBytes __fastcall IPv6AAAAToDNSStr(const System::UnicodeString AIPv6Address);
extern DELPHI_PACKAGE bool __fastcall IsValidIPv6(const System::UnicodeString v6Address);
extern DELPHI_PACKAGE System::UnicodeString __fastcall ConvertToValidv6IP(const System::UnicodeString OrgIP);
extern DELPHI_PACKAGE System::UnicodeString __fastcall ConvertToCanonical6IP(const System::UnicodeString OrgIP);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetErrorStr(const int Code, const int Id);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetRCodeStr(int RCode);
extern DELPHI_PACKAGE System::UnicodeString __fastcall ReplaceSpecString(System::UnicodeString Source, System::UnicodeString Target, System::UnicodeString NewString, bool ReplaceAll = true);
extern DELPHI_PACKAGE bool __fastcall IsBig5(System::WideChar ch1, System::WideChar ch2);
}	/* namespace Iddnscommon */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDDNSCOMMON)
using namespace Iddnscommon;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IddnscommonHPP
