	void Operation::StartOperation(Session *session)
	{
		_operationContext.AddOperation();
		Process(session);
	}