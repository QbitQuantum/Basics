void MKLPoolingLayer<Dtype>::pack_buffer(FeatureMap *fm, Dtype *to, const Dtype *from) {
      for (int i = 0; i < fm->NumPackBlocks(); i++) {
          BlockInfo * bi = fm->GetPackBlock(i);
          int bMBLen = bi->MBLen();
          int bMBStart = bi->MBStart();
          int bFMLen = bi->FMLen();
          int bFMStart = bi->FMStart();
          Dtype *src = (Dtype*) from;
          Dtype *dst = (Dtype*) (to + bi->BufOffset());
          for (int mb = 0; mb < bMBLen; mb++) {
              for (int fm = 0; fm < bFMLen; fm++) {
                  for (int s = 0 ; s < bi->FMSize(); s++) {
                      //dst[fm][mb][s] = src[s][bFMStart+fm][bMBStart+mb]; //[bMBStart+mb][bFMStart+fm][s];
                      dst[(fm*bMBLen + mb)*bi->FMSize() + s] =
                          src[s*bFMLen*bMBLen + (bFMStart+fm)*bMBLen + (bMBStart+mb)];
                  }
              }
          }
      }
  }