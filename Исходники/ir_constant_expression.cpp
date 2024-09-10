ir_constant* ir_expression::constant_expression_value()
{
	if (this->type->is_error())
	{
		return NULL;
	}

	ir_constant* op[Elements(this->operands)] = { NULL, };
	ir_constant_data data;

	memset(&data, 0, sizeof(data));

	for (unsigned operand = 0; operand < this->get_num_operands(); operand++)
	{
		op[operand] = this->operands[operand]->constant_expression_value();
		if (!op[operand])
		{
			return NULL;
		}
	}

	check(op[0]);
	if (op[1] != NULL)
	{
		check(op[0]->type->base_type == op[1]->type->base_type ||
			this->operation == ir_binop_lshift ||
			this->operation == ir_binop_rshift);
	}

	bool op0_scalar = op[0]->type->is_scalar();
	bool op1_scalar = op[1] != NULL && op[1]->type->is_scalar();

	bool op2_scalar = op[2] ? op[2]->type->is_scalar() : false;
	unsigned c2_inc = op2_scalar ? 0 : 1;

	/* When iterating over a vector or matrix's components, we want to increase
	* the loop counter.  However, for scalars, we want to stay at 0.
	*/
	unsigned c0_inc = op0_scalar ? 0 : 1;
	unsigned c1_inc = op1_scalar ? 0 : 1;
	unsigned components;
	if (op1_scalar || !op[1])
	{
		components = op[0]->type->components();
	}
	else
	{
		components = op[1]->type->components();
	}

	void *ctx = ralloc_parent(this);

	/* Handle array operations here, rather than below. */
	if (op[0]->type->is_array())
	{
		check(op[1] != NULL && op[1]->type->is_array());
		switch (this->operation)
		{
		case ir_binop_all_equal:
			return new(ctx)ir_constant(op[0]->has_value(op[1]));
		case ir_binop_any_nequal:
			return new(ctx)ir_constant(!op[0]->has_value(op[1]));
		default:
			break;
		}
		return NULL;
	}

	switch (this->operation)
	{
	case ir_unop_bit_not:
		switch (op[0]->type->base_type)
		{
		case GLSL_TYPE_INT:
			for (unsigned c = 0; c < components; c++)
			{
				data.i[c] = ~op[0]->value.i[c];
			}
			break;
		case GLSL_TYPE_UINT:
			for (unsigned c = 0; c < components; c++)
			{
				data.u[c] = ~op[0]->value.u[c];
			}
			break;
		default:
			check(0);
		}
		break;

	case ir_unop_logic_not:
		check(op[0]->type->base_type == GLSL_TYPE_BOOL);
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.b[c] = !op[0]->value.b[c];
		}
		break;

	case ir_unop_h2i:
		check(op[0]->type->base_type == GLSL_TYPE_HALF);
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.i[c] = (int)op[0]->value.f[c];
		}
		break;
	case ir_unop_f2i:
		check(op[0]->type->base_type == GLSL_TYPE_FLOAT);
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.i[c] = (int)op[0]->value.f[c];
		}
		break;
	case ir_unop_i2f:
	case ir_unop_i2h:
		check(op[0]->type->base_type == GLSL_TYPE_INT);
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = (float)op[0]->value.i[c];
		}
		break;
	case ir_unop_u2h:
	case ir_unop_u2f:
		check(op[0]->type->base_type == GLSL_TYPE_UINT);
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = (float)op[0]->value.u[c];
		}
		break;
	case ir_unop_f2h:
		check(op[0]->type->base_type == GLSL_TYPE_FLOAT);
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = op[0]->value.f[c];
		}
		break;
	case ir_unop_f2u:
		check(op[0]->type->base_type == GLSL_TYPE_FLOAT);
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.u[c] = (unsigned)op[0]->value.f[c];
		}
		break;
	case ir_unop_b2h:
	case ir_unop_b2f:
		check(op[0]->type->base_type == GLSL_TYPE_BOOL);
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = op[0]->value.b[c] ? 1.0F : 0.0F;
		}
		break;
	case ir_unop_h2b:
		check(op[0]->type->base_type == GLSL_TYPE_HALF);
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.b[c] = op[0]->value.f[c] != 0.0F ? true : false;
		}
		break;
	case ir_unop_f2b:
		check(op[0]->type->base_type == GLSL_TYPE_FLOAT);
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.b[c] = op[0]->value.f[c] != 0.0F ? true : false;
		}
		break;
	case ir_unop_b2i:
		check(op[0]->type->base_type == GLSL_TYPE_BOOL);
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.u[c] = op[0]->value.b[c] ? 1 : 0;
		}
		break;
	case ir_unop_i2b:
		check(op[0]->type->is_integer());
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.b[c] = op[0]->value.u[c] ? true : false;
		}
		break;
	case ir_unop_u2i:
		check(op[0]->type->base_type == GLSL_TYPE_UINT);
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.i[c] = op[0]->value.u[c];
		}
		break;
	case ir_unop_i2u:
		check(op[0]->type->base_type == GLSL_TYPE_INT);
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.u[c] = op[0]->value.i[c];
		}
		break;
	case ir_unop_b2u:
		check(op[0]->type->base_type == GLSL_TYPE_BOOL);
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.u[c] = (unsigned)op[0]->value.b[c];
		}
		break;
	case ir_unop_u2b:
		check(op[0]->type->base_type == GLSL_TYPE_UINT);
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.b[c] = (bool)op[0]->value.u[c];
		}
		break;
	case ir_unop_any:
		check(op[0]->type->is_boolean());
		data.b[0] = false;
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			if (op[0]->value.b[c])
			{
				data.b[0] = true;
			}
		}
		break;

	case ir_unop_all:
		check(op[0]->type->is_boolean());
		data.b[0] = true;
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			if (op[0]->value.b[c] == false)
			{
				data.b[0] = false;
			}
		}
		break;

	case ir_unop_trunc:
		check(op[0]->type->is_float());
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = truncf(op[0]->value.f[c]);
		}
		break;

	case ir_unop_round:
		check(op[0]->type->is_float());
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = (float)(IROUND(op[0]->value.f[c]));
		}
		break;

	case ir_unop_ceil:
		check(op[0]->type->is_float());
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = ceilf(op[0]->value.f[c]);
		}
		break;

	case ir_unop_floor:
		check(op[0]->type->is_float());
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = floorf(op[0]->value.f[c]);
		}
		break;

	case ir_unop_fract:
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			switch (this->type->base_type)
			{
			case GLSL_TYPE_UINT:
				data.u[c] = 0;
				break;
			case GLSL_TYPE_INT:
				data.i[c] = 0;
				break;
			case GLSL_TYPE_HALF:
			case GLSL_TYPE_FLOAT:
				data.f[c] = op[0]->value.f[c] - floor(op[0]->value.f[c]);
				break;
			default:
				check(0);
			}
		}
		break;

	case ir_unop_sin:
		check(op[0]->type->is_float());
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = sinf(op[0]->value.f[c]);
		}
		break;

	case ir_unop_cos:
		check(op[0]->type->is_float());
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = cosf(op[0]->value.f[c]);
		}
		break;

	case ir_unop_tan:
		check(op[0]->type->is_float());
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = tanf(op[0]->value.f[c]);
		}
		break;

	case ir_unop_asin:
		check(op[0]->type->is_float());
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = asinf(op[0]->value.f[c]);
		}
		break;

	case ir_unop_acos:
		check(op[0]->type->is_float());
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = acosf(op[0]->value.f[c]);
		}
		break;

	case ir_unop_atan:
		check(op[0]->type->is_float());
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = atanf(op[0]->value.f[c]);
		}
		break;

	case ir_unop_sinh:
		check(op[0]->type->is_float());
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = sinhf(op[0]->value.f[c]);
		}
		break;

	case ir_unop_cosh:
		check(op[0]->type->is_float());
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = coshf(op[0]->value.f[c]);
		}
		break;

	case ir_unop_tanh:
		check(op[0]->type->is_float());
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = tanhf(op[0]->value.f[c]);
		}
		break;

	case ir_unop_neg:
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			switch (this->type->base_type)
			{
			case GLSL_TYPE_UINT:
				data.u[c] = -((int)op[0]->value.u[c]);
				break;
			case GLSL_TYPE_INT:
				data.i[c] = -op[0]->value.i[c];
				break;
			case GLSL_TYPE_HALF:
			case GLSL_TYPE_FLOAT:
				data.f[c] = -op[0]->value.f[c];
				break;
			default:
				check(0);
			}
		}
		break;

	case ir_unop_abs:
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			switch (this->type->base_type)
			{
			case GLSL_TYPE_UINT:
				data.u[c] = op[0]->value.u[c];
				break;
			case GLSL_TYPE_INT:
				data.i[c] = op[0]->value.i[c];
				if (data.i[c] < 0)
				{
					data.i[c] = -data.i[c];
				}
				break;
			case GLSL_TYPE_HALF:
			case GLSL_TYPE_FLOAT:
				data.f[c] = fabs(op[0]->value.f[c]);
				break;
			default:
				check(0);
			}
		}
		break;

	case ir_unop_sign:
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			switch (this->type->base_type)
			{
			case GLSL_TYPE_UINT:
				data.u[c] = op[0]->value.i[c] > 0;
				break;
			case GLSL_TYPE_INT:
				data.i[c] = (op[0]->value.i[c] > 0) - (op[0]->value.i[c] < 0);
				break;
			case GLSL_TYPE_HALF:
			case GLSL_TYPE_FLOAT:
				data.f[c] = float((op[0]->value.f[c] > 0) - (op[0]->value.f[c] < 0));
				break;
			default:
				check(0);
			}
		}
		break;

	case ir_unop_rcp:
		check(op[0]->type->is_float());
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			switch (this->type->base_type)
			{
			case GLSL_TYPE_UINT:
				if (op[0]->value.u[c] != 0.0)
				{
					data.u[c] = 1 / op[0]->value.u[c];
				}
				break;
			case GLSL_TYPE_INT:
				if (op[0]->value.i[c] != 0.0)
				{
					data.i[c] = 1 / op[0]->value.i[c];
				}
				break;
			case GLSL_TYPE_HALF:
			case GLSL_TYPE_FLOAT:
				if (op[0]->value.f[c] != 0.0)
				{
					data.f[c] = 1.0F / op[0]->value.f[c];
				}
				break;
			default:
				check(0);
			}
		}
		break;

	case ir_unop_rsq:
		check(op[0]->type->is_float());
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = 1.0F / sqrtf(op[0]->value.f[c]);
		}
		break;

	case ir_unop_sqrt:
		check(op[0]->type->is_float());
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = sqrtf(op[0]->value.f[c]);
		}
		break;

	case ir_unop_exp:
		check(op[0]->type->is_float());
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = expf(op[0]->value.f[c]);
		}
		break;

	case ir_unop_exp2:
		check(op[0]->type->is_float());
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = exp2f(op[0]->value.f[c]);
		}
		break;

	case ir_unop_log:
		check(op[0]->type->is_float());
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = logf(op[0]->value.f[c]);
		}
		break;

	case ir_unop_log2:
		check(op[0]->type->is_float());
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = log2f(op[0]->value.f[c]);
		}
		break;

	case ir_unop_normalize:
		check(op[0]->type->is_float());
		{
			float mag = 0.0f;
			for (unsigned c = 0; c < op[0]->type->components(); c++)
			{
				mag += op[0]->value.f[c] * op[0]->value.f[c];
			}
			mag = sqrtf(mag);
			for (unsigned c = 0; c < op[0]->type->components(); c++)
			{
				data.f[c] = op[0]->value.f[c] / mag;
			}
		}
		break;

	case ir_unop_dFdx:
	case ir_unop_dFdy:
		check(op[0]->type->is_float());
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = 0.0;
		}
		break;

	case ir_binop_pow:
		check(op[0]->type->is_float());
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = powf(op[0]->value.f[c], op[1]->value.f[c]);
		}
		break;

	case ir_binop_atan2:
		check(op[0]->type->is_float());
		check(op[1] && op[1]->type->base_type == op[0]->type->base_type);
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			data.f[c] = atan2f(op[0]->value.f[c], op[1]->value.f[c]);
		}
		break;

	case ir_binop_cross:
		check(op[0]->type == glsl_type::vec3_type || op[0]->type == glsl_type::half3_type);
		check(op[1] && (op[1]->type == glsl_type::vec3_type || op[1]->type == glsl_type::half3_type));
		data.f[0] = (op[0]->value.f[1] * op[1]->value.f[2]) - (op[0]->value.f[2] * op[1]->value.f[1]);
		data.f[1] = (op[0]->value.f[2] * op[1]->value.f[0]) - (op[0]->value.f[0] * op[1]->value.f[2]);
		data.f[2] = (op[0]->value.f[0] * op[1]->value.f[1]) - (op[0]->value.f[1] * op[1]->value.f[0]);
		break;

	case ir_binop_dot:
		data.f[0] = dot(op[0], op[1]);
		break;

	case ir_binop_min:
		check(op[1]);
		check(op[0]->type == op[1]->type || op0_scalar || op1_scalar);
		for (unsigned c = 0, c0 = 0, c1 = 0;
			c < components;
			c0 += c0_inc, c1 += c1_inc, c++)
		{
			switch (op[0]->type->base_type)
			{
			case GLSL_TYPE_UINT:
				data.u[c] = MIN2(op[0]->value.u[c0], op[1]->value.u[c1]);
				break;
			case GLSL_TYPE_INT:
				data.i[c] = MIN2(op[0]->value.i[c0], op[1]->value.i[c1]);
				break;
			case GLSL_TYPE_HALF:
			case GLSL_TYPE_FLOAT:
				data.f[c] = MIN2(op[0]->value.f[c0], op[1]->value.f[c1]);
				break;
			default:
				check(0);
			}
		}

		break;
	case ir_binop_max:
		check(op[1]);
		check(op[0]->type == op[1]->type || op0_scalar || op1_scalar);
		for (unsigned c = 0, c0 = 0, c1 = 0;
			c < components;
			c0 += c0_inc, c1 += c1_inc, c++)
		{
			switch (op[0]->type->base_type)
			{
			case GLSL_TYPE_UINT:
				data.u[c] = MAX2(op[0]->value.u[c0], op[1]->value.u[c1]);
				break;
			case GLSL_TYPE_INT:
				data.i[c] = MAX2(op[0]->value.i[c0], op[1]->value.i[c1]);
				break;
			case GLSL_TYPE_HALF:
			case GLSL_TYPE_FLOAT:
				data.f[c] = MAX2(op[0]->value.f[c0], op[1]->value.f[c1]);
				break;
			default:
				check(0);
			}
		}
		break;

	case ir_binop_add:
		check(op[1]);
		check(op[0]->type == op[1]->type || op0_scalar || op1_scalar);
		for (unsigned c = 0, c0 = 0, c1 = 0;
			c < components;
			c0 += c0_inc, c1 += c1_inc, c++)
		{
			switch (op[0]->type->base_type)
			{
			case GLSL_TYPE_UINT:
				data.u[c] = op[0]->value.u[c0] + op[1]->value.u[c1];
				break;
			case GLSL_TYPE_INT:
				data.i[c] = op[0]->value.i[c0] + op[1]->value.i[c1];
				break;
			case GLSL_TYPE_HALF:
			case GLSL_TYPE_FLOAT:
				data.f[c] = op[0]->value.f[c0] + op[1]->value.f[c1];
				break;
			default:
				check(0);
			}
		}

		break;
	case ir_binop_sub:
		check(op[1]);
		check(op[0]->type == op[1]->type || op0_scalar || op1_scalar);
		for (unsigned c = 0, c0 = 0, c1 = 0;
			c < components;
			c0 += c0_inc, c1 += c1_inc, c++)
		{
			switch (op[0]->type->base_type)
			{
			case GLSL_TYPE_UINT:
				data.u[c] = op[0]->value.u[c0] - op[1]->value.u[c1];
				break;
			case GLSL_TYPE_INT:
				data.i[c] = op[0]->value.i[c0] - op[1]->value.i[c1];
				break;
			case GLSL_TYPE_HALF:
			case GLSL_TYPE_FLOAT:
				data.f[c] = op[0]->value.f[c0] - op[1]->value.f[c1];
				break;
			default:
				check(0);
			}
		}

		break;
	case ir_binop_mul:
		/* Check for equal types, or unequal types involving scalars */
		check(op[1]);
		if ((op[0]->type == op[1]->type) || op0_scalar || op1_scalar)
		{
			for (unsigned c = 0, c0 = 0, c1 = 0;
				c < components;
				c0 += c0_inc, c1 += c1_inc, c++)
			{
				switch (op[0]->type->base_type)
				{
				case GLSL_TYPE_UINT:
					data.u[c] = op[0]->value.u[c0] * op[1]->value.u[c1];
					break;
				case GLSL_TYPE_INT:
					data.i[c] = op[0]->value.i[c0] * op[1]->value.i[c1];
					break;
				case GLSL_TYPE_HALF:
				case GLSL_TYPE_FLOAT:
					data.f[c] = op[0]->value.f[c0] * op[1]->value.f[c1];
					break;
				default:
					check(0);
				}
			}
		}
		break;
	case ir_binop_div:
		/* FINISHME: Emit warning when division-by-zero is detected. */
		check(op[1]);
		check(op[0]->type == op[1]->type || op0_scalar || op1_scalar);
		for (unsigned c = 0, c0 = 0, c1 = 0;
			c < components;
			c0 += c0_inc, c1 += c1_inc, c++)
		{

			switch (op[0]->type->base_type)
			{
			case GLSL_TYPE_UINT:
				if (op[1]->value.u[c1] == 0)
				{
					data.u[c] = 0;
				}
				else
				{
					data.u[c] = op[0]->value.u[c0] / op[1]->value.u[c1];
				}
				break;
			case GLSL_TYPE_INT:
				if (op[1]->value.i[c1] == 0)
				{
					data.i[c] = 0;
				}
				else
				{
					data.i[c] = op[0]->value.i[c0] / op[1]->value.i[c1];
				}
				break;
			case GLSL_TYPE_HALF:
			case GLSL_TYPE_FLOAT:
				data.f[c] = op[0]->value.f[c0] / op[1]->value.f[c1];
				break;
			default:
				check(0);
			}
		}

		break;
	case ir_binop_mod:
		/* FINISHME: Emit warning when division-by-zero is detected. */
		check(op[1]);
		check(op[0]->type == op[1]->type || op0_scalar || op1_scalar);
		for (unsigned c = 0, c0 = 0, c1 = 0;
			c < components;
			c0 += c0_inc, c1 += c1_inc, c++)
		{
			switch (op[0]->type->base_type)
			{
			case GLSL_TYPE_UINT:
				if (op[1]->value.u[c1] == 0)
				{
					data.u[c] = 0;
				}
				else
				{
					data.u[c] = op[0]->value.u[c0] % op[1]->value.u[c1];
				}
				break;
			case GLSL_TYPE_INT:
				if (op[1]->value.i[c1] == 0)
				{
					data.i[c] = 0;
				}
				else
				{
					data.i[c] = op[0]->value.i[c0] % op[1]->value.i[c1];
				}
				break;
			case GLSL_TYPE_HALF:
			case GLSL_TYPE_FLOAT:
				/* We don't use fmod because it rounds toward zero; GLSL specifies
				* the use of floor.
				*/
				data.f[c] = op[0]->value.f[c0] - op[1]->value.f[c1]
					* floorf(op[0]->value.f[c0] / op[1]->value.f[c1]);
				break;
			default:
				check(0);
			}
		}

		break;

	case ir_binop_logic_and:
		check(op[1]);
		check(op[0]->type->base_type == GLSL_TYPE_BOOL);
		for (unsigned c = 0; c < op[0]->type->components(); c++)
			data.b[c] = op[0]->value.b[c] && op[1]->value.b[c];
		break;
	case ir_binop_logic_xor:
		check(op[0]->type->base_type == GLSL_TYPE_BOOL);
		for (unsigned c = 0; c < op[0]->type->components(); c++)
			data.b[c] = op[0]->value.b[c] ^ op[1]->value.b[c];
		break;
	case ir_binop_logic_or:
		check(op[0]->type->base_type == GLSL_TYPE_BOOL);
		for (unsigned c = 0; c < op[0]->type->components(); c++)
			data.b[c] = op[0]->value.b[c] || op[1]->value.b[c];
		break;

	case ir_binop_less:
		check(op[1]);
		check(op[0]->type == op[1]->type);
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			switch (op[0]->type->base_type)
			{
			case GLSL_TYPE_UINT:
				data.b[0] = op[0]->value.u[0] < op[1]->value.u[0];
				break;
			case GLSL_TYPE_INT:
				data.b[0] = op[0]->value.i[0] < op[1]->value.i[0];
				break;
			case GLSL_TYPE_HALF:
			case GLSL_TYPE_FLOAT:
				data.b[0] = op[0]->value.f[0] < op[1]->value.f[0];
				break;
			default:
				check(0);
			}
		}
		break;
	case ir_binop_greater:
		check(op[1]);
		check(op[0]->type == op[1]->type);
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			switch (op[0]->type->base_type)
			{
			case GLSL_TYPE_UINT:
				data.b[c] = op[0]->value.u[c] > op[1]->value.u[c];
				break;
			case GLSL_TYPE_INT:
				data.b[c] = op[0]->value.i[c] > op[1]->value.i[c];
				break;
			case GLSL_TYPE_HALF:
			case GLSL_TYPE_FLOAT:
				data.b[c] = op[0]->value.f[c] > op[1]->value.f[c];
				break;
			default:
				check(0);
			}
		}
		break;
	case ir_binop_lequal:
		check(op[1]);
		check(op[0]->type == op[1]->type);
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			switch (op[0]->type->base_type)
			{
			case GLSL_TYPE_UINT:
				data.b[0] = op[0]->value.u[0] <= op[1]->value.u[0];
				break;
			case GLSL_TYPE_INT:
				data.b[0] = op[0]->value.i[0] <= op[1]->value.i[0];
				break;
			case GLSL_TYPE_HALF:
			case GLSL_TYPE_FLOAT:
				data.b[0] = op[0]->value.f[0] <= op[1]->value.f[0];
				break;
			default:
				check(0);
			}
		}
		break;
	case ir_binop_gequal:
		check(op[1]);
		check(op[0]->type == op[1]->type);
		for (unsigned c = 0; c < op[0]->type->components(); c++)
		{
			switch (op[0]->type->base_type)
			{
			case GLSL_TYPE_UINT:
				data.b[0] = op[0]->value.u[0] >= op[1]->value.u[0];
				break;
			case GLSL_TYPE_INT:
				data.b[0] = op[0]->value.i[0] >= op[1]->value.i[0];
				break;
			case GLSL_TYPE_HALF:
			case GLSL_TYPE_FLOAT:
				data.b[0] = op[0]->value.f[0] >= op[1]->value.f[0];
				break;
			default:
				check(0);
			}
		}
		break;
	case ir_binop_equal:
		check(op[1]);
		check(op[0]->type == op[1]->type);
		for (unsigned c = 0; c < components; c++)
		{
			switch (op[0]->type->base_type)
			{
			case GLSL_TYPE_UINT:
				data.b[c] = op[0]->value.u[c] == op[1]->value.u[c];
				break;
			case GLSL_TYPE_INT:
				data.b[c] = op[0]->value.i[c] == op[1]->value.i[c];
				break;
			case GLSL_TYPE_HALF:
			case GLSL_TYPE_FLOAT:
				data.b[c] = op[0]->value.f[c] == op[1]->value.f[c];
				break;
			case GLSL_TYPE_BOOL:
				data.b[c] = op[0]->value.b[c] == op[1]->value.b[c];
				break;
			default:
				check(0);
			}
		}
		break;
	case ir_binop_nequal:
		check(op[1]);
		check(op[0]->type == op[1]->type);
		for (unsigned c = 0; c < components; c++)
		{
			switch (op[0]->type->base_type)
			{
			case GLSL_TYPE_UINT:
				data.b[c] = op[0]->value.u[c] != op[1]->value.u[c];
				break;
			case GLSL_TYPE_INT:
				data.b[c] = op[0]->value.i[c] != op[1]->value.i[c];
				break;
			case GLSL_TYPE_HALF:
			case GLSL_TYPE_FLOAT:
				data.b[c] = op[0]->value.f[c] != op[1]->value.f[c];
				break;
			case GLSL_TYPE_BOOL:
				data.b[c] = op[0]->value.b[c] != op[1]->value.b[c];
				break;
			default:
				check(0);
			}
		}
		break;
	case ir_binop_all_equal:
		check(op[1]);
		data.b[0] = op[0]->has_value(op[1]);
		break;
	case ir_binop_any_nequal:
		check(op[1]);
		data.b[0] = !op[0]->has_value(op[1]);
		break;

	case ir_binop_lshift:
		for (unsigned c = 0, c0 = 0, c1 = 0;
			c < components;
			c0 += c0_inc, c1 += c1_inc, c++)
		{

			check(op[1]);
			if (op[0]->type->base_type == GLSL_TYPE_INT &&
				op[1]->type->base_type == GLSL_TYPE_INT)
			{
				data.i[c] = op[0]->value.i[c0] << op[1]->value.i[c1];

			}
			else if (op[0]->type->base_type == GLSL_TYPE_INT &&
				op[1]->type->base_type == GLSL_TYPE_UINT)
			{
				data.i[c] = op[0]->value.i[c0] << op[1]->value.u[c1];

			}
			else if (op[0]->type->base_type == GLSL_TYPE_UINT &&
				op[1]->type->base_type == GLSL_TYPE_INT)
			{
				data.u[c] = op[0]->value.u[c0] << op[1]->value.i[c1];

			}
			else if (op[0]->type->base_type == GLSL_TYPE_UINT &&
				op[1]->type->base_type == GLSL_TYPE_UINT)
			{
				data.u[c] = op[0]->value.u[c0] << op[1]->value.u[c1];
			}
		}
		break;

	case ir_binop_rshift:
		for (unsigned c = 0, c0 = 0, c1 = 0;
			c < components;
			c0 += c0_inc, c1 += c1_inc, c++)
		{
			check(op[1]);
			if (op[0]->type->base_type == GLSL_TYPE_INT &&
				op[1]->type->base_type == GLSL_TYPE_INT)
			{
				data.i[c] = op[0]->value.i[c0] >> op[1]->value.i[c1];
			}
			else if (op[0]->type->base_type == GLSL_TYPE_INT &&
				op[1]->type->base_type == GLSL_TYPE_UINT)
			{
				data.i[c] = op[0]->value.i[c0] >> op[1]->value.u[c1];

			}