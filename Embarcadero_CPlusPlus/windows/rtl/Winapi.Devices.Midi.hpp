// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Devices.Midi.pas' rev: 34.00 (Windows)

#ifndef Winapi_Devices_MidiHPP
#define Winapi_Devices_MidiHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.WinRT.hpp>
#include <System.Types.hpp>
#include <System.Win.WinRT.hpp>
#include <Winapi.CommonTypes.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Devices
{
namespace Midi
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IMidiMessage;
typedef System::DelphiInterface<IMidiMessage> _di_IMidiMessage;
__interface DELPHIINTERFACE IMidiNoteOffMessage;
typedef System::DelphiInterface<IMidiNoteOffMessage> _di_IMidiNoteOffMessage;
__interface DELPHIINTERFACE IMidiNoteOnMessage;
typedef System::DelphiInterface<IMidiNoteOnMessage> _di_IMidiNoteOnMessage;
__interface DELPHIINTERFACE IMidiPolyphonicKeyPressureMessage;
typedef System::DelphiInterface<IMidiPolyphonicKeyPressureMessage> _di_IMidiPolyphonicKeyPressureMessage;
__interface DELPHIINTERFACE IMidiControlChangeMessage;
typedef System::DelphiInterface<IMidiControlChangeMessage> _di_IMidiControlChangeMessage;
__interface DELPHIINTERFACE IMidiProgramChangeMessage;
typedef System::DelphiInterface<IMidiProgramChangeMessage> _di_IMidiProgramChangeMessage;
__interface DELPHIINTERFACE IMidiChannelPressureMessage;
typedef System::DelphiInterface<IMidiChannelPressureMessage> _di_IMidiChannelPressureMessage;
__interface DELPHIINTERFACE IMidiPitchBendChangeMessage;
typedef System::DelphiInterface<IMidiPitchBendChangeMessage> _di_IMidiPitchBendChangeMessage;
__interface DELPHIINTERFACE IMidiTimeCodeMessage;
typedef System::DelphiInterface<IMidiTimeCodeMessage> _di_IMidiTimeCodeMessage;
__interface DELPHIINTERFACE IMidiSongPositionPointerMessage;
typedef System::DelphiInterface<IMidiSongPositionPointerMessage> _di_IMidiSongPositionPointerMessage;
__interface DELPHIINTERFACE IMidiSongSelectMessage;
typedef System::DelphiInterface<IMidiSongSelectMessage> _di_IMidiSongSelectMessage;
__interface DELPHIINTERFACE IMidiNoteOffMessageFactory;
typedef System::DelphiInterface<IMidiNoteOffMessageFactory> _di_IMidiNoteOffMessageFactory;
__interface DELPHIINTERFACE IMidiNoteOnMessageFactory;
typedef System::DelphiInterface<IMidiNoteOnMessageFactory> _di_IMidiNoteOnMessageFactory;
__interface DELPHIINTERFACE IMidiPolyphonicKeyPressureMessageFactory;
typedef System::DelphiInterface<IMidiPolyphonicKeyPressureMessageFactory> _di_IMidiPolyphonicKeyPressureMessageFactory;
__interface DELPHIINTERFACE IMidiControlChangeMessageFactory;
typedef System::DelphiInterface<IMidiControlChangeMessageFactory> _di_IMidiControlChangeMessageFactory;
__interface DELPHIINTERFACE IMidiProgramChangeMessageFactory;
typedef System::DelphiInterface<IMidiProgramChangeMessageFactory> _di_IMidiProgramChangeMessageFactory;
__interface DELPHIINTERFACE IMidiChannelPressureMessageFactory;
typedef System::DelphiInterface<IMidiChannelPressureMessageFactory> _di_IMidiChannelPressureMessageFactory;
__interface DELPHIINTERFACE IMidiPitchBendChangeMessageFactory;
typedef System::DelphiInterface<IMidiPitchBendChangeMessageFactory> _di_IMidiPitchBendChangeMessageFactory;
__interface DELPHIINTERFACE IMidiSystemExclusiveMessageFactory;
typedef System::DelphiInterface<IMidiSystemExclusiveMessageFactory> _di_IMidiSystemExclusiveMessageFactory;
__interface DELPHIINTERFACE IMidiTimeCodeMessageFactory;
typedef System::DelphiInterface<IMidiTimeCodeMessageFactory> _di_IMidiTimeCodeMessageFactory;
__interface DELPHIINTERFACE IMidiSongPositionPointerMessageFactory;
typedef System::DelphiInterface<IMidiSongPositionPointerMessageFactory> _di_IMidiSongPositionPointerMessageFactory;
__interface DELPHIINTERFACE IMidiSongSelectMessageFactory;
typedef System::DelphiInterface<IMidiSongSelectMessageFactory> _di_IMidiSongSelectMessageFactory;
__interface DELPHIINTERFACE IMidiMessageReceivedEventArgs;
typedef System::DelphiInterface<IMidiMessageReceivedEventArgs> _di_IMidiMessageReceivedEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IMidiInPort__IMidiMessageReceivedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IMidiInPort__IMidiMessageReceivedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IMidiInPort__IMidiMessageReceivedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IMidiInPort__IMidiMessageReceivedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IMidiInPort__IMidiMessageReceivedEventArgs> _di_TypedEventHandler_2__IMidiInPort__IMidiMessageReceivedEventArgs;
__interface DELPHIINTERFACE IMidiInPort;
typedef System::DelphiInterface<IMidiInPort> _di_IMidiInPort;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IMidiInPort_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IMidiInPort_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IMidiInPort_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IMidiInPort;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IMidiInPort> _di_AsyncOperationCompletedHandler_1__IMidiInPort;
__interface DELPHIINTERFACE IAsyncOperation_1__IMidiInPort_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IMidiInPort_Base> _di_IAsyncOperation_1__IMidiInPort_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IMidiInPort;
typedef System::DelphiInterface<IAsyncOperation_1__IMidiInPort> _di_IAsyncOperation_1__IMidiInPort;
__interface DELPHIINTERFACE IMidiInPortStatics;
typedef System::DelphiInterface<IMidiInPortStatics> _di_IMidiInPortStatics;
__interface DELPHIINTERFACE IMidiOutPort;
typedef System::DelphiInterface<IMidiOutPort> _di_IMidiOutPort;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IMidiOutPort_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IMidiOutPort_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IMidiOutPort_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IMidiOutPort;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IMidiOutPort> _di_AsyncOperationCompletedHandler_1__IMidiOutPort;
__interface DELPHIINTERFACE IAsyncOperation_1__IMidiOutPort_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IMidiOutPort_Base> _di_IAsyncOperation_1__IMidiOutPort_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IMidiOutPort;
typedef System::DelphiInterface<IAsyncOperation_1__IMidiOutPort> _di_IAsyncOperation_1__IMidiOutPort;
__interface DELPHIINTERFACE IMidiOutPortStatics;
typedef System::DelphiInterface<IMidiOutPortStatics> _di_IMidiOutPortStatics;
__interface DELPHIINTERFACE IMidiSynthesizer;
typedef System::DelphiInterface<IMidiSynthesizer> _di_IMidiSynthesizer;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IMidiSynthesizer_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IMidiSynthesizer_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IMidiSynthesizer_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IMidiSynthesizer;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IMidiSynthesizer> _di_AsyncOperationCompletedHandler_1__IMidiSynthesizer;
__interface DELPHIINTERFACE IAsyncOperation_1__IMidiSynthesizer_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IMidiSynthesizer_Base> _di_IAsyncOperation_1__IMidiSynthesizer_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IMidiSynthesizer;
typedef System::DelphiInterface<IAsyncOperation_1__IMidiSynthesizer> _di_IAsyncOperation_1__IMidiSynthesizer;
__interface DELPHIINTERFACE IMidiSynthesizerStatics;
typedef System::DelphiInterface<IMidiSynthesizerStatics> _di_IMidiSynthesizerStatics;
class DELPHICLASS TMidiNoteOffMessage;
class DELPHICLASS TMidiNoteOnMessage;
class DELPHICLASS TMidiPolyphonicKeyPressureMessage;
class DELPHICLASS TMidiControlChangeMessage;
class DELPHICLASS TMidiProgramChangeMessage;
class DELPHICLASS TMidiChannelPressureMessage;
class DELPHICLASS TMidiPitchBendChangeMessage;
class DELPHICLASS TMidiSystemExclusiveMessage;
class DELPHICLASS TMidiTimeCodeMessage;
class DELPHICLASS TMidiSongPositionPointerMessage;
class DELPHICLASS TMidiSongSelectMessage;
class DELPHICLASS TMidiTuneRequestMessage;
class DELPHICLASS TMidiTimingClockMessage;
class DELPHICLASS TMidiStartMessage;
class DELPHICLASS TMidiContinueMessage;
class DELPHICLASS TMidiStopMessage;
class DELPHICLASS TMidiActiveSensingMessage;
class DELPHICLASS TMidiSystemResetMessage;
class DELPHICLASS TMidiInPort;
class DELPHICLASS TMidiOutPort;
class DELPHICLASS TMidiSynthesizer;
//-- type declarations -------------------------------------------------------
typedef _di_IMidiMessage *PIMidiMessage;

typedef _di_IMidiNoteOffMessage *PIMidiNoteOffMessage;

typedef _di_IMidiNoteOnMessage *PIMidiNoteOnMessage;

typedef _di_IMidiPolyphonicKeyPressureMessage *PIMidiPolyphonicKeyPressureMessage;

typedef _di_IMidiControlChangeMessage *PIMidiControlChangeMessage;

typedef _di_IMidiProgramChangeMessage *PIMidiProgramChangeMessage;

typedef _di_IMidiChannelPressureMessage *PIMidiChannelPressureMessage;

typedef _di_IMidiPitchBendChangeMessage *PIMidiPitchBendChangeMessage;

typedef _di_IMidiTimeCodeMessage *PIMidiTimeCodeMessage;

typedef _di_IMidiSongPositionPointerMessage *PIMidiSongPositionPointerMessage;

typedef _di_IMidiSongSelectMessage *PIMidiSongSelectMessage;

typedef _di_IMidiNoteOffMessageFactory *PIMidiNoteOffMessageFactory;

typedef _di_IMidiNoteOnMessageFactory *PIMidiNoteOnMessageFactory;

typedef _di_IMidiPolyphonicKeyPressureMessageFactory *PIMidiPolyphonicKeyPressureMessageFactory;

typedef _di_IMidiControlChangeMessageFactory *PIMidiControlChangeMessageFactory;

typedef _di_IMidiProgramChangeMessageFactory *PIMidiProgramChangeMessageFactory;

typedef _di_IMidiChannelPressureMessageFactory *PIMidiChannelPressureMessageFactory;

typedef _di_IMidiPitchBendChangeMessageFactory *PIMidiPitchBendChangeMessageFactory;

typedef _di_IMidiSystemExclusiveMessageFactory *PIMidiSystemExclusiveMessageFactory;

typedef _di_IMidiTimeCodeMessageFactory *PIMidiTimeCodeMessageFactory;

typedef _di_IMidiSongPositionPointerMessageFactory *PIMidiSongPositionPointerMessageFactory;

typedef _di_IMidiSongSelectMessageFactory *PIMidiSongSelectMessageFactory;

typedef _di_IMidiMessageReceivedEventArgs *PIMidiMessageReceivedEventArgs;

typedef _di_TypedEventHandler_2__IMidiInPort__IMidiMessageReceivedEventArgs *PTypedEventHandler_2__IMidiInPort__IMidiMessageReceivedEventArgs;

typedef _di_IMidiInPort *PIMidiInPort;

typedef _di_AsyncOperationCompletedHandler_1__IMidiInPort *PAsyncOperationCompletedHandler_1__IMidiInPort;

typedef _di_IAsyncOperation_1__IMidiInPort *PIAsyncOperation_1__IMidiInPort;

typedef _di_IMidiInPortStatics *PIMidiInPortStatics;

typedef _di_IMidiOutPort *PIMidiOutPort;

typedef _di_AsyncOperationCompletedHandler_1__IMidiOutPort *PAsyncOperationCompletedHandler_1__IMidiOutPort;

typedef _di_IAsyncOperation_1__IMidiOutPort *PIAsyncOperation_1__IMidiOutPort;

typedef _di_IMidiOutPortStatics *PIMidiOutPortStatics;

typedef _di_IMidiSynthesizer *PIMidiSynthesizer;

typedef _di_AsyncOperationCompletedHandler_1__IMidiSynthesizer *PAsyncOperationCompletedHandler_1__IMidiSynthesizer;

typedef _di_IAsyncOperation_1__IMidiSynthesizer *PIAsyncOperation_1__IMidiSynthesizer;

typedef _di_IMidiSynthesizerStatics *PIMidiSynthesizerStatics;

__interface  INTERFACE_UUID("{79767945-1094-4283-9BE0-289FC0EE8334}") IMidiMessage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Timestamp(Winapi::Commontypes::TimeSpan &__get_Timestamp_result) = 0 ;
	virtual HRESULT __safecall get_RawData(Winapi::Commontypes::_di_IBuffer &__get_RawData_result) = 0 ;
	virtual HRESULT __safecall get_Type(Winapi::Commontypes::MidiMessageType &__get_Type_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IBuffer _scw_get_RawData() { Winapi::Commontypes::_di_IBuffer __r; HRESULT __hr = get_RawData(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IBuffer RawData = {read=_scw_get_RawData};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_Timestamp() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_Timestamp(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan Timestamp = {read=_scw_get_Timestamp};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::MidiMessageType _scw_get_Type() { Winapi::Commontypes::MidiMessageType __r; HRESULT __hr = get_Type(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::MidiMessageType Type = {read=_scw_get_Type};
};

__interface  INTERFACE_UUID("{16FD8AF4-198E-4D8F-A654-D305A293548F}") IMidiNoteOffMessage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Channel(System::Byte &__get_Channel_result) = 0 ;
	virtual HRESULT __safecall get_Note(System::Byte &__get_Note_result) = 0 ;
	virtual HRESULT __safecall get_Velocity(System::Byte &__get_Velocity_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_Channel() { System::Byte __r; HRESULT __hr = get_Channel(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte Channel = {read=_scw_get_Channel};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_Note() { System::Byte __r; HRESULT __hr = get_Note(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte Note = {read=_scw_get_Note};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_Velocity() { System::Byte __r; HRESULT __hr = get_Velocity(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte Velocity = {read=_scw_get_Velocity};
};

__interface  INTERFACE_UUID("{E0224AF5-6181-46DD-AFA2-410004C057AA}") IMidiNoteOnMessage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Channel(System::Byte &__get_Channel_result) = 0 ;
	virtual HRESULT __safecall get_Note(System::Byte &__get_Note_result) = 0 ;
	virtual HRESULT __safecall get_Velocity(System::Byte &__get_Velocity_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_Channel() { System::Byte __r; HRESULT __hr = get_Channel(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte Channel = {read=_scw_get_Channel};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_Note() { System::Byte __r; HRESULT __hr = get_Note(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte Note = {read=_scw_get_Note};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_Velocity() { System::Byte __r; HRESULT __hr = get_Velocity(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte Velocity = {read=_scw_get_Velocity};
};

__interface  INTERFACE_UUID("{1F7337FE-ACE8-48A0-868E-7CDBF20F04D6}") IMidiPolyphonicKeyPressureMessage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Channel(System::Byte &__get_Channel_result) = 0 ;
	virtual HRESULT __safecall get_Note(System::Byte &__get_Note_result) = 0 ;
	virtual HRESULT __safecall get_Pressure(System::Byte &__get_Pressure_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_Channel() { System::Byte __r; HRESULT __hr = get_Channel(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte Channel = {read=_scw_get_Channel};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_Note() { System::Byte __r; HRESULT __hr = get_Note(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte Note = {read=_scw_get_Note};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_Pressure() { System::Byte __r; HRESULT __hr = get_Pressure(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte Pressure = {read=_scw_get_Pressure};
};

__interface  INTERFACE_UUID("{B7E15F83-780D-405F-B781-3E1598C97F40}") IMidiControlChangeMessage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Channel(System::Byte &__get_Channel_result) = 0 ;
	virtual HRESULT __safecall get_Controller(System::Byte &__get_Controller_result) = 0 ;
	virtual HRESULT __safecall get_ControlValue(System::Byte &__get_ControlValue_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_Channel() { System::Byte __r; HRESULT __hr = get_Channel(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte Channel = {read=_scw_get_Channel};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_ControlValue() { System::Byte __r; HRESULT __hr = get_ControlValue(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte ControlValue = {read=_scw_get_ControlValue};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_Controller() { System::Byte __r; HRESULT __hr = get_Controller(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte Controller = {read=_scw_get_Controller};
};

__interface  INTERFACE_UUID("{9CBB3C78-7A3E-4327-AA98-20B8E4485AF8}") IMidiProgramChangeMessage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Channel(System::Byte &__get_Channel_result) = 0 ;
	virtual HRESULT __safecall get_Program(System::Byte &__get_Program_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_Channel() { System::Byte __r; HRESULT __hr = get_Channel(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte Channel = {read=_scw_get_Channel};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_Program() { System::Byte __r; HRESULT __hr = get_Program(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte Program = {read=_scw_get_Program};
};

__interface  INTERFACE_UUID("{BE1FA860-62B4-4D52-A37E-92E54D35B909}") IMidiChannelPressureMessage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Channel(System::Byte &__get_Channel_result) = 0 ;
	virtual HRESULT __safecall get_Pressure(System::Byte &__get_Pressure_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_Channel() { System::Byte __r; HRESULT __hr = get_Channel(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte Channel = {read=_scw_get_Channel};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_Pressure() { System::Byte __r; HRESULT __hr = get_Pressure(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte Pressure = {read=_scw_get_Pressure};
};

__interface  INTERFACE_UUID("{29DF4CB1-2E9F-4FAF-8C2B-9CB82A9079CA}") IMidiPitchBendChangeMessage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Channel(System::Byte &__get_Channel_result) = 0 ;
	virtual HRESULT __safecall get_Bend(System::Word &__get_Bend_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Word _scw_get_Bend() { System::Word __r; HRESULT __hr = get_Bend(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Word Bend = {read=_scw_get_Bend};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_Channel() { System::Byte __r; HRESULT __hr = get_Channel(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte Channel = {read=_scw_get_Channel};
};

__interface  INTERFACE_UUID("{0BF7087D-FA63-4A1C-8DEB-C0E87796A6D7}") IMidiTimeCodeMessage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_FrameType(System::Byte &__get_FrameType_result) = 0 ;
	virtual HRESULT __safecall get_Values(System::Byte &__get_Values_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_FrameType() { System::Byte __r; HRESULT __hr = get_FrameType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte FrameType = {read=_scw_get_FrameType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_Values() { System::Byte __r; HRESULT __hr = get_Values(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte Values = {read=_scw_get_Values};
};

__interface  INTERFACE_UUID("{4CA50C56-EC5E-4AE4-A115-88DC57CC2B79}") IMidiSongPositionPointerMessage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Beats(System::Word &__get_Beats_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Word _scw_get_Beats() { System::Word __r; HRESULT __hr = get_Beats(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Word Beats = {read=_scw_get_Beats};
};

__interface  INTERFACE_UUID("{49F0F27F-6D83-4741-A5BF-4629F6BE974F}") IMidiSongSelectMessage  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Song(System::Byte &__get_Song_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_get_Song() { System::Byte __r; HRESULT __hr = get_Song(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte Song = {read=_scw_get_Song};
};

__interface  INTERFACE_UUID("{A6B240E0-A749-425F-8AF4-A4D979CC15B5}") IMidiNoteOffMessageFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateMidiNoteOffMessage(System::Byte channel, System::Byte note, System::Byte velocity, _di_IMidiNoteOffMessage &__CreateMidiNoteOffMessage_result) = 0 ;
};

__interface  INTERFACE_UUID("{9B4280A0-59C1-420E-B517-15A10AA9606B}") IMidiNoteOnMessageFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateMidiNoteOnMessage(System::Byte channel, System::Byte note, System::Byte velocity, _di_IMidiNoteOnMessage &__CreateMidiNoteOnMessage_result) = 0 ;
};

__interface  INTERFACE_UUID("{E98F483E-C4B3-4DD2-917C-E349815A1B3B}") IMidiPolyphonicKeyPressureMessageFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateMidiPolyphonicKeyPressureMessage(System::Byte channel, System::Byte note, System::Byte pressure, _di_IMidiPolyphonicKeyPressureMessage &__CreateMidiPolyphonicKeyPressureMessage_result) = 0 ;
};

__interface  INTERFACE_UUID("{2AB14321-956C-46AD-9752-F87F55052FE3}") IMidiControlChangeMessageFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateMidiControlChangeMessage(System::Byte channel, System::Byte controller, System::Byte controlValue, _di_IMidiControlChangeMessage &__CreateMidiControlChangeMessage_result) = 0 ;
};

__interface  INTERFACE_UUID("{D6B04387-524B-4104-9C99-6572BFD2E261}") IMidiProgramChangeMessageFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateMidiProgramChangeMessage(System::Byte channel, System::Byte program, _di_IMidiProgramChangeMessage &__CreateMidiProgramChangeMessage_result) = 0 ;
};

__interface  INTERFACE_UUID("{6218ED2F-2284-412A-94CF-10FB04842C6C}") IMidiChannelPressureMessageFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateMidiChannelPressureMessage(System::Byte channel, System::Byte pressure, _di_IMidiChannelPressureMessage &__CreateMidiChannelPressureMessage_result) = 0 ;
};

__interface  INTERFACE_UUID("{F5EEDF55-CFC8-4926-B30E-A3622393306C}") IMidiPitchBendChangeMessageFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateMidiPitchBendChangeMessage(System::Byte channel, System::Word bend, _di_IMidiPitchBendChangeMessage &__CreateMidiPitchBendChangeMessage_result) = 0 ;
};

__interface  INTERFACE_UUID("{083DE222-3B74-4320-9B42-0CA8545F8A24}") IMidiSystemExclusiveMessageFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateMidiSystemExclusiveMessage(Winapi::Commontypes::_di_IBuffer rawData, _di_IMidiMessage &__CreateMidiSystemExclusiveMessage_result) = 0 ;
};

__interface  INTERFACE_UUID("{EB3099C5-771C-40DE-B961-175A7489A85E}") IMidiTimeCodeMessageFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateMidiTimeCodeMessage(System::Byte frameType, System::Byte values, _di_IMidiTimeCodeMessage &__CreateMidiTimeCodeMessage_result) = 0 ;
};

__interface  INTERFACE_UUID("{9C00E996-F10B-4FEA-B395-F5D6CF80F64E}") IMidiSongPositionPointerMessageFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateMidiSongPositionPointerMessage(System::Word beats, _di_IMidiSongPositionPointerMessage &__CreateMidiSongPositionPointerMessage_result) = 0 ;
};

__interface  INTERFACE_UUID("{848878E4-8748-4129-A66C-A05493F75DAA}") IMidiSongSelectMessageFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateMidiSongSelectMessage(System::Byte song, _di_IMidiSongSelectMessage &__CreateMidiSongSelectMessage_result) = 0 ;
};

__interface  INTERFACE_UUID("{76566E56-F328-4B51-907D-B3A8CE96BF80}") IMidiMessageReceivedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Message(_di_IMidiMessage &__get_Message_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IMidiMessage _scw_get_Message() { _di_IMidiMessage __r; HRESULT __hr = get_Message(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IMidiMessage Message = {read=_scw_get_Message};
};

__interface  INTERFACE_UUID("{50017240-CC39-5775-8A6B-F6F22386BFCA}") TypedEventHandler_2__IMidiInPort__IMidiMessageReceivedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{405CE118-C844-59EB-91B5-61568095BA74}") TypedEventHandler_2__IMidiInPort__IMidiMessageReceivedEventArgs  : public TypedEventHandler_2__IMidiInPort__IMidiMessageReceivedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IMidiInPort sender, _di_IMidiMessageReceivedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{D5C1D9DB-971A-4EAF-A23D-EA19FE607FF9}") IMidiInPort  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall add_MessageReceived(_di_TypedEventHandler_2__IMidiInPort__IMidiMessageReceivedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_MessageReceived_result) = 0 ;
	virtual HRESULT __safecall remove_MessageReceived(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	virtual HRESULT __safecall get_DeviceId(HSTRING &__get_DeviceId_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DeviceId() { HSTRING __r; HRESULT __hr = get_DeviceId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DeviceId = {read=_scw_get_DeviceId};
};

__interface  INTERFACE_UUID("{6C090FB2-8099-558F-8A92-9A8EA806E6FB}") AsyncOperationCompletedHandler_1__IMidiInPort_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{C57FE1CC-0C94-540B-8223-7E4F273FD7F2}") AsyncOperationCompletedHandler_1__IMidiInPort  : public AsyncOperationCompletedHandler_1__IMidiInPort_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IMidiInPort asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{CC664F0E-EDB1-55C8-9EF7-EC9007E4561C}") IAsyncOperation_1__IMidiInPort_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{18E03B23-441E-5EDE-8E92-A457ABECF3DD}") IAsyncOperation_1__IMidiInPort  : public IAsyncOperation_1__IMidiInPort_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IMidiInPort handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IMidiInPort &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IMidiInPort &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IMidiInPort _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IMidiInPort __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IMidiInPort Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{44C439DC-67FF-4A6E-8BAC-FDB6610CF296}") IMidiInPortStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall FromIdAsync(HSTRING deviceId, _di_IAsyncOperation_1__IMidiInPort &__FromIdAsync_result) = 0 ;
	virtual HRESULT __safecall GetDeviceSelector(HSTRING &__GetDeviceSelector_result) = 0 ;
};

__interface  INTERFACE_UUID("{931D6D9F-57A2-4A3A-ADB8-4640886F6693}") IMidiOutPort  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall SendMessage(_di_IMidiMessage midiMessage) = 0 ;
	virtual HRESULT __safecall SendBuffer(Winapi::Commontypes::_di_IBuffer midiData) = 0 ;
	virtual HRESULT __safecall get_DeviceId(HSTRING &__get_DeviceId_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DeviceId() { HSTRING __r; HRESULT __hr = get_DeviceId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DeviceId = {read=_scw_get_DeviceId};
};

__interface  INTERFACE_UUID("{EED37805-2A49-59B4-B4D4-1188C6819122}") AsyncOperationCompletedHandler_1__IMidiOutPort_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{EED37805-2A49-59B4-B4D4-1188C6819122}") AsyncOperationCompletedHandler_1__IMidiOutPort  : public AsyncOperationCompletedHandler_1__IMidiOutPort_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IMidiOutPort asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{32699A4D-1CC0-5A1C-9DA6-875197875086}") IAsyncOperation_1__IMidiOutPort_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{32699A4D-1CC0-5A1C-9DA6-875197875086}") IAsyncOperation_1__IMidiOutPort  : public IAsyncOperation_1__IMidiOutPort_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IMidiOutPort handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IMidiOutPort &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IMidiOutPort &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IMidiOutPort _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IMidiOutPort __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IMidiOutPort Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{065CC3E9-0F88-448B-9B64-A95826C65B8F}") IMidiOutPortStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall FromIdAsync(HSTRING deviceId, _di_IAsyncOperation_1__IMidiOutPort &__FromIdAsync_result) = 0 ;
	virtual HRESULT __safecall GetDeviceSelector(HSTRING &__GetDeviceSelector_result) = 0 ;
};

__interface  INTERFACE_UUID("{F0DA155E-DB90-405F-B8AE-21D2E17F2E45}") IMidiSynthesizer  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_AudioDevice(Winapi::Commontypes::_di_IDeviceInformation &__get_AudioDevice_result) = 0 ;
	virtual HRESULT __safecall get_Volume(double &__get_Volume_result) = 0 ;
	virtual HRESULT __safecall put_Volume(double value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IDeviceInformation _scw_get_AudioDevice() { Winapi::Commontypes::_di_IDeviceInformation __r; HRESULT __hr = get_AudioDevice(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IDeviceInformation AudioDevice = {read=_scw_get_AudioDevice};
	#pragma option push -w-inl
	/* safecall wrapper */ inline double _scw_get_Volume() { double __r; HRESULT __hr = get_Volume(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property double Volume = {read=_scw_get_Volume, write=put_Volume};
};

__interface  INTERFACE_UUID("{5D716335-D087-516F-AD0A-63F61CBCF342}") AsyncOperationCompletedHandler_1__IMidiSynthesizer_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{D26AED51-C3FB-55A7-B983-E077BFC95748}") AsyncOperationCompletedHandler_1__IMidiSynthesizer  : public AsyncOperationCompletedHandler_1__IMidiSynthesizer_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IMidiSynthesizer asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{9388B978-13F1-5E37-8133-94430D90DD50}") IAsyncOperation_1__IMidiSynthesizer_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{6CF9602B-DAAF-568D-AEAE-24B0B87A64E1}") IAsyncOperation_1__IMidiSynthesizer  : public IAsyncOperation_1__IMidiSynthesizer_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IMidiSynthesizer handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IMidiSynthesizer &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IMidiSynthesizer &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IMidiSynthesizer _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IMidiSynthesizer __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IMidiSynthesizer Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{4224EAA8-6629-4D6B-AA8F-D4521A5A31CE}") IMidiSynthesizerStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateAsync(_di_IAsyncOperation_1__IMidiSynthesizer &__CreateAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall CreateAsync(Winapi::Commontypes::_di_IDeviceInformation audioDevice, _di_IAsyncOperation_1__IMidiSynthesizer &__CreateAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall IsSynthesizer(Winapi::Commontypes::_di_IDeviceInformation midiDevice, bool &__IsSynthesizer_result) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMidiNoteOffMessage : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiNoteOffMessageFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiNoteOffMessageFactory> inherited;
	
public:
	static _di_IMidiNoteOffMessage __fastcall CreateMidiNoteOffMessage(System::Byte channel, System::Byte note, System::Byte velocity);
public:
	/* TObject.Create */ inline __fastcall TMidiNoteOffMessage() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiNoteOffMessageFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMidiNoteOffMessage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMidiNoteOnMessage : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiNoteOnMessageFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiNoteOnMessageFactory> inherited;
	
public:
	static _di_IMidiNoteOnMessage __fastcall CreateMidiNoteOnMessage(System::Byte channel, System::Byte note, System::Byte velocity);
public:
	/* TObject.Create */ inline __fastcall TMidiNoteOnMessage() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiNoteOnMessageFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMidiNoteOnMessage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMidiPolyphonicKeyPressureMessage : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiPolyphonicKeyPressureMessageFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiPolyphonicKeyPressureMessageFactory> inherited;
	
public:
	static _di_IMidiPolyphonicKeyPressureMessage __fastcall CreateMidiPolyphonicKeyPressureMessage(System::Byte channel, System::Byte note, System::Byte pressure);
public:
	/* TObject.Create */ inline __fastcall TMidiPolyphonicKeyPressureMessage() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiPolyphonicKeyPressureMessageFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMidiPolyphonicKeyPressureMessage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMidiControlChangeMessage : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiControlChangeMessageFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiControlChangeMessageFactory> inherited;
	
public:
	static _di_IMidiControlChangeMessage __fastcall CreateMidiControlChangeMessage(System::Byte channel, System::Byte controller, System::Byte controlValue);
public:
	/* TObject.Create */ inline __fastcall TMidiControlChangeMessage() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiControlChangeMessageFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMidiControlChangeMessage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMidiProgramChangeMessage : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiProgramChangeMessageFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiProgramChangeMessageFactory> inherited;
	
public:
	static _di_IMidiProgramChangeMessage __fastcall CreateMidiProgramChangeMessage(System::Byte channel, System::Byte program);
public:
	/* TObject.Create */ inline __fastcall TMidiProgramChangeMessage() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiProgramChangeMessageFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMidiProgramChangeMessage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMidiChannelPressureMessage : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiChannelPressureMessageFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiChannelPressureMessageFactory> inherited;
	
public:
	static _di_IMidiChannelPressureMessage __fastcall CreateMidiChannelPressureMessage(System::Byte channel, System::Byte pressure);
public:
	/* TObject.Create */ inline __fastcall TMidiChannelPressureMessage() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiChannelPressureMessageFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMidiChannelPressureMessage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMidiPitchBendChangeMessage : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiPitchBendChangeMessageFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiPitchBendChangeMessageFactory> inherited;
	
public:
	static _di_IMidiPitchBendChangeMessage __fastcall CreateMidiPitchBendChangeMessage(System::Byte channel, System::Word bend);
public:
	/* TObject.Create */ inline __fastcall TMidiPitchBendChangeMessage() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiPitchBendChangeMessageFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMidiPitchBendChangeMessage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMidiSystemExclusiveMessage : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiSystemExclusiveMessageFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiSystemExclusiveMessageFactory> inherited;
	
public:
	static _di_IMidiMessage __fastcall CreateMidiSystemExclusiveMessage(Winapi::Commontypes::_di_IBuffer rawData);
public:
	/* TObject.Create */ inline __fastcall TMidiSystemExclusiveMessage() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiSystemExclusiveMessageFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMidiSystemExclusiveMessage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMidiTimeCodeMessage : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiTimeCodeMessageFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiTimeCodeMessageFactory> inherited;
	
public:
	static _di_IMidiTimeCodeMessage __fastcall CreateMidiTimeCodeMessage(System::Byte frameType, System::Byte values);
public:
	/* TObject.Create */ inline __fastcall TMidiTimeCodeMessage() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiTimeCodeMessageFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMidiTimeCodeMessage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMidiSongPositionPointerMessage : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiSongPositionPointerMessageFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiSongPositionPointerMessageFactory> inherited;
	
public:
	static _di_IMidiSongPositionPointerMessage __fastcall CreateMidiSongPositionPointerMessage(System::Word beats);
public:
	/* TObject.Create */ inline __fastcall TMidiSongPositionPointerMessage() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiSongPositionPointerMessageFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMidiSongPositionPointerMessage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMidiSongSelectMessage : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiSongSelectMessageFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiSongSelectMessageFactory> inherited;
	
public:
	static _di_IMidiSongSelectMessage __fastcall CreateMidiSongSelectMessage(System::Byte song);
public:
	/* TObject.Create */ inline __fastcall TMidiSongSelectMessage() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IMidiSongSelectMessageFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMidiSongSelectMessage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMidiTuneRequestMessage : public System::Win::Winrt::TWinRTGenericImportI__1<_di_IMidiMessage>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_IMidiMessage> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TMidiTuneRequestMessage() : System::Win::Winrt::TWinRTGenericImportI__1<_di_IMidiMessage>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMidiTuneRequestMessage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMidiTimingClockMessage : public System::Win::Winrt::TWinRTGenericImportI__1<_di_IMidiMessage>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_IMidiMessage> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TMidiTimingClockMessage() : System::Win::Winrt::TWinRTGenericImportI__1<_di_IMidiMessage>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMidiTimingClockMessage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMidiStartMessage : public System::Win::Winrt::TWinRTGenericImportI__1<_di_IMidiMessage>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_IMidiMessage> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TMidiStartMessage() : System::Win::Winrt::TWinRTGenericImportI__1<_di_IMidiMessage>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMidiStartMessage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMidiContinueMessage : public System::Win::Winrt::TWinRTGenericImportI__1<_di_IMidiMessage>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_IMidiMessage> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TMidiContinueMessage() : System::Win::Winrt::TWinRTGenericImportI__1<_di_IMidiMessage>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMidiContinueMessage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMidiStopMessage : public System::Win::Winrt::TWinRTGenericImportI__1<_di_IMidiMessage>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_IMidiMessage> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TMidiStopMessage() : System::Win::Winrt::TWinRTGenericImportI__1<_di_IMidiMessage>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMidiStopMessage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMidiActiveSensingMessage : public System::Win::Winrt::TWinRTGenericImportI__1<_di_IMidiMessage>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_IMidiMessage> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TMidiActiveSensingMessage() : System::Win::Winrt::TWinRTGenericImportI__1<_di_IMidiMessage>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMidiActiveSensingMessage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMidiSystemResetMessage : public System::Win::Winrt::TWinRTGenericImportI__1<_di_IMidiMessage>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_IMidiMessage> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TMidiSystemResetMessage() : System::Win::Winrt::TWinRTGenericImportI__1<_di_IMidiMessage>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMidiSystemResetMessage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMidiInPort : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IMidiInPortStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IMidiInPortStatics> inherited;
	
public:
	static _di_IAsyncOperation_1__IMidiInPort __fastcall FromIdAsync(HSTRING deviceId);
	static HSTRING __fastcall GetDeviceSelector();
public:
	/* TObject.Create */ inline __fastcall TMidiInPort() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IMidiInPortStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMidiInPort() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMidiOutPort : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IMidiOutPortStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IMidiOutPortStatics> inherited;
	
public:
	static _di_IAsyncOperation_1__IMidiOutPort __fastcall FromIdAsync(HSTRING deviceId);
	static HSTRING __fastcall GetDeviceSelector();
public:
	/* TObject.Create */ inline __fastcall TMidiOutPort() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IMidiOutPortStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMidiOutPort() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMidiSynthesizer : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IMidiSynthesizerStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IMidiSynthesizerStatics> inherited;
	
public:
	static _di_IAsyncOperation_1__IMidiSynthesizer __fastcall CreateAsync()/* overload */;
	static _di_IAsyncOperation_1__IMidiSynthesizer __fastcall CreateAsync(Winapi::Commontypes::_di_IDeviceInformation audioDevice)/* overload */;
	static bool __fastcall IsSynthesizer(Winapi::Commontypes::_di_IDeviceInformation midiDevice);
public:
	/* TObject.Create */ inline __fastcall TMidiSynthesizer() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IMidiSynthesizerStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMidiSynthesizer() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Midi */
}	/* namespace Devices */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Devices_MidiHPP
