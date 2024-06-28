// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeSpline.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeesplineHPP
#define Vcltee_TeesplineHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <VCLTee.TeEngine.hpp>

//-- user supplied -----------------------------------------------------------
#define TeeSpline_MaxError  ((System::Extended)1.000000E-05)

namespace Vcltee
{
namespace Teespline
{
//-- forward type declarations -----------------------------------------------
struct TVertex;
class DELPHICLASS TBSpline;
class DELPHICLASS TSmoothingFunction;
//-- type declarations -------------------------------------------------------
typedef double TDataType;

struct DECLSPEC_DRECORD TVertex
{
public:
	double X;
	double Y;
};


typedef System::DynamicArray<TVertex> T2DPointList;

typedef System::DynamicArray<TVertex> TVertexList;

typedef System::DynamicArray<bool> TKnuckleList;

typedef System::DynamicArray<double> TMatrixRow;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBSpline : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::DynamicArray<TMatrixRow> _TBSpline__1;
	
	
private:
	_TBSpline__1 Matrix;
	int FNoPoints;
	int FCapacity;
	T2DPointList FPointList;
	TVertexList FVertexList;
	TKnuckleList FKnuckleList;
	bool FBuild;
	int FNoVertices;
	bool FInterpolated;
	int FFragments;
	void __fastcall ClearVertexList();
	void __fastcall FSetBuild(bool Val);
	void __fastcall SetCapacity(int NewCapacity);
	void __fastcall FSetInterpolated(const bool Value);
	void __fastcall FSetFragments(const int Value);
	TVertex __fastcall FGetPoint(int Index);
	void __fastcall FSetPoint(int Index, const TVertex &Value);
	bool __fastcall FGetKnuckle(int Index);
	void __fastcall FSetKnuckle(int Index, bool Value);
	int __fastcall FGetNumberOfVertices();
	void __fastcall FInterpolate();
	void __fastcall FPhantomPoints();
	
public:
	__fastcall TBSpline();
	__fastcall virtual ~TBSpline();
	void __fastcall AddPoint(const double X, const double Y);
	void __fastcall Clear();
	__property int Count = {read=FNoPoints, nodefault};
	TVertex __fastcall Value(const double Parameter);
	void __fastcall Rebuild();
	__property bool Build = {read=FBuild, write=FSetBuild, nodefault};
	__property int Fragments = {read=FFragments, write=FSetFragments, nodefault};
	__property bool Interpolated = {read=FInterpolated, write=FSetInterpolated, nodefault};
	__property int NumberOfVertices = {read=FGetNumberOfVertices, nodefault};
	__property TVertex Point[int Index] = {read=FGetPoint, write=FSetPoint};
	__property bool Knuckle[int Index] = {read=FGetKnuckle, write=FSetKnuckle};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TSmoothingFunction : public Vcltee::Teengine::TTeeFunction
{
	typedef Vcltee::Teengine::TTeeFunction inherited;
	
private:
	bool FInterpolate;
	int FFactor;
	void __fastcall SetFactor(const int Value);
	void __fastcall SetInterpolate(const bool Value);
	
protected:
	__classmethod virtual System::UnicodeString __fastcall GetEditorClass();
	virtual void __fastcall PrepareForGallery(Vcltee::Teengine::TCustomAxisPanel* const Chart);
	
public:
	__fastcall virtual TSmoothingFunction(System::Classes::TComponent* AOwner);
	DYNAMIC void __fastcall AddPoints(Vcltee::Teengine::TChartSeries* Source);
	
__published:
	__property bool Interpolate = {read=FInterpolate, write=SetInterpolate, default=1};
	__property int Factor = {read=FFactor, write=SetFactor, default=4};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TSmoothingFunction() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static const System::Word MaxFragments = System::Word(0x258);
static const System::Word MaxResults = System::Word(0x262);
static const System::Byte MaxCalcSteps = System::Byte(0x96);
static const System::Int8 MaxIterations = System::Int8(0x50);
static const System::Int8 VerticesIncrement = System::Int8(0x5);
}	/* namespace Teespline */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEESPLINE)
using namespace Vcltee::Teespline;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeesplineHPP
