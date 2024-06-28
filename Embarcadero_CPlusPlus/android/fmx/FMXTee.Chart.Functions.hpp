// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Chart.Functions.pas' rev: 34.00 (Android)

#ifndef Fmxtee_Chart_FunctionsHPP
#define Fmxtee_Chart_FunctionsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <FMXTee.Engine.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Chart
{
namespace Functions
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAddTeeFunction;
class DELPHICLASS TManySeriesTeeFunction;
class DELPHICLASS TSubtractTeeFunction;
class DELPHICLASS TMultiplyTeeFunction;
class DELPHICLASS TDivideTeeFunction;
class DELPHICLASS THighTeeFunction;
class DELPHICLASS TLowTeeFunction;
class DELPHICLASS TAverageTeeFunction;
class DELPHICLASS TCustomTeeFunction;
class DELPHICLASS TCustomSortedFunction;
class DELPHICLASS TMedianTeeFunction;
class DELPHICLASS TModeTeeFunction;
class DELPHICLASS TSubsetTeeFunction;
class DELPHICLASS TParetoTeeFunction;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TAddTeeFunction : public Fmxtee::Engine::TTeeFunction
{
	typedef Fmxtee::Engine::TTeeFunction inherited;
	
protected:
	virtual double __fastcall CalculateValue(const Fmxtee::Engine::TChartValues Values);
	virtual void __fastcall PrepareForGallery(Fmxtee::Engine::TCustomAxisPanel* const Chart);
public:
	/* TTeeFunction.Create */ inline __fastcall virtual TAddTeeFunction(System::Classes::TComponent* AOwner) : Fmxtee::Engine::TTeeFunction(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TAddTeeFunction() { }
	
};


class PASCALIMPLEMENTATION TManySeriesTeeFunction : public Fmxtee::Engine::TTeeFunction
{
	typedef Fmxtee::Engine::TTeeFunction inherited;
	
public:
	/* TTeeFunction.Create */ inline __fastcall virtual TManySeriesTeeFunction(System::Classes::TComponent* AOwner) : Fmxtee::Engine::TTeeFunction(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TManySeriesTeeFunction() { }
	
};


class PASCALIMPLEMENTATION TSubtractTeeFunction : public TManySeriesTeeFunction
{
	typedef TManySeriesTeeFunction inherited;
	
protected:
	virtual double __fastcall CalculateValue(const Fmxtee::Engine::TChartValues Values);
	virtual void __fastcall PrepareForGallery(Fmxtee::Engine::TCustomAxisPanel* const Chart);
public:
	/* TTeeFunction.Create */ inline __fastcall virtual TSubtractTeeFunction(System::Classes::TComponent* AOwner) : TManySeriesTeeFunction(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TSubtractTeeFunction() { }
	
};


class PASCALIMPLEMENTATION TMultiplyTeeFunction : public TManySeriesTeeFunction
{
	typedef TManySeriesTeeFunction inherited;
	
protected:
	virtual double __fastcall CalculateValue(const Fmxtee::Engine::TChartValues Values);
	virtual void __fastcall PrepareForGallery(Fmxtee::Engine::TCustomAxisPanel* const Chart);
public:
	/* TTeeFunction.Create */ inline __fastcall virtual TMultiplyTeeFunction(System::Classes::TComponent* AOwner) : TManySeriesTeeFunction(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TMultiplyTeeFunction() { }
	
};


class PASCALIMPLEMENTATION TDivideTeeFunction : public TManySeriesTeeFunction
{
	typedef TManySeriesTeeFunction inherited;
	
protected:
	virtual double __fastcall CalculateValue(const Fmxtee::Engine::TChartValues Values);
	virtual void __fastcall PrepareForGallery(Fmxtee::Engine::TCustomAxisPanel* const Chart);
public:
	/* TTeeFunction.Create */ inline __fastcall virtual TDivideTeeFunction(System::Classes::TComponent* AOwner) : TManySeriesTeeFunction(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TDivideTeeFunction() { }
	
};


class PASCALIMPLEMENTATION THighTeeFunction : public Fmxtee::Engine::TTeeFunction
{
	typedef Fmxtee::Engine::TTeeFunction inherited;
	
protected:
	virtual double __fastcall CalculateValue(const Fmxtee::Engine::TChartValues Values);
	
public:
	virtual double __fastcall Calculate(Fmxtee::Engine::TChartSeries* const SourceSeries, int FirstIndex, int LastIndex);
public:
	/* TTeeFunction.Create */ inline __fastcall virtual THighTeeFunction(System::Classes::TComponent* AOwner) : Fmxtee::Engine::TTeeFunction(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~THighTeeFunction() { }
	
};


class PASCALIMPLEMENTATION TLowTeeFunction : public Fmxtee::Engine::TTeeFunction
{
	typedef Fmxtee::Engine::TTeeFunction inherited;
	
protected:
	virtual double __fastcall CalculateValue(const Fmxtee::Engine::TChartValues Values);
	
public:
	virtual double __fastcall Calculate(Fmxtee::Engine::TChartSeries* const SourceSeries, int FirstIndex, int LastIndex);
public:
	/* TTeeFunction.Create */ inline __fastcall virtual TLowTeeFunction(System::Classes::TComponent* AOwner) : Fmxtee::Engine::TTeeFunction(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TLowTeeFunction() { }
	
};


class PASCALIMPLEMENTATION TAverageTeeFunction : public Fmxtee::Engine::TTeeFunction
{
	typedef Fmxtee::Engine::TTeeFunction inherited;
	
protected:
	virtual double __fastcall CalculateValue(const Fmxtee::Engine::TChartValues Values);
	__classmethod virtual System::UnicodeString __fastcall GetEditorClass();
	
public:
	virtual double __fastcall Calculate(Fmxtee::Engine::TChartSeries* const SourceSeries, int FirstIndex, int LastIndex);
public:
	/* TTeeFunction.Create */ inline __fastcall virtual TAverageTeeFunction(System::Classes::TComponent* AOwner) : Fmxtee::Engine::TTeeFunction(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TAverageTeeFunction() { }
	
};


typedef void __fastcall (__closure *TCalculateEvent)(TCustomTeeFunction* Sender, const double x, double &y);

class PASCALIMPLEMENTATION TCustomTeeFunction : public Fmxtee::Engine::TTeeFunction
{
	typedef Fmxtee::Engine::TTeeFunction inherited;
	
private:
	TCalculateEvent FCalculate;
	int FNumPoints;
	double FStartX;
	double FX;
	void __fastcall GalleryCalculate(TCustomTeeFunction* Sender, const double x, double &y);
	
protected:
	__classmethod virtual System::UnicodeString __fastcall GetEditorClass();
	virtual void __fastcall PrepareForGallery(Fmxtee::Engine::TCustomAxisPanel* const Chart);
	
public:
	int ValueIndex;
	__fastcall virtual TCustomTeeFunction(System::Classes::TComponent* AOwner);
	DYNAMIC void __fastcall AddPoints(Fmxtee::Engine::TChartSeries* Source);
	__property double X = {read=FX, write=FX};
	
__published:
	__property int NumPoints = {read=FNumPoints, write=FNumPoints, nodefault};
	__property double StartX = {read=FStartX, write=FStartX};
	__property TCalculateEvent OnCalculate = {read=FCalculate, write=FCalculate};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TCustomTeeFunction() { }
	
};


class PASCALIMPLEMENTATION TCustomSortedFunction : public Fmxtee::Engine::TTeeFunction
{
	typedef Fmxtee::Engine::TTeeFunction inherited;
	
protected:
	virtual void __fastcall AddValue(const double Value, const Fmxtee::Engine::TChartValues Values, int Index);
public:
	/* TTeeFunction.Create */ inline __fastcall virtual TCustomSortedFunction(System::Classes::TComponent* AOwner) : Fmxtee::Engine::TTeeFunction(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TCustomSortedFunction() { }
	
};


class PASCALIMPLEMENTATION TMedianTeeFunction : public TCustomSortedFunction
{
	typedef TCustomSortedFunction inherited;
	
protected:
	virtual double __fastcall CalculateValue(const Fmxtee::Engine::TChartValues Values);
public:
	/* TTeeFunction.Create */ inline __fastcall virtual TMedianTeeFunction(System::Classes::TComponent* AOwner) : TCustomSortedFunction(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TMedianTeeFunction() { }
	
};


class PASCALIMPLEMENTATION TModeTeeFunction : public TCustomSortedFunction
{
	typedef TCustomSortedFunction inherited;
	
protected:
	virtual double __fastcall CalculateValue(const Fmxtee::Engine::TChartValues Values);
public:
	/* TTeeFunction.Create */ inline __fastcall virtual TModeTeeFunction(System::Classes::TComponent* AOwner) : TCustomSortedFunction(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TModeTeeFunction() { }
	
};


class PASCALIMPLEMENTATION TSubsetTeeFunction : public Fmxtee::Engine::TTeeFunction
{
	typedef Fmxtee::Engine::TTeeFunction inherited;
	
private:
	double FEnd;
	double FStart;
	void __fastcall SetEnd(const double Value);
	void __fastcall SetStart(const double Value);
	
protected:
	__classmethod virtual System::UnicodeString __fastcall GetEditorClass();
	virtual void __fastcall PrepareForGallery(Fmxtee::Engine::TCustomAxisPanel* const Chart);
	
public:
	__fastcall virtual TSubsetTeeFunction(System::Classes::TComponent* AOwner);
	DYNAMIC void __fastcall AddPoints(Fmxtee::Engine::TChartSeries* Source);
	
__published:
	__property double EndValue = {read=FEnd, write=SetEnd};
	__property double StartValue = {read=FStart, write=SetStart};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TSubsetTeeFunction() { }
	
};


class PASCALIMPLEMENTATION TParetoTeeFunction : public Fmxtee::Engine::TTeeFunction
{
	typedef Fmxtee::Engine::TTeeFunction inherited;
	
protected:
	virtual void __fastcall PrepareForGallery(Fmxtee::Engine::TCustomAxisPanel* const Chart);
	
public:
	__fastcall virtual TParetoTeeFunction(System::Classes::TComponent* AOwner);
	virtual double __fastcall Calculate(Fmxtee::Engine::TChartSeries* const Series, int First, int Last);
	
__published:
	__property Period = {default=0};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TParetoTeeFunction() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Functions */
}	/* namespace Chart */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_CHART_FUNCTIONS)
using namespace Fmxtee::Chart::Functions;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_CHART)
using namespace Fmxtee::Chart;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE)
using namespace Fmxtee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmxtee_Chart_FunctionsHPP
