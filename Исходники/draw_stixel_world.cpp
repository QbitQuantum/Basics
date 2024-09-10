void v_disparity_data_to_matrix(const FastGroundPlaneEstimator::v_disparity_data_t &image_data,
                                Eigen::MatrixXf &image_matrix)
{
    typedef FastGroundPlaneEstimator::v_disparity_data_t::const_reference row_slice_t;

    const int rows = image_data.shape()[0], cols = image_data.shape()[1];
    image_matrix.setZero(rows, cols);
    for(int row=0; row < rows; row +=1)
    {
        row_slice_t row_slice = image_data[row];
        row_slice_t::const_iterator data_it = row_slice.begin();
        for(int col=0; col < cols; ++data_it, col+=1)
        {
            //printf("%.f\n", *data_it);
            image_matrix(row, col) = *data_it;
        } // end "for each column"

    } // end of "for each row"

    return;
}