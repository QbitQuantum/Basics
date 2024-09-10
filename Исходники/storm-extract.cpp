/* List all files in a CASC archive.
 *
 * @param (string) Source directory of CASC files
 * @return (array) Full paths of files in the archive
 */
void nodeListFiles(const Nan::FunctionCallbackInfo<v8::Value> &args) {
    // Set API variables
    bQuiet = true;
    bVerbose = false;

    // Allocate a new scope when we create v8 JavaScript objects.
    v8::Isolate *isolate = args.GetIsolate();
    Nan::HandleScope scope;

    strSource = *v8::String::Utf8Value(args[0]->ToString());

    if ((strSource[strSource.size() - 1] == '/') || (strSource[strSource.size() - 1] == '\\'))
        strSource = strSource.substr(0, strSource.size() - 1);

    if (!CascOpenStorage(strSource.c_str(), 0, &hStorage)) {
        cerr << "Failed to open the storage '" << strSource << "'" << endl;
        return;
    }

    // Define variables
    CASC_FIND_DATA findData;
    HANDLE handle = CascFindFirstFile(hStorage, "*", &findData, NULL);

    // Let's get this party started..
    vector<string> results = searchArchive();

    // Convert returned vector of *chars to a v8::Array of v8::Strings
    v8::Handle<v8::Array> files = v8::Array::New(isolate);
    for (unsigned int i = 0; i < results.size(); i++ ) {
      v8::Handle<v8::String> result = v8::String::NewFromUtf8(isolate, results[i].c_str());
      files->Set(i, result);
    }

    // Clean it up...
    CascFindClose(handle);
    CascCloseStorage(hStorage);
    handle = NULL;
    hStorage = NULL;

    // Ship it out...
    args.GetReturnValue().Set(files);
    return;
}