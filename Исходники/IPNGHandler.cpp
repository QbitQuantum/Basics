PixelBuffer* IPNGHandler::loadImage(const std::string fileName)
{
    cout << "IPNGHandler LOAD IMAGE" << endl;
    printf("IPNGHandler -> loadImage\n");
    PixelBuffer* loadedImageBuffer = NULL;

    png_image image;
    memset(&image, 0, (sizeof image));
    image.version = PNG_IMAGE_VERSION;

    if (png_image_begin_read_from_file(&image, fileName.c_str())) {

        loadedImageBuffer = new PixelBuffer(image.width, image.height, ColorData(0.0,0.0,0.0));

        png_bytep buffer;
        image.format = PNG_FORMAT_RGBA;
        buffer = new png_byte[PNG_IMAGE_SIZE(image)];

        if (buffer && png_image_finish_read(&image, NULL, buffer, 0, NULL)) {
          cout << "Finished buffer read" << endl;
            for (int y = 0; y < image.height; y++) {
                for (int x = 0; x < image.width; x++) {
                    int r, g, b, a = 0;
                    r = (int)buffer[(y*image.width*4)+(x*4)];
                    g = (int)buffer[(y*image.width*4)+(x*4)+1];
                    b = (int)buffer[(y*image.width*4)+(x*4)+2];
                    a = (int)buffer[(y*image.width*4)+(x*4)+3];
                    loadedImageBuffer->setPixel(x, image.height-(y+1), ColorData(r/255.0f,g/255.0f,b/255.0f,a/255.0f));
                }
            }

        }

        delete[] buffer;
    }
    cout << "returning loaded image buffer" << endl;
    return loadedImageBuffer;
}