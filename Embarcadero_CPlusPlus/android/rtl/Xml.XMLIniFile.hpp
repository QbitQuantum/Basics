// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.XMLIniFile.pas' rev: 34.00 (Android)

#ifndef Xml_XmlinifileHPP
#define Xml_XmlinifileHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.IniFiles.hpp>
#include <Xml.XMLIntf.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Xmlinifile
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TXmlIniFile;
class DELPHICLASS TXmlMemIniFile;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlIniFile : public System::Inifiles::TCustomIniFile
{
	typedef System::Inifiles::TCustomIniFile inherited;
	
private:
	Xml::Xmlintf::_di_IXMLNode FNode;
	Xml::Xmlintf::_di_IXMLNode __fastcall FindXmlNode(const System::UnicodeString NodeName);
	Xml::Xmlintf::_di_IXMLNode __fastcall FindXmlNodeOrAdd(const System::UnicodeString NodeName);
	void __fastcall DeleteChildNode(Xml::Xmlintf::_di_IXMLNode AParentNode, int AIndex);
	System::UnicodeString __fastcall ReadXmlString(const System::UnicodeString Section, const System::UnicodeString Name, const System::UnicodeString Default);
	void __fastcall WriteXmlString(const System::UnicodeString Section, const System::UnicodeString Name, const System::UnicodeString Value);
	void __fastcall GetSectionValues(const System::UnicodeString Section, System::Classes::TStrings* const Strings);
	
public:
	__fastcall TXmlIniFile(const Xml::Xmlintf::_di_IXMLNode ANode);
	virtual System::UnicodeString __fastcall ReadString(const System::UnicodeString Section, const System::UnicodeString Ident, const System::UnicodeString Default);
	virtual void __fastcall WriteString(const System::UnicodeString Section, const System::UnicodeString Ident, const System::UnicodeString Value);
	virtual int __fastcall ReadInteger(const System::UnicodeString Section, const System::UnicodeString Ident, int Default);
	virtual void __fastcall WriteInteger(const System::UnicodeString Section, const System::UnicodeString Ident, int Value);
	virtual bool __fastcall ReadBool(const System::UnicodeString Section, const System::UnicodeString Ident, bool Default);
	virtual void __fastcall WriteBool(const System::UnicodeString Section, const System::UnicodeString Ident, bool Value);
	virtual void __fastcall DeleteKey(const System::UnicodeString Section, const System::UnicodeString Ident);
	virtual void __fastcall ReadSection(const System::UnicodeString Section, System::Classes::TStrings* Strings);
	virtual void __fastcall ReadSections(System::Classes::TStrings* Strings)/* overload */;
	virtual void __fastcall ReadSectionValues(const System::UnicodeString Section, System::Classes::TStrings* Strings);
	virtual void __fastcall EraseSection(const System::UnicodeString Section);
	virtual void __fastcall UpdateFile();
	virtual bool __fastcall ValueExists(const System::UnicodeString Section, const System::UnicodeString Ident);
	void __fastcall GetStrings(System::Classes::TStrings* const List);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlIniFile() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  ReadSections(const System::UnicodeString Section, System::Classes::TStrings* Strings){ System::Inifiles::TCustomIniFile::ReadSections(Section, Strings); }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlMemIniFile : public System::Inifiles::TMemIniFile
{
	typedef System::Inifiles::TMemIniFile inherited;
	
private:
	TXmlIniFile* FXmlIniFile;
	HIDESBASE void __fastcall LoadValues();
	
public:
	__fastcall TXmlMemIniFile(const Xml::Xmlintf::_di_IXMLNode ANode);
	__fastcall virtual ~TXmlMemIniFile();
	virtual void __fastcall UpdateFile();
	virtual bool __fastcall ReadBool(const System::UnicodeString Section, const System::UnicodeString Ident, bool Default);
	virtual int __fastcall ReadInteger(const System::UnicodeString Section, const System::UnicodeString Ident, int Default);
	virtual System::UnicodeString __fastcall ReadString(const System::UnicodeString Section, const System::UnicodeString Ident, const System::UnicodeString Default);
	virtual void __fastcall DeleteKey(const System::UnicodeString Section, const System::UnicodeString Ident);
	virtual void __fastcall EraseSection(const System::UnicodeString Section);
	virtual void __fastcall WriteString(const System::UnicodeString Section, const System::UnicodeString Ident, const System::UnicodeString Value);
	virtual void __fastcall WriteBool(const System::UnicodeString Section, const System::UnicodeString Ident, bool Value);
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Xmlinifile */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_XMLINIFILE)
using namespace Xml::Xmlinifile;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML)
using namespace Xml;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Xml_XmlinifileHPP
