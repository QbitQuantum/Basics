void EMULATOR_SESSION_CLASS::registerEmulateSCPThread(BASE_SCP_EMULATOR_CLASS *emulator_ptr)

//  DESCRIPTION     : Register the emulator thread.
//  PRECONDITIONS   :
//  POSTCONDITIONS  :
//  EXCEPTIONS      :
//  NOTES           :
//<<===========================================================================
{
	// add the thead to the list
	scpEmulatorThreadM.add(emulator_ptr);

	// set the owner thread ID of the socket to this thread
	emulator_ptr->setSocketOwnerThreadId(getThreadId());

}