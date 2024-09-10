void OSConfigurator_linux24::addVirtualAddressForNAT(const Address *addr)
{
    FWOptions* options=fw->getOptionsObject();
    if ( options->getBool("manage_virtual_addr") )
    {
        const InetAddr *addr_addr = addr->getAddressPtr();

        if (virtual_addresses.empty() || 
            find(virtual_addresses.begin(),
                 virtual_addresses.end(), *addr_addr) == virtual_addresses.end())
        {
            FWObject *vaddr = findAddressFor(addr, fw );
            if (vaddr!=nullptr)
            {
                Interface *iface = Interface::cast(vaddr->getParent());
                assert(iface!=nullptr);

                QStringList addresses;
                const InetAddr *vaddr_netm =
                    Address::cast(vaddr)->getNetmaskPtr();

                addresses.push_back(QString("%1/%2").
                                    arg(addr_addr->toString().c_str()).
                                    arg(vaddr_netm->getLength()));

                if (virtual_addresses_for_nat.count(iface->getName()) > 0)
                    addresses.push_front(virtual_addresses_for_nat[iface->getName()].c_str());

                virtual_addresses_for_nat[iface->getName()] =
                    addresses.join(" ").toStdString();
        
                virtual_addresses.push_back(*(addr_addr));
                registerVirtualAddressForNat();
            } else
                warning("Can not add virtual address for object " + addr->getName());
        }
        return;
    }
}