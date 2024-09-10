// Analysis_Wavelet::Analyze()
Analysis::RetType Analysis_Wavelet::Analyze() {
    // Step 1 - Create a matrix that is #atoms rows by #frames - 1 cols,
    //          where matrix(frame, atom) is the distance that atom has
    //          travelled from the previous frame.
    // TODO: Implement this in Action_Matrix()?
    mprintf("    WAVELET:\n");
    // First set up atom mask.
    if (coords_->Top().SetupIntegerMask( mask_ )) return Analysis::ERR;
    mask_.MaskInfo();
    int natoms = mask_.Nselected();
    int nframes = (int)coords_->Size();
    if (natoms < 1 || nframes < 2) {
        mprinterr("Error: Not enough frames (%i) or atoms (%i) in '%s'\n",
                  nframes, natoms, coords_->legend());
        return Analysis::ERR;
    }
    Matrix<double> d_matrix;
    mprintf("\t%i frames, %i atoms, distance matrix will require %.2f MB\n",
            (double)d_matrix.sizeInBytes(nframes, natoms) / (1024.0*1024.0));
    d_matrix.resize(nframes, natoms);
    // Get initial frame.
    Frame currentFrame, lastFrame;
    currentFrame.SetupFrameFromMask( mask_, coords_->Top().Atoms() );
    lastFrame = currentFrame;
    coords_->GetFrame( 0, lastFrame, mask_ );
    // Iterate over frames
    for (int frm = 1; frm != nframes; frm++) {
        coords_->GetFrame( frm, currentFrame, mask_ );
        int idx = frm; // Position in distance matrix; start at column 'frame'
        for (int at = 0; at != natoms; at++, idx += nframes)
            // Distance of atom in currentFrame from its position in lastFrame.
            d_matrix[idx] = sqrt(DIST2_NoImage( currentFrame.XYZ(at), lastFrame.XYZ(at) ));
        //lastFrame = currentFrame; // TODO: Re-enable?
    }
# ifdef DEBUG_WAVELET
    // DEBUG: Write matrix to file.
    CpptrajFile dmatrixOut; // DEBUG
    dmatrixOut.OpenWrite("dmatrix.dat");
    Matrix<double>::iterator mval = d_matrix.begin();
    for (int row = 0; row != natoms; row++) {
        for (int col = 0; col != nframes; col++)
            dmatrixOut.Printf("%g ", *(mval++));
        dmatrixOut.Printf("\n");
    }
    dmatrixOut.CloseFile();
# endif

    // Precompute some factors for calculating scaled wavelets.
    const double one_over_sqrt_N = 1.0 / sqrt(static_cast<double>( nframes ));
    std::vector<int> arrayK( nframes );
    arrayK[0] = -1 * (nframes/2);
    for (int i = 1; i != nframes; i++)
        arrayK[i] = arrayK[i-1] + 1;
# ifdef DEBUG_WAVELET
    mprintf("DEBUG: K:");
    for (std::vector<int>::const_iterator kval = arrayK.begin(); kval != arrayK.end(); ++kval)
        mprintf(" %i", *kval);
    mprintf("\n");
# endif

    // Step 2 - Get FFT of wavelet for each scale.
    PubFFT pubfft;
    pubfft.SetupFFTforN( nframes );
    mprintf("\tMemory required for scaled wavelet array: %.2f MB\n",
            (double)(2 * nframes * nb_ * sizeof(double)) / (1024 * 1024));
    typedef std::vector<ComplexArray> WaveletArray;
    WaveletArray FFT_of_Scaled_Wavelets;
    FFT_of_Scaled_Wavelets.reserve( nb_ );
    typedef std::vector<double> Darray;
    Darray scaleVector;
    scaleVector.reserve( nb_ );
    Darray MIN( nb_ * 2 );
    for (int iscale = 0; iscale != nb_; iscale++)
    {
        // Calculate and store scale factor.
        scaleVector.push_back( S0_ * pow(2.0, iscale * ds_) );
        // Populate MIN array
        MIN[iscale    ] = (0.00647*pow((correction_*scaleVector.back()),1.41344)+19.7527)*chival_;
        MIN[iscale+nb_] = correction_*scaleVector.back();
        // Calculate scalved wavelet
        ComplexArray scaledWavelet;
        switch (wavelet_type_) {
        case W_MORLET:
            scaledWavelet = F_Morlet(arrayK, scaleVector.back());
            break;
        case W_PAUL  :
            scaledWavelet = F_Paul(arrayK, scaleVector.back());
            break;
        case W_NONE  :
            return Analysis::ERR; // Sanity check
        }
#   ifdef DEBUG_WAVELET
        PrintComplex("wavelet_before_fft", scaledWavelet);
#   endif
        // Perform FFT
        pubfft.Forward( scaledWavelet );
        // Normalize
        scaledWavelet.Normalize( one_over_sqrt_N );
#   ifdef DEBUG_WAVELET
        PrintComplex("wavelet_after_fft", scaledWavelet);
#   endif
        FFT_of_Scaled_Wavelets.push_back( scaledWavelet );
    }
# ifdef DEBUG_WAVELET
    mprintf("DEBUG: Scaling factors:");
    for (Darray::const_iterator sval = scaleVector.begin(); sval != scaleVector.end(); ++sval)
        mprintf(" %g", *sval);
    mprintf("\n");
    mprintf("DEBUG: MIN:");
    for (int i = 0; i != nb_; i++)
        mprintf(" %g", MIN[i]);
    mprintf("\n");
# endif

    // Step 3 - For each atom, calculate the convolution of scaled wavelets
    //          with rows (atom distance vs frame) via dot product of the
    //          frequency domains, i.e. Fourier-transformed, followed by an
    //          inverse FT.
    DataSet_MatrixFlt& OUT = static_cast<DataSet_MatrixFlt&>( *output_ );
    mprintf("\tMemory required for output matrix: %.2f MB\n",
            (double)Matrix<float>::sizeInBytes(nframes, natoms)/(1024.0*1024.0));
    OUT.Allocate2D( nframes, natoms ); // Should initialize to zero
    Matrix<double> MAX;
    mprintf("\tMemory required for Max array: %.2f MB\n",
            (double)MAX.sizeInBytes(nframes, natoms)/(1024.0*1024.0));
    MAX.resize( nframes, natoms );
    Darray magnitude( nframes ); // Scratch space for calculating magnitude across rows
    for (int at = 0; at != natoms; at++) {
        ComplexArray AtomSignal( nframes ); // Initializes to zero
        // Calculate the distance variance for this atom and populate the array.
        int midx = at * nframes; // Index into d_matrix
        int cidx = 0;            // Index into AtomSignal
        double d_avg = 0.0;
        double d_var = 0.0;
        for (int frm = 0; frm != nframes; frm++, cidx += 2, midx++) {
            d_avg += d_matrix[midx];
            d_var += (d_matrix[midx] * d_matrix[midx]);
            AtomSignal[cidx] = d_matrix[midx];
        }
        d_var = (d_var - ((d_avg * d_avg) / (double)nframes)) / ((double)(nframes - 1));
#   ifdef DEBUG_WAVELET
        mprintf("VARIANCE: %g\n", d_var);
#   endif
        double var_norm = 1.0 / d_var;
        // Calculate FT of atom signal
        pubfft.Forward( AtomSignal );
#   ifdef DEBUG_WAVELET
        PrintComplex("AtomSignal", AtomSignal);
#   endif
        // Normalize
        AtomSignal.Normalize( one_over_sqrt_N );
        // Calculate dot product of atom signal with each scaled FT wavelet
        for (int iscale = 0; iscale != nb_; iscale++) {
            ComplexArray dot = AtomSignal.TimesComplexConj( FFT_of_Scaled_Wavelets[iscale] );
            // Inverse FT of dot product
            pubfft.Back( dot );
#     ifdef DEBUG_WAVELET
            PrintComplex("InverseFT_Dot", dot);
#     endif
            // Chi-squared testing
            midx = at * nframes;
            cidx = 0;
            for (int frm = 0; frm != nframes; frm++, cidx += 2, midx++) {
                magnitude[frm] = (dot[cidx]*dot[cidx] + dot[cidx+1]*dot[cidx+1]) * var_norm;
                if (magnitude[frm] < MIN[iscale])
                    magnitude[frm] = 0.0;
                if (magnitude[frm] > MAX[midx]) {
                    MAX[midx] = magnitude[frm];
                    //Indices[midx] = iscale
                    OUT[midx] = (float)(correction_ * scaleVector[iscale]);
                }
            }
#     ifdef DEBUG_WAVELET
            mprintf("DEBUG: AbsoluteValue:");
            for (Darray::const_iterator dval = magnitude.begin(); dval != magnitude.end(); ++dval)
                mprintf(" %g", *dval);
            mprintf("\n");
#     endif
        } // END loop over scales
    } // END loop over atoms
# ifdef DEBUG_WAVELET
    // DEBUG: Print MAX
    CpptrajFile maxmatrixOut; // DEBUG
    maxmatrixOut.OpenWrite("maxmatrix.dat");
    for (int col = 0; col != nframes; col++) {
        for (int row = 0; row != natoms; row++)
            maxmatrixOut.Printf("%g ", MAX.element(col, row));
        maxmatrixOut.Printf("\n");
    }
    maxmatrixOut.CloseFile();
# endif

    return Analysis::OK;
}