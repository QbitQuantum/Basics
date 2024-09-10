void SimpleXbox360Controller::update(){
    XINPUT_STATE xInputState;
    memset(&xInputState,0, sizeof(XINPUT_STATE));
    curConnected=(XInputGetState(controllerNum, &xInputState) == ERROR_SUCCESS);

    //handling gamepad connection/deconnection
    if(prevConnected==false&&curConnected==true){
        emit controllerConnected(controllerNum);
    }
    else if(prevConnected==true&&curConnected==false){
        emit controllerDisconnected(controllerNum);
    }
    prevConnected=curConnected;

    if(curConnected){
        //buttons state
        curState.buttons=xInputState.Gamepad.wButtons;

        //sticks state
        processStickDeadZone(xInputState.Gamepad.sThumbLX,xInputState.Gamepad.sThumbLY,curState.leftThumbX,curState.leftThumbY,leftStickDeadZone);
        processStickDeadZone(xInputState.Gamepad.sThumbRX,xInputState.Gamepad.sThumbRY,curState.rightThumbX,curState.rightThumbY,rightStickDeadZone);

        //triggers state
        processTriggerThreshold(xInputState.Gamepad.bLeftTrigger,curState.leftTrigger,triggerThreshold);
        processTriggerThreshold(xInputState.Gamepad.bRightTrigger,curState.rightTrigger,triggerThreshold);

        //battery state
        XINPUT_BATTERY_INFORMATION xInputBattery;
        memset(&xInputBattery,0,sizeof(XINPUT_BATTERY_INFORMATION));
        if(XInputGetBatteryInformation(controllerNum,BATTERY_DEVTYPE_GAMEPAD,&xInputBattery)==ERROR_SUCCESS){
            curState.batteryType=xInputBattery.BatteryType;
            curState.batteryLevel=xInputBattery.BatteryLevel;
        }
        else{
            curState.batteryType=BATTERY_TYPE_UNKNOWN;
            curState.batteryLevel=BATTERY_LEVEL_EMPTY;
        }

        if(curState!=prevState) emit controllerNewState(curState);
        if(!InputState::batteryEquals(prevState,curState)) emit controllerNewBatteryState(curState.batteryType,curState.batteryLevel);
        prevState=curState;
    }
}