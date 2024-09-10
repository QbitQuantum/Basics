F_NONNULL
static void config_addrset(const char* res_name, const char* stanza, const bool ipv6, addrset_t* addrset, const vscf_data_t* cfg) {
    dmn_assert(res_name); dmn_assert(stanza); dmn_assert(addrset); dmn_assert(cfg);

    if(!vscf_is_hash(cfg))
        log_fatal("plugin_weighted: resource '%s' stanza '%s' value must be a hash", res_name, stanza);

    const vscf_data_t* parent = vscf_get_parent(cfg);

    // inherit down the applicable res-level parameters
    vscf_hash_inherit(parent, (vscf_data_t*)cfg, "service_types", true);
    vscf_hash_inherit(parent, (vscf_data_t*)cfg, "multi", true);
    vscf_hash_inherit(parent, (vscf_data_t*)cfg, "up_thresh", true);

    // Get a starting assumption of our item count
    addrset->count = vscf_hash_get_len(cfg);

    /////// Process the parameters...

    // service_types
    addrset->num_svcs = 0;
    const vscf_data_t* res_stypes = vscf_hash_get_data_byconstkey(cfg, "service_types", true);
    if (res_stypes) {
        addrset->count--; // minus one for service_types entry
        addrset->num_svcs = vscf_array_get_len(res_stypes);
        if(addrset->num_svcs) {
            addrset->svc_names = malloc(addrset->num_svcs * sizeof(char*));
            for(unsigned i = 0; i < addrset->num_svcs; i++) {
                const vscf_data_t* this_svc_cfg = vscf_array_get_data(res_stypes, i);
                if(!vscf_is_simple(this_svc_cfg))
                    log_fatal("plugin_weighted: resource '%s' (%s): service_types values must be strings", res_name, stanza);
                addrset->svc_names[i] = strdup(vscf_simple_get_data(this_svc_cfg));
            }
        }
    }
    else {
        addrset->num_svcs = 1;
        addrset->svc_names = malloc(sizeof(char*));
        addrset->svc_names[0] = strdup(DEFAULT_SVCNAME);
    }

    // multi option
    addrset->multi = false;
    const vscf_data_t* multi_cfg = vscf_hash_get_data_byconstkey(cfg, "multi", true);
    if(multi_cfg) {
        addrset->count--; // minus one for multi entry
        if(!vscf_is_simple(multi_cfg) || !vscf_simple_get_as_bool(multi_cfg, &addrset->multi))
            log_fatal("plugin_weighted: resource '%s' (%s): 'multi' must be a boolean value ('true' or 'false')", res_name, stanza);
    }

    // up threshold as double
    double up_thresh = 0.5;
    const vscf_data_t* thresh_cfg = vscf_hash_get_data_byconstkey(cfg, "up_thresh", true);
    if(thresh_cfg) {
        addrset->count--; // minus one for up_thresh entry
        if(!vscf_is_simple(thresh_cfg) || !vscf_simple_get_as_double(thresh_cfg, &up_thresh)
           || up_thresh <= 0.0 || up_thresh > 1.0)
            log_fatal("plugin_weighted: resource '%s' (%s): 'up_thresh' must be a floating point value in the range (0.0 - 1.0]", res_name, stanza);
    }

    if(addrset->count > MAX_ITEMS_PER_SET)
        log_fatal("plugin_weighted: resource '%s' (%s): number of direct groups or addrs within one family cannot be more than %u", res_name, stanza, MAX_ITEMS_PER_SET);
    if(!addrset->count)
        log_fatal("plugin_weighted: resource '%s' (%s): empty address-family sets not allowed", res_name, stanza);

    addrset->items = calloc(addrset->count, sizeof(res_aitem_t));
    addrset->gmode = RES_ASET_UNKNOWN;
    addr_iter_data_t aid = {
        .item_idx = 0,
        .addrset = addrset,
        .res_name = res_name,
        .stanza = stanza,
        .ipv6 = ipv6
    };
    vscf_hash_iterate(cfg, true, config_addrset_item, &aid);

    addrset->weight = 0;
    addrset->max_weight = 0;
    for(unsigned i = 0; i < addrset->count; i++) {
        const unsigned iwt = addrset->items[i].weight;
        const unsigned num_addrs = addrset->items[i].count;
        dmn_assert(iwt); dmn_assert(addrset->items[i].max_weight);
        addrset->weight += iwt;
        if(addrset->max_weight < iwt)
            addrset->max_weight = iwt;
        if(addrset->max_addrs_pergroup < num_addrs)
            addrset->max_addrs_pergroup = num_addrs;
    }

    dmn_assert(addrset->weight);
    dmn_assert(addrset->max_weight);

    addrset->up_weight = ceil(up_thresh * addrset->weight);
    dmn_assert(addrset->up_weight);
}

typedef struct {
    cnset_t* cnset;
    const char* res_name;
    const char* stanza;
    unsigned item_idx;
} cname_iter_data_t;

F_NONNULL
static bool config_item_cname(const char* item_name, unsigned klen V_UNUSED, const vscf_data_t* cfg_data, void* cid_asvoid) {
    dmn_assert(item_name); dmn_assert(cfg_data); dmn_assert(cid_asvoid);
    cname_iter_data_t* cid = (cname_iter_data_t*)cid_asvoid;

    cnset_t* cnset = cid->cnset;
    const char* res_name = cid->res_name;
    const char* stanza = cid->stanza;
    const unsigned item_idx = cid->item_idx++;
    res_citem_t* res_item = &cnset->items[item_idx];

    long wtemp = 0;
    if(!vscf_is_array(cfg_data)
            || (2 != vscf_array_get_len(cfg_data))
            || !vscf_is_simple(vscf_array_get_data(cfg_data, 0))
            || !vscf_is_simple(vscf_array_get_data(cfg_data, 1))
            || !vscf_simple_get_as_long(vscf_array_get_data(cfg_data, 1), &wtemp)
            || wtemp < 1 || wtemp > MAX_WEIGHT )
        log_fatal("plugin_weighted: resource '%s' (%s), item '%s': values in cname mode must be arrays of [ CNAME, WEIGHT ], where weight must be an integer in the range 1 - " MAX_WEIGHT_STR, res_name, stanza, item_name);
    res_item->weight = wtemp;

    const vscf_data_t* cn = vscf_array_get_data(cfg_data, 0);
    const char* cname_txt = vscf_simple_get_data(cn);
    uint8_t* dname = malloc(256);
    dname_status_t dnstat = vscf_simple_get_as_dname(cn, dname);
    if(dnstat == DNAME_INVALID)
        log_fatal("plugin_weighted: resource '%s' (%s), item '%s': '%s' is not a legal domainname", res_name, stanza, item_name, vscf_simple_get_data(vscf_array_get_data(cfg_data, 0)));
    if(dnstat == DNAME_VALID)
        dname = dname_trim(dname);
    res_item->cname = dname;

    if(cnset->num_svcs) {
        res_item->indices = malloc(cnset->num_svcs * sizeof(unsigned));
        for(unsigned i = 0; i < cnset->num_svcs; i++)
            res_item->indices[i] = gdnsd_mon_cname(cnset->svc_names[i], cname_txt, dname);
    }

    log_debug("plugin_weighted: resource '%s' (%s), item '%s', CNAME '%s' added with weight %u", res_name, stanza, item_name, logf_dname(dname), res_item->weight);

    return true;
}