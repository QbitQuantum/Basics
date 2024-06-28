// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.CoreData.pas' rev: 34.00 (iOS)

#ifndef Iosapi_CoredataHPP
#define Iosapi_CoredataHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <iOSapi.Foundation.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Coredata
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE NSMappingModelClass;
typedef System::DelphiInterface<NSMappingModelClass> _di_NSMappingModelClass;
__interface DELPHIINTERFACE NSMappingModel;
typedef System::DelphiInterface<NSMappingModel> _di_NSMappingModel;
class DELPHICLASS TNSMappingModel;
__interface DELPHIINTERFACE NSMergeConflictClass;
typedef System::DelphiInterface<NSMergeConflictClass> _di_NSMergeConflictClass;
__interface DELPHIINTERFACE NSMergeConflict;
typedef System::DelphiInterface<NSMergeConflict> _di_NSMergeConflict;
class DELPHICLASS TNSMergeConflict;
__interface DELPHIINTERFACE NSMergePolicyClass;
typedef System::DelphiInterface<NSMergePolicyClass> _di_NSMergePolicyClass;
__interface DELPHIINTERFACE NSMergePolicy;
typedef System::DelphiInterface<NSMergePolicy> _di_NSMergePolicy;
class DELPHICLASS TNSMergePolicy;
__interface DELPHIINTERFACE NSManagedObjectContextClass;
typedef System::DelphiInterface<NSManagedObjectContextClass> _di_NSManagedObjectContextClass;
__interface DELPHIINTERFACE NSManagedObjectContext;
typedef System::DelphiInterface<NSManagedObjectContext> _di_NSManagedObjectContext;
class DELPHICLASS TNSManagedObjectContext;
__interface DELPHIINTERFACE NSManagedObjectIDClass;
typedef System::DelphiInterface<NSManagedObjectIDClass> _di_NSManagedObjectIDClass;
__interface DELPHIINTERFACE NSManagedObjectID;
typedef System::DelphiInterface<NSManagedObjectID> _di_NSManagedObjectID;
class DELPHICLASS TNSManagedObjectID;
__interface DELPHIINTERFACE NSManagedObjectModelClass;
typedef System::DelphiInterface<NSManagedObjectModelClass> _di_NSManagedObjectModelClass;
__interface DELPHIINTERFACE NSManagedObjectModel;
typedef System::DelphiInterface<NSManagedObjectModel> _di_NSManagedObjectModel;
class DELPHICLASS TNSManagedObjectModel;
__interface DELPHIINTERFACE NSMigrationManagerClass;
typedef System::DelphiInterface<NSMigrationManagerClass> _di_NSMigrationManagerClass;
__interface DELPHIINTERFACE NSMigrationManager;
typedef System::DelphiInterface<NSMigrationManager> _di_NSMigrationManager;
class DELPHICLASS TNSMigrationManager;
__interface DELPHIINTERFACE NSPersistentStoreRequestClass;
typedef System::DelphiInterface<NSPersistentStoreRequestClass> _di_NSPersistentStoreRequestClass;
__interface DELPHIINTERFACE NSPersistentStoreRequest;
typedef System::DelphiInterface<NSPersistentStoreRequest> _di_NSPersistentStoreRequest;
class DELPHICLASS TNSPersistentStoreRequest;
__interface DELPHIINTERFACE NSPropertyDescriptionClass;
typedef System::DelphiInterface<NSPropertyDescriptionClass> _di_NSPropertyDescriptionClass;
__interface DELPHIINTERFACE NSPropertyDescription;
typedef System::DelphiInterface<NSPropertyDescription> _di_NSPropertyDescription;
class DELPHICLASS TNSPropertyDescription;
__interface DELPHIINTERFACE NSPropertyMappingClass;
typedef System::DelphiInterface<NSPropertyMappingClass> _di_NSPropertyMappingClass;
__interface DELPHIINTERFACE NSPropertyMapping;
typedef System::DelphiInterface<NSPropertyMapping> _di_NSPropertyMapping;
class DELPHICLASS TNSPropertyMapping;
__interface DELPHIINTERFACE NSPersistentStoreClass;
typedef System::DelphiInterface<NSPersistentStoreClass> _di_NSPersistentStoreClass;
__interface DELPHIINTERFACE NSPersistentStore;
typedef System::DelphiInterface<NSPersistentStore> _di_NSPersistentStore;
class DELPHICLASS TNSPersistentStore;
__interface DELPHIINTERFACE NSPersistentStoreCoordinatorClass;
typedef System::DelphiInterface<NSPersistentStoreCoordinatorClass> _di_NSPersistentStoreCoordinatorClass;
__interface DELPHIINTERFACE NSPersistentStoreCoordinator;
typedef System::DelphiInterface<NSPersistentStoreCoordinator> _di_NSPersistentStoreCoordinator;
class DELPHICLASS TNSPersistentStoreCoordinator;
__interface DELPHIINTERFACE NSManagedObjectClass;
typedef System::DelphiInterface<NSManagedObjectClass> _di_NSManagedObjectClass;
__interface DELPHIINTERFACE NSManagedObject;
typedef System::DelphiInterface<NSManagedObject> _di_NSManagedObject;
class DELPHICLASS TNSManagedObject;
__interface DELPHIINTERFACE NSEntityMappingClass;
typedef System::DelphiInterface<NSEntityMappingClass> _di_NSEntityMappingClass;
__interface DELPHIINTERFACE NSEntityMapping;
typedef System::DelphiInterface<NSEntityMapping> _di_NSEntityMapping;
class DELPHICLASS TNSEntityMapping;
__interface DELPHIINTERFACE NSEntityMigrationPolicyClass;
typedef System::DelphiInterface<NSEntityMigrationPolicyClass> _di_NSEntityMigrationPolicyClass;
__interface DELPHIINTERFACE NSEntityMigrationPolicy;
typedef System::DelphiInterface<NSEntityMigrationPolicy> _di_NSEntityMigrationPolicy;
class DELPHICLASS TNSEntityMigrationPolicy;
__interface DELPHIINTERFACE NSAtomicStoreCacheNodeClass;
typedef System::DelphiInterface<NSAtomicStoreCacheNodeClass> _di_NSAtomicStoreCacheNodeClass;
__interface DELPHIINTERFACE NSAtomicStoreCacheNode;
typedef System::DelphiInterface<NSAtomicStoreCacheNode> _di_NSAtomicStoreCacheNode;
class DELPHICLASS TNSAtomicStoreCacheNode;
__interface DELPHIINTERFACE NSEntityDescriptionClass;
typedef System::DelphiInterface<NSEntityDescriptionClass> _di_NSEntityDescriptionClass;
__interface DELPHIINTERFACE NSEntityDescription;
typedef System::DelphiInterface<NSEntityDescription> _di_NSEntityDescription;
class DELPHICLASS TNSEntityDescription;
__interface DELPHIINTERFACE NSFetchRequestExpressionClass;
typedef System::DelphiInterface<NSFetchRequestExpressionClass> _di_NSFetchRequestExpressionClass;
__interface DELPHIINTERFACE NSFetchRequestExpression;
typedef System::DelphiInterface<NSFetchRequestExpression> _di_NSFetchRequestExpression;
class DELPHICLASS TNSFetchRequestExpression;
__interface DELPHIINTERFACE NSFetchedResultsControllerClass;
typedef System::DelphiInterface<NSFetchedResultsControllerClass> _di_NSFetchedResultsControllerClass;
__interface DELPHIINTERFACE NSFetchedResultsController;
typedef System::DelphiInterface<NSFetchedResultsController> _di_NSFetchedResultsController;
class DELPHICLASS TNSFetchedResultsController;
__interface DELPHIINTERFACE NSIncrementalStoreNodeClass;
typedef System::DelphiInterface<NSIncrementalStoreNodeClass> _di_NSIncrementalStoreNodeClass;
__interface DELPHIINTERFACE NSIncrementalStoreNode;
typedef System::DelphiInterface<NSIncrementalStoreNode> _di_NSIncrementalStoreNode;
class DELPHICLASS TNSIncrementalStoreNode;
__interface DELPHIINTERFACE NSAtomicStoreClass;
typedef System::DelphiInterface<NSAtomicStoreClass> _di_NSAtomicStoreClass;
__interface DELPHIINTERFACE NSAtomicStore;
typedef System::DelphiInterface<NSAtomicStore> _di_NSAtomicStore;
class DELPHICLASS TNSAtomicStore;
__interface DELPHIINTERFACE NSSaveChangesRequestClass;
typedef System::DelphiInterface<NSSaveChangesRequestClass> _di_NSSaveChangesRequestClass;
__interface DELPHIINTERFACE NSSaveChangesRequest;
typedef System::DelphiInterface<NSSaveChangesRequest> _di_NSSaveChangesRequest;
class DELPHICLASS TNSSaveChangesRequest;
__interface DELPHIINTERFACE NSRelationshipDescriptionClass;
typedef System::DelphiInterface<NSRelationshipDescriptionClass> _di_NSRelationshipDescriptionClass;
__interface DELPHIINTERFACE NSRelationshipDescription;
typedef System::DelphiInterface<NSRelationshipDescription> _di_NSRelationshipDescription;
class DELPHICLASS TNSRelationshipDescription;
__interface DELPHIINTERFACE NSAttributeDescriptionClass;
typedef System::DelphiInterface<NSAttributeDescriptionClass> _di_NSAttributeDescriptionClass;
__interface DELPHIINTERFACE NSAttributeDescription;
typedef System::DelphiInterface<NSAttributeDescription> _di_NSAttributeDescription;
class DELPHICLASS TNSAttributeDescription;
__interface DELPHIINTERFACE NSExpressionDescriptionClass;
typedef System::DelphiInterface<NSExpressionDescriptionClass> _di_NSExpressionDescriptionClass;
__interface DELPHIINTERFACE NSExpressionDescription;
typedef System::DelphiInterface<NSExpressionDescription> _di_NSExpressionDescription;
class DELPHICLASS TNSExpressionDescription;
__interface DELPHIINTERFACE NSFetchRequestClass;
typedef System::DelphiInterface<NSFetchRequestClass> _di_NSFetchRequestClass;
__interface DELPHIINTERFACE NSFetchRequest;
typedef System::DelphiInterface<NSFetchRequest> _di_NSFetchRequest;
class DELPHICLASS TNSFetchRequest;
__interface DELPHIINTERFACE NSIncrementalStoreClass;
typedef System::DelphiInterface<NSIncrementalStoreClass> _di_NSIncrementalStoreClass;
__interface DELPHIINTERFACE NSIncrementalStore;
typedef System::DelphiInterface<NSIncrementalStore> _di_NSIncrementalStore;
class DELPHICLASS TNSIncrementalStore;
__interface DELPHIINTERFACE NSFetchedPropertyDescriptionClass;
typedef System::DelphiInterface<NSFetchedPropertyDescriptionClass> _di_NSFetchedPropertyDescriptionClass;
__interface DELPHIINTERFACE NSFetchedPropertyDescription;
typedef System::DelphiInterface<NSFetchedPropertyDescription> _di_NSFetchedPropertyDescription;
class DELPHICLASS TNSFetchedPropertyDescription;
//-- type declarations -------------------------------------------------------
typedef unsigned long NSAttributeType;

typedef unsigned long NSDeleteRule;

typedef unsigned long NSEntityMappingType;

typedef unsigned long NSFetchRequestResultType;

typedef unsigned long NSManagedObjectContextConcurrencyType;

typedef unsigned long NSMergePolicyType;

typedef unsigned long NSPersistentStoreRequestType;

typedef unsigned long NSSnapshotEventType;

__interface  INTERFACE_UUID("{63AC4E41-59B6-461E-8BDB-FA718208DFAD}") NSMappingModelClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void * __cdecl inferredMappingModelForSourceModel(_di_NSManagedObjectModel sourceModel, _di_NSManagedObjectModel destinationModel, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void * __cdecl mappingModelFromBundles(Iosapi::Foundation::_di_NSArray bundles, _di_NSManagedObjectModel forSourceModel, _di_NSManagedObjectModel destinationModel) = 0 ;
};

__interface  INTERFACE_UUID("{EC45C6DE-1BBC-41F5-A24D-744A21052E42}") NSMappingModel  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl entityMappings() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl entityMappingsByName() = 0 ;
	virtual void * __cdecl initWithContentsOfURL(Iosapi::Foundation::_di_NSURL url) = 0 ;
	virtual void __cdecl setEntityMappings(Iosapi::Foundation::_di_NSArray mappings) = 0 ;
};

class PASCALIMPLEMENTATION TNSMappingModel : public Macapi::Objectivec::TOCGenericImport__2<_di_NSMappingModelClass,_di_NSMappingModel>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSMappingModelClass,_di_NSMappingModel> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSMappingModel(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSMappingModelClass,_di_NSMappingModel>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSMappingModel() { }
	
};


__interface  INTERFACE_UUID("{0A5B8648-1006-440F-A4BF-AE5E4F3C1036}") NSMergeConflictClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{DF228EDB-F4EA-4FFB-9036-40C8DD27B7E1}") NSMergeConflict  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl cachedSnapshot() = 0 ;
	virtual void * __cdecl initWithSource(_di_NSManagedObject srcObject, unsigned long newVersion, unsigned long oldVersion, Iosapi::Foundation::_di_NSDictionary cachedSnapshot, Iosapi::Foundation::_di_NSDictionary persistedSnapshot) = 0 ;
	virtual unsigned long __cdecl newVersionNumber() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl objectSnapshot() = 0 ;
	virtual unsigned long __cdecl oldVersionNumber() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl persistedSnapshot() = 0 ;
	virtual _di_NSManagedObject __cdecl sourceObject() = 0 ;
};

class PASCALIMPLEMENTATION TNSMergeConflict : public Macapi::Objectivec::TOCGenericImport__2<_di_NSMergeConflictClass,_di_NSMergeConflict>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSMergeConflictClass,_di_NSMergeConflict> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSMergeConflict(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSMergeConflictClass,_di_NSMergeConflict>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSMergeConflict() { }
	
};


__interface  INTERFACE_UUID("{1A714DF9-B3AD-4A0E-A4ED-34EB3E696D97}") NSMergePolicyClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{6DE4FF12-0F6B-40FB-B5B7-EA78CCCA9937}") NSMergePolicy  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl initWithMergeType(unsigned long ty) = 0 ;
	virtual unsigned long __cdecl mergeType() = 0 ;
	virtual bool __cdecl resolveConflicts(Iosapi::Foundation::_di_NSArray list, Iosapi::Foundation::_di_NSError error) = 0 ;
};

class PASCALIMPLEMENTATION TNSMergePolicy : public Macapi::Objectivec::TOCGenericImport__2<_di_NSMergePolicyClass,_di_NSMergePolicy>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSMergePolicyClass,_di_NSMergePolicy> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSMergePolicy(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSMergePolicyClass,_di_NSMergePolicy>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSMergePolicy() { }
	
};


__interface  INTERFACE_UUID("{4B3C0627-2417-4ABF-95F0-E9B1CF5C2512}") NSManagedObjectContextClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{8D71FCBA-F1CB-4055-B373-83AFC5EC3EAE}") NSManagedObjectContext  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl assignObject(void * object_, _di_NSPersistentStore toPersistentStore) = 0 ;
	virtual unsigned long __cdecl concurrencyType() = 0 ;
	virtual unsigned long __cdecl countForFetchRequest(_di_NSFetchRequest request, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl deleteObject(_di_NSManagedObject object_) = 0 ;
	virtual Iosapi::Foundation::_di_NSSet __cdecl deletedObjects() = 0 ;
	virtual void __cdecl detectConflictsForObject(_di_NSManagedObject object_) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl executeFetchRequest(_di_NSFetchRequest request, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual _di_NSManagedObject __cdecl existingObjectWithID(_di_NSManagedObjectID objectID, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual bool __cdecl hasChanges() = 0 ;
	virtual void * __cdecl initWithConcurrencyType(unsigned long ct) = 0 ;
	virtual void __cdecl insertObject(_di_NSManagedObject object_) = 0 ;
	virtual Iosapi::Foundation::_di_NSSet __cdecl insertedObjects() = 0 ;
	virtual void __cdecl lock() = 0 ;
	virtual void __cdecl mergeChangesFromContextDidSaveNotification(Iosapi::Foundation::_di_NSNotification notification) = 0 ;
	virtual void * __cdecl mergePolicy() = 0 ;
	virtual _di_NSManagedObject __cdecl objectRegisteredForID(_di_NSManagedObjectID objectID) = 0 ;
	virtual _di_NSManagedObject __cdecl objectWithID(_di_NSManagedObjectID objectID) = 0 ;
	virtual void __cdecl observeValueForKeyPath(Iosapi::Foundation::_di_NSString keyPath, void * ofObject, Iosapi::Foundation::_di_NSDictionary change, void * context) = 0 ;
	virtual bool __cdecl obtainPermanentIDsForObjects(Iosapi::Foundation::_di_NSArray objects, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual _di_NSManagedObjectContext __cdecl parentContext() = 0 ;
	virtual _di_NSPersistentStoreCoordinator __cdecl persistentStoreCoordinator() = 0 ;
	virtual void __cdecl processPendingChanges() = 0 ;
	virtual bool __cdecl propagatesDeletesAtEndOfEvent() = 0 ;
	virtual void __cdecl redo() = 0 ;
	virtual void __cdecl refreshObject(_di_NSManagedObject object_, bool mergeChanges) = 0 ;
	virtual Iosapi::Foundation::_di_NSSet __cdecl registeredObjects() = 0 ;
	virtual void __cdecl reset() = 0 ;
	virtual bool __cdecl retainsRegisteredObjects() = 0 ;
	virtual void __cdecl rollback() = 0 ;
	virtual bool __cdecl save(Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl setMergePolicy(void * mergePolicy) = 0 ;
	virtual void __cdecl setParentContext(_di_NSManagedObjectContext parent) = 0 ;
	virtual void __cdecl setPersistentStoreCoordinator(_di_NSPersistentStoreCoordinator coordinator) = 0 ;
	virtual void __cdecl setPropagatesDeletesAtEndOfEvent(bool flag) = 0 ;
	virtual void __cdecl setRetainsRegisteredObjects(bool flag) = 0 ;
	virtual void __cdecl setStalenessInterval(double expiration) = 0 ;
	virtual void __cdecl setUndoManager(Iosapi::Foundation::_di_NSUndoManager undoManager) = 0 ;
	virtual double __cdecl stalenessInterval() = 0 ;
	virtual bool __cdecl tryLock() = 0 ;
	virtual void __cdecl undo() = 0 ;
	virtual Iosapi::Foundation::_di_NSUndoManager __cdecl undoManager() = 0 ;
	virtual void __cdecl unlock() = 0 ;
	virtual Iosapi::Foundation::_di_NSSet __cdecl updatedObjects() = 0 ;
	virtual Iosapi::Foundation::_di_NSMutableDictionary __cdecl userInfo() = 0 ;
};

class PASCALIMPLEMENTATION TNSManagedObjectContext : public Macapi::Objectivec::TOCGenericImport__2<_di_NSManagedObjectContextClass,_di_NSManagedObjectContext>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSManagedObjectContextClass,_di_NSManagedObjectContext> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSManagedObjectContext(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSManagedObjectContextClass,_di_NSManagedObjectContext>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSManagedObjectContext() { }
	
};


__interface  INTERFACE_UUID("{2E268789-1589-4EFF-9304-B8F03F82E8C9}") NSManagedObjectIDClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{85D42F36-1371-4348-A5E4-FD44793CB30C}") NSManagedObjectID  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSURL __cdecl URIRepresentation() = 0 ;
	virtual _di_NSEntityDescription __cdecl entity() = 0 ;
	virtual bool __cdecl isTemporaryID() = 0 ;
	virtual _di_NSPersistentStore __cdecl persistentStore() = 0 ;
};

class PASCALIMPLEMENTATION TNSManagedObjectID : public Macapi::Objectivec::TOCGenericImport__2<_di_NSManagedObjectIDClass,_di_NSManagedObjectID>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSManagedObjectIDClass,_di_NSManagedObjectID> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSManagedObjectID(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSManagedObjectIDClass,_di_NSManagedObjectID>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSManagedObjectID() { }
	
};


__interface  INTERFACE_UUID("{E5215F0A-5415-40AA-A25F-F6AA55E163E9}") NSManagedObjectModelClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void * __cdecl mergedModelFromBundles(Iosapi::Foundation::_di_NSArray bundles) = 0 /* overload */;
	virtual void * __cdecl mergedModelFromBundles(Iosapi::Foundation::_di_NSArray bundles, Iosapi::Foundation::_di_NSDictionary forStoreMetadata) = 0 /* overload */;
	virtual void * __cdecl modelByMergingModels(Iosapi::Foundation::_di_NSArray models) = 0 /* overload */;
	virtual void * __cdecl modelByMergingModels(Iosapi::Foundation::_di_NSArray models, Iosapi::Foundation::_di_NSDictionary forStoreMetadata) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{BC685AB5-7951-44A5-A182-A3170A7868A4}") NSManagedObjectModel  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl configurations() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl entities() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl entitiesByName() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl entitiesForConfiguration(Iosapi::Foundation::_di_NSString configuration) = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl entityVersionHashesByName() = 0 ;
	virtual _di_NSFetchRequest __cdecl fetchRequestFromTemplateWithName(Iosapi::Foundation::_di_NSString name, Iosapi::Foundation::_di_NSDictionary substitutionVariables) = 0 ;
	virtual _di_NSFetchRequest __cdecl fetchRequestTemplateForName(Iosapi::Foundation::_di_NSString name) = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl fetchRequestTemplatesByName() = 0 ;
	HIDESBASE virtual void * __cdecl init() = 0 ;
	virtual void * __cdecl initWithContentsOfURL(Iosapi::Foundation::_di_NSURL url) = 0 ;
	virtual bool __cdecl isConfiguration(Iosapi::Foundation::_di_NSString configuration, Iosapi::Foundation::_di_NSDictionary compatibleWithStoreMetadata) = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl localizationDictionary() = 0 ;
	virtual void __cdecl setEntities(Iosapi::Foundation::_di_NSArray entities) = 0 /* overload */;
	virtual void __cdecl setEntities(Iosapi::Foundation::_di_NSArray entities, Iosapi::Foundation::_di_NSString forConfiguration) = 0 /* overload */;
	virtual void __cdecl setFetchRequestTemplate(_di_NSFetchRequest fetchRequestTemplate, Iosapi::Foundation::_di_NSString forName) = 0 ;
	virtual void __cdecl setLocalizationDictionary(Iosapi::Foundation::_di_NSDictionary localizationDictionary) = 0 ;
	virtual void __cdecl setVersionIdentifiers(Iosapi::Foundation::_di_NSSet identifiers) = 0 ;
	virtual Iosapi::Foundation::_di_NSSet __cdecl versionIdentifiers() = 0 ;
};

class PASCALIMPLEMENTATION TNSManagedObjectModel : public Macapi::Objectivec::TOCGenericImport__2<_di_NSManagedObjectModelClass,_di_NSManagedObjectModel>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSManagedObjectModelClass,_di_NSManagedObjectModel> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSManagedObjectModel(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSManagedObjectModelClass,_di_NSManagedObjectModel>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSManagedObjectModel() { }
	
};


__interface  INTERFACE_UUID("{05D0A670-C230-424E-8D79-AF92E63376DB}") NSMigrationManagerClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{36F93ECB-8CE9-4796-941A-48C2B9DD8E3F}") NSMigrationManager  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl associateSourceInstance(_di_NSManagedObject sourceInstance, _di_NSManagedObject withDestinationInstance, _di_NSEntityMapping forEntityMapping) = 0 ;
	virtual void __cdecl cancelMigrationWithError(Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual _di_NSEntityMapping __cdecl currentEntityMapping() = 0 ;
	virtual _di_NSManagedObjectContext __cdecl destinationContext() = 0 ;
	virtual _di_NSEntityDescription __cdecl destinationEntityForEntityMapping(_di_NSEntityMapping mEntity) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl destinationInstancesForEntityMappingNamed(Iosapi::Foundation::_di_NSString mappingName, Iosapi::Foundation::_di_NSArray sourceInstances) = 0 ;
	virtual _di_NSManagedObjectModel __cdecl destinationModel() = 0 ;
	virtual void * __cdecl initWithSourceModel(_di_NSManagedObjectModel sourceModel, _di_NSManagedObjectModel destinationModel) = 0 ;
	virtual _di_NSMappingModel __cdecl mappingModel() = 0 ;
	virtual float __cdecl migrationProgress() = 0 ;
	virtual void __cdecl reset() = 0 ;
	virtual void __cdecl setUserInfo(Iosapi::Foundation::_di_NSDictionary dict) = 0 ;
	virtual void __cdecl setUsesStoreSpecificMigrationManager(bool flag) = 0 ;
	virtual _di_NSManagedObjectContext __cdecl sourceContext() = 0 ;
	virtual _di_NSEntityDescription __cdecl sourceEntityForEntityMapping(_di_NSEntityMapping mEntity) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl sourceInstancesForEntityMappingNamed(Iosapi::Foundation::_di_NSString mappingName, Iosapi::Foundation::_di_NSArray destinationInstances) = 0 ;
	virtual _di_NSManagedObjectModel __cdecl sourceModel() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl userInfo() = 0 ;
	virtual bool __cdecl usesStoreSpecificMigrationManager() = 0 ;
};

class PASCALIMPLEMENTATION TNSMigrationManager : public Macapi::Objectivec::TOCGenericImport__2<_di_NSMigrationManagerClass,_di_NSMigrationManager>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSMigrationManagerClass,_di_NSMigrationManager> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSMigrationManager(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSMigrationManagerClass,_di_NSMigrationManager>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSMigrationManager() { }
	
};


__interface  INTERFACE_UUID("{34D96963-F1A1-4CBC-9ABF-494601DE3AF9}") NSPersistentStoreRequestClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{C606EE35-8921-4F28-BCAD-21B7E9B0FCD4}") NSPersistentStoreRequest  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl affectedStores() = 0 ;
	virtual unsigned long __cdecl requestType() = 0 ;
	virtual void __cdecl setAffectedStores(Iosapi::Foundation::_di_NSArray stores) = 0 ;
};

class PASCALIMPLEMENTATION TNSPersistentStoreRequest : public Macapi::Objectivec::TOCGenericImport__2<_di_NSPersistentStoreRequestClass,_di_NSPersistentStoreRequest>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSPersistentStoreRequestClass,_di_NSPersistentStoreRequest> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSPersistentStoreRequest(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSPersistentStoreRequestClass,_di_NSPersistentStoreRequest>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSPersistentStoreRequest() { }
	
};


__interface  INTERFACE_UUID("{8E659BEE-6D35-4FB4-833A-ECE177C6F88D}") NSPropertyDescriptionClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{FEA1210A-25AB-4B5B-B94E-1A3B8323C064}") NSPropertyDescription  : public Iosapi::Foundation::NSObject 
{
	virtual _di_NSEntityDescription __cdecl entity() = 0 ;
	virtual bool __cdecl isIndexed() = 0 ;
	virtual bool __cdecl isIndexedBySpotlight() = 0 ;
	virtual bool __cdecl isOptional() = 0 ;
	virtual bool __cdecl isStoredInExternalRecord() = 0 ;
	virtual bool __cdecl isTransient() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl renamingIdentifier() = 0 ;
	virtual void __cdecl setIndexed(bool flag) = 0 ;
	virtual void __cdecl setIndexedBySpotlight(bool flag) = 0 ;
	virtual void __cdecl setName(Iosapi::Foundation::_di_NSString name) = 0 ;
	virtual void __cdecl setOptional(bool flag) = 0 ;
	virtual void __cdecl setRenamingIdentifier(Iosapi::Foundation::_di_NSString value) = 0 ;
	virtual void __cdecl setStoredInExternalRecord(bool flag) = 0 ;
	virtual void __cdecl setTransient(bool flag) = 0 ;
	virtual void __cdecl setUserInfo(Iosapi::Foundation::_di_NSDictionary dictionary) = 0 ;
	virtual void __cdecl setValidationPredicates(Iosapi::Foundation::_di_NSArray validationPredicates, Iosapi::Foundation::_di_NSArray withValidationWarnings) = 0 ;
	virtual void __cdecl setVersionHashModifier(Iosapi::Foundation::_di_NSString modifierString) = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl userInfo() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl validationPredicates() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl validationWarnings() = 0 ;
	virtual Iosapi::Foundation::_di_NSData __cdecl versionHash() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl versionHashModifier() = 0 ;
};

class PASCALIMPLEMENTATION TNSPropertyDescription : public Macapi::Objectivec::TOCGenericImport__2<_di_NSPropertyDescriptionClass,_di_NSPropertyDescription>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSPropertyDescriptionClass,_di_NSPropertyDescription> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSPropertyDescription(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSPropertyDescriptionClass,_di_NSPropertyDescription>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSPropertyDescription() { }
	
};


__interface  INTERFACE_UUID("{4AE8DE07-7968-4FF5-8EDA-9E909DE61247}") NSPropertyMappingClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{DCBFEBF6-C554-4F2D-905E-E8FB44CAEE79}") NSPropertyMapping  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
	virtual void __cdecl setName(Iosapi::Foundation::_di_NSString name) = 0 ;
	virtual void __cdecl setUserInfo(Iosapi::Foundation::_di_NSDictionary userInfo) = 0 ;
	virtual void __cdecl setValueExpression(Iosapi::Foundation::_di_NSExpression expression) = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl userInfo() = 0 ;
	virtual Iosapi::Foundation::_di_NSExpression __cdecl valueExpression() = 0 ;
};

class PASCALIMPLEMENTATION TNSPropertyMapping : public Macapi::Objectivec::TOCGenericImport__2<_di_NSPropertyMappingClass,_di_NSPropertyMapping>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSPropertyMappingClass,_di_NSPropertyMapping> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSPropertyMapping(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSPropertyMappingClass,_di_NSPropertyMapping>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSPropertyMapping() { }
	
};


__interface  INTERFACE_UUID("{F9399137-998A-4D9E-9FBD-8BAD36B45451}") NSPersistentStoreClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl metadataForPersistentStoreWithURL(Iosapi::Foundation::_di_NSURL url, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual bool __cdecl setMetadata(Iosapi::Foundation::_di_NSDictionary metadata, Iosapi::Foundation::_di_NSURL forPersistentStoreWithURL, Iosapi::Foundation::_di_NSError error) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{AE92EC4A-E3F3-47E3-9BE5-93C67763F776}") NSPersistentStore  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSURL __cdecl URL() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl configurationName() = 0 ;
	virtual void __cdecl didAddToPersistentStoreCoordinator(_di_NSPersistentStoreCoordinator coordinator) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl identifier() = 0 ;
	virtual void * __cdecl initWithPersistentStoreCoordinator(_di_NSPersistentStoreCoordinator root, Iosapi::Foundation::_di_NSString configurationName, Iosapi::Foundation::_di_NSURL URL, Iosapi::Foundation::_di_NSDictionary options) = 0 ;
	virtual bool __cdecl isReadOnly() = 0 ;
	virtual bool __cdecl loadMetadata(Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl metadata() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl options() = 0 ;
	virtual _di_NSPersistentStoreCoordinator __cdecl persistentStoreCoordinator() = 0 ;
	virtual void __cdecl setIdentifier(Iosapi::Foundation::_di_NSString identifier) = 0 ;
	virtual void __cdecl setMetadata(Iosapi::Foundation::_di_NSDictionary storeMetadata) = 0 /* overload */;
	virtual void __cdecl setReadOnly(bool flag) = 0 ;
	virtual void __cdecl setURL(Iosapi::Foundation::_di_NSURL url) = 0 ;
	virtual void __cdecl willRemoveFromPersistentStoreCoordinator(_di_NSPersistentStoreCoordinator coordinator) = 0 ;
};

class PASCALIMPLEMENTATION TNSPersistentStore : public Macapi::Objectivec::TOCGenericImport__2<_di_NSPersistentStoreClass,_di_NSPersistentStore>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSPersistentStoreClass,_di_NSPersistentStore> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSPersistentStore(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSPersistentStoreClass,_di_NSPersistentStore>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSPersistentStore() { }
	
};


__interface  INTERFACE_UUID("{DE87F288-F2D5-4F36-A72D-85C91532B4FF}") NSPersistentStoreCoordinatorClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl metadataForPersistentStoreOfType(Iosapi::Foundation::_di_NSString storeType, Iosapi::Foundation::_di_NSURL URL, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl registerStoreClass(void * storeClass, Iosapi::Foundation::_di_NSString forStoreType) = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl registeredStoreTypes() = 0 ;
	virtual bool __cdecl setMetadata(Iosapi::Foundation::_di_NSDictionary metadata, Iosapi::Foundation::_di_NSString forPersistentStoreOfType, Iosapi::Foundation::_di_NSURL URL, Iosapi::Foundation::_di_NSError error) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{C1AE026B-86D6-40F1-9884-76E37F98E971}") NSPersistentStoreCoordinator  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSURL __cdecl URLForPersistentStore(_di_NSPersistentStore store) = 0 ;
	virtual _di_NSPersistentStore __cdecl addPersistentStoreWithType(Iosapi::Foundation::_di_NSString storeType, Iosapi::Foundation::_di_NSString configuration, Iosapi::Foundation::_di_NSURL URL, Iosapi::Foundation::_di_NSDictionary options, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void * __cdecl executeRequest(_di_NSPersistentStoreRequest request, _di_NSManagedObjectContext withContext, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void * __cdecl initWithManagedObjectModel(_di_NSManagedObjectModel model) = 0 ;
	virtual void __cdecl lock() = 0 ;
	virtual _di_NSManagedObjectID __cdecl managedObjectIDForURIRepresentation(Iosapi::Foundation::_di_NSURL url) = 0 ;
	virtual _di_NSManagedObjectModel __cdecl managedObjectModel() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl metadataForPersistentStore(_di_NSPersistentStore store) = 0 ;
	virtual _di_NSPersistentStore __cdecl migratePersistentStore(_di_NSPersistentStore store, Iosapi::Foundation::_di_NSURL toURL, Iosapi::Foundation::_di_NSDictionary options, Iosapi::Foundation::_di_NSString withType, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual _di_NSPersistentStore __cdecl persistentStoreForURL(Iosapi::Foundation::_di_NSURL URL) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl persistentStores() = 0 ;
	virtual bool __cdecl removePersistentStore(_di_NSPersistentStore store, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl setMetadata(Iosapi::Foundation::_di_NSDictionary metadata, _di_NSPersistentStore forPersistentStore) = 0 /* overload */;
	virtual bool __cdecl setURL(Iosapi::Foundation::_di_NSURL url, _di_NSPersistentStore forPersistentStore) = 0 ;
	virtual bool __cdecl tryLock() = 0 ;
	virtual void __cdecl unlock() = 0 ;
};

class PASCALIMPLEMENTATION TNSPersistentStoreCoordinator : public Macapi::Objectivec::TOCGenericImport__2<_di_NSPersistentStoreCoordinatorClass,_di_NSPersistentStoreCoordinator>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSPersistentStoreCoordinatorClass,_di_NSPersistentStoreCoordinator> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSPersistentStoreCoordinator(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSPersistentStoreCoordinatorClass,_di_NSPersistentStoreCoordinator>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSPersistentStoreCoordinator() { }
	
};


__interface  INTERFACE_UUID("{25B84FEC-04DB-4F87-8E77-B6BAD4CFD779}") NSManagedObjectClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual bool __cdecl contextShouldIgnoreUnmodeledPropertyChanges() = 0 ;
};

__interface  INTERFACE_UUID("{4B980CDA-4853-49C4-93F3-D8F585697011}") NSManagedObject  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl awakeFromFetch() = 0 ;
	virtual void __cdecl awakeFromInsert() = 0 ;
	virtual void __cdecl awakeFromSnapshotEvents(unsigned long flags) = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl changedValues() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl changedValuesForCurrentEvent() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl committedValuesForKeys(Iosapi::Foundation::_di_NSArray keys) = 0 ;
	virtual void __cdecl didAccessValueForKey(Iosapi::Foundation::_di_NSString key) = 0 ;
	virtual void __cdecl didChangeValueForKey(Iosapi::Foundation::_di_NSString key) = 0 /* overload */;
	virtual void __cdecl didChangeValueForKey(Iosapi::Foundation::_di_NSString inKey, unsigned long withSetMutation, Iosapi::Foundation::_di_NSSet usingObjects) = 0 /* overload */;
	virtual void __cdecl didSave() = 0 ;
	virtual void __cdecl didTurnIntoFault() = 0 ;
	virtual _di_NSEntityDescription __cdecl entity() = 0 ;
	virtual unsigned long __cdecl faultingState() = 0 ;
	virtual bool __cdecl hasChanges() = 0 ;
	virtual bool __cdecl hasFaultForRelationshipNamed(Iosapi::Foundation::_di_NSString key) = 0 ;
	virtual void * __cdecl initWithEntity(_di_NSEntityDescription entity, _di_NSManagedObjectContext insertIntoManagedObjectContext) = 0 ;
	virtual bool __cdecl isDeleted() = 0 ;
	virtual bool __cdecl isFault() = 0 ;
	virtual bool __cdecl isInserted() = 0 ;
	virtual bool __cdecl isUpdated() = 0 ;
	virtual _di_NSManagedObjectContext __cdecl managedObjectContext() = 0 ;
	virtual _di_NSManagedObjectID __cdecl objectID() = 0 ;
	virtual void * __cdecl observationInfo() = 0 ;
	virtual void __cdecl prepareForDeletion() = 0 ;
	virtual void * __cdecl primitiveValueForKey(Iosapi::Foundation::_di_NSString key) = 0 ;
	virtual void __cdecl setObservationInfo(void * inObservationInfo) = 0 ;
	virtual void __cdecl setPrimitiveValue(void * value, Iosapi::Foundation::_di_NSString forKey) = 0 ;
	virtual void __cdecl setValue(void * value, Iosapi::Foundation::_di_NSString forKey) = 0 ;
	virtual bool __cdecl validateForDelete(Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual bool __cdecl validateForInsert(Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual bool __cdecl validateForUpdate(Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual bool __cdecl validateValue(void * value, Iosapi::Foundation::_di_NSString forKey, Iosapi::Foundation::_di_NSError error) = 0 ;
	HIDESBASE virtual void * __cdecl valueForKey(Iosapi::Foundation::_di_NSString key) = 0 ;
	virtual void __cdecl willAccessValueForKey(Iosapi::Foundation::_di_NSString key) = 0 ;
	virtual void __cdecl willChangeValueForKey(Iosapi::Foundation::_di_NSString key) = 0 /* overload */;
	virtual void __cdecl willChangeValueForKey(Iosapi::Foundation::_di_NSString inKey, unsigned long withSetMutation, Iosapi::Foundation::_di_NSSet usingObjects) = 0 /* overload */;
	virtual void __cdecl willSave() = 0 ;
	virtual void __cdecl willTurnIntoFault() = 0 ;
};

class PASCALIMPLEMENTATION TNSManagedObject : public Macapi::Objectivec::TOCGenericImport__2<_di_NSManagedObjectClass,_di_NSManagedObject>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSManagedObjectClass,_di_NSManagedObject> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSManagedObject(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSManagedObjectClass,_di_NSManagedObject>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSManagedObject() { }
	
};


__interface  INTERFACE_UUID("{6B39438F-7DCE-47BD-AFA3-63A3A5141AE8}") NSEntityMappingClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{77B2622D-863F-44C0-A133-EE601C64C30D}") NSEntityMapping  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl attributeMappings() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl destinationEntityName() = 0 ;
	virtual Iosapi::Foundation::_di_NSData __cdecl destinationEntityVersionHash() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl entityMigrationPolicyClassName() = 0 ;
	virtual unsigned long __cdecl mappingType() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl relationshipMappings() = 0 ;
	virtual void __cdecl setAttributeMappings(Iosapi::Foundation::_di_NSArray mappings) = 0 ;
	virtual void __cdecl setDestinationEntityName(Iosapi::Foundation::_di_NSString name) = 0 ;
	virtual void __cdecl setDestinationEntityVersionHash(Iosapi::Foundation::_di_NSData vhash) = 0 ;
	virtual void __cdecl setEntityMigrationPolicyClassName(Iosapi::Foundation::_di_NSString name) = 0 ;
	virtual void __cdecl setMappingType(unsigned long type_) = 0 ;
	virtual void __cdecl setName(Iosapi::Foundation::_di_NSString name) = 0 ;
	virtual void __cdecl setRelationshipMappings(Iosapi::Foundation::_di_NSArray mappings) = 0 ;
	virtual void __cdecl setSourceEntityName(Iosapi::Foundation::_di_NSString name) = 0 ;
	virtual void __cdecl setSourceEntityVersionHash(Iosapi::Foundation::_di_NSData vhash) = 0 ;
	virtual void __cdecl setSourceExpression(Iosapi::Foundation::_di_NSExpression source) = 0 ;
	virtual void __cdecl setUserInfo(Iosapi::Foundation::_di_NSDictionary dict) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl sourceEntityName() = 0 ;
	virtual Iosapi::Foundation::_di_NSData __cdecl sourceEntityVersionHash() = 0 ;
	virtual Iosapi::Foundation::_di_NSExpression __cdecl sourceExpression() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl userInfo() = 0 ;
};

class PASCALIMPLEMENTATION TNSEntityMapping : public Macapi::Objectivec::TOCGenericImport__2<_di_NSEntityMappingClass,_di_NSEntityMapping>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSEntityMappingClass,_di_NSEntityMapping> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSEntityMapping(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSEntityMappingClass,_di_NSEntityMapping>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSEntityMapping() { }
	
};


__interface  INTERFACE_UUID("{24AE98EA-97C8-4AA2-BE7F-9F67D8177F8E}") NSEntityMigrationPolicyClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{D0E1C6D4-2750-4F30-96A6-01FE1646B106}") NSEntityMigrationPolicy  : public Iosapi::Foundation::NSObject 
{
	virtual bool __cdecl beginEntityMapping(_di_NSEntityMapping mapping, _di_NSMigrationManager manager, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual bool __cdecl createDestinationInstancesForSourceInstance(_di_NSManagedObject sInstance, _di_NSEntityMapping entityMapping, _di_NSMigrationManager manager, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual bool __cdecl createRelationshipsForDestinationInstance(_di_NSManagedObject dInstance, _di_NSEntityMapping entityMapping, _di_NSMigrationManager manager, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual bool __cdecl endEntityMapping(_di_NSEntityMapping mapping, _di_NSMigrationManager manager, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual bool __cdecl endInstanceCreationForEntityMapping(_di_NSEntityMapping mapping, _di_NSMigrationManager manager, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual bool __cdecl endRelationshipCreationForEntityMapping(_di_NSEntityMapping mapping, _di_NSMigrationManager manager, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual bool __cdecl performCustomValidationForEntityMapping(_di_NSEntityMapping mapping, _di_NSMigrationManager manager, Iosapi::Foundation::_di_NSError error) = 0 ;
};

class PASCALIMPLEMENTATION TNSEntityMigrationPolicy : public Macapi::Objectivec::TOCGenericImport__2<_di_NSEntityMigrationPolicyClass,_di_NSEntityMigrationPolicy>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSEntityMigrationPolicyClass,_di_NSEntityMigrationPolicy> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSEntityMigrationPolicy(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSEntityMigrationPolicyClass,_di_NSEntityMigrationPolicy>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSEntityMigrationPolicy() { }
	
};


__interface  INTERFACE_UUID("{EBDD6FE0-5B68-4AC9-AB60-24775C4D844D}") NSAtomicStoreCacheNodeClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{7D98386A-FC49-485A-8634-4745ADEF18F6}") NSAtomicStoreCacheNode  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl initWithObjectID(_di_NSManagedObjectID moid) = 0 ;
	virtual _di_NSManagedObjectID __cdecl objectID() = 0 ;
	virtual Iosapi::Foundation::_di_NSMutableDictionary __cdecl propertyCache() = 0 ;
	virtual void __cdecl setPropertyCache(Iosapi::Foundation::_di_NSMutableDictionary propertyCache) = 0 ;
	virtual void __cdecl setValue(void * value, Iosapi::Foundation::_di_NSString forKey) = 0 ;
	HIDESBASE virtual void * __cdecl valueForKey(Iosapi::Foundation::_di_NSString key) = 0 ;
};

class PASCALIMPLEMENTATION TNSAtomicStoreCacheNode : public Macapi::Objectivec::TOCGenericImport__2<_di_NSAtomicStoreCacheNodeClass,_di_NSAtomicStoreCacheNode>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSAtomicStoreCacheNodeClass,_di_NSAtomicStoreCacheNode> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSAtomicStoreCacheNode(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSAtomicStoreCacheNodeClass,_di_NSAtomicStoreCacheNode>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSAtomicStoreCacheNode() { }
	
};


__interface  INTERFACE_UUID("{C7FE5391-A70E-45F7-BFCA-BEAF0F15481D}") NSEntityDescriptionClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void * __cdecl entityForName(Iosapi::Foundation::_di_NSString entityName, _di_NSManagedObjectContext inManagedObjectContext) = 0 ;
	virtual void * __cdecl insertNewObjectForEntityForName(Iosapi::Foundation::_di_NSString entityName, _di_NSManagedObjectContext inManagedObjectContext) = 0 ;
};

__interface  INTERFACE_UUID("{76DD39A4-1905-4DDE-9021-C2F14C89E1BB}") NSEntityDescription  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl attributesByName() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl compoundIndexes() = 0 ;
	virtual bool __cdecl isAbstract() = 0 ;
	virtual bool __cdecl isKindOfEntity(_di_NSEntityDescription entity) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl managedObjectClassName() = 0 ;
	virtual _di_NSManagedObjectModel __cdecl managedObjectModel() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl properties() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl propertiesByName() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl relationshipsByName() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl relationshipsWithDestinationEntity(_di_NSEntityDescription entity) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl renamingIdentifier() = 0 ;
	virtual void __cdecl setAbstract(bool flag) = 0 ;
	virtual void __cdecl setCompoundIndexes(Iosapi::Foundation::_di_NSArray value) = 0 ;
	virtual void __cdecl setManagedObjectClassName(Iosapi::Foundation::_di_NSString name) = 0 ;
	virtual void __cdecl setName(Iosapi::Foundation::_di_NSString name) = 0 ;
	virtual void __cdecl setProperties(Iosapi::Foundation::_di_NSArray properties) = 0 ;
	virtual void __cdecl setRenamingIdentifier(Iosapi::Foundation::_di_NSString value) = 0 ;
	virtual void __cdecl setSubentities(Iosapi::Foundation::_di_NSArray array_) = 0 ;
	virtual void __cdecl setUserInfo(Iosapi::Foundation::_di_NSDictionary dictionary) = 0 ;
	virtual void __cdecl setVersionHashModifier(Iosapi::Foundation::_di_NSString modifierString) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl subentities() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl subentitiesByName() = 0 ;
	virtual _di_NSEntityDescription __cdecl superentity() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl userInfo() = 0 ;
	virtual Iosapi::Foundation::_di_NSData __cdecl versionHash() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl versionHashModifier() = 0 ;
};

class PASCALIMPLEMENTATION TNSEntityDescription : public Macapi::Objectivec::TOCGenericImport__2<_di_NSEntityDescriptionClass,_di_NSEntityDescription>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSEntityDescriptionClass,_di_NSEntityDescription> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSEntityDescription(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSEntityDescriptionClass,_di_NSEntityDescription>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSEntityDescription() { }
	
};


__interface  INTERFACE_UUID("{330EC7A6-1685-4A35-9F46-769C14C0CC90}") NSFetchRequestExpressionClass  : public Iosapi::Foundation::NSExpressionClass 
{
	virtual Iosapi::Foundation::_di_NSExpression __cdecl expressionForFetch(Iosapi::Foundation::_di_NSExpression fetch, Iosapi::Foundation::_di_NSExpression context, bool countOnly) = 0 ;
};

__interface  INTERFACE_UUID("{AE2713C4-6106-4432-8CBC-EE4468602762}") NSFetchRequestExpression  : public Iosapi::Foundation::NSExpression 
{
	virtual Iosapi::Foundation::_di_NSExpression __cdecl contextExpression() = 0 ;
	virtual bool __cdecl isCountOnlyRequest() = 0 ;
	virtual Iosapi::Foundation::_di_NSExpression __cdecl requestExpression() = 0 ;
};

class PASCALIMPLEMENTATION TNSFetchRequestExpression : public Macapi::Objectivec::TOCGenericImport__2<_di_NSFetchRequestExpressionClass,_di_NSFetchRequestExpression>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSFetchRequestExpressionClass,_di_NSFetchRequestExpression> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSFetchRequestExpression(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSFetchRequestExpressionClass,_di_NSFetchRequestExpression>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSFetchRequestExpression() { }
	
};


__interface  INTERFACE_UUID("{B3158917-371A-4DDE-B0F0-BB2BE109BD15}") NSFetchedResultsControllerClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual void __cdecl deleteCacheWithName(Iosapi::Foundation::_di_NSString name) = 0 ;
};

__interface  INTERFACE_UUID("{E77C61EA-F5B0-40AA-9F6C-224B27945043}") NSFetchedResultsController  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl cacheName() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual _di_NSFetchRequest __cdecl fetchRequest() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl fetchedObjects() = 0 ;
	virtual Iosapi::Foundation::_di_NSIndexPath __cdecl indexPathForObject(void * object_) = 0 ;
	virtual void * __cdecl initWithFetchRequest(_di_NSFetchRequest fetchRequest, _di_NSManagedObjectContext managedObjectContext, Iosapi::Foundation::_di_NSString sectionNameKeyPath, Iosapi::Foundation::_di_NSString cacheName) = 0 ;
	virtual _di_NSManagedObjectContext __cdecl managedObjectContext() = 0 ;
	virtual void * __cdecl objectAtIndexPath(Iosapi::Foundation::_di_NSIndexPath indexPath) = 0 ;
	virtual bool __cdecl performFetch(Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual long __cdecl sectionForSectionIndexTitle(Iosapi::Foundation::_di_NSString title, long atIndex) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl sectionIndexTitleForSectionName(Iosapi::Foundation::_di_NSString sectionName) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl sectionIndexTitles() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl sectionNameKeyPath() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl sections() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
};

class PASCALIMPLEMENTATION TNSFetchedResultsController : public Macapi::Objectivec::TOCGenericImport__2<_di_NSFetchedResultsControllerClass,_di_NSFetchedResultsController>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSFetchedResultsControllerClass,_di_NSFetchedResultsController> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSFetchedResultsController(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSFetchedResultsControllerClass,_di_NSFetchedResultsController>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSFetchedResultsController() { }
	
};


__interface  INTERFACE_UUID("{C1A16F62-6B77-4F02-A1D7-E89AD712813A}") NSIncrementalStoreNodeClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{0054849A-1220-4897-8C7C-4A46AAD113BE}") NSIncrementalStoreNode  : public Iosapi::Foundation::NSObject 
{
	virtual void * __cdecl initWithObjectID(_di_NSManagedObjectID objectID, Iosapi::Foundation::_di_NSDictionary withValues, unsigned __int64 version) = 0 ;
	virtual _di_NSManagedObjectID __cdecl objectID() = 0 ;
	virtual void __cdecl updateWithValues(Iosapi::Foundation::_di_NSDictionary values, unsigned __int64 version) = 0 ;
	virtual void * __cdecl valueForPropertyDescription(_di_NSPropertyDescription prop) = 0 ;
	virtual unsigned __int64 __cdecl version() = 0 ;
};

class PASCALIMPLEMENTATION TNSIncrementalStoreNode : public Macapi::Objectivec::TOCGenericImport__2<_di_NSIncrementalStoreNodeClass,_di_NSIncrementalStoreNode>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSIncrementalStoreNodeClass,_di_NSIncrementalStoreNode> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSIncrementalStoreNode(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSIncrementalStoreNodeClass,_di_NSIncrementalStoreNode>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSIncrementalStoreNode() { }
	
};


__interface  INTERFACE_UUID("{DEB77ED2-9713-40CD-BE4D-8BE25BAAC95F}") NSAtomicStoreClass  : public NSPersistentStoreClass 
{
	
};

__interface  INTERFACE_UUID("{87C90CF6-E7D7-4C18-A35E-ED885A53A740}") NSAtomicStore  : public NSPersistentStore 
{
	virtual void __cdecl addCacheNodes(Iosapi::Foundation::_di_NSSet cacheNodes) = 0 ;
	virtual _di_NSAtomicStoreCacheNode __cdecl cacheNodeForObjectID(_di_NSManagedObjectID objectID) = 0 ;
	virtual Iosapi::Foundation::_di_NSSet __cdecl cacheNodes() = 0 ;
	HIDESBASE virtual void * __cdecl initWithPersistentStoreCoordinator(_di_NSPersistentStoreCoordinator coordinator, Iosapi::Foundation::_di_NSString configurationName, Iosapi::Foundation::_di_NSURL URL, Iosapi::Foundation::_di_NSDictionary options) = 0 ;
	virtual bool __cdecl load(Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual _di_NSAtomicStoreCacheNode __cdecl newCacheNodeForManagedObject(_di_NSManagedObject managedObject) = 0 ;
	virtual void * __cdecl newReferenceObjectForManagedObject(_di_NSManagedObject managedObject) = 0 ;
	virtual _di_NSManagedObjectID __cdecl objectIDForEntity(_di_NSEntityDescription entity, void * referenceObject) = 0 ;
	virtual void * __cdecl referenceObjectForObjectID(_di_NSManagedObjectID objectID) = 0 ;
	virtual bool __cdecl save(Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl updateCacheNode(_di_NSAtomicStoreCacheNode node, _di_NSManagedObject fromManagedObject) = 0 ;
	virtual void __cdecl willRemoveCacheNodes(Iosapi::Foundation::_di_NSSet cacheNodes) = 0 ;
};

class PASCALIMPLEMENTATION TNSAtomicStore : public Macapi::Objectivec::TOCGenericImport__2<_di_NSAtomicStoreClass,_di_NSAtomicStore>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSAtomicStoreClass,_di_NSAtomicStore> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSAtomicStore(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSAtomicStoreClass,_di_NSAtomicStore>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSAtomicStore() { }
	
};


__interface  INTERFACE_UUID("{7374668B-52CA-4929-9EB6-CF2D659081FA}") NSSaveChangesRequestClass  : public NSPersistentStoreRequestClass 
{
	
};

__interface  INTERFACE_UUID("{C31BD3D0-DAC0-47A0-92EF-19E040A934EC}") NSSaveChangesRequest  : public NSPersistentStoreRequest 
{
	virtual Iosapi::Foundation::_di_NSSet __cdecl deletedObjects() = 0 ;
	virtual void * __cdecl initWithInsertedObjects(Iosapi::Foundation::_di_NSSet insertedObjects, Iosapi::Foundation::_di_NSSet updatedObjects, Iosapi::Foundation::_di_NSSet deletedObjects, Iosapi::Foundation::_di_NSSet lockedObjects) = 0 ;
	virtual Iosapi::Foundation::_di_NSSet __cdecl insertedObjects() = 0 ;
	virtual Iosapi::Foundation::_di_NSSet __cdecl lockedObjects() = 0 ;
	virtual Iosapi::Foundation::_di_NSSet __cdecl updatedObjects() = 0 ;
};

class PASCALIMPLEMENTATION TNSSaveChangesRequest : public Macapi::Objectivec::TOCGenericImport__2<_di_NSSaveChangesRequestClass,_di_NSSaveChangesRequest>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSSaveChangesRequestClass,_di_NSSaveChangesRequest> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSSaveChangesRequest(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSSaveChangesRequestClass,_di_NSSaveChangesRequest>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSSaveChangesRequest() { }
	
};


__interface  INTERFACE_UUID("{C6A58AA6-048C-41A1-9039-5BFEC691CD88}") NSRelationshipDescriptionClass  : public NSPropertyDescriptionClass 
{
	
};

__interface  INTERFACE_UUID("{809570AE-1E79-488D-8999-8B7FCBE63A00}") NSRelationshipDescription  : public NSPropertyDescription 
{
	virtual unsigned long __cdecl deleteRule() = 0 ;
	virtual _di_NSEntityDescription __cdecl destinationEntity() = 0 ;
	virtual _di_NSRelationshipDescription __cdecl inverseRelationship() = 0 ;
	virtual bool __cdecl isOrdered() = 0 ;
	virtual bool __cdecl isToMany() = 0 ;
	virtual unsigned long __cdecl maxCount() = 0 ;
	virtual unsigned long __cdecl minCount() = 0 ;
	virtual void __cdecl setDeleteRule(unsigned long rule) = 0 ;
	virtual void __cdecl setDestinationEntity(_di_NSEntityDescription entity) = 0 ;
	virtual void __cdecl setInverseRelationship(_di_NSRelationshipDescription relationship) = 0 ;
	virtual void __cdecl setMaxCount(unsigned long maxCount) = 0 ;
	virtual void __cdecl setMinCount(unsigned long minCount) = 0 ;
	virtual void __cdecl setOrdered(bool flag) = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSData __cdecl versionHash() = 0 ;
};

class PASCALIMPLEMENTATION TNSRelationshipDescription : public Macapi::Objectivec::TOCGenericImport__2<_di_NSRelationshipDescriptionClass,_di_NSRelationshipDescription>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSRelationshipDescriptionClass,_di_NSRelationshipDescription> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSRelationshipDescription(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSRelationshipDescriptionClass,_di_NSRelationshipDescription>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSRelationshipDescription() { }
	
};


__interface  INTERFACE_UUID("{D4C64F53-2034-4093-B587-4954E50E1E9B}") NSAttributeDescriptionClass  : public NSPropertyDescriptionClass 
{
	
};

__interface  INTERFACE_UUID("{E7525400-E928-4C30-9637-D3B5B3C78DEF}") NSAttributeDescription  : public NSPropertyDescription 
{
	virtual bool __cdecl allowsExternalBinaryDataStorage() = 0 ;
	virtual unsigned long __cdecl attributeType() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl attributeValueClassName() = 0 ;
	virtual void * __cdecl defaultValue() = 0 ;
	virtual void __cdecl setAllowsExternalBinaryDataStorage(bool flag) = 0 ;
	virtual void __cdecl setAttributeType(unsigned long type_) = 0 ;
	virtual void __cdecl setAttributeValueClassName(Iosapi::Foundation::_di_NSString className) = 0 ;
	virtual void __cdecl setDefaultValue(void * value) = 0 ;
	virtual void __cdecl setValueTransformerName(Iosapi::Foundation::_di_NSString string_) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl valueTransformerName() = 0 ;
	HIDESBASE virtual Iosapi::Foundation::_di_NSData __cdecl versionHash() = 0 ;
};

class PASCALIMPLEMENTATION TNSAttributeDescription : public Macapi::Objectivec::TOCGenericImport__2<_di_NSAttributeDescriptionClass,_di_NSAttributeDescription>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSAttributeDescriptionClass,_di_NSAttributeDescription> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSAttributeDescription(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSAttributeDescriptionClass,_di_NSAttributeDescription>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSAttributeDescription() { }
	
};


__interface  INTERFACE_UUID("{43D4D384-9FC3-40D6-B02E-35F646D82FF8}") NSExpressionDescriptionClass  : public NSPropertyDescriptionClass 
{
	
};

__interface  INTERFACE_UUID("{B2E09F7C-396B-4B25-92A9-0527C32F1CB2}") NSExpressionDescription  : public NSPropertyDescription 
{
	virtual Iosapi::Foundation::_di_NSExpression __cdecl expression() = 0 ;
	virtual unsigned long __cdecl expressionResultType() = 0 ;
	virtual void __cdecl setExpression(Iosapi::Foundation::_di_NSExpression expression) = 0 ;
	virtual void __cdecl setExpressionResultType(unsigned long type_) = 0 ;
};

class PASCALIMPLEMENTATION TNSExpressionDescription : public Macapi::Objectivec::TOCGenericImport__2<_di_NSExpressionDescriptionClass,_di_NSExpressionDescription>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSExpressionDescriptionClass,_di_NSExpressionDescription> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSExpressionDescription(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSExpressionDescriptionClass,_di_NSExpressionDescription>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSExpressionDescription() { }
	
};


__interface  INTERFACE_UUID("{BCB5CC13-82B7-41B7-8729-F68BE8FFB513}") NSFetchRequestClass  : public NSPersistentStoreRequestClass 
{
	virtual void * __cdecl fetchRequestWithEntityName(Iosapi::Foundation::_di_NSString entityName) = 0 ;
};

__interface  INTERFACE_UUID("{A9C2B82B-5C6C-4CD5-B6DF-3F18CEC79A95}") NSFetchRequest  : public NSPersistentStoreRequest 
{
	HIDESBASE virtual Iosapi::Foundation::_di_NSArray __cdecl affectedStores() = 0 ;
	virtual _di_NSEntityDescription __cdecl entity() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl entityName() = 0 ;
	virtual unsigned long __cdecl fetchBatchSize() = 0 ;
	virtual unsigned long __cdecl fetchLimit() = 0 ;
	virtual unsigned long __cdecl fetchOffset() = 0 ;
	virtual Iosapi::Foundation::_di_NSPredicate __cdecl havingPredicate() = 0 ;
	virtual bool __cdecl includesPendingChanges() = 0 ;
	virtual bool __cdecl includesPropertyValues() = 0 ;
	virtual bool __cdecl includesSubentities() = 0 ;
	HIDESBASE virtual void * __cdecl init() = 0 ;
	virtual void * __cdecl initWithEntityName(Iosapi::Foundation::_di_NSString entityName) = 0 ;
	virtual Iosapi::Foundation::_di_NSPredicate __cdecl predicate() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl propertiesToFetch() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl propertiesToGroupBy() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl relationshipKeyPathsForPrefetching() = 0 ;
	virtual unsigned long __cdecl resultType() = 0 ;
	virtual bool __cdecl returnsDistinctResults() = 0 ;
	virtual bool __cdecl returnsObjectsAsFaults() = 0 ;
	HIDESBASE virtual void __cdecl setAffectedStores(Iosapi::Foundation::_di_NSArray stores) = 0 ;
	virtual void __cdecl setEntity(_di_NSEntityDescription entity) = 0 ;
	virtual void __cdecl setFetchBatchSize(unsigned long bsize) = 0 ;
	virtual void __cdecl setFetchLimit(unsigned long limit) = 0 ;
	virtual void __cdecl setFetchOffset(unsigned long offset) = 0 ;
	virtual void __cdecl setHavingPredicate(Iosapi::Foundation::_di_NSPredicate predicate) = 0 ;
	virtual void __cdecl setIncludesPendingChanges(bool flag) = 0 ;
	virtual void __cdecl setIncludesPropertyValues(bool yesNo) = 0 ;
	virtual void __cdecl setIncludesSubentities(bool yesNo) = 0 ;
	virtual void __cdecl setPredicate(Iosapi::Foundation::_di_NSPredicate predicate) = 0 ;
	virtual void __cdecl setPropertiesToFetch(Iosapi::Foundation::_di_NSArray values) = 0 ;
	virtual void __cdecl setPropertiesToGroupBy(Iosapi::Foundation::_di_NSArray array_) = 0 ;
	virtual void __cdecl setRelationshipKeyPathsForPrefetching(Iosapi::Foundation::_di_NSArray keys) = 0 ;
	virtual void __cdecl setResultType(unsigned long type_) = 0 ;
	virtual void __cdecl setReturnsDistinctResults(bool flag) = 0 ;
	virtual void __cdecl setReturnsObjectsAsFaults(bool yesNo) = 0 ;
	virtual void __cdecl setShouldRefreshRefetchedObjects(bool flag) = 0 ;
	virtual void __cdecl setSortDescriptors(Iosapi::Foundation::_di_NSArray sortDescriptors) = 0 ;
	virtual bool __cdecl shouldRefreshRefetchedObjects() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl sortDescriptors() = 0 ;
};

class PASCALIMPLEMENTATION TNSFetchRequest : public Macapi::Objectivec::TOCGenericImport__2<_di_NSFetchRequestClass,_di_NSFetchRequest>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSFetchRequestClass,_di_NSFetchRequest> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSFetchRequest(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSFetchRequestClass,_di_NSFetchRequest>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSFetchRequest() { }
	
};


__interface  INTERFACE_UUID("{7930BC8D-E524-4CF2-A5F9-9DAC1EDF8CE4}") NSIncrementalStoreClass  : public NSPersistentStoreClass 
{
	virtual void * __cdecl identifierForNewStoreAtURL(Iosapi::Foundation::_di_NSURL storeURL) = 0 ;
};

__interface  INTERFACE_UUID("{F44000C5-5E2A-4331-B6D2-6056DD2E0F7D}") NSIncrementalStore  : public NSPersistentStore 
{
	virtual void * __cdecl executeRequest(_di_NSPersistentStoreRequest request, _di_NSManagedObjectContext withContext, Iosapi::Foundation::_di_NSError error) = 0 ;
	HIDESBASE virtual bool __cdecl loadMetadata(Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void __cdecl managedObjectContextDidRegisterObjectsWithIDs(Iosapi::Foundation::_di_NSArray objectIDs) = 0 ;
	virtual void __cdecl managedObjectContextDidUnregisterObjectsWithIDs(Iosapi::Foundation::_di_NSArray objectIDs) = 0 ;
	virtual _di_NSManagedObjectID __cdecl newObjectIDForEntity(_di_NSEntityDescription entity, void * referenceObject) = 0 ;
	virtual void * __cdecl newValueForRelationship(_di_NSRelationshipDescription relationship, _di_NSManagedObjectID forObjectWithID, _di_NSManagedObjectContext withContext, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual _di_NSIncrementalStoreNode __cdecl newValuesForObjectWithID(_di_NSManagedObjectID objectID, _di_NSManagedObjectContext withContext, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl obtainPermanentIDsForObjects(Iosapi::Foundation::_di_NSArray array_, Iosapi::Foundation::_di_NSError error) = 0 ;
	virtual void * __cdecl referenceObjectForObjectID(_di_NSManagedObjectID objectID) = 0 ;
};

class PASCALIMPLEMENTATION TNSIncrementalStore : public Macapi::Objectivec::TOCGenericImport__2<_di_NSIncrementalStoreClass,_di_NSIncrementalStore>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSIncrementalStoreClass,_di_NSIncrementalStore> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSIncrementalStore(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSIncrementalStoreClass,_di_NSIncrementalStore>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSIncrementalStore() { }
	
};


__interface  INTERFACE_UUID("{4E7F3A8B-93BA-4906-BC29-1C49A893F4A1}") NSFetchedPropertyDescriptionClass  : public NSPropertyDescriptionClass 
{
	
};

__interface  INTERFACE_UUID("{5108171A-1F8A-4C6C-B7C1-9C41A613E283}") NSFetchedPropertyDescription  : public NSPropertyDescription 
{
	virtual _di_NSFetchRequest __cdecl fetchRequest() = 0 ;
	virtual void __cdecl setFetchRequest(_di_NSFetchRequest fetchRequest) = 0 ;
};

class PASCALIMPLEMENTATION TNSFetchedPropertyDescription : public Macapi::Objectivec::TOCGenericImport__2<_di_NSFetchedPropertyDescriptionClass,_di_NSFetchedPropertyDescription>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSFetchedPropertyDescriptionClass,_di_NSFetchedPropertyDescription> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSFetchedPropertyDescription(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSFetchedPropertyDescriptionClass,_di_NSFetchedPropertyDescription>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSFetchedPropertyDescription() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 NSAddEntityMappingType = System::Int8(0x2);
static constexpr System::Word NSBinaryDataAttributeType = System::Word(0x3e8);
static constexpr System::Word NSBooleanAttributeType = System::Word(0x320);
static constexpr System::Int8 NSCascadeDeleteRule = System::Int8(0x2);
static constexpr System::Int8 NSConfinementConcurrencyType = System::Int8(0x0);
static constexpr System::Int8 NSCopyEntityMappingType = System::Int8(0x4);
static constexpr int NSCoreDataError = int(0x20bac);
#define NSCoreDataVersionNumber10_4  (4.600000E+01)
#define NSCoreDataVersionNumber10_4_3  (7.700000E+01)
#define NSCoreDataVersionNumber10_5  (1.850000E+02)
#define NSCoreDataVersionNumber10_5_3  (1.860000E+02)
#define NSCoreDataVersionNumber10_6  (2.460000E+02)
#define NSCoreDataVersionNumber10_6_2  (2.500000E+02)
#define NSCoreDataVersionNumber10_6_3  (2.510000E+02)
#define NSCoreDataVersionNumber_iPhoneOS_3_0  (2.410000E+02)
#define NSCoreDataVersionNumber_iPhoneOS_3_1  (2.480000E+02)
#define NSCoreDataVersionNumber_iPhoneOS_3_2  (3.102000E+02)
#define NSCoreDataVersionNumber_iPhoneOS_4_0  (3.205000E+02)
#define NSCoreDataVersionNumber_iPhoneOS_4_1  (3.201100E+02)
#define NSCoreDataVersionNumber_iPhoneOS_4_2  (3.201500E+02)
#define NSCoreDataVersionNumber_iPhoneOS_4_3  (3.201700E+02)
static constexpr System::Int8 NSCountResultType = System::Int8(0x4);
static constexpr System::Int8 NSCustomEntityMappingType = System::Int8(0x1);
static constexpr System::Word NSDateAttributeType = System::Word(0x384);
static constexpr System::Word NSDecimalAttributeType = System::Word(0x190);
static constexpr System::Int8 NSDenyDeleteRule = System::Int8(0x3);
static constexpr System::Int8 NSDictionaryResultType = System::Int8(0x2);
static constexpr System::Word NSDoubleAttributeType = System::Word(0x1f4);
static constexpr int NSEntityMigrationPolicyError = int(0x20c1a);
static constexpr System::Int8 NSErrorMergePolicyType = System::Int8(0x0);
static constexpr int NSExternalRecordImportError = int(0x20c38);
static constexpr System::Int8 NSFetchRequestExpressionType = System::Int8(0x32);
static constexpr System::Int8 NSFetchRequestType = System::Int8(0x1);
static constexpr System::Int8 NSFetchedResultsChangeDelete = System::Int8(0x2);
static constexpr System::Int8 NSFetchedResultsChangeInsert = System::Int8(0x1);
static constexpr System::Int8 NSFetchedResultsChangeMove = System::Int8(0x3);
static constexpr System::Int8 NSFetchedResultsChangeUpdate = System::Int8(0x4);
static constexpr System::Word NSFloatAttributeType = System::Word(0x258);
static constexpr int NSInferredMappingModelError = int(0x20c2e);
static constexpr System::Int8 NSInteger16AttributeType = System::Int8(0x64);
static constexpr System::Byte NSInteger32AttributeType = System::Byte(0xc8);
static constexpr System::Word NSInteger64AttributeType = System::Word(0x12c);
static constexpr System::Int8 NSMainQueueConcurrencyType = System::Int8(0x2);
static constexpr int NSManagedObjectContextLockingError = int(0x203a0);
static constexpr int NSManagedObjectExternalRelationshipError = int(0x20792);
static constexpr System::Int8 NSManagedObjectIDResultType = System::Int8(0x1);
static constexpr int NSManagedObjectMergeError = int(0x2079c);
static constexpr int NSManagedObjectReferentialIntegrityError = int(0x20788);
static constexpr System::Int8 NSManagedObjectResultType = System::Int8(0x0);
static constexpr System::Word NSManagedObjectValidationError = System::Word(0x60e);
static constexpr System::Int8 NSMergeByPropertyObjectTrumpMergePolicyType = System::Int8(0x2);
static constexpr System::Int8 NSMergeByPropertyStoreTrumpMergePolicyType = System::Int8(0x1);
static constexpr int NSMigrationCancelledError = int(0x20be8);
static constexpr int NSMigrationError = int(0x20bde);
static constexpr int NSMigrationManagerDestinationStoreError = int(0x20c10);
static constexpr int NSMigrationManagerSourceStoreError = int(0x20c06);
static constexpr int NSMigrationMissingMappingModelError = int(0x20bfc);
static constexpr int NSMigrationMissingSourceModelError = int(0x20bf2);
static constexpr System::Int8 NSNoActionDeleteRule = System::Int8(0x0);
static constexpr System::Int8 NSNullifyDeleteRule = System::Int8(0x1);
static constexpr System::Word NSObjectIDAttributeType = System::Word(0x7d0);
static constexpr System::Int8 NSOverwriteMergePolicyType = System::Int8(0x3);
static constexpr int NSPersistentStoreCoordinatorLockingError = int(0x203aa);
static constexpr int NSPersistentStoreIncompatibleSchemaError = int(0x20b84);
static constexpr int NSPersistentStoreIncompatibleVersionHashError = int(0x20bd4);
static constexpr int NSPersistentStoreIncompleteSaveError = int(0x20b98);
static constexpr int NSPersistentStoreInvalidTypeError = int(0x20b70);
static constexpr int NSPersistentStoreOpenError = int(0x20bc0);
static constexpr int NSPersistentStoreOperationError = int(0x20bb6);
static constexpr int NSPersistentStoreSaveConflictsError = int(0x20ba2);
static constexpr int NSPersistentStoreSaveError = int(0x20b8e);
static constexpr int NSPersistentStoreTimeoutError = int(0x20bca);
static constexpr int NSPersistentStoreTypeMismatchError = int(0x20b7a);
static constexpr int NSPersistentStoreUnsupportedRequestTypeError = int(0x20bcb);
static constexpr System::Int8 NSPrivateQueueConcurrencyType = System::Int8(0x1);
static constexpr System::Int8 NSRemoveEntityMappingType = System::Int8(0x3);
static constexpr System::Int8 NSRollbackMergePolicyType = System::Int8(0x4);
static constexpr int NSSQLiteError = int(0x20c24);
static constexpr System::Int8 NSSaveRequestType = System::Int8(0x2);
static constexpr System::Int8 NSSnapshotEventMergePolicy = System::Int8(0x40);
static constexpr System::Int8 NSSnapshotEventRefresh = System::Int8(0x20);
static constexpr System::Int8 NSSnapshotEventRollback = System::Int8(0x10);
static constexpr System::Int8 NSSnapshotEventUndoDeletion = System::Int8(0x4);
static constexpr System::Int8 NSSnapshotEventUndoInsertion = System::Int8(0x2);
static constexpr System::Int8 NSSnapshotEventUndoUpdate = System::Int8(0x8);
static constexpr System::Word NSStringAttributeType = System::Word(0x2bc);
static constexpr System::Int8 NSTransformEntityMappingType = System::Int8(0x5);
static constexpr System::Word NSTransformableAttributeType = System::Word(0x708);
static constexpr System::Int8 NSUndefinedAttributeType = System::Int8(0x0);
static constexpr System::Int8 NSUndefinedEntityMappingType = System::Int8(0x0);
static constexpr System::Word NSValidationDateTooLateError = System::Word(0x65e);
static constexpr System::Word NSValidationDateTooSoonError = System::Word(0x668);
static constexpr System::Word NSValidationInvalidDateError = System::Word(0x672);
static constexpr System::Word NSValidationMissingMandatoryPropertyError = System::Word(0x622);
static constexpr System::Word NSValidationMultipleErrorsError = System::Word(0x618);
static constexpr System::Word NSValidationNumberTooLargeError = System::Word(0x64a);
static constexpr System::Word NSValidationNumberTooSmallError = System::Word(0x654);
static constexpr System::Word NSValidationRelationshipDeniedDeleteError = System::Word(0x640);
static constexpr System::Word NSValidationRelationshipExceedsMaximumCountError = System::Word(0x636);
static constexpr System::Word NSValidationRelationshipLacksMinimumCountError = System::Word(0x62c);
static constexpr System::Word NSValidationStringPatternMatchingError = System::Word(0x690);
static constexpr System::Word NSValidationStringTooLongError = System::Word(0x67c);
static constexpr System::Word NSValidationStringTooShortError = System::Word(0x686);
#define libCoreData u"/System/Library/Frameworks/CoreData.framework/CoreData"
}	/* namespace Coredata */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_COREDATA)
using namespace Iosapi::Coredata;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_CoredataHPP
