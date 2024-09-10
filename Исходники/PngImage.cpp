    PngImage::PngImage(const char *file_name) {
        png_image_t *png_image = new png_image_t();
        ImageLoader::LoadPNGImage(file_name, png_image);

        this->bitDepth = png_image->bit_depth;
        this->colorType = png_image->color_type;

        CreateBitMap(png_image->row_pointers, png_image->width, png_image->height);
    }