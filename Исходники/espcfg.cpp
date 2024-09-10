CEspConfig::CEspConfig(IProperties* inputs, IPropertyTree* envpt, IPropertyTree* procpt, bool isDali)
{
    hsami_=0;
    serverstatus=NULL;
    useDali=false;
    
    if(inputs)
        m_inputs.setown(inputs);

    if(!envpt || !procpt)
        return;

    m_envpt.setown(envpt);
    m_cfg.setown(procpt);

    loadBuiltIns();   
   
    // load options
    const char* level = m_cfg->queryProp("@logLevel");
    m_options.logLevel = level ? atoi(level) : LogMin;
    m_options.logReq = m_cfg->getPropBool("@logRequests", true);
    m_options.logResp = m_cfg->getPropBool("@logResponses", false);
    m_options.frameTitle.set(m_cfg->queryProp("@name"));
    m_options.slowProcessingTime = m_cfg->getPropInt("@slowProcessingTime", 30) * 1000; //in msec

    if (!m_cfg->getProp("@name", m_process))
    {
        ERRLOG("EspProcess name not found");
    }
    else
    {
        DBGLOG("ESP process name [%s]", m_process.str());

        IPropertyTreeIterator *pt_iter = NULL;
        StringBuffer daliservers;
        if (m_cfg->getProp("@daliServers", daliservers))
            initDali(daliservers.str());

#ifndef _DEBUG
        startPerformanceMonitor(m_cfg->getPropInt("@perfReportDelay", 60)*1000);
#endif

        //get the local computer name:              
        m_cfg->getProp("@computer", m_computer);

        //get the local computer information:               
        StringBuffer xpath;
        xpath.appendf("Hardware/Computer[@name=\"%s\"]", m_computer.str());

        IPropertyTree *computer = m_envpt->queryPropTree(xpath.str());
        if (computer)
        {
            StringBuffer address;
            computer->getProp("@netAddress", address);

            int port = m_cfg->getPropInt("@port", 1500);
            if(strcmp(address.str(), ".") == 0)
            {
                GetHostName(address.clear());
            }
            m_address.set(address.str(), (unsigned short) port);
        }
      
        xpath.clear();
        xpath.append("EspService");
 
        pt_iter = m_cfg->getElements(xpath.str());

        if (pt_iter!=NULL)
        {
            IPropertyTree *ptree = NULL;

            pt_iter->first();

            while(pt_iter->isValid())
            {
                ptree = &pt_iter->query();
                if (ptree)
                {
                    srv_cfg *svcfg = new srv_cfg;

                    ptree->getProp("@name", svcfg->name);
                    ptree->getProp("@type", svcfg->type);
                    ptree->getProp("@plugin", svcfg->plugin);
                    fixPlugin(svcfg->plugin);

                    map<string, srv_cfg*>::value_type en(svcfg->name.str(), svcfg);
                    m_services.insert(en);
                }               
                pt_iter->next();
            }
    
            pt_iter->Release();
            pt_iter=NULL;
        }

        xpath.clear();
        xpath.append("EspProtocol");
 
        pt_iter = m_cfg->getElements(xpath.str());

        if (pt_iter!=NULL)
        {
            IPropertyTree *ptree = NULL;

            pt_iter->first();
    

            while(pt_iter->isValid())
            {
                ptree = &pt_iter->query();
                if (ptree)
                {
                    protocol_cfg *pcfg = new protocol_cfg;

                    ptree->getProp("@name", pcfg->name);
                    ptree->getProp("@plugin", pcfg->plugin);
                    fixPlugin(pcfg->plugin);
                    ptree->getProp("@type", pcfg->type);

                    map<string, protocol_cfg*>::value_type en(pcfg->name.str(), pcfg);
                    m_protocols.insert(en);
                }               

                pt_iter->next();
            }
    
            pt_iter->Release();
            pt_iter=NULL;
        }

        xpath.clear();
        xpath.append("EspBinding");
 
        pt_iter = m_cfg->getElements(xpath.str());

        if (pt_iter!=NULL)
        {
            IPropertyTree *ptree = NULL;

            pt_iter->first();
    

            while(pt_iter->isValid())
            {
                ptree = &pt_iter->query();
                if (ptree)
                {
                    binding_cfg *bcfg = new binding_cfg;
                    
                    ptree->getProp("@name", bcfg->name);
                    ptree->getProp("@type", bcfg->type);
                    ptree->getProp("@plugin", bcfg->plugin);
                    fixPlugin(bcfg->plugin);
                    bcfg->isDefault = ptree->getPropBool("@defaultBinding", false);
                    
                    StringBuffer addr;
                    ptree->getProp("@netAddress", addr);
                    if(strcmp(addr.str(), ".") == 0)
                    {
                        bcfg->address.append("0.0.0.0");
                    }
                    else
                    {
                        bcfg->address.append(addr.str());
                    }
                    
                    StringBuffer portstr;
                    ptree->getProp("@port", portstr);
                    bcfg->port = atoi(portstr.str());
                    ptree->getProp("@service", bcfg->service_name);
                    ptree->getProp("@protocol", bcfg->protocol_name);
                    
                    m_bindings.push_back(bcfg);
                }
                
                pt_iter->next();
            }
    
            pt_iter->Release();
            pt_iter=NULL;
        }
    }
}