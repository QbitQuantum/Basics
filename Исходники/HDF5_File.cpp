/**
 * Read header from the input file.
 * @param [in] InputFile - Input file to read from
 */
void THDF5_FileHeader::ReadHeaderFromInputFile(THDF5_File & InputFile){
    
    // read file type
    HDF5_FileHeaderValues[hdf5_fhi_file_type] = InputFile.ReadStringAttribute("/",HDF5_FileHeaderNames[hdf5_fhi_file_type].c_str());
    
    if (GetFileType() == hdf5_ft_input) {                
        HDF5_FileHeaderValues[hdf5_fhi_created_by]       = InputFile.ReadStringAttribute("/",HDF5_FileHeaderNames[hdf5_fhi_created_by].c_str());
        HDF5_FileHeaderValues[hdf5_fhi_creation_date]    = InputFile.ReadStringAttribute("/",HDF5_FileHeaderNames[hdf5_fhi_creation_date].c_str());
        HDF5_FileHeaderValues[hdf5_fhi_file_description] = InputFile.ReadStringAttribute("/",HDF5_FileHeaderNames[hdf5_fhi_file_description].c_str());
        HDF5_FileHeaderValues[hdf5_fhi_major_version]    = InputFile.ReadStringAttribute("/",HDF5_FileHeaderNames[hdf5_fhi_major_version].c_str());
        HDF5_FileHeaderValues[hdf5_fhi_minor_version]    = InputFile.ReadStringAttribute("/",HDF5_FileHeaderNames[hdf5_fhi_minor_version].c_str());        
    }
    
    
}// end of ReadHeaderFromInputFile