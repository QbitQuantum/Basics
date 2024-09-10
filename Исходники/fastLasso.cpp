// barebones version of the lasso for fixed lambda
// Eigen library is used for linear algebra
// x .............. predictor matrix
// y .............. response
// lambda ......... penalty parameter
// useSubset ...... logical indicating whether lasso should be computed on a
//                  subset
// subset ......... indices of subset on which lasso should be computed
// normalize ...... logical indicating whether predictors should be normalized
// useIntercept ... logical indicating whether intercept should be included
// eps ............ small numerical value (effective zero)
// useGram ........ logical indicating whether Gram matrix should be computed
//                  in advance
// useCrit ........ logical indicating whether to compute objective function
void fastLasso(const MatrixXd& x, const VectorXd& y, const double& lambda,
		const bool& useSubset, const VectorXi& subset, const bool& normalize, 
    const bool& useIntercept, const double& eps, const bool& useGram, 
    const bool& useCrit,
    // intercept, coefficients, residuals and objective function are returned 
    // through the following parameters
    double& intercept, VectorXd& beta, VectorXd& residuals, double& crit) {

	// data initializations
	int n, p = x.cols();
	MatrixXd xs;
	VectorXd ys;
	if(useSubset) {
		n = subset.size();
		xs.resize(n, p);
		ys.resize(n);
		int s;
		for(int i = 0; i < n; i++) {
			s = subset(i);
			xs.row(i) = x.row(s);
			ys(i) = y(s);
		}
	} else {
		n = x.rows();
		xs = x;	// does this copy memory?
		ys = y;	// does this copy memory?
	}
	double rescaledLambda = n * lambda / 2;

	// center data and store means
	RowVectorXd meanX;
	double meanY;
	if(useIntercept) {
		meanX = xs.colwise().mean();	// columnwise means of predictors
		xs.rowwise() -= meanX;			// sweep out columnwise means
		meanY = ys.mean();				// mean of response
		for(int i = 0; i < n; i++) {
			ys(i) -= meanY;				// sweep out mean
		}
	} else {
		meanY = 0;		// just to avoid warning, this is never used
//		intercept = 0;	// zero intercept
	}

	// some initializations
	VectorXi inactive(p);	// inactive predictors
	int m = 0;				// number of inactive predictors
	VectorXi ignores;		// indicates variables to be ignored
	int s = 0;				// number of ignored variables

	// normalize predictors and store norms
	RowVectorXd normX;
  if(normalize) {
    normX = xs.colwise().norm();	// columnwise norms
	  double epsNorm = eps * sqrt(n);	// R package 'lars' uses n, not n-1
	  for(int j = 0; j < p; j++) {
		  if(normX(j) < epsNorm) {
			  // variance is too small: ignore variable
			  ignores.append(j, s);
			  s++;
			  // set norm to tolerance to avoid numerical problems
			  normX(j) = epsNorm;
		  } else {
			  inactive(m) = j;		// add variable to inactive set
			  m++;					// increase number of inactive variables
		  }
		  xs.col(j) /= normX(j);		// sweep out norm
	  }
	  // resize inactive set and update number of variables if necessary
	  if(m < p) {
		  inactive.conservativeResize(m);
		  p = m;
	  }
  } else {
    for(int j = 0; j < p; j++) inactive(j) = j;  // add variable to inactive set
    m = p;
  }

	// compute Gram matrix if requested (saves time if number of variables is
	// not too large)
	MatrixXd Gram;
	if(useGram) {
		Gram.noalias() = xs.transpose() * xs;
	}

	// further initializations for iterative steps
  RowVectorXd corY;
  corY.noalias() = ys.transpose() * xs; // current correlations
  beta.resize(p+s);                     // final coefficients

  // compute lasso solution
  if(p == 1) {

    // special case of only one variable (with sufficiently large norm)
    int j = inactive(0);          
    // set maximum step size in the direction of that variable
    double maxStep = corY(j);
    if(maxStep < 0) maxStep = -maxStep; // absolute value
    // compute coefficients for least squares solution
    VectorXd betaLS = xs.col(j).householderQr().solve(ys);
    // compute lasso coefficients
    beta.setZero();
    if(rescaledLambda < maxStep) {
      // interpolate towards least squares solution
      beta(j) = (maxStep - rescaledLambda) * betaLS(0) / maxStep;
    }

  } else {

    // further initializations for iterative steps
    VectorXi active;  // active predictors
  	int k = 0;        // number of active predictors
    // previous and current regression coefficients
  	VectorXd previousBeta = VectorXd::Zero(p+s), currentBeta = VectorXd::Zero(p+s);
  	// previous and current penalty parameter
    double previousLambda = 0, currentLambda = 0;
  	// indicates variables to be dropped
    VectorXi drops;
  	// keep track of sign of correlations for the active variables 
    // (double precision is necessary for solve())
    VectorXd signs;
  	// Cholesky L of Gram matrix of active variables
    MatrixXd L;
  	int rank = 0;		// rank of Cholesky L
    // maximum number of variables to be sequenced
  	int maxActive = findMaxActive(n, p, useIntercept);

  	// modified LARS algorithm for lasso solution
  	while(k < maxActive) {

  		// extract current correlations of inactive variables
  		VectorXd corInactiveY(m);
  		for(int j = 0; j < m; j++) {
  			corInactiveY(j) = corY(inactive(j));
  		}
  		// compute absolute values of correlations and find maximum
  		VectorXd absCorInactiveY = corInactiveY.cwiseAbs();
  		double maxCor = absCorInactiveY.maxCoeff();
  		// update current lambda
  		if(k == 0) {	// no active variables
  			previousLambda = maxCor;
  		} else {
  			previousLambda = currentLambda;
  		}
  		currentLambda = maxCor;
  		if(currentLambda <= rescaledLambda) break;

  		if(drops.size() == 0) {
  			// new active variables
  			VectorXi newActive = findNewActive(absCorInactiveY, maxCor - eps);
  			// do calculations for new active variables
  			for(int j = 0; j < newActive.size(); j++) {
  				// update Cholesky L of Gram matrix of active variables
  				// TODO: put this into void function
  				int newJ = inactive(newActive(j));
  				VectorXd xNewJ;
  				double newX;
  				if(useGram) {
  					newX = Gram(newJ, newJ);
  				} else {
  					xNewJ = xs.col(newJ);
  					newX = xNewJ.squaredNorm();
  				}
  				double normNewX = sqrt(newX);
  				if(k == 0) {	// no active variables, L is empty
  					L.resize(1,1);
  					L(0, 0) = normNewX;
  					rank = 1;
  				} else {
  					VectorXd oldX(k);
  					if(useGram) {
  						for(int j = 0; j < k; j++) {
  							oldX(j) = Gram(active(j), newJ);
  						}
  					} else {
  						for(int j = 0; j < k; j++) {
  							oldX(j) = xNewJ.dot(xs.col(active(j)));
  						}
  					}
  					VectorXd l = L.triangularView<Lower>().solve(oldX);
  					double lkk = newX - l.squaredNorm();
  					// check if L is machine singular
  					if(lkk > eps) {
  						// no singularity: update Cholesky L
  						lkk = sqrt(lkk);
  						rank++;
  						// add new row and column to Cholesky L
  						// this is a little trick: sometimes we need
  						// lower triangular matrix, sometimes upper
  						// hence we define quadratic matrix and use
  						// triangularView() to interpret matrix the
  						// correct way
  						L.conservativeResize(k+1, k+1);
  						for(int j = 0; j < k; j++) {
  							L(k, j) = l(j);
  							L(j, k) = l(j);
  						}
  						L(k,k) = lkk;
  					}
  				}
  				// add new variable to active set or drop it for good
  				// in case of singularity
  				if(rank == k) {
  					// singularity: drop variable for good
  					ignores.append(newJ, s);
  					s++;	// increase number of ignored variables
  					p--;	// decrease number of variables
  					if(p < maxActive) {
  						// adjust maximum number of active variables
  						maxActive = p;
  					}
  				} else {
  					// no singularity: add variable to active set
  					active.append(newJ, k);
  					// keep track of sign of correlation for new active variable
  					signs.append(sign(corY(newJ)), k);
  					k++;	// increase number of active variables
  				}
  			}
  			// remove new active or ignored variables from inactive variables
  			// and corresponding vector of current correlations
  			inactive.remove(newActive);
  			corInactiveY.remove(newActive);
  			m = inactive.size();	// update number of inactive variables
  		}
  		// prepare for computation of step size
  		// here double precision of signs is necessary
  		VectorXd b = L.triangularView<Lower>().solve(signs);
  		VectorXd G = L.triangularView<Upper>().solve(b);
  		// correlations of active variables with equiangular vector
  		double corActiveU = 1/sqrt(G.dot(signs));
  		// coefficients of active variables in linear combination forming the
  		// equiangular vector
  		VectorXd w = G * corActiveU;	// note that this has the right signs
  		// equiangular vector
  		VectorXd u;
  		if(!useGram) {
  			// we only need equiangular vector if we don't use the precomputed
  			// Gram matrix, otherwise we can compute the correlations directly
  			// from the Gram matrix
  			u = VectorXd::Zero(n);
  			for(int i = 0; i < n; i++) {
  				for(int j = 0; j < k; j++) {
  					u(i) += xs(i, active(j)) * w(j);
  				}
  			}
  		}
  		// compute step size in equiangular direction
  		double step;
  		if(k < maxActive) {
  			// correlations of inactive variables with equiangular vector
  			VectorXd corInactiveU(m);
  			if(useGram) {
  				for(int j = 0; j < m; j++) {
  					corInactiveU(j) = 0;
  					for(int i = 0; i < k; i++) {
  						corInactiveU(j) += w(i) * Gram(active(i), inactive(j));
  					}
  				}
  			} else {
  				for(int j = 0; j < m; j++) {
  					corInactiveU(j) = u.dot(xs.col(inactive(j)));
  				}
  			}
  			// compute step size in the direction of the equiangular vector
  			step = findStep(maxCor, corInactiveY, corActiveU, corInactiveU, eps);
  		} else {
  			// last step: take maximum possible step
  			step = maxCor/corActiveU;
  		}
  		// adjust step size if any sign changes and drop corresponding variables
  		drops = findDrops(currentBeta, active, w, eps, step);
  		// update current regression coefficients
  		previousBeta = currentBeta;
  		for(int j = 0; j < k; j++) {
  			currentBeta(active(j)) += step * w(j);
  		}
  		// update current correlations
  		if(useGram) {
  			// we also need to do this for active variables, since they may be
  			// dropped at a later stage
  			// TODO: computing a vector step * w in advance may save some computation time
  			for(int j = 0; j < Gram.cols(); j++) {
  				for(int i = 0; i < k; i++) {
  					corY(j) -= step * w(i) * Gram(active(i), j);
  				}
  			}
  		} else {
  			ys -= step * u;	// take step in equiangular direction
  			corY.noalias() = ys.transpose() * xs;	// update correlations
  		}
  		// drop variables if necessary
  		if(drops.size() > 0) {
  			// downdate Cholesky L
  			// TODO: put this into void function
  			for(int j = drops.size()-1; j >= 0; j--) {
  				// variables need to be dropped in descending order
  				int drop = drops(j);	// index with respect to active set
  				// modify upper triangular part as in R package 'lars'
  				// simply deleting columns is not enough, other computations
  				// necessary but complicated due to Fortran code
  				L.removeCol(drop);
  				VectorXd z = VectorXd::Constant(k, 1, 1);
  				k--;	// decrease number of active variables
  				for(int i = drop; i < k; i++) {
  					double a = L(i,i), b = L(i+1,i);
  					if(b != 0.0) {
  						// compute the rotation
  						double tau, s, c;
  						if(std::abs(b) > std::abs(a)) {
  							tau = -a/b;
  							s = 1.0/sqrt(1.0+tau*tau);
  							c = s * tau;
  						} else {
  							tau = -b/a;
  							c = 1.0/sqrt(1.0+tau*tau);
  							s = c * tau;
  						}
  						// update 'L' and 'z';
  						L(i,i) = c*a - s*b;
  						for(int j = i+1; j < k; j++) {
  							a = L(i,j);
  							b = L(i+1,j);
  							L(i,j) = c*a - s*b;
  							L(i+1,j) = s*a + c*b;
  						}
  						a = z(i);
  						b = z(i+1);
  						z(i) = c*a - s*b;
  						z(i+1) = s*a + c*b;
  					}
  				}
  				// TODO: removing all rows together may save some computation time
  				L.conservativeResize(k, NoChange);
  				rank--;
  			}
  			// mirror lower triangular part
  			for(int j = 0; j < k; j++) {
  				for(int i = j+1; i < k; i++) {
  					L(i,j) = L(j,i);
  				}
  			}
  			// add dropped variables to inactive set and make sure
  			// coefficients are 0
  			inactive.conservativeResize(m + drops.size());
  			for(int j = 0; j < drops.size(); j++) {
  				int newInactive = active(drops(j));
  				inactive(m + j) = newInactive;
  				currentBeta(newInactive) = 0;	// make sure coefficient is 0
  			}
  			m = inactive.size();	// update number of inactive variables
  			// drop variables from active set and sign vector
  			// number of active variables is already updated above
  			active.remove(drops);
  			signs.remove(drops);
  		}
  	}

  	// interpolate coefficients for given lambda
    if(k == 0) {
      // lambda larger than largest lambda from steps of LARS algorithm
  		beta.setZero();
    } else {
    	// penalty parameter within two steps
      if(k == maxActive) {
          // current coefficients are the least squares solution (in the 
          // high-dimensional case, as far along the solution path as possible)
          // current and previous values of the penalty parameter need to be 
          // reset for interpolation
          previousLambda = currentLambda;
          currentLambda = 0;
      }
      // interpolate coefficients
    	beta = ((rescaledLambda - currentLambda) * previousBeta +
  				(previousLambda - rescaledLambda) * currentBeta) /
  				(previousLambda - currentLambda);
    }
  }

	// transform coefficients back
  VectorXd normedBeta;
	if(normalize) {
    if(useCrit) normedBeta = beta;
    for(int j = 0; j < p; j++) beta(j) /= normX(j);
	}
	if(useIntercept) intercept = meanY - beta.dot(meanX);

  // compute residuals for all observations
  n = x.rows();
  residuals = y - x * beta;
  if(useIntercept) {
    for(int i = 0; i < n; i++) residuals(i) -= intercept;
  }

  // compute value of objective function on the subset
  if(useCrit && useSubset) {
    if(normalize) crit = objective(normedBeta, residuals, subset, lambda);
    else crit = objective(beta, residuals, subset, lambda);
  }
}