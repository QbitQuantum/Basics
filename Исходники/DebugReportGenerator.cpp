status_t
DebugReportGenerator::_DumpDebuggedThreadInfo(BFile& _output,
	::Thread* thread)
{
	AutoLocker< ::Team> locker;
	if (thread->State() != THREAD_STATE_STOPPED)
		return B_OK;

	status_t error;
	StackTrace* trace = NULL;
	for (;;) {
		trace = thread->GetStackTrace();
		if (trace != NULL)
			break;

		locker.Unlock();
		fTraceWaitingThread = thread;
		do {
			error = acquire_sem(fTeamDataSem);
		} while (error == B_INTERRUPTED);

		if (error != B_OK)
			break;

		locker.Lock();
	}

	BString data("\t\tFrame\t\tIP\t\t\tFunction Name\n");
	WRITE_AND_CHECK(_output, data);
	data = "\t\t-----------------------------------------------\n";
	WRITE_AND_CHECK(_output, data);
	for (int32 i = 0; StackFrame* frame = trace->FrameAt(i); i++) {
		char functionName[512];
		BString sourcePath;

		target_addr_t ip = frame->InstructionPointer();
		FunctionInstance* functionInstance;
		Statement* statement;
		if (fTeam->GetStatementAtAddress(ip,
				functionInstance, statement) == B_OK) {
			BReference<Statement> statementReference(statement, true);

			int32 line = statement->StartSourceLocation().Line();
			LocatableFile* sourceFile = functionInstance->GetFunction()
				->SourceFile();
			if (sourceFile != NULL) {
				sourceFile->GetPath(sourcePath);
				sourcePath.SetToFormat("(%s:%" B_PRId32 ")",
					sourcePath.String(), line);
			}
		}


		data.SetToFormat("\t\t%#08" B_PRIx64 "\t%#08" B_PRIx64 "\t%s %s\n",
			frame->FrameAddress(), ip, UiUtils::FunctionNameForFrame(
				frame, functionName, sizeof(functionName)),
				sourcePath.String());

		WRITE_AND_CHECK(_output, data);

		// only dump the topmost frame
		if (i == 0) {
			locker.Unlock();
			error = _DumpFunctionDisassembly(_output, frame->InstructionPointer());
			if (error != B_OK)
				return error;
			error = _DumpStackFrameMemory(_output, thread->GetCpuState(),
				frame->FrameAddress(), thread->GetTeam()->GetArchitecture()
					->StackGrowthDirection());
			if (error != B_OK)
				return error;
			locker.Lock();
		}

		if (frame->CountParameters() == 0 && frame->CountLocalVariables() == 0)
			continue;

		data = "\t\t\tVariables:\n";
		WRITE_AND_CHECK(_output, data);
		error = fNodeManager->SetStackFrame(thread, frame);
		if (error != B_OK)
			continue;

		ValueNodeContainer* container = fNodeManager->GetContainer();
		AutoLocker<ValueNodeContainer> containerLocker(container);
		for (int32 i = 0; i < container->CountChildren(); i++) {
			data.Truncate(0L);
			ValueNodeChild* child = container->ChildAt(i);
			containerLocker.Unlock();
			_ResolveValueIfNeeded(child->Node(), frame, 1);
			containerLocker.Lock();
			UiUtils::PrintValueNodeGraph(data, child, 3, 1);
			WRITE_AND_CHECK(_output, data);
		}
		data = "\n";
		WRITE_AND_CHECK(_output, data);
	}

	data = "\n\t\tRegisters:\n";
	WRITE_AND_CHECK(_output, data);

	CpuState* state = thread->GetCpuState();
	BVariant value;
	const Register* reg = NULL;
	for (int32 i = 0; i < fArchitecture->CountRegisters(); i++) {
		reg = fArchitecture->Registers() + i;
		state->GetRegisterValue(reg, value);

		if (reg->Format() == REGISTER_FORMAT_SIMD) {
			data.SetToFormat("\t\t\t%5s:\t%s\n", reg->Name(),
				UiUtils::FormatSIMDValue(value, reg->BitSize(),
					SIMD_RENDER_FORMAT_INT16, data).String());
		} else {
			char buffer[64];
			data.SetToFormat("\t\t\t%5s:\t%s\n", reg->Name(),
				UiUtils::VariantToString(value, buffer, sizeof(buffer)));
		}

		WRITE_AND_CHECK(_output, data);
	}

	return B_OK;
}