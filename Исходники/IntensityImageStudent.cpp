void IntensityImageStudent::set(const IntensityImageStudent &other) {
    Intensity** t_intensity_array = intensity_image;
    int old_height = height;
    width = other.width;
    height = other.height;

    init_intensity_image();
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            intensity_image[x][y] = other.getPixel(x, y);
        }
    }
    delete_intensity_array(t_intensity_array, old_height);
}