    /**
     * Compute the histogram of euclidean distances from a query point to sample points on the shape. The histogram bins
     * uniformly subdivide the range of distances from zero to \a max_distance. If \a max_distance is negative, the shape scale
     * specified in the constructor will be used.
     *
     * @param position The position of the query point.
     * @param histogram The histogram to be computed.
     * @param max_distance The distance to the furthest point to consider for the histogram. A negative value indicates the
     *   entire shape is to be considered (in which case \a max_distance is set to the shape scale specified in the
     *   constructor). The histogram range is set appropriately.
     * @param sample_reduction_ratio The fraction of the available set of samples -- expressed as a number between 0 and 1 --
     *   that will be randomly selected and used to actually build the histogram. This may be useful for getting a more evenly
     *   sampled set of pairwise distances when calling this function with multiple query points (and an extra-large initial set
     *   of points). A negative value, or a value of 1, indicates all sample points will be used.
     */
    void computeGeodesic(Vector3 const & position, Histogram & histogram, Real max_distance, Real sample_reduction_ratio) const
    {
        if (sample_reduction_ratio < 0)
            sample_reduction_ratio = 1.1;  // play safe

        bool process_all = (max_distance < 0);
        if (process_all)
            max_distance = this->getNormalizationScale();

        histogram.setRange(0, std::max((double)max_distance, 1.0e-30));
        histogram.setZero();

        SampleGraph * graph = const_cast<SampleGraph *>(this->getSampleGraph());
        alwaysAssertM(graph, "LocalDistanceHistogram: Non-null sample graph required to compute geodesic distances");

        // Find the sample closest to the query position and use it as the source for all distance calculations
        long seed_index = -1;
        if (this->hasExternalKDTree())
            seed_index = this->getMutableExternalKDTree()->template closestElement<MetricL2>(position);
        else
            seed_index = this->getMutableInternalKDTree()->template closestElement<MetricL2>(position);

        alwaysAssertM(seed_index >= 0, "LocalDistanceHistogram: Seed sample for geodesic distances not found");

        // Assume the graph and the kd-tree have samples in the same sequence
        SampleGraph::SurfaceSample * seed_sample = const_cast<SampleGraph::SurfaceSample *>(&graph->getSample(seed_index));

        ShortestPaths<SampleGraph> shortest_paths;
        GeodesicCallback callback(histogram, sample_reduction_ratio);
        shortest_paths.dijkstraWithCallback(*graph, seed_sample, &callback, (process_all ? -1 : max_distance));
    }