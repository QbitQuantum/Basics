// This function tries to execute a Java program (parameter 1) using 
// the supplied call (parameter 2). The first parameter ("the executable") 
// is needed for internal error management (i.e. did the Java call fail or 
// was the executable not found?). The function checks whether Java is 
// installed on the user's machine; if Java is installed, the function 
// determines if the desired program exists (thus we need parameter 1); 
// if the program exists, this function tries to execute the program 
// within a shell window
void ShellExecuteJava(const CString &_javaProgram, const CString &_javaProgramCompleteCall, const CString &_path) {

	CString javaProgram = _javaProgram;
	CString javaProgramCompleteCall = _javaProgramCompleteCall;

	// check if Java is installed
	if(reinterpret_cast<int>(ShellExecute(NULL, NULL, "java", NULL, NULL, SW_HIDE)) <= 32) {
		CString message;
		message.LoadStringA(IDS_STRING_JAVA_JRE_NOT_INSTALLED);
		AfxMessageBox(message, MB_ICONINFORMATION);
		return;
	}
	// check if Java program is there
	javaProgram.Insert(0, _path);
	struct stat javaProgramFileInformation;
	if(stat(javaProgram.GetBuffer(), &javaProgramFileInformation) != 0) {
		CString message;
		message.Format(IDS_STRING_JAVA_PROGRAM_NOT_FOUND, javaProgram);
		AfxMessageBox(message, MB_ICONINFORMATION);
		return;
	}
	// try to execute the Java progam
	if(reinterpret_cast<int>(ShellExecute(NULL, NULL, "java", javaProgramCompleteCall, _path, SW_HIDE)) <= 32) {
		CString message;
		message.LoadStringA(IDS_STRING_JAVA_PROGRAM_EXECUTION_FAILED);
		AfxMessageBox(message, MB_ICONSTOP);
		return;
	}	
}