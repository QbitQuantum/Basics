    virtual void report(const SearchReport& report, const char *context) {
        ConstString ctx = context;
        ConstString key = report.key.c_str();
        ConstString prefix = "";

        prefix = ctx;
        prefix += ".";

        key = prefix + key;
        if (key.substr(0,1)==".") {
            key = key.substr(1,key.length());
        }

        if (!present.check(key.c_str())) {
            present.put(key.c_str(),"present");
            order.addString(key.c_str());
        }

        if (report.isFound) {
            actual.put(key.c_str(),report.value);
            return;
        }

        if (report.isComment==true) {
            comment.put(key.c_str(),report.value);
            return;
        }

        if (report.isDefault==true) {
            fallback.put(key.c_str(),report.value);
            return;
        }
    }