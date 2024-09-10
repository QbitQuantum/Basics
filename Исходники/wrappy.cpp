PythonObject callWithArgs(
    const std::string& name,
    const std::vector<PythonObject>& args,
    const std::vector<std::pair<std::string, PythonObject>>& kwargs)
{
    size_t cutoff;
    PythonObject module = loadModule(name, cutoff);
    PythonObject function;

    if (module) {
        function = loadFunction(module, name.substr(cutoff));
    } else {
        // No proper prefix was a valid module, but maybe it's a built-in
        function = loadBuiltin(name);
    }

    if (!function) {
        std::string error_message;
        if(cutoff != std::string::npos) {
            error_message = "Wrappy: Lookup of function " +
                name.substr(cutoff) + " in module " +
                name.substr(0,cutoff) + " failed.";
        } else {
            error_message = "Wrappy: Lookup of function " + name + "failed.";
        }

        throw WrappyError(error_message);
    }

    return callFunctionWithArgs(function, args, kwargs);
}