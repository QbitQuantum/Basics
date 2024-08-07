﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdDNSResolver.pas' rev: 34.00 (Windows)

#ifndef IddnsresolverHPP
#define IddnsresolverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdBuffer.hpp>
#include <IdComponent.hpp>
#include <IdGlobal.hpp>
#include <IdExceptionCore.hpp>
#include <IdNetworkCalculator.hpp>
#include <IdGlobalProtocols.hpp>
#include <IdDNSCommon.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdUDPClient.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------
#if defined(_VCL_ALIAS_RECORDS)
#if !defined(UNICODE)
#pragma alias "@Iddnsresolver@TIdDNSResolver@SetPortA$qqrxus"="@Iddnsresolver@TIdDNSResolver@SetPort$qqrxus"
#else
#pragma alias "@Iddnsresolver@TIdDNSResolver@SetPortW$qqrxus"="@Iddnsresolver@TIdDNSResolver@SetPort$qqrxus"
#endif
#endif

namespace Iddnsresolver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TResultRecord;
class DELPHICLASS TRDATARecord;
class DELPHICLASS TARecord;
class DELPHICLASS TAAAARecord;
class DELPHICLASS TWKSRecord;
class DELPHICLASS TMXRecord;
class DELPHICLASS TTextRecord;
class DELPHICLASS TErrorRecord;
class DELPHICLASS THINFORecord;
class DELPHICLASS TMINFORecord;
class DELPHICLASS TSOARecord;
class DELPHICLASS TNAMERecord;
class DELPHICLASS TNSRecord;
class DELPHICLASS TCNRecord;
class DELPHICLASS TDNAMERecord;
class DELPHICLASS TSRVRecord;
class DELPHICLASS TNAPTRRecord;
class DELPHICLASS TQueryResult;
class DELPHICLASS TPTRRecord;
class DELPHICLASS TIdDNSResolver;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TQueryRecordTypes : unsigned char { qtA, qtNS, qtMD, qtMF, qtName, qtSOA, qtMB, qtMG, qtMR, qtNull, qtWKS, qtPTR, qtHINFO, qtMINFO, qtMX, qtTXT, qtRT, qtNSAP, qtNSAP_PTR, qtSIG, qtAAAA, qtService, qtNAPTR, qtCERT, qtV6Addr, qtDName, qtR40, qtOptional, qtIXFR, qtAXFR, qtSTAR };

typedef System::Set<TQueryRecordTypes, TQueryRecordTypes::qtA, TQueryRecordTypes::qtSTAR> TQueryType;

enum DECLSPEC_DENUM TResultSection : unsigned char { rsAnswer, rsNameServer, rsAdditional };

typedef System::Set<TResultSection, TResultSection::rsAnswer, TResultSection::rsAdditional> TResultSections;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TResultRecord : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
protected:
	TQueryRecordTypes FRecType;
	System::Word FRecClass;
	System::UnicodeString FName;
	unsigned FTTL;
	int FRDataLength;
	Idglobal::TIdBytes FRData;
	TResultSection FSection;
	System::Word FTypeCode;
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall Parse(Idglobal::TIdBytes CompleteMessage, int APos);
	__property TQueryRecordTypes RecType = {read=FRecType, nodefault};
	__property System::Word RecClass = {read=FRecClass, nodefault};
	__property System::UnicodeString Name = {read=FName};
	__property unsigned TTL = {read=FTTL, nodefault};
	__property int RDataLength = {read=FRDataLength, nodefault};
	__property Idglobal::TIdBytes RData = {read=FRData};
	__property TResultSection Section = {read=FSection, nodefault};
	__property System::Word TypeCode = {read=FTypeCode, nodefault};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TResultRecord(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TResultRecord() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* TResultRecordClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TResultRecordClass);
#endif /* _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TRDATARecord : public TResultRecord
{
	typedef TResultRecord inherited;
	
protected:
	System::UnicodeString FIPAddress;
	
public:
	virtual void __fastcall Parse(Idglobal::TIdBytes CompleteMessage, int APos);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property System::UnicodeString IPAddress = {read=FIPAddress};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TRDATARecord(System::Classes::TCollection* Collection) : TResultRecord(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TRDATARecord() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TARecord : public TRDATARecord
{
	typedef TRDATARecord inherited;
	
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TARecord(System::Classes::TCollection* Collection) : TRDATARecord(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TARecord() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAAAARecord : public TResultRecord
{
	typedef TResultRecord inherited;
	
protected:
	System::UnicodeString FAddress;
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall Parse(Idglobal::TIdBytes CompleteMessage, int APos);
	__property System::UnicodeString Address = {read=FAddress};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TAAAARecord(System::Classes::TCollection* Collection) : TResultRecord(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TAAAARecord() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWKSRecord : public TResultRecord
{
	typedef TResultRecord inherited;
	
protected:
	int FByteCount;
	Idglobal::TIdBytes FData;
	System::UnicodeString FIPAddress;
	System::Word FProtocol;
	System::Byte __fastcall GetABit(int AIndex);
	
public:
	virtual void __fastcall Parse(Idglobal::TIdBytes CompleteMessage, int APos);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property System::UnicodeString IPAddress = {read=FIPAddress};
	__property System::Word Protocol = {read=FProtocol, nodefault};
	__property System::Byte BitMap[int index] = {read=GetABit};
	__property int ByteCount = {read=FByteCount, nodefault};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TWKSRecord(System::Classes::TCollection* Collection) : TResultRecord(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TWKSRecord() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMXRecord : public TResultRecord
{
	typedef TResultRecord inherited;
	
protected:
	System::UnicodeString FExchangeServer;
	System::Word FPreference;
	
public:
	virtual void __fastcall Parse(Idglobal::TIdBytes CompleteMessage, int APos);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property System::UnicodeString ExchangeServer = {read=FExchangeServer};
	__property System::Word Preference = {read=FPreference, nodefault};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TMXRecord(System::Classes::TCollection* Collection) : TResultRecord(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TMXRecord() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TTextRecord : public TResultRecord
{
	typedef TResultRecord inherited;
	
protected:
	System::Classes::TStrings* FText;
	
public:
	__fastcall virtual TTextRecord(System::Classes::TCollection* Collection);
	__fastcall virtual ~TTextRecord();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall Parse(Idglobal::TIdBytes CompleteMessage, int APos);
	__property System::Classes::TStrings* Text = {read=FText};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TErrorRecord : public TResultRecord
{
	typedef TResultRecord inherited;
	
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TErrorRecord(System::Classes::TCollection* Collection) : TResultRecord(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TErrorRecord() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION THINFORecord : public TTextRecord
{
	typedef TTextRecord inherited;
	
protected:
	System::UnicodeString FCPU;
	System::UnicodeString FOS;
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall Parse(Idglobal::TIdBytes CompleteMessage, int APos);
	__property System::UnicodeString CPU = {read=FCPU};
	__property System::UnicodeString OS = {read=FOS};
public:
	/* TTextRecord.Create */ inline __fastcall virtual THINFORecord(System::Classes::TCollection* Collection) : TTextRecord(Collection) { }
	/* TTextRecord.Destroy */ inline __fastcall virtual ~THINFORecord() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMINFORecord : public TResultRecord
{
	typedef TResultRecord inherited;
	
protected:
	System::UnicodeString FResponsiblePerson;
	System::UnicodeString FErrorMailbox;
	
public:
	virtual void __fastcall Parse(Idglobal::TIdBytes CompleteMessage, int APos);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property System::UnicodeString ResponsiblePersonMailbox = {read=FResponsiblePerson};
	__property System::UnicodeString ErrorMailbox = {read=FErrorMailbox};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TMINFORecord(System::Classes::TCollection* Collection) : TResultRecord(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TMINFORecord() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSOARecord : public TResultRecord
{
	typedef TResultRecord inherited;
	
protected:
	unsigned FSerial;
	unsigned FMinimumTTL;
	unsigned FRefresh;
	unsigned FRetry;
	System::UnicodeString FMNAME;
	System::UnicodeString FRNAME;
	unsigned FExpire;
	
public:
	virtual void __fastcall Parse(Idglobal::TIdBytes CompleteMessage, int APos);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property System::UnicodeString Primary = {read=FMNAME};
	__property System::UnicodeString ResponsiblePerson = {read=FRNAME};
	__property unsigned Serial = {read=FSerial, nodefault};
	__property unsigned Refresh = {read=FRefresh, nodefault};
	__property unsigned Retry = {read=FRetry, nodefault};
	__property unsigned Expire = {read=FExpire, nodefault};
	__property unsigned MinimumTTL = {read=FMinimumTTL, nodefault};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TSOARecord(System::Classes::TCollection* Collection) : TResultRecord(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TSOARecord() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TNAMERecord : public TResultRecord
{
	typedef TResultRecord inherited;
	
protected:
	System::UnicodeString FHostName;
	
public:
	virtual void __fastcall Parse(Idglobal::TIdBytes CompleteMessage, int APos);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property System::UnicodeString HostName = {read=FHostName};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TNAMERecord(System::Classes::TCollection* Collection) : TResultRecord(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TNAMERecord() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TNSRecord : public TNAMERecord
{
	typedef TNAMERecord inherited;
	
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TNSRecord(System::Classes::TCollection* Collection) : TNAMERecord(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TNSRecord() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCNRecord : public TNAMERecord
{
	typedef TNAMERecord inherited;
	
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TCNRecord(System::Classes::TCollection* Collection) : TNAMERecord(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TCNRecord() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDNAMERecord : public TNAMERecord
{
	typedef TNAMERecord inherited;
	
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TDNAMERecord(System::Classes::TCollection* Collection) : TNAMERecord(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TDNAMERecord() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSRVRecord : public TResultRecord
{
	typedef TResultRecord inherited;
	
private:
	System::UnicodeString FService;
	System::UnicodeString FProtocol;
	int FPriority;
	int FWeight;
	int FPort;
	System::UnicodeString FTarget;
	System::UnicodeString FOriginalName;
	bool __fastcall IsValidIdent(const System::UnicodeString aStr);
	System::UnicodeString __fastcall CleanIdent(const System::UnicodeString aStr);
	
public:
	virtual void __fastcall Parse(Idglobal::TIdBytes CompleteMessage, int APos);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property System::UnicodeString OriginalName = {read=FOriginalName};
	__property System::UnicodeString Service = {read=FService};
	__property System::UnicodeString Protocol = {read=FProtocol};
	__property int Priority = {read=FPriority, nodefault};
	__property int Weight = {read=FWeight, nodefault};
	__property int Port = {read=FPort, nodefault};
	__property System::UnicodeString Target = {read=FTarget};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TSRVRecord(System::Classes::TCollection* Collection) : TResultRecord(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TSRVRecord() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TNAPTRRecord : public TResultRecord
{
	typedef TResultRecord inherited;
	
private:
	int FOrder;
	int FPreference;
	System::UnicodeString FFlags;
	System::UnicodeString FService;
	System::UnicodeString FRegExp;
	System::UnicodeString FReplacement;
	
public:
	virtual void __fastcall Parse(Idglobal::TIdBytes CompleteMessage, int APos);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property int Order = {read=FOrder, nodefault};
	__property int Preference = {read=FPreference, nodefault};
	__property System::UnicodeString Flags = {read=FFlags};
	__property System::UnicodeString Service = {read=FService};
	__property System::UnicodeString RegExp = {read=FRegExp};
	__property System::UnicodeString Replacement = {read=FReplacement};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TNAPTRRecord(System::Classes::TCollection* Collection) : TResultRecord(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TNAPTRRecord() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TQueryResult : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TResultRecord* operator[](int Index) { return this->Items[Index]; }
	
protected:
	System::UnicodeString FDomainName;
	System::Word FQueryClass;
	System::Word FQueryType;
	System::Classes::TStringList* FQueryPointerList;
	HIDESBASE void __fastcall SetItem(int Index, TResultRecord* Value);
	HIDESBASE TResultRecord* __fastcall GetItem(int Index);
	
public:
	__fastcall TQueryResult();
	__fastcall virtual ~TQueryResult();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	HIDESBASE TResultRecord* __fastcall Add(Idglobal::TIdBytes Answer, int &APos);
	HIDESBASE void __fastcall Clear();
	void __fastcall FilterBySection(const TResultSections AKeep = (TResultSections() << TResultSection::rsAnswer ));
	void __fastcall FilterByClass(const TResultRecordClass AKeep);
	__property System::Word QueryClass = {read=FQueryClass, nodefault};
	__property System::Word QueryType = {read=FQueryType, nodefault};
	__property System::UnicodeString DomainName = {read=FDomainName};
	__property TResultRecord* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TPTRRecord : public TNAMERecord
{
	typedef TNAMERecord inherited;
	
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TPTRRecord(System::Classes::TCollection* Collection) : TNAMERecord(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TPTRRecord() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TIdDNSResolver : public Idtcpconnection::TIdTCPConnection
{
	typedef Idtcpconnection::TIdTCPConnection inherited;
	
protected:
	bool FAllowRecursiveQueries;
	Idglobal::TIdBytes FInternalQuery;
	int FQuestionLength;
	System::UnicodeString FHost;
	Idglobal::TIdIPVersion FIPVersion;
	System::Word FPort;
	TQueryResult* FQueryResult;
	TQueryType FQueryType;
	int FWaitingTime;
	Idglobal::TIdBytes FPlainTextResult;
	Iddnscommon::TDNSHeader* FDNSHeader;
	void __fastcall SetInternalQuery(const Idglobal::TIdBytes Value);
	void __fastcall SetPlainTextResult(const Idglobal::TIdBytes Value);
	virtual void __fastcall InitComponent();
	virtual void __fastcall SetIPVersion(const Idglobal::TIdIPVersion AValue);
	virtual void __fastcall SetPort(const System::Word AValue);
	
public:
	__property Iddnscommon::TDNSHeader* DNSHeader = {read=FDNSHeader};
	void __fastcall ClearInternalQuery();
	__fastcall virtual ~TIdDNSResolver();
	void __fastcall ParseAnswers(Iddnscommon::TDNSHeader* DNSHeader, Idglobal::TIdBytes Answer, bool ResetResult = true);
	void __fastcall CreateQuery(System::UnicodeString ADomain, Iddnscommon::TIdRR_SOA* SOARR, int QueryClass = 0x1);
	void __fastcall FillResult(Idglobal::TIdBytes AResult, bool checkID = true, bool ResetResult = true);
	void __fastcall FillResultWithOutCheckId _DEPRECATED_ATTRIBUTE1("Use FillResult() with checkID=False") (Idglobal::TIdBytes AResult);
	void __fastcall Resolve(System::UnicodeString ADomain, Iddnscommon::TIdRR_SOA* SOARR = (Iddnscommon::TIdRR_SOA*)(0x0), int QClass = 0x1);
	__property TQueryResult* QueryResult = {read=FQueryResult};
	__property Idglobal::TIdBytes InternalQuery = {read=FInternalQuery, write=SetInternalQuery};
	__property Idglobal::TIdBytes PlainTextResult = {read=FPlainTextResult, write=SetPlainTextResult};
	
__published:
	__property TQueryType QueryType = {read=FQueryType, write=FQueryType, nodefault};
	__property int WaitingTime = {read=FWaitingTime, write=FWaitingTime, nodefault};
	__property bool AllowRecursiveQueries = {read=FAllowRecursiveQueries, write=FAllowRecursiveQueries, nodefault};
	__property System::UnicodeString Host = {read=FHost, write=FHost};
	__property System::Word Port = {read=FPort, write=SetPort, default=53};
	__property Idglobal::TIdIPVersion IPVersion = {read=FIPVersion, write=SetIPVersion, default=0};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdDNSResolver(System::Classes::TComponent* AOwner)/* overload */ : Idtcpconnection::TIdTCPConnection(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdDNSResolver()/* overload */ : Idtcpconnection::TIdTCPConnection() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static const System::Int8 QueryRecordCount = System::Int8(0x1e);
extern DELPHI_PACKAGE System::StaticArray<System::Word, 31> QueryRecordValues;
extern DELPHI_PACKAGE System::StaticArray<TQueryRecordTypes, 31> QueryRecordTypes;
extern DELPHI_PACKAGE System::UnicodeString __fastcall DNSStrToDomain(const Idglobal::TIdBytes DNSStr, int &VPos);
extern DELPHI_PACKAGE System::UnicodeString __fastcall NextDNSLabel(const Idglobal::TIdBytes DNSStr, int &VPos);
}	/* namespace Iddnsresolver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDDNSRESOLVER)
using namespace Iddnsresolver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IddnsresolverHPP
