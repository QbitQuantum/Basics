template <class GF_q, class real> void linear_code_utils<GF_q, real>::compute_dual_code(
      const matrix<GF_q> & orgMat, matrix<GF_q> & dualCodeGenMatrix,
      array1i_t & systematic_perm)
   {
   int length_n = orgMat.size().cols();
   int dim_k = orgMat.size().rows();
   int dim_m = length_n - dim_k;
   matrix<GF_q> refOrgMat;
#if DEBUG>=2
   std::cout << "The original matrix is given by:" << std::endl;
   orgMat.serialize(std::cout, '\n');
#endif
   linear_code_utils::compute_row_dim(orgMat, refOrgMat);

   dim_k = refOrgMat.size().rows();
   dim_m = length_n - dim_k;

   // Now we need to check that the columns are systematic
   //if they aren't then we need to perform some column permutation
   //otherwise the permutation is simple the identy map

   systematic_perm.init(length_n);
   for (int loop1 = 0; loop1 < length_n; loop1++)
      {
      //the identity permutation
      systematic_perm(loop1) = loop1;
      }

   bool needsPermutation =
         !(libbase::linear_code_utils<GF_q, real>::is_systematic(refOrgMat));
   if (needsPermutation)
      {
      //matrix needs its columns permuted before it is in systematic form
      //find the pivots
      int col_pos = 0;
      for (int loop1 = 0; loop1 < dim_k; loop1++)
         {

         while ((GF_q(1)) != refOrgMat(loop1, col_pos))
            {
            col_pos++;
            }
         std::swap(systematic_perm(loop1), systematic_perm(col_pos));
         col_pos++;
         }
#if DEBUG>=2
      std::cout << std::endl << "The permutation is given by:" << std::endl;
      systematic_perm.serialize(std::cout, ' ');
#endif
      if (needsPermutation)
         {
         //rejig the matrix
         matrix<GF_q> tmprefMatrix;
         tmprefMatrix.init(dim_k, length_n);
         int col_index;
         for (int loop1 = 0; loop1 < length_n; loop1++)
            {
            col_index = systematic_perm(loop1);
            tmprefMatrix.insertcol(refOrgMat.extractcol(col_index), loop1);
            }
         refOrgMat = tmprefMatrix;
         }
      }
   //the matrix should now be in the right format
#if DEBUG>=2
   std::cout << "After permuting any columns, the matrix is now given by:" << std::endl;
   refOrgMat.serialize(std::cout, '\n');
#endif

   //extract the P part of G'=(I_k|P)
   matrix<GF_q> tmp_p_mat;
   tmp_p_mat.init(dim_k, dim_m);

   for (int loop = dim_k; loop < length_n; loop++)
      {
      tmp_p_mat.insertcol(refOrgMat.extractcol(loop), loop - dim_k);
      }

   //this will hold -P^t=P^t (as we are in char GF(q)=2)
   matrix<GF_q> tmp_p_mat_t;
   tmp_p_mat_t.init(dim_m, length_n - dim_m);
   //now transpose yourself
   tmp_p_mat_t = tmp_p_mat.transpose();
   matrix<GF_q> id_m = matrix<GF_q>::eye(dim_m);

   //Construct the dual code gen matrix which is of the form
   //H=(-P^t|I_m)
   dualCodeGenMatrix.init(dim_m, length_n);

   //insert the transposed matrix
   for (int loop = 0; loop < (length_n - dim_m); loop++)
      {
      dualCodeGenMatrix.insertcol(tmp_p_mat_t.extractcol(loop), loop);
      }

   //now add the identity matrix
   int counter = 0;
   for (int loop = (length_n - dim_m); loop < length_n; loop++)
      {
      dualCodeGenMatrix.insertcol(id_m.extractcol(counter), loop);
      counter++;
      }

#if DEBUG>=2
   std::cout << "The generator matrix of the permuted dual code is given by:" << std::endl;
   dualCodeGenMatrix.serialize(std::cout, '\n');
#endif

   //undo any permutation that we did
   if (needsPermutation)
      {

      matrix<GF_q> tmpdualCodeGenMatrix;
      tmpdualCodeGenMatrix.init(dim_m, length_n);
      int col_index;
      for (int loop1 = 0; loop1 < length_n; loop1++)
         {
         col_index = systematic_perm(loop1);
         tmpdualCodeGenMatrix.insertcol(dualCodeGenMatrix.extractcol(loop1),
               col_index);
         }
      dualCodeGenMatrix = tmpdualCodeGenMatrix;
      }

#if DEBUG>=2
   std::cout
   << "After undoing the permutation, the generator matrix of the dual code is given by:" << std::endl;
   dualCodeGenMatrix.serialize(std::cout, '\n');
#endif

#if DEBUG>=2
   std::cout
   << "we now multiply the generator matrix by the transpose of the original matrix, ie:" << std::endl;
   std::cout << "the transpose of:" << std::endl;
   orgMat.serialize(std::cout, '\n');
   std::cout << "is:" << std::endl;
   matrix<GF_q> trans(orgMat.transpose());
   trans.serialize(std::cout, '\n');
   matrix<GF_q> zeroTest(dualCodeGenMatrix*trans);
   std::cout << "the result is:" << std::endl;
   zeroTest.serialize(std::cout, '\n');
   assertalways(GF_q(0)==zeroTest.max());
#endif

   }