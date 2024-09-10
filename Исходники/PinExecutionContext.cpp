unsigned int PinExecutionContext::getInstructionPointer(void **value) const {
	return getRegisterValue(EREG_INST_POINTER, (unsigned long *) value);
}