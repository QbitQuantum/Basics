static int execute_nl_interface_cmd(const char *iface,
                                    enum nl80211_iftype type,
                                    uint8_t cmd)
{
    struct nl_cb *cb;
    struct nl_msg *msg;
    int devidx = 0;
    int err;
    int add_interface = (cmd == NL80211_CMD_NEW_INTERFACE);

    if (add_interface) {
        devidx = phy_lookup();
    } else {
        devidx = if_nametoindex(iface);
        if (devidx == 0) {
            ALOGE("failed to translate ifname to idx");
            return -errno;
        }
    }

    msg = nlmsg_alloc();
    if (!msg) {
        ALOGE("failed to allocate netlink message");
        return 2;
    }

    cb = nl_cb_alloc(NL_CB_DEFAULT);
    if (!cb) {
        ALOGE("failed to allocate netlink callbacks");
        err = 2;
        goto out_free_msg;
    }

    genlmsg_put(msg, 0, 0, genl_family_get_id(nl80211), 0, 0, cmd, 0);

    if (add_interface) {
        NLA_PUT_U32(msg, NL80211_ATTR_WIPHY, devidx);
    } else {
        NLA_PUT_U32(msg, NL80211_ATTR_IFINDEX, devidx);
    }

    if (add_interface) {
        NLA_PUT_STRING(msg, NL80211_ATTR_IFNAME, iface);
        NLA_PUT_U32(msg, NL80211_ATTR_IFTYPE, type);
    }

    err = nl_send_auto_complete(nl_soc, msg);
    if (err < 0)
        goto out;

    err = 1;

    nl_cb_err(cb, NL_CB_CUSTOM, nl_error_handler, &err);
    nl_cb_set(cb, NL_CB_FINISH, NL_CB_CUSTOM, nl_finish_handler, &err);
    nl_cb_set(cb, NL_CB_ACK, NL_CB_CUSTOM, nl_ack_handler, &err);

    while (err > 0)
        nl_recvmsgs(nl_soc, cb);
out:
    nl_cb_put(cb);
out_free_msg:
    nlmsg_free(msg);
    return err;
nla_put_failure:
    ALOGW("building message failed");
    return 2;
}