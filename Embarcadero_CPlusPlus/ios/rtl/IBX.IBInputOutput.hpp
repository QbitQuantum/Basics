// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBInputOutput.pas' rev: 34.00 (iOS)

#ifndef Ibx_IbinputoutputHPP
#define Ibx_IbinputoutputHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IBX.IBSQL.hpp>
#include <System.SysUtils.hpp>
#include <IBX.IBDatabase.hpp>
#include <IBX.IBHeader.hpp>
#include <IBX.IBExternals.hpp>
#include <Data.DB.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibinputoutput
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIBBatch;
class DELPHICLASS TIBBatchInput;
class DELPHICLASS TIBBatchOutput;
class DELPHICLASS TIBOutputDelimitedFile;
class DELPHICLASS TIBInputDelimitedFile;
class DELPHICLASS TIBOutputRawFile;
class DELPHICLASS TIBInputRawFile;
class DELPHICLASS TIBOutputXML;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIBBatch : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	Ibx::Ibdatabase::TIBBase* FBase;
	System::Classes::TStrings* FSQL;
	Ibx::Ibdatabase::TIBDatabase* __fastcall GetDatabase();
	Ibx::Ibdatabase::TIBTransaction* __fastcall GetTransaction();
	void __fastcall SetDatabase(Ibx::Ibdatabase::TIBDatabase* const Value);
	void __fastcall SetTransaction(Ibx::Ibdatabase::TIBTransaction* const Value);
	System::Classes::TStrings* __fastcall GetSQL();
	void __fastcall SetSQL(System::Classes::TStrings* const Value);
	
protected:
	System::Classes::TFileStream* FFile;
	System::UnicodeString FFilename;
	Ibx::Ibsql::TIBXSQLDA* FColumns;
	Ibx::Ibsql::TIBXSQLDA* FParams;
	
public:
	__fastcall virtual TIBBatch(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall TIBBatch()/* overload */;
	__fastcall virtual ~TIBBatch();
	virtual void __fastcall ReadyFile();
	__property Ibx::Ibsql::TIBXSQLDA* Columns = {read=FColumns, write=FColumns};
	__property Ibx::Ibsql::TIBXSQLDA* Params = {read=FParams, write=FParams};
	virtual void __fastcall FinalizeFile();
	
__published:
	__property System::UnicodeString Filename = {read=FFilename, write=FFilename};
	__property Ibx::Ibdatabase::TIBDatabase* Database = {read=GetDatabase, write=SetDatabase};
	__property Ibx::Ibdatabase::TIBTransaction* Transaction = {read=GetTransaction, write=SetTransaction};
	__property System::Classes::TStrings* SQL = {read=GetSQL, write=SetSQL};
};


enum DECLSPEC_DENUM TIBBatchType : unsigned char { ibBatch, ibSingle };

typedef void __fastcall (__closure *TIBBatchEvent)(TIBBatchInput* Sender, int BatchCount, int AffectedRows);

typedef void __fastcall (__closure *TIBBatchSetBlobOrigins)(TIBBatchInput* Sender, Ibx::Ibsql::TIBXSQLDA* Params);

class PASCALIMPLEMENTATION TIBBatchInput : public TIBBatch
{
	typedef TIBBatch inherited;
	
	
private:
	struct DECLSPEC_DRECORD TIBInputStorage
	{
	public:
		int sqllen;
		System::TArray__1<System::Byte> sqldata;
		short sqlind;
		bool sqlindnil;
		void __fastcall SetData(int len, System::PByte asqldata, Ibx::Ibexternals::PShort asqlind);
		Ibx::Ibexternals::PShort __fastcall psqlind();
	};
	
	
	typedef System::DynamicArray<Ibx::Ibheader::TXSQLVAR> _TIBBatchInput__1;
	
	typedef System::DynamicArray<unsigned> _TIBBatchInput__2;
	
	typedef System::DynamicArray<TIBInputStorage> _TIBBatchInput__3;
	
	typedef System::DynamicArray<System::DynamicArray<TIBInputStorage> > _TIBBatchInput__4;
	
	
private:
	int FBatchSize;
	int FTotalReadCount;
	int BufferIndex;
	_TIBBatchInput__1 FParamArray;
	_TIBBatchInput__1 FParamTemplate;
	_TIBBatchInput__2 FRowsAffected;
	_TIBBatchInput__4 FSQLVarData;
	void * *FHandle;
	Ibx::Ibheader::TXSQLDA *sqlda;
	TIBBatchType FBatchType;
	TIBBatchEvent FBatchEvent;
	int FRowsAffectedCount;
	System::UnicodeString FLastError;
	bool FInitialAttempt;
	TIBBatchSetBlobOrigins FSetBlobOrigin;
	int __fastcall xsqlvar_blr_length();
	int __fastcall xsqlvar_msg_length();
	
protected:
	void __fastcall SetBatchSize(const int Value);
	void __fastcall AddToBatch();
	void __fastcall ProcessBatch(Ibx::Ibexternals::PVoid Handle);
	void __fastcall CalculateDataArrays();
	void __fastcall PrepareSQL();
	void __fastcall Cleanup();
	
public:
	virtual bool __fastcall ReadParameters() = 0 ;
	void __fastcall BatchInput();
	void __fastcall BatchInputFrom(Ibx::Ibsql::TIBSQL* SourceSQL)/* overload */;
	void __fastcall BatchInputFrom(Data::Db::TDataSet* SourceSQL)/* overload */;
	__property int BatchSize = {read=FBatchSize, nodefault};
	__property int TotalReadCount = {read=FTotalReadCount, nodefault};
	__property int RowsAffected = {read=FRowsAffectedCount, nodefault};
	__property System::UnicodeString LastError = {read=FLastError};
	
__published:
	__fastcall virtual TIBBatchInput(System::Classes::TComponent* AOwner)/* overload */;
	__property TIBBatchType BatchType = {read=FBatchType, write=FBatchType, nodefault};
	__property TIBBatchEvent OnBatch = {read=FBatchEvent, write=FBatchEvent};
	__property TIBBatchSetBlobOrigins OnSetBlobOrigins = {read=FSetBlobOrigin, write=FSetBlobOrigin};
public:
	/* TIBBatch.Create */ inline __fastcall TIBBatchInput()/* overload */ : TIBBatch() { }
	/* TIBBatch.Destroy */ inline __fastcall virtual ~TIBBatchInput() { }
	
};


typedef void __fastcall (__closure *TIBBeforeWriteColumn)(System::UnicodeString ColumnName, System::UnicodeString &Value);

class PASCALIMPLEMENTATION TIBBatchOutput : public TIBBatch
{
	typedef TIBBatch inherited;
	
public:
	virtual bool __fastcall WriteColumns() = 0 ;
	void __fastcall BatchOutput(Ibx::Ibsql::TIBSQL* aQry = (Ibx::Ibsql::TIBSQL*)(0x0));
public:
	/* TIBBatch.Create */ inline __fastcall virtual TIBBatchOutput(System::Classes::TComponent* AOwner)/* overload */ : TIBBatch(AOwner) { }
	/* TIBBatch.Create */ inline __fastcall TIBBatchOutput()/* overload */ : TIBBatch() { }
	/* TIBBatch.Destroy */ inline __fastcall virtual ~TIBBatchOutput() { }
	
};


class PASCALIMPLEMENTATION TIBOutputDelimitedFile : public TIBBatchOutput
{
	typedef TIBBatchOutput inherited;
	
private:
	System::Sysutils::TEncoding* FEncoding;
	TIBBeforeWriteColumn FBeforeWriteColumn;
	bool FWriteBoM;
	System::Sysutils::TEncoding* __fastcall GetEncoding();
	
protected:
	bool FOutputTitles;
	System::UnicodeString FColDelimiter;
	System::UnicodeString FRowDelimiter;
	
public:
	virtual void __fastcall ReadyFile();
	virtual bool __fastcall WriteColumns();
	__property System::Sysutils::TEncoding* Encoding = {read=GetEncoding, write=FEncoding};
	
__published:
	__property System::UnicodeString ColDelimiter = {read=FColDelimiter, write=FColDelimiter};
	__property bool OutputTitles = {read=FOutputTitles, write=FOutputTitles, nodefault};
	__property System::UnicodeString RowDelimiter = {read=FRowDelimiter, write=FRowDelimiter};
	__property bool WriteBOM = {read=FWriteBoM, write=FWriteBoM, nodefault};
	__property TIBBeforeWriteColumn BeforeWriteColumn = {read=FBeforeWriteColumn, write=FBeforeWriteColumn};
public:
	/* TIBBatch.Create */ inline __fastcall virtual TIBOutputDelimitedFile(System::Classes::TComponent* AOwner)/* overload */ : TIBBatchOutput(AOwner) { }
	/* TIBBatch.Create */ inline __fastcall TIBOutputDelimitedFile()/* overload */ : TIBBatchOutput() { }
	/* TIBBatch.Destroy */ inline __fastcall virtual ~TIBOutputDelimitedFile() { }
	
};


class PASCALIMPLEMENTATION TIBInputDelimitedFile : public TIBBatchInput
{
	typedef TIBBatchInput inherited;
	
private:
	System::Sysutils::TEncoding* FEncoding;
	System::Sysutils::TStringBuilder* FBufferedData;
	bool FNoDataInStream;
	System::UnicodeString FCurrentData;
	System::Classes::TStrings* FTitles;
	System::Sysutils::TEncoding* __fastcall GetEncoding();
	
protected:
	System::UnicodeString FColDelimiter;
	System::UnicodeString FRowDelimiter;
	bool FEOF;
	System::Byte FLookAhead;
	bool FReadBlanksAsNull;
	bool FSkipTitles;
	System::UnicodeString __fastcall ReadLine();
	void __fastcall FillBuffer(System::Sysutils::TEncoding* AnEncoding);
	
public:
	__fastcall virtual TIBInputDelimitedFile(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TIBInputDelimitedFile();
	int __fastcall GetColumn(System::UnicodeString &Col);
	virtual bool __fastcall ReadParameters();
	virtual void __fastcall ReadyFile();
	__property System::Sysutils::TEncoding* Encoding = {read=GetEncoding, write=FEncoding};
	__property System::Classes::TStrings* Titles = {read=FTitles};
	
__published:
	__property System::UnicodeString ColDelimiter = {read=FColDelimiter, write=FColDelimiter};
	__property bool ReadBlanksAsNull = {read=FReadBlanksAsNull, write=FReadBlanksAsNull, nodefault};
	__property System::UnicodeString RowDelimiter = {read=FRowDelimiter, write=FRowDelimiter};
	__property bool SkipTitles = {read=FSkipTitles, write=FSkipTitles, nodefault};
public:
	/* TIBBatch.Create */ inline __fastcall TIBInputDelimitedFile()/* overload */ : TIBBatchInput() { }
	
};


class PASCALIMPLEMENTATION TIBOutputRawFile : public TIBBatchOutput
{
	typedef TIBBatchOutput inherited;
	
public:
	virtual bool __fastcall WriteColumns();
	virtual void __fastcall ReadyFile();
public:
	/* TIBBatch.Create */ inline __fastcall virtual TIBOutputRawFile(System::Classes::TComponent* AOwner)/* overload */ : TIBBatchOutput(AOwner) { }
	/* TIBBatch.Create */ inline __fastcall TIBOutputRawFile()/* overload */ : TIBBatchOutput() { }
	/* TIBBatch.Destroy */ inline __fastcall virtual ~TIBOutputRawFile() { }
	
};


class PASCALIMPLEMENTATION TIBInputRawFile : public TIBBatchInput
{
	typedef TIBBatchInput inherited;
	
public:
	virtual bool __fastcall ReadParameters();
	virtual void __fastcall ReadyFile();
__published:
	/* TIBBatchInput.Create */ inline __fastcall virtual TIBInputRawFile(System::Classes::TComponent* AOwner)/* overload */ : TIBBatchInput(AOwner) { }
	
public:
	/* TIBBatch.Create */ inline __fastcall TIBInputRawFile()/* overload */ : TIBBatchInput() { }
	/* TIBBatch.Destroy */ inline __fastcall virtual ~TIBInputRawFile() { }
	
};


enum DECLSPEC_DENUM TIBXMLFlag : unsigned char { xmlAttribute, xmlDisplayNull, xmlNoHeader };

typedef System::Set<TIBXMLFlag, TIBXMLFlag::xmlAttribute, TIBXMLFlag::xmlNoHeader> TIBXMLFlags;

class PASCALIMPLEMENTATION TIBOutputXML : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::UnicodeString FTableTag;
	System::UnicodeString FHeaderTag;
	System::UnicodeString FDatabaseTag;
	TIBXMLFlags FFlags;
	System::UnicodeString FRowTag;
	System::Classes::TStream* FStream;
	
public:
	void __fastcall WriteXML(Ibx::Ibsql::TIBSQL* SQL);
	void __fastcall OutputXML(Ibx::Ibsql::TIBSQL* OutputObject);
	__property System::Classes::TStream* Stream = {read=FStream, write=FStream};
	
__published:
	__property System::UnicodeString HeaderTag = {read=FHeaderTag, write=FHeaderTag};
	__property System::UnicodeString DatabaseTag = {read=FDatabaseTag, write=FDatabaseTag};
	__property System::UnicodeString TableTag = {read=FTableTag, write=FTableTag};
	__property System::UnicodeString RowTag = {read=FRowTag, write=FRowTag};
	__property TIBXMLFlags Flags = {read=FFlags, write=FFlags, nodefault};
public:
	/* TComponent.Create */ inline __fastcall virtual TIBOutputXML(System::Classes::TComponent* AOwner) : System::Classes::TComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TIBOutputXML() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall OutputXML(Ibx::Ibsql::TIBSQL* sqlObject, TIBOutputXML* OutputObject);
}	/* namespace Ibinputoutput */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBINPUTOUTPUT)
using namespace Ibx::Ibinputoutput;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbinputoutputHPP
