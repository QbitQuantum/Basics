void
testSimple(SimdInterpreter &interp)
{
    int numTries = 3;

    interp.loadModule ("testCppCall");


    int numArgs;
    FunctionCallPtr func;
    FunctionArgPtr ret;

    // test return value of a simple function
    {
	func = interp.newFunctionCall("cppCall::funcRETi");
	numArgs = func->numInputArgs();
	assert(numArgs == 0);

	for(int i = 0; i < numTries; i++)
	{
	    func->callFunction(1000);
	    ret = func->returnValue();
	    int retVal = *(int*)(ret->data());
	    assert(retVal == 5);
	}
    }

    // test passing & return value of a simple function
    {
	func = interp.newFunctionCall("cppCall::funcINifbRETf");
	numArgs = func->numInputArgs();
	assert(numArgs == 3);
	
	float f = 1.2345;
	FunctionArgPtr arg1 = func->inputArg(1);
	assert(!arg1->isVarying());
	((float*)(arg1->data()))[0] = f;

	for(int i = 0; i < numTries; i++)
	{
	    func->callFunction(1000);
	    ret = func->returnValue();
	    float retVal = *(float*)(ret->data());
	    assert(retVal == f);
	}
    }

    // test passing w/ default value
    {
	func = interp.newFunctionCall("cppCall::funcINifbRETfD");
	numArgs = func->numInputArgs();
	assert(numArgs == 3);
	
	float f = 1.2345;
	FunctionArgPtr arg2 = func->inputArg(2);
	assert(!arg2->isVarying());
	((float*)(arg2->data()))[0] = f;

	for(int i = 0; i < numTries; i++)
	{
	    func->callFunction(1000);
	    ret = func->returnValue();
	    float retVal = *(float*)(ret->data());
	    assert(retVal == f);
	}
    }

    // test default value
    {
	func = interp.newFunctionCall("cppCall::funcINifbRETfD");
	numArgs = func->numInputArgs();
	assert(numArgs == 3);
	
	FunctionArgPtr arg2 = func->inputArg(2);
	assert(!arg2->isVarying());
	arg2->setDefaultValue();

	for(int i = 0; i < numTries; i++)
	{
	    func->callFunction(1000);
	    ret = func->returnValue();
	    float retVal = *(float*)(ret->data());
	    assert(retVal == 2.0);
	}
    }

    // test default value after setting to something else
    {
	func = interp.newFunctionCall("cppCall::funcINifbRETfD");
	numArgs = func->numInputArgs();
	assert(numArgs == 3);
	
	FunctionArgPtr arg2 = func->inputArg(2);
	((float*)(arg2->data()))[0] = 1.2345;
	assert(!arg2->isVarying());
	arg2->setDefaultValue();

	for(int i = 0; i < numTries; i++)
	{
	    func->callFunction(1000);
	    ret = func->returnValue();
	    float retVal = *(float*)(ret->data());
	    assert(retVal == 2.0);
	}
    }

    // call set default value when none exists
    {
	func = interp.newFunctionCall("cppCall::funcINifbRETf");
	numArgs = func->numInputArgs();
	assert(numArgs == 3);
	
	float f = 1.2345;
	FunctionArgPtr arg1 = func->inputArg(1);
	assert(!arg1->isVarying());
	arg1->setDefaultValue();
	((float*)(arg1->data()))[0] = f;
	arg1->setDefaultValue();

	for(int i = 0; i < numTries; i++)
	{
	    func->callFunction(1000);
	    ret = func->returnValue();
	    float retVal = *(float*)(ret->data());
	    assert(retVal == f);
	}
    }
    
    // test value varying
    {
	func = interp.newFunctionCall("cppCall::funcINifbRETfD2");
	numArgs = func->numInputArgs();
	assert(numArgs == 3);
	
	FunctionArgPtr arg2 = func->inputArg(2);
	assert(arg2->isVarying());
	float * data = (float*)(arg2->data());

	int dataSize = 30;
	assert (interp.maxSamples() >= dataSize);

	for(int i = 0; i < dataSize; i++)
	{
	    data[i] = i + .1;
	}

	func->callFunction(dataSize);

	ret = func->returnValue();
	data = (float*)(ret->data());
	for(int i = 0; i < dataSize; i++)
	{
	    assert (equalWithRelError (data[i], i + .2f, 0.00001f));
	}


    }
}