void runSelect(unsigned int * d_result)
{
    switch(type)
    {
    case 1:
        copyImage(h_img, d_result, width, height);
        break;
    case 2:
        bilateralFilterRGBA(d_result, width, height, euclidean_delta, filter_radius, iterations, nthreads);
        //bilateralFilterGold(h_img, h_temp, euclidean_delta, width, height, filter_radius);
        //copyImage(h_temp, d_result, width, height);
        break;
    default:
        break;
    }
}