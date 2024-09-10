static pngquant_error write_image(png8_image *output_image, png24_image *output_image24, const char *outname, struct pngquant_options *options)
{
    FILE *outfile;
    char *tempname = NULL;

    if (options->using_stdout) {
        set_binary_mode(stdout);
        outfile = stdout;

        if (output_image) {
            verbose_printf(options, "  writing %d-color image to stdout", output_image->num_palette);
        } else {
            verbose_printf(options, "  writing truecolor image to stdout");
        }
    } else {
        tempname = temp_filename(outname);
        if (!tempname) return OUT_OF_MEMORY_ERROR;

        if ((outfile = fopen(tempname, "wb")) == NULL) {
            fprintf(stderr, "  error: cannot open '%s' for writing\n", tempname);
            free(tempname);
            return CANT_WRITE_ERROR;
        }

        if (output_image) {
            verbose_printf(options, "  writing %d-color image as %s", output_image->num_palette, filename_part(outname));
        } else {
            verbose_printf(options, "  writing truecolor image as %s", filename_part(outname));
        }
    }

    pngquant_error retval;
    #pragma omp critical (libpng)
    {
        if (output_image) {
            retval = rwpng_write_image8(outfile, output_image);
        } else {
            retval = rwpng_write_image24(outfile, output_image24);
        }
    }

    if (!options->using_stdout) {
        fclose(outfile);

        if (SUCCESS == retval) {
            // Image has been written to a temporary file and then moved over destination.
            // This makes replacement atomic and avoids damaging destination file on write error.
            if (!replace_file(tempname, outname, options->force)) {
                retval = CANT_WRITE_ERROR;
            }
        }

        if (retval) {
            unlink(tempname);
        }
        free(tempname);
    }

    if (retval && retval != TOO_LARGE_FILE) {
        fprintf(stderr, "  error: failed writing image to %s\n", outname);
    }

    return retval;
}