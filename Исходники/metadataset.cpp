///
/// \brief MetaDataset::MetaDataset
/// \param name Name of this dataset as displayed to user
/// \param main_window Main window of the program
/// \param log_file The log file
/// \param directory The current global working directory
/// \param method_description The description of the method used
/// \param endmember_selection The string used by the user to select endmembers
/// \param method An enum specifying the method
/// \param parent_datasets The datasets from which this dataset is extracted
///
MetaDataset::MetaDataset(QString name,
                         MainWindow *main_window,
                         QString *directory,
                         QString method_description,
                         MetaMethod::Method method,
                         QList<QSharedPointer<VespucciDataset> > parent_datasets)
    : VespucciDataset(name, main_window, directory)
{
    parent_datasets_ = parent_datasets;

    if(!ParentsValid()){
        throw std::runtime_error("Improper input to MetaDataset constructor");
        cerr << "Improper input to MetaDataset constructor\n";

    }
    method_ = method;
    method_description_ = method_description;
    mat spectra;
    vec wavelength = parent_datasets_[0]->wavelength();
    vec x;
    vec y;
    switch(method_) {
    case MetaMethod::AverageSpectra :
        try{
            spectra = ProcessAverage(x, y);
        }
        catch(std::exception e){
            throw std::runtime_error("MetaDataset::ProcessAverage");
        }

        break;
    case MetaMethod::ConcatenateDatasets :
        try{
            spectra = Concatenate(x, y);
        }
        catch(std::exception e){
            throw std::runtime_error("MetaDataset::Concatenate");
        }
        break;
    default:
        throw std::runtime_error("Improper input to MetaDataset");
    }

    try{
        SetData(spectra, wavelength, x, y);
        SetParentDatasetIndices(parent_coordinates_);
    }
    catch(std::exception e){
        throw std::runtime_error("Failure to set data in MetaDataset constructor");
    }
    vec indices_temp(spectra.n_cols);
    for (uword i = 0; i < indices_temp.n_elem; ++i){
        indices_temp(i) = i;
    }
    SetIndices(indices_temp);
}