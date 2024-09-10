static void print_iface_info(uct_worker_h worker, uct_md_h md,
                             uct_tl_resource_desc_t *resource)
{
    uct_iface_config_t *iface_config;
    uct_iface_attr_t iface_attr;
    ucs_status_t status;
    uct_iface_h iface;
    char buf[200] = {0};
    uct_iface_params_t iface_params = {
        .field_mask            = UCT_IFACE_PARAM_FIELD_OPEN_MODE   |
                                 UCT_IFACE_PARAM_FIELD_DEVICE      |
                                 UCT_IFACE_PARAM_FIELD_STATS_ROOT  |
                                 UCT_IFACE_PARAM_FIELD_RX_HEADROOM |
                                 UCT_IFACE_PARAM_FIELD_CPU_MASK,
        .open_mode             = UCT_IFACE_OPEN_MODE_DEVICE,
        .mode.device.tl_name   = resource->tl_name,
        .mode.device.dev_name  = resource->dev_name,
        .stats_root            = ucs_stats_get_root(),
        .rx_headroom           = 0
    };

    UCS_CPU_ZERO(&iface_params.cpu_mask);
    status = uct_md_iface_config_read(md, resource->tl_name, NULL, NULL, &iface_config);
    if (status != UCS_OK) {
        return;
    }

    printf("#   Device: %s\n", resource->dev_name);

    status = uct_iface_open(md, worker, &iface_params, iface_config, &iface);
    uct_config_release(iface_config);

    if (status != UCS_OK) {
        printf("#   < failed to open interface >\n");
        return;
    }

    printf("#\n");
    printf("#      capabilities:\n");
    status = uct_iface_query(iface, &iface_attr);
    if (status != UCS_OK) {
        printf("#   < failed to query interface >\n");
    } else {
        printf("#            bandwidth: %-.2f MB/sec\n", iface_attr.bandwidth / UCS_MBYTE);
        printf("#              latency: %-.0f nsec", iface_attr.latency.overhead * 1e9);
        if (iface_attr.latency.growth > 0) {
            printf(" + %.0f * N\n", iface_attr.latency.growth * 1e9);
        } else {
            printf("\n");
        }
        printf("#             overhead: %-.0f nsec\n", iface_attr.overhead * 1e9);

        PRINT_CAP(PUT_SHORT, iface_attr.cap.flags, iface_attr.cap.put.max_short);
        PRINT_CAP(PUT_BCOPY, iface_attr.cap.flags, iface_attr.cap.put.max_bcopy);
        PRINT_ZCAP(PUT_ZCOPY, iface_attr.cap.flags, iface_attr.cap.put.min_zcopy,
                   iface_attr.cap.put.max_zcopy, iface_attr.cap.put.max_iov);

        if (iface_attr.cap.flags & UCT_IFACE_FLAG_PUT_ZCOPY) {
            printf("#  put_opt_zcopy_align: %s\n",
                   size_limit_to_str(0, iface_attr.cap.put.opt_zcopy_align));
            printf("#        put_align_mtu: %s\n",
                   size_limit_to_str(0, iface_attr.cap.put.align_mtu));
        }

        PRINT_CAP(GET_SHORT, iface_attr.cap.flags, iface_attr.cap.get.max_short);
        PRINT_CAP(GET_BCOPY, iface_attr.cap.flags, iface_attr.cap.get.max_bcopy);
        PRINT_ZCAP(GET_ZCOPY, iface_attr.cap.flags, iface_attr.cap.get.min_zcopy,
                   iface_attr.cap.get.max_zcopy, iface_attr.cap.get.max_iov);
        if (iface_attr.cap.flags & UCT_IFACE_FLAG_GET_ZCOPY) {
            printf("#  get_opt_zcopy_align: %s\n",
                   size_limit_to_str(0, iface_attr.cap.get.opt_zcopy_align));
            printf("#        get_align_mtu: %s\n",
                   size_limit_to_str(0, iface_attr.cap.get.align_mtu));
        }

        PRINT_CAP(AM_SHORT,  iface_attr.cap.flags, iface_attr.cap.am.max_short);
        PRINT_CAP(AM_BCOPY,  iface_attr.cap.flags, iface_attr.cap.am.max_bcopy);
        PRINT_ZCAP(AM_ZCOPY,  iface_attr.cap.flags, iface_attr.cap.am.min_zcopy,
                   iface_attr.cap.am.max_zcopy, iface_attr.cap.am.max_iov);
        if (iface_attr.cap.flags & UCT_IFACE_FLAG_AM_ZCOPY) {
            printf("#   am_opt_zcopy_align: %s\n",
                   size_limit_to_str(0, iface_attr.cap.am.opt_zcopy_align));
            printf("#         am_align_mtu: %s\n",
                   size_limit_to_str(0, iface_attr.cap.am.align_mtu));
            printf("#            am header: %s\n",
                   size_limit_to_str(0, iface_attr.cap.am.max_hdr));
        }

        PRINT_CAP(TAG_EAGER_SHORT, iface_attr.cap.flags,
                  iface_attr.cap.tag.eager.max_short);
        PRINT_CAP(TAG_EAGER_BCOPY, iface_attr.cap.flags,
                  iface_attr.cap.tag.eager.max_bcopy);
        PRINT_ZCAP(TAG_EAGER_ZCOPY, iface_attr.cap.flags, 0,
                   iface_attr.cap.tag.eager.max_zcopy,
                   iface_attr.cap.tag.eager.max_iov);

        if (iface_attr.cap.flags & UCT_IFACE_FLAG_TAG_RNDV_ZCOPY) {
            PRINT_ZCAP_NO_CHECK(TAG_RNDV_ZCOPY, 0,
                                iface_attr.cap.tag.rndv.max_zcopy,
                                iface_attr.cap.tag.rndv.max_iov);
            printf("#  rndv private header: %s\n",
                   size_limit_to_str(0, iface_attr.cap.tag.rndv.max_hdr));
        }

        if (iface_attr.cap.flags & (UCT_IFACE_FLAG_TAG_EAGER_SHORT |
                                    UCT_IFACE_FLAG_TAG_EAGER_BCOPY |
                                    UCT_IFACE_FLAG_TAG_EAGER_ZCOPY |
                                    UCT_IFACE_FLAG_TAG_RNDV_ZCOPY)) {
            PRINT_ZCAP_NO_CHECK(TAG_RECV, iface_attr.cap.tag.recv.min_recv,
                                iface_attr.cap.tag.recv.max_zcopy,
                                iface_attr.cap.tag.recv.max_iov);
            printf("#  tag_max_outstanding: %s\n",
                   size_limit_to_str(0, iface_attr.cap.tag.recv.max_outstanding));
        }

        if (iface_attr.cap.atomic32.op_flags  ||
            iface_attr.cap.atomic64.op_flags  ||
            iface_attr.cap.atomic32.fop_flags ||
            iface_attr.cap.atomic64.fop_flags) {
            if (iface_attr.cap.flags & UCT_IFACE_FLAG_ATOMIC_DEVICE) {
                printf("#               domain: device\n");
            } else if (iface_attr.cap.flags & UCT_IFACE_FLAG_ATOMIC_CPU) {
                printf("#               domain: cpu\n");
            }

            PRINT_ATOMIC_POST(ADD, iface_attr.cap);
            PRINT_ATOMIC_POST(AND, iface_attr.cap);
            PRINT_ATOMIC_POST(OR,  iface_attr.cap);
            PRINT_ATOMIC_POST(XOR, iface_attr.cap);

            PRINT_ATOMIC_FETCH(ADD,   iface_attr.cap, "f");
            PRINT_ATOMIC_FETCH(AND,   iface_attr.cap, "f");
            PRINT_ATOMIC_FETCH(OR,    iface_attr.cap, "f");
            PRINT_ATOMIC_FETCH(XOR,   iface_attr.cap, "f");
            PRINT_ATOMIC_FETCH(SWAP , iface_attr.cap, "");
            PRINT_ATOMIC_FETCH(CSWAP, iface_attr.cap, "");
        }

        buf[0] = '\0';
        if (iface_attr.cap.flags & (UCT_IFACE_FLAG_CONNECT_TO_EP |
                                    UCT_IFACE_FLAG_CONNECT_TO_IFACE)) {
            if (iface_attr.cap.flags & UCT_IFACE_FLAG_CONNECT_TO_EP) {
                strncat(buf, " to ep,", sizeof(buf) - 1);
            }
            if (iface_attr.cap.flags & UCT_IFACE_FLAG_CONNECT_TO_IFACE) {
                strncat(buf, " to iface,", sizeof(buf) - 1);
            }
            buf[strlen(buf) - 1] = '\0';
        } else {
            strncat(buf, " none", sizeof(buf) - 1);
        }
        printf("#           connection:%s\n", buf);

        printf("#             priority: %d\n", iface_attr.priority);

        printf("#       device address: %zu bytes\n", iface_attr.device_addr_len);
        if (iface_attr.cap.flags & UCT_IFACE_FLAG_CONNECT_TO_IFACE) {
            printf("#        iface address: %zu bytes\n", iface_attr.iface_addr_len);
        }
        if (iface_attr.cap.flags & UCT_IFACE_FLAG_CONNECT_TO_EP) {
            printf("#           ep address: %zu bytes\n", iface_attr.ep_addr_len);
        }

        buf[0] = '\0';
        if (iface_attr.cap.flags & (UCT_IFACE_FLAG_ERRHANDLE_SHORT_BUF   |
                                    UCT_IFACE_FLAG_ERRHANDLE_BCOPY_BUF   |
                                    UCT_IFACE_FLAG_ERRHANDLE_ZCOPY_BUF   |
                                    UCT_IFACE_FLAG_ERRHANDLE_AM_ID       |
                                    UCT_IFACE_FLAG_ERRHANDLE_REMOTE_MEM  |
                                    UCT_IFACE_FLAG_ERRHANDLE_PEER_FAILURE)) {

            if (iface_attr.cap.flags & (UCT_IFACE_FLAG_ERRHANDLE_SHORT_BUF |
                                        UCT_IFACE_FLAG_ERRHANDLE_BCOPY_BUF |
                                        UCT_IFACE_FLAG_ERRHANDLE_ZCOPY_BUF)) {
                strncat(buf, " buffer (", sizeof(buf) - 1);
                if (iface_attr.cap.flags & UCT_IFACE_FLAG_ERRHANDLE_SHORT_BUF) {
                    strncat(buf, "short,", sizeof(buf) - 1);
                }
                if (iface_attr.cap.flags & UCT_IFACE_FLAG_ERRHANDLE_BCOPY_BUF) {
                    strncat(buf, "bcopy,", sizeof(buf) - 1);
                }
                if (iface_attr.cap.flags & UCT_IFACE_FLAG_ERRHANDLE_ZCOPY_BUF) {
                    strncat(buf, "zcopy,", sizeof(buf) - 1);
                }
                buf[strlen(buf) - 1] = '\0';
                strncat(buf, "),", sizeof(buf) - 1);
            }
            if (iface_attr.cap.flags & UCT_IFACE_FLAG_ERRHANDLE_AM_ID) {
                strncat(buf, " active-message id,", sizeof(buf) - 1);
            }
            if (iface_attr.cap.flags & UCT_IFACE_FLAG_ERRHANDLE_REMOTE_MEM) {
                strncat(buf, " remote access,", sizeof(buf) - 1);
            }
            if (iface_attr.cap.flags & UCT_IFACE_FLAG_ERRHANDLE_PEER_FAILURE) {
                strncat(buf, " peer failure,", sizeof(buf) - 1);
            }
            buf[strlen(buf) - 1] = '\0';
        } else {
            strncat(buf, " none", sizeof(buf) - 1);
        }
        printf("#       error handling:%s\n", buf);
    }

    uct_iface_close(iface);
    printf("#\n");
}

static ucs_status_t print_tl_info(uct_md_h md, const char *tl_name,
                                  uct_tl_resource_desc_t *resources,
                                  unsigned num_resources,
                                  int print_opts,
                                  ucs_config_print_flags_t print_flags)
{
    ucs_async_context_t async;
    uct_worker_h worker;
    ucs_status_t status;
    unsigned i;

    status = ucs_async_context_init(&async, UCS_ASYNC_THREAD_LOCK_TYPE);
    if (status != UCS_OK) {
        return status;
    }

    /* coverity[alloc_arg] */
    status = uct_worker_create(&async, UCS_THREAD_MODE_SINGLE, &worker);
    if (status != UCS_OK) {
        goto out;
    }

    printf("#\n");
    printf("#   Transport: %s\n", tl_name);
    printf("#\n");

    if (num_resources == 0) {
        printf("# (No supported devices found)\n");
    }
    for (i = 0; i < num_resources; ++i) {
        ucs_assert(!strcmp(tl_name, resources[i].tl_name));
        print_iface_info(worker, md, &resources[i]);
    }

    uct_worker_destroy(worker);
out:
    ucs_async_context_cleanup(&async);
    return status;
}