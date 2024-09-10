/**
 * Executes a command.
 */
Handle<Value> Exec(const Arguments& args) {
    HandleScope scope;

    if (args.Length() < 1) {
        return ThrowException(
            Exception::TypeError(String::New("First argument must be a string"))
        );
    }

    Local<String> str = args[0]->ToString();
    std::string cmd = FlattenString(str);
    int result = exec(cmd.c_str());

    return scope.Close(Integer::New(result));
}