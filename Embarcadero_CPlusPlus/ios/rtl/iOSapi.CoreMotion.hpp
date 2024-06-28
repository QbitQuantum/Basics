// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.CoreMotion.pas' rev: 34.00 (iOS)

#ifndef Iosapi_CoremotionHPP
#define Iosapi_CoremotionHPP

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
namespace Coremotion
{
//-- forward type declarations -----------------------------------------------
struct CMAcceleration;
struct CMMagneticField;
struct CMCalibratedMagneticField;
struct CMRotationMatrix;
struct CMRotationRate;
struct CMQuaternion;
__interface DELPHIINTERFACE CMLogItemClass;
typedef System::DelphiInterface<CMLogItemClass> _di_CMLogItemClass;
__interface DELPHIINTERFACE CMLogItem;
typedef System::DelphiInterface<CMLogItem> _di_CMLogItem;
class DELPHICLASS TCMLogItem;
__interface DELPHIINTERFACE CMAttitudeClass;
typedef System::DelphiInterface<CMAttitudeClass> _di_CMAttitudeClass;
__interface DELPHIINTERFACE CMAttitude;
typedef System::DelphiInterface<CMAttitude> _di_CMAttitude;
class DELPHICLASS TCMAttitude;
__interface DELPHIINTERFACE CMMotionManagerClass;
typedef System::DelphiInterface<CMMotionManagerClass> _di_CMMotionManagerClass;
__interface DELPHIINTERFACE CMMotionManager;
typedef System::DelphiInterface<CMMotionManager> _di_CMMotionManager;
class DELPHICLASS TCMMotionManager;
__interface DELPHIINTERFACE CMMagnetometerDataClass;
typedef System::DelphiInterface<CMMagnetometerDataClass> _di_CMMagnetometerDataClass;
__interface DELPHIINTERFACE CMMagnetometerData;
typedef System::DelphiInterface<CMMagnetometerData> _di_CMMagnetometerData;
class DELPHICLASS TCMMagnetometerData;
__interface DELPHIINTERFACE CMAccelerometerDataClass;
typedef System::DelphiInterface<CMAccelerometerDataClass> _di_CMAccelerometerDataClass;
__interface DELPHIINTERFACE CMAccelerometerData;
typedef System::DelphiInterface<CMAccelerometerData> _di_CMAccelerometerData;
class DELPHICLASS TCMAccelerometerData;
__interface DELPHIINTERFACE CMDeviceMotionClass;
typedef System::DelphiInterface<CMDeviceMotionClass> _di_CMDeviceMotionClass;
__interface DELPHIINTERFACE CMDeviceMotion;
typedef System::DelphiInterface<CMDeviceMotion> _di_CMDeviceMotion;
class DELPHICLASS TCMDeviceMotion;
__interface DELPHIINTERFACE CMGyroDataClass;
typedef System::DelphiInterface<CMGyroDataClass> _di_CMGyroDataClass;
__interface DELPHIINTERFACE CMGyroData;
typedef System::DelphiInterface<CMGyroData> _di_CMGyroData;
class DELPHICLASS TCMGyroData;
//-- type declarations -------------------------------------------------------
typedef unsigned long CMAttitudeReferenceFrame;

typedef long CMMagneticFieldCalibrationAccuracy;

struct DECLSPEC_DRECORD CMAcceleration
{
public:
	double x;
	double y;
	double z;
};


struct DECLSPEC_DRECORD CMMagneticField
{
public:
	double x;
	double y;
	double z;
};


struct DECLSPEC_DRECORD CMCalibratedMagneticField
{
public:
	CMMagneticField field;
	long accuracy;
};


struct DECLSPEC_DRECORD CMRotationMatrix
{
public:
	double m11;
	double m12;
	double m13;
	double m21;
	double m22;
	double m23;
	double m31;
	double m32;
	double m33;
};


struct DECLSPEC_DRECORD CMRotationRate
{
public:
	double x;
	double y;
	double z;
};


struct DECLSPEC_DRECORD CMQuaternion
{
public:
	double x;
	double y;
	double z;
	double w;
};


__interface  INTERFACE_UUID("{94AD5408-5C36-4438-B4D3-94D0548AD773}") CMLogItemClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{5C9C9161-A569-4099-80AA-B3E13FA3FCB2}") CMLogItem  : public Iosapi::Foundation::NSObject 
{
	virtual double __cdecl timestamp() = 0 ;
};

class PASCALIMPLEMENTATION TCMLogItem : public Macapi::Objectivec::TOCGenericImport__2<_di_CMLogItemClass,_di_CMLogItem>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CMLogItemClass,_di_CMLogItem> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCMLogItem(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CMLogItemClass,_di_CMLogItem>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCMLogItem() { }
	
};


__interface  INTERFACE_UUID("{276D225F-4487-4726-87E2-DDC32747EC6E}") CMAttitudeClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{6C5DC6B9-02B2-45FE-842A-D21FAA09BABD}") CMAttitude  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl multiplyByInverseOfAttitude(_di_CMAttitude attitude) = 0 ;
	virtual double __cdecl pitch() = 0 ;
	virtual CMQuaternion __cdecl quaternion() = 0 ;
	virtual double __cdecl roll() = 0 ;
	virtual CMRotationMatrix __cdecl rotationMatrix() = 0 ;
	virtual double __cdecl yaw() = 0 ;
};

class PASCALIMPLEMENTATION TCMAttitude : public Macapi::Objectivec::TOCGenericImport__2<_di_CMAttitudeClass,_di_CMAttitude>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CMAttitudeClass,_di_CMAttitude> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCMAttitude(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CMAttitudeClass,_di_CMAttitude>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCMAttitude() { }
	
};


__interface  INTERFACE_UUID("{F7099C0F-3410-48CD-B18E-5C8A98DBACD4}") CMMotionManagerClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual unsigned long __cdecl availableAttitudeReferenceFrames() = 0 ;
};

__interface  INTERFACE_UUID("{28BF5961-841D-40F8-91B5-D6B386D45E2E}") CMMotionManager  : public Iosapi::Foundation::NSObject 
{
	virtual _di_CMAccelerometerData __cdecl accelerometerData() = 0 ;
	virtual double __cdecl accelerometerUpdateInterval() = 0 ;
	virtual unsigned long __cdecl attitudeReferenceFrame() = 0 ;
	virtual _di_CMDeviceMotion __cdecl deviceMotion() = 0 ;
	virtual double __cdecl deviceMotionUpdateInterval() = 0 ;
	virtual _di_CMGyroData __cdecl gyroData() = 0 ;
	virtual double __cdecl gyroUpdateInterval() = 0 ;
	virtual bool __cdecl isAccelerometerActive() = 0 ;
	virtual bool __cdecl isAccelerometerAvailable() = 0 ;
	virtual bool __cdecl isDeviceMotionActive() = 0 ;
	virtual bool __cdecl isDeviceMotionAvailable() = 0 ;
	virtual bool __cdecl isGyroActive() = 0 ;
	virtual bool __cdecl isGyroAvailable() = 0 ;
	virtual bool __cdecl isMagnetometerActive() = 0 ;
	virtual bool __cdecl isMagnetometerAvailable() = 0 ;
	virtual _di_CMMagnetometerData __cdecl magnetometerData() = 0 ;
	virtual double __cdecl magnetometerUpdateInterval() = 0 ;
	virtual void __cdecl setAccelerometerUpdateInterval(double accelerometerUpdateInterval) = 0 ;
	virtual void __cdecl setDeviceMotionUpdateInterval(double deviceMotionUpdateInterval) = 0 ;
	virtual void __cdecl setGyroUpdateInterval(double gyroUpdateInterval) = 0 ;
	virtual void __cdecl setMagnetometerUpdateInterval(double magnetometerUpdateInterval) = 0 ;
	virtual void __cdecl setShowsDeviceMovementDisplay(bool showsDeviceMovementDisplay) = 0 ;
	virtual bool __cdecl showsDeviceMovementDisplay() = 0 ;
	virtual void __cdecl startAccelerometerUpdates() = 0 ;
	virtual void __cdecl startDeviceMotionUpdates() = 0 ;
	virtual void __cdecl startDeviceMotionUpdatesUsingReferenceFrame(unsigned long referenceFrame) = 0 /* overload */;
	virtual void __cdecl startGyroUpdates() = 0 ;
	virtual void __cdecl startMagnetometerUpdates() = 0 ;
	virtual void __cdecl stopAccelerometerUpdates() = 0 ;
	virtual void __cdecl stopDeviceMotionUpdates() = 0 ;
	virtual void __cdecl stopGyroUpdates() = 0 ;
	virtual void __cdecl stopMagnetometerUpdates() = 0 ;
};

class PASCALIMPLEMENTATION TCMMotionManager : public Macapi::Objectivec::TOCGenericImport__2<_di_CMMotionManagerClass,_di_CMMotionManager>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CMMotionManagerClass,_di_CMMotionManager> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCMMotionManager(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CMMotionManagerClass,_di_CMMotionManager>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCMMotionManager() { }
	
};


__interface  INTERFACE_UUID("{69ED80AF-51B9-417C-827C-101023DF3527}") CMMagnetometerDataClass  : public CMLogItemClass 
{
	
};

__interface  INTERFACE_UUID("{77FB8624-B966-4553-9F4E-947D0FC1867F}") CMMagnetometerData  : public CMLogItem 
{
	virtual CMMagneticField __cdecl magneticField() = 0 ;
};

class PASCALIMPLEMENTATION TCMMagnetometerData : public Macapi::Objectivec::TOCGenericImport__2<_di_CMMagnetometerDataClass,_di_CMMagnetometerData>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CMMagnetometerDataClass,_di_CMMagnetometerData> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCMMagnetometerData(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CMMagnetometerDataClass,_di_CMMagnetometerData>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCMMagnetometerData() { }
	
};


__interface  INTERFACE_UUID("{F1210D8D-7700-4E5E-A87E-C53DC7A3C34E}") CMAccelerometerDataClass  : public CMLogItemClass 
{
	
};

__interface  INTERFACE_UUID("{FF6C3080-F946-42CD-82C0-F07617F2272A}") CMAccelerometerData  : public CMLogItem 
{
	virtual CMAcceleration __cdecl acceleration() = 0 ;
};

class PASCALIMPLEMENTATION TCMAccelerometerData : public Macapi::Objectivec::TOCGenericImport__2<_di_CMAccelerometerDataClass,_di_CMAccelerometerData>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CMAccelerometerDataClass,_di_CMAccelerometerData> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCMAccelerometerData(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CMAccelerometerDataClass,_di_CMAccelerometerData>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCMAccelerometerData() { }
	
};


__interface  INTERFACE_UUID("{66DC7DC9-E96D-407C-869E-6D28D63C4846}") CMDeviceMotionClass  : public CMLogItemClass 
{
	
};

__interface  INTERFACE_UUID("{CFB6B9D3-EF36-4CCE-B0B4-8BFA18AA684B}") CMDeviceMotion  : public CMLogItem 
{
	virtual _di_CMAttitude __cdecl attitude() = 0 ;
	virtual CMAcceleration __cdecl gravity() = 0 ;
	virtual CMCalibratedMagneticField __cdecl magneticField() = 0 ;
	virtual CMRotationRate __cdecl rotationRate() = 0 ;
	virtual CMAcceleration __cdecl userAcceleration() = 0 ;
};

class PASCALIMPLEMENTATION TCMDeviceMotion : public Macapi::Objectivec::TOCGenericImport__2<_di_CMDeviceMotionClass,_di_CMDeviceMotion>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CMDeviceMotionClass,_di_CMDeviceMotion> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCMDeviceMotion(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CMDeviceMotionClass,_di_CMDeviceMotion>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCMDeviceMotion() { }
	
};


__interface  INTERFACE_UUID("{2F4702BE-ED8E-4D10-9AA5-421D950FED0C}") CMGyroDataClass  : public CMLogItemClass 
{
	
};

__interface  INTERFACE_UUID("{3CB41300-E395-437C-81A1-950CABD4F410}") CMGyroData  : public CMLogItem 
{
	virtual CMRotationRate __cdecl rotationRate() = 0 ;
};

class PASCALIMPLEMENTATION TCMGyroData : public Macapi::Objectivec::TOCGenericImport__2<_di_CMGyroDataClass,_di_CMGyroData>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_CMGyroDataClass,_di_CMGyroData> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TCMGyroData(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_CMGyroDataClass,_di_CMGyroData>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TCMGyroData() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 CMAttitudeReferenceFrameXArbitraryCorrectedZVertical = System::Int8(0x2);
static constexpr System::Int8 CMAttitudeReferenceFrameXArbitraryZVertical = System::Int8(0x1);
static constexpr System::Int8 CMAttitudeReferenceFrameXMagneticNorthZVertical = System::Int8(0x4);
static constexpr System::Int8 CMAttitudeReferenceFrameXTrueNorthZVertical = System::Int8(0x8);
static constexpr System::Int8 CMErrorDeviceRequiresMovement = System::Int8(0x65);
static constexpr System::Int8 CMErrorNULL = System::Int8(0x64);
static constexpr System::Int8 CMErrorTrueNorthNotAvailable = System::Int8(0x66);
static constexpr System::Int8 CMMagneticFieldCalibrationAccuracyHigh = System::Int8(0x2);
static constexpr System::Int8 CMMagneticFieldCalibrationAccuracyLow = System::Int8(0x0);
static constexpr System::Int8 CMMagneticFieldCalibrationAccuracyMedium = System::Int8(0x1);
static constexpr System::Int8 CMMagneticFieldCalibrationAccuracyUncalibrated = System::Int8(-1);
#define libCoreMotion u"/System/Library/Frameworks/CoreMotion.framework/CoreMotion"
}	/* namespace Coremotion */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_COREMOTION)
using namespace Iosapi::Coremotion;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_CoremotionHPP
