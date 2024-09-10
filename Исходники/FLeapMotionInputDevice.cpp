void FLeapMotionInputDevice::ParseEvents()
{
	//Optimization: If we don't have any delegates, skip
	if (EventDelegates.Num() == 0)
	{
		return;
	}

	//Pointers
	Leap::Frame Frame = ControllerData.LeapController.frame();
	Leap::Frame PastFrame = ControllerData.LeapController.frame(1);

	//Calculate HMD Timewarp if valid
	if (GEngine->HMDDevice.IsValid() && ControllerData.bTimeWarpEnabled) {
		LeapHMDSnapshot ThenSnapshot = HMDSamples->HMDSampleClosestToTimestamp(Frame.timestamp());
		LeapHMDSnapshot NowSnapShot = HMDSamples->CurrentHMDSample();

		LeapHMDSnapshot HistorySnapshot = HMDSamples->LastHMDSample();	//reduce jitter
		//ControllerData.TimeWarpSnapshot = NowSnapShot.Difference(ThenSnapshot, ControllerData.TimeWarpFactor);// * ControllerData.TimeWarpFactor;

		FQuat WarpQuat = NowSnapShot.Orientation;//FQuat::Slerp(NowSnapShot.Orientation, HistorySnapshot.Orientation, ControllerData.TimeWarpTween);
		FQuat ThenTweened = FQuat::Slerp(ThenSnapshot.Orientation, HistorySnapshot.Orientation, ControllerData.TimeWarpTween);

		ControllerData.TimeWarpSnapshot.Orientation = (WarpQuat.Inverse() * ControllerData.TimeWarpFactor) * ThenTweened;

		ControllerData.TimeWarpAmountMs = (ControllerData.TimeWarpSnapshot.Timestamp) / 1000.f;
	}

	//-Hands-

	//Hand Count
	int HandCount = Frame.hands().count();

	if (PastState->HandCount != HandCount)
	{
		CallFunctionOnDelegates([&](UObject* EventDelegate)
		{
			ILeapEventInterface::Execute_HandCountChanged(EventDelegate, HandCount);
		});
		//Zero our input mapping orientations (akin to letting go of a joystick)
		if (HandCount == 0)
		{
			EmitAnalogInputEventForKey(EKeysLeap::LeapLeftPalmPitch, 0, 0, 0);
			EmitAnalogInputEventForKey(EKeysLeap::LeapLeftPalmYaw, 0, 0, 0);
			EmitAnalogInputEventForKey(EKeysLeap::LeapLeftPalmRoll, 0, 0, 0);
			EmitAnalogInputEventForKey(EKeysLeap::LeapRightPalmPitch, 0, 0, 0);
			EmitAnalogInputEventForKey(EKeysLeap::LeapRightPalmYaw, 0, 0, 0);
			EmitAnalogInputEventForKey(EKeysLeap::LeapRightPalmRoll, 0, 0, 0);
		}
	}

	//Cycle through each hand
	for (int i = 0; i < HandCount; i++)
	{
		Leap::Hand Hand = Frame.hands()[i];
		LeapHandStateData PastHandState = PastState->StateForId(Hand.id());		//we use a custom class to hold reliable state tracking based on id's

																				//Make a ULeapHand
		if (PEventHand == nullptr)
		{
			PEventHand = NewObject<ULeapHand>();
			PEventHand->AddToRoot();
		}
		PEventHand->SetHand(Hand);

		//Emit hand
		CallFunctionOnDelegates([&](UObject* EventDelegate)
		{
			ILeapEventInterface::Execute_LeapHandMoved(EventDelegate, PEventHand);
		});


		//Left/Right hand forwarding
		if (Hand.isRight())
		{
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_LeapRightHandMoved(EventDelegate, PEventHand);
			});

			//Input Mapping
			FRotator PalmOrientation = PEventHand->PalmOrientation;
			EmitAnalogInputEventForKey(EKeysLeap::LeapRightPalmPitch, PalmOrientation.Pitch * LEAP_IM_SCALE, 0, 0);
			EmitAnalogInputEventForKey(EKeysLeap::LeapRightPalmYaw, PalmOrientation.Yaw * LEAP_IM_SCALE, 0, 0);
			EmitAnalogInputEventForKey(EKeysLeap::LeapRightPalmRoll, PalmOrientation.Roll * LEAP_IM_SCALE, 0, 0);
		}
		else if (Hand.isLeft())
		{
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_LeapLeftHandMoved(EventDelegate, PEventHand);
			});

			//Input Mapping
			FRotator PalmOrientation = PEventHand->PalmOrientation;
			EmitAnalogInputEventForKey(EKeysLeap::LeapLeftPalmPitch, PalmOrientation.Pitch * LEAP_IM_SCALE, 0, 0);
			EmitAnalogInputEventForKey(EKeysLeap::LeapLeftPalmYaw, PalmOrientation.Yaw * LEAP_IM_SCALE, 0, 0);
			EmitAnalogInputEventForKey(EKeysLeap::LeapLeftPalmRoll, PalmOrientation.Roll * LEAP_IM_SCALE, 0, 0);
		}

		//Grabbing
		float GrabStrength = Hand.grabStrength();
		bool Grabbed = HandClosed(GrabStrength);

		if (Grabbed)
		{
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_LeapHandGrabbing(EventDelegate, GrabStrength, PEventHand);
			});

		}

		if (Grabbed && !PastHandState.Grabbed)
		{
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_LeapHandGrabbed(EventDelegate, GrabStrength, PEventHand);
			});

			//input mapping
			if (PEventHand->HandType == LeapHandType::HAND_LEFT)
			{
				EmitKeyDownEventForKey(EKeysLeap::LeapLeftGrab, 0, 0);
			}
			else
			{
				EmitKeyDownEventForKey(EKeysLeap::LeapRightGrab, 0, 0);
			}
		}
		else if (!Grabbed && PastHandState.Grabbed)
		{
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_LeapHandReleased(EventDelegate, GrabStrength, PEventHand);
			});

			//input mapping
			if (PEventHand->HandType == LeapHandType::HAND_LEFT)
			{
				EmitKeyUpEventForKey(EKeysLeap::LeapLeftGrab, 0, 0);
			}
			else
			{
				EmitKeyUpEventForKey(EKeysLeap::LeapRightGrab, 0, 0);
			}
		}

		//Pinching
		float PinchStrength = Hand.pinchStrength();
		bool Pinched = HandPinched(PinchStrength);

		//While grabbing disable pinching detection, this helps to reduce spam as pose confidence plummets
		if (Grabbed)
		{
			Pinched = PastHandState.Pinched;
		}
		else
		{
			if (Pinched)
			{
				CallFunctionOnDelegates([&](UObject* EventDelegate)
				{
					ILeapEventInterface::Execute_LeapHandPinching(EventDelegate, PinchStrength, PEventHand);
				});
			}
			if (Pinched && !PastHandState.Pinched)
			{
				CallFunctionOnDelegates([&](UObject* EventDelegate)
				{
					ILeapEventInterface::Execute_LeapHandPinched(EventDelegate, PinchStrength, PEventHand);
				});
				//input mapping
				if (PEventHand->HandType == LeapHandType::HAND_LEFT)
				{
					EmitKeyDownEventForKey(EKeysLeap::LeapLeftPinch, 0, 0);
				}
				else
				{
					EmitKeyDownEventForKey(EKeysLeap::LeapRightPinch, 0, 0);
				}
			}
			else if (!Pinched && PastHandState.Pinched)
			{
				CallFunctionOnDelegates([&](UObject* EventDelegate)
				{
					ILeapEventInterface::Execute_LeapHandUnpinched(EventDelegate, PinchStrength, PEventHand);
				});
				//input mapping
				if (PEventHand->HandType == LeapHandType::HAND_LEFT)
				{
					EmitKeyUpEventForKey(EKeysLeap::LeapLeftPinch, 0, 0);
				}
				else
				{
					EmitKeyUpEventForKey(EKeysLeap::LeapRightPinch, 0, 0);
				}
			}
		}

		//-Fingers-
		Leap::FingerList Fingers = Hand.fingers();

		//Count
		int FingerCount = Fingers.count();
		if ((PastHandState.FingerCount != FingerCount))
		{
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_FingerCountChanged(EventDelegate, FingerCount);
			});
		}
		if (PEventFinger == nullptr)
		{
			PEventFinger = NewObject<ULeapFinger>();
			PEventFinger->AddToRoot();
		}

		Leap::Finger Finger;

		//Cycle through each finger
		for (int j = 0; j < FingerCount; j++)
		{
			Finger = Fingers[j];
			PEventFinger->SetFinger(Finger);

			//Finger Moved
			if (Finger.isValid())
			{
				CallFunctionOnDelegates([&](UObject* EventDelegate)
				{
					ILeapEventInterface::Execute_LeapFingerMoved(EventDelegate, PEventFinger);
				});
			}
		}

		//Do these last so we can easily override debug shapes

		//Leftmost
		Finger = Fingers.leftmost();
		PEventFinger->SetFinger(Finger);
		CallFunctionOnDelegates([&](UObject* EventDelegate)
		{
			ILeapEventInterface::Execute_LeapLeftMostFingerMoved(EventDelegate, PEventFinger);
		});

		//Rightmost
		Finger = Fingers.rightmost();
		PEventFinger->SetFinger(Finger);
		CallFunctionOnDelegates([&](UObject* EventDelegate)
		{
			ILeapEventInterface::Execute_LeapRightMostFingerMoved(EventDelegate, PEventFinger);
		});

		//Frontmost
		Finger = Fingers.frontmost();
		PEventFinger->SetFinger(Finger);
		CallFunctionOnDelegates([&](UObject* EventDelegate)
		{
			ILeapEventInterface::Execute_LeapFrontMostFingerMoved(EventDelegate, PEventFinger);
		});

		//touch only for front-most finger, most common use case
		float touchDistance = Finger.touchDistance();
		if (touchDistance <= 0.f)
		{
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_LeapFrontFingerTouch(EventDelegate, PEventFinger);
			});
		}

		//Set the state data for next cycle
		PastHandState.Grabbed = Grabbed;
		PastHandState.Pinched = Pinched;
		PastHandState.FingerCount = FingerCount;

		PastState->SetStateForId(PastHandState, Hand.id());
	}

	PastState->HandCount = HandCount;

	//Gestures
	for (int i = 0; i < Frame.gestures().count(); i++)
	{
		Leap::Gesture Gesture = Frame.gestures()[i];
		Leap::Gesture::Type Type = Gesture.type();

		switch (Type)
		{
		case Leap::Gesture::TYPE_CIRCLE:
			if (PEventCircleGesture == nullptr)
			{
				PEventCircleGesture = NewObject<ULeapCircleGesture>();
				PEventCircleGesture->AddToRoot();
			}
			PEventCircleGesture->SetGesture(Leap::CircleGesture(Gesture));
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_CircleGestureDetected(EventDelegate, PEventCircleGesture);
			});
			PEventGesture = PEventCircleGesture;
			break;
		case Leap::Gesture::TYPE_KEY_TAP:
			if (PEventKeyTapGesture == nullptr)
			{
				PEventKeyTapGesture = NewObject<ULeapKeyTapGesture>();
				PEventKeyTapGesture->AddToRoot();
			}
			PEventKeyTapGesture->SetGesture(Leap::KeyTapGesture(Gesture));
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_KeyTapGestureDetected(EventDelegate, PEventKeyTapGesture);
			});
			PEventGesture = PEventKeyTapGesture;
			break;
		case Leap::Gesture::TYPE_SCREEN_TAP:
			if (PEventScreenTapGesture == nullptr)
			{
				PEventScreenTapGesture = NewObject<ULeapScreenTapGesture>();
				PEventScreenTapGesture->AddToRoot();
			}
			PEventScreenTapGesture->SetGesture(Leap::ScreenTapGesture(Gesture));
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_ScreenTapGestureDetected(EventDelegate, PEventScreenTapGesture);
			});
			PEventGesture = PEventScreenTapGesture;
			break;
		case Leap::Gesture::TYPE_SWIPE:
			if (PEventSwipeGesture == nullptr)
			{
				PEventSwipeGesture = NewObject<ULeapSwipeGesture>();
				PEventSwipeGesture->AddToRoot();
			}
			PEventSwipeGesture->SetGesture(Leap::SwipeGesture(Gesture));
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_SwipeGestureDetected(EventDelegate, PEventSwipeGesture);
			});
			PEventGesture = PEventSwipeGesture;
			break;
		default:
			break;
		}

		//emit gesture
		if (Type != Leap::Gesture::TYPE_INVALID)
		{
			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_GestureDetected(EventDelegate, PEventGesture);
			});
		}
	}

	//Image
	if (ControllerData.bAllowImageEvents && ControllerData.bImageEventsEnabled)
	{
		int ImageCount = Frame.images().count();

		//We only support getting both images
		if (ImageCount >= 2)
		{
			Leap::Image Image1 = Frame.images()[0];
			if (PEventImage1 == nullptr)
			{
				PEventImage1 = NewObject<ULeapImage>();
				PEventImage1->AddToRoot();
			}
			PEventImage1->UseGammaCorrection = ControllerData.bUseGammaCorrection;
			PEventImage1->SetLeapImage(Image1);

			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_RawImageReceived(EventDelegate, PEventImage1->Texture(), PEventImage1);
			});

			Leap::Image Image2 = Frame.images()[1];
			if (PEventImage2 == nullptr)
			{
				PEventImage2 = NewObject<ULeapImage>();
				PEventImage2->AddToRoot();
			}
			PEventImage2->UseGammaCorrection = ControllerData.bUseGammaCorrection;
			PEventImage2->SetLeapImage(Image2);

			CallFunctionOnDelegates([&](UObject* EventDelegate)
			{
				ILeapEventInterface::Execute_RawImageReceived(EventDelegate, PEventImage2->Texture(), PEventImage2);
			});
		}
	}
}