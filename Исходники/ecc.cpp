static void project_onto_jacobian_ECC(const Mat& src1, const Mat& src2, Mat& dst)
{
    /* this functions is used for two types of projections. If src1.cols ==src.cols
    it does a blockwise multiplication (like in the outer product of vectors)
    of the blocks in matrices src1 and src2 and dst
    has size (number_of_blcks x number_of_blocks), otherwise dst is a vector of size
    (number_of_blocks x 1) since src2 is "multiplied"(dot) with each block of src1.

    The number_of_blocks is equal to the number of parameters we are lloking for
    (i.e. rtanslation:2, euclidean: 3, affine: 6, homography: 8)

    */
    CV_Assert(src1.rows == src2.rows);
    CV_Assert((src1.cols % src2.cols) == 0);
    int w;

    float* dstPtr = dst.ptr<float>(0);

    if (src1.cols !=src2.cols){//dst.cols==1
        w  = src2.cols;
        for (int i=0; i<dst.rows; i++){
            dstPtr[i] = (float) src2.dot(src1.colRange(i*w,(i+1)*w));
        }
    }

    else {
        CV_Assert(dst.cols == dst.rows); //dst is square (and symmetric)
        w = src2.cols/dst.cols;
        Mat mat;
        for (int i=0; i<dst.rows; i++){

            mat = Mat(src1.colRange(i*w, (i+1)*w));
            dstPtr[i*(dst.rows+1)] = (float) pow(norm(mat),2); //diagonal elements

            for (int j=i+1; j<dst.cols; j++){ //j starts from i+1
                dstPtr[i*dst.cols+j] = (float) mat.dot(src2.colRange(j*w, (j+1)*w));
                dstPtr[j*dst.cols+i] = dstPtr[i*dst.cols+j]; //due to symmetry
            }
        }
    }
}