    void GameWindow::DetectControllers()
    {
        //Cache the last controller detection time stamp
        m_LastControllerDetection = ServiceLocator::GetPlatformLayer()->GetTicks();

        //Local variables used in the for loop below
        bool duplicate = false;
        XINPUT_STATE state;

        //Cycle through available controller ports
	    for(unsigned int controllerPort = 0; controllerPort < XUSER_MAX_COUNT; controllerPort++) 
        {
            //Zero out the memory of the state struct
            ZeroMemory(&state, sizeof(XINPUT_STATE));
 
            //Can we get the state of a controller on this port
            if(XInputGetState(controllerPort, &state) == ERROR_SUCCESS)
            {
			    duplicate = false;
			    for(unsigned int i = 0; i < GameDev2D::ServiceLocator::GetInputManager()->GetNumberOfControllers(); i++) 
                {    
                    //Check if this port already has a registered contoller
                    if(GameDev2D::ServiceLocator::GetInputManager()->GetControllerForIndex(i) != nullptr)
                    {
                        if((uintptr_t)GameDev2D::ServiceLocator::GetInputManager()->GetControllerForIndex(i)->GetDevice() == (uintptr_t)controllerPort) 
                        {
					        duplicate = true;
					        break;
				        }
                    }
			    }

                //If its a duplicate, continue to the next port
			    if(duplicate == true) 
                {
				    continue;
			    }

                //Used to get the vendor id and the product ids
                int vendorId = -1;
                int productId = -1;

                //Determine the vendor id and product id
                JOYCAPS caps;
                if(joyGetDevCaps(controllerPort, &caps, sizeof(JOYCAPS)) == JOYERR_NOERROR) 
                {
                    vendorId = caps.wMid;
                    productId = caps.wPid;
                }
            
                //Create a ControllerData object, pass it the device, vendor id and product id
                GameDev2D::ControllerData* controllerData = new GameDev2D::ControllerData((void*)controllerPort, vendorId, productId);
                assert(controllerData != nullptr);

                //Pass the controller data onto the input manager, it will
                GameDev2D::ControllerGeneric* controller = GameDev2D::ServiceLocator::GetInputManager()->HandleMatchedController(controllerData);
                assert(controller != nullptr);

                //Set the controller data's initial state
                controllerData->SetStateInfo(state);

                //Add all the controller buttons
                controllerData->AddButton(XINPUT_GAMEPAD_DPAD_UP);
                controllerData->AddButton(XINPUT_GAMEPAD_DPAD_DOWN);
                controllerData->AddButton(XINPUT_GAMEPAD_DPAD_LEFT);
                controllerData->AddButton(XINPUT_GAMEPAD_DPAD_RIGHT);
                controllerData->AddButton(XINPUT_GAMEPAD_START);
                controllerData->AddButton(XINPUT_GAMEPAD_BACK);
                controllerData->AddButton(XINPUT_GAMEPAD_LEFT_THUMB);
                controllerData->AddButton(XINPUT_GAMEPAD_RIGHT_THUMB);
                controllerData->AddButton(XINPUT_GAMEPAD_LEFT_SHOULDER);
                controllerData->AddButton(XINPUT_GAMEPAD_RIGHT_SHOULDER);
                controllerData->AddButton(XINPUT_GAMEPAD_A);
                controllerData->AddButton(XINPUT_GAMEPAD_B);
                controllerData->AddButton(XINPUT_GAMEPAD_X);
                controllerData->AddButton(XINPUT_GAMEPAD_Y);

                //Add the analog trugger
                controllerData->AddAnalog(VK_PAD_LTRIGGER, 0, 255, 0);
                controllerData->AddAnalog(VK_PAD_RTRIGGER, 0, 255, 0);

                //Add the left analog stick
                controllerData->AddAnalog(VK_PAD_LTHUMB_UP, -32768, 32767, 0);
                controllerData->AddAnalog(VK_PAD_LTHUMB_LEFT, -32768, 32767, 0);

                //Add the right analog stick
                controllerData->AddAnalog(VK_PAD_RTHUMB_UP, -32768, 32767, 0);
                controllerData->AddAnalog(VK_PAD_RTHUMB_LEFT, -32768, 32767, 0);
            }
        }
    }