// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPBaseFileSystem.pas' rev: 34.00 (iOS)

#ifndef IdftpbasefilesystemHPP
#define IdftpbasefilesystemHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdBaseComponent.hpp>
#include <IdException.hpp>
#include <IdFTPList.hpp>
#include <IdFTPListOutput.hpp>
#include <IdFTPServerContextBase.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idftpbasefilesystem
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdFTPBaseFileSystem;
class DELPHICLASS EIdFileSystemException;
class DELPHICLASS EIdFileSystemPermissionDenied;
class DELPHICLASS EIdFileSystemFileNotFound;
class DELPHICLASS EIdFileSystemNotAFile;
class DELPHICLASS EIdFileSystemNotADir;
class DELPHICLASS EIdFileSystemCannotRemoveDir;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdFTPBaseFileSystem : public Idbasecomponent::TIdBaseComponent
{
	typedef Idbasecomponent::TIdBaseComponent inherited;
	
protected:
	void __fastcall ErrPermissionDenied();
	void __fastcall ErrCantRemoveDir();
	void __fastcall ErrFileNotFound();
	void __fastcall ErrNotAFile();
	void __fastcall ErrNotADir();
	
public:
	virtual void __fastcall ChangeDir(Idftpservercontextbase::TIdFTPServerContextBase* AContext, System::UnicodeString &VDirectory) = 0 ;
	virtual void __fastcall GetFileSize(Idftpservercontextbase::TIdFTPServerContextBase* AContext, const System::UnicodeString AFilename, __int64 &VFileSize) = 0 ;
	virtual void __fastcall GetFileDate(Idftpservercontextbase::TIdFTPServerContextBase* AContext, const System::UnicodeString AFilename, System::TDateTime &VFileDate) = 0 ;
	virtual void __fastcall ListDirectory(Idftpservercontextbase::TIdFTPServerContextBase* AContext, const System::UnicodeString APath, Idftplistoutput::TIdFTPListOutput* ADirectoryListing, const System::UnicodeString ACmd, const System::UnicodeString ASwitches) = 0 ;
	virtual void __fastcall RenameFile(Idftpservercontextbase::TIdFTPServerContextBase* AContext, const System::UnicodeString ARenameToFile) = 0 ;
	virtual void __fastcall DeleteFile(Idftpservercontextbase::TIdFTPServerContextBase* AContext, const System::UnicodeString APathName) = 0 ;
	virtual void __fastcall RetrieveFile(Idftpservercontextbase::TIdFTPServerContextBase* AContext, const System::UnicodeString AFileName, System::Classes::TStream* &VStream) = 0 ;
	virtual void __fastcall StoreFile(Idftpservercontextbase::TIdFTPServerContextBase* AContext, const System::UnicodeString AFileName, bool AAppend, System::Classes::TStream* &VStream) = 0 ;
	virtual void __fastcall MakeDirectory(Idftpservercontextbase::TIdFTPServerContextBase* AContext, System::UnicodeString &VDirectory) = 0 ;
	virtual void __fastcall RemoveDirectory(Idftpservercontextbase::TIdFTPServerContextBase* AContext, System::UnicodeString &VDirectory) = 0 ;
	virtual void __fastcall SetModifiedFileDate(Idftpservercontextbase::TIdFTPServerContextBase* AContext, const System::UnicodeString AFileName, System::TDateTime &VDateTime) = 0 ;
	virtual void __fastcall GetCRCCalcStream(Idftpservercontextbase::TIdFTPServerContextBase* AContext, const System::UnicodeString AFileName, System::Classes::TStream* &VStream) = 0 ;
	virtual void __fastcall CombineFiles(Idftpservercontextbase::TIdFTPServerContextBase* AContext, const System::UnicodeString ATargetFileName, System::Classes::TStrings* AParts) = 0 ;
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdFTPBaseFileSystem(System::Classes::TComponent* AOwner)/* overload */ : Idbasecomponent::TIdBaseComponent(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdFTPBaseFileSystem()/* overload */ : Idbasecomponent::TIdBaseComponent() { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TIdFTPBaseFileSystem() { }
	
};


class PASCALIMPLEMENTATION EIdFileSystemException : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFileSystemException(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFileSystemException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFileSystemException(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFileSystemException(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFileSystemException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFileSystemException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFileSystemException(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFileSystemException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFileSystemException(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFileSystemException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFileSystemException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFileSystemException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFileSystemException() { }
	
};


class PASCALIMPLEMENTATION EIdFileSystemPermissionDenied : public EIdFileSystemException
{
	typedef EIdFileSystemException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFileSystemPermissionDenied(const System::UnicodeString AMsg)/* overload */ : EIdFileSystemException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFileSystemPermissionDenied(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFileSystemException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFileSystemPermissionDenied(NativeUInt Ident)/* overload */ : EIdFileSystemException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFileSystemPermissionDenied(System::PResStringRec ResStringRec)/* overload */ : EIdFileSystemException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFileSystemPermissionDenied(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFileSystemException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFileSystemPermissionDenied(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFileSystemException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFileSystemPermissionDenied(const System::UnicodeString Msg, int AHelpContext) : EIdFileSystemException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFileSystemPermissionDenied(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFileSystemException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFileSystemPermissionDenied(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFileSystemException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFileSystemPermissionDenied(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFileSystemException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFileSystemPermissionDenied(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFileSystemException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFileSystemPermissionDenied(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFileSystemException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFileSystemPermissionDenied() { }
	
};


class PASCALIMPLEMENTATION EIdFileSystemFileNotFound : public EIdFileSystemException
{
	typedef EIdFileSystemException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFileSystemFileNotFound(const System::UnicodeString AMsg)/* overload */ : EIdFileSystemException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFileSystemFileNotFound(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFileSystemException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFileSystemFileNotFound(NativeUInt Ident)/* overload */ : EIdFileSystemException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFileSystemFileNotFound(System::PResStringRec ResStringRec)/* overload */ : EIdFileSystemException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFileSystemFileNotFound(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFileSystemException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFileSystemFileNotFound(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFileSystemException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFileSystemFileNotFound(const System::UnicodeString Msg, int AHelpContext) : EIdFileSystemException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFileSystemFileNotFound(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFileSystemException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFileSystemFileNotFound(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFileSystemException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFileSystemFileNotFound(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFileSystemException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFileSystemFileNotFound(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFileSystemException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFileSystemFileNotFound(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFileSystemException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFileSystemFileNotFound() { }
	
};


class PASCALIMPLEMENTATION EIdFileSystemNotAFile : public EIdFileSystemException
{
	typedef EIdFileSystemException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFileSystemNotAFile(const System::UnicodeString AMsg)/* overload */ : EIdFileSystemException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFileSystemNotAFile(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFileSystemException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFileSystemNotAFile(NativeUInt Ident)/* overload */ : EIdFileSystemException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFileSystemNotAFile(System::PResStringRec ResStringRec)/* overload */ : EIdFileSystemException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFileSystemNotAFile(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFileSystemException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFileSystemNotAFile(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFileSystemException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFileSystemNotAFile(const System::UnicodeString Msg, int AHelpContext) : EIdFileSystemException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFileSystemNotAFile(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFileSystemException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFileSystemNotAFile(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFileSystemException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFileSystemNotAFile(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFileSystemException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFileSystemNotAFile(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFileSystemException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFileSystemNotAFile(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFileSystemException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFileSystemNotAFile() { }
	
};


class PASCALIMPLEMENTATION EIdFileSystemNotADir : public EIdFileSystemException
{
	typedef EIdFileSystemException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFileSystemNotADir(const System::UnicodeString AMsg)/* overload */ : EIdFileSystemException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFileSystemNotADir(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFileSystemException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFileSystemNotADir(NativeUInt Ident)/* overload */ : EIdFileSystemException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFileSystemNotADir(System::PResStringRec ResStringRec)/* overload */ : EIdFileSystemException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFileSystemNotADir(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFileSystemException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFileSystemNotADir(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFileSystemException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFileSystemNotADir(const System::UnicodeString Msg, int AHelpContext) : EIdFileSystemException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFileSystemNotADir(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFileSystemException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFileSystemNotADir(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFileSystemException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFileSystemNotADir(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFileSystemException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFileSystemNotADir(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFileSystemException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFileSystemNotADir(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFileSystemException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFileSystemNotADir() { }
	
};


class PASCALIMPLEMENTATION EIdFileSystemCannotRemoveDir : public EIdFileSystemException
{
	typedef EIdFileSystemException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFileSystemCannotRemoveDir(const System::UnicodeString AMsg)/* overload */ : EIdFileSystemException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFileSystemCannotRemoveDir(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFileSystemException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFileSystemCannotRemoveDir(NativeUInt Ident)/* overload */ : EIdFileSystemException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFileSystemCannotRemoveDir(System::PResStringRec ResStringRec)/* overload */ : EIdFileSystemException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFileSystemCannotRemoveDir(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFileSystemException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFileSystemCannotRemoveDir(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFileSystemException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFileSystemCannotRemoveDir(const System::UnicodeString Msg, int AHelpContext) : EIdFileSystemException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFileSystemCannotRemoveDir(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFileSystemException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFileSystemCannotRemoveDir(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFileSystemException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFileSystemCannotRemoveDir(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFileSystemException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFileSystemCannotRemoveDir(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFileSystemException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFileSystemCannotRemoveDir(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFileSystemException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFileSystemCannotRemoveDir() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idftpbasefilesystem */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPBASEFILESYSTEM)
using namespace Idftpbasefilesystem;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdftpbasefilesystemHPP
