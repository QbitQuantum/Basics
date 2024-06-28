// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeFunci.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeefunciHPP
#define Vcltee_TeefunciHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <VCLTee.TeEngine.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teefunci
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
class PASCALIMPLEMENTATION TAddTeeFunction : public Vcltee::Teengine::TTeeFunction
{
	typedef Vcltee::Teengine::TTeeFunction inherited;
	
protected:
	virtual double __fastcall CalculateValue(const Vcltee::Teengine::TChartValues Values);
	virtual void __fastcall PrepareForGallery(Vcltee::Teengine::TCustomAxisPanel* const Chart);
public:
	/* TTeeFunction.Create */ inline __fastcall virtual TAddTeeFunction(System::Classes::TComponent* AOwner) : Vcltee::Teengine::TTeeFunction(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TAddTeeFunction() { }
	
};


class PASCALIMPLEMENTATION TManySeriesTeeFunction : public Vcltee::Teengine::TTeeFunction
{
	typedef Vcltee::Teengine::TTeeFunction inherited;
	
public:
	/* TTeeFunction.Create */ inline __fastcall virtual TManySeriesTeeFunction(System::Classes::TComponent* AOwner) : Vcltee::Teengine::TTeeFunction(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TManySeriesTeeFunction() { }
	
};


class PASCALIMPLEMENTATION TSubtractTeeFunction : public TManySeriesTeeFunction
{
	typedef TManySeriesTeeFunction inherited;
	
protected:
	virtual double __fastcall CalculateValue(const Vcltee::Teengine::TChartValues Values);
	virtual void __fastcall PrepareForGallery(Vcltee::Teengine::TCustomAxisPanel* const Chart);
public:
	/* TTeeFunction.Create */ inline __fastcall virtual TSubtractTeeFunction(System::Classes::TComponent* AOwner) : TManySeriesTeeFunction(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TSubtractTeeFunction() { }
	
};


class PASCALIMPLEMENTATION TMultiplyTeeFunction : public TManySeriesTeeFunction
{
	typedef TManySeriesTeeFunction inherited;
	
protected:
	virtual double __fastcall CalculateValue(const Vcltee::Teengine::TChartValues Values);
	virtual void __fastcall PrepareForGallery(Vcltee::Teengine::TCustomAxisPanel* const Chart);
public:
	/* TTeeFunction.Create */ inline __fastcall virtual TMultiplyTeeFunction(System::Classes::TComponent* AOwner) : TManySeriesTeeFunction(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TMultiplyTeeFunction() { }
	
};


class PASCALIMPLEMENTATION TDivideTeeFunction : public TManySeriesTeeFunction
{
	typedef TManySeriesTeeFunction inherited;
	
protected:
	virtual double __fastcall CalculateValue(const Vcltee::Teengine::TChartValues Values);
	virtual void __fastcall PrepareForGallery(Vcltee::Teengine::TCustomAxisPanel* const Chart);
public:
	/* TTeeFunction.Create */ inline __fastcall virtual TDivideTeeFunction(System::Classes::TComponent* AOwner) : TManySeriesTeeFunction(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TDivideTeeFunction() { }
	
};


class PASCALIMPLEMENTATION THighTeeFunction : public Vcltee::Teengine::TTeeFunction
{
	typedef Vcltee::Teengine::TTeeFunction inherited;
	
protected:
	virtual double __fastcall CalculateValue(const Vcltee::Teengine::TChartValues Values);
	
public:
	virtual double __fastcall Calculate(Vcltee::Teengine::TChartSeries* const SourceSeries, int FirstIndex, int LastIndex);
public:
	/* TTeeFunction.Create */ inline __fastcall virtual THighTeeFunction(System::Classes::TComponent* AOwner) : Vcltee::Teengine::TTeeFunction(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~THighTeeFunction() { }
	
};


class PASCALIMPLEMENTATION TLowTeeFunction : public Vcltee::Teengine::TTeeFunction
{
	typedef Vcltee::Teengine::TTeeFunction inherited;
	
protected:
	virtual double __fastcall CalculateValue(const Vcltee::Teengine::TChartValues Values);
	
public:
	virtual double __fastcall Calculate(Vcltee::Teengine::TChartSeries* const SourceSeries, int FirstIndex, int LastIndex);
public:
	/* TTeeFunction.Create */ inline __fastcall virtual TLowTeeFunction(System::Classes::TComponent* AOwner) : Vcltee::Teengine::TTeeFunction(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TLowTeeFunction() { }
	
};


class PASCALIMPLEMENTATION TAverageTeeFunction : public Vcltee::Teengine::TTeeFunction
{
	typedef Vcltee::Teengine::TTeeFunction inherited;
	
protected:
	virtual double __fastcall CalculateValue(const Vcltee::Teengine::TChartValues Values);
	__classmethod virtual System::UnicodeString __fastcall GetEditorClass();
	
public:
	virtual double __fastcall Calculate(Vcltee::Teengine::TChartSeries* const SourceSeries, int FirstIndex, int LastIndex);
public:
	/* TTeeFunction.Create */ inline __fastcall virtual TAverageTeeFunction(System::Classes::TComponent* AOwner) : Vcltee::Teengine::TTeeFunction(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TAverageTeeFunction() { }
	
};


typedef void __fastcall (__closure *TCalculateEvent)(TCustomTeeFunction* Sender, const double x, double &y);

class PASCALIMPLEMENTATION TCustomTeeFunction : public Vcltee::Teengine::TTeeFunction
{
	typedef Vcltee::Teengine::TTeeFunction inherited;
	
private:
	TCalculateEvent FCalculate;
	int FNumPoints;
	double FStartX;
	double FX;
	void __fastcall GalleryCalculate(TCustomTeeFunction* Sender, const double x, double &y);
	
protected:
	__classmethod virtual System::UnicodeString __fastcall GetEditorClass();
	virtual void __fastcall PrepareForGallery(Vcltee::Teengine::TCustomAxisPanel* const Chart);
	
public:
	int ValueIndex;
	__fastcall virtual TCustomTeeFunction(System::Classes::TComponent* AOwner);
	DYNAMIC void __fastcall AddPoints(Vcltee::Teengine::TChartSeries* Source);
	__property double X = {read=FX, write=FX};
	
__published:
	__property int NumPoints = {read=FNumPoints, write=FNumPoints, nodefault};
	__property double StartX = {read=FStartX, write=FStartX};
	__property TCalculateEvent OnCalculate = {read=FCalculate, write=FCalculate};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TCustomTeeFunction() { }
	
};


class PASCALIMPLEMENTATION TCustomSortedFunction : public Vcltee::Teengine::TTeeFunction
{
	typedef Vcltee::Teengine::TTeeFunction inherited;
	
protected:
	virtual void __fastcall AddValue(const double Value, const Vcltee::Teengine::TChartValues Values, int Index);
public:
	/* TTeeFunction.Create */ inline __fastcall virtual TCustomSortedFunction(System::Classes::TComponent* AOwner) : Vcltee::Teengine::TTeeFunction(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TCustomSortedFunction() { }
	
};


class PASCALIMPLEMENTATION TMedianTeeFunction : public TCustomSortedFunction
{
	typedef TCustomSortedFunction inherited;
	
protected:
	virtual double __fastcall CalculateValue(const Vcltee::Teengine::TChartValues Values);
public:
	/* TTeeFunction.Create */ inline __fastcall virtual TMedianTeeFunction(System::Classes::TComponent* AOwner) : TCustomSortedFunction(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TMedianTeeFunction() { }
	
};


class PASCALIMPLEMENTATION TModeTeeFunction : public TCustomSortedFunction
{
	typedef TCustomSortedFunction inherited;
	
protected:
	virtual double __fastcall CalculateValue(const Vcltee::Teengine::TChartValues Values);
public:
	/* TTeeFunction.Create */ inline __fastcall virtual TModeTeeFunction(System::Classes::TComponent* AOwner) : TCustomSortedFunction(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TModeTeeFunction() { }
	
};


class PASCALIMPLEMENTATION TSubsetTeeFunction : public Vcltee::Teengine::TTeeFunction
{
	typedef Vcltee::Teengine::TTeeFunction inherited;
	
private:
	double FEnd;
	double FStart;
	void __fastcall SetEnd(const double Value);
	void __fastcall SetStart(const double Value);
	
protected:
	__classmethod virtual System::UnicodeString __fastcall GetEditorClass();
	virtual void __fastcall PrepareForGallery(Vcltee::Teengine::TCustomAxisPanel* const Chart);
	
public:
	__fastcall virtual TSubsetTeeFunction(System::Classes::TComponent* AOwner);
	DYNAMIC void __fastcall AddPoints(Vcltee::Teengine::TChartSeries* Source);
	
__published:
	__property double EndValue = {read=FEnd, write=SetEnd};
	__property double StartValue = {read=FStart, write=SetStart};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TSubsetTeeFunction() { }
	
};


class PASCALIMPLEMENTATION TParetoTeeFunction : public Vcltee::Teengine::TTeeFunction
{
	typedef Vcltee::Teengine::TTeeFunction inherited;
	
protected:
	virtual void __fastcall PrepareForGallery(Vcltee::Teengine::TCustomAxisPanel* const Chart);
	
public:
	__fastcall virtual TParetoTeeFunction(System::Classes::TComponent* AOwner);
	virtual double __fastcall Calculate(Vcltee::Teengine::TChartSeries* const Series, int First, int Last);
	
__published:
	__property Period = {default=0};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TParetoTeeFunction() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teefunci */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEFUNCI)
using namespace Vcltee::Teefunci;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeefunciHPP
