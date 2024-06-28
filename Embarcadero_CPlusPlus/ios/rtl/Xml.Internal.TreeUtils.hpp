// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.Internal.TreeUtils.pas' rev: 34.00 (iOS)

#ifndef Xml_Internal_TreeutilsHPP
#define Xml_Internal_TreeutilsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Internal
{
namespace Treeutils
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EHierarchyRequestError;
class DELPHICLASS ENoModificationAllowedError;
class DELPHICLASS ENotAssignedError;
class DELPHICLASS ENotFoundError;
class DELPHICLASS EWrongOwnerError;
class DELPHICLASS TCustomOwnedObject;
class DELPHICLASS TCustomOwnedNode;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION EHierarchyRequestError : public System::Sysutils::EListError
{
	typedef System::Sysutils::EListError inherited;
	
public:
	/* Exception.Create */ inline __fastcall EHierarchyRequestError(const System::UnicodeString Msg) : System::Sysutils::EListError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EHierarchyRequestError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::EListError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EHierarchyRequestError(NativeUInt Ident)/* overload */ : System::Sysutils::EListError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EHierarchyRequestError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::EListError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EHierarchyRequestError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::EListError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EHierarchyRequestError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::EListError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EHierarchyRequestError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::EListError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EHierarchyRequestError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::EListError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EHierarchyRequestError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::EListError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EHierarchyRequestError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::EListError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EHierarchyRequestError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::EListError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EHierarchyRequestError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::EListError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EHierarchyRequestError() { }
	
};


class PASCALIMPLEMENTATION ENoModificationAllowedError : public System::Sysutils::EListError
{
	typedef System::Sysutils::EListError inherited;
	
public:
	/* Exception.Create */ inline __fastcall ENoModificationAllowedError(const System::UnicodeString Msg) : System::Sysutils::EListError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ENoModificationAllowedError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::EListError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ENoModificationAllowedError(NativeUInt Ident)/* overload */ : System::Sysutils::EListError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ENoModificationAllowedError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::EListError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ENoModificationAllowedError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::EListError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ENoModificationAllowedError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::EListError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ENoModificationAllowedError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::EListError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ENoModificationAllowedError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::EListError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENoModificationAllowedError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::EListError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENoModificationAllowedError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::EListError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENoModificationAllowedError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::EListError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENoModificationAllowedError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::EListError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ENoModificationAllowedError() { }
	
};


class PASCALIMPLEMENTATION ENotAssignedError : public System::Sysutils::EListError
{
	typedef System::Sysutils::EListError inherited;
	
public:
	/* Exception.Create */ inline __fastcall ENotAssignedError(const System::UnicodeString Msg) : System::Sysutils::EListError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ENotAssignedError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::EListError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ENotAssignedError(NativeUInt Ident)/* overload */ : System::Sysutils::EListError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ENotAssignedError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::EListError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ENotAssignedError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::EListError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ENotAssignedError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::EListError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ENotAssignedError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::EListError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ENotAssignedError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::EListError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENotAssignedError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::EListError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENotAssignedError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::EListError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENotAssignedError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::EListError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENotAssignedError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::EListError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ENotAssignedError() { }
	
};


class PASCALIMPLEMENTATION ENotFoundError : public System::Sysutils::EListError
{
	typedef System::Sysutils::EListError inherited;
	
public:
	/* Exception.Create */ inline __fastcall ENotFoundError(const System::UnicodeString Msg) : System::Sysutils::EListError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ENotFoundError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::EListError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ENotFoundError(NativeUInt Ident)/* overload */ : System::Sysutils::EListError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ENotFoundError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::EListError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ENotFoundError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::EListError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ENotFoundError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::EListError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ENotFoundError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::EListError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ENotFoundError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::EListError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENotFoundError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::EListError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENotFoundError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::EListError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENotFoundError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::EListError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENotFoundError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::EListError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ENotFoundError() { }
	
};


class PASCALIMPLEMENTATION EWrongOwnerError : public System::Sysutils::EListError
{
	typedef System::Sysutils::EListError inherited;
	
public:
	/* Exception.Create */ inline __fastcall EWrongOwnerError(const System::UnicodeString Msg) : System::Sysutils::EListError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EWrongOwnerError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::EListError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EWrongOwnerError(NativeUInt Ident)/* overload */ : System::Sysutils::EListError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EWrongOwnerError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::EListError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EWrongOwnerError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::EListError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EWrongOwnerError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::EListError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EWrongOwnerError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::EListError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EWrongOwnerError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::EListError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWrongOwnerError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::EListError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWrongOwnerError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::EListError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWrongOwnerError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::EListError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWrongOwnerError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::EListError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EWrongOwnerError() { }
	
};


class PASCALIMPLEMENTATION TCustomOwnedObject : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::Generics::Collections::TList__1<TCustomOwnedObject*>* FOwnedObjects;
	TCustomOwnedObject* FOwner;
	void __fastcall Attach(TCustomOwnedObject* const Obj);
	void __fastcall Detach(TCustomOwnedObject* const Obj);
	TCustomOwnedObject* __fastcall GetOwnedObject(int Index);
	int __fastcall GetOwnedObjectsCount();
	void __fastcall InternalClear();
	
protected:
	virtual void __fastcall Adopt(TCustomOwnedObject* const Obj);
	virtual void __fastcall Clear();
	virtual void __fastcall DoBeforeAttach(TCustomOwnedObject* const Obj);
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner();
	__property TCustomOwnedObject* OwnedObject[int Index] = {read=GetOwnedObject};
	__property int OwnedObjectsCount = {read=GetOwnedObjectsCount, nodefault};
	
public:
	__fastcall TCustomOwnedObject(TCustomOwnedObject* const AOwner);
	__fastcall virtual ~TCustomOwnedObject();
};


class PASCALIMPLEMENTATION TCustomOwnedNode : public TCustomOwnedObject
{
	typedef TCustomOwnedObject inherited;
	
public:
	TCustomOwnedNode* operator[](int Index) { return this->Item[Index]; }
	
private:
	System::Generics::Collections::TList__1<TCustomOwnedNode*>* FItems;
	TCustomOwnedNode* FNextSibling;
	TCustomOwnedNode* FParent;
	TCustomOwnedNode* FPreviousSibling;
	bool FReadOnly;
	TCustomOwnedNode* __fastcall GetItem(int Index);
	void __fastcall InternalAdopt(TCustomOwnedNode* const NewOwner, TCustomOwnedNode* const Node);
	HIDESBASE void __fastcall InternalClear();
	void __fastcall InternalInsertBefore(TCustomOwnedNode* const NewChild, TCustomOwnedNode* const RefChild);
	void __fastcall InternalRemove(TCustomOwnedNode* const OldChild);
	
protected:
	HIDESBASE virtual void __fastcall Adopt(TCustomOwnedNode* const Node);
	virtual TCustomOwnedNode* __fastcall Append(TCustomOwnedNode* const NewChild);
	void __fastcall CheckAssigned(TCustomOwnedNode* const Node);
	void __fastcall CheckDissimilarity(TCustomOwnedNode* const Node_1, TCustomOwnedNode* const Node_2);
	void __fastcall CheckHasChild(TCustomOwnedNode* const Node);
	void __fastcall CheckNotAncestorOrSelf(TCustomOwnedNode* const Node);
	void __fastcall CheckNotReadOnly();
	void __fastcall CheckParentNotReadOnly(TCustomOwnedNode* const Node);
	void __fastcall CheckSameOwner(TCustomOwnedNode* const Node);
	virtual void __fastcall Clear();
	virtual void __fastcall DoAfterAddition(TCustomOwnedNode* const Node);
	virtual void __fastcall DoAfterClear();
	virtual void __fastcall DoAfterRemoval(TCustomOwnedNode* const Node);
	virtual void __fastcall DoBeforeAddition(TCustomOwnedNode* const Node);
	virtual void __fastcall DoBeforeClear();
	virtual void __fastcall DoBeforeRemoval(TCustomOwnedNode* const Node);
	virtual int __fastcall GetCount();
	virtual TCustomOwnedNode* __fastcall GetFirstChild();
	virtual TCustomOwnedNode* __fastcall GetLastChild();
	virtual TCustomOwnedNode* __fastcall GetNextSibling();
	virtual TCustomOwnedNode* __fastcall GetParent();
	virtual TCustomOwnedNode* __fastcall GetPreviousSibling();
	virtual bool __fastcall GetReadOnly();
	virtual bool __fastcall HasAsAncestor(TCustomOwnedNode* const Node);
	virtual bool __fastcall HasChildren();
	virtual int __fastcall IndexOf(TCustomOwnedNode* Node);
	virtual TCustomOwnedNode* __fastcall InsertBefore(TCustomOwnedNode* const NewChild, TCustomOwnedNode* const RefChild);
	virtual void __fastcall RaiseException(const System::Sysutils::ExceptClass E);
	virtual TCustomOwnedNode* __fastcall Remove(TCustomOwnedNode* const OldChild);
	virtual TCustomOwnedNode* __fastcall Replace(TCustomOwnedNode* const NewChild, TCustomOwnedNode* const OldChild);
	virtual void __fastcall SetReadOnly(const bool Value);
	__property int Count = {read=GetCount, nodefault};
	__property TCustomOwnedNode* FirstChild = {read=GetFirstChild};
	__property TCustomOwnedNode* Item[int Index] = {read=GetItem/*, default*/};
	__property System::Generics::Collections::TList__1<TCustomOwnedNode*>* Items = {read=FItems};
	__property TCustomOwnedNode* LastChild = {read=GetLastChild};
	__property TCustomOwnedNode* NextSibling = {read=GetNextSibling};
	__property TCustomOwnedNode* Parent = {read=GetParent};
	__property TCustomOwnedNode* PreviousSibling = {read=GetPreviousSibling};
	__property bool ReadOnly = {read=GetReadOnly, write=SetReadOnly, nodefault};
	
public:
	__fastcall TCustomOwnedNode(TCustomOwnedObject* const AOwner);
	__fastcall virtual ~TCustomOwnedNode();
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Treeutils */
}	/* namespace Internal */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_INTERNAL_TREEUTILS)
using namespace Xml::Internal::Treeutils;
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
#endif	// Xml_Internal_TreeutilsHPP
