ThinConsole& ThinConsole::WriteToConsole(string_type const& outputString, console_location_type const& location, console_color_type const& foreground, console_color_type const& background) {
	assert(outputHandle != NULL && "Output Handle Not Initialized");
	std::vector<console_attribute_type> outputAttributes(outputString.size(), foregroundColorMap[foreground] | backgroundColorMap[background]);
	console_information_type charsWritten;
	ExceptionCheck(WriteConsoleOutputCharacter(outputHandle, std::wstring(outputString.begin(), outputString.end()).c_str(), outputString.size(), location, &charsWritten), __FUNCTION__, __LINE__);
	ExceptionCheck(WriteConsoleOutputAttribute(outputHandle, outputAttributes.data(), outputAttributes.size(), location, &charsWritten), __FUNCTION__, __LINE__);
	return *this;
}