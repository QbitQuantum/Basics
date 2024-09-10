static void eml_qrsolve(const emxArray_real_T *A, emxArray_real_T *B, double Y[2],
  double *rankR)
{
  emxArray_real_T *b_A;
  int m;
  int mn;
  int i6;
  int itemp;
  int b_m;
  int b_mn;
  double tau_data[2];
  signed char jpvt[2];
  double work[2];
  int i;
  int k;
  double vn1[2];
  double vn2[2];
  int pvt;
  double smax;
  int i_i;
  int mmi;
  double temp2;
  int ix;
  int iy;
  double atmp;
  int lastv;
  int lastc;
  boolean_T exitg2;
  int32_T exitg1;
  double t;
  unsigned int b_i;
  emxInit_real_T(&b_A, 2);
  m = A->size[0] - 2;
  mn = (int)fmin(A->size[0], 2.0) - 1;
  i6 = b_A->size[0] * b_A->size[1];
  b_A->size[0] = A->size[0];
  b_A->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)b_A, i6, (int)sizeof(double));
  itemp = A->size[0] * A->size[1];
  for (i6 = 0; i6 < itemp; i6++) {
    b_A->data[i6] = A->data[i6];
  }

  b_m = b_A->size[0];
  if (b_A->size[0] <= 2) {
    b_mn = b_A->size[0];
  } else {
    b_mn = 2;
  }

  for (i6 = 0; i6 < 2; i6++) {
    jpvt[i6] = (signed char)(1 + i6);
  }

  if (b_A->size[0] == 0) {
  } else {
    for (i = 0; i < 2; i++) {
      work[i] = 0.0;
    }

    k = 1;
    for (pvt = 0; pvt < 2; pvt++) {
      smax = eml_xnrm2(b_m, b_A, k);
      vn2[pvt] = smax;
      k += b_m;
      vn1[pvt] = smax;
    }

    for (i = 0; i + 1 <= b_mn; i++) {
      i_i = i + i * b_m;
      mmi = (b_m - i) - 1;
      itemp = 0;
      if (2 - i > 1) {
        smax = fabs(vn1[i]);
        k = 2;
        while (k <= 2 - i) {
          temp2 = fabs(vn1[1]);
          if (temp2 > smax) {
            itemp = 1;
            smax = temp2;
          }

          k = 3;
        }
      }

      pvt = i + itemp;
      if (pvt + 1 != i + 1) {
        ix = b_m * pvt;
        iy = b_m * i;
        for (k = 1; k <= b_m; k++) {
          smax = b_A->data[ix];
          b_A->data[ix] = b_A->data[iy];
          b_A->data[iy] = smax;
          ix++;
          iy++;
        }

        itemp = jpvt[pvt];
        jpvt[pvt] = jpvt[i];
        jpvt[i] = (signed char)itemp;
        vn1[pvt] = vn1[i];
        vn2[pvt] = vn2[i];
      }

      if (i + 1 < b_m) {
        atmp = b_A->data[i_i];
        temp2 = 0.0;
        if (1 + mmi <= 0) {
        } else {
          smax = b_eml_xnrm2(mmi, b_A, i_i + 2);
          if (smax != 0.0) {
            smax = hypot(b_A->data[i_i], smax);
            if (b_A->data[i_i] >= 0.0) {
              smax = -smax;
            }

            if (fabs(smax) < 1.0020841800044864E-292) {
              pvt = 0;
              do {
                pvt++;
                eml_xscal(mmi, 9.9792015476736E+291, b_A, i_i + 2);
                smax *= 9.9792015476736E+291;
                atmp *= 9.9792015476736E+291;
              } while (!(fabs(smax) >= 1.0020841800044864E-292));

              smax = b_eml_xnrm2(mmi, b_A, i_i + 2);
              smax = hypot(atmp, smax);
              if (atmp >= 0.0) {
                smax = -smax;
              }

              temp2 = (smax - atmp) / smax;
              eml_xscal(mmi, 1.0 / (atmp - smax), b_A, i_i + 2);
              for (k = 1; k <= pvt; k++) {
                smax *= 1.0020841800044864E-292;
              }

              atmp = smax;
            } else {
              temp2 = (smax - b_A->data[i_i]) / smax;
              eml_xscal(mmi, 1.0 / (b_A->data[i_i] - smax), b_A, i_i + 2);
              atmp = smax;
            }
          }
        }

        tau_data[i] = temp2;
      } else {
        atmp = b_A->data[i_i];
        tau_data[i] = eml_matlab_zlarfg();
      }

      b_A->data[i_i] = atmp;
      if (i + 1 < 2) {
        atmp = b_A->data[i_i];
        b_A->data[i_i] = 1.0;
        if (tau_data[0] != 0.0) {
          lastv = mmi + 1;
          itemp = i_i + mmi;
          while ((lastv > 0) && (b_A->data[itemp] == 0.0)) {
            lastv--;
            itemp--;
          }

          lastc = 1;
          exitg2 = false;
          while ((!exitg2) && (lastc > 0)) {
            itemp = b_m + 1;
            do {
              exitg1 = 0;
              if (itemp <= b_m + lastv) {
                if (b_A->data[itemp - 1] != 0.0) {
                  exitg1 = 1;
                } else {
                  itemp++;
                }
              } else {
                lastc = 0;
                exitg1 = 2;
              }
            } while (exitg1 == 0);

            if (exitg1 == 1) {
              exitg2 = true;
            }
          }
        } else {
          lastv = 0;
          lastc = 0;
        }

        if (lastv > 0) {
          if (lastc == 0) {
          } else {
            work[0] = 0.0;
            iy = 0;
            pvt = 1 + b_m;
            while ((b_m > 0) && (pvt <= b_m + 1)) {
              ix = i_i;
              smax = 0.0;
              i6 = (pvt + lastv) - 1;
              for (itemp = pvt; itemp <= i6; itemp++) {
                smax += b_A->data[itemp - 1] * b_A->data[ix];
                ix++;
              }

              work[iy] += smax;
              iy++;
              pvt += b_m;
            }
          }

          if (-tau_data[0] == 0.0) {
          } else {
            k = b_m;
            iy = 0;
            pvt = 1;
            while (pvt <= lastc) {
              if (work[iy] != 0.0) {
                smax = work[iy] * -tau_data[0];
                ix = i_i;
                i6 = lastv + k;
                for (itemp = k; itemp + 1 <= i6; itemp++) {
                  b_A->data[itemp] += b_A->data[ix] * smax;
                  ix++;
                }
              }

              iy++;
              k += b_m;
              pvt = 2;
            }
          }
        }

        b_A->data[i_i] = atmp;
      }

      pvt = i + 2;
      while (pvt < 3) {
        itemp = (i + b_m) + 1;
        if (vn1[1] != 0.0) {
          smax = fabs(b_A->data[i + b_A->size[0]]) / vn1[1];
          smax = 1.0 - smax * smax;
          if (smax < 0.0) {
            smax = 0.0;
          }

          temp2 = vn1[1] / vn2[1];
          temp2 = smax * (temp2 * temp2);
          if (temp2 <= 1.4901161193847656E-8) {
            if (i + 1 < b_m) {
              smax = 0.0;
              if (mmi < 1) {
              } else if (mmi == 1) {
                smax = fabs(b_A->data[itemp]);
              } else {
                temp2 = 2.2250738585072014E-308;
                pvt = itemp + mmi;
                while (itemp + 1 <= pvt) {
                  atmp = fabs(b_A->data[itemp]);
                  if (atmp > temp2) {
                    t = temp2 / atmp;
                    smax = 1.0 + smax * t * t;
                    temp2 = atmp;
                  } else {
                    t = atmp / temp2;
                    smax += t * t;
                  }

                  itemp++;
                }

                smax = temp2 * sqrt(smax);
              }

              vn1[1] = smax;
              vn2[1] = smax;
            } else {
              vn1[1] = 0.0;
              vn2[1] = 0.0;
            }
          } else {
            vn1[1] *= sqrt(smax);
          }
        }

        pvt = 3;
      }
    }
  }

  *rankR = 0.0;
  if (mn + 1 > 0) {
    smax = fmax(A->size[0], 2.0) * fabs(b_A->data[0]) * 2.2204460492503131E-16;
    k = 0;
    while ((k <= mn) && (!(fabs(b_A->data[k + b_A->size[0] * k]) <= smax))) {
      (*rankR)++;
      k++;
    }
  }

  for (i = 0; i < 2; i++) {
    Y[i] = 0.0;
  }

  for (pvt = 0; pvt <= mn; pvt++) {
    if (tau_data[pvt] != 0.0) {
      smax = B->data[pvt];
      i6 = m - pvt;
      for (i = 0; i <= i6; i++) {
        b_i = ((unsigned int)pvt + i) + 2U;
        smax += b_A->data[((int)b_i + b_A->size[0] * pvt) - 1] * B->data[(int)
          b_i - 1];
      }

      smax *= tau_data[pvt];
      if (smax != 0.0) {
        B->data[pvt] -= smax;
        i6 = m - pvt;
        for (i = 0; i <= i6; i++) {
          b_i = ((unsigned int)pvt + i) + 2U;
          B->data[(int)b_i - 1] -= b_A->data[((int)b_i + b_A->size[0] * pvt) - 1]
            * smax;
        }
      }
    }
  }

  for (i = 0; i <= mn; i++) {
    Y[jpvt[i] - 1] = B->data[i];
  }

  for (pvt = 0; pvt <= mn; pvt++) {
    itemp = mn - pvt;
    Y[jpvt[itemp] - 1] /= b_A->data[itemp + b_A->size[0] * itemp];
    i = 0;
    while (i <= itemp - 1) {
      Y[jpvt[0] - 1] -= Y[jpvt[itemp] - 1] * b_A->data[b_A->size[0] * itemp];
      i = 1;
    }
  }

  emxFree_real_T(&b_A);
}