void sigfpe_test()
{ 
    // Code taken from http://www.devx.com/cplus/Article/34993/1954

    //Set the x86 floating-point control word according to what
    //exceptions you want to trap. 
    _clearfp(); //Always call _clearfp before setting the control
    //word
    //Because the second parameter in the following call is 0, it
    //only returns the floating-point control word
    unsigned int cw; 
#if _MSC_VER<1400
    cw = _controlfp(0, 0); //Get the default control
#else
    _controlfp_s(&cw, 0, 0); //Get the default control
#endif 
    //word
    //Set the exception masks off for exceptions that you want to
    //trap.  When a mask bit is set, the corresponding floating-point
    //exception is //blocked from being generating.
    cw &=~(EM_OVERFLOW|EM_UNDERFLOW|EM_ZERODIVIDE|
        EM_DENORMAL|EM_INVALID);
    //For any bit in the second parameter (mask) that is 1, the 
    //corresponding bit in the first parameter is used to update
    //the control word.  
    unsigned int cwOriginal = 0;
#if _MSC_VER<1400
    cwOriginal = _controlfp(cw, MCW_EM); //Set it.
#else
    _controlfp_s(&cwOriginal, cw, MCW_EM); //Set it.
#endif
    //MCW_EM is defined in float.h.

    // Divide by zero

    float a = 1.0f;
    float b = 0.0f;
    float c = a/b;
    c;

    //Restore the original value when done:
    //_controlfp_s(cwOriginal, MCW_EM);
}