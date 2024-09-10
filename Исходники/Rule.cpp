RuleSet* PolicyRule::getBranch()
{
    if (getAction() != PolicyRule::Branch) return NULL;
    FWObject *fw = this;
    while (fw && Firewall::cast(fw) == NULL) fw = fw->getParent();
    assert(fw!=NULL);
    string branch_id = getOptionsObject()->getStr("branch_id");
    if (!branch_id.empty())
    {
        return RuleSet::cast(getRoot()->findInIndex(
                                 FWObjectDatabase::getIntId(branch_id)));
    } else
    {
        string branch_name = getOptionsObject()->getStr("branch_name");
        if (!branch_name.empty())
        {
            return RuleSet::cast(
                fw->findObjectByName(Policy::TYPENAME, branch_name));
        } else
            return NULL;
    }
}