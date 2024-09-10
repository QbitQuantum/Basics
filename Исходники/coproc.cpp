void PCI_INFO::write(MIOFILE& f) {
    f.printf(
        "<pci_info>\n"
        "   <bus_id>%d</bus_id>\n"
        "   <device_id>%d</device_id>\n"
        "   <domain_id>%d</domain_id>\n"
        "</pci_info>\n",
        bus_id,
        device_id,
        domain_id
    );
}