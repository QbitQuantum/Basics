bool BootstrapServer::configFileBootstrap(yarp::os::Contact& contact,
                                          bool configFileRequired,
                                          bool mayEditConfigFile) {
    Contact suggest = contact;

    // see what address is lying around
    Contact prev;
    NameConfig conf;
    if (conf.fromFile()) {
        prev = conf.getAddress();
    } else if (configFileRequired) {
        fprintf(stderr,"Could not read configuration file %s\n",
                conf.getConfigFileName().c_str());
        return false;
    }

    // merge
    if (prev.isValid()) {
        if (suggest.getHost() == "...") {
            suggest.setHost(prev.getHost());
        }
        if (suggest.getCarrier() == "...") {
            suggest.setCarrier(prev.getCarrier());
        }
        if (suggest.getPort() == 0) {
            suggest.setPort(prev.getPort());
        }
    }

    if (suggest.getRegName() == "...") {
        suggest.setName(conf.getNamespace());
    }

    // still something not set?
    if (suggest.getPort() == 0) {
        suggest.setPort(10000);
    }
    if (suggest.getHost() == "...") {
        // should get my IP
        suggest.setHost(conf.getHostName());
    }

    if (!configFileRequired)  {
        // finally, should make sure IP is local, and if not, correct it
        if (!conf.isLocalName(suggest.getHost())) {
            fprintf(stderr,"Overriding non-local address for name server\n");
            suggest.setHost(conf.getHostName());
        } else {
            // Let's just check we're not a loopback
            ConstString betterHost = conf.getHostName(false,suggest.getHost());
            if (betterHost!=suggest.getHost()) {
                fprintf(stderr,"Overriding loopback address for name server\n");
                suggest.setHost(betterHost);
            }
        }
    }
    else
    {
        if (!conf.isLocalName(conf.getHostName())) {
            fprintf(stderr,"The address written in config file doesn't belong any interface \n");
            return false;
        }
        suggest.setHost(conf.getHostName());
    }

    bool changed = false;
    if (prev.isValid()) {
        changed = (prev.getHost() != suggest.getHost()) ||
            (prev.getPort() != suggest.getPort()) ||
            (conf.getMode() != "yarp" && conf.getMode() != "");
    }
    if (changed && !mayEditConfigFile) {
        fprintf(stderr,"PROBLEM: need to change settings in %s\n",
                conf.getConfigFileName().c_str());
        fprintf(stderr,"  Current settings: host %s port %d family %s\n",
                prev.getHost().c_str(), prev.getPort(),
                (conf.getMode()=="")?"yarp":conf.getMode().c_str());
        fprintf(stderr,"  Desired settings:  host %s port %d family %s\n",
                suggest.getHost().c_str(), suggest.getPort(), "yarp");
        fprintf(stderr,"Please specify '--write' if it is ok to overwrite current settings, or\n");
        if(!configFileRequired)
            fprintf(stderr,"Please specify '--read' to use the current settings, or\n");
        else
            fprintf(stderr,"Please set an existing address in config file, or\n");
        fprintf(stderr,"delete %s\n", conf.getConfigFileName().c_str());
        return false;
    }
    bool shouldSave = changed || !prev.isValid();

    if (shouldSave) {
        // and save
        conf.setAddress(suggest);
        if (!conf.toFile()) {
            fprintf(stderr,"Could not save configuration file %s\n",
                    conf.getConfigFileName().c_str());
        }
    }

    contact = suggest;
    return true;
}