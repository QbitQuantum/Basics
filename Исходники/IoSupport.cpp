unsigned int CIoSupport::ReadPartitionTable(PARTITION_TABLE *p_table)
{
#ifdef _XBOX
  ANSI_STRING a_file;
  OBJECT_ATTRIBUTES obj_attr;
  IO_STATUS_BLOCK io_stat_block;
  HANDLE handle;
  unsigned int stat;
  unsigned int ioctl_cmd_in_buf[100];
  unsigned int ioctl_cmd_out_buf[100];
  unsigned int partition_table_addr;

  memset(p_table, 0, sizeof(PARTITION_TABLE));

  RtlInitAnsiString(&a_file, "\\Device\\Harddisk0\\partition0");
  obj_attr.RootDirectory = 0;
  obj_attr.ObjectName = &a_file;
  obj_attr.Attributes = OBJ_CASE_INSENSITIVE;

  stat = NtOpenFile(&handle, (GENERIC_READ | 0x00100000), &obj_attr, &io_stat_block, (FILE_SHARE_READ | FILE_SHARE_WRITE), 0x10);

  if (stat != STATUS_SUCCESS)
  {
    return stat;
  }

  memset(ioctl_cmd_out_buf, 0, sizeof(ioctl_cmd_out_buf));
  memset(ioctl_cmd_in_buf, 0, sizeof(ioctl_cmd_in_buf));
  ioctl_cmd_in_buf[0] = IOCTL_SUBCMD_GET_INFO;


  stat = NtDeviceIoControlFile(handle, 0, 0, 0, &io_stat_block,
                               IOCTL_CMD_LBA48_ACCESS,
                               ioctl_cmd_in_buf, sizeof(ioctl_cmd_in_buf),
                               ioctl_cmd_out_buf, sizeof(ioctl_cmd_out_buf));

  NtClose(handle);
  if (stat != STATUS_SUCCESS)
  {
    return stat;
  }

  if ((ioctl_cmd_out_buf[LBA48_GET_INFO_MAGIC1_IDX] != LBA48_GET_INFO_MAGIC1_VAL) ||
      (ioctl_cmd_out_buf[LBA48_GET_INFO_MAGIC2_IDX] != LBA48_GET_INFO_MAGIC2_VAL))
  {

    return STATUS_UNSUCCESSFUL;
  }

  partition_table_addr = ioctl_cmd_out_buf[LBA48_GET_INFO_LOWCODE_BASE_IDX];
  partition_table_addr += ioctl_cmd_out_buf[LBA48_GET_INFO_PART_TABLE_OFS_IDX];

  memcpy(p_table, (void *)partition_table_addr, sizeof(PARTITION_TABLE));

  return STATUS_SUCCESS;
#else
  return (unsigned int) -1;
#endif
}