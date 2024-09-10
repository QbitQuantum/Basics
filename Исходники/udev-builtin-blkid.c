static int find_gpt_root(struct udev_device *dev, blkid_probe pr, bool test) {

#if defined(GPT_ROOT_NATIVE) && defined(ENABLE_EFI)

        _cleanup_free_ char *root_id = NULL;
        bool found_esp = false;
        blkid_partlist pl;
        int i, nvals, r;

        assert(pr);

        /* Iterate through the partitions on this disk, and see if the
         * EFI ESP we booted from is on it. If so, find the first root
         * disk, and add a property indicating its partition UUID. */

        errno = 0;
        pl = blkid_probe_get_partitions(pr);
        if (!pl)
                return -errno ?: -ENOMEM;

        nvals = blkid_partlist_numof_partitions(pl);
        for (i = 0; i < nvals; i++) {
                blkid_partition pp;
                const char *stype, *sid;
                sd_id128_t type;

                pp = blkid_partlist_get_partition(pl, i);
                if (!pp)
                        continue;

                sid = blkid_partition_get_uuid(pp);
                if (!sid)
                        continue;

                stype = blkid_partition_get_type_string(pp);
                if (!stype)
                        continue;

                if (sd_id128_from_string(stype, &type) < 0)
                        continue;

                if (sd_id128_equal(type, GPT_ESP)) {
                        sd_id128_t id, esp;

                        /* We found an ESP, let's see if it matches
                         * the ESP we booted from. */

                        if (sd_id128_from_string(sid, &id) < 0)
                                continue;

                        r = efi_loader_get_device_part_uuid(&esp);
                        if (r < 0)
                                return r;

                        if (sd_id128_equal(id, esp))
                                found_esp = true;

                } else if (sd_id128_equal(type, GPT_ROOT_NATIVE)) {
                        unsigned long long flags;

                        flags = blkid_partition_get_flags(pp);
                        if (flags & GPT_FLAG_NO_AUTO)
                                continue;

                        /* We found a suitable root partition, let's
                         * remember the first one. */

                        if (!root_id) {
                                root_id = strdup(sid);
                                if (!root_id)
                                        return -ENOMEM;
                        }
                }
        }

        /* We found the ESP on this disk, and also found a root
         * partition, nice! Let's export its UUID */
        if (found_esp && root_id)
                udev_builtin_add_property(dev, test, "ID_PART_GPT_AUTO_ROOT_UUID", root_id);
#endif

        return 0;
}