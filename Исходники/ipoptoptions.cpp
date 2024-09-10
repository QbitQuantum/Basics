void IpoptOptions::setOption (const char* label, const mxArray* ptr) {

    // Check to make sure we have a valid option.
    SmartPtr<const RegisteredOption> option = app.RegOptions()->GetOption(label);
    if (!IsValid(option)) {
        char buf[256];
        Snprintf(buf, 255, "You have specified a nonexistent IPOPT option (\"%s\")", label);
        throw MatlabException(buf);
    }

    Ipopt::RegisteredOptionType type = option->Type();
    if (type == Ipopt::OT_String)
        setStringOption(label,ptr);
    else if (type == Ipopt::OT_Integer)
        setIntegerOption(label,ptr);
    else
        setNumberOption(label,ptr);
}