static double nloptObjectiveFunction(unsigned n, const double *x, double *grad, void *f_data)
{
	GradientOptimizerContext *goc = (GradientOptimizerContext *) f_data;
	nlopt_opt opt = (nlopt_opt) goc->extraData;
	FitContext *fc = goc->fc;
	assert(n == fc->numParam);
	int mode = 0;
	double fit = goc->solFun((double*) x, &mode);
	if (grad) {
		fc->iterations += 1;
		if (goc->maxMajorIterations != -1 && fc->iterations >= goc->maxMajorIterations) {
			nlopt_force_stop(opt);
		}
	}
	if (grad && goc->verbose >= 2) {
		mxLog("major iteration fit=%.12f", fit);
	}
	if (mode == -1) {
		if (!goc->feasible) {
			nlopt_force_stop(opt);
		}
		return nan("infeasible");
	}
	if (!grad) return fit;

	Eigen::Map< Eigen::VectorXd > Epoint((double*) x, n);
	Eigen::Map< Eigen::VectorXd > Egrad(grad, n);
	if (fc->wanted & FF_COMPUTE_GRADIENT) {
		Egrad = fc->grad;
	} else if (fc->CI && fc->CI->varIndex >= 0) {
		Egrad.setZero();
		Egrad[fc->CI->varIndex] = fc->lowerBound? 1 : -1;
		fc->grad = Egrad;
	} else {
		if (goc->verbose >= 3) mxLog("fd_gradient start");
		fit_functional ff(*goc);
		gradient_with_ref(goc->gradientAlgo, goc->gradientIterations, goc->gradientStepSize,
				  ff, fit, Epoint, Egrad);
		fc->grad = Egrad;
	}
	if (goc->verbose >= 3) {
		mxPrintMat("gradient", Egrad);
	}
	return fit;
}