void AbstractTarget::Dsyevj3(Matc3<real> &a, Matc3<real> &q, Vect3<real> &w)
{
/* ** 
----------------------------------------------------------------------
Numerical diagonalization of 3x3 matrcies
Copyright (C) 2006  Joachim Kopp
----------------------------------------------------------------------
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-13
----------------------------------------------------------------------

----------------------------------------------------------------------
Calculates the eigenvalues and normalized eigenvectors of a symmetric
matrix A using the Jacobi algorithm.
The upper triangular part of A is destroyed during the calculation,
the diagonal elements are read but not destroyed, and the lower
triangular elements are not referenced at all.
----------------------------------------------------------------------
Parameters:
  A: The symmetric input matrix
  Q: Storage buffer for eigenvectors
  W: Storage buffer for eigenvalues
----------------------------------------------------------------------
C++ version was created by Choliy V., 2012.
** */
	const int n = 3;
//
// Initialize Q to the identitity matrix 
// --- This loop can be omitted if only the eigenvalues are desired -
	q.Unity();
//
// Initialize W to diag(A)
	int x, y;
	for(x=0; x<n; ++x)
		w.data[x] = a.Data(x, x);
//
// Calculate SQR(tr(A))
	real sd = zero_;
	for(x=0; x<n; ++x)
		sd += Fabs(w.data[x]);
	sd = sd*sd;
//
// Main iteration loop
	int i;
	for(i=0; i<50; ++i)
	{
//
// Test for convergence
		real so = zero_;
		for(x=0; x<n; ++x)
			for(y=x+1; y<n; ++y)
				so += Fabs(a.Data(x, y));
		if (so == zero_)
		{
			fprintf(stderr, "Dsyevj3 converged.\n");
			return;
		}

		real thresh = (i < 3) ? (real)0.2*so/(n*n) : zero_;
//        
// Do sweep
		real t, theta;
		for(x=0; x<n; ++x)
		{
			for(y=x+1; y<n; ++y)
			{
				real g = (real)100.0*(Fabs(a.Data(x,y)));
				if ((i > 3) && (Fabs(w.data[x])+g == Fabs(w.data[x])) && (Fabs(w.data[y])+g == Fabs(w.data[y])))
					a.Data(x,y) = zero_;
				else
				{
					if (Fabs(a.Data(x,y)) > thresh)							// Calculate Jacobi transformation
					{
						real h = w.data[y] - w.data[x];
						if (Fabs(h)+g == Fabs(h))
							t = a.Data(x,y) / h;
						else
						{
							theta = half_*h/a.Data(x,y);
							t = (theta < zero_) ? -(real)1./(Sqrt((real)1. + theta*theta) - theta) : (real)1./(sqrt((real)1. + theta*theta) + theta);
						}
						real c = (real)1./Sqrt((real)1. + t*t);
						real s = t*c;
						real z = t*a.Data(x,y);
// Apply Jacobi transformation
						a.Data(x,y) = zero_;
						w.data[x] -= z;
						w.data[y] += z;
						int r;
						for(r=0; r<x; ++r)
						{
							t = a.Data(r, x);
							a.Data(r, x) = c*t - s*a.Data(r, y);
							a.Data(r, y) = s*t + c*a.Data(r, y);
						}
						for(r=x+1; r<y; ++r)
						{
							t = a.Data(x, r);
							a.Data(x, r) = c*t - s*a.Data(r, y);
							a.Data(r, y) = s*t + c*a.Data(r, y);
						}
						for(r=y+1; r<n; ++r)
						{
							t = a.Data(x, r);
							a.Data(x, r) = c*t - s*a.Data(y, r);
							a.Data(y, r) = s*t + c*a.Data(y, r);
						}
// Update eigenvectors
// --- This loop can be omitted if only the eigenvalues are desired
						for(r=0; r<n; ++r)
						{
							t = q.Data(r,x);
							q.Data(r,x) = c*t - s*q.Data(r,y);
							q.Data(r,y) = s*t + c*q.Data(r,y);
						}
					}
				}
			}
		}
	}
	fprintf(stderr, ">DSYEVJ3: No convergence.\n");
}