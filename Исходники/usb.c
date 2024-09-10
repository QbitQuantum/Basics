bool usb_restore(FILE *image) {
    return fread(&usb, sizeof(usb), 1, image) == 1;
}