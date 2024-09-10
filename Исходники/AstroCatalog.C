/*
 * Given a URL pointing to preview data (FITS image or tab table data),
 * request the data from the server and return 0 if all is OK.  On
 * return, if there were no errors, the "ctype" argument is set to the
 * Content-type of the result to indicate the type of data. The data is
 * automatically decompressed if needed (if the content-type is
 * recognized).  The "tmpfile()" method gives the name of the file
 * containing the results on success.
 */
int AstroCatalog::getPreview(const char* url, char*& ctype)
{
    // we need to use a new file, since the old one may be still in use
    // (even after it was deleted, since it may still be open and/or mmapped)
    newTempFile();

    // open the tmp file
    std::ofstream f(tmpfile_);
    if (!f)
        return sys_error("could not open file for writing: ", tmpfile_);

    if (http_.get(url, f) != 0) {
        unlink(tmpfile_);
        return ERROR;
    }
    f.close();

    // check the Content-type of the return data to determine whether it
    // needs to be decompressed and if so, how...
    ctype = http_.content_type();
    if (!ctype)
        ctype = (char *)"";

    if (strcmp(ctype, "text/html") == 0) {
        // most likely an HTML formatted server error message
        std::ifstream is(tmpfile_);
        unlink(tmpfile_);
        return http_.html_error(is);
    }

    // for now, assume uncompressed table if the Content-type is not recognized
    char* t = ctype;
    int is_image = 0;
    if (strncmp(ctype, "image/", 6) == 0) {
        t = ctype+6;
        is_image++;
    }
    else if (strncmp(ctype, "text/", 5) == 0) {
        t = ctype+5;
    }
    else {
        // unknown content type, check if it might be a FITS file
        Mem m(tmpfile_);
        if (m.status() == 0
                && m.size() >= 2880
                && strncmp((const char*)m.ptr(), "SIMPLE", 6) == 0) {
            ctype = (char *)"image/x-fits";   // assume FITS file
            is_image++;
        } else {
            ctype = (char *)"text/x-starbase"; // assume catalog data
        }
        return 0;
    }

    // In some cases the Content-type only gives the general type and
    // we need to check the Content-Encoding also. For example "file.fits.gz"
    // might have a Content-type of image/x-fits and Content-Encoding of
    // x-gzip
    char* ce = http_.content_encoding();
    if (is_image && strcmp(t, "x-fits") == 0 && ce != NULL) {
        if (strcmp(ce, "x-gzip") == 0) {
            ctype = (char *)"image/x-gfits";
            t = ctype+6;
        }
        else if (strcmp(ce, "x-compress") == 0) {
            ctype = (char *)"image/x-cfits";
            t = ctype+6;
        }
    }

    // pure FITS or starbase table ?
    if (strcmp(t, "x-fits") == 0
            || strcmp(t, "fits" ) == 0
            || strcmp(t, "fits") == 0
            || strcmp(t, "x-starbase") == 0
            || strcmp(t, "plain") == 0
            || strcmp(t, "tab-separated-values") == 0) {
        return 0;	// not compressed, just return filename
    }

    Compress::CompressType type = Compress::NO_COMPRESS;
    if (strcmp(t, "x-hfits") == 0) {
        type = Compress::H_COMPRESS; // Hcompressed FITS file
    }
    else if (strcmp(t, "x-gfits") == 0 || strcmp(t, "x-gstarbase") == 0) {
        type = Compress::GZIP_COMPRESS; // GZIPed FITS or tab table
    }
    else if (strcmp(t, "x-cfits") == 0 || strcmp(t, "x-cstarbase") == 0) {
        type = Compress::UNIX_COMPRESS; // UNIX Compressed FITS ir tab table
    }
    else if (strcmp(t, "x-sfits") == 0) { // Compressed FITS file (Stark)
        // type = Compress::S_COMPRESS;
        unlink(tmpfile_);
        return error("x-sfits compression (Stark) not supported");
    }
    else {
        unlink(tmpfile_);
        return error("unknown preview data Content-type: ", ctype);
    }

    // do the decompression
    FILE* feedback = http_.feedback();
    if (feedback) {
        fprintf(feedback, "decompressing data...\n");
        fflush(feedback);
    }

    Compress c;
    if (c.decompress(tmpfile_, type) != 0) {
        unlink(tmpfile_);
        return ERROR;
    }

    // correct Content-type after decompression
    ctype = (char*)(is_image ? "image/x-fits" : "text/x-starbase");

    // if we got here, then we have the FITS file, so return the file name
    return 0;
}