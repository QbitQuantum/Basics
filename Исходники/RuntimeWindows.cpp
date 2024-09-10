	Value catchRuntimeExceptions(const std::function<Value()>& thunk)
	{
		// Ensure that there's enough space left on the stack in the case of a stack overflow to prepare the stack trace.
		ULONG stackOverflowReserveBytes = 32768;
		SetThreadStackGuarantee(&stackOverflowReserveBytes);

		Exception* runtimeException = nullptr;
		__try
		{
			return thunk();
		}
		__except(sehFilterFunction(GetExceptionInformation(),runtimeException))
		{}

		if(runtimeException->cause == Exception::Cause::StackOverflow)
		{
			// After a stack overflow, the stack will be left in a damaged state. Let the CRT repair it.
			_resetstkoflw();
		}

		return Value(runtimeException);
	}