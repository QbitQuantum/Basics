// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.EditChar.pas' rev: 34.00 (Windows)

#ifndef Vcltee_EditcharHPP
#define Vcltee_EditcharHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Forms.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.Chart.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Editchar
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall EditSeries(System::Classes::TComponent* const AOwner, Vcltee::Teengine::TChartSeries* const ASeries);
extern DELPHI_PACKAGE void __fastcall EditSeriesMarks(System::Classes::TComponent* const AOwner, Vcltee::Teengine::TChartSeries* const ASeries, bool SymbolsTab = false);
extern DELPHI_PACKAGE void __fastcall EditSeriesDataSource(System::Classes::TComponent* const AOwner, Vcltee::Teengine::TChartSeries* const ASeries);
extern DELPHI_PACKAGE void __fastcall EditChartPage(System::Classes::TComponent* const AOwner, Vcltee::Chart::TCustomChart* const AChart, int PageIndex);
extern DELPHI_PACKAGE void __fastcall EditChartTitle(System::Classes::TComponent* const AOwner, Vcltee::Chart::TChartTitle* const ATitle);
extern DELPHI_PACKAGE void __fastcall EditChartWall(System::Classes::TComponent* const AOwner, Vcltee::Chart::TCustomChartWall* const AWall);
extern DELPHI_PACKAGE void __fastcall EditChartAxis(System::Classes::TComponent* const AOwner, Vcltee::Teengine::TChartAxis* const Axis);
extern DELPHI_PACKAGE void __fastcall EditDSSChart(System::Classes::TComponent* const AOwner, Vcltee::Chart::TCustomChart* const ADSSChart);
extern DELPHI_PACKAGE void __fastcall EditChartTool(System::Classes::TComponent* const AOwner, Vcltee::Teengine::TTeeCustomTool* const AChartTool);
extern DELPHI_PACKAGE void __fastcall EditChartAnimation(System::Classes::TComponent* const AOwner, Vcltee::Teengine::TTeeCustomAnimation* const AChartAnimation);
extern DELPHI_PACKAGE void __fastcall EditChart(System::Classes::TComponent* const AOwner, Vcltee::Chart::TCustomChart* const AChart);
extern DELPHI_PACKAGE void __fastcall EditChartLegend(System::Classes::TComponent* const AOwner, Vcltee::Chart::TCustomChart* const AChart);
extern DELPHI_PACKAGE void __fastcall EditChartPart(System::Classes::TComponent* const AOwner, Vcltee::Chart::TCustomChart* const AChart, const Vcltee::Teengine::TChartClickedPart &Part);
}	/* namespace Editchar */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_EDITCHAR)
using namespace Vcltee::Editchar;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_EditcharHPP
