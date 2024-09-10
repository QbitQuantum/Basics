void CommandsDefPrivate::generateConfig()
{
    if (cfg.size())
        return;
    if (config.length()){
        list<unsigned> processed;
        string active = config;
        string noactive;
        int n = config.find('/');
        if (n >= 0){
            active   = config.substr(0, n);
            noactive = config.substr(n + 1);
        }
        while (active.length()){
            string v = getToken(active, ',');
            unsigned id = atol(v.c_str());
            cfg.push_back(id);
            if (id)
                processed.push_back(id);
        }
        while (noactive.length()){
            string v = getToken(noactive, ',');
            unsigned id = atol(v.c_str());
            if (id)
                processed.push_back(id);
        }
        for (list<CommandDef>::iterator it = buttons.begin(); it != buttons.end(); ++it){
            CommandDef &c = (*it);
            unsigned grp = m_bMenu ? c.menu_grp : c.bar_grp;
            if (grp == 0)
                continue;
            list<unsigned>::iterator it_p;
            for (it_p = processed.begin(); it_p != processed.end(); ++it_p)
                if ((*it_p) == c.id)
                    break;
            if (it_p != processed.end())
                continue;
            unsigned cur_grp = 0;
            for (it_p = cfg.begin(); it_p != cfg.end(); ++it_p){
                if ((*it_p) == 0){
                    if (cur_grp == grp)
                        break;
                    continue;
                }
                list<CommandDef>::iterator itl;
                for (itl = buttons.begin(); itl != buttons.end(); ++itl)
                    if ((*itl).id == (*it_p))
                        break;
                if (itl == buttons.end())
                    continue;
                unsigned itl_grp = m_bMenu ? (*itl).menu_grp : (*itl).bar_grp;
                if (itl_grp == 0)
                    continue;
                cur_grp = itl_grp;
                if (grp > cur_grp)
                    break;
            }
            cfg.insert(it_p, c.id);
        }
    }else{
        unsigned cur_grp = 0;
        for (list<CommandDef>::iterator it = buttons.begin(); it != buttons.end(); ++it){
            CommandDef &c = (*it);
            unsigned grp = m_bMenu ? c.menu_grp : c.bar_grp;
            if (grp == 0)
                continue;
            if ((grp & ~0xFF) != (cur_grp & ~0xFF)){
                if (cur_grp)
                    cfg.push_back(0);
            }
            cur_grp = grp;
            cfg.push_back(c.id);
        }
    }
}