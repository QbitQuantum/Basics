/* WriteParms: write generated parameter vector sequences */
void WriteParms(char *labfn, GenInfo * genInfo)
{
   int p, t, v, k;
   char ext[MAXSTRLEN], fn[MAXFNAMELEN];
   float ig;
   Vector igvec;
   TriMat igtm;
   FILE *parmfp = NULL, *pdffp = NULL;
   Boolean isPipe1, isPipe2;
   PdfStream *pst;

   /* get ignore value for MSD */
   ig = ReturnIgnoreValue();

   /* save generated parameters */
   for (p = 1; p <= genInfo->nPdfStream[0]; p++) {
      /* p-th PdfStream */
      pst = &(genInfo->pst[p]);

      /* create ignore value vector/triangular matrix */
      igvec = CreateVector(&genStack, pst->vSize);
      igtm = CreateTriMat(&genStack, pst->vSize);
      for (v = 1; v <= pst->vSize; v++) {
         igvec[v] = ig;
         for (k = 1; k <= v; k++)
            igtm[v][k] = ig;
      }

      /* open file pointer for saving generated parameters */
      MakeFN(labfn, genDir, pst->ext, fn);
      if ((parmfp = FOpen(fn, NoOFilter, &isPipe1)) == NULL)
         HError(9911, "WriteParms: Cannot create ouput file %s", fn);

      /* open file pointer for saving pdf parameters */
      if (outPdf) {
         sprintf(ext, "%s_%s", pst->ext, pdfExt);
         MakeFN(labfn, genDir, ext, fn);
         if ((pdffp = FOpen(fn, NoOFilter, &isPipe2)) == NULL)
            HError(9911, "WriteParms: Cannot create output file %s", fn);
      }

      /* output generated parameter sequence */
      for (t = pst->t = 1; t <= genInfo->tframe; t++) {
         if (pst->ContSpace[t]) {
            /* output generated parameters */
            WriteVector(parmfp, pst->C[pst->t], inBinary);

            /* output pdfs */
            if (outPdf) {
               WriteVector(pdffp, pst->mseq[pst->t], inBinary);
               if (pst->fullCov)
                  WriteTriMat(pdffp, pst->vseq[pst->t].inv, inBinary);
               else
                  WriteVector(pdffp, pst->vseq[pst->t].var, inBinary);
            }

            pst->t++;
         } else {
            /* output ignoreValue symbol for generated parameters */
            WriteFloat(parmfp, &igvec[1], pst->order, inBinary);

            /* output ignoreValue symbol for pdfs */
            if (outPdf) {
               WriteVector(pdffp, igvec, inBinary);
               if (pst->fullCov)
                  WriteTriMat(pdffp, igtm, inBinary);
               else
                  WriteVector(pdffp, igvec, inBinary);
            }
         }
      }

      /* close file pointer */
      if (outPdf)
         FClose(pdffp, isPipe2);
      FClose(parmfp, isPipe1);

      /* free igvec */
      FreeVector(&genStack, igvec);
   }

   return;
}