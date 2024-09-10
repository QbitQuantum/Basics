int get_PSRFITS_rawblock(float *fdata, struct spectra_info *s, int *padding)
// This routine reads a single block (i.e subint) from the input files
// which contain raw data in PSRFITS format.  If padding is
// returned as 1, then padding was added and statistics should not be
// calculated.  Return 1 on success.
{
    int numtopad = 0, numtoread, status = 0, anynull;
    float *fdataptr = fdata;

    fdataptr = fdata + numbuffered * s->num_channels;
    // numtoread is always this size since we need to read
    // full PSRFITS subints...
    numtoread = s->spectra_per_subint;

    // If our buffer array is offset from last time,
    // copy the previously offset part into the beginning.
    // New data comes after the old data in the buffer.
    if (numbuffered)
        memcpy((char *) fdata, (char *) (fdata + numtoread * s->num_channels),
               numbuffered * s->num_channels * sizeof(float));

    // Make sure our current file number is valid
    if (cur_file >= s->num_files)
        return 0;

    // Read a subint of data from the DATA col
    if (cur_subint <= s->num_subint[cur_file]) {
        double offs_sub = 0.0;
        if (!offs_sub_are_zero) {
            // Read the OFFS_SUB column value in case there were dropped blocks
            fits_read_col(s->fitsfiles[cur_file], TDOUBLE,
                          s->offs_sub_col, cur_subint, 1L, 1L,
                          0, &offs_sub, &anynull, &status);
            // Set new_spec to proper value, accounting for possibly
            // missing initial rows of data and/or combining observations
            // Note: need to remove start_subint because that was already put
            // into start_spec.  This is important if initial rows are gone.
            new_spec = s->start_spec[cur_file] +
                roundl((offs_sub - (s->start_subint[cur_file] + 0.5)
                        * s->time_per_subint) / s->dt);
        } else {
            new_spec = s->start_spec[cur_file] +
                (cur_subint - 1) * s->spectra_per_subint;
        }

        //printf("cur/new_spec = %lld, %lld  s->start_spec[cur_file] = %lld\n",
        //       cur_spec, new_spec, s->start_spec[cur_file]);

        // The following determines if there were lost blocks, or if
        // we are putting different observations together so that
        // the blocks are not aligned
        if (new_spec == cur_spec + numbuffered) {
            // if things look good, with no missing blocks, read the data
            get_PSRFITS_subint(fdataptr, cdatabuffer, s);
            cur_subint++;
            goto return_block;
        } else {
            goto padding_block;
        }
    } else {
        // We are going to move to the next file, so update
        // new_spec to be the starting spectra from the next file
        // so we can see if any padding is necessary
        if (cur_file < s->num_files - 1)
            new_spec = s->start_spec[cur_file + 1];
        else
            new_spec = cur_spec + numbuffered;
    }

    if (new_spec == cur_spec + numbuffered) {
        // No padding is necessary, so switch files
        cur_file++;
        cur_subint = 1;
        return get_PSRFITS_rawblock(fdata, s, padding);
    } else {                    // add padding
        goto padding_block;
    }

  padding_block:
    if (new_spec < cur_spec) {
        // Files out of order?  Shouldn't get here.
        fprintf(stderr, "Error!:  Current subint has earlier time than previous!\n\n"
                "\tfilename = '%s', subint = %d\n"
                "\tcur_spec = %lld  new_spec = %lld\n",
                s->filenames[cur_file], cur_subint, cur_spec, new_spec);
        exit(1);
    }
    numtopad = new_spec - cur_spec;
    // Don't add more than 1 block and if buffered, then realign the buffer
    if (numtopad > (s->spectra_per_subint - numbuffered))
        numtopad = s->spectra_per_subint - numbuffered;
    add_padding(fdataptr, s->padvals, s->num_channels, numtopad);
    // Update pointer into the buffer
    numbuffered = (numbuffered + numtopad) % s->spectra_per_subint;
    // Set the padding flag
    *padding = 1;
    // If we haven't gotten a full block, or completed the buffered one
    // then recursively call get_PSRFITS_rawblock()
    if (numbuffered) {
        printf("Adding %d spectra of padding to buffer at subint %d\n",
               numtopad, cur_subint);
        return get_PSRFITS_rawblock(fdata, s, padding);
    } else {
        printf("Adding %d spectra of padding at subint %d\n", numtopad, cur_subint);
        goto return_block;
    }

  return_block:
    // Apply the corrections that need a full block

    // Invert the band if needed
    if (s->apply_flipband)
        flip_band(fdata, s);

    // Perform Zero-DMing if requested
    if (s->remove_zerodm)
        remove_zerodm(fdata, s);

    // Increment our static counter (to determine how much data we
    // have written on the fly).
    cur_spec += s->spectra_per_subint;

    return 1;
}