// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.Internal.LangUtils.pas' rev: 34.00 (iOS)

#ifndef Xml_Internal_LangutilsHPP
#define Xml_Internal_LangutilsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Internal
{
namespace Langutils
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIso639Info;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TIso639LanguageCode : unsigned char { iso639_aa, iso639_ab, iso639_af, iso639_am, iso639_ar, iso639_as, iso639_ay, iso639_az, iso639_ba, iso639_be, iso639_bg, iso639_bh, iso639_bi, iso639_bn, iso639_bo, iso639_br, iso639_ca, iso639_co, iso639_cs, iso639_cy, iso639_da, iso639_de, iso639_dz, iso639_el, iso639_en, iso639_eo, iso639_es, iso639_et, iso639_eu, iso639_fa, iso639_fi, iso639_fj, iso639_fo, iso639_fr, iso639_fy, iso639_ga, iso639_gd, iso639_gl, iso639_gn, iso639_gu, iso639_ha, iso639_hi, iso639_hr, iso639_hu, iso639_hy, iso639_ia, iso639_ie, iso639_ik, iso639_in, iso639_is, iso639_it, iso639_iw, iso639_ja, iso639_ji, iso639_jw, iso639_ka, iso639_kk, iso639_kl, iso639_km, iso639_kn, iso639_ko, iso639_ks, iso639_ku, iso639_ky, 
	iso639_la, iso639_ln, iso639_lo, iso639_lt, iso639_lv, iso639_mg, iso639_mi, iso639_mk, iso639_ml, iso639_mn, iso639_mo, iso639_mr, iso639_ms, iso639_mt, iso639_my, iso639_na, iso639_ne, iso639_nl, iso639_no, iso639_oc, iso639_om, iso639_or, iso639_pa, iso639_pl, iso639_ps, iso639_pt, iso639_qu, iso639_rm, iso639_rn, iso639_ro, iso639_ru, iso639_rw, iso639_sa, iso639_sd, iso639_sg, iso639_sh, iso639_si, iso639_sk, iso639_sl, iso639_sm, iso639_sn, iso639_so, iso639_sq, iso639_sr, iso639_ss, iso639_st, iso639_su, iso639_sv, iso639_sw, iso639_ta, iso639_te, iso639_tg, iso639_th, iso639_ti, iso639_tk, iso639_tl, iso639_tn, iso639_to, iso639_tr, iso639_ts, iso639_tt, iso639_tw, iso639_uk, iso639_ur, iso639_uz, iso639_vi, iso639_vo, iso639_wo, iso639_xh, 
	iso639_yo, iso639_zh, iso639_zu };

typedef System::Set<TIso639LanguageCode, TIso639LanguageCode::iso639_aa, TIso639LanguageCode::iso639_zu> TIso639LanguageCodeSet;

class PASCALIMPLEMENTATION TIso639Info : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::WideString __fastcall CodeToName_en(TIso639LanguageCode Value);
	TIso639LanguageCode __fastcall NameToCode_en(System::WideString Value);
	
protected:
	bool FAppendSymbolToName;
	TIso639LanguageCode FNameLanguage;
	TIso639LanguageCodeSet FSupportedLanguages;
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	virtual void __fastcall SetNameLanguage(const TIso639LanguageCode Value);
	
public:
	__fastcall TIso639Info();
	virtual System::WideString __fastcall CodeToName(const TIso639LanguageCode Value);
	virtual System::WideString __fastcall CodeToSymbol(const TIso639LanguageCode Value);
	virtual TIso639LanguageCode __fastcall NameToCode(const System::WideString Value);
	virtual TIso639LanguageCode __fastcall SymbolToCode(const System::WideString Value);
	__property bool AppendSymbolToName = {read=FAppendSymbolToName, write=FAppendSymbolToName, default=0};
	__property TIso639LanguageCode NameLanguage = {read=FNameLanguage, write=SetNameLanguage, default=24};
	__property TIso639LanguageCodeSet SupportedLanguages = {read=FSupportedLanguages};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TIso639Info() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool __fastcall IsRFC3066LanguageTag(const System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall IsSubLanguage(const System::WideString Sublanguage, const System::WideString Superlanguage);
}	/* namespace Langutils */
}	/* namespace Internal */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_INTERNAL_LANGUTILS)
using namespace Xml::Internal::Langutils;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_INTERNAL)
using namespace Xml::Internal;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML)
using namespace Xml;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Xml_Internal_LangutilsHPP
