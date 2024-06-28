// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.GanttCh.pas' rev: 34.00 (Windows)

#ifndef Vcltee_GanttchHPP
#define Vcltee_GanttchHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <Vcl.Graphics.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeEngine.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Ganttch
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TGanttSeries;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TGanttSeries : public Vcltee::Series::TPointSeries
{
	typedef Vcltee::Series::TPointSeries inherited;
	
private:
	Vcltee::Teengine::TMarksCallout* FCallout;
	Vcltee::Teengine::TChartValueList* FEndValues;
	Vcltee::Teengine::TChartValueList* FNextTask;
	Vcltee::Teengine::TMarksCallout* __fastcall GetCallout();
	Vcltee::Tecanvas::TTeePen* __fastcall GetConnectingPen();
	Vcltee::Teengine::TChartValueList* __fastcall GetStartValues();
	void __fastcall SetCallout(Vcltee::Teengine::TMarksCallout* const Value);
	void __fastcall SetConnectingPen(Vcltee::Tecanvas::TTeePen* Value);
	void __fastcall SetEndValues(Vcltee::Teengine::TChartValueList* const Value);
	void __fastcall SetNextTask(Vcltee::Teengine::TChartValueList* const Value);
	void __fastcall SetStartValues(Vcltee::Teengine::TChartValueList* const Value);
	
protected:
	DYNAMIC void __fastcall AddSampleValues(int NumValues, bool OnlyMandatory = false);
	virtual void __fastcall AssignFormatting(Vcltee::Teengine::TChartSeries* Source);
	virtual void __fastcall CalcVerticalMargins(int &TopMargin, int &BottomMargin);
	virtual bool __fastcall ClickedPointer(int ValueIndex, int tmpX, int tmpY, int x, int y)/* overload */;
	virtual void __fastcall DrawValue(int ValueIndex);
	virtual void __fastcall DrawMark(int ValueIndex, const System::UnicodeString St, Vcltee::Teengine::TSeriesMarkPosition* APosition);
	__classmethod virtual System::UnicodeString __fastcall GetEditorClass();
	DYNAMIC void __fastcall PrepareForGallery();
	
public:
	__fastcall virtual TGanttSeries(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TGanttSeries();
	int __fastcall AddGantt(const double AStart, const double AEnd, const double AY, const System::UnicodeString AXLabel = System::UnicodeString());
	int __fastcall AddGanttColor(const double AStart, const double AEnd, const double AY, const System::UnicodeString AXLabel = System::UnicodeString(), System::Uitypes::TColor AColor = (System::Uitypes::TColor)(0x20000000));
	virtual int __fastcall AddXY(const double AXValue, const double AYValue, const System::UnicodeString ALabel = System::UnicodeString(), System::Uitypes::TColor AColor = (System::Uitypes::TColor)(0x20000000));
	DYNAMIC bool __fastcall IsValidSourceOf(Vcltee::Teengine::TChartSeries* Value);
	virtual double __fastcall MaxXValue();
	
__published:
	__property Vcltee::Teengine::TMarksCallout* Callout = {read=GetCallout, write=SetCallout};
	__property ColorEachPoint = {default=1};
	__property Vcltee::Tecanvas::TTeePen* ConnectingPen = {read=GetConnectingPen, write=SetConnectingPen};
	__property Vcltee::Teengine::TChartValueList* StartValues = {read=GetStartValues, write=SetStartValues};
	__property Vcltee::Teengine::TChartValueList* EndValues = {read=FEndValues, write=SetEndValues};
	__property Vcltee::Teengine::TChartValueList* NextTask = {read=FNextTask, write=SetNextTask};
	/* Hoisted overloads: */
	
protected:
	inline bool __fastcall  ClickedPointer(int ValueIndex, int tmpX, int tmpY, const System::Types::TPoint &P){ return Vcltee::Teengine::TChartSeries::ClickedPointer(ValueIndex, tmpX, tmpY, P); }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ganttch */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_GANTTCH)
using namespace Vcltee::Ganttch;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_GanttchHPP
