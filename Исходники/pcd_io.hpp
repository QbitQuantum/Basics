template <typename PointT> int
pcl::PCDWriter::writeBinary (const std::string &file_name, 
                             const pcl::PointCloud<PointT> &cloud)
{
  if (cloud.empty ())
  {
    throw pcl::IOException ("[pcl::PCDWriter::writeBinary] Input point cloud has no data!");
    return (-1);
  }
  int data_idx = 0;
  std::ostringstream oss;
  oss << generateHeader<PointT> (cloud) << "DATA binary\n";
  oss.flush ();
  data_idx = static_cast<int> (oss.tellp ());

#if _WIN32
  HANDLE h_native_file = CreateFileA (file_name.c_str (), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  if (h_native_file == INVALID_HANDLE_VALUE)
  {
    throw pcl::IOException ("[pcl::PCDWriter::writeBinary] Error during CreateFile!");
    return (-1);
  }
#else
  int fd = pcl_open (file_name.c_str (), O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd < 0)
  {
    throw pcl::IOException ("[pcl::PCDWriter::writeBinary] Error during open!");
    return (-1);
  }
#endif
  // Mandatory lock file
  boost::interprocess::file_lock file_lock;
  setLockingPermissions (file_name, file_lock);

  std::vector<pcl::PCLPointField> fields;
  std::vector<int> fields_sizes;
  size_t fsize = 0;
  size_t data_size = 0;
  size_t nri = 0;
  pcl::getFields (cloud, fields);
  // Compute the total size of the fields
  for (size_t i = 0; i < fields.size (); ++i)
  {
    if (fields[i].name == "_")
      continue;
    
    int fs = fields[i].count * getFieldSize (fields[i].datatype);
    fsize += fs;
    fields_sizes.push_back (fs);
    fields[nri++] = fields[i];
  }
  fields.resize (nri);
  
  data_size = cloud.points.size () * fsize;

  // Prepare the map
#if _WIN32
  HANDLE fm = CreateFileMappingA (h_native_file, NULL, PAGE_READWRITE, 0, (DWORD) (data_idx + data_size), NULL);
  if (fm == NULL)
  {
      throw pcl::IOException("[pcl::PCDWriter::writeBinary] Error during memory map creation ()!");
      return (-1);
  }
  char *map = static_cast<char*>(MapViewOfFile (fm, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, data_idx + data_size));
  CloseHandle (fm);

#else
  // Stretch the file size to the size of the data
  off_t result = pcl_lseek (fd, getpagesize () + data_size - 1, SEEK_SET);

  if (result < 0)
  {
    pcl_close (fd);
    resetLockingPermissions (file_name, file_lock);
    PCL_ERROR ("[pcl::PCDWriter::writeBinary] lseek errno: %d strerror: %s\n", errno, strerror (errno));

    throw pcl::IOException ("[pcl::PCDWriter::writeBinary] Error during lseek ()!");
    return (-1);
  }
  // Write a bogus entry so that the new file size comes in effect
  result = static_cast<int> (::write (fd, "", 1));
  if (result != 1)
  {
    pcl_close (fd);
    resetLockingPermissions (file_name, file_lock);
    throw pcl::IOException ("[pcl::PCDWriter::writeBinary] Error during write ()!");
    return (-1);
  }

  char *map = static_cast<char*> (mmap (0, data_idx + data_size, PROT_WRITE, MAP_SHARED, fd, 0));
  if (map == reinterpret_cast<char*> (-1)) //MAP_FAILED)
  {
    pcl_close (fd);
    resetLockingPermissions (file_name, file_lock);
    throw pcl::IOException ("[pcl::PCDWriter::writeBinary] Error during mmap ()!");
    return (-1);
  }
#endif

  // Copy the header
  memcpy (&map[0], oss.str ().c_str (), data_idx);

  // Copy the data
  char *out = &map[0] + data_idx;
  for (size_t i = 0; i < cloud.points.size (); ++i)
  {
    int nrj = 0;
    for (size_t j = 0; j < fields.size (); ++j)
    {
      memcpy (out, reinterpret_cast<const char*> (&cloud.points[i]) + fields[j].offset, fields_sizes[nrj]);
      out += fields_sizes[nrj++];
    }
  }

  // If the user set the synchronization flag on, call msync
#if !_WIN32
  if (map_synchronization_)
    msync (map, data_idx + data_size, MS_SYNC);
#endif

  // Unmap the pages of memory
#if _WIN32
    UnmapViewOfFile (map);
#else
  if (munmap (map, (data_idx + data_size)) == -1)
  {
    pcl_close (fd);
    resetLockingPermissions (file_name, file_lock);
    throw pcl::IOException ("[pcl::PCDWriter::writeBinary] Error during munmap ()!");
    return (-1);
  }
#endif
  // Close file
#if _WIN32
  CloseHandle (h_native_file);
#else
  pcl_close (fd);
#endif
  resetLockingPermissions (file_name, file_lock);
  return (0);
}