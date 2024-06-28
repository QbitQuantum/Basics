// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.DAE.Schema.MathTypes.pas' rev: 34.00 (Windows)

#ifndef Fmx_Dae_Schema_MathtypesHPP
#define Fmx_Dae_Schema_MathtypesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.XMLIntf.hpp>
#include <FMX.DAE.Schema.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Dae
{
namespace Schema
{
namespace Mathtypes
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TXMLMathTextBaseType;
class DELPHICLASS TXMLMathBaseType;
class DELPHICLASS TXMLMathtype;
class DELPHICLASS TXMLCntype;
class DELPHICLASS TXMLCitype;
class DELPHICLASS TXMLCsymboltype;
class DELPHICLASS TXMLArithtype;
class DELPHICLASS TXMLFunctionstype;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TXMLMathTextBaseType : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLMitype __fastcall Get_Mi();
	Fmx::Dae::Schema::_di_IXMLMotype __fastcall Get_Mo();
	Fmx::Dae::Schema::_di_IXMLMntype __fastcall Get_Mn();
	Fmx::Dae::Schema::_di_IXMLMtexttype __fastcall Get_Mtext();
	Fmx::Dae::Schema::_di_IXMLMstype __fastcall Get_Ms();
	Fmx::Dae::Schema::_di_IXMLMrowtype __fastcall Get_Mrow();
	Fmx::Dae::Schema::_di_IXMLMfractype __fastcall Get_Mfrac();
	Fmx::Dae::Schema::_di_IXMLMsqrttype __fastcall Get_Msqrt();
	Fmx::Dae::Schema::_di_IXMLMroottype __fastcall Get_Mroot();
	Fmx::Dae::Schema::_di_IXMLMpaddedtype __fastcall Get_Mpadded();
	Fmx::Dae::Schema::_di_IXMLMphantomtype __fastcall Get_Mphantom();
	Fmx::Dae::Schema::_di_IXMLMfencedtype __fastcall Get_Mfenced();
	Fmx::Dae::Schema::_di_IXMLMenclosetype __fastcall Get_Menclose();
	Fmx::Dae::Schema::_di_IXMLMsubtype __fastcall Get_Msub();
	Fmx::Dae::Schema::_di_IXMLMsuptype __fastcall Get_Msup();
	Fmx::Dae::Schema::_di_IXMLMsubsuptype __fastcall Get_Msubsup();
	Fmx::Dae::Schema::_di_IXMLMundertype __fastcall Get_Munder();
	Fmx::Dae::Schema::_di_IXMLMovertype __fastcall Get_Mover();
	Fmx::Dae::Schema::_di_IXMLMunderovertype __fastcall Get_Munderover();
	Fmx::Dae::Schema::_di_IXMLMmultiscriptstype __fastcall Get_Mmultiscripts();
	Fmx::Dae::Schema::_di_IXMLMtabletype __fastcall Get_Mtable();
	Fmx::Dae::Schema::_di_IXMLMaligngrouptype __fastcall Get_Maligngroup();
	Fmx::Dae::Schema::_di_IXMLMalignmarktype __fastcall Get_Malignmark();
	Fmx::Dae::Schema::_di_IXMLMspacetype __fastcall Get_Mspace();
	Fmx::Dae::Schema::_di_IXMLMactiontype __fastcall Get_Maction();
	Fmx::Dae::Schema::_di_IXMLMerrortype __fastcall Get_Merror();
	Fmx::Dae::Schema::_di_IXMLMstyletype __fastcall Get_Mstyle();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLMathTextBaseType(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLMathTextBaseType(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLMathTextBaseType() { }
	
};


class PASCALIMPLEMENTATION TXMLMathBaseType : public TXMLMathTextBaseType
{
	typedef TXMLMathTextBaseType inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLCntype __fastcall Get_Cn();
	Fmx::Dae::Schema::_di_IXMLCitype __fastcall Get_Ci();
	Fmx::Dae::Schema::_di_IXMLCsymboltype __fastcall Get_Csymbol();
	Fmx::Dae::Schema::_di_IXMLArithtype __fastcall Get_Abs();
	Fmx::Dae::Schema::_di_IXMLArithtype __fastcall Get_Conjugate();
	Fmx::Dae::Schema::_di_IXMLArithtype __fastcall Get_Factorial();
	Fmx::Dae::Schema::_di_IXMLArithtype __fastcall Get_Arg();
	Fmx::Dae::Schema::_di_IXMLArithtype __fastcall Get_Real();
	Fmx::Dae::Schema::_di_IXMLArithtype __fastcall Get_Imaginary();
	Fmx::Dae::Schema::_di_IXMLArithtype __fastcall Get_Floor();
	Fmx::Dae::Schema::_di_IXMLArithtype __fastcall Get_Ceiling();
	Fmx::Dae::Schema::_di_IXMLArithtype __fastcall Get_Quotient();
	Fmx::Dae::Schema::_di_IXMLArithtype __fastcall Get_Divide();
	Fmx::Dae::Schema::_di_IXMLArithtype __fastcall Get_Rem();
	Fmx::Dae::Schema::_di_IXMLArithtype __fastcall Get_Minus();
	Fmx::Dae::Schema::_di_IXMLArithtype __fastcall Get_Plus();
	Fmx::Dae::Schema::_di_IXMLArithtype __fastcall Get_Times();
	Fmx::Dae::Schema::_di_IXMLArithtype __fastcall Get_Power();
	Fmx::Dae::Schema::_di_IXMLArithtype __fastcall Get_Root();
	Fmx::Dae::Schema::_di_IXMLArithtype __fastcall Get_Max();
	Fmx::Dae::Schema::_di_IXMLArithtype __fastcall Get_Min();
	Fmx::Dae::Schema::_di_IXMLArithtype __fastcall Get_Gcd();
	Fmx::Dae::Schema::_di_IXMLArithtype __fastcall Get_Lcm();
	Fmx::Dae::Schema::_di_IXMLArithtype __fastcall Get_Sum();
	Fmx::Dae::Schema::_di_IXMLArithtype __fastcall Get_Product();
	Fmx::Dae::Schema::_di_IXMLFunctionstype __fastcall Get_Compose();
	Fmx::Dae::Schema::_di_IXMLFunctionstype __fastcall Get_Domain();
	Fmx::Dae::Schema::_di_IXMLFunctionstype __fastcall Get_Codomain();
	Fmx::Dae::Schema::_di_IXMLFunctionstype __fastcall Get_Image();
	Fmx::Dae::Schema::_di_IXMLDomainofapplicationtype __fastcall Get_Domainofapplication();
	Fmx::Dae::Schema::_di_IXMLFunctionstype __fastcall Get_Ident();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_And_();
	Fmx::Dae::Schema::_di_IXMLLogictype __fastcall Get_Or_();
	Fmx::Dae::Schema::_di_IXMLLogictype __fastcall Get_Xor_();
	Fmx::Dae::Schema::_di_IXMLLogictype __fastcall Get_Not_();
	Fmx::Dae::Schema::_di_IXMLLogictype __fastcall Get_Exists();
	Fmx::Dae::Schema::_di_IXMLLogictype __fastcall Get_Forall();
	Fmx::Dae::Schema::_di_IXMLLogictype __fastcall Get_Implies();
	Fmx::Dae::Schema::_di_IXMLConstanttype __fastcall Get_Naturalnumbers();
	Fmx::Dae::Schema::_di_IXMLConstanttype __fastcall Get_Primes();
	Fmx::Dae::Schema::_di_IXMLConstanttype __fastcall Get_Integers();
	Fmx::Dae::Schema::_di_IXMLConstanttype __fastcall Get_Rationals();
	Fmx::Dae::Schema::_di_IXMLConstanttype __fastcall Get_Reals();
	Fmx::Dae::Schema::_di_IXMLConstanttype __fastcall Get_Complexes();
	Fmx::Dae::Schema::_di_IXMLConstanttype __fastcall Get_Emptyset();
	Fmx::Dae::Schema::_di_IXMLConstanttype __fastcall Get_Exponentiale();
	Fmx::Dae::Schema::_di_IXMLConstanttype __fastcall Get_Imaginaryi();
	Fmx::Dae::Schema::_di_IXMLConstanttype __fastcall Get_Pi();
	Fmx::Dae::Schema::_di_IXMLConstanttype __fastcall Get_Eulergamma();
	Fmx::Dae::Schema::_di_IXMLConstanttype __fastcall Get_True();
	Fmx::Dae::Schema::_di_IXMLConstanttype __fastcall Get_False();
	Fmx::Dae::Schema::_di_IXMLConstanttype __fastcall Get_Infinity();
	Fmx::Dae::Schema::_di_IXMLConstanttype __fastcall Get_Notanumber();
	Fmx::Dae::Schema::_di_IXMLSettype __fastcall Get_Set_();
	Fmx::Dae::Schema::_di_IXMLListtype __fastcall Get_List();
	Fmx::Dae::Schema::_di_IXMLUniontype __fastcall Get_Union();
	Fmx::Dae::Schema::_di_IXMLIntersecttype __fastcall Get_Intersect();
	Fmx::Dae::Schema::_di_IXMLIntype __fastcall Get_In_();
	Fmx::Dae::Schema::_di_IXMLNotintype __fastcall Get_Notin();
	Fmx::Dae::Schema::_di_IXMLSubsettype __fastcall Get_Subset();
	Fmx::Dae::Schema::_di_IXMLPrsubsettype __fastcall Get_Prsubset();
	Fmx::Dae::Schema::_di_IXMLNotsubsettype __fastcall Get_Notsubset();
	Fmx::Dae::Schema::_di_IXMLNotprsubsettype __fastcall Get_Notprsubset();
	Fmx::Dae::Schema::_di_IXMLSetdifftype __fastcall Get_Setdiff();
	Fmx::Dae::Schema::_di_IXMLCardtype __fastcall Get_Card();
	Fmx::Dae::Schema::_di_IXMLCartesianproducttype __fastcall Get_Cartesianproduct();
	Fmx::Dae::Schema::_di_IXMLRelationstype __fastcall Get_Eq();
	Fmx::Dae::Schema::_di_IXMLRelationstype __fastcall Get_Neq();
	Fmx::Dae::Schema::_di_IXMLRelationstype __fastcall Get_Leq();
	Fmx::Dae::Schema::_di_IXMLRelationstype __fastcall Get_Lt();
	Fmx::Dae::Schema::_di_IXMLRelationstype __fastcall Get_Geq();
	Fmx::Dae::Schema::_di_IXMLRelationstype __fastcall Get_Gt();
	Fmx::Dae::Schema::_di_IXMLRelationstype __fastcall Get_Equivalent();
	Fmx::Dae::Schema::_di_IXMLRelationstype __fastcall Get_Approx();
	Fmx::Dae::Schema::_di_IXMLRelationstype __fastcall Get_Factorof();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Exp();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Ln();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Log();
	Fmx::Dae::Schema::_di_IXMLLogbasetype __fastcall Get_Logbase();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Sin();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Cos();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Tan();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Sec();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Csc();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Cot();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Arcsin();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Arccos();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Arctan();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Arcsec();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Arccsc();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Arccot();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Sinh();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Cosh();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Tanh();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Sech();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Csch();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Coth();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Arccosh();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Arccoth();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Arccsch();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Arcsech();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Arcsinh();
	Fmx::Dae::Schema::_di_IXMLElementaryfunctionstype __fastcall Get_Arctanh();
	Fmx::Dae::Schema::_di_IXMLInttype __fastcall Get_Int();
	Fmx::Dae::Schema::_di_IXMLDifftype __fastcall Get_Diff();
	Fmx::Dae::Schema::_di_IXMLPartialdifftype __fastcall Get_Partialdiff();
	Fmx::Dae::Schema::_di_IXMLLimittype __fastcall Get_Limit();
	Fmx::Dae::Schema::_di_IXMLLowlimittype __fastcall Get_Lowlimit();
	Fmx::Dae::Schema::_di_IXMLUplimittype __fastcall Get_Uplimit();
	Fmx::Dae::Schema::_di_IXMLTendstotype __fastcall Get_Tendsto();
	Fmx::Dae::Schema::_di_IXMLVectortype __fastcall Get_Vector();
	Fmx::Dae::Schema::_di_IXMLMatrixtype __fastcall Get_Matrix();
	Fmx::Dae::Schema::_di_IXMLDeterminanttype __fastcall Get_Determinant();
	Fmx::Dae::Schema::_di_IXMLTransposetype __fastcall Get_Transpose();
	Fmx::Dae::Schema::_di_IXMLSelectortype __fastcall Get_Selector();
	Fmx::Dae::Schema::_di_IXMLVectorproducttype __fastcall Get_Vectorproduct();
	Fmx::Dae::Schema::_di_IXMLScalarproducttype __fastcall Get_Scalarproduct();
	Fmx::Dae::Schema::_di_IXMLOuterproducttype __fastcall Get_Outerproduct();
	Fmx::Dae::Schema::_di_IXMLDivergencetype __fastcall Get_Divergence();
	Fmx::Dae::Schema::_di_IXMLGradtype __fastcall Get_Grad();
	Fmx::Dae::Schema::_di_IXMLCurltype __fastcall Get_Curl();
	Fmx::Dae::Schema::_di_IXMLLaplaciantype __fastcall Get_Laplacian();
	Fmx::Dae::Schema::_di_IXMLMeantype __fastcall Get_Mean();
	Fmx::Dae::Schema::_di_IXMLSdevtype __fastcall Get_Sdev();
	Fmx::Dae::Schema::_di_IXMLVariancetype __fastcall Get_Variance();
	Fmx::Dae::Schema::_di_IXMLMediantype __fastcall Get_Median();
	Fmx::Dae::Schema::_di_IXMLModetype __fastcall Get_Mode();
	Fmx::Dae::Schema::_di_IXMLMomenttype __fastcall Get_Moment();
	Fmx::Dae::Schema::_di_IXMLMomentabouttype __fastcall Get_Momentabout();
	Fmx::Dae::Schema::_di_IXMLApplytype __fastcall Get_Apply();
	Fmx::Dae::Schema::_di_IXMLIntervaltype __fastcall Get_Interval();
	Fmx::Dae::Schema::_di_IXMLInversetype __fastcall Get_Inverse();
	Fmx::Dae::Schema::_di_IXMLConditiontype __fastcall Get_Condition();
	Fmx::Dae::Schema::_di_IXMLDeclaretype __fastcall Get_Declare();
	Fmx::Dae::Schema::_di_IXMLLambdatype __fastcall Get_Lambda();
	Fmx::Dae::Schema::_di_IXMLPiecewisetype __fastcall Get_Piecewise();
	Fmx::Dae::Schema::_di_IXMLBvartype __fastcall Get_Bvar();
	Fmx::Dae::Schema::_di_IXMLDegreetype __fastcall Get_Degree();
	Fmx::Dae::Schema::_di_IXMLSemanticstype __fastcall Get_Semantics();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLMathBaseType(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLMathTextBaseType(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLMathBaseType(Xml::Xmldoc::TXMLNode* HostNode) : TXMLMathTextBaseType(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLMathBaseType() { }
	
};


class PASCALIMPLEMENTATION TXMLMathtype : public TXMLMathBaseType
{
	typedef TXMLMathBaseType inherited;
	
protected:
	System::UnicodeString __fastcall Get_Baseline();
	System::UnicodeString __fastcall Get_Overflow();
	System::UnicodeString __fastcall Get_Altimg();
	System::UnicodeString __fastcall Get_Alttext();
	System::UnicodeString __fastcall Get_Type_();
	System::UnicodeString __fastcall Get_Name();
	System::UnicodeString __fastcall Get_Height();
	System::UnicodeString __fastcall Get_Width();
	System::UnicodeString __fastcall Get_Macros();
	System::UnicodeString __fastcall Get_Display();
	System::UnicodeString __fastcall Get_Class_();
	System::UnicodeString __fastcall Get_Style();
	System::UnicodeString __fastcall Get_Xref();
	System::UnicodeString __fastcall Get_Id();
	System::UnicodeString __fastcall Get_Href();
	void __fastcall Set_Baseline(System::UnicodeString Value);
	void __fastcall Set_Overflow(System::UnicodeString Value);
	void __fastcall Set_Altimg(System::UnicodeString Value);
	void __fastcall Set_Alttext(System::UnicodeString Value);
	void __fastcall Set_Type_(System::UnicodeString Value);
	void __fastcall Set_Name(System::UnicodeString Value);
	void __fastcall Set_Height(System::UnicodeString Value);
	void __fastcall Set_Width(System::UnicodeString Value);
	void __fastcall Set_Macros(System::UnicodeString Value);
	void __fastcall Set_Display(System::UnicodeString Value);
	void __fastcall Set_Class_(System::UnicodeString Value);
	void __fastcall Set_Style(System::UnicodeString Value);
	void __fastcall Set_Xref(System::UnicodeString Value);
	void __fastcall Set_Id(System::UnicodeString Value);
	void __fastcall Set_Href(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLMathtype(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLMathBaseType(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLMathtype(Xml::Xmldoc::TXMLNode* HostNode) : TXMLMathBaseType(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLMathtype() { }
	
private:
	void *__IXMLMathtype;	// Fmx::Dae::Schema::IXMLMathtype 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {337BB8DF-F405-48B9-BD1B-C12E83656C7B}
	operator Fmx::Dae::Schema::_di_IXMLMathtype()
	{
		Fmx::Dae::Schema::_di_IXMLMathtype intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLMathtype*(void) { return (Fmx::Dae::Schema::IXMLMathtype*)&__IXMLMathtype; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLCntype : public TXMLMathBaseType
{
	typedef TXMLMathBaseType inherited;
	
protected:
	unsigned __fastcall Get_Base();
	System::UnicodeString __fastcall Get_Type_();
	System::UnicodeString __fastcall Get_Encoding();
	System::UnicodeString __fastcall Get_DefinitionURL();
	System::UnicodeString __fastcall Get_Class_();
	System::UnicodeString __fastcall Get_Style();
	System::UnicodeString __fastcall Get_Xref();
	System::UnicodeString __fastcall Get_Id();
	System::UnicodeString __fastcall Get_Href();
	Fmx::Dae::Schema::_di_IXMLSeptype __fastcall Get_Sep();
	void __fastcall Set_Base(unsigned Value);
	void __fastcall Set_Type_(System::UnicodeString Value);
	void __fastcall Set_Encoding(System::UnicodeString Value);
	void __fastcall Set_DefinitionURL(System::UnicodeString Value);
	void __fastcall Set_Class_(System::UnicodeString Value);
	void __fastcall Set_Style(System::UnicodeString Value);
	void __fastcall Set_Xref(System::UnicodeString Value);
	void __fastcall Set_Id(System::UnicodeString Value);
	void __fastcall Set_Href(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLCntype(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLMathBaseType(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLCntype(Xml::Xmldoc::TXMLNode* HostNode) : TXMLMathBaseType(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLCntype() { }
	
private:
	void *__IXMLCntype;	// Fmx::Dae::Schema::IXMLCntype 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FDF1A3F3-378D-4E2D-88C0-AD7878C86453}
	operator Fmx::Dae::Schema::_di_IXMLCntype()
	{
		Fmx::Dae::Schema::_di_IXMLCntype intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLCntype*(void) { return (Fmx::Dae::Schema::IXMLCntype*)&__IXMLCntype; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLCitype : public TXMLMathBaseType
{
	typedef TXMLMathBaseType inherited;
	
protected:
	System::UnicodeString __fastcall Get_Type_();
	System::UnicodeString __fastcall Get_Encoding();
	System::UnicodeString __fastcall Get_DefinitionURL();
	System::UnicodeString __fastcall Get_Class_();
	System::UnicodeString __fastcall Get_Style();
	System::UnicodeString __fastcall Get_Xref();
	System::UnicodeString __fastcall Get_Id();
	System::UnicodeString __fastcall Get_Href();
	void __fastcall Set_Type_(System::UnicodeString Value);
	void __fastcall Set_Encoding(System::UnicodeString Value);
	void __fastcall Set_DefinitionURL(System::UnicodeString Value);
	void __fastcall Set_Class_(System::UnicodeString Value);
	void __fastcall Set_Style(System::UnicodeString Value);
	void __fastcall Set_Xref(System::UnicodeString Value);
	void __fastcall Set_Id(System::UnicodeString Value);
	void __fastcall Set_Href(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLCitype(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLMathBaseType(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLCitype(Xml::Xmldoc::TXMLNode* HostNode) : TXMLMathBaseType(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLCitype() { }
	
private:
	void *__IXMLCitype;	// Fmx::Dae::Schema::IXMLCitype 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7AF55407-3608-4FE7-99B2-25A8CA9D492A}
	operator Fmx::Dae::Schema::_di_IXMLCitype()
	{
		Fmx::Dae::Schema::_di_IXMLCitype intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLCitype*(void) { return (Fmx::Dae::Schema::IXMLCitype*)&__IXMLCitype; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLCsymboltype : public TXMLMathBaseType
{
	typedef TXMLMathBaseType inherited;
	
protected:
	System::UnicodeString __fastcall Get_Encoding();
	System::UnicodeString __fastcall Get_DefinitionURL();
	System::UnicodeString __fastcall Get_Class_();
	System::UnicodeString __fastcall Get_Style();
	System::UnicodeString __fastcall Get_Xref();
	System::UnicodeString __fastcall Get_Id();
	System::UnicodeString __fastcall Get_Href();
	void __fastcall Set_Encoding(System::UnicodeString Value);
	void __fastcall Set_DefinitionURL(System::UnicodeString Value);
	void __fastcall Set_Class_(System::UnicodeString Value);
	void __fastcall Set_Style(System::UnicodeString Value);
	void __fastcall Set_Xref(System::UnicodeString Value);
	void __fastcall Set_Id(System::UnicodeString Value);
	void __fastcall Set_Href(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLCsymboltype(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLMathBaseType(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLCsymboltype(Xml::Xmldoc::TXMLNode* HostNode) : TXMLMathBaseType(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLCsymboltype() { }
	
private:
	void *__IXMLCsymboltype;	// Fmx::Dae::Schema::IXMLCsymboltype 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {41B9A5B8-68A3-4E4B-A6A2-13142E962986}
	operator Fmx::Dae::Schema::_di_IXMLCsymboltype()
	{
		Fmx::Dae::Schema::_di_IXMLCsymboltype intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLCsymboltype*(void) { return (Fmx::Dae::Schema::IXMLCsymboltype*)&__IXMLCsymboltype; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLArithtype : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Encoding();
	System::UnicodeString __fastcall Get_DefinitionURL();
	System::UnicodeString __fastcall Get_Class_();
	System::UnicodeString __fastcall Get_Style();
	System::UnicodeString __fastcall Get_Xref();
	System::UnicodeString __fastcall Get_Id();
	System::UnicodeString __fastcall Get_Href();
	void __fastcall Set_Encoding(System::UnicodeString Value);
	void __fastcall Set_DefinitionURL(System::UnicodeString Value);
	void __fastcall Set_Class_(System::UnicodeString Value);
	void __fastcall Set_Style(System::UnicodeString Value);
	void __fastcall Set_Xref(System::UnicodeString Value);
	void __fastcall Set_Id(System::UnicodeString Value);
	void __fastcall Set_Href(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLArithtype(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLArithtype(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLArithtype() { }
	
private:
	void *__IXMLArithtype;	// Fmx::Dae::Schema::IXMLArithtype 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {937C3B97-5D51-4D69-9066-775C83D23FAD}
	operator Fmx::Dae::Schema::_di_IXMLArithtype()
	{
		Fmx::Dae::Schema::_di_IXMLArithtype intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLArithtype*(void) { return (Fmx::Dae::Schema::IXMLArithtype*)&__IXMLArithtype; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFunctionstype : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Encoding();
	System::UnicodeString __fastcall Get_DefinitionURL();
	System::UnicodeString __fastcall Get_Class_();
	System::UnicodeString __fastcall Get_Style();
	System::UnicodeString __fastcall Get_Xref();
	System::UnicodeString __fastcall Get_Id();
	System::UnicodeString __fastcall Get_Href();
	void __fastcall Set_Encoding(System::UnicodeString Value);
	void __fastcall Set_DefinitionURL(System::UnicodeString Value);
	void __fastcall Set_Class_(System::UnicodeString Value);
	void __fastcall Set_Style(System::UnicodeString Value);
	void __fastcall Set_Xref(System::UnicodeString Value);
	void __fastcall Set_Id(System::UnicodeString Value);
	void __fastcall Set_Href(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFunctionstype(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFunctionstype(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFunctionstype() { }
	
private:
	void *__IXMLFunctionstype;	// Fmx::Dae::Schema::IXMLFunctionstype 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {0D5420A8-3CE0-4D6F-ABE7-9C1E358185B8}
	operator Fmx::Dae::Schema::_di_IXMLFunctionstype()
	{
		Fmx::Dae::Schema::_di_IXMLFunctionstype intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFunctionstype*(void) { return (Fmx::Dae::Schema::IXMLFunctionstype*)&__IXMLFunctionstype; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Mathtypes */
}	/* namespace Schema */
}	/* namespace Dae */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_DAE_SCHEMA_MATHTYPES)
using namespace Fmx::Dae::Schema::Mathtypes;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_DAE_SCHEMA)
using namespace Fmx::Dae::Schema;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_DAE)
using namespace Fmx::Dae;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Dae_Schema_MathtypesHPP
