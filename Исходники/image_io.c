/*
 * read_bitmap: Read in bitmap image data from .bmp file.
 *
 * Parameters:
 *  - filename: string name of bitmap file to be read
 *
 * Return value:
 *  - byte vector of bitmap data
 */
vector_t read_bitmap(char *filename)
{
#ifdef IMAGE_IO_DBG
    printf("In read_bitmap, filename: %s\n", filename);
#endif
    char *mode = FILE_MODE;

    /* Read in the bitmap file */
    FILE *image = Fopen(filename, mode);

    /* Extract header bytes */
    uint8_t header[BMP_HEADER_SIZE];
    Fread(header, sizeof(uint8_t), BMP_HEADER_SIZE, image);
   
#ifdef IMAGE_IO_DBG
    printf("Bitmap header: \n");
    for (int i = 0; i < BMP_HEADER_SIZE; i++) {
        printf("%x ", header[i]);
    }
    printf("\n");
#endif
   
    /* Extract width, height from header */
    uint32_t height = read_word_le(header, HEIGHT_OFFSET);
    uint32_t width = read_word_le(header, WIDTH_OFFSET);
    uint32_t num_pix = height * width;
    uint32_t num_bytes = num_pix * NUM_BYTES_IN_PIX;

#ifdef IMAGE_IO_DBG
    printf("Height: %d\n", height);
    printf("Width: %d\n", width);
    printf("Number of pixels: %d\n", num_pix);
    printf("Number of bytes in image: %d\n", num_bytes);
#endif

    /* Read the image data */
    uint8_t *image_data = (uint8_t*) Calloc(num_bytes, sizeof(uint8_t)); 
    uint32_t actual_size;
    if ((actual_size = fread(image_data, 1, num_bytes, image)) < num_bytes) {
#ifdef IMAGE_IO_DBG
        printf("Error: Couldn't read image data, actual_size: %d\n", actual_size);
#endif
        Free(image_data);
        Fclose(image);
        return NULL;
    }

#ifdef IMAGE_IO_DBG
    printf("DATA: \n[ ");
    for (uint32_t i = 0; i < num_bytes; i++) {
        printf("%x ", image_data[i]);
    }
    printf("]\n");
#endif

    uint8_t *reduced_image = (uint8_t*) Calloc(num_bytes / NUM_BYTES_IN_PIX, sizeof(uint8_t)); 
    uint32_t reduced_count = 0;
    for (uint32_t i = 0; i < num_bytes; i++) {
        if (i % NUM_BYTES_IN_PIX == 0) {
            reduced_image[reduced_count] = image_data[i];
            reduced_count++;
        } 
    }

#ifdef IMAGE_IO_DBG
    printf("REDUCED DATA: \n[ ");
    for (uint32_t i = 0; i < num_bytes / NUM_BYTES_IN_PIX; i++) {
        printf("%x ", reduced_image[i]);
    }
    printf("]\n");
#endif
    
    vector_t vec = Vector((size_t) (num_bytes / NUM_BYTES_IN_PIX));
    uint32_t *vector_data = (uint32_t*) Calloc(num_bytes / NUM_BYTES_IN_PIX, 
                                              sizeof(uint32_t));
    /* Copy over image data into vectro data and set the vector's data */
    for (uint32_t i = 0; i < num_bytes / NUM_BYTES_IN_PIX; i++) {
        vector_data[i] = (uint32_t) reduced_image[i];
    }
    assert(vec);
    vec->data = vector_data;
    
#ifdef IMAGE_IO_DBG
    printf("VECTOR DATA: Length: %zu\n[ ", vec->length);
    assert(vec->data);
    for (uint32_t i = 0; i < num_bytes / NUM_BYTES_IN_PIX; i++) {
        printf("%x ", vec->data[i]);
    }
    printf("]\n");
#endif

    Fclose(image);
    Free(image_data); 
    Free(reduced_image); 
    return vec;
}