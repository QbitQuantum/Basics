// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeURL.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeurlHPP
#define Vcltee_TeeurlHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Classes.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.Chart.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeurl
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TTeeSeriesSourceFile;
class DELPHICLASS TImportChart;
class DELPHICLASS TChartWebSource;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TTeeSeriesSourceFile : public Vcltee::Teengine::TTeeSeriesSource
{
	typedef Vcltee::Teengine::TTeeSeriesSource inherited;
	
private:
	Vcltee::Chart::TCustomChart* FChart;
	System::UnicodeString FFileName;
	void __fastcall SetChart(Vcltee::Chart::TCustomChart* const Value);
	void __fastcall SetFileName(const System::UnicodeString Value);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	virtual void __fastcall Load();
	void __fastcall LoadFromFile(const System::UnicodeString AFileName);
	virtual void __fastcall LoadFromStream(System::Classes::TStream* AStream);
	void __fastcall LoadFromURL(const System::UnicodeString URL);
	__property Vcltee::Chart::TCustomChart* Chart = {read=FChart, write=SetChart};
	__property System::UnicodeString FileName = {read=FFileName, write=SetFileName};
public:
	/* TTeeSeriesSource.Create */ inline __fastcall virtual TTeeSeriesSourceFile(System::Classes::TComponent* AOwner) : Vcltee::Teengine::TTeeSeriesSource(AOwner) { }
	/* TTeeSeriesSource.Destroy */ inline __fastcall virtual ~TTeeSeriesSourceFile() { }
	
};


class PASCALIMPLEMENTATION TImportChart : public Vcltee::Chart::TCustomChartLink
{
	typedef Vcltee::Chart::TCustomChartLink inherited;
	
private:
	bool FKeepPosition;
	bool FKeepSize;
	System::Classes::TNotifyEvent FOnLoaded;
	System::Classes::TNotifyEvent FOnLoading;
	void __fastcall CheckChart();
	void __fastcall CheckPosition(const System::Types::TRect &Rect);
	
public:
	__fastcall virtual TImportChart(System::Classes::TComponent* AOwner);
	void __fastcall LoadFromFile(const System::UnicodeString FileName);
	void __fastcall LoadFromStream(System::Classes::TStream* const Stream);
	void __fastcall LoadFromURL(const System::UnicodeString URL);
	
__published:
	__property Chart;
	__property bool KeepPosition = {read=FKeepPosition, write=FKeepPosition, default=1};
	__property bool KeepSize = {read=FKeepSize, write=FKeepSize, default=1};
	__property System::Classes::TNotifyEvent OnLoaded = {read=FOnLoaded, write=FOnLoaded};
	__property System::Classes::TNotifyEvent OnLoading = {read=FOnLoading, write=FOnLoading};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TImportChart() { }
	
};


class PASCALIMPLEMENTATION TChartWebSource : public TImportChart
{
	typedef TImportChart inherited;
	
private:
	System::UnicodeString FURL;
	
public:
	__fastcall virtual TChartWebSource(System::Classes::TComponent* AOwner);
	void __fastcall Execute();
	
__published:
	__property System::UnicodeString URL = {read=FURL, write=FURL};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TChartWebSource() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE NativeUInt TeeWinInetDLL;
extern DELPHI_PACKAGE void __fastcall LoadChartFromURL(Vcltee::Chart::TCustomChart* &AChart, const System::UnicodeString URL)/* overload */;
extern DELPHI_PACKAGE void __fastcall LoadChartFromURL(Vcltee::Chart::TCustomChart* &AChart, const System::UnicodeString URL, System::Classes::TStream* AStream)/* overload */;
extern DELPHI_PACKAGE HRESULT __fastcall DownloadURL(const System::UnicodeString URL, System::Classes::TStream* const ToStream, Vcltee::Teeprocs::TDownloadURLCallBack OnCallback = 0x0, bool UseCache = false);
extern DELPHI_PACKAGE System::UnicodeString __fastcall TeeURLErrorMessage(int ErrorCode);
extern DELPHI_PACKAGE bool __fastcall TeeIsURL(System::UnicodeString St);
extern DELPHI_PACKAGE bool __fastcall TeeURLExists(System::UnicodeString URL);
}	/* namespace Teeurl */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEURL)
using namespace Vcltee::Teeurl;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeurlHPP
