// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Gestures.pas' rev: 34.00 (Windows)

#ifndef Fmx_GesturesHPP
#define Fmx_GesturesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <FMX.Types.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.Generics.Collections.hpp>
#include <FMX.ActnList.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Gestures
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EGestureException;
class DELPHICLASS TGestureCollectionItem;
class DELPHICLASS TGestureCollection;
class DELPHICLASS TGestureManager;
class DELPHICLASS TGestureEngine;
class DELPHICLASS TCustomGestureRecognizer;
struct TStandardGestureData;
//-- type declarations -------------------------------------------------------
typedef System::Generics::Collections::TList__1<System::Types::TPointF>* TGesturePoints;

enum class DECLSPEC_DENUM TGestureNotification : unsigned char { gnChanged, gnDeleted };

typedef void __fastcall (__closure *TGestureItemChangeEvent)(System::TObject* Sender, TGestureNotification Action, Fmx::Types::TCustomGestureCollectionItem* Item);

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EGestureException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EGestureException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EGestureException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EGestureException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EGestureException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EGestureException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EGestureException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EGestureException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EGestureException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EGestureException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EGestureException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EGestureException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EGestureException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EGestureException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TGestureCollectionItem : public Fmx::Types::TCustomGestureCollectionItem
{
	typedef Fmx::Types::TCustomGestureCollectionItem inherited;
	
private:
	Fmx::Actnlist::TActionLink* FActionLink;
	bool FActionClient;
	int FDeviation;
	int FErrorMargin;
	Fmx::Types::TGestureID FGestureID;
	System::UnicodeString FName;
	Fmx::Types::TGestureOptions FOptions;
	Fmx::Types::TGesturePointArray FPoints;
	virtual void __fastcall DoActionClientChanged();
	void __fastcall ReadDeviation(System::Classes::TReader* Reader);
	void __fastcall ReadErrorMargin(System::Classes::TReader* Reader);
	void __fastcall ReadGestureID(System::Classes::TReader* Reader);
	void __fastcall ReadName(System::Classes::TReader* Reader);
	void __fastcall ReadPoints(System::Classes::TStream* Stream);
	void __fastcall SetActionClient(const bool Value);
	void __fastcall WriteDeviation(System::Classes::TWriter* Writer);
	void __fastcall WriteErrorMargin(System::Classes::TWriter* Writer);
	void __fastcall WriteGestureID(System::Classes::TWriter* Writer);
	void __fastcall WriteName(System::Classes::TWriter* Writer);
	void __fastcall WritePoints(System::Classes::TStream* Stream);
	
protected:
	virtual Fmx::Actnlist::TCustomAction* __fastcall GetAction();
	virtual Fmx::Actnlist::TActionLinkClass __fastcall GetActionLinkClass();
	virtual int __fastcall GetDeviation();
	virtual int __fastcall GetErrorMargin();
	virtual Fmx::Types::TGestureID __fastcall GetGestureID();
	virtual Fmx::Types::TGestureType __fastcall GetGestureType();
	virtual System::UnicodeString __fastcall GetName();
	virtual Fmx::Types::TGestureOptions __fastcall GetOptions();
	virtual Fmx::Types::TGesturePointArray __fastcall GetPoints();
	virtual void __fastcall ActionChange(System::Classes::TBasicAction* Sender, bool CheckDefaults);
	virtual void __fastcall DoActionChange(System::TObject* Sender);
	virtual void __fastcall SetAction(Fmx::Actnlist::TCustomAction* const Value);
	virtual void __fastcall SetDeviation(const int Value);
	virtual void __fastcall SetErrorMargin(const int Value);
	virtual void __fastcall SetGestureID(const Fmx::Types::TGestureID Value);
	virtual void __fastcall SetName(const System::UnicodeString Value);
	virtual void __fastcall SetOptions(const Fmx::Types::TGestureOptions Value);
	virtual void __fastcall SetPoints(const Fmx::Types::TGesturePointArray Value);
	
protected:
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual System::UnicodeString __fastcall GetDisplayName();
	
public:
	__fastcall virtual TGestureCollectionItem(System::Classes::TCollection* Collection);
	__fastcall virtual ~TGestureCollectionItem();
	__property Fmx::Actnlist::TActionLink* ActionLink = {read=FActionLink, write=FActionLink};
	
__published:
	__property Action;
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TGestureCollection : public Fmx::Types::TCustomGestureCollection
{
	typedef Fmx::Types::TCustomGestureCollection inherited;
	
private:
	TGestureManager* FGestureManager;
	TGestureItemChangeEvent FOnItemChange;
	
protected:
	bool FStreamGestureDetails;
	virtual Fmx::Types::TCustomGestureManager* __fastcall GetGestureManager();
	virtual void __fastcall Update(System::Classes::TCollectionItem* Item);
	
public:
	__fastcall virtual TGestureCollection()/* overload */;
	__fastcall virtual TGestureCollection(TGestureManager* const AGestureManager)/* overload */;
	__fastcall virtual ~TGestureCollection();
	HIDESBASE TGestureCollectionItem* __fastcall Add();
	virtual Fmx::Types::TCustomGestureCollectionItem* __fastcall AddGesture();
	virtual Fmx::Types::TCustomGestureCollectionItem* __fastcall FindGesture(Fmx::Types::TGestureID AGestureID)/* overload */;
	virtual Fmx::Types::TCustomGestureCollectionItem* __fastcall FindGesture(const System::UnicodeString AName)/* overload */;
	virtual Fmx::Types::TGestureID __fastcall GetUniqueGestureID();
	virtual void __fastcall RemoveGesture(Fmx::Types::TGestureID AGestureID);
	__property TGestureItemChangeEvent OnItemChange = {read=FOnItemChange, write=FOnItemChange};
};


class PASCALIMPLEMENTATION TGestureManager : public Fmx::Types::TCustomGestureManager
{
	typedef Fmx::Types::TCustomGestureManager inherited;
	
	
private:
	typedef System::Generics::Collections::TDictionary__2<System::Classes::TComponent*,TGestureCollection*>* TGestureControlList;
	
	typedef void __fastcall (__closure *TDesignerHook)(Fmx::Types::TCustomGestureCollectionItem* AGesture);
	
	
private:
	static System::Generics::Collections::TList__1<Fmx::Types::TCustomGestureManager*>* FInstanceList;
	static Fmx::Types::TGestureID FNextGestureID;
	static TGestureCollection* FRegisteredGestures;
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	static int __fastcall GetRegisteredGestureCount();
	static Fmx::Types::TGestureArray __fastcall GetRegisteredGestures();
	System::Generics::Collections::TDictionary__2<System::Classes::TComponent*,TGestureCollection*>* FControls;
	System::Sysutils::TFileName FFileName;
	bool FLoading;
	System::Generics::Collections::TList__1<System::Classes::TComponent*>* FNotifyList;
	TGestureCollection* FRecordedGestures;
	bool FSaved;
	System::Generics::Collections::TStack__1<System::Classes::TCollection*>* FStreamCollections;
	bool FUpdating;
	void __fastcall GestureItemChanged(System::TObject* Sender, TGestureNotification Action, Fmx::Types::TCustomGestureCollectionItem* Item);
	int __fastcall GetCustomGestureCount();
	Fmx::Types::TGestureArray __fastcall GetCustomGestures();
	int __fastcall GetRecordedGestureCount();
	Fmx::Types::TGestureArray __fastcall GetRecordedGestures();
	void __fastcall ReadControlData(System::Classes::TReader* Reader);
	void __fastcall ReadRecordedGestures(System::Classes::TReader* Reader);
	void __fastcall WriteControlData(System::Classes::TWriter* Writer);
	void __fastcall WriteRecordedGestures(System::Classes::TWriter* Writer);
	void __fastcall SetSensitivity(const float AValue);
	float __fastcall GetSensitivity();
	
protected:
	static TDesignerHook FDesignerHook;
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual Fmx::Types::TGestureArray __fastcall GetGestureList(System::Classes::TComponent* Control);
	virtual Fmx::Types::TStandardGestures __fastcall GetStandardGestures(System::Classes::TComponent* AControl);
	virtual void __fastcall Loaded();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall SetStandardGestures(System::Classes::TComponent* AControl, const Fmx::Types::TStandardGestures &AStandardGestures);
	__property bool Loading = {read=FLoading, nodefault};
	
public:
	static Fmx::Types::TGestureID __fastcall RegisterGesture(Fmx::Types::TCustomGestureCollectionItem* const AGesture);
	static void __fastcall UnregisterGesture(const Fmx::Types::TGestureID AGesture);
	/* static */ __property int RegisteredGestureCount = {read=GetRegisteredGestureCount, nodefault};
	/* static */ __property Fmx::Types::TGestureArray RegisteredGestures = {read=GetRegisteredGestures};
	__fastcall virtual TGestureManager(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TGestureManager();
	virtual Fmx::Types::TGestureID __fastcall AddRecordedGesture(Fmx::Types::TCustomGestureCollectionItem* const Item)/* overload */;
	void __fastcall ChangeNotification(System::Classes::TComponent* const AControl);
	virtual Fmx::Types::TCustomGestureCollectionItem* __fastcall FindCustomGesture(Fmx::Types::TGestureID AGestureID)/* overload */;
	virtual Fmx::Types::TCustomGestureCollectionItem* __fastcall FindCustomGesture(const System::UnicodeString AName)/* overload */;
	virtual Fmx::Types::TCustomGestureCollectionItem* __fastcall FindGesture(System::Classes::TComponent* const AControl, Fmx::Types::TGestureID AGestureID)/* overload */;
	virtual Fmx::Types::TCustomGestureCollectionItem* __fastcall FindGesture(System::Classes::TComponent* const AControl, const System::UnicodeString AName)/* overload */;
	void __fastcall LoadFromFile(const System::UnicodeString Filename);
	void __fastcall LoadFromStream(System::Classes::TStream* S);
	virtual void __fastcall RegisterControl(System::Classes::TComponent* const AControl);
	void __fastcall RemoveChangeNotification(System::Classes::TComponent* const AControl);
	virtual void __fastcall RemoveRecordedGesture(Fmx::Types::TGestureID AGestureID)/* overload */;
	virtual void __fastcall RemoveRecordedGesture(Fmx::Types::TCustomGestureCollectionItem* const AGesture)/* overload */;
	void __fastcall SaveToFile(const System::UnicodeString Filename);
	void __fastcall SaveToStream(System::Classes::TStream* const S);
	virtual bool __fastcall SelectGesture(System::Classes::TComponent* const AControl, Fmx::Types::TGestureID AGestureID)/* overload */;
	virtual bool __fastcall SelectGesture(System::Classes::TComponent* const AControl, const System::UnicodeString AName)/* overload */;
	void __fastcall SetRecordedGestures(const Fmx::Types::TGestureArray Gestures);
	virtual void __fastcall UnregisterControl(System::Classes::TComponent* const AControl);
	virtual void __fastcall UnselectGesture(System::Classes::TComponent* const AControl, Fmx::Types::TGestureID AGestureID);
	__property int CustomGestureCount = {read=GetCustomGestureCount, nodefault};
	__property Fmx::Types::TGestureArray CustomGestures = {read=GetCustomGestures};
	__property int RecordedGestureCount = {read=GetRecordedGestureCount, nodefault};
	__property Fmx::Types::TGestureArray RecordedGestures = {read=GetRecordedGestures};
	
__published:
	__property System::Sysutils::TFileName FileName = {read=FFileName, write=FFileName};
	__property float Sensitivity = {read=GetSensitivity, write=SetSensitivity};
};


#ifndef _WIN64
typedef System::TMetaClass* TGestureEngineClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TGestureEngineClass);
#endif /* _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* TCustomGestureRecognizerClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TCustomGestureRecognizerClass);
#endif /* _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TGestureEngine : public Fmx::Types::TCustomGestureEngine
{
	typedef Fmx::Types::TCustomGestureEngine inherited;
	
	
protected:
#ifndef _WIN64
	typedef System::TMetaClass* TGestureEngineType;
#else /* _WIN64 */
	_DECLARE_METACLASS(System::TMetaClass, TGestureEngineType);
#endif /* _WIN64 */
	
	
private:
	System::Types::TPointF FInitialPoint;
	static int FSensitivity;
	// __classmethod void __fastcall Create@();
	int __fastcall GetPointCount();
	Fmx::Types::TGesturePointArray __fastcall GetPoints();
	static void __fastcall SetSensitivity(const int Value);
	
protected:
	System::Generics::Collections::TList__1<System::Types::TPointF>* FPoints;
	virtual void __fastcall SetInitialPoint(const System::Types::TPointF &Value);
	static TCustomGestureRecognizer* FRecognizer;
	static TCustomGestureRecognizerClass FDefaultRecognizerClass;
	static TGestureEngineType FGestureEngineType;
	virtual __classmethod TGestureEngine* __fastcall GetGestureEngine(System::Classes::TComponent* const AControl) = 0 ;
	__classmethod void __fastcall GetCompleteGestureList(System::Classes::TComponent* const AControl, System::Generics::Collections::TList__1<Fmx::Types::TCustomGestureCollectionItem*>* const AGestureList);
	__classmethod virtual void __fastcall DoSetDefaultRecognizerClass(const TCustomGestureRecognizerClass Value);
	static void __fastcall SetDefaultRecognizerClass(const TCustomGestureRecognizerClass Value);
	__classmethod virtual TCustomGestureRecognizer* __fastcall DoGetRecognizer();
	static TCustomGestureRecognizer* __fastcall GetRecognizer();
	/* static */ __property TCustomGestureRecognizer* Recognizer = {read=GetRecognizer};
	/* static */ __property TCustomGestureRecognizerClass DefaultRecognizerClass = {read=FDefaultRecognizerClass, write=SetDefaultRecognizerClass};
	
public:
	void __fastcall AddPoint(const float X, const float Y);
	__classmethod void __fastcall CreateEngine(System::Classes::TComponent* const AControl);
	static bool __fastcall IsGesture(const System::Types::TPointF *Points, const int Points_High, System::Generics::Collections::TList__1<Fmx::Types::TCustomGestureCollectionItem*>* const Items, Fmx::Types::TGestureTypes GestureTypes, Fmx::Types::TGestureEventInfo &EventInfo);
	/* static */ __property int Sensitivity = {read=FSensitivity, write=SetSensitivity, nodefault};
	__property System::Types::TPointF InitialPoint = {read=FInitialPoint, write=SetInitialPoint};
	__property int PointCount = {read=GetPointCount, nodefault};
	__property Fmx::Types::TGesturePointArray Points = {read=GetPoints};
	virtual void __fastcall BroadcastGesture(System::Classes::TComponent* const AControl, const Fmx::Types::TGestureEventInfo &EventInfo);
	void __fastcall ClearPoints();
	__fastcall virtual ~TGestureEngine();
	
private:
	// __classmethod void __fastcall Destroy@();
public:
	/* TCustomGestureEngine.Create */ inline __fastcall virtual TGestureEngine(System::Classes::TComponent* const AControl) /* = 0 */ : Fmx::Types::TCustomGestureEngine(AControl) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCustomGestureRecognizer : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	static int __fastcall IsPointsGesture(const System::Types::TPointF *Points, const int Points_High, const System::Types::TPointF *GesturePoints, const int GesturePoints_High, Fmx::Types::TGestureID GestureID, int Deviation, int ErrorMargin, double *Percentages, const int Percentages_High);
	static int __fastcall IsScratchout(const System::Types::TPointF *Points, const int Points_High, Fmx::Types::TGestureID GestureID, const int Deviation, const int ErrorMargin, double *Percentages, const int Percentages_High);
	static Fmx::Types::TGesturePointArray __fastcall ReverseGesturePoints(const System::Types::TPointF *Points, const int Points_High);
	static Fmx::Types::TGesturePointArray __fastcall CopyGesturePoints(System::Generics::Collections::TList__1<System::Types::TPointF>* const Points);
	static Fmx::Types::TGesturePointArray __fastcall InterpolateGesturePoints(const System::Types::TPointF *Points, const int Points_High);
	static Fmx::Types::TGesturePointArray __fastcall RemoveDuplicatedGesturePoints(const System::Types::TPointF *Points, const int Points_High);
	static Fmx::Types::TGesturePointArray __fastcall RotateGesturePoints(const System::Types::TPointF *Points, const int Points_High, const System::Types::TPointF *GesturePoints, const int GesturePoints_High, int ErrorMargin, double &Angle);
	static Fmx::Types::TGesturePointArray __fastcall NormalizeGesturePoints(const System::Types::TPointF *Points, const int Points_High);
	static Fmx::Types::TGesturePointArray __fastcall ScaleGesturePoints(const System::Types::TPointF *Points, const int Points_High, const System::Types::TPointF *GesturePoints, const int GesturePoints_High, const int MinScale, const bool Scaling = false);
	
public:
	virtual float __fastcall Match(const System::Types::TPointF *Points, const int Points_High, const System::Types::TPointF *GesturePoints, const int GesturePoints_High, const Fmx::Types::TGestureOptions Options, Fmx::Types::TGestureID GestureID, int Deviation, int ErrorMargin) = 0 ;
	virtual Fmx::Types::TGesturePointArray __fastcall NormalizePoints(const System::Types::TPointF *Points, const int Points_High);
	virtual Fmx::Types::TGesturePointArray __fastcall RotatePoints(const System::Types::TPointF *Points, const int Points_High, const System::Types::TPointF *GesturePoints, const int GesturePoints_High, int ErrorMargin, double &Angle);
	virtual Fmx::Types::TGesturePointArray __fastcall ScalePoints(const System::Types::TPointF *Points, const int Points_High, const System::Types::TPointF *GesturePoints, const int GesturePoints_High, int MinScale, bool Scaling = false);
	virtual Fmx::Types::TGesturePointArray __fastcall RemoveDuplicates(const System::Types::TPointF *Points, const int Points_High);
	virtual void __fastcall Reset() = 0 ;
public:
	/* TObject.Create */ inline __fastcall TCustomGestureRecognizer() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCustomGestureRecognizer() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

struct DECLSPEC_DRECORD TStandardGestureData
{
public:
	Fmx::Types::TGesturePointArray Points;
	Fmx::Types::TGestureID GestureID;
	Fmx::Types::TGestureOptions Options;
	int Deviation;
	int ErrorMargin;
};


//-- var, const, procedure ---------------------------------------------------
static const short cgiFirst = short(-512);
static const System::Int8 cgiLast = System::Int8(-1);
static const short rgiFirst = short(-1024);
static const short rgiLast = short(-513);
extern DELPHI_PACKAGE Fmx::Types::TGestureTypes CustomGestureTypes;
extern DELPHI_PACKAGE bool __fastcall GestureToIdent(int ID, System::UnicodeString &Ident);
extern DELPHI_PACKAGE bool __fastcall IdentToGesture(const System::UnicodeString Ident, int &ID);
extern DELPHI_PACKAGE bool __fastcall FindStandardGesture(Fmx::Types::TGestureID AGestureID, TStandardGestureData &AGestureData)/* overload */;
extern DELPHI_PACKAGE bool __fastcall FindStandardGesture(const System::UnicodeString AName, Fmx::Types::TGestureID &AGestureID)/* overload */;
}	/* namespace Gestures */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_GESTURES)
using namespace Fmx::Gestures;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_GesturesHPP
