// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Macapi.CoreFoundation.pas' rev: 34.00 (iOS)

#ifndef Macapi_CorefoundationHPP
#define Macapi_CorefoundationHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.StdDef.hpp>
#include <Macapi.CoreServices.hpp>
#include <Macapi.Mach.hpp>

//-- user supplied -----------------------------------------------------------

#include <CoreFoundation/CoreFoundation.h>


namespace Macapi
{
namespace Corefoundation
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef unsigned *POSType;

typedef unsigned *PUInt32;

typedef System::WideChar * PUniChar;

typedef unsigned *PUTF32Char;

typedef long *PCFIndex;

typedef void * *PCFTypeRef;

typedef CFStringRef *PCFStringRef;

typedef CFMutableStringRef *PCFMutableStringRef;

typedef void * *PCFPropertyListRef;

typedef CFRange *PCFRange;

typedef CFNullRef *PCFNullRef;

typedef CFAllocatorRef *PCFAllocatorRef;

typedef CFAllocatorContext *PCFAllocatorContext;

typedef CFArrayCallBacks *PCFArrayCallBacks;

typedef CFArrayRef *PCFArrayRef;

typedef CFMutableArrayRef *PCFMutableArrayRef;

typedef CFDictionaryKeyCallBacks *PCFDictionaryKeyCallBacks;

typedef CFDictionaryValueCallBacks *PCFDictionaryValueCallBacks;

typedef CFDictionaryRef *PCFDictionaryRef;

typedef CFMutableDictionaryRef *PCFMutableDictionaryRef;

typedef CFDataRef *PCFDataRef;

typedef CFMutableDataRef *PCFMutableDataRef;

typedef CFCharacterSetRef *PCFCharacterSetRef;

typedef CFMutableCharacterSetRef *PCFMutableCharacterSetRef;

typedef CFLocaleRef *PCFLocaleRef;

typedef unsigned *PCFStringEncoding;

typedef CFStringInlineBuffer *PCFStringInlineBuffer;

typedef CFAttributedStringRef *PCFAttributedStringRef;

typedef CFBagCallBacks *PCFBagCallBacks;

typedef CFBagRef *PCFBagRef;

typedef CFMutableBagRef *PCFMutableBagRef;

typedef CFBinaryHeapCompareContext *PCFBinaryHeapCompareContext;

typedef CFBinaryHeapCallBacks *PCFBinaryHeapCallBacks;

typedef CFBinaryHeapRef *PCFBinaryHeapRef;

typedef CFBitVectorRef *PCFBitVectorRef;

typedef CFMutableBitVectorRef *PCFMutableBitVectorRef;

typedef CFErrorRef *PCFErrorRef;

typedef CFURLRef *PCFURLRef;

typedef CFBundleRef *PCFBundleRef;

typedef CFPlugInRef *PCFPlugInRef;

typedef int *PCFBundleRefNum;

typedef double *PCFTimeInterval;

typedef double *PCFAbsoluteTime;

typedef CFDateRef *PCFDateRef;

typedef CFTimeZoneRef *PCFTimeZoneRef;

typedef CFGregorianDate *PCFGregorianDate;

typedef CFGregorianUnits *PCFGregorianUnits;

typedef CFCalendarRef *PCFCalendarRef;

typedef CFDateFormatterRef *PCFDateFormatterRef;

typedef CFRunLoopRef *PCFRunLoopRef;

typedef CFRunLoopSourceRef *PCFRunLoopSourceRef;

typedef CFRunLoopObserverRef *PCFRunLoopObserverRef;

typedef CFRunLoopTimerRef *PCFRunLoopTimerRef;

typedef bool __cdecl (*CFRunLoopEqualCallback)(void * info1, void * info2);

typedef unsigned long __cdecl (*CFRunLoopHashCallback)(void * info);

typedef void __cdecl (*CFRunLoopSheduleCallback)(void * info, CFRunLoopRef r1, CFStringRef mode);

typedef void __cdecl (*CFRunLoopCancelCallback)(void * info, CFRunLoopRef r1, CFStringRef mode);

typedef void __cdecl (*CFRunLoopPerformCallback)(void * info);

typedef CFRunLoopSourceContext *PCFRunLoopSourceContext;

typedef unsigned __cdecl (*CFRunLoopGetPortCallBack)(void * info);

typedef void * __cdecl (*CFRunLoopMachPerformCallBack)(void * msg, long size, CFAllocatorRef allocator, void * info);

typedef CFRunLoopSourceContext1 *PCFRunLoopSourceContext1;

typedef CFRunLoopObserverContext *PCFRunLoopObserverContext;

typedef CFRunLoopTimerContext *PCFRunLoopTimerContext;

typedef CFFileDescriptorRef *PCFFileDescriptorRef;

typedef CFFileDescriptorContext *PCFFileDescriptorContext;

typedef CFMachPortRef *PCFMachPortRef;

typedef CFMachPortContext *PCFMachPortContext;

typedef CFMessagePortRef *PCFMessagePortRef;

typedef CFMessagePortContext *PCFMessagePortContext;

typedef CFNotificationCenterRef *PCFNotificationCenterRef;

typedef CFBooleanRef *PCFBooleanRef;

typedef CFNumberRef *PCFNumberRef;

typedef CFNumberFormatterRef *PCFNumberFormatterRef;

typedef CFUUIDRef *PCFUUIDRef;

typedef CFUUIDBytes *PCFUUIDBytes;

typedef CFSocketRef *PCFSocketRef;

typedef CFSocketSignature *PCFSocketSignature;

typedef CFSocketContext *PCFSocketContext;

typedef CFStreamClientContext *PCFStreamClientContext;

typedef CFReadStreamRef *PCFReadStreamRef;

typedef CFWriteStreamRef *PCFWriteStreamRef;

typedef CFStreamError *PCFStreamError;

typedef long *PCFPropertyListFormat;

typedef CFSetCallBacks *PCFSetCallBacks;

typedef CFStringTokenizerRef *PCFStringTokenizerRef;

typedef CFTreeContext *PCFTreeContext;

typedef CFTreeRef *PCFTreeRef;

typedef CFURLEnumeratorRef *PCFURLEnumeratorRef;

//-- var, const, procedure ---------------------------------------------------
#define CoreFoundationLib u"/System/Library/Frameworks/CoreFoundation.framework/CoreFo"\
	u"undation"
extern DELPHI_PACKAGE void __fastcall CFStringInitInlineBuffer(CFStringRef str, PCFStringInlineBuffer buf, const CFRange &range);
extern DELPHI_PACKAGE System::WideChar __fastcall CFStringGetCharacterFromInlineBuffer(PCFStringInlineBuffer buf, long idx);
extern DELPHI_PACKAGE bool __fastcall CFStringIsSurrogateHighCharacter(System::WideChar character);
extern DELPHI_PACKAGE bool __fastcall CFStringIsSurrogateLowCharacter(System::WideChar character);
extern DELPHI_PACKAGE unsigned __fastcall CFStringGetLongCharacterForSurrogatePair(System::WideChar surrogateHigh, System::WideChar surrogateLow);
extern DELPHI_PACKAGE bool __fastcall CFStringGetSurrogatePairForLongCharacter(unsigned character, System::WideChar * surrogates);
}	/* namespace Corefoundation */
}	/* namespace Macapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI_COREFOUNDATION)
using namespace Macapi::Corefoundation;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI)
using namespace Macapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Macapi_CorefoundationHPP
