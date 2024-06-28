// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.Cloud.AmazonAPI.LifeCycle.pas' rev: 34.00 (iOS)

#ifndef Data_Cloud_Amazonapi_LifecycleHPP
#define Data_Cloud_Amazonapi_LifecycleHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Cloud
{
namespace Amazonapi
{
namespace Lifecycle
{
//-- forward type declarations -----------------------------------------------
struct TAmazonLifeCycleTransition;
struct TAmazonLifeCycleRule;
struct TAmazonLifeCycleConfiguration;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TAmazonStorageClass : unsigned char { Standard, StandardIA, Glacier, ReduceRedundancy };

struct DECLSPEC_DRECORD TAmazonLifeCycleTransition
{
private:
	int FDays;
	TAmazonStorageClass FStorageClass;
	System::UnicodeString __fastcall GetXML();
	
public:
	static TAmazonLifeCycleTransition __fastcall Create(int ADays, TAmazonStorageClass AStorageClass);
	__property int Days = {read=FDays};
	__property TAmazonStorageClass StorageClass = {read=FStorageClass};
	__property System::UnicodeString XML = {read=GetXML};
};


struct DECLSPEC_DRECORD TAmazonLifeCycleRule
{
public:
	TAmazonLifeCycleTransition operator[](int Index) { return this->Transitions[Index]; }
	
private:
	System::UnicodeString FID;
	System::UnicodeString FPrefix;
	bool FStatus;
	System::TArray__1<TAmazonLifeCycleTransition> FTransitions;
	int FExpirationDays;
	int FNoncurrentVersionTransitionDays;
	TAmazonStorageClass FNoncurrentVersionTransitionStorageClass;
	int FNoncurrentVersionExpirationDays;
	TAmazonLifeCycleTransition __fastcall GetTransition(int AIndex);
	System::UnicodeString __fastcall GetXML();
	
public:
	static TAmazonLifeCycleRule __fastcall Create(const System::UnicodeString AID, const System::UnicodeString APrefix, bool AStatus, System::TArray__1<TAmazonLifeCycleTransition> ATransitions, int AExpirationDays, int ANoncurrentVersionTransitionDays, TAmazonStorageClass ANoncurrentVersionTransitionStorageClass, int ANoncurrentVersionExpirationDays);
	int __fastcall AddTransition(int ADays, TAmazonStorageClass AStorageClass);
	void __fastcall DeleteTransition(int AIndex);
	__property System::UnicodeString ID = {read=FID};
	__property System::UnicodeString Prefix = {read=FPrefix};
	__property bool Status = {read=FStatus};
	__property TAmazonLifeCycleTransition Transitions[int Index] = {read=GetTransition};
	__property int ExpirationDays = {read=FExpirationDays, write=FExpirationDays};
	__property int NoncurrentVersionTransitionDays = {read=FNoncurrentVersionTransitionDays};
	__property TAmazonStorageClass NoncurrentVersionTransitionStorageClass = {read=FNoncurrentVersionTransitionStorageClass};
	__property int NoncurrentVersionExpirationDays = {read=FNoncurrentVersionExpirationDays};
	__property System::UnicodeString XML = {read=GetXML};
};


struct DECLSPEC_DRECORD TAmazonLifeCycleConfiguration
{
public:
	TAmazonLifeCycleRule operator[](int Index) { return this->Rules[Index]; }
	
private:
	System::TArray__1<TAmazonLifeCycleRule> FRules;
	TAmazonLifeCycleRule __fastcall GetRule(int AIndex);
	System::UnicodeString __fastcall GetXML();
	
public:
	static TAmazonLifeCycleConfiguration __fastcall Create(System::TArray__1<TAmazonLifeCycleRule> ARules);
	int __fastcall AddRule(const System::UnicodeString AID, const System::UnicodeString APrefix, bool AStatus, System::TArray__1<TAmazonLifeCycleTransition> ATransitions, int AExpirationDays, int ANoncurrentVersionTransitionDays, TAmazonStorageClass ANoncurrentVersionTransitionStorageClass, int ANoncurrentVersionExpirationDays)/* overload */;
	int __fastcall AddRule(const TAmazonLifeCycleRule &ARule)/* overload */;
	void __fastcall DeleteRule(int AIndex);
	__property TAmazonLifeCycleRule Rules[int Index] = {read=GetRule};
	__property System::UnicodeString XML = {read=GetXML};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Lifecycle */
}	/* namespace Amazonapi */
}	/* namespace Cloud */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_CLOUD_AMAZONAPI_LIFECYCLE)
using namespace Data::Cloud::Amazonapi::Lifecycle;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_CLOUD_AMAZONAPI)
using namespace Data::Cloud::Amazonapi;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_CLOUD)
using namespace Data::Cloud;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_Cloud_Amazonapi_LifecycleHPP
