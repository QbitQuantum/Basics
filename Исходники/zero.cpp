double FindZero (double t1, double t2, double (*function)(double), double tol)
{
    double a, b, c, s, fa, fb, fc, fs, e, g, h, y,  fg, fy;

    if (tol <= 0) Matpack.Error(Mat::ArgumentDomain,
				"FindZero: Tolerance must be positve");

    a = t1;
    b = t2;

    fa = function(a);
    fb = function(b);

    c = a;
    fc = fa;
    s = c;
    fs = fc;

    for (;;) {

	h = (b + c) * 0.5;
	if (fabs(h - b) <= tol) return h;
	
	if (fabs(fb) <= fabs(fc)) {
	    y = s;
	    fy = fs;
	    g = c;
	    fg = fc;
	    s = b;
	    fs = fb;
	} else { 
	    y = b;
	    fy = fb;
	    g = b;
	    fg = fb;
	    s = c;
	    fs = fc;
	}
	
	if (fy != fs) {    
	    e = (s * fy - y * fs) / (fy - fs);
	    if (fabs(e-s) <= tol) e = s + CopySign(tol,g-s);
	    b = ((e - h) * (s - e) < 0.0) ? h : e;
	} else
	    b = h;

	// call function
	fb = function(b);
	
	if (fg * fb < 0.0) {  
	    c = g;
	    fc = fg;
	} else {
	    c = s;
	    fc = fs;
	}
    }
}