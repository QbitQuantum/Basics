static int fail_this_path(int fd, int lun, int use_6_byte)
{
    unsigned char fail_paths_pg[308];
    struct rdac_legacy_page *rdac_page;
    struct rdac_expanded_page *rdac_page_exp;
    struct rdac_page_common *rdac_common = NULL;
    int res;
    char b[80];

    if (use_6_byte && lun > 32) {
        pr2serr("must use 10 byte cdb to fail luns over 32\n");
        return -1;
    }

    memset(fail_paths_pg, 0, 308);
    if (use_6_byte) {
        memcpy(fail_paths_pg, mode6_hdr, 4);
        memcpy(fail_paths_pg + 4, block_descriptor, 8);
        rdac_page = (struct rdac_legacy_page *)(fail_paths_pg + 4 + 8);
        rdac_page->page_code = RDAC_CONTROLLER_PAGE;
        rdac_page->page_length = RDAC_CONTROLLER_PAGE_LEN;
        rdac_common = &rdac_page->attr;
        memset(rdac_page->lun_table, 0x0, 32);
        rdac_page->lun_table[lun] = 0x81;
    } else {
        memcpy(fail_paths_pg, mode10_hdr, 8);
        rdac_page_exp = (struct rdac_expanded_page *)
                        (fail_paths_pg + 8);
        rdac_page_exp->page_code = RDAC_CONTROLLER_PAGE | 0x40;
        rdac_page_exp->subpage_code = 0x1;
        sg_put_unaligned_be16(EXPANDED_LUN_SPACE_PAGE_LEN,
                              rdac_page_exp->page_length + 0);
        rdac_common = &rdac_page_exp->attr;
        memset(rdac_page_exp->lun_table, 0x0, 256);
        rdac_page_exp->lun_table[lun] = 0x81;
    }

    rdac_common->current_mode_lsb =  RDAC_FAIL_SELECTED_PATHS;
    rdac_common->quiescence = RDAC_QUIESCENCE_TIME;
    rdac_common->options = RDAC_FORCE_QUIESCENCE;

    if (use_6_byte) {
        res = sg_ll_mode_select6(fd, 1 /* pf */, 0 /* sp */,
                                 fail_paths_pg, 118,
                                 1, (do_verbose ? 2 : 0));
    } else {
        res = sg_ll_mode_select10(fd, 1 /* pf */, 0 /* sp */,
                                  fail_paths_pg, 308,
                                  1, (do_verbose ? 2: 0));
    }

    switch (res) {
    case 0:
        if (do_verbose)
            pr2serr("fail paths successful\n");
        break;
    default:
        sg_get_category_sense_str(res, sizeof(b), b, do_verbose);
        pr2serr("fail paths page (lun=%d) failed: %s\n", lun, b);
        break;
    }

    return res;
}