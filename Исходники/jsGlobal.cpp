Handle<Value> alert(const Arguments& args)
{
    bool first = true;
    string res = "";
    for (int i = 0; i < args.Length(); i++) {
        HandleScope handle_scope;
        if (first) {
            first = false;
        } else {
            res += " ";
        }
        res += value_to_string(args[i]);
    }
    LOG4CXX_INFO(webEngine::iLogger::GetLogger(), _T("js::alert: ") << res);
    return Undefined();
}