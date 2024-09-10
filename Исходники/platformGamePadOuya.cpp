    static float getControllerAxisValue(int playerNum, int axis)
    {
        jfloat jvalue = (jfloat)_getControllerAxisValue.getEnv()->CallStaticFloatMethod(_getControllerAxisValue.classID,
                                                                                   _getControllerAxisValue.methodID,
                                                                                   playerNum, axis);

        return jvalue;
    }