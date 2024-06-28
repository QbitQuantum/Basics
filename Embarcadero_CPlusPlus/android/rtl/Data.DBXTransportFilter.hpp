// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXTransportFilter.pas' rev: 34.00 (Android)

#ifndef Data_DbxtransportfilterHPP
#define Data_DbxtransportfilterHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.JSON.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXTransport.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxtransportfilter
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXFilterSocketChannel;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXFilterSocketChannel : public Data::Dbxtransport::TDbxChannel
{
	typedef Data::Dbxtransport::TDbxChannel inherited;
	
public:
	virtual bool __fastcall HasLeftover();
	__fastcall TDBXFilterSocketChannel()/* overload */;
	__fastcall TDBXFilterSocketChannel(Data::Dbxtransport::TTransportFilterCollection* const List)/* overload */;
	__fastcall virtual ~TDBXFilterSocketChannel();
	virtual bool __fastcall HasFilters();
	virtual int __fastcall Read(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
	virtual int __fastcall Write(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
	virtual void __fastcall Close();
	virtual void __fastcall Open();
	
protected:
	virtual int __fastcall GetFlag();
	virtual void __fastcall SetChannel(Data::Dbxtransport::TDbxChannel* const Channel);
	virtual void __fastcall SetFilterList(Data::Dbxtransport::TTransportFilterCollection* const Filters);
	virtual Data::Dbxtransport::TDBXChannelInfo* __fastcall GetChannelInfo();
	virtual Data::Dbxcommon::TDBXProperties* __fastcall GetDBXProperties();
	virtual void __fastcall SetDBXProperties(Data::Dbxcommon::TDBXProperties* const Properties);
	virtual bool __fastcall IsConnectionLost();
	
private:
	int __fastcall ConsumeLeftover(const System::TArray__1<System::Byte> Data, const int Offset, const int Len);
	void __fastcall SetLeftover(const System::TArray__1<System::Byte> Data, const int Offset);
	System::Json::TJSONObject* __fastcall FilterParameters(const bool OnlyPublicKeyCryptographs);
	bool __fastcall RestoreFilterList(const System::TArray__1<System::Byte> Data, const int Pos);
	bool __fastcall FillBuffer(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
	int __fastcall SendFilterParameters(const bool OnlyPublickKeyCryptographs);
	int __fastcall ReceiveAndSetConfederateFilterParameters(const bool PublicKeyEncrypted);
	System::TArray__1<System::Byte> __fastcall FilterDataRead(const System::TArray__1<System::Byte> Data, const int Count, const bool OnlyPublikKeyCryptographs);
	System::TArray__1<System::Byte> __fastcall FilterDataWrite(const System::TArray__1<System::Byte> Data, const int Count, const bool OnlyPublikKeyCryptographs);
	
public:
	static int Pendant;
	static int Filtered;
	static int Regular;
	
private:
	Data::Dbxtransport::TTransportFilterCollection* FFilterList;
	bool FOwnFilterList;
	System::TArray__1<System::Byte> FHeaderData;
	Data::Dbxtransport::TDbxChannel* FDelegate;
	int FFilterFlag;
	System::TArray__1<System::Byte> FLeftover;
	int FLeftoverPos;
	
public:
	__property int Flag = {read=GetFlag, nodefault};
	__property Data::Dbxtransport::TDbxChannel* Channel = {read=FDelegate, write=SetChannel};
	__property Data::Dbxtransport::TTransportFilterCollection* FilterList = {write=SetFilterList};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxtransportfilter */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXTRANSPORTFILTER)
using namespace Data::Dbxtransportfilter;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxtransportfilterHPP
