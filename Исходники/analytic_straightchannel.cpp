/**
 * @brief This defines the functionpart of the whole thing. Needed for rheolef::interpolate
 *
 *	Let \f$ x = (x_0,x_1)\f$	

	\f[
		u(x) =  (u_0(x_1), 0)
	\f]
	\f{eqnarray}
		\begin{cases}
			\frac{f}{2}
			\left[
				|y_w|-\frac{Bn}{|f|}
			\right]^2
			&
			x_1 \in [\pm Bn / |f|] \\
			\frac{f}{2}
			\left[ 
				\left( |y_w| - \frac{Bn}{|f|} \right )^2-
				\left( |y|   - \frac{Bn}{|f|} \right )^2
			\right]
			&
			|x_1| >  Bn / |f|
		\end{cases}
	\f}
 * @param x point position
 * @return analytic velocity
 */
point analytic_straight_velocity ::operator() (const point & x)
{
	point u;
	Float yc = _Bn / abs(_dpdx);
	if (abs(x[1]) <= yc)
	{
		u[0]=(_dpdx/2)*sqr(abs(_ywall)-yc);
	}
	else
	{
		u[0]=(_dpdx/2)*(sqr(abs(_ywall)-yc)-sqr(abs(x[1])-yc));
	}
	return u;
}