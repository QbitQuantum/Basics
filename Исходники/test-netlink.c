int main(void) {
        sd_netlink *rtnl;
        sd_netlink_message *m;
        sd_netlink_message *r;
        const char *string_data;
        int if_loopback;
        uint16_t type;

        test_match();

        test_multiple();

        assert_se(sd_netlink_open(&rtnl) >= 0);
        assert_se(rtnl);

        test_route(rtnl);

        test_message(rtnl);

        test_container(rtnl);

        if_loopback = (int) if_nametoindex("lo");
        assert_se(if_loopback > 0);

        test_async(if_loopback);

        test_pipe(if_loopback);

        test_event_loop(if_loopback);

        test_link_configure(rtnl, if_loopback);

        test_get_addresses(rtnl);

        test_message_link_bridge(rtnl);

        assert_se(sd_rtnl_message_new_link(rtnl, &m, RTM_GETLINK, if_loopback) >= 0);
        assert_se(m);

        assert_se(sd_netlink_message_get_type(m, &type) >= 0);
        assert_se(type == RTM_GETLINK);

        assert_se(sd_netlink_message_read_string(m, IFLA_IFNAME, &string_data) == -EPERM);

        assert_se(sd_netlink_call(rtnl, m, 0, &r) == 1);
        assert_se(sd_netlink_message_get_type(r, &type) >= 0);
        assert_se(type == RTM_NEWLINK);

        assert_se((r = sd_netlink_message_unref(r)) == NULL);

        assert_se(sd_netlink_call(rtnl, m, -1, &r) == -EPERM);
        assert_se((m = sd_netlink_message_unref(m)) == NULL);
        assert_se((r = sd_netlink_message_unref(r)) == NULL);

        test_link_get(rtnl, if_loopback);
        test_address_get(rtnl, if_loopback);

        assert_se((m = sd_netlink_message_unref(m)) == NULL);
        assert_se((r = sd_netlink_message_unref(r)) == NULL);
        assert_se((rtnl = sd_netlink_unref(rtnl)) == NULL);

        return EXIT_SUCCESS;
}