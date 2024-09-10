static int resolve_host(sd_bus *bus, const char *name) {

    _cleanup_(sd_bus_message_unrefp) sd_bus_message *req = NULL, *reply = NULL;
    _cleanup_(sd_bus_error_free) sd_bus_error error = SD_BUS_ERROR_NULL;
    const char *canonical = NULL;
    char ifname[IF_NAMESIZE] = "";
    unsigned c = 0;
    int r;
    uint64_t flags;
    usec_t ts;

    assert(name);

    if (arg_ifindex > 0 && !if_indextoname(arg_ifindex, ifname))
        return log_error_errno(errno, "Failed to resolve interface name for index %i: %m", arg_ifindex);

    log_debug("Resolving %s (family %s, interface %s).", name, af_to_name(arg_family) ?: "*", isempty(ifname) ? "*" : ifname);

    r = sd_bus_message_new_method_call(
            bus,
            &req,
            "org.freedesktop.resolve1",
            "/org/freedesktop/resolve1",
            "org.freedesktop.resolve1.Manager",
            "ResolveHostname");
    if (r < 0)
        return bus_log_create_error(r);

    r = sd_bus_message_append(req, "isit", arg_ifindex, name, arg_family, arg_flags);
    if (r < 0)
        return bus_log_create_error(r);

    ts = now(CLOCK_MONOTONIC);

    r = sd_bus_call(bus, req, DNS_CALL_TIMEOUT_USEC, &error, &reply);
    if (r < 0)
        return log_error_errno(r, "%s: resolve call failed: %s", name, bus_error_message(&error, r));

    ts = now(CLOCK_MONOTONIC) - ts;

    r = sd_bus_message_enter_container(reply, 'a', "(iiay)");
    if (r < 0)
        return bus_log_parse_error(r);

    while ((r = sd_bus_message_enter_container(reply, 'r', "iiay")) > 0) {
        _cleanup_free_ char *pretty = NULL;
        int ifindex, family;
        const void *a;
        size_t sz;

        assert_cc(sizeof(int) == sizeof(int32_t));

        r = sd_bus_message_read(reply, "ii", &ifindex, &family);
        if (r < 0)
            return bus_log_parse_error(r);

        r = sd_bus_message_read_array(reply, 'y', &a, &sz);
        if (r < 0)
            return bus_log_parse_error(r);

        r = sd_bus_message_exit_container(reply);
        if (r < 0)
            return bus_log_parse_error(r);

        if (!IN_SET(family, AF_INET, AF_INET6)) {
            log_debug("%s: skipping entry with family %d (%s)", name, family, af_to_name(family) ?: "unknown");
            continue;
        }

        if (sz != FAMILY_ADDRESS_SIZE(family)) {
            log_error("%s: systemd-resolved returned address of invalid size %zu for family %s", name, sz, af_to_name(family) ?: "unknown");
            return -EINVAL;
        }