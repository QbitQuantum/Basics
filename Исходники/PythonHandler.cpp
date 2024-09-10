//Enable lazy initialization
//Loads the function and arguments
void PythonHandler::init(std::string filename, std::string functionname, PythonArgList arg_list) {
	good = true;
	loadName(filename);
	loadModule();
	loadFunction(functionname);
	packArgs(arg_list);
}