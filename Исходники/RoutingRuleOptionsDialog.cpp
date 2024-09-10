void RoutingRuleOptionsDialog::loadFWObject(FWObject *o)
{
    obj=o;

    FWObject *p = obj;
    while ( !Firewall::cast(p) ) p = p->getParent();
    platform = p->getStr("platform").c_str();

    Rule      *rule = dynamic_cast<Rule*>(o);
    FWOptions *ropt = rule->getOptionsObject();

    int wid = 0;
    if (platform=="iptables") wid = 0;
    else      wid = 1;

    /*
        if (platform=="ipf")      wid = 1;
        if (platform=="pf")       wid = 2;
        if (platform=="ipfw")     wid = 3;
    */

    m_dialog->wStack->setCurrentIndex( wid );
    m_dialog->wStack->widget(wid)->raise();

    data.clear();

    if (platform=="iptables")
    {
        data.registerOption(m_dialog->routing_non_critical_rule, ropt,  "no_fail");
    }

    init = true;
    data.loadAll();

    init = false;
}