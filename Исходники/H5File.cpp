H5DataSet * H5File::CreateDataSet ( const std::string &name,
                                    hsize_t rank,
                                    const hsize_t dims[],
                                    const hsize_t chunking[],
                                    int compression,
                                    hid_t type )
{
  size_t id = mCurrentId;
  mCurrentId++;
  H5DataSet *ds = new H5DataSet ( id );
  string groupName, dsName;
  FillInGroupFromName ( name, groupName, dsName );
  hid_t group = GetOrCreateGroup ( mHFile, groupName );
  ds->SetGroup ( group );
  ds->SetParent ( this );
  ds->SetName ( dsName );
  ds->SetCompression ( compression );
  ds->SetDataspace ( rank, dims, chunking, type );
  if ( ds->CreateDataSet() )
  {
    mDSMap[id] = ds;
    return mDSMap[id];
  }
  delete ds;
  return NULL;
}