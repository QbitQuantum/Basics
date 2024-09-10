gboolean
SrvAgent::invoke_resources(qmf::AgentSession session, qmf::AgentEvent event,
                           gpointer user_data)
{
    const std::string& methodName(event.getMethodName());
    if (event.getType() != qmf::AGENT_METHOD) {
        return TRUE;
    }

    qpid::types::Variant::Map& args = event.getArguments();

    if (methodName == "list_standards") {
        event.addReturnArgument("standards", standards);

    } else if (methodName == "list_providers") {
        GList *gIter = NULL;
        GList *providers = NULL;
        _qtype::Variant::List p_list;

	providers = resources_list_providers(args["standard"].asString().c_str());
        for (gIter = providers; gIter != NULL; gIter = gIter->next) {
            p_list.push_back((const char *) gIter->data);
        }
        event.addReturnArgument("providers", p_list);

    } else if (methodName == "list") {
        GList *gIter = NULL;
        GList *agents = NULL;
	const char *standard = "ocf";
	const char *provider = "heartbeat";
        _qtype::Variant::List t_list;

	if(args.count("standard") > 0) {
	    standard = args["standard"].asString().c_str();
	}
	if(args.count("provider") > 0) {
	    provider = args["provider"].asString().c_str();
	}

	agents = resources_list_agents(standard, provider);
        for (gIter = agents; gIter != NULL; gIter = gIter->next) {
            t_list.push_back((const char *) gIter->data);
        }
        event.addReturnArgument("agents", t_list);

    } else if (methodName == "invoke") {
	svc_action_t *op = NULL;
	bool valid_standard = false;
	_qtype::Variant::List::iterator iter;
	_qtype::Variant::Map map;

	if(args.count("parameters") == 1) {
	    map = args["parameters"].asMap();
	}
	
	GHashTable *params = qmf_map_to_hash(map);

	int32_t interval = 0;
	int32_t timeout = 60000;
	const char *agent = NULL;
	const char *standard = "ocf";
	const char *provider = "heartbeat";

	for ( iter=standards.begin() ; iter != standards.end(); iter++ ) {
	    if(args["standard"].asString() == (*iter).asString()) {
		valid_standard = true;
		break;
	    }
	}

	if(valid_standard == false) {
	    mh_err("%s is not a known resource standard", args["standard"].asString().c_str());
	    session.raiseException(event, MH_NOT_IMPLEMENTED);
	    return TRUE;
	}

	if(args.count("standard") > 0) {
	    standard = args["standard"].asString().c_str();
	}
	if(args.count("provider") > 0) {
	    provider = args["provider"].asString().c_str();
	}
	if(args.count("agent") > 0) {
	    agent = args["agent"].asString().c_str();
	} else {
	    agent = args["name"].asString().c_str();	    
	}

	if(args.count("interval") > 0) {
	    interval = args["interval"].asInt32();
	}
	if(args.count("timeout") > 0) {
	    timeout = args["timeout"].asInt32();
	}

	op = resources_action_create(
	    args["name"].asString().c_str(),
	    standard, provider, agent,
	    args["action"].asString().c_str(),
	    interval, timeout, params);

	if(args.count("expected-rc") == 1) {
	    op->expected_rc = args["expected-rc"].asInt32();
	}
	
	action_async(SRV_RESOURCES, session, event, op, true);
	return TRUE;
	
    } else if (methodName == "cancel") {
        services_action_cancel(
                args["name"].asString().c_str(),
                args["action"].asString().c_str(),
                args["interval"].asInt32());

    } else {
        session.raiseException(event, MH_NOT_IMPLEMENTED);
        return TRUE;
    }

    session.methodSuccess(event);
    return TRUE;
}