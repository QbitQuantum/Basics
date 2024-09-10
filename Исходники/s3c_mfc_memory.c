unsigned int s3c_mfc_get_data_buf_phys_addr()
{
    unsigned int phys_addr;

    s3c_mfc_phys_data_buf = s3c_mfc_get_risc_buf_phys_addr(MFC_MAX_INSTANCE_NUM);
    phys_addr = Align(s3c_mfc_phys_data_buf, 4*BUF_L_UNIT);

    return phys_addr;
}