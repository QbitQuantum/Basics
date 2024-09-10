void eml_xgesvd(const float A[25], float U[25], float S[5], float V[25])
{
  float b_A[25];
  float s[5];
  float e[5];
  float work[5];
  int kase;
  int q;
  int iter;
  boolean_T apply_transform;
  float ztest0;
  int qp1jj;
  int qs;
  int m;
  float rt;
  float ztest;
  float snorm;
  int32_T exitg3;
  boolean_T exitg2;
  float f;
  float varargin_1[5];
  float mtmp;
  boolean_T exitg1;
  float sqds;
  float mtmp_inv;

  for (int k=0;k<25;k++)
    b_A[k] = A[k];
  //mem_fp_cpy(&b_A[0], &A[0], 25);
  //memcpy(&b_A[0], &A[0], 25U * sizeof(float));
  for (kase = 0; kase < 5; kase++) {
    s[kase] = 0.0F;
    e[kase] = 0.0F;
    work[kase] = 0.0F;
  }

  for (kase = 0; kase < 25; kase++) {
    U[kase] = 0.0F;
    V[kase] = 0.0F;
  }

  for (q = 0; q < 4; q++) {
    iter = q + 5 * q;
    apply_transform = false;
    ztest0 = eml_xnrm2(5 - q, b_A, iter + 1);
    if (ztest0 > 0.0F) {
      apply_transform = true;
      if (b_A[iter] < 0.0F) {
        s[q] = -ztest0;
      } else {
        s[q] = ztest0;
      }

      if (fAbs(s[q]) >= 9.86076132E-32F) {
        ztest0 = fDiv(1.0F,  s[q]);
        kase = (iter - q) + 5;
        for (qp1jj = iter; qp1jj + 1 <= kase; qp1jj++) {
          b_A[qp1jj] *= ztest0;
        }
      } else {
        kase = (iter - q) + 5;
        for (qp1jj = iter; qp1jj + 1 <= kase; qp1jj++) {
          b_A[qp1jj] = fDiv(b_A[qp1jj],s[q]);
        }
      }

      b_A[iter]++;
      s[q] = -s[q];
    } else {
      s[q] = 0.0F;
    }

    for (qs = q + 1; qs + 1 < 6; qs++) {
      kase = q + 5 * qs;
      if (apply_transform) {
        eml_xaxpy(5 - q, -(fDiv(eml_xdotc(5 - q, b_A, iter + 1, b_A, kase + 1), b_A[q + 5 * q])), iter + 1, b_A, kase + 1);
      }

      e[qs] = b_A[kase];
    }

    for (qp1jj = q; qp1jj + 1 < 6; qp1jj++) {
      U[qp1jj + 5 * q] = b_A[qp1jj + 5 * q];
    }

    if (q + 1 <= 3) {
      ztest0 = b_eml_xnrm2(4 - q, e, q + 2);
      if (ztest0 == 0.0F) {
        e[q] = 0.0F;
      } else {
        if (e[q + 1] < 0.0F) {
          e[q] = -ztest0;
        } else {
          e[q] = ztest0;
        }

        ztest0 = e[q];
        if (fAbs(e[q]) >= 9.86076132E-32F) {
          ztest0 = fDiv(1.0F, e[q]);
          for (qp1jj = q + 1; qp1jj + 1 < 6; qp1jj++) {
            e[qp1jj] *= ztest0;
          }
        } else {
          for (qp1jj = q + 1; qp1jj + 1 < 6; qp1jj++) {
            e[qp1jj] = fDiv(e[qp1jj],ztest0);
          }
        }

        e[q + 1]++;
        e[q] = -e[q];
        for (qp1jj = q + 1; qp1jj + 1 < 6; qp1jj++) {
          work[qp1jj] = 0.0F;
        }

        for (qs = q + 1; qs + 1 < 6; qs++) {
          b_eml_xaxpy(4 - q, e[qs], b_A, (q + 5 * qs) + 2, work, q + 2);
        }

        for (qs = q + 1; qs + 1 < 6; qs++) {
          c_eml_xaxpy(4 - q, -fDiv(e[qs], e[q + 1]), work, q + 2, b_A, (q + 5 * qs) +
                      2);
        }
      }

      for (qp1jj = q + 1; qp1jj + 1 < 6; qp1jj++) {
        V[qp1jj + 5 * q] = e[qp1jj];
      }
    }
  }

  m = 3;
  s[4] = b_A[24];
  e[3] = b_A[23];
  e[4] = 0.0F;
  for (qp1jj = 0; qp1jj < 5; qp1jj++) {
    U[20 + qp1jj] = 0.0F;
  }

  U[24] = 1.0F;
  for (q = 3; q > -1; q += -1) {
    iter = q + 5 * q;
    if (s[q] != 0.0F) {
      for (qs = q + 1; qs + 1 < 6; qs++) {
        kase = (q + 5 * qs) + 1;
        eml_xaxpy(5 - q, -(fDiv(eml_xdotc(5 - q, U, iter + 1, U, kase), U[iter])),
                  iter + 1, U, kase);
      }

      for (qp1jj = q; qp1jj + 1 < 6; qp1jj++) {
        U[qp1jj + 5 * q] = -U[qp1jj + 5 * q];
      }

      U[iter]++;
      for (qp1jj = 1; qp1jj <= q; qp1jj++) {
        U[(qp1jj + 5 * q) - 1] = 0.0F;
      }
    } else {
      for (qp1jj = 0; qp1jj < 5; qp1jj++) {
        U[qp1jj + 5 * q] = 0.0F;
      }

      U[iter] = 1.0F;
    }
  }

  for (q = 4; q > -1; q += -1) {
    if ((q + 1 <= 3) && (e[q] != 0.0F)) {
      kase = (q + 5 * q) + 2;
      for (qs = q + 1; qs + 1 < 6; qs++) {
        qp1jj = (q + 5 * qs) + 2;
        eml_xaxpy(4 - q, -(fDiv(eml_xdotc(4 - q, V, kase, V, qp1jj), V[kase - 1])),
                  kase, V, qp1jj);
      }
    }

    for (qp1jj = 0; qp1jj < 5; qp1jj++) {
      V[qp1jj + 5 * q] = 0.0F;
    }

    V[q + 5 * q] = 1.0F;
  }

  for (q = 0; q < 5; q++) {
    ztest0 = e[q];
    if (s[q] != 0.0F) {
      rt = fAbs(s[q]);
      ztest = fDiv(s[q], rt);
      s[q] = rt;
      if (q + 1 < 5) {
        ztest0 = fDiv(e[q], ztest);
      }

      eml_xscal(ztest, U, 1 + 5 * q);
    }

    if ((q + 1 < 5) && (ztest0 != 0.0F)) {
      rt = fAbs(ztest0);
      ztest = fDiv(rt, ztest0);
      ztest0 = rt;
      s[q + 1] *= ztest;
      eml_xscal(ztest, V, 1 + 5 * (q + 1));
    }

    e[q] = ztest0;
  }

  iter = 0;
  snorm = 0.0F;
  for (qp1jj = 0; qp1jj < 5; qp1jj++) {
    ztest0 = fAbs(s[qp1jj]);
    ztest = fAbs(e[qp1jj]);
    if ((ztest0 >= ztest) || fIsNan(ztest)) {
    } else {
      ztest0 = ztest;
    }

    if ((snorm >= ztest0) || fIsNan(ztest0)) {
    } else {
      snorm = ztest0;
    }
  }

  while ((m + 2 > 0) && (!(iter >= 75))) {
    qp1jj = m;
    do {
      exitg3 = 0;
      q = qp1jj + 1;
      if (qp1jj + 1 == 0) {
        exitg3 = 1;
      } else {
        ztest0 = fAbs(e[qp1jj]);
        if ((ztest0 <= 1.1920929E-7F * (fAbs(s[qp1jj]) + fAbs(s[qp1jj + 1]))) || (ztest0 <= 9.86076132E-32F) || ((iter > 20)
             && (ztest0 <= 1.1920929E-7F * snorm))) {
          e[qp1jj] = 0.0F;
          exitg3 = 1;
        } else {
          qp1jj--;
        }
      }
    } while (exitg3 == 0);

    if (qp1jj + 1 == m + 1) {
      kase = 4;
    } else {
      qs = m + 2;
      kase = m + 2;
      exitg2 = false;
      while ((!exitg2) && (kase >= qp1jj + 1)) {
        qs = kase;
        if (kase == qp1jj + 1) {
          exitg2 = true;
        } else {
          ztest0 = 0.0F;
          if (kase < m + 2) {
            ztest0 = fAbs(e[kase - 1]);
          }

          if (kase > qp1jj + 2) {
            ztest0 += fAbs(e[kase - 2]);
          }

          ztest = fAbs(s[kase - 1]);
          if ((ztest <= 1.1920929E-7F * ztest0) || (ztest <= 9.86076132E-32F)) {
            s[kase - 1] = 0.0F;
            exitg2 = true;
          } else {
            kase--;
          }
        }
      }

      if (qs == qp1jj + 1) {
        kase = 3;
      } else if (qs == m + 2) {
        kase = 1;
      } else {
        kase = 2;
        q = qs;
      }
    }

    switch (kase) {
     case 1:
      f = e[m];
      e[m] = 0.0F;
      for (qp1jj = m; qp1jj + 1 >= q + 1; qp1jj--) {
        ztest0 = s[qp1jj];
        eml_xrotg(&ztest0, &f, &ztest, &rt);
        s[qp1jj] = ztest0;
        if (qp1jj + 1 > q + 1) {
          f = -rt * e[qp1jj - 1];
          e[qp1jj - 1] *= ztest;
        }

        eml_xrot(V, 1 + 5 * qp1jj, 1 + 5 * (m + 1), ztest, rt);
      }
      break;

     case 2:
      f = e[q - 1];
      e[q - 1] = 0.0F;
      for (qp1jj = q; qp1jj + 1 <= m + 2; qp1jj++) {
        eml_xrotg(&s[qp1jj], &f, &ztest, &rt);
        f = -rt * e[qp1jj];
        e[qp1jj] *= ztest;
        eml_xrot(U, 1 + 5 * qp1jj, 1 + 5 * (q - 1), ztest, rt);
      }
      break;

     case 3:
      varargin_1[0] = fAbs(s[m + 1]);
      varargin_1[1] = fAbs(s[m]);
      varargin_1[2] = fAbs(e[m]);
      varargin_1[3] = fAbs(s[q]);
      varargin_1[4] = fAbs(e[q]);
      kase = 1;
      mtmp = varargin_1[0];
      if (fIsNan(varargin_1[0])) {
        qp1jj = 2;
        exitg1 = false;
        while ((!exitg1) && (qp1jj < 6)) {
          kase = qp1jj;
          if (!fIsNan(varargin_1[qp1jj - 1])) {
            mtmp = varargin_1[qp1jj - 1];
            exitg1 = true;
          } else {
            qp1jj++;
          }
        }
      }

      if (kase < 5) {
        while (kase + 1 < 6) {
          if (varargin_1[kase] > mtmp) {
            mtmp = varargin_1[kase];
          }

          kase++;
        }
      }

      mtmp_inv = fDiv(1.0F,mtmp);
      
      f = s[m + 1] * mtmp_inv;
      ztest0 = s[m] * mtmp_inv;
      ztest = e[m] * mtmp_inv;
      sqds = s[q] * mtmp_inv;
      rt = ((ztest0 + f) * (ztest0 - f) + ztest * ztest) * 0.5F;
      ztest0 = f * ztest;
      ztest0 *= ztest0;
      if ((rt != 0.0F) || (ztest0 != 0.0F)) {
        ztest = fSqrt(rt * rt + ztest0);
        if (rt < 0.0F) {
          ztest = -ztest;
        }

        ztest = fDiv(ztest0, (rt + ztest));
      } else {
        ztest = 0.0F;
      }

      f = (sqds + f) * (sqds - f) + ztest;
      ztest0 = sqds * fDiv(e[q], mtmp);
      for (qp1jj = q + 1; qp1jj <= m + 1; qp1jj++) {
        eml_xrotg(&f, &ztest0, &ztest, &rt);
        if (qp1jj > q + 1) {
          e[qp1jj - 2] = f;
        }

        f = ztest * s[qp1jj - 1] + rt * e[qp1jj - 1];
        e[qp1jj - 1] = ztest * e[qp1jj - 1] - rt * s[qp1jj - 1];
        ztest0 = rt * s[qp1jj];
        s[qp1jj] *= ztest;
        eml_xrot(V, 1 + 5 * (qp1jj - 1), 1 + 5 * qp1jj, ztest, rt);
        s[qp1jj - 1] = f;
        eml_xrotg(&s[qp1jj - 1], &ztest0, &ztest, &rt);
        f = ztest * e[qp1jj - 1] + rt * s[qp1jj];
        s[qp1jj] = -rt * e[qp1jj - 1] + ztest * s[qp1jj];
        ztest0 = rt * e[qp1jj];
        e[qp1jj] *= ztest;
        eml_xrot(U, 1 + 5 * (qp1jj - 1), 1 + 5 * qp1jj, ztest, rt);
      }

      e[m] = f;
      iter++;
      break;

     default:
      if (s[q] < 0.0F) {
        s[q] = -s[q];
        eml_xscal(-1.0F, V, 1 + 5 * q);
      }

      kase = q + 1;
      while ((q + 1 < 5) && (s[q] < s[kase])) {
        rt = s[q];
        s[q] = s[kase];
        s[kase] = rt;
        eml_xswap(V, 1 + 5 * q, 1 + 5 * (q + 1));
        eml_xswap(U, 1 + 5 * q, 1 + 5 * (q + 1));
        q = kase;
        kase++;
      }

      iter = 0;
      m--;
      break;
    }
  }

  for (qp1jj = 0; qp1jj < 5; qp1jj++) {
    S[qp1jj] = s[qp1jj];
  }
}