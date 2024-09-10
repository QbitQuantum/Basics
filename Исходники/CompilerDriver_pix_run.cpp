void CompilerDriver_pix::pixClusterGroupChecks(ClusterGroup *cluster_group)
{
    FWObject *cluster = cluster_group;
    while (cluster && !Cluster::isA(cluster)) cluster = cluster->getParent();

    FWObject *cluster_interface = NULL;
    FWObject *p = cluster_group->getParent();
    if (Interface::isA(p)) cluster_interface = p;

    map<QString, const InetAddrMask*> addresses_and_masks;

    for (FWObjectTypedChildIterator it = cluster_group->findByType(FWObjectReference::TYPENAME);
         it != it.end(); ++it)
    {
        Interface *member_iface = Interface::cast(FWObjectReference::getObject(*it));
        assert(member_iface);
        FWObject *member = Host::getParentHost(member_iface);
        //FWObject *member = member_iface->getParentHost();

        if (cluster_interface)
        {
            // check consistency of the names.
            // In case of PIX the name of the cluster interface should match 
            // names of member interfaces
            if (cluster_interface->getName() != member_iface->getName())
            {
                QString err("Names of interfaces used in state synchronization "
                            "or failover group must match the name of the "
                            "cluster inetrface. Interface %1:%2 has the name "
                            "that is different from the cluster interface name %3");

                abort(cluster, NULL, NULL,
                      err.arg(member->getName().c_str())
                      .arg(member_iface->getName().c_str())
                      .arg(cluster_interface->getName().c_str()).toStdString());
                throw FatalErrorInSingleRuleCompileMode();
            }
        }

        if (StateSyncClusterGroup::isA(cluster_group) &&
            !member_iface->isDedicatedFailover())
        {
            QString err("Interface %1 is used in a state synchronization "
                        "but is not marked as 'Dedicated Failover' "
                        "interface. All interfaces used for the state "
                        "synchronization or failover must be marked "
                        "'Dedicated Failover'. ");

            abort(member, NULL, NULL,
                  err.arg(member_iface->getName().c_str()).toStdString());
            throw FatalErrorInSingleRuleCompileMode();
        }

        if (!member_iface->isRegular() || member_iface->countInetAddresses(true)==0)
        {
            QString err("Interface %1 which is used in state synchronization "
                        "or failover group does not have an IP address. "
                        "All interfaces used for the state "
                        "synchronization or failover must have ip addresses.");

            abort(member, NULL, NULL,
                  err.arg(member_iface->getName().c_str()).toStdString());
            throw FatalErrorInSingleRuleCompileMode();
        }
        QString key("%1:%2");

        FWObjectTypedChildIterator it_addr = member_iface->findByType(IPv4::TYPENAME);
        IPv4* addr = IPv4::cast(*it_addr);
        addresses_and_masks[key.arg(member->getName().c_str()).arg(member_iface->getName().c_str())] =
            addr->getInetAddrMaskObjectPtr();
    }
    
    if (addresses_and_masks.size() >= 2)
    {
        QString first_key;
        const InetAddr *first_network_addr = NULL;
        map<QString, const InetAddrMask*>::iterator it;
        for (it=addresses_and_masks.begin(); it!=addresses_and_masks.end(); ++it)
        {
            QString key = it->first;
            const InetAddrMask *am = it->second;
            if (first_network_addr == NULL)
            {
                first_key = key;
                first_network_addr = am->getNetworkAddressPtr();
            } else
            {
                const InetAddr *network_addr = am->getNetworkAddressPtr();
                if (*first_network_addr != *(network_addr))
                {
                    QString err("Interfaces used in state synchronization "
                                "or failover group must have IP addresses on "
                                "the same subnet. Interfaces %1 and %2 have "
                                "addresses on different subnets: %3 , %4");

                    abort(cluster, NULL, NULL,
                          err.arg(first_key).arg(key)
                          .arg(first_network_addr->toString().c_str())
                          .arg(network_addr->toString().c_str()).toStdString());
                    throw FatalErrorInSingleRuleCompileMode();
                }
            }
        }
    }
}