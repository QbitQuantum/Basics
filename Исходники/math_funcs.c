static int rpn_eval(const token* t)
{
  double o1, o2;

  switch (t->type) {
  case MATHOP_NUMBER:
    return push_number(t->value);

  case MATHOP_ADD:
    return pop_number(&o2) || pop_number(&o1) || push_number(o1 + o2);

  case MATHOP_SUB:
    return pop_number(&o2) || pop_number(&o1) || push_number(o1 - o2);

  case MATHOP_MUL:
    return pop_number(&o2) || pop_number(&o1) || push_number(o1 * o2);

  case MATHOP_DIV:
    return pop_number(&o2) || pop_number(&o1) || push_number(o1 / o2);

  case MATHOP_NEG:
    return pop_number(&o1) || push_number(-o1);

  case MATHOP_DROP:
    return pop_number(&o1);

  case MATHOP_DUP:
    if(pop_number(&o1)) return -1;
    return push_number(o1) || push_number(o1);

  case MATHOP_SWAP:
    return pop_number(&o2) || pop_number(&o1) || push_number(o2) || push_number(o1);

  case MATHOP_MOD:
    return pop_number(&o2) || pop_number(&o1) || push_number(fmod(o1,o2));

  case MATHOP_POW:
    return pop_number(&o2) || pop_number(&o1) || push_number(pow(o1,o2));

  case MATHOP_EXP:
    return pop_number(&o1) || push_number(exp(o1));

  case MATHOP_LOG10:
    return pop_number(&o1) || push_number(log10(o1));

  case MATHOP_LN:
    return pop_number(&o1) || push_number(log(o1));

  case MATHOP_ABS:
    return pop_number(&o1) || push_number(fabs(o1));

  case MATHOP_SQRT:
    return pop_number(&o1) || push_number(sqrt(o1));

  case MATHOP_CBRT:
    return pop_number(&o1) || push_number(cbrt(o1));

  case MATHOP_FLOOR:
    return pop_number(&o1) || push_number(floor(o1));

  case MATHOP_CEIL:
    return pop_number(&o1) || push_number(ceil(o1));

  case MATHOP_ROUND:
    return pop_number(&o1) || push_number(round(o1));

  case MATHOP_NEARBYINT:
    return pop_number(&o1) || push_number(nearbyint(o1));

  case MATHOP_TRUNC:
    return pop_number(&o1) || push_number(trunc(o1));

  case MATHOP_E:
    return push_number(M_E);

  case MATHOP_PI:
    return push_number(M_PI);

  default:
    LM_WARN("Invalid RPN token type\n");
    return -1;
  }
}