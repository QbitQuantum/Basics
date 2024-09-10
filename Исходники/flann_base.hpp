    Index(const Matrix<ElementType>& features, const IndexParams& params, Distance distance = Distance() )
        : index_params_(params)
    {
        flann_algorithm_t index_type = get_param<flann_algorithm_t>(params,"algorithm");
        loaded_ = false;

        if (index_type == FLANN_INDEX_SAVED) {
            nnIndex_ = load_saved_index<Distance>(features, get_param<cv::String>(params,"filename"), distance);
            loaded_ = true;
        }
        else {
            nnIndex_ = create_index_by_type<Distance>(features, params, distance);
        }
    }