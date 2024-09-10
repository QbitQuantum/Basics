void Bundle2::saveGeometry(const boost::filesystem::path& fileName) const {
	H5::H5File bundleFile;
	bundleFile.openFile(fileName.string(), H5F_ACC_RDWR);

	H5::Group rootGroup = bundleFile.openGroup("/");

	// If the group "Geometry" exists, delete it!
	if(checkGeometry_(bundleFile)) {
		rootGroup.unlink("Geometry");
	}

	// Creating group Geometry
	H5::Group geometryGroup = rootGroup.createGroup("Geometry");

	// Saving poses
	const hsize_t posesChunkDim[] = { 3, 12 };
	H5::DSetCreatPropList posesPropList;
	posesPropList.setLayout(H5D_CHUNKED);
	posesPropList.setChunk(2, posesChunkDim);
	posesPropList.setDeflate(9);

	const hsize_t posesMaxDim[] = { H5S_UNLIMITED, 12 };
	const hsize_t posesCurDim[] = { frames_.size(), 12 };
	H5::DataSpace posesDS(2, posesCurDim, posesMaxDim);

	H5::DataSet posesDataSet = geometryGroup.createDataSet("Poses", H5::PredType::IEEE_F64LE, posesDS, posesPropList);

	double* posesData = (double*)malloc(frames_.size()*12*sizeof(double));
	size_t i = 0;
	for(deque<Frame*>::const_iterator it = frames_.begin(); it != frames_.end(); it++) {
		posesData[i*12] = (*it)->pose()->t().x();
		posesData[i*12 + 1] = (*it)->pose()->t().y();
		posesData[i*12 + 2] = (*it)->pose()->t().z();

		core::Matrix<double> R = (*it)->pose()->R();
		posesData[i*12 + 3] = R[0][0];
		posesData[i*12 + 4] = R[1][0];
		posesData[i*12 + 5] = R[2][0];
		posesData[i*12 + 6] = R[0][1];
		posesData[i*12 + 7] = R[1][1];
		posesData[i*12 + 8] = R[2][1];
		posesData[i*12 + 9] = R[0][2];
		posesData[i*12 + 10] = R[1][2];
		posesData[i*12 + 11] = R[2][2];

		++i;
	}

	posesDataSet.write((const void*)posesData, H5::PredType::NATIVE_DOUBLE, H5::DataSpace::ALL, H5::DataSpace::ALL);
	free((void*)posesData);
	posesDataSet.close();
	posesDS.close();

	// Saving points
	const hsize_t pointsChunkDim[] = {10, 3};
	H5::DSetCreatPropList pointsPropList;
	pointsPropList.setLayout(H5D_CHUNKED);
	pointsPropList.setChunk(2, pointsChunkDim);
	pointsPropList.setDeflate(9);

	const hsize_t pointsMaxDim[] = { H5S_UNLIMITED, 3 };
	const hsize_t pointsCurDim[] = { tracks_.size(), 3 };
	H5::DataSpace pointsDS(2, pointsCurDim, pointsMaxDim);

	H5::DataSet pointsDataSet = geometryGroup.createDataSet("Points", H5::PredType::IEEE_F64LE, pointsDS, pointsPropList);

	double* pointsData = (double*)malloc(tracks_.size()*3*sizeof(double));

	i = 0;
	for(deque<Track*>::const_iterator it = tracks_.begin(); it != tracks_.end(); it++) {
		pointsData[i*3] = (*it)->point()->coords().x();
		pointsData[i*3 + 1] = (*it)->point()->coords().y();
		pointsData[i*3 + 2] = (*it)->point()->coords().z();

		++i;
	}

	pointsDataSet.write((const void*)pointsData, H5::PredType::NATIVE_DOUBLE, H5::DataSpace::ALL, H5::DataSpace::ALL);
	free((void*)pointsData);
	pointsDataSet.close();
	pointsDS.close();

	// Saving inlier information
	const hsize_t inliersChunkDim[] = { 3 };
	H5::DSetCreatPropList inliersPropList;
	inliersPropList.setLayout(H5D_CHUNKED);
	inliersPropList.setChunk(1, inliersChunkDim);
	inliersPropList.setDeflate(9);

	const hsize_t inliersMaxDim[] = { H5S_UNLIMITED };
	const hsize_t inliersCurDim[] = { frames_.size() };
	H5::DataSpace inliersDS(1, inliersCurDim, inliersMaxDim);

	H5::VarLenType inliersType(&H5::PredType::STD_U8LE);

	H5::DataSet inliersDataSet = geometryGroup.createDataSet("Inliers", inliersType, inliersDS, inliersPropList);

	i = 0;
	for(deque<Frame*>::const_iterator it = frames_.begin(); it != frames_.end(); it++) {
		hvl_t inliersLine;

        size_t inliersLineSize = 0;
        for(size_t j = 0; j < (*it)->size(); ++j) {
            View& v = (**it)[j];
            for(unsigned int cam = 0; cam < v.numCameras(); ++cam) {
                if(v.inCamera(cam)) ++inliersLineSize;
            }
        }

		inliersLine.len = inliersLineSize;
		inliersLine.p = malloc(inliersLineSize*sizeof(unsigned char));

        size_t k = 0;
		for(size_t j = 0; j < (*it)->size(); ++j) {
            View& v = (**it)[j];
            for(unsigned int cam = 0; cam < v.numCameras(); ++cam) {
                if(v.inCamera(cam)) {
                    ((unsigned char*)(inliersLine.p))[k] = v.ray(cam).inlier()?1:0;
                    ++k;
                }
            }
        }

		const hsize_t dsOffset[] = { i };
		const hsize_t dsCount[] = { 1 };
		H5::DataSpace inliersCurDS = inliersDataSet.getSpace();
		inliersCurDS.selectHyperslab(H5S_SELECT_SET, dsCount, dsOffset);

		const hsize_t memDim[] = { 1 };
		H5::DataSpace memDS(1, memDim, memDim);

		H5::VarLenType memType(&H5::PredType::NATIVE_UCHAR);

		inliersDataSet.write((const void*)&inliersLine, memType, memDS, inliersCurDS);

		memType.close();
		memDS.close();
		inliersCurDS.close();

		free(inliersLine.p);

		++i;
	}

	inliersDataSet.close();
	inliersType.close();
	inliersDS.close();

	// Saving curves
	if(!curves_.empty()) {
		const hsize_t chunkDim[] = { 5 };
		H5::DSetCreatPropList propList;
		propList.setLayout(H5D_CHUNKED);
		propList.setChunk(1, chunkDim);
		propList.setDeflate(9);

		H5::VarLenType curveDatasetType(&H5::PredType::STD_U64LE);

		hsize_t curvesDim[] = { curves_.size() };
		hsize_t curvesMaxDim[] = { H5S_UNLIMITED };
		H5::DataSpace curvesDataspace(1, curvesDim, curvesMaxDim);

		H5::DataSet curvesDataset = geometryGroup.createDataSet("Curves", curveDatasetType, curvesDataspace, propList);

		for(size_t i = 0; i < curves_.size(); ++i) {
			hvl_t curveLine;

			curveLine.len = curves_[i].size();
			curveLine.p = malloc(curves_[i].size()*sizeof(size_t));

			for(size_t j = 0; j < curves_[i].size(); ++j) ((size_t*)(curveLine.p))[j] = curves_[i].track(j);

			const hsize_t dsOffset[] = { i };
			const hsize_t dsCount[] = { 1 };
			H5::DataSpace curDS = curvesDataset.getSpace();
			curDS.selectHyperslab(H5S_SELECT_SET, dsCount, dsOffset);

			const hsize_t memDim[] = { 1 };
			H5::DataSpace memDS(1, memDim, memDim);

			H5::VarLenType memType(&H5::PredType::NATIVE_HSIZE);

			curvesDataset.write((const void*)&curveLine, memType, memDS, curDS);

			memType.close();
			memDS.close();
			curDS.close();

			free(curveLine.p);
 		}

		curvesDataset.close();
		curvesDataspace.close();
		curveDatasetType.close();
		propList.close();
	}

	geometryGroup.close();
	rootGroup.close();
	bundleFile.close();
}