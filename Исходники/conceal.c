/*
  The function creates the interpolated spectral data according to the 
  energy of the last good frame and the current (good) frame.
*/
void CConcealment_InterpolateBuffer (float       *spectrum,
                                     float       *enPrev,
                                     float       *enAct,
                                     int          sfbCnt,
                                     const short *pSfbOffset)
{
  int    sfb, line = 0;
  float  multiplier;

  FLC_sub_start("CConcealment_InterpolateBuffer");

  MOVE(1); /* counting previous operation */

  PTR_INIT(3); /* enAct[]
                  enPrev[]
                  spectrum[]
               */
  LOOP(1);
  for(sfb = 0; sfb < sfbCnt; sfb++) {

    DIV(1); TRANS(1);
    multiplier = (float) pow(enAct[sfb] / enPrev[sfb], 0.25f);

    LOOP(1);
    for(; line < pSfbOffset[sfb+1]; line++) {

      MULT(1); STORE(1);
      spectrum [line] = spectrum[line] * multiplier;
    }
  }

  FLC_sub_end();
}