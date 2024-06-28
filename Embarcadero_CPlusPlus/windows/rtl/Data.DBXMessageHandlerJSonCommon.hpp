// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXMessageHandlerJSonCommon.pas' rev: 34.00 (Windows)

#ifndef Data_DbxmessagehandlerjsoncommonHPP
#define Data_DbxmessagehandlerjsoncommonHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.JSON.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXCommonTable.hpp>
#include <Data.DBXMessageHandlerCommon.hpp>
#include <Data.DBXStream.hpp>
#include <Data.DBXStreamPlatform.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxmessagehandlerjsoncommon
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXJSonConnectionHandler;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXJSonConnectionHandler : public Data::Dbxmessagehandlercommon::TDBXConnectionHandler
{
	typedef Data::Dbxmessagehandlercommon::TDBXConnectionHandler inherited;
	
public:
	__fastcall TDBXJSonConnectionHandler(Data::Dbxcommon::TDBXContext* const ADbxContext, const bool AUsesDbxParameters, Data::Dbxstream::TDBXJSonStreamReader* const ADbxStreamReader, Data::Dbxstream::TDBXJSonStreamWriter* const ADbxStreamWriter, Data::Dbxstream::TDBXRowBuffer* const ARowBuffer, const bool AOwnsStreamers);
	__fastcall virtual ~TDBXJSonConnectionHandler();
	Data::Dbxcommontable::TDBXActiveTableReaderItem* __fastcall GetActiveTableReaderItem(Data::Dbxcommontable::TDBXActiveTableReaderList* const ActiveStreamerRowList, const int CommandHandle, const int RowHandle);
	Data::Dbxstreamplatform::TDBXJSonRow* __fastcall CreateJSonRow(const int CommandHandle, const bool OwnsRow);
	Data::Dbxcommon::TDBXReader* __fastcall ReadDBXReader();
	Data::Dbxstreamplatform::TDBXJSonReader* __fastcall ReadDBXReaderMetaData();
	void __fastcall HandleMetadataData();
	System::Json::TJSONObject* __fastcall ReadMetadataData();
	System::Json::TJSONValue* __fastcall ReadCallbackData();
	void __fastcall WriteFirst(const int CommandHandle, const int RowHandle, Data::Dbxstreamplatform::TDBXJSonRow* const DbxRow, Data::Dbxcommon::TDBXReader* const Value, const int BcdFormat);
	bool __fastcall WriteNext(const int CommandHandle, Data::Dbxstreamplatform::TDBXJSonRow* const DbxStreamerRow, Data::Dbxcommon::TDBXReader* const Value, const bool FirstRows);
	void __fastcall WriteDBXReader(const int CommandHandle, Data::Dbxcommontable::TDBXActiveTableReaderItem* const Item);
	Data::Dbxcommon::TDBXParameter* __fastcall ReadParameter();
	void __fastcall ReadParameters(Data::Dbxmessagehandlercommon::TDBXCommandMessage* const Message);
	void __fastcall WriteParameters(Data::Dbxmessagehandlercommon::TDBXCommandMessage* const Message, const bool SomethingWritten);
	void __fastcall WriteCallbackData(System::Json::TJSONValue* const Data, const bool Flush);
	void __fastcall WriteMetadataData(System::Json::TJSONObject* const Data, const bool Flush);
	
protected:
	bool __fastcall IsNoDBXReaderParameterReturn(Data::Dbxcommon::TDBXParameterList* const Parameters);
	bool __fastcall IsOutputDBXReader(Data::Dbxcommon::TDBXParameter* const Parameter);
	bool __fastcall IsConnectionLost();
	
private:
	Data::Dbxstream::TDBXRowBuffer* __fastcall CreateRowBuffer(const int CommandHandle);
	Data::Dbxcommon::TDBXWritableValueArray __fastcall ReadValueTypes(Data::Dbxcommon::TDBXContext* const Context, Data::Dbxcommon::TDBXRow* const Row, const int ColumnCount, const bool UseDbxFlags);
	void __fastcall FlushStreamWriterIfNeeded();
	void __fastcall WriteParameter(Data::Dbxcommon::TDBXParameter* const Parameter);
	
protected:
	Data::Dbxstream::TDBXJSonStreamReader* FDbxStreamReader;
	Data::Dbxstream::TDBXJSonStreamWriter* FDbxStreamWriter;
	Data::Dbxstream::TDBXRowBuffer* FDbxRowBuffer;
	bool FUsesDbxParameters;
	bool FOwnsStreamers;
	
public:
	__property bool ConnectionLost = {read=IsConnectionLost, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxmessagehandlerjsoncommon */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXMESSAGEHANDLERJSONCOMMON)
using namespace Data::Dbxmessagehandlerjsoncommon;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxmessagehandlerjsoncommonHPP
