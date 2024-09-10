int main(int argc, char ** argv) {
    uid_t uid = geteuid();

    if ( argv[1] == NULL || argv[2] == NULL ) {
        fprintf(stderr, "USAGE: %s [attach/detach] [image/loop]\n", argv[0]);
        return(1);
    }

    message(VERBOSE, "Checking calling user\n");
    if ( uid != 0 ) {
        message(ERROR, "Calling user must be root\n");
        ABORT(1);
    }

    message(VERBOSE, "Checking command: %s\n", argv[1]);
    if ( strcmp(argv[1], "attach") == 0 ) {
        FILE *containerimage_fp;
        char *containerimage;
        char *loop_dev;

        message(VERBOSE, "Preparing to attach container to loop\n");

        containerimage = xstrdup(argv[2]);

        message(VERBOSE, "Evaluating image: %s\n", containerimage);
    
        message(VERBOSE, "Checking if container image exists\n");
        if ( is_file(containerimage) < 0 ) {
            message(ERROR, "Container image not found: %s\n", containerimage);
            ABORT(1);
        }

        message(VERBOSE, "Checking if container can be opened read/write\n");
        if ( !( containerimage_fp = fopen(containerimage, "r+") ) ) { // Flawfinder: ignore
            message(ERROR, "Could not open image %s: %s\n", containerimage, strerror(errno));
            ABORT(255);
        }

        message(DEBUG, "Binding container to loop interface\n");
        if ( loop_bind(containerimage_fp, &loop_dev, 0) < 0 ) {
            message(ERROR, "Could not bind image to loop!\n");
            ABORT(255);
        }

        printf("%s\n", loop_dev);
    } else if (strcmp(argv[1], "detach") == 0 ) {
        char *loop_dev;

        loop_dev = xstrdup(argv[2]);

        message(VERBOSE, "Preparing to detach loop: %s\n", loop_dev);

        message(VERBOSE, "Checking loop device\n");
        if ( is_blk(loop_dev) < 0 ) {
            message(ERROR, "Block device not found: %s\n", loop_dev);
            ABORT(255);
        }

        message(VERBOSE, "Unbinding container image from loop\n");
        if ( loop_free(loop_dev) < 0 ) {
            message(ERROR, "Failed to detach loop device: %s\n", loop_dev);
            ABORT(255);
        }

    }

    return(0);
}