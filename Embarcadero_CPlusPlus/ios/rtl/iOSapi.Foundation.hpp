// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.Foundation.pas' rev: 34.00 (iOS)

#ifndef Iosapi_FoundationHPP
#define Iosapi_FoundationHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Math.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <Macapi.CoreFoundation.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <Macapi.ObjCRuntime.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Foundation
{
//-- forward type declarations -----------------------------------------------
struct NSDecimal;
struct NSRange;
struct NSPoint;
struct NSSize;
struct NSRect;
__interface DELPHIINTERFACE NSString;
typedef System::DelphiInterface<NSString> _di_NSString;
__interface DELPHIINTERFACE NSObjectClass;
typedef System::DelphiInterface<NSObjectClass> _di_NSObjectClass;
__interface DELPHIINTERFACE NSObject;
typedef System::DelphiInterface<NSObject> _di_NSObject;
class DELPHICLASS TNSObject;
__interface DELPHIINTERFACE NSTimerClass;
typedef System::DelphiInterface<NSTimerClass> _di_NSTimerClass;
__interface DELPHIINTERFACE NSTimer;
typedef System::DelphiInterface<NSTimer> _di_NSTimer;
class DELPHICLASS TNSTimer;
__interface DELPHIINTERFACE NSTimeZoneClass;
typedef System::DelphiInterface<NSTimeZoneClass> _di_NSTimeZoneClass;
__interface DELPHIINTERFACE NSTimeZone;
typedef System::DelphiInterface<NSTimeZone> _di_NSTimeZone;
class DELPHICLASS TNSTimeZone;
__interface DELPHIINTERFACE NSURLClass;
typedef System::DelphiInterface<NSURLClass> _di_NSURLClass;
__interface DELPHIINTERFACE NSURL;
typedef System::DelphiInterface<NSURL> _di_NSURL;
class DELPHICLASS TNSURL;
__interface DELPHIINTERFACE NSMethodSignatureClass;
typedef System::DelphiInterface<NSMethodSignatureClass> _di_NSMethodSignatureClass;
__interface DELPHIINTERFACE NSMethodSignature;
typedef System::DelphiInterface<NSMethodSignature> _di_NSMethodSignature;
class DELPHICLASS TNSMethodSignature;
__interface DELPHIINTERFACE NSURLAuthenticationChallengeClass;
typedef System::DelphiInterface<NSURLAuthenticationChallengeClass> _di_NSURLAuthenticationChallengeClass;
__interface DELPHIINTERFACE NSURLAuthenticationChallenge;
typedef System::DelphiInterface<NSURLAuthenticationChallenge> _di_NSURLAuthenticationChallenge;
class DELPHICLASS TNSURLAuthenticationChallenge;
__interface DELPHIINTERFACE NSStreamClass;
typedef System::DelphiInterface<NSStreamClass> _di_NSStreamClass;
__interface DELPHIINTERFACE NSStream;
typedef System::DelphiInterface<NSStream> _di_NSStream;
class DELPHICLASS TNSStream;
__interface DELPHIINTERFACE NSSortDescriptorClass;
typedef System::DelphiInterface<NSSortDescriptorClass> _di_NSSortDescriptorClass;
__interface DELPHIINTERFACE NSSortDescriptor;
typedef System::DelphiInterface<NSSortDescriptor> _di_NSSortDescriptor;
class DELPHICLASS TNSSortDescriptor;
__interface DELPHIINTERFACE NSStringClass;
typedef System::DelphiInterface<NSStringClass> _di_NSStringClass;
class DELPHICLASS TNSString;
__interface DELPHIINTERFACE NSThreadClass;
typedef System::DelphiInterface<NSThreadClass> _di_NSThreadClass;
__interface DELPHIINTERFACE NSThread;
typedef System::DelphiInterface<NSThread> _di_NSThread;
class DELPHICLASS TNSThread;
__interface DELPHIINTERFACE NSTextCheckingResultClass;
typedef System::DelphiInterface<NSTextCheckingResultClass> _di_NSTextCheckingResultClass;
__interface DELPHIINTERFACE NSTextCheckingResult;
typedef System::DelphiInterface<NSTextCheckingResult> _di_NSTextCheckingResult;
class DELPHICLASS TNSTextCheckingResult;
__interface DELPHIINTERFACE NSMetadataQueryResultGroupClass;
typedef System::DelphiInterface<NSMetadataQueryResultGroupClass> _di_NSMetadataQueryResultGroupClass;
__interface DELPHIINTERFACE NSMetadataQueryResultGroup;
typedef System::DelphiInterface<NSMetadataQueryResultGroup> _di_NSMetadataQueryResultGroup;
class DELPHICLASS TNSMetadataQueryResultGroup;
__interface DELPHIINTERFACE NSLinguisticTaggerClass;
typedef System::DelphiInterface<NSLinguisticTaggerClass> _di_NSLinguisticTaggerClass;
__interface DELPHIINTERFACE NSLinguisticTagger;
typedef System::DelphiInterface<NSLinguisticTagger> _di_NSLinguisticTagger;
class DELPHICLASS TNSLinguisticTagger;
__interface DELPHIINTERFACE NSLocaleClass;
typedef System::DelphiInterface<NSLocaleClass> _di_NSLocaleClass;
__interface DELPHIINTERFACE NSLocale;
typedef System::DelphiInterface<NSLocale> _di_NSLocale;
class DELPHICLASS TNSLocale;
__interface DELPHIINTERFACE NSURLConnectionClass;
typedef System::DelphiInterface<NSURLConnectionClass> _di_NSURLConnectionClass;
__interface DELPHIINTERFACE NSURLConnection;
typedef System::DelphiInterface<NSURLConnection> _di_NSURLConnection;
class DELPHICLASS TNSURLConnection;
__interface DELPHIINTERFACE NSJSONSerializationClass;
typedef System::DelphiInterface<NSJSONSerializationClass> _di_NSJSONSerializationClass;
__interface DELPHIINTERFACE NSJSONSerialization;
typedef System::DelphiInterface<NSJSONSerialization> _di_NSJSONSerialization;
class DELPHICLASS TNSJSONSerialization;
__interface DELPHIINTERFACE NSURLCredentialClass;
typedef System::DelphiInterface<NSURLCredentialClass> _di_NSURLCredentialClass;
__interface DELPHIINTERFACE NSURLCredential;
typedef System::DelphiInterface<NSURLCredential> _di_NSURLCredential;
class DELPHICLASS TNSURLCredential;
__interface DELPHIINTERFACE NSMetadataQueryClass;
typedef System::DelphiInterface<NSMetadataQueryClass> _di_NSMetadataQueryClass;
__interface DELPHIINTERFACE NSMetadataQuery;
typedef System::DelphiInterface<NSMetadataQuery> _di_NSMetadataQuery;
class DELPHICLASS TNSMetadataQuery;
__interface DELPHIINTERFACE NSMetadataQueryAttributeValueTupleClass;
typedef System::DelphiInterface<NSMetadataQueryAttributeValueTupleClass> _di_NSMetadataQueryAttributeValueTupleClass;
__interface DELPHIINTERFACE NSMetadataQueryAttributeValueTuple;
typedef System::DelphiInterface<NSMetadataQueryAttributeValueTuple> _di_NSMetadataQueryAttributeValueTuple;
class DELPHICLASS TNSMetadataQueryAttributeValueTuple;
__interface DELPHIINTERFACE NSMetadataItemClass;
typedef System::DelphiInterface<NSMetadataItemClass> _di_NSMetadataItemClass;
__interface DELPHIINTERFACE NSMetadataItem;
typedef System::DelphiInterface<NSMetadataItem> _di_NSMetadataItem;
class DELPHICLASS TNSMetadataItem;
__interface DELPHIINTERFACE NSLockClass;
typedef System::DelphiInterface<NSLockClass> _di_NSLockClass;
__interface DELPHIINTERFACE NSLock;
typedef System::DelphiInterface<NSLock> _di_NSLock;
class DELPHICLASS TNSLock;
__interface DELPHIINTERFACE NSURLCacheClass;
typedef System::DelphiInterface<NSURLCacheClass> _di_NSURLCacheClass;
__interface DELPHIINTERFACE NSURLCache;
typedef System::DelphiInterface<NSURLCache> _di_NSURLCache;
class DELPHICLASS TNSURLCache;
__interface DELPHIINTERFACE NSSetClass;
typedef System::DelphiInterface<NSSetClass> _di_NSSetClass;
__interface DELPHIINTERFACE NSSet;
typedef System::DelphiInterface<NSSet> _di_NSSet;
class DELPHICLASS TNSSet;
__interface DELPHIINTERFACE NSPipeClass;
typedef System::DelphiInterface<NSPipeClass> _di_NSPipeClass;
__interface DELPHIINTERFACE NSPipe;
typedef System::DelphiInterface<NSPipe> _di_NSPipe;
class DELPHICLASS TNSPipe;
__interface DELPHIINTERFACE NSPortClass;
typedef System::DelphiInterface<NSPortClass> _di_NSPortClass;
__interface DELPHIINTERFACE NSPort;
typedef System::DelphiInterface<NSPort> _di_NSPort;
class DELPHICLASS TNSPort;
__interface DELPHIINTERFACE NSRegularExpressionClass;
typedef System::DelphiInterface<NSRegularExpressionClass> _di_NSRegularExpressionClass;
__interface DELPHIINTERFACE NSRegularExpression;
typedef System::DelphiInterface<NSRegularExpression> _di_NSRegularExpression;
class DELPHICLASS TNSRegularExpression;
__interface DELPHIINTERFACE NSOrderedSetClass;
typedef System::DelphiInterface<NSOrderedSetClass> _di_NSOrderedSetClass;
__interface DELPHIINTERFACE NSOrderedSet;
typedef System::DelphiInterface<NSOrderedSet> _di_NSOrderedSet;
class DELPHICLASS TNSOrderedSet;
__interface DELPHIINTERFACE NSOrthographyClass;
typedef System::DelphiInterface<NSOrthographyClass> _di_NSOrthographyClass;
__interface DELPHIINTERFACE NSOrthography;
typedef System::DelphiInterface<NSOrthography> _di_NSOrthography;
class DELPHICLASS TNSOrthography;
__interface DELPHIINTERFACE NSProxyClass;
typedef System::DelphiInterface<NSProxyClass> _di_NSProxyClass;
__interface DELPHIINTERFACE NSProxy;
typedef System::DelphiInterface<NSProxy> _di_NSProxy;
class DELPHICLASS TNSProxy;
__interface DELPHIINTERFACE NSRecursiveLockClass;
typedef System::DelphiInterface<NSRecursiveLockClass> _di_NSRecursiveLockClass;
__interface DELPHIINTERFACE NSRecursiveLock;
typedef System::DelphiInterface<NSRecursiveLock> _di_NSRecursiveLock;
class DELPHICLASS TNSRecursiveLock;
__interface DELPHIINTERFACE NSPropertyListSerializationClass;
typedef System::DelphiInterface<NSPropertyListSerializationClass> _di_NSPropertyListSerializationClass;
__interface DELPHIINTERFACE NSPropertyListSerialization;
typedef System::DelphiInterface<NSPropertyListSerialization> _di_NSPropertyListSerialization;
class DELPHICLASS TNSPropertyListSerialization;
__interface DELPHIINTERFACE NSPredicateClass;
typedef System::DelphiInterface<NSPredicateClass> _di_NSPredicateClass;
__interface DELPHIINTERFACE NSPredicate;
typedef System::DelphiInterface<NSPredicate> _di_NSPredicate;
class DELPHICLASS TNSPredicate;
__interface DELPHIINTERFACE NSProcessInfoClass;
typedef System::DelphiInterface<NSProcessInfoClass> _di_NSProcessInfoClass;
__interface DELPHIINTERFACE NSProcessInfo;
typedef System::DelphiInterface<NSProcessInfo> _di_NSProcessInfo;
class DELPHICLASS TNSProcessInfo;
__interface DELPHIINTERFACE NSOperationQueueClass;
typedef System::DelphiInterface<NSOperationQueueClass> _di_NSOperationQueueClass;
__interface DELPHIINTERFACE NSOperationQueue;
typedef System::DelphiInterface<NSOperationQueue> _di_NSOperationQueue;
class DELPHICLASS TNSOperationQueue;
__interface DELPHIINTERFACE NSNotificationCenterClass;
typedef System::DelphiInterface<NSNotificationCenterClass> _di_NSNotificationCenterClass;
__interface DELPHIINTERFACE NSNotificationCenter;
typedef System::DelphiInterface<NSNotificationCenter> _di_NSNotificationCenter;
class DELPHICLASS TNSNotificationCenter;
__interface DELPHIINTERFACE NSNotificationQueueClass;
typedef System::DelphiInterface<NSNotificationQueueClass> _di_NSNotificationQueueClass;
__interface DELPHIINTERFACE NSNotificationQueue;
typedef System::DelphiInterface<NSNotificationQueue> _di_NSNotificationQueue;
class DELPHICLASS TNSNotificationQueue;
__interface DELPHIINTERFACE NSNotificationClass;
typedef System::DelphiInterface<NSNotificationClass> _di_NSNotificationClass;
__interface DELPHIINTERFACE NSNotification;
typedef System::DelphiInterface<NSNotification> _di_NSNotification;
class DELPHICLASS TNSNotification;
__interface DELPHIINTERFACE NSNetServiceClass;
typedef System::DelphiInterface<NSNetServiceClass> _di_NSNetServiceClass;
__interface DELPHIINTERFACE NSNetService;
typedef System::DelphiInterface<NSNetService> _di_NSNetService;
class DELPHICLASS TNSNetService;
__interface DELPHIINTERFACE NSNetServiceBrowserClass;
typedef System::DelphiInterface<NSNetServiceBrowserClass> _di_NSNetServiceBrowserClass;
__interface DELPHIINTERFACE NSNetServiceBrowser;
typedef System::DelphiInterface<NSNetServiceBrowser> _di_NSNetServiceBrowser;
class DELPHICLASS TNSNetServiceBrowser;
__interface DELPHIINTERFACE NSOperationClass;
typedef System::DelphiInterface<NSOperationClass> _di_NSOperationClass;
__interface DELPHIINTERFACE NSOperation;
typedef System::DelphiInterface<NSOperation> _di_NSOperation;
class DELPHICLASS TNSOperation;
__interface DELPHIINTERFACE NSRunLoopClass;
typedef System::DelphiInterface<NSRunLoopClass> _di_NSRunLoopClass;
__interface DELPHIINTERFACE NSRunLoop;
typedef System::DelphiInterface<NSRunLoop> _di_NSRunLoop;
class DELPHICLASS TNSRunLoop;
__interface DELPHIINTERFACE NSNullClass;
typedef System::DelphiInterface<NSNullClass> _di_NSNullClass;
__interface DELPHIINTERFACE NSNull;
typedef System::DelphiInterface<NSNull> _di_NSNull;
class DELPHICLASS TNSNull;
__interface DELPHIINTERFACE NSScannerClass;
typedef System::DelphiInterface<NSScannerClass> _di_NSScannerClass;
__interface DELPHIINTERFACE NSScanner;
typedef System::DelphiInterface<NSScanner> _di_NSScanner;
class DELPHICLASS TNSScanner;
__interface DELPHIINTERFACE NSConditionLockClass;
typedef System::DelphiInterface<NSConditionLockClass> _di_NSConditionLockClass;
__interface DELPHIINTERFACE NSConditionLock;
typedef System::DelphiInterface<NSConditionLock> _di_NSConditionLock;
class DELPHICLASS TNSConditionLock;
__interface DELPHIINTERFACE NSUserDefaultsClass;
typedef System::DelphiInterface<NSUserDefaultsClass> _di_NSUserDefaultsClass;
__interface DELPHIINTERFACE NSUserDefaults;
typedef System::DelphiInterface<NSUserDefaults> _di_NSUserDefaults;
class DELPHICLASS TNSUserDefaults;
__interface DELPHIINTERFACE NSConditionClass;
typedef System::DelphiInterface<NSConditionClass> _di_NSConditionClass;
__interface DELPHIINTERFACE NSCondition;
typedef System::DelphiInterface<NSCondition> _di_NSCondition;
class DELPHICLASS TNSCondition;
__interface DELPHIINTERFACE NSValueTransformerClass;
typedef System::DelphiInterface<NSValueTransformerClass> _di_NSValueTransformerClass;
__interface DELPHIINTERFACE NSValueTransformer;
typedef System::DelphiInterface<NSValueTransformer> _di_NSValueTransformer;
class DELPHICLASS TNSValueTransformer;
__interface DELPHIINTERFACE NSValueClass;
typedef System::DelphiInterface<NSValueClass> _di_NSValueClass;
__interface DELPHIINTERFACE NSValue;
typedef System::DelphiInterface<NSValue> _di_NSValue;
class DELPHICLASS TNSValue;
__interface DELPHIINTERFACE NSDateComponentsClass;
typedef System::DelphiInterface<NSDateComponentsClass> _di_NSDateComponentsClass;
__interface DELPHIINTERFACE NSDateComponents;
typedef System::DelphiInterface<NSDateComponents> _di_NSDateComponents;
class DELPHICLASS TNSDateComponents;
__interface DELPHIINTERFACE NSUbiquitousKeyValueStoreClass;
typedef System::DelphiInterface<NSUbiquitousKeyValueStoreClass> _di_NSUbiquitousKeyValueStoreClass;
__interface DELPHIINTERFACE NSUbiquitousKeyValueStore;
typedef System::DelphiInterface<NSUbiquitousKeyValueStore> _di_NSUbiquitousKeyValueStore;
class DELPHICLASS TNSUbiquitousKeyValueStore;
__interface DELPHIINTERFACE NSDateClass;
typedef System::DelphiInterface<NSDateClass> _di_NSDateClass;
__interface DELPHIINTERFACE NSDate;
typedef System::DelphiInterface<NSDate> _di_NSDate;
class DELPHICLASS TNSDate;
__interface DELPHIINTERFACE NSDataClass;
typedef System::DelphiInterface<NSDataClass> _di_NSDataClass;
__interface DELPHIINTERFACE NSData;
typedef System::DelphiInterface<NSData> _di_NSData;
class DELPHICLASS TNSData;
__interface DELPHIINTERFACE NSUndoManagerClass;
typedef System::DelphiInterface<NSUndoManagerClass> _di_NSUndoManagerClass;
__interface DELPHIINTERFACE NSUndoManager;
typedef System::DelphiInterface<NSUndoManager> _di_NSUndoManager;
class DELPHICLASS TNSUndoManager;
__interface DELPHIINTERFACE NSCoderClass;
typedef System::DelphiInterface<NSCoderClass> _di_NSCoderClass;
__interface DELPHIINTERFACE NSCoder;
typedef System::DelphiInterface<NSCoder> _di_NSCoder;
class DELPHICLASS TNSCoder;
__interface DELPHIINTERFACE NSAutoreleasePoolClass;
typedef System::DelphiInterface<NSAutoreleasePoolClass> _di_NSAutoreleasePoolClass;
__interface DELPHIINTERFACE NSAutoreleasePool;
typedef System::DelphiInterface<NSAutoreleasePool> _di_NSAutoreleasePool;
class DELPHICLASS TNSAutoreleasePool;
__interface DELPHIINTERFACE NSXMLParserClass;
typedef System::DelphiInterface<NSXMLParserClass> _di_NSXMLParserClass;
__interface DELPHIINTERFACE NSXMLParser;
typedef System::DelphiInterface<NSXMLParser> _di_NSXMLParser;
class DELPHICLASS TNSXMLParser;
__interface DELPHIINTERFACE NSAttributedStringClass;
typedef System::DelphiInterface<NSAttributedStringClass> _di_NSAttributedStringClass;
__interface DELPHIINTERFACE NSAttributedString;
typedef System::DelphiInterface<NSAttributedString> _di_NSAttributedString;
class DELPHICLASS TNSAttributedString;
__interface DELPHIINTERFACE NSArrayClass;
typedef System::DelphiInterface<NSArrayClass> _di_NSArrayClass;
__interface DELPHIINTERFACE NSArray;
typedef System::DelphiInterface<NSArray> _di_NSArray;
class DELPHICLASS TNSArray;
__interface DELPHIINTERFACE NSAssertionHandlerClass;
typedef System::DelphiInterface<NSAssertionHandlerClass> _di_NSAssertionHandlerClass;
__interface DELPHIINTERFACE NSAssertionHandler;
typedef System::DelphiInterface<NSAssertionHandler> _di_NSAssertionHandler;
class DELPHICLASS TNSAssertionHandler;
__interface DELPHIINTERFACE NSCalendarClass;
typedef System::DelphiInterface<NSCalendarClass> _di_NSCalendarClass;
__interface DELPHIINTERFACE NSCalendar;
typedef System::DelphiInterface<NSCalendar> _di_NSCalendar;
class DELPHICLASS TNSCalendar;
__interface DELPHIINTERFACE NSCharacterSetClass;
typedef System::DelphiInterface<NSCharacterSetClass> _di_NSCharacterSetClass;
__interface DELPHIINTERFACE NSCharacterSet;
typedef System::DelphiInterface<NSCharacterSet> _di_NSCharacterSet;
class DELPHICLASS TNSCharacterSet;
__interface DELPHIINTERFACE NSCachedURLResponseClass;
typedef System::DelphiInterface<NSCachedURLResponseClass> _di_NSCachedURLResponseClass;
__interface DELPHIINTERFACE NSCachedURLResponse;
typedef System::DelphiInterface<NSCachedURLResponse> _di_NSCachedURLResponse;
class DELPHICLASS TNSCachedURLResponse;
__interface DELPHIINTERFACE NSBundleClass;
typedef System::DelphiInterface<NSBundleClass> _di_NSBundleClass;
__interface DELPHIINTERFACE NSBundle;
typedef System::DelphiInterface<NSBundle> _di_NSBundle;
class DELPHICLASS TNSBundle;
__interface DELPHIINTERFACE NSCacheClass;
typedef System::DelphiInterface<NSCacheClass> _di_NSCacheClass;
__interface DELPHIINTERFACE NSCache;
typedef System::DelphiInterface<NSCache> _di_NSCache;
class DELPHICLASS TNSCache;
__interface DELPHIINTERFACE NSURLResponseClass;
typedef System::DelphiInterface<NSURLResponseClass> _di_NSURLResponseClass;
__interface DELPHIINTERFACE NSURLResponse;
typedef System::DelphiInterface<NSURLResponse> _di_NSURLResponse;
class DELPHICLASS TNSURLResponse;
__interface DELPHIINTERFACE NSHTTPCookieStorageClass;
typedef System::DelphiInterface<NSHTTPCookieStorageClass> _di_NSHTTPCookieStorageClass;
__interface DELPHIINTERFACE NSHTTPCookieStorage;
typedef System::DelphiInterface<NSHTTPCookieStorage> _di_NSHTTPCookieStorage;
class DELPHICLASS TNSHTTPCookieStorage;
__interface DELPHIINTERFACE NSURLProtocolClass;
typedef System::DelphiInterface<NSURLProtocolClass> _di_NSURLProtocolClass;
__interface DELPHIINTERFACE NSURLProtocol;
typedef System::DelphiInterface<NSURLProtocol> _di_NSURLProtocol;
class DELPHICLASS TNSURLProtocol;
__interface DELPHIINTERFACE NSHTTPCookieClass;
typedef System::DelphiInterface<NSHTTPCookieClass> _di_NSHTTPCookieClass;
__interface DELPHIINTERFACE NSHTTPCookie;
typedef System::DelphiInterface<NSHTTPCookie> _di_NSHTTPCookie;
class DELPHICLASS TNSHTTPCookie;
__interface DELPHIINTERFACE NSFileWrapperClass;
typedef System::DelphiInterface<NSFileWrapperClass> _di_NSFileWrapperClass;
__interface DELPHIINTERFACE NSFileWrapper;
typedef System::DelphiInterface<NSFileWrapper> _di_NSFileWrapper;
class DELPHICLASS TNSFileWrapper;
__interface DELPHIINTERFACE NSFormatterClass;
typedef System::DelphiInterface<NSFormatterClass> _di_NSFormatterClass;
__interface DELPHIINTERFACE NSFormatter;
typedef System::DelphiInterface<NSFormatter> _di_NSFormatter;
class DELPHICLASS TNSFormatter;
__interface DELPHIINTERFACE NSInvocationClass;
typedef System::DelphiInterface<NSInvocationClass> _di_NSInvocationClass;
__interface DELPHIINTERFACE NSInvocation;
typedef System::DelphiInterface<NSInvocation> _di_NSInvocation;
class DELPHICLASS TNSInvocation;
__interface DELPHIINTERFACE NSURLCredentialStorageClass;
typedef System::DelphiInterface<NSURLCredentialStorageClass> _di_NSURLCredentialStorageClass;
__interface DELPHIINTERFACE NSURLCredentialStorage;
typedef System::DelphiInterface<NSURLCredentialStorage> _di_NSURLCredentialStorage;
class DELPHICLASS TNSURLCredentialStorage;
__interface DELPHIINTERFACE NSURLProtectionSpaceClass;
typedef System::DelphiInterface<NSURLProtectionSpaceClass> _di_NSURLProtectionSpaceClass;
__interface DELPHIINTERFACE NSURLProtectionSpace;
typedef System::DelphiInterface<NSURLProtectionSpace> _di_NSURLProtectionSpace;
class DELPHICLASS TNSURLProtectionSpace;
__interface DELPHIINTERFACE NSIndexPathClass;
typedef System::DelphiInterface<NSIndexPathClass> _di_NSIndexPathClass;
__interface DELPHIINTERFACE NSIndexPath;
typedef System::DelphiInterface<NSIndexPath> _di_NSIndexPath;
class DELPHICLASS TNSIndexPath;
__interface DELPHIINTERFACE NSIndexSetClass;
typedef System::DelphiInterface<NSIndexSetClass> _di_NSIndexSetClass;
__interface DELPHIINTERFACE NSIndexSet;
typedef System::DelphiInterface<NSIndexSet> _di_NSIndexSet;
class DELPHICLASS TNSIndexSet;
__interface DELPHIINTERFACE NSFileVersionClass;
typedef System::DelphiInterface<NSFileVersionClass> _di_NSFileVersionClass;
__interface DELPHIINTERFACE NSFileVersion;
typedef System::DelphiInterface<NSFileVersion> _di_NSFileVersion;
class DELPHICLASS TNSFileVersion;
__interface DELPHIINTERFACE NSEnumeratorClass;
typedef System::DelphiInterface<NSEnumeratorClass> _di_NSEnumeratorClass;
__interface DELPHIINTERFACE NSEnumerator;
typedef System::DelphiInterface<NSEnumerator> _di_NSEnumerator;
class DELPHICLASS TNSEnumerator;
__interface DELPHIINTERFACE NSErrorClass;
typedef System::DelphiInterface<NSErrorClass> _di_NSErrorClass;
__interface DELPHIINTERFACE NSError;
typedef System::DelphiInterface<NSError> _di_NSError;
class DELPHICLASS TNSError;
__interface DELPHIINTERFACE NSURLRequestClass;
typedef System::DelphiInterface<NSURLRequestClass> _di_NSURLRequestClass;
__interface DELPHIINTERFACE NSURLRequest;
typedef System::DelphiInterface<NSURLRequest> _di_NSURLRequest;
class DELPHICLASS TNSURLRequest;
__interface DELPHIINTERFACE NSDecimalNumberHandlerClass;
typedef System::DelphiInterface<NSDecimalNumberHandlerClass> _di_NSDecimalNumberHandlerClass;
__interface DELPHIINTERFACE NSDecimalNumberHandler;
typedef System::DelphiInterface<NSDecimalNumberHandler> _di_NSDecimalNumberHandler;
class DELPHICLASS TNSDecimalNumberHandler;
__interface DELPHIINTERFACE NSDictionaryClass;
typedef System::DelphiInterface<NSDictionaryClass> _di_NSDictionaryClass;
__interface DELPHIINTERFACE NSDictionary;
typedef System::DelphiInterface<NSDictionary> _di_NSDictionary;
class DELPHICLASS TNSDictionary;
__interface DELPHIINTERFACE NSFileHandleClass;
typedef System::DelphiInterface<NSFileHandleClass> _di_NSFileHandleClass;
__interface DELPHIINTERFACE NSFileHandle;
typedef System::DelphiInterface<NSFileHandle> _di_NSFileHandle;
class DELPHICLASS TNSFileHandle;
__interface DELPHIINTERFACE NSFileManagerClass;
typedef System::DelphiInterface<NSFileManagerClass> _di_NSFileManagerClass;
__interface DELPHIINTERFACE NSFileManager;
typedef System::DelphiInterface<NSFileManager> _di_NSFileManager;
class DELPHICLASS TNSFileManager;
__interface DELPHIINTERFACE NSFileCoordinatorClass;
typedef System::DelphiInterface<NSFileCoordinatorClass> _di_NSFileCoordinatorClass;
__interface DELPHIINTERFACE NSFileCoordinator;
typedef System::DelphiInterface<NSFileCoordinator> _di_NSFileCoordinator;
class DELPHICLASS TNSFileCoordinator;
__interface DELPHIINTERFACE NSExceptionClass;
typedef System::DelphiInterface<NSExceptionClass> _di_NSExceptionClass;
__interface DELPHIINTERFACE NSException;
typedef System::DelphiInterface<NSException> _di_NSException;
class DELPHICLASS TNSException;
__interface DELPHIINTERFACE NSExpressionClass;
typedef System::DelphiInterface<NSExpressionClass> _di_NSExpressionClass;
__interface DELPHIINTERFACE NSExpression;
typedef System::DelphiInterface<NSExpression> _di_NSExpression;
class DELPHICLASS TNSExpression;
__interface DELPHIINTERFACE NSInvocationOperationClass;
typedef System::DelphiInterface<NSInvocationOperationClass> _di_NSInvocationOperationClass;
__interface DELPHIINTERFACE NSInvocationOperation;
typedef System::DelphiInterface<NSInvocationOperation> _di_NSInvocationOperation;
class DELPHICLASS TNSInvocationOperation;
__interface DELPHIINTERFACE NSInputStreamClass;
typedef System::DelphiInterface<NSInputStreamClass> _di_NSInputStreamClass;
__interface DELPHIINTERFACE NSInputStream;
typedef System::DelphiInterface<NSInputStream> _di_NSInputStream;
class DELPHICLASS TNSInputStream;
__interface DELPHIINTERFACE NSHTTPURLResponseClass;
typedef System::DelphiInterface<NSHTTPURLResponseClass> _di_NSHTTPURLResponseClass;
__interface DELPHIINTERFACE NSHTTPURLResponse;
typedef System::DelphiInterface<NSHTTPURLResponse> _di_NSHTTPURLResponse;
class DELPHICLASS TNSHTTPURLResponse;
__interface DELPHIINTERFACE NSMachPortClass;
typedef System::DelphiInterface<NSMachPortClass> _di_NSMachPortClass;
__interface DELPHIINTERFACE NSMachPort;
typedef System::DelphiInterface<NSMachPort> _di_NSMachPort;
class DELPHICLASS TNSMachPort;
__interface DELPHIINTERFACE NSKeyedUnarchiverClass;
typedef System::DelphiInterface<NSKeyedUnarchiverClass> _di_NSKeyedUnarchiverClass;
__interface DELPHIINTERFACE NSKeyedUnarchiver;
typedef System::DelphiInterface<NSKeyedUnarchiver> _di_NSKeyedUnarchiver;
class DELPHICLASS TNSKeyedUnarchiver;
__interface DELPHIINTERFACE NSKeyedArchiverClass;
typedef System::DelphiInterface<NSKeyedArchiverClass> _di_NSKeyedArchiverClass;
__interface DELPHIINTERFACE NSKeyedArchiver;
typedef System::DelphiInterface<NSKeyedArchiver> _di_NSKeyedArchiver;
class DELPHICLASS TNSKeyedArchiver;
__interface DELPHIINTERFACE NSCompoundPredicateClass;
typedef System::DelphiInterface<NSCompoundPredicateClass> _di_NSCompoundPredicateClass;
__interface DELPHIINTERFACE NSCompoundPredicate;
typedef System::DelphiInterface<NSCompoundPredicate> _di_NSCompoundPredicate;
class DELPHICLASS TNSCompoundPredicate;
__interface DELPHIINTERFACE NSComparisonPredicateClass;
typedef System::DelphiInterface<NSComparisonPredicateClass> _di_NSComparisonPredicateClass;
__interface DELPHIINTERFACE NSComparisonPredicate;
typedef System::DelphiInterface<NSComparisonPredicate> _di_NSComparisonPredicate;
class DELPHICLASS TNSComparisonPredicate;
__interface DELPHIINTERFACE NSBlockOperationClass;
typedef System::DelphiInterface<NSBlockOperationClass> _di_NSBlockOperationClass;
__interface DELPHIINTERFACE NSBlockOperation;
typedef System::DelphiInterface<NSBlockOperation> _di_NSBlockOperation;
class DELPHICLASS TNSBlockOperation;
__interface DELPHIINTERFACE NSDirectoryEnumeratorClass;
typedef System::DelphiInterface<NSDirectoryEnumeratorClass> _di_NSDirectoryEnumeratorClass;
__interface DELPHIINTERFACE NSDirectoryEnumerator;
typedef System::DelphiInterface<NSDirectoryEnumerator> _di_NSDirectoryEnumerator;
class DELPHICLASS TNSDirectoryEnumerator;
__interface DELPHIINTERFACE NSDateFormatterClass;
typedef System::DelphiInterface<NSDateFormatterClass> _di_NSDateFormatterClass;
__interface DELPHIINTERFACE NSDateFormatter;
typedef System::DelphiInterface<NSDateFormatter> _di_NSDateFormatter;
class DELPHICLASS TNSDateFormatter;
__interface DELPHIINTERFACE NSExtensionContextClass;
typedef System::DelphiInterface<NSExtensionContextClass> _di_NSExtensionContextClass;
__interface DELPHIINTERFACE NSExtensionContext;
typedef System::DelphiInterface<NSExtensionContext> _di_NSExtensionContext;
class DELPHICLASS TNSExtensionContext;
__interface DELPHIINTERFACE NSDataDetectorClass;
typedef System::DelphiInterface<NSDataDetectorClass> _di_NSDataDetectorClass;
__interface DELPHIINTERFACE NSDataDetector;
typedef System::DelphiInterface<NSDataDetector> _di_NSDataDetector;
class DELPHICLASS TNSDataDetector;
__interface DELPHIINTERFACE NSMutableArrayClass;
typedef System::DelphiInterface<NSMutableArrayClass> _di_NSMutableArrayClass;
__interface DELPHIINTERFACE NSMutableArray;
typedef System::DelphiInterface<NSMutableArray> _di_NSMutableArray;
class DELPHICLASS TNSMutableArray;
__interface DELPHIINTERFACE NSMutableURLRequestClass;
typedef System::DelphiInterface<NSMutableURLRequestClass> _di_NSMutableURLRequestClass;
__interface DELPHIINTERFACE NSMutableURLRequest;
typedef System::DelphiInterface<NSMutableURLRequest> _di_NSMutableURLRequest;
class DELPHICLASS TNSMutableURLRequest;
__interface DELPHIINTERFACE NSMutableStringClass;
typedef System::DelphiInterface<NSMutableStringClass> _di_NSMutableStringClass;
__interface DELPHIINTERFACE NSMutableString;
typedef System::DelphiInterface<NSMutableString> _di_NSMutableString;
class DELPHICLASS TNSMutableString;
__interface DELPHIINTERFACE NSMutableSetClass;
typedef System::DelphiInterface<NSMutableSetClass> _di_NSMutableSetClass;
__interface DELPHIINTERFACE NSMutableSet;
typedef System::DelphiInterface<NSMutableSet> _di_NSMutableSet;
class DELPHICLASS TNSMutableSet;
__interface DELPHIINTERFACE NSOutputStreamClass;
typedef System::DelphiInterface<NSOutputStreamClass> _di_NSOutputStreamClass;
__interface DELPHIINTERFACE NSOutputStream;
typedef System::DelphiInterface<NSOutputStream> _di_NSOutputStream;
class DELPHICLASS TNSOutputStream;
__interface DELPHIINTERFACE NSNumberFormatterClass;
typedef System::DelphiInterface<NSNumberFormatterClass> _di_NSNumberFormatterClass;
__interface DELPHIINTERFACE NSNumberFormatter;
typedef System::DelphiInterface<NSNumberFormatter> _di_NSNumberFormatter;
class DELPHICLASS TNSNumberFormatter;
__interface DELPHIINTERFACE NSNumberClass;
typedef System::DelphiInterface<NSNumberClass> _di_NSNumberClass;
__interface DELPHIINTERFACE NSNumber;
typedef System::DelphiInterface<NSNumber> _di_NSNumber;
class DELPHICLASS TNSNumber;
__interface DELPHIINTERFACE NSMutableDataClass;
typedef System::DelphiInterface<NSMutableDataClass> _di_NSMutableDataClass;
__interface DELPHIINTERFACE NSMutableData;
typedef System::DelphiInterface<NSMutableData> _di_NSMutableData;
class DELPHICLASS TNSMutableData;
__interface DELPHIINTERFACE NSMutableCharacterSetClass;
typedef System::DelphiInterface<NSMutableCharacterSetClass> _di_NSMutableCharacterSetClass;
__interface DELPHIINTERFACE NSMutableCharacterSet;
typedef System::DelphiInterface<NSMutableCharacterSet> _di_NSMutableCharacterSet;
class DELPHICLASS TNSMutableCharacterSet;
__interface DELPHIINTERFACE NSMutableAttributedStringClass;
typedef System::DelphiInterface<NSMutableAttributedStringClass> _di_NSMutableAttributedStringClass;
__interface DELPHIINTERFACE NSMutableAttributedString;
typedef System::DelphiInterface<NSMutableAttributedString> _di_NSMutableAttributedString;
class DELPHICLASS TNSMutableAttributedString;
__interface DELPHIINTERFACE NSMutableDictionaryClass;
typedef System::DelphiInterface<NSMutableDictionaryClass> _di_NSMutableDictionaryClass;
__interface DELPHIINTERFACE NSMutableDictionary;
typedef System::DelphiInterface<NSMutableDictionary> _di_NSMutableDictionary;
class DELPHICLASS TNSMutableDictionary;
__interface DELPHIINTERFACE NSMutableOrderedSetClass;
typedef System::DelphiInterface<NSMutableOrderedSetClass> _di_NSMutableOrderedSetClass;
__interface DELPHIINTERFACE NSMutableOrderedSet;
typedef System::DelphiInterface<NSMutableOrderedSet> _di_NSMutableOrderedSet;
class DELPHICLASS TNSMutableOrderedSet;
__interface DELPHIINTERFACE NSMutableIndexSetClass;
typedef System::DelphiInterface<NSMutableIndexSetClass> _di_NSMutableIndexSetClass;
__interface DELPHIINTERFACE NSMutableIndexSet;
typedef System::DelphiInterface<NSMutableIndexSet> _di_NSMutableIndexSet;
class DELPHICLASS TNSMutableIndexSet;
__interface DELPHIINTERFACE NSCountedSetClass;
typedef System::DelphiInterface<NSCountedSetClass> _di_NSCountedSetClass;
__interface DELPHIINTERFACE NSCountedSet;
typedef System::DelphiInterface<NSCountedSet> _di_NSCountedSet;
class DELPHICLASS TNSCountedSet;
__interface DELPHIINTERFACE NSDecimalNumberClass;
typedef System::DelphiInterface<NSDecimalNumberClass> _di_NSDecimalNumberClass;
__interface DELPHIINTERFACE NSDecimalNumber;
typedef System::DelphiInterface<NSDecimalNumber> _di_NSDecimalNumber;
class DELPHICLASS TNSDecimalNumber;
__interface DELPHIINTERFACE NSUUIDClass;
typedef System::DelphiInterface<NSUUIDClass> _di_NSUUIDClass;
__interface DELPHIINTERFACE NSUUID;
typedef System::DelphiInterface<NSUUID> _di_NSUUID;
class DELPHICLASS TNSUUID;
__interface DELPHIINTERFACE NSURLComponentsClass;
typedef System::DelphiInterface<NSURLComponentsClass> _di_NSURLComponentsClass;
__interface DELPHIINTERFACE NSURLComponents;
typedef System::DelphiInterface<NSURLComponents> _di_NSURLComponents;
class DELPHICLASS TNSURLComponents;
__interface DELPHIINTERFACE NSURLSessionClass;
typedef System::DelphiInterface<NSURLSessionClass> _di_NSURLSessionClass;
__interface DELPHIINTERFACE NSURLSession;
typedef System::DelphiInterface<NSURLSession> _di_NSURLSession;
class DELPHICLASS TNSURLSession;
__interface DELPHIINTERFACE NSURLSessionTaskClass;
typedef System::DelphiInterface<NSURLSessionTaskClass> _di_NSURLSessionTaskClass;
__interface DELPHIINTERFACE NSURLSessionTask;
typedef System::DelphiInterface<NSURLSessionTask> _di_NSURLSessionTask;
class DELPHICLASS TNSURLSessionTask;
__interface DELPHIINTERFACE NSURLSessionDataTaskClass;
typedef System::DelphiInterface<NSURLSessionDataTaskClass> _di_NSURLSessionDataTaskClass;
__interface DELPHIINTERFACE NSURLSessionDataTask;
typedef System::DelphiInterface<NSURLSessionDataTask> _di_NSURLSessionDataTask;
class DELPHICLASS TNSURLSessionDataTask;
__interface DELPHIINTERFACE NSURLSessionUploadTaskClass;
typedef System::DelphiInterface<NSURLSessionUploadTaskClass> _di_NSURLSessionUploadTaskClass;
__interface DELPHIINTERFACE NSURLSessionUploadTask;
typedef System::DelphiInterface<NSURLSessionUploadTask> _di_NSURLSessionUploadTask;
class DELPHICLASS TNSURLSessionUploadTask;
__interface DELPHIINTERFACE NSURLSessionDownloadTaskClass;
typedef System::DelphiInterface<NSURLSessionDownloadTaskClass> _di_NSURLSessionDownloadTaskClass;
__interface DELPHIINTERFACE NSURLSessionDownloadTask;
typedef System::DelphiInterface<NSURLSessionDownloadTask> _di_NSURLSessionDownloadTask;
class DELPHICLASS TNSURLSessionDownloadTask;
__interface DELPHIINTERFACE NSURLSessionConfigurationClass;
typedef System::DelphiInterface<NSURLSessionConfigurationClass> _di_NSURLSessionConfigurationClass;
__interface DELPHIINTERFACE NSURLSessionConfiguration;
typedef System::DelphiInterface<NSURLSessionConfiguration> _di_NSURLSessionConfiguration;
class DELPHICLASS TNSURLSessionConfiguration;
__interface DELPHIINTERFACE NSCopying;
typedef System::DelphiInterface<NSCopying> _di_NSCopying;
__interface DELPHIINTERFACE NSMutableCopying;
typedef System::DelphiInterface<NSMutableCopying> _di_NSMutableCopying;
__interface DELPHIINTERFACE NSCoding;
typedef System::DelphiInterface<NSCoding> _di_NSCoding;
__interface DELPHIINTERFACE NSSecureCoding;
typedef System::DelphiInterface<NSSecureCoding> _di_NSSecureCoding;
__interface DELPHIINTERFACE NSDiscardableContent;
typedef System::DelphiInterface<NSDiscardableContent> _di_NSDiscardableContent;
__interface DELPHIINTERFACE NSFastEnumeration;
typedef System::DelphiInterface<NSFastEnumeration> _di_NSFastEnumeration;
__interface DELPHIINTERFACE NSDecimalNumberBehaviors;
typedef System::DelphiInterface<NSDecimalNumberBehaviors> _di_NSDecimalNumberBehaviors;
__interface DELPHIINTERFACE NSFileManagerDelegate;
typedef System::DelphiInterface<NSFileManagerDelegate> _di_NSFileManagerDelegate;
__interface DELPHIINTERFACE NSKeyedArchiverDelegate;
typedef System::DelphiInterface<NSKeyedArchiverDelegate> _di_NSKeyedArchiverDelegate;
__interface DELPHIINTERFACE NSKeyedUnarchiverDelegate;
typedef System::DelphiInterface<NSKeyedUnarchiverDelegate> _di_NSKeyedUnarchiverDelegate;
__interface DELPHIINTERFACE NSLocking;
typedef System::DelphiInterface<NSLocking> _di_NSLocking;
__interface DELPHIINTERFACE NSMachPortDelegate;
typedef System::DelphiInterface<NSMachPortDelegate> _di_NSMachPortDelegate;
__interface DELPHIINTERFACE NSStreamDelegate;
typedef System::DelphiInterface<NSStreamDelegate> _di_NSStreamDelegate;
__interface DELPHIINTERFACE NSURLAuthenticationChallengeSender;
typedef System::DelphiInterface<NSURLAuthenticationChallengeSender> _di_NSURLAuthenticationChallengeSender;
__interface DELPHIINTERFACE NSURLConnectionDelegate;
typedef System::DelphiInterface<NSURLConnectionDelegate> _di_NSURLConnectionDelegate;
__interface DELPHIINTERFACE NSURLConnectionDataDelegate;
typedef System::DelphiInterface<NSURLConnectionDataDelegate> _di_NSURLConnectionDataDelegate;
__interface DELPHIINTERFACE NSURLConnectionDownloadDelegate;
typedef System::DelphiInterface<NSURLConnectionDownloadDelegate> _di_NSURLConnectionDownloadDelegate;
__interface DELPHIINTERFACE NSURLProtocolClient;
typedef System::DelphiInterface<NSURLProtocolClient> _di_NSURLProtocolClient;
__interface DELPHIINTERFACE NSXMLParserDelegate;
typedef System::DelphiInterface<NSXMLParserDelegate> _di_NSXMLParserDelegate;
__interface DELPHIINTERFACE NSCacheDelegate;
typedef System::DelphiInterface<NSCacheDelegate> _di_NSCacheDelegate;
__interface DELPHIINTERFACE NSFilePresenter;
typedef System::DelphiInterface<NSFilePresenter> _di_NSFilePresenter;
__interface DELPHIINTERFACE NSMetadataQueryDelegate;
typedef System::DelphiInterface<NSMetadataQueryDelegate> _di_NSMetadataQueryDelegate;
__interface DELPHIINTERFACE NSNetServiceDelegate;
typedef System::DelphiInterface<NSNetServiceDelegate> _di_NSNetServiceDelegate;
__interface DELPHIINTERFACE NSNetServiceBrowserDelegate;
typedef System::DelphiInterface<NSNetServiceBrowserDelegate> _di_NSNetServiceBrowserDelegate;
__interface DELPHIINTERFACE NSURLSessionDelegate;
typedef System::DelphiInterface<NSURLSessionDelegate> _di_NSURLSessionDelegate;
__interface DELPHIINTERFACE NSURLSessionTaskDelegate;
typedef System::DelphiInterface<NSURLSessionTaskDelegate> _di_NSURLSessionTaskDelegate;
__interface DELPHIINTERFACE NSURLSessionDataDelegate;
typedef System::DelphiInterface<NSURLSessionDataDelegate> _di_NSURLSessionDataDelegate;
__interface DELPHIINTERFACE NSURLSessionDownloadDelegate;
typedef System::DelphiInterface<NSURLSessionDownloadDelegate> _di_NSURLSessionDownloadDelegate;
//-- type declarations -------------------------------------------------------
typedef unsigned long NSCalendarUnit;

typedef unsigned long NSComparisonPredicateOptions;

typedef void * NSComparator;

typedef unsigned long NSComparisonPredicateModifier;

typedef long NSComparisonResult;

typedef unsigned long NSCompoundPredicateType;

typedef unsigned long NSDataReadingOptions;

typedef unsigned long NSDataSearchOptions;

typedef unsigned long NSDataWritingOptions;

typedef unsigned long NSDateFormatterBehavior;

typedef unsigned long NSDateFormatterStyle;

typedef unsigned long NSDirectoryEnumerationOptions;

typedef unsigned long NSExpressionType;

typedef unsigned long NSFileManagerItemReplacementOptions;

typedef unsigned long NSFileVersionAddingOptions;

typedef unsigned long NSFileVersionReplacingOptions;

typedef unsigned long NSFileWrapperReadingOptions;

typedef unsigned long NSFileWrapperWritingOptions;

typedef unsigned long NSHTTPCookieAcceptPolicy;

typedef unsigned long NSJSONReadingOptions;

typedef unsigned long NSJSONWritingOptions;

typedef unsigned long NSKeyValueChange;

typedef unsigned long NSKeyValueObservingOptions;

typedef unsigned long NSKeyValueSetMutationKind;

typedef unsigned long NSLinguisticTaggerOptions;

typedef unsigned long NSLocaleLanguageDirection;

typedef unsigned long NSMatchingOptions;

typedef unsigned long NSNetServiceOptions;

typedef unsigned long NSNumberFormatterBehavior;

typedef unsigned long NSNumberFormatterPadPosition;

typedef unsigned long NSNumberFormatterRoundingMode;

typedef unsigned long NSNumberFormatterStyle;

typedef long NSOperationQueuePriority;

typedef unsigned long NSPostingStyle;

typedef unsigned long NSPredicateOperatorType;

typedef unsigned long NSPropertyListFormat;

typedef unsigned long *PNSPropertyListFormat;

typedef unsigned long NSPropertyListMutabilityOptions;

typedef unsigned long NSPropertyListReadOptions;

typedef unsigned long NSPropertyListWriteOptions;

typedef unsigned long NSRegularExpressionOptions;

typedef unsigned long NSRoundingMode;

typedef unsigned long NSSearchPathDirectory;

typedef unsigned long NSSearchPathDomainMask;

typedef unsigned long NSStreamEvent;

typedef unsigned long NSStreamStatus;

typedef unsigned long NSStringCompareOptions;

typedef unsigned long NSStringEncoding;

typedef unsigned long *PNSStringEncoding;

typedef unsigned long NSStringEncodingConversionOptions;

typedef unsigned __int64 NSTextCheckingType;

typedef unsigned __int64 NSTextCheckingTypes;

typedef long NSTimeZoneNameStyle;

typedef unsigned long NSURLBookmarkCreationOptions;

typedef unsigned long NSURLBookmarkFileCreationOptions;

typedef unsigned long NSURLBookmarkResolutionOptions;

typedef int NSURLCacheStoragePolicy;

typedef unsigned long NSURLCredentialPersistence;

typedef unsigned long NSURLRequestCachePolicy;

typedef unsigned long NSURLRequestNetworkServiceType;

typedef unsigned long NSVolumeEnumerationOptions;

typedef void * PNSArray;

typedef void * PNSString;

typedef void * SecIdentityRef;

typedef void * SecTrustRef;

typedef long NSURLSessionTaskState;

typedef long NSURLSessionAuthChallengeDisposition;

typedef long NSURLSessionResponseDisposition;

typedef unsigned long NSCalculationError;

typedef unsigned SSLProtocol;

struct DECLSPEC_DRECORD NSDecimal
{
public:
	int _exponent;
	unsigned _length;
	unsigned _isNegative;
	unsigned _isCompact;
	System::StaticArray<System::Word, 8> _mantissa;
};


typedef NSDecimal *PNSDecimal;

struct DECLSPEC_DRECORD NSRange
{
public:
	unsigned long location;
	unsigned long length;
};


typedef NSRange *PNSRange;

struct DECLSPEC_DRECORD NSPoint
{
public:
	double x;
	double y;
	__fastcall NSPoint(const System::Types::TPointF &Origin);
	System::Types::TPointF __fastcall ToPointF();
	static bool __fastcall _op_Equality(const NSPoint &Lhs, const NSPoint &Rhs);
	static bool __fastcall _op_Inequality(const NSPoint &Lhs, const NSPoint &Rhs);
	NSPoint() {}
	
	friend bool operator ==(const NSPoint &Lhs, const NSPoint &Rhs) { return NSPoint::_op_Equality(Lhs, Rhs); }
	friend bool operator !=(const NSPoint &Lhs, const NSPoint &Rhs) { return NSPoint::_op_Inequality(Lhs, Rhs); }
};


struct DECLSPEC_DRECORD NSSize
{
public:
	double width;
	double height;
	__fastcall NSSize(const System::Types::TSizeF &Origin);
	System::Types::TSizeF __fastcall ToSizeF();
	System::Types::TPointF __fastcall ToPointF();
	static bool __fastcall _op_Equality(const NSSize &Lhs, const NSSize &Rhs);
	static bool __fastcall _op_Inequality(const NSSize &Lhs, const NSSize &Rhs);
	NSSize() {}
	
	friend bool operator ==(const NSSize &Lhs, const NSSize &Rhs) { return NSSize::_op_Equality(Lhs, Rhs); }
	friend bool operator !=(const NSSize &Lhs, const NSSize &Rhs) { return NSSize::_op_Inequality(Lhs, Rhs); }
};


struct DECLSPEC_DRECORD NSRect
{
public:
	NSPoint origin;
	NSSize size;
	__fastcall NSRect(const System::Types::TRectF &Origin)/* overload */;
	__fastcall NSRect(const float X, float Y, float Width, float Height)/* overload */;
	System::Types::TSizeF __fastcall ToSizeF();
	System::Types::TRectF __fastcall ToRectF();
	static bool __fastcall _op_Equality(const NSRect &Lhs, const NSRect &Rhs);
	static bool __fastcall _op_Inequality(const NSRect &Lhs, const NSRect &Rhs);
	NSRect() {}
	
	friend bool operator ==(const NSRect &Lhs, const NSRect &Rhs) { return NSRect::_op_Equality(Lhs, Rhs); }
	friend bool operator !=(const NSRect &Lhs, const NSRect &Rhs) { return NSRect::_op_Inequality(Lhs, Rhs); }
};


typedef void * PNSDictionary;

typedef _di_NSString NSNotificationName;

typedef void __fastcall (__closure *TFoundationCompletionBlock)(void);

typedef void __fastcall (__closure *TFoundationCompletionHandler)(_di_NSURLResponse param1, _di_NSData param2, _di_NSError param3);

typedef void __fastcall (__closure *TFoundationCompletionHandler1)(_di_NSError param1);

typedef void __fastcall (__closure *TFoundationCompletionHandler2)(_di_NSArray param1, _di_NSArray param2, _di_NSArray param3);

typedef void __fastcall (__closure *TFoundationCompletionHandler3)(_di_NSData param1, _di_NSURLResponse param2, _di_NSError param3);

typedef void __fastcall (__closure *TFoundationCompletionHandler5)(_di_NSData param1);

typedef void __fastcall (__closure *TFoundationCompletionHandler4)(_di_NSURL param1, _di_NSURLResponse param2, _di_NSError param3);

typedef void __fastcall (__closure *TFoundationCompletionHandler6)(long param1, _di_NSURLCredential param2);

typedef void __fastcall (__closure *TFoundationCompletionHandler7)(_di_NSURLRequest param1);

typedef void __fastcall (__closure *TFoundationNeedNewBodyStream)(_di_NSInputStream param1);

typedef void __fastcall (__closure *TFoundationCompletionHandler8)(long param1);

typedef void __fastcall (__closure *TFoundationCompletionHandler9)(_di_NSCachedURLResponse param1);

typedef void __fastcall (__closure *TFoundationByAccessor)(_di_NSURL param1);

typedef void __fastcall (__closure *TFoundationByAccessor1)(_di_NSURL param1, _di_NSURL param2);

typedef void __fastcall (__closure *TFoundationByAccessor2)(TFoundationCompletionBlock param1);

__interface  INTERFACE_UUID("{84CDD025-E02A-4128-B1AC-35A7A5A4643B}") NSObjectClass  : public Macapi::Objectivec::IObjectiveCClass 
{
	virtual void * __cdecl Class() = 0 ;
	virtual void __cdecl cancelPreviousPerformRequestsWithTarget(void * target) = 0 /* overload */;
	virtual void __cdecl cancelPreviousPerformRequestsWithTarget(void * target, void * selector, void * object) = 0 /* overload */;
	virtual bool __cdecl conformsToProtocol(void * protocol) = 0 ;
	virtual _di_NSString __cdecl debugDescription() = 0 ;
	virtual _di_NSString __cdecl description() = 0 ;
	virtual bool __cdecl isSubclassOfClass(void * aClass) = 0 ;
	virtual void * __cdecl superclass() = 0 ;
};

__interface  INTERFACE_UUID("{C8CC567E-50C3-461C-BAA7-AD96D2CDC5C6}") NSObject  : public Macapi::Objectivec::IObjectiveCInstance 
{
	virtual void __cdecl addObserver(_di_NSObject observer, _di_NSString forKeyPath, unsigned long options, void * context) = 0 ;
	virtual bool __cdecl isKindOfClass(void * cls) = 0 ;
	virtual bool __cdecl isMemberOfClass(void * cls) = 0 ;
	virtual void __cdecl performSelector(void * aSelector, void * withObject, double afterDelay, _di_NSArray inModes) = 0 /* overload */;
	virtual void __cdecl performSelector(void * aSelector, _di_NSThread onThread, void * withObject, bool waitUntilDone, _di_NSArray modes) = 0 /* overload */;
	virtual void __cdecl performSelector(void * aSelector, _di_NSThread onThread, void * withObject, bool waitUntilDone) = 0 /* overload */;
	virtual void __cdecl performSelector(void * aSelector, void * withObject, double afterDelay) = 0 /* overload */;
	virtual void __cdecl performSelectorInBackground(void * aSelector, void * withObject) = 0 ;
	virtual void __cdecl performSelectorOnMainThread(void * aSelector, void * withObject, bool waitUntilDone) = 0 /* overload */;
	virtual void __cdecl performSelectorOnMainThread(void * aSelector, void * withObject, bool waitUntilDone, _di_NSArray modes) = 0 /* overload */;
	virtual void __cdecl release() = 0 ;
	virtual void __cdecl removeObserver(_di_NSObject observer, _di_NSString forKeyPath) = 0 /* overload */;
	virtual void __cdecl removeObserver(_di_NSObject observer, _di_NSString forKeyPath, void * context) = 0 /* overload */;
	virtual bool __cdecl respondsToSelector(void * aSelector) = 0 ;
	virtual void __cdecl retain() = 0 ;
	virtual unsigned long __cdecl retainCount() = 0 ;
	virtual void __cdecl setValueForKey(void * value, _di_NSString forKey) = 0 ;
	virtual void __cdecl setValueForKeyPath(void * value, _di_NSString forKeyPath) = 0 ;
	virtual void * __cdecl valueForKey(_di_NSString key) = 0 ;
	virtual void * __cdecl valueForKeyPath(_di_NSString keyPath) = 0 ;
};

class PASCALIMPLEMENTATION TNSObject : public Macapi::Objectivec::TOCGenericImport__2<_di_NSObjectClass,_di_NSObject>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSObjectClass,_di_NSObject> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSObject(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSObjectClass,_di_NSObject>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSObject() { }
	
};


__interface  INTERFACE_UUID("{C6D8E649-A9E8-4504-AB80-CD00B1648C26}") NSTimerClass  : public NSObjectClass 
{
	virtual void * __cdecl scheduledTimerWithTimeInterval(double ti, _di_NSInvocation invocation, bool repeats) = 0 /* overload */;
	virtual void * __cdecl scheduledTimerWithTimeInterval(double ti, void * target, void * selector, void * userInfo, bool repeats) = 0 /* overload */;
	virtual void * __cdecl timerWithTimeInterval(double ti, _di_NSInvocation invocation, bool repeats) = 0 /* overload */;
	virtual void * __cdecl timerWithTimeInterval(double ti, void * target, void * selector, void * userInfo, bool repeats) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{DFFD98EE-530A-431B-B88F-251C935DF474}") NSTimer  : public NSObject 
{
	virtual void __cdecl fire() = 0 ;
	virtual _di_NSDate __cdecl fireDate() = 0 ;
	virtual void * __cdecl initWithFireDate(_di_NSDate date, double interval, void * target, void * selector, void * userInfo, bool repeats) = 0 ;
	virtual void __cdecl invalidate() = 0 ;
	virtual bool __cdecl isValid() = 0 ;
	virtual void __cdecl setFireDate(_di_NSDate date) = 0 ;
	virtual double __cdecl timeInterval() = 0 ;
	virtual void * __cdecl userInfo() = 0 ;
};

class PASCALIMPLEMENTATION TNSTimer : public Macapi::Objectivec::TOCGenericImport__2<_di_NSTimerClass,_di_NSTimer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSTimerClass,_di_NSTimer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSTimer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSTimerClass,_di_NSTimer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSTimer() { }
	
};


__interface  INTERFACE_UUID("{73225883-9AEE-4DC8-BCF6-61897B676A73}") NSTimeZoneClass  : public NSObjectClass 
{
	virtual _di_NSDictionary __cdecl abbreviationDictionary() = 0 ;
	virtual void * __cdecl defaultTimeZone() = 0 ;
	virtual _di_NSArray __cdecl knownTimeZoneNames() = 0 ;
	virtual void * __cdecl localTimeZone() = 0 ;
	virtual void __cdecl resetSystemTimeZone() = 0 ;
	virtual void __cdecl setAbbreviationDictionary(_di_NSDictionary dict) = 0 ;
	virtual void __cdecl setDefaultTimeZone(_di_NSTimeZone aTimeZone) = 0 ;
	virtual void * __cdecl systemTimeZone() = 0 ;
	virtual _di_NSString __cdecl timeZoneDataVersion() = 0 ;
	virtual void * __cdecl timeZoneForSecondsFromGMT(long seconds) = 0 ;
	virtual void * __cdecl timeZoneWithAbbreviation(_di_NSString abbreviation) = 0 ;
	virtual void * __cdecl timeZoneWithName(_di_NSString tzName) = 0 /* overload */;
	virtual void * __cdecl timeZoneWithName(_di_NSString tzName, _di_NSData data) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{95840E3F-DA85-4DB7-941C-4496669174B8}") NSTimeZone  : public NSObject 
{
	virtual _di_NSString __cdecl abbreviation() = 0 ;
	virtual _di_NSString __cdecl abbreviationForDate(_di_NSDate aDate) = 0 ;
	virtual _di_NSData __cdecl data() = 0 ;
	virtual double __cdecl daylightSavingTimeOffset() = 0 ;
	virtual double __cdecl daylightSavingTimeOffsetForDate(_di_NSDate aDate) = 0 ;
	virtual _di_NSString __cdecl description() = 0 ;
	virtual void * __cdecl initWithName(_di_NSString tzName) = 0 /* overload */;
	virtual void * __cdecl initWithName(_di_NSString tzName, _di_NSData data) = 0 /* overload */;
	virtual bool __cdecl isDaylightSavingTime() = 0 ;
	virtual bool __cdecl isDaylightSavingTimeForDate(_di_NSDate aDate) = 0 ;
	virtual bool __cdecl isEqualToTimeZone(_di_NSTimeZone aTimeZone) = 0 ;
	virtual _di_NSString __cdecl localizedName(long style, _di_NSLocale locale) = 0 ;
	virtual _di_NSString __cdecl name() = 0 ;
	virtual _di_NSDate __cdecl nextDaylightSavingTimeTransition() = 0 ;
	virtual _di_NSDate __cdecl nextDaylightSavingTimeTransitionAfterDate(_di_NSDate aDate) = 0 ;
	virtual long __cdecl secondsFromGMT() = 0 ;
	virtual long __cdecl secondsFromGMTForDate(_di_NSDate aDate) = 0 ;
};

class PASCALIMPLEMENTATION TNSTimeZone : public Macapi::Objectivec::TOCGenericImport__2<_di_NSTimeZoneClass,_di_NSTimeZone>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSTimeZoneClass,_di_NSTimeZone> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSTimeZone(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSTimeZoneClass,_di_NSTimeZone>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSTimeZone() { }
	
};


__interface  INTERFACE_UUID("{B6B9A999-A7CF-430F-8FA7-987AC532BD1E}") NSURLClass  : public NSObjectClass 
{
	virtual void * __cdecl URLByResolvingBookmarkData(_di_NSData bookmarkData, unsigned long options, _di_NSURL relativeToURL, System::PBoolean bookmarkDataIsStale, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual void * __cdecl URLWithString(_di_NSString URLString) = 0 /* overload */;
	virtual void * __cdecl URLWithString(_di_NSString URLString, _di_NSURL relativeToURL) = 0 /* overload */;
	virtual _di_NSData __cdecl bookmarkDataWithContentsOfURL(_di_NSURL bookmarkFileURL, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual void * __cdecl fileURLWithPath(_di_NSString path) = 0 /* overload */;
	virtual void * __cdecl fileURLWithPath(_di_NSString path, bool isDirectory) = 0 /* overload */;
	virtual void * __cdecl fileURLWithPathComponents(_di_NSArray components) = 0 ;
	virtual _di_NSDictionary __cdecl resourceValuesForKeys(_di_NSArray keys, _di_NSData fromBookmarkData) = 0 /* overload */;
	virtual bool __cdecl writeBookmarkData(_di_NSData bookmarkData, _di_NSURL toURL, unsigned long options, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
};

__interface  INTERFACE_UUID("{17F81A07-11FF-4ABE-BFA3-F16C1CCF4C06}") NSURL  : public NSObject 
{
	virtual _di_NSURL __cdecl URLByAppendingPathComponent(_di_NSString pathComponent) = 0 /* overload */;
	virtual _di_NSURL __cdecl URLByAppendingPathComponent(_di_NSString pathComponent, bool isDirectory) = 0 /* overload */;
	virtual _di_NSURL __cdecl URLByAppendingPathExtension(_di_NSString pathExtension) = 0 ;
	virtual _di_NSURL __cdecl URLByDeletingLastPathComponent() = 0 ;
	virtual _di_NSURL __cdecl URLByDeletingPathExtension() = 0 ;
	virtual _di_NSURL __cdecl URLByResolvingSymlinksInPath() = 0 ;
	virtual _di_NSURL __cdecl URLByStandardizingPath() = 0 ;
	virtual _di_NSString __cdecl absoluteString() = 0 ;
	virtual _di_NSURL __cdecl absoluteURL() = 0 ;
	virtual _di_NSURL __cdecl baseURL() = 0 ;
	virtual _di_NSData __cdecl bookmarkDataWithOptions(unsigned long options, _di_NSArray includingResourceValuesForKeys, _di_NSURL relativeToURL, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual bool __cdecl checkResourceIsReachableAndReturnError(System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual _di_NSURL __cdecl filePathURL() = 0 ;
	virtual _di_NSURL __cdecl fileReferenceURL() = 0 ;
	virtual _di_NSString __cdecl fragment() = 0 ;
	virtual bool __cdecl getResourceValue(void * value, _di_NSString forKey, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual _di_NSString __cdecl host() = 0 ;
	virtual void * __cdecl initByResolvingBookmarkData(_di_NSData bookmarkData, unsigned long options, _di_NSURL relativeToURL, System::PBoolean bookmarkDataIsStale, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual void * __cdecl initFileURLWithPath(_di_NSString path) = 0 /* overload */;
	virtual void * __cdecl initFileURLWithPath(_di_NSString path, bool isDirectory) = 0 /* overload */;
	virtual void * __cdecl initWithScheme(_di_NSString scheme, _di_NSString host, _di_NSString path) = 0 ;
	virtual void * __cdecl initWithString(_di_NSString URLString) = 0 /* overload */;
	virtual void * __cdecl initWithString(_di_NSString URLString, _di_NSURL relativeToURL) = 0 /* overload */;
	virtual bool __cdecl isFileReferenceURL() = 0 ;
	virtual bool __cdecl isFileURL() = 0 ;
	virtual _di_NSString __cdecl lastPathComponent() = 0 ;
	virtual _di_NSString __cdecl parameterString() = 0 ;
	virtual _di_NSString __cdecl password() = 0 ;
	virtual _di_NSString __cdecl path() = 0 ;
	virtual _di_NSArray __cdecl pathComponents() = 0 ;
	virtual _di_NSString __cdecl pathExtension() = 0 ;
	virtual _di_NSNumber __cdecl port() = 0 ;
	virtual _di_NSString __cdecl query() = 0 ;
	virtual _di_NSString __cdecl relativePath() = 0 ;
	virtual _di_NSString __cdecl relativeString() = 0 ;
	virtual _di_NSString __cdecl resourceSpecifier() = 0 ;
	virtual _di_NSDictionary __cdecl resourceValuesForKeys(_di_NSArray keys, System::PPointer error = (System::PPointer)(0x0)) = 0 /* overload */;
	virtual _di_NSString __cdecl scheme() = 0 ;
	virtual bool __cdecl setResourceValue(void * value, _di_NSString forKey, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual bool __cdecl setResourceValues(_di_NSDictionary keyedValues, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual _di_NSURL __cdecl standardizedURL() = 0 ;
	virtual _di_NSString __cdecl user() = 0 ;
};

class PASCALIMPLEMENTATION TNSURL : public Macapi::Objectivec::TOCGenericImport__2<_di_NSURLClass,_di_NSURL>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSURLClass,_di_NSURL> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSURL(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSURLClass,_di_NSURL>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSURL() { }
	
};


__interface  INTERFACE_UUID("{D86B4BB9-8BE3-43CF-BF8A-7BE43B86D2D5}") NSMethodSignatureClass  : public NSObjectClass 
{
	virtual void * __cdecl signatureWithObjCTypes(char * types) = 0 ;
};

__interface  INTERFACE_UUID("{DA5CDD2A-212A-45F6-8863-BA60CA7CB855}") NSMethodSignature  : public NSObject 
{
	virtual unsigned long __cdecl frameLength() = 0 ;
	virtual char * __cdecl getArgumentTypeAtIndex(unsigned long idx) = 0 ;
	virtual bool __cdecl isOneway() = 0 ;
	virtual unsigned long __cdecl methodReturnLength() = 0 ;
	virtual char * __cdecl methodReturnType() = 0 ;
	virtual unsigned long __cdecl numberOfArguments() = 0 ;
};

class PASCALIMPLEMENTATION TNSMethodSignature : public Macapi::Objectivec::TOCGenericImport__2<_di_NSMethodSignatureClass,_di_NSMethodSignature>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSMethodSignatureClass,_di_NSMethodSignature> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSMethodSignature(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSMethodSignatureClass,_di_NSMethodSignature>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSMethodSignature() { }
	
};


__interface  INTERFACE_UUID("{F30BA11A-EFD1-410C-AE68-476E71BA8361}") NSURLAuthenticationChallengeClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{1E71FEDD-0AA2-48C7-9383-6F011D2FC4A6}") NSURLAuthenticationChallenge  : public NSObject 
{
	virtual _di_NSError __cdecl error() = 0 ;
	virtual _di_NSURLResponse __cdecl failureResponse() = 0 ;
	virtual void * __cdecl initWithAuthenticationChallenge(_di_NSURLAuthenticationChallenge challenge, void * sender) = 0 ;
	virtual void * __cdecl initWithProtectionSpace(_di_NSURLProtectionSpace space, _di_NSURLCredential proposedCredential, long previousFailureCount, _di_NSURLResponse failureResponse, _di_NSError error, void * sender) = 0 ;
	virtual long __cdecl previousFailureCount() = 0 ;
	virtual _di_NSURLCredential __cdecl proposedCredential() = 0 ;
	virtual _di_NSURLProtectionSpace __cdecl protectionSpace() = 0 ;
	virtual void * __cdecl sender() = 0 ;
};

class PASCALIMPLEMENTATION TNSURLAuthenticationChallenge : public Macapi::Objectivec::TOCGenericImport__2<_di_NSURLAuthenticationChallengeClass,_di_NSURLAuthenticationChallenge>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSURLAuthenticationChallengeClass,_di_NSURLAuthenticationChallenge> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSURLAuthenticationChallenge(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSURLAuthenticationChallengeClass,_di_NSURLAuthenticationChallenge>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSURLAuthenticationChallenge() { }
	
};


__interface  INTERFACE_UUID("{67F62CBB-288A-483F-9757-ADE7C6DE6C37}") NSStreamClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{1FF54EEE-3422-465E-8FDF-8ACB63719DDB}") NSStream  : public NSObject 
{
	virtual void __cdecl close() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl open() = 0 ;
	virtual void * __cdecl propertyForKey(_di_NSString key) = 0 ;
	virtual void __cdecl removeFromRunLoop(_di_NSRunLoop aRunLoop, _di_NSString forMode) = 0 ;
	virtual void __cdecl scheduleInRunLoop(_di_NSRunLoop aRunLoop, _di_NSString forMode) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual bool __cdecl setProperty(void * property_, _di_NSString forKey) = 0 ;
	virtual _di_NSError __cdecl streamError() = 0 ;
	virtual unsigned long __cdecl streamStatus() = 0 ;
};

class PASCALIMPLEMENTATION TNSStream : public Macapi::Objectivec::TOCGenericImport__2<_di_NSStreamClass,_di_NSStream>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSStreamClass,_di_NSStream> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSStream(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSStreamClass,_di_NSStream>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSStream() { }
	
};


__interface  INTERFACE_UUID("{F05469BE-3EB8-4C4F-8288-809A802549C4}") NSSortDescriptorClass  : public NSObjectClass 
{
	virtual void * __cdecl sortDescriptorWithKey(_di_NSString key, bool ascending) = 0 /* overload */;
	virtual void * __cdecl sortDescriptorWithKey(_di_NSString key, bool ascending, void * selector) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{F38A315C-02F2-4684-B892-1591E48C70D8}") NSSortDescriptor  : public NSObject 
{
	virtual bool __cdecl ascending() = 0 ;
	virtual void * __cdecl comparator() = 0 ;
	virtual long __cdecl compareObject(void * object1, void * toObject) = 0 ;
	virtual void * __cdecl initWithKey(_di_NSString key, bool ascending) = 0 /* overload */;
	virtual void * __cdecl initWithKey(_di_NSString key, bool ascending, void * selector) = 0 /* overload */;
	virtual _di_NSString __cdecl key() = 0 ;
	virtual void * __cdecl reversedSortDescriptor() = 0 ;
	virtual void * __cdecl selector() = 0 ;
};

class PASCALIMPLEMENTATION TNSSortDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_NSSortDescriptorClass,_di_NSSortDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSSortDescriptorClass,_di_NSSortDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSSortDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSSortDescriptorClass,_di_NSSortDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSSortDescriptor() { }
	
};


__interface  INTERFACE_UUID("{00B82BBF-C972-47D7-BC7E-2B6AB042FF34}") NSStringClass  : public NSObjectClass 
{
	virtual PNSStringEncoding __cdecl availableStringEncodings() = 0 ;
	virtual unsigned long __cdecl defaultCStringEncoding() = 0 ;
	virtual void * __cdecl localizedNameOfStringEncoding(unsigned long encoding) = 0 ;
	virtual void * __cdecl localizedStringWithFormat(_di_NSString format) = 0 ;
	virtual void * __cdecl pathWithComponents(_di_NSArray components) = 0 ;
	virtual void * __cdecl stringWithCString(char * bytes) = 0 /* overload */;
	virtual void * __cdecl stringWithCString(char * cString, unsigned long encoding) = 0 /* overload */;
	virtual void * __cdecl stringWithCharacters(System::WideChar * characters, unsigned long length) = 0 ;
	virtual void * __cdecl stringWithContentsOfFile(_di_NSString path) = 0 /* overload */;
	virtual void * __cdecl stringWithContentsOfFile(_di_NSString path, unsigned long encoding, System::PPointer error = (System::PPointer)(0x0)) = 0 /* overload */;
	virtual void * __cdecl stringWithContentsOfFile(_di_NSString path, PNSStringEncoding usedEncoding, System::PPointer error = (System::PPointer)(0x0)) = 0 /* overload */;
	virtual void * __cdecl stringWithContentsOfURL(_di_NSURL url) = 0 /* overload */;
	virtual void * __cdecl stringWithContentsOfURL(_di_NSURL url, unsigned long encoding, System::PPointer error = (System::PPointer)(0x0)) = 0 /* overload */;
	virtual void * __cdecl stringWithContentsOfURL(_di_NSURL url, PNSStringEncoding usedEncoding, System::PPointer error = (System::PPointer)(0x0)) = 0 /* overload */;
	virtual void * __cdecl stringWithFormat(_di_NSString format) = 0 ;
	virtual void * __cdecl stringWithString(_di_NSString string_) = 0 ;
	virtual void * __cdecl stringWithUTF8String(char * nullTerminatedCString) = 0 ;
};

__interface  INTERFACE_UUID("{1DE2D395-9581-465A-8C45-C1E6DDC2F269}") NSString  : public NSObject 
{
	virtual char * __cdecl UTF8String() = 0 ;
	virtual bool __cdecl boolValue() = 0 ;
	virtual char * __cdecl cString() = 0 ;
	virtual unsigned long __cdecl cStringLength() = 0 ;
	virtual char * __cdecl cStringUsingEncoding(unsigned long encoding) = 0 ;
	virtual bool __cdecl canBeConvertedToEncoding(unsigned long encoding) = 0 ;
	virtual _di_NSString __cdecl capitalizedString() = 0 ;
	virtual long __cdecl caseInsensitiveCompare(_di_NSString string_) = 0 ;
	virtual System::WideChar __cdecl characterAtIndex(unsigned long index) = 0 ;
	virtual _di_NSString __cdecl commonPrefixWithString(_di_NSString aString, unsigned long options) = 0 ;
	virtual long __cdecl compare(_di_NSString string_) = 0 /* overload */;
	virtual long __cdecl compare(_di_NSString string_, unsigned long options) = 0 /* overload */;
	virtual long __cdecl compare(_di_NSString string_, unsigned long options, NSRange range) = 0 /* overload */;
	virtual long __cdecl compare(_di_NSString string_, unsigned long options, NSRange range, void * locale) = 0 /* overload */;
	virtual unsigned long __cdecl completePathIntoString(_di_NSString outputName, bool caseSensitive, _di_NSArray matchesIntoArray, _di_NSArray filterTypes) = 0 ;
	virtual _di_NSArray __cdecl componentsSeparatedByCharactersInSet(_di_NSCharacterSet separator) = 0 ;
	virtual _di_NSArray __cdecl componentsSeparatedByString(_di_NSString separator) = 0 ;
	virtual _di_NSData __cdecl dataUsingEncoding(unsigned long encoding) = 0 /* overload */;
	virtual _di_NSData __cdecl dataUsingEncoding(unsigned long encoding, bool allowLossyConversion) = 0 /* overload */;
	virtual _di_NSString __cdecl decomposedStringWithCanonicalMapping() = 0 ;
	virtual _di_NSString __cdecl decomposedStringWithCompatibilityMapping() = 0 ;
	virtual _di_NSString __cdecl description() = 0 ;
	virtual double __cdecl doubleValue() = 0 ;
	virtual unsigned long __cdecl fastestEncoding() = 0 ;
	virtual char * __cdecl fileSystemRepresentation() = 0 ;
	virtual float __cdecl floatValue() = 0 ;
	virtual bool __cdecl getBytes(void * buffer, unsigned long maxLength, Iosapi::Cocoatypes::PNSUInteger usedLength, unsigned long encoding, unsigned long options, NSRange range, PNSRange remainingRange) = 0 ;
	virtual void __cdecl getCString(char * bytes) = 0 /* overload */;
	virtual void __cdecl getCString(char * bytes, unsigned long maxLength) = 0 /* overload */;
	virtual bool __cdecl getCString(char * buffer, unsigned long maxLength, unsigned long encoding) = 0 /* overload */;
	virtual void __cdecl getCString(char * bytes, unsigned long maxLength, NSRange range, PNSRange remainingRange) = 0 /* overload */;
	virtual void __cdecl getCharacters(System::WideChar * buffer) = 0 /* overload */;
	virtual void __cdecl getCharacters(System::WideChar * buffer, NSRange range) = 0 /* overload */;
	virtual bool __cdecl getFileSystemRepresentation(char * cname, unsigned long maxLength) = 0 ;
	virtual bool __cdecl hasPrefix(_di_NSString aString) = 0 ;
	virtual bool __cdecl hasSuffix(_di_NSString aString) = 0 ;
	virtual unsigned long __cdecl hash() = 0 ;
	HIDESBASE virtual void * __cdecl init() = 0 ;
	virtual void * __cdecl initWithBytes(void * bytes, unsigned long length, unsigned long encoding) = 0 ;
	virtual void * __cdecl initWithBytesNoCopy(void * bytes, unsigned long length, unsigned long encoding, bool freeWhenDone) = 0 ;
	virtual void * __cdecl initWithCString(char * bytes) = 0 /* overload */;
	virtual void * __cdecl initWithCString(char * nullTerminatedCString, unsigned long encoding) = 0 /* overload */;
	virtual void * __cdecl initWithCStringNoCopy(char * bytes, unsigned long length, bool freeWhenDone) = 0 ;
	virtual void * __cdecl initWithCharacters(System::WideChar * characters, unsigned long length) = 0 ;
	virtual void * __cdecl initWithCharactersNoCopy(System::WideChar * characters, unsigned long length, bool freeWhenDone) = 0 ;
	virtual void * __cdecl initWithContentsOfFile(_di_NSString path) = 0 /* overload */;
	virtual void * __cdecl initWithContentsOfFile(_di_NSString path, unsigned long encoding, System::PPointer error = (System::PPointer)(0x0)) = 0 /* overload */;
	virtual void * __cdecl initWithContentsOfFile(_di_NSString path, PNSStringEncoding usedEncoding, System::PPointer error = (System::PPointer)(0x0)) = 0 /* overload */;
	virtual void * __cdecl initWithContentsOfURL(_di_NSURL url) = 0 /* overload */;
	virtual void * __cdecl initWithContentsOfURL(_di_NSURL url, unsigned long encoding, System::PPointer error = (System::PPointer)(0x0)) = 0 /* overload */;
	virtual void * __cdecl initWithContentsOfURL(_di_NSURL url, PNSStringEncoding usedEncoding, System::PPointer error = (System::PPointer)(0x0)) = 0 /* overload */;
	virtual void * __cdecl initWithData(_di_NSData data, unsigned long encoding) = 0 ;
	virtual void * __cdecl initWithFormat(_di_NSString format) = 0 /* overload */;
	virtual void * __cdecl initWithFormat(_di_NSString format, void * locale) = 0 /* overload */;
	virtual void * __cdecl initWithString(_di_NSString aString) = 0 ;
	virtual void * __cdecl initWithUTF8String(char * nullTerminatedCString) = 0 ;
	virtual int __cdecl intValue() = 0 ;
	virtual long __cdecl integerValue() = 0 ;
	virtual bool __cdecl isAbsolutePath() = 0 ;
	virtual bool __cdecl isEqualToString(_di_NSString aString) = 0 ;
	virtual _di_NSString __cdecl lastPathComponent() = 0 ;
	virtual unsigned long __cdecl length() = 0 ;
	virtual unsigned long __cdecl lengthOfBytesUsingEncoding(unsigned long enc) = 0 ;
	virtual NSRange __cdecl lineRangeForRange(NSRange range) = 0 ;
	virtual _di_NSArray __cdecl linguisticTagsInRange(NSRange range, _di_NSString scheme, unsigned long options, _di_NSOrthography orthography, _di_NSArray tokenRanges) = 0 ;
	virtual long __cdecl localizedCaseInsensitiveCompare(_di_NSString string_) = 0 ;
	virtual long __cdecl localizedCompare(_di_NSString string_) = 0 ;
	virtual long __cdecl localizedStandardCompare(_di_NSString string_) = 0 ;
	virtual __int64 __cdecl longLongValue() = 0 ;
	virtual char * __cdecl lossyCString() = 0 ;
	virtual _di_NSString __cdecl lowercaseString() = 0 ;
	virtual unsigned long __cdecl maximumLengthOfBytesUsingEncoding(unsigned long enc) = 0 ;
	virtual NSRange __cdecl paragraphRangeForRange(NSRange range) = 0 ;
	virtual _di_NSArray __cdecl pathComponents() = 0 ;
	virtual _di_NSString __cdecl pathExtension() = 0 ;
	virtual _di_NSString __cdecl precomposedStringWithCanonicalMapping() = 0 ;
	virtual _di_NSString __cdecl precomposedStringWithCompatibilityMapping() = 0 ;
	virtual void * __cdecl propertyList() = 0 ;
	virtual _di_NSDictionary __cdecl propertyListFromStringsFileFormat() = 0 ;
	virtual NSRange __cdecl rangeOfCharacterFromSet(_di_NSCharacterSet aSet) = 0 /* overload */;
	virtual NSRange __cdecl rangeOfCharacterFromSet(_di_NSCharacterSet aSet, unsigned long options) = 0 /* overload */;
	virtual NSRange __cdecl rangeOfCharacterFromSet(_di_NSCharacterSet aSet, unsigned long options, NSRange range) = 0 /* overload */;
	virtual NSRange __cdecl rangeOfComposedCharacterSequenceAtIndex(unsigned long index) = 0 ;
	virtual NSRange __cdecl rangeOfComposedCharacterSequencesForRange(NSRange range) = 0 ;
	virtual NSRange __cdecl rangeOfString(_di_NSString aString) = 0 /* overload */;
	virtual NSRange __cdecl rangeOfString(_di_NSString aString, unsigned long options) = 0 /* overload */;
	virtual NSRange __cdecl rangeOfString(_di_NSString aString, unsigned long options, NSRange range) = 0 /* overload */;
	virtual NSRange __cdecl rangeOfString(_di_NSString aString, unsigned long options, NSRange range, _di_NSLocale locale) = 0 /* overload */;
	virtual unsigned long __cdecl smallestEncoding() = 0 ;
	virtual _di_NSString __cdecl stringByAbbreviatingWithTildeInPath() = 0 ;
	virtual _di_NSString __cdecl stringByAddingPercentEscapesUsingEncoding(unsigned long enc) = 0 ;
	virtual _di_NSString __cdecl stringByAppendingFormat(_di_NSString format) = 0 ;
	virtual _di_NSString __cdecl stringByAppendingPathComponent(_di_NSString str) = 0 ;
	virtual _di_NSString __cdecl stringByAppendingPathExtension(_di_NSString str) = 0 ;
	virtual _di_NSString __cdecl stringByAppendingString(_di_NSString aString) = 0 ;
	virtual _di_NSString __cdecl stringByDeletingLastPathComponent() = 0 ;
	virtual _di_NSString __cdecl stringByDeletingPathExtension() = 0 ;
	virtual _di_NSString __cdecl stringByExpandingTildeInPath() = 0 ;
	virtual _di_NSString __cdecl stringByFoldingWithOptions(unsigned long options, _di_NSLocale locale) = 0 ;
	virtual _di_NSString __cdecl stringByPaddingToLength(unsigned long newLength, _di_NSString withString, unsigned long startingAtIndex) = 0 ;
	virtual _di_NSString __cdecl stringByReplacingCharactersInRange(NSRange range, _di_NSString withString) = 0 ;
	virtual _di_NSString __cdecl stringByReplacingOccurrencesOfString(_di_NSString target, _di_NSString withString) = 0 /* overload */;
	virtual _di_NSString __cdecl stringByReplacingOccurrencesOfString(_di_NSString target, _di_NSString withString, unsigned long options, NSRange range) = 0 /* overload */;
	virtual _di_NSString __cdecl stringByReplacingPercentEscapesUsingEncoding(unsigned long enc) = 0 ;
	virtual _di_NSString __cdecl stringByResolvingSymlinksInPath() = 0 ;
	virtual _di_NSString __cdecl stringByStandardizingPath() = 0 ;
	virtual _di_NSString __cdecl stringByTrimmingCharactersInSet(_di_NSCharacterSet set_) = 0 ;
	virtual _di_NSArray __cdecl stringsByAppendingPaths(_di_NSArray paths) = 0 ;
	virtual _di_NSString __cdecl substringFromIndex(unsigned long from) = 0 ;
	virtual _di_NSString __cdecl substringToIndex(unsigned long to_) = 0 ;
	virtual _di_NSString __cdecl substringWithRange(NSRange range) = 0 ;
	virtual _di_NSString __cdecl uppercaseString() = 0 ;
	virtual _di_NSString __cdecl uppercaseStringWithLocale(void * locale) = 0 ;
	virtual bool __cdecl writeToFile(_di_NSString path, bool atomically) = 0 /* overload */;
	virtual bool __cdecl writeToFile(_di_NSString path, bool atomically, unsigned long encoding, System::PPointer error = (System::PPointer)(0x0)) = 0 /* overload */;
	virtual bool __cdecl writeToURL(_di_NSURL url, bool atomically) = 0 /* overload */;
	virtual bool __cdecl writeToURL(_di_NSURL url, bool atomically, unsigned long encoding, System::PPointer error = (System::PPointer)(0x0)) = 0 /* overload */;
};

class PASCALIMPLEMENTATION TNSString : public Macapi::Objectivec::TOCGenericImport__2<_di_NSStringClass,_di_NSString>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSStringClass,_di_NSString> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSString(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSStringClass,_di_NSString>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSString() { }
	
};


__interface  INTERFACE_UUID("{C46348C9-34B5-4DB7-8F0A-2ABCC245C63C}") NSThreadClass  : public NSObjectClass 
{
	virtual _di_NSArray __cdecl callStackReturnAddresses() = 0 ;
	virtual _di_NSArray __cdecl callStackSymbols() = 0 ;
	virtual void * __cdecl currentThread() = 0 ;
	virtual void __cdecl detachNewThreadSelector(void * selector, void * toTarget, void * withObject) = 0 ;
	virtual void __cdecl exit() = 0 ;
	virtual bool __cdecl isMainThread() = 0 /* overload */;
	virtual bool __cdecl isMultiThreaded() = 0 ;
	virtual void * __cdecl mainThread() = 0 ;
	virtual bool __cdecl setThreadPriority(double p) = 0 /* overload */;
	virtual void __cdecl sleepForTimeInterval(double ti) = 0 ;
	virtual void __cdecl sleepUntilDate(_di_NSDate date) = 0 ;
	virtual double __cdecl threadPriority() = 0 /* overload */;
};

__interface  INTERFACE_UUID("{221D82A7-7E85-4BEE-99DD-E6E1817F2D43}") NSThread  : public NSObject 
{
	virtual void __cdecl cancel() = 0 ;
	HIDESBASE virtual void * __cdecl init() = 0 ;
	virtual bool __cdecl isCancelled() = 0 ;
	virtual bool __cdecl isExecuting() = 0 ;
	virtual bool __cdecl isFinished() = 0 ;
	virtual bool __cdecl isMainThread() = 0 /* overload */;
	virtual void __cdecl main() = 0 ;
	virtual _di_NSString __cdecl name() = 0 ;
	virtual void __cdecl setName(_di_NSString n) = 0 ;
	virtual void __cdecl setStackSize(unsigned long s) = 0 ;
	virtual void __cdecl setThreadPriority(double p) = 0 /* overload */;
	virtual unsigned long __cdecl stackSize() = 0 ;
	virtual void __cdecl start() = 0 ;
	virtual _di_NSMutableDictionary __cdecl threadDictionary() = 0 ;
	virtual double __cdecl threadPriority() = 0 /* overload */;
};

class PASCALIMPLEMENTATION TNSThread : public Macapi::Objectivec::TOCGenericImport__2<_di_NSThreadClass,_di_NSThread>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSThreadClass,_di_NSThread> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSThread(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSThreadClass,_di_NSThread>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSThread() { }
	
};


__interface  INTERFACE_UUID("{8ECAB4BC-2421-47F4-B3D5-5E050A34E3DB}") NSTextCheckingResultClass  : public NSObjectClass 
{
	virtual void * __cdecl addressCheckingResultWithRange(NSRange range, _di_NSDictionary components) = 0 ;
	virtual void * __cdecl correctionCheckingResultWithRange(NSRange range, _di_NSString replacementString) = 0 ;
	virtual void * __cdecl dashCheckingResultWithRange(NSRange range, _di_NSString replacementString) = 0 ;
	virtual void * __cdecl dateCheckingResultWithRange(NSRange range, _di_NSDate date) = 0 /* overload */;
	virtual void * __cdecl dateCheckingResultWithRange(NSRange range, _di_NSDate date, _di_NSTimeZone timeZone, double duration) = 0 /* overload */;
	virtual void * __cdecl grammarCheckingResultWithRange(NSRange range, _di_NSArray details) = 0 ;
	virtual void * __cdecl linkCheckingResultWithRange(NSRange range, _di_NSURL URL) = 0 ;
	virtual void * __cdecl orthographyCheckingResultWithRange(NSRange range, _di_NSOrthography orthography) = 0 ;
	virtual void * __cdecl phoneNumberCheckingResultWithRange(NSRange range, _di_NSString phoneNumber) = 0 ;
	virtual void * __cdecl quoteCheckingResultWithRange(NSRange range, _di_NSString replacementString) = 0 ;
	virtual void * __cdecl regularExpressionCheckingResultWithRanges(PNSRange ranges, unsigned long count, _di_NSRegularExpression regularExpression) = 0 ;
	virtual void * __cdecl replacementCheckingResultWithRange(NSRange range, _di_NSString replacementString) = 0 ;
	virtual void * __cdecl spellCheckingResultWithRange(NSRange range) = 0 ;
	virtual void * __cdecl transitInformationCheckingResultWithRange(NSRange range, _di_NSDictionary components) = 0 ;
};

__interface  INTERFACE_UUID("{446F0F8C-4EA7-4DB1-9FCF-FB1D12594CAA}") NSTextCheckingResult  : public NSObject 
{
	virtual _di_NSURL __cdecl URL() = 0 ;
	virtual _di_NSDictionary __cdecl addressComponents() = 0 ;
	virtual _di_NSDictionary __cdecl components() = 0 ;
	virtual _di_NSDate __cdecl date() = 0 ;
	virtual double __cdecl duration() = 0 ;
	virtual _di_NSArray __cdecl grammarDetails() = 0 ;
	virtual unsigned long __cdecl numberOfRanges() = 0 ;
	virtual _di_NSOrthography __cdecl orthography() = 0 ;
	virtual _di_NSString __cdecl phoneNumber() = 0 ;
	virtual NSRange __cdecl range() = 0 ;
	virtual NSRange __cdecl rangeAtIndex(unsigned long idx) = 0 ;
	virtual _di_NSRegularExpression __cdecl regularExpression() = 0 ;
	virtual _di_NSString __cdecl replacementString() = 0 ;
	virtual _di_NSTextCheckingResult __cdecl resultByAdjustingRangesWithOffset(long offset) = 0 ;
	virtual unsigned __int64 __cdecl resultType() = 0 ;
	virtual _di_NSTimeZone __cdecl timeZone() = 0 ;
};

class PASCALIMPLEMENTATION TNSTextCheckingResult : public Macapi::Objectivec::TOCGenericImport__2<_di_NSTextCheckingResultClass,_di_NSTextCheckingResult>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSTextCheckingResultClass,_di_NSTextCheckingResult> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSTextCheckingResult(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSTextCheckingResultClass,_di_NSTextCheckingResult>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSTextCheckingResult() { }
	
};


__interface  INTERFACE_UUID("{4515A289-FF4F-45C9-A778-70F9F9BDA0B7}") NSMetadataQueryResultGroupClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{6C4EEEF6-84DB-415B-A46E-D3584A5852AC}") NSMetadataQueryResultGroup  : public NSObject 
{
	virtual _di_NSString __cdecl attribute() = 0 ;
	virtual void * __cdecl resultAtIndex(unsigned long idx) = 0 ;
	virtual unsigned long __cdecl resultCount() = 0 ;
	virtual _di_NSArray __cdecl results() = 0 ;
	virtual _di_NSArray __cdecl subgroups() = 0 ;
	virtual void * __cdecl value() = 0 ;
};

class PASCALIMPLEMENTATION TNSMetadataQueryResultGroup : public Macapi::Objectivec::TOCGenericImport__2<_di_NSMetadataQueryResultGroupClass,_di_NSMetadataQueryResultGroup>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSMetadataQueryResultGroupClass,_di_NSMetadataQueryResultGroup> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSMetadataQueryResultGroup(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSMetadataQueryResultGroupClass,_di_NSMetadataQueryResultGroup>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSMetadataQueryResultGroup() { }
	
};


__interface  INTERFACE_UUID("{7EA24D86-2C1B-4EBB-B568-0B8C0494487F}") NSLinguisticTaggerClass  : public NSObjectClass 
{
	virtual _di_NSArray __cdecl availableTagSchemesForLanguage(_di_NSString language) = 0 ;
};

__interface  INTERFACE_UUID("{26A1545C-D71B-436F-9B39-219FD87383D1}") NSLinguisticTagger  : public NSObject 
{
	virtual void * __cdecl initWithTagSchemes(_di_NSArray tagSchemes, unsigned long options) = 0 ;
	virtual _di_NSOrthography __cdecl orthographyAtIndex(unsigned long charIndex, PNSRange effectiveRange) = 0 ;
	virtual _di_NSArray __cdecl possibleTagsAtIndex(unsigned long charIndex, _di_NSString scheme, PNSRange tokenRange, PNSRange sentenceRange, _di_NSArray scores) = 0 ;
	virtual NSRange __cdecl sentenceRangeForRange(NSRange range) = 0 ;
	virtual void __cdecl setOrthography(_di_NSOrthography orthography, NSRange range) = 0 ;
	virtual void __cdecl setString(_di_NSString string_) = 0 ;
	virtual void __cdecl stringEditedInRange(NSRange newRange, long changeInLength) = 0 ;
	virtual _di_NSString __cdecl tagAtIndex(unsigned long charIndex, _di_NSString scheme, PNSRange tokenRange, PNSRange sentenceRange) = 0 ;
	virtual _di_NSArray __cdecl tagSchemes() = 0 ;
	virtual _di_NSArray __cdecl tagsInRange(NSRange range, _di_NSString scheme, unsigned long options, _di_NSArray tokenRanges) = 0 ;
};

class PASCALIMPLEMENTATION TNSLinguisticTagger : public Macapi::Objectivec::TOCGenericImport__2<_di_NSLinguisticTaggerClass,_di_NSLinguisticTagger>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSLinguisticTaggerClass,_di_NSLinguisticTagger> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSLinguisticTagger(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSLinguisticTaggerClass,_di_NSLinguisticTagger>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSLinguisticTagger() { }
	
};


__interface  INTERFACE_UUID("{D4D49576-C188-4BE8-B484-EC99EA9E7DC0}") NSLocaleClass  : public NSObjectClass 
{
	virtual _di_NSArray __cdecl ISOCountryCodes() = 0 ;
	virtual _di_NSArray __cdecl ISOCurrencyCodes() = 0 ;
	virtual _di_NSArray __cdecl ISOLanguageCodes() = 0 ;
	virtual void * __cdecl autoupdatingCurrentLocale() = 0 ;
	virtual _di_NSArray __cdecl availableLocaleIdentifiers() = 0 ;
	virtual _di_NSString __cdecl canonicalLanguageIdentifierFromString(_di_NSString string_) = 0 ;
	virtual _di_NSString __cdecl canonicalLocaleIdentifierFromString(_di_NSString string_) = 0 ;
	virtual unsigned long __cdecl characterDirectionForLanguage(_di_NSString isoLangCode) = 0 ;
	virtual _di_NSArray __cdecl commonISOCurrencyCodes() = 0 ;
	virtual _di_NSDictionary __cdecl componentsFromLocaleIdentifier(_di_NSString string_) = 0 ;
	virtual void * __cdecl currentLocale() = 0 ;
	virtual unsigned long __cdecl lineDirectionForLanguage(_di_NSString isoLangCode) = 0 ;
	virtual _di_NSString __cdecl localeIdentifierFromComponents(_di_NSDictionary dict) = 0 ;
	virtual _di_NSString __cdecl localeIdentifierFromWindowsLocaleCode(unsigned lcid) = 0 ;
	virtual void * __cdecl localeWithLocaleIdentifier(_di_NSString ident) = 0 ;
	virtual _di_NSArray __cdecl preferredLanguages() = 0 ;
	virtual void * __cdecl systemLocale() = 0 ;
	virtual unsigned __cdecl windowsLocaleCodeFromLocaleIdentifier(_di_NSString localeIdentifier) = 0 ;
};

__interface  INTERFACE_UUID("{FD343FD1-617B-4DAD-942B-469AD1F8C4A5}") NSLocale  : public NSObject 
{
	virtual _di_NSString __cdecl alternateQuotationBeginDelimiter() = 0 ;
	virtual _di_NSString __cdecl alternateQuotationEndDelimiter() = 0 ;
	virtual _di_NSString __cdecl calendarIdentifier() = 0 ;
	virtual _di_NSString __cdecl collationIdentifier() = 0 ;
	virtual _di_NSString __cdecl collatorIdentifier() = 0 ;
	virtual _di_NSString __cdecl countryCode() = 0 ;
	virtual _di_NSString __cdecl currencyCode() = 0 ;
	virtual _di_NSString __cdecl currencySymbol() = 0 ;
	virtual _di_NSString __cdecl decimalSeparator() = 0 ;
	virtual _di_NSString __cdecl displayNameForKey(void * key, void * value) = 0 ;
	virtual _di_NSCharacterSet __cdecl exemplarCharacterSet() = 0 ;
	virtual _di_NSString __cdecl groupingSeparator() = 0 ;
	virtual void * __cdecl initWithCoder(_di_NSCoder coder) = 0 ;
	virtual void * __cdecl initWithLocaleIdentifier(_di_NSString string_) = 0 ;
	virtual _di_NSString __cdecl languageCode() = 0 ;
	virtual _di_NSString __cdecl localeIdentifier() = 0 ;
	virtual _di_NSString __cdecl localizedStringForCalendarIdentifier(_di_NSString calendarIdentifier) = 0 ;
	virtual _di_NSString __cdecl localizedStringForCollationIdentifier(_di_NSString collationIdentifier) = 0 ;
	virtual _di_NSString __cdecl localizedStringForCollatorIdentifier(_di_NSString collatorIdentifier) = 0 ;
	virtual _di_NSString __cdecl localizedStringForCountryCode(_di_NSString countryCode) = 0 ;
	virtual _di_NSString __cdecl localizedStringForCurrencyCode(_di_NSString currencyCode) = 0 ;
	virtual _di_NSString __cdecl localizedStringForLanguageCode(_di_NSString languageCode) = 0 ;
	virtual _di_NSString __cdecl localizedStringForLocaleIdentifier(_di_NSString localeIdentifier) = 0 ;
	virtual _di_NSString __cdecl localizedStringForScriptCode(_di_NSString scriptCode) = 0 ;
	virtual _di_NSString __cdecl localizedStringForVariantCode(_di_NSString variantCode) = 0 ;
	virtual void * __cdecl objectForKey(void * key) = 0 ;
	virtual _di_NSString __cdecl quotationBeginDelimiter() = 0 ;
	virtual _di_NSString __cdecl quotationEndDelimiter() = 0 ;
	virtual _di_NSString __cdecl scriptCode() = 0 ;
	virtual bool __cdecl usesMetricSystem() = 0 ;
	virtual _di_NSString __cdecl variantCode() = 0 ;
};

class PASCALIMPLEMENTATION TNSLocale : public Macapi::Objectivec::TOCGenericImport__2<_di_NSLocaleClass,_di_NSLocale>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSLocaleClass,_di_NSLocale> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSLocale(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSLocaleClass,_di_NSLocale>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSLocale() { }
	
};


__interface  INTERFACE_UUID("{7021CED4-133B-4485-ABB1-F3A755EB3C75}") NSURLConnectionClass  : public NSObjectClass 
{
	virtual bool __cdecl canHandleRequest(_di_NSURLRequest request) = 0 ;
	virtual void * __cdecl connectionWithRequest(_di_NSURLRequest request, void * delegate) = 0 ;
	virtual _di_NSData __cdecl sendSynchronousRequest(_di_NSURLRequest request, System::PPointer returningResponse, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual void __cdecl sendAsynchronousRequest(_di_NSURLRequest request, _di_NSOperationQueue queue, TFoundationCompletionHandler completionHandler) = 0 ;
};

__interface  INTERFACE_UUID("{545DDD3E-AC2D-4403-9115-3DFE321D78FB}") NSURLConnection  : public NSObject 
{
	virtual void __cdecl cancel() = 0 ;
	virtual void * __cdecl initWithRequest(_di_NSURLRequest request, void * delegate) = 0 /* overload */;
	virtual void * __cdecl initWithRequest(_di_NSURLRequest request, void * delegate, bool startImmediately) = 0 /* overload */;
	virtual void __cdecl scheduleInRunLoop(_di_NSRunLoop aRunLoop, _di_NSString forMode) = 0 ;
	virtual void __cdecl setDelegateQueue(_di_NSOperationQueue queue) = 0 ;
	virtual void __cdecl start() = 0 ;
	virtual void __cdecl unscheduleFromRunLoop(_di_NSRunLoop aRunLoop, _di_NSString forMode) = 0 ;
};

class PASCALIMPLEMENTATION TNSURLConnection : public Macapi::Objectivec::TOCGenericImport__2<_di_NSURLConnectionClass,_di_NSURLConnection>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSURLConnectionClass,_di_NSURLConnection> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSURLConnection(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSURLConnectionClass,_di_NSURLConnection>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSURLConnection() { }
	
};


__interface  INTERFACE_UUID("{6FCDBDE2-6AE0-409C-8860-56362811EAC1}") NSJSONSerializationClass  : public NSObjectClass 
{
	virtual void * __cdecl JSONObjectWithData(_di_NSData data, unsigned long options, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual void * __cdecl JSONObjectWithStream(_di_NSInputStream stream, unsigned long options, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual _di_NSData __cdecl dataWithJSONObject(void * obj, unsigned long options, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual bool __cdecl isValidJSONObject(void * obj) = 0 ;
	virtual long __cdecl writeJSONObject(void * obj, _di_NSOutputStream toStream, unsigned long options, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
};

__interface  INTERFACE_UUID("{7E4617A1-93F0-4FC4-84EE-C20079084FB0}") NSJSONSerialization  : public NSObject 
{
	
};

class PASCALIMPLEMENTATION TNSJSONSerialization : public Macapi::Objectivec::TOCGenericImport__2<_di_NSJSONSerializationClass,_di_NSJSONSerialization>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSJSONSerializationClass,_di_NSJSONSerialization> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSJSONSerialization(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSJSONSerializationClass,_di_NSJSONSerialization>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSJSONSerialization() { }
	
};


__interface  INTERFACE_UUID("{4081992B-7792-4ED1-9A11-292B757E5987}") NSURLCredentialClass  : public NSObjectClass 
{
	virtual void * __cdecl credentialForTrust(void * trust) = 0 ;
	virtual void * __cdecl credentialWithIdentity(void * identity, _di_NSArray certificates, unsigned long persistence) = 0 ;
	virtual void * __cdecl credentialWithUser(_di_NSString user, _di_NSString password, unsigned long persistence) = 0 ;
};

__interface  INTERFACE_UUID("{64F6800A-3D46-4541-9AA8-956E11391E6A}") NSURLCredential  : public NSObject 
{
	virtual _di_NSArray __cdecl certificates() = 0 ;
	virtual bool __cdecl hasPassword() = 0 ;
	virtual void * __cdecl identity() = 0 ;
	virtual void * __cdecl initWithIdentity(void * identity, _di_NSArray certificates, unsigned long persistence) = 0 ;
	virtual void * __cdecl initWithTrust(void * trust) = 0 ;
	virtual void * __cdecl initWithUser(_di_NSString user, _di_NSString password, unsigned long persistence) = 0 ;
	virtual _di_NSString __cdecl password() = 0 ;
	virtual unsigned long __cdecl persistence() = 0 ;
	virtual _di_NSString __cdecl user() = 0 ;
};

class PASCALIMPLEMENTATION TNSURLCredential : public Macapi::Objectivec::TOCGenericImport__2<_di_NSURLCredentialClass,_di_NSURLCredential>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSURLCredentialClass,_di_NSURLCredential> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSURLCredential(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSURLCredentialClass,_di_NSURLCredential>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSURLCredential() { }
	
};


__interface  INTERFACE_UUID("{7F3DDA6C-BAD2-4510-A092-9ABEEB4FD008}") NSMetadataQueryClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{2493279D-2907-437A-BDBF-BA97E714A57F}") NSMetadataQuery  : public NSObject 
{
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl disableUpdates() = 0 ;
	virtual void __cdecl enableUpdates() = 0 ;
	virtual _di_NSArray __cdecl groupedResults() = 0 ;
	virtual _di_NSArray __cdecl groupingAttributes() = 0 ;
	virtual unsigned long __cdecl indexOfResult(void * result) = 0 ;
	HIDESBASE virtual void * __cdecl init() = 0 ;
	virtual bool __cdecl isGathering() = 0 ;
	virtual bool __cdecl isStarted() = 0 ;
	virtual bool __cdecl isStopped() = 0 ;
	virtual double __cdecl notificationBatchingInterval() = 0 ;
	virtual _di_NSPredicate __cdecl predicate() = 0 ;
	virtual void * __cdecl resultAtIndex(unsigned long idx) = 0 ;
	virtual unsigned long __cdecl resultCount() = 0 ;
	virtual _di_NSArray __cdecl results() = 0 ;
	virtual _di_NSArray __cdecl searchScopes() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setGroupingAttributes(_di_NSArray attrs) = 0 ;
	virtual void __cdecl setNotificationBatchingInterval(double ti) = 0 ;
	virtual void __cdecl setPredicate(_di_NSPredicate predicate) = 0 ;
	virtual void __cdecl setSearchScopes(_di_NSArray scopes) = 0 ;
	virtual void __cdecl setSortDescriptors(_di_NSArray descriptors) = 0 ;
	virtual void __cdecl setValueListAttributes(_di_NSArray attrs) = 0 ;
	virtual _di_NSArray __cdecl sortDescriptors() = 0 ;
	virtual bool __cdecl startQuery() = 0 ;
	virtual void __cdecl stopQuery() = 0 ;
	virtual _di_NSArray __cdecl valueListAttributes() = 0 ;
	virtual _di_NSDictionary __cdecl valueLists() = 0 ;
	virtual void * __cdecl valueOfAttribute(_di_NSString attrName, unsigned long forResultAtIndex) = 0 ;
};

class PASCALIMPLEMENTATION TNSMetadataQuery : public Macapi::Objectivec::TOCGenericImport__2<_di_NSMetadataQueryClass,_di_NSMetadataQuery>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSMetadataQueryClass,_di_NSMetadataQuery> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSMetadataQuery(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSMetadataQueryClass,_di_NSMetadataQuery>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSMetadataQuery() { }
	
};


__interface  INTERFACE_UUID("{AE9DB44E-7A11-4C17-BBE1-1FE5B2688C1F}") NSMetadataQueryAttributeValueTupleClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{9710F657-4605-47E6-AEDB-84F37C109F57}") NSMetadataQueryAttributeValueTuple  : public NSObject 
{
	virtual _di_NSString __cdecl attribute() = 0 ;
	virtual unsigned long __cdecl count() = 0 ;
	virtual void * __cdecl value() = 0 ;
};

class PASCALIMPLEMENTATION TNSMetadataQueryAttributeValueTuple : public Macapi::Objectivec::TOCGenericImport__2<_di_NSMetadataQueryAttributeValueTupleClass,_di_NSMetadataQueryAttributeValueTuple>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSMetadataQueryAttributeValueTupleClass,_di_NSMetadataQueryAttributeValueTuple> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSMetadataQueryAttributeValueTuple(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSMetadataQueryAttributeValueTupleClass,_di_NSMetadataQueryAttributeValueTuple>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSMetadataQueryAttributeValueTuple() { }
	
};


__interface  INTERFACE_UUID("{51A55335-B649-4249-9678-27BBCEEFDCED}") NSMetadataItemClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{6B077406-E1DC-4FFC-8400-2C2992B4F0C3}") NSMetadataItem  : public NSObject 
{
	virtual _di_NSArray __cdecl attributes() = 0 ;
	virtual void * __cdecl valueForAttribute(_di_NSString key) = 0 ;
	virtual _di_NSDictionary __cdecl valuesForAttributes(_di_NSArray keys) = 0 ;
};

class PASCALIMPLEMENTATION TNSMetadataItem : public Macapi::Objectivec::TOCGenericImport__2<_di_NSMetadataItemClass,_di_NSMetadataItem>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSMetadataItemClass,_di_NSMetadataItem> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSMetadataItem(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSMetadataItemClass,_di_NSMetadataItem>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSMetadataItem() { }
	
};


__interface  INTERFACE_UUID("{DD30A910-42FA-455D-ADA8-576655E0E799}") NSLockClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{15DCD242-9633-4902-9E6E-7B2948E75BFD}") NSLock  : public NSObject 
{
	virtual bool __cdecl lockBeforeDate(_di_NSDate limit) = 0 ;
	virtual _di_NSString __cdecl name() = 0 ;
	virtual void __cdecl setName(_di_NSString n) = 0 ;
	virtual bool __cdecl tryLock() = 0 ;
};

class PASCALIMPLEMENTATION TNSLock : public Macapi::Objectivec::TOCGenericImport__2<_di_NSLockClass,_di_NSLock>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSLockClass,_di_NSLock> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSLock(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSLockClass,_di_NSLock>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSLock() { }
	
};


__interface  INTERFACE_UUID("{4C7D8256-F0E0-44A5-983B-296A6708D3D0}") NSURLCacheClass  : public NSObjectClass 
{
	virtual void __cdecl setSharedURLCache(_di_NSURLCache cache) = 0 ;
	virtual void * __cdecl sharedURLCache() = 0 ;
};

__interface  INTERFACE_UUID("{DD172655-5100-4BA0-B8D6-EB9D17601C66}") NSURLCache  : public NSObject 
{
	virtual _di_NSCachedURLResponse __cdecl cachedResponseForRequest(_di_NSURLRequest request) = 0 ;
	virtual unsigned long __cdecl currentDiskUsage() = 0 ;
	virtual unsigned long __cdecl currentMemoryUsage() = 0 ;
	virtual unsigned long __cdecl diskCapacity() = 0 ;
	virtual void * __cdecl initWithMemoryCapacity(unsigned long memoryCapacity, unsigned long diskCapacity, _di_NSString diskPath) = 0 ;
	virtual unsigned long __cdecl memoryCapacity() = 0 ;
	virtual void __cdecl removeAllCachedResponses() = 0 ;
	virtual void __cdecl removeCachedResponseForRequest(_di_NSURLRequest request) = 0 ;
	virtual void __cdecl setDiskCapacity(unsigned long diskCapacity) = 0 ;
	virtual void __cdecl setMemoryCapacity(unsigned long memoryCapacity) = 0 ;
	virtual void __cdecl storeCachedResponse(_di_NSCachedURLResponse cachedResponse, _di_NSURLRequest forRequest) = 0 ;
};

class PASCALIMPLEMENTATION TNSURLCache : public Macapi::Objectivec::TOCGenericImport__2<_di_NSURLCacheClass,_di_NSURLCache>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSURLCacheClass,_di_NSURLCache> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSURLCache(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSURLCacheClass,_di_NSURLCache>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSURLCache() { }
	
};


__interface  INTERFACE_UUID("{C04B64A4-BEB7-48D8-A453-A8D55B254147}") NSSetClass  : public NSObjectClass 
{
	virtual void * __cdecl setWithArray(_di_NSArray array_) = 0 ;
	virtual void * __cdecl setWithObject(void * object_) = 0 ;
	virtual void * __cdecl setWithObjects(void * firstObj) = 0 /* overload */;
	virtual void * __cdecl setWithObjects(void * objects, unsigned long count) = 0 /* overload */;
	virtual void * __cdecl setWithSet(_di_NSSet set_) = 0 ;
};

__interface  INTERFACE_UUID("{1DDF31B4-3BAA-4547-942C-D31EC314F78A}") NSSet  : public NSObject 
{
	HIDESBASE virtual void __cdecl addObserver(_di_NSObject observer, _di_NSString forKeyPath, unsigned long options, void * context) = 0 ;
	virtual _di_NSArray __cdecl allObjects() = 0 ;
	virtual void * __cdecl anyObject() = 0 ;
	virtual bool __cdecl containsObject(void * anObject) = 0 ;
	virtual unsigned long __cdecl count() = 0 ;
	virtual _di_NSString __cdecl description() = 0 ;
	virtual _di_NSString __cdecl descriptionWithLocale(void * locale) = 0 ;
	virtual _di_NSSet __cdecl filteredSetUsingPredicate(_di_NSPredicate predicate) = 0 ;
	virtual void * __cdecl initWithArray(_di_NSArray array_) = 0 ;
	virtual void * __cdecl initWithObjects(void * firstObj) = 0 /* overload */;
	virtual void * __cdecl initWithObjects(void * objects, unsigned long count) = 0 /* overload */;
	virtual void * __cdecl initWithSet(_di_NSSet set_) = 0 /* overload */;
	virtual void * __cdecl initWithSet(_di_NSSet set_, bool copyItems) = 0 /* overload */;
	virtual bool __cdecl intersectsSet(_di_NSSet otherSet) = 0 ;
	virtual bool __cdecl isEqualToSet(_di_NSSet otherSet) = 0 ;
	virtual bool __cdecl isSubsetOfSet(_di_NSSet otherSet) = 0 ;
	virtual void __cdecl makeObjectsPerformSelector(void * aSelector) = 0 /* overload */;
	virtual void __cdecl makeObjectsPerformSelector(void * aSelector, void * withObject) = 0 /* overload */;
	virtual void * __cdecl member(void * object_) = 0 ;
	virtual _di_NSEnumerator __cdecl objectEnumerator() = 0 ;
	HIDESBASE virtual void __cdecl removeObserver(_di_NSObject observer, _di_NSString forKeyPath) = 0 /* overload */;
	HIDESBASE virtual void __cdecl removeObserver(_di_NSObject observer, _di_NSString forKeyPath, void * context) = 0 /* overload */;
	virtual _di_NSSet __cdecl setByAddingObject(void * anObject) = 0 ;
	virtual _di_NSSet __cdecl setByAddingObjectsFromArray(_di_NSArray other) = 0 ;
	virtual _di_NSSet __cdecl setByAddingObjectsFromSet(_di_NSSet other) = 0 ;
	virtual void __cdecl setValue(void * value, _di_NSString forKey) = 0 ;
	virtual _di_NSArray __cdecl sortedArrayUsingDescriptors(_di_NSArray sortDescriptors) = 0 ;
	HIDESBASE virtual void * __cdecl valueForKey(_di_NSString key) = 0 ;
};

class PASCALIMPLEMENTATION TNSSet : public Macapi::Objectivec::TOCGenericImport__2<_di_NSSetClass,_di_NSSet>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSSetClass,_di_NSSet> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSSet(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSSetClass,_di_NSSet>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSSet() { }
	
};


__interface  INTERFACE_UUID("{3B325647-ED51-4326-8784-69DE588E25AB}") NSPipeClass  : public NSObjectClass 
{
	virtual void * __cdecl pipe() = 0 ;
};

__interface  INTERFACE_UUID("{957A5978-0E43-40F0-B5FD-010484870568}") NSPipe  : public NSObject 
{
	virtual _di_NSFileHandle __cdecl fileHandleForReading() = 0 ;
	virtual _di_NSFileHandle __cdecl fileHandleForWriting() = 0 ;
	HIDESBASE virtual void * __cdecl init() = 0 ;
};

class PASCALIMPLEMENTATION TNSPipe : public Macapi::Objectivec::TOCGenericImport__2<_di_NSPipeClass,_di_NSPipe>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSPipeClass,_di_NSPipe> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSPipe(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSPipeClass,_di_NSPipe>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSPipe() { }
	
};


__interface  INTERFACE_UUID("{01EEB6A6-3661-4ABF-885C-0C07DCDDEA75}") NSPortClass  : public NSObjectClass 
{
	virtual void * __cdecl port() = 0 ;
};

__interface  INTERFACE_UUID("{114492E3-1289-4897-9932-21C5E4825899}") NSPort  : public NSObject 
{
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl invalidate() = 0 ;
	virtual bool __cdecl isValid() = 0 ;
	virtual void __cdecl removeFromRunLoop(_di_NSRunLoop runLoop, _di_NSString forMode) = 0 ;
	virtual unsigned long __cdecl reservedSpaceLength() = 0 ;
	virtual void __cdecl scheduleInRunLoop(_di_NSRunLoop runLoop, _di_NSString forMode) = 0 ;
	virtual bool __cdecl sendBeforeDate(_di_NSDate limitDate, _di_NSMutableArray components, _di_NSPort from, unsigned long reserved) = 0 /* overload */;
	virtual bool __cdecl sendBeforeDate(_di_NSDate limitDate, unsigned long msgid, _di_NSMutableArray components, _di_NSPort from, unsigned long reserved) = 0 /* overload */;
	virtual void __cdecl setDelegate(void * anObject) = 0 ;
};

class PASCALIMPLEMENTATION TNSPort : public Macapi::Objectivec::TOCGenericImport__2<_di_NSPortClass,_di_NSPort>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSPortClass,_di_NSPort> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSPort(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSPortClass,_di_NSPort>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSPort() { }
	
};


__interface  INTERFACE_UUID("{A6FC9813-8148-44EF-A5CF-77248B0BC9B5}") NSRegularExpressionClass  : public NSObjectClass 
{
	virtual _di_NSString __cdecl escapedPatternForString(_di_NSString string_) = 0 ;
	virtual _di_NSString __cdecl escapedTemplateForString(_di_NSString string_) = 0 ;
	virtual void * __cdecl regularExpressionWithPattern(_di_NSString pattern, unsigned long options, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
};

__interface  INTERFACE_UUID("{E88DECD7-E8CB-454B-8CAF-C4235DBA815B}") NSRegularExpression  : public NSObject 
{
	virtual _di_NSTextCheckingResult __cdecl firstMatchInString(_di_NSString string_, unsigned long options, NSRange range) = 0 ;
	virtual void * __cdecl initWithPattern(_di_NSString pattern, unsigned long options, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual _di_NSArray __cdecl matchesInString(_di_NSString string_, unsigned long options, NSRange range) = 0 ;
	virtual unsigned long __cdecl numberOfCaptureGroups() = 0 ;
	virtual unsigned long __cdecl numberOfMatchesInString(_di_NSString string_, unsigned long options, NSRange range) = 0 ;
	virtual unsigned long __cdecl options() = 0 ;
	virtual _di_NSString __cdecl pattern() = 0 ;
	virtual NSRange __cdecl rangeOfFirstMatchInString(_di_NSString string_, unsigned long options, NSRange range) = 0 ;
	virtual unsigned long __cdecl replaceMatchesInString(_di_NSMutableString string_, unsigned long options, NSRange range, _di_NSString withTemplate) = 0 ;
	virtual _di_NSString __cdecl replacementStringForResult(_di_NSTextCheckingResult result, _di_NSString inString, long offset, _di_NSString Template) = 0 ;
	virtual _di_NSString __cdecl stringByReplacingMatchesInString(_di_NSString string_, unsigned long options, NSRange range, _di_NSString withTemplate) = 0 ;
};

class PASCALIMPLEMENTATION TNSRegularExpression : public Macapi::Objectivec::TOCGenericImport__2<_di_NSRegularExpressionClass,_di_NSRegularExpression>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSRegularExpressionClass,_di_NSRegularExpression> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSRegularExpression(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSRegularExpressionClass,_di_NSRegularExpression>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSRegularExpression() { }
	
};


__interface  INTERFACE_UUID("{066987D3-4AB4-4FC4-BFE8-529D9011E7D9}") NSOrderedSetClass  : public NSObjectClass 
{
	virtual void * __cdecl orderedSet() = 0 ;
	virtual void * __cdecl orderedSetWithArray(_di_NSArray array_) = 0 /* overload */;
	virtual void * __cdecl orderedSetWithArray(_di_NSArray array_, NSRange range, bool copyItems) = 0 /* overload */;
	virtual void * __cdecl orderedSetWithObject(void * object_) = 0 ;
	virtual void * __cdecl orderedSetWithObjects(void * firstObj) = 0 /* overload */;
	virtual void * __cdecl orderedSetWithObjects(void * objects, unsigned long count) = 0 /* overload */;
	virtual void * __cdecl orderedSetWithOrderedSet(_di_NSOrderedSet set_) = 0 /* overload */;
	virtual void * __cdecl orderedSetWithOrderedSet(_di_NSOrderedSet set_, NSRange range, bool copyItems) = 0 /* overload */;
	virtual void * __cdecl orderedSetWithSet(_di_NSSet set_) = 0 /* overload */;
	virtual void * __cdecl orderedSetWithSet(_di_NSSet set_, bool copyItems) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{638A917E-F246-4097-81E0-76A32B925630}") NSOrderedSet  : public NSObject 
{
	HIDESBASE virtual void __cdecl addObserver(_di_NSObject observer, _di_NSString forKeyPath, unsigned long options, void * context) = 0 ;
	virtual bool __cdecl containsObject(void * object_) = 0 ;
	virtual unsigned long __cdecl count() = 0 ;
	virtual _di_NSString __cdecl description() = 0 ;
	virtual _di_NSString __cdecl descriptionWithLocale(void * locale) = 0 /* overload */;
	virtual _di_NSString __cdecl descriptionWithLocale(void * locale, unsigned long indent) = 0 /* overload */;
	virtual void * __cdecl firstObject() = 0 ;
	virtual void __cdecl getObjects(void * objects, NSRange range) = 0 ;
	virtual unsigned long __cdecl indexOfObject(void * object_) = 0 /* overload */;
	virtual void * __cdecl initWithArray(_di_NSArray array_) = 0 /* overload */;
	virtual void * __cdecl initWithArray(_di_NSArray set_, bool copyItems) = 0 /* overload */;
	virtual void * __cdecl initWithArray(_di_NSArray set_, NSRange range, bool copyItems) = 0 /* overload */;
	virtual void * __cdecl initWithObject(void * object_) = 0 ;
	virtual void * __cdecl initWithObjects(void * firstObj) = 0 /* overload */;
	virtual void * __cdecl initWithObjects(void * objects, unsigned long count) = 0 /* overload */;
	virtual void * __cdecl initWithOrderedSet(_di_NSOrderedSet set_) = 0 /* overload */;
	virtual void * __cdecl initWithOrderedSet(_di_NSOrderedSet set_, bool copyItems) = 0 /* overload */;
	virtual void * __cdecl initWithOrderedSet(_di_NSOrderedSet set_, NSRange range, bool copyItems) = 0 /* overload */;
	virtual void * __cdecl initWithSet(_di_NSSet set_) = 0 /* overload */;
	virtual void * __cdecl initWithSet(_di_NSSet set_, bool copyItems) = 0 /* overload */;
	virtual bool __cdecl intersectsOrderedSet(_di_NSOrderedSet other) = 0 ;
	virtual bool __cdecl intersectsSet(_di_NSSet set_) = 0 ;
	virtual bool __cdecl isEqualToOrderedSet(_di_NSOrderedSet other) = 0 ;
	virtual bool __cdecl isSubsetOfOrderedSet(_di_NSOrderedSet other) = 0 ;
	virtual bool __cdecl isSubsetOfSet(_di_NSSet set_) = 0 ;
	virtual void * __cdecl lastObject() = 0 ;
	virtual void * __cdecl objectAtIndex(unsigned long idx) = 0 ;
	virtual _di_NSEnumerator __cdecl objectEnumerator() = 0 ;
	virtual _di_NSArray __cdecl objectsAtIndexes(_di_NSIndexSet indexes) = 0 ;
	HIDESBASE virtual void __cdecl removeObserver(_di_NSObject observer, _di_NSString forKeyPath) = 0 /* overload */;
	HIDESBASE virtual void __cdecl removeObserver(_di_NSObject observer, _di_NSString forKeyPath, void * context) = 0 /* overload */;
	virtual _di_NSEnumerator __cdecl reverseObjectEnumerator() = 0 ;
	virtual _di_NSOrderedSet __cdecl reversedOrderedSet() = 0 ;
	virtual void __cdecl setValue(void * value, _di_NSString forKey) = 0 ;
	HIDESBASE virtual void * __cdecl valueForKey(_di_NSString key) = 0 ;
};

class PASCALIMPLEMENTATION TNSOrderedSet : public Macapi::Objectivec::TOCGenericImport__2<_di_NSOrderedSetClass,_di_NSOrderedSet>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSOrderedSetClass,_di_NSOrderedSet> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSOrderedSet(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSOrderedSetClass,_di_NSOrderedSet>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSOrderedSet() { }
	
};


__interface  INTERFACE_UUID("{C987D790-1892-4E3B-B400-7B62805EDC4E}") NSOrthographyClass  : public NSObjectClass 
{
	virtual void * __cdecl orthographyWithDominantScript(_di_NSString script, _di_NSDictionary languageMap) = 0 ;
};

__interface  INTERFACE_UUID("{2F3F9873-D720-48EC-A10E-0B3033C89C02}") NSOrthography  : public NSObject 
{
	virtual _di_NSArray __cdecl allLanguages() = 0 ;
	virtual _di_NSArray __cdecl allScripts() = 0 ;
	virtual _di_NSString __cdecl dominantLanguage() = 0 ;
	virtual _di_NSString __cdecl dominantLanguageForScript(_di_NSString script) = 0 ;
	virtual _di_NSString __cdecl dominantScript() = 0 ;
	virtual void * __cdecl initWithDominantScript(_di_NSString script, _di_NSDictionary languageMap) = 0 ;
	virtual _di_NSDictionary __cdecl languageMap() = 0 ;
	virtual _di_NSArray __cdecl languagesForScript(_di_NSString script) = 0 ;
};

class PASCALIMPLEMENTATION TNSOrthography : public Macapi::Objectivec::TOCGenericImport__2<_di_NSOrthographyClass,_di_NSOrthography>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSOrthographyClass,_di_NSOrthography> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSOrthography(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSOrthographyClass,_di_NSOrthography>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSOrthography() { }
	
};


__interface  INTERFACE_UUID("{7890B5C0-0CFE-47F9-8FCB-F8BC95535138}") NSProxyClass  : public Macapi::Objectivec::IObjectiveCClass 
{
	HIDESBASE virtual void * __cdecl alloc() = 0 ;
	virtual void * __cdecl allocWithZone(void * zone) = 0 ;
	virtual bool __cdecl respondsToSelector(void * aSelector) = 0 ;
};

__interface  INTERFACE_UUID("{28249DE4-888B-401C-85A6-D1FCAAFDD974}") NSProxy  : public Macapi::Objectivec::IObjectiveCInstance 
{
	virtual void __cdecl dealloc() = 0 ;
	virtual _di_NSString __cdecl debugDescription() = 0 ;
	virtual _di_NSString __cdecl description() = 0 ;
	virtual void __cdecl finalize() = 0 ;
	virtual void __cdecl forwardInvocation(_di_NSInvocation invocation) = 0 ;
	virtual _di_NSMethodSignature __cdecl methodSignatureForSelector(void * sel) = 0 ;
};

class PASCALIMPLEMENTATION TNSProxy : public Macapi::Objectivec::TOCGenericImport__2<_di_NSProxyClass,_di_NSProxy>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSProxyClass,_di_NSProxy> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSProxy(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSProxyClass,_di_NSProxy>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSProxy() { }
	
};


__interface  INTERFACE_UUID("{015F69BC-51D8-4D8F-897F-6AE7BD06A3C3}") NSRecursiveLockClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{31E9C72A-530E-45CB-A5E6-A3954D14CEFB}") NSRecursiveLock  : public NSObject 
{
	virtual bool __cdecl lockBeforeDate(_di_NSDate limit) = 0 ;
	virtual _di_NSString __cdecl name() = 0 ;
	virtual void __cdecl setName(_di_NSString n) = 0 ;
	virtual bool __cdecl tryLock() = 0 ;
};

class PASCALIMPLEMENTATION TNSRecursiveLock : public Macapi::Objectivec::TOCGenericImport__2<_di_NSRecursiveLockClass,_di_NSRecursiveLock>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSRecursiveLockClass,_di_NSRecursiveLock> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSRecursiveLock(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSRecursiveLockClass,_di_NSRecursiveLock>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSRecursiveLock() { }
	
};


__interface  INTERFACE_UUID("{9B73589B-7736-4B9D-A541-374CA196D74B}") NSPropertyListSerializationClass  : public NSObjectClass 
{
	virtual _di_NSData __cdecl dataFromPropertyList(void * plist, unsigned long format, _di_NSString errorDescription) = 0 ;
	virtual _di_NSData __cdecl dataWithPropertyList(void * plist, unsigned long format, unsigned long options, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual bool __cdecl propertyList(void * plist, unsigned long isValidForFormat) = 0 ;
	virtual void * __cdecl propertyListFromData(_di_NSData data, unsigned long mutabilityOption, PNSPropertyListFormat format, _di_NSString errorDescription) = 0 ;
	virtual void * __cdecl propertyListWithData(_di_NSData data, unsigned long options, PNSPropertyListFormat format, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual void * __cdecl propertyListWithStream(_di_NSInputStream stream, unsigned long options, PNSPropertyListFormat format, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual long __cdecl writePropertyList(void * plist, _di_NSOutputStream toStream, unsigned long format, unsigned long options, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
};

__interface  INTERFACE_UUID("{13CAB0EB-1565-4436-8E6C-D5BB3446C723}") NSPropertyListSerialization  : public NSObject 
{
	
};

class PASCALIMPLEMENTATION TNSPropertyListSerialization : public Macapi::Objectivec::TOCGenericImport__2<_di_NSPropertyListSerializationClass,_di_NSPropertyListSerialization>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSPropertyListSerializationClass,_di_NSPropertyListSerialization> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSPropertyListSerialization(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSPropertyListSerializationClass,_di_NSPropertyListSerialization>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSPropertyListSerialization() { }
	
};


__interface  INTERFACE_UUID("{5EF9036E-3D70-44E6-AB6F-D1FDE278D09E}") NSPredicateClass  : public NSObjectClass 
{
	virtual void * __cdecl predicateWithFormat(_di_NSString predicateFormat) = 0 /* overload */;
	virtual void * __cdecl predicateWithFormat(_di_NSString predicateFormat, _di_NSArray argumentArray) = 0 /* overload */;
	virtual void * __cdecl predicateWithValue(bool value) = 0 ;
};

__interface  INTERFACE_UUID("{FCC547FA-EA01-4E62-AF05-39B55B6018A6}") NSPredicate  : public NSObject 
{
	virtual bool __cdecl evaluateWithObject(void * object_) = 0 /* overload */;
	virtual bool __cdecl evaluateWithObject(void * object_, _di_NSDictionary substitutionVariables) = 0 /* overload */;
	virtual _di_NSString __cdecl predicateFormat() = 0 ;
	virtual _di_NSPredicate __cdecl predicateWithSubstitutionVariables(_di_NSDictionary variables) = 0 ;
};

class PASCALIMPLEMENTATION TNSPredicate : public Macapi::Objectivec::TOCGenericImport__2<_di_NSPredicateClass,_di_NSPredicate>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSPredicateClass,_di_NSPredicate> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSPredicate(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSPredicateClass,_di_NSPredicate>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSPredicate() { }
	
};


__interface  INTERFACE_UUID("{D96F16FF-BFB7-40ED-A24C-F1B3012EEBD0}") NSProcessInfoClass  : public NSObjectClass 
{
	virtual void * __cdecl processInfo() = 0 ;
};

__interface  INTERFACE_UUID("{76BE35B3-3880-4BDC-A996-346AE469289C}") NSProcessInfo  : public NSObject 
{
	virtual unsigned long __cdecl activeProcessorCount() = 0 ;
	virtual _di_NSArray __cdecl arguments() = 0 ;
	virtual bool __cdecl automaticTerminationSupportEnabled() = 0 ;
	virtual void __cdecl disableAutomaticTermination(_di_NSString reason) = 0 ;
	virtual void __cdecl disableSuddenTermination() = 0 ;
	virtual void __cdecl enableAutomaticTermination(_di_NSString reason) = 0 ;
	virtual void __cdecl enableSuddenTermination() = 0 ;
	virtual _di_NSDictionary __cdecl environment() = 0 ;
	virtual _di_NSString __cdecl globallyUniqueString() = 0 ;
	virtual _di_NSString __cdecl hostName() = 0 ;
	virtual unsigned long __cdecl operatingSystem() = 0 ;
	virtual _di_NSString __cdecl operatingSystemName() = 0 ;
	virtual _di_NSString __cdecl operatingSystemVersionString() = 0 ;
	virtual unsigned __int64 __cdecl physicalMemory() = 0 ;
	virtual int __cdecl processIdentifier() = 0 ;
	virtual _di_NSString __cdecl processName() = 0 ;
	virtual unsigned long __cdecl processorCount() = 0 ;
	virtual void __cdecl setAutomaticTerminationSupportEnabled(bool flag) = 0 ;
	virtual void __cdecl setProcessName(_di_NSString newName) = 0 ;
	virtual double __cdecl systemUptime() = 0 ;
};

class PASCALIMPLEMENTATION TNSProcessInfo : public Macapi::Objectivec::TOCGenericImport__2<_di_NSProcessInfoClass,_di_NSProcessInfo>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSProcessInfoClass,_di_NSProcessInfo> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSProcessInfo(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSProcessInfoClass,_di_NSProcessInfo>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSProcessInfo() { }
	
};


__interface  INTERFACE_UUID("{1C7F4DC1-28A5-4776-ADE9-E8448E7E3587}") NSOperationQueueClass  : public NSObjectClass 
{
	virtual void * __cdecl currentQueue() = 0 ;
	virtual void * __cdecl mainQueue() = 0 ;
};

__interface  INTERFACE_UUID("{F2F92F8B-D4BD-462E-961C-6FCD5C558AB0}") NSOperationQueue  : public NSObject 
{
	virtual void __cdecl addOperation(_di_NSOperation op) = 0 ;
	virtual void __cdecl addOperations(_di_NSArray ops, bool waitUntilFinished) = 0 ;
	virtual void __cdecl cancelAllOperations() = 0 ;
	virtual bool __cdecl isSuspended() = 0 ;
	virtual long __cdecl maxConcurrentOperationCount() = 0 ;
	virtual _di_NSString __cdecl name() = 0 ;
	virtual unsigned long __cdecl operationCount() = 0 ;
	virtual _di_NSArray __cdecl operations() = 0 ;
	virtual void __cdecl setMaxConcurrentOperationCount(long cnt) = 0 ;
	virtual void __cdecl setName(_di_NSString n) = 0 ;
	virtual void __cdecl setSuspended(bool b) = 0 ;
	virtual void __cdecl waitUntilAllOperationsAreFinished() = 0 ;
};

class PASCALIMPLEMENTATION TNSOperationQueue : public Macapi::Objectivec::TOCGenericImport__2<_di_NSOperationQueueClass,_di_NSOperationQueue>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSOperationQueueClass,_di_NSOperationQueue> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSOperationQueue(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSOperationQueueClass,_di_NSOperationQueue>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSOperationQueue() { }
	
};


__interface  INTERFACE_UUID("{6B3FCEF9-6DC4-4677-9494-7DBFD4B5E73F}") NSNotificationCenterClass  : public NSObjectClass 
{
	virtual void * __cdecl defaultCenter() = 0 ;
};

__interface  INTERFACE_UUID("{51EA2C04-9CE2-481F-98E1-D456AE279AD7}") NSNotificationCenter  : public NSObject 
{
	virtual void __cdecl postNotification(_di_NSNotification notification) = 0 ;
	HIDESBASE virtual void __cdecl removeObserver(void * observer) = 0 /* overload */;
	HIDESBASE virtual void __cdecl addObserver(void * notificationObserver, void * selector, void * name, void * object) = 0 ;
	virtual void __cdecl postNotificationName(void * notificationName, void * object) = 0 ;
};

class PASCALIMPLEMENTATION TNSNotificationCenter : public Macapi::Objectivec::TOCGenericImport__2<_di_NSNotificationCenterClass,_di_NSNotificationCenter>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSNotificationCenterClass,_di_NSNotificationCenter> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSNotificationCenter(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSNotificationCenterClass,_di_NSNotificationCenter>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSNotificationCenter() { }
	
};


__interface  INTERFACE_UUID("{291DCF57-9CB7-4F1C-8D52-11364A2D49AD}") NSNotificationQueueClass  : public NSObjectClass 
{
	virtual void * __cdecl defaultQueue() = 0 ;
};

__interface  INTERFACE_UUID("{D075C94F-F16B-4953-8790-4341DCF149C4}") NSNotificationQueue  : public NSObject 
{
	virtual void __cdecl dequeueNotificationsMatching(_di_NSNotification notification, unsigned long coalesceMask) = 0 ;
	virtual void __cdecl enqueueNotification(_di_NSNotification notification, unsigned long postingStyle) = 0 /* overload */;
	virtual void __cdecl enqueueNotification(_di_NSNotification notification, unsigned long postingStyle, unsigned long coalesceMask, _di_NSArray forModes) = 0 /* overload */;
	virtual void * __cdecl initWithNotificationCenter(_di_NSNotificationCenter notificationCenter) = 0 ;
};

class PASCALIMPLEMENTATION TNSNotificationQueue : public Macapi::Objectivec::TOCGenericImport__2<_di_NSNotificationQueueClass,_di_NSNotificationQueue>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSNotificationQueueClass,_di_NSNotificationQueue> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSNotificationQueue(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSNotificationQueueClass,_di_NSNotificationQueue>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSNotificationQueue() { }
	
};


__interface  INTERFACE_UUID("{28331A7D-99D9-4C73-8DF9-8649EF42F675}") NSNotificationClass  : public NSObjectClass 
{
	virtual void * __cdecl notificationWithName(_di_NSString aName, void * anObject) = 0 /* overload */;
	virtual void * __cdecl notificationWithName(_di_NSString aName, void * anObject, _di_NSDictionary aUserInfo) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{B153D7B5-2F8B-49E4-9A2B-A4DDCF002BEC}") NSNotification  : public NSObject 
{
	virtual void * __cdecl initWithCoder(_di_NSCoder coder) = 0 ;
	virtual void * __cdecl initWithName(_di_NSString name, void * object, _di_NSDictionary userInfo) = 0 ;
	virtual _di_NSString __cdecl name() = 0 ;
	virtual void * __cdecl object() = 0 ;
	virtual _di_NSDictionary __cdecl userInfo() = 0 ;
};

class PASCALIMPLEMENTATION TNSNotification : public Macapi::Objectivec::TOCGenericImport__2<_di_NSNotificationClass,_di_NSNotification>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSNotificationClass,_di_NSNotification> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSNotification(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSNotificationClass,_di_NSNotification>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSNotification() { }
	
};


__interface  INTERFACE_UUID("{73C87953-2B1B-4685-866B-8995C7994268}") NSNetServiceClass  : public NSObjectClass 
{
	virtual _di_NSData __cdecl dataFromTXTRecordDictionary(_di_NSDictionary txtDictionary) = 0 ;
	virtual _di_NSDictionary __cdecl dictionaryFromTXTRecordData(_di_NSData txtData) = 0 ;
};

__interface  INTERFACE_UUID("{A1B6027E-ECBC-4C0B-917F-50E09B385F5B}") NSNetService  : public NSObject 
{
	virtual _di_NSData __cdecl TXTRecordData() = 0 ;
	virtual _di_NSArray __cdecl addresses() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual _di_NSString __cdecl domain() = 0 ;
	virtual bool __cdecl getInputStream(_di_NSInputStream inputStream, _di_NSOutputStream outputStream) = 0 ;
	virtual _di_NSString __cdecl hostName() = 0 ;
	virtual _di_NSString __cdecl name() = 0 ;
	virtual long __cdecl port() = 0 ;
	virtual void __cdecl publish() = 0 ;
	virtual void __cdecl publishWithOptions(unsigned long options) = 0 ;
	virtual void __cdecl removeFromRunLoop(_di_NSRunLoop aRunLoop, _di_NSString forMode) = 0 ;
	virtual void __cdecl resolve() = 0 ;
	virtual void __cdecl resolveWithTimeout(double timeout) = 0 ;
	virtual void __cdecl scheduleInRunLoop(_di_NSRunLoop aRunLoop, _di_NSString forMode) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual bool __cdecl setTXTRecordData(_di_NSData recordData) = 0 ;
	virtual void __cdecl startMonitoring() = 0 ;
	virtual void __cdecl stop() = 0 ;
	virtual void __cdecl stopMonitoring() = 0 ;
};

class PASCALIMPLEMENTATION TNSNetService : public Macapi::Objectivec::TOCGenericImport__2<_di_NSNetServiceClass,_di_NSNetService>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSNetServiceClass,_di_NSNetService> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSNetService(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSNetServiceClass,_di_NSNetService>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSNetService() { }
	
};


__interface  INTERFACE_UUID("{6C15A4AF-6403-4B2C-9EC6-FCA90D5D0B2F}") NSNetServiceBrowserClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{3F70EA13-4042-4A4B-834F-DD3B7173723E}") NSNetServiceBrowser  : public NSObject 
{
	virtual void * __cdecl delegate() = 0 ;
	HIDESBASE virtual void * __cdecl init() = 0 ;
	virtual void __cdecl removeFromRunLoop(_di_NSRunLoop aRunLoop, _di_NSString forMode) = 0 ;
	virtual void __cdecl scheduleInRunLoop(_di_NSRunLoop aRunLoop, _di_NSString forMode) = 0 ;
	virtual void __cdecl searchForBrowsableDomains() = 0 ;
	virtual void __cdecl searchForRegistrationDomains() = 0 ;
	virtual void __cdecl searchForServicesOfType(_di_NSString type_, _di_NSString inDomain) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl stop() = 0 ;
};

class PASCALIMPLEMENTATION TNSNetServiceBrowser : public Macapi::Objectivec::TOCGenericImport__2<_di_NSNetServiceBrowserClass,_di_NSNetServiceBrowser>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSNetServiceBrowserClass,_di_NSNetServiceBrowser> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSNetServiceBrowser(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSNetServiceBrowserClass,_di_NSNetServiceBrowser>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSNetServiceBrowser() { }
	
};


__interface  INTERFACE_UUID("{93F325F4-A0F6-4CBF-B3F2-951ACB5CCB81}") NSOperationClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{DC872914-E61F-483D-8A77-8951EC87708C}") NSOperation  : public NSObject 
{
	virtual void __cdecl addDependency(_di_NSOperation op) = 0 ;
	virtual void __cdecl cancel() = 0 ;
	virtual _di_NSArray __cdecl dependencies() = 0 ;
	HIDESBASE virtual void * __cdecl init() = 0 ;
	virtual bool __cdecl isCancelled() = 0 ;
	virtual bool __cdecl isConcurrent() = 0 ;
	virtual bool __cdecl isExecuting() = 0 ;
	virtual bool __cdecl isFinished() = 0 ;
	virtual bool __cdecl isReady() = 0 ;
	virtual void __cdecl main() = 0 ;
	virtual long __cdecl queuePriority() = 0 ;
	virtual void __cdecl removeDependency(_di_NSOperation op) = 0 ;
	virtual void __cdecl setQueuePriority(long p) = 0 ;
	virtual void __cdecl setThreadPriority(double p) = 0 ;
	virtual void __cdecl start() = 0 ;
	virtual double __cdecl threadPriority() = 0 ;
	virtual void __cdecl waitUntilFinished() = 0 ;
};

class PASCALIMPLEMENTATION TNSOperation : public Macapi::Objectivec::TOCGenericImport__2<_di_NSOperationClass,_di_NSOperation>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSOperationClass,_di_NSOperation> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSOperation(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSOperationClass,_di_NSOperation>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSOperation() { }
	
};


__interface  INTERFACE_UUID("{A7BD196E-2B24-4EB3-8336-8723006676EB}") NSRunLoopClass  : public NSObjectClass 
{
	virtual void * __cdecl currentRunLoop() = 0 ;
	virtual void * __cdecl mainRunLoop() = 0 ;
};

__interface  INTERFACE_UUID("{775F67AF-A91B-4E43-B905-F89D1E8B75A5}") NSRunLoop  : public NSObject 
{
	virtual void __cdecl acceptInputForMode(_di_NSString mode, _di_NSDate beforeDate) = 0 ;
	virtual void __cdecl addPort(_di_NSPort aPort, _di_NSString forMode) = 0 ;
	virtual void __cdecl addTimer(_di_NSTimer timer, _di_NSString forMode) = 0 ;
	virtual void __cdecl cancelPerformSelector(void * aSelector, void * target, void * argument) = 0 ;
	virtual void __cdecl cancelPerformSelectorsWithTarget(void * target) = 0 ;
	virtual _di_NSString __cdecl currentMode() = 0 ;
	virtual CFRunLoopRef __cdecl getCFRunLoop() = 0 ;
	virtual _di_NSDate __cdecl limitDateForMode(_di_NSString mode) = 0 ;
	HIDESBASE virtual void __cdecl performSelector(void * aSelector, void * target, void * argument, unsigned long order, _di_NSArray modes) = 0 ;
	virtual void __cdecl removePort(_di_NSPort aPort, _di_NSString forMode) = 0 ;
	virtual void __cdecl run() = 0 ;
	virtual bool __cdecl runMode(_di_NSString mode, _di_NSDate beforeDate) = 0 ;
	virtual void __cdecl runUntilDate(_di_NSDate limitDate) = 0 ;
};

class PASCALIMPLEMENTATION TNSRunLoop : public Macapi::Objectivec::TOCGenericImport__2<_di_NSRunLoopClass,_di_NSRunLoop>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSRunLoopClass,_di_NSRunLoop> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSRunLoop(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSRunLoopClass,_di_NSRunLoop>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSRunLoop() { }
	
};


__interface  INTERFACE_UUID("{3BC76A3D-21AE-47F9-BC0C-1761CE7FE000}") NSNullClass  : public NSObjectClass 
{
	virtual void * __cdecl null() = 0 ;
};

__interface  INTERFACE_UUID("{24ED5CA8-7361-4914-809C-DD2897CD1710}") NSNull  : public NSObject 
{
	
};

class PASCALIMPLEMENTATION TNSNull : public Macapi::Objectivec::TOCGenericImport__2<_di_NSNullClass,_di_NSNull>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSNullClass,_di_NSNull> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSNull(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSNullClass,_di_NSNull>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSNull() { }
	
};


__interface  INTERFACE_UUID("{BFB87C94-DC51-431E-B952-B1AECDC7BF40}") NSScannerClass  : public NSObjectClass 
{
	virtual void * __cdecl localizedScannerWithString(_di_NSString string_) = 0 ;
	virtual void * __cdecl scannerWithString(_di_NSString string_) = 0 ;
};

__interface  INTERFACE_UUID("{6C70A589-CA01-4B10-B829-891ECB6DF232}") NSScanner  : public NSObject 
{
	virtual bool __cdecl caseSensitive() = 0 ;
	virtual _di_NSCharacterSet __cdecl charactersToBeSkipped() = 0 ;
	virtual void * __cdecl initWithString(_di_NSString string_) = 0 ;
	virtual bool __cdecl isAtEnd() = 0 ;
	virtual void * __cdecl locale() = 0 ;
	virtual bool __cdecl scanCharactersFromSet(_di_NSCharacterSet set_, _di_NSString intoString) = 0 ;
	virtual bool __cdecl scanDecimal(NSDecimal dcm) = 0 ;
	virtual bool __cdecl scanDouble(System::PDouble value) = 0 ;
	virtual bool __cdecl scanFloat(System::PSingle value) = 0 ;
	virtual bool __cdecl scanHexDouble(System::PDouble result) = 0 ;
	virtual bool __cdecl scanHexFloat(System::PSingle result) = 0 ;
	virtual bool __cdecl scanHexInt(Macapi::Corefoundation::PUInt32 value) = 0 ;
	virtual bool __cdecl scanHexLongLong(System::PUInt64 result) = 0 ;
	virtual bool __cdecl scanInt(System::PInteger value) = 0 ;
	virtual bool __cdecl scanInteger(Iosapi::Cocoatypes::PNSInteger value) = 0 ;
	virtual unsigned long __cdecl scanLocation() = 0 ;
	virtual bool __cdecl scanLongLong(System::PInt64 value) = 0 ;
	virtual bool __cdecl scanString(_di_NSString string_, _di_NSString intoString) = 0 ;
	virtual bool __cdecl scanUpToCharactersFromSet(_di_NSCharacterSet set_, _di_NSString intoString) = 0 ;
	virtual bool __cdecl scanUpToString(_di_NSString string_, _di_NSString intoString) = 0 ;
	virtual void __cdecl setCaseSensitive(bool flag) = 0 ;
	virtual void __cdecl setCharactersToBeSkipped(_di_NSCharacterSet set_) = 0 ;
	virtual void __cdecl setLocale(void * locale) = 0 ;
	virtual void __cdecl setScanLocation(unsigned long pos) = 0 ;
};

class PASCALIMPLEMENTATION TNSScanner : public Macapi::Objectivec::TOCGenericImport__2<_di_NSScannerClass,_di_NSScanner>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSScannerClass,_di_NSScanner> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSScanner(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSScannerClass,_di_NSScanner>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSScanner() { }
	
};


__interface  INTERFACE_UUID("{BD5235E9-ABB9-4592-8677-94DADAE8F00B}") NSConditionLockClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{BAFDC74F-2E71-40FE-B950-3E32D875BB6E}") NSConditionLock  : public NSObject 
{
	virtual long __cdecl condition() = 0 ;
	virtual void * __cdecl initWithCondition(long condition) = 0 ;
	virtual bool __cdecl lockBeforeDate(_di_NSDate limit) = 0 ;
	virtual void __cdecl lockWhenCondition(long condition) = 0 /* overload */;
	virtual bool __cdecl lockWhenCondition(long condition, _di_NSDate beforeDate) = 0 /* overload */;
	virtual _di_NSString __cdecl name() = 0 ;
	virtual void __cdecl setName(_di_NSString n) = 0 ;
	virtual bool __cdecl tryLock() = 0 ;
	virtual bool __cdecl tryLockWhenCondition(long condition) = 0 ;
	virtual void __cdecl unlockWithCondition(long condition) = 0 ;
};

class PASCALIMPLEMENTATION TNSConditionLock : public Macapi::Objectivec::TOCGenericImport__2<_di_NSConditionLockClass,_di_NSConditionLock>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSConditionLockClass,_di_NSConditionLock> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSConditionLock(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSConditionLockClass,_di_NSConditionLock>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSConditionLock() { }
	
};


__interface  INTERFACE_UUID("{AA19A42B-50C7-47B5-916D-C1D9A21B0566}") NSUserDefaultsClass  : public NSObjectClass 
{
	virtual void __cdecl resetStandardUserDefaults() = 0 ;
	virtual void * __cdecl standardUserDefaults() = 0 ;
};

__interface  INTERFACE_UUID("{07413276-93BF-45FC-95FC-1E18CA4863CB}") NSUserDefaults  : public NSObject 
{
	virtual _di_NSURL __cdecl URLForKey(_di_NSString defaultName) = 0 ;
	virtual void __cdecl addSuiteNamed(_di_NSString suiteName) = 0 ;
	virtual _di_NSArray __cdecl arrayForKey(_di_NSString defaultName) = 0 ;
	virtual bool __cdecl boolForKey(_di_NSString defaultName) = 0 ;
	virtual _di_NSData __cdecl dataForKey(_di_NSString defaultName) = 0 ;
	virtual _di_NSDictionary __cdecl dictionaryForKey(_di_NSString defaultName) = 0 ;
	virtual _di_NSDictionary __cdecl dictionaryRepresentation() = 0 ;
	virtual double __cdecl doubleForKey(_di_NSString defaultName) = 0 ;
	virtual float __cdecl floatForKey(_di_NSString defaultName) = 0 ;
	HIDESBASE virtual void * __cdecl init() = 0 ;
	virtual void * __cdecl initWithUser(_di_NSString username) = 0 ;
	virtual long __cdecl integerForKey(_di_NSString defaultName) = 0 ;
	virtual void * __cdecl objectForKey(_di_NSString defaultName) = 0 ;
	virtual bool __cdecl objectIsForcedForKey(_di_NSString key) = 0 /* overload */;
	virtual bool __cdecl objectIsForcedForKey(_di_NSString key, _di_NSString inDomain) = 0 /* overload */;
	virtual _di_NSDictionary __cdecl persistentDomainForName(_di_NSString domainName) = 0 ;
	virtual _di_NSArray __cdecl persistentDomainNames() = 0 ;
	virtual void __cdecl registerDefaults(_di_NSDictionary registrationDictionary) = 0 ;
	virtual void __cdecl removeObjectForKey(_di_NSString defaultName) = 0 ;
	virtual void __cdecl removePersistentDomainForName(_di_NSString domainName) = 0 ;
	virtual void __cdecl removeSuiteNamed(_di_NSString suiteName) = 0 ;
	virtual void __cdecl removeVolatileDomainForName(_di_NSString domainName) = 0 ;
	virtual void __cdecl setBool(bool value, _di_NSString forKey) = 0 ;
	virtual void __cdecl setDouble(double value, _di_NSString forKey) = 0 ;
	virtual void __cdecl setFloat(float value, _di_NSString forKey) = 0 ;
	virtual void __cdecl setInteger(long value, _di_NSString forKey) = 0 ;
	virtual void __cdecl setObject(void * value, _di_NSString forKey) = 0 ;
	virtual void __cdecl setPersistentDomain(_di_NSDictionary domain, _di_NSString forName) = 0 ;
	virtual void __cdecl setURL(_di_NSURL url, _di_NSString forKey) = 0 ;
	virtual void __cdecl setVolatileDomain(_di_NSDictionary domain, _di_NSString forName) = 0 ;
	virtual _di_NSArray __cdecl stringArrayForKey(_di_NSString defaultName) = 0 ;
	virtual _di_NSString __cdecl stringForKey(_di_NSString defaultName) = 0 ;
	virtual bool __cdecl synchronize() = 0 ;
	virtual _di_NSDictionary __cdecl volatileDomainForName(_di_NSString domainName) = 0 ;
	virtual _di_NSArray __cdecl volatileDomainNames() = 0 ;
};

class PASCALIMPLEMENTATION TNSUserDefaults : public Macapi::Objectivec::TOCGenericImport__2<_di_NSUserDefaultsClass,_di_NSUserDefaults>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSUserDefaultsClass,_di_NSUserDefaults> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSUserDefaults(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSUserDefaultsClass,_di_NSUserDefaults>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSUserDefaults() { }
	
};


__interface  INTERFACE_UUID("{2B574496-79E9-411D-A51E-AA634E07421D}") NSConditionClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{E23AECF0-6BA2-4110-8244-D7C39CBFAA36}") NSCondition  : public NSObject 
{
	virtual void __cdecl broadcast() = 0 ;
	virtual _di_NSString __cdecl name() = 0 ;
	virtual void __cdecl setName(_di_NSString n) = 0 ;
	virtual void __cdecl signal() = 0 ;
	virtual void __cdecl wait() = 0 ;
	virtual bool __cdecl waitUntilDate(_di_NSDate limit) = 0 ;
};

class PASCALIMPLEMENTATION TNSCondition : public Macapi::Objectivec::TOCGenericImport__2<_di_NSConditionClass,_di_NSCondition>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSConditionClass,_di_NSCondition> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSCondition(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSConditionClass,_di_NSCondition>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSCondition() { }
	
};


__interface  INTERFACE_UUID("{B62A5881-27E0-444A-A6B2-06EDA757184F}") NSValueTransformerClass  : public NSObjectClass 
{
	virtual bool __cdecl allowsReverseTransformation() = 0 ;
	virtual void __cdecl setValueTransformer(_di_NSValueTransformer transformer, _di_NSString forName) = 0 ;
	virtual void * __cdecl valueTransformerForName(_di_NSString name) = 0 ;
	virtual _di_NSArray __cdecl valueTransformerNames() = 0 ;
};

__interface  INTERFACE_UUID("{87BD3A8C-2E71-425F-B42E-5FD56B6F80E4}") NSValueTransformer  : public NSObject 
{
	virtual void * __cdecl reverseTransformedValue(void * value) = 0 ;
	virtual void * __cdecl transformedValue(void * value) = 0 ;
};

class PASCALIMPLEMENTATION TNSValueTransformer : public Macapi::Objectivec::TOCGenericImport__2<_di_NSValueTransformerClass,_di_NSValueTransformer>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSValueTransformerClass,_di_NSValueTransformer> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSValueTransformer(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSValueTransformerClass,_di_NSValueTransformer>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSValueTransformer() { }
	
};


__interface  INTERFACE_UUID("{182B7688-3BE2-465F-B2E5-A9D5015E6E88}") NSValueClass  : public NSObjectClass 
{
	virtual void * __cdecl value(void * value, char * withObjCType) = 0 ;
	virtual void * __cdecl valueWithBytes(void * value, char * objCType) = 0 ;
	virtual void * __cdecl valueWithNonretainedObject(void * anObject) = 0 ;
	virtual void * __cdecl valueWithPointer(void * pointer) = 0 ;
	virtual void * __cdecl valueWithRange(NSRange range) = 0 ;
};

__interface  INTERFACE_UUID("{3CF18344-A043-4C8F-ACCE-B52DC34C14A9}") NSValue  : public NSObject 
{
	virtual void __cdecl getValue(void * value) = 0 ;
	virtual void * __cdecl initWithBytes(void * value, char * objCType) = 0 ;
	virtual bool __cdecl isEqualToValue(_di_NSValue value) = 0 ;
	virtual void * __cdecl nonretainedObjectValue() = 0 ;
	virtual char * __cdecl objCType() = 0 ;
	virtual void * __cdecl pointerValue() = 0 ;
	virtual NSRange __cdecl rangeValue() = 0 ;
};

class PASCALIMPLEMENTATION TNSValue : public Macapi::Objectivec::TOCGenericImport__2<_di_NSValueClass,_di_NSValue>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSValueClass,_di_NSValue> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSValue(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSValueClass,_di_NSValue>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSValue() { }
	
};


__interface  INTERFACE_UUID("{12C8F7BC-F3BC-425F-B1C6-4D17A93F861B}") NSDateComponentsClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{485F32A8-8CE5-4CCA-A03B-EEE021A8D8D8}") NSDateComponents  : public NSObject 
{
	virtual _di_NSCalendar __cdecl calendar() = 0 ;
	virtual _di_NSDate __cdecl date() = 0 ;
	virtual long __cdecl day() = 0 ;
	virtual long __cdecl era() = 0 ;
	virtual long __cdecl hour() = 0 ;
	virtual long __cdecl minute() = 0 ;
	virtual long __cdecl month() = 0 ;
	virtual long __cdecl quarter() = 0 ;
	virtual long __cdecl second() = 0 ;
	virtual long __cdecl nanosecond() = 0 ;
	virtual void __cdecl setCalendar(_di_NSCalendar cal) = 0 ;
	virtual void __cdecl setDay(long v) = 0 ;
	virtual void __cdecl setEra(long v) = 0 ;
	virtual void __cdecl setHour(long v) = 0 ;
	virtual void __cdecl setMinute(long v) = 0 ;
	virtual void __cdecl setMonth(long v) = 0 ;
	virtual void __cdecl setQuarter(long v) = 0 ;
	virtual void __cdecl setSecond(long v) = 0 ;
	virtual void __cdecl setTimeZone(_di_NSTimeZone tz) = 0 ;
	virtual void __cdecl setWeek(long v) = 0 ;
	virtual void __cdecl setWeekOfMonth(long w) = 0 ;
	virtual void __cdecl setWeekOfYear(long w) = 0 ;
	virtual void __cdecl setWeekday(long v) = 0 ;
	virtual void __cdecl setWeekdayOrdinal(long v) = 0 ;
	virtual void __cdecl setYear(long v) = 0 ;
	virtual void __cdecl setYearForWeekOfYear(long y) = 0 ;
	virtual void __cdecl setNanosecond(long n) = 0 ;
	virtual _di_NSTimeZone __cdecl timeZone() = 0 ;
	virtual long __cdecl week() = 0 ;
	virtual long __cdecl weekOfMonth() = 0 ;
	virtual long __cdecl weekOfYear() = 0 ;
	virtual long __cdecl weekday() = 0 ;
	virtual long __cdecl weekdayOrdinal() = 0 ;
	virtual long __cdecl year() = 0 ;
	virtual long __cdecl yearForWeekOfYear() = 0 ;
};

class PASCALIMPLEMENTATION TNSDateComponents : public Macapi::Objectivec::TOCGenericImport__2<_di_NSDateComponentsClass,_di_NSDateComponents>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSDateComponentsClass,_di_NSDateComponents> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSDateComponents(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSDateComponentsClass,_di_NSDateComponents>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSDateComponents() { }
	
};


__interface  INTERFACE_UUID("{188E43E2-1970-41A6-AF30-47FBEBCE88C8}") NSUbiquitousKeyValueStoreClass  : public NSObjectClass 
{
	virtual void * __cdecl defaultStore() = 0 ;
};

__interface  INTERFACE_UUID("{76EC096B-4E30-4C34-9BD3-B9751D3414C0}") NSUbiquitousKeyValueStore  : public NSObject 
{
	virtual _di_NSArray __cdecl arrayForKey(_di_NSString aKey) = 0 ;
	virtual bool __cdecl boolForKey(_di_NSString aKey) = 0 ;
	virtual _di_NSData __cdecl dataForKey(_di_NSString aKey) = 0 ;
	virtual _di_NSDictionary __cdecl dictionaryForKey(_di_NSString aKey) = 0 ;
	virtual _di_NSDictionary __cdecl dictionaryRepresentation() = 0 ;
	virtual double __cdecl doubleForKey(_di_NSString aKey) = 0 ;
	virtual __int64 __cdecl longLongForKey(_di_NSString aKey) = 0 ;
	virtual void * __cdecl objectForKey(_di_NSString aKey) = 0 ;
	virtual void __cdecl removeObjectForKey(_di_NSString aKey) = 0 ;
	virtual void __cdecl setArray(_di_NSArray anArray, _di_NSString forKey) = 0 ;
	virtual void __cdecl setBool(bool value, _di_NSString forKey) = 0 ;
	virtual void __cdecl setData(_di_NSData aData, _di_NSString forKey) = 0 ;
	virtual void __cdecl setDictionary(_di_NSDictionary aDictionary, _di_NSString forKey) = 0 ;
	virtual void __cdecl setDouble(double value, _di_NSString forKey) = 0 ;
	virtual void __cdecl setLongLong(__int64 value, _di_NSString forKey) = 0 ;
	virtual void __cdecl setObject(void * anObject, _di_NSString forKey) = 0 ;
	virtual void __cdecl setString(_di_NSString aString, _di_NSString forKey) = 0 ;
	virtual _di_NSString __cdecl stringForKey(_di_NSString aKey) = 0 ;
	virtual bool __cdecl synchronize() = 0 ;
};

class PASCALIMPLEMENTATION TNSUbiquitousKeyValueStore : public Macapi::Objectivec::TOCGenericImport__2<_di_NSUbiquitousKeyValueStoreClass,_di_NSUbiquitousKeyValueStore>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSUbiquitousKeyValueStoreClass,_di_NSUbiquitousKeyValueStore> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSUbiquitousKeyValueStore(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSUbiquitousKeyValueStoreClass,_di_NSUbiquitousKeyValueStore>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSUbiquitousKeyValueStore() { }
	
};


__interface  INTERFACE_UUID("{CD5F76FF-1CAF-4AA7-B2D2-BACA8B0CF3DE}") NSDateClass  : public NSObjectClass 
{
	virtual void * __cdecl date() = 0 ;
	virtual void * __cdecl dateWithTimeInterval(double ti, _di_NSDate sinceDate) = 0 ;
	virtual void * __cdecl dateWithTimeIntervalSince1970(double secs) = 0 ;
	virtual void * __cdecl dateWithTimeIntervalSinceNow(double secs) = 0 ;
	virtual void * __cdecl dateWithTimeIntervalSinceReferenceDate(double secs) = 0 ;
	virtual void * __cdecl distantFuture() = 0 ;
	virtual void * __cdecl distantPast() = 0 ;
	virtual double __cdecl timeIntervalSinceReferenceDate() = 0 /* overload */;
};

__interface  INTERFACE_UUID("{93FC9F8F-5AC2-4ED8-B5DA-0B05FC45FFFA}") NSDate  : public NSObject 
{
	virtual void * __cdecl addTimeInterval(double seconds) = 0 ;
	virtual long __cdecl compare(_di_NSDate other) = 0 ;
	virtual void * __cdecl dateByAddingTimeInterval(double ti) = 0 ;
	virtual _di_NSString __cdecl description() = 0 ;
	virtual _di_NSString __cdecl descriptionWithLocale(void * locale) = 0 ;
	virtual _di_NSDate __cdecl earlierDate(_di_NSDate anotherDate) = 0 ;
	HIDESBASE virtual void * __cdecl init() = 0 ;
	virtual void * __cdecl initWithTimeInterval(double secsToBeAdded, _di_NSDate sinceDate) = 0 ;
	virtual void * __cdecl initWithTimeIntervalSince1970(double ti) = 0 ;
	virtual void * __cdecl initWithTimeIntervalSinceNow(double secs) = 0 ;
	virtual void * __cdecl initWithTimeIntervalSinceReferenceDate(double secsToBeAdded) = 0 ;
	virtual bool __cdecl isEqualToDate(_di_NSDate otherDate) = 0 ;
	virtual _di_NSDate __cdecl laterDate(_di_NSDate anotherDate) = 0 ;
	virtual double __cdecl timeIntervalSince1970() = 0 ;
	virtual double __cdecl timeIntervalSinceDate(_di_NSDate anotherDate) = 0 ;
	virtual double __cdecl timeIntervalSinceNow() = 0 ;
	virtual double __cdecl timeIntervalSinceReferenceDate() = 0 /* overload */;
};

class PASCALIMPLEMENTATION TNSDate : public Macapi::Objectivec::TOCGenericImport__2<_di_NSDateClass,_di_NSDate>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSDateClass,_di_NSDate> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSDate(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSDateClass,_di_NSDate>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSDate() { }
	
};


__interface  INTERFACE_UUID("{FC1B5E54-5356-41B1-9784-806C092CC2C8}") NSDataClass  : public NSObjectClass 
{
	virtual void * __cdecl data() = 0 ;
	virtual void * __cdecl dataWithBytes(void * bytes, unsigned long length) = 0 ;
	virtual void * __cdecl dataWithBytesNoCopy(void * bytes, unsigned long length) = 0 /* overload */;
	virtual void * __cdecl dataWithBytesNoCopy(void * bytes, unsigned long length, bool freeWhenDone) = 0 /* overload */;
	virtual void * __cdecl dataWithContentsOfFile(_di_NSString path) = 0 /* overload */;
	virtual void * __cdecl dataWithContentsOfFile(_di_NSString path, unsigned long options, System::PPointer error = (System::PPointer)(0x0)) = 0 /* overload */;
	virtual void * __cdecl dataWithContentsOfMappedFile(_di_NSString path) = 0 ;
	virtual void * __cdecl dataWithContentsOfURL(_di_NSURL url) = 0 /* overload */;
	virtual void * __cdecl dataWithContentsOfURL(_di_NSURL url, unsigned long options, System::PPointer error = (System::PPointer)(0x0)) = 0 /* overload */;
	virtual void * __cdecl dataWithData(_di_NSData data) = 0 ;
};

__interface  INTERFACE_UUID("{E3D4B061-40E6-4506-8B27-34185AB7FD5E}") NSData  : public NSObject 
{
	virtual void * __cdecl bytes() = 0 ;
	virtual _di_NSString __cdecl description() = 0 ;
	virtual void __cdecl getBytes(void * buffer) = 0 /* overload */;
	virtual void __cdecl getBytes(void * buffer, unsigned long length) = 0 /* overload */;
	virtual void __cdecl getBytes(void * buffer, NSRange range) = 0 /* overload */;
	virtual void * __cdecl initWithBytes(void * bytes, unsigned long length) = 0 ;
	virtual void * __cdecl initWithBytesNoCopy(void * bytes, unsigned long length) = 0 /* overload */;
	virtual void * __cdecl initWithBytesNoCopy(void * bytes, unsigned long length, bool freeWhenDone) = 0 /* overload */;
	virtual void * __cdecl initWithContentsOfFile(_di_NSString path) = 0 /* overload */;
	virtual void * __cdecl initWithContentsOfFile(_di_NSString path, unsigned long options, System::PPointer error = (System::PPointer)(0x0)) = 0 /* overload */;
	virtual void * __cdecl initWithContentsOfMappedFile(_di_NSString path) = 0 ;
	virtual void * __cdecl initWithContentsOfURL(_di_NSURL url) = 0 /* overload */;
	virtual void * __cdecl initWithContentsOfURL(_di_NSURL url, unsigned long options, System::PPointer error = (System::PPointer)(0x0)) = 0 /* overload */;
	virtual void * __cdecl initWithData(_di_NSData data) = 0 ;
	virtual bool __cdecl isEqualToData(_di_NSData other) = 0 ;
	virtual unsigned long __cdecl length() = 0 ;
	virtual NSRange __cdecl rangeOfData(_di_NSData dataToFind, unsigned long options, NSRange range) = 0 ;
	virtual _di_NSData __cdecl subdataWithRange(NSRange range) = 0 ;
	virtual bool __cdecl writeToFile(_di_NSString path, bool atomically) = 0 /* overload */;
	virtual bool __cdecl writeToFile(_di_NSString path, unsigned long options, System::PPointer error = (System::PPointer)(0x0)) = 0 /* overload */;
	virtual bool __cdecl writeToURL(_di_NSURL url, bool atomically) = 0 /* overload */;
	virtual bool __cdecl writeToURL(_di_NSURL url, unsigned long options, System::PPointer error = (System::PPointer)(0x0)) = 0 /* overload */;
};

class PASCALIMPLEMENTATION TNSData : public Macapi::Objectivec::TOCGenericImport__2<_di_NSDataClass,_di_NSData>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSDataClass,_di_NSData> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSData(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSDataClass,_di_NSData>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSData() { }
	
};


__interface  INTERFACE_UUID("{7A732426-E04C-4526-AA3B-CE84723EC6FE}") NSUndoManagerClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{D0712CF9-8A53-4281-AA41-C66CD12B1122}") NSUndoManager  : public NSObject 
{
	virtual void __cdecl beginUndoGrouping() = 0 ;
	virtual bool __cdecl canRedo() = 0 ;
	virtual bool __cdecl canUndo() = 0 ;
	virtual void __cdecl disableUndoRegistration() = 0 ;
	virtual void __cdecl enableUndoRegistration() = 0 ;
	virtual void __cdecl endUndoGrouping() = 0 ;
	virtual long __cdecl groupingLevel() = 0 ;
	virtual bool __cdecl groupsByEvent() = 0 ;
	virtual bool __cdecl isRedoing() = 0 ;
	virtual bool __cdecl isUndoRegistrationEnabled() = 0 ;
	virtual bool __cdecl isUndoing() = 0 ;
	virtual unsigned long __cdecl levelsOfUndo() = 0 ;
	virtual void * __cdecl prepareWithInvocationTarget(void * target) = 0 ;
	virtual void __cdecl redo() = 0 ;
	virtual bool __cdecl redoActionIsDiscardable() = 0 ;
	virtual _di_NSString __cdecl redoActionName() = 0 ;
	virtual _di_NSString __cdecl redoMenuItemTitle() = 0 ;
	virtual _di_NSString __cdecl redoMenuTitleForUndoActionName(_di_NSString actionName) = 0 ;
	virtual void __cdecl removeAllActions() = 0 ;
	virtual void __cdecl removeAllActionsWithTarget(void * target) = 0 ;
	virtual _di_NSArray __cdecl runLoopModes() = 0 ;
	virtual void __cdecl setActionIsDiscardable(bool discardable) = 0 ;
	virtual void __cdecl setActionName(_di_NSString actionName) = 0 ;
	virtual void __cdecl setGroupsByEvent(bool groupsByEvent) = 0 ;
	virtual void __cdecl setLevelsOfUndo(unsigned long levels) = 0 ;
	virtual void __cdecl setRunLoopModes(_di_NSArray runLoopModes) = 0 ;
	virtual void __cdecl undo() = 0 ;
	virtual bool __cdecl undoActionIsDiscardable() = 0 ;
	virtual _di_NSString __cdecl undoActionName() = 0 ;
	virtual _di_NSString __cdecl undoMenuItemTitle() = 0 ;
	virtual _di_NSString __cdecl undoMenuTitleForUndoActionName(_di_NSString actionName) = 0 ;
	virtual void __cdecl undoNestedGroup() = 0 ;
};

class PASCALIMPLEMENTATION TNSUndoManager : public Macapi::Objectivec::TOCGenericImport__2<_di_NSUndoManagerClass,_di_NSUndoManager>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSUndoManagerClass,_di_NSUndoManager> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSUndoManager(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSUndoManagerClass,_di_NSUndoManager>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSUndoManager() { }
	
};


__interface  INTERFACE_UUID("{6D32BE75-E10C-4B9E-9F3E-49F748647B3A}") NSCoderClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{949794EC-3459-4BD6-918A-0F542F675C94}") NSCoder  : public NSObject 
{
	virtual bool __cdecl allowsKeyedCoding() = 0 ;
	virtual bool __cdecl containsValueForKey(_di_NSString key) = 0 ;
	virtual void __cdecl decodeArrayOfObjCType(char * itemType, unsigned long count, void * at) = 0 ;
	virtual bool __cdecl decodeBoolForKey(_di_NSString key) = 0 ;
	virtual System::PByte __cdecl decodeBytesForKey(_di_NSString key, Iosapi::Cocoatypes::PNSUInteger returnedLength) = 0 ;
	virtual void * __cdecl decodeBytesWithReturnedLength(Iosapi::Cocoatypes::PNSUInteger lengthp) = 0 ;
	virtual _di_NSData __cdecl decodeDataObject() = 0 ;
	virtual double __cdecl decodeDoubleForKey(_di_NSString key) = 0 ;
	virtual float __cdecl decodeFloatForKey(_di_NSString key) = 0 ;
	virtual int __cdecl decodeInt32ForKey(_di_NSString key) = 0 ;
	virtual __int64 __cdecl decodeInt64ForKey(_di_NSString key) = 0 ;
	virtual int __cdecl decodeIntForKey(_di_NSString key) = 0 ;
	virtual long __cdecl decodeIntegerForKey(_di_NSString key) = 0 ;
	virtual void * __cdecl decodeObject() = 0 ;
	virtual void * __cdecl decodeObjectForKey(_di_NSString key) = 0 ;
	virtual void __cdecl decodeValueOfObjCType(char * type_, void * at) = 0 ;
	virtual void __cdecl decodeValuesOfObjCTypes(char * types) = 0 ;
	virtual void __cdecl encodeArrayOfObjCType(char * type_, unsigned long count, void * at) = 0 ;
	virtual void __cdecl encodeBool(bool boolv, _di_NSString forKey) = 0 ;
	virtual void __cdecl encodeBycopyObject(void * anObject) = 0 ;
	virtual void __cdecl encodeByrefObject(void * anObject) = 0 ;
	virtual void __cdecl encodeBytes(void * byteaddr, unsigned long length) = 0 /* overload */;
	virtual void __cdecl encodeBytes(System::PByte bytesp, unsigned long length, _di_NSString forKey) = 0 /* overload */;
	virtual void __cdecl encodeConditionalObject(void * object_) = 0 /* overload */;
	virtual void __cdecl encodeConditionalObject(void * objv, _di_NSString forKey) = 0 /* overload */;
	virtual void __cdecl encodeDataObject(_di_NSData data) = 0 ;
	virtual void __cdecl encodeDouble(double realv, _di_NSString forKey) = 0 ;
	virtual void __cdecl encodeFloat(float realv, _di_NSString forKey) = 0 ;
	virtual void __cdecl encodeInt32(int intv, _di_NSString forKey) = 0 ;
	virtual void __cdecl encodeInt64(__int64 intv, _di_NSString forKey) = 0 ;
	virtual void __cdecl encodeInt(int intv, _di_NSString forKey) = 0 ;
	virtual void __cdecl encodeInteger(long intv, _di_NSString forKey) = 0 ;
	virtual void __cdecl encodeObject(void * object_) = 0 /* overload */;
	virtual void __cdecl encodeObject(void * objv, _di_NSString forKey) = 0 /* overload */;
	virtual void __cdecl encodeRootObject(void * rootObject) = 0 ;
	virtual void __cdecl encodeValueOfObjCType(char * type_, void * at) = 0 ;
	virtual void __cdecl encodeValuesOfObjCTypes(char * types) = 0 ;
	virtual void * __cdecl objectZone() = 0 ;
	virtual void __cdecl setObjectZone(void * zone) = 0 ;
	virtual unsigned __cdecl systemVersion() = 0 ;
	virtual long __cdecl versionForClassName(_di_NSString className) = 0 ;
};

class PASCALIMPLEMENTATION TNSCoder : public Macapi::Objectivec::TOCGenericImport__2<_di_NSCoderClass,_di_NSCoder>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSCoderClass,_di_NSCoder> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSCoder(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSCoderClass,_di_NSCoder>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSCoder() { }
	
};


__interface  INTERFACE_UUID("{DBA0D78E-8F08-45AA-A5AD-F8467DE270A9}") NSAutoreleasePoolClass  : public NSObjectClass 
{
	virtual void __cdecl addObject(void * anObject) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{587CDD53-8646-42AC-8A6F-3F9B356C5D7B}") NSAutoreleasePool  : public NSObject 
{
	virtual void __cdecl addObject(void * anObject) = 0 /* overload */;
	virtual void __cdecl drain() = 0 ;
};

class PASCALIMPLEMENTATION TNSAutoreleasePool : public Macapi::Objectivec::TOCGenericImport__2<_di_NSAutoreleasePoolClass,_di_NSAutoreleasePool>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSAutoreleasePoolClass,_di_NSAutoreleasePool> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSAutoreleasePool(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSAutoreleasePoolClass,_di_NSAutoreleasePool>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSAutoreleasePool() { }
	
};


__interface  INTERFACE_UUID("{8891E206-097C-4813-8484-2A5269B52970}") NSXMLParserClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{F6681F54-46BC-4EFE-B60E-C2D36CBC366E}") NSXMLParser  : public NSObject 
{
	virtual void __cdecl abortParsing() = 0 ;
	virtual long __cdecl columnNumber() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual void * __cdecl initWithContentsOfURL(_di_NSURL url) = 0 ;
	virtual void * __cdecl initWithData(_di_NSData data) = 0 ;
	virtual void * __cdecl initWithStream(_di_NSInputStream stream) = 0 ;
	virtual long __cdecl lineNumber() = 0 ;
	virtual bool __cdecl parse() = 0 ;
	virtual _di_NSError __cdecl parserError() = 0 ;
	virtual _di_NSString __cdecl publicID() = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setShouldProcessNamespaces(bool shouldProcessNamespaces) = 0 ;
	virtual void __cdecl setShouldReportNamespacePrefixes(bool shouldReportNamespacePrefixes) = 0 ;
	virtual void __cdecl setShouldResolveExternalEntities(bool shouldResolveExternalEntities) = 0 ;
	virtual bool __cdecl shouldProcessNamespaces() = 0 ;
	virtual bool __cdecl shouldReportNamespacePrefixes() = 0 ;
	virtual bool __cdecl shouldResolveExternalEntities() = 0 ;
	virtual _di_NSString __cdecl systemID() = 0 ;
};

class PASCALIMPLEMENTATION TNSXMLParser : public Macapi::Objectivec::TOCGenericImport__2<_di_NSXMLParserClass,_di_NSXMLParser>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSXMLParserClass,_di_NSXMLParser> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSXMLParser(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSXMLParserClass,_di_NSXMLParser>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSXMLParser() { }
	
};


__interface  INTERFACE_UUID("{B73B65A2-F931-4FD6-921C-366915725D58}") NSAttributedStringClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{D1B80173-A550-4876-93C5-70EAB5E6E8A7}") NSAttributedString  : public NSObject 
{
	virtual void * __cdecl attribute(_di_NSString attrName, unsigned long atIndex, PNSRange effectiveRange) = 0 /* overload */;
	virtual void * __cdecl attribute(_di_NSString attrName, unsigned long atIndex, PNSRange longestEffectiveRange, NSRange inRange) = 0 /* overload */;
	virtual _di_NSAttributedString __cdecl attributedSubstringFromRange(NSRange range) = 0 ;
	virtual _di_NSDictionary __cdecl attributesAtIndex(unsigned long location, PNSRange effectiveRange) = 0 /* overload */;
	virtual _di_NSDictionary __cdecl attributesAtIndex(unsigned long location, PNSRange longestEffectiveRange, NSRange inRange) = 0 /* overload */;
	virtual void * __cdecl initWithAttributedString(_di_NSAttributedString attrStr) = 0 ;
	virtual void * __cdecl initWithString(_di_NSString str) = 0 /* overload */;
	virtual void * __cdecl initWithString(_di_NSString str, _di_NSDictionary attributes) = 0 /* overload */;
	virtual bool __cdecl isEqualToAttributedString(_di_NSAttributedString other) = 0 ;
	virtual unsigned long __cdecl length() = 0 ;
};

class PASCALIMPLEMENTATION TNSAttributedString : public Macapi::Objectivec::TOCGenericImport__2<_di_NSAttributedStringClass,_di_NSAttributedString>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSAttributedStringClass,_di_NSAttributedString> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSAttributedString(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSAttributedStringClass,_di_NSAttributedString>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSAttributedString() { }
	
};


__interface  INTERFACE_UUID("{4046AAAF-5D17-4625-BCB3-74560E52835A}") NSArrayClass  : public NSObjectClass 
{
	virtual void * __cdecl arrayWithArray(_di_NSArray array_) = 0 ;
	virtual void * __cdecl arrayWithContentsOfFile(_di_NSString path) = 0 ;
	virtual void * __cdecl arrayWithContentsOfURL(_di_NSURL url) = 0 ;
	virtual void * __cdecl arrayWithObject(void * anObject) = 0 ;
	virtual void * __cdecl arrayWithObjects(void * firstObj) = 0 /* overload */;
	virtual void * __cdecl arrayWithObjects(void * objects, unsigned long count) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{4738B4F2-347A-41C6-8B62-F0E324B67C7B}") NSArray  : public NSObject 
{
	HIDESBASE virtual void __cdecl addObserver(_di_NSObject observer, _di_NSString forKeyPath, unsigned long options, void * context) = 0 /* overload */;
	HIDESBASE virtual void __cdecl addObserver(_di_NSObject observer, _di_NSIndexSet toObjectsAtIndexes, _di_NSString forKeyPath, unsigned long options, void * context) = 0 /* overload */;
	virtual _di_NSArray __cdecl arrayByAddingObject(void * anObject) = 0 ;
	virtual _di_NSArray __cdecl arrayByAddingObjectsFromArray(_di_NSArray otherArray) = 0 ;
	virtual _di_NSString __cdecl componentsJoinedByString(_di_NSString separator) = 0 ;
	virtual bool __cdecl containsObject(void * anObject) = 0 ;
	virtual unsigned long __cdecl count() = 0 ;
	virtual _di_NSString __cdecl description() = 0 ;
	virtual _di_NSString __cdecl descriptionWithLocale(void * locale) = 0 /* overload */;
	virtual _di_NSString __cdecl descriptionWithLocale(void * locale, unsigned long indent) = 0 /* overload */;
	virtual _di_NSArray __cdecl filteredArrayUsingPredicate(_di_NSPredicate predicate) = 0 ;
	virtual void * __cdecl firstObjectCommonWithArray(_di_NSArray otherArray) = 0 ;
	virtual void __cdecl getObjects(void * objects) = 0 /* overload */;
	virtual void __cdecl getObjects(void * objects, NSRange range) = 0 /* overload */;
	virtual unsigned long __cdecl indexOfObject(void * anObject) = 0 /* overload */;
	virtual unsigned long __cdecl indexOfObject(void * anObject, NSRange inRange) = 0 /* overload */;
	virtual unsigned long __cdecl indexOfObjectIdenticalTo(void * anObject) = 0 /* overload */;
	virtual unsigned long __cdecl indexOfObjectIdenticalTo(void * anObject, NSRange inRange) = 0 /* overload */;
	virtual void * __cdecl initWithArray(_di_NSArray array_) = 0 /* overload */;
	virtual void * __cdecl initWithArray(_di_NSArray array_, bool copyItems) = 0 /* overload */;
	virtual void * __cdecl initWithContentsOfFile(_di_NSString path) = 0 ;
	virtual void * __cdecl initWithContentsOfURL(_di_NSURL url) = 0 ;
	virtual void * __cdecl initWithObjects(void * firstObj) = 0 /* overload */;
	virtual void * __cdecl initWithObjects(void * objects, unsigned long count) = 0 /* overload */;
	virtual bool __cdecl isEqualToArray(_di_NSArray otherArray) = 0 ;
	virtual void * __cdecl lastObject() = 0 ;
	virtual void __cdecl makeObjectsPerformSelector(void * aSelector) = 0 /* overload */;
	virtual void __cdecl makeObjectsPerformSelector(void * aSelector, void * withObject) = 0 /* overload */;
	virtual void * __cdecl objectAtIndex(unsigned long index) = 0 ;
	virtual _di_NSEnumerator __cdecl objectEnumerator() = 0 ;
	virtual _di_NSArray __cdecl objectsAtIndexes(_di_NSIndexSet indexes) = 0 ;
	virtual _di_NSArray __cdecl pathsMatchingExtensions(_di_NSArray filterTypes) = 0 ;
	HIDESBASE virtual void __cdecl removeObserver(_di_NSObject observer, _di_NSString forKeyPath) = 0 /* overload */;
	HIDESBASE virtual void __cdecl removeObserver(_di_NSObject observer, _di_NSString forKeyPath, void * context) = 0 /* overload */;
	HIDESBASE virtual void __cdecl removeObserver(_di_NSObject observer, _di_NSIndexSet fromObjectsAtIndexes, _di_NSString forKeyPath) = 0 /* overload */;
	HIDESBASE virtual void __cdecl removeObserver(_di_NSObject observer, _di_NSIndexSet fromObjectsAtIndexes, _di_NSString forKeyPath, void * context) = 0 /* overload */;
	virtual _di_NSEnumerator __cdecl reverseObjectEnumerator() = 0 ;
	virtual void __cdecl setValue(void * value, _di_NSString forKey) = 0 ;
	virtual _di_NSData __cdecl sortedArrayHint() = 0 ;
	virtual _di_NSArray __cdecl sortedArrayUsingDescriptors(_di_NSArray sortDescriptors) = 0 ;
	virtual _di_NSArray __cdecl sortedArrayUsingSelector(void * comparator) = 0 ;
	virtual _di_NSArray __cdecl subarrayWithRange(NSRange range) = 0 ;
	HIDESBASE virtual void * __cdecl valueForKey(_di_NSString key) = 0 ;
	virtual bool __cdecl writeToFile(_di_NSString path, bool atomically) = 0 ;
	virtual bool __cdecl writeToURL(_di_NSURL url, bool atomically) = 0 ;
};

class PASCALIMPLEMENTATION TNSArray : public Macapi::Objectivec::TOCGenericImport__2<_di_NSArrayClass,_di_NSArray>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSArrayClass,_di_NSArray> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSArray(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSArrayClass,_di_NSArray>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSArray() { }
	
};


__interface  INTERFACE_UUID("{FAD13D4D-08C4-4800-AE0A-3C7BDA6D8EA2}") NSAssertionHandlerClass  : public NSObjectClass 
{
	virtual void * __cdecl currentHandler() = 0 ;
};

__interface  INTERFACE_UUID("{34F7FF7F-1D9B-47B0-B5D0-73D8DCE851DF}") NSAssertionHandler  : public NSObject 
{
	
};

class PASCALIMPLEMENTATION TNSAssertionHandler : public Macapi::Objectivec::TOCGenericImport__2<_di_NSAssertionHandlerClass,_di_NSAssertionHandler>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSAssertionHandlerClass,_di_NSAssertionHandler> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSAssertionHandler(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSAssertionHandlerClass,_di_NSAssertionHandler>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSAssertionHandler() { }
	
};


__interface  INTERFACE_UUID("{D79DCC09-8263-448E-B5A4-FD6982962107}") NSCalendarClass  : public NSObjectClass 
{
	virtual void * __cdecl autoupdatingCurrentCalendar() = 0 ;
	virtual void * __cdecl currentCalendar() = 0 ;
};

__interface  INTERFACE_UUID("{C77984D5-A41A-418B-9191-3ACA383B4C1D}") NSCalendar  : public NSObject 
{
	virtual _di_NSString __cdecl calendarIdentifier() = 0 ;
	virtual _di_NSDateComponents __cdecl components(unsigned long unitFlags, _di_NSDate fromDate) = 0 /* overload */;
	virtual _di_NSDateComponents __cdecl components(unsigned long unitFlags, _di_NSDate fromDate, _di_NSDate toDate, unsigned long options) = 0 /* overload */;
	virtual _di_NSDate __cdecl dateByAddingComponents(_di_NSDateComponents comps, _di_NSDate toDate, unsigned long options) = 0 ;
	virtual _di_NSDate __cdecl dateFromComponents(_di_NSDateComponents comps) = 0 ;
	virtual unsigned long __cdecl firstWeekday() = 0 ;
	virtual void * __cdecl initWithCalendarIdentifier(_di_NSString ident) = 0 ;
	virtual _di_NSLocale __cdecl locale() = 0 ;
	virtual NSRange __cdecl maximumRangeOfUnit(unsigned long unit_) = 0 ;
	virtual unsigned long __cdecl minimumDaysInFirstWeek() = 0 ;
	virtual NSRange __cdecl minimumRangeOfUnit(unsigned long unit_) = 0 ;
	virtual unsigned long __cdecl ordinalityOfUnit(unsigned long smaller, unsigned long inUnit, _di_NSDate forDate) = 0 ;
	virtual NSRange __cdecl rangeOfUnit(unsigned long smaller, unsigned long inUnit, _di_NSDate forDate) = 0 /* overload */;
	virtual bool __cdecl rangeOfUnit(unsigned long unit_, _di_NSDate startDate, double interval, _di_NSDate forDate) = 0 /* overload */;
	virtual void __cdecl setFirstWeekday(unsigned long weekday) = 0 ;
	virtual void __cdecl setLocale(_di_NSLocale locale) = 0 ;
	virtual void __cdecl setMinimumDaysInFirstWeek(unsigned long mdw) = 0 ;
	virtual void __cdecl setTimeZone(_di_NSTimeZone tz) = 0 ;
	virtual _di_NSTimeZone __cdecl timeZone() = 0 ;
};

class PASCALIMPLEMENTATION TNSCalendar : public Macapi::Objectivec::TOCGenericImport__2<_di_NSCalendarClass,_di_NSCalendar>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSCalendarClass,_di_NSCalendar> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSCalendar(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSCalendarClass,_di_NSCalendar>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSCalendar() { }
	
};


__interface  INTERFACE_UUID("{9A6BBEF7-C9AA-44B0-B0E9-DDAF728B416E}") NSCharacterSetClass  : public NSObjectClass 
{
	virtual void * __cdecl alphanumericCharacterSet() = 0 ;
	virtual void * __cdecl capitalizedLetterCharacterSet() = 0 ;
	virtual void * __cdecl characterSetWithBitmapRepresentation(_di_NSData data) = 0 ;
	virtual void * __cdecl characterSetWithCharactersInString(_di_NSString aString) = 0 ;
	virtual void * __cdecl characterSetWithContentsOfFile(_di_NSString fName) = 0 ;
	virtual void * __cdecl characterSetWithRange(NSRange aRange) = 0 ;
	virtual void * __cdecl controlCharacterSet() = 0 ;
	virtual void * __cdecl decimalDigitCharacterSet() = 0 ;
	virtual void * __cdecl decomposableCharacterSet() = 0 ;
	virtual void * __cdecl illegalCharacterSet() = 0 ;
	virtual void * __cdecl letterCharacterSet() = 0 ;
	virtual void * __cdecl lowercaseLetterCharacterSet() = 0 ;
	virtual void * __cdecl newlineCharacterSet() = 0 ;
	virtual void * __cdecl nonBaseCharacterSet() = 0 ;
	virtual void * __cdecl punctuationCharacterSet() = 0 ;
	virtual void * __cdecl symbolCharacterSet() = 0 ;
	virtual void * __cdecl uppercaseLetterCharacterSet() = 0 ;
	virtual void * __cdecl whitespaceAndNewlineCharacterSet() = 0 ;
	virtual void * __cdecl whitespaceCharacterSet() = 0 ;
};

__interface  INTERFACE_UUID("{71DB44B0-140C-4D12-AE86-1605B8597A34}") NSCharacterSet  : public NSObject 
{
	virtual _di_NSData __cdecl bitmapRepresentation() = 0 ;
	virtual bool __cdecl characterIsMember(System::WideChar aCharacter) = 0 ;
	virtual bool __cdecl hasMemberInPlane(System::Byte thePlane) = 0 ;
	virtual _di_NSCharacterSet __cdecl invertedSet() = 0 ;
	virtual bool __cdecl isSupersetOfSet(_di_NSCharacterSet theOtherSet) = 0 ;
	virtual bool __cdecl longCharacterIsMember(unsigned theLongChar) = 0 ;
};

class PASCALIMPLEMENTATION TNSCharacterSet : public Macapi::Objectivec::TOCGenericImport__2<_di_NSCharacterSetClass,_di_NSCharacterSet>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSCharacterSetClass,_di_NSCharacterSet> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSCharacterSet(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSCharacterSetClass,_di_NSCharacterSet>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSCharacterSet() { }
	
};


__interface  INTERFACE_UUID("{4ABF03BD-8B4B-48D4-A693-8B33CA7032A6}") NSCachedURLResponseClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{41FEF993-7A8B-4EEB-B8D1-A6CC8ED02074}") NSCachedURLResponse  : public NSObject 
{
	virtual _di_NSData __cdecl data() = 0 ;
	virtual void * __cdecl initWithResponse(_di_NSURLResponse response, _di_NSData data) = 0 /* overload */;
	virtual void * __cdecl initWithResponse(_di_NSURLResponse response, _di_NSData data, _di_NSDictionary userInfo, int storagePolicy) = 0 /* overload */;
	virtual _di_NSURLResponse __cdecl response() = 0 ;
	virtual int __cdecl storagePolicy() = 0 ;
	virtual _di_NSDictionary __cdecl userInfo() = 0 ;
};

class PASCALIMPLEMENTATION TNSCachedURLResponse : public Macapi::Objectivec::TOCGenericImport__2<_di_NSCachedURLResponseClass,_di_NSCachedURLResponse>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSCachedURLResponseClass,_di_NSCachedURLResponse> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSCachedURLResponse(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSCachedURLResponseClass,_di_NSCachedURLResponse>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSCachedURLResponse() { }
	
};


__interface  INTERFACE_UUID("{0072ABF4-50F5-46A4-BC0D-D6C5BEADF849}") NSBundleClass  : public NSObjectClass 
{
	virtual _di_NSURL __cdecl URLForResource(_di_NSString name, _di_NSString withExtension, _di_NSString subdirectory, _di_NSURL inBundleWithURL) = 0 /* overload */;
	virtual _di_NSArray __cdecl URLsForResourcesWithExtension(_di_NSString ext, _di_NSString subdirectory, _di_NSURL inBundleWithURL) = 0 /* overload */;
	virtual _di_NSArray __cdecl allBundles() = 0 ;
	virtual _di_NSArray __cdecl allFrameworks() = 0 ;
	virtual void * __cdecl bundleForClass(void * aClass) = 0 ;
	virtual void * __cdecl bundleWithIdentifier(_di_NSString identifier) = 0 ;
	virtual void * __cdecl bundleWithPath(_di_NSString path) = 0 ;
	virtual void * __cdecl bundleWithURL(_di_NSURL url) = 0 ;
	virtual void * __cdecl mainBundle() = 0 ;
	virtual _di_NSString __cdecl pathForResource(_di_NSString name, _di_NSString ofType, _di_NSString inDirectory) = 0 /* overload */;
	virtual _di_NSArray __cdecl pathsForResourcesOfType(_di_NSString ext, _di_NSString inDirectory) = 0 /* overload */;
	virtual _di_NSArray __cdecl preferredLocalizationsFromArray(_di_NSArray localizationsArray) = 0 /* overload */;
	virtual _di_NSArray __cdecl preferredLocalizationsFromArray(_di_NSArray localizationsArray, _di_NSArray forPreferences) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{7C2EF877-25D5-4D60-9CA7-6FD9F99B844A}") NSBundle  : public NSObject 
{
	virtual _di_NSURL __cdecl URLForAuxiliaryExecutable(_di_NSString executableName) = 0 ;
	virtual _di_NSURL __cdecl URLForResource(_di_NSString name, _di_NSString withExtension) = 0 /* overload */;
	virtual _di_NSURL __cdecl URLForResource(_di_NSString name, _di_NSString withExtension, _di_NSString subdirectory) = 0 /* overload */;
	virtual _di_NSURL __cdecl URLForResource(_di_NSString name, _di_NSString withExtension, _di_NSString subdirectory, _di_NSString localization) = 0 /* overload */;
	virtual _di_NSArray __cdecl URLsForResourcesWithExtension(_di_NSString ext, _di_NSString subdirectory) = 0 /* overload */;
	virtual _di_NSArray __cdecl URLsForResourcesWithExtension(_di_NSString ext, _di_NSString subdirectory, _di_NSString localization) = 0 /* overload */;
	virtual _di_NSURL __cdecl appStoreReceiptURL() = 0 ;
	virtual _di_NSString __cdecl builtInPlugInsPath() = 0 ;
	virtual _di_NSURL __cdecl builtInPlugInsURL() = 0 ;
	virtual _di_NSString __cdecl bundleIdentifier() = 0 ;
	virtual _di_NSString __cdecl bundlePath() = 0 ;
	virtual _di_NSURL __cdecl bundleURL() = 0 ;
	virtual _di_NSString __cdecl developmentLocalization() = 0 ;
	virtual _di_NSArray __cdecl executableArchitectures() = 0 ;
	virtual _di_NSString __cdecl executablePath() = 0 ;
	virtual _di_NSURL __cdecl executableURL() = 0 ;
	virtual _di_NSDictionary __cdecl infoDictionary() = 0 ;
	virtual void * __cdecl initWithPath(_di_NSString path) = 0 ;
	virtual void * __cdecl initWithURL(_di_NSURL url) = 0 ;
	virtual bool __cdecl isLoaded() = 0 ;
	virtual bool __cdecl load() = 0 ;
	virtual bool __cdecl loadAndReturnError(System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual _di_NSArray __cdecl localizations() = 0 ;
	virtual _di_NSDictionary __cdecl localizedInfoDictionary() = 0 ;
	virtual _di_NSString __cdecl localizedStringForKey(_di_NSString key, _di_NSString value, _di_NSString table) = 0 ;
	virtual void * __cdecl objectForInfoDictionaryKey(_di_NSString key) = 0 ;
	virtual _di_NSString __cdecl pathForAuxiliaryExecutable(_di_NSString executableName) = 0 ;
	virtual _di_NSString __cdecl pathForResource(_di_NSString name, _di_NSString ofType) = 0 /* overload */;
	virtual _di_NSString __cdecl pathForResource(_di_NSString name, _di_NSString ofType, _di_NSString inDirectory) = 0 /* overload */;
	virtual _di_NSString __cdecl pathForResource(_di_NSString name, _di_NSString ofType, _di_NSString inDirectory, _di_NSString forLocalization) = 0 /* overload */;
	virtual _di_NSArray __cdecl pathsForResourcesOfType(_di_NSString ext, _di_NSString inDirectory) = 0 /* overload */;
	virtual _di_NSArray __cdecl pathsForResourcesOfType(_di_NSString ext, _di_NSString inDirectory, _di_NSString forLocalization) = 0 /* overload */;
	virtual _di_NSArray __cdecl preferredLocalizations() = 0 ;
	virtual bool __cdecl preflightAndReturnError(System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual _di_NSString __cdecl privateFrameworksPath() = 0 ;
	virtual _di_NSURL __cdecl privateFrameworksURL() = 0 ;
	virtual _di_NSString __cdecl resourcePath() = 0 ;
	virtual _di_NSURL __cdecl resourceURL() = 0 ;
	virtual _di_NSString __cdecl sharedFrameworksPath() = 0 ;
	virtual _di_NSURL __cdecl sharedFrameworksURL() = 0 ;
	virtual _di_NSString __cdecl sharedSupportPath() = 0 ;
	virtual _di_NSURL __cdecl sharedSupportURL() = 0 ;
	virtual bool __cdecl unload() = 0 ;
};

class PASCALIMPLEMENTATION TNSBundle : public Macapi::Objectivec::TOCGenericImport__2<_di_NSBundleClass,_di_NSBundle>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSBundleClass,_di_NSBundle> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSBundle(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSBundleClass,_di_NSBundle>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSBundle() { }
	
};


__interface  INTERFACE_UUID("{ACF90BE9-BBE1-4514-B1D0-8BBC6486C284}") NSCacheClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{D5B63E0B-F7B8-445A-AE16-C2375948AD8C}") NSCache  : public NSObject 
{
	virtual unsigned long __cdecl countLimit() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual bool __cdecl evictsObjectsWithDiscardedContent() = 0 ;
	virtual _di_NSString __cdecl name() = 0 ;
	virtual void * __cdecl objectForKey(void * key) = 0 ;
	virtual void __cdecl removeAllObjects() = 0 ;
	virtual void __cdecl removeObjectForKey(void * key) = 0 ;
	virtual void __cdecl setCountLimit(unsigned long lim) = 0 ;
	virtual void __cdecl setDelegate(void * d) = 0 ;
	virtual void __cdecl setEvictsObjectsWithDiscardedContent(bool b) = 0 ;
	virtual void __cdecl setName(_di_NSString n) = 0 ;
	virtual void __cdecl setObject(void * obj, void * forKey) = 0 /* overload */;
	virtual void __cdecl setObject(void * obj, void * forKey, unsigned long cost) = 0 /* overload */;
	virtual void __cdecl setTotalCostLimit(unsigned long lim) = 0 ;
	virtual unsigned long __cdecl totalCostLimit() = 0 ;
};

class PASCALIMPLEMENTATION TNSCache : public Macapi::Objectivec::TOCGenericImport__2<_di_NSCacheClass,_di_NSCache>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSCacheClass,_di_NSCache> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSCache(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSCacheClass,_di_NSCache>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSCache() { }
	
};


__interface  INTERFACE_UUID("{1565D623-EB1D-464E-94D8-42C0A8905B18}") NSURLResponseClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{F5E0DFBA-CFA5-4EDC-9CD6-251968315F43}") NSURLResponse  : public NSObject 
{
	virtual _di_NSString __cdecl MIMEType() = 0 ;
	virtual _di_NSURL __cdecl URL() = 0 ;
	virtual __int64 __cdecl expectedContentLength() = 0 ;
	virtual void * __cdecl initWithURL(_di_NSURL URL, _di_NSString MIMEType, long expectedContentLength, _di_NSString textEncodingName) = 0 ;
	virtual _di_NSString __cdecl suggestedFilename() = 0 ;
	virtual _di_NSString __cdecl textEncodingName() = 0 ;
};

class PASCALIMPLEMENTATION TNSURLResponse : public Macapi::Objectivec::TOCGenericImport__2<_di_NSURLResponseClass,_di_NSURLResponse>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSURLResponseClass,_di_NSURLResponse> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSURLResponse(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSURLResponseClass,_di_NSURLResponse>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSURLResponse() { }
	
};


__interface  INTERFACE_UUID("{19865EAE-890E-479A-B968-C1A3766ECB1F}") NSHTTPCookieStorageClass  : public NSObjectClass 
{
	virtual void * __cdecl sharedHTTPCookieStorage() = 0 ;
};

__interface  INTERFACE_UUID("{7EC095E5-728A-4A89-9388-CC75ABE4FB62}") NSHTTPCookieStorage  : public NSObject 
{
	virtual unsigned long __cdecl cookieAcceptPolicy() = 0 ;
	virtual _di_NSArray __cdecl cookies() = 0 ;
	virtual _di_NSArray __cdecl cookiesForURL(_di_NSURL URL) = 0 ;
	virtual void __cdecl deleteCookie(_di_NSHTTPCookie cookie) = 0 ;
	virtual void __cdecl setCookie(_di_NSHTTPCookie cookie) = 0 ;
	virtual void __cdecl setCookieAcceptPolicy(unsigned long cookieAcceptPolicy) = 0 ;
	virtual void __cdecl setCookies(_di_NSArray cookies, _di_NSURL forURL, _di_NSURL mainDocumentURL) = 0 ;
	virtual _di_NSArray __cdecl sortedCookiesUsingDescriptors(_di_NSArray sortOrder) = 0 ;
};

class PASCALIMPLEMENTATION TNSHTTPCookieStorage : public Macapi::Objectivec::TOCGenericImport__2<_di_NSHTTPCookieStorageClass,_di_NSHTTPCookieStorage>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSHTTPCookieStorageClass,_di_NSHTTPCookieStorage> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSHTTPCookieStorage(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSHTTPCookieStorageClass,_di_NSHTTPCookieStorage>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSHTTPCookieStorage() { }
	
};


__interface  INTERFACE_UUID("{57A83353-99AD-4DE3-99F4-7A397BDFCF91}") NSURLProtocolClass  : public NSObjectClass 
{
	virtual bool __cdecl canInitWithRequest(_di_NSURLRequest request) = 0 ;
	virtual _di_NSURLRequest __cdecl canonicalRequestForRequest(_di_NSURLRequest request) = 0 ;
	virtual void * __cdecl propertyForKey(_di_NSString key, _di_NSURLRequest inRequest) = 0 ;
	virtual bool __cdecl registerClass(void * protocolClass) = 0 ;
	virtual void __cdecl removePropertyForKey(_di_NSString key, _di_NSMutableURLRequest inRequest) = 0 ;
	virtual bool __cdecl requestIsCacheEquivalent(_di_NSURLRequest a, _di_NSURLRequest toRequest) = 0 ;
	virtual void __cdecl setProperty(void * value, _di_NSString forKey, _di_NSMutableURLRequest inRequest) = 0 ;
	virtual void __cdecl unregisterClass(void * protocolClass) = 0 ;
};

__interface  INTERFACE_UUID("{08CDF707-4E62-484E-99C0-B829E283D232}") NSURLProtocol  : public NSObject 
{
	virtual _di_NSCachedURLResponse __cdecl cachedResponse() = 0 ;
	virtual void * __cdecl client() = 0 ;
	virtual void * __cdecl initWithRequest(_di_NSURLRequest request, _di_NSCachedURLResponse cachedResponse, void * client) = 0 ;
	virtual _di_NSURLRequest __cdecl request() = 0 ;
	virtual void __cdecl startLoading() = 0 ;
	virtual void __cdecl stopLoading() = 0 ;
};

class PASCALIMPLEMENTATION TNSURLProtocol : public Macapi::Objectivec::TOCGenericImport__2<_di_NSURLProtocolClass,_di_NSURLProtocol>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSURLProtocolClass,_di_NSURLProtocol> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSURLProtocol(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSURLProtocolClass,_di_NSURLProtocol>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSURLProtocol() { }
	
};


__interface  INTERFACE_UUID("{A90972DB-B51A-4E1A-98D3-33A8069A7F12}") NSHTTPCookieClass  : public NSObjectClass 
{
	virtual void * __cdecl cookieWithProperties(_di_NSDictionary properties) = 0 ;
	virtual _di_NSArray __cdecl cookiesWithResponseHeaderFields(_di_NSDictionary headerFields, _di_NSURL forURL) = 0 ;
	virtual _di_NSDictionary __cdecl requestHeaderFieldsWithCookies(_di_NSArray cookies) = 0 ;
};

__interface  INTERFACE_UUID("{0AC47694-5657-453B-8C16-567F432F7A76}") NSHTTPCookie  : public NSObject 
{
	virtual _di_NSString __cdecl comment() = 0 ;
	virtual _di_NSURL __cdecl commentURL() = 0 ;
	virtual _di_NSString __cdecl domain() = 0 ;
	virtual _di_NSDate __cdecl expiresDate() = 0 ;
	virtual void * __cdecl initWithProperties(_di_NSDictionary properties) = 0 ;
	virtual bool __cdecl isHTTPOnly() = 0 ;
	virtual bool __cdecl isSecure() = 0 ;
	virtual bool __cdecl isSessionOnly() = 0 ;
	virtual _di_NSString __cdecl name() = 0 ;
	virtual _di_NSString __cdecl path() = 0 ;
	virtual _di_NSArray __cdecl portList() = 0 ;
	virtual _di_NSDictionary __cdecl properties() = 0 ;
	virtual _di_NSString __cdecl value() = 0 ;
	virtual unsigned long __cdecl version() = 0 ;
};

class PASCALIMPLEMENTATION TNSHTTPCookie : public Macapi::Objectivec::TOCGenericImport__2<_di_NSHTTPCookieClass,_di_NSHTTPCookie>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSHTTPCookieClass,_di_NSHTTPCookie> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSHTTPCookie(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSHTTPCookieClass,_di_NSHTTPCookie>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSHTTPCookie() { }
	
};


__interface  INTERFACE_UUID("{B5F18BD1-1847-485B-8372-BDD46C9B5C91}") NSFileWrapperClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{4B43D5A5-2039-47EA-8D3A-4D7FA9E8ACBD}") NSFileWrapper  : public NSObject 
{
	virtual _di_NSString __cdecl addFileWrapper(_di_NSFileWrapper child) = 0 ;
	virtual _di_NSString __cdecl addRegularFileWithContents(_di_NSData data, _di_NSString preferredFilename) = 0 ;
	virtual _di_NSDictionary __cdecl fileAttributes() = 0 ;
	virtual _di_NSDictionary __cdecl fileWrappers() = 0 ;
	virtual _di_NSString __cdecl filename() = 0 ;
	virtual void * __cdecl initDirectoryWithFileWrappers(_di_NSDictionary childrenByPreferredName) = 0 ;
	virtual void * __cdecl initRegularFileWithContents(_di_NSData contents) = 0 ;
	virtual void * __cdecl initSymbolicLinkWithDestinationURL(_di_NSURL url) = 0 ;
	virtual void * __cdecl initWithSerializedRepresentation(_di_NSData serializeRepresentation) = 0 ;
	virtual void * __cdecl initWithURL(_di_NSURL url, unsigned long options, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual bool __cdecl isDirectory() = 0 ;
	virtual bool __cdecl isRegularFile() = 0 ;
	virtual bool __cdecl isSymbolicLink() = 0 ;
	virtual _di_NSString __cdecl keyForFileWrapper(_di_NSFileWrapper child) = 0 ;
	virtual bool __cdecl matchesContentsOfURL(_di_NSURL url) = 0 ;
	virtual _di_NSString __cdecl preferredFilename() = 0 ;
	virtual bool __cdecl readFromURL(_di_NSURL url, unsigned long options, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual _di_NSData __cdecl regularFileContents() = 0 ;
	virtual void __cdecl removeFileWrapper(_di_NSFileWrapper child) = 0 ;
	virtual _di_NSData __cdecl serializedRepresentation() = 0 ;
	virtual void __cdecl setFileAttributes(_di_NSDictionary fileAttributes) = 0 ;
	virtual void __cdecl setFilename(_di_NSString fileName) = 0 ;
	virtual void __cdecl setPreferredFilename(_di_NSString fileName) = 0 ;
	virtual _di_NSURL __cdecl symbolicLinkDestinationURL() = 0 ;
	virtual bool __cdecl writeToURL(_di_NSURL url, unsigned long options, _di_NSURL originalContentsURL, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
};

class PASCALIMPLEMENTATION TNSFileWrapper : public Macapi::Objectivec::TOCGenericImport__2<_di_NSFileWrapperClass,_di_NSFileWrapper>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSFileWrapperClass,_di_NSFileWrapper> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSFileWrapper(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSFileWrapperClass,_di_NSFileWrapper>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSFileWrapper() { }
	
};


__interface  INTERFACE_UUID("{9CF8F6A6-4B40-474D-BF8B-EB86169872AF}") NSFormatterClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{4284B953-9A8D-411D-8B6C-5D4A980790D0}") NSFormatter  : public NSObject 
{
	virtual _di_NSAttributedString __cdecl attributedStringForObjectValue(void * obj, _di_NSDictionary withDefaultAttributes) = 0 ;
	virtual _di_NSString __cdecl editingStringForObjectValue(void * obj) = 0 ;
	virtual bool __cdecl getObjectValue(void * obj, _di_NSString forString, System::PPointer errorDescription = (System::PPointer)(0x0)) = 0 ;
	virtual bool __cdecl isPartialStringValid(_di_NSString partialString, _di_NSString newEditingString, _di_NSString errorDescription) = 0 /* overload */;
	virtual bool __cdecl isPartialStringValid(_di_NSString partialStringPtr, PNSRange proposedSelectedRange, _di_NSString originalString, NSRange originalSelectedRange, _di_NSString errorDescription) = 0 /* overload */;
	virtual _di_NSString __cdecl stringForObjectValue(void * obj) = 0 ;
};

class PASCALIMPLEMENTATION TNSFormatter : public Macapi::Objectivec::TOCGenericImport__2<_di_NSFormatterClass,_di_NSFormatter>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSFormatterClass,_di_NSFormatter> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSFormatter(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSFormatterClass,_di_NSFormatter>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSFormatter() { }
	
};


__interface  INTERFACE_UUID("{EC179FA9-9693-4174-BA51-D16905365E9A}") NSInvocationClass  : public NSObjectClass 
{
	virtual void * __cdecl invocationWithMethodSignature(_di_NSMethodSignature sig) = 0 ;
};

__interface  INTERFACE_UUID("{BA98E2B3-94E8-4406-8DAE-4FD4272FA386}") NSInvocation  : public NSObject 
{
	virtual bool __cdecl argumentsRetained() = 0 ;
	virtual void __cdecl getArgument(void * argumentLocation, long atIndex) = 0 ;
	virtual void __cdecl getReturnValue(void * retLoc) = 0 ;
	virtual void __cdecl invoke() = 0 ;
	virtual void __cdecl invokeWithTarget(void * target) = 0 ;
	virtual _di_NSMethodSignature __cdecl methodSignature() = 0 ;
	virtual void __cdecl retainArguments() = 0 ;
	virtual void * __cdecl selector() = 0 ;
	virtual void __cdecl setArgument(void * argumentLocation, long atIndex) = 0 ;
	virtual void __cdecl setReturnValue(void * retLoc) = 0 ;
	virtual void __cdecl setSelector(void * selector) = 0 ;
	virtual void __cdecl setTarget(void * target) = 0 ;
	virtual void * __cdecl target() = 0 ;
};

class PASCALIMPLEMENTATION TNSInvocation : public Macapi::Objectivec::TOCGenericImport__2<_di_NSInvocationClass,_di_NSInvocation>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSInvocationClass,_di_NSInvocation> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSInvocation(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSInvocationClass,_di_NSInvocation>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSInvocation() { }
	
};


__interface  INTERFACE_UUID("{BDB08B72-1FF0-49F8-B634-9392631D0BAC}") NSURLCredentialStorageClass  : public NSObjectClass 
{
	virtual void * __cdecl sharedCredentialStorage() = 0 ;
};

__interface  INTERFACE_UUID("{A226D276-9EE2-483F-82C8-28B58AC1607C}") NSURLCredentialStorage  : public NSObject 
{
	virtual _di_NSDictionary __cdecl allCredentials() = 0 ;
	virtual _di_NSDictionary __cdecl credentialsForProtectionSpace(_di_NSURLProtectionSpace space) = 0 ;
	virtual _di_NSURLCredential __cdecl defaultCredentialForProtectionSpace(_di_NSURLProtectionSpace space) = 0 ;
	virtual void __cdecl removeCredential(_di_NSURLCredential credential, _di_NSURLProtectionSpace forProtectionSpace) = 0 ;
	virtual void __cdecl setCredential(_di_NSURLCredential credential, _di_NSURLProtectionSpace forProtectionSpace) = 0 ;
	virtual void __cdecl setDefaultCredential(_di_NSURLCredential credential, _di_NSURLProtectionSpace forProtectionSpace) = 0 ;
};

class PASCALIMPLEMENTATION TNSURLCredentialStorage : public Macapi::Objectivec::TOCGenericImport__2<_di_NSURLCredentialStorageClass,_di_NSURLCredentialStorage>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSURLCredentialStorageClass,_di_NSURLCredentialStorage> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSURLCredentialStorage(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSURLCredentialStorageClass,_di_NSURLCredentialStorage>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSURLCredentialStorage() { }
	
};


__interface  INTERFACE_UUID("{5EC3B966-8944-441D-855C-8288207EEDA8}") NSURLProtectionSpaceClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{3B64DE60-2FE6-4131-B85B-623B0DE8A745}") NSURLProtectionSpace  : public NSObject 
{
	virtual _di_NSString __cdecl authenticationMethod() = 0 ;
	virtual _di_NSArray __cdecl distinguishedNames() = 0 ;
	virtual _di_NSString __cdecl host() = 0 ;
	virtual void * __cdecl initWithHost(_di_NSString host, long port, _di_NSString protocol, _di_NSString realm, _di_NSString authenticationMethod) = 0 ;
	virtual bool __cdecl isProxy() = 0 ;
	virtual long __cdecl port() = 0 ;
	virtual _di_NSString __cdecl protocol() = 0 ;
	virtual _di_NSString __cdecl proxyType() = 0 ;
	virtual _di_NSString __cdecl realm() = 0 ;
	virtual bool __cdecl receivesCredentialSecurely() = 0 ;
	virtual void * __cdecl serverTrust() = 0 ;
};

class PASCALIMPLEMENTATION TNSURLProtectionSpace : public Macapi::Objectivec::TOCGenericImport__2<_di_NSURLProtectionSpaceClass,_di_NSURLProtectionSpace>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSURLProtectionSpaceClass,_di_NSURLProtectionSpace> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSURLProtectionSpace(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSURLProtectionSpaceClass,_di_NSURLProtectionSpace>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSURLProtectionSpace() { }
	
};


__interface  INTERFACE_UUID("{EB1F22E7-9955-4266-91E7-66ED41BE8B09}") NSIndexPathClass  : public NSObjectClass 
{
	virtual void * __cdecl indexPathWithIndex(unsigned long index) = 0 ;
	virtual void * __cdecl indexPathWithIndexes(unsigned long indexes, unsigned long length) = 0 ;
	virtual void * __cdecl indexPathForRow(long row, long inSection) = 0 ;
	virtual void * __cdecl indexPathForItem(long item, long inSection) = 0 ;
};

__interface  INTERFACE_UUID("{CF5A1A30-CA1B-4791-A6D2-20F2155883CA}") NSIndexPath  : public NSObject 
{
	virtual long __cdecl compare(_di_NSIndexPath otherObject) = 0 ;
	virtual void __cdecl getIndexes(Iosapi::Cocoatypes::PNSUInteger indexes) = 0 ;
	virtual unsigned long __cdecl indexAtPosition(unsigned long position) = 0 ;
	virtual _di_NSIndexPath __cdecl indexPathByAddingIndex(unsigned long index) = 0 ;
	virtual _di_NSIndexPath __cdecl indexPathByRemovingLastIndex() = 0 ;
	virtual _di_NSIndexPath __cdecl indexPathForRow(long row, long inSection) = 0 ;
	virtual _di_NSIndexPath __cdecl indexPathForItem(long item, long inSection) = 0 ;
	virtual void * __cdecl initWithIndex(unsigned long index) = 0 ;
	virtual void * __cdecl initWithIndexes(Iosapi::Cocoatypes::PNSUInteger indexes, unsigned long length) = 0 ;
	virtual unsigned long __cdecl length() = 0 ;
	virtual long __cdecl row() = 0 ;
	virtual long __cdecl section() = 0 ;
};

class PASCALIMPLEMENTATION TNSIndexPath : public Macapi::Objectivec::TOCGenericImport__2<_di_NSIndexPathClass,_di_NSIndexPath>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSIndexPathClass,_di_NSIndexPath> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSIndexPath(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSIndexPathClass,_di_NSIndexPath>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSIndexPath() { }
	
};


__interface  INTERFACE_UUID("{B2F478A1-098B-4B54-8C14-5DAC46536411}") NSIndexSetClass  : public NSObjectClass 
{
	virtual void * __cdecl indexSet() = 0 ;
	virtual void * __cdecl indexSetWithIndex(unsigned long value) = 0 ;
	virtual void * __cdecl indexSetWithIndexesInRange(NSRange range) = 0 ;
};

__interface  INTERFACE_UUID("{FDAC7E88-723F-4003-B83F-8910145956A4}") NSIndexSet  : public NSObject 
{
	virtual bool __cdecl containsIndex(unsigned long value) = 0 ;
	virtual bool __cdecl containsIndexes(_di_NSIndexSet indexSet) = 0 ;
	virtual bool __cdecl containsIndexesInRange(NSRange range) = 0 ;
	virtual unsigned long __cdecl count() = 0 ;
	virtual unsigned long __cdecl countOfIndexesInRange(NSRange range) = 0 ;
	virtual unsigned long __cdecl firstIndex() = 0 ;
	virtual unsigned long __cdecl getIndexes(Iosapi::Cocoatypes::PNSUInteger indexBuffer, unsigned long maxCount, PNSRange inIndexRange) = 0 ;
	virtual unsigned long __cdecl indexGreaterThanIndex(unsigned long value) = 0 ;
	virtual unsigned long __cdecl indexGreaterThanOrEqualToIndex(unsigned long value) = 0 ;
	virtual unsigned long __cdecl indexLessThanIndex(unsigned long value) = 0 ;
	virtual unsigned long __cdecl indexLessThanOrEqualToIndex(unsigned long value) = 0 ;
	HIDESBASE virtual void * __cdecl init() = 0 ;
	virtual void * __cdecl initWithIndex(unsigned long value) = 0 ;
	virtual void * __cdecl initWithIndexSet(_di_NSIndexSet indexSet) = 0 ;
	virtual void * __cdecl initWithIndexesInRange(NSRange range) = 0 ;
	virtual bool __cdecl intersectsIndexesInRange(NSRange range) = 0 ;
	virtual bool __cdecl isEqualToIndexSet(_di_NSIndexSet indexSet) = 0 ;
	virtual unsigned long __cdecl lastIndex() = 0 ;
};

class PASCALIMPLEMENTATION TNSIndexSet : public Macapi::Objectivec::TOCGenericImport__2<_di_NSIndexSetClass,_di_NSIndexSet>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSIndexSetClass,_di_NSIndexSet> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSIndexSet(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSIndexSetClass,_di_NSIndexSet>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSIndexSet() { }
	
};


__interface  INTERFACE_UUID("{ABE6514E-360B-49BF-AC81-A7BB8B66E20D}") NSFileVersionClass  : public NSObjectClass 
{
	virtual void * __cdecl addVersionOfItemAtURL(_di_NSURL url, _di_NSURL withContentsOfURL, unsigned long options, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual void * __cdecl currentVersionOfItemAtURL(_di_NSURL url) = 0 ;
	virtual _di_NSArray __cdecl otherVersionsOfItemAtURL(_di_NSURL url) = 0 ;
	virtual bool __cdecl removeOtherVersionsOfItemAtURL(_di_NSURL url, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual _di_NSURL __cdecl temporaryDirectoryURLForNewVersionOfItemAtURL(_di_NSURL url) = 0 ;
	virtual _di_NSArray __cdecl unresolvedConflictVersionsOfItemAtURL(_di_NSURL url) = 0 ;
	virtual void * __cdecl versionOfItemAtURL(_di_NSURL url, void * forPersistentIdentifier) = 0 ;
};

__interface  INTERFACE_UUID("{47278444-EC20-48C2-B775-4540BA872242}") NSFileVersion  : public NSObject 
{
	virtual _di_NSURL __cdecl URL() = 0 ;
	virtual bool __cdecl isConflict() = 0 ;
	virtual bool __cdecl isDiscardable() = 0 ;
	virtual bool __cdecl isResolved() = 0 ;
	virtual _di_NSString __cdecl localizedName() = 0 ;
	virtual _di_NSString __cdecl localizedNameOfSavingComputer() = 0 ;
	virtual _di_NSDate __cdecl modificationDate() = 0 ;
	virtual void * __cdecl persistentIdentifier() = 0 ;
	virtual bool __cdecl removeAndReturnError(System::PPointer outError = (System::PPointer)(0x0)) = 0 ;
	virtual _di_NSURL __cdecl replaceItemAtURL(_di_NSURL url, unsigned long options, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual void __cdecl setDiscardable(bool discardable) = 0 ;
	virtual void __cdecl setResolved(bool resolved) = 0 ;
};

class PASCALIMPLEMENTATION TNSFileVersion : public Macapi::Objectivec::TOCGenericImport__2<_di_NSFileVersionClass,_di_NSFileVersion>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSFileVersionClass,_di_NSFileVersion> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSFileVersion(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSFileVersionClass,_di_NSFileVersion>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSFileVersion() { }
	
};


__interface  INTERFACE_UUID("{CA84BD67-2FEB-4589-B36E-082676B41F4B}") NSEnumeratorClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{25DFC98A-5BCC-41AC-AB84-1801E17E838D}") NSEnumerator  : public NSObject 
{
	virtual _di_NSArray __cdecl allObjects() = 0 ;
	virtual void * __cdecl nextObject() = 0 ;
};

class PASCALIMPLEMENTATION TNSEnumerator : public Macapi::Objectivec::TOCGenericImport__2<_di_NSEnumeratorClass,_di_NSEnumerator>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSEnumeratorClass,_di_NSEnumerator> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSEnumerator(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSEnumeratorClass,_di_NSEnumerator>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSEnumerator() { }
	
};


__interface  INTERFACE_UUID("{97B5F2E2-DD78-4874-9EF6-D2BD111587E1}") NSErrorClass  : public NSObjectClass 
{
	virtual void * __cdecl errorWithDomain(_di_NSString domain, long code, _di_NSDictionary userInfo) = 0 ;
};

__interface  INTERFACE_UUID("{8E8F832A-5F75-4F65-A18B-5A8E2F49A867}") NSError  : public NSObject 
{
	virtual long __cdecl code() = 0 ;
	virtual _di_NSString __cdecl domain() = 0 ;
	virtual _di_NSString __cdecl helpAnchor() = 0 ;
	virtual void * __cdecl initWithDomain(_di_NSString domain, long code, _di_NSDictionary userInfo) = 0 ;
	virtual _di_NSString __cdecl localizedDescription() = 0 ;
	virtual _di_NSString __cdecl localizedFailureReason() = 0 ;
	virtual _di_NSArray __cdecl localizedRecoveryOptions() = 0 ;
	virtual _di_NSString __cdecl localizedRecoverySuggestion() = 0 ;
	virtual void * __cdecl recoveryAttempter() = 0 ;
	virtual _di_NSDictionary __cdecl userInfo() = 0 ;
};

class PASCALIMPLEMENTATION TNSError : public Macapi::Objectivec::TOCGenericImport__2<_di_NSErrorClass,_di_NSError>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSErrorClass,_di_NSError> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSError(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSErrorClass,_di_NSError>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSError() { }
	
};


typedef _di_NSError *PNSError;

__interface  INTERFACE_UUID("{A93A4D14-529E-41F0-86EC-B570715512BB}") NSURLRequestClass  : public NSObjectClass 
{
	virtual void * __cdecl requestWithURL(_di_NSURL URL) = 0 /* overload */;
	virtual void * __cdecl requestWithURL(_di_NSURL URL, unsigned long cachePolicy, double timeoutInterval) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{83575778-CDDD-41D2-A02D-B12358709400}") NSURLRequest  : public NSObject 
{
	virtual _di_NSData __cdecl HTTPBody() = 0 ;
	virtual _di_NSInputStream __cdecl HTTPBodyStream() = 0 ;
	virtual _di_NSString __cdecl HTTPMethod() = 0 ;
	virtual bool __cdecl HTTPShouldHandleCookies() = 0 ;
	virtual bool __cdecl HTTPShouldUsePipelining() = 0 ;
	virtual _di_NSURL __cdecl URL() = 0 ;
	virtual _di_NSDictionary __cdecl allHTTPHeaderFields() = 0 ;
	virtual unsigned long __cdecl cachePolicy() = 0 ;
	virtual void * __cdecl initWithURL(_di_NSURL URL) = 0 /* overload */;
	virtual void * __cdecl initWithURL(_di_NSURL URL, unsigned long cachePolicy, double timeoutInterval) = 0 /* overload */;
	virtual _di_NSURL __cdecl mainDocumentURL() = 0 ;
	virtual unsigned long __cdecl networkServiceType() = 0 ;
	virtual double __cdecl timeoutInterval() = 0 ;
	virtual _di_NSString __cdecl valueForHTTPHeaderField(_di_NSString field) = 0 ;
	virtual _di_NSMutableURLRequest __cdecl mutableCopy() = 0 ;
};

class PASCALIMPLEMENTATION TNSURLRequest : public Macapi::Objectivec::TOCGenericImport__2<_di_NSURLRequestClass,_di_NSURLRequest>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSURLRequestClass,_di_NSURLRequest> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSURLRequest(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSURLRequestClass,_di_NSURLRequest>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSURLRequest() { }
	
};


__interface  INTERFACE_UUID("{51007C90-91B2-407C-ADB5-C0645C103D7C}") NSDecimalNumberHandlerClass  : public NSObjectClass 
{
	virtual void * __cdecl decimalNumberHandlerWithRoundingMode(unsigned long roundingMode, short scale, bool raiseOnExactness, bool raiseOnOverflow, bool raiseOnUnderflow, bool raiseOnDivideByZero) = 0 ;
	virtual void * __cdecl defaultDecimalNumberHandler() = 0 ;
};

__interface  INTERFACE_UUID("{E2924457-A750-4174-A29B-1F9E685D06D3}") NSDecimalNumberHandler  : public NSObject 
{
	virtual void * __cdecl initWithRoundingMode(unsigned long roundingMode, short scale, bool raiseOnExactness, bool raiseOnOverflow, bool raiseOnUnderflow, bool raiseOnDivideByZero) = 0 ;
};

class PASCALIMPLEMENTATION TNSDecimalNumberHandler : public Macapi::Objectivec::TOCGenericImport__2<_di_NSDecimalNumberHandlerClass,_di_NSDecimalNumberHandler>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSDecimalNumberHandlerClass,_di_NSDecimalNumberHandler> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSDecimalNumberHandler(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSDecimalNumberHandlerClass,_di_NSDecimalNumberHandler>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSDecimalNumberHandler() { }
	
};


__interface  INTERFACE_UUID("{5B8960AD-1E66-4A78-AAF5-208CEB603583}") NSDictionaryClass  : public NSObjectClass 
{
	virtual void * __cdecl dictionary() = 0 ;
	virtual void * __cdecl dictionaryWithContentsOfFile(_di_NSString path) = 0 ;
	virtual void * __cdecl dictionaryWithContentsOfURL(_di_NSURL url) = 0 ;
	virtual void * __cdecl dictionaryWithDictionary(_di_NSDictionary dict) = 0 ;
	virtual void * __cdecl dictionaryWithObject(void * object_, void * forKey) = 0 ;
	virtual void * __cdecl dictionaryWithObjects(_di_NSArray objects, _di_NSArray forKeys) = 0 /* overload */;
	virtual void * __cdecl dictionaryWithObjects(void * objects, void * forKeys, unsigned long count) = 0 /* overload */;
	virtual void * __cdecl dictionaryWithObjectsAndKeys(void * firstObject) = 0 ;
};

__interface  INTERFACE_UUID("{9F4A8304-A061-4C6E-8A1C-62FFD42B76AE}") NSDictionary  : public NSObject 
{
	virtual _di_NSArray __cdecl allKeys() = 0 ;
	virtual _di_NSArray __cdecl allKeysForObject(void * anObject) = 0 ;
	virtual _di_NSArray __cdecl allValues() = 0 ;
	virtual unsigned long __cdecl count() = 0 ;
	virtual _di_NSString __cdecl description() = 0 ;
	virtual _di_NSString __cdecl descriptionInStringsFileFormat() = 0 ;
	virtual _di_NSString __cdecl descriptionWithLocale(void * locale) = 0 /* overload */;
	virtual _di_NSString __cdecl descriptionWithLocale(void * locale, unsigned long indent) = 0 /* overload */;
	virtual _di_NSDate __cdecl fileCreationDate() = 0 ;
	virtual bool __cdecl fileExtensionHidden() = 0 ;
	virtual _di_NSNumber __cdecl fileGroupOwnerAccountID() = 0 ;
	virtual _di_NSString __cdecl fileGroupOwnerAccountName() = 0 ;
	virtual unsigned __cdecl fileHFSCreatorCode() = 0 ;
	virtual unsigned __cdecl fileHFSTypeCode() = 0 ;
	virtual bool __cdecl fileIsAppendOnly() = 0 ;
	virtual bool __cdecl fileIsImmutable() = 0 ;
	virtual _di_NSDate __cdecl fileModificationDate() = 0 ;
	virtual _di_NSNumber __cdecl fileOwnerAccountID() = 0 ;
	virtual _di_NSString __cdecl fileOwnerAccountName() = 0 ;
	virtual unsigned long __cdecl filePosixPermissions() = 0 ;
	virtual unsigned __int64 __cdecl fileSize() = 0 ;
	virtual unsigned long __cdecl fileSystemFileNumber() = 0 ;
	virtual long __cdecl fileSystemNumber() = 0 ;
	virtual _di_NSString __cdecl fileType() = 0 ;
	virtual void __cdecl getObjects(void * objects, void * andKeys) = 0 ;
	virtual void * __cdecl initWithContentsOfFile(_di_NSString path) = 0 ;
	virtual void * __cdecl initWithContentsOfURL(_di_NSURL url) = 0 ;
	virtual void * __cdecl initWithDictionary(_di_NSDictionary otherDictionary) = 0 /* overload */;
	virtual void * __cdecl initWithDictionary(_di_NSDictionary otherDictionary, bool copyItems) = 0 /* overload */;
	virtual void * __cdecl initWithObjects(_di_NSArray objects, _di_NSArray forKeys) = 0 /* overload */;
	virtual void * __cdecl initWithObjects(void * objects, void * forKeys, unsigned long count) = 0 /* overload */;
	virtual void * __cdecl initWithObjectsAndKeys(void * firstObject) = 0 ;
	virtual bool __cdecl isEqualToDictionary(_di_NSDictionary otherDictionary) = 0 ;
	virtual _di_NSEnumerator __cdecl keyEnumerator() = 0 ;
	virtual _di_NSArray __cdecl keysSortedByValueUsingSelector(void * comparator) = 0 ;
	virtual _di_NSEnumerator __cdecl objectEnumerator() = 0 ;
	virtual void * __cdecl objectForKey(void * aKey) = 0 ;
	virtual _di_NSArray __cdecl objectsForKeys(_di_NSArray keys, void * notFoundMarker) = 0 ;
	HIDESBASE virtual void * __cdecl valueForKey(_di_NSString key) = 0 ;
	virtual bool __cdecl writeToFile(_di_NSString path, bool atomically) = 0 ;
	virtual bool __cdecl writeToURL(_di_NSURL url, bool atomically) = 0 ;
};

class PASCALIMPLEMENTATION TNSDictionary : public Macapi::Objectivec::TOCGenericImport__2<_di_NSDictionaryClass,_di_NSDictionary>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSDictionaryClass,_di_NSDictionary> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSDictionary(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSDictionaryClass,_di_NSDictionary>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSDictionary() { }
	
};


__interface  INTERFACE_UUID("{F271DE7C-9A1A-4AAE-A2C1-3E21D318DCD1}") NSFileHandleClass  : public NSObjectClass 
{
	virtual void * __cdecl fileHandleForReadingAtPath(_di_NSString path) = 0 ;
	virtual void * __cdecl fileHandleForReadingFromURL(_di_NSURL url, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual void * __cdecl fileHandleForUpdatingAtPath(_di_NSString path) = 0 ;
	virtual void * __cdecl fileHandleForUpdatingURL(_di_NSURL url, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual void * __cdecl fileHandleForWritingAtPath(_di_NSString path) = 0 ;
	virtual void * __cdecl fileHandleForWritingToURL(_di_NSURL url, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual void * __cdecl fileHandleWithNullDevice() = 0 ;
	virtual void * __cdecl fileHandleWithStandardError() = 0 ;
	virtual void * __cdecl fileHandleWithStandardInput() = 0 ;
	virtual void * __cdecl fileHandleWithStandardOutput() = 0 ;
};

__interface  INTERFACE_UUID("{742193ED-CEAD-4D44-B686-12EE2EB17BAE}") NSFileHandle  : public NSObject 
{
	virtual void __cdecl acceptConnectionInBackgroundAndNotify() = 0 ;
	virtual void __cdecl acceptConnectionInBackgroundAndNotifyForModes(_di_NSArray modes) = 0 ;
	virtual _di_NSData __cdecl availableData() = 0 ;
	virtual void __cdecl closeFile() = 0 ;
	virtual int __cdecl fileDescriptor() = 0 ;
	virtual void * __cdecl initWithFileDescriptor(int fd) = 0 /* overload */;
	virtual void * __cdecl initWithFileDescriptor(int fd, bool closeOnDealloc) = 0 /* overload */;
	virtual unsigned __int64 __cdecl offsetInFile() = 0 ;
	virtual _di_NSData __cdecl readDataOfLength(unsigned long length) = 0 ;
	virtual _di_NSData __cdecl readDataToEndOfFile() = 0 ;
	virtual void __cdecl readInBackgroundAndNotify() = 0 ;
	virtual void __cdecl readInBackgroundAndNotifyForModes(_di_NSArray modes) = 0 ;
	virtual void __cdecl readToEndOfFileInBackgroundAndNotify() = 0 ;
	virtual void __cdecl readToEndOfFileInBackgroundAndNotifyForModes(_di_NSArray modes) = 0 ;
	virtual unsigned __int64 __cdecl seekToEndOfFile() = 0 ;
	virtual void __cdecl seekToFileOffset(unsigned __int64 offset) = 0 ;
	virtual void __cdecl synchronizeFile() = 0 ;
	virtual void __cdecl truncateFileAtOffset(unsigned __int64 offset) = 0 ;
	virtual void __cdecl waitForDataInBackgroundAndNotify() = 0 ;
	virtual void __cdecl waitForDataInBackgroundAndNotifyForModes(_di_NSArray modes) = 0 ;
	virtual void __cdecl writeData(_di_NSData data) = 0 ;
};

class PASCALIMPLEMENTATION TNSFileHandle : public Macapi::Objectivec::TOCGenericImport__2<_di_NSFileHandleClass,_di_NSFileHandle>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSFileHandleClass,_di_NSFileHandle> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSFileHandle(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSFileHandleClass,_di_NSFileHandle>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSFileHandle() { }
	
};


__interface  INTERFACE_UUID("{007F0D12-E722-4DD0-8C0D-F609187C4E6F}") NSFileManagerClass  : public NSObjectClass 
{
	virtual void * __cdecl defaultManager() = 0 ;
};

__interface  INTERFACE_UUID("{BB6643FC-20D8-41EF-881C-15326FD03C77}") NSFileManager  : public NSObject 
{
	virtual _di_NSURL __cdecl URLForDirectory(unsigned long directory, unsigned long inDomain, _di_NSURL appropriateForURL, bool create, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual _di_NSURL __cdecl URLForPublishingUbiquitousItemAtURL(_di_NSURL url, _di_NSDate expirationDate, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual _di_NSURL __cdecl URLForUbiquityContainerIdentifier(_di_NSString containerIdentifier) = 0 ;
	virtual _di_NSArray __cdecl URLsForDirectory(unsigned long directory, unsigned long inDomains) = 0 ;
	virtual _di_NSDictionary __cdecl attributesOfFileSystemForPath(_di_NSString path, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual _di_NSDictionary __cdecl attributesOfItemAtPath(_di_NSString path, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual bool __cdecl changeCurrentDirectoryPath(_di_NSString path) = 0 ;
	virtual bool __cdecl changeFileAttributes(_di_NSDictionary attributes, _di_NSString atPath) = 0 ;
	virtual _di_NSArray __cdecl componentsToDisplayForPath(_di_NSString path) = 0 ;
	virtual _di_NSData __cdecl contentsAtPath(_di_NSString path) = 0 ;
	virtual bool __cdecl contentsEqualAtPath(_di_NSString path1, _di_NSString andPath) = 0 ;
	virtual _di_NSArray __cdecl contentsOfDirectoryAtPath(_di_NSString path, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual _di_NSArray __cdecl contentsOfDirectoryAtURL(_di_NSURL url, _di_NSArray includingPropertiesForKeys, unsigned long options, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual bool __cdecl copyItemAtPath(_di_NSString srcPath, _di_NSString toPath, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual bool __cdecl copyItemAtURL(_di_NSURL srcURL, _di_NSURL toURL, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual bool __cdecl createDirectoryAtPath(_di_NSString path, _di_NSDictionary attributes) = 0 /* overload */;
	virtual bool __cdecl createDirectoryAtPath(_di_NSString path, bool withIntermediateDirectories, _di_NSDictionary attributes, System::PPointer error = (System::PPointer)(0x0)) = 0 /* overload */;
	virtual bool __cdecl createDirectoryAtURL(_di_NSURL url, bool withIntermediateDirectories, _di_NSDictionary attributes, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual bool __cdecl createFileAtPath(_di_NSString path, _di_NSData contents, _di_NSDictionary attributes) = 0 ;
	virtual bool __cdecl createSymbolicLinkAtPath(_di_NSString path, _di_NSString pathContent) = 0 /* overload */;
	virtual bool __cdecl createSymbolicLinkAtPath(_di_NSString path, _di_NSString withDestinationPath, System::PPointer error = (System::PPointer)(0x0)) = 0 /* overload */;
	virtual bool __cdecl createSymbolicLinkAtURL(_di_NSURL url, _di_NSURL withDestinationURL, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual _di_NSString __cdecl currentDirectoryPath() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual _di_NSString __cdecl destinationOfSymbolicLinkAtPath(_di_NSString path, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual _di_NSArray __cdecl directoryContentsAtPath(_di_NSString path) = 0 ;
	virtual _di_NSString __cdecl displayNameAtPath(_di_NSString path) = 0 ;
	virtual _di_NSDirectoryEnumerator __cdecl enumeratorAtPath(_di_NSString path) = 0 ;
	virtual bool __cdecl evictUbiquitousItemAtURL(_di_NSURL url, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual _di_NSDictionary __cdecl fileAttributesAtPath(_di_NSString path, bool traverseLink) = 0 ;
	virtual bool __cdecl fileExistsAtPath(_di_NSString path) = 0 /* overload */;
	virtual bool __cdecl fileExistsAtPath(_di_NSString path, System::PBoolean isDirectory) = 0 /* overload */;
	virtual _di_NSDictionary __cdecl fileSystemAttributesAtPath(_di_NSString path) = 0 ;
	virtual char * __cdecl fileSystemRepresentationWithPath(_di_NSString path) = 0 ;
	virtual bool __cdecl isDeletableFileAtPath(_di_NSString path) = 0 ;
	virtual bool __cdecl isExecutableFileAtPath(_di_NSString path) = 0 ;
	virtual bool __cdecl isReadableFileAtPath(_di_NSString path) = 0 ;
	virtual bool __cdecl isUbiquitousItemAtURL(_di_NSURL url) = 0 ;
	virtual bool __cdecl isWritableFileAtPath(_di_NSString path) = 0 ;
	virtual bool __cdecl linkItemAtPath(_di_NSString srcPath, _di_NSString toPath, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual bool __cdecl linkItemAtURL(_di_NSURL srcURL, _di_NSURL toURL, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual _di_NSArray __cdecl mountedVolumeURLsIncludingResourceValuesForKeys(_di_NSArray propertyKeys, unsigned long options) = 0 ;
	virtual bool __cdecl moveItemAtPath(_di_NSString srcPath, _di_NSString toPath, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual bool __cdecl moveItemAtURL(_di_NSURL srcURL, _di_NSURL toURL, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual _di_NSString __cdecl pathContentOfSymbolicLinkAtPath(_di_NSString path) = 0 ;
	virtual bool __cdecl removeItemAtPath(_di_NSString path, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual bool __cdecl removeItemAtURL(_di_NSURL URL, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual bool __cdecl replaceItemAtURL(_di_NSURL originalItemURL, _di_NSURL withItemAtURL, _di_NSString backupItemName, unsigned long options, _di_NSURL resultingItemURL, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual bool __cdecl setAttributes(_di_NSDictionary attributes, _di_NSString ofItemAtPath, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual bool __cdecl setUbiquitous(bool flag, _di_NSURL itemAtURL, _di_NSURL destinationURL, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual bool __cdecl startDownloadingUbiquitousItemAtURL(_di_NSURL url, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual _di_NSString __cdecl stringWithFileSystemRepresentation(char * str, unsigned long length) = 0 ;
	virtual _di_NSArray __cdecl subpathsAtPath(_di_NSString path) = 0 ;
	virtual _di_NSArray __cdecl subpathsOfDirectoryAtPath(_di_NSString path, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
};

class PASCALIMPLEMENTATION TNSFileManager : public Macapi::Objectivec::TOCGenericImport__2<_di_NSFileManagerClass,_di_NSFileManager>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSFileManagerClass,_di_NSFileManager> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSFileManager(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSFileManagerClass,_di_NSFileManager>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSFileManager() { }
	
};


__interface  INTERFACE_UUID("{92A34809-475A-44F2-AD48-3DBC94E45C87}") NSFileCoordinatorClass  : public NSObjectClass 
{
	virtual void __cdecl addFilePresenter(void * filePresenter) = 0 ;
	virtual _di_NSArray __cdecl filePresenters() = 0 ;
	virtual void __cdecl removeFilePresenter(void * filePresenter) = 0 ;
};

__interface  INTERFACE_UUID("{6657485B-2F55-49FF-AC00-1CF5C79AA429}") NSFileCoordinator  : public NSObject 
{
	virtual void __cdecl cancel() = 0 ;
	virtual void * __cdecl initWithFilePresenter(void * filePresenterOrNil) = 0 ;
	virtual void __cdecl itemAtURL(_di_NSURL oldURL, _di_NSURL didMoveToURL) = 0 ;
};

class PASCALIMPLEMENTATION TNSFileCoordinator : public Macapi::Objectivec::TOCGenericImport__2<_di_NSFileCoordinatorClass,_di_NSFileCoordinator>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSFileCoordinatorClass,_di_NSFileCoordinator> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSFileCoordinator(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSFileCoordinatorClass,_di_NSFileCoordinator>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSFileCoordinator() { }
	
};


__interface  INTERFACE_UUID("{01AA9836-6962-4514-8E8A-77A34DDD7305}") NSExceptionClass  : public NSObjectClass 
{
	virtual void * __cdecl exceptionWithName(_di_NSString name, _di_NSString reason, _di_NSDictionary userInfo) = 0 ;
};

__interface  INTERFACE_UUID("{CA04D403-6602-4FE7-9763-498D837C49F7}") NSException  : public NSObject 
{
	virtual _di_NSArray __cdecl callStackReturnAddresses() = 0 ;
	virtual _di_NSArray __cdecl callStackSymbols() = 0 ;
	virtual void * __cdecl initWithName(_di_NSString aName, _di_NSString reason, _di_NSDictionary userInfo) = 0 ;
	virtual _di_NSString __cdecl name() = 0 ;
	virtual _di_NSString __cdecl reason() = 0 ;
	virtual _di_NSDictionary __cdecl userInfo() = 0 ;
};

class PASCALIMPLEMENTATION TNSException : public Macapi::Objectivec::TOCGenericImport__2<_di_NSExceptionClass,_di_NSException>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSExceptionClass,_di_NSException> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSException(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSExceptionClass,_di_NSException>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSException() { }
	
};


__interface  INTERFACE_UUID("{4C3D1539-EE0E-4C3F-B2B2-4C9301B0FDDE}") NSExpressionClass  : public NSObjectClass 
{
	virtual void * __cdecl expressionForAggregate(_di_NSArray subexpressions) = 0 ;
	virtual void * __cdecl expressionForConstantValue(void * obj) = 0 ;
	virtual void * __cdecl expressionForEvaluatedObject() = 0 ;
	virtual void * __cdecl expressionForFunction(_di_NSString name, _di_NSArray arguments) = 0 /* overload */;
	virtual void * __cdecl expressionForFunction(_di_NSExpression target, _di_NSString selectorName, _di_NSArray arguments) = 0 /* overload */;
	virtual void * __cdecl expressionForKeyPath(_di_NSString keyPath) = 0 ;
	virtual void * __cdecl expressionForSubquery(_di_NSExpression expression, _di_NSString usingIteratorVariable, void * predicate) = 0 ;
	virtual void * __cdecl expressionForVariable(_di_NSString string_) = 0 ;
	virtual void * __cdecl expressionWithFormat(_di_NSString expressionFormat) = 0 /* overload */;
	virtual void * __cdecl expressionWithFormat(_di_NSString expressionFormat, _di_NSArray argumentArray) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{A79DFF89-2D05-4A2B-9441-BEE45D9F708F}") NSExpression  : public NSObject 
{
	virtual _di_NSArray __cdecl arguments() = 0 ;
	virtual void * __cdecl collection() = 0 ;
	virtual void * __cdecl constantValue() = 0 ;
	virtual void * __cdecl expressionBlock() = 0 ;
	virtual unsigned long __cdecl expressionType() = 0 ;
	virtual void * __cdecl expressionValueWithObject(void * object_, _di_NSMutableDictionary context) = 0 ;
	virtual void * __cdecl initWithExpressionType(unsigned long type_) = 0 ;
	virtual _di_NSString __cdecl keyPath() = 0 ;
	virtual _di_NSExpression __cdecl leftExpression() = 0 ;
	virtual _di_NSExpression __cdecl operand() = 0 ;
	virtual _di_NSPredicate __cdecl predicate() = 0 ;
	virtual _di_NSExpression __cdecl rightExpression() = 0 ;
	virtual _di_NSString __cdecl variable() = 0 ;
};

class PASCALIMPLEMENTATION TNSExpression : public Macapi::Objectivec::TOCGenericImport__2<_di_NSExpressionClass,_di_NSExpression>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSExpressionClass,_di_NSExpression> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSExpression(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSExpressionClass,_di_NSExpression>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSExpression() { }
	
};


__interface  INTERFACE_UUID("{5C07C02B-E9D7-47C0-826E-B6A6D079EC75}") NSInvocationOperationClass  : public NSOperationClass 
{
	
};

__interface  INTERFACE_UUID("{128CD074-6666-472E-97AF-EB05BB958BD3}") NSInvocationOperation  : public NSOperation 
{
	virtual void * __cdecl initWithInvocation(_di_NSInvocation inv) = 0 ;
	virtual _di_NSInvocation __cdecl invocation() = 0 ;
	virtual void * __cdecl result() = 0 ;
};

class PASCALIMPLEMENTATION TNSInvocationOperation : public Macapi::Objectivec::TOCGenericImport__2<_di_NSInvocationOperationClass,_di_NSInvocationOperation>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSInvocationOperationClass,_di_NSInvocationOperation> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSInvocationOperation(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSInvocationOperationClass,_di_NSInvocationOperation>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSInvocationOperation() { }
	
};


__interface  INTERFACE_UUID("{16A102FC-917E-4EF6-A142-8321BB2F8B19}") NSInputStreamClass  : public NSStreamClass 
{
	virtual void * __cdecl inputStreamWithData(_di_NSData data) = 0 ;
	virtual void * __cdecl inputStreamWithFileAtPath(_di_NSString path) = 0 ;
	virtual void * __cdecl inputStreamWithURL(_di_NSURL url) = 0 ;
};

__interface  INTERFACE_UUID("{978FB0D8-3E75-4980-973D-3F6967A1D975}") NSInputStream  : public NSStream 
{
	virtual bool __cdecl getBuffer(System::PByte buffer, Iosapi::Cocoatypes::PNSUInteger length) = 0 ;
	virtual bool __cdecl hasBytesAvailable() = 0 ;
	virtual void * __cdecl initWithData(_di_NSData data) = 0 ;
	virtual void * __cdecl initWithFileAtPath(_di_NSString path) = 0 ;
	virtual void * __cdecl initWithURL(_di_NSURL url) = 0 ;
	virtual long __cdecl read(System::PByte buffer, Iosapi::Cocoatypes::PNSUInteger maxLength) = 0 ;
};

class PASCALIMPLEMENTATION TNSInputStream : public Macapi::Objectivec::TOCGenericImport__2<_di_NSInputStreamClass,_di_NSInputStream>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSInputStreamClass,_di_NSInputStream> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSInputStream(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSInputStreamClass,_di_NSInputStream>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSInputStream() { }
	
};


__interface  INTERFACE_UUID("{EE289328-43FD-4F16-A662-B9E1E3636A1C}") NSHTTPURLResponseClass  : public NSURLResponseClass 
{
	virtual _di_NSString __cdecl localizedStringForStatusCode(long statusCode) = 0 ;
};

__interface  INTERFACE_UUID("{C413D5CD-C39F-468C-BBB0-6435B74E2C60}") NSHTTPURLResponse  : public NSURLResponse 
{
	virtual _di_NSDictionary __cdecl allHeaderFields() = 0 ;
	HIDESBASE virtual void * __cdecl initWithURL(_di_NSURL url, long statusCode, _di_NSString HTTPVersion, _di_NSDictionary headerFields) = 0 ;
	virtual long __cdecl statusCode() = 0 ;
};

class PASCALIMPLEMENTATION TNSHTTPURLResponse : public Macapi::Objectivec::TOCGenericImport__2<_di_NSHTTPURLResponseClass,_di_NSHTTPURLResponse>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSHTTPURLResponseClass,_di_NSHTTPURLResponse> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSHTTPURLResponse(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSHTTPURLResponseClass,_di_NSHTTPURLResponse>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSHTTPURLResponse() { }
	
};


__interface  INTERFACE_UUID("{5DE1035F-E455-43C9-A2BF-2A5A99F7538F}") NSMachPortClass  : public NSPortClass 
{
	virtual _di_NSPort __cdecl portWithMachPort(unsigned machPort) = 0 /* overload */;
	virtual _di_NSPort __cdecl portWithMachPort(unsigned machPort, unsigned long options) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{D1FC873A-2A57-48C8-A55A-E85742270A7F}") NSMachPort  : public NSPort 
{
	HIDESBASE virtual void * __cdecl delegate() = 0 ;
	virtual void * __cdecl initWithMachPort(unsigned machPort) = 0 /* overload */;
	virtual void * __cdecl initWithMachPort(unsigned machPort, unsigned long options) = 0 /* overload */;
	virtual unsigned __cdecl machPort() = 0 ;
	HIDESBASE virtual void __cdecl removeFromRunLoop(_di_NSRunLoop runLoop, _di_NSString forMode) = 0 ;
	HIDESBASE virtual void __cdecl scheduleInRunLoop(_di_NSRunLoop runLoop, _di_NSString forMode) = 0 ;
	HIDESBASE virtual void __cdecl setDelegate(void * anObject) = 0 ;
};

class PASCALIMPLEMENTATION TNSMachPort : public Macapi::Objectivec::TOCGenericImport__2<_di_NSMachPortClass,_di_NSMachPort>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSMachPortClass,_di_NSMachPort> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSMachPort(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSMachPortClass,_di_NSMachPort>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSMachPort() { }
	
};


__interface  INTERFACE_UUID("{B67F9B9F-FF05-4F03-99CE-136EA85ECE07}") NSKeyedUnarchiverClass  : public NSCoderClass 
{
	virtual void __cdecl setClass(void * cls, _di_NSString forClassName) = 0 /* overload */;
	virtual void * __cdecl unarchiveObjectWithData(_di_NSData data) = 0 ;
	virtual void * __cdecl unarchiveObjectWithFile(_di_NSString path) = 0 ;
};

__interface  INTERFACE_UUID("{194D4B2F-5496-42BB-B674-73BA86288A22}") NSKeyedUnarchiver  : public NSCoder 
{
	HIDESBASE virtual bool __cdecl containsValueForKey(_di_NSString key) = 0 ;
	HIDESBASE virtual bool __cdecl decodeBoolForKey(_di_NSString key) = 0 ;
	HIDESBASE virtual System::PByte __cdecl decodeBytesForKey(_di_NSString key, Iosapi::Cocoatypes::PNSUInteger returnedLength) = 0 ;
	HIDESBASE virtual double __cdecl decodeDoubleForKey(_di_NSString key) = 0 ;
	HIDESBASE virtual float __cdecl decodeFloatForKey(_di_NSString key) = 0 ;
	HIDESBASE virtual int __cdecl decodeInt32ForKey(_di_NSString key) = 0 ;
	HIDESBASE virtual __int64 __cdecl decodeInt64ForKey(_di_NSString key) = 0 ;
	HIDESBASE virtual int __cdecl decodeIntForKey(_di_NSString key) = 0 ;
	HIDESBASE virtual void * __cdecl decodeObjectForKey(_di_NSString key) = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual void __cdecl finishDecoding() = 0 ;
	virtual void * __cdecl initForReadingWithData(_di_NSData data) = 0 ;
	virtual void __cdecl setClass(void * cls, _di_NSString forClassName) = 0 /* overload */;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
};

class PASCALIMPLEMENTATION TNSKeyedUnarchiver : public Macapi::Objectivec::TOCGenericImport__2<_di_NSKeyedUnarchiverClass,_di_NSKeyedUnarchiver>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSKeyedUnarchiverClass,_di_NSKeyedUnarchiver> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSKeyedUnarchiver(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSKeyedUnarchiverClass,_di_NSKeyedUnarchiver>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSKeyedUnarchiver() { }
	
};


__interface  INTERFACE_UUID("{DF9BC570-C5E5-4CB8-B23F-CC3D45CD7826}") NSKeyedArchiverClass  : public NSCoderClass 
{
	virtual bool __cdecl archiveRootObject(void * rootObject, _di_NSString toFile) = 0 ;
	virtual _di_NSData __cdecl archivedDataWithRootObject(void * rootObject) = 0 ;
	virtual _di_NSString __cdecl classNameForClass(void * cls) = 0 /* overload */;
	virtual void __cdecl setClassName(_di_NSString codedName, void * forClass) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{BD14DE95-B9E3-4753-B7AC-F471B533D842}") NSKeyedArchiver  : public NSCoder 
{
	virtual _di_NSString __cdecl classNameForClass(void * cls) = 0 /* overload */;
	virtual void * __cdecl delegate() = 0 ;
	HIDESBASE virtual void __cdecl encodeBool(bool boolv, _di_NSString forKey) = 0 ;
	HIDESBASE virtual void __cdecl encodeBytes(System::PByte bytesp, unsigned long length, _di_NSString forKey) = 0 ;
	HIDESBASE virtual void __cdecl encodeConditionalObject(void * objv, _di_NSString forKey) = 0 ;
	HIDESBASE virtual void __cdecl encodeDouble(double realv, _di_NSString forKey) = 0 ;
	HIDESBASE virtual void __cdecl encodeFloat(float realv, _di_NSString forKey) = 0 ;
	HIDESBASE virtual void __cdecl encodeInt32(int intv, _di_NSString forKey) = 0 ;
	HIDESBASE virtual void __cdecl encodeInt64(__int64 intv, _di_NSString forKey) = 0 ;
	HIDESBASE virtual void __cdecl encodeInt(int intv, _di_NSString forKey) = 0 ;
	HIDESBASE virtual void __cdecl encodeObject(void * objv, _di_NSString forKey) = 0 ;
	virtual void __cdecl finishEncoding() = 0 ;
	virtual void * __cdecl initForWritingWithMutableData(_di_NSMutableData data) = 0 ;
	virtual unsigned long __cdecl outputFormat() = 0 ;
	virtual void __cdecl setClassName(_di_NSString codedName, void * forClass) = 0 /* overload */;
	virtual void __cdecl setDelegate(void * delegate) = 0 ;
	virtual void __cdecl setOutputFormat(unsigned long format) = 0 ;
};

class PASCALIMPLEMENTATION TNSKeyedArchiver : public Macapi::Objectivec::TOCGenericImport__2<_di_NSKeyedArchiverClass,_di_NSKeyedArchiver>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSKeyedArchiverClass,_di_NSKeyedArchiver> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSKeyedArchiver(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSKeyedArchiverClass,_di_NSKeyedArchiver>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSKeyedArchiver() { }
	
};


__interface  INTERFACE_UUID("{E4E1609D-295E-49FE-804E-EB0EDA50C192}") NSCompoundPredicateClass  : public NSPredicateClass 
{
	virtual _di_NSPredicate __cdecl andPredicateWithSubpredicates(_di_NSArray subpredicates) = 0 ;
	virtual _di_NSPredicate __cdecl notPredicateWithSubpredicate(_di_NSPredicate predicate) = 0 ;
	virtual _di_NSPredicate __cdecl orPredicateWithSubpredicates(_di_NSArray subpredicates) = 0 ;
};

__interface  INTERFACE_UUID("{F57072CB-F2E2-4182-882B-EE23D5D7123E}") NSCompoundPredicate  : public NSPredicate 
{
	virtual unsigned long __cdecl compoundPredicateType() = 0 ;
	virtual void * __cdecl initWithType(unsigned long type_, _di_NSArray subpredicates) = 0 ;
	virtual _di_NSArray __cdecl subpredicates() = 0 ;
};

class PASCALIMPLEMENTATION TNSCompoundPredicate : public Macapi::Objectivec::TOCGenericImport__2<_di_NSCompoundPredicateClass,_di_NSCompoundPredicate>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSCompoundPredicateClass,_di_NSCompoundPredicate> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSCompoundPredicate(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSCompoundPredicateClass,_di_NSCompoundPredicate>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSCompoundPredicate() { }
	
};


__interface  INTERFACE_UUID("{786AB822-4B8B-4070-BF93-5D11B68472C9}") NSComparisonPredicateClass  : public NSPredicateClass 
{
	virtual _di_NSPredicate __cdecl predicateWithLeftExpression(_di_NSExpression lhs, _di_NSExpression rightExpression, void * customSelector) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{E5909A18-ED9B-4255-8CED-8455ECD28843}") NSComparisonPredicate  : public NSPredicate 
{
	virtual unsigned long __cdecl comparisonPredicateModifier() = 0 ;
	virtual void * __cdecl customSelector() = 0 ;
	virtual void * __cdecl initWithLeftExpression(_di_NSExpression lhs, _di_NSExpression rightExpression, void * customSelector) = 0 /* overload */;
	virtual _di_NSExpression __cdecl leftExpression() = 0 ;
	virtual unsigned long __cdecl options() = 0 ;
	virtual unsigned long __cdecl predicateOperatorType() = 0 ;
	virtual _di_NSExpression __cdecl rightExpression() = 0 ;
};

class PASCALIMPLEMENTATION TNSComparisonPredicate : public Macapi::Objectivec::TOCGenericImport__2<_di_NSComparisonPredicateClass,_di_NSComparisonPredicate>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSComparisonPredicateClass,_di_NSComparisonPredicate> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSComparisonPredicate(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSComparisonPredicateClass,_di_NSComparisonPredicate>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSComparisonPredicate() { }
	
};


__interface  INTERFACE_UUID("{44B31923-9CB8-4C4E-B789-CDCC3954E0B7}") NSBlockOperationClass  : public NSOperationClass 
{
	
};

__interface  INTERFACE_UUID("{2491EBFA-C43F-4AC6-AA82-D1679E0760DC}") NSBlockOperation  : public NSOperation 
{
	virtual _di_NSArray __cdecl executionBlocks() = 0 ;
};

class PASCALIMPLEMENTATION TNSBlockOperation : public Macapi::Objectivec::TOCGenericImport__2<_di_NSBlockOperationClass,_di_NSBlockOperation>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSBlockOperationClass,_di_NSBlockOperation> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSBlockOperation(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSBlockOperationClass,_di_NSBlockOperation>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSBlockOperation() { }
	
};


__interface  INTERFACE_UUID("{35015557-9EC0-4C85-955C-7B36FFC16CE0}") NSDirectoryEnumeratorClass  : public NSEnumeratorClass 
{
	
};

__interface  INTERFACE_UUID("{6CE6B7F6-ECA3-43A9-8495-94D2270960A3}") NSDirectoryEnumerator  : public NSEnumerator 
{
	virtual _di_NSDictionary __cdecl directoryAttributes() = 0 ;
	virtual _di_NSDictionary __cdecl fileAttributes() = 0 ;
	virtual unsigned long __cdecl level() = 0 ;
	virtual void __cdecl skipDescendants() = 0 ;
	virtual void __cdecl skipDescendents() = 0 ;
};

class PASCALIMPLEMENTATION TNSDirectoryEnumerator : public Macapi::Objectivec::TOCGenericImport__2<_di_NSDirectoryEnumeratorClass,_di_NSDirectoryEnumerator>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSDirectoryEnumeratorClass,_di_NSDirectoryEnumerator> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSDirectoryEnumerator(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSDirectoryEnumeratorClass,_di_NSDirectoryEnumerator>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSDirectoryEnumerator() { }
	
};


__interface  INTERFACE_UUID("{7D7FC6A9-97FF-4CEA-9B2F-B36971A14C42}") NSDateFormatterClass  : public NSFormatterClass 
{
	virtual _di_NSString __cdecl dateFormatFromTemplate(_di_NSString tmplate, unsigned long options, _di_NSLocale locale) = 0 ;
	virtual unsigned long __cdecl defaultFormatterBehavior() = 0 ;
	virtual _di_NSString __cdecl localizedStringFromDate(_di_NSDate date, unsigned long dateStyle, unsigned long timeStyle) = 0 ;
	virtual void __cdecl setDefaultFormatterBehavior(unsigned long behavior) = 0 ;
};

__interface  INTERFACE_UUID("{0CCF42E5-243E-48DD-959C-C35E0AAC4A10}") NSDateFormatter  : public NSFormatter 
{
	virtual _di_NSString __cdecl AMSymbol() = 0 ;
	virtual _di_NSString __cdecl PMSymbol() = 0 ;
	virtual _di_NSCalendar __cdecl calendar() = 0 ;
	virtual _di_NSString __cdecl dateFormat() = 0 ;
	virtual _di_NSDate __cdecl dateFromString(_di_NSString string_) = 0 ;
	virtual unsigned long __cdecl dateStyle() = 0 ;
	virtual _di_NSDate __cdecl defaultDate() = 0 ;
	virtual bool __cdecl doesRelativeDateFormatting() = 0 ;
	virtual _di_NSArray __cdecl eraSymbols() = 0 ;
	virtual unsigned long __cdecl formatterBehavior() = 0 ;
	virtual bool __cdecl generatesCalendarDates() = 0 ;
	HIDESBASE virtual bool __cdecl getObjectValue(/* out */ void * &obj, _di_NSString forString, NSRange &range, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual _di_NSDate __cdecl gregorianStartDate() = 0 ;
	virtual bool __cdecl isLenient() = 0 ;
	virtual _di_NSLocale __cdecl locale() = 0 ;
	virtual _di_NSArray __cdecl longEraSymbols() = 0 ;
	virtual _di_NSArray __cdecl monthSymbols() = 0 ;
	virtual _di_NSArray __cdecl quarterSymbols() = 0 ;
	virtual void __cdecl setAMSymbol(_di_NSString string_) = 0 ;
	virtual void __cdecl setCalendar(_di_NSCalendar calendar) = 0 ;
	virtual void __cdecl setDateFormat(_di_NSString string_) = 0 ;
	virtual void __cdecl setDateStyle(unsigned long style) = 0 ;
	virtual void __cdecl setDefaultDate(_di_NSDate date) = 0 ;
	virtual void __cdecl setDoesRelativeDateFormatting(bool b) = 0 ;
	virtual void __cdecl setEraSymbols(_di_NSArray array_) = 0 ;
	virtual void __cdecl setFormatterBehavior(unsigned long behavior) = 0 ;
	virtual void __cdecl setGeneratesCalendarDates(bool b) = 0 ;
	virtual void __cdecl setGregorianStartDate(_di_NSDate date) = 0 ;
	virtual void __cdecl setLenient(bool b) = 0 ;
	virtual void __cdecl setLocale(_di_NSLocale locale) = 0 ;
	virtual void __cdecl setLongEraSymbols(_di_NSArray array_) = 0 ;
	virtual void __cdecl setMonthSymbols(_di_NSArray array_) = 0 ;
	virtual void __cdecl setPMSymbol(_di_NSString string_) = 0 ;
	virtual void __cdecl setQuarterSymbols(_di_NSArray array_) = 0 ;
	virtual void __cdecl setShortMonthSymbols(_di_NSArray array_) = 0 ;
	virtual void __cdecl setShortQuarterSymbols(_di_NSArray array_) = 0 ;
	virtual void __cdecl setShortStandaloneMonthSymbols(_di_NSArray array_) = 0 ;
	virtual void __cdecl setShortStandaloneQuarterSymbols(_di_NSArray array_) = 0 ;
	virtual void __cdecl setShortStandaloneWeekdaySymbols(_di_NSArray array_) = 0 ;
	virtual void __cdecl setShortWeekdaySymbols(_di_NSArray array_) = 0 ;
	virtual void __cdecl setStandaloneMonthSymbols(_di_NSArray array_) = 0 ;
	virtual void __cdecl setStandaloneQuarterSymbols(_di_NSArray array_) = 0 ;
	virtual void __cdecl setStandaloneWeekdaySymbols(_di_NSArray array_) = 0 ;
	virtual void __cdecl setTimeStyle(unsigned long style) = 0 ;
	virtual void __cdecl setTimeZone(_di_NSTimeZone tz) = 0 ;
	virtual void __cdecl setTwoDigitStartDate(_di_NSDate date) = 0 ;
	virtual void __cdecl setVeryShortMonthSymbols(_di_NSArray array_) = 0 ;
	virtual void __cdecl setVeryShortStandaloneMonthSymbols(_di_NSArray array_) = 0 ;
	virtual void __cdecl setVeryShortStandaloneWeekdaySymbols(_di_NSArray array_) = 0 ;
	virtual void __cdecl setVeryShortWeekdaySymbols(_di_NSArray array_) = 0 ;
	virtual void __cdecl setWeekdaySymbols(_di_NSArray array_) = 0 ;
	virtual _di_NSArray __cdecl shortMonthSymbols() = 0 ;
	virtual _di_NSArray __cdecl shortQuarterSymbols() = 0 ;
	virtual _di_NSArray __cdecl shortStandaloneMonthSymbols() = 0 ;
	virtual _di_NSArray __cdecl shortStandaloneQuarterSymbols() = 0 ;
	virtual _di_NSArray __cdecl shortStandaloneWeekdaySymbols() = 0 ;
	virtual _di_NSArray __cdecl shortWeekdaySymbols() = 0 ;
	virtual _di_NSArray __cdecl standaloneMonthSymbols() = 0 ;
	virtual _di_NSArray __cdecl standaloneQuarterSymbols() = 0 ;
	virtual _di_NSArray __cdecl standaloneWeekdaySymbols() = 0 ;
	virtual _di_NSString __cdecl stringFromDate(_di_NSDate date) = 0 ;
	virtual unsigned long __cdecl timeStyle() = 0 ;
	virtual _di_NSTimeZone __cdecl timeZone() = 0 ;
	virtual _di_NSDate __cdecl twoDigitStartDate() = 0 ;
	virtual _di_NSArray __cdecl veryShortMonthSymbols() = 0 ;
	virtual _di_NSArray __cdecl veryShortStandaloneMonthSymbols() = 0 ;
	virtual _di_NSArray __cdecl veryShortStandaloneWeekdaySymbols() = 0 ;
	virtual _di_NSArray __cdecl veryShortWeekdaySymbols() = 0 ;
	virtual _di_NSArray __cdecl weekdaySymbols() = 0 ;
};

class PASCALIMPLEMENTATION TNSDateFormatter : public Macapi::Objectivec::TOCGenericImport__2<_di_NSDateFormatterClass,_di_NSDateFormatter>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSDateFormatterClass,_di_NSDateFormatter> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSDateFormatter(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSDateFormatterClass,_di_NSDateFormatter>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSDateFormatter() { }
	
};


__interface  INTERFACE_UUID("{6035CFA9-D820-4529-8455-4123E92C7A7A}") NSExtensionContextClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{2B22A0D2-E0FB-4EA1-8E2C-BC7108AFF1BA}") NSExtensionContext  : public NSObject 
{
	virtual _di_NSArray __cdecl inputItems() = 0 ;
	virtual void __cdecl completeRequestReturningItems(_di_NSArray items, TFoundationCompletionHandler5 completionHandler) = 0 ;
	virtual void __cdecl cancelRequestWithError(_di_NSError error) = 0 ;
	virtual void __cdecl openURL(_di_NSURL url, TFoundationCompletionHandler5 completionHandler) = 0 ;
};

class PASCALIMPLEMENTATION TNSExtensionContext : public Macapi::Objectivec::TOCGenericImport__2<_di_NSExtensionContextClass,_di_NSExtensionContext>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSExtensionContextClass,_di_NSExtensionContext> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSExtensionContext(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSExtensionContextClass,_di_NSExtensionContext>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSExtensionContext() { }
	
};


typedef void * PNSExtensionContext;

__interface  INTERFACE_UUID("{098B3580-09D4-4CAC-A909-ADC38FE7F221}") NSDataDetectorClass  : public NSRegularExpressionClass 
{
	virtual void * __cdecl dataDetectorWithTypes(unsigned __int64 checkingTypes, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
};

__interface  INTERFACE_UUID("{FF837F9D-876C-4595-85E9-D67A8E2F46D4}") NSDataDetector  : public NSRegularExpression 
{
	virtual unsigned __int64 __cdecl checkingTypes() = 0 ;
	virtual void * __cdecl initWithTypes(unsigned __int64 checkingTypes, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
};

class PASCALIMPLEMENTATION TNSDataDetector : public Macapi::Objectivec::TOCGenericImport__2<_di_NSDataDetectorClass,_di_NSDataDetector>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSDataDetectorClass,_di_NSDataDetector> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSDataDetector(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSDataDetectorClass,_di_NSDataDetector>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSDataDetector() { }
	
};


__interface  INTERFACE_UUID("{553484FC-06B7-42B8-AE42-7B521728E9A6}") NSMutableArrayClass  : public NSArrayClass 
{
	virtual void * __cdecl arrayWithCapacity(unsigned long numItems) = 0 ;
};

__interface  INTERFACE_UUID("{F0B9F97E-F33A-4A1A-AD8F-920C03FDD3B7}") NSMutableArray  : public NSArray 
{
	virtual void __cdecl addObject(void * anObject) = 0 ;
	virtual void __cdecl addObjectsFromArray(_di_NSArray otherArray) = 0 ;
	virtual void __cdecl exchangeObjectAtIndex(unsigned long idx1, unsigned long withObjectAtIndex) = 0 ;
	virtual void __cdecl filterUsingPredicate(_di_NSPredicate predicate) = 0 ;
	virtual void * __cdecl initWithCapacity(unsigned long numItems) = 0 ;
	virtual void __cdecl insertObject(void * anObject, unsigned long atIndex) = 0 ;
	virtual void __cdecl insertObjects(_di_NSArray objects, _di_NSIndexSet atIndexes) = 0 ;
	virtual void __cdecl removeAllObjects() = 0 ;
	virtual void __cdecl removeLastObject() = 0 ;
	virtual void __cdecl removeObject(void * anObject) = 0 /* overload */;
	virtual void __cdecl removeObject(void * anObject, NSRange inRange) = 0 /* overload */;
	virtual void __cdecl removeObjectAtIndex(unsigned long index) = 0 ;
	virtual void __cdecl removeObjectIdenticalTo(void * anObject) = 0 /* overload */;
	virtual void __cdecl removeObjectIdenticalTo(void * anObject, NSRange inRange) = 0 /* overload */;
	virtual void __cdecl removeObjectsAtIndexes(_di_NSIndexSet indexes) = 0 ;
	virtual void __cdecl removeObjectsFromIndices(Iosapi::Cocoatypes::PNSUInteger indices, unsigned long numIndices) = 0 ;
	virtual void __cdecl removeObjectsInArray(_di_NSArray otherArray) = 0 ;
	virtual void __cdecl removeObjectsInRange(NSRange range) = 0 ;
	virtual void __cdecl replaceObjectAtIndex(unsigned long index, void * withObject) = 0 ;
	virtual void __cdecl replaceObjectsAtIndexes(_di_NSIndexSet indexes, _di_NSArray withObjects) = 0 ;
	virtual void __cdecl replaceObjectsInRange(NSRange range, _di_NSArray withObjectsFromArray) = 0 /* overload */;
	virtual void __cdecl setArray(_di_NSArray otherArray) = 0 ;
	virtual void __cdecl sortUsingDescriptors(_di_NSArray sortDescriptors) = 0 ;
	virtual void __cdecl sortUsingSelector(void * comparator) = 0 ;
};

class PASCALIMPLEMENTATION TNSMutableArray : public Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableArrayClass,_di_NSMutableArray>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableArrayClass,_di_NSMutableArray> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSMutableArray(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableArrayClass,_di_NSMutableArray>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSMutableArray() { }
	
};


__interface  INTERFACE_UUID("{34615854-F0B3-45A1-BBED-F5C44E9E7D56}") NSMutableURLRequestClass  : public NSURLRequestClass 
{
	
};

__interface  INTERFACE_UUID("{49BEA692-B5DD-4469-90EE-EE46801F5148}") NSMutableURLRequest  : public NSURLRequest 
{
	virtual void __cdecl addValue(_di_NSString value, _di_NSString forHTTPHeaderField) = 0 ;
	virtual void __cdecl setAllHTTPHeaderFields(_di_NSDictionary headerFields) = 0 ;
	virtual void __cdecl setCachePolicy(unsigned long policy) = 0 ;
	virtual void __cdecl setHTTPBody(_di_NSData data) = 0 ;
	virtual void __cdecl setHTTPBodyStream(_di_NSInputStream inputStream) = 0 ;
	virtual void __cdecl setHTTPMethod(_di_NSString method) = 0 ;
	virtual void __cdecl setHTTPShouldHandleCookies(bool should) = 0 ;
	virtual void __cdecl setHTTPShouldUsePipelining(bool shouldUsePipelining) = 0 ;
	virtual void __cdecl setMainDocumentURL(_di_NSURL URL) = 0 ;
	virtual void __cdecl setNetworkServiceType(unsigned long networkServiceType) = 0 ;
	virtual void __cdecl setTimeoutInterval(double seconds) = 0 ;
	virtual void __cdecl setURL(_di_NSURL URL) = 0 ;
	virtual void __cdecl setValue(_di_NSString value, _di_NSString forHTTPHeaderField) = 0 ;
};

class PASCALIMPLEMENTATION TNSMutableURLRequest : public Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableURLRequestClass,_di_NSMutableURLRequest>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableURLRequestClass,_di_NSMutableURLRequest> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSMutableURLRequest(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableURLRequestClass,_di_NSMutableURLRequest>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSMutableURLRequest() { }
	
};


__interface  INTERFACE_UUID("{5CBD1AF1-C96E-467F-82CC-3B111FA880F9}") NSMutableStringClass  : public NSStringClass 
{
	virtual void * __cdecl stringWithCapacity(unsigned long capacity) = 0 ;
};

__interface  INTERFACE_UUID("{0DE0FF9A-B0CD-4448-8262-4FACD281E4DB}") NSMutableString  : public NSString 
{
	virtual void __cdecl appendFormat(_di_NSString format) = 0 ;
	virtual void __cdecl appendString(_di_NSString aString) = 0 ;
	virtual void __cdecl deleteCharactersInRange(NSRange range) = 0 ;
	virtual void * __cdecl initWithCapacity(unsigned long capacity) = 0 ;
	virtual void __cdecl insertString(_di_NSString aString, unsigned long atIndex) = 0 ;
	virtual void __cdecl replaceCharactersInRange(NSRange range, _di_NSString withString) = 0 ;
	virtual unsigned long __cdecl replaceOccurrencesOfString(_di_NSString target, _di_NSString withString, unsigned long options, NSRange range) = 0 ;
	virtual void __cdecl setString(_di_NSString aString) = 0 ;
};

class PASCALIMPLEMENTATION TNSMutableString : public Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableStringClass,_di_NSMutableString>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableStringClass,_di_NSMutableString> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSMutableString(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableStringClass,_di_NSMutableString>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSMutableString() { }
	
};


__interface  INTERFACE_UUID("{DA83FDA5-F35B-4EB8-B259-6D211349AF37}") NSMutableSetClass  : public NSSetClass 
{
	virtual void * __cdecl setWithCapacity(unsigned long numItems) = 0 ;
};

__interface  INTERFACE_UUID("{A99715A3-693D-4FBF-8374-3580A703A5C1}") NSMutableSet  : public NSSet 
{
	virtual void __cdecl addObject(void * object_) = 0 ;
	virtual void __cdecl addObjectsFromArray(_di_NSArray array_) = 0 ;
	virtual void __cdecl filterUsingPredicate(_di_NSPredicate predicate) = 0 ;
	virtual void * __cdecl initWithCapacity(unsigned long numItems) = 0 ;
	virtual void __cdecl intersectSet(_di_NSSet otherSet) = 0 ;
	virtual void __cdecl minusSet(_di_NSSet otherSet) = 0 ;
	virtual void __cdecl removeAllObjects() = 0 ;
	virtual void __cdecl removeObject(void * object_) = 0 ;
	virtual void __cdecl setSet(_di_NSSet otherSet) = 0 ;
	virtual void __cdecl unionSet(_di_NSSet otherSet) = 0 ;
};

class PASCALIMPLEMENTATION TNSMutableSet : public Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableSetClass,_di_NSMutableSet>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableSetClass,_di_NSMutableSet> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSMutableSet(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableSetClass,_di_NSMutableSet>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSMutableSet() { }
	
};


__interface  INTERFACE_UUID("{8503B038-20EB-4F49-B36D-665782C7D05F}") NSOutputStreamClass  : public NSStreamClass 
{
	virtual void * __cdecl outputStreamToBuffer(System::PByte buffer, unsigned long capacity) = 0 ;
	virtual void * __cdecl outputStreamToFileAtPath(_di_NSString path, bool append) = 0 ;
	virtual void * __cdecl outputStreamToMemory() = 0 ;
	virtual void * __cdecl outputStreamWithURL(_di_NSURL url, bool append) = 0 ;
};

__interface  INTERFACE_UUID("{A76DB431-5E26-4853-B0F1-095363B009F1}") NSOutputStream  : public NSStream 
{
	virtual bool __cdecl hasSpaceAvailable() = 0 ;
	virtual void * __cdecl initToBuffer(System::PByte buffer, unsigned long capacity) = 0 ;
	virtual void * __cdecl initToFileAtPath(_di_NSString path, bool append) = 0 ;
	virtual void * __cdecl initToMemory() = 0 ;
	virtual void * __cdecl initWithURL(_di_NSURL url, bool append) = 0 ;
	virtual long __cdecl write(System::PByte buffer, unsigned long maxLength) = 0 ;
};

class PASCALIMPLEMENTATION TNSOutputStream : public Macapi::Objectivec::TOCGenericImport__2<_di_NSOutputStreamClass,_di_NSOutputStream>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSOutputStreamClass,_di_NSOutputStream> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSOutputStream(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSOutputStreamClass,_di_NSOutputStream>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSOutputStream() { }
	
};


__interface  INTERFACE_UUID("{7943B454-721E-4A57-AD86-D2DC25D68D2A}") NSNumberFormatterClass  : public NSFormatterClass 
{
	virtual unsigned long __cdecl defaultFormatterBehavior() = 0 ;
	virtual _di_NSString __cdecl localizedStringFromNumber(_di_NSNumber num, unsigned long numberStyle) = 0 ;
	virtual void __cdecl setDefaultFormatterBehavior(unsigned long behavior) = 0 ;
};

__interface  INTERFACE_UUID("{D4C838DB-7233-40DA-8D0A-8FA4D8384A0F}") NSNumberFormatter  : public NSFormatter 
{
	virtual bool __cdecl allowsFloats() = 0 ;
	virtual bool __cdecl alwaysShowsDecimalSeparator() = 0 ;
	virtual _di_NSString __cdecl currencyCode() = 0 ;
	virtual _di_NSString __cdecl currencyDecimalSeparator() = 0 ;
	virtual _di_NSString __cdecl currencyGroupingSeparator() = 0 ;
	virtual _di_NSString __cdecl currencySymbol() = 0 ;
	virtual _di_NSString __cdecl decimalSeparator() = 0 ;
	virtual _di_NSString __cdecl exponentSymbol() = 0 ;
	virtual unsigned long __cdecl formatWidth() = 0 ;
	virtual unsigned long __cdecl formatterBehavior() = 0 ;
	virtual bool __cdecl generatesDecimalNumbers() = 0 ;
	HIDESBASE virtual bool __cdecl getObjectValue(/* out */ void * &obj, _di_NSString forString, NSRange &range, System::PPointer error = (System::PPointer)(0x0)) = 0 ;
	virtual _di_NSString __cdecl groupingSeparator() = 0 ;
	virtual unsigned long __cdecl groupingSize() = 0 ;
	virtual _di_NSString __cdecl internationalCurrencySymbol() = 0 ;
	virtual bool __cdecl isLenient() = 0 ;
	virtual bool __cdecl isPartialStringValidationEnabled() = 0 ;
	virtual _di_NSLocale __cdecl locale() = 0 ;
	virtual _di_NSNumber __cdecl maximum() = 0 ;
	virtual unsigned long __cdecl maximumFractionDigits() = 0 ;
	virtual unsigned long __cdecl maximumIntegerDigits() = 0 ;
	virtual unsigned long __cdecl maximumSignificantDigits() = 0 ;
	virtual _di_NSNumber __cdecl minimum() = 0 ;
	virtual unsigned long __cdecl minimumFractionDigits() = 0 ;
	virtual unsigned long __cdecl minimumIntegerDigits() = 0 ;
	virtual unsigned long __cdecl minimumSignificantDigits() = 0 ;
	virtual _di_NSString __cdecl minusSign() = 0 ;
	virtual _di_NSNumber __cdecl multiplier() = 0 ;
	virtual _di_NSString __cdecl negativeFormat() = 0 ;
	virtual _di_NSString __cdecl negativeInfinitySymbol() = 0 ;
	virtual _di_NSString __cdecl negativePrefix() = 0 ;
	virtual _di_NSString __cdecl negativeSuffix() = 0 ;
	virtual _di_NSString __cdecl nilSymbol() = 0 ;
	virtual _di_NSString __cdecl notANumberSymbol() = 0 ;
	virtual _di_NSNumber __cdecl numberFromString(_di_NSString string_) = 0 ;
	virtual unsigned long __cdecl numberStyle() = 0 ;
	virtual _di_NSString __cdecl paddingCharacter() = 0 ;
	virtual unsigned long __cdecl paddingPosition() = 0 ;
	virtual _di_NSString __cdecl perMillSymbol() = 0 ;
	virtual _di_NSString __cdecl percentSymbol() = 0 ;
	virtual _di_NSString __cdecl plusSign() = 0 ;
	virtual _di_NSString __cdecl positiveFormat() = 0 ;
	virtual _di_NSString __cdecl positiveInfinitySymbol() = 0 ;
	virtual _di_NSString __cdecl positivePrefix() = 0 ;
	virtual _di_NSString __cdecl positiveSuffix() = 0 ;
	virtual _di_NSNumber __cdecl roundingIncrement() = 0 ;
	virtual unsigned long __cdecl roundingMode() = 0 ;
	virtual unsigned long __cdecl secondaryGroupingSize() = 0 ;
	virtual void __cdecl setAllowsFloats(bool flag) = 0 ;
	virtual void __cdecl setAlwaysShowsDecimalSeparator(bool b) = 0 ;
	virtual void __cdecl setCurrencyCode(_di_NSString string_) = 0 ;
	virtual void __cdecl setCurrencyDecimalSeparator(_di_NSString string_) = 0 ;
	virtual void __cdecl setCurrencyGroupingSeparator(_di_NSString string_) = 0 ;
	virtual void __cdecl setCurrencySymbol(_di_NSString string_) = 0 ;
	virtual void __cdecl setDecimalSeparator(_di_NSString string_) = 0 ;
	virtual void __cdecl setExponentSymbol(_di_NSString string_) = 0 ;
	virtual void __cdecl setFormatWidth(unsigned long number) = 0 ;
	virtual void __cdecl setFormatterBehavior(unsigned long behavior) = 0 ;
	virtual void __cdecl setGeneratesDecimalNumbers(bool b) = 0 ;
	virtual void __cdecl setGroupingSeparator(_di_NSString string_) = 0 ;
	virtual void __cdecl setGroupingSize(unsigned long number) = 0 ;
	virtual void __cdecl setInternationalCurrencySymbol(_di_NSString string_) = 0 ;
	virtual void __cdecl setLenient(bool b) = 0 ;
	virtual void __cdecl setLocale(_di_NSLocale locale) = 0 ;
	virtual void __cdecl setMaximum(_di_NSNumber number) = 0 ;
	virtual void __cdecl setMaximumFractionDigits(unsigned long number) = 0 ;
	virtual void __cdecl setMaximumIntegerDigits(unsigned long number) = 0 ;
	virtual void __cdecl setMaximumSignificantDigits(unsigned long number) = 0 ;
	virtual void __cdecl setMinimum(_di_NSNumber number) = 0 ;
	virtual void __cdecl setMinimumFractionDigits(unsigned long number) = 0 ;
	virtual void __cdecl setMinimumIntegerDigits(unsigned long number) = 0 ;
	virtual void __cdecl setMinimumSignificantDigits(unsigned long number) = 0 ;
	virtual void __cdecl setMinusSign(_di_NSString string_) = 0 ;
	virtual void __cdecl setMultiplier(_di_NSNumber number) = 0 ;
	virtual void __cdecl setNegativeFormat(_di_NSString format) = 0 ;
	virtual void __cdecl setNegativeInfinitySymbol(_di_NSString string_) = 0 ;
	virtual void __cdecl setNegativePrefix(_di_NSString string_) = 0 ;
	virtual void __cdecl setNegativeSuffix(_di_NSString string_) = 0 ;
	virtual void __cdecl setNilSymbol(_di_NSString string_) = 0 ;
	virtual void __cdecl setNotANumberSymbol(_di_NSString string_) = 0 ;
	virtual void __cdecl setNumberStyle(unsigned long style) = 0 ;
	virtual void __cdecl setPaddingCharacter(_di_NSString string_) = 0 ;
	virtual void __cdecl setPaddingPosition(unsigned long position) = 0 ;
	virtual void __cdecl setPartialStringValidationEnabled(bool b) = 0 ;
	virtual void __cdecl setPerMillSymbol(_di_NSString string_) = 0 ;
	virtual void __cdecl setPercentSymbol(_di_NSString string_) = 0 ;
	virtual void __cdecl setPlusSign(_di_NSString string_) = 0 ;
	virtual void __cdecl setPositiveFormat(_di_NSString format) = 0 ;
	virtual void __cdecl setPositiveInfinitySymbol(_di_NSString string_) = 0 ;
	virtual void __cdecl setPositivePrefix(_di_NSString string_) = 0 ;
	virtual void __cdecl setPositiveSuffix(_di_NSString string_) = 0 ;
	virtual void __cdecl setRoundingIncrement(_di_NSNumber number) = 0 ;
	virtual void __cdecl setRoundingMode(unsigned long mode) = 0 ;
	virtual void __cdecl setSecondaryGroupingSize(unsigned long number) = 0 ;
	virtual void __cdecl setTextAttributesForNegativeInfinity(_di_NSDictionary newAttributes) = 0 ;
	virtual void __cdecl setTextAttributesForNegativeValues(_di_NSDictionary newAttributes) = 0 ;
	virtual void __cdecl setTextAttributesForNil(_di_NSDictionary newAttributes) = 0 ;
	virtual void __cdecl setTextAttributesForNotANumber(_di_NSDictionary newAttributes) = 0 ;
	virtual void __cdecl setTextAttributesForPositiveInfinity(_di_NSDictionary newAttributes) = 0 ;
	virtual void __cdecl setTextAttributesForPositiveValues(_di_NSDictionary newAttributes) = 0 ;
	virtual void __cdecl setTextAttributesForZero(_di_NSDictionary newAttributes) = 0 ;
	virtual void __cdecl setUsesGroupingSeparator(bool b) = 0 ;
	virtual void __cdecl setUsesSignificantDigits(bool b) = 0 ;
	virtual void __cdecl setZeroSymbol(_di_NSString string_) = 0 ;
	virtual _di_NSString __cdecl stringFromNumber(_di_NSNumber number) = 0 ;
	virtual _di_NSDictionary __cdecl textAttributesForNegativeInfinity() = 0 ;
	virtual _di_NSDictionary __cdecl textAttributesForNegativeValues() = 0 ;
	virtual _di_NSDictionary __cdecl textAttributesForNil() = 0 ;
	virtual _di_NSDictionary __cdecl textAttributesForNotANumber() = 0 ;
	virtual _di_NSDictionary __cdecl textAttributesForPositiveInfinity() = 0 ;
	virtual _di_NSDictionary __cdecl textAttributesForPositiveValues() = 0 ;
	virtual _di_NSDictionary __cdecl textAttributesForZero() = 0 ;
	virtual bool __cdecl usesGroupingSeparator() = 0 ;
	virtual bool __cdecl usesSignificantDigits() = 0 ;
	virtual _di_NSString __cdecl zeroSymbol() = 0 ;
};

class PASCALIMPLEMENTATION TNSNumberFormatter : public Macapi::Objectivec::TOCGenericImport__2<_di_NSNumberFormatterClass,_di_NSNumberFormatter>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSNumberFormatterClass,_di_NSNumberFormatter> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSNumberFormatter(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSNumberFormatterClass,_di_NSNumberFormatter>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSNumberFormatter() { }
	
};


__interface  INTERFACE_UUID("{82392D79-32AF-4380-9389-667299F94C07}") NSNumberClass  : public NSValueClass 
{
	virtual void * __cdecl numberWithBool(bool value) = 0 ;
	virtual void * __cdecl numberWithChar(System::WideChar value) = 0 ;
	virtual void * __cdecl numberWithDouble(double value) = 0 ;
	virtual void * __cdecl numberWithFloat(float value) = 0 ;
	virtual void * __cdecl numberWithInt(int value) = 0 ;
	virtual void * __cdecl numberWithInteger(long value) = 0 ;
	virtual void * __cdecl numberWithLong(long value) = 0 ;
	virtual void * __cdecl numberWithLongLong(__int64 value) = 0 ;
	virtual void * __cdecl numberWithShort(short value) = 0 ;
	virtual void * __cdecl numberWithUnsignedChar(System::Byte value) = 0 ;
	virtual void * __cdecl numberWithUnsignedInt(unsigned value) = 0 ;
	virtual void * __cdecl numberWithUnsignedInteger(unsigned long value) = 0 ;
	virtual void * __cdecl numberWithUnsignedLong(unsigned long value) = 0 ;
	virtual void * __cdecl numberWithUnsignedLongLong(unsigned __int64 value) = 0 ;
	virtual void * __cdecl numberWithUnsignedShort(System::Word value) = 0 ;
};

__interface  INTERFACE_UUID("{547076CE-9409-4389-B449-47DA1D9718EF}") NSNumber  : public NSValue 
{
	virtual bool __cdecl boolValue() = 0 ;
	virtual System::WideChar __cdecl charValue() = 0 ;
	virtual long __cdecl compare(_di_NSNumber otherNumber) = 0 ;
	virtual NSDecimal __cdecl decimalValue() = 0 ;
	virtual _di_NSString __cdecl descriptionWithLocale(void * locale) = 0 ;
	virtual double __cdecl doubleValue() = 0 ;
	virtual float __cdecl floatValue() = 0 ;
	virtual void * __cdecl initWithBool(bool value) = 0 ;
	virtual void * __cdecl initWithChar(System::WideChar value) = 0 ;
	virtual void * __cdecl initWithDouble(double value) = 0 ;
	virtual void * __cdecl initWithFloat(float value) = 0 ;
	virtual void * __cdecl initWithInt(int value) = 0 ;
	virtual void * __cdecl initWithInteger(long value) = 0 ;
	virtual void * __cdecl initWithLong(long value) = 0 ;
	virtual void * __cdecl initWithLongLong(__int64 value) = 0 ;
	virtual void * __cdecl initWithShort(short value) = 0 ;
	virtual void * __cdecl initWithUnsignedChar(System::Byte value) = 0 ;
	virtual void * __cdecl initWithUnsignedInt(unsigned value) = 0 ;
	virtual void * __cdecl initWithUnsignedInteger(unsigned long value) = 0 ;
	virtual void * __cdecl initWithUnsignedLong(unsigned long value) = 0 ;
	virtual void * __cdecl initWithUnsignedLongLong(unsigned __int64 value) = 0 ;
	virtual void * __cdecl initWithUnsignedShort(System::Word value) = 0 ;
	virtual int __cdecl intValue() = 0 ;
	virtual long __cdecl integerValue() = 0 ;
	virtual bool __cdecl isEqualToNumber(_di_NSNumber number) = 0 ;
	virtual __int64 __cdecl longLongValue() = 0 ;
	virtual long __cdecl longValue() = 0 ;
	virtual short __cdecl shortValue() = 0 ;
	virtual _di_NSString __cdecl stringValue() = 0 ;
	virtual System::Byte __cdecl unsignedCharValue() = 0 ;
	virtual unsigned __cdecl unsignedIntValue() = 0 ;
	virtual unsigned long __cdecl unsignedIntegerValue() = 0 ;
	virtual unsigned __int64 __cdecl unsignedLongLongValue() = 0 ;
	virtual unsigned long __cdecl unsignedLongValue() = 0 ;
	virtual System::Word __cdecl unsignedShortValue() = 0 ;
};

class PASCALIMPLEMENTATION TNSNumber : public Macapi::Objectivec::TOCGenericImport__2<_di_NSNumberClass,_di_NSNumber>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSNumberClass,_di_NSNumber> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSNumber(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSNumberClass,_di_NSNumber>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSNumber() { }
	
};


__interface  INTERFACE_UUID("{D59C5AA0-FAFC-4F5D-A86C-CB8299298413}") NSMutableDataClass  : public NSDataClass 
{
	virtual void * __cdecl dataWithCapacity(unsigned long aNumItems) = 0 ;
	virtual void * __cdecl dataWithLength(unsigned long length) = 0 ;
};

__interface  INTERFACE_UUID("{FE359B3B-16C3-4EC1-9912-C9DAB084D827}") NSMutableData  : public NSData 
{
	virtual void __cdecl appendBytes(void * bytes, unsigned long length) = 0 ;
	virtual void __cdecl appendData(_di_NSData other) = 0 ;
	virtual void __cdecl increaseLengthBy(unsigned long extraLength) = 0 ;
	virtual void * __cdecl initWithCapacity(unsigned long capacity) = 0 ;
	virtual void * __cdecl initWithLength(unsigned long length) = 0 ;
	virtual void * __cdecl mutableBytes() = 0 ;
	virtual void __cdecl replaceBytesInRange(NSRange range, void * withBytes) = 0 /* overload */;
	virtual void __cdecl replaceBytesInRange(NSRange range, void * withBytes, unsigned long length) = 0 /* overload */;
	virtual void __cdecl resetBytesInRange(NSRange range) = 0 ;
	virtual void __cdecl setData(_di_NSData data) = 0 ;
	virtual void __cdecl setLength(unsigned long length) = 0 ;
};

class PASCALIMPLEMENTATION TNSMutableData : public Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableDataClass,_di_NSMutableData>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableDataClass,_di_NSMutableData> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSMutableData(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableDataClass,_di_NSMutableData>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSMutableData() { }
	
};


__interface  INTERFACE_UUID("{AC618765-16E8-4507-B8EB-66DF1702CF84}") NSMutableCharacterSetClass  : public NSCharacterSetClass 
{
	
};

__interface  INTERFACE_UUID("{EB87C54C-F16F-4FEF-9F75-64FD2F0926F4}") NSMutableCharacterSet  : public NSCharacterSet 
{
	virtual void __cdecl addCharactersInRange(NSRange aRange) = 0 ;
	virtual void __cdecl addCharactersInString(_di_NSString aString) = 0 ;
	virtual void __cdecl formIntersectionWithCharacterSet(_di_NSCharacterSet otherSet) = 0 ;
	virtual void __cdecl formUnionWithCharacterSet(_di_NSCharacterSet otherSet) = 0 ;
	virtual void __cdecl invert() = 0 ;
	virtual void __cdecl removeCharactersInRange(NSRange aRange) = 0 ;
	virtual void __cdecl removeCharactersInString(_di_NSString aString) = 0 ;
};

class PASCALIMPLEMENTATION TNSMutableCharacterSet : public Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableCharacterSetClass,_di_NSMutableCharacterSet>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableCharacterSetClass,_di_NSMutableCharacterSet> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSMutableCharacterSet(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableCharacterSetClass,_di_NSMutableCharacterSet>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSMutableCharacterSet() { }
	
};


__interface  INTERFACE_UUID("{C6ED1E21-1F3C-4109-9277-710F12D40EF7}") NSMutableAttributedStringClass  : public NSAttributedStringClass 
{
	
};

__interface  INTERFACE_UUID("{469A5ABD-EC5A-4667-A228-AAEFFD710631}") NSMutableAttributedString  : public NSAttributedString 
{
	virtual void __cdecl addAttribute(_di_NSString name, void * value, NSRange range) = 0 ;
	virtual void __cdecl addAttributes(_di_NSDictionary attrs, NSRange range) = 0 ;
	virtual void __cdecl appendAttributedString(_di_NSAttributedString attrString) = 0 ;
	virtual void __cdecl beginEditing() = 0 ;
	virtual void __cdecl deleteCharactersInRange(NSRange range) = 0 ;
	virtual void __cdecl endEditing() = 0 ;
	virtual void __cdecl insertAttributedString(_di_NSAttributedString attrString, unsigned long atIndex) = 0 ;
	virtual _di_NSMutableString __cdecl mutableString() = 0 ;
	virtual void __cdecl removeAttribute(_di_NSString name, NSRange range) = 0 ;
	virtual void __cdecl replaceCharactersInRange(NSRange range, _di_NSAttributedString withAttributedString) = 0 /* overload */;
	virtual void __cdecl replaceCharactersInRange(NSRange range, _di_NSString withString) = 0 /* overload */;
	virtual void __cdecl setAttributedString(_di_NSAttributedString attrString) = 0 ;
	virtual void __cdecl setAttributes(_di_NSDictionary attrs, NSRange range) = 0 ;
};

class PASCALIMPLEMENTATION TNSMutableAttributedString : public Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableAttributedStringClass,_di_NSMutableAttributedString>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableAttributedStringClass,_di_NSMutableAttributedString> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSMutableAttributedString(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableAttributedStringClass,_di_NSMutableAttributedString>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSMutableAttributedString() { }
	
};


__interface  INTERFACE_UUID("{99BDB475-B46E-4A68-8D4C-94EB9B2DA1A0}") NSMutableDictionaryClass  : public NSDictionaryClass 
{
	virtual void * __cdecl dictionaryWithCapacity(unsigned long numItems) = 0 ;
};

__interface  INTERFACE_UUID("{C03FBD1C-B89A-4B95-B21F-0E567665B10A}") NSMutableDictionary  : public NSDictionary 
{
	virtual void __cdecl addEntriesFromDictionary(_di_NSDictionary otherDictionary) = 0 ;
	virtual void * __cdecl initWithCapacity(unsigned long numItems) = 0 ;
	virtual void __cdecl removeAllObjects() = 0 ;
	virtual void __cdecl removeObjectForKey(void * aKey) = 0 ;
	virtual void __cdecl removeObjectsForKeys(_di_NSArray keyArray) = 0 ;
	virtual void __cdecl setDictionary(_di_NSDictionary otherDictionary) = 0 ;
	virtual void __cdecl setObject(void * anObject, void * forKey) = 0 ;
	virtual void __cdecl setValue(void * value, _di_NSString forKey) = 0 ;
};

class PASCALIMPLEMENTATION TNSMutableDictionary : public Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableDictionaryClass,_di_NSMutableDictionary>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableDictionaryClass,_di_NSMutableDictionary> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSMutableDictionary(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableDictionaryClass,_di_NSMutableDictionary>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSMutableDictionary() { }
	
};


__interface  INTERFACE_UUID("{CA252F5F-42EC-4F9B-A149-B8FF6073B440}") NSMutableOrderedSetClass  : public NSOrderedSetClass 
{
	virtual void * __cdecl orderedSetWithCapacity(unsigned long numItems) = 0 ;
};

__interface  INTERFACE_UUID("{7B781355-2096-4665-AB2F-73F268D58961}") NSMutableOrderedSet  : public NSOrderedSet 
{
	virtual void __cdecl addObject(void * object_) = 0 ;
	virtual void __cdecl addObjects(void * objects, unsigned long count) = 0 ;
	virtual void __cdecl addObjectsFromArray(_di_NSArray array_) = 0 ;
	virtual void __cdecl exchangeObjectAtIndex(unsigned long idx1, unsigned long withObjectAtIndex) = 0 ;
	virtual void * __cdecl initWithCapacity(unsigned long numItems) = 0 ;
	virtual void __cdecl insertObject(void * object_, unsigned long atIndex) = 0 ;
	virtual void __cdecl insertObjects(_di_NSArray objects, _di_NSIndexSet atIndexes) = 0 ;
	virtual void __cdecl intersectOrderedSet(_di_NSOrderedSet other) = 0 ;
	virtual void __cdecl intersectSet(_di_NSSet other) = 0 ;
	virtual void __cdecl minusOrderedSet(_di_NSOrderedSet other) = 0 ;
	virtual void __cdecl minusSet(_di_NSSet other) = 0 ;
	virtual void __cdecl moveObjectsAtIndexes(_di_NSIndexSet indexes, unsigned long toIndex) = 0 ;
	virtual void __cdecl removeAllObjects() = 0 ;
	virtual void __cdecl removeObject(void * object_) = 0 ;
	virtual void __cdecl removeObjectAtIndex(unsigned long idx) = 0 ;
	virtual void __cdecl removeObjectsAtIndexes(_di_NSIndexSet indexes) = 0 ;
	virtual void __cdecl removeObjectsInArray(_di_NSArray array_) = 0 ;
	virtual void __cdecl removeObjectsInRange(NSRange range) = 0 ;
	virtual void __cdecl replaceObjectAtIndex(unsigned long idx, void * withObject) = 0 ;
	virtual void __cdecl replaceObjectsAtIndexes(_di_NSIndexSet indexes, _di_NSArray withObjects) = 0 ;
	virtual void __cdecl replaceObjectsInRange(NSRange range, void * withObjects, unsigned long count) = 0 ;
	virtual void __cdecl setObject(void * obj, unsigned long atIndex) = 0 ;
	virtual void __cdecl unionOrderedSet(_di_NSOrderedSet other) = 0 ;
	virtual void __cdecl unionSet(_di_NSSet other) = 0 ;
};

class PASCALIMPLEMENTATION TNSMutableOrderedSet : public Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableOrderedSetClass,_di_NSMutableOrderedSet>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableOrderedSetClass,_di_NSMutableOrderedSet> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSMutableOrderedSet(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableOrderedSetClass,_di_NSMutableOrderedSet>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSMutableOrderedSet() { }
	
};


__interface  INTERFACE_UUID("{73C480DD-4EF5-421E-81C4-151DEE3B0D0F}") NSMutableIndexSetClass  : public NSIndexSetClass 
{
	
};

__interface  INTERFACE_UUID("{77C90236-5A11-4BD2-9371-1ED064FD5B27}") NSMutableIndexSet  : public NSIndexSet 
{
	virtual void __cdecl addIndex(unsigned long value) = 0 ;
	virtual void __cdecl addIndexes(_di_NSIndexSet indexSet) = 0 ;
	virtual void __cdecl addIndexesInRange(NSRange range) = 0 ;
	virtual void __cdecl removeAllIndexes() = 0 ;
	virtual void __cdecl removeIndex(unsigned long value) = 0 ;
	virtual void __cdecl removeIndexes(_di_NSIndexSet indexSet) = 0 ;
	virtual void __cdecl removeIndexesInRange(NSRange range) = 0 ;
	virtual void __cdecl shiftIndexesStartingAtIndex(unsigned long index, long by) = 0 ;
};

class PASCALIMPLEMENTATION TNSMutableIndexSet : public Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableIndexSetClass,_di_NSMutableIndexSet>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableIndexSetClass,_di_NSMutableIndexSet> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSMutableIndexSet(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSMutableIndexSetClass,_di_NSMutableIndexSet>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSMutableIndexSet() { }
	
};


__interface  INTERFACE_UUID("{E09CF650-F47E-4E87-B682-6974D345A40C}") NSCountedSetClass  : public NSMutableSetClass 
{
	
};

__interface  INTERFACE_UUID("{74B496BA-3AAC-4529-A936-2AF76731072A}") NSCountedSet  : public NSMutableSet 
{
	HIDESBASE virtual void __cdecl addObject(void * object_) = 0 ;
	virtual unsigned long __cdecl countForObject(void * object_) = 0 ;
	HIDESBASE virtual void * __cdecl initWithArray(_di_NSArray array_) = 0 ;
	HIDESBASE virtual void * __cdecl initWithCapacity(unsigned long numItems) = 0 ;
	HIDESBASE virtual void * __cdecl initWithSet(_di_NSSet set_) = 0 ;
	HIDESBASE virtual _di_NSEnumerator __cdecl objectEnumerator() = 0 ;
	HIDESBASE virtual void __cdecl removeObject(void * object_) = 0 ;
};

class PASCALIMPLEMENTATION TNSCountedSet : public Macapi::Objectivec::TOCGenericImport__2<_di_NSCountedSetClass,_di_NSCountedSet>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSCountedSetClass,_di_NSCountedSet> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSCountedSet(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSCountedSetClass,_di_NSCountedSet>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSCountedSet() { }
	
};


__interface  INTERFACE_UUID("{E41F598D-6651-44B9-98F5-624D607FD89E}") NSDecimalNumberClass  : public NSNumberClass 
{
	virtual void * __cdecl decimalNumberWithDecimal(NSDecimal dcm) = 0 ;
	virtual void * __cdecl decimalNumberWithMantissa(unsigned __int64 mantissa, short exponent, bool isNegative) = 0 ;
	virtual void * __cdecl decimalNumberWithString(_di_NSString numberValue) = 0 /* overload */;
	virtual void * __cdecl decimalNumberWithString(_di_NSString numberValue, void * locale) = 0 /* overload */;
	virtual void * __cdecl defaultBehavior() = 0 ;
	virtual void * __cdecl maximumDecimalNumber() = 0 ;
	virtual void * __cdecl minimumDecimalNumber() = 0 ;
	virtual void * __cdecl notANumber() = 0 ;
	virtual void * __cdecl one() = 0 ;
	virtual void __cdecl setDefaultBehavior(void * behavior) = 0 ;
	virtual void * __cdecl zero() = 0 ;
};

__interface  INTERFACE_UUID("{A141A5E9-C247-41C1-B677-787F77B700AC}") NSDecimalNumber  : public NSNumber 
{
	HIDESBASE virtual long __cdecl compare(_di_NSNumber decimalNumber) = 0 ;
	virtual _di_NSDecimalNumber __cdecl decimalNumberByAdding(_di_NSDecimalNumber decimalNumber) = 0 /* overload */;
	virtual _di_NSDecimalNumber __cdecl decimalNumberByAdding(_di_NSDecimalNumber decimalNumber, void * withBehavior) = 0 /* overload */;
	virtual _di_NSDecimalNumber __cdecl decimalNumberByDividingBy(_di_NSDecimalNumber decimalNumber) = 0 /* overload */;
	virtual _di_NSDecimalNumber __cdecl decimalNumberByDividingBy(_di_NSDecimalNumber decimalNumber, void * withBehavior) = 0 /* overload */;
	virtual _di_NSDecimalNumber __cdecl decimalNumberByMultiplyingBy(_di_NSDecimalNumber decimalNumber) = 0 /* overload */;
	virtual _di_NSDecimalNumber __cdecl decimalNumberByMultiplyingBy(_di_NSDecimalNumber decimalNumber, void * withBehavior) = 0 /* overload */;
	virtual _di_NSDecimalNumber __cdecl decimalNumberByMultiplyingByPowerOf10(short power) = 0 /* overload */;
	virtual _di_NSDecimalNumber __cdecl decimalNumberByMultiplyingByPowerOf10(short power, void * withBehavior) = 0 /* overload */;
	virtual _di_NSDecimalNumber __cdecl decimalNumberByRaisingToPower(unsigned long power) = 0 /* overload */;
	virtual _di_NSDecimalNumber __cdecl decimalNumberByRaisingToPower(unsigned long power, void * withBehavior) = 0 /* overload */;
	virtual _di_NSDecimalNumber __cdecl decimalNumberByRoundingAccordingToBehavior(void * behavior) = 0 ;
	virtual _di_NSDecimalNumber __cdecl decimalNumberBySubtracting(_di_NSDecimalNumber decimalNumber) = 0 /* overload */;
	virtual _di_NSDecimalNumber __cdecl decimalNumberBySubtracting(_di_NSDecimalNumber decimalNumber, void * withBehavior) = 0 /* overload */;
	HIDESBASE virtual NSDecimal __cdecl decimalValue() = 0 ;
	HIDESBASE virtual _di_NSString __cdecl descriptionWithLocale(void * locale) = 0 ;
	HIDESBASE virtual double __cdecl doubleValue() = 0 ;
	virtual void * __cdecl initWithDecimal(NSDecimal dcm) = 0 ;
	virtual void * __cdecl initWithMantissa(unsigned __int64 mantissa, short exponent, bool isNegative) = 0 ;
	virtual void * __cdecl initWithString(_di_NSString numberValue) = 0 /* overload */;
	virtual void * __cdecl initWithString(_di_NSString numberValue, void * locale) = 0 /* overload */;
	HIDESBASE virtual char * __cdecl objCType() = 0 ;
};

class PASCALIMPLEMENTATION TNSDecimalNumber : public Macapi::Objectivec::TOCGenericImport__2<_di_NSDecimalNumberClass,_di_NSDecimalNumber>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSDecimalNumberClass,_di_NSDecimalNumber> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSDecimalNumber(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSDecimalNumberClass,_di_NSDecimalNumber>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSDecimalNumber() { }
	
};


__interface  INTERFACE_UUID("{E46675F8-A60F-4ED3-A168-12D3B381B913}") NSUUIDClass  : public NSObjectClass 
{
	virtual void * __cdecl UUID() = 0 ;
};

__interface  INTERFACE_UUID("{A6E35A1D-0491-4918-9B50-7CAF9F66B2AD}") NSUUID  : public NSObject 
{
	HIDESBASE virtual _di_NSUUID __cdecl init() = 0 ;
	virtual _di_NSUUID __cdecl initWithUUIDBytes() = 0 ;
	virtual _di_NSUUID __cdecl initWithUUIDString(_di_NSString string_) = 0 ;
	virtual _di_NSString __cdecl UUIDString() = 0 ;
	virtual void __cdecl getUUIDBytes(System::PByte uuid) = 0 ;
};

class PASCALIMPLEMENTATION TNSUUID : public Macapi::Objectivec::TOCGenericImport__2<_di_NSUUIDClass,_di_NSUUID>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSUUIDClass,_di_NSUUID> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSUUID(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSUUIDClass,_di_NSUUID>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSUUID() { }
	
};


__interface  INTERFACE_UUID("{CDD1C932-3FE3-40C7-8296-04718D157B0B}") NSURLComponentsClass  : public NSObjectClass 
{
	virtual void * __cdecl componentsWithURL(_di_NSURL url, bool resolvingAgainstBaseURL) = 0 ;
	virtual void * __cdecl componentsWithString(_di_NSString URLString) = 0 ;
};

__interface  INTERFACE_UUID("{23722A70-A973-4DD3-9313-C00A692DC94B}") NSURLComponents  : public NSObject 
{
	HIDESBASE virtual void * __cdecl init() = 0 ;
	virtual void * __cdecl initWithURL(_di_NSURL url, bool resolvingAgainstBaseURL) = 0 ;
	virtual void * __cdecl initWithString(_di_NSString URLString) = 0 ;
	virtual _di_NSURL __cdecl url() = 0 ;
	virtual _di_NSURL __cdecl URLRelativeToURL(_di_NSURL baseURL) = 0 ;
	virtual void __cdecl setScheme(_di_NSString scheme) = 0 ;
	virtual _di_NSString __cdecl scheme() = 0 ;
	virtual void __cdecl setUser(_di_NSString user) = 0 ;
	virtual _di_NSString __cdecl user() = 0 ;
	virtual void __cdecl setPassword(_di_NSString password) = 0 ;
	virtual _di_NSString __cdecl password() = 0 ;
	virtual void __cdecl setHost(_di_NSString host) = 0 ;
	virtual _di_NSString __cdecl host() = 0 ;
	virtual void __cdecl setPort(_di_NSNumber port) = 0 ;
	virtual _di_NSNumber __cdecl port() = 0 ;
	virtual void __cdecl setPath(_di_NSString path) = 0 ;
	virtual _di_NSString __cdecl path() = 0 ;
	virtual void __cdecl setQuery(_di_NSString query) = 0 ;
	virtual _di_NSString __cdecl query() = 0 ;
	virtual void __cdecl setFragment(_di_NSString fragment) = 0 ;
	virtual _di_NSString __cdecl fragment() = 0 ;
	virtual void __cdecl setPercentEncodedUser(_di_NSString percentEncodedUser) = 0 ;
	virtual _di_NSString __cdecl percentEncodedUser() = 0 ;
	virtual void __cdecl setPercentEncodedPassword(_di_NSString percentEncodedPassword) = 0 ;
	virtual _di_NSString __cdecl percentEncodedPassword() = 0 ;
	virtual void __cdecl setPercentEncodedHost(_di_NSString percentEncodedHost) = 0 ;
	virtual _di_NSString __cdecl percentEncodedHost() = 0 ;
	virtual void __cdecl setPercentEncodedPath(_di_NSString percentEncodedPath) = 0 ;
	virtual _di_NSString __cdecl percentEncodedPath() = 0 ;
	virtual void __cdecl setPercentEncodedQuery(_di_NSString percentEncodedQuery) = 0 ;
	virtual _di_NSString __cdecl percentEncodedQuery() = 0 ;
	virtual void __cdecl setPercentEncodedFragment(_di_NSString percentEncodedFragment) = 0 ;
	virtual _di_NSString __cdecl percentEncodedFragment() = 0 ;
};

class PASCALIMPLEMENTATION TNSURLComponents : public Macapi::Objectivec::TOCGenericImport__2<_di_NSURLComponentsClass,_di_NSURLComponents>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSURLComponentsClass,_di_NSURLComponents> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSURLComponents(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSURLComponentsClass,_di_NSURLComponents>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSURLComponents() { }
	
};


__interface  INTERFACE_UUID("{B317314F-9614-45B8-8333-A928577FFED1}") NSURLSessionClass  : public NSObjectClass 
{
	virtual _di_NSURLSession __cdecl sharedSession() = 0 ;
	virtual _di_NSURLSession __cdecl sessionWithConfiguration(_di_NSURLSessionConfiguration configuration) = 0 ;
	virtual _di_NSURLSession __cdecl sessionWithConfigurationDelegateDelegateQueue(_di_NSURLSessionConfiguration configuration, void * delegate, _di_NSOperationQueue delegateQueue) = 0 ;
};

__interface  INTERFACE_UUID("{3A2E70E8-D4B5-4FC0-943E-F9EB9E0F0876}") NSURLSession  : public NSObject 
{
	virtual _di_NSOperationQueue __cdecl delegateQueue() = 0 ;
	virtual void * __cdecl delegate() = 0 ;
	virtual _di_NSURLSessionConfiguration __cdecl configuration() = 0 ;
	virtual void __cdecl setSessionDescription(_di_NSString sessionDescription) = 0 ;
	virtual _di_NSString __cdecl sessionDescription() = 0 ;
	virtual void __cdecl finishTasksAndInvalidate() = 0 ;
	virtual void __cdecl invalidateAndCancel() = 0 ;
	virtual void __cdecl resetWithCompletionHandler(TFoundationCompletionBlock completionHandler) = 0 ;
	virtual void __cdecl flushWithCompletionHandler(TFoundationCompletionBlock completionHandler) = 0 ;
	virtual void __cdecl getTasksWithCompletionHandler(TFoundationCompletionHandler2 completionHandler) = 0 ;
	virtual _di_NSURLSessionDataTask __cdecl dataTaskWithRequest(_di_NSURLRequest request) = 0 ;
	virtual _di_NSURLSessionDataTask __cdecl dataTaskWithURL(_di_NSURL url) = 0 ;
	virtual _di_NSURLSessionUploadTask __cdecl uploadTaskWithRequestFromFile(_di_NSURLRequest request, _di_NSURL fromFile) = 0 ;
	virtual _di_NSURLSessionUploadTask __cdecl uploadTaskWithRequestFromData(_di_NSURLRequest request, _di_NSData fromData) = 0 ;
	virtual _di_NSURLSessionUploadTask __cdecl uploadTaskWithStreamedRequest(_di_NSURLRequest request) = 0 ;
	virtual _di_NSURLSessionDownloadTask __cdecl downloadTaskWithRequest(_di_NSURLRequest request) = 0 ;
	virtual _di_NSURLSessionDownloadTask __cdecl downloadTaskWithURL(_di_NSURL url) = 0 ;
	virtual _di_NSURLSessionDownloadTask __cdecl downloadTaskWithResumeData(_di_NSData resumeData) = 0 ;
	virtual _di_NSURLSessionDataTask __cdecl dataTaskWithRequestCompletionHandler(_di_NSURLRequest request, TFoundationCompletionHandler3 completionHandler) = 0 ;
	virtual _di_NSURLSessionDataTask __cdecl dataTaskWithURLCompletionHandler(_di_NSURL url, TFoundationCompletionHandler3 completionHandler) = 0 ;
	virtual _di_NSURLSessionUploadTask __cdecl uploadTaskWithRequestFromFileCompletionHandler(_di_NSURLRequest request, _di_NSURL fromFile, TFoundationCompletionHandler3 completionHandler) = 0 ;
	virtual _di_NSURLSessionUploadTask __cdecl uploadTaskWithRequestFromDataCompletionHandler(_di_NSURLRequest request, _di_NSData fromData, TFoundationCompletionHandler3 completionHandler) = 0 ;
	virtual _di_NSURLSessionDownloadTask __cdecl downloadTaskWithRequestCompletionHandler(_di_NSURLRequest request, TFoundationCompletionHandler4 completionHandler) = 0 ;
	virtual _di_NSURLSessionDownloadTask __cdecl downloadTaskWithURLCompletionHandler(_di_NSURL url, TFoundationCompletionHandler4 completionHandler) = 0 ;
	virtual _di_NSURLSessionDownloadTask __cdecl downloadTaskWithResumeDataCompletionHandler(_di_NSData resumeData, TFoundationCompletionHandler4 completionHandler) = 0 ;
	virtual _di_NSURLSessionDataTask __cdecl dataTaskWithHTTPGetRequest(_di_NSURL url) = 0 ;
	virtual _di_NSURLSessionDataTask __cdecl dataTaskWithHTTPGetRequestCompletionHandler(_di_NSURL url, TFoundationCompletionHandler3 completionHandler) = 0 ;
};

class PASCALIMPLEMENTATION TNSURLSession : public Macapi::Objectivec::TOCGenericImport__2<_di_NSURLSessionClass,_di_NSURLSession>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSURLSessionClass,_di_NSURLSession> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSURLSession(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSURLSessionClass,_di_NSURLSession>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSURLSession() { }
	
};


__interface  INTERFACE_UUID("{28E43E7B-CBB6-4EF6-AAB7-168E2BF4C903}") NSURLSessionTaskClass  : public NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{D8069D47-61A5-41EB-8E18-005AB0DE4775}") NSURLSessionTask  : public NSObject 
{
	virtual unsigned long __cdecl taskIdentifier() = 0 ;
	virtual _di_NSURLRequest __cdecl originalRequest() = 0 ;
	virtual _di_NSURLRequest __cdecl currentRequest() = 0 ;
	virtual _di_NSURLResponse __cdecl response() = 0 ;
	virtual __int64 __cdecl countOfBytesReceived() = 0 ;
	virtual __int64 __cdecl countOfBytesSent() = 0 ;
	virtual __int64 __cdecl countOfBytesExpectedToSend() = 0 ;
	virtual __int64 __cdecl countOfBytesExpectedToReceive() = 0 ;
	virtual void __cdecl setTaskDescription(_di_NSString taskDescription) = 0 ;
	virtual _di_NSString __cdecl taskDescription() = 0 ;
	virtual void __cdecl cancel() = 0 ;
	virtual long __cdecl state() = 0 ;
	virtual _di_NSError __cdecl error() = 0 ;
	virtual void __cdecl suspend() = 0 ;
	virtual void __cdecl resume() = 0 ;
};

class PASCALIMPLEMENTATION TNSURLSessionTask : public Macapi::Objectivec::TOCGenericImport__2<_di_NSURLSessionTaskClass,_di_NSURLSessionTask>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSURLSessionTaskClass,_di_NSURLSessionTask> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSURLSessionTask(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSURLSessionTaskClass,_di_NSURLSessionTask>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSURLSessionTask() { }
	
};


__interface  INTERFACE_UUID("{15D58131-2A0A-49DC-92DF-845A1C7A7C28}") NSURLSessionDataTaskClass  : public NSURLSessionTaskClass 
{
	
};

__interface  INTERFACE_UUID("{E07AC982-D3E2-4FFB-BD3A-1B9B0EE086EE}") NSURLSessionDataTask  : public NSURLSessionTask 
{
	
};

class PASCALIMPLEMENTATION TNSURLSessionDataTask : public Macapi::Objectivec::TOCGenericImport__2<_di_NSURLSessionDataTaskClass,_di_NSURLSessionDataTask>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSURLSessionDataTaskClass,_di_NSURLSessionDataTask> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSURLSessionDataTask(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSURLSessionDataTaskClass,_di_NSURLSessionDataTask>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSURLSessionDataTask() { }
	
};


__interface  INTERFACE_UUID("{8F15823A-D4B0-41AE-9AB0-E3AD00CAFB71}") NSURLSessionUploadTaskClass  : public NSURLSessionDataTaskClass 
{
	
};

__interface  INTERFACE_UUID("{357766E6-712E-4BE4-ACB5-45B452188A82}") NSURLSessionUploadTask  : public NSURLSessionDataTask 
{
	
};

class PASCALIMPLEMENTATION TNSURLSessionUploadTask : public Macapi::Objectivec::TOCGenericImport__2<_di_NSURLSessionUploadTaskClass,_di_NSURLSessionUploadTask>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSURLSessionUploadTaskClass,_di_NSURLSessionUploadTask> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSURLSessionUploadTask(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSURLSessionUploadTaskClass,_di_NSURLSessionUploadTask>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSURLSessionUploadTask() { }
	
};


__interface  INTERFACE_UUID("{C1A4E605-2364-477B-9E65-BAEDD2213D11}") NSURLSessionDownloadTaskClass  : public NSURLSessionTaskClass 
{
	
};

__interface  INTERFACE_UUID("{ADBBDFF5-3EC5-4131-A6C1-B3F6840553A9}") NSURLSessionDownloadTask  : public NSURLSessionTask 
{
	virtual void __cdecl cancelByProducingResumeData(TFoundationCompletionHandler5 completionHandler) = 0 ;
};

class PASCALIMPLEMENTATION TNSURLSessionDownloadTask : public Macapi::Objectivec::TOCGenericImport__2<_di_NSURLSessionDownloadTaskClass,_di_NSURLSessionDownloadTask>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSURLSessionDownloadTaskClass,_di_NSURLSessionDownloadTask> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSURLSessionDownloadTask(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSURLSessionDownloadTaskClass,_di_NSURLSessionDownloadTask>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSURLSessionDownloadTask() { }
	
};


__interface  INTERFACE_UUID("{298D2352-F6BA-40E4-8320-A3CFBD87F1C3}") NSURLSessionConfigurationClass  : public NSObjectClass 
{
	virtual _di_NSURLSessionConfiguration __cdecl defaultSessionConfiguration() = 0 ;
	virtual _di_NSURLSessionConfiguration __cdecl ephemeralSessionConfiguration() = 0 ;
	virtual _di_NSURLSessionConfiguration __cdecl backgroundSessionConfiguration(_di_NSString identifier) = 0 ;
};

__interface  INTERFACE_UUID("{F410845C-ADC0-4D66-8546-2CDE27137C52}") NSURLSessionConfiguration  : public NSObject 
{
	virtual _di_NSString __cdecl identifier() = 0 ;
	virtual void __cdecl setRequestCachePolicy(unsigned long requestCachePolicy) = 0 ;
	virtual unsigned long __cdecl requestCachePolicy() = 0 ;
	virtual void __cdecl setTimeoutIntervalForRequest(double timeoutIntervalForRequest) = 0 ;
	virtual double __cdecl timeoutIntervalForRequest() = 0 ;
	virtual void __cdecl setTimeoutIntervalForResource(double timeoutIntervalForResource) = 0 ;
	virtual double __cdecl timeoutIntervalForResource() = 0 ;
	virtual void __cdecl setNetworkServiceType(unsigned long networkServiceType) = 0 ;
	virtual unsigned long __cdecl networkServiceType() = 0 ;
	virtual void __cdecl setAllowsCellularAccess(bool allowsCellularAccess) = 0 ;
	virtual bool __cdecl allowsCellularAccess() = 0 ;
	virtual void __cdecl setDiscretionary(bool discretionary) = 0 ;
	virtual bool __cdecl isDiscretionary() = 0 ;
	virtual void __cdecl setSessionSendsLaunchEvents(bool sessionSendsLaunchEvents) = 0 ;
	virtual bool __cdecl sessionSendsLaunchEvents() = 0 ;
	virtual void __cdecl setConnectionProxyDictionary(_di_NSDictionary connectionProxyDictionary) = 0 ;
	virtual _di_NSDictionary __cdecl connectionProxyDictionary() = 0 ;
	virtual void __cdecl setTLSMinimumSupportedProtocol(unsigned TLSMinimumSupportedProtocol) = 0 ;
	virtual unsigned __cdecl TLSMinimumSupportedProtocol() = 0 ;
	virtual void __cdecl setTLSMaximumSupportedProtocol(unsigned TLSMaximumSupportedProtocol) = 0 ;
	virtual unsigned __cdecl TLSMaximumSupportedProtocol() = 0 ;
	virtual void __cdecl setHTTPShouldUsePipelining(bool HTTPShouldUsePipelining) = 0 ;
	virtual bool __cdecl HTTPShouldUsePipelining() = 0 ;
	virtual void __cdecl setHTTPShouldSetCookies(bool HTTPShouldSetCookies) = 0 ;
	virtual bool __cdecl HTTPShouldSetCookies() = 0 ;
	virtual void __cdecl setHTTPCookieAcceptPolicy(unsigned long HTTPCookieAcceptPolicy) = 0 ;
	virtual unsigned long __cdecl HTTPCookieAcceptPolicy() = 0 ;
	virtual void __cdecl setHTTPAdditionalHeaders(_di_NSDictionary HTTPAdditionalHeaders) = 0 ;
	virtual _di_NSDictionary __cdecl HTTPAdditionalHeaders() = 0 ;
	virtual void __cdecl setHTTPMaximumConnectionsPerHost(long HTTPMaximumConnectionsPerHost) = 0 ;
	virtual long __cdecl HTTPMaximumConnectionsPerHost() = 0 ;
	virtual void __cdecl setHTTPCookieStorage(_di_NSHTTPCookieStorage HTTPCookieStorage) = 0 ;
	virtual _di_NSHTTPCookieStorage __cdecl HTTPCookieStorage() = 0 ;
	virtual void __cdecl setURLCredentialStorage(_di_NSURLCredentialStorage URLCredentialStorage) = 0 ;
	virtual _di_NSURLCredentialStorage __cdecl URLCredentialStorage() = 0 ;
	virtual void __cdecl setURLCache(_di_NSURLCache URLCache) = 0 ;
	virtual _di_NSURLCache __cdecl URLCache() = 0 ;
	virtual void __cdecl setProtocolClasses(_di_NSArray protocolClasses) = 0 ;
	virtual _di_NSArray __cdecl protocolClasses() = 0 ;
};

class PASCALIMPLEMENTATION TNSURLSessionConfiguration : public Macapi::Objectivec::TOCGenericImport__2<_di_NSURLSessionConfigurationClass,_di_NSURLSessionConfiguration>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_NSURLSessionConfigurationClass,_di_NSURLSessionConfiguration> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TNSURLSessionConfiguration(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_NSURLSessionConfigurationClass,_di_NSURLSessionConfiguration>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TNSURLSessionConfiguration() { }
	
};


__interface  INTERFACE_UUID("{6183127B-C011-4400-908E-2434EFEDC851}") NSCopying  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void * __cdecl copyWithZone(void * zone) = 0 ;
};

__interface  INTERFACE_UUID("{CB815D94-B488-493B-A62C-9BB4FE62F7CC}") NSMutableCopying  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void * __cdecl mutableCopyWithZone(void * zone) = 0 ;
};

__interface  INTERFACE_UUID("{5EA2673A-9D64-408B-A182-0B6AFE77BF54}") NSCoding  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl encodeWithCoder(_di_NSCoder aCoder) = 0 ;
	virtual void * __cdecl initWithCoder(_di_NSCoder aDecoder) = 0 ;
};

__interface  INTERFACE_UUID("{85A3C08B-D715-4BD3-AF33-948AD42B35AA}") NSSecureCoding  : public Macapi::Objectivec::IObjectiveC 
{
	virtual bool __cdecl supportsSecureCoding() = 0 ;
};

__interface  INTERFACE_UUID("{863366D0-EB10-4A23-B270-A7A1BCAAE138}") NSDiscardableContent  : public Macapi::Objectivec::IObjectiveC 
{
	virtual bool __cdecl beginContentAccess() = 0 ;
	virtual void __cdecl endContentAccess() = 0 ;
	virtual void __cdecl discardContentIfPossible() = 0 ;
	virtual bool __cdecl isContentDiscarded() = 0 ;
};

__interface  INTERFACE_UUID("{35B10381-FC70-4959-8380-1CB021AABB80}") NSFastEnumeration  : public Macapi::Objectivec::IObjectiveC 
{
	virtual unsigned long __cdecl countByEnumeratingWithState(void * state, void * objects, unsigned long count) = 0 ;
};

__interface  INTERFACE_UUID("{88AFE64D-F4A9-4DC9-9E5D-AFCA337AA075}") NSDecimalNumberBehaviors  : public Macapi::Objectivec::IObjectiveC 
{
	virtual unsigned long __cdecl roundingMode() = 0 ;
	virtual short __cdecl scale() = 0 ;
	virtual _di_NSDecimalNumber __cdecl exceptionDuringOperation(void * operation, unsigned long error, _di_NSDecimalNumber leftOperand, _di_NSDecimalNumber rightOperand) = 0 ;
};

__interface  INTERFACE_UUID("{C8ACB2F3-AF6B-47C7-8CBF-061568F84716}") NSFileManagerDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual bool __cdecl fileManagerShouldCopyItemAtPathToPath(_di_NSFileManager fileManager, _di_NSString shouldCopyItemAtPath, _di_NSString toPath) = 0 ;
	virtual bool __cdecl fileManagerShouldCopyItemAtURLToURL(_di_NSFileManager fileManager, _di_NSURL shouldCopyItemAtURL, _di_NSURL toURL) = 0 ;
	virtual bool __cdecl fileManagerShouldProceedAfterErrorCopyingItemAtPathToPath(_di_NSFileManager fileManager, _di_NSError shouldProceedAfterError, _di_NSString copyingItemAtPath, _di_NSString toPath) = 0 ;
	virtual bool __cdecl fileManagerShouldProceedAfterErrorCopyingItemAtURLToURL(_di_NSFileManager fileManager, _di_NSError shouldProceedAfterError, _di_NSURL copyingItemAtURL, _di_NSURL toURL) = 0 ;
	virtual bool __cdecl fileManagerShouldMoveItemAtPathToPath(_di_NSFileManager fileManager, _di_NSString shouldMoveItemAtPath, _di_NSString toPath) = 0 ;
	virtual bool __cdecl fileManagerShouldMoveItemAtURLToURL(_di_NSFileManager fileManager, _di_NSURL shouldMoveItemAtURL, _di_NSURL toURL) = 0 ;
	virtual bool __cdecl fileManagerShouldProceedAfterErrorMovingItemAtPathToPath(_di_NSFileManager fileManager, _di_NSError shouldProceedAfterError, _di_NSString movingItemAtPath, _di_NSString toPath) = 0 ;
	virtual bool __cdecl fileManagerShouldProceedAfterErrorMovingItemAtURLToURL(_di_NSFileManager fileManager, _di_NSError shouldProceedAfterError, _di_NSURL movingItemAtURL, _di_NSURL toURL) = 0 ;
	virtual bool __cdecl fileManagerShouldLinkItemAtPathToPath(_di_NSFileManager fileManager, _di_NSString shouldLinkItemAtPath, _di_NSString toPath) = 0 ;
	virtual bool __cdecl fileManagerShouldLinkItemAtURLToURL(_di_NSFileManager fileManager, _di_NSURL shouldLinkItemAtURL, _di_NSURL toURL) = 0 ;
	virtual bool __cdecl fileManagerShouldProceedAfterErrorLinkingItemAtPathToPath(_di_NSFileManager fileManager, _di_NSError shouldProceedAfterError, _di_NSString linkingItemAtPath, _di_NSString toPath) = 0 ;
	virtual bool __cdecl fileManagerShouldProceedAfterErrorLinkingItemAtURLToURL(_di_NSFileManager fileManager, _di_NSError shouldProceedAfterError, _di_NSURL linkingItemAtURL, _di_NSURL toURL) = 0 ;
	virtual bool __cdecl fileManagerShouldRemoveItemAtPath(_di_NSFileManager fileManager, _di_NSString shouldRemoveItemAtPath) = 0 ;
	virtual bool __cdecl fileManagerShouldRemoveItemAtURL(_di_NSFileManager fileManager, _di_NSURL shouldRemoveItemAtURL) = 0 ;
	virtual bool __cdecl fileManagerShouldProceedAfterErrorRemovingItemAtPath(_di_NSFileManager fileManager, _di_NSError shouldProceedAfterError, _di_NSString removingItemAtPath) = 0 ;
	virtual bool __cdecl fileManagerShouldProceedAfterErrorRemovingItemAtURL(_di_NSFileManager fileManager, _di_NSError shouldProceedAfterError, _di_NSURL removingItemAtURL) = 0 ;
};

__interface  INTERFACE_UUID("{1718D4CD-1836-40EB-9C66-3F9405332F26}") NSKeyedArchiverDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void * __cdecl archiverWillEncodeObject(_di_NSKeyedArchiver archiver, void * willEncodeObject) = 0 ;
	virtual void __cdecl archiverDidEncodeObject(_di_NSKeyedArchiver archiver, void * didEncodeObject) = 0 ;
	virtual void __cdecl archiverWillReplaceObjectWithObject(_di_NSKeyedArchiver archiver, void * willReplaceObject, void * withObject) = 0 ;
	virtual void __cdecl archiverWillFinish(_di_NSKeyedArchiver archiver) = 0 ;
	virtual void __cdecl archiverDidFinish(_di_NSKeyedArchiver archiver) = 0 ;
};

__interface  INTERFACE_UUID("{FD4DBE87-DC82-447A-93A5-968DE070B136}") NSKeyedUnarchiverDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void * __cdecl unarchiverCannotDecodeObjectOfClassNameOriginalClasses(_di_NSKeyedUnarchiver unarchiver, _di_NSString cannotDecodeObjectOfClassName, _di_NSArray originalClasses) = 0 ;
	virtual void * __cdecl unarchiverDidDecodeObject(_di_NSKeyedUnarchiver unarchiver, void * didDecodeObject) = 0 ;
	virtual void __cdecl unarchiverWillReplaceObjectWithObject(_di_NSKeyedUnarchiver unarchiver, void * willReplaceObject, void * withObject) = 0 ;
	virtual void __cdecl unarchiverWillFinish(_di_NSKeyedUnarchiver unarchiver) = 0 ;
	virtual void __cdecl unarchiverDidFinish(_di_NSKeyedUnarchiver unarchiver) = 0 ;
};

__interface  INTERFACE_UUID("{B543F276-E03A-46C2-BA21-1AEA79066E2F}") NSLocking  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl lock() = 0 ;
	virtual void __cdecl unlock() = 0 ;
};

__interface  INTERFACE_UUID("{E44337DE-5755-441C-A111-08860C63CB2B}") NSMachPortDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl handleMachMessage(void * msg) = 0 ;
};

__interface  INTERFACE_UUID("{4C2D18FF-F413-4FE4-9E54-E6EA2B221E30}") NSStreamDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl stream(_di_NSStream aStream, unsigned long handleEvent) = 0 ;
};

__interface  INTERFACE_UUID("{2F1CE868-3027-452E-8115-D7CF2A6B38DC}") NSURLAuthenticationChallengeSender  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl useCredential(_di_NSURLCredential credential, _di_NSURLAuthenticationChallenge forAuthenticationChallenge) = 0 ;
	virtual void __cdecl continueWithoutCredentialForAuthenticationChallenge(_di_NSURLAuthenticationChallenge challenge) = 0 ;
	virtual void __cdecl cancelAuthenticationChallenge(_di_NSURLAuthenticationChallenge challenge) = 0 ;
	virtual void __cdecl performDefaultHandlingForAuthenticationChallenge(_di_NSURLAuthenticationChallenge challenge) = 0 ;
	virtual void __cdecl rejectProtectionSpaceAndContinueWithChallenge(_di_NSURLAuthenticationChallenge challenge) = 0 ;
};

__interface  INTERFACE_UUID("{1D7FD17E-50A9-486C-9A9C-E6BAFBB7FF9C}") NSURLConnectionDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl connectionDidFailWithError(_di_NSURLConnection connection, _di_NSError didFailWithError) = 0 ;
	virtual bool __cdecl connectionShouldUseCredentialStorage(_di_NSURLConnection connection) = 0 ;
	virtual void __cdecl connectionWillSendRequestForAuthenticationChallenge(_di_NSURLConnection connection, _di_NSURLAuthenticationChallenge willSendRequestForAuthenticationChallenge) = 0 ;
	virtual bool __cdecl connectionCanAuthenticateAgainstProtectionSpace(_di_NSURLConnection connection, _di_NSURLProtectionSpace canAuthenticateAgainstProtectionSpace) = 0 ;
	virtual void __cdecl connectionDidReceiveAuthenticationChallenge(_di_NSURLConnection connection, _di_NSURLAuthenticationChallenge didReceiveAuthenticationChallenge) = 0 ;
	virtual void __cdecl connectionDidCancelAuthenticationChallenge(_di_NSURLConnection connection, _di_NSURLAuthenticationChallenge didCancelAuthenticationChallenge) = 0 ;
};

__interface  INTERFACE_UUID("{4B2F087B-7274-4790-9F84-F784500480FD}") NSURLConnectionDataDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual _di_NSURLRequest __cdecl connectionWillSendRequestRedirectResponse(_di_NSURLConnection connection, _di_NSURLRequest willSendRequest, _di_NSURLResponse redirectResponse) = 0 ;
	virtual void __cdecl connectionDidReceiveResponse(_di_NSURLConnection connection, _di_NSURLResponse didReceiveResponse) = 0 ;
	virtual void __cdecl connectionDidReceiveData(_di_NSURLConnection connection, _di_NSData didReceiveData) = 0 ;
	virtual _di_NSInputStream __cdecl connectionNeedNewBodyStream(_di_NSURLConnection connection, _di_NSURLRequest needNewBodyStream) = 0 ;
	virtual void __cdecl connectionDidSendBodyDataTotalBytesWrittenTotalBytesExpectedToWrite(_di_NSURLConnection connection, long didSendBodyData, long totalBytesWritten, long totalBytesExpectedToWrite) = 0 ;
	virtual _di_NSCachedURLResponse __cdecl connectionWillCacheResponse(_di_NSURLConnection connection, _di_NSCachedURLResponse willCacheResponse) = 0 ;
	virtual void __cdecl connectionDidFinishLoading(_di_NSURLConnection connection) = 0 ;
};

__interface  INTERFACE_UUID("{0ED78C57-C053-41D3-9BFE-B4E97A9C32B5}") NSURLConnectionDownloadDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl connection(_di_NSURLConnection connection, __int64 didWriteData, __int64 totalBytesWritten, __int64 expectedTotalBytes) = 0 ;
	virtual void __cdecl connectionDidResumeDownloading(_di_NSURLConnection connection, __int64 totalBytesWritten, __int64 expectedTotalBytes) = 0 ;
	virtual void __cdecl connectionDidFinishDownloading(_di_NSURLConnection connection, _di_NSURL destinationURL) = 0 ;
};

__interface  INTERFACE_UUID("{87FC62E2-4194-4AB7-9012-C530BFC9C8EB}") NSURLProtocolClient  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl URLProtocolWasRedirectedToRequestRedirectResponse(_di_NSURLProtocol protocol, _di_NSURLRequest wasRedirectedToRequest, _di_NSURLResponse redirectResponse) = 0 ;
	virtual void __cdecl URLProtocolCachedResponseIsValid(_di_NSURLProtocol protocol, _di_NSCachedURLResponse cachedResponseIsValid) = 0 ;
	virtual void __cdecl URLProtocolDidReceiveResponseCacheStoragePolicy(_di_NSURLProtocol protocol, _di_NSURLResponse didReceiveResponse, int cacheStoragePolicy) = 0 ;
	virtual void __cdecl URLProtocolDidLoadData(_di_NSURLProtocol protocol, _di_NSData didLoadData) = 0 ;
	virtual void __cdecl URLProtocolDidFinishLoading(_di_NSURLProtocol protocol) = 0 ;
	virtual void __cdecl URLProtocolDidFailWithError(_di_NSURLProtocol protocol, _di_NSError didFailWithError) = 0 ;
	virtual void __cdecl URLProtocolDidReceiveAuthenticationChallenge(_di_NSURLProtocol protocol, _di_NSURLAuthenticationChallenge didReceiveAuthenticationChallenge) = 0 ;
	virtual void __cdecl URLProtocolDidCancelAuthenticationChallenge(_di_NSURLProtocol protocol, _di_NSURLAuthenticationChallenge didCancelAuthenticationChallenge) = 0 ;
};

__interface  INTERFACE_UUID("{32C35EB3-28E8-4C02-90B1-878EC1F3C8DF}") NSXMLParserDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl parserDidStartDocument(_di_NSXMLParser parser) = 0 ;
	virtual void __cdecl parserDidEndDocument(_di_NSXMLParser parser) = 0 ;
	virtual void __cdecl parserFoundNotationDeclarationWithNamePublicIDSystemID(_di_NSXMLParser parser, _di_NSString foundNotationDeclarationWithName, _di_NSString publicID, _di_NSString systemID) = 0 ;
	virtual void __cdecl parserFoundUnparsedEntityDeclarationWithNamePublicIDSystemIDNotationName(_di_NSXMLParser parser, _di_NSString foundUnparsedEntityDeclarationWithName, _di_NSString publicID, _di_NSString systemID, _di_NSString notationName) = 0 ;
	virtual void __cdecl parserFoundAttributeDeclarationWithNameForElementTypeDefaultValue(_di_NSXMLParser parser, _di_NSString foundAttributeDeclarationWithName, _di_NSString forElement, _di_NSString type, _di_NSString defaultValue) = 0 ;
	virtual void __cdecl parserFoundElementDeclarationWithNameModel(_di_NSXMLParser parser, _di_NSString foundElementDeclarationWithName, _di_NSString model) = 0 ;
	virtual void __cdecl parserFoundInternalEntityDeclarationWithNameValue(_di_NSXMLParser parser, _di_NSString foundInternalEntityDeclarationWithName, _di_NSString value) = 0 ;
	virtual void __cdecl parserFoundExternalEntityDeclarationWithNamePublicIDSystemID(_di_NSXMLParser parser, _di_NSString foundExternalEntityDeclarationWithName, _di_NSString publicID, _di_NSString systemID) = 0 ;
	virtual void __cdecl parserDidStartElementNamespaceURIQualifiedNameAttributes(_di_NSXMLParser parser, _di_NSString didStartElement, _di_NSString namespaceURI, _di_NSString qualifiedName, _di_NSDictionary attributes) = 0 ;
	virtual void __cdecl parserDidEndElementNamespaceURIQualifiedName(_di_NSXMLParser parser, _di_NSString didEndElement, _di_NSString namespaceURI, _di_NSString qualifiedName) = 0 ;
	virtual void __cdecl parserDidStartMappingPrefixToURI(_di_NSXMLParser parser, _di_NSString didStartMappingPrefix, _di_NSString toURI) = 0 ;
	virtual void __cdecl parserDidEndMappingPrefix(_di_NSXMLParser parser, _di_NSString didEndMappingPrefix) = 0 ;
	virtual void __cdecl parserFoundCharacters(_di_NSXMLParser parser, _di_NSString foundCharacters) = 0 ;
	virtual void __cdecl parserFoundIgnorableWhitespace(_di_NSXMLParser parser, _di_NSString foundIgnorableWhitespace) = 0 ;
	virtual void __cdecl parserFoundProcessingInstructionWithTargetData(_di_NSXMLParser parser, _di_NSString foundProcessingInstructionWithTarget, _di_NSString data) = 0 ;
	virtual void __cdecl parserFoundComment(_di_NSXMLParser parser, _di_NSString foundComment) = 0 ;
	virtual void __cdecl parserFoundCDATA(_di_NSXMLParser parser, _di_NSData foundCDATA) = 0 ;
	virtual _di_NSData __cdecl parserResolveExternalEntityNameSystemID(_di_NSXMLParser parser, _di_NSString resolveExternalEntityName, _di_NSString systemID) = 0 ;
	virtual void __cdecl parserParseErrorOccurred(_di_NSXMLParser parser, _di_NSError parseErrorOccurred) = 0 ;
	virtual void __cdecl parserValidationErrorOccurred(_di_NSXMLParser parser, _di_NSError validationErrorOccurred) = 0 ;
};

__interface  INTERFACE_UUID("{8E5A1146-3E28-4508-A2F0-6FD66E2790BC}") NSCacheDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl cache(_di_NSCache cache, void * willEvictObject) = 0 ;
};

__interface  INTERFACE_UUID("{E3627249-F300-41FE-8BB2-9E37CEDCAC50}") NSFilePresenter  : public Macapi::Objectivec::IObjectiveC 
{
	virtual _di_NSURL __cdecl presentedItemURL() = 0 ;
	virtual _di_NSOperationQueue __cdecl presentedItemOperationQueue() = 0 ;
	virtual _di_NSURL __cdecl primaryPresentedItemURL() = 0 ;
	virtual void __cdecl relinquishPresentedItemToReader(TFoundationByAccessor2 reader) = 0 ;
	virtual void __cdecl relinquishPresentedItemToWriter(TFoundationByAccessor2 writer) = 0 ;
	virtual void __cdecl savePresentedItemChangesWithCompletionHandler(TFoundationCompletionHandler1 completionHandler) = 0 ;
	virtual void __cdecl accommodatePresentedItemDeletionWithCompletionHandler(TFoundationCompletionHandler1 completionHandler) = 0 ;
	virtual void __cdecl presentedItemDidMoveToURL(_di_NSURL newURL) = 0 ;
	virtual void __cdecl presentedItemDidChange() = 0 ;
	virtual void __cdecl presentedItemDidGainVersion(_di_NSFileVersion version) = 0 ;
	virtual void __cdecl presentedItemDidLoseVersion(_di_NSFileVersion version) = 0 ;
	virtual void __cdecl presentedItemDidResolveConflictVersion(_di_NSFileVersion version) = 0 ;
	virtual void __cdecl accommodatePresentedSubitemDeletionAtURL(_di_NSURL url, TFoundationCompletionHandler1 completionHandler) = 0 ;
	virtual void __cdecl presentedSubitemDidAppearAtURL(_di_NSURL url) = 0 ;
	virtual void __cdecl presentedSubitemAtURLDidMoveToURL(_di_NSURL oldURL, _di_NSURL didMoveToURL) = 0 ;
	virtual void __cdecl presentedSubitemDidChangeAtURL(_di_NSURL url) = 0 ;
	virtual void __cdecl presentedSubitemAtURLDidGainVersion(_di_NSURL url, _di_NSFileVersion didGainVersion) = 0 ;
	virtual void __cdecl presentedSubitemAtURLDidLoseVersion(_di_NSURL url, _di_NSFileVersion didLoseVersion) = 0 ;
	virtual void __cdecl presentedSubitemAtURLDidResolveConflictVersion(_di_NSURL url, _di_NSFileVersion didResolveConflictVersion) = 0 ;
};

__interface  INTERFACE_UUID("{B0935765-7E85-4EFF-9155-C54229EF8F37}") NSMetadataQueryDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void * __cdecl metadataQueryReplacementObjectForResultObject(_di_NSMetadataQuery query, _di_NSMetadataItem replacementObjectForResultObject) = 0 ;
	virtual void * __cdecl metadataQueryReplacementValueForAttributeValue(_di_NSMetadataQuery query, _di_NSString replacementValueForAttribute, void * value) = 0 ;
};

__interface  INTERFACE_UUID("{8E3FFC73-9CA5-48EC-A96C-C8A46AE093FC}") NSNetServiceDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl netServiceWillPublish(_di_NSNetService sender) = 0 ;
	virtual void __cdecl netServiceDidPublish(_di_NSNetService sender) = 0 ;
	virtual void __cdecl netServiceDidNotPublish(_di_NSNetService sender, _di_NSDictionary didNotPublish) = 0 ;
	virtual void __cdecl netServiceWillResolve(_di_NSNetService sender) = 0 ;
	virtual void __cdecl netServiceDidResolveAddress(_di_NSNetService sender) = 0 ;
	virtual void __cdecl netServiceDidNotResolve(_di_NSNetService sender, _di_NSDictionary didNotResolve) = 0 ;
	virtual void __cdecl netServiceDidStop(_di_NSNetService sender) = 0 ;
	virtual void __cdecl netServiceDidUpdateTXTRecordData(_di_NSNetService sender, _di_NSData didUpdateTXTRecordData) = 0 ;
	virtual void __cdecl netServiceDidAcceptConnectionWithInputStreamOutputStream(_di_NSNetService sender, _di_NSInputStream didAcceptConnectionWithInputStream, _di_NSOutputStream outputStream) = 0 ;
};

__interface  INTERFACE_UUID("{AB7BC138-FB43-46D2-8023-9883391F8842}") NSNetServiceBrowserDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl netServiceBrowserWillSearch(_di_NSNetServiceBrowser aNetServiceBrowser) = 0 ;
	virtual void __cdecl netServiceBrowserDidStopSearch(_di_NSNetServiceBrowser aNetServiceBrowser) = 0 ;
	virtual void __cdecl netServiceBrowserDidNotSearch(_di_NSNetServiceBrowser aNetServiceBrowser, _di_NSDictionary didNotSearch) = 0 ;
	virtual void __cdecl netServiceBrowserDidFindDomainMoreComing(_di_NSNetServiceBrowser aNetServiceBrowser, _di_NSString didFindDomain, bool moreComing) = 0 ;
	virtual void __cdecl netServiceBrowserDidFindServiceMoreComing(_di_NSNetServiceBrowser aNetServiceBrowser, _di_NSNetService didFindService, bool moreComing) = 0 ;
	virtual void __cdecl netServiceBrowserDidRemoveDomainMoreComing(_di_NSNetServiceBrowser aNetServiceBrowser, _di_NSString didRemoveDomain, bool moreComing) = 0 ;
	virtual void __cdecl netServiceBrowserDidRemoveServiceMoreComing(_di_NSNetServiceBrowser aNetServiceBrowser, _di_NSNetService didRemoveService, bool moreComing) = 0 ;
};

__interface  INTERFACE_UUID("{8EE204C3-F429-4384-8C39-69341D7CDC2E}") NSURLSessionDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl URLSessionDidBecomeInvalidWithError(_di_NSURLSession session, _di_NSError didBecomeInvalidWithError) = 0 ;
	virtual void __cdecl URLSessionDidReceiveChallengeCompletionHandler(_di_NSURLSession session, _di_NSURLAuthenticationChallenge didReceiveChallenge, TFoundationCompletionHandler6 completionHandler) = 0 ;
	virtual void __cdecl URLSessionDidFinishEventsForBackgroundURLSession(_di_NSURLSession session) = 0 ;
};

__interface  INTERFACE_UUID("{DB1BD3DF-5806-4AB9-A113-3C261DD981B2}") NSURLSessionTaskDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl URLSessionTaskWillPerformHTTPRedirectionNewRequestCompletionHandler(_di_NSURLSession session, _di_NSURLSessionTask task, _di_NSHTTPURLResponse willPerformHTTPRedirection, _di_NSURLRequest newRequest, TFoundationCompletionHandler7 completionHandler) = 0 ;
	virtual void __cdecl URLSessionTaskDidReceiveChallengeCompletionHandler(_di_NSURLSession session, _di_NSURLSessionTask task, _di_NSURLAuthenticationChallenge didReceiveChallenge, TFoundationCompletionHandler6 completionHandler) = 0 ;
	virtual void __cdecl URLSessionTaskNeedNewBodyStream(_di_NSURLSession session, _di_NSURLSessionTask task, TFoundationNeedNewBodyStream needNewBodyStream) = 0 ;
	virtual void __cdecl URLSessionTaskDidSendBodyDataTotalBytesSentTotalBytesExpectedToSend(_di_NSURLSession session, _di_NSURLSessionTask task, __int64 didSendBodyData, __int64 totalBytesSent, __int64 totalBytesExpectedToSend) = 0 ;
	virtual void __cdecl URLSessionTaskDidCompleteWithError(_di_NSURLSession session, _di_NSURLSessionTask task, _di_NSError didCompleteWithError) = 0 ;
};

__interface  INTERFACE_UUID("{86F1CA3F-241F-45FD-8E99-BF0B8FD89B50}") NSURLSessionDataDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl URLSessionDataTaskDidReceiveResponseCompletionHandler(_di_NSURLSession session, _di_NSURLSessionDataTask dataTask, _di_NSURLResponse didReceiveResponse, TFoundationCompletionHandler8 completionHandler) = 0 ;
	virtual void __cdecl URLSessionDataTaskDidBecomeDownloadTask(_di_NSURLSession session, _di_NSURLSessionDataTask dataTask, _di_NSURLSessionDownloadTask didBecomeDownloadTask) = 0 ;
	virtual void __cdecl URLSessionDataTaskDidReceiveData(_di_NSURLSession session, _di_NSURLSessionDataTask dataTask, _di_NSData didReceiveData) = 0 ;
	virtual void __cdecl URLSessionDataTaskWillCacheResponseCompletionHandler(_di_NSURLSession session, _di_NSURLSessionDataTask dataTask, _di_NSCachedURLResponse willCacheResponse, TFoundationCompletionHandler9 completionHandler) = 0 ;
};

__interface  INTERFACE_UUID("{18C1FDFC-F78D-4EE0-9DCA-B7D5FE88C45D}") NSURLSessionDownloadDelegate  : public Macapi::Objectivec::IObjectiveC 
{
	virtual void __cdecl URLSessionDownloadTaskDidFinishDownloadingToURL(_di_NSURLSession session, _di_NSURLSessionDownloadTask downloadTask, _di_NSURL didFinishDownloadingToURL) = 0 ;
	virtual void __cdecl URLSessionDownloadTaskDidWriteDataTotalBytesWrittenTotalBytesExpectedToWrite(_di_NSURLSession session, _di_NSURLSessionDownloadTask downloadTask, __int64 didWriteData, __int64 totalBytesWritten, __int64 totalBytesExpectedToWrite) = 0 ;
	virtual void __cdecl URLSessionDownloadTaskDidResumeAtOffsetExpectedTotalBytes(_di_NSURLSession session, _di_NSURLSessionDownloadTask downloadTask, __int64 didResumeAtOffset, __int64 expectedTotalBytes) = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
extern "C" void * __cdecl CFBridgingRelease(void * X);
extern "C" void * __cdecl CFBridgingRetain(void * X);
extern "C" void * __cdecl NSAllocateMemoryPages(unsigned long bytes);
extern "C" void * __cdecl NSAllocateObject(void * aClass, unsigned long extraBytes, void * zone);
extern "C" void * __cdecl NSClassFromString(void * aClassName);
extern "C" void __cdecl NSCopyMemoryPages(void * source, void * dest, unsigned long bytes);
extern "C" void * __cdecl NSCopyObject(void * object_, unsigned long extraBytes, void * zone);
extern "C" void * __cdecl NSCreateZone(unsigned long startSize, unsigned long granularity, bool canFree);
extern "C" void __cdecl NSDeallocateMemoryPages(void * ptr, unsigned long bytes);
extern "C" void __cdecl NSDeallocateObject(void * object_);
extern "C" void __cdecl NSDecimalCompact(PNSDecimal number);
extern "C" long __cdecl NSDecimalCompare(PNSDecimal leftOperand, PNSDecimal rightOperand);
extern "C" void __cdecl NSDecimalCopy(PNSDecimal destination, PNSDecimal source);
extern "C" void __cdecl NSDecimalRound(PNSDecimal result, PNSDecimal number, long scale, unsigned long roundingMode);
extern "C" void * __cdecl NSDecimalString(PNSDecimal dcm, void * locale);
extern "C" bool __cdecl NSDecrementExtraRefCountWasZero(void * object_);
extern "C" void * __cdecl NSDefaultMallocZone(void);
extern "C" unsigned long __cdecl NSExtraRefCount(void * object_);
extern "C" void * __cdecl NSFullUserName(void);
extern "C" char * __cdecl NSGetSizeAndAlignment(char * typePtr, Iosapi::Cocoatypes::PNSUInteger sizep, Iosapi::Cocoatypes::PNSUInteger alignp);
extern "C" void * __cdecl NSHomeDirectory(void);
extern "C" void * __cdecl NSHomeDirectoryForUser(void * userName);
extern "C" long __cdecl NSHostByteOrder(void);
extern "C" void __cdecl NSIncrementExtraRefCount(void * object_);
extern "C" NSRange __cdecl NSIntersectionRange(NSRange range1, NSRange range2);
extern "C" void __cdecl NSLog(void * format, ...);
extern "C" unsigned long __cdecl NSLogPageSize(void);
extern "C" void * __cdecl NSMakeCollectable(void * cf);
extern "C" void * __cdecl NSOpenStepRootDirectory(void);
extern "C" unsigned long __cdecl NSPageSize(void);
extern "C" void * __cdecl NSProtocolFromString(void * namestr);
extern "C" NSRange __cdecl NSRangeFromString(void * aString);
extern "C" unsigned long __cdecl NSRealMemoryAvailable(void);
extern "C" void __cdecl NSRecycleZone(void * zone);
extern "C" unsigned long __cdecl NSRoundDownToMultipleOfPageSize(unsigned long bytes);
extern "C" unsigned long __cdecl NSRoundUpToMultipleOfPageSize(unsigned long bytes);
extern "C" void * __cdecl NSSearchPathForDirectoriesInDomains(unsigned long directory, unsigned long domainMask, bool expandTilde);
extern "C" void * __cdecl NSSelectorFromString(void * aSelectorName);
extern "C" void __cdecl NSSetZoneName(void * zone, void * name);
extern "C" bool __cdecl NSShouldRetainWithZone(void * anObject, void * requestedZone);
extern "C" void * __cdecl NSStringFromClass(void * aClass);
extern "C" void * __cdecl NSStringFromProtocol(void * proto);
extern "C" void * __cdecl NSStringFromRange(NSRange range);
extern "C" void * __cdecl NSStringFromSelector(void * aSelector);
extern "C" unsigned __cdecl NSSwapBigIntToHost(unsigned x);
extern "C" unsigned __int64 __cdecl NSSwapBigLongLongToHost(unsigned __int64 x);
extern "C" unsigned long __cdecl NSSwapBigLongToHost(unsigned long x);
extern "C" System::Word __cdecl NSSwapBigShortToHost(System::Word x);
extern "C" unsigned __cdecl NSSwapHostIntToBig(unsigned x);
extern "C" unsigned __cdecl NSSwapHostIntToLittle(unsigned x);
extern "C" unsigned __int64 __cdecl NSSwapHostLongLongToBig(unsigned __int64 x);
extern "C" unsigned __int64 __cdecl NSSwapHostLongLongToLittle(unsigned __int64 x);
extern "C" unsigned long __cdecl NSSwapHostLongToBig(unsigned long x);
extern "C" unsigned long __cdecl NSSwapHostLongToLittle(unsigned long x);
extern "C" System::Word __cdecl NSSwapHostShortToBig(System::Word x);
extern "C" System::Word __cdecl NSSwapHostShortToLittle(System::Word x);
extern "C" unsigned __cdecl NSSwapInt(unsigned inv);
extern "C" unsigned __cdecl NSSwapLittleIntToHost(unsigned x);
extern "C" unsigned __int64 __cdecl NSSwapLittleLongLongToHost(unsigned __int64 x);
extern "C" unsigned long __cdecl NSSwapLittleLongToHost(unsigned long x);
extern "C" System::Word __cdecl NSSwapLittleShortToHost(System::Word x);
extern "C" unsigned long __cdecl NSSwapLong(unsigned long inv);
extern "C" unsigned __int64 __cdecl NSSwapLongLong(unsigned __int64 inv);
extern "C" System::Word __cdecl NSSwapShort(System::Word inv);
extern "C" void * __cdecl NSTemporaryDirectory(void);
extern "C" NSRange __cdecl NSUnionRange(NSRange range1, NSRange range2);
extern "C" void * __cdecl NSUserName(void);
extern "C" void * __cdecl NSZoneCalloc(void * zone, unsigned long numElems, unsigned long byteSize);
extern "C" void __cdecl NSZoneFree(void * zone, void * ptr);
extern "C" void * __cdecl NSZoneFromPointer(void * ptr);
extern "C" void * __cdecl NSZoneMalloc(void * zone, unsigned long size);
extern "C" void * __cdecl NSZoneName(void * zone);
extern "C" void * __cdecl NSZoneRealloc(void * zone, void * ptr, unsigned long size);
extern DELPHI_PACKAGE _di_NSString __fastcall NSSTR _DEPRECATED_ATTRIBUTE1("use StrToNSStr instead") (const System::UnicodeString Str);
extern DELPHI_PACKAGE int __fastcall CocoaIntegerConst(const System::UnicodeString Fwk, const System::UnicodeString ConstStr);
extern DELPHI_PACKAGE void * __fastcall CocoaPointerConst(const System::UnicodeString Fwk, const System::UnicodeString ConstStr);
extern DELPHI_PACKAGE _di_NSString __fastcall CocoaNSStringConst(const System::UnicodeString Fwk, const System::UnicodeString ConstStr);
extern DELPHI_PACKAGE bool __fastcall NSInheritsFrom(const _di_NSObject AObject, const _di_NSObjectClass AClass);
extern DELPHI_PACKAGE _di_NSString __fastcall NSDefaultRunLoopMode(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSRunLoopCommonModes(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSLocaleLanguageCode(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSHTTPPropertyStatusCodeKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSHTTPPropertyStatusReasonKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSHTTPPropertyServerHTTPVersionKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSHTTPPropertyRedirectionHeadersKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSHTTPPropertyErrorPageDataKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSHTTPPropertyHTTPProxy(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSFTPPropertyUserLoginKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSFTPPropertyUserPasswordKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSFTPPropertyActiveTransferModeKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSFTPPropertyFileOffsetKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSFTPPropertyFTPProxy(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLFileScheme(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLKeysOfUnsetValuesKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLNameKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLLocalizedNameKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLIsRegularFileKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLIsDirectoryKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLIsSymbolicLinkKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLIsVolumeKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLIsPackageKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLIsSystemImmutableKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLIsUserImmutableKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLIsHiddenKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLHasHiddenExtensionKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLCreationDateKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLContentAccessDateKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLContentModificationDateKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLAttributeModificationDateKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLLinkCountKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLParentDirectoryURLKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeURLKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLTypeIdentifierKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLLocalizedTypeDescriptionKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLLabelNumberKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLLabelColorKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLLocalizedLabelKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLEffectiveIconKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLCustomIconKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLFileResourceIdentifierKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeIdentifierKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLPreferredIOBlockSizeKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLIsReadableKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLIsWritableKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLIsExecutableKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLFileSecurityKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLIsExcludedFromBackupKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLTagNamesKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLPathKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLIsMountTriggerKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLFileResourceTypeKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLFileResourceTypeNamedPipe(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLFileResourceTypeCharacterSpecial(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLFileResourceTypeDirectory(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLFileResourceTypeBlockSpecial(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLFileResourceTypeRegular(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLFileResourceTypeSymbolicLink(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLFileResourceTypeSocket(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLFileResourceTypeUnknown(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLFileSizeKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLFileAllocatedSizeKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLTotalFileSizeKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLTotalFileAllocatedSizeKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLIsAliasFileKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeLocalizedFormatDescriptionKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeTotalCapacityKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeAvailableCapacityKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeResourceCountKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeSupportsPersistentIDsKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeSupportsSymbolicLinksKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeSupportsHardLinksKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeSupportsJournalingKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeIsJournalingKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeSupportsSparseFilesKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeSupportsZeroRunsKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeSupportsCaseSensitiveNamesKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeSupportsCasePreservedNamesKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeSupportsRootDirectoryDatesKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeSupportsVolumeSizesKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeSupportsRenamingKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeSupportsAdvisoryFileLockingKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeSupportsExtendedSecurityKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeIsBrowsableKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeMaximumFileSizeKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeIsEjectableKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeIsRemovableKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeIsInternalKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeIsAutomountedKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeIsLocalKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeIsReadOnlyKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeCreationDateKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeURLForRemountingKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeUUIDStringKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeNameKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLVolumeLocalizedNameKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLIsUbiquitousItemKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLUbiquitousItemHasUnresolvedConflictsKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLUbiquitousItemIsDownloadedKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLUbiquitousItemIsDownloadingKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLUbiquitousItemIsUploadedKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLUbiquitousItemIsUploadingKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLUbiquitousItemPercentDownloadedKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLUbiquitousItemPercentUploadedKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLUbiquitousItemDownloadingStatusKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLUbiquitousItemDownloadingErrorKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLUbiquitousItemUploadingErrorKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLUbiquitousItemDownloadingStatusNotDownloaded(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLUbiquitousItemDownloadingStatusDownloaded(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLUbiquitousItemDownloadingStatusCurrent(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLCredentialStorageChangedNotification(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLCredentialStorageRemoveSynchronizableCredentials(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLErrorDomain(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLErrorFailingURLErrorKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLErrorFailingURLStringErrorKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSErrorFailingURLStringKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLErrorFailingURLPeerTrustErrorKey(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLProtectionSpaceHTTP(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLProtectionSpaceHTTPS(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLProtectionSpaceFTP(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLProtectionSpaceHTTPProxy(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLProtectionSpaceHTTPSProxy(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLProtectionSpaceFTPProxy(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLProtectionSpaceSOCKSProxy(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLAuthenticationMethodDefault(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLAuthenticationMethodHTTPBasic(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLAuthenticationMethodHTTPDigest(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLAuthenticationMethodHTMLForm(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLAuthenticationMethodNTLM(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLAuthenticationMethodNegotiate(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLAuthenticationMethodClientCertificate(void);
extern DELPHI_PACKAGE _di_NSString __fastcall NSURLAuthenticationMethodServerTrust(void);
extern DELPHI_PACKAGE bool __cdecl NSDecimalIsNotANumber(PNSDecimal dcm);
extern DELPHI_PACKAGE NSRange __fastcall NSMakeRange(unsigned long loc, unsigned long len);
extern DELPHI_PACKAGE unsigned long __fastcall NSMaxRange(const NSRange &range);
extern DELPHI_PACKAGE bool __fastcall NSLocationInRange(unsigned long loc, const NSRange &range);
extern DELPHI_PACKAGE bool __fastcall NSEqualRanges(const NSRange &range1, const NSRange &range2);
}	/* namespace Foundation */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_FOUNDATION)
using namespace Iosapi::Foundation;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_FoundationHPP
