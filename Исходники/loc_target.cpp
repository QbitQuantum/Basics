unsigned int loc_get_target(void)
{
    if (gTarget != (unsigned int)-1)
        return gTarget;

    static const char hw_platform[]      = "/sys/devices/soc0/hw_platform";
    static const char id[]               = "/sys/devices/soc0/soc_id";
    static const char hw_platform_dep[]  =
        "/sys/devices/system/soc/soc0/hw_platform";
    static const char id_dep[]           = "/sys/devices/system/soc/soc0/id";
    static const char mdm[]              = "/dev/mdm"; // No such file or directory

    char rd_hw_platform[LINE_LEN];
    char rd_id[LINE_LEN];
    char rd_mdm[LINE_LEN];
    char baseband[LINE_LEN];

    if (is_qca1530()) {
        gTarget = TARGET_QCA1530;
        goto detected;
    }

    loc_get_target_baseband(baseband, sizeof(baseband));

    if (!access(hw_platform, F_OK)) {
        read_a_line(hw_platform, rd_hw_platform, LINE_LEN);
    } else {
        read_a_line(hw_platform_dep, rd_hw_platform, LINE_LEN);
    }
    if (!access(id, F_OK)) {
        read_a_line(id, rd_id, LINE_LEN);
    } else {
        read_a_line(id_dep, rd_id, LINE_LEN);
    }

    if( !memcmp(baseband, STR_APQ, LENGTH(STR_APQ)) ){
        if( !memcmp(rd_id, MPQ8064_ID_1, LENGTH(MPQ8064_ID_1))
            && IS_STR_END(rd_id[LENGTH(MPQ8064_ID_1)]) )
            gTarget = TARGET_MPQ;
        else
            gTarget = TARGET_APQ_SA;
    }
    else {
        if( (!memcmp(rd_hw_platform, STR_LIQUID, LENGTH(STR_LIQUID))
             && IS_STR_END(rd_hw_platform[LENGTH(STR_LIQUID)])) ||
            (!memcmp(rd_hw_platform, STR_SURF,   LENGTH(STR_SURF))
             && IS_STR_END(rd_hw_platform[LENGTH(STR_SURF)])) ||
            (!memcmp(rd_hw_platform, STR_MTP,   LENGTH(STR_MTP))
             && IS_STR_END(rd_hw_platform[LENGTH(STR_MTP)]))) {

            if (!read_a_line( mdm, rd_mdm, LINE_LEN))
                gTarget = TARGET_MDM;
        }
        else if( (!memcmp(rd_id, MSM8930_ID_1, LENGTH(MSM8930_ID_1))
                   && IS_STR_END(rd_id[LENGTH(MSM8930_ID_1)])) ||
                  (!memcmp(rd_id, MSM8930_ID_2, LENGTH(MSM8930_ID_2))
                   && IS_STR_END(rd_id[LENGTH(MSM8930_ID_2)])) )
             gTarget = TARGET_MSM_NO_SSC;
        else
             gTarget = TARGET_UNKNOWN;
    }

detected:
    LOC_LOGD("HAL: %s returned %d", __FUNCTION__, gTarget);
    return gTarget;
}