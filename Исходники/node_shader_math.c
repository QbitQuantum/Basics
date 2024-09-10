static void node_shader_exec_math(void *UNUSED(data), int UNUSED(thread), bNode *node, bNodeExecData *UNUSED(execdata), bNodeStack **in, bNodeStack **out) 
{
	float a, b, r = 0.0f;
	
	nodestack_get_vec(&a, SOCK_FLOAT, in[0]);
	nodestack_get_vec(&b, SOCK_FLOAT, in[1]);
	
	switch (node->custom1) {
	
		case 0: /* Add */
			r = a + b;
			break;
		case 1: /* Subtract */
			r = a - b;
			break;
		case 2: /* Multiply */
			r = a * b;
			break;
		case 3: /* Divide */
		{
			if (b == 0) /* We don't want to divide by zero. */
				r = 0.0;
			else
				r = a / b;
			break;
		}
		case 4: /* Sine */
		{
			if (in[0]->hasinput || !in[1]->hasinput)  /* This one only takes one input, so we've got to choose. */
				r = sinf(a);
			else
				r = sinf(b);
			break;
		}
		case 5: /* Cosine */
		{
			if (in[0]->hasinput || !in[1]->hasinput)  /* This one only takes one input, so we've got to choose. */
				r = cosf(a);
			else
				r = cosf(b);
			break;
		}
		case 6: /* Tangent */
		{
			if (in[0]->hasinput || !in[1]->hasinput)  /* This one only takes one input, so we've got to choose. */
				r = tanf(a);
			else
				r = tanf(b);
			break;
		}
		case 7: /* Arc-Sine */
		{
			if (in[0]->hasinput || !in[1]->hasinput) { /* This one only takes one input, so we've got to choose. */
				/* Can't do the impossible... */
				if (a <= 1 && a >= -1)
					r = asinf(a);
				else
					r = 0.0;
			}
			else {
				/* Can't do the impossible... */
				if (b <= 1 && b >= -1)
					r = asinf(b);
				else
					r = 0.0;
			}
			break;
		}
		case 8: /* Arc-Cosine */
		{
			if (in[0]->hasinput || !in[1]->hasinput) { /* This one only takes one input, so we've got to choose. */
				/* Can't do the impossible... */
				if (a <= 1 && a >= -1)
					r = acosf(a);
				else
					r = 0.0;
			}
			else {
				/* Can't do the impossible... */
				if (b <= 1 && b >= -1)
					r = acosf(b);
				else
					r = 0.0;
			}
			break;
		}
		case 9: /* Arc-Tangent */
		{
			if (in[0]->hasinput || !in[1]->hasinput) /* This one only takes one input, so we've got to choose. */
				r = atan(a);
			else
				r = atan(b);
			break;
		}
		case 10: /* Power */
		{
			/* Only raise negative numbers by full integers */
			if (a >= 0) {
				r = pow(a, b);
			}
			else {
				float y_mod_1 = fabsf(fmodf(b, 1.0f));
				
				/* if input value is not nearly an integer, fall back to zero, nicer than straight rounding */
				if (y_mod_1 > 0.999f || y_mod_1 < 0.001f) {
					r = powf(a, floorf(b + 0.5f));
				}
				else {
					r = 0.0f;
				}
			}

			break;
		}
		case 11: /* Logarithm */
		{
			/* Don't want any imaginary numbers... */
			if (a > 0  && b > 0)
				r = log(a) / log(b);
			else
				r = 0.0;
			break;
		}
		case 12: /* Minimum */
		{
			if (a < b)
				r = a;
			else
				r = b;
			break;
		}
		case 13: /* Maximum */
		{
			if (a > b)
				r = a;
			else
				r = b;
			break;
		}
		case 14: /* Round */
		{
			if (in[0]->hasinput || !in[1]->hasinput) /* This one only takes one input, so we've got to choose. */
				r = (a < 0) ? (int)(a - 0.5f) : (int)(a + 0.5f);
			else
				r = (b < 0) ? (int)(b - 0.5f) : (int)(b + 0.5f);
			break;
		}
		case 15: /* Less Than */
		{
			if (a < b)
				r = 1.0f;
			else
				r = 0.0f;
			break;
		}
		case 16: /* Greater Than */
		{
			if (a > b)
				r = 1.0f;
			else
				r = 0.0f;
			break;
		}
		case 17: /* Modulo */
		{
			if (b == 0.0f)
				r = 0.0f;
			else
				r = fmod(a, b);
			break;
		}
		case 18: /* Absolute */
		{
			r = fabsf(a);
			break;
		}
	}
	
	out[0]->vec[0] = r;
}