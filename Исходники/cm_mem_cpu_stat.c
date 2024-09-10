T_CM_DISK_PARTITION_STAT_ALL *
cm_get_host_disk_partition_stat (T_CM_ERROR * err_buf)
{
  int i, len;
  char buf[160] = { 0 };
  ULONGLONG total_size[32], free_size[32];
  char names[32][4] = { 0 };
  char *token;
  T_CM_DISK_PARTITION_STAT_ALL *res;

  len = GetLogicalDriveStringsA (sizeof (buf), buf);

  for (i = 0; i < len; i++)
    {
      if (buf[i] == 0)
	{
	  buf[i] = ';';
	}
    }

  buf[len - 1] = 0;
  i = 0;

  for (token = strtok (buf, ";"); token != NULL && i < 32;
       token = strtok (NULL, ";"))
    {
      if (GetDriveTypeA (token) == DRIVE_FIXED)
	{
	  ULARGE_INTEGER ul_total, ul_free;
	  GetDiskFreeSpaceExA (token, &ul_free, &ul_total, NULL);
	  total_size[i] = ul_total.QuadPart;
	  free_size[i] = ul_free.QuadPart;
	  strcpy_limit (names[i], token, sizeof (names[i]));
	  i++;
	}
    }


  res = malloc (sizeof (T_CM_DISK_PARTITION_STAT_ALL));

  if (res == NULL)
    {
      return NULL;
    }

  res->num_stat = i;
  res->partitions = malloc (sizeof (T_CM_DISK_PARTITION_STAT) * i);

  if (res->partitions == NULL)
    {
      FREE_MEM (res);
      return NULL;
    }

  for (i = 0; i < res->num_stat; i++)
    {
      res->partitions[i].avail = free_size[i];
      res->partitions[i].size = total_size[i];
      res->partitions[i].used = total_size[i] - free_size[i];
      strcpy_limit (res->partitions[i].name, names[i],
		    sizeof (res->partitions[i].name));
    }

  return res;
}