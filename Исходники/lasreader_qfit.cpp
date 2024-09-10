BOOL LASreaderQFIT::open(const char* file_name)
{
  if (file_name == 0)
  {
    fprintf(stderr,"ERROR: fine name pointer is zero\n");
    return FALSE;
  }

  // open file

  file = fopen(file_name, "rb");
  if (file == 0)
  {
    fprintf(stderr, "ERROR: cannot open file '%s'\n", file_name);
    return FALSE;
  }

  // create input stream

  ByteStreamIn* in;
  if (IS_LITTLE_ENDIAN())
    in = new ByteStreamInFileLE(file);
  else
    in = new ByteStreamInFileBE(file);

  // clean the header

  header.clean();

  // set projection

  LASvlr_key_entry geo_keys[4];

  // projected coordinates
  geo_keys[0].key_id = 1024; // GTModelTypeGeoKey
  geo_keys[0].tiff_tag_location = 0;
  geo_keys[0].count = 1;
  geo_keys[0].value_offset = 2; // ModelTypeGeographic

  // ellipsoid used with latitude/longitude coordinates
  geo_keys[1].key_id = 2048; // GeographicTypeGeoKey
  geo_keys[1].tiff_tag_location = 0;
  geo_keys[1].count = 1;
  geo_keys[1].value_offset = 4326; // GCS_WGS_84 

  // vertical units
  geo_keys[2].key_id = 4099; // VerticalUnitsGeoKey
  geo_keys[2].tiff_tag_location = 0;
  geo_keys[2].count = 1;
  geo_keys[2].value_offset = 9001; // meter

  // vertical datum
  geo_keys[3].key_id = 4096; // VerticalCSTypeGeoKey
  geo_keys[3].tiff_tag_location = 0;
  geo_keys[3].count = 1;
  geo_keys[3].value_offset = 5030; // VertCS_WGS_84_ellipsoid

  header.set_geo_keys(4, geo_keys);

  // maybe set creation date

#ifdef _WIN32
  WIN32_FILE_ATTRIBUTE_DATA attr;
	SYSTEMTIME creation;
  GetFileAttributesEx(file_name, GetFileExInfoStandard, &attr);
	FileTimeToSystemTime(&attr.ftCreationTime, &creation);
  int startday[13] = {-1, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
  header.file_creation_day = startday[creation.wMonth] + creation.wDay;
  header.file_creation_year = creation.wYear;
  // leap year handling
  if ((((creation.wYear)%4) == 0) && (creation.wMonth > 2)) header.file_creation_day++;
#else
  header.file_creation_day = 333;
  header.file_creation_year = 2011;
#endif

  return open(in);
}