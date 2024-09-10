/*
  La entrada es una recta normalizada al primer cuadrante
*/
void compute_mid_point_line(const long double & sx, const long double & sy, 
			    const long double & tx, const long double & ty,
			    const long double & d,
			    const bool &        left,
			    long double & mx, long double & my)
{
  const long double lx = fabsl(tx - sx);
  const long double ly = fabsl(ty - sy);

  const long double h = sqrtl(lx*lx + ly*ly); // longitud del segmento
					      // (sx,sy) --> (tx,ty) 

  const long double h2 = h/2; // mitad del segmento

  const long double alpha = atanl(ly/lx); // ángulo del segmento
						 // respecto al eje x

  const long double beta = atanl(d/h2); // ángulo entre el segmento
                                           // y la recta que estaría
					   // entre (sx,sy) y (mx,my)

  const long double hp = sqrtl(d*d + h2*h2); // longitud del segmento
					     // (sx,sy) --> (mx,my) 

  const long double ab = alpha + beta; // ángulo del segmento
				       // (sx,sy)-->(mx,my) respecto al
				       // eje x

  const long double dx = hp*cosl(ab);
  const long double dy = hp*sinl(ab);

      // coordenadas del punto normalizadas a un segmento apuntando
      // hacia el noroeste
  mx = tx - dx;
  my = dy;  
}