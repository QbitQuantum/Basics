void StateSet::init_from_datafile(std::string filename) {
	// open other file read-only
	H5::H5File otherfile;
	otherfile.openFile(filename, H5F_ACC_RDONLY);
	H5::Group otherroot = otherfile.openGroup("/");
	// check that grid properties match
	int othersx, othersy, otherN;
	double otherdx;
	otherroot.openAttribute("num_states").read(H5::PredType::NATIVE_INT, &otherN);
	otherroot.openAttribute("grid_sizex").read(H5::PredType::NATIVE_INT, &othersx);
	otherroot.openAttribute("grid_sizex").read(H5::PredType::NATIVE_INT, &othersy);
	otherroot.openAttribute("grid_delta").read(H5::PredType::NATIVE_DOUBLE, &otherdx);
	if (static_cast<int>(N) != otherN)
		throw GeneralError("Cannot copy state data from datafile: value for num_states does not match.");
	if (static_cast<int>(datalayout.sizex) != othersx)
		throw GeneralError("Cannot copy state data from datafile: value for grid_sizex does not match.");
	if (static_cast<int>(datalayout.sizey) != othersy)
		throw GeneralError("Cannot copy state data from datafile: value for grid_sizey does not match.");
	if (datalayout.dx != otherdx)
		throw GeneralError("Cannot copy state data from datafile: value for grid_delta does not match.");
	// copy data
	H5::DataSet other_states_data = otherfile.openDataSet("/states");
	other_states_data.read(state_array->get_dataptr(), other_states_data.getArrayType());
}