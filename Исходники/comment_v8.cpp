// Initializes commentary data, reading it from the language.dat file
//
void commentary::init_commentary(Handle<Object> languageDat)
{
    HandleScope scope;
    // Read languageDat line by line, updating the
    // commentary database
    //
    const Local<Array> props = languageDat->GetOwnPropertyNames();
    const uint32_t length = props->Length();
    Local<String> key;
    Local<Array> value;
    Local<String> event, comment;
    char strKey[64];
    char strValue[128];

    for (uint32_t i=0 ; i<length ; ++i) {
        key = props->Get(i)->ToString();
        value = Local<Array>::Cast(languageDat->Get(key));

        event = value->Get(0)->ToString();

        comment = value->Get(1)->ToString();

        // Add line to the commentary database 
        //
        comm_data[toAscii(event, strKey)].push_back(toAscii(comment, strValue));
    }
}