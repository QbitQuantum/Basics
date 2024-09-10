/* .External */
SEXP ocl_call(SEXP args) {
    struct arg_chain *float_args = 0;
    ocl_call_context_t *occ;
    int on, an = 0, ftype = FT_DOUBLE, ftsize, ftres, async;
    SEXP ker = CADR(args), olen, arg, res, octx, dimVec;
    cl_kernel kernel = getKernel(ker);
    cl_context context;
    cl_command_queue commands;
    cl_device_id device_id = getDeviceID(getAttrib(ker, Rf_install("device")));
    cl_mem output;
    cl_int err;
    size_t wdims[3] = {0, 0, 0};
    int wdim = 1;

    if (clGetKernelInfo(kernel, CL_KERNEL_CONTEXT, sizeof(context), &context, NULL) != CL_SUCCESS || !context)
	Rf_error("cannot obtain kernel context via clGetKernelInfo");
    args = CDDR(args);
    res = Rf_getAttrib(ker, install("precision"));
    if (TYPEOF(res) == STRSXP && LENGTH(res) == 1 && CHAR(STRING_ELT(res, 0))[0] != 'd')
	ftype = FT_SINGLE;
    ftsize = (ftype == FT_DOUBLE) ? sizeof(double) : sizeof(float);
    olen = CAR(args);  /* size */
    args = CDR(args);
    on = Rf_asInteger(olen);
    if (on < 0)
	Rf_error("invalid output length");
    ftres = (Rf_asInteger(CAR(args)) == 1) ? 1 : 0;  /* native.result */
    if (ftype != FT_SINGLE) ftres = 0;
    args = CDR(args);
    async = (Rf_asInteger(CAR(args)) == 1) ? 0 : 1;  /* wait */
    args = CDR(args);
    dimVec = coerceVector(CAR(args), INTSXP);  /* dim */
    wdim = LENGTH(dimVec);
    if (wdim > 3)
	Rf_error("OpenCL standard only supports up to three work item dimensions - use index vectors for higher dimensions");
    if (wdim) {
	int i; /* we don't use memcpy in case int and size_t are different */
	for (i = 0; i < wdim; i++)
	    wdims[i] = INTEGER(dimVec)[i];
    }
    if (wdim < 1 || wdims[0] < 1 || (wdim > 1 && wdims[1] < 1) || (wdim > 2 && wdims[2] < 1))
	Rf_error("invalid dimensions - muse be a numeric vector with positive values");

    args = CDR(args);
    occ = (ocl_call_context_t*) calloc(1, sizeof(ocl_call_context_t));
    if (!occ) Rf_error("unable to allocate ocl_call context");
    octx = PROTECT(R_MakeExternalPtr(occ, R_NilValue, R_NilValue));
    R_RegisterCFinalizerEx(octx, ocl_call_context_fin, TRUE);

    occ->output = output = clCreateBuffer(context, CL_MEM_WRITE_ONLY, ftsize * on, NULL, &err);
    if (!output)
	Rf_error("failed to create output buffer of %d elements via clCreateBuffer (%d)", on, err);
    if (clSetKernelArg(kernel, an++, sizeof(cl_mem), &output) != CL_SUCCESS)
	Rf_error("failed to set first kernel argument as output in clSetKernelArg");
    if (clSetKernelArg(kernel, an++, sizeof(on), &on) != CL_SUCCESS)
	Rf_error("failed to set second kernel argument as output length in clSetKernelArg");
    occ->commands = commands = clCreateCommandQueue(context, device_id, 0, &err);
    if (!commands)
	ocl_err("clCreateCommandQueue");
    if (ftype == FT_SINGLE) /* need conversions, create floats buffer */
	occ->float_args = float_args = arg_alloc(0, 32);
    while ((arg = CAR(args)) != R_NilValue) {
	int n, ndiv = 1;
	void *ptr;
	size_t al;
	
	switch (TYPEOF(arg)) {
	case REALSXP:
	    if (ftype == FT_SINGLE) {
		int i;
		float *f;
		double *d = REAL(arg);
		n = LENGTH(arg);
		f = (float*) malloc(sizeof(float) * n);
		if (!f)
		    Rf_error("unable to allocate temporary single-precision memory for conversion from a double-precision argument vector of length %d", n);
		for (i = 0; i < n; i++) f[i] = d[i];
		ptr = f;
		al = sizeof(float);
		arg_add(float_args, ptr);
	    } else {
		ptr = REAL(arg);
		al = sizeof(double);
	    }
	    break;
	case INTSXP:
	    ptr = INTEGER(arg);
	    al = sizeof(int);
	    break;
	case LGLSXP:
	    ptr = LOGICAL(arg);
	    al = sizeof(int);
	    break;
	case RAWSXP:
	    if (inherits(arg, "clFloat")) {
		ptr = RAW(arg);
		ndiv = al = sizeof(float);
		break;
	    }
	default:
	    Rf_error("only numeric or logical kernel arguments are supported");
	    /* no-ops but needed to make the compiler happy */
	    ptr = 0;
	    al = 0;
	}
	n = LENGTH(arg);
	if (ndiv != 1) n /= ndiv;
	if (n == 1) {/* scalar */
	    if (clSetKernelArg(kernel, an++, al, ptr) != CL_SUCCESS)
		Rf_error("Failed to set scalar kernel argument %d (size=%d)", an, al);
	} else {
	    cl_mem input = clCreateBuffer(context,  CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR,  al * n, ptr, &err);
	    if (!input)
		Rf_error("Unable to create buffer (%d elements, %d bytes each) for vector argument %d (oclError %d)", n, al, an, err);
	    if (!occ->mem_objects)
		occ->mem_objects = arg_alloc(0, 32);
	    arg_add(occ->mem_objects, input);
#if 0 /* we used this before CL_MEM_USE_HOST_PTR */
	    if (clEnqueueWriteBuffer(commands, input, CL_TRUE, 0, al * n, ptr, 0, NULL, NULL) != CL_SUCCESS)
		Rf_error("Failed to transfer data (%d elements) for vector argument %d", n, an);
#endif
	    if (clSetKernelArg(kernel, an++, sizeof(cl_mem), &input) != CL_SUCCESS)
		Rf_error("Failed to set vector kernel argument %d (size=%d, length=%d)", an, al, n);
	    /* clReleaseMemObject(input); */
	}
	args = CDR(args);
    }

    if (clEnqueueNDRangeKernel(commands, kernel, wdim, NULL, wdims, NULL, 0, NULL, async ? &occ->event : NULL) != CL_SUCCESS)
	Rf_error("Error during kernel execution");

    if (async) { /* asynchronous call -> get out and return the context */
#if USE_OCL_COMPLETE_CALLBACK
	clSetEventCallback(occ->event, CL_COMPLETE, ocl_complete_callback, occ);
#endif
	clFlush(commands); /* the specs don't guarantee execution unless clFlush is called */
	occ->ftres = ftres;
	occ->ftype = ftype;
	occ->on = on;
	Rf_setAttrib(octx, R_ClassSymbol, mkString("clCallContext"));
	UNPROTECT(1);
	return octx;
    }

    clFinish(commands);
    occ->finished = 1;

    /* we can release input memory objects now */
    if (occ->mem_objects) {
      arg_free(occ->mem_objects, (afin_t) clReleaseMemObject);
      occ->mem_objects = 0;
    }
    if (float_args) {
      arg_free(float_args, 0);
      float_args = occ->float_args = 0;
    }

    res = ftres ? Rf_allocVector(RAWSXP, on * sizeof(float)) : Rf_allocVector(REALSXP, on);
    if (ftype == FT_SINGLE) {
	if (ftres) {
	  if ((err = clEnqueueReadBuffer( commands, output, CL_TRUE, 0, sizeof(float) * on, RAW(res), 0, NULL, NULL )) != CL_SUCCESS)
		Rf_error("Unable to transfer result vector (%d float elements, oclError %d)", on, err);
	    PROTECT(res);
	    Rf_setAttrib(res, R_ClassSymbol, mkString("clFloat"));
	    UNPROTECT(1);
	} else {
	    /* float - need a temporary buffer */
	    float *fr = (float*) malloc(sizeof(float) * on);
	    double *r = REAL(res);
	    int i;
	    if (!fr)
		Rf_error("unable to allocate memory for temporary single-precision output buffer");
	    occ->float_out = fr;
	    if ((err = clEnqueueReadBuffer( commands, output, CL_TRUE, 0, sizeof(float) * on, fr, 0, NULL, NULL )) != CL_SUCCESS)
		Rf_error("Unable to transfer result vector (%d float elements, oclError %d)", on, err);
	    for (i = 0; i < on; i++)
		r[i] = fr[i];
	}
    } else if ((err = clEnqueueReadBuffer( commands, output, CL_TRUE, 0, sizeof(double) * on, REAL(res), 0, NULL, NULL )) != CL_SUCCESS)
	Rf_error("Unable to transfer result vector (%d double elements, oclError %d)", on, err);

    ocl_call_context_fin(octx);
    UNPROTECT(1);
    return res;
}