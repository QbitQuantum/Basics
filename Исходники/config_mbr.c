struct write_list *
config_mbr(struct disk_info *dinfo)
{
    struct part_info *pinfo;
    uint32_t cur_lba = dinfo->skip_lba;
    uint32_t ext_lba = 0;
    struct write_list *wr_list = NULL;
    struct write_list *temp_wr = NULL;
    int cnt = 0;
    int extended = 0;

    if (!dinfo->part_lst)
        return NULL;

    for (cnt = 0; cnt < dinfo->num_parts; ++cnt) {
        pinfo = &dinfo->part_lst[cnt];

        /* Should we create an extedned partition? */
        if (cnt == (PC_NUM_BOOT_RECORD_PARTS - 1)) {
            if (cnt + 1 < dinfo->num_parts) {
                extended = 1;
                ext_lba = cur_lba;
                if ((temp_wr = mk_pri_pentry(dinfo, NULL, cnt, &cur_lba)))
                    wlist_add(&wr_list, temp_wr);
                else {
                    ALOGE("Cannot create primary extended partition.");
                    goto fail;
                }
            }
        }

        /* if extended, need 1 lba for ebr */
        if ((cur_lba + extended) >= dinfo->num_lba)
            goto nospace;
        else if (pinfo->len_kb != (uint32_t)-1) {
            uint32_t sz_lba = (pinfo->len_kb / dinfo->sect_size) * 1024;
            if ((cur_lba + sz_lba + extended) > dinfo->num_lba)
                goto nospace;
        }

        if (!extended)
            temp_wr = mk_pri_pentry(dinfo, pinfo, cnt, &cur_lba);
        else {
            struct part_info *pnext;
            pnext = cnt + 1 < dinfo->num_parts ? &dinfo->part_lst[cnt+1] : NULL;
            temp_wr = mk_ext_pentry(dinfo, pinfo, &cur_lba, ext_lba, pnext);
        }

        if (temp_wr)
            wlist_add(&wr_list, temp_wr);
        else {
            ALOGE("Cannot create partition %d (%s).", cnt, pinfo->name);
            goto fail;
        }
    }

    /* fill in the rest of the MBR with empty parts (if needed). */
    for (; cnt < PC_NUM_BOOT_RECORD_PARTS; ++cnt) {
        struct part_info blank;
        cur_lba = 0;
        memset(&blank, 0, sizeof(struct part_info));
        if (!(temp_wr = mk_pri_pentry(dinfo, &blank, cnt, &cur_lba))) {
            ALOGE("Cannot create blank partition %d.", cnt);
            goto fail;
        }
        wlist_add(&wr_list, temp_wr);
    }

    return wr_list;

nospace:
    ALOGE("Not enough space to add parttion '%s'.", pinfo->name);

fail:
    wlist_free(wr_list);
    return NULL;
}