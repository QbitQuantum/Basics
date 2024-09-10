Image * loadTexture(){
    Image *image1;
    image1 = (Image *) malloc(sizeof(Image));
    if (!ImageLoad("asd.bmp", image1)) {
        exit(1);
    }     
    return image1;
}