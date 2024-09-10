bool BufferedConnectionWriter::applyConvertTextMode() {
    if (convertTextModePending) {
        convertTextModePending = false;

        Bottle b;
        StringOutputStream sos;
        for (size_t i=0; i<lst_used; i++) {
            yarp::os::ManagedBytes& m = *(lst[i]);
            sos.write(m.usedBytes());
        }
        const String& str = sos.str();
        b.fromBinary(str.c_str(),str.length());
        ConstString replacement = b.toString() + "\n";
        for (size_t i=0; i<lst.size(); i++) {
            delete lst[i];
        }
        lst_used = 0;
        target = &lst;
        lst.clear();
        stopPool();
        Bytes data((char*)replacement.c_str(),replacement.length());
        appendBlockCopy(data);
    }
    return true;
}