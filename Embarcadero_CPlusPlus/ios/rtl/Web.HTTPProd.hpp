// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.HTTPProd.pas' rev: 34.00 (iOS)

#ifndef Web_HttpprodHPP
#define Web_HttpprodHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Web.HTTPApp.hpp>
#include <System.Masks.hpp>

//-- user supplied -----------------------------------------------------------

namespace Web
{
namespace Httpprod
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IDesignerFileManager;
typedef System::DelphiInterface<IDesignerFileManager> _di_IDesignerFileManager;
class DELPHICLASS THTMLTagAttributes;
class DELPHICLASS THTMLTableAttributes;
class DELPHICLASS THTMLTableElementAttributes;
class DELPHICLASS THTMLTableHeaderAttributes;
class DELPHICLASS THTMLTableRowAttributes;
class DELPHICLASS THTMLTableCellAttributes;
__interface DELPHIINTERFACE IGetProducerTemplate;
typedef System::DelphiInterface<IGetProducerTemplate> _di_IGetProducerTemplate;
class DELPHICLASS TBasePageProducer;
class DELPHICLASS TCustomPageProducer;
class DELPHICLASS TPageProducer;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM THTMLAlign : unsigned char { haDefault, haLeft, haRight, haCenter };

enum DECLSPEC_DENUM THTMLVAlign : unsigned char { haVDefault, haTop, haMiddle, haBottom, haBaseline };

_DECLARE_STRING_TYPE_ALIAS(System::UnicodeString, THTMLBgColor);

__interface  INTERFACE_UUID("{1DF271BF-F2EC-11D4-A559-00C04F6BB853}") IDesignerFileManager  : public System::IInterface 
{
	virtual System::UnicodeString __fastcall QualifyFileName(const System::UnicodeString AFileName) = 0 ;
	virtual System::Classes::TStream* __fastcall GetStream(const System::UnicodeString AFileName, bool &AOwned) = 0 ;
};

class PASCALIMPLEMENTATION THTMLTagAttributes : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	Web::Httpapp::TCustomContentProducer* FProducer;
	System::UnicodeString FCustom;
	System::Classes::TNotifyEvent FOnChange;
	void __fastcall SetCustom(const System::UnicodeString Value);
	
protected:
	void __fastcall Changed();
	
public:
	__fastcall THTMLTagAttributes(Web::Httpapp::TCustomContentProducer* Producer);
	virtual void __fastcall RestoreDefaults();
	__property Web::Httpapp::TCustomContentProducer* Producer = {read=FProducer};
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	
__published:
	__property System::UnicodeString Custom = {read=FCustom, write=SetCustom};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~THTMLTagAttributes() { }
	
};


class PASCALIMPLEMENTATION THTMLTableAttributes : public THTMLTagAttributes
{
	typedef THTMLTagAttributes inherited;
	
private:
	THTMLAlign FAlign;
	int FBorder;
	THTMLBgColor FBgColor;
	int FCellSpacing;
	int FCellPadding;
	int FWidth;
	void __fastcall SetAlign(THTMLAlign Value);
	void __fastcall SetBorder(int Value);
	void __fastcall SetBGColor(THTMLBgColor Value);
	void __fastcall SetCellSpacing(int Value);
	void __fastcall SetCellPadding(int Value);
	void __fastcall SetWidth(int Value);
	
protected:
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	
public:
	__fastcall THTMLTableAttributes(Web::Httpapp::TCustomContentProducer* Producer);
	virtual void __fastcall RestoreDefaults();
	
__published:
	__property THTMLAlign Align = {read=FAlign, write=SetAlign, default=0};
	__property THTMLBgColor BgColor = {read=FBgColor, write=SetBGColor};
	__property int Border = {read=FBorder, write=SetBorder, default=-1};
	__property int CellSpacing = {read=FCellSpacing, write=SetCellSpacing, default=-1};
	__property int CellPadding = {read=FCellPadding, write=SetCellPadding, default=-1};
	__property int Width = {read=FWidth, write=SetWidth, default=100};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~THTMLTableAttributes() { }
	
};


class PASCALIMPLEMENTATION THTMLTableElementAttributes : public THTMLTagAttributes
{
	typedef THTMLTagAttributes inherited;
	
private:
	THTMLAlign FAlign;
	THTMLBgColor FBgColor;
	THTMLVAlign FVAlign;
	void __fastcall SetAlign(THTMLAlign Value);
	void __fastcall SetBGColor(THTMLBgColor Value);
	void __fastcall SetVAlign(THTMLVAlign Value);
	
protected:
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	
public:
	virtual void __fastcall RestoreDefaults();
	
__published:
	__property THTMLAlign Align = {read=FAlign, write=SetAlign, default=0};
	__property THTMLBgColor BgColor = {read=FBgColor, write=SetBGColor};
	__property THTMLVAlign VAlign = {read=FVAlign, write=SetVAlign, default=0};
public:
	/* THTMLTagAttributes.Create */ inline __fastcall THTMLTableElementAttributes(Web::Httpapp::TCustomContentProducer* Producer) : THTMLTagAttributes(Producer) { }
	
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~THTMLTableElementAttributes() { }
	
};


class PASCALIMPLEMENTATION THTMLTableHeaderAttributes : public THTMLTableElementAttributes
{
	typedef THTMLTableElementAttributes inherited;
	
private:
	System::UnicodeString FCaption;
	void __fastcall SetCaption(System::UnicodeString Value);
	
protected:
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	
public:
	virtual void __fastcall RestoreDefaults();
	
__published:
	__property System::UnicodeString Caption = {read=FCaption, write=SetCaption};
public:
	/* THTMLTagAttributes.Create */ inline __fastcall THTMLTableHeaderAttributes(Web::Httpapp::TCustomContentProducer* Producer) : THTMLTableElementAttributes(Producer) { }
	
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~THTMLTableHeaderAttributes() { }
	
};


class PASCALIMPLEMENTATION THTMLTableRowAttributes : public THTMLTableElementAttributes
{
	typedef THTMLTableElementAttributes inherited;
	
public:
	/* THTMLTagAttributes.Create */ inline __fastcall THTMLTableRowAttributes(Web::Httpapp::TCustomContentProducer* Producer) : THTMLTableElementAttributes(Producer) { }
	
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~THTMLTableRowAttributes() { }
	
};


class PASCALIMPLEMENTATION THTMLTableCellAttributes : public THTMLTableElementAttributes
{
	typedef THTMLTableElementAttributes inherited;
	
public:
	/* THTMLTagAttributes.Create */ inline __fastcall THTMLTableCellAttributes(Web::Httpapp::TCustomContentProducer* Producer) : THTMLTableElementAttributes(Producer) { }
	
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~THTMLTableCellAttributes() { }
	
};


enum DECLSPEC_DENUM TTag : unsigned char { tgCustom, tgLink, tgImage, tgTable, tgImageMap, tgObject, tgEmbed };

typedef void __fastcall (__closure *THTMLTagEvent)(System::TObject* Sender, TTag Tag, const System::UnicodeString TagString, System::Classes::TStrings* TagParams, System::UnicodeString &ReplaceText);

__interface  INTERFACE_UUID("{44AA3FC1-FEB9-11D4-A566-00C04F6BB853}") IGetProducerTemplate  : public System::IInterface 
{
	virtual System::Classes::TStream* __fastcall GetProducerTemplateStream(/* out */ bool &AOwned) = 0 ;
	virtual System::UnicodeString __fastcall GetProducerTemplateFileName() = 0 ;
};

typedef System::TObject TWebModuleContext;

class PASCALIMPLEMENTATION TBasePageProducer : public Web::Httpapp::TCustomContentProducer
{
	typedef Web::Httpapp::TCustomContentProducer inherited;
	
private:
	THTMLTagEvent FOnHTMLTag;
	System::UnicodeString FScriptEngine;
	bool FStripParamQuotes;
	System::TObject* __fastcall GetWebModuleContext _DEPRECATED_ATTRIBUTE0 ();
	void __fastcall ReadScriptEngine(System::Classes::TReader* AReader);
	
protected:
	virtual System::UnicodeString __fastcall GetScriptEngine _DEPRECATED_ATTRIBUTE0 ();
	virtual bool __fastcall UseScriptEngine _DEPRECATED_ATTRIBUTE0 ();
	TTag __fastcall GetTagID(const System::UnicodeString TagString);
	virtual System::UnicodeString __fastcall HandleTag(const System::UnicodeString TagString, System::Classes::TStrings* TagParams);
	System::UnicodeString __fastcall ImplHandleTag(const System::UnicodeString TagString, System::Classes::TStrings* TagParams);
	DYNAMIC void __fastcall DoTagEvent(TTag Tag, const System::UnicodeString TagString, System::Classes::TStrings* TagParams, System::UnicodeString &ReplaceText);
	virtual bool __fastcall HandleScriptTag _DEPRECATED_ATTRIBUTE0 (const System::UnicodeString TagString, System::Classes::TStrings* TagParams, System::UnicodeString &ReplaceString);
	System::UnicodeString __fastcall ServerScriptFromStream _DEPRECATED_ATTRIBUTE0 (System::Classes::TStream* Stream);
	System::Classes::TStream* __fastcall GetProducerTemplateStream(/* out */ bool &AOwned);
	System::UnicodeString __fastcall GetProducerTemplateFileName();
	virtual System::UnicodeString __fastcall GetTemplateFileName();
	virtual System::Classes::TStream* __fastcall GetTemplateStream(/* out */ bool &AOwned);
	__property THTMLTagEvent OnHTMLTag = {read=FOnHTMLTag, write=FOnHTMLTag};
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	
public:
	__fastcall virtual TBasePageProducer(System::Classes::TComponent* AOwner);
	virtual System::UnicodeString __fastcall Content();
	virtual System::UnicodeString __fastcall ContentFromStream(System::Classes::TStream* Stream);
	virtual System::UnicodeString __fastcall ContentFromString(const System::UnicodeString S);
	__property System::TObject* WebModuleContext = {read=GetWebModuleContext};
	__property bool StripParamQuotes = {read=FStripParamQuotes, write=FStripParamQuotes, default=1};
	__property System::UnicodeString ScriptEngine = {read=GetScriptEngine};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TBasePageProducer() { }
	
private:
	void *__IGetProducerTemplate;	// IGetProducerTemplate 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {44AA3FC1-FEB9-11D4-A566-00C04F6BB853}
	operator _di_IGetProducerTemplate()
	{
		_di_IGetProducerTemplate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IGetProducerTemplate*(void) { return (IGetProducerTemplate*)&__IGetProducerTemplate; }
	#endif
	
};


class PASCALIMPLEMENTATION TCustomPageProducer : public TBasePageProducer
{
	typedef TBasePageProducer inherited;
	
private:
	System::Sysutils::TFileName FHTMLFile;
	System::Classes::TStrings* FHTMLDoc;
	void __fastcall SetHTMLFile(const System::Sysutils::TFileName Value);
	void __fastcall SetHTMLDoc(System::Classes::TStrings* Value);
	
protected:
	virtual System::Classes::TStream* __fastcall GetTemplateStream(/* out */ bool &AOwned);
	virtual System::UnicodeString __fastcall HandleTag(const System::UnicodeString TagString, System::Classes::TStrings* TagParams);
	virtual System::UnicodeString __fastcall GetTemplateFileName();
	
public:
	__fastcall virtual TCustomPageProducer(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomPageProducer();
	__property System::Classes::TStrings* HTMLDoc = {read=FHTMLDoc, write=SetHTMLDoc};
	__property System::Sysutils::TFileName HTMLFile = {read=FHTMLFile, write=SetHTMLFile};
};


class PASCALIMPLEMENTATION TPageProducer : public TCustomPageProducer
{
	typedef TCustomPageProducer inherited;
	
__published:
	__property HTMLDoc;
	__property HTMLFile = {default=0};
	__property StripParamQuotes = {default=1};
	__property OnHTMLTag;
public:
	/* TCustomPageProducer.Create */ inline __fastcall virtual TPageProducer(System::Classes::TComponent* AOwner) : TCustomPageProducer(AOwner) { }
	/* TCustomPageProducer.Destroy */ inline __fastcall virtual ~TPageProducer() { }
	
};


typedef System::UnicodeString __fastcall (__closure *THandleTagProc)(const System::UnicodeString TagString, System::Classes::TStrings* TagParams);

typedef bool __fastcall (__closure *THandledTagProc)(const System::UnicodeString TagString, System::Classes::TStrings* TagParams, System::UnicodeString &ReplaceString);

typedef System::StaticArray<System::UnicodeString, 4> Web_Httpprod__01;

typedef System::StaticArray<System::UnicodeString, 5> Web_Httpprod__11;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE Web_Httpprod__01 HTMLAlign;
extern DELPHI_PACKAGE Web_Httpprod__11 HTMLVAlign;
extern DELPHI_PACKAGE _di_IDesignerFileManager DesignerFileManager;
extern DELPHI_PACKAGE TTag __fastcall GetTagID(const System::UnicodeString TagString);
extern DELPHI_PACKAGE System::Sysutils::TEncoding* __fastcall GetEncodingOfStream(System::Classes::TStream* AStream, /* out */ int &ASignatureSize);
extern DELPHI_PACKAGE System::UnicodeString __fastcall ContentFromStream(System::Classes::TStream* AStream, bool AStripParamQuotes, THandleTagProc AHandleTag, THandledTagProc AHandledTag);
extern DELPHI_PACKAGE System::UnicodeString __fastcall ContentFromString(const System::UnicodeString AValue, bool AStripParamQuotes, THandleTagProc AHandleTag, THandledTagProc AHandledTag);
extern DELPHI_PACKAGE System::UnicodeString __fastcall QualifyFileName(const System::UnicodeString AFileName);
}	/* namespace Httpprod */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_HTTPPROD)
using namespace Web::Httpprod;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_HttpprodHPP
