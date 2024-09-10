bool NameServiceOnTriples::cmdList(NameTripleState& act) {
    if (!act.bottleMode) {
        act.reply.addString("old");
    } else {
        act.reply.addString("ports");
    }
    lock();
    Triple t;
    t.setNameValue("port","*");
    ConstString prefix = "";
    if (act.cmd.size()>1) {
        prefix = act.cmd.get(1).asString();
    }
    list<Triple> lst = act.mem.query(t, YARP_NULLPTR);
    act.nestedMode = true;
    for (list<Triple>::iterator it=lst.begin(); it!=lst.end(); it++) {
        if (prefix=="") {
            act.cmd.clear();
            act.cmd.addString("query");
            act.cmd.addString(it->value.c_str());
            act.mem.reset();
            cmdQuery(act,true);
        } else {
            ConstString iname = it->value.c_str();
            if (iname.find(prefix)==0) {
                if (iname==prefix || iname[prefix.length()]=='/' ||
                    prefix[prefix.length()-1]=='/') {
                    act.cmd.clear();
                    act.cmd.addString("query");
                    act.cmd.addString(iname);
                    act.mem.reset();
                    cmdQuery(act,true);
                }
            }
        }
    }
    unlock();
    return true;
}