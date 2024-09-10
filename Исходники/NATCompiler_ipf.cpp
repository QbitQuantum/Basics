bool NATCompiler_ipf::AssignInterface::processNext()
{
    NATRule *rule = getNext(); if (rule==NULL) return false;
    RuleElementItfOutb *itf_re = rule->getItfOutb();

    Address *a = NULL;

    switch (rule->getRuleType() )
    {

    case NATRule::Continue:
    case NATRule::NONAT:
    {
/* use heuristic to assign nonat rule to interfaces */
        Interface *iface;

        a=compiler->getFirstODst(rule);
        iface=compiler->findInterfaceFor( compiler->getFirstODst(rule) , 
                                          compiler->fw);
        if (iface!=NULL && !iface->isLoopback()) 
        { 
            if ( ! itf_re->hasRef(iface)) itf_re->addRef(iface);
            // rule->setInterfaceId( iface->getId() );
            tmp_queue.push_back( rule );
            return true;
        }
/* slip into Redirect case to assign rule to all interfaces */
    }

    case NATRule::Redirect: 
    case NATRule::DNAT:
    case NATRule::DNetnat:
    case NATRule::LB:
    {
/*
 * we do not have network zones here, so our ability to pick right
 * interfaces is rather limited. First, we try to find interface that
 * is connected to the subnet OSrc belongs to. If that does not work,
 * we assign rule to all interfaces, except loopback 
 */
        a = NULL;
        if ( ! rule->getOSrc()->isAny() )  a = compiler->getFirstOSrc(rule);
        if ( a==NULL && ! rule->getODst()->isAny() )
            a = compiler->getFirstODst(rule);

        if (a!=NULL)
        {
            Interface *iface;
            iface = compiler->findInterfaceFor(a,compiler->fw);

            if (iface!=NULL && !iface->isLoopback()) 
            { 
                if ( ! itf_re->hasRef(iface)) itf_re->addRef(iface);
                // rule->setInterfaceId( iface->getId() );
                tmp_queue.push_back(rule);
                return true;
            }
        }

        FWObjectTypedChildIterator j=compiler->fw->findByType(Interface::TYPENAME);
        for ( ; j!=j.end(); ++j ) 
        {
            Interface *iface = Interface::cast(*j);
            assert(iface);
            if ( iface->isUnnumbered() || 
                 iface->isBridgePort() || 
                 iface->isLoopback()) continue;

            NATRule *r = compiler->dbcopy->createNATRule();
            compiler->temp_ruleset->add(r);
            r->duplicate(rule);
            RuleElementItfOutb *itf_re = r->getItfOutb();
            if ( ! itf_re->hasRef(iface)) itf_re->addRef(iface);
            //r->setInterfaceId( iface->getId() );
            tmp_queue.push_back( r );
        }
        return true;
    }

    case NATRule::SNAT:
    case NATRule::SNetnat:
    {
        a=compiler->getFirstTSrc(rule);

        if ( (Interface::isA(a) || IPv4::isA(a)) && a->isChildOf(compiler->fw))
        {
            FWObject *p = a;
            while ( ! Interface::isA(p) ) p = p->getParent();
            if ( ! itf_re->hasRef(p)) itf_re->addRef(p);
            // rule->setInterfaceId( p->getId() );
            tmp_queue.push_back(rule);
            return true;
        }

/* if we appear here, then TSrc is not an interface or address of an
 * interface. 
 */
        int n=0;
        list<FWObject*> l2=compiler->fw->getByType(Interface::TYPENAME);
        for (list<FWObject*>::iterator i=l2.begin(); i!=l2.end(); ++i) 
        {
            Interface *iface=Interface::cast(*i);
            assert(iface);

            if (iface->isLoopback() ||
                iface->isUnnumbered() ||
                iface->isBridgePort()) continue;

            NATRule *r = compiler->dbcopy->createNATRule();
            r->duplicate(rule);
            compiler->temp_ruleset->add(r);

            RuleElementItfOutb *itf_re = r->getItfOutb();
            if ( ! itf_re->hasRef(iface)) itf_re->addRef(iface);
            // r->setInterfaceId( iface->getId() );
            
            tmp_queue.push_back(r);
            n++;
        }
        if (n==0) tmp_queue.push_back(rule);

        return true;
    }
    default: ;
    }

    compiler->abort(rule,
                    "Could not assign NAT rule to the interface. "
                    "Perhaps one of the objects has address which does not "
                    "belong to any subnet the firewall has interface on");
    
    return true;
}