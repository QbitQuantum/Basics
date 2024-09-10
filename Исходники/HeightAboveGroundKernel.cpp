int HeightAboveGroundKernel::execute()
{
    // we require separate contexts for the input and ground files
    PointContextRef input_ctx;
    PointContextRef ground_ctx;

    // because we are appending HeightAboveGround to the input buffer, we must
    // register it's Dimension
    input_ctx.registerDim(Dimension::Id::HeightAboveGround);

    // StageFactory will be used to create required stages
    StageFactory f;

    // setup the reader, inferring driver type from the filename
    std::string reader_driver = f.inferReaderDriver(m_input_file);
    std::unique_ptr<Reader> input(f.createReader(reader_driver));
    Options readerOptions;
    readerOptions.add("filename", m_input_file);
    input->setOptions(readerOptions);

    // go ahead and execute to get the PointBuffer
    input->prepare(input_ctx);
    PointBufferSet pbSetInput = input->execute(input_ctx);
    PointBufferPtr input_buf = *pbSetInput.begin();

    PointBufferSet pbSetGround;
    PointBufferPtr ground_buf;

    if (m_use_classification)
    {
        // the user has indicated that the classification dimension exists, so
        // we will find all ground returns
        Option source("source",
                      "import numpy as np\n"
                      "def yow1(ins,outs):\n"
                      "  cls = ins['Classification']\n"
                      "  keep_classes = [2]\n"
                      "  keep = np.equal(cls, keep_classes[0])\n"
                      "  outs['Mask'] = keep\n"
                      "  return True\n"
                     );
        Option module("module", "MyModule");
        Option function("function", "yow1");
        Options opts;
        opts.add(source);
        opts.add(module);
        opts.add(function);

        // and create a PointBuffer of only ground returns
        std::unique_ptr<Filter> pred(f.createFilter("filters.predicate"));
        pred->setOptions(opts);
        pred->setInput(input.get());
        pred->prepare(ground_ctx);
        pbSetGround = pred->execute(ground_ctx);
        ground_buf = *pbSetGround.begin();
    }
    else
    {
        // the user has provided a file containing only ground returns, setup
        // the reader, inferring driver type from the filename
        std::string ground_driver = f.inferReaderDriver(m_ground_file);
        std::unique_ptr<Reader> ground(f.createReader(ground_driver));
        Options ro;
        ro.add("filename", m_ground_file);
        ground->setOptions(ro);

        // go ahead and execute to get the PointBuffer
        ground->prepare(ground_ctx);
        pbSetGround = ground->execute(ground_ctx);
        ground_buf = *pbSetGround.begin();
    }

    typedef pcl::PointXYZ PointT;
    typedef pcl::PointCloud<PointT> Cloud;
    typedef Cloud::Ptr CloudPtr;

    // convert the input PointBuffer to a PointCloud
    CloudPtr cloud(new Cloud);
    BOX3D const& bounds = input_buf->calculateBounds();
    pclsupport::PDALtoPCD(*input_buf, *cloud, bounds);

    // convert the ground PointBuffer to a PointCloud
    CloudPtr cloud_g(new Cloud);
    // here, we offset the ground cloud by the input bounds so that the two are aligned
    pclsupport::PDALtoPCD(*ground_buf, *cloud_g, bounds);

    // create a set of planar coefficients with X=Y=0,Z=1
    pcl::ModelCoefficients::Ptr coefficients(new pcl::ModelCoefficients());
    coefficients->values.resize(4);
    coefficients->values[0] = coefficients->values[1] = 0;
    coefficients->values[2] = 1.0;
    coefficients->values[3] = 0;

    // create the filtering object and project ground returns into xy plane
    pcl::ProjectInliers<PointT> proj;
    proj.setModelType(pcl::SACMODEL_PLANE);
    proj.setInputCloud(cloud_g);
    proj.setModelCoefficients(coefficients);
    CloudPtr cloud_projected(new Cloud);
    proj.filter(*cloud_projected);

    // setup the KdTree
    pcl::KdTreeFLANN<PointT> tree;
    tree.setInputCloud(cloud_projected);

    // loop over all points in the input cloud, finding the nearest neighbor in
    // the ground returns (XY plane only), and calculating the difference in z
    int32_t k = 1;
    for (size_t idx = 0; idx < cloud->points.size(); ++idx)
    {
        // Search for nearesrt neighbor of the query point
        std::vector<int32_t> neighbors(k);
        std::vector<float> distances(k);
        PointT temp_pt = cloud->points[idx];
        temp_pt.z = 0.0f;
        int num_neighbors = tree.nearestKSearch(temp_pt, k, neighbors, distances);

        double hag = cloud->points[idx].z - cloud_g->points[neighbors[0]].z;
        input_buf->setField(Dimension::Id::HeightAboveGround, idx, hag);
    }

    // populate BufferReader with the input PointBuffer, which now has the
    // HeightAboveGround dimension
    BufferReader bufferReader;
    bufferReader.addBuffer(input_buf);

    // we require that the output be BPF for now, to house our non-standard
    // dimension
    Options wo;
    wo.add("filename", m_output_file);
    std::unique_ptr<Writer> writer(f.createWriter("writers.bpf"));
    writer->setOptions(wo);
    writer->setInput(&bufferReader);
    writer->prepare(input_ctx);
    writer->execute(input_ctx);

    return 0;
}