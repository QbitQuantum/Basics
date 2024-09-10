static Handle<Value> LocationReplace(const v8::Arguments& args)
{
    Local<Object> self = args.Holder();
    Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
    void* ptr = wrap->Value();

    jsLocation* url = static_cast<jsLocation*>(ptr);
    if (url->win != NULL && args.Length() > 0) {
        url->url.assign_with_referer(value_to_string(args[0]), &url->url);
        url->win->history->push_back(url->url.tostring());
        url->win->load(url->url.tostring());
    } else {
        std::string log_info = "Location changed from '";
        if(url->url.is_valid()) {
            log_info += url->url.tostring();
        } else {
            log_info += "undefined";
        }
        log_info += "' to \n\thref: ";
        if (args.Length() > 0) {
            url->url.assign_with_referer(value_to_string(args[0]), &url->url);
            if(url->url.is_valid()) {
                log_info += url->url.tostring();
            } else {
                log_info += "undefined";
            }
        } else {
            if(url->url.is_valid()) {
                log_info += url->url.tostring();
            } else {
                log_info += "undefined";
            }
        }
        append_results(log_info);
    }
    return Handle<Value>();
}