/*
 * read_images: Reads the images from and mnist image db file and puts the
 *              images into and array of vectors.
 *
 * Parameters:
 *  - train: boolean value, read from training db if 0, test db if 1
 *
 * Return value:
 *  - array of vectors containing mnist images
 */ 
mnist_images_t read_images(uint32_t train)
{
    // Set the filename based the mode (train or test)
    char *full_path;
    if (train) {
        full_path = concat_fname(mnist_path, train_image_fname);
    } else {
        full_path = concat_fname(mnist_path, test_image_fname);
    }

    // Open the file for reading
    char *mode = FILE_MODE;
    FILE *fp = Fopen(full_path, mode); 

    // Read the header of the file
    uint8_t header[IMAGE_HEADER_SIZE];
    Fread(header, sizeof(uint8_t), IMAGE_HEADER_SIZE, fp);

    // Extract size info from mnist db header
    uint32_t num_images = read_word(header, NUM_ITEMS_OFFSET);
    uint32_t rows = read_word(header, ROW_OFFSET);
    uint32_t cols = read_word(header, COL_OFFSET);
    uint32_t img_size = rows * cols;

    // Create array of mnist image vectors
    vector_t *mnist_data = (vector_t*) Calloc(num_images, sizeof(vector_t));
    
    // Populate vectors with one image each
    for (uint32_t i = 0; i < num_images; i++) {
        mnist_data[i] = Vector((size_t) img_size);

        uint8_t *image_bytes = (uint8_t*) Calloc(img_size, sizeof(uint8_t));
        uint32_t actual_size;
        // Read img_size bytes from the db file into the byte array
        if ((actual_size = fread(image_bytes, sizeof(uint8_t), img_size, fp)) < img_size) {
            Free(image_bytes);
            for (uint32_t i = 0; i < num_images; i++) vector_destroy(mnist_data[i]);
            return NULL;
        }

        // Move 8 bit data to 32 bit integer for more precision
        uint32_t *vector_data = (uint32_t*) Calloc(img_size, sizeof(uint32_t));
        for (uint32_t j = 0; j < img_size; j++) {
            vector_data[j] = (uint32_t) image_bytes[j];
        }
        mnist_data[i]->data = vector_data;
        Free(image_bytes);
    }

    // Create the mnist_images_t pointer and populate the struct it points to
    mnist_images_t mnist_imgs = Mnist_images((size_t) num_images); 
    mnist_imgs->imgs = mnist_data;

    Free(full_path);
    Fclose(fp);
    return mnist_imgs;
}