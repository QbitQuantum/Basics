Bottle NameServer::ncmdList(int argc, char *argv[]) {
    Bottle response;

    ConstString prefix = "";

    if (argc==1) {
        prefix = STR(argv[0]);
    }

    response.addString("ports");
    for (PLATFORM_MAP(ConstString,NameRecord)::iterator it = nameMap.begin(); it!=nameMap.end(); it++) {
        NameRecord& rec = PLATFORM_MAP_ITERATOR_SECOND(it);
        ConstString iname = rec.getAddress().getRegName();
        if (iname.find(prefix)==0) {
            if (iname==prefix || iname[prefix.length()]=='/' ||
                prefix[prefix.length()-1]=='/') {
                if (rec.getAddress().isValid()) {
                    response.addList() = botify(rec.getAddress());
                }
            }
        }
    }

    return response;
}