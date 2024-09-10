struct Image *kodak_dc2x_get_picture (int picNum, int thumbnail) {

    int tfd, image_size, image_width, net_width, camera_header, components;
    Dc20Info *my_info;
    unsigned char color_thumb[14400];
    unsigned char pic[MAX_IMAGE_SIZE];
    struct pixmap	*pp;

    GdkImlibImage *this_image, *scaled_image;
    GdkImlibColorModifier mod;

    FILE *jpgfile;
    int jpgfile_size;
    char filename[1024];
    struct Image *im;

    if ((tfd = kodak_dc2x_open_camera()) == 0) {
        error_dialog("Could not open camera.");
        return (0);
    }

    my_info = get_info(tfd);

    fprintf(stderr, "downloading from a DC%x\n", my_info->model);

    if (my_info->model == 0x25) {
        fprintf(stderr, "Match with 25!\n");
        if (thumbnail) {
            fprintf(stderr, "Getting thumbnail #%d from a DC25!\n", picNum);
            if (get_thumb(tfd, picNum, color_thumb) == -1) {
                fprintf(stderr,"get_thumb failed!\n");
                return(0);
            } else {
                fprintf(stderr,"get_thumb returned ok! Creating ImLib image!\n");
                this_image = gdk_imlib_create_image_from_data(color_thumb, NULL, 80, 60);
                fprintf(stderr, "Made it back from imlib_create!\n");
                sprintf(filename, "%s/gphoto-kodak-%i.jpg", gphotoDir, picNum);
                gdk_imlib_save_image (this_image, filename, NULL);
                gdk_imlib_kill_image (this_image);
                jpgfile = fopen(filename, "r");
                fseek(jpgfile, 0, SEEK_END);
                jpgfile_size = ftell(jpgfile);
                rewind(jpgfile);
                im = (struct Image*)malloc(sizeof(struct Image));
                im->image = (char *)malloc(sizeof(char)*jpgfile_size);
                fread(im->image, (size_t)sizeof(char), (size_t)jpgfile_size, jpgfile);
                fclose(jpgfile);
                strcpy(im->image_type, "jpg");
                im->image_size = (int)jpgfile_size;
                im->image_info_size = 0;
                remove(filename);
                return (im);
            }
        } else {
            fprintf(stderr, "Getting picture #%d from a DC25!\n", picNum );
            if (get_pic(tfd, picNum, pic, 0) == -1) {
                fprintf(stderr, "get_pic puked!\n");
                return(0);
            } else {
                fprintf(stderr, "returned from get_pic ok!\n");

                /*
                 *	Setup image size with resolution
                 */

                image_size = IMAGE_SIZE(pic[4]);
                image_width = WIDTH(pic[4]);
                net_width = image_width - LEFT_MARGIN - RIGHT_MARGIN(pic[4]);
                camera_header = CAMERA_HEADER(pic[4]);
                components = 3;

                /*
                 *	Convert the image to 24 bits
                 */

                if ((pp = alloc_pixmap(net_width - 1, HEIGHT - BOTTOM_MARGIN - 1, components)) == NULL) {
                    if (!quiet) fprintf(stderr, "%s: convert_pic: error: alloc_pixmap\n", __progname);
                    return 0;
                }

                if (comet_to_pixmap(pic, pp) == -1) {
                    fprintf(stderr, "comet_to_pixmap puked!\n");
                    return (0);
                } else {

                    fprintf(stderr, "attempting to imlib_create the image!\n");
                    this_image = gdk_imlib_create_image_from_data(pp->planes, NULL, pp->width, pp->height);
                    fprintf(stderr, "Made it back from imlib_create!\n");

                    /* now we just need to resize it! */
                    if (!pic[4]) {
                        /* high res 493x373 */
                        fprintf(stderr, "High Res!\n");
                        scaled_image = gdk_imlib_clone_scaled_image(this_image, 493, 373);

                    } else {
                        /* low res 320x240 */
                        fprintf(stderr, "Low Res!\n");
                        scaled_image = gdk_imlib_clone_scaled_image(this_image, 320, 240);

                        /* How? */
                    }

                    gdk_imlib_kill_image(this_image);

                    /* correct the contrast a bit before handing it back.. */
                    gdk_imlib_get_image_modifier(scaled_image,&mod);
                    mod.contrast = 256 * 1.3;
                    gdk_imlib_set_image_modifier(scaled_image,&mod);
                    gdk_imlib_apply_modifiers_to_rgb(scaled_image);

                    kodak_dc2x_close_camera(tfd);

                    sprintf(filename, "%s/gphoto-kodak-%i.jpg", gphotoDir, picNum);
                    gdk_imlib_save_image (scaled_image, filename, NULL);
                    gdk_imlib_kill_image (scaled_image);
                    jpgfile = fopen(filename, "r");
                    fseek(jpgfile, 0, SEEK_END);
                    jpgfile_size = ftell(jpgfile);
                    rewind(jpgfile);
                    im = (struct Image*)malloc(sizeof(struct Image));
                    im->image = (char *)malloc(sizeof(char)*jpgfile_size);
                    fread(im->image,(size_t)sizeof(char),(size_t)jpgfile_size,jpgfile);
                    fclose(jpgfile);
                    strcpy(im->image_type, "jpg");
                    im->image_size = jpgfile_size;
                    im->image_info_size = 0;
                    remove(filename);

                    return (im);
                }

            }
        }
    } else {
        fprintf(stderr, "No match with 25!");
        return(0);
    }
    return(0);
}