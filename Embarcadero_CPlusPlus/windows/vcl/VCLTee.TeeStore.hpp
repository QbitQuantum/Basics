// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeStore.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeestoreHPP
#define Vcltee_TeestoreHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.UITypes.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.Chart.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teestore
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TSeriesData;
class DELPHICLASS TSeriesDataText;
class DELPHICLASS TSeriesDataXML;
class DELPHICLASS TSeriesDataHTML;
class DELPHICLASS TSeriesDataXLS;
class DELPHICLASS TSeriesDataJSON;
//-- type declarations -------------------------------------------------------
typedef bool __fastcall (__closure *TProcTeeCheckError)(const System::UnicodeString Message);

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSeriesData : public Vcltee::Teeprocs::TTeeExportData
{
	typedef Vcltee::Teeprocs::TTeeExportData inherited;
	
private:
	Vcltee::Chart::TCustomChart* FChart;
	bool FIncludeColors;
	bool FIncludeIndex;
	bool FIncludeHeader;
	bool FIncludeLabels;
	Vcltee::Teengine::TChartSeries* FSeries;
	Vcltee::Teengine::TCustomSeriesList* FSeriesList;
	bool FUseSeriesFormat;
	System::UnicodeString FValueFormat;
	void __fastcall Prepare()/* overload */;
	
protected:
	Vcltee::Teengine::TeeFormatFlag IFormat;
	virtual void __fastcall GuessSeriesFormat()/* overload */;
	virtual void __fastcall GuessSeriesFormat(Vcltee::Teengine::TChartSeries* ASeries)/* overload */;
	int __fastcall MaxSeriesCount();
	virtual System::UnicodeString __fastcall PointToString(int Index);
	void __fastcall Prepare(Vcltee::Teengine::TChartSeries* const ASeries)/* overload */;
	int __fastcall TotalColumns();
	int __fastcall TotalRows();
	int __fastcall TotalSeries();
	
public:
	__fastcall virtual TSeriesData(Vcltee::Chart::TCustomChart* AChart, Vcltee::Teengine::TChartSeries* ASeries);
	__fastcall virtual ~TSeriesData();
	virtual System::UnicodeString __fastcall AsString();
	DYNAMIC void __fastcall SaveToStream(System::Classes::TStream* AStream);
	bool __fastcall ValidSeries(Vcltee::Teengine::TChartSeries* const ASeries);
	System::UnicodeString __fastcall ValueToString(Vcltee::Teengine::TChartSeries* const ASeries, const double Value);
	__property Vcltee::Chart::TCustomChart* Chart = {read=FChart, write=FChart};
	__property Vcltee::Teengine::TChartSeries* Series = {read=FSeries, write=FSeries};
	__property Vcltee::Teengine::TCustomSeriesList* SeriesList = {read=FSeriesList};
	
__published:
	__property bool IncludeColors = {read=FIncludeColors, write=FIncludeColors, default=0};
	__property bool IncludeHeader = {read=FIncludeHeader, write=FIncludeHeader, default=0};
	__property bool IncludeIndex = {read=FIncludeIndex, write=FIncludeIndex, default=0};
	__property bool IncludeLabels = {read=FIncludeLabels, write=FIncludeLabels, default=1};
	__property bool UseSeriesFormat = {read=FUseSeriesFormat, write=FUseSeriesFormat, default=0};
	__property System::UnicodeString ValueFormat = {read=FValueFormat, write=FValueFormat};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSeriesDataText : public TSeriesData
{
	typedef TSeriesData inherited;
	
private:
	System::WideChar FTextDelimiter;
	System::UnicodeString FTextQuotes;
	
protected:
	virtual void __fastcall GuessSeriesFormat()/* overload */;
	virtual System::UnicodeString __fastcall PointToString(int Index);
	
public:
	__fastcall virtual TSeriesDataText(Vcltee::Chart::TCustomChart* AChart, Vcltee::Teengine::TChartSeries* ASeries);
	virtual System::UnicodeString __fastcall AsString();
	
__published:
	__property System::WideChar TextDelimiter = {read=FTextDelimiter, write=FTextDelimiter, default=9};
	__property System::UnicodeString TextQuotes = {read=FTextQuotes, write=FTextQuotes};
public:
	/* TSeriesData.Destroy */ inline __fastcall virtual ~TSeriesDataText() { }
	
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  GuessSeriesFormat(Vcltee::Teengine::TChartSeries* ASeries){ TSeriesData::GuessSeriesFormat(ASeries); }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSeriesDataXML : public TSeriesData
{
	typedef TSeriesData inherited;
	
private:
	System::UnicodeString FEncoding;
	bool __fastcall IsEncodingStored();
	
public:
	__fastcall virtual TSeriesDataXML(Vcltee::Chart::TCustomChart* AChart, Vcltee::Teengine::TChartSeries* ASeries);
	virtual System::UnicodeString __fastcall AsString();
	
__published:
	__property System::UnicodeString Encoding = {read=FEncoding, write=FEncoding, stored=IsEncodingStored};
	__property IncludeHeader = {default=1};
public:
	/* TSeriesData.Destroy */ inline __fastcall virtual ~TSeriesDataXML() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSeriesDataHTML : public TSeriesData
{
	typedef TSeriesData inherited;
	
protected:
	virtual System::UnicodeString __fastcall PointToString(int Index);
	
public:
	bool FirstSeriesLabels;
	virtual System::UnicodeString __fastcall AsString();
public:
	/* TSeriesData.Create */ inline __fastcall virtual TSeriesDataHTML(Vcltee::Chart::TCustomChart* AChart, Vcltee::Teengine::TChartSeries* ASeries) : TSeriesData(AChart, ASeries) { }
	/* TSeriesData.Destroy */ inline __fastcall virtual ~TSeriesDataHTML() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSeriesDataXLS : public TSeriesData
{
	typedef TSeriesData inherited;
	
public:
	DYNAMIC void __fastcall SaveToStream(System::Classes::TStream* AStream);
public:
	/* TSeriesData.Create */ inline __fastcall virtual TSeriesDataXLS(Vcltee::Chart::TCustomChart* AChart, Vcltee::Teengine::TChartSeries* ASeries) : TSeriesData(AChart, ASeries) { }
	/* TSeriesData.Destroy */ inline __fastcall virtual ~TSeriesDataXLS() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TJSONDateTimeFormat : unsigned char { jdTimeStamp, jdJavaScript };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TSeriesDataJSON : public TSeriesData
{
	typedef TSeriesData inherited;
	
private:
	TJSONDateTimeFormat FDateFormat;
	
public:
	__fastcall virtual TSeriesDataJSON(Vcltee::Chart::TCustomChart* AChart, Vcltee::Teengine::TChartSeries* ASeries);
	virtual System::UnicodeString __fastcall AsString();
	__property TJSONDateTimeFormat DateTimeFormat = {read=FDateFormat, write=FDateFormat, nodefault};
public:
	/* TSeriesData.Destroy */ inline __fastcall virtual ~TSeriesDataJSON() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall ConvertTeeToBinary(System::Classes::TStream* const SInput, System::Classes::TStream* const SOutput);
extern DELPHI_PACKAGE void __fastcall ConvertTeeToText(System::Classes::TStream* const SInput, System::Classes::TStream* const SOutput);
extern DELPHI_PACKAGE void __fastcall LoadChartFromStreamCheck(Vcltee::Chart::TCustomChart* const AChart, System::Classes::TStream* const AStream, TProcTeeCheckError ACheckError = 0x0, bool TryReadData = false);
extern DELPHI_PACKAGE void __fastcall LoadChartFromStream(Vcltee::Chart::TCustomChart* const AChart, System::Classes::TStream* const AStream);
extern DELPHI_PACKAGE System::UnicodeString __fastcall TeeCheckExtension(const System::UnicodeString AFileName);
extern DELPHI_PACKAGE void __fastcall LoadChartFromFileCheck(Vcltee::Chart::TCustomChart* const AChart, const System::UnicodeString AName, TProcTeeCheckError ACheckError);
extern DELPHI_PACKAGE void __fastcall LoadChartFromFile(Vcltee::Chart::TCustomChart* const AChart, const System::UnicodeString AFileName);
extern DELPHI_PACKAGE void __fastcall ConvertTeeFileToText(const System::UnicodeString InputFile, const System::UnicodeString OutputFile);
extern DELPHI_PACKAGE void __fastcall ConvertTeeFileToBinary(const System::UnicodeString InputFile, const System::UnicodeString OutputFile);
extern DELPHI_PACKAGE void __fastcall SaveChartToStream(Vcltee::Chart::TCustomChart* const AChart, System::Classes::TStream* const AStream, bool IncludeData = true, bool TextFormat = false);
extern DELPHI_PACKAGE void __fastcall SaveChartToXMLStream(Vcltee::Chart::TCustomChart* const AChart, System::Classes::TStream* const AStream, bool IncludeData = true, bool XMLHeader = true);
extern DELPHI_PACKAGE void __fastcall SaveChartToFile(Vcltee::Chart::TCustomChart* const AChart, const System::UnicodeString AFileName, bool IncludeData = true, bool TextFormat = false);
extern DELPHI_PACKAGE void __fastcall SaveChartToXMLFile(Vcltee::Chart::TCustomChart* const AChart, const System::UnicodeString AFileName, bool IncludeData = true, bool XMLHeader = true);
}	/* namespace Teestore */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEESTORE)
using namespace Vcltee::Teestore;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeestoreHPP
