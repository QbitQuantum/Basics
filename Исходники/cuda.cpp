//----------------------------------------------------------------------------//
int _execPipe(const char* cmd, std::string * err) {
#ifdef __unix__
    FILE* pipe = popen(cmd, "r");
#else
    FILE* pipe = _popen(cmd, "r");
#endif
    if (!pipe) {
        (*err) += "Could not execute command";
        (*err) += std::string(cmd);
        return 1;
    }
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
    	if(fgets(buffer, 128, pipe) != NULL)
    		result += buffer;
    }
#ifdef __unix__
    int exit_status = pclose(pipe);
#else
    int exit_status = _pclose(pipe);
#endif
    if (exit_status) {
        (*err) += result;
    }
    return exit_status;
}