void getImage() {
image = (Image *) malloc(sizeof(Image));
if (image == NULL) {
printf("Error allocating space for the image");
exit(-1);
}
if (!ImageLoad(filename, image)) {
exit(-2);
printf("Image loading successful\n\n");
}    /*******************************************/
//get image data
/*******************************************/
}