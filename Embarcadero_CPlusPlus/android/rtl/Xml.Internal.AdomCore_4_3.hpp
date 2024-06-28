// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.Internal.AdomCore_4_3.pas' rev: 34.00 (Android)

#ifndef Xml_Internal_Adomcore_4_3HPP
#define Xml_Internal_Adomcore_4_3HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Xml.Internal.CodecUtilsWin32.hpp>
#include <Xml.Internal.ParserUtilsWin32.hpp>
#include <Xml.Internal.TreeUtils.hpp>
#include <Xml.Internal.WideStringUtils.hpp>
#include <Xml.xmldom.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Internal
{
namespace Adomcore_4_3
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EDomException;
class DELPHICLASS EIndex_Size_Err;
class DELPHICLASS EHierarchy_Request_Err;
class DELPHICLASS EWrong_Document_Err;
class DELPHICLASS EInvalid_Character_Err;
class DELPHICLASS ENo_Data_Allowed_Err;
class DELPHICLASS ENo_Modification_Allowed_Err;
class DELPHICLASS ENot_Found_Err;
class DELPHICLASS ENot_Supported_Err;
class DELPHICLASS EInuse_Err;
class DELPHICLASS EInvalid_State_Err;
class DELPHICLASS ESyntax_Err;
class DELPHICLASS EInvalid_Modification_Err;
class DELPHICLASS ENamespace_Err;
class DELPHICLASS EWrong_DOM_Implementation_Err;
class DELPHICLASS EParserException;
class DELPHICLASS EXPath_Exception;
class DELPHICLASS EXPath_Invalid_Expression_Err;
class DELPHICLASS EXPath_Invalid_Function_Call_Err;
class DELPHICLASS EXPath_Type_Err;
class DELPHICLASS TUtilsNoRefCount;
class DELPHICLASS TDomBaseComponent;
class DELPHICLASS TDomImplementation;
class DELPHICLASS TDomNodeFilter;
class DELPHICLASS TDomTreeWalker;
class DELPHICLASS TDomNodeIterator;
class DELPHICLASS TDomNodeList;
class DELPHICLASS TDomElementsNodeList;
class DELPHICLASS TDomElementsNodeListNS;
class DELPHICLASS TDomCustomNode;
class DELPHICLASS TDomNamedNodeMap;
class DELPHICLASS TDomNode;
class DELPHICLASS TDomCharacterData;
class DELPHICLASS TDomAttr;
class DELPHICLASS TDomElement;
class DELPHICLASS TDomText;
class DELPHICLASS TDomComment;
class DELPHICLASS TDomProcessingInstruction;
class DELPHICLASS TDomCDATASection;
class DELPHICLASS TDomDocumentTypeDecl;
class DELPHICLASS TDomEntityReference;
class DELPHICLASS TDomDocumentFragment;
class DELPHICLASS TDomXPathNamespace;
class DELPHICLASS TDomCustomDocument;
class DELPHICLASS TDomDocument;
class DELPHICLASS TDomDocumentNS;
class DELPHICLASS TDomDocumentXPath;
__interface DELPHIINTERFACE IDomLocator;
typedef System::DelphiInterface<IDomLocator> _di_IDomLocator;
class DELPHICLASS TDomError;
class DELPHICLASS TDtdObjectList;
class DELPHICLASS TDtdNamedObjectMap;
class DELPHICLASS TDtdValidationAgent;
class DELPHICLASS TDtdObject;
class DELPHICLASS TDtdContentModel;
class DELPHICLASS TDtdAttDeclCollection;
class DELPHICLASS TDtdAttributeDecl;
class DELPHICLASS TDtdElementDecl;
class DELPHICLASS TDtdEntityDecl;
class DELPHICLASS TDtdNotationDecl;
class DELPHICLASS TDtdModel;
class DELPHICLASS TDomAbstractView;
class DELPHICLASS TDomStyleSheet;
class DELPHICLASS TDomMediaList;
class DELPHICLASS TDomStyleSheetList;
class DELPHICLASS TDomDocumentStyle;
class DELPHICLASS TXmlSourceCode;
class DELPHICLASS TXmlSourceCodePiece;
class DELPHICLASS TCustomResourceResolver;
class DELPHICLASS TStandardResourceResolver;
class DELPHICLASS TXmlSimpleInputSource;
class DELPHICLASS TXmlInputSource;
class DELPHICLASS TXmlCustomTokenizer;
class DELPHICLASS TXmlDocTokenizer;
class DELPHICLASS TXmlDtdDetailTokenizer;
class DELPHICLASS TXmlDtdDetailPETokenizer;
class DELPHICLASS TXmlCustomSubsetTokenizer;
class DELPHICLASS TXmlExtSubsetTokenizer;
class DELPHICLASS TXmlIntSubsetTokenizer;
class DELPHICLASS TXmlElementCMTokenizer;
class DELPHICLASS TXmlDoctypeDeclTokenizer;
class DELPHICLASS TXmlAttrValueTokenizer;
class DELPHICLASS TXmlOutputSource;
class DELPHICLASS TDomPERepository;
class DELPHICLASS TDomPEInfoObject;
class DELPHICLASS TXmlSignal;
class DELPHICLASS TXmlCompletedSignal;
class DELPHICLASS TXmlAbortedSignal;
class DELPHICLASS TXmlAttributeSignal;
class DELPHICLASS TXmlCDATASignal;
class DELPHICLASS TXmlDoctypeSignal;
class DELPHICLASS TXmlEndElementSignal;
class DELPHICLASS TXmlEndPrefixMappingSignal;
class DELPHICLASS TXmlEntityRefSignal;
class DELPHICLASS TXmlPCDATASignal;
class DELPHICLASS TXmlSkippedEntitySignal;
class DELPHICLASS TXmlStartDocumentSignal;
class DELPHICLASS TXmlStartDocumentFragmentSignal;
class DELPHICLASS TXmlStartElementSignal;
class DELPHICLASS TXmlStartPrefixMappingSignal;
class DELPHICLASS TXmlCommentSignal;
class DELPHICLASS TXmlProcessingInstructionSignal;
class DELPHICLASS TXmlAttributeDefinitionSignal;
class DELPHICLASS TXmlElementTypeDeclarationSignal;
class DELPHICLASS TXmlEntityDeclarationSignal;
class DELPHICLASS TXmlExternalPEReferenceSignal;
class DELPHICLASS TXmlNotationDeclarationSignal;
class DELPHICLASS TXmlParameterEntityDeclarationSignal;
class DELPHICLASS TXmlPEReferenceFoundSignal;
class DELPHICLASS TXmlStartExtDtdSignal;
class DELPHICLASS TXmlStartIntDtdSignal;
class DELPHICLASS TXmlCustomReader;
class DELPHICLASS TXmlStandardDocReader;
class DELPHICLASS TXmlStandardDtdReader;
class DELPHICLASS TXmlStandardDomReader;
class DELPHICLASS TXmlCustomHandler;
class DELPHICLASS TXmlStandardHandler;
class DELPHICLASS TXmlHandlerItem;
class DELPHICLASS TXmlHandlers;
class DELPHICLASS TXmlDistributor;
class DELPHICLASS TXmlWFTestHandler;
class DELPHICLASS TXmlNamespaceSignalGenerator;
class DELPHICLASS TXmlDomBuilder;
class DELPHICLASS TXmlDtdModelBuilder;
class DELPHICLASS TXmlStreamBuilder;
class DELPHICLASS TXmlStreamBuilderExt;
class DELPHICLASS TXmlCustomParser;
class DELPHICLASS TXmlToDomParser;
class DELPHICLASS TDtdToDtdModelParser;
class DELPHICLASS TDomToXmlParser;
class DELPHICLASS TDomToXmlParserExt;
class DELPHICLASS TDomXPathTokenizer;
class DELPHICLASS TDomXPathCustomResult;
class DELPHICLASS TDomXPathNodeSetResult;
class DELPHICLASS TDomXPathBooleanResult;
class DELPHICLASS TDomXPathNumberResult;
class DELPHICLASS TDomXPathStringResult;
class DELPHICLASS TDomXPathSyntaxTree;
class DELPHICLASS TXPathExpression;
class DELPHICLASS TDomXPathSyntaxNodeStack;
class DELPHICLASS TDomXPathSyntaxNode;
class DELPHICLASS TDomXPathAbsoluteLocationPath;
class DELPHICLASS TDomXPathStep;
class DELPHICLASS TDomXPathCustomAxisName;
class DELPHICLASS TDomXPathAxisNameAncestor;
class DELPHICLASS TDomXPathAxisNameAncestorOrSelf;
class DELPHICLASS TDomXPathAxisNameAttribute;
class DELPHICLASS TDomXPathAxisNameChild;
class DELPHICLASS TDomXPathAxisNameDescendant;
class DELPHICLASS TDomXPathAxisNameDescendantOrSelf;
class DELPHICLASS TDomXPathAxisNameFollowing;
class DELPHICLASS TDomXPathAxisNameFollowingSibling;
class DELPHICLASS TDomXPathAxisNameNamespace;
class DELPHICLASS TDomXPathAxisNameParent;
class DELPHICLASS TDomXPathAxisNamePreceding;
class DELPHICLASS TDomXPathAxisNamePrecedingSibling;
class DELPHICLASS TDomXPathAxisNameSelf;
class DELPHICLASS TDomXPathNodeTest;
class DELPHICLASS TDomXPathPredicate;
class DELPHICLASS TDomXPathExpr;
class DELPHICLASS TDomXPathPrimaryExpr;
class DELPHICLASS TDomXPathFunctionCall;
class DELPHICLASS TDomXPathUnionExpr;
class DELPHICLASS TDomXPathPathExpr;
class DELPHICLASS TDomXPathFilterExpr;
class DELPHICLASS TDomXPathOrExpr;
class DELPHICLASS TDomXPathAndExpr;
class DELPHICLASS TDomXPathEqualityExpr;
class DELPHICLASS TDomXPathIsEqualExpr;
class DELPHICLASS TDomXPathIsNotEqualExpr;
class DELPHICLASS TDomXPathRelationalExpr;
class DELPHICLASS TDomXPathLessThanExpr;
class DELPHICLASS TDomXPathLessThanOrEqualExpr;
class DELPHICLASS TDomXPathGreaterThanExpr;
class DELPHICLASS TDomXPathGreaterThanOrEqualExpr;
class DELPHICLASS TDomXPathAdditiveExpr;
class DELPHICLASS TDomXPathPlusExpr;
class DELPHICLASS TDomXPathMinusExpr;
class DELPHICLASS TDomXPathMultiplicativeExpr;
class DELPHICLASS TDomXPathMultiplyExpr;
class DELPHICLASS TDomXPathDivExpr;
class DELPHICLASS TDomXPathModExpr;
class DELPHICLASS TDomXPathUnaryExpr;
class DELPHICLASS TDomXPathLeftParenthesis;
class DELPHICLASS TDomXPathRightParenthesis;
class DELPHICLASS TDomXPathLeftSquareBracket;
class DELPHICLASS TDomXPathRightSquareBracket;
class DELPHICLASS TDomXPathSingleDot;
class DELPHICLASS TDomXPathDoubleDot;
class DELPHICLASS TDomXPathCommercialAt;
class DELPHICLASS TDomXPathComma;
class DELPHICLASS TDomXPathDoubleColon;
class DELPHICLASS TDomXPathLiteral;
class DELPHICLASS TDomXPathNumber;
class DELPHICLASS TDomXPathSlashOperator;
class DELPHICLASS TDomXPathShefferStrokeOperator;
class DELPHICLASS TDomXPathPlusOperator;
class DELPHICLASS TDomXPathMinusOperator;
class DELPHICLASS TDomXPathIsEqualOperator;
class DELPHICLASS TDomXPathIsNotEqualOperator;
class DELPHICLASS TDomXPathLessThanOperator;
class DELPHICLASS TDomXPathLessThanOrEqualOperator;
class DELPHICLASS TDomXPathGreaterThanOperator;
class DELPHICLASS TDomXPathGreaterThanOrEqualOperator;
class DELPHICLASS TDomXPathAndOperator;
class DELPHICLASS TDomXPathOrOperator;
class DELPHICLASS TDomXPathModOperator;
class DELPHICLASS TDomXPathDivOperator;
class DELPHICLASS TDomXPathMultiplyOperator;
class DELPHICLASS TDomXPathFunctionName;
class DELPHICLASS TDomXPathVariableReference;
class DELPHICLASS TDomXPathNameTest;
class DELPHICLASS TDomXPathNodeTypeComment;
class DELPHICLASS TDomXPathNodeTypeNode;
class DELPHICLASS TDomXPathNodeTypePI;
class DELPHICLASS TDomXPathNodeTypeText;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EDomException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EDomException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EDomException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EDomException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EDomException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EDomException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EDomException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EDomException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EDomException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDomException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDomException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDomException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDomException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EDomException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIndex_Size_Err : public EDomException
{
	typedef EDomException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EIndex_Size_Err(const System::UnicodeString Msg) : EDomException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EIndex_Size_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EDomException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIndex_Size_Err(NativeUInt Ident)/* overload */ : EDomException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIndex_Size_Err(System::PResStringRec ResStringRec)/* overload */ : EDomException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIndex_Size_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIndex_Size_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIndex_Size_Err(const System::UnicodeString Msg, int AHelpContext) : EDomException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIndex_Size_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EDomException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIndex_Size_Err(NativeUInt Ident, int AHelpContext)/* overload */ : EDomException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIndex_Size_Err(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EDomException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIndex_Size_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIndex_Size_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIndex_Size_Err() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EHierarchy_Request_Err : public EDomException
{
	typedef EDomException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EHierarchy_Request_Err(const System::UnicodeString Msg) : EDomException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EHierarchy_Request_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EDomException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EHierarchy_Request_Err(NativeUInt Ident)/* overload */ : EDomException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EHierarchy_Request_Err(System::PResStringRec ResStringRec)/* overload */ : EDomException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EHierarchy_Request_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EHierarchy_Request_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EHierarchy_Request_Err(const System::UnicodeString Msg, int AHelpContext) : EDomException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EHierarchy_Request_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EDomException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EHierarchy_Request_Err(NativeUInt Ident, int AHelpContext)/* overload */ : EDomException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EHierarchy_Request_Err(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EDomException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EHierarchy_Request_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EHierarchy_Request_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EHierarchy_Request_Err() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EWrong_Document_Err : public EDomException
{
	typedef EDomException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EWrong_Document_Err(const System::UnicodeString Msg) : EDomException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EWrong_Document_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EDomException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EWrong_Document_Err(NativeUInt Ident)/* overload */ : EDomException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EWrong_Document_Err(System::PResStringRec ResStringRec)/* overload */ : EDomException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EWrong_Document_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EWrong_Document_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EWrong_Document_Err(const System::UnicodeString Msg, int AHelpContext) : EDomException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EWrong_Document_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EDomException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWrong_Document_Err(NativeUInt Ident, int AHelpContext)/* overload */ : EDomException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWrong_Document_Err(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EDomException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWrong_Document_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWrong_Document_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EWrong_Document_Err() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EInvalid_Character_Err : public EDomException
{
	typedef EDomException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EInvalid_Character_Err(const System::UnicodeString Msg) : EDomException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EInvalid_Character_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EDomException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EInvalid_Character_Err(NativeUInt Ident)/* overload */ : EDomException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EInvalid_Character_Err(System::PResStringRec ResStringRec)/* overload */ : EDomException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EInvalid_Character_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EInvalid_Character_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EInvalid_Character_Err(const System::UnicodeString Msg, int AHelpContext) : EDomException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EInvalid_Character_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EDomException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EInvalid_Character_Err(NativeUInt Ident, int AHelpContext)/* overload */ : EDomException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EInvalid_Character_Err(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EDomException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EInvalid_Character_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EInvalid_Character_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EInvalid_Character_Err() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ENo_Data_Allowed_Err : public EDomException
{
	typedef EDomException inherited;
	
public:
	/* Exception.Create */ inline __fastcall ENo_Data_Allowed_Err(const System::UnicodeString Msg) : EDomException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ENo_Data_Allowed_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EDomException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ENo_Data_Allowed_Err(NativeUInt Ident)/* overload */ : EDomException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ENo_Data_Allowed_Err(System::PResStringRec ResStringRec)/* overload */ : EDomException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ENo_Data_Allowed_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ENo_Data_Allowed_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ENo_Data_Allowed_Err(const System::UnicodeString Msg, int AHelpContext) : EDomException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ENo_Data_Allowed_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EDomException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENo_Data_Allowed_Err(NativeUInt Ident, int AHelpContext)/* overload */ : EDomException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENo_Data_Allowed_Err(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EDomException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENo_Data_Allowed_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENo_Data_Allowed_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ENo_Data_Allowed_Err() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ENo_Modification_Allowed_Err : public EDomException
{
	typedef EDomException inherited;
	
public:
	/* Exception.Create */ inline __fastcall ENo_Modification_Allowed_Err(const System::UnicodeString Msg) : EDomException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ENo_Modification_Allowed_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EDomException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ENo_Modification_Allowed_Err(NativeUInt Ident)/* overload */ : EDomException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ENo_Modification_Allowed_Err(System::PResStringRec ResStringRec)/* overload */ : EDomException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ENo_Modification_Allowed_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ENo_Modification_Allowed_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ENo_Modification_Allowed_Err(const System::UnicodeString Msg, int AHelpContext) : EDomException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ENo_Modification_Allowed_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EDomException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENo_Modification_Allowed_Err(NativeUInt Ident, int AHelpContext)/* overload */ : EDomException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENo_Modification_Allowed_Err(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EDomException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENo_Modification_Allowed_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENo_Modification_Allowed_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ENo_Modification_Allowed_Err() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ENot_Found_Err : public EDomException
{
	typedef EDomException inherited;
	
public:
	/* Exception.Create */ inline __fastcall ENot_Found_Err(const System::UnicodeString Msg) : EDomException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ENot_Found_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EDomException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ENot_Found_Err(NativeUInt Ident)/* overload */ : EDomException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ENot_Found_Err(System::PResStringRec ResStringRec)/* overload */ : EDomException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ENot_Found_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ENot_Found_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ENot_Found_Err(const System::UnicodeString Msg, int AHelpContext) : EDomException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ENot_Found_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EDomException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENot_Found_Err(NativeUInt Ident, int AHelpContext)/* overload */ : EDomException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENot_Found_Err(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EDomException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENot_Found_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENot_Found_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ENot_Found_Err() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ENot_Supported_Err : public EDomException
{
	typedef EDomException inherited;
	
public:
	/* Exception.Create */ inline __fastcall ENot_Supported_Err(const System::UnicodeString Msg) : EDomException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ENot_Supported_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EDomException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ENot_Supported_Err(NativeUInt Ident)/* overload */ : EDomException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ENot_Supported_Err(System::PResStringRec ResStringRec)/* overload */ : EDomException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ENot_Supported_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ENot_Supported_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ENot_Supported_Err(const System::UnicodeString Msg, int AHelpContext) : EDomException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ENot_Supported_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EDomException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENot_Supported_Err(NativeUInt Ident, int AHelpContext)/* overload */ : EDomException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENot_Supported_Err(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EDomException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENot_Supported_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENot_Supported_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ENot_Supported_Err() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EInuse_Err : public EDomException
{
	typedef EDomException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EInuse_Err(const System::UnicodeString Msg) : EDomException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EInuse_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EDomException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EInuse_Err(NativeUInt Ident)/* overload */ : EDomException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EInuse_Err(System::PResStringRec ResStringRec)/* overload */ : EDomException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EInuse_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EInuse_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EInuse_Err(const System::UnicodeString Msg, int AHelpContext) : EDomException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EInuse_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EDomException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EInuse_Err(NativeUInt Ident, int AHelpContext)/* overload */ : EDomException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EInuse_Err(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EDomException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EInuse_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EInuse_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EInuse_Err() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EInvalid_State_Err : public EDomException
{
	typedef EDomException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EInvalid_State_Err(const System::UnicodeString Msg) : EDomException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EInvalid_State_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EDomException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EInvalid_State_Err(NativeUInt Ident)/* overload */ : EDomException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EInvalid_State_Err(System::PResStringRec ResStringRec)/* overload */ : EDomException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EInvalid_State_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EInvalid_State_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EInvalid_State_Err(const System::UnicodeString Msg, int AHelpContext) : EDomException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EInvalid_State_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EDomException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EInvalid_State_Err(NativeUInt Ident, int AHelpContext)/* overload */ : EDomException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EInvalid_State_Err(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EDomException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EInvalid_State_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EInvalid_State_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EInvalid_State_Err() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ESyntax_Err : public EDomException
{
	typedef EDomException inherited;
	
public:
	/* Exception.Create */ inline __fastcall ESyntax_Err(const System::UnicodeString Msg) : EDomException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ESyntax_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EDomException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ESyntax_Err(NativeUInt Ident)/* overload */ : EDomException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ESyntax_Err(System::PResStringRec ResStringRec)/* overload */ : EDomException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ESyntax_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ESyntax_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ESyntax_Err(const System::UnicodeString Msg, int AHelpContext) : EDomException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ESyntax_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EDomException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESyntax_Err(NativeUInt Ident, int AHelpContext)/* overload */ : EDomException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESyntax_Err(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EDomException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESyntax_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESyntax_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ESyntax_Err() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EInvalid_Modification_Err : public EDomException
{
	typedef EDomException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EInvalid_Modification_Err(const System::UnicodeString Msg) : EDomException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EInvalid_Modification_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EDomException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EInvalid_Modification_Err(NativeUInt Ident)/* overload */ : EDomException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EInvalid_Modification_Err(System::PResStringRec ResStringRec)/* overload */ : EDomException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EInvalid_Modification_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EInvalid_Modification_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EInvalid_Modification_Err(const System::UnicodeString Msg, int AHelpContext) : EDomException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EInvalid_Modification_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EDomException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EInvalid_Modification_Err(NativeUInt Ident, int AHelpContext)/* overload */ : EDomException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EInvalid_Modification_Err(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EDomException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EInvalid_Modification_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EInvalid_Modification_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EInvalid_Modification_Err() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ENamespace_Err : public EDomException
{
	typedef EDomException inherited;
	
public:
	/* Exception.Create */ inline __fastcall ENamespace_Err(const System::UnicodeString Msg) : EDomException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ENamespace_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EDomException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ENamespace_Err(NativeUInt Ident)/* overload */ : EDomException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ENamespace_Err(System::PResStringRec ResStringRec)/* overload */ : EDomException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ENamespace_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ENamespace_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ENamespace_Err(const System::UnicodeString Msg, int AHelpContext) : EDomException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ENamespace_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EDomException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENamespace_Err(NativeUInt Ident, int AHelpContext)/* overload */ : EDomException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENamespace_Err(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EDomException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENamespace_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENamespace_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ENamespace_Err() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EWrong_DOM_Implementation_Err : public EDomException
{
	typedef EDomException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EWrong_DOM_Implementation_Err(const System::UnicodeString Msg) : EDomException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EWrong_DOM_Implementation_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EDomException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EWrong_DOM_Implementation_Err(NativeUInt Ident)/* overload */ : EDomException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EWrong_DOM_Implementation_Err(System::PResStringRec ResStringRec)/* overload */ : EDomException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EWrong_DOM_Implementation_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EWrong_DOM_Implementation_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EWrong_DOM_Implementation_Err(const System::UnicodeString Msg, int AHelpContext) : EDomException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EWrong_DOM_Implementation_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EDomException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWrong_DOM_Implementation_Err(NativeUInt Ident, int AHelpContext)/* overload */ : EDomException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWrong_DOM_Implementation_Err(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EDomException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWrong_DOM_Implementation_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWrong_DOM_Implementation_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EWrong_DOM_Implementation_Err() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EParserException : public EDomException
{
	typedef EDomException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EParserException(const System::UnicodeString Msg) : EDomException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EParserException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EDomException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EParserException(NativeUInt Ident)/* overload */ : EDomException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EParserException(System::PResStringRec ResStringRec)/* overload */ : EDomException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EParserException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EParserException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EParserException(const System::UnicodeString Msg, int AHelpContext) : EDomException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EParserException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EDomException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EParserException(NativeUInt Ident, int AHelpContext)/* overload */ : EDomException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EParserException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EDomException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EParserException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EParserException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EParserException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EXPath_Exception : public EDomException
{
	typedef EDomException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EXPath_Exception(const System::UnicodeString Msg) : EDomException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EXPath_Exception(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EDomException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EXPath_Exception(NativeUInt Ident)/* overload */ : EDomException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EXPath_Exception(System::PResStringRec ResStringRec)/* overload */ : EDomException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EXPath_Exception(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EXPath_Exception(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EXPath_Exception(const System::UnicodeString Msg, int AHelpContext) : EDomException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EXPath_Exception(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EDomException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EXPath_Exception(NativeUInt Ident, int AHelpContext)/* overload */ : EDomException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EXPath_Exception(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EDomException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EXPath_Exception(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EXPath_Exception(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EXPath_Exception() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EXPath_Invalid_Expression_Err : public EXPath_Exception
{
	typedef EXPath_Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EXPath_Invalid_Expression_Err(const System::UnicodeString Msg) : EXPath_Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EXPath_Invalid_Expression_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EXPath_Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EXPath_Invalid_Expression_Err(NativeUInt Ident)/* overload */ : EXPath_Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EXPath_Invalid_Expression_Err(System::PResStringRec ResStringRec)/* overload */ : EXPath_Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EXPath_Invalid_Expression_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EXPath_Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EXPath_Invalid_Expression_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EXPath_Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EXPath_Invalid_Expression_Err(const System::UnicodeString Msg, int AHelpContext) : EXPath_Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EXPath_Invalid_Expression_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EXPath_Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EXPath_Invalid_Expression_Err(NativeUInt Ident, int AHelpContext)/* overload */ : EXPath_Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EXPath_Invalid_Expression_Err(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EXPath_Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EXPath_Invalid_Expression_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EXPath_Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EXPath_Invalid_Expression_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EXPath_Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EXPath_Invalid_Expression_Err() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EXPath_Invalid_Function_Call_Err : public EXPath_Exception
{
	typedef EXPath_Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EXPath_Invalid_Function_Call_Err(const System::UnicodeString Msg) : EXPath_Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EXPath_Invalid_Function_Call_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EXPath_Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EXPath_Invalid_Function_Call_Err(NativeUInt Ident)/* overload */ : EXPath_Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EXPath_Invalid_Function_Call_Err(System::PResStringRec ResStringRec)/* overload */ : EXPath_Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EXPath_Invalid_Function_Call_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EXPath_Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EXPath_Invalid_Function_Call_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EXPath_Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EXPath_Invalid_Function_Call_Err(const System::UnicodeString Msg, int AHelpContext) : EXPath_Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EXPath_Invalid_Function_Call_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EXPath_Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EXPath_Invalid_Function_Call_Err(NativeUInt Ident, int AHelpContext)/* overload */ : EXPath_Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EXPath_Invalid_Function_Call_Err(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EXPath_Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EXPath_Invalid_Function_Call_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EXPath_Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EXPath_Invalid_Function_Call_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EXPath_Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EXPath_Invalid_Function_Call_Err() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EXPath_Type_Err : public EXPath_Exception
{
	typedef EXPath_Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EXPath_Type_Err(const System::UnicodeString Msg) : EXPath_Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EXPath_Type_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EXPath_Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EXPath_Type_Err(NativeUInt Ident)/* overload */ : EXPath_Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EXPath_Type_Err(System::PResStringRec ResStringRec)/* overload */ : EXPath_Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EXPath_Type_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EXPath_Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EXPath_Type_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EXPath_Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EXPath_Type_Err(const System::UnicodeString Msg, int AHelpContext) : EXPath_Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EXPath_Type_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EXPath_Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EXPath_Type_Err(NativeUInt Ident, int AHelpContext)/* overload */ : EXPath_Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EXPath_Type_Err(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EXPath_Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EXPath_Type_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EXPath_Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EXPath_Type_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EXPath_Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EXPath_Type_Err() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM TXmlErrorType : unsigned char { ET_NONE, ET_DOCTYPE_NOT_FOUND, ET_DOUBLE_ATTLISTDECL, ET_DOUBLE_ATTDEF, ET_DOUBLE_ENTITY_DECL, ET_DOUBLE_PARAMETER_ENTITY_DECL, ET_FRAGMENT_IDENTIFIER_IN_SYSTEM_IDENTIFIER, ET_SYSTEM_IDENTIFIER_IS_NOT_URI_REFERENCE, ET_UNPARSED_ENTITY_REFERENCED_IN_ENTITY_DECLARATION, ET_XML_SPACE_ATTRIBUTE_ERRONEOUS_VALUE_DECLARED, ET_XML_SPACE_ATTRIBUTE_ERRONEOUS_VALUE_SPECIFIED, ET_XML_SPACE_ATTRIBUTE_NOT_ENUMERATED_TYPE, ET_ATTRIBUTE_DEFAULT_TYPE_MISMATCH, ET_ATTRIBUTE_TYPE_MISMATCH, ET_DUPLICATE_ELEMENT_TYPE_DECL, ET_DUPLICATE_ENUMERATION_TOKEN, ET_DUPLICATE_ID_ON_ELEMENT_TYPE, ET_DUPLICATE_ID_VALUE, ET_DUPLICATE_NAME_IN_MIXED_CONTENT, ET_DUPLICATE_NOTATION_DECL, ET_DUPLICATE_NOTATION_ON_ELEMENT_TYPE, 
	ET_DUPLICATE_NOTATION_TOKEN, ET_DUPLICATE_TOKENS, ET_ELEMENT_CONTENT_MODEL_MISMATCH_WITH_CDATA_SECTION_WHERE_ELEMENT_ONLY, ET_ELEMENT_CONTENT_MODEL_MISMATCH_WITH_CHILD_ELEMENT_TYPE, ET_ELEMENT_CONTENT_MODEL_MISMATCH_WITH_ELEMENT_WHERE_PCDATA_ONLY, ET_ELEMENT_CONTENT_MODEL_MISMATCH_WITH_PCDATA_WHERE_ELEMENT_ONLY, ET_ELEMENT_DECLARED_EMPTY_HAS_CONTENT, ET_ENTITY_REFERENCED_BEFORE_DECLARED_VC, ET_FIXED_ATTRIBUTE_MISMATCH, ET_ID_NEITHER_IMPLIED_NOR_REQUIRED, ET_NONDETERMINISTIC_ELEMENT_CONTENT_MODEL, ET_NOTATION_ON_EMPTY_ELEMENT, ET_PE_NOT_PROPERLY_NESTED_WITH_CONDITIONAL_SECTION, ET_PE_NOT_PROPERLY_NESTED_WITH_DECL, ET_PE_NOT_PROPERLY_NESTED_WITH_PARENTHESIZED_GROUP, ET_PREDEFINED_ENTITY_INCORRECTLY_REDECLARED, ET_REQUIRED_ATTRIBUTE_NOT_SPECIFIED, 
	ET_TARGET_ID_VALUE_NOT_FOUND, ET_UNDEFINED_ATTRIBUTE, ET_UNDEFINED_ELEMENT_TYPE, ET_UNDEFINED_ENTITY_VC, ET_UNDEFINED_NOTATION, ET_UNDEFINED_PARAMETER_ENTITY, ET_UNDEFINED_TARGET_UNPARSED_ENTITY, ET_UNNORMALIZED_EXT_ATTR_IN_STANDALONE_DOC, ET_UNRESOLVABLE_EXTERNAL_SUBSET, ET_UNSPECIFIED_EXT_ATTR_IN_STANDALONE_DOC, ET_WHITESPACE_IN_EXT_ELEMENT_CONTENT_IN_STANDALONE_DOC, ET_WRONG_ROOT_ELEMENT_TYPE, ET_ATTRIBUTE_VALUE_REFERS_TO_EXTERNAL_ENTITY, ET_BYTE_ORDER_MARK_ENCODING_MISMATCH, ET_CDATA_START_EXPECTED, ET_COMMENT_START_EXPECTED, ET_DOCTYPE_START_EXPECTED, ET_DOUBLE_ATTRIBUTE_NAME, ET_DOUBLE_EQUALITY_SIGN, ET_DOUBLE_HYPHEN_IN_COMMENT, ET_DOUBLE_ROOT_ELEMENT, ET_ENTITY_REFERENCED_BEFORE_DECLARED_WFC, ET_EXT_DECL_ENTITY_REFERENCED_IN_STANDALONE_DOC, 
	ET_HYPHEN_AT_COMMENT_END, ET_INVALID_ATTRIBUTE_NAME, ET_INVALID_ATTRIBUTE_VALUE, ET_INVALID_CDATA_SECTION, ET_INVALID_CHARACTER, ET_INVALID_CHAR_REF, ET_INVALID_COMMENT, ET_INVALID_ELEMENT_NAME, ET_INVALID_ENCODING_NAME, ET_INVALID_ENTITY_NAME, ET_INVALID_PARAMETER_ENTITY_NAME, ET_INVALID_PROCESSING_INSTRUCTION, ET_INVALID_PUBID_LITERAL, ET_INVALID_SYSTEM_LITERAL, ET_INVALID_TEXT_DECL, ET_INVALID_VERSION_NUMBER, ET_INVALID_XML_DECL, ET_LEFT_SQUARE_BRACKET_EXPECTED, ET_LT_IN_ATTRIBUTE_VALUE, ET_MISSING_ELEMENT_NAME, ET_MISSING_END_TAG, ET_MISSING_ENTITY_NAME, ET_MISSING_EQUALITY_SIGN, ET_MISSING_QUOTATION_MARK, ET_MISSING_START_TAG, ET_MISSING_WHITE_SPACE, ET_NOT_IN_ROOT_ELEMENT, ET_NO_PROPER_MARKUP_REFERENCED, ET_PE_BETWEEN_DECLARATIONS, 
	ET_PUBLIC_KEYWORD_EXPECTED, ET_QUOTATION_MARK_EXPECTED, ET_RECURSIVE_REFERENCE, ET_REFERS_TO_UNPARSED_ENTITY, ET_RIGHT_SQUARE_BRACKET_EXPECTED, ET_ROOT_ELEMENT_NOT_FOUND, ET_SYSTEM_KEYWORD_EXPECTED, ET_UNCLOSED_CDATA_SECTION, ET_UNCLOSED_CHAR_REF, ET_UNCLOSED_COMMENT, ET_UNCLOSED_DOCTYPE, ET_UNCLOSED_ELEMENT, ET_UNCLOSED_ENTITY_REF, ET_UNCLOSED_PROCESSING_INSTRUCTION, ET_UNDEFINED_ENTITY_WFC, ET_WRONG_ORDER, ET_ATTLIST_DECL_START_EXPECTED, ET_CONDITIONAL_SECTION_NOT_ALLOWED, ET_DOUBLE_DOCTYPE, ET_ELEMENT_DECL_START_EXPECTED, ET_ENTITY_DECL_START_EXPECTED, ET_INVALID_ATTLIST_DECL_NAME, ET_INVALID_ATTRIBUTE_DECL, ET_INVALID_ATTRIBUTE_NAME_IN_ATTRIBUTE_DECL, ET_INVALID_CONDITIONAL_SECTION, ET_INVALID_CONTENT_MODEL_TOKEN_IN_ELEMENT_DECL, ET_INVALID_ELEMENT_DECL, 
	ET_INVALID_ELEMENT_NAME_IN_ATTRIBUTE_DECL, ET_INVALID_ELEMENT_NAME_IN_ELEMENT_DECL, ET_INVALID_ENTITY_DECL, ET_INVALID_ENTITY_NAME_IN_ENTITY_DECL, ET_INVALID_ENTITY_NAME_IN_PARAMETER_ENTITY_DECL, ET_INVALID_ENTITY_VALUE_IN_ENTITY_DECL, ET_INVALID_ENTITY_VALUE_IN_PARAMETER_ENTITY_DECL, ET_INVALID_ENUMERATION_TOKEN_IN_ATTRIBUTE_DECL, ET_INVALID_MARKUP_DECL, ET_INVALID_NOTATION_DECL, ET_INVALID_NOTATION_NAME_IN_ENTITY_DECL, ET_INVALID_NOTATION_NAME_IN_NOTATION_DECL, ET_INVALID_NOTATION_TOKEN_IN_ATTRIBUTE_DECL, ET_INVALID_PARAMETER_ENTITY_DECL, ET_INVALID_ROOT_ELEMENT_NAME_IN_DOCTYPE_DECL, ET_KEYWORD_ANY_NOT_ALLOWED, ET_KEYWORD_EMPTY_NOT_ALLOWED, ET_KEYWORD_PCDATA_NOT_ALLOWED, ET_MALFORMED_CONTENT_MODEL_IN_ELEMENT_DECL, ET_MISSING_ENTITY_VALUE_IN_ENTITY_DECL, 
	ET_MISSING_ENTITY_VALUE_IN_PARAMETER_ENTITY_DECL, ET_NOTATION_DECL_START_EXPECTED, ET_PARAMETER_ENTITY_REF_NOT_ALLOWED, ET_UNCLOSED_ATTLIST_DECL, ET_UNCLOSED_CONDITIONAL_SECTION, ET_UNCLOSED_ELEMENT_DECL, ET_UNCLOSED_ENTITY_DECL, ET_UNCLOSED_NOTATION_DECL, ET_UNCLOSED_PARAMETER_ENTITY_REF, ET_UNKNOWN_DECL_TYPE, ET_WHITESPACE_EXPECTED, ET_INVALID_NAMESPACE_URI, ET_INVALID_PREFIX, ET_INVALID_QUALIFIED_NAME, ET_NAMESPACE_URI_NOT_FOUND, ET_WRONG_PREFIX_MAPPING_NESTING, ET_ENCODING_NOT_SUPPORTED, ET_EXT_ENTITY_RESOURCE_NOT_FOUND, ET_EXT_PARAMETER_ENTITY_RESOURCE_NOT_FOUND, ET_INVALID_CHARACTER_IN_EXT_ENTITY, ET_XML_VERSION_NOT_SUPPORTED };

typedef System::Set<TXmlErrorType, TXmlErrorType::ET_NONE, TXmlErrorType::ET_XML_VERSION_NOT_SUPPORTED> TXmlErrorTypes;

enum DECLSPEC_DENUM TDomTrinarean : unsigned char { T_UNKNOWN, T_TRUE, T_FALSE };

enum DECLSPEC_DENUM TDomNodeType : unsigned char { ntUnknown, ntElement_Node, ntAttribute_Node, ntText_Node, ntCDATA_Section_Node, ntEntity_Reference_Node, ntProcessing_Instruction_Node, ntComment_Node, ntDocument_Node, ntDocument_Fragment_Node, ntDocument_Type_Decl_Node, ntXPath_Namespace_Node };

typedef System::Set<TDomNodeType, TDomNodeType::ntUnknown, TDomNodeType::ntXPath_Namespace_Node> TDomWhatToShow;

enum DECLSPEC_DENUM TDomXPathResultType : unsigned char { XPATH_BOOLEAN_TYPE, XPATH_NODE_SET_TYPE, XPATH_NUMBER_TYPE, XPATH_STRING_TYPE };

typedef System::Set<TDomXPathResultType, TDomXPathResultType::XPATH_BOOLEAN_TYPE, TDomXPathResultType::XPATH_STRING_TYPE> TDomXPathResultTypes;

enum DECLSPEC_DENUM TXmlDataType : unsigned char { AS_STRING_DATATYPE, AS_NOTATION_DATATYPE, AS_ID_DATATYPE, AS_IDREF_DATATYPE, AS_IDREFS_DATATYPE, AS_ENTITY_DATATYPE, AS_ENTITIES_DATATYPE, AS_NMTOKEN_DATATYPE, AS_NMTOKENS_DATATYPE, AS_BOOLEAN_DATATYPE, AS_FLOAT_DATATYPE, AS_DOUBLE_DATATYPE, AS_DECIMAL_DATATYPE, AS_HEXBINARY_DATATYPE, AS_BASE64BINARY_DATATYPE, AS_ANYURI_DATATYPE, AS_QNAME_DATATYPE, AS_DURATION_DATATYPE, AS_DATETIME_DATATYPE, AS_DATE_DATATYPE, AS_TIME_DATATYPE, AS_GYEARMONTH_DATATYPE, AS_GYEAR_DATATYPE, AS_GMONTHDAY_DATATYPE, AS_GDAY_DATATYPE, AS_GMONTH_DATATYPE, AS_INTEGER_DATATYPE, AS_NAME_DATATYPE, AS_NCNAME_DATATYPE, AS_NORMALIZEDSTRING_DATATYPE, AS_TOKEN_DATATYPE, AS_LANGUAGE_DATATYPE, AS_NONPOSITIVEINTEGER_DATATYPE, 
	AS_NEGATIVEINTEGER_DATATYPE, AS_LONG_DATATYPE, AS_INT_DATATYPE, AS_SHORT_DATATYPE, AS_BYTE_DATATYPE, AS_NONNEGATIVEINTEGER_DATATYPE, AS_UNSIGNEDLONG_DATATYPE, AS_UNSIGNEDINT_DATATYPE, AS_UNSIGNEDSHORT_DATATYPE, AS_UNSIGNEDBYTE_DATATYPE, AS_POSITIVEINTEGER_DATATYPE, AS_ANYSIMPLETYPE_DATATYPE, AS_ANYTYPE_DATATYPE };

enum DECLSPEC_DENUM TDomAttrValueConstraint : unsigned char { AVC_DEFAULT, AVC_FIXED, AVC_IMPLIED, AVC_REQUIRED };

enum DECLSPEC_DENUM TDtdContentModelType : unsigned char { DTD_CHOICE_CM, DTD_ELEMENT_CM, DTD_SEQUENCE_CM };

enum DECLSPEC_DENUM TDtdContentType : unsigned char { DTD_ANY_CONTENTTYPE, DTD_EMPTY_CONTENTTYPE, DTD_ELEMENT_CONTENTTYPE, DTD_MIXED_CONTENTTYPE, DTD_STRICT_MIXED_CONTENTTYPE };

enum DECLSPEC_DENUM TDtdEntityType : unsigned char { DTD_INTERNAL_ENTITY, DTD_EXTERNAL_ENTITY, DTD_PREDEFINED_ENTITY };

enum DECLSPEC_DENUM TDtdOrigin : unsigned char { DTD_INTERNALLY_DECLARED, DTD_EXTERNALLY_DECLARED, DTD_PREDEFINED };

enum DECLSPEC_DENUM TDtdFrequency : unsigned char { DTD_REQUIRED_FRQ, DTD_OPTIONAL_FRQ, DTD_ONE_OR_MORE_FRQ, DTD_ZERO_OR_MORE_FRQ };

enum DECLSPEC_DENUM TDtdObjectType : unsigned char { DTD_UNDEFINED, DTD_ATTLIST_DECLARATION, DTD_ATTRIBUTE_DECLARATION, DTD_CONTENT_MODEL, DTD_ELEMENT_DECLARATION, DTD_ENTITY_DECLARATION, DTD_NOTATION_DECLARATION };

typedef System::Set<TDtdObjectType, TDtdObjectType::DTD_UNDEFINED, TDtdObjectType::DTD_NOTATION_DECLARATION> TDtdObjectTypeSet;

enum DECLSPEC_DENUM TDomPieceType : unsigned char { xmlProcessingInstruction, xmlComment, xmlCDATA, xmlPCDATA, xmlDoctype, xmlStartTag, xmlEndTag, xmlEmptyElementTag, xmlCharRef, xmlEntityRef, xmlAttribute, xmlParameterEntityRef, xmlEntityDecl, xmlElementDecl, xmlAttributeDecl, xmlNotationDecl, xmlCondSection, xmlParameterEntityDecl, xmlXmlDeclaration, xmlTextDeclaration, xmlUnknown };

enum DECLSPEC_DENUM Xml_Internal_Adomcore_4_3__12 : unsigned char { Document_Position_Contained_By, Document_Position_Contains, Document_Position_Disconnected, Document_Position_Equivalent, Document_Position_Following, Document_Position_Preceding, Document_Position_Same_Node };

typedef System::Set<Xml_Internal_Adomcore_4_3__12, Xml_Internal_Adomcore_4_3__12::Document_Position_Contained_By, Xml_Internal_Adomcore_4_3__12::Document_Position_Same_Node> TDomDocumentPosition;

enum DECLSPEC_DENUM TDomEntityResolveOption : unsigned char { erReplace, erExpand };

enum DECLSPEC_DENUM TDomEntityType : unsigned char { etExternal_Entity, etInternal_Entity };

enum DECLSPEC_DENUM TDomFilterResult : unsigned char { filter_accept, filter_reject, filter_skip };

enum DECLSPEC_DENUM Xml_Internal_Adomcore_4_3__22 : unsigned char { fuSetLocalhost, fuPlainColon };

typedef System::Set<Xml_Internal_Adomcore_4_3__22, Xml_Internal_Adomcore_4_3__22::fuSetLocalhost, Xml_Internal_Adomcore_4_3__22::fuPlainColon> TDomFilenameToUriOptions;

enum DECLSPEC_DENUM TDomNodeEvent : unsigned char { neClearing, neRemoving };

enum DECLSPEC_DENUM TDomPosition : unsigned char { posBefore, posAfter };

enum DECLSPEC_DENUM TDomStandalone : unsigned char { STANDALONE_YES, STANDALONE_NO, STANDALONE_UNSPECIFIED };

enum DECLSPEC_DENUM TDomOperationType : unsigned char { OT_NODE_ADOPTED, OT_NODE_CLONED, OT_NODE_DESTROYED, OT_NODE_IMPORTED, OT_NODE_RENAMED };

enum DECLSPEC_DENUM TDomAttrChange : unsigned char { AC_ADDITION, AC_MODIFICATION, AC_REMOVAL };

enum DECLSPEC_DENUM TDomXmlnsDeclType : unsigned char { NSDT_DEFAULT, NSDT_PREFIXED, NSDT_NONE };

enum DECLSPEC_DENUM TDomPreparationStatus : unsigned char { PS_UNPREPARED, PS_INCOMPLETE, PS_INCOMPLETE_STANDALONE, PS_INCOMPLETE_NOT_STANDALONE, PS_INCOMPLETE_ABORTED, PS_INT_SUBSET_COMPLETED, PS_COMPLETED, PS_INEXISTANT };

enum DECLSPEC_DENUM TDomDocTypeDeclTreatment : unsigned char { dtIgnore, dtCheckWellformedness, dtCheckValidity };

typedef void __fastcall (__closure *TDomUserDataEvent)(const TDomOperationType Operation, const System::WideString Key, System::TObject* const Data, TDomNode* const Src, TDomNode* const Dst);

typedef void __fastcall (__closure *TDomAttrModifiedEvent)(System::TObject* Sender, TDomNode* ModifiedNode, TDomAttrChange AttrChange, TDomAttr* RelatedAttr);

typedef void __fastcall (__closure *TDomNotifyNodeEvent)(System::TObject* Sender, TDomNode* Node);

typedef void __fastcall (__closure *TDomNotifyDtdObjectEvent)(System::TObject* Sender, TDtdObject* DtdObject);

typedef void __fastcall (__closure *TDomLocationEvent)(System::TObject* Sender, const _di_IDomLocator Locator);

typedef void __fastcall (__closure *TDomResolveResourceEvent)(System::TObject* Sender, const System::WideString ResourceType, const System::WideString NamespaceURI, System::WideString &PublicId, System::WideString &SystemId, System::Classes::TStream* &Stream, bool &CertifiedText);

typedef void __fastcall (__closure *TDomResolveEntityProc)(const TDtdOrigin Origin, const System::WideString BaseURI, const System::WideString PubId, const System::WideString SysId, /* out */ System::WideString &ReplacementText, /* out */ TXmlErrorType &Error);

typedef void __fastcall (__closure *TDomResolveEntityEvent)(System::TObject* Sender, const System::WideString EntityName, System::WideString &EntityValue, System::WideString &PubId, System::WideString &SysId, TXmlErrorType &Error);

typedef void __fastcall (__closure *TDomSerializationEvent)(TXmlStreamBuilder* Sender, TDomPieceType PieceType, const _di_IDomLocator Locator);

typedef void __fastcall (__closure *TDomWideStringLocationEvent)(System::TObject* Sender, const System::WideString S, const _di_IDomLocator Locator);

typedef void __fastcall (__closure *TDomErrorEvent)(System::TObject* Sender, TDomError* Error, bool &Go);

typedef void __fastcall (__closure *TDomRequestXPathFunctionResultEvent)(const System::WideString NamespaceURI, const System::WideString LocalName, TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments, TDomXPathCustomResult* &Value);

typedef void __fastcall (__closure *TDomRequestXPathVariableEvent)(TXPathExpression* const Sender, const System::WideString NamespaceURI, const System::WideString LocalName, TDomXPathCustomResult* &Value);

typedef void __fastcall (__closure *TDomXPathLookupNamespaceURIEvent)(TXPathExpression* const Sender, const System::WideString APrefix, System::WideString &ANamespaceURI);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TUtilsNoRefCount : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	HRESULT __stdcall QueryInterface(const GUID IID, /* out */ void *Obj);
	int __stdcall _AddRef();
	int __stdcall _Release();
public:
	/* TObject.Create */ inline __fastcall TUtilsNoRefCount() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TUtilsNoRefCount() { }
	
private:
	void *__IInterface;	// System::IInterface 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {00000000-0000-0000-C000-000000000046}
	operator System::_di_IInterface()
	{
		System::_di_IInterface intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::IInterface*(void) { return (System::IInterface*)&__IInterface; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomBaseComponent : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
protected:
	System::WideString __fastcall GetADOMVersion();
	
public:
	__property System::WideString ADOMVersion = {read=GetADOMVersion};
public:
	/* TComponent.Create */ inline __fastcall virtual TDomBaseComponent(System::Classes::TComponent* AOwner) : System::Classes::TComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TDomBaseComponent() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomImplementation : public TDomBaseComponent
{
	typedef TDomBaseComponent inherited;
	
private:
	System::Word FErrorReportLevel;
	TCustomResourceResolver* FResourceResolver;
	TDomAttrModifiedEvent FOnAttrModified;
	TDomNotifyNodeEvent FOnCharacterDataModified;
	TDomErrorEvent FOnError;
	TDomNotifyNodeEvent FOnNodeClearing;
	TDomNotifyNodeEvent FOnNodeInserted;
	TDomNotifyNodeEvent FOnNodeRemoving;
	TDomRequestXPathFunctionResultEvent FOnRequestXPathFunctionResult;
	TDomRequestXPathVariableEvent FOnRequestXPathVariable;
	void __fastcall Attach(TDomCustomDocument* ADocument);
	void __fastcall DestroyOwnedDocuments();
	void __fastcall Detach(TDomCustomDocument* ADocument);
	bool __fastcall GetErrorEventsDisabled();
	
protected:
	TDomNodeList* FDocuments;
	System::Generics::Collections::TList__1<Xml::Internal::Treeutils::TCustomOwnedNode*>* FOwnedDocumentsList;
	virtual void __fastcall DoAttrModified(TDomNode* const ModifiedNode, const TDomAttrChange AttrChange, TDomAttr* const RelatedAttr);
	virtual void __fastcall DoCharacterDataModified(TDomNode* ModifiedNode);
	virtual void __fastcall DoError(System::TObject* Sender, TDomError* Error, bool &Go);
	virtual void __fastcall DoNodeClearing(TDomNode* Node);
	virtual void __fastcall DoNodeInserted(TDomNode* Node);
	virtual void __fastcall DoNodeRemoving(TDomNode* Node);
	virtual void __fastcall DoRequestXPathFunctionResult(const System::WideString NamespaceURI, const System::WideString LocalName, TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments, TDomXPathCustomResult* &Value);
	virtual void __fastcall DoRequestXPathVariable(TXPathExpression* const XPathExpression, const System::WideString NamespaceURI, const System::WideString LocalName, TDomXPathCustomResult* &Value);
	virtual TDomNodeList* __fastcall GetDocuments();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall SetResourceResolver(TCustomResourceResolver* const AResourceResolver);
	
public:
	__fastcall virtual TDomImplementation(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDomImplementation();
	virtual void __fastcall Clear();
	virtual void __fastcall DisableErrorEvents();
	virtual void __fastcall EnableErrorEvents();
	virtual bool __fastcall HandleError(System::TObject* const Sender, TDomError* const Error);
	virtual System::Classes::TStream* __fastcall ResolveResourceAsStream(const System::WideString ABaseURI, System::WideString &PublicId, System::WideString &SystemId);
	virtual void __fastcall ResolveResourceAsWideString(const System::WideString ABaseURI, System::WideString &PublicId, System::WideString &SystemId, /* out */ System::WideString &S, /* out */ TXmlErrorType &Error);
	__property TDomNodeList* Documents = {read=GetDocuments};
	__property bool ErrorEventsDisabled = {read=GetErrorEventsDisabled, nodefault};
	__property TDomRequestXPathFunctionResultEvent OnRequestXPathFunctionResult = {read=FOnRequestXPathFunctionResult, write=FOnRequestXPathFunctionResult};
	
__published:
	__property TCustomResourceResolver* ResourceResolver = {read=FResourceResolver, write=SetResourceResolver};
	__property TDomAttrModifiedEvent OnAttrModified = {read=FOnAttrModified, write=FOnAttrModified};
	__property TDomNotifyNodeEvent OnCharacterDataModified = {read=FOnCharacterDataModified, write=FOnCharacterDataModified};
	__property TDomErrorEvent OnError = {read=FOnError, write=FOnError};
	__property TDomNotifyNodeEvent OnNodeClearing = {read=FOnNodeClearing, write=FOnNodeClearing};
	__property TDomNotifyNodeEvent OnNodeInserted = {read=FOnNodeInserted, write=FOnNodeInserted};
	__property TDomNotifyNodeEvent OnNodeRemoving = {read=FOnNodeRemoving, write=FOnNodeRemoving};
	__property TDomRequestXPathVariableEvent OnRequestXPathVariable = {read=FOnRequestXPathVariable, write=FOnRequestXPathVariable};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomNodeFilter : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual TDomFilterResult __fastcall AcceptNode(TDomNode* const N) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TDomNodeFilter() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDomNodeFilter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomTreeWalker : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TDomNode* FCurrentNode;
	bool FExpandEntityReferences;
	TDomNodeFilter* FFilter;
	TDomNode* FRoot;
	TDomWhatToShow FWhatToShow;
	
protected:
	virtual TDomNode* __fastcall FindFirstChild(TDomNode* const OldNode);
	virtual TDomNode* __fastcall FindLastChild(TDomNode* const OldNode);
	virtual TDomNode* __fastcall FindNextNode(TDomNode* OldNode);
	virtual TDomNode* __fastcall FindNextSibling(TDomNode* const OldNode);
	virtual TDomNode* __fastcall FindParentNode(TDomNode* const OldNode);
	virtual TDomNode* __fastcall FindPreviousNode(TDomNode* const OldNode);
	virtual TDomNode* __fastcall FindPreviousSibling(TDomNode* const OldNode);
	virtual void __fastcall SetCurrentNode(TDomNode* const Node);
	virtual void __fastcall SetExpandEntityReferences(const bool Value);
	virtual void __fastcall SetFilter(TDomNodeFilter* const Value);
	virtual void __fastcall SetRoot(TDomNode* const Node);
	virtual void __fastcall SetWhatToShow(const TDomWhatToShow Value);
	
public:
	__fastcall virtual TDomTreeWalker(TDomNode* const Root, const TDomWhatToShow WhatToShow, TDomNodeFilter* const NodeFilter, const bool EntityReferenceExpansion);
	virtual TDomNode* __fastcall ParentNode();
	virtual TDomNode* __fastcall FirstChild();
	virtual TDomNode* __fastcall LastChild();
	virtual TDomNode* __fastcall PreviousSibling();
	virtual TDomNode* __fastcall NextSibling();
	virtual TDomNode* __fastcall NextNode();
	virtual TDomNode* __fastcall PreviousNode();
	__property TDomNode* CurrentNode = {read=FCurrentNode, write=SetCurrentNode};
	__property bool ExpandEntityReferences = {read=FExpandEntityReferences, nodefault};
	__property TDomNodeFilter* Filter = {read=FFilter};
	__property TDomNode* Root = {read=FRoot};
	__property TDomWhatToShow WhatToShow = {read=FWhatToShow, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDomTreeWalker() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomNodeIterator : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TDomNode* FRoot;
	TDomNode* FReferenceNode;
	TDomPosition FPosition;
	TDomWhatToShow FWhatToShow;
	bool FExpandEntityReferences;
	TDomNodeFilter* FFilter;
	bool FInvalid;
	
protected:
	virtual void __fastcall HandleNodeEvent(TDomNode* const Node, const TDomNodeEvent EventType);
	virtual TDomNode* __fastcall FindNextNode(TDomNode* OldNode);
	virtual TDomNode* __fastcall FindPreviousNode(TDomNode* const OldNode);
	
public:
	__fastcall virtual TDomNodeIterator(TDomNode* const Root, const TDomWhatToShow WhatToShow, TDomNodeFilter* const NodeFilter, const bool EntityReferenceExpansion);
	virtual void __fastcall Detach();
	virtual TDomNode* __fastcall NextNode();
	virtual TDomNode* __fastcall PreviousNode();
	__property bool ExpandEntityReferences = {read=FExpandEntityReferences, nodefault};
	__property TDomNodeFilter* Filter = {read=FFilter};
	__property TDomNode* Root = {read=FRoot};
	__property TDomWhatToShow WhatToShow = {read=FWhatToShow, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDomNodeIterator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomNodeList : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Generics::Collections::TList__1<Xml::Internal::Treeutils::TCustomOwnedNode*>* FNodeList;
	
protected:
	virtual int __fastcall GetLength();
	virtual int __fastcall IndexOf(TDomNode* const Node);
	
public:
	__fastcall TDomNodeList(System::Generics::Collections::TList__1<Xml::Internal::Treeutils::TCustomOwnedNode*>* const NodeList);
	virtual TDomNode* __fastcall Item(const int Index);
	__property int Length = {read=GetLength, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDomNodeList() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomElementsNodeList : public TDomNodeList
{
	typedef TDomNodeList inherited;
	
private:
	System::WideString FQueryName;
	TDomNode* FStartElement;
	
protected:
	virtual int __fastcall GetLength();
	
public:
	virtual int __fastcall IndexOf(TDomNode* const Node);
	virtual TDomNode* __fastcall Item(const int Index);
	__fastcall virtual TDomElementsNodeList(const System::WideString QueryName, TDomNode* const StartElement);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDomElementsNodeList() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomElementsNodeListNS : public TDomNodeList
{
	typedef TDomNodeList inherited;
	
private:
	System::WideString FQueryNamespaceURI;
	System::WideString FQueryLocalName;
	TDomNode* FStartElement;
	
protected:
	virtual int __fastcall GetLength();
	
public:
	virtual int __fastcall IndexOf(TDomNode* const Node);
	virtual TDomNode* __fastcall Item(const int Index);
	__fastcall virtual TDomElementsNodeListNS(const System::WideString QueryNamespaceURI, const System::WideString QueryLocalName, TDomNode* const StartElement);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDomElementsNodeListNS() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomCustomNode : public Xml::Internal::Treeutils::TCustomOwnedNode
{
	typedef Xml::Internal::Treeutils::TCustomOwnedNode inherited;
	
protected:
	virtual System::WideString __fastcall GetNodeName() = 0 ;
	virtual void __fastcall RaiseException(const System::Sysutils::ExceptClass E);
	
public:
	__property System::WideString NodeName = {read=GetNodeName};
public:
	/* TCustomOwnedNode.Create */ inline __fastcall TDomCustomNode(Xml::Internal::Treeutils::TCustomOwnedObject* const AOwner) : Xml::Internal::Treeutils::TCustomOwnedNode(AOwner) { }
	/* TCustomOwnedNode.Destroy */ inline __fastcall virtual ~TDomCustomNode() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomNamedNodeMap : public TDomNodeList
{
	typedef TDomNodeList inherited;
	
private:
	TDomWhatToShow FAllowedNodeTypes;
	bool FDefaultNamespaceAware;
	TDomNode* FOwnerNode;
	
protected:
	void __fastcall CheckAllowedNodeType(TDomNode* const Node);
	void __fastcall CheckHasNode(TDomNode* const Node);
	void __fastcall CheckNamespaceAware();
	void __fastcall CheckNotInUse(TDomNode* const Node);
	void __fastcall CheckNotNamespaceAware();
	void __fastcall CheckNotReadOnly();
	void __fastcall CheckSameRootDocument(TDomNode* const Node);
	bool __fastcall GetNamespaceAware();
	bool __fastcall GetReadOnly();
	virtual void __fastcall InternalAdd(TDomNode* const Node);
	virtual void __fastcall InternalRemove(TDomNode* const Node);
	virtual TDomNode* __fastcall RemoveItem(TDomNode* const Arg);
	
public:
	__fastcall virtual TDomNamedNodeMap(TDomNode* const AOwner, System::Generics::Collections::TList__1<Xml::Internal::Treeutils::TCustomOwnedNode*>* const NodeList, const TDomWhatToShow AllowedNTs, const bool DefaultNamespaceAware);
	virtual TDomNode* __fastcall GetNamedItem(const System::WideString Name);
	virtual TDomNode* __fastcall GetNamedItemNS(const System::WideString NamespaceURI, const System::WideString LocalName);
	virtual TDomNode* __fastcall RemoveNamedItem(const System::WideString Name);
	virtual TDomNode* __fastcall RemoveNamedItemNS(const System::WideString NamespaceURI, const System::WideString LocalName);
	virtual TDomNode* __fastcall SetNamedItem(TDomNode* const Arg);
	virtual TDomNode* __fastcall SetNamedItemNS(TDomNode* const Arg);
	__property bool NamespaceAware = {read=GetNamespaceAware, nodefault};
	__property TDomNode* OwnerNode = {read=FOwnerNode};
	__property bool readOnly = {read=GetReadOnly, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDomNamedNodeMap() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomNode : public TDomCustomNode
{
	typedef TDomCustomNode inherited;
	
private:
	bool FIsNamespaceNode;
	TDomNodeList* FNodeList;
	System::Classes::TStringList* FNodeValues;
	System::WideString FNodeValue;
	TDomCustomDocument* FOwnerDocument;
	Xml::Internal::Widestringutils::TUtilsWideStringList* FUserData;
	System::Generics::Collections::TList__1<TDomUserDataEvent>* FUserDataHandlers;
	void __fastcall MakeChildrenReadOnly();
	TDomNode* __fastcall PreviousNode();
	bool __fastcall HasEntRef(const System::WideString EntName);
	
protected:
	System::Set<TDomNodeType, TDomNodeType::ntUnknown, TDomNodeType::ntXPath_Namespace_Node> FAllowedChildTypes;
	virtual void __fastcall CheckTypeAllowed(TDomNode* const Node);
	virtual void __fastcall DoAfterAddition(Xml::Internal::Treeutils::TCustomOwnedNode* const Node);
	virtual void __fastcall DoBeforeClear();
	virtual void __fastcall DoBeforeRemoval(Xml::Internal::Treeutils::TCustomOwnedNode* const Node);
	virtual int __fastcall GetAbsoluteIndex();
	virtual TDomNamedNodeMap* __fastcall GetAttributes();
	virtual System::WideString __fastcall GetBaseUri();
	virtual TDomNodeList* __fastcall GetChildNodes();
	virtual TDomCustomDocument* __fastcall GetDocument();
	virtual System::WideString __fastcall GetExpandedName();
	HIDESBASE virtual TDomNode* __fastcall GetFirstChild();
	virtual System::WideString __fastcall GetLanguage();
	HIDESBASE virtual TDomNode* __fastcall GetLastChild();
	virtual int __fastcall GetLevel();
	virtual System::WideString __fastcall GetLocalName();
	virtual System::WideString __fastcall GetNamespaceURI();
	HIDESBASE virtual TDomNode* __fastcall GetNextSibling();
	virtual System::WideString __fastcall GetNodeName();
	virtual System::WideString __fastcall GetNodeValue();
	virtual TDomNodeType __fastcall GetNodeType();
	virtual TDomNode* __fastcall GetParentNode();
	HIDESBASE virtual TDomNode* __fastcall GetPreviousSibling();
	virtual System::WideString __fastcall GetPrefix();
	virtual TDomCustomDocument* __fastcall GetRootDocument();
	virtual System::WideString __fastcall GetTextContent();
	virtual System::WideString __fastcall GetXPathStringValue();
	virtual void __fastcall SetNodeValue(const System::WideString Value);
	virtual void __fastcall SetPrefix(const System::WideString Value);
	void __fastcall AddNodeValue(const System::WideString Value);
	
public:
	__fastcall TDomNode(Xml::Internal::Treeutils::TCustomOwnedObject* const AOwner);
	__fastcall virtual ~TDomNode();
	virtual TDomNode* __fastcall AppendChild(TDomNode* const NewChild);
	virtual void __fastcall Clear();
	virtual TDomNode* __fastcall CloneNode(const bool Deep);
	virtual TDomDocumentPosition __fastcall CompareDocumentPosition(TDomNode* const Other);
	virtual bool __fastcall EvaluateToBoolean(const System::WideString Expression);
	virtual double __fastcall EvaluateToNumber(const System::WideString Expression);
	virtual TDomNode* __fastcall EvaluateToNode(const System::WideString Expression);
	virtual System::WideString __fastcall EvaluateToWideString(const System::WideString Expression);
	virtual TDomElement* __fastcall FindFirstChildElement();
	virtual TDomElement* __fastcall FindLastChildElement();
	virtual TDomElement* __fastcall FindNextSiblingElement();
	virtual TDomElement* __fastcall FindParentElement();
	virtual TDomElement* __fastcall FindPreviousSiblingElement();
	virtual TDomElement* __fastcall GetFirstChildElement(const System::WideString Name);
	virtual TDomElement* __fastcall GetFirstChildElementNS(const System::WideString NamespaceURI, const System::WideString LocalName);
	virtual TDomElement* __fastcall GetLastChildElement(const System::WideString Name);
	virtual TDomElement* __fastcall GetLastChildElementNS(const System::WideString NamespaceURI, const System::WideString LocalName);
	virtual TDomElement* __fastcall GetNextSiblingElement(const System::WideString Name);
	virtual TDomElement* __fastcall GetNextSiblingElementNS(const System::WideString NamespaceURI, const System::WideString LocalName);
	virtual TDomElement* __fastcall GetParentElement(const System::WideString Name);
	virtual TDomElement* __fastcall GetParentElementNS(const System::WideString NamespaceURI, const System::WideString LocalName);
	virtual TDomElement* __fastcall GetPreviousSiblingElement(const System::WideString Name);
	virtual TDomElement* __fastcall GetPreviousSiblingElementNS(const System::WideString NamespaceURI, const System::WideString LocalName);
	virtual System::TObject* __fastcall GetUserData(const System::WideString Key);
	HIDESBASE virtual bool __fastcall HasAsAncestor(TDomNode* const Node);
	virtual bool __fastcall HasAttributes();
	virtual bool __fastcall HasChildNodes();
	HIDESBASE virtual TDomNode* __fastcall InsertBefore(TDomNode* const NewChild, TDomNode* const RefChild);
	virtual System::WideString __fastcall LookupNamespaceURI(const System::WideString APrefix);
	virtual bool __fastcall HasNamespaceURI(const System::WideString APrefix);
	virtual void __fastcall Normalize();
	virtual TDomNode* __fastcall RemoveChild(TDomNode* const OldChild);
	virtual TDomNode* __fastcall ReplaceChild(TDomNode* const NewChild, TDomNode* const OldChild);
	virtual System::TObject* __fastcall SetUserData(const System::WideString Key, System::TObject* const Data, const TDomUserDataEvent Handler);
	__property int AbsoluteIndex = {read=GetAbsoluteIndex, nodefault};
	__property TDomNamedNodeMap* Attributes = {read=GetAttributes};
	__property System::WideString BaseUri = {read=GetBaseUri};
	__property TDomNodeList* ChildNodes = {read=GetChildNodes};
	__property System::WideString ExpandedName = {read=GetExpandedName};
	__property TDomNode* FirstChild = {read=GetFirstChild};
	__property bool IsNamespaceNode = {read=FIsNamespaceNode, nodefault};
	__property bool IsReadonly = {read=GetReadOnly, nodefault};
	__property System::WideString Language = {read=GetLanguage};
	__property TDomNode* LastChild = {read=GetLastChild};
	__property int Level = {read=GetLevel, nodefault};
	__property System::WideString LocalName = {read=GetLocalName};
	__property System::WideString NamespaceURI = {read=GetNamespaceURI};
	__property TDomNode* NextSibling = {read=GetNextSibling};
	__property TDomNodeType NodeType = {read=GetNodeType, nodefault};
	__property System::WideString NodeValue = {read=GetNodeValue, write=SetNodeValue};
	__property TDomCustomDocument* OwnerDocument = {read=GetDocument};
	__property TDomNode* ParentNode = {read=GetParentNode};
	__property TDomNode* PreviousSibling = {read=GetPreviousSibling};
	__property System::WideString Prefix = {read=GetPrefix, write=SetPrefix};
	__property TDomCustomDocument* RootDocument = {read=GetRootDocument};
	__property System::WideString TextContent = {read=GetTextContent};
	__property System::WideString XPathStringValue = {read=GetXPathStringValue};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomCharacterData : public TDomNode
{
	typedef TDomNode inherited;
	
private:
	virtual System::WideString __fastcall GetData();
	virtual void __fastcall SetData(const System::WideString Value);
	virtual int __fastcall GetLength();
	
protected:
	virtual void __fastcall DoCharacterDataModified();
	
public:
	__fastcall TDomCharacterData(TDomCustomDocument* const AOwner);
	virtual System::WideString __fastcall SubstringData(const int Offset, const int Count);
	virtual void __fastcall AppendData(const System::WideString Arg);
	virtual void __fastcall InsertData(const int Offset, const System::WideString Arg);
	virtual void __fastcall DeleteData(const int Offset, const int Count);
	virtual void __fastcall ReplaceData(const int Offset, const int Count, const System::WideString Arg);
	__property System::WideString Data = {read=GetData, write=SetData};
	__property int Length = {read=GetLength, nodefault};
public:
	/* TDomNode.Destroy */ inline __fastcall virtual ~TDomCharacterData() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomAttr : public TDomNode
{
	typedef TDomNode inherited;
	
private:
	TDomXmlnsDeclType FIsXmlnsDecl;
	System::WideString FLocalName;
	System::WideString FNamespaceURI;
	System::WideString FNodeName;
	TDomNamedNodeMap* FOwnerMap;
	System::WideString FPrefix;
	TXmlDataType __fastcall GetDataType();
	
protected:
	bool FSpecified;
	virtual void __fastcall DoAttrModified(const TDomAttrChange AttrChange);
	virtual System::WideString __fastcall GetExpandedName();
	virtual TDomXmlnsDeclType __fastcall GetIsXmlnsDecl();
	virtual System::WideString __fastcall GetLocalName();
	virtual System::WideString __fastcall GetName();
	virtual System::WideString __fastcall GetNamespaceURI();
	virtual TDomNode* __fastcall GetNextSibling();
	virtual System::WideString __fastcall GetNodeName();
	virtual TDomNodeType __fastcall GetNodeType();
	virtual TDomElement* __fastcall GetOwnerElement();
	virtual System::WideString __fastcall GetPrefix();
	virtual TDomNode* __fastcall GetPreviousSibling();
	virtual bool __fastcall GetSpecified();
	virtual System::WideString __fastcall GetValue();
	virtual void __fastcall SetNodeValue(const System::WideString Value);
	virtual void __fastcall SetPrefix(const System::WideString Value);
	
public:
	__fastcall TDomAttr(TDomDocument* const AOwner, const System::WideString Name, const bool Spcfd);
	__fastcall TDomAttr(TDomDocumentNS* const AOwner, const System::WideString NamespaceURI, const System::WideString QualifiedName, const bool Spcfd);
	__fastcall virtual ~TDomAttr();
	virtual System::WideString __fastcall LookupNamespaceURI(const System::WideString APrefix);
	__property TXmlDataType DataType = {read=GetDataType, nodefault};
	__property TDomXmlnsDeclType IsXmlnsDecl = {read=GetIsXmlnsDecl, nodefault};
	__property System::WideString Name = {read=GetName};
	__property TDomElement* OwnerElement = {read=GetOwnerElement};
	__property bool Specified = {read=GetSpecified, nodefault};
	__property System::WideString Value = {read=GetValue};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomElement : public TDomNode
{
	typedef TDomNode inherited;
	
private:
	TDomNamedNodeMap* FAttributeList;
	System::Generics::Collections::TList__1<Xml::Internal::Treeutils::TCustomOwnedNode*>* FAttributeListing;
	System::Generics::Collections::TList__1<TDomNodeList*>* FCreatedElementsNodeListNSs;
	System::Generics::Collections::TList__1<TDomNodeList*>* FCreatedElementsNodeLists;
	System::WideString FLocalName;
	System::WideString FNamespaceURI;
	System::WideString FNodeName;
	System::WideString FPrefix;
	
protected:
	virtual void __fastcall DoAttrModified(TDomNode* const originalTarget, const TDomAttrChange AttrChange, TDomAttr* const RelatedAttr);
	virtual void __fastcall DoBeforeClear();
	virtual System::WideString __fastcall GetExpandedName();
	virtual System::WideString __fastcall GetLocalName();
	virtual System::WideString __fastcall GetNamespaceURI();
	virtual System::WideString __fastcall GetNodeName();
	virtual TDomNodeType __fastcall GetNodeType();
	virtual System::WideString __fastcall GetPrefix();
	virtual void __fastcall SetNodeValue(const System::WideString Value);
	virtual void __fastcall SetPrefix(const System::WideString Value);
	
public:
	__fastcall TDomElement(TDomDocument* const AOwner, const System::WideString TagName);
	__fastcall TDomElement(TDomDocumentNS* const AOwner, const System::WideString NamespaceURI, const System::WideString QualifiedName);
	__fastcall virtual ~TDomElement();
	virtual System::WideString __fastcall GetAttributeLiteralValue(const System::WideString Name);
	virtual TDomAttr* __fastcall GetAttributeNode(const System::WideString Name);
	virtual TDomAttr* __fastcall GetAttributeNodeNS(const System::WideString NamespaceURI, const System::WideString LocalName);
	virtual System::WideString __fastcall GetAttributeNormalizedValue(const System::WideString Name);
	virtual System::WideString __fastcall GetAttributeNSLiteralValue(const System::WideString NamespaceURI, const System::WideString LocalName);
	virtual System::WideString __fastcall GetAttributeNSNormalizedValue(const System::WideString NamespaceURI, const System::WideString LocalName);
	virtual TDomNamedNodeMap* __fastcall GetAttributes();
	virtual TDomNodeList* __fastcall GetElementsByTagName(const System::WideString Name);
	virtual TDomNodeList* __fastcall GetElementsByTagNameNS(const System::WideString NamespaceURI, const System::WideString LocalName);
	virtual System::WideString __fastcall GetTagName();
	virtual bool __fastcall HasAttribute(const System::WideString Name);
	virtual bool __fastcall HasAttributeNS(const System::WideString NamespaceURI, const System::WideString LocalName);
	virtual System::WideString __fastcall LookupNamespaceURI(const System::WideString APrefix);
	virtual bool __fastcall HasNamespaceURI(const System::WideString APrefix);
	virtual void __fastcall Normalize();
	virtual TDomAttr* __fastcall RemoveAttribute(const System::WideString Name);
	virtual TDomAttr* __fastcall RemoveAttributeNode(TDomAttr* const OldAttr);
	virtual TDomAttr* __fastcall RemoveAttributeNS(const System::WideString NamespaceURI, const System::WideString LocalName);
	virtual TDomAttr* __fastcall SetAttribute(const System::WideString Name, const System::WideString Value);
	virtual TDomAttr* __fastcall SetAttributeNode(TDomAttr* const NewAttr);
	virtual TDomAttr* __fastcall SetAttributeNodeNS(TDomAttr* const NewAttr);
	virtual TDomAttr* __fastcall SetAttributeNS(const System::WideString NamespaceURI, const System::WideString QualifiedName, const System::WideString Value);
	__property System::WideString TagName = {read=GetTagName};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomText : public TDomCharacterData
{
	typedef TDomCharacterData inherited;
	
private:
	bool FCharRefGenerated;
	
protected:
	virtual bool __fastcall GetIsElementContentWhitespace();
	virtual System::WideString __fastcall GetNodeName();
	virtual TDomNodeType __fastcall GetNodeType();
	
public:
	__fastcall TDomText(TDomCustomDocument* const AOwner);
	virtual TDomText* __fastcall SplitText(const int Offset);
	__property bool CharRefGenerated = {read=FCharRefGenerated, write=FCharRefGenerated, default=0};
	__property bool IsElementContentWhitespace = {read=GetIsElementContentWhitespace, nodefault};
public:
	/* TDomNode.Destroy */ inline __fastcall virtual ~TDomText() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomComment : public TDomCharacterData
{
	typedef TDomCharacterData inherited;
	
protected:
	virtual System::WideString __fastcall GetNodeName();
	virtual TDomNodeType __fastcall GetNodeType();
	
public:
	__fastcall TDomComment(TDomCustomDocument* const AOwner);
public:
	/* TDomNode.Destroy */ inline __fastcall virtual ~TDomComment() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomProcessingInstruction : public TDomNode
{
	typedef TDomNode inherited;
	
private:
	System::WideString FTarget;
	
protected:
	virtual void __fastcall DoCharacterDataModified();
	virtual System::WideString __fastcall GetData();
	virtual System::WideString __fastcall GetExpandedName();
	virtual System::WideString __fastcall GetNodeName();
	virtual TDomNodeType __fastcall GetNodeType();
	virtual void __fastcall SetData(const System::WideString Value);
	
public:
	__fastcall TDomProcessingInstruction(TDomCustomDocument* const AOwner, const System::WideString Targ);
	__property System::WideString Target = {read=FTarget};
	__property System::WideString Data = {read=GetData, write=SetData};
public:
	/* TDomNode.Destroy */ inline __fastcall virtual ~TDomProcessingInstruction() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomCDATASection : public TDomText
{
	typedef TDomText inherited;
	
protected:
	virtual System::WideString __fastcall GetNodeName();
	virtual TDomNodeType __fastcall GetNodeType();
	
public:
	__fastcall TDomCDATASection(TDomCustomDocument* const AOwner);
public:
	/* TDomNode.Destroy */ inline __fastcall virtual ~TDomCDATASection() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TDomDocumentTypeDecl : public TDomNode
{
	typedef TDomNode inherited;
	
private:
	System::WideString FInternalSubset;
	__int64 FIntSubsetStartColumn;
	__int64 FIntSubsetCharNumber;
	__int64 FIntSubsetByteNumber;
	__int64 FIntSubsetStartLine;
	System::WideString FNodeName;
	System::WideString FPublicId;
	System::WideString FSystemId;
	
protected:
	virtual System::WideString __fastcall GetInternalSubset();
	virtual System::WideString __fastcall GetName();
	virtual System::WideString __fastcall GetNodeName();
	virtual TDomNodeType __fastcall GetNodeType();
	virtual System::WideString __fastcall GetPublicId();
	virtual System::WideString __fastcall GetSystemId();
	virtual void __fastcall SetNodeValue(const System::WideString Value);
	
public:
	__fastcall TDomDocumentTypeDecl(TDomCustomDocument* const AOwner, const System::WideString DoctypeName, const System::WideString PubId, const System::WideString SysId, const System::WideString IntSubset);
	__property System::WideString InternalSubset = {read=GetInternalSubset};
	__property __int64 IntSubsetStartByteNumber = {read=FIntSubsetByteNumber, write=FIntSubsetByteNumber, default=0};
	__property __int64 IntSubsetStartCharNumber = {read=FIntSubsetCharNumber, write=FIntSubsetCharNumber, default=0};
	__property __int64 IntSubsetStartColumn = {read=FIntSubsetStartColumn, write=FIntSubsetStartColumn, default=0};
	__property __int64 IntSubsetStartLine = {read=FIntSubsetStartLine, write=FIntSubsetStartLine, default=1};
	__property System::WideString Name = {read=GetName};
	__property System::WideString PublicId = {read=GetPublicId};
	__property System::WideString SystemId = {read=GetSystemId};
public:
	/* TDomNode.Destroy */ inline __fastcall virtual ~TDomDocumentTypeDecl() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomEntityReference : public TDomNode
{
	typedef TDomNode inherited;
	
private:
	System::WideString FNodeName;
	
protected:
	virtual System::WideString __fastcall GetNodeName();
	virtual TDomNodeType __fastcall GetNodeType();
	virtual void __fastcall SetNodeValue(const System::WideString Value);
	
public:
	__fastcall TDomEntityReference(TDomCustomDocument* const AOwner, const System::WideString Name);
public:
	/* TDomNode.Destroy */ inline __fastcall virtual ~TDomEntityReference() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomDocumentFragment : public TDomNode
{
	typedef TDomNode inherited;
	
protected:
	virtual int __fastcall GetAbsoluteIndex();
	virtual int __fastcall GetLevel();
	virtual System::WideString __fastcall GetNodeName();
	virtual TDomNodeType __fastcall GetNodeType();
	virtual void __fastcall SetNodeValue(const System::WideString Value);
	
public:
	__fastcall virtual TDomDocumentFragment(TDomCustomDocument* const AOwner);
public:
	/* TDomNode.Destroy */ inline __fastcall virtual ~TDomDocumentFragment() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathNamespace : public TDomNode
{
	typedef TDomNode inherited;
	
private:
	System::WideString FNamespaceURI;
	TDomElement* FOwnerElement;
	System::WideString FPrefix;
	TDomXPathNodeSetResult* __fastcall GetOwnerSet();
	
protected:
	virtual TDomCustomDocument* __fastcall GetDocument();
	virtual System::WideString __fastcall GetExpandedName();
	virtual System::WideString __fastcall GetLocalName();
	virtual System::WideString __fastcall GetNamespaceURI();
	virtual System::WideString __fastcall GetNodeName();
	virtual TDomNodeType __fastcall GetNodeType();
	virtual System::WideString __fastcall GetNodeValue();
	virtual TDomElement* __fastcall GetOwnerElement();
	virtual System::WideString __fastcall GetPrefix();
	
public:
	__fastcall TDomXPathNamespace(TDomXPathNodeSetResult* const AOwnerSet, TDomElement* const AOwnerElement, const System::WideString ANamespaceUri, const System::WideString APrefix);
	__property TDomElement* OwnerElement = {read=GetOwnerElement};
	__property TDomXPathNodeSetResult* OwnerSet = {read=GetOwnerSet};
	virtual System::WideString __fastcall LookupNamespaceURI(const System::WideString APrefix);
public:
	/* TDomNode.Destroy */ inline __fastcall virtual ~TDomXPathNamespace() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomCustomDocument : public TDomNode
{
	typedef TDomNode inherited;
	
private:
	System::Generics::Collections::TList__1<TDomNodeIterator*>* FCreatedNodeIterators;
	System::Generics::Collections::TList__1<TDomTreeWalker*>* FCreatedTreeWalkers;
	TDomAbstractView* FDefaultView;
	System::WideString FDocumentUri;
	TDomImplementation* FDOMImpl;
	System::WideString FInputEncoding;
	bool FModified;
	System::WideString FSystemId;
	System::WideString FXmlEncoding;
	TDomStandalone FXmlStandalone;
	System::WideString FXmlVersion;
	TDomAttrModifiedEvent FOnAttrModified;
	TDomNotifyNodeEvent FOnCharacterDataModified;
	TDomNotifyNodeEvent FOnNodeClearing;
	TDomNotifyNodeEvent FOnNodeInserted;
	TDomNotifyNodeEvent FOnNodeRemoving;
	void __fastcall NotifyIterators(TDomNode* const Node, const TDomNodeEvent EventType);
	
protected:
	virtual void __fastcall CalculateNormalizedAttrValue(const System::WideString AttrLiteralValue, const TXmlDataType AttrDataType, /* out */ System::WideString &NormalizedValue, /* out */ TXmlErrorType &Error);
	virtual void __fastcall DoAttrModified(TDomNode* const SourceNode, const TDomAttrChange AttrChange, TDomAttr* const RelatedAttr);
	virtual void __fastcall DoBeforeClear();
	virtual void __fastcall DoCharacterDataModified(TDomNode* Node);
	virtual void __fastcall DoNodeClearing(TDomNode* Node);
	virtual void __fastcall DoNodeInserted(TDomNode* Node);
	virtual void __fastcall DoNodeRemoving(TDomNode* Node);
	virtual int __fastcall GetAbsoluteIndex();
	virtual TXmlDataType __fastcall GetAttrDataType(const System::WideString ElementName, const System::WideString AttrName);
	virtual System::WideString __fastcall GetBaseUri();
	virtual TDomDocumentTypeDecl* __fastcall GetDoctypeDecl();
	virtual TDomElement* __fastcall GetDocumentElement();
	virtual int __fastcall GetLevel();
	virtual System::WideString __fastcall GetNodeName();
	virtual TDomNodeType __fastcall GetNodeType();
	virtual TDomCustomDocument* __fastcall GetRootDocument();
	virtual TDomNode* __fastcall ImportNode2(TDomNode* const ImportedNode, const bool Deep);
	virtual void __fastcall SetNodeValue(const System::WideString Value);
	
public:
	__fastcall TDomCustomDocument(TDomImplementation* const AOwner);
	__fastcall virtual ~TDomCustomDocument();
	virtual TDomNode* __fastcall AppendChild(TDomNode* const NewChild);
	virtual void __fastcall ClearInvalidNodeIterators();
	virtual TDomNodeIterator* __fastcall CreateNodeIterator(TDomNode* const Root, TDomWhatToShow WhatToShow, TDomNodeFilter* NodeFilter, bool EntityReferenceExpansion);
	virtual TDomTreeWalker* __fastcall CreateTreeWalker(TDomNode* const Root, TDomWhatToShow WhatToShow, TDomNodeFilter* NodeFilter, bool EntityReferenceExpansion);
	virtual void __fastcall FreeTreeWalker(TDomTreeWalker* &TreeWalker);
	virtual TDomElement* __fastcall GetElementById(const System::WideString ElementId) = 0 ;
	virtual TDomNode* __fastcall ImportNode(TDomNode* const ImportedNode, const bool Deep);
	virtual TDomNode* __fastcall InsertBefore(TDomNode* const NewChild, TDomNode* const RefChild);
	virtual TDomNode* __fastcall ReplaceChild(TDomNode* const NewChild, TDomNode* const OldChild);
	__property TDomAbstractView* DefaultView = {read=FDefaultView};
	__property TDomDocumentTypeDecl* DoctypeDecl = {read=GetDoctypeDecl};
	__property TDomElement* DocumentElement = {read=GetDocumentElement};
	__property System::WideString DocumentUri = {read=FDocumentUri, write=FDocumentUri};
	__property TDomImplementation* DomImplementation = {read=FDOMImpl};
	__property System::WideString InputEncoding = {read=FInputEncoding, write=FInputEncoding};
	__property bool Modified = {read=FModified, write=FModified, nodefault};
	__property System::WideString XmlEncoding = {read=FXmlEncoding, write=FXmlEncoding};
	__property TDomStandalone XmlStandalone = {read=FXmlStandalone, write=FXmlStandalone, nodefault};
	__property System::WideString XmlVersion = {read=FXmlVersion, write=FXmlVersion};
	__property TDomAttrModifiedEvent OnAttrModified = {read=FOnAttrModified, write=FOnAttrModified};
	__property TDomNotifyNodeEvent OnCharacterDataModified = {read=FOnCharacterDataModified, write=FOnCharacterDataModified};
	__property TDomNotifyNodeEvent OnNodeClearing = {read=FOnNodeClearing, write=FOnNodeClearing};
	__property TDomNotifyNodeEvent OnNodeInserted = {read=FOnNodeInserted, write=FOnNodeInserted};
	__property TDomNotifyNodeEvent OnNodeRemoving = {read=FOnNodeRemoving, write=FOnNodeRemoving};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomDocument : public TDomCustomDocument
{
	typedef TDomCustomDocument inherited;
	
private:
	System::Generics::Collections::TList__1<TDomNodeList*>* FCreatedElementsNodeLists;
	TDtdValidationAgent* FValidationAgent;
	
protected:
	virtual void __fastcall CalculateNormalizedAttrValue(const System::WideString AttrLiteralValue, const TXmlDataType AttrDataType, /* out */ System::WideString &NormalizedValue, /* out */ TXmlErrorType &Error);
	virtual void __fastcall DoBeforeClear();
	virtual TXmlDataType __fastcall GetAttrDataType(const System::WideString ElementName, const System::WideString AttrName);
	virtual bool __fastcall GetIsElementContentWhitespace(TDomText* const TextNode);
	virtual TDomNode* __fastcall ImportNode2(TDomNode* const ImportedNode, const bool Deep);
	virtual bool __fastcall PrepareAttributes2(TDomNode* const Node);
	
public:
	__fastcall TDomDocument(TDomImplementation* const AOwner);
	__fastcall virtual ~TDomDocument();
	virtual TDomElement* __fastcall GetElementById(const System::WideString ElementId);
	virtual TDomNodeList* __fastcall GetElementsByTagName(const System::WideString TagName);
	virtual bool __fastcall PrepareAttributes();
	__property TDtdValidationAgent* ValidationAgent = {read=FValidationAgent};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomDocumentNS : public TDomCustomDocument
{
	typedef TDomCustomDocument inherited;
	
private:
	System::Generics::Collections::TList__1<TDomNodeList*>* FCreatedElementsNodeListNSs;
	Xml::Internal::Widestringutils::TUtilsWideStringList* FIDs;
	void __fastcall SetIDs(Xml::Internal::Widestringutils::TUtilsWideStringList* const Value);
	
protected:
	virtual void __fastcall DoBeforeClear();
	
public:
	__fastcall TDomDocumentNS(TDomImplementation* const AOwner);
	__fastcall virtual ~TDomDocumentNS();
	virtual TDomElement* __fastcall GetElementById(const System::WideString ElementId);
	virtual TDomNodeList* __fastcall GetElementsByTagNameNS(const System::WideString NamespaceURI, const System::WideString LocalName);
	__property Xml::Internal::Widestringutils::TUtilsWideStringList* IDs = {read=FIDs, write=SetIDs};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomDocumentXPath : public TDomDocumentNS
{
	typedef TDomDocumentNS inherited;
	
protected:
	virtual void __fastcall DoBeforeAttach(Xml::Internal::Treeutils::TCustomOwnedObject* const Obj);
public:
	/* TDomDocumentNS.Create */ inline __fastcall TDomDocumentXPath(TDomImplementation* const AOwner) : TDomDocumentNS(AOwner) { }
	/* TDomDocumentNS.Destroy */ inline __fastcall virtual ~TDomDocumentXPath() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM TDomSeverity : unsigned char { DOM_SEVERITY_WARNING, DOM_SEVERITY_ERROR, DOM_SEVERITY_FATAL_ERROR };

__interface IDomLocator  : public System::IInterface 
{
	virtual __int64 __fastcall GetEndByteNumber() = 0 ;
	virtual __int64 __fastcall GetEndCharNumber() = 0 ;
	virtual __int64 __fastcall GetEndColumnNumber() = 0 ;
	virtual __int64 __fastcall GetEndLineNumber() = 0 ;
	virtual __int64 __fastcall GetEndTabsInLine() = 0 ;
	virtual TDtdObject* __fastcall GetRelatedDtdObject() = 0 ;
	virtual TDomNode* __fastcall GetRelatedNode() = 0 ;
	virtual __int64 __fastcall GetStartByteNumber() = 0 ;
	virtual __int64 __fastcall GetStartCharNumber() = 0 ;
	virtual __int64 __fastcall GetStartColumnNumber() = 0 ;
	virtual __int64 __fastcall GetStartLineNumber() = 0 ;
	virtual __int64 __fastcall GetStartTabsInLine() = 0 ;
	virtual System::WideString __fastcall GetUri() = 0 ;
	__property __int64 EndByteNumber = {read=GetEndByteNumber};
	__property __int64 EndCharNumber = {read=GetEndCharNumber};
	__property __int64 EndColumnNumber = {read=GetEndColumnNumber};
	__property __int64 EndLineNumber = {read=GetEndLineNumber};
	__property __int64 EndTabsInLine = {read=GetEndTabsInLine};
	__property TDtdObject* RelatedDtdObject = {read=GetRelatedDtdObject};
	__property TDomNode* RelatedNode = {read=GetRelatedNode};
	__property __int64 StartByteNumber = {read=GetStartByteNumber};
	__property __int64 StartCharNumber = {read=GetStartCharNumber};
	__property __int64 StartColumnNumber = {read=GetStartColumnNumber};
	__property __int64 StartLineNumber = {read=GetStartLineNumber};
	__property __int64 StartTabsInLine = {read=GetStartTabsInLine};
	__property System::WideString Uri = {read=GetUri};
};

class PASCALIMPLEMENTATION TDomError : public TUtilsNoRefCount
{
	typedef TUtilsNoRefCount inherited;
	
private:
	System::WideString FClue;
	System::WideString FCode;
	__int64 FEndByteNumber;
	__int64 FEndCharNumber;
	__int64 FEndColumnNumber;
	__int64 FEndLineNumber;
	__int64 FEndTabsInLine;
	TDtdObject* FRelatedDtdObject;
	TXmlErrorType FRelatedException;
	TDomNode* FRelatedNode;
	__int64 FStartByteNumber;
	__int64 FStartCharNumber;
	__int64 FStartColumnNumber;
	__int64 FStartLineNumber;
	__int64 FStartTabsInLine;
	System::WideString FUri;
	
protected:
	virtual TDomSeverity __fastcall GetSeverity();
	virtual __int64 __fastcall GetEndByteNumber();
	virtual __int64 __fastcall GetEndCharNumber();
	virtual __int64 __fastcall GetEndColumnNumber();
	virtual __int64 __fastcall GetEndLineNumber();
	virtual __int64 __fastcall GetEndTabsInLine();
	virtual TDtdObject* __fastcall GetRelatedDtdObject();
	virtual TDomNode* __fastcall GetRelatedNode();
	virtual __int64 __fastcall GetStartByteNumber();
	virtual __int64 __fastcall GetStartCharNumber();
	virtual __int64 __fastcall GetStartColumnNumber();
	virtual __int64 __fastcall GetStartLineNumber();
	virtual __int64 __fastcall GetStartTabsInLine();
	virtual System::WideString __fastcall GetUri();
	
public:
	__fastcall TDomError(const TXmlErrorType ARelatedException, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode, const System::WideString ACode, const System::WideString AClue);
	__fastcall TDomError(const TXmlErrorType ARelatedException, const _di_IDomLocator ALocation, const System::WideString ACode, const System::WideString AClue);
	virtual TDomError* __fastcall CloneError();
	__property System::WideString Clue = {read=FClue};
	__property System::WideString Code = {read=FCode};
	__property TXmlErrorType RelatedException = {read=FRelatedException, nodefault};
	__property TDomSeverity Severity = {read=GetSeverity, nodefault};
	__property __int64 EndByteNumber = {read=GetEndByteNumber};
	__property __int64 EndCharNumber = {read=GetEndCharNumber};
	__property __int64 EndColumnNumber = {read=GetEndColumnNumber};
	__property __int64 EndLineNumber = {read=GetEndLineNumber};
	__property __int64 EndTabsInLine = {read=GetEndTabsInLine};
	__property TDtdObject* RelatedDtdObject = {read=GetRelatedDtdObject};
	__property TDomNode* RelatedNode = {read=GetRelatedNode};
	__property __int64 StartByteNumber = {read=GetStartByteNumber};
	__property __int64 StartCharNumber = {read=GetStartCharNumber};
	__property __int64 StartColumnNumber = {read=GetStartColumnNumber};
	__property __int64 StartLineNumber = {read=GetStartLineNumber};
	__property __int64 StartTabsInLine = {read=GetStartTabsInLine};
	__property System::WideString Uri = {read=GetUri};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDomError() { }
	
private:
	void *__IDomLocator;	// IDomLocator 
	
public:
	operator IDomLocator*(void) { return (IDomLocator*)&__IDomLocator; }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDtdObjectList : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Generics::Collections::TList__1<TDtdObject*>* FNodeList;
	
protected:
	void __fastcall Clear();
	virtual TDtdObject* __fastcall AppendNode(TDtdObject* const NewNode);
	virtual void __fastcall Delete(const int Index);
	virtual int __fastcall IndexOf(TDtdObject* const Node);
	virtual TDtdObject* __fastcall InsertBefore(TDtdObject* const NewNode, TDtdObject* const RefNode);
	virtual int __fastcall GetLength();
	virtual TDtdObject* __fastcall RemoveNode(TDtdObject* const OldNode);
	
public:
	__fastcall TDtdObjectList();
	__fastcall virtual ~TDtdObjectList();
	virtual TDtdObject* __fastcall Item(const int Index);
	__property int Length = {read=GetLength, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDtdNamedObjectMap : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	System::Generics::Collections::TList__1<TDtdObject*>* FObjectList;
	TDtdModel* FOwnerObject;
	virtual int __fastcall GetLength();
	virtual TDtdObject* __fastcall RemoveNamedItem(const System::WideString Name);
	virtual TDtdObject* __fastcall SetNamedItem(TDtdObject* const Arg);
	virtual void __fastcall Clear();
	
public:
	__fastcall TDtdNamedObjectMap(TDtdModel* const AOwner);
	__fastcall virtual ~TDtdNamedObjectMap();
	virtual TDtdObject* __fastcall GetNamedItem(const System::WideString Name);
	virtual TDtdObject* __fastcall Item(const int Index);
	__property int Length = {read=GetLength, nodefault};
	__property TDtdModel* OwnerModel = {read=FOwnerObject};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDtdValidationAgent : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TDtdModel* FDtdModel;
	Xml::Internal::Widestringutils::TUtilsWideStringList* FIDs;
	Xml::Internal::Widestringutils::TUtilsWideStringList* FIDREFs;
	TDomDocument* FOwnerDocument;
	bool FErrorReportingEnabled;
	void __fastcall AddDefaultAttr(TDomElement* const Elmt, const System::WideString AttrName, const System::WideString AttrValue);
	TDomImplementation* __fastcall GetDomImplementation();
	bool __fastcall IsUnparsedEntity(const System::WideString EntityName);
	void __fastcall NormalizeAttrValueStep1(const System::WideString S, const __int64 AttrDeclKey, /* out */ System::WideString &S_Normalized, /* out */ TXmlErrorType &Error);
	void __fastcall NormalizeValue(const System::WideString AttrLiteralValue, const TXmlDataType AttrDataType, const __int64 AttrDeclKey, /* out */ System::WideString &NormalizedValue, /* out */ TXmlErrorType &Error);
	TDomDocumentFragment* __fastcall ParseWideString(const System::WideString S)/* overload */;
	
protected:
	virtual bool __fastcall AddDefaultAttributes(TDomElement* const Elmt);
	virtual void __fastcall AddAndValidateDefaultAttributes(TDomElement* const Elmt, /* out */ bool &IsValid, /* out */ bool &AContinue);
	virtual void __fastcall Clear();
	bool __fastcall DocumentIsStandalone();
	virtual TXmlErrorType __fastcall ExpandEntityReference(TDomEntityReference* const EntRef);
	virtual TDtdAttributeDecl* __fastcall FindAttributeDecl(const System::WideString ElementName, const System::WideString AttributeName);
	virtual TDtdElementDecl* __fastcall FindElementDecl(const System::WideString Name);
	virtual TDtdEntityDecl* __fastcall FindEntityDecl(const System::WideString Name);
	virtual TXmlErrorType __fastcall FindEntityReplacementText(const System::WideString EntityName, /* out */ System::WideString &ReplText, /* out */ bool &IsExternalEntity, /* out */ __int64 &Key);
	virtual TDtdNotationDecl* __fastcall FindNotationDecl(const System::WideString Name);
	virtual TXmlDataType __fastcall GetAttrDataType(const System::WideString ElementName, const System::WideString AttrName);
	virtual TDtdContentType __fastcall GetElementContentType(const System::WideString ElementName);
	virtual void __fastcall NormalizeAttributeValue(const System::WideString AttrLiteralValue, const TXmlDataType AttrDataType, /* out */ System::WideString &NormalizedValue, /* out */ TXmlErrorType &Error);
	virtual void __fastcall NormalizeAttrDeclValue(TDtdAttributeDecl* const AttrDecl, /* out */ System::WideString &NormalizedValue, /* out */ TXmlErrorType &Error);
	virtual void __fastcall ResolveEntity(const TDtdOrigin Origin, const System::WideString BaseURI, const System::WideString PubId, const System::WideString SysId, /* out */ System::WideString &ReplacementText, /* out */ TXmlErrorType &Error);
	virtual bool __fastcall SendErrorNotification(const TXmlErrorType XmlErrorType, TDtdObject* const RelDtdObject, TDomNode* const RelNode);
	virtual void __fastcall SetErrorReportingEnabled(const bool Value);
	virtual void __fastcall ValidateAttr(TDomAttr* const Attr, const TDomEntityResolveOption Opt, /* out */ bool &IsValid, /* out */ bool &AContinue);
	virtual void __fastcall ValidateDTD(/* out */ bool &IsValid, /* out */ bool &AContinue);
	virtual void __fastcall ValidateElement(TDomElement* const Elmt, const TDomEntityResolveOption Opt, /* out */ bool &IsValid, /* out */ bool &AContinue);
	virtual void __fastcall ValidateEntityRef(TDomEntityReference* const EntRef, /* out */ bool &IsValid, /* out */ bool &AContinue);
	virtual void __fastcall ValidateNode(TDomNode* const Node, const TDomEntityResolveOption Opt, /* out */ bool &IsValid, /* out */ bool &AContinue);
	__property TDomImplementation* DomImplementation = {read=GetDomImplementation};
	__property Xml::Internal::Widestringutils::TUtilsWideStringList* IDs = {read=FIDs};
	
public:
	__fastcall TDtdValidationAgent(TDomDocument* const AOwner);
	__fastcall virtual ~TDtdValidationAgent();
	virtual void __fastcall BuildDtdModel(const bool ResolveExtEntities);
	virtual bool __fastcall ValidateDocument(const TDomEntityResolveOption Opt);
	__property TDtdModel* DtdModel = {read=FDtdModel};
	__property bool ErrorReportingEnabled = {read=FErrorReportingEnabled, write=SetErrorReportingEnabled, default=1};
	__property TDomDocument* OwnerDocument = {read=FOwnerDocument};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TDtdObject : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::WideString FName;
	TDtdObjectType FObjectType;
	TDtdModel* FOwnerModel;
	__int64 FKey;
	
protected:
	virtual System::WideString __fastcall GetName();
	
public:
	__fastcall TDtdObject(TDtdModel* const AOwner, const System::WideString AName);
	__property __int64 Key = {read=FKey};
	__property System::WideString Name = {read=GetName};
	__property TDtdObjectType ObjectType = {read=FObjectType, nodefault};
	__property TDtdModel* OwnerModel = {read=FOwnerModel};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDtdObject() { }
	
};


class PASCALIMPLEMENTATION TDtdContentModel : public TDtdObject
{
	typedef TDtdObject inherited;
	
protected:
	System::Set<TDtdContentModelType, TDtdContentModelType::DTD_CHOICE_CM, TDtdContentModelType::DTD_SEQUENCE_CM> FAllowedChildTypes;
	TDtdContentModelType FContentModelType;
	TDtdFrequency FFrequency;
	bool FInuse;
	TDtdElementDecl* FOwnerElementDecl;
	TDtdObjectList* FSubModels;
	virtual bool __fastcall ValidateChoiceNames(Xml::Internal::Widestringutils::TUtilsWideStringList* const Source, int &Index, TDtdFrequency Freq, /* out */ bool &IsNonDeterministic);
	virtual bool __fastcall ValidateElementNames(Xml::Internal::Widestringutils::TUtilsWideStringList* const Source, int &Index, TDtdFrequency Freq, /* out */ bool &IsNonDeterministic);
	virtual bool __fastcall ValidateNames2(Xml::Internal::Widestringutils::TUtilsWideStringList* const Source, int &Index, TDtdFrequency Freq, /* out */ bool &IsNonDeterministic);
	virtual bool __fastcall ValidateNames(Xml::Internal::Widestringutils::TUtilsWideStringList* const Source, int &Index, /* out */ bool &IsNonDeterministic);
	virtual bool __fastcall ValidateSequenceNames(Xml::Internal::Widestringutils::TUtilsWideStringList* const Source, int &Index, TDtdFrequency Freq, /* out */ bool &IsNonDeterministic);
	
public:
	__fastcall TDtdContentModel(TDtdElementDecl* const AOwnerElementDecl, const System::WideString AName, const TDtdContentModelType AContentModelType);
	__fastcall virtual ~TDtdContentModel();
	virtual TDtdContentModel* __fastcall AppendSubModel(TDtdContentModel* const NewCM);
	virtual TDtdContentModel* __fastcall InsertBeforeSubModel(TDtdContentModel* const NewCM, TDtdContentModel* const RefCM);
	virtual TDtdContentModel* __fastcall RemoveSubModel(TDtdContentModel* const OldCM);
	__property TDtdContentModelType ContentModelType = {read=FContentModelType, nodefault};
	__property TDtdFrequency Frequency = {read=FFrequency, write=FFrequency, default=0};
	__property TDtdObjectList* SubModels = {read=FSubModels};
	__property TDtdElementDecl* OwnerElementDecl = {read=FOwnerElementDecl};
};


class PASCALIMPLEMENTATION TDtdAttDeclCollection : public TDtdObject
{
	typedef TDtdObject inherited;
	
private:
	TDtdNamedObjectMap* FAttributeDeclarations;
	
public:
	__fastcall TDtdAttDeclCollection(TDtdModel* const AOwner, const System::WideString AName);
	__fastcall virtual ~TDtdAttDeclCollection();
	virtual void __fastcall Clear();
	virtual TDtdAttributeDecl* __fastcall FindAttributeDecl(const System::WideString Name);
	virtual bool __fastcall RemoveAttributeDecl(const System::WideString Name);
	virtual bool __fastcall SetAttributeDecl(const System::WideString AAttrName, const System::WideString AAttrValue, Xml::Internal::Widestringutils::TUtilsWideStringList* const AEnumeration, const TXmlDataType AAttrType, const TDomAttrValueConstraint AConstraintType, const TDtdOrigin AOrigin, /* out */ TDtdAttributeDecl* &AttributeDecl);
	__property TDtdNamedObjectMap* AttributeDecls = {read=FAttributeDeclarations};
};


class PASCALIMPLEMENTATION TDtdAttributeDecl : public TDtdObject
{
	typedef TDtdObject inherited;
	
private:
	TXmlDataType FAttrType;
	System::WideString FDefaultValue;
	TDomAttrValueConstraint FConstraintType;
	Xml::Internal::Widestringutils::TUtilsWideStringList* FEnumeration;
	TDtdOrigin FOrigin;
	TDtdAttDeclCollection* FOwnerCollection;
	
public:
	__fastcall TDtdAttributeDecl(TDtdAttDeclCollection* const AOwnerCollection, const System::WideString AAttrName, const System::WideString aDefaultValue, Xml::Internal::Widestringutils::TUtilsWideStringList* const AEnumeration, const TXmlDataType AAttrType, const TDomAttrValueConstraint AConstraintType, const TDtdOrigin AOrigin);
	__fastcall virtual ~TDtdAttributeDecl();
	__property TXmlDataType AttrType = {read=FAttrType, nodefault};
	__property TDomAttrValueConstraint ConstraintType = {read=FConstraintType, nodefault};
	__property System::WideString DefaultValue = {read=FDefaultValue};
	__property Xml::Internal::Widestringutils::TUtilsWideStringList* Enumeration = {read=FEnumeration};
	__property TDtdOrigin Origin = {read=FOrigin, nodefault};
	__property TDtdAttDeclCollection* OwnerCollection = {read=FOwnerCollection};
};


class PASCALIMPLEMENTATION TDtdElementDecl : public TDtdObject
{
	typedef TDtdObject inherited;
	
private:
	TDtdOrigin FOrigin;
	
protected:
	System::Set<TDtdContentModelType, TDtdContentModelType::DTD_CHOICE_CM, TDtdContentModelType::DTD_SEQUENCE_CM> FAllowedChildTypes;
	TDtdContentModel* FContentModel;
	TDtdContentType FContentType;
	TDtdObjectList* FCreatedContentModels;
	
public:
	__fastcall TDtdElementDecl(TDtdModel* const AOwner, const System::WideString AName, const TDtdContentType AContentType, const TDtdOrigin AOrigin);
	__fastcall virtual ~TDtdElementDecl();
	virtual void __fastcall Clear();
	virtual TDtdContentModel* __fastcall CreateContentModel(const System::WideString Name, const TDtdContentModelType ContentModelType);
	virtual void __fastcall FreeAndNilContentModel(TDtdContentModel* &CM);
	virtual TDtdContentModel* __fastcall ReplaceContentModel(TDtdContentModel* const NewContentModel);
	__property TDtdContentModel* ContentModel = {read=FContentModel};
	__property TDtdContentType ContentType = {read=FContentType, nodefault};
	__property TDtdObjectList* CreatedContentModels = {read=FCreatedContentModels};
	__property TDtdOrigin Origin = {read=FOrigin, nodefault};
};


class PASCALIMPLEMENTATION TDtdEntityDecl : public TDtdObject
{
	typedef TDtdObject inherited;
	
private:
	System::WideString FBaseUri;
	Xml::Internal::Widestringutils::TUtilsWideStringList* FEntityRefs;
	System::WideString FNotationName;
	TDtdOrigin FOrigin;
	System::WideString FPublicId;
	System::WideString FReplacementText;
	System::WideString FSystemId;
	bool FIsResolved;
	TDtdEntityType __fastcall GetEntityType();
	void __fastcall SetReplacementText(const System::WideString S);
	
protected:
	virtual bool __fastcall CheckNoRecursion_2(Xml::Internal::Widestringutils::TUtilsWideStringList* const AncestorEntities);
	virtual bool __fastcall GetIsParsedEntity();
	
public:
	__fastcall TDtdEntityDecl(TDtdModel* const AOwner, const System::WideString AName, const System::WideString AReplacementText, const System::WideString APublicId, const System::WideString ASystemId, const System::WideString ANotationName, const System::WideString ABaseUri, const TDtdOrigin AOrigin);
	__fastcall virtual ~TDtdEntityDecl();
	virtual bool __fastcall CheckNoRecursion();
	virtual TXmlErrorType __fastcall ResolveReplacementText(const TDomResolveEntityProc ResolveEntityProc);
	__property System::WideString BaseUri = {read=FBaseUri};
	__property Xml::Internal::Widestringutils::TUtilsWideStringList* EntityRefs = {read=FEntityRefs};
	__property TDtdEntityType EntityType = {read=GetEntityType, nodefault};
	__property bool IsParsedEntity = {read=GetIsParsedEntity, nodefault};
	__property System::WideString NotationName = {read=FNotationName};
	__property TDtdOrigin Origin = {read=FOrigin, nodefault};
	__property System::WideString PublicId = {read=FPublicId};
	__property System::WideString ReplacementText = {read=FReplacementText};
	__property System::WideString SystemId = {read=FSystemId};
	__property bool IsResolved = {read=FIsResolved, nodefault};
};


class PASCALIMPLEMENTATION TDtdNotationDecl : public TDtdObject
{
	typedef TDtdObject inherited;
	
private:
	TDtdOrigin FOrigin;
	System::WideString FPublicId;
	System::WideString FSystemId;
	
public:
	__fastcall TDtdNotationDecl(TDtdModel* const AOwner, const System::WideString AName, const System::WideString APublicId, const System::WideString ASystemId, const TDtdOrigin AOrigin);
	__property TDtdOrigin Origin = {read=FOrigin, nodefault};
	__property System::WideString PublicId = {read=FPublicId};
	__property System::WideString SystemId = {read=FSystemId};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDtdNotationDecl() { }
	
};


class PASCALIMPLEMENTATION TDtdModel : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::WideString FExtSubsetSysId;
	System::WideString FIntSubsetSysId;
	__int64 FLastKey;
	bool FPEsInIntSubset;
	TDomPreparationStatus FPreparationStatus;
	bool FSetDefaults;
	__int64 __fastcall GetNewKey();
	
protected:
	TDtdNamedObjectMap* FAttDeclCollections;
	TDtdNamedObjectMap* FElementDeclarations;
	TDtdNamedObjectMap* FEntityDeclarations;
	TDtdNamedObjectMap* FNotationDeclarations;
	virtual void __fastcall ClearMaps();
	void __fastcall SetDefaults();
	virtual void __fastcall SetPreparationStatus(const TDomPreparationStatus Value);
	
public:
	__fastcall TDtdModel();
	__fastcall virtual ~TDtdModel();
	virtual void __fastcall Clear();
	virtual TDtdAttDeclCollection* __fastcall FindAttDeclCollection(const System::WideString Name);
	virtual TDtdAttributeDecl* __fastcall FindAttributeDecl(const System::WideString ElementName, const System::WideString AttributeName);
	virtual TDtdElementDecl* __fastcall FindElementDecl(const System::WideString Name);
	virtual TDtdEntityDecl* __fastcall FindEntityDecl(const System::WideString Name);
	virtual TDtdNotationDecl* __fastcall FindNotationDecl(const System::WideString Name);
	virtual bool __fastcall RemoveAttributeDecl(const System::WideString ElementName, const System::WideString AttributeName);
	virtual bool __fastcall RemoveElementDecl(const System::WideString Name);
	virtual bool __fastcall RemoveEntityDecl(const System::WideString Name);
	virtual bool __fastcall RemoveNotationDecl(const System::WideString Name);
	virtual bool __fastcall SetAttributeDecl(const System::WideString ElementName, const System::WideString AttrName, const System::WideString AttrValue, Xml::Internal::Widestringutils::TUtilsWideStringList* const Enumeration, const TXmlDataType AttrType, const TDomAttrValueConstraint ConstraintType, const TDtdOrigin Origin, /* out */ TDtdAttributeDecl* &AttributeDecl);
	virtual bool __fastcall SetElementDecl(const System::WideString Name, const TDtdContentType ContentType, const TDtdOrigin Origin, /* out */ TDtdElementDecl* &ElementDecl);
	virtual bool __fastcall SetEntityDecl(const System::WideString Name, const System::WideString ReplacementText, const System::WideString PublicId, const System::WideString SystemId, const System::WideString NotationName, const System::WideString BaseUri, const TDtdOrigin Origin, /* out */ TDtdEntityDecl* &EntityDecl);
	virtual bool __fastcall SetNotationDecl(const System::WideString Name, const System::WideString PublicId, const System::WideString SystemId, const TDtdOrigin Origin, /* out */ TDtdNotationDecl* &NotationDecl);
	__property TDtdNamedObjectMap* AttDeclCollections = {read=FAttDeclCollections};
	__property TDtdNamedObjectMap* ElementDecls = {read=FElementDeclarations};
	__property TDtdNamedObjectMap* EntityDecls = {read=FEntityDeclarations};
	__property TDtdNamedObjectMap* NotationDecls = {read=FNotationDeclarations};
	__property System::WideString ExtSubsetSysId = {read=FExtSubsetSysId, write=FExtSubsetSysId};
	__property System::WideString IntSubsetSysId = {read=FIntSubsetSysId, write=FIntSubsetSysId};
	__property bool PEsInIntSubset = {read=FPEsInIntSubset, write=FPEsInIntSubset, default=0};
	__property TDomPreparationStatus PreparationStatus = {read=FPreparationStatus, write=SetPreparationStatus, default=0};
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomAbstractView : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	TDomCustomDocument* FDocument;
	
public:
	__property TDomCustomDocument* Document = {read=FDocument};
public:
	/* TObject.Create */ inline __fastcall TDomAbstractView() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDomAbstractView() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomStyleSheet : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	virtual System::WideString __fastcall GetStyleSheetType() = 0 ;
	virtual bool __fastcall GetDisabled() = 0 ;
	virtual void __fastcall SetDisabled(const bool Value) = 0 ;
	virtual TDomNode* __fastcall GetOwnerNode() = 0 ;
	virtual TDomStyleSheet* __fastcall GetParentStyleSheet() = 0 ;
	virtual System::WideString __fastcall GetHref() = 0 ;
	virtual System::WideString __fastcall GetTitle() = 0 ;
	virtual TDomMediaList* __fastcall GetMedia() = 0 ;
	
public:
	__property System::WideString StyleSheetType = {read=GetStyleSheetType};
	__property bool Disabled = {read=GetDisabled, write=SetDisabled, nodefault};
	__property TDomNode* OwnerNode = {read=GetOwnerNode};
	__property TDomStyleSheet* ParentStyleSheet = {read=GetParentStyleSheet};
	__property System::WideString Href = {read=GetHref};
	__property System::WideString Title = {read=GetTitle};
	__property TDomMediaList* Media = {read=GetMedia};
public:
	/* TObject.Create */ inline __fastcall TDomStyleSheet() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDomStyleSheet() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomMediaList : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	virtual System::WideString __fastcall GetCssText() = 0 ;
	virtual void __fastcall SetCssText(const System::WideString Value) = 0 ;
	virtual int __fastcall GetLength() = 0 ;
	
public:
	virtual TDomStyleSheet* __fastcall Item(const int Index) = 0 ;
	virtual void __fastcall Delete(const System::WideString OldMedium) = 0 ;
	virtual void __fastcall Append(const System::WideString NewMedium) = 0 ;
	__property int Length = {read=GetLength, nodefault};
	__property System::WideString CssText = {read=GetCssText, write=SetCssText};
public:
	/* TObject.Create */ inline __fastcall TDomMediaList() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDomMediaList() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomStyleSheetList : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	virtual int __fastcall GetLength() = 0 ;
	
public:
	virtual TDomStyleSheet* __fastcall Item(const int Index) = 0 ;
	__property int Length = {read=GetLength, nodefault};
public:
	/* TObject.Create */ inline __fastcall TDomStyleSheetList() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDomStyleSheetList() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomDocumentStyle : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	virtual TDomStyleSheetList* __fastcall GetStyleSheets() = 0 ;
	
public:
	__property TDomStyleSheetList* StyleSheets = {read=GetStyleSheets};
public:
	/* TObject.Create */ inline __fastcall TDomDocumentStyle() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDomDocumentStyle() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlSourceCode : public System::Classes::TList
{
	typedef System::Classes::TList inherited;
	
private:
	void __fastcall CalculatePieceOffset(const int StartItem);
	System::WideString __fastcall GetNameOfFirstTag();
	System::WideString __fastcall GetText();
	
public:
	HIDESBASE int __fastcall Add(TXmlSourceCodePiece* Item);
	virtual void __fastcall Clear();
	virtual void __fastcall ClearAndFree();
	HIDESBASE void __fastcall Delete(int Index);
	HIDESBASE void __fastcall Exchange(int Index1, int Index2);
	TXmlSourceCodePiece* __fastcall GetPieceAtPos(int Pos);
	HIDESBASE void __fastcall Insert(int Index, TXmlSourceCodePiece* Item);
	HIDESBASE void __fastcall Move(int CurIndex, int NewIndex);
	HIDESBASE void __fastcall Pack();
	HIDESBASE int __fastcall Remove(TXmlSourceCodePiece* Item);
	HIDESBASE void __fastcall Sort(System::Classes::TListSortCompare Compare);
	__property System::WideString NameOfFirstTag = {read=GetNameOfFirstTag};
	__property System::WideString Text = {read=GetText};
public:
	/* TList.Destroy */ inline __fastcall virtual ~TXmlSourceCode() { }
	
public:
	/* TObject.Create */ inline __fastcall TXmlSourceCode() : System::Classes::TList() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlSourceCodePiece : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TDomPieceType FPieceType;
	System::WideString FText;
	int FOffset;
	TXmlSourceCode* FOwner;
	
public:
	__fastcall virtual TXmlSourceCodePiece(const TDomPieceType pt);
	__property TDomPieceType PieceType = {read=FPieceType, nodefault};
	__property System::WideString Text = {read=FText, write=FText};
	__property int Offset = {read=FOffset, nodefault};
	__property TXmlSourceCode* OwnerSourceCode = {read=FOwner};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlSourceCodePiece() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCustomResourceResolver : public TDomBaseComponent
{
	typedef TDomBaseComponent inherited;
	
public:
	virtual System::Classes::TStream* __fastcall ResolveResource(const System::WideString ABaseURI, System::WideString &PublicId, System::WideString &SystemId) = 0 ;
public:
	/* TComponent.Create */ inline __fastcall virtual TCustomResourceResolver(System::Classes::TComponent* AOwner) : TDomBaseComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TCustomResourceResolver() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TStandardResourceResolver : public TCustomResourceResolver
{
	typedef TCustomResourceResolver inherited;
	
private:
	TDomResolveResourceEvent FOnResolveResource;
	
protected:
	virtual System::Classes::TStream* __fastcall AcquireStreamFromUri(const System::WideString Uri);
	
public:
	virtual System::Classes::TStream* __fastcall ResolveResource(const System::WideString ABaseURI, System::WideString &PublicId, System::WideString &SystemId);
	
__published:
	__property TDomResolveResourceEvent OnResolveResource = {read=FOnResolveResource, write=FOnResolveResource};
public:
	/* TComponent.Create */ inline __fastcall virtual TStandardResourceResolver(System::Classes::TComponent* AOwner) : TCustomResourceResolver(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TStandardResourceResolver() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM TDomXMLDeclType : unsigned char { DT_XML_DECLARATION, DT_TEXT_DECLARATION, DT_XML_OR_TEXT_DECLARATION, DT_UNSPECIFIED };

class PASCALIMPLEMENTATION TXmlSimpleInputSource : public Xml::Internal::Parserutilswin32::TUtilsUCS4Reader
{
	typedef Xml::Internal::Parserutilswin32::TUtilsUCS4Reader inherited;
	
private:
	System::WideString FPublicId;
	System::Classes::TStringStream* FStrStream;
	System::WideString FSystemId;
	Xml::Internal::Widestringutils::TUtilsWideStringStream* FWStrStream;
	
protected:
	virtual System::UnicodeString __fastcall GetInputEncoding();
	
public:
	__fastcall TXmlSimpleInputSource(System::Classes::TStream* const Stream, const System::WideString APublicId, const System::WideString ASystemId, const int ABufSize, const System::UnicodeString AEncoding, const __int64 InitialByteCount, const __int64 InitialCharCount, const __int64 InitialCharsInLine, const __int64 InitialTabsInLine, const __int64 InitialLine)/* overload */;
	__fastcall TXmlSimpleInputSource(const System::UnicodeString S, const System::WideString APublicId, const System::WideString ASystemId, const int ABufSize, const System::UnicodeString AEncoding, const __int64 InitialByteCount, const __int64 InitialCharCount, const __int64 InitialCharsInLine, const __int64 InitialTabsInLine, const __int64 InitialLine)/* overload */;
	__fastcall TXmlSimpleInputSource(const System::WideString S, const System::WideString APublicId, const System::WideString ASystemId, const int ABufSize, const __int64 InitialByteCount, const __int64 InitialCharCount, const __int64 InitialCharsInLine, const __int64 InitialTabsInLine, const __int64 InitialLine)/* overload */;
	__fastcall virtual ~TXmlSimpleInputSource();
	__property System::UnicodeString InputEncoding = {read=GetInputEncoding};
	__property System::WideString PublicId = {read=FPublicId};
	__property System::WideString SystemId = {read=FSystemId};
};


class PASCALIMPLEMENTATION TXmlInputSource : public TXmlSimpleInputSource
{
	typedef TXmlSimpleInputSource inherited;
	
private:
	TDomXMLDeclType FDeclType;
	bool FHasMalformedDecl;
	System::UnicodeString FXmlEncoding;
	TDomStandalone FXmlStandalone;
	System::UnicodeString FXmlVersion;
	void __fastcall CheckEncoding(const System::UnicodeString Encoding);
	bool __fastcall EvaluateXmlOrTextDecl(/* out */ TDomXMLDeclType &DeclType, /* out */ System::UnicodeString &Version, /* out */ System::UnicodeString &EncName, /* out */ TDomStandalone &Standalone);
	
public:
	__fastcall TXmlInputSource(System::Classes::TStream* const Stream, const System::WideString APublicId, const System::WideString ASystemId, const int ABufSize, const System::UnicodeString AEncoding, const bool InclDecl, const __int64 InitialByteCount, const __int64 InitialCharCount, const __int64 InitialCharsInLine, const __int64 InitialTabsInLine, const __int64 InitialLine)/* overload */;
	__fastcall TXmlInputSource(const System::UnicodeString S, const System::WideString APublicId, const System::WideString ASystemId, const int ABufSize, const System::UnicodeString AEncoding, const bool InclDecl, const __int64 InitialByteCount, const __int64 InitialCharCount, const __int64 InitialCharsInLine, const __int64 InitialTabsInLine, const __int64 InitialLine)/* overload */;
	__fastcall TXmlInputSource(const System::WideString S, const System::WideString APublicId, const System::WideString ASystemId, const int ABufSize, const bool InclDecl, const __int64 InitialByteCount, const __int64 InitialCharCount, const __int64 InitialCharsInLine, const __int64 InitialTabsInLine, const __int64 InitialLine)/* overload */;
	__property BufSize;
	__property TDomXMLDeclType DeclType = {read=FDeclType, nodefault};
	__property bool HasMalformedDecl = {read=FHasMalformedDecl, nodefault};
	__property System::UnicodeString XmlEncoding = {read=FXmlEncoding};
	__property TDomStandalone XmlStandalone = {read=FXmlStandalone, nodefault};
	__property System::UnicodeString XmlVersion = {read=FXmlVersion};
public:
	/* TXmlSimpleInputSource.Create */ inline __fastcall TXmlInputSource(System::Classes::TStream* const Stream, const System::WideString APublicId, const System::WideString ASystemId, const int ABufSize, const System::UnicodeString AEncoding, const __int64 InitialByteCount, const __int64 InitialCharCount, const __int64 InitialCharsInLine, const __int64 InitialTabsInLine, const __int64 InitialLine)/* overload */ : TXmlSimpleInputSource(Stream, APublicId, ASystemId, ABufSize, AEncoding, InitialByteCount, InitialCharCount, InitialCharsInLine, InitialTabsInLine, InitialLine) { }
	/* TXmlSimpleInputSource.Create */ inline __fastcall TXmlInputSource(const System::UnicodeString S, const System::WideString APublicId, const System::WideString ASystemId, const int ABufSize, const System::UnicodeString AEncoding, const __int64 InitialByteCount, const __int64 InitialCharCount, const __int64 InitialCharsInLine, const __int64 InitialTabsInLine, const __int64 InitialLine)/* overload */ : TXmlSimpleInputSource(S, APublicId, ASystemId, ABufSize, AEncoding, InitialByteCount, InitialCharCount, InitialCharsInLine, InitialTabsInLine, InitialLine) { }
	/* TXmlSimpleInputSource.Create */ inline __fastcall TXmlInputSource(const System::WideString S, const System::WideString APublicId, const System::WideString ASystemId, const int ABufSize, const __int64 InitialByteCount, const __int64 InitialCharCount, const __int64 InitialCharsInLine, const __int64 InitialTabsInLine, const __int64 InitialLine)/* overload */ : TXmlSimpleInputSource(S, APublicId, ASystemId, ABufSize, InitialByteCount, InitialCharCount, InitialCharsInLine, InitialTabsInLine, InitialLine) { }
	/* TXmlSimpleInputSource.Destroy */ inline __fastcall virtual ~TXmlInputSource() { }
	
};


class PASCALIMPLEMENTATION TXmlCustomTokenizer : public TUtilsNoRefCount
{
	typedef TUtilsNoRefCount inherited;
	
protected:
	System::WideString FClue;
	TXmlErrorType FErrorType;
	TXmlSimpleInputSource* FInputSource;
	Xml::Internal::Parserutilswin32::TUtilsUCS4CharData FTokenEnd;
	Xml::Internal::Parserutilswin32::TUtilsUCS4CharData FTokenStart;
	Xml::Internal::Widestringutils::TUtilsCustomWideStr* FTokenValue;
	virtual System::WideString __fastcall GetTokenValue();
	virtual __int64 __fastcall GetEndByteNumber();
	virtual __int64 __fastcall GetEndCharNumber();
	virtual __int64 __fastcall GetEndColumnNumber();
	virtual __int64 __fastcall GetEndLineNumber();
	virtual __int64 __fastcall GetEndTabsInLine();
	virtual TDtdObject* __fastcall GetRelatedDtdObject();
	virtual TDomNode* __fastcall GetRelatedNode();
	virtual __int64 __fastcall GetStartByteNumber();
	virtual __int64 __fastcall GetStartCharNumber();
	virtual __int64 __fastcall GetStartColumnNumber();
	virtual __int64 __fastcall GetStartLineNumber();
	virtual __int64 __fastcall GetStartTabsInLine();
	virtual System::WideString __fastcall GetUri();
	
public:
	__fastcall TXmlCustomTokenizer(TXmlSimpleInputSource* const InputSource);
	__fastcall virtual ~TXmlCustomTokenizer();
	virtual void __fastcall Next() = 0 ;
	__property System::WideString Clue = {read=FClue};
	__property TXmlErrorType ErrorType = {read=FErrorType, nodefault};
	__property System::WideString TokenValue = {read=GetTokenValue};
private:
	void *__IDomLocator;	// IDomLocator 
	
public:
	operator IDomLocator*(void) { return (IDomLocator*)&__IDomLocator; }
	
};


enum DECLSPEC_DENUM TXmlDocTokenType : unsigned char { XML_CDATA_TOKEN, XML_CHAR_REF_DEC_TOKEN, XML_CHAR_REF_HEX_TOKEN, XML_COMMENT_TOKEN, XML_DOCTYPE_TOKEN, XML_EMPTY_ELEMENT_TAG_TOKEN, XML_END_OF_SOURCE_TOKEN, XML_END_TAG_TOKEN, XML_ENTITY_REF_TOKEN, XML_PCDATA_TOKEN, XML_PI_TOKEN, XML_START_OF_SOURCE_TOKEN, XML_START_TAG_TOKEN };

class PASCALIMPLEMENTATION TXmlDocTokenizer : public TXmlCustomTokenizer
{
	typedef TXmlCustomTokenizer inherited;
	
protected:
	TXmlDocTokenType FTokenType;
	
public:
	__fastcall TXmlDocTokenizer(TXmlSimpleInputSource* const InputSource);
	virtual void __fastcall Next();
	__property TXmlDocTokenType TokenType = {read=FTokenType, nodefault};
public:
	/* TXmlCustomTokenizer.Destroy */ inline __fastcall virtual ~TXmlDocTokenizer() { }
	
};


enum DECLSPEC_DENUM TXmlDtdDetailTokenType : unsigned char { DTD_DETAIL_ATTLIST_DECL_START_TOKEN, DTD_DETAIL_COMMENT_TOKEN, DTD_DETAIL_COND_SECT_END_TOKEN, DTD_DETAIL_COND_SECT_OPENER_TOKEN, DTD_DETAIL_COND_SECT_START_TOKEN, DTD_DETAIL_DECL_END_TOKEN, DTD_DETAIL_ELEMENT_DECL_START_TOKEN, DTD_DETAIL_END_OF_SOURCE_TOKEN, DTD_DETAIL_ENTITY_DECL_START_TOKEN, DTD_DETAIL_INVALID_MARKUP_TOKEN, DTD_DETAIL_KEYWORD_TOKEN, DTD_DETAIL_NOTATION_DECL_START_TOKEN, DTD_DETAIL_OPERATOR_TOKEN, DTD_DETAIL_PARAMETER_ENTITY_REF_TOKEN, DTD_DETAIL_PI_CONTENT_TOKEN, DTD_DETAIL_PI_TARGET_TOKEN, DTD_DETAIL_QUOTED_STRING_TOKEN, DTD_DETAIL_START_OF_SOURCE_TOKEN, DTD_DETAIL_UNQUOTED_STRING_TOKEN, DTD_DETAIL_WHITESPACE_TOKEN };

class PASCALIMPLEMENTATION TXmlDtdDetailTokenizer : public TXmlCustomTokenizer
{
	typedef TXmlCustomTokenizer inherited;
	
private:
	bool FIsPERefInDeclSep;
	bool FInPI;
	
protected:
	TXmlDtdDetailTokenType FLastTokenType;
	TXmlDtdDetailTokenType FTokenType;
	
public:
	__fastcall TXmlDtdDetailTokenizer(TXmlSimpleInputSource* const InputSource, const bool AIsPERefInDeclSep);
	virtual void __fastcall Next();
	virtual void __fastcall NextEndOfIgnoredCondSect();
	__property bool IsPERefInDeclSep = {read=FIsPERefInDeclSep, nodefault};
	__property TXmlDtdDetailTokenType TokenType = {read=FTokenType, nodefault};
public:
	/* TXmlCustomTokenizer.Destroy */ inline __fastcall virtual ~TXmlDtdDetailTokenizer() { }
	
};


enum DECLSPEC_DENUM TXmlPERefTreatment : unsigned char { petResolve, petResolveInDeclSep, petResolveInDeclSepSkipExt };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlDtdDetailPETokenizer : public TUtilsNoRefCount
{
	typedef TUtilsNoRefCount inherited;
	
private:
	int FBufSize;
	TXmlErrorType FErrorType;
	System::Generics::Collections::TStack__1<TXmlSimpleInputSource*>* FInputSourceStack;
	Xml::Internal::Widestringutils::TUtilsWideStringList* FPENameStack;
	TXmlPERefTreatment FPERefTreatment;
	System::Generics::Collections::TStack__1<Xml::Internal::Widestringutils::TUtilsWideStringStream*>* FStreamStack;
	System::Generics::Collections::TStack__1<TXmlDtdDetailTokenizer*>* FTokenizerStack;
	TDomResolveEntityEvent FOnResolveParameterEntity;
	void __fastcall CreateInternalInputSource(System::Classes::TStream* const Stream, const System::WideString PEName, const System::WideString PubId, const System::WideString SysId, const bool IsPERefInDeclSep);
	void __fastcall CreateInternalStream(const System::WideString S, const System::WideString PEName, const System::WideString PubId, const System::WideString SysId, const bool IsPERefInDeclSep);
	void __fastcall CreateInternalTokenizer(TXmlSimpleInputSource* const InputSource, const System::WideString PEName, const bool IsPERefInDeclSep);
	void __fastcall DestroyInternalTokenizer();
	System::WideString __fastcall GetClue();
	System::WideString __fastcall GetCurrentPEName();
	TXmlErrorType __fastcall GetErrorType();
	TXmlDtdDetailTokenizer* __fastcall GetInternalTokenizer();
	bool __fastcall GetIsPERefInDeclSep();
	TXmlDtdDetailTokenType __fastcall GetTokenType();
	System::WideString __fastcall GetTokenValue();
	void __fastcall SetPERefTreatment(const TXmlPERefTreatment Value);
	
protected:
	bool FIsInMarkup;
	void __fastcall DoResolveParameterEntity(const System::WideString EntityName, /* out */ System::WideString &EntityValue, /* out */ System::WideString &PubId, /* out */ System::WideString &SysId, /* out */ TXmlErrorType &Error);
	virtual bool __fastcall GetIsProcessingPE();
	virtual __int64 __fastcall GetEndByteNumber();
	virtual __int64 __fastcall GetEndCharNumber();
	virtual __int64 __fastcall GetEndColumnNumber();
	virtual __int64 __fastcall GetEndLineNumber();
	virtual __int64 __fastcall GetEndTabsInLine();
	virtual TDtdObject* __fastcall GetRelatedDtdObject();
	virtual TDomNode* __fastcall GetRelatedNode();
	virtual __int64 __fastcall GetStartByteNumber();
	virtual __int64 __fastcall GetStartCharNumber();
	virtual __int64 __fastcall GetStartColumnNumber();
	virtual __int64 __fastcall GetStartLineNumber();
	virtual __int64 __fastcall GetStartTabsInLine();
	virtual System::WideString __fastcall GetUri();
	__property TXmlDtdDetailTokenizer* InternalTokenizer = {read=GetInternalTokenizer};
	
public:
	__fastcall TXmlDtdDetailPETokenizer(TXmlSimpleInputSource* const AInputSource, const bool AIsPERefInDeclSep);
	__fastcall virtual ~TXmlDtdDetailPETokenizer();
	virtual void __fastcall Next();
	virtual void __fastcall NextEndOfIgnoredCondSect();
	__property System::WideString Clue = {read=GetClue};
	__property System::WideString CurrentPEName = {read=GetCurrentPEName};
	__property TXmlErrorType ErrorType = {read=GetErrorType, nodefault};
	__property bool IsInMarkup = {read=FIsInMarkup, nodefault};
	__property bool IsPERefInDeclSep = {read=GetIsPERefInDeclSep, nodefault};
	__property bool IsProcessingPE = {read=GetIsProcessingPE, nodefault};
	__property TXmlPERefTreatment PERefTreatment = {read=FPERefTreatment, write=SetPERefTreatment, default=0};
	__property TXmlDtdDetailTokenType TokenType = {read=GetTokenType, nodefault};
	__property System::WideString TokenValue = {read=GetTokenValue};
	__property TDomResolveEntityEvent OnResolveParameterEntity = {read=FOnResolveParameterEntity, write=FOnResolveParameterEntity};
private:
	void *__IDomLocator;	// IDomLocator 
	
public:
	operator IDomLocator*(void) { return (IDomLocator*)&__IDomLocator; }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM TXmlDtdAbstractTokenType : unsigned char { DTD_ABSTRACT_ATTLIST_DECL_TOKEN, DTD_ABSTRACT_COMMENT_TOKEN, DTD_ABSTRACT_CONDITIONAL_SECTION_TOKEN, DTD_ABSTRACT_ELEMENT_DECL_TOKEN, DTD_ABSTRACT_END_OF_SOURCE_TOKEN, DTD_ABSTRACT_ENTITY_DECL_TOKEN, DTD_ABSTRACT_EXT_PARAMETER_ENTITY_REF_TOKEN, DTD_ABSTRACT_IGNORABLE_WHITESPACE_TOKEN, DTD_ABSTRACT_INVALID_MARKUP_TOKEN, DTD_ABSTRACT_NOTATION_DECL_TOKEN, DTD_ABSTRACT_PARAMETER_ENTITY_DECL_TOKEN, DTD_ABSTRACT_PI_TOKEN, DTD_ABSTRACT_START_OF_SOURCE_TOKEN };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlCustomSubsetTokenizer : public TUtilsNoRefCount
{
	typedef TUtilsNoRefCount inherited;
	
private:
	bool __fastcall FindNextAttDef(System::WideString Decl, /* out */ TXmlDataType &AttType, /* out */ TDomAttrValueConstraint &Constraint, /* out */ System::WideString &AttName, /* out */ System::WideString &Enumeration, /* out */ System::WideString &DefaultValue, /* out */ System::WideString &Rest);
	
protected:
	bool FAllowConditionalSections;
	System::WideString FAttDeclElementType;
	System::WideString FClue;
	Xml::Internal::Widestringutils::TUtilsWideStringList* FCondSectBracketPEName;
	Xml::Internal::Widestringutils::TUtilsWideStringList* FCondSectStartPEName;
	TXmlSignal* FCurrentSignal;
	System::WideString FEntityDeclBaseUri;
	TXmlErrorType FErrorType;
	TDomPERepository* FPERepository;
	TXmlDtdAbstractTokenType FTokenType;
	TDomLocationEvent FOnPEReference;
	TDomWideStringLocationEvent FOnProcessingAttListDecl;
	Xml::Internal::Widestringutils::TUtilsWideStringList* FOpeningBracketPEName;
	System::WideString FPendingAttrDefs;
	TXmlDtdDetailPETokenizer* FXmlDtdDetailPETokenizer;
	TXmlCommentSignal* __fastcall CreateCommentSignal(const System::WideString Data);
	TXmlElementTypeDeclarationSignal* __fastcall CreateElementDeclSignal(const System::WideString ElementName, const System::WideString Data, const bool IsDeclaredInPE);
	TXmlEntityDeclarationSignal* __fastcall CreateEntityDeclSignal(const System::WideString EntityName, const System::WideString EntityValue, const System::WideString PublicId, const System::WideString SystemId, const System::WideString NotationName, const System::WideString BaseUri, const bool IsDeclaredInPE);
	TXmlExternalPEReferenceSignal* __fastcall CreateExtPERefSignal(const System::WideString ParameterEntityReference);
	TXmlParameterEntityDeclarationSignal* __fastcall CreateParameterEntityDeclSignal(const System::WideString EntityName, const System::WideString EntityValue, const System::WideString PublicId, const System::WideString SystemId, const System::WideString BaseUri);
	TXmlProcessingInstructionSignal* __fastcall CreatePISignal(const System::WideString Target, const System::WideString Data);
	TXmlNotationDeclarationSignal* __fastcall CreateNotationDeclSignal(const System::WideString NotationName, const System::WideString PubidLiteral, const System::WideString SystemLiteral, const bool IsDeclaredInPE);
	void __fastcall DoPEReference();
	void __fastcall DoProcessingAttListDecl(const System::WideString ElementType);
	virtual bool __fastcall GetAllowPEsInMarkup();
	virtual System::WideString __fastcall GetClue();
	virtual System::WideString __fastcall GetEntityDeclBaseUri();
	virtual TXmlErrorType __fastcall GetErrorType();
	virtual bool __fastcall GetIsProcessingPE();
	virtual System::WideString __fastcall GetSystemId();
	virtual TXmlDtdAbstractTokenType __fastcall GetTokenType();
	System::WideString __fastcall IncludePERefsInLiteral(const System::WideString S, /* out */ TXmlErrorType &ErrType);
	bool __fastcall ProcessPendingAttrDef();
	virtual void __fastcall ResolveParameterEntityEventHandler(System::TObject* Sender, const System::WideString EntityName, System::WideString &EntityValue, System::WideString &PubId, System::WideString &SysId, TXmlErrorType &Error) = 0 ;
	virtual __int64 __fastcall GetEndByteNumber();
	virtual __int64 __fastcall GetEndCharNumber();
	virtual __int64 __fastcall GetEndColumnNumber();
	virtual __int64 __fastcall GetEndLineNumber();
	virtual __int64 __fastcall GetEndTabsInLine();
	virtual TDtdObject* __fastcall GetRelatedDtdObject();
	virtual TDomNode* __fastcall GetRelatedNode();
	virtual __int64 __fastcall GetStartByteNumber();
	virtual __int64 __fastcall GetStartCharNumber();
	virtual __int64 __fastcall GetStartColumnNumber();
	virtual __int64 __fastcall GetStartLineNumber();
	virtual __int64 __fastcall GetStartTabsInLine();
	virtual System::WideString __fastcall GetUri();
	
public:
	__fastcall TXmlCustomSubsetTokenizer(TXmlSimpleInputSource* const AInputSource, TDomPERepository* const APERepository);
	__fastcall virtual ~TXmlCustomSubsetTokenizer();
	virtual void __fastcall Next();
	__property bool AllowPEsInMarkup = {read=GetAllowPEsInMarkup, nodefault};
	__property System::WideString Clue = {read=GetClue};
	__property TXmlSignal* CurrentSignal = {read=FCurrentSignal};
	__property System::WideString EntityDeclBaseUri = {read=GetEntityDeclBaseUri};
	__property TXmlErrorType ErrorType = {read=GetErrorType, nodefault};
	__property bool IsProcessingPE = {read=GetIsProcessingPE, nodefault};
	__property TDomPERepository* PERepository = {read=FPERepository};
	__property System::WideString SystemId = {read=GetSystemId};
	__property TXmlDtdAbstractTokenType TokenType = {read=GetTokenType, nodefault};
	__property TDomLocationEvent OnPEReference = {read=FOnPEReference, write=FOnPEReference};
	__property TDomWideStringLocationEvent OnProcessingAttListDecl = {read=FOnProcessingAttListDecl, write=FOnProcessingAttListDecl};
private:
	void *__IDomLocator;	// IDomLocator 
	
public:
	operator IDomLocator*(void) { return (IDomLocator*)&__IDomLocator; }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlExtSubsetTokenizer : public TXmlCustomSubsetTokenizer
{
	typedef TXmlCustomSubsetTokenizer inherited;
	
protected:
	virtual void __fastcall ResolveParameterEntityEventHandler(System::TObject* Sender, const System::WideString EntityName, System::WideString &EntityValue, System::WideString &PubId, System::WideString &SysId, TXmlErrorType &Error);
	
public:
	__fastcall TXmlExtSubsetTokenizer(TXmlInputSource* const AInputSource, TDomPERepository* const APERepository);
public:
	/* TXmlCustomSubsetTokenizer.Destroy */ inline __fastcall virtual ~TXmlExtSubsetTokenizer() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlIntSubsetTokenizer : public TXmlCustomSubsetTokenizer
{
	typedef TXmlCustomSubsetTokenizer inherited;
	
protected:
	virtual bool __fastcall GetResolveExtPEs();
	virtual void __fastcall ResolveParameterEntityEventHandler(System::TObject* Sender, const System::WideString EntityName, System::WideString &EntityValue, System::WideString &PubId, System::WideString &SysId, TXmlErrorType &Error);
	virtual void __fastcall SetResolveExtPEs(const bool Value);
	
public:
	__fastcall TXmlIntSubsetTokenizer(TXmlSimpleInputSource* const AInputSource, TDomPERepository* const APERepository);
	__property bool ResolveExtPEs = {read=GetResolveExtPEs, write=SetResolveExtPEs, default=1};
public:
	/* TXmlCustomSubsetTokenizer.Destroy */ inline __fastcall virtual ~TXmlIntSubsetTokenizer() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM TXmlElementCMTokenType : unsigned char { DTD_ECM_ANY_KEYWORD_TOKEN, DTD_ECM_CLOSING_BRACKET_TOKEN, DTD_ECM_EMPTY_KEYWORD_TOKEN, DTD_ECM_END_OF_SOURCE_TOKEN, DTD_ECM_FREQUENCY_TOKEN, DTD_ECM_INVALID_MARKUP_TOKEN, DTD_ECM_NAME_TOKEN, DTD_ECM_OPENING_BRACKET_TOKEN, DTD_ECM_PCDATA_KEYWORD_TOKEN, DTD_ECM_SEPARATOR_TOKEN, DTD_ECM_START_OF_SOURCE_TOKEN };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlElementCMTokenizer : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	System::WideString FClue;
	bool FBracketFound;
	TXmlErrorType FErrorType;
	Xml::Internal::Parserutilswin32::TUtilsUCS4Reader* FUCS4Reader;
	Xml::Internal::Widestringutils::TUtilsWideStringStream* FStringStream;
	TXmlElementCMTokenType FTokenType;
	Xml::Internal::Widestringutils::TUtilsCustomWideStr* FTokenValue;
	virtual System::WideString __fastcall GetTokenValue();
	
public:
	__fastcall TXmlElementCMTokenizer(const System::WideString S);
	__fastcall virtual ~TXmlElementCMTokenizer();
	virtual void __fastcall Next();
	__property System::WideString Clue = {read=FClue};
	__property TXmlErrorType ErrorType = {read=FErrorType, nodefault};
	__property TXmlElementCMTokenType TokenType = {read=FTokenType, nodefault};
	__property System::WideString TokenValue = {read=GetTokenValue};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM TXmlDoctypeDeclTokenType : unsigned char { DOCTYPE_END_OF_SOURCE_TOKEN, DOCTYPE_INTSUBSET_TOKEN, DOCTYPE_NAME_TOKEN, DOCTYPE_PUBID_TOKEN, DOCTYPE_START_OF_SOURCE_TOKEN, DOCTYPE_SYSID_TOKEN };

class PASCALIMPLEMENTATION TXmlDoctypeDeclTokenizer : public TUtilsNoRefCount
{
	typedef TUtilsNoRefCount inherited;
	
protected:
	System::WideString FClue;
	TXmlErrorType FErrorType;
	TXmlSimpleInputSource* FInputSource;
	Xml::Internal::Widestringutils::TUtilsWideStringStream* FStringStream;
	Xml::Internal::Parserutilswin32::TUtilsUCS4CharData FTokenEnd;
	Xml::Internal::Parserutilswin32::TUtilsUCS4CharData FTokenStart;
	TXmlDoctypeDeclTokenType FTokenType;
	Xml::Internal::Widestringutils::TUtilsCustomWideStr* FTokenValue;
	virtual System::WideString __fastcall GetTokenValue();
	virtual __int64 __fastcall GetEndByteNumber();
	virtual __int64 __fastcall GetEndCharNumber();
	virtual __int64 __fastcall GetEndColumnNumber();
	virtual __int64 __fastcall GetEndLineNumber();
	virtual __int64 __fastcall GetEndTabsInLine();
	virtual TDtdObject* __fastcall GetRelatedDtdObject();
	virtual TDomNode* __fastcall GetRelatedNode();
	virtual __int64 __fastcall GetStartByteNumber();
	virtual __int64 __fastcall GetStartCharNumber();
	virtual __int64 __fastcall GetStartColumnNumber();
	virtual __int64 __fastcall GetStartLineNumber();
	virtual __int64 __fastcall GetStartTabsInLine();
	virtual System::WideString __fastcall GetUri();
	
public:
	__fastcall TXmlDoctypeDeclTokenizer(const System::WideString S, const System::WideString DocumentUri, __int64 InitialByteCount, __int64 InitialCharCount, __int64 InitialCharsInLine, __int64 InitialTabsInLine, __int64 InitialLine);
	__fastcall virtual ~TXmlDoctypeDeclTokenizer();
	virtual void __fastcall Next();
	__property System::WideString Clue = {read=FClue};
	__property TXmlErrorType ErrorType = {read=FErrorType, nodefault};
	__property TXmlDoctypeDeclTokenType TokenType = {read=FTokenType, nodefault};
	__property System::WideString TokenValue = {read=GetTokenValue};
private:
	void *__IDomLocator;	// IDomLocator 
	
public:
	operator IDomLocator*(void) { return (IDomLocator*)&__IDomLocator; }
	
};


enum DECLSPEC_DENUM TXmlAttrValueTokenType : unsigned char { ATTR_CHAR_REF, ATTR_END_OF_SOURCE_TOKEN, ATTR_ENTITY_REF, ATTR_START_OF_SOURCE_TOKEN, ATTR_TEXT };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlAttrValueTokenizer : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	TXmlErrorType FErrorType;
	Xml::Internal::Parserutilswin32::TUtilsUCS4Reader* FUCS4Reader;
	Xml::Internal::Widestringutils::TUtilsWideStringStream* FStringStream;
	TXmlAttrValueTokenType FTokenType;
	Xml::Internal::Widestringutils::TUtilsCustomWideStr* FTokenValue;
	virtual System::WideString __fastcall GetTokenValue();
	
public:
	__fastcall TXmlAttrValueTokenizer(const System::WideString S);
	__fastcall virtual ~TXmlAttrValueTokenizer();
	virtual void __fastcall Next();
	__property TXmlErrorType ErrorType = {read=FErrorType, nodefault};
	__property TXmlAttrValueTokenType TokenType = {read=FTokenType, nodefault};
	__property System::WideString TokenValue = {read=GetTokenValue};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TXmlOutputSource : public Xml::Internal::Parserutilswin32::TUtilsCustomOutputStream
{
	typedef Xml::Internal::Parserutilswin32::TUtilsCustomOutputStream inherited;
	
private:
	Xml::Internal::Codecutilswin32::TUnicodeCodec* FCodec;
	System::UnicodeString FEncoding;
	void __fastcall SetEncoding(const System::UnicodeString Value);
	Xml::Internal::Codecutilswin32::TCodecWriteLFOption __fastcall GetWriteLFOption();
	void __fastcall SetWriteLFOption(const Xml::Internal::Codecutilswin32::TCodecWriteLFOption Value);
	
protected:
#ifndef __aarch64__
	virtual void __fastcall WriteEventHandler(System::TObject* const Sender, const void *Buf, int Count);
#else /* __aarch64__ */
	virtual void __fastcall WriteEventHandler(System::TObject* const Sender, const void *Buf, long Count);
#endif /* __aarch64__ */
	
public:
	__fastcall TXmlOutputSource(System::Classes::TStream* const Stream, const int BufSize);
	__fastcall virtual ~TXmlOutputSource();
	virtual int __fastcall WriteByteOrderMark();
	virtual void __fastcall WriteUCS4Char(const unsigned C, /* out */ int &ByteCount);
	__property BufSize;
	__property System::UnicodeString Encoding = {read=FEncoding, write=SetEncoding};
	__property Xml::Internal::Codecutilswin32::TCodecWriteLFOption WriteLFOption = {read=GetWriteLFOption, write=SetWriteLFOption, default=2};
};


typedef void __fastcall (__closure *TXmlProcessingEvent)(System::TObject* Sender, TXmlSignal* Signal, bool &Accept);

typedef void __fastcall (__closure *TXmlPostProcessingEvent)(System::TObject* Sender, TXmlSignal* Signal);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomPERepository : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TXmlCustomReader* FOwner;
	Xml::Internal::Widestringutils::TUtilsWideStringList* FPEList;
	
protected:
	virtual void __fastcall ResolveResourceAsWideString(const System::WideString BaseURI, const System::WideString PublicId, const System::WideString SystemId, /* out */ System::WideString &S, /* out */ TXmlErrorType &Error);
	
public:
	__fastcall TDomPERepository(TXmlCustomReader* const AOwner);
	__fastcall virtual ~TDomPERepository();
	bool __fastcall Add(const System::WideString Name, const System::WideString Value)/* overload */;
	bool __fastcall Add(const System::WideString Name, const System::WideString BaseUri, const System::WideString PubId, const System::WideString SysId)/* overload */;
	virtual void __fastcall Clear();
	virtual bool __fastcall Delete(const System::WideString Name);
	virtual TXmlErrorType __fastcall ResolvePE(const System::WideString Name, const bool AcceptExtEntity, /* out */ System::WideString &Value, /* out */ System::WideString &PubId, /* out */ System::WideString &SysId);
	__property TXmlCustomReader* OwnerReader = {read=FOwner};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomPEInfoObject : public TDomCustomNode
{
	typedef TDomCustomNode inherited;
	
private:
	System::WideString FBaseUri;
	TDomEntityType FEntityType;
	bool FUpdateAttempted;
	TXmlErrorType FUpdateError;
	System::WideString FLiteralValue;
	System::WideString FNodeName;
	TDomPERepository* FOwnerRepository;
	System::WideString FPublicId;
	System::WideString FSystemId;
	
protected:
	virtual System::WideString __fastcall GetNodeName();
	
public:
	__fastcall TDomPEInfoObject(TDomPERepository* const AOwner, const System::WideString EntityName, const System::WideString LitValue);
	__fastcall TDomPEInfoObject(TDomPERepository* const AOwner, const System::WideString EntityName, const System::WideString ABaseUri, const System::WideString PubId, const System::WideString SysId);
	System::WideString __fastcall EntityURI();
	void __fastcall Update();
	__property System::WideString BaseUri = {read=FBaseUri};
	__property TDomEntityType EntityType = {read=FEntityType, nodefault};
	__property System::WideString LiteralValue = {read=FLiteralValue};
	__property TDomPERepository* OwnerRepository = {read=FOwnerRepository};
	__property System::WideString PublicId = {read=FPublicId};
	__property System::WideString SystemId = {read=FSystemId};
	__property bool UpdateAttempted = {read=FUpdateAttempted, nodefault};
	__property TXmlErrorType UpdateError = {read=FUpdateError, nodefault};
public:
	/* TCustomOwnedNode.Destroy */ inline __fastcall virtual ~TDomPEInfoObject() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM Xml_Internal_Adomcore_4_3__68 : unsigned char { ssDoc, ssDtd };

typedef System::Set<Xml_Internal_Adomcore_4_3__68, Xml_Internal_Adomcore_4_3__68::ssDoc, Xml_Internal_Adomcore_4_3__68::ssDtd> TXmlSignalScope;

class PASCALIMPLEMENTATION TXmlSignal : public TUtilsNoRefCount
{
	typedef TUtilsNoRefCount inherited;
	
private:
	__int64 FEndByteNumber;
	__int64 FEndCharNumber;
	__int64 FEndColumnNumber;
	__int64 FEndLineNumber;
	__int64 FEndTabsInLine;
	TXmlCustomReader* FReader;
	TDtdObject* FRelatedDtdObject;
	TDomNode* FRelatedNode;
	__int64 FStartByteNumber;
	__int64 FStartCharNumber;
	__int64 FStartColumnNumber;
	__int64 FStartLineNumber;
	__int64 FStartTabsInLine;
	System::WideString FUri;
	
protected:
	virtual void __fastcall InitSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode);
	virtual __int64 __fastcall GetEndByteNumber();
	virtual __int64 __fastcall GetEndCharNumber();
	virtual __int64 __fastcall GetEndColumnNumber();
	virtual __int64 __fastcall GetEndLineNumber();
	virtual __int64 __fastcall GetEndTabsInLine();
	virtual TDtdObject* __fastcall GetRelatedDtdObject();
	virtual TDomNode* __fastcall GetRelatedNode();
	virtual __int64 __fastcall GetStartByteNumber();
	virtual __int64 __fastcall GetStartCharNumber();
	virtual __int64 __fastcall GetStartColumnNumber();
	virtual __int64 __fastcall GetStartLineNumber();
	virtual __int64 __fastcall GetStartTabsInLine();
	virtual System::WideString __fastcall GetUri();
	
public:
	__fastcall virtual TXmlSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode);
	__fastcall virtual TXmlSignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location);
	virtual void __fastcall CheckWellformedness(/* out */ TXmlErrorType &XmlErrorType, /* out */ System::WideString &Flaw, /* out */ System::WideString &Clue);
	virtual TXmlSignal* __fastcall CloneSignal(TXmlCustomReader* const AReader);
	virtual TXmlSignalScope __fastcall Scope() = 0 ;
	__property TXmlCustomReader* Reader = {read=FReader};
	__property __int64 EndByteNumber = {read=GetEndByteNumber};
	__property __int64 EndCharNumber = {read=GetEndCharNumber};
	__property __int64 EndColumnNumber = {read=GetEndColumnNumber};
	__property __int64 EndLineNumber = {read=GetEndLineNumber};
	__property __int64 EndTabsInLine = {read=GetEndTabsInLine};
	__property TDtdObject* RelatedDtdObject = {read=GetRelatedDtdObject};
	__property TDomNode* RelatedNode = {read=GetRelatedNode};
	__property __int64 StartByteNumber = {read=GetStartByteNumber};
	__property __int64 StartCharNumber = {read=GetStartCharNumber};
	__property __int64 StartColumnNumber = {read=GetStartColumnNumber};
	__property __int64 StartLineNumber = {read=GetStartLineNumber};
	__property __int64 StartTabsInLine = {read=GetStartTabsInLine};
	__property System::WideString Uri = {read=GetUri};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlSignal() { }
	
private:
	void *__IDomLocator;	// IDomLocator 
	
public:
	operator IDomLocator*(void) { return (IDomLocator*)&__IDomLocator; }
	
};


class PASCALIMPLEMENTATION TXmlCompletedSignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
public:
	virtual TXmlSignalScope __fastcall Scope();
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlCompletedSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlCompletedSignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlCompletedSignal() { }
	
};


class PASCALIMPLEMENTATION TXmlAbortedSignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
public:
	virtual TXmlSignalScope __fastcall Scope();
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlAbortedSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlAbortedSignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlAbortedSignal() { }
	
};


class PASCALIMPLEMENTATION TXmlAttributeSignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
private:
	TXmlDataType FDataType;
	System::WideString FName;
	System::WideString FValue;
	
public:
	virtual void __fastcall CheckWellformedness(/* out */ TXmlErrorType &XmlErrorType, /* out */ System::WideString &Flaw, /* out */ System::WideString &Clue);
	virtual TXmlSignal* __fastcall CloneSignal(TXmlCustomReader* const AReader);
	virtual TXmlSignalScope __fastcall Scope();
	__property TXmlDataType DataType = {read=FDataType, write=FDataType, nodefault};
	__property System::WideString Name = {read=FName, write=FName};
	__property System::WideString Value = {read=FValue, write=FValue};
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlAttributeSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlAttributeSignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlAttributeSignal() { }
	
};


class PASCALIMPLEMENTATION TXmlCDATASignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
private:
	System::WideString FData;
	
public:
	virtual void __fastcall CheckWellformedness(/* out */ TXmlErrorType &XmlErrorType, /* out */ System::WideString &Flaw, /* out */ System::WideString &Clue);
	virtual TXmlSignal* __fastcall CloneSignal(TXmlCustomReader* const AReader);
	virtual TXmlSignalScope __fastcall Scope();
	__property System::WideString Data = {read=FData, write=FData};
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlCDATASignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlCDATASignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlCDATASignal() { }
	
};


class PASCALIMPLEMENTATION TXmlDoctypeSignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
private:
	System::WideString FData;
	System::WideString FDoctypeName;
	__int64 FIntSubsetByteNumber;
	__int64 FIntSubsetCharNumber;
	__int64 FIntSubsetStartColumn;
	__int64 FIntSubsetStartLine;
	System::WideString FPublicId;
	System::WideString FSystemId;
	
public:
	virtual void __fastcall CheckWellformedness(/* out */ TXmlErrorType &XmlErrorType, /* out */ System::WideString &Flaw, /* out */ System::WideString &Clue);
	virtual TXmlSignal* __fastcall CloneSignal(TXmlCustomReader* const AReader);
	virtual TXmlSignalScope __fastcall Scope();
	__property System::WideString Data = {read=FData, write=FData};
	__property System::WideString DoctypeName = {read=FDoctypeName, write=FDoctypeName};
	__property __int64 IntSubsetStartByteNumber = {read=FIntSubsetByteNumber, write=FIntSubsetByteNumber};
	__property __int64 IntSubsetStartCharNumber = {read=FIntSubsetCharNumber, write=FIntSubsetCharNumber};
	__property __int64 IntSubsetStartColumn = {read=FIntSubsetStartColumn, write=FIntSubsetStartColumn};
	__property __int64 IntSubsetStartLine = {read=FIntSubsetStartLine, write=FIntSubsetStartLine};
	__property System::WideString PublicId = {read=FPublicId, write=FPublicId};
	__property System::WideString SystemId = {read=FSystemId, write=FSystemId};
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlDoctypeSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlDoctypeSignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlDoctypeSignal() { }
	
};


class PASCALIMPLEMENTATION TXmlEndElementSignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
private:
	System::WideString FTagName;
	
public:
	virtual void __fastcall CheckWellformedness(/* out */ TXmlErrorType &XmlErrorType, /* out */ System::WideString &Flaw, /* out */ System::WideString &Clue);
	virtual TXmlSignal* __fastcall CloneSignal(TXmlCustomReader* const AReader);
	virtual TXmlSignalScope __fastcall Scope();
	__property System::WideString TagName = {read=FTagName, write=FTagName};
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlEndElementSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlEndElementSignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlEndElementSignal() { }
	
};


class PASCALIMPLEMENTATION TXmlEndPrefixMappingSignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
private:
	System::WideString FPrefix;
	
public:
	virtual void __fastcall CheckWellformedness(/* out */ TXmlErrorType &XmlErrorType, /* out */ System::WideString &Flaw, /* out */ System::WideString &Clue);
	virtual TXmlSignal* __fastcall CloneSignal(TXmlCustomReader* const AReader);
	virtual TXmlSignalScope __fastcall Scope();
	__property System::WideString Prefix = {read=FPrefix, write=FPrefix};
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlEndPrefixMappingSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlEndPrefixMappingSignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlEndPrefixMappingSignal() { }
	
};


class PASCALIMPLEMENTATION TXmlEntityRefSignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
private:
	System::WideString FEntityName;
	
public:
	virtual void __fastcall CheckWellformedness(/* out */ TXmlErrorType &XmlErrorType, /* out */ System::WideString &Flaw, /* out */ System::WideString &Clue);
	virtual TXmlSignal* __fastcall CloneSignal(TXmlCustomReader* const AReader);
	virtual TXmlSignalScope __fastcall Scope();
	__property System::WideString EntityName = {read=FEntityName, write=FEntityName};
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlEntityRefSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlEntityRefSignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlEntityRefSignal() { }
	
};


class PASCALIMPLEMENTATION TXmlPCDATASignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
private:
	bool FCharRefGenerated;
	System::WideString FData;
	
protected:
	virtual void __fastcall InitSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode);
	
public:
	virtual void __fastcall CheckWellformedness(/* out */ TXmlErrorType &XmlErrorType, /* out */ System::WideString &Flaw, /* out */ System::WideString &Clue);
	virtual TXmlSignal* __fastcall CloneSignal(TXmlCustomReader* const AReader);
	virtual TXmlSignalScope __fastcall Scope();
	__property bool CharRefGenerated = {read=FCharRefGenerated, write=FCharRefGenerated, default=0};
	__property System::WideString Data = {read=FData, write=FData};
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlPCDATASignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlPCDATASignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlPCDATASignal() { }
	
};


class PASCALIMPLEMENTATION TXmlSkippedEntitySignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
private:
	System::WideString FEntityName;
	
public:
	virtual TXmlSignal* __fastcall CloneSignal(TXmlCustomReader* const AReader);
	virtual TXmlSignalScope __fastcall Scope();
	__property System::WideString EntityName = {read=FEntityName, write=FEntityName};
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlSkippedEntitySignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlSkippedEntitySignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlSkippedEntitySignal() { }
	
};


class PASCALIMPLEMENTATION TXmlStartDocumentSignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
private:
	System::WideString FEncodingName;
	System::WideString FInputEncoding;
	TDomStandalone FStandaloneDecl;
	System::WideString FVersion;
	
public:
	virtual void __fastcall CheckWellformedness(/* out */ TXmlErrorType &XmlErrorType, /* out */ System::WideString &Flaw, /* out */ System::WideString &Clue);
	virtual TXmlSignal* __fastcall CloneSignal(TXmlCustomReader* const AReader);
	virtual TXmlSignalScope __fastcall Scope();
	__property System::WideString EncodingName = {read=FEncodingName, write=FEncodingName};
	__property System::WideString InputEncoding = {read=FInputEncoding, write=FInputEncoding};
	__property TDomStandalone StandaloneDecl = {read=FStandaloneDecl, write=FStandaloneDecl, nodefault};
	__property System::WideString Version = {read=FVersion, write=FVersion};
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlStartDocumentSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlStartDocumentSignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlStartDocumentSignal() { }
	
};


class PASCALIMPLEMENTATION TXmlStartDocumentFragmentSignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
private:
	System::WideString FEncodingName;
	
public:
	virtual void __fastcall CheckWellformedness(/* out */ TXmlErrorType &XmlErrorType, /* out */ System::WideString &Flaw, /* out */ System::WideString &Clue);
	virtual TXmlSignal* __fastcall CloneSignal(TXmlCustomReader* const AReader);
	virtual TXmlSignalScope __fastcall Scope();
	__property System::WideString EncodingName = {read=FEncodingName, write=FEncodingName};
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlStartDocumentFragmentSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlStartDocumentFragmentSignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlStartDocumentFragmentSignal() { }
	
};


class PASCALIMPLEMENTATION TXmlStartElementSignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
private:
	System::WideString FTagName;
	
public:
	virtual void __fastcall CheckWellformedness(/* out */ TXmlErrorType &XmlErrorType, /* out */ System::WideString &Flaw, /* out */ System::WideString &Clue);
	virtual TXmlSignal* __fastcall CloneSignal(TXmlCustomReader* const AReader);
	virtual TXmlSignalScope __fastcall Scope();
	__property System::WideString TagName = {read=FTagName, write=FTagName};
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlStartElementSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlStartElementSignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlStartElementSignal() { }
	
};


class PASCALIMPLEMENTATION TXmlStartPrefixMappingSignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
private:
	System::WideString FPrefix;
	System::WideString FUri;
	
public:
	virtual void __fastcall CheckWellformedness(/* out */ TXmlErrorType &XmlErrorType, /* out */ System::WideString &Flaw, /* out */ System::WideString &Clue);
	virtual TXmlSignal* __fastcall CloneSignal(TXmlCustomReader* const AReader);
	virtual TXmlSignalScope __fastcall Scope();
	__property System::WideString Prefix = {read=FPrefix, write=FPrefix};
	__property System::WideString Uri = {read=FUri, write=FUri};
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlStartPrefixMappingSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlStartPrefixMappingSignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlStartPrefixMappingSignal() { }
	
};


class PASCALIMPLEMENTATION TXmlCommentSignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
private:
	System::WideString FData;
	
public:
	virtual void __fastcall CheckWellformedness(/* out */ TXmlErrorType &XmlErrorType, /* out */ System::WideString &Flaw, /* out */ System::WideString &Clue);
	virtual TXmlSignal* __fastcall CloneSignal(TXmlCustomReader* const AReader);
	virtual TXmlSignalScope __fastcall Scope();
	__property System::WideString Data = {read=FData, write=FData};
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlCommentSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlCommentSignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlCommentSignal() { }
	
};


class PASCALIMPLEMENTATION TXmlProcessingInstructionSignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
private:
	System::WideString FData;
	System::WideString FTarget;
	
public:
	virtual void __fastcall CheckWellformedness(/* out */ TXmlErrorType &XmlErrorType, /* out */ System::WideString &Flaw, /* out */ System::WideString &Clue);
	virtual TXmlSignal* __fastcall CloneSignal(TXmlCustomReader* const AReader);
	virtual TXmlSignalScope __fastcall Scope();
	__property System::WideString Data = {read=FData, write=FData};
	__property System::WideString Target = {read=FTarget, write=FTarget};
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlProcessingInstructionSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlProcessingInstructionSignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlProcessingInstructionSignal() { }
	
};


class PASCALIMPLEMENTATION TXmlAttributeDefinitionSignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
private:
	System::WideString FAttributeName;
	TXmlDataType FAttributeType;
	TDomAttrValueConstraint FConstraint;
	System::WideString FDefaultValue;
	Xml::Internal::Widestringutils::TUtilsWideStringList* FEnumeration;
	System::WideString FElementName;
	bool FIsDeclaredInPE;
	void __fastcall SetEnumeration(Xml::Internal::Widestringutils::TUtilsWideStringList* const Value);
	
protected:
	virtual void __fastcall InitSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode);
	
public:
	__fastcall virtual ~TXmlAttributeDefinitionSignal();
	virtual void __fastcall CheckWellformedness(/* out */ TXmlErrorType &XmlErrorType, /* out */ System::WideString &Flaw, /* out */ System::WideString &Clue);
	virtual TXmlSignal* __fastcall CloneSignal(TXmlCustomReader* const AReader);
	virtual TXmlSignalScope __fastcall Scope();
	__property System::WideString AttributeName = {read=FAttributeName, write=FAttributeName};
	__property TXmlDataType AttributeType = {read=FAttributeType, write=FAttributeType, nodefault};
	__property TDomAttrValueConstraint Constraint = {read=FConstraint, write=FConstraint, nodefault};
	__property System::WideString DefaultValue = {read=FDefaultValue, write=FDefaultValue};
	__property System::WideString ElementName = {read=FElementName, write=FElementName};
	__property Xml::Internal::Widestringutils::TUtilsWideStringList* Enumeration = {read=FEnumeration, write=SetEnumeration};
	__property bool IsDeclaredInPE = {read=FIsDeclaredInPE, write=FIsDeclaredInPE, nodefault};
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlAttributeDefinitionSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlAttributeDefinitionSignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
};


class PASCALIMPLEMENTATION TXmlElementTypeDeclarationSignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
private:
	System::WideString FData;
	System::WideString FElementName;
	bool FIsDeclaredInPE;
	
public:
	virtual void __fastcall CheckWellformedness(/* out */ TXmlErrorType &XmlErrorType, /* out */ System::WideString &Flaw, /* out */ System::WideString &Clue);
	virtual TXmlSignal* __fastcall CloneSignal(TXmlCustomReader* const AReader);
	virtual TXmlSignalScope __fastcall Scope();
	__property System::WideString Data = {read=FData, write=FData};
	__property System::WideString ElementName = {read=FElementName, write=FElementName};
	__property bool IsDeclaredInPE = {read=FIsDeclaredInPE, write=FIsDeclaredInPE, nodefault};
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlElementTypeDeclarationSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlElementTypeDeclarationSignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlElementTypeDeclarationSignal() { }
	
};


class PASCALIMPLEMENTATION TXmlEntityDeclarationSignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
private:
	System::WideString FBaseUri;
	System::WideString FEntityValue;
	System::WideString FPublicId;
	System::WideString FNotationName;
	System::WideString FEntityName;
	System::WideString FSystemId;
	bool FIsDeclaredInPE;
	
public:
	virtual void __fastcall CheckWellformedness(/* out */ TXmlErrorType &XmlErrorType, /* out */ System::WideString &Flaw, /* out */ System::WideString &Clue);
	virtual TXmlSignal* __fastcall CloneSignal(TXmlCustomReader* const AReader);
	virtual TXmlSignalScope __fastcall Scope();
	__property System::WideString BaseUri = {read=FBaseUri, write=FBaseUri};
	__property System::WideString EntityName = {read=FEntityName, write=FEntityName};
	__property System::WideString EntityValue = {read=FEntityValue, write=FEntityValue};
	__property bool IsDeclaredInPE = {read=FIsDeclaredInPE, write=FIsDeclaredInPE, nodefault};
	__property System::WideString NotationName = {read=FNotationName, write=FNotationName};
	__property System::WideString PublicId = {read=FPublicId, write=FPublicId};
	__property System::WideString SystemId = {read=FSystemId, write=FSystemId};
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlEntityDeclarationSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlEntityDeclarationSignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlEntityDeclarationSignal() { }
	
};


class PASCALIMPLEMENTATION TXmlExternalPEReferenceSignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
private:
	System::WideString FParameterEntityName;
	
public:
	virtual void __fastcall CheckWellformedness(/* out */ TXmlErrorType &XmlErrorType, /* out */ System::WideString &Flaw, /* out */ System::WideString &Clue);
	virtual TXmlSignal* __fastcall CloneSignal(TXmlCustomReader* const AReader);
	virtual TXmlSignalScope __fastcall Scope();
	__property System::WideString ParameterEntityName = {read=FParameterEntityName, write=FParameterEntityName};
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlExternalPEReferenceSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlExternalPEReferenceSignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlExternalPEReferenceSignal() { }
	
};


class PASCALIMPLEMENTATION TXmlNotationDeclarationSignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
private:
	System::WideString FNotationName;
	System::WideString FPublicId;
	System::WideString FSystemId;
	bool FIsDeclaredInPE;
	
public:
	virtual void __fastcall CheckWellformedness(/* out */ TXmlErrorType &XmlErrorType, /* out */ System::WideString &Flaw, /* out */ System::WideString &Clue);
	virtual TXmlSignal* __fastcall CloneSignal(TXmlCustomReader* const AReader);
	virtual TXmlSignalScope __fastcall Scope();
	__property bool IsDeclaredInPE = {read=FIsDeclaredInPE, write=FIsDeclaredInPE, nodefault};
	__property System::WideString NotationName = {read=FNotationName, write=FNotationName};
	__property System::WideString PublicId = {read=FPublicId, write=FPublicId};
	__property System::WideString SystemId = {read=FSystemId, write=FSystemId};
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlNotationDeclarationSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlNotationDeclarationSignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlNotationDeclarationSignal() { }
	
};


class PASCALIMPLEMENTATION TXmlParameterEntityDeclarationSignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
private:
	System::WideString FBaseUri;
	System::WideString FEntityName;
	System::WideString FEntityValue;
	System::WideString FPublicId;
	System::WideString FSystemId;
	
public:
	virtual void __fastcall CheckWellformedness(/* out */ TXmlErrorType &XmlErrorType, /* out */ System::WideString &Flaw, /* out */ System::WideString &Clue);
	virtual TXmlSignal* __fastcall CloneSignal(TXmlCustomReader* const AReader);
	virtual TXmlSignalScope __fastcall Scope();
	__property System::WideString BaseUri = {read=FBaseUri, write=FBaseUri};
	__property System::WideString EntityName = {read=FEntityName, write=FEntityName};
	__property System::WideString EntityValue = {read=FEntityValue, write=FEntityValue};
	__property System::WideString PublicId = {read=FPublicId, write=FPublicId};
	__property System::WideString SystemId = {read=FSystemId, write=FSystemId};
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlParameterEntityDeclarationSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlParameterEntityDeclarationSignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlParameterEntityDeclarationSignal() { }
	
};


class PASCALIMPLEMENTATION TXmlPEReferenceFoundSignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
public:
	virtual TXmlSignalScope __fastcall Scope();
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlPEReferenceFoundSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlPEReferenceFoundSignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlPEReferenceFoundSignal() { }
	
};


class PASCALIMPLEMENTATION TXmlStartExtDtdSignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
private:
	System::WideString FEncodingName;
	System::WideString FInputEncoding;
	System::WideString FPublicId;
	System::WideString FSystemId;
	System::WideString FVersion;
	
public:
	virtual void __fastcall CheckWellformedness(/* out */ TXmlErrorType &XmlErrorType, /* out */ System::WideString &Flaw, /* out */ System::WideString &Clue);
	virtual TXmlSignal* __fastcall CloneSignal(TXmlCustomReader* const AReader);
	virtual TXmlSignalScope __fastcall Scope();
	__property System::WideString EncodingName = {read=FEncodingName, write=FEncodingName};
	__property System::WideString InputEncoding = {read=FInputEncoding, write=FInputEncoding};
	__property System::WideString PublicId = {read=FPublicId, write=FPublicId};
	__property System::WideString SystemId = {read=FSystemId, write=FSystemId};
	__property System::WideString Version = {read=FVersion, write=FVersion};
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlStartExtDtdSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlStartExtDtdSignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlStartExtDtdSignal() { }
	
};


class PASCALIMPLEMENTATION TXmlStartIntDtdSignal : public TXmlSignal
{
	typedef TXmlSignal inherited;
	
private:
	System::WideString FSystemId;
	TDomStandalone FXmlStandalone;
	
public:
	virtual TXmlSignal* __fastcall CloneSignal(TXmlCustomReader* const AReader);
	virtual TXmlSignalScope __fastcall Scope();
	__property System::WideString SystemId = {read=FSystemId, write=FSystemId};
	__property TDomStandalone XmlStandalone = {read=FXmlStandalone, write=FXmlStandalone, nodefault};
public:
	/* TXmlSignal.Create */ inline __fastcall virtual TXmlStartIntDtdSignal(TXmlCustomReader* const AReader, const __int64 AStartByteNumber, const __int64 AStartCharNumber, const __int64 AStartColumnNumber, const __int64 AStartLineNumber, const __int64 AStartTabsInLine, const __int64 AEndByteNumber, const __int64 AEndCharNumber, const __int64 AEndColumnNumber, const __int64 AEndLineNumber, const __int64 AEndTabsInLine, const System::WideString AUri, TDtdObject* const ARelatedDtdObject, TDomNode* const ARelatedNode) : TXmlSignal(AReader, AStartByteNumber, AStartCharNumber, AStartColumnNumber, AStartLineNumber, AStartTabsInLine, AEndByteNumber, AEndCharNumber, AEndColumnNumber, AEndLineNumber, AEndTabsInLine, AUri, ARelatedDtdObject, ARelatedNode) { }
	/* TXmlSignal.CreateFromLocator */ inline __fastcall virtual TXmlStartIntDtdSignal(TXmlCustomReader* const AReader, const _di_IDomLocator Location) : TXmlSignal(AReader, Location) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TXmlStartIntDtdSignal() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlCustomReader : public TDomBaseComponent
{
	typedef TDomBaseComponent inherited;
	
private:
	TDomImplementation* FDOMImpl;
	TXmlCustomHandler* FNextHandler;
	bool FErrorReportingEnabled;
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall ResolveResourceAsWideString(const System::WideString BaseURI, const System::WideString PublicId, const System::WideString SystemId, /* out */ System::WideString &S, /* out */ TXmlErrorType &Error);
	virtual void __fastcall SendErrorNotification(const TXmlErrorType XmlErrorType, const _di_IDomLocator Location, const System::WideString Code, const System::WideString Clue);
	virtual void __fastcall SetDomImpl(TDomImplementation* const Impl);
	virtual void __fastcall SetErrorReportingEnabled(const bool Value);
	
public:
	__fastcall virtual TXmlCustomReader(System::Classes::TComponent* AOwner);
	
__published:
	__property TDomImplementation* DOMImpl = {read=FDOMImpl, write=SetDomImpl};
	__property bool ErrorReportingEnabled = {read=FErrorReportingEnabled, write=SetErrorReportingEnabled, default=1};
	__property TXmlCustomHandler* NextHandler = {read=FNextHandler, write=FNextHandler};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TXmlCustomReader() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlStandardDocReader : public TXmlCustomReader
{
	typedef TXmlCustomReader inherited;
	
protected:
	virtual void __fastcall Parse2(TXmlDocTokenizer* const XmlTokenizer);
	virtual void __fastcall SendAbortedSignal(const _di_IDomLocator Locator);
	virtual void __fastcall WriteAttribute(const _di_IDomLocator Locator, const System::WideString Name, const System::WideString Value);
	virtual void __fastcall WriteCDATA(const _di_IDomLocator Locator, const System::WideString Content);
	virtual void __fastcall WriteCharRefDec(const _di_IDomLocator Locator, const System::WideString Content);
	virtual void __fastcall WriteCharRefHex(const _di_IDomLocator Locator, const System::WideString Content);
	virtual void __fastcall WriteComment(const _di_IDomLocator Locator, const System::WideString Content);
	virtual void __fastcall WritePCDATA(const _di_IDomLocator Locator, const System::WideString Content);
	virtual void __fastcall WriteProcessingInstruction(const _di_IDomLocator Locator, const System::WideString Content);
	virtual void __fastcall WriteStartDocument(const _di_IDomLocator Locator, const System::WideString InputEnc, const System::WideString Version, const System::WideString EncName, TDomStandalone SdDl);
	virtual void __fastcall WriteStartDocumentFragment(const _di_IDomLocator Locator, const System::WideString EncName);
	virtual void __fastcall WriteStartElement(const _di_IDomLocator Locator, const System::WideString TagName);
	virtual void __fastcall WriteStartTag(const _di_IDomLocator Locator, System::WideString Content, /* out */ System::WideString &TagName);
	virtual void __fastcall WriteEndTag(const _di_IDomLocator Locator, const System::WideString Content);
	virtual void __fastcall WriteEmptyElementTag(const _di_IDomLocator Locator, const System::WideString Content);
	virtual void __fastcall WriteEntityRef(const _di_IDomLocator Locator, const System::WideString Content);
	virtual void __fastcall WriteDoctype(const _di_IDomLocator Locator, const System::WideString Content);
	virtual void __fastcall WriteCompleted(const _di_IDomLocator Locator);
	
public:
	virtual bool __fastcall Parse(TXmlInputSource* const InputSource);
	virtual bool __fastcall ParseFragment(TXmlSimpleInputSource* const InputSource);
public:
	/* TXmlCustomReader.Create */ inline __fastcall virtual TXmlStandardDocReader(System::Classes::TComponent* AOwner) : TXmlCustomReader(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TXmlStandardDocReader() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlStandardDtdReader : public TXmlCustomReader
{
	typedef TXmlCustomReader inherited;
	
private:
	Xml::Internal::Widestringutils::TUtilsWideStringList* FAttrListDeclNames;
	TDomPERepository* FPERepository;
	bool FXmlErrorDetected;
	bool FXmlFatalErrorDetected;
	void __fastcall Parseloop(TXmlCustomSubsetTokenizer* const Tokenizer);
	
protected:
	virtual bool __fastcall GetXmlErrorDetected();
	virtual bool __fastcall GetXmlFatalErrorDetected();
	virtual void __fastcall PEReferenceEventHandler(System::TObject* Sender, const _di_IDomLocator Locator);
	virtual void __fastcall PEProcessingAttListDeclEventHandler(System::TObject* Sender, const System::WideString ElementName, const _di_IDomLocator Locator);
	virtual void __fastcall SendAbortedSignal(const _di_IDomLocator Locator);
	virtual void __fastcall SendErrorNotification(const TXmlErrorType XmlErrorType, const _di_IDomLocator Location, const System::WideString Code, const System::WideString Clue);
	virtual void __fastcall WriteCompleted(const _di_IDomLocator Locator);
	virtual void __fastcall WriteStartExtDtd(const _di_IDomLocator Locator, const System::WideString InputEnc, const System::WideString PubId, const System::WideString SysId, const System::WideString Version, const System::WideString EncName);
	virtual void __fastcall WriteStartIntDtd(const _di_IDomLocator Locator, const System::WideString SysId, const TDomStandalone Standalone);
	virtual void __fastcall WriteSignal(TXmlSignal* const Signal);
	
public:
	__fastcall virtual TXmlStandardDtdReader(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TXmlStandardDtdReader();
	virtual bool __fastcall ParseExtSubset(TXmlInputSource* const InputSource);
	virtual bool __fastcall ParseIntSubset(TXmlSimpleInputSource* const InputSource, const TDomStandalone Standalone, const bool ResolveExtPEs);
	virtual void __fastcall Prepare();
	__property bool XmlErrorDetected = {read=GetXmlErrorDetected, nodefault};
	__property bool XmlFatalErrorDetected = {read=GetXmlFatalErrorDetected, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlStandardDomReader : public TXmlCustomReader
{
	typedef TXmlCustomReader inherited;
	
private:
	TDomNode* FContextNode;
	bool FIgnoreUnspecified;
	
protected:
	virtual TDomNode* __fastcall GetContextNode();
	virtual System::WideString __fastcall GetSystemId();
	virtual void __fastcall Parseloop(TDomNode* const SourceNode);
	virtual void __fastcall SendAbortedSignal();
	virtual void __fastcall WriteAttribute(const TXmlDataType ADataType, const System::WideString ANodeName, const System::WideString ANodeValue);
	virtual void __fastcall WriteCDATA(const System::WideString Content);
	virtual void __fastcall WriteComment(const System::WideString Content);
	virtual void __fastcall WriteDoctype(const System::WideString DoctypeName, const System::WideString PublicId, const System::WideString SystemId, const System::WideString IntSubset);
	virtual void __fastcall WriteEndElement(const System::WideString TagName);
	virtual void __fastcall WriteEndPrefixMapping(const System::WideString Prefix);
	virtual void __fastcall WriteEntityRef(const System::WideString EntityName);
	virtual void __fastcall WriteCompleted();
	virtual void __fastcall WritePCDATA(const System::WideString Content, const bool CharRefGenerated);
	virtual void __fastcall WriteProcessingInstruction(const System::WideString Targ, const System::WideString AttribSequence);
	virtual void __fastcall WriteStartDocument(const System::WideString InputEnc, const System::WideString Version, const System::WideString EncName, TDomStandalone SdDl);
	virtual void __fastcall WriteStartDocumentFragment(const System::WideString EncName);
	virtual void __fastcall WriteStartElement(const System::WideString TagName);
	virtual void __fastcall WriteStartPrefixMapping(const System::WideString Prefix, const System::WideString Uri);
	
public:
	__fastcall virtual TXmlStandardDomReader(System::Classes::TComponent* AOwner);
	virtual bool __fastcall Parse(TDomNode* const SourceNode);
	__property TDomNode* ContextNode = {read=GetContextNode};
	
__published:
	__property bool IgnoreUnspecified = {read=FIgnoreUnspecified, write=FIgnoreUnspecified, nodefault};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TXmlStandardDomReader() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlCustomHandler : public TDomBaseComponent
{
	typedef TDomBaseComponent inherited;
	
protected:
	virtual void __fastcall SendErrorNotification(TXmlCustomReader* const Target, const TXmlErrorType XmlErrorType, const _di_IDomLocator Location, const System::WideString Code, const System::WideString Clue);
	
public:
	virtual void __fastcall ProcessSignal(TXmlSignal* const Signal) = 0 ;
public:
	/* TComponent.Create */ inline __fastcall virtual TXmlCustomHandler(System::Classes::TComponent* AOwner) : TDomBaseComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TXmlCustomHandler() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlStandardHandler : public TXmlCustomHandler
{
	typedef TXmlCustomHandler inherited;
	
protected:
	TXmlCustomHandler* FNextHandler;
	TXmlProcessingEvent FOnSignal;
	TXmlPostProcessingEvent FOnSignaled;
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	virtual void __fastcall ProcessSignal(TXmlSignal* const Signal);
	
__published:
	__property TXmlCustomHandler* NextHandler = {read=FNextHandler, write=FNextHandler};
	__property TXmlProcessingEvent OnSignal = {read=FOnSignal, write=FOnSignal};
	__property TXmlPostProcessingEvent OnSignaled = {read=FOnSignaled, write=FOnSignaled};
public:
	/* TComponent.Create */ inline __fastcall virtual TXmlStandardHandler(System::Classes::TComponent* AOwner) : TXmlCustomHandler(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TXmlStandardHandler() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlHandlerItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
protected:
	TXmlCustomHandler* FXmlHandler;
	TXmlCustomHandler* __fastcall GetXmlHandler();
	void __fastcall SetXmlHandler(TXmlCustomHandler* Value);
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property TXmlCustomHandler* XmlHandler = {read=GetXmlHandler, write=SetXmlHandler};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TXmlHandlerItem(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TXmlHandlerItem() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlHandlers : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TXmlHandlerItem* operator[](int Index) { return this->Items[Index]; }
	
private:
	TXmlDistributor* FDistributor;
	
protected:
	HIDESBASE virtual TXmlHandlerItem* __fastcall GetItem(int Index);
	HIDESBASE virtual void __fastcall SetItem(int Index, TXmlHandlerItem* Value);
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner();
	
public:
	__fastcall TXmlHandlers(TXmlDistributor* Distributor);
	HIDESBASE TXmlHandlerItem* __fastcall Add();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	TXmlHandlerItem* __fastcall FindHandlerItem(TXmlCustomHandler* AHandler);
	__property TXmlDistributor* Distributor = {read=FDistributor};
	__property TXmlHandlerItem* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TXmlHandlers() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlDistributor : public TXmlCustomHandler
{
	typedef TXmlCustomHandler inherited;
	
private:
	int FDisableCount;
	void __fastcall ReadData(System::Classes::TReader* Reader);
	void __fastcall WriteData(System::Classes::TWriter* Writer);
	
protected:
	TXmlHandlers* FNextHandlers;
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	void __fastcall SetNextHandlers(TXmlHandlers* const Value);
	
public:
	__fastcall virtual TXmlDistributor(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TXmlDistributor();
	virtual void __fastcall ProcessSignal(TXmlSignal* const Signal);
	
__published:
	__property TXmlHandlers* NextHandlers = {read=FNextHandlers, write=SetNextHandlers};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM TXmlActivityStatus : unsigned char { asInactive, asDocActive, asDocFragActive, asExtDtdActive, asIntDtdActive };

enum DECLSPEC_DENUM TXmlRootProcessingStatus : unsigned char { rsBeforeRoot, rsInRoot, rsAfterRoot };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlWFTestHandler : public TXmlCustomHandler
{
	typedef TXmlCustomHandler inherited;
	
protected:
	TXmlActivityStatus FActivityStatus;
	bool FDoctypeFound;
	TXmlCustomHandler* FNextHandler;
	Xml::Internal::Widestringutils::TUtilsWideStringList* FPrefixStack;
	TXmlRootProcessingStatus FRootProcessingStatus;
	Xml::Internal::Widestringutils::TUtilsWideStringList* FTagStack;
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall Reset();
	
public:
	__fastcall virtual TXmlWFTestHandler(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TXmlWFTestHandler();
	virtual void __fastcall ProcessSignal(TXmlSignal* const Signal);
	__property TXmlActivityStatus ActivityStatus = {read=FActivityStatus, nodefault};
	
__published:
	__property TXmlCustomHandler* NextHandler = {read=FNextHandler, write=FNextHandler};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlNamespaceSignalGenerator : public TXmlCustomHandler
{
	typedef TXmlCustomHandler inherited;
	
protected:
	System::Generics::Collections::TList__1<TXmlSignal*>* FAttributeSignals;
	System::WideString FElementName;
	TXmlCustomHandler* FNextHandler;
	bool FPrefixMapping;
	System::Generics::Collections::TList__1<Xml::Internal::Widestringutils::TUtilsWideStringList*>* FPrefixMappingStack;
	bool FStartElementIsOpen;
	bool FSuppressXmlns;
	virtual void __fastcall ClearPrefixMappingStack();
	void __fastcall CloseStartElement(TXmlCustomReader* const Sender, const _di_IDomLocator Locator);
	virtual void __fastcall ProcessAttributeSignal(TXmlAttributeSignal* const Signal);
	virtual void __fastcall ProcessStartElementSignal(TXmlStartElementSignal* const Signal);
	virtual void __fastcall WriteEndPrefixMapping(TXmlCustomReader* const Sender, const _di_IDomLocator Locator);
	virtual void __fastcall WriteStartPrefixMapping(TXmlCustomReader* const Sender, const _di_IDomLocator Locator, const System::WideString Prefix, const System::WideString Uri);
	virtual void __fastcall Reset();
	
public:
	__fastcall virtual TXmlNamespaceSignalGenerator(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TXmlNamespaceSignalGenerator();
	virtual void __fastcall ProcessSignal(TXmlSignal* const Signal);
	
__published:
	__property TXmlCustomHandler* NextHandler = {read=FNextHandler, write=FNextHandler};
	__property bool PrefixMapping = {read=FPrefixMapping, write=FPrefixMapping, default=1};
	__property bool SuppressXmlns = {read=FSuppressXmlns, write=FSuppressXmlns, default=0};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlDomBuilder : public TXmlCustomHandler
{
	typedef TXmlCustomHandler inherited;
	
private:
	bool FBuildIDList;
	TDomDocTypeDeclTreatment FDocTypeDeclTreatment;
	bool FErrorReportingEnabled;
	bool FKeepCDATASections;
	bool FKeepComments;
	bool FKeepEntityRefs;
	
protected:
	TDomNode* FRefNode;
	System::Generics::Collections::TDictionary__2<int,System::Generics::Collections::TPair__2<System::WideString,System::WideString> >* FPrefixUriList;
	System::WideString __fastcall GetUriListLastValue(System::WideString Name);
	virtual void __fastcall ProcessPCDATA(TXmlCustomReader* const Sender, const _di_IDomLocator Locator, const System::WideString Data, const bool CharRefGenerated);
	virtual void __fastcall Reset();
	virtual void __fastcall SetErrorReportingEnabled(const bool Value);
	
public:
	__fastcall virtual TXmlDomBuilder(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TXmlDomBuilder();
	virtual void __fastcall ProcessSignal(TXmlSignal* const Signal);
	__property TDomNode* ReferenceNode = {read=FRefNode, write=FRefNode};
	
__published:
	__property bool BuildIDList = {read=FBuildIDList, write=FBuildIDList, default=1};
	__property TDomDocTypeDeclTreatment DocTypeDeclTreatment = {read=FDocTypeDeclTreatment, write=FDocTypeDeclTreatment, default=1};
	__property bool ErrorReportingEnabled = {read=FErrorReportingEnabled, write=SetErrorReportingEnabled, default=1};
	__property bool KeepCDATASections = {read=FKeepCDATASections, write=FKeepCDATASections, default=1};
	__property bool KeepComments = {read=FKeepComments, write=FKeepComments, default=1};
	__property bool KeepEntityRefs = {read=FKeepEntityRefs, write=FKeepEntityRefs, default=1};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlDtdModelBuilder : public TXmlCustomHandler
{
	typedef TXmlCustomHandler inherited;
	
private:
	TDtdModel* FDtdModel;
	
protected:
	TXmlActivityStatus FActivityStatus;
	TDomStandalone FDocStandalone;
	bool FIgnoreDeclarations;
	virtual void __fastcall InsertMixedContent(TDtdElementDecl* const RefASElementDecl, const System::WideString ContSpec);
	virtual void __fastcall InsertChildrenContent(TDtdObject* const RefDtdObject, const System::WideString ContSpec);
	virtual void __fastcall SetDtdModel(TDtdModel* const Value);
	virtual void __fastcall Reset();
	
public:
	__fastcall virtual TXmlDtdModelBuilder(System::Classes::TComponent* AOwner);
	virtual void __fastcall ProcessSignal(TXmlSignal* const Signal);
	__property TXmlActivityStatus ActivityStatus = {read=FActivityStatus, nodefault};
	__property TDtdModel* DtdModel = {read=FDtdModel, write=SetDtdModel};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TXmlDtdModelBuilder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM Xml_Internal_Adomcore_4_3__621 : unsigned char { bomUTF8, bomUTF16, bomUCS2 };

typedef System::Set<Xml_Internal_Adomcore_4_3__621, Xml_Internal_Adomcore_4_3__621::bomUTF8, Xml_Internal_Adomcore_4_3__621::bomUCS2> TXmlBOMOpt;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlStreamBuilder : public TXmlCustomHandler
{
	typedef TXmlCustomHandler inherited;
	
private:
	bool FAttListDeclIsOpen;
	bool FStartElementIsOpen;
	int FByteCount;
	int FCharacterCount;
	int FColumnCount;
	System::WideString FCurrentAttListDeclName;
	System::UnicodeString FDefaultEncoding;
	bool FIncludeXmlDecl;
	int FLineFeedCount;
	int FTabCount;
	TXmlBOMOpt FUseByteOrderMark;
	TXmlOutputSource* FOutputSource;
	TDomSerializationEvent FOnAfterWrite;
	TDomSerializationEvent FOnBeforeWrite;
	void __fastcall CheckAttListDeclarationClosed(TXmlCustomReader* const Sender, const _di_IDomLocator Locator);
	void __fastcall CheckAttListDeclarationOpen(TXmlCustomReader* const Sender, const _di_IDomLocator Locator, const System::WideString ElementName);
	void __fastcall CheckStartElementClosed(TXmlCustomReader* const Sender, const _di_IDomLocator Locator, bool ElementIsEmpty);
	System::UnicodeString __fastcall GetCurrentEncoding();
	void __fastcall ResetCurrentEncoding();
	void __fastcall SetDefaultEncoding(const System::UnicodeString Value);
	void __fastcall SetOutputSource(TXmlOutputSource* const Value);
	bool __fastcall TrySetCurrentEncoding(const System::WideString Value);
	void __fastcall WriteWideString(const System::WideString S, const bool UseCharRefs);
	void __fastcall WriteAttributeDefinitionSignal(TXmlAttributeDefinitionSignal* const Signal);
	void __fastcall WriteAttributeSignal(TXmlAttributeSignal* const Signal);
	void __fastcall WriteCDATASignal(TXmlCDATASignal* const Signal);
	void __fastcall WriteCommentSignal(TXmlCommentSignal* const Signal);
	void __fastcall WriteDoctypeSignal(TXmlDoctypeSignal* const Signal);
	void __fastcall WriteElementTypeDeclarationSignal(TXmlElementTypeDeclarationSignal* const Signal);
	void __fastcall WriteEndElementSignal(TXmlEndElementSignal* const Signal);
	void __fastcall WriteEntityDeclarationSignal(TXmlEntityDeclarationSignal* const Signal);
	void __fastcall WriteEntityRefSignal(TXmlEntityRefSignal* const Signal);
	void __fastcall WriteCompletedSignal(TXmlCompletedSignal* const Signal);
	void __fastcall WriteNotationDeclarationSignal(TXmlNotationDeclarationSignal* const Signal);
	void __fastcall WriteParameterEntityDeclarationSignal(TXmlParameterEntityDeclarationSignal* const Signal);
	void __fastcall WritePCDATASignal(TXmlPCDATASignal* const Signal);
	void __fastcall WriteProcessingInstructionSignal(TXmlProcessingInstructionSignal* const Signal);
	void __fastcall WriteSkippedEntitySignal(TXmlSkippedEntitySignal* const Signal);
	void __fastcall WriteStartDocumentSignal(TXmlStartDocumentSignal* const Signal);
	void __fastcall WriteStartDocumentFragmentSignal(TXmlStartDocumentFragmentSignal* const Signal);
	void __fastcall WriteStartElementSignal(TXmlStartElementSignal* const Signal);
	void __fastcall WriteStartExtDtdSignal(TXmlStartExtDtdSignal* const Signal);
	void __fastcall WriteStartIntDtdSignal(TXmlStartIntDtdSignal* const Signal);
	
protected:
	int FOpenElementsCount;
	void __fastcall DoAfterWrite(const TDomPieceType PieceType, const _di_IDomLocator Locator);
	void __fastcall DoBeforeWrite(const TDomPieceType PieceType, const _di_IDomLocator Locator);
	virtual void __fastcall Reset();
	virtual void __fastcall SetIncludeXmlDecl(const bool Value);
	virtual void __fastcall SetUseByteOrderMark(const TXmlBOMOpt Value);
	virtual void __fastcall WriteByteOrderMark(TXmlCustomReader* const Sender, const _di_IDomLocator Locator, /* out */ int &ByteCount);
	virtual void __fastcall WriteWideStrings(TXmlCustomReader* const Sender, const _di_IDomLocator Locator, const System::WideString *XmlStrgs, const int XmlStrgs_High, const bool UseCharRefs);
	
public:
	__fastcall virtual TXmlStreamBuilder(System::Classes::TComponent* AOwner);
	virtual void __fastcall ProcessSignal(TXmlSignal* const Signal);
	__property int ByteCount = {read=FByteCount, nodefault};
	__property int CharacterCount = {read=FCharacterCount, nodefault};
	__property int ColumnCount = {read=FColumnCount, nodefault};
	__property System::UnicodeString CurrentEncoding = {read=GetCurrentEncoding};
	__property System::UnicodeString DefaultEncoding = {read=FDefaultEncoding, write=SetDefaultEncoding};
	__property int LineFeedCount = {read=FLineFeedCount, nodefault};
	__property TXmlOutputSource* OutputSource = {read=FOutputSource, write=SetOutputSource};
	__property int TabCount = {read=FTabCount, nodefault};
	
__published:
	__property TXmlBOMOpt UseByteOrderMark = {read=FUseByteOrderMark, write=SetUseByteOrderMark, default=6};
	__property bool IncludeXmlDecl = {read=FIncludeXmlDecl, write=SetIncludeXmlDecl, default=1};
	__property TDomSerializationEvent OnAfterWrite = {read=FOnAfterWrite, write=FOnAfterWrite};
	__property TDomSerializationEvent OnBeforeWrite = {read=FOnBeforeWrite, write=FOnBeforeWrite};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TXmlStreamBuilder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlStreamBuilderExt : public TXmlStreamBuilder
{
	typedef TXmlStreamBuilder inherited;
	
private:
	bool FIncludeXmlEnc;
	
public:
	__fastcall virtual TXmlStreamBuilderExt(System::Classes::TComponent* AOwner);
	
__published:
	__property bool IncludeXmlEnc = {read=FIncludeXmlEnc, write=FIncludeXmlEnc, default=1};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TXmlStreamBuilderExt() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlCustomParser : public TDomBaseComponent
{
	typedef TDomBaseComponent inherited;
	
private:
	TDomImplementation* FDOMImpl;
	bool FErrorReportingEnabled;
	
protected:
	virtual void __fastcall SetDomImpl(TDomImplementation* const Impl);
	virtual void __fastcall SetErrorReportingEnabled(const bool Value);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TXmlCustomParser(System::Classes::TComponent* AOwner);
	
__published:
	__property TDomImplementation* DOMImpl = {read=FDOMImpl, write=SetDomImpl};
	__property bool ErrorReportingEnabled = {read=FErrorReportingEnabled, write=SetErrorReportingEnabled, default=1};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TXmlCustomParser() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM TXmlParserAction : unsigned char { ACTION_APPEND_AS_CHILDREN, ACTION_INSERT_AFTER, ACTION_INSERT_BEFORE, ACTION_REPLACE, ACTION_REPLACE_CHILDREN };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXmlToDomParser : public TXmlCustomParser
{
	typedef TXmlCustomParser inherited;
	
private:
	bool __fastcall GetKeepCDATASections();
	bool __fastcall GetKeepComments();
	bool __fastcall GetKeepEntityRefs();
	void __fastcall SetKeepCDATASections(const bool Value);
	void __fastcall SetKeepComments(const bool Value);
	void __fastcall SetKeepEntityRefs(const bool Value);
	
protected:
	int FBufferSize;
	TXmlDomBuilder* FDocBuilder;
	TXmlStandardDocReader* FDocReader;
	TXmlWFTestHandler* FWFTestHandler;
	virtual void __fastcall CreateSubcomponents();
	virtual void __fastcall ParseFragment(TXmlSimpleInputSource* const InputSource, TDomDocumentFragment* const DocFrag);
	virtual bool __fastcall SendErrorNotification(const TXmlErrorType XmlErrorType);
	virtual void __fastcall SetBufferSize(const int Value);
	virtual void __fastcall SetDomImpl(TDomImplementation* const Impl);
	virtual void __fastcall SetErrorReportingEnabled(const bool Value);
	
public:
	__fastcall virtual TXmlToDomParser(System::Classes::TComponent* AOwner);
	virtual TDomDocument* __fastcall Parse(TXmlInputSource* const InputSource);
	virtual TDomDocument* __fastcall ParseFile(const System::Sysutils::TFileName Filename, const bool InclDecl);
	virtual TDomDocument* __fastcall ParseResource(const System::WideString BaseUri, System::WideString PublicId, System::WideString SystemId, const System::WideString Encoding, const bool InclDecl);
	virtual TDomNode* __fastcall ParseWithContext(TXmlInputSource* const InputSource, TDomNode* const ContextNode, const TXmlParserAction Action);
	
__published:
	__property int BufferSize = {read=FBufferSize, write=SetBufferSize, default=4096};
	__property bool KeepCDATASections = {read=GetKeepCDATASections, write=SetKeepCDATASections, default=1};
	__property bool KeepComments = {read=GetKeepComments, write=SetKeepComments, default=1};
	__property bool KeepEntityRefs = {read=GetKeepEntityRefs, write=SetKeepEntityRefs, default=1};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TXmlToDomParser() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDtdToDtdModelParser : public TXmlCustomParser
{
	typedef TXmlCustomParser inherited;
	
private:
	int FBufferSize;
	bool __fastcall GetXmlErrorDetected();
	bool __fastcall GetXmlFatalErrorDetected();
	
protected:
	TXmlDtdModelBuilder* FDtdModelBuilder;
	TXmlStandardDtdReader* FDtdReader;
	TXmlWFTestHandler* FWFTestHandler;
	virtual void __fastcall CreateSubcomponents();
	virtual TDtdModel* __fastcall GetTargetDtdModel();
	virtual bool __fastcall SendErrorNotification(const TXmlErrorType XmlErrorType);
	virtual void __fastcall SetBufferSize(const int Value);
	virtual void __fastcall SetDomImpl(TDomImplementation* const ADOMImpl);
	virtual void __fastcall SetErrorReportingEnabled(const bool Value);
	virtual void __fastcall SetTargetDtdModel(TDtdModel* const Value);
	
public:
	__fastcall virtual TDtdToDtdModelParser(System::Classes::TComponent* AOwner);
	virtual void __fastcall ParseDocTypeDecl(TDomDocumentTypeDecl* const DocTypeDecl, const bool ResolveExtEntities, const bool InclDecl);
	virtual void __fastcall ParseExtSubset(TXmlInputSource* const InputSource);
	virtual void __fastcall ParseIntSubset(TXmlSimpleInputSource* const InputSource, const TDomStandalone Standalone, const bool ResolveExtPEs);
	virtual void __fastcall Prepare();
	__property TDtdModel* TargetDtdModel = {read=GetTargetDtdModel, write=SetTargetDtdModel};
	__property bool XmlErrorDetected = {read=GetXmlErrorDetected, nodefault};
	__property bool XmlFatalErrorDetected = {read=GetXmlFatalErrorDetected, nodefault};
	
__published:
	__property int BufferSize = {read=FBufferSize, write=SetBufferSize, default=4096};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TDtdToDtdModelParser() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomToXmlParser : public TXmlCustomParser
{
	typedef TXmlCustomParser inherited;
	
private:
	TXmlStandardDomReader* FDomReader;
	int FBufferSize;
	TXmlStreamBuilder* FStreamBuilder;
	TXmlWFTestHandler* FWFTestHandler;
	Xml::Internal::Codecutilswin32::TCodecWriteLFOption FWriteLFOption;
	TDomSerializationEvent __fastcall GetOnAfterWrite();
	TDomSerializationEvent __fastcall GetOnBeforeWrite();
	bool __fastcall GetStrictErrorChecking();
	TXmlBOMOpt __fastcall GetUseByteOrderMark();
	void __fastcall SetOnAfterWrite(const TDomSerializationEvent Value);
	void __fastcall SetOnBeforeWrite(const TDomSerializationEvent Value);
	void __fastcall SetStrictErrorChecking(const bool Value);
	void __fastcall SetUseByteOrderMark(const TXmlBOMOpt Value);
	
protected:
	virtual bool __fastcall GetIgnoreUnspecified();
	virtual bool __fastcall GetIncludeXmlDecl();
	virtual void __fastcall SetBufferSize(const int Value);
	virtual void __fastcall SetDomImpl(TDomImplementation* const Impl);
	virtual void __fastcall SetErrorReportingEnabled(const bool Value);
	virtual void __fastcall SetIgnoreUnspecified(const bool Value);
	virtual void __fastcall SetIncludeXmlDecl(const bool Value);
	virtual void __fastcall SetWriteLFOption(const Xml::Internal::Codecutilswin32::TCodecWriteLFOption Value);
	__property TXmlStandardDomReader* DomReader = {read=FDomReader};
	__property TXmlStreamBuilder* StreamBuilder = {read=FStreamBuilder};
	__property TXmlWFTestHandler* WFTestHandler = {read=FWFTestHandler};
	
public:
	__fastcall virtual TDomToXmlParser(System::Classes::TComponent* AOwner);
	virtual bool __fastcall WriteToStream(TDomNode* const WNode, const System::UnicodeString Encoding, System::Classes::TStream* const Destination);
	virtual bool __fastcall WriteToString(TDomNode* const WNode, System::UnicodeString Encoding, /* out */ System::UnicodeString &S);
	virtual bool __fastcall WriteToWideString(TDomNode* const WNode, /* out */ System::WideString &S);
	
__published:
	__property int BufferSize = {read=FBufferSize, write=SetBufferSize, default=4096};
	__property bool IgnoreUnspecified = {read=GetIgnoreUnspecified, write=SetIgnoreUnspecified, nodefault};
	__property bool IncludeXmlDecl = {read=GetIncludeXmlDecl, write=SetIncludeXmlDecl, default=1};
	__property bool StrictErrorChecking = {read=GetStrictErrorChecking, write=SetStrictErrorChecking, default=0};
	__property TXmlBOMOpt UseByteOrderMark = {read=GetUseByteOrderMark, write=SetUseByteOrderMark, default=6};
	__property Xml::Internal::Codecutilswin32::TCodecWriteLFOption WriteLFOption = {read=FWriteLFOption, write=SetWriteLFOption, default=2};
	__property TDomSerializationEvent OnAfterWrite = {read=GetOnAfterWrite, write=SetOnAfterWrite};
	__property TDomSerializationEvent OnBeforeWrite = {read=GetOnBeforeWrite, write=SetOnBeforeWrite};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TDomToXmlParser() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomToXmlParserExt : public TDomToXmlParser
{
	typedef TDomToXmlParser inherited;
	
private:
	bool __fastcall GetIncludeXmlEnc();
	void __fastcall SetIncludeXmlEnc(const bool Value);
	
__published:
	__property bool IncludeXmlEnc = {read=GetIncludeXmlEnc, write=SetIncludeXmlEnc, default=1};
public:
	/* TDomToXmlParser.Create */ inline __fastcall virtual TDomToXmlParserExt(System::Classes::TComponent* AOwner) : TDomToXmlParser(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TDomToXmlParserExt() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM TDomXPathTokenType : unsigned char { XPATH_LEFT_PARENTHESIS_TOKEN, XPATH_RIGHT_PARENTHESIS_TOKEN, XPATH_LEFT_SQUARE_BRACKET_TOKEN, XPATH_RIGHT_SQUARE_BRACKET_TOKEN, XPATH_SINGLE_DOT_TOKEN, XPATH_DOUBLE_DOT_TOKEN, XPATH_COMMERCIAL_AT_TOKEN, XPATH_COMMA_TOKEN, XPATH_DOUBLE_COLON_TOKEN, XPATH_NAME_TEST_TOKEN, XPATH_NODE_TYPE_COMMENT_TOKEN, XPATH_NODE_TYPE_TEXT_TOKEN, XPATH_NODE_TYPE_PI_TOKEN, XPATH_NODE_TYPE_NODE_TOKEN, XPATH_AND_OPERATOR_TOKEN, XPATH_OR_OPERATOR_TOKEN, XPATH_MOD_OPERATOR_TOKEN, XPATH_DIV_OPERATOR_TOKEN, XPATH_MULTIPLY_OPERATOR_TOKEN, XPATH_SLASH_OPERATOR_TOKEN, XPATH_SHEFFER_STROKE_OPERATOR_TOKEN, XPATH_PLUS_OPERATOR_TOKEN, XPATH_MINUS_OPERATOR_TOKEN, XPATH_IS_EQUAL_OPERATOR_TOKEN, XPATH_IS_NOT_EQUAL_OPERATOR_TOKEN, 
	XPATH_LESS_THAN_OPERATOR_TOKEN, XPATH_LESS_THAN_OR_EQUAL_OPERATOR_TOKEN, XPATH_GREATER_THAN_OPERATOR_TOKEN, XPATH_GREATER_THAN_OR_EQUAL_OPERATOR_TOKEN, XPATH_FUNCTION_NAME_TOKEN, XPATH_AXIS_NAME_ANCESTOR_TOKEN, XPATH_AXIS_NAME_ANCESTOR_OR_SELF_TOKEN, XPATH_AXIS_NAME_ATTRIBUTE_TOKEN, XPATH_AXIS_NAME_CHILD_TOKEN, XPATH_AXIS_NAME_DESCENDANT_TOKEN, XPATH_AXIS_NAME_DESCENDANT_OR_SELF_TOKEN, XPATH_AXIS_NAME_FOLLOWING_TOKEN, XPATH_AXIS_NAME_FOLLOWING_SIBLING_TOKEN, XPATH_AXIS_NAME_NAMESPACE_TOKEN, XPATH_AXIS_NAME_PARENT_TOKEN, XPATH_AXIS_NAME_PRECEDING_TOKEN, XPATH_AXIS_NAME_PRECEDING_SIBLING_TOKEN, XPATH_AXIS_NAME_SELF_TOKEN, XPATH_LITERAL_TOKEN, XPATH_NUMBER_TOKEN, XPATH_VARIABLE_REFERENCE_TOKEN, XPATH_END_OF_TEXT_TOKEN, XPATH_INVALID_TOKEN };

enum DECLSPEC_DENUM TDomXPathAxisType : unsigned char { XPATH_FORWARD_AXIS, XPATH_REVERSE_AXIS };

typedef TDomXPathCustomResult* __fastcall (*TDomXPathFunction)(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);

enum DECLSPEC_DENUM TDomXPathSlashStatus : unsigned char { SL_NO_DOUBLE_SLASH, SL_XPATH_AXIS_NAME_DESCENDANT_OR_SELF_TOKEN_FOLLOWS, SL_XPATH_DOUBLE_COLON_TOKEN_FOLLOWS, SL_XPATH_NODE_TYPE_NODE_TOKEN_FOLLOWS, SL_XPATH_LEFT_PARENTHESIS_FOLLOWS, SL_XPATH_RIGHT_PARENTHESIS_FOLLOWS, SL_XPATH_SLASH_OPERATOR_TOKEN_FOLLLOWS };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathTokenizer : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	bool FCacheIsActive;
	TDomXPathSlashStatus FDoubleSlashStatus;
	System::WideString FExpression;
	TDomXPathTokenType FLastSymbol;
	int FPosition;
	int FPositionCache;
	TDomXPathTokenType FSymbolCache;
	System::WideString FValueCache;
	virtual bool __fastcall DoubleColonFollows();
	virtual bool __fastcall GetNextWideChar(/* out */ System::WideChar &S);
	virtual bool __fastcall LeftParanthesisFollows();
	virtual bool __fastcall LookAheadNextWideChar(/* out */ System::WideChar &S);
	
public:
	__fastcall virtual TDomXPathTokenizer(const System::WideString Expression, const System::WideString XPathVersion);
	virtual bool __fastcall IsFollowing(const TDomXPathTokenType Symbol);
	virtual void __fastcall Read(/* out */ TDomXPathTokenType &Symbol, /* out */ System::WideString &Value, /* out */ int &Position);
	virtual void __fastcall Reset();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDomXPathTokenizer() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathCustomResult : public Xml::Internal::Treeutils::TCustomOwnedNode
{
	typedef Xml::Internal::Treeutils::TCustomOwnedNode inherited;
	
protected:
	virtual TDomXPathAxisType __fastcall GetAxisType();
	virtual void __fastcall SetAxisType(const TDomXPathAxisType Value);
	
public:
	__fastcall TDomXPathCustomResult();
	virtual bool __fastcall AsBoolean() = 0 ;
	virtual double __fastcall AsNumber() = 0 ;
	virtual System::WideString __fastcall AsWideString() = 0 ;
	HIDESBASE virtual TDomNode* __fastcall Item(const int Index);
	virtual int __fastcall Length();
	virtual TDomXPathResultType __fastcall ResultType() = 0 ;
	__property TDomXPathAxisType AxisType = {read=GetAxisType, write=SetAxisType, nodefault};
public:
	/* TCustomOwnedNode.Destroy */ inline __fastcall virtual ~TDomXPathCustomResult() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathNodeSetResult : public TDomXPathCustomResult
{
	typedef TDomXPathCustomResult inherited;
	
private:
	TDomXPathNamespace* __fastcall CreateXPathNamespace(TDomElement* const AOwnerElement, const System::WideString ANamespaceUri, const System::WideString APrefix);
	
protected:
	TDomXPathAxisType FAxisType;
	System::Generics::Collections::TList__1<TDomNode*>* FList;
	virtual void __fastcall AddXPathNamespace(TDomElement* const AOwnerElement, const System::WideString ANamespaceUri, const System::WideString APrefix);
	virtual TDomXPathAxisType __fastcall GetAxisType();
	virtual void __fastcall Insert(const int Index, TDomNode* const Node);
	virtual void __fastcall SetAxisType(const TDomXPathAxisType Value);
	
public:
	__fastcall virtual TDomXPathNodeSetResult();
	__fastcall virtual ~TDomXPathNodeSetResult();
	virtual void __fastcall Add(TDomNode* const Node);
	virtual void __fastcall AddSubtree(TDomNode* const Node);
	virtual bool __fastcall AsBoolean();
	virtual double __fastcall AsNumber();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual System::WideString __fastcall AsWideString();
	HIDESBASE virtual void __fastcall Clear();
	virtual void __fastcall Delete(const int Index);
	virtual TDomNode* __fastcall Item(const int Index);
	virtual int __fastcall Length();
	virtual void __fastcall Merge(TDomXPathNodeSetResult* const NodeSet);
	virtual TDomXPathResultType __fastcall ResultType();
	virtual void __fastcall Sort();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathBooleanResult : public TDomXPathCustomResult
{
	typedef TDomXPathCustomResult inherited;
	
private:
	bool FBooleanValue;
	
public:
	__fastcall virtual TDomXPathBooleanResult(const bool ABooleanValue);
	virtual bool __fastcall AsBoolean();
	virtual double __fastcall AsNumber();
	virtual System::WideString __fastcall AsWideString();
	virtual TDomXPathResultType __fastcall ResultType();
public:
	/* TCustomOwnedNode.Destroy */ inline __fastcall virtual ~TDomXPathBooleanResult() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TDomXPathNumberResult : public TDomXPathCustomResult
{
	typedef TDomXPathCustomResult inherited;
	
private:
	double FNumberValue;
	
public:
	__fastcall virtual TDomXPathNumberResult(const double ANumberValue);
	virtual bool __fastcall AsBoolean();
	virtual double __fastcall AsNumber();
	virtual System::WideString __fastcall AsWideString();
	virtual TDomXPathResultType __fastcall ResultType();
public:
	/* TCustomOwnedNode.Destroy */ inline __fastcall virtual ~TDomXPathNumberResult() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathStringResult : public TDomXPathCustomResult
{
	typedef TDomXPathCustomResult inherited;
	
private:
	System::WideString FStringValue;
	
public:
	__fastcall virtual TDomXPathStringResult(const System::WideString AStringValue);
	virtual bool __fastcall AsBoolean();
	virtual double __fastcall AsNumber();
	virtual System::WideString __fastcall AsWideString();
	virtual TDomXPathResultType __fastcall ResultType();
public:
	/* TCustomOwnedNode.Destroy */ inline __fastcall virtual ~TDomXPathStringResult() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathSyntaxTree : public Xml::Internal::Treeutils::TCustomOwnedObject
{
	typedef Xml::Internal::Treeutils::TCustomOwnedObject inherited;
	
private:
	TXPathExpression* FOwnerXPathExpression;
	
protected:
	TDomXPathExpr* FRootExpr;
	virtual TDomXPathSyntaxNode* __fastcall CreateSyntaxNode(const TDomXPathTokenType Symbol, const System::WideString Value);
	virtual TDomNode* __fastcall GetContextNode();
	virtual bool __fastcall GetIsPrepared();
	System::WideString __fastcall LookupNamespaceURI(const System::WideString APrefix);
	
public:
	__fastcall TDomXPathSyntaxTree(TXPathExpression* AOwner);
	virtual void __fastcall Clear();
	virtual TDomXPathCustomResult* __fastcall Evaluate();
	virtual bool __fastcall Prepare(const System::WideString Expression);
	__property TDomNode* ContextNode = {read=GetContextNode};
	__property bool IsPrepared = {read=GetIsPrepared, nodefault};
	__property TXPathExpression* OwnerXPathExpression = {read=FOwnerXPathExpression};
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathSyntaxTree() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TXPathExpression : public TDomBaseComponent
{
	typedef TDomBaseComponent inherited;
	
private:
	TDomXPathLookupNamespaceURIEvent FOnLookupNamespaceURI;
	
protected:
	TDomNode* FContextNode;
	TDomTrinarean FIsValid;
	System::WideString FExpression;
	TDomXPathSyntaxTree* FSyntaxTree;
	TDomXPathCustomResult* FXPathResult;
	System::WideString __fastcall LookupNamespaceURI(const System::WideString APrefix);
	virtual void __fastcall SetContextNode(TDomNode* const Node);
	virtual void __fastcall SetExpression(const System::WideString S);
	
public:
	__fastcall virtual TXPathExpression(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TXPathExpression();
	virtual bool __fastcall Evaluate();
	virtual bool __fastcall HasNodeSetResult();
	virtual bool __fastcall Prepare();
	virtual TDomXPathAxisType __fastcall ResultAxisType();
	virtual bool __fastcall ResultAsBoolean();
	virtual double __fastcall ResultAsNumber();
	virtual System::WideString __fastcall ResultAsWideString();
	virtual TDomNode* __fastcall ResultNode(const int Index);
	virtual int __fastcall ResultLength();
	__property TDomNode* ContextNode = {read=FContextNode, write=SetContextNode};
	__property TDomTrinarean IsValid = {read=FIsValid, nodefault};
	
__published:
	__property System::WideString Expression = {read=FExpression, write=SetExpression};
	__property TDomXPathLookupNamespaceURIEvent OnLookupNamespaceURI = {read=FOnLookupNamespaceURI, write=FOnLookupNamespaceURI};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathSyntaxNodeStack : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* FNodeList;
	
protected:
	virtual int __fastcall GetLength();
	
public:
	__fastcall virtual TDomXPathSyntaxNodeStack();
	__fastcall virtual ~TDomXPathSyntaxNodeStack();
	virtual void __fastcall Clear();
	virtual TDomXPathSyntaxNode* __fastcall Peek(int Offset);
	virtual TDomXPathSyntaxNode* __fastcall Pop();
	virtual void __fastcall Push(TDomXPathSyntaxNode* Node);
	__property int Length = {read=GetLength, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathSyntaxNode : public Xml::Internal::Treeutils::TCustomOwnedObject
{
	typedef Xml::Internal::Treeutils::TCustomOwnedObject inherited;
	
protected:
	TDomXPathSyntaxNode* FLeft;
	TDomXPathSyntaxNode* FRight;
	System::WideString FValue;
	virtual TDomXPathSyntaxTree* __fastcall GetOwnerSyntaxTree();
	System::WideString __fastcall LookupNamespaceURI(const System::WideString APrefix);
	
public:
	__fastcall virtual TDomXPathSyntaxNode(TDomXPathSyntaxTree* const AOwner, const System::WideString Value);
	__property TDomXPathSyntaxNode* Left = {read=FLeft, write=FLeft};
	__property TDomXPathSyntaxTree* OwnerSyntaxTree = {read=GetOwnerSyntaxTree};
	__property TDomXPathSyntaxNode* Right = {read=FRight, write=FRight};
	__property System::WideString Value = {read=FValue};
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathSyntaxNode() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathAbsoluteLocationPath : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathAbsoluteLocationPath(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathAbsoluteLocationPath() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathStep : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	virtual bool __fastcall AddStep(TDomXPathStep* const Step);
	virtual TDomXPathNodeSetResult* __fastcall Evaluate(TDomXPathNodeSetResult* const OldSnapshotResult);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathStep(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathStep() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathCustomAxisName : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
protected:
	TDomXPathAxisType FAxisType;
	TDomNodeType FPrincipalNodeType;
	virtual TDomXPathNodeSetResult* __fastcall GetAxisNodeSnapshot(TDomNode* const ContextNode) = 0 ;
	
public:
	__fastcall virtual TDomXPathCustomAxisName(TDomXPathSyntaxTree* const AOwner, const System::WideString Value);
	virtual TDomXPathNodeSetResult* __fastcall Evaluate(TDomXPathNodeSetResult* const OldSnapshotResult);
	__property TDomXPathAxisType AxisType = {read=FAxisType, nodefault};
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathCustomAxisName() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathAxisNameAncestor : public TDomXPathCustomAxisName
{
	typedef TDomXPathCustomAxisName inherited;
	
protected:
	virtual TDomXPathNodeSetResult* __fastcall GetAxisNodeSnapshot(TDomNode* const ContextNode);
	
public:
	__fastcall virtual TDomXPathAxisNameAncestor(TDomXPathSyntaxTree* const AOwner, const System::WideString Value);
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathAxisNameAncestor() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathAxisNameAncestorOrSelf : public TDomXPathCustomAxisName
{
	typedef TDomXPathCustomAxisName inherited;
	
protected:
	virtual TDomXPathNodeSetResult* __fastcall GetAxisNodeSnapshot(TDomNode* const ContextNode);
	
public:
	__fastcall virtual TDomXPathAxisNameAncestorOrSelf(TDomXPathSyntaxTree* const AOwner, const System::WideString Value);
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathAxisNameAncestorOrSelf() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathAxisNameAttribute : public TDomXPathCustomAxisName
{
	typedef TDomXPathCustomAxisName inherited;
	
protected:
	virtual TDomXPathNodeSetResult* __fastcall GetAxisNodeSnapshot(TDomNode* const ContextNode);
	
public:
	__fastcall virtual TDomXPathAxisNameAttribute(TDomXPathSyntaxTree* const AOwner, const System::WideString Value);
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathAxisNameAttribute() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathAxisNameChild : public TDomXPathCustomAxisName
{
	typedef TDomXPathCustomAxisName inherited;
	
protected:
	virtual TDomXPathNodeSetResult* __fastcall GetAxisNodeSnapshot(TDomNode* const ContextNode);
public:
	/* TDomXPathCustomAxisName.Create */ inline __fastcall virtual TDomXPathAxisNameChild(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathCustomAxisName(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathAxisNameChild() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathAxisNameDescendant : public TDomXPathCustomAxisName
{
	typedef TDomXPathCustomAxisName inherited;
	
protected:
	virtual TDomXPathNodeSetResult* __fastcall GetAxisNodeSnapshot(TDomNode* const ContextNode);
public:
	/* TDomXPathCustomAxisName.Create */ inline __fastcall virtual TDomXPathAxisNameDescendant(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathCustomAxisName(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathAxisNameDescendant() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathAxisNameDescendantOrSelf : public TDomXPathCustomAxisName
{
	typedef TDomXPathCustomAxisName inherited;
	
protected:
	virtual TDomXPathNodeSetResult* __fastcall GetAxisNodeSnapshot(TDomNode* const ContextNode);
public:
	/* TDomXPathCustomAxisName.Create */ inline __fastcall virtual TDomXPathAxisNameDescendantOrSelf(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathCustomAxisName(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathAxisNameDescendantOrSelf() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathAxisNameFollowing : public TDomXPathCustomAxisName
{
	typedef TDomXPathCustomAxisName inherited;
	
protected:
	virtual TDomXPathNodeSetResult* __fastcall GetAxisNodeSnapshot(TDomNode* const ContextNode);
public:
	/* TDomXPathCustomAxisName.Create */ inline __fastcall virtual TDomXPathAxisNameFollowing(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathCustomAxisName(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathAxisNameFollowing() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathAxisNameFollowingSibling : public TDomXPathCustomAxisName
{
	typedef TDomXPathCustomAxisName inherited;
	
protected:
	virtual TDomXPathNodeSetResult* __fastcall GetAxisNodeSnapshot(TDomNode* const ContextNode);
public:
	/* TDomXPathCustomAxisName.Create */ inline __fastcall virtual TDomXPathAxisNameFollowingSibling(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathCustomAxisName(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathAxisNameFollowingSibling() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathAxisNameNamespace : public TDomXPathCustomAxisName
{
	typedef TDomXPathCustomAxisName inherited;
	
protected:
	virtual TDomXPathNodeSetResult* __fastcall GetAxisNodeSnapshot(TDomNode* const ContextNode);
	
public:
	__fastcall virtual TDomXPathAxisNameNamespace(TDomXPathSyntaxTree* const AOwner, const System::WideString Value);
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathAxisNameNamespace() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathAxisNameParent : public TDomXPathCustomAxisName
{
	typedef TDomXPathCustomAxisName inherited;
	
protected:
	virtual TDomXPathNodeSetResult* __fastcall GetAxisNodeSnapshot(TDomNode* const ContextNode);
public:
	/* TDomXPathCustomAxisName.Create */ inline __fastcall virtual TDomXPathAxisNameParent(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathCustomAxisName(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathAxisNameParent() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathAxisNamePreceding : public TDomXPathCustomAxisName
{
	typedef TDomXPathCustomAxisName inherited;
	
protected:
	virtual TDomXPathNodeSetResult* __fastcall GetAxisNodeSnapshot(TDomNode* const ContextNode);
	
public:
	__fastcall virtual TDomXPathAxisNamePreceding(TDomXPathSyntaxTree* const AOwner, const System::WideString Value);
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathAxisNamePreceding() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathAxisNamePrecedingSibling : public TDomXPathCustomAxisName
{
	typedef TDomXPathCustomAxisName inherited;
	
protected:
	virtual TDomXPathNodeSetResult* __fastcall GetAxisNodeSnapshot(TDomNode* const ContextNode);
	
public:
	__fastcall virtual TDomXPathAxisNamePrecedingSibling(TDomXPathSyntaxTree* const AOwner, const System::WideString Value);
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathAxisNamePrecedingSibling() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathAxisNameSelf : public TDomXPathCustomAxisName
{
	typedef TDomXPathCustomAxisName inherited;
	
protected:
	virtual TDomXPathNodeSetResult* __fastcall GetAxisNodeSnapshot(TDomNode* const ContextNode);
public:
	/* TDomXPathCustomAxisName.Create */ inline __fastcall virtual TDomXPathAxisNameSelf(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathCustomAxisName(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathAxisNameSelf() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathNodeTest : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	virtual TDomXPathNodeSetResult* __fastcall Evaluate(TDomXPathNodeSetResult* const oldsnapshotResult, const TDomNodeType PrincipalNodeType);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathNodeTest(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathNodeTest() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathPredicate : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	virtual TDomXPathNodeSetResult* __fastcall Evaluate(TDomXPathNodeSetResult* const OldSnapshotResult);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathPredicate(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathPredicate() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathExpr : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathExpr(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathExpr() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathPrimaryExpr : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathPrimaryExpr(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathPrimaryExpr() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathFunctionCall : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
private:
	System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* FArguments;
	
protected:
	System::WideString FPrefix;
	System::WideString FLocalName;
	TDomXPathFunction FXPathFunction;
	virtual System::WideString __fastcall GetFunctionName();
	virtual void __fastcall SetFunctionName(const System::WideString AFunctionName);
	
public:
	__fastcall virtual TDomXPathFunctionCall(TDomXPathSyntaxTree* const AOwner, const System::WideString Value);
	__fastcall virtual ~TDomXPathFunctionCall();
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize);
	__property System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* Arguments = {read=FArguments};
	__property System::WideString FunctionName = {read=GetFunctionName, write=SetFunctionName};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathUnionExpr : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathUnionExpr(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathUnionExpr() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathPathExpr : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	virtual bool __fastcall AddStep(TDomXPathStep* const Step);
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathPathExpr(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathPathExpr() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathFilterExpr : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathFilterExpr(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathFilterExpr() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathOrExpr : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathOrExpr(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathOrExpr() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathAndExpr : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathAndExpr(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathAndExpr() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathEqualityExpr : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize) = 0 ;
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathEqualityExpr(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathEqualityExpr() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathIsEqualExpr : public TDomXPathEqualityExpr
{
	typedef TDomXPathEqualityExpr inherited;
	
public:
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathIsEqualExpr(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathEqualityExpr(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathIsEqualExpr() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathIsNotEqualExpr : public TDomXPathEqualityExpr
{
	typedef TDomXPathEqualityExpr inherited;
	
public:
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathIsNotEqualExpr(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathEqualityExpr(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathIsNotEqualExpr() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathRelationalExpr : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize) = 0 ;
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathRelationalExpr(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathRelationalExpr() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathLessThanExpr : public TDomXPathRelationalExpr
{
	typedef TDomXPathRelationalExpr inherited;
	
public:
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathLessThanExpr(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathRelationalExpr(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathLessThanExpr() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathLessThanOrEqualExpr : public TDomXPathRelationalExpr
{
	typedef TDomXPathRelationalExpr inherited;
	
__published:
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathLessThanOrEqualExpr(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathRelationalExpr(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathLessThanOrEqualExpr() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathGreaterThanExpr : public TDomXPathRelationalExpr
{
	typedef TDomXPathRelationalExpr inherited;
	
public:
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathGreaterThanExpr(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathRelationalExpr(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathGreaterThanExpr() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathGreaterThanOrEqualExpr : public TDomXPathRelationalExpr
{
	typedef TDomXPathRelationalExpr inherited;
	
public:
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathGreaterThanOrEqualExpr(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathRelationalExpr(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathGreaterThanOrEqualExpr() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathAdditiveExpr : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize) = 0 ;
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathAdditiveExpr(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathAdditiveExpr() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathPlusExpr : public TDomXPathAdditiveExpr
{
	typedef TDomXPathAdditiveExpr inherited;
	
public:
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathPlusExpr(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathAdditiveExpr(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathPlusExpr() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathMinusExpr : public TDomXPathAdditiveExpr
{
	typedef TDomXPathAdditiveExpr inherited;
	
public:
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathMinusExpr(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathAdditiveExpr(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathMinusExpr() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathMultiplicativeExpr : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize) = 0 ;
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathMultiplicativeExpr(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathMultiplicativeExpr() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathMultiplyExpr : public TDomXPathMultiplicativeExpr
{
	typedef TDomXPathMultiplicativeExpr inherited;
	
public:
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathMultiplyExpr(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathMultiplicativeExpr(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathMultiplyExpr() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathDivExpr : public TDomXPathMultiplicativeExpr
{
	typedef TDomXPathMultiplicativeExpr inherited;
	
public:
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathDivExpr(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathMultiplicativeExpr(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathDivExpr() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathModExpr : public TDomXPathMultiplicativeExpr
{
	typedef TDomXPathMultiplicativeExpr inherited;
	
public:
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathModExpr(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathMultiplicativeExpr(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathModExpr() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathUnaryExpr : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	virtual TDomXPathCustomResult* __fastcall Evaluate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathUnaryExpr(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathUnaryExpr() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathLeftParenthesis : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathLeftParenthesis(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathLeftParenthesis() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathRightParenthesis : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathRightParenthesis(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathRightParenthesis() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathLeftSquareBracket : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathLeftSquareBracket(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathLeftSquareBracket() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathRightSquareBracket : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathRightSquareBracket(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathRightSquareBracket() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathSingleDot : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathSingleDot(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathSingleDot() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathDoubleDot : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathDoubleDot(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathDoubleDot() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathCommercialAt : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathCommercialAt(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathCommercialAt() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathComma : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathComma(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathComma() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathDoubleColon : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathDoubleColon(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathDoubleColon() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathLiteral : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	virtual TDomXPathCustomResult* __fastcall Evaluate();
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathLiteral(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathLiteral() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathNumber : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	virtual TDomXPathCustomResult* __fastcall Evaluate();
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathNumber(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathNumber() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathSlashOperator : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathSlashOperator(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathSlashOperator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathShefferStrokeOperator : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathShefferStrokeOperator(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathShefferStrokeOperator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathPlusOperator : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathPlusOperator(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathPlusOperator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathMinusOperator : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathMinusOperator(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathMinusOperator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathIsEqualOperator : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathIsEqualOperator(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathIsEqualOperator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathIsNotEqualOperator : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathIsNotEqualOperator(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathIsNotEqualOperator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathLessThanOperator : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathLessThanOperator(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathLessThanOperator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathLessThanOrEqualOperator : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathLessThanOrEqualOperator(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathLessThanOrEqualOperator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathGreaterThanOperator : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathGreaterThanOperator(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathGreaterThanOperator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathGreaterThanOrEqualOperator : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathGreaterThanOrEqualOperator(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathGreaterThanOrEqualOperator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathAndOperator : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathAndOperator(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathAndOperator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathOrOperator : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathOrOperator(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathOrOperator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathModOperator : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathModOperator(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathModOperator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathDivOperator : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathDivOperator(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathDivOperator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathMultiplyOperator : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathMultiplyOperator(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathMultiplyOperator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathFunctionName : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathFunctionName(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathFunctionName() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathVariableReference : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
protected:
	System::WideString FPrefix;
	System::WideString FLocalName;
	
public:
	__fastcall virtual TDomXPathVariableReference(TDomXPathSyntaxTree* const AOwner, const System::WideString Value);
	virtual TDomXPathCustomResult* __fastcall Evaluate();
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathVariableReference() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathNameTest : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
protected:
	System::WideString FPrefix;
	System::WideString FLocalName;
	
public:
	__fastcall virtual TDomXPathNameTest(TDomXPathSyntaxTree* const AOwner, const System::WideString Value);
	virtual TDomXPathNodeSetResult* __fastcall Evaluate(TDomXPathNodeSetResult* const OldSnapshotResult, const TDomNodeType PrincipalNodeType);
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathNameTest() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathNodeTypeComment : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	virtual TDomXPathNodeSetResult* __fastcall Evaluate(TDomXPathNodeSetResult* const OldSnapshotResult);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathNodeTypeComment(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathNodeTypeComment() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathNodeTypeNode : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathNodeTypeNode(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathNodeTypeNode() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathNodeTypePI : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	virtual TDomXPathNodeSetResult* __fastcall Evaluate(TDomXPathNodeSetResult* const OldSnapshotResult);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathNodeTypePI(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathNodeTypePI() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDomXPathNodeTypeText : public TDomXPathSyntaxNode
{
	typedef TDomXPathSyntaxNode inherited;
	
public:
	virtual TDomXPathNodeSetResult* __fastcall Evaluate(TDomXPathNodeSetResult* const OldSnapshotResult);
public:
	/* TDomXPathSyntaxNode.Create */ inline __fastcall virtual TDomXPathNodeTypeText(TDomXPathSyntaxTree* const AOwner, const System::WideString Value) : TDomXPathSyntaxNode(AOwner, Value) { }
	
public:
	/* TCustomOwnedObject.Destroy */ inline __fastcall virtual ~TDomXPathNodeTypeText() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TXmlErrorTypes ET_WARNINGS;
extern DELPHI_PACKAGE TXmlErrorTypes ET_ERRORS;
extern DELPHI_PACKAGE TXmlErrorTypes ET_FATAL_ERRORS;
extern DELPHI_PACKAGE TXmlErrorTypes ET_NAMESPACE_FATAL_ERRORS;
extern DELPHI_PACKAGE TDomWhatToShow SHOW_ALL;
static constexpr int AS_UNBOUNDED = int(2147483647);
extern DELPHI_PACKAGE TDomXPathResultTypes XPATH_ANY_TYPE;
extern DELPHI_PACKAGE System::WideString __fastcall XmlReplaceQuotes(const System::WideString Source);
extern DELPHI_PACKAGE void __fastcall XmlTruncRoundBrackets(const System::WideString Source, System::WideString &Content, /* out */ bool &Error);
extern DELPHI_PACKAGE System::WideString __fastcall NormalizeSpace(const System::WideString S);
extern DELPHI_PACKAGE System::WideString __fastcall NormalizeWhiteSpace(const System::WideString S);
extern DELPHI_PACKAGE System::WideString __fastcall TrimWhitespace(const System::WideString S);
extern DELPHI_PACKAGE System::WideString __fastcall TrimWhitespaceLeft(const System::WideString S);
extern DELPHI_PACKAGE System::WideString __fastcall TrimWhitespaceRight(const System::WideString S);
extern DELPHI_PACKAGE System::WideString __fastcall XmlExtractPrefix(const System::WideString QualifiedName);
extern DELPHI_PACKAGE System::WideString __fastcall XmlExtractLocalName(const System::WideString QualifiedName);
extern DELPHI_PACKAGE bool __fastcall XmlExtractPrefixAndLocalName(const System::WideString QualifiedName, /* out */ System::WideString &Prefix, /* out */ System::WideString &LocalName);
extern DELPHI_PACKAGE System::WideString __fastcall EscapeDelimiters(const System::WideString S);
extern DELPHI_PACKAGE System::WideString __fastcall ResolveCharRefs(const System::WideString S);
extern DELPHI_PACKAGE int __fastcall XmlCharRefToInt(const System::WideString S);
extern DELPHI_PACKAGE System::WideString __fastcall XmlCharRefToStr(const System::WideString S);
#ifndef __aarch64__
extern DELPHI_PACKAGE System::WideString __fastcall XmlIntToCharRef(const int Value);
extern DELPHI_PACKAGE System::WideString __fastcall XmlIntToCharRefHex(const int Value);
#else /* __aarch64__ */
extern DELPHI_PACKAGE System::WideString __fastcall XmlIntToCharRef(const long Value);
extern DELPHI_PACKAGE System::WideString __fastcall XmlIntToCharRefHex(const long Value);
#endif /* __aarch64__ */
extern DELPHI_PACKAGE double __fastcall XPathRound(const double D);
extern DELPHI_PACKAGE double __fastcall XPathWideStringToNumber(const System::WideString S);
extern DELPHI_PACKAGE TDomXPathBooleanResult* __fastcall XPathBooleanFunc(TDomXPathCustomResult* const oldResult);
extern DELPHI_PACKAGE TDomXPathNumberResult* __fastcall XPathNumberFunc(TDomXPathCustomResult* const oldResult);
extern DELPHI_PACKAGE TDomXPathStringResult* __fastcall XPathStringFunc(TDomXPathCustomResult* const oldResult);
extern DELPHI_PACKAGE __int64 __fastcall HexToInt64(const System::WideString Hex);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionLast(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionPosition(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionCount(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionId(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionLocalName(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionNamespaceUri(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionName(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionString(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionConcat(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionStartsWith(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionContains(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionSubstringBefore(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionSubstringAfter(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionSubstring(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionStringLength(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionNormalizeSpace(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionTranslate(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionBoolean(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionNot(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionTrue(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionFalse(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionLang(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionNumber(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionSum(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionFloor(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionCeiling(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
extern DELPHI_PACKAGE TDomXPathCustomResult* __fastcall XPathFunctionRound(TDomNode* const ContextNode, const int ContextPosition, const int ContextSize, System::Generics::Collections::TList__1<TDomXPathSyntaxNode*>* const Arguments);
}	/* namespace Adomcore_4_3 */
}	/* namespace Internal */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_INTERNAL_ADOMCORE_4_3)
using namespace Xml::Internal::Adomcore_4_3;
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
#endif	// Xml_Internal_Adomcore_4_3HPP
