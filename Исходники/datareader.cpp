// Load the data.
void GPCMDataReader::load(
    std::vector<std::string> filelist,      // List of files from which to load the data.
    std::vector<double> noiselist           // Amount of noise to add to each file.
    )
{
    // Read data files.
    int i = 0;
    for (std::vector<std::string>::iterator itr = filelist.begin();
         itr != filelist.end(); ++itr)
    {
        // Load the file.
        MatrixXd data = loadFile(*itr);

        // Load auxiliary data.
        MatrixXd aux = loadAuxFile(*itr);

        // Check for blank auxiliary data.
        if (aux.cols() == 0)
            aux.setZero(data.rows(),1);

        // Add noise if desired.
        addDataNoise(data,noiselist[i]);

        // Concatenate into Y.
        MatrixXd newY(data.rows()+Y.rows(),data.cols());
        MatrixXd newAux(data.rows()+Y.rows(),aux.cols());

        // Store data.
        if (Y.rows() > 0)
            newY << Y,data;
        else
            newY = data;

        // Store auxiliary.
        if (auxData.rows() > 0)
            newAux << auxData,aux;
        else
            newAux = aux;

        // Switch over to the new matrices.
        Y = newY;
        auxData = newAux;

        // Concatenate into sequence.
        sequence.push_back(Y.rows());

        // Increment index.
        i++;
    }

    // Do any additional processing here, such as computing velocities and building supplementary
    // data structures.
    postProcessData();

    // Remove constant entries.
    MatrixXd constantEntries;
    std::vector<int> constantIndices;
    std::vector<int> variableIndices;
    int totalIndices = removeConstantEntries(Y,constantEntries,
        constantIndices,variableIndices);

    // Remove constant entries from scales.
    if (supplementary->getScale().cols() > 0)
    {
        MatrixXd newScale(1,variableIndices.size());
        for (unsigned i = 0; i < variableIndices.size(); i++)
        {
            newScale(0,i) = supplementary->getScale()(0,variableIndices[i]);
        }
        supplementary->getScale() = newScale;
    }

    // Pass duplicate entry information to supplement.
    supplementary->setConstant(constantEntries,constantIndices,variableIndices,totalIndices);
}