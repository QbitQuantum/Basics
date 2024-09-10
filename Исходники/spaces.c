/*
:h3.MatrixInvert() - Invert a Matrix
 
My reference for matrix inversion was :hp1/Elementary Linear Algebra/
by Paul C. Shields, Worth Publishers, Inc., 1968.
*/
void 
MatrixInvert(double M[2][2],      /* input matrix                            */
	     double Mprime[2][2]) /* output inverted matrix                  */
{
       register double D;    /* determinant of matrix M                      */
       register double txx,txy,tyx,tyy;
 
       txx = M[0][0];
       txy = M[1][0];
       tyx = M[0][1];
       tyy = M[1][1];
 
       D = M[1][1] * M[0][0] - M[1][0] * M[0][1];
       if (D == 0.0)
               Abort("MatrixInvert:  can't");
 
       Mprime[0][0] = tyy / D;
       Mprime[1][0] = -txy / D;
       Mprime[0][1] = -tyx / D;
       Mprime[1][1] = txx / D;
}