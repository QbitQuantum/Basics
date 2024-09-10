//==========================================================================
void PrecPrecomputed::compute() {
  using Teuchos::Array;
  using Teuchos::ArrayRCP;
  using Teuchos::ArrayView;
  using Teuchos::as;
  using Teuchos::rcp;
  using Teuchos::reduceAll;

  //--------------------------------------------------------------------------
  // Ifpack2::ILUT is a translation of the Aztec ILUT implementation. The Aztec
  // ILUT implementation was written by Ray Tuminaro.
  //
  // This isn't an exact translation of the Aztec ILUT algorithm, for the
  // following reasons:
  // 1. Minor differences result from the fact that Aztec factors a MSR format
  // matrix in place, while the code below factors an input CrsMatrix which
  // remains untouched and stores the resulting factors in separate L and U
  // CrsMatrix objects.
  // Also, the Aztec code begins by shifting the matrix pointers back
  // by one, and the pointer contents back by one, and then using 1-based
  // Fortran-style indexing in the algorithm. This Ifpack2 code uses C-style
  // 0-based indexing throughout.
  // 2. Aztec stores the inverse of the diagonal of U. This Ifpack2 code
  // stores the non-inverted diagonal in U.
  // The triangular solves (in Ifpack2::ILUT::apply()) are performed by
  // calling the Tpetra::CrsMatrix::solve method on the L and U objects, and
  // this requires U to contain the non-inverted diagonal.
  //
  // ABW.
  //--------------------------------------------------------------------------

  // Don't count initialization in the compute() time.
  if (! isInitialized ()) {
    initialize ();
  }

  Teuchos::Time timer ("ILUT::compute");
  { // Timer scope for timing compute()
    Teuchos::TimeMonitor timeMon (timer, true);
    /*
    const scalar_type zero = STS::zero ();
    const scalar_type one  = STS::one ();

    const local_ordinal_type myNumRows = A_->getNodeNumRows ();
    L_ = rcp (new MatrixType (A_->getRowMap (), A_->getColMap (), 0));
    U_ = rcp (new MatrixType (A_->getRowMap (), A_->getColMap (), 0));

    // CGB: note, this caching approach may not be necessary anymore
    // We will store ArrayView objects that are views of the rows of U, so that
    // we don't have to repeatedly retrieve the view for each row. These will
    // be populated row by row as the factorization proceeds.
    Array<ArrayView<const local_ordinal_type> > Uindices (myNumRows);
    Array<ArrayView<const scalar_type> >       Ucoefs (myNumRows);

    // If this macro is defined, files containing the L and U factors
    // will be written. DON'T CHECK IN THE CODE WITH THIS MACRO ENABLED!!!
    // #define IFPACK2_WRITE_FACTORS
#ifdef IFPACK2_WRITE_FACTORS
    std::ofstream ofsL("L.tif.mtx", std::ios::out);
    std::ofstream ofsU("U.tif.mtx", std::ios::out);
#endif

    // mfh 28 Nov 2012: The code here uses double for fill calculations.
    // This really has nothing to do with magnitude_type.  The point is
    // to avoid rounding and overflow for integer calculations.  That
    // should work just fine for reasonably-sized integer values, so I'm
    // leaving it.  However, the fill level parameter is a
    // magnitude_type, so I do need to cast to double.  Typical values
    // of the fill level are small, so this should not cause overflow.

    // Calculate how much fill will be allowed in addition to the space that
    // corresponds to the input matrix entries.
    double local_nnz = static_cast<double>(A_->getNodeNumEntries());
    double fill;
    {
      const double fillLevel = as<double> (getLevelOfFill ());
      fill = ((fillLevel - 1) * local_nnz) / (2 * myNumRows);
    }

    // std::ceil gives the smallest integer larger than the argument.
    // this may give a slightly different result than Aztec's fill value in
    // some cases.
    double fill_ceil=std::ceil(fill);

    // Similarly to Aztec, we will allow the same amount of fill for each
    // row, half in L and half in U.
    size_type fillL = static_cast<size_type>(fill_ceil);
    size_type fillU = static_cast<size_type>(fill_ceil);

    Array<scalar_type> InvDiagU (myNumRows, zero);

    Array<local_ordinal_type> tmp_idx;
    Array<scalar_type> tmpv;

    enum { UNUSED, ORIG, FILL };
    local_ordinal_type max_col = myNumRows;

    Array<int> pattern(max_col, UNUSED);
    Array<scalar_type> cur_row(max_col, zero);
    Array<magnitude_type> unorm(max_col);
    magnitude_type rownorm;
    Array<local_ordinal_type> L_cols_heap;
    Array<local_ordinal_type> U_cols;
    Array<local_ordinal_type> L_vals_heap;
    Array<local_ordinal_type> U_vals_heap;

    // A comparison object which will be used to create 'heaps' of indices
    // that are ordered according to the corresponding values in the
    // 'cur_row' array.
    greater_indirect<scalar_type,local_ordinal_type> vals_comp(cur_row);

    // =================== //
    // start factorization //
    // =================== //

    ArrayRCP<local_ordinal_type> ColIndicesARCP;
    ArrayRCP<scalar_type>       ColValuesARCP;
    if (! A_->supportsRowViews ()) {
      const size_t maxnz = A_->getNodeMaxNumRowEntries ();
      ColIndicesARCP.resize (maxnz);
      ColValuesARCP.resize (maxnz);
    }

    for (local_ordinal_type row_i = 0 ; row_i < myNumRows ; ++row_i) {
      ArrayView<const local_ordinal_type> ColIndicesA;
      ArrayView<const scalar_type> ColValuesA;
      size_t RowNnz;

      if (A_->supportsRowViews ()) {
        A_->getLocalRowView (row_i, ColIndicesA, ColValuesA);
        RowNnz = ColIndicesA.size ();
      }
      else {
        A_->getLocalRowCopy (row_i, ColIndicesARCP (), ColValuesARCP (), RowNnz);
        ColIndicesA = ColIndicesARCP (0, RowNnz);
        ColValuesA = ColValuesARCP (0, RowNnz);
      }

      // Always include the diagonal in the U factor. The value should get
      // set in the next loop below.
      U_cols.push_back(row_i);
      cur_row[row_i] = zero;
      pattern[row_i] = ORIG;

      size_type L_cols_heaplen = 0;
      rownorm = STM::zero ();
      for (size_t i = 0; i < RowNnz; ++i) {
        if (ColIndicesA[i] < myNumRows) {
          if (ColIndicesA[i] < row_i) {
            add_to_heap(ColIndicesA[i], L_cols_heap, L_cols_heaplen);
          }
          else if (ColIndicesA[i] > row_i) {
            U_cols.push_back(ColIndicesA[i]);
          }

          cur_row[ColIndicesA[i]] = ColValuesA[i];
          pattern[ColIndicesA[i]] = ORIG;
          rownorm += scalar_mag(ColValuesA[i]);
        }
      }

      // Alter the diagonal according to the absolute-threshold and
      // relative-threshold values. If not set, those values default
      // to zero and one respectively.
      const magnitude_type rthresh = getRelativeThreshold();
      const scalar_type& v = cur_row[row_i];
      cur_row[row_i] = as<scalar_type> (getAbsoluteThreshold() * IFPACK2_SGN(v)) + rthresh*v;

      size_type orig_U_len = U_cols.size();
      RowNnz = L_cols_heap.size() + orig_U_len;
      rownorm = getDropTolerance() * rownorm/RowNnz;

      // The following while loop corresponds to the 'L30' goto's in Aztec.
      size_type L_vals_heaplen = 0;
      while (L_cols_heaplen > 0) {
        local_ordinal_type row_k = L_cols_heap.front();

        scalar_type multiplier = cur_row[row_k] * InvDiagU[row_k];
        cur_row[row_k] = multiplier;
        magnitude_type mag_mult = scalar_mag(multiplier);
        if (mag_mult*unorm[row_k] < rownorm) {
          pattern[row_k] = UNUSED;
          rm_heap_root(L_cols_heap, L_cols_heaplen);
          continue;
        }
        if (pattern[row_k] != ORIG) {
          if (L_vals_heaplen < fillL) {
            add_to_heap(row_k, L_vals_heap, L_vals_heaplen, vals_comp);
          }
          else if (L_vals_heaplen==0 ||
                   mag_mult < scalar_mag(cur_row[L_vals_heap.front()])) {
            pattern[row_k] = UNUSED;
            rm_heap_root(L_cols_heap, L_cols_heaplen);
            continue;
          }
          else {
            pattern[L_vals_heap.front()] = UNUSED;
            rm_heap_root(L_vals_heap, L_vals_heaplen, vals_comp);
            add_to_heap(row_k, L_vals_heap, L_vals_heaplen, vals_comp);
          }
        }

        */
        /* Reduce current row */
        /*

        ArrayView<const local_ordinal_type>& ColIndicesU = Uindices[row_k];
        ArrayView<const scalar_type>& ColValuesU = Ucoefs[row_k];
        size_type ColNnzU = ColIndicesU.size();

        for(size_type j=0; j<ColNnzU; ++j) {
          if (ColIndicesU[j] > row_k) {
            scalar_type tmp = multiplier * ColValuesU[j];
            local_ordinal_type col_j = ColIndicesU[j];
            if (pattern[col_j] != UNUSED) {
              cur_row[col_j] -= tmp;
            }
            else if (scalar_mag(tmp) > rownorm) {
              cur_row[col_j] = -tmp;
              pattern[col_j] = FILL;
              if (col_j > row_i) {
                U_cols.push_back(col_j);
              }
              else {
                add_to_heap(col_j, L_cols_heap, L_cols_heaplen);
              }
            }
          }
        }

        rm_heap_root(L_cols_heap, L_cols_heaplen);
      }//end of while(L_cols_heaplen) loop


      // Put indices and values for L into arrays and then into the L_ matrix.

      //   first, the original entries from the L section of A:
      for (size_type i = 0; i < ColIndicesA.size (); ++i) {
        if (ColIndicesA[i] < row_i) {
          tmp_idx.push_back(ColIndicesA[i]);
          tmpv.push_back(cur_row[ColIndicesA[i]]);
          pattern[ColIndicesA[i]] = UNUSED;
        }
      }

      //   next, the L entries resulting from fill:
      for (size_type j = 0; j < L_vals_heaplen; ++j) {
        tmp_idx.push_back(L_vals_heap[j]);
        tmpv.push_back(cur_row[L_vals_heap[j]]);
        pattern[L_vals_heap[j]] = UNUSED;
      }

      // L has a one on the diagonal, but we don't explicitly store it.
      // If we don't store it, then the Tpetra/Kokkos kernel which performs
      // the triangular solve can assume a unit diagonal, take a short-cut
      // and perform faster.

      L_->insertLocalValues (row_i, tmp_idx (), tmpv ());
#ifdef IFPACK2_WRITE_FACTORS
      for (size_type ii = 0; ii < tmp_idx.size (); ++ii) {
        ofsL << row_i << " " << tmp_idx[ii] << " " << tmpv[ii] << std::endl;
      }
#endif

      tmp_idx.clear();
      tmpv.clear();

      // Pick out the diagonal element, store its reciprocal.
      if (cur_row[row_i] == zero) {
        std::cerr << "Ifpack2::ILUT::Compute: zero pivot encountered! Replacing with rownorm and continuing...(You may need to set the parameter 'fact: absolute threshold'.)" << std::endl;
        cur_row[row_i] = rownorm;
      }
      InvDiagU[row_i] = one / cur_row[row_i];

      // Non-inverted diagonal is stored for U:
      tmp_idx.push_back(row_i);
      tmpv.push_back(cur_row[row_i]);
      unorm[row_i] = scalar_mag(cur_row[row_i]);
      pattern[row_i] = UNUSED;

      // Now put indices and values for U into arrays and then into the U_ matrix.
      // The first entry in U_cols is the diagonal, which we just handled, so we'll
      // start our loop at j=1.

      size_type U_vals_heaplen = 0;
      for(size_type j=1; j<U_cols.size(); ++j) {
        local_ordinal_type col = U_cols[j];
        if (pattern[col] != ORIG) {
          if (U_vals_heaplen < fillU) {
            add_to_heap(col, U_vals_heap, U_vals_heaplen, vals_comp);
          }
          else if (U_vals_heaplen!=0 && scalar_mag(cur_row[col]) >
                   scalar_mag(cur_row[U_vals_heap.front()])) {
            rm_heap_root(U_vals_heap, U_vals_heaplen, vals_comp);
            add_to_heap(col, U_vals_heap, U_vals_heaplen, vals_comp);
          }
        }
        else {
          tmp_idx.push_back(col);
          tmpv.push_back(cur_row[col]);
          unorm[row_i] += scalar_mag(cur_row[col]);
        }
        pattern[col] = UNUSED;
      }

      for(size_type j=0; j<U_vals_heaplen; ++j) {
        tmp_idx.push_back(U_vals_heap[j]);
        tmpv.push_back(cur_row[U_vals_heap[j]]);
        unorm[row_i] += scalar_mag(cur_row[U_vals_heap[j]]);
      }

      unorm[row_i] /= (orig_U_len + U_vals_heaplen);

      U_->insertLocalValues(row_i, tmp_idx(), tmpv() );
#ifdef IFPACK2_WRITE_FACTORS
      for(int ii=0; ii<tmp_idx.size(); ++ii) {
        ofsU <<row_i<< " " <<tmp_idx[ii]<< " " <<tmpv[ii]<< std::endl;
      }
#endif
      tmp_idx.clear();
      tmpv.clear();

      U_->getLocalRowView(row_i, Uindices[row_i], Ucoefs[row_i] );

      L_cols_heap.clear();
      U_cols.clear();
      L_vals_heap.clear();
      U_vals_heap.clear();
    } // end of for(row_i) loop

    // FIXME (mfh 03 Apr 2013) Do we need to supply a domain and range Map?
    L_->fillComplete();
    U_->fillComplete();
    */
    U_ = Tpetra::MatrixMarket::Reader<OP>::readSparseFile(precFileName_, getComm(), Kokkos::DefaultNode::getDefaultNode());
    Tpetra::RowMatrixTransposer<Scalar, Ordinal, Ordinal, Node, Kokkos::DefaultKernels<Scalar, Ordinal, Node>::SparseOps> trans(U_.getConst());
    L_ = trans.createTranspose();
    //std::cout << "###" << U_->isUpperTriangular() << std::endl;
    
  }
  ComputeTime_ += timer.totalElapsedTime ();
  IsComputed_ = true;
  ++NumCompute_;
}