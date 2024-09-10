void coefficient_lcm(const lp_polynomial_context_t* ctx, coefficient_t* lcm, const coefficient_t* C1, const coefficient_t* C2) {
  TRACE("coefficient", "coefficient_lcm()\n");
  STAT(coefficient, lcm) ++;

  if (trace_is_enabled("coefficient")) {
    tracef("C1 = "); coefficient_print(ctx, C1, trace_out); tracef("\n");
    tracef("C2 = "); coefficient_print(ctx, C2, trace_out); tracef("\n");
  }

  assert(ctx->K == lp_Z);

  if (C1->type == COEFFICIENT_NUMERIC && C2->type == COEFFICIENT_NUMERIC) {
    // Integer LCM
    if (lcm->type == COEFFICIENT_POLYNOMIAL) {
      coefficient_destruct(lcm);
      coefficient_construct(ctx, lcm);
    }
    integer_lcm_Z(&lcm->value.num, &C1->value.num, &C2->value.num);
  } else {
    // LCM(C1, C2) = C1*C2/GCD(C1, C2)
    coefficient_t gcd;
    coefficient_construct(ctx, &gcd);
    coefficient_gcd(ctx, &gcd, C1, C2);
    if (coefficient_is_one(ctx, &gcd)) {
      coefficient_mul(ctx, lcm, C1, C2);
    } else {
      if (coefficient_cmp_type(ctx, C1, C2) <= 0) {
        coefficient_div(ctx, lcm, C1, &gcd);
        coefficient_mul(ctx, lcm, lcm, C2);
      } else {
        coefficient_div(ctx, lcm, C2, &gcd);
        coefficient_mul(ctx, lcm, lcm, C1);
      }
    }
    if (coefficient_lc_sgn(ctx, lcm) < 0) {
      coefficient_neg(ctx, lcm, lcm);
    }
    coefficient_destruct(&gcd);
  }

  if (trace_is_enabled("coefficient")) {
    tracef("coefficient_lcm() => "); coefficient_print(ctx, lcm, trace_out); tracef("\n");
  }

  assert(coefficient_is_normalized(ctx, lcm));
}