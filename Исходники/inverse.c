    void cofactor(float num[25][25], float f)

    {

     float b[25][25], fac[25][25];

     int p, q, m, n, i, j;

     for (q = 0;q < f; q++)

     {

       for (p = 0;p < f; p++)

        {

         m = 0;

         n = 0;

         for (i = 0;i < f; i++)

         {

           for (j = 0;j < f; j++)

            {

              if (i != q && j != p)

              {

                b[m][n] = num[i][j];

                if (n < (f - 2))

                 n++;

                else

                 {

                   n = 0;

                   m++;

                   }

                }

            }

          }

          fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);

        }

      }

      transpose(num, fac, f);//calling the function transpose to transpose the matrix

    }