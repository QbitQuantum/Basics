// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSClientMetadata.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DsclientmetadataHPP
#define Datasnap_DsclientmetadataHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Datasnap.DSClientRest.hpp>
#include <Datasnap.DSCommonProxy.hpp>
#include <Datasnap.DSProxyWriter.hpp>
#include <Datasnap.DSMetadata.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dsclientmetadata
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSRestMetaDataProvider;
class DELPHICLASS TDSCustomProxyGenerator;
class DELPHICLASS TDSProxyGenerator;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDSRestMetaDataProvider : public Datasnap::Dsmetadata::TDSCustomMetaDataProvider
{
	typedef Datasnap::Dsmetadata::TDSCustomMetaDataProvider inherited;
	
private:
	Datasnap::Dsclientrest::TDSCustomRestConnection* FConnection;
	void __fastcall SetConnection(Datasnap::Dsclientrest::TDSCustomRestConnection* const Value);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	virtual bool __fastcall HasProvider();
	virtual Datasnap::Dscommonproxy::_di_IDSProxyMetaDataLoader __fastcall GetProvider();
	
__published:
	__property Datasnap::Dsclientrest::TDSCustomRestConnection* RestConnection = {read=FConnection, write=SetConnection};
public:
	/* TComponent.Create */ inline __fastcall virtual TDSRestMetaDataProvider(System::Classes::TComponent* AOwner) : Datasnap::Dsmetadata::TDSCustomMetaDataProvider(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TDSRestMetaDataProvider() { }
	
};


typedef System::Generics::Collections::TDictionary__2<System::UnicodeString,System::Classes::TStream*>* TDSProxyWriterStreamDictionary;

typedef void __fastcall (__closure *TDSProxyGeneratorCreatingFiles)(System::TObject* Sender, System::Classes::TStrings* FileName, bool &Cancel);

typedef void __fastcall (__closure *TDSProxyGeneratorPrepareWriter)(System::TObject* Sender, Datasnap::Dsproxywriter::TDSCustomProxyWriter* Writer, bool &Cancel);

typedef void __fastcall (__closure *TDSProxyGeneratorFinishWriter)(System::TObject* Sender, Datasnap::Dsproxywriter::TDSCustomProxyWriter* Writer);

typedef void __fastcall (__closure *TDSProxyGeneratorCreatedFiles)(System::TObject* Sender, System::Classes::TStrings* FileName);

typedef void __fastcall (__closure *TDSProxyGeneratorCreateStream)(System::TObject* Sender, const Datasnap::Dsproxywriter::TDSProxyFileDescription &AFileDescription, const System::UnicodeString AFileName, /* out */ System::Classes::TStream* &AStream);

class PASCALIMPLEMENTATION TDSCustomProxyGenerator : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::UnicodeString FTargetDirectory;
	System::UnicodeString FTargetUnitName;
	System::UnicodeString FIncludeClasses;
	System::UnicodeString FExcludeClasses;
	System::UnicodeString FIncludeMethods;
	System::UnicodeString FExcludeMethods;
	System::UnicodeString FWriter;
	Datasnap::Dsmetadata::TDSCustomMetaDataProvider* FMetaDataProvider;
	TDSProxyGeneratorCreatedFiles FCreatedFiles;
	TDSProxyGeneratorCreatingFiles FCreatingFiles;
	TDSProxyGeneratorCreateStream FCreateStream;
	Datasnap::Dscommonproxy::_di_IDSProxyMetaDataLoader FMetaDataLoaderIntf;
	TDSProxyGeneratorPrepareWriter FPrepareWriter;
	TDSProxyGeneratorFinishWriter FFinishWriter;
	void __fastcall WriteToStreams(System::DelphiInterface<System::Sysutils::TProc__1<System::Generics::Collections::TDictionary__2<System::UnicodeString,System::Classes::TStream*>*> > Callback)/* overload */;
	void __fastcall WriteToStreams(const Datasnap::Dsproxywriter::TDSProxyWriterProperties &AProperties, Datasnap::Dsproxywriter::TDSCustomProxyWriter* AProxyWriter, Datasnap::Dscommonproxy::_di_IDSProxyMetaDataLoader AConnection, System::Generics::Collections::TDictionary__2<System::UnicodeString,System::Classes::TStream*>* AStreams)/* overload */;
	void __fastcall GetProxyWriter(System::DelphiInterface<System::Sysutils::TProc__2<Datasnap::Dsproxywriter::TDSProxyWriterProperties,Datasnap::Dsproxywriter::TDSCustomProxyWriter*> > Callback);
	void __fastcall SetMetaDataProvider(Datasnap::Dsmetadata::TDSCustomMetaDataProvider* const Value);
	
protected:
	virtual System::Generics::Collections::TDictionary__2<System::UnicodeString,System::Classes::TStream*>* __fastcall GetStreams(/* out */ System::Classes::TStrings* &ACreatedFileNames, bool &LCancel);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	
public:
	__fastcall virtual TDSCustomProxyGenerator(System::Classes::TComponent* AOwner);
	void __fastcall Write()/* overload */;
	void __fastcall Write(Datasnap::Dscommonproxy::_di_IDSProxyMetaDataLoader AConnection)/* overload */;
	void __fastcall WriteToStreams(System::Generics::Collections::TDictionary__2<System::UnicodeString,System::Classes::TStream*>* AStreams)/* overload */;
	void __fastcall WriteToStreams(Datasnap::Dscommonproxy::_di_IDSProxyMetaDataLoader AConnection, System::Generics::Collections::TDictionary__2<System::UnicodeString,System::Classes::TStream*>* AStreams)/* overload */;
	Datasnap::Dsproxywriter::TDSProxyWriterProperties __fastcall WriterProperties();
	Datasnap::Dsproxywriter::TDSProxyFileDescriptions __fastcall FileDescriptions();
	virtual Datasnap::Dscommonproxy::_di_IDSProxyMetaDataLoader __fastcall GetMetaDataLoaderIntf();
	__property Datasnap::Dscommonproxy::_di_IDSProxyMetaDataLoader MetaDataLoaderIntf = {read=GetMetaDataLoaderIntf, write=FMetaDataLoaderIntf};
	__property System::UnicodeString IncludeClasses = {read=FIncludeClasses, write=FIncludeClasses};
	__property System::UnicodeString ExcludeClasses = {read=FExcludeClasses, write=FExcludeClasses};
	__property System::UnicodeString IncludeMethods = {read=FIncludeMethods, write=FIncludeMethods};
	__property System::UnicodeString ExcludeMethods = {read=FExcludeMethods, write=FExcludeMethods};
	__property Datasnap::Dsmetadata::TDSCustomMetaDataProvider* MetaDataProvider = {read=FMetaDataProvider, write=SetMetaDataProvider};
	__property TDSProxyGeneratorCreatingFiles OnCreatingFiles = {read=FCreatingFiles, write=FCreatingFiles};
	__property TDSProxyGeneratorCreatedFiles OnCreatedFiles = {read=FCreatedFiles, write=FCreatedFiles};
	__property TDSProxyGeneratorCreateStream OnCreateStream = {read=FCreateStream, write=FCreateStream};
	__property TDSProxyGeneratorPrepareWriter OnPrepareWriter = {read=FPrepareWriter, write=FPrepareWriter};
	__property TDSProxyGeneratorFinishWriter OnFinishWriter = {read=FFinishWriter, write=FFinishWriter};
	__property System::UnicodeString TargetUnitName = {read=FTargetUnitName, write=FTargetUnitName};
	__property System::UnicodeString TargetDirectory = {read=FTargetDirectory, write=FTargetDirectory};
	__property System::UnicodeString Writer = {read=FWriter, write=FWriter};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TDSCustomProxyGenerator() { }
	
};


class PASCALIMPLEMENTATION TDSProxyGenerator : public TDSCustomProxyGenerator
{
	typedef TDSCustomProxyGenerator inherited;
	
__published:
	__property IncludeClasses = {default=0};
	__property ExcludeClasses = {default=0};
	__property IncludeMethods = {default=0};
	__property ExcludeMethods = {default=0};
	__property MetaDataProvider;
	__property OnCreatingFiles;
	__property OnCreatedFiles;
	__property OnCreateStream;
	__property TargetUnitName = {default=0};
	__property TargetDirectory = {default=0};
	__property Writer = {default=0};
public:
	/* TDSCustomProxyGenerator.Create */ inline __fastcall virtual TDSProxyGenerator(System::Classes::TComponent* AOwner) : TDSCustomProxyGenerator(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TDSProxyGenerator() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dsclientmetadata */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSCLIENTMETADATA)
using namespace Datasnap::Dsclientmetadata;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsclientmetadataHPP
