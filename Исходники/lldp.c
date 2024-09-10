size_t lldp_packet(uint8_t proto, void *packet, struct netif *netif,
		struct nhead *netifs, struct my_sysinfo *sysinfo) {

    struct ether_hdr ether;

    char *tlv;
    char *pos = packet;
    size_t length = ETHER_MAX_LEN;

    uint16_t cap = 0, cap_active = 0;
    struct netif *parent, *mgmt, *vlanif = NULL;
    uint8_t *hwaddr;
    struct hinv *hinv;
    char *description;

    const uint8_t lldp_dst[] = LLDP_MULTICAST_ADDR;

    // fixup parent netif
    if (netif->parent != NULL)
	parent = netif->parent;
    else
	parent = netif;

    // configure managment interface
    mgmt = sysinfo->mnetif;
    if (!mgmt)
	mgmt = parent;

    // ethernet header
    memcpy(ether.dst, lldp_dst, ETHER_ADDR_LEN);
    memcpy(ether.src, netif->hwaddr, ETHER_ADDR_LEN);
    ether.type = htons(ETHERTYPE_LLDP);
    memcpy(pos, &ether, sizeof(struct ether_hdr));
    pos += sizeof(struct ether_hdr);

    // update tlv counters
    length -= VOIDP_DIFF(pos, packet);

    // chassis id and hinv
    hwaddr = (options & OPT_CHASSIS_IF) ? netif->hwaddr : sysinfo->hwaddr;
    hinv = &(sysinfo->hinv);

    if (!(
	START_LLDP_TLV(LLDP_TYPE_CHASSIS_ID) &&
	PUSH_UINT8(LLDP_CHASSIS_MAC_ADDR_SUBTYPE) &&
	PUSH_BYTES(hwaddr, ETHER_ADDR_LEN)
    ))
	return 0;
    END_LLDP_TLV;


    // port id
    if (!(
	START_LLDP_TLV(LLDP_TYPE_PORT_ID) &&
	PUSH_UINT8(LLDP_PORT_INTF_NAME_SUBTYPE) &&
	PUSH_BYTES(netif->name, strlen(netif->name))
    ))
	return 0;
    END_LLDP_TLV;


    // ttl
    if (!(
	START_LLDP_TLV(LLDP_TYPE_TTL) &&
	PUSH_UINT16(LADVD_TTL)
    ))
	return 0;
    END_LLDP_TLV;


    // port description
    if (options & OPT_IFDESCR)
	description = netif->device_name;
    else if (strlen(netif->description))
	description = netif->description;
    else if (strlen(parent->description))
	description = parent->description;
    else
	description = netif->device_name;

    if (strlen(description) > 0) {
	if (!(
	    START_LLDP_TLV(LLDP_TYPE_PORT_DESCR) &&
	    PUSH_BYTES(description, strlen(description))
	))
	    return 0;
	END_LLDP_TLV;
    }


    // system name
    if (!(
	START_LLDP_TLV(LLDP_TYPE_SYSTEM_NAME) &&
	PUSH_BYTES(sysinfo->hostname, strlen(sysinfo->hostname))
    ))
	return 0;
    END_LLDP_TLV;


    // system description
    if (!(
	START_LLDP_TLV(LLDP_TYPE_SYSTEM_DESCR) &&
	PUSH_BYTES(sysinfo->uts_str, strlen(sysinfo->uts_str))
    ))
	return 0;
    END_LLDP_TLV;


    // capabilities
    if (sysinfo->cap == CAP_HOST) {
	cap = cap_active = LLDP_CAP_STATION_ONLY;
    } else {
	cap |= (sysinfo->cap & CAP_BRIDGE) ? LLDP_CAP_BRIDGE : 0;
	cap_active |= (sysinfo->cap_active & CAP_BRIDGE) ? LLDP_CAP_BRIDGE : 0;

	cap |= (sysinfo->cap & CAP_ROUTER) ? LLDP_CAP_ROUTER : 0;
	cap_active |= (sysinfo->cap_active & CAP_ROUTER) ? LLDP_CAP_ROUTER : 0;

	cap |= (sysinfo->cap & CAP_SWITCH) ? LLDP_CAP_BRIDGE : 0;
	cap_active |= (sysinfo->cap_active & CAP_SWITCH) ? LLDP_CAP_BRIDGE : 0;

	cap |= (sysinfo->cap & CAP_WLAN) ? LLDP_CAP_WLAN_AP : 0;
	cap_active |= (sysinfo->cap_active & CAP_WLAN) ? LLDP_CAP_WLAN_AP : 0;
    }

    if (!(
	START_LLDP_TLV(LLDP_TYPE_SYSTEM_CAP) &&
	PUSH_UINT16(cap) && PUSH_UINT16(cap_active)
    ))
	return 0;
    END_LLDP_TLV;


    // ipv4 management addr
    if (mgmt->ipaddr4 != 0) {
	if (!(
	    START_LLDP_TLV(LLDP_TYPE_MGMT_ADDR) &&
	    PUSH_UINT8(1 + sizeof(mgmt->ipaddr4)) &&
	    PUSH_UINT8(LLDP_AFNUM_INET) &&
	    PUSH_BYTES(&mgmt->ipaddr4, sizeof(mgmt->ipaddr4)) &&
	    PUSH_UINT8(LLDP_INTF_NUMB_IFX_SUBTYPE) &&
	    PUSH_UINT32(mgmt->index) &&
	    PUSH_UINT8(0)
	))
	    return 0;
	END_LLDP_TLV;
    }


    // ipv6 management addr
    if (!IN6_IS_ADDR_UNSPECIFIED((struct in6_addr *)mgmt->ipaddr6)) {
	if (!(
	    START_LLDP_TLV(LLDP_TYPE_MGMT_ADDR) &&
	    PUSH_UINT8(1 + sizeof(mgmt->ipaddr6)) &&
	    PUSH_UINT8(LLDP_AFNUM_INET6) &&
	    PUSH_BYTES(mgmt->ipaddr6, sizeof(mgmt->ipaddr6)) &&
	    PUSH_UINT8(LLDP_INTF_NUMB_IFX_SUBTYPE) &&
	    PUSH_UINT32(mgmt->index) &&
	    PUSH_UINT8(0)
	))
	    return 0;
	END_LLDP_TLV;
    }


    // hw management addr
    if (!(
	START_LLDP_TLV(LLDP_TYPE_MGMT_ADDR) &&
	PUSH_UINT8(1 + sizeof(mgmt->hwaddr)) &&
	PUSH_UINT8(LLDP_AFNUM_802) &&
	PUSH_BYTES(mgmt->hwaddr, sizeof(mgmt->hwaddr)) &&
	PUSH_UINT8(LLDP_INTF_NUMB_IFX_SUBTYPE) &&
	PUSH_UINT32(mgmt->index) &&
	PUSH_UINT8(0)
    ))
	return 0;
    END_LLDP_TLV;


    // IEEE 802.1 Organizationally Specific TLV set

    // vlan names
    while ((vlanif = netif_iter(vlanif, netifs)) != NULL) {    
	    if (vlanif->type != NETIF_VLAN)
		continue;

	    // skip unless attached to this interface or the parent
	    if ((vlanif->vlan_parent != netif->index) &&
		(vlanif->vlan_parent != parent->index))
		continue;

	    if (!(
		START_LLDP_TLV(LLDP_TYPE_PRIVATE) &&
		PUSH_BYTES(OUI_IEEE_8021_PRIVATE, OUI_LEN) &&
		PUSH_UINT8(LLDP_PRIVATE_8021_SUBTYPE_VLAN_NAME) &&
		PUSH_UINT16(vlanif->vlan_id) &&
		PUSH_UINT8(strlen(vlanif->name)) &&
		PUSH_BYTES(vlanif->name, strlen(vlanif->name))
	    ))
		return 0;
	    END_LLDP_TLV;
    }


    // IEEE 802.3 Organizationally Specific TLV set

    // autoneg
    if (netif->autoneg_supported != -1) {
	if (!(
	    START_LLDP_TLV(LLDP_TYPE_PRIVATE) &&
	    PUSH_BYTES(OUI_IEEE_8023_PRIVATE, OUI_LEN) &&
	    PUSH_UINT8(LLDP_PRIVATE_8023_SUBTYPE_MACPHY) &&
	    PUSH_UINT8(netif->autoneg_supported +
		       (netif->autoneg_enabled << 1)) &&
	    PUSH_UINT16(netif->autoneg_pmd) &&
	    PUSH_UINT16(netif->mau)
	))
	    return 0;
	END_LLDP_TLV;
    }


    // lacp
    if (parent->bonding_mode == NETIF_BONDING_LACP) {
	if (!(
	    START_LLDP_TLV(LLDP_TYPE_PRIVATE) &&
	    PUSH_BYTES(OUI_IEEE_8023_PRIVATE, OUI_LEN) &&
	    PUSH_UINT8(LLDP_PRIVATE_8023_SUBTYPE_LINKAGGR) &&
	    PUSH_UINT8(LLDP_AGGREGATION_CAPABILTIY|LLDP_AGGREGATION_STATUS) &&
	    PUSH_UINT32(netif->lacp_index)
	))
	    return 0;
	END_LLDP_TLV;
    }


    // mtu
    if (netif->mtu != 0) {
	if (!(
	    START_LLDP_TLV(LLDP_TYPE_PRIVATE) &&
	    PUSH_BYTES(OUI_IEEE_8023_PRIVATE, OUI_LEN) &&
	    PUSH_UINT8(LLDP_PRIVATE_8023_SUBTYPE_MTU) &&
	    PUSH_UINT16(netif->mtu + 22)
	))
	    return 0;
	END_LLDP_TLV;
    }


    // TIA LLDP-MED Capabilities TLV
    if (!(
	START_LLDP_TLV(LLDP_TYPE_PRIVATE) &&
	PUSH_BYTES(OUI_TIA, OUI_LEN) &&
	PUSH_UINT8(LLDP_PRIVATE_TIA_SUBTYPE_CAPABILITIES) &&
	PUSH_UINT16(sysinfo->cap_lldpmed) &&
	PUSH_UINT8(sysinfo->lldpmed_devtype)
    ))
	return 0;
    END_LLDP_TLV;

    // TIA Location Identification TLv

    // LOC ("location", CAtype 22): unstructured additional information
    if ((strlen(sysinfo->country) == 2) && (strlen(sysinfo->location) != 0)) {
	if (!(
	    START_LLDP_TLV(LLDP_TYPE_PRIVATE) &&
	    PUSH_BYTES(OUI_TIA, OUI_LEN) &&
	    PUSH_UINT8(LLDP_PRIVATE_TIA_SUBTYPE_LOCAL_ID) &&
	    PUSH_UINT8(LLDP_TIA_LOCATION_DATA_FORMAT_CIVIC_ADDRESS) &&
	    PUSH_UINT8(5 + strlen(sysinfo->location)) &&
	    PUSH_UINT8(LLDP_TIA_LOCATION_LCI_WHAT_CLIENT) &&
	    PUSH_BYTES(sysinfo->country, 2) &&
	    PUSH_UINT8(LLDP_TIA_LOCATION_LCI_CATYPE_LOC) &&
	    PUSH_UINT8(strlen(sysinfo->location)) &&
	    PUSH_BYTES(sysinfo->location, strlen(sysinfo->location))
	))
	    return 0;
	END_LLDP_TLV;
    }



    // TIA Inventory Management TLV Set

    // hardware revision
    if (strlen(hinv->hw_revision) > 0) {
	if (!(
	    START_LLDP_TLV(LLDP_TYPE_PRIVATE) &&
	    PUSH_BYTES(OUI_TIA, OUI_LEN) &&
	    PUSH_UINT8(LLDP_PRIVATE_TIA_SUBTYPE_INVENTORY_HARDWARE_REV) &&
	    PUSH_BYTES(hinv->hw_revision, strlen(hinv->hw_revision))
	))
	    return 0;
	END_LLDP_TLV;
    }


    // firmware revision
    if (strlen(hinv->fw_revision) > 0) {
	if (!(
	    START_LLDP_TLV(LLDP_TYPE_PRIVATE) &&
	    PUSH_BYTES(OUI_TIA, OUI_LEN) &&
	    PUSH_UINT8(LLDP_PRIVATE_TIA_SUBTYPE_INVENTORY_FIRMWARE_REV) &&
	    PUSH_BYTES(hinv->fw_revision, strlen(hinv->fw_revision))
	))
	    return 0;
	END_LLDP_TLV;
    }


    // software revision
    if (strlen(hinv->sw_revision) > 0) {
	if (!(
	    START_LLDP_TLV(LLDP_TYPE_PRIVATE) &&
	    PUSH_BYTES(OUI_TIA, OUI_LEN) &&
	    PUSH_UINT8(LLDP_PRIVATE_TIA_SUBTYPE_INVENTORY_SOFTWARE_REV) &&
	    PUSH_BYTES(hinv->sw_revision, strlen(hinv->sw_revision))
	))
	    return 0;
	END_LLDP_TLV;
    }


    // serial number
    if (strlen(hinv->serial_number) > 0) {
	if (!(
	    START_LLDP_TLV(LLDP_TYPE_PRIVATE) &&
	    PUSH_BYTES(OUI_TIA, OUI_LEN) &&
	    PUSH_UINT8(LLDP_PRIVATE_TIA_SUBTYPE_INVENTORY_SERIAL_NUMBER) &&
	    PUSH_BYTES(hinv->serial_number, strlen(hinv->serial_number))
	))
	    return 0;
	END_LLDP_TLV;
    }


    // manufacturer
    if (strlen(hinv->manufacturer) > 0) {
	if (!(
	    START_LLDP_TLV(LLDP_TYPE_PRIVATE) &&
	    PUSH_BYTES(OUI_TIA, OUI_LEN) &&
	    PUSH_UINT8(LLDP_PRIVATE_TIA_SUBTYPE_INVENTORY_MANUFACTURER_NAME) &&
	    PUSH_BYTES(hinv->manufacturer, strlen(hinv->manufacturer))
	))
	    return 0;
	END_LLDP_TLV;
    }


    // model name
    if (strlen(hinv->model_name) > 0) {
	if (!(
	    START_LLDP_TLV(LLDP_TYPE_PRIVATE) &&
	    PUSH_BYTES(OUI_TIA, OUI_LEN) &&
	    PUSH_UINT8(LLDP_PRIVATE_TIA_SUBTYPE_INVENTORY_MODEL_NAME) &&
	    PUSH_BYTES(hinv->model_name, strlen(hinv->model_name))
	))
	    return 0;
	END_LLDP_TLV;
    }


    // asset id
    if (strlen(hinv->asset_id) > 0) {
	if (!(
	    START_LLDP_TLV(LLDP_TYPE_PRIVATE) &&
	    PUSH_BYTES(OUI_TIA, OUI_LEN) &&
	    PUSH_UINT8(LLDP_PRIVATE_TIA_SUBTYPE_INVENTORY_ASSET_ID) &&
	    PUSH_BYTES(hinv->asset_id, strlen(hinv->asset_id))
	))
	    return 0;
	END_LLDP_TLV;
    }



    // the end
    if (!(
	START_LLDP_TLV(LLDP_TYPE_END)
    ))
	return 0;
    END_LLDP_TLV;


    // return the packet length
    return(VOIDP_DIFF(pos, packet));
}