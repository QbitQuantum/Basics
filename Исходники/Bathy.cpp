/**
 * Generates a bathymetryGrid by reading data from a local file.  Results are
 * dumped into topographyGrid.
 * @param topographyGrid A pointer to a zero-initialized Grid of size
 *      numRows x numCols.
 * @param inputFile The relative path to the topography file you wish to use.
 * @param inputFileType Use 'netcdf' if your file is in netcdf format.  Use
 *      'asc' if the file is a matrix of ascii values in the GIS asc format.
 * @param startRow The row to start reading data from.
 * @param startCol The col to start reading data from.
 * @param numRows The desired number of rows of data to read.
 * @param numCols The desired number of cols of data to read.
 * @param seriesName If inputFileType was set to 'netcdf', this should be set
 *      to the name of the series you wish to use.
 * @param timestamp A timestamp value used for error reporting.
 */
void getBathy(Grid* topographyGrid, std::string inputFile,
              std::string inputFileType, size_t startRow, size_t startCol,
              size_t numRows, size_t numCols, std::string seriesName,
              std::string timestamp) {
    // This will be the netCDF ID for the file and data variable.
    Eigen::MatrixXd temp;
    int ncid, varid, retval = -100;

    // NetCDF
    if (inputFileType.compare("netcdf") == 0) {
        // Data will be read in column major, so set up a matrix of inverse
        //    size to recieve it.
        temp.resize(numCols, numRows);
        // Open the file. NC_NOWRITE tells netCDF we want read-only access to
        //    the file.
        if ((retval = nc_open(inputFile.c_str(), NC_NOWRITE, &ncid))) {
            printError("ERROR: Cant open NetCDF File. Invalid inputFile path.",
                        retval, timestamp);
        }

        // Get the varid of the data variable, based on its name.
        if ((retval = nc_inq_varid(ncid, seriesName.c_str(), &varid))) {
            printError("ERROR: Can't access variable id.  Invalid seriesName.",
                        retval, timestamp);
        }
        // Read the data.
        try {
            // for whatever reason, this is in column, row order.
            static size_t start[] = {startRow, startCol};
            static size_t range[] = {numRows, numCols};
            retval = nc_get_vara_double(ncid, varid, start, range,
                                        temp.data());
            // TODO(Greg) Figure out a way to read data in row wise to avoid
            //             this transposition.
            topographyGrid->data.block(border, border, numRows, numCols) =
                            temp.transpose().block(0, 0, numRows, numCols);
        }
        catch (int i) {
            printError("ERROR: Error reading data.  Invalid file format.",
                        retval, timestamp);
        }
        // Close the file, freeing all resources.
        if ((retval = nc_close(ncid))) {
            printError("ERROR: Error closing the file.", retval, timestamp);
        }
    } else if (inputFileType.compare("asc") == 0) {
        // ASC
        temp.resize(numRows, numCols);
        std::ifstream input(inputFile);
        int null = 0;
        size_t numHeaderLines = 5,
               rowsLine = 1,
               colsLine = 0,
               nullLine = 5,
               cursor = 0,
               rows = 0,
               cols = 0,
               startRowIndex = startRow+numHeaderLines,
               endRowIndex = startRowIndex+numRows,
               i = 0,
               j = 0;
        std::string line = "";
        std::vector<std::string> vLine;
        if (input.is_open()) {
            for (cursor = 0; cursor < endRowIndex; cursor ++) {
                getline(input, line);

                if (cursor <= numHeaderLines) {
                    // Get the number of columns in the file
                    if (cursor == colsLine) {
                        vLine = split(&line, ' ');
                        if (!silent) {
                            std::cout << "\nAvailable Cols: " <<
                                         vLine[vLine.size()-1];
                        }
                        cols = stoi(vLine[vLine.size() - 1]);

                        if (cols < startCol + numCols) {
                            std::cout << "\nERROR, requested bathymetry " <<
                                    " grid column coordinates are out of" <<
                                    " bounds.\n";
                            exit(1);
                        }
                    } else if (cursor == rowsLine) {
                        // Get the number of rows in the file.
                        vLine = split(&line, ' ');
                        if (!silent) {
                        std::cout << "Available Rows:" <<
                                     vLine[vLine.size() - 1];
                        }
                        rows = stoi(vLine[vLine.size() - 1]);

                        if (rows < startRow + numRows) {
                            std::cout << "\nERROR, requested bathymetry" <<
                                    " grid row coordinates are out of" <<
                                    " bounds.\n";
                            exit(1);
                        }
                    } else if (cursor == nullLine) {
                        // Get the null value substitute
                        vLine = split(&line, ' ');
                        if (debug) {
                            std::cout << "Null values =" <<
                                         vLine[vLine.size() - 1] << "\n";
                        }
                        null = stoi(vLine[vLine.size() - 1]);
                    }
                } else if (cursor >= startRowIndex) {
                    vLine = split(&line, ' ');
                    for (i = startCol; i < startCol + numCols; i ++) {
                        // std::cout<<"accessing temp(" <<
                        // cursor-startRowIndex-1 << "," <<i-startCol<<")\n";
                        // std::cout<<"Cursor:"<<cursor<<"   SRI:" <<
                        // startRowIndex << "\n";
                        temp(cursor - startRowIndex, i - startCol) =
                                stod(vLine[i]);
                    }
                }
            }

            input.close();

            for (i = 0; i < numRows; i ++) {
                for (j = 0; j < numCols; j ++) {
                    if (temp(i, j) == null) {
                        temp(i, j) = 0;
                    }
                }
            }
            topographyGrid->data.block(border, border, numRows, numCols) =
                            temp.block(0, 0, numRows, numCols);
        } else {
            std::cout << "\nUnable to open bathymetry file: \"" << inputFile <<
                         "\"\n";
            exit(0);
        }
    } else {
        // Invalid filetype
        std::cout << "Bathymetry file type not supported.  Simulating" <<
                     "Bathymetry.\n";
        simulatetopographyGrid(topographyGrid, static_cast<int>(numRows),
                               static_cast<int>(numCols));
    }
    topographyGrid->clearNA();
    topographyGrid->data =
            topographyGrid->data.unaryExpr(std::ptr_fun(validateDepth));
    if (acousticParams["debug"] == "1") {
        // topographyGrid->printData();
        std::cout << "startx " << startCol << "\nXDist: "<< numCols <<
                  "\nstartY:  "<< startRow << "\nYDist: " << numRows << "\n";
        std::cout << "inputFileType: " << inputFileType << "\ninputFile: " <<
                  inputFile << "\nseriesName: " << seriesName << "\n";
        std::cout << "retval: " << retval << "\n" << "ncid: " << ncid << "\n\n";
    }
}