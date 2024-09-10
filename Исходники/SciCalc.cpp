void SciCalc::factorial() {
  double lg, alpha;

  /* uses gamma functions to get result for non-integer values */

	alpha = value[top] + 1.0;
	if ((floor(alpha) == alpha)&&(alpha <= 0.0))
	{
		init_value(0);
		leddisplay->label("Error: -ve integer ");
		leddisplay->redraw();
	}
	else
	if (alpha > 32)
	 {
		lg = exp(gammaln(alpha));
    		value[top] = lg;
   		 set_display(value[top],NORM);
		ready = 1;
	}
	else
	if (alpha > 1.0)
	{
		int n = (int)truncf(alpha);
		lg = 1.0;
		for (int i = 1; i <n; i++) lg *= i;
		value[top] = lg;
		set_display(value[top],NORM);
		ready = 1;
	}
}