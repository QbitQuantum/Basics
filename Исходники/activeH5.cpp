//'@title This function writes a character vector to the meta data
//'
//'@description This function writes a character vector to the meta data and is intended for internal use.
//'
//'@param charName the name that will be given to the meta data character vector
//'@param charVec the character vector to be written as meta data
//'@param filePath the path to the h5 file where the data will be written
//'@param update integer denoting whether the data item is new or whether it is an update 
//'(which will overwrite any previous item)
//'@return int 0
// [[Rcpp::export]]
int h5WriteCharVector(std::string charName, SEXP charVec, std::string filePath, int update)
{
  H5File *file = new H5File(filePath, H5F_ACC_RDWR);
  
  int len = Rf_length(charVec);
  hsize_t DIM1 = len;
  int rank = 1;
  //cout << "The length is ... " << len << endl;
  // Create a datatype to refer to
  StrType vlst(0, H5T_VARIABLE);
  
  // This is the char array
  char** arr = convertCharArray(charVec);
  
  string meta = "/MetaData";
  
  // Group Meta Group
  Group* metaGroup = new Group(file->openGroup(meta));
  
  // The dataset and dataspace
  hsize_t dims[] = {DIM1};
  //hsize_t maxdims[] = {H5S_UNLIMITED};
  DataSet dataset;
  if(update == 1)
  {
    string slash = "/";
    string groupName = meta + slash + charName;
    file->unlink(groupName); 
  }
  
  DataSpace dataspace(rank, dims);
  dataset = metaGroup->createDataSet(charName, vlst, dataspace);
  dataset.write(arr, vlst);
  dataset.close(); //nn
  metaGroup->close();
  file->close();
  return 0;
}