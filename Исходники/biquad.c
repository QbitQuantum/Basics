void ctss_calculate_biquad_coeff(CTSS_DSPNode *node,
                                 CTSS_BiquadType type,
                                 float freq,
                                 float dbGain,
                                 float bandwidth) {
  CTSS_BiquadState *state = node->state;
  float a0, a1, a2, b0, b1, b2;

  float A     = powf(10.0f, dbGain / 40.0f);
  float omega = HZ_TO_RAD(freq);
  float sn    = sinf(omega);
  float cs    = cosf(omega);
  float alpha = sn * sinh(CT_LN2 / 2.0f * bandwidth * omega / sn);
  float beta  = sqrtf(A + A);

  switch (type) {
    case LPF:
    default:
      b0 = (1.0f - cs) / 2.0f;
      b1 = 1.0f - cs;
      b2 = (1.0f - cs) / 2.0f;
      a0 = 1.0f + alpha;
      a1 = -2.0f * cs;
      a2 = 1.0f - alpha;
      break;
    case HPF:
      b0 = (1.0f + cs) / 2.0f;
      b1 = -(1.0f + cs);
      b2 = (1.0f + cs) / 2.0f;
      a0 = 1.0f + alpha;
      a1 = -2.0f * cs;
      a2 = 1.0f - alpha;
      break;
    case BPF:
      b0 = alpha;
      b1 = 0;
      b2 = -alpha;
      a0 = 1.0f + alpha;
      a1 = -2.0f * cs;
      a2 = 1.0f - alpha;
      break;
    case NOTCH:
      b0 = 1.0f;
      b1 = -2.0f * cs;
      b2 = 1.0f;
      a0 = 1.0f + alpha;
      a1 = -2.0f * cs;
      a2 = 1.0f - alpha;
      break;
    case PEQ:
      b0 = 1.0f + (alpha * A);
      b1 = -2.0f * cs;
      b2 = 1.0f - (alpha * A);
      a0 = 1.0f + (alpha / A);
      a1 = -2.0f * cs;
      a2 = 1.0f - (alpha / A);
      break;
    case LSH:
      b0 = A * ((A + 1.0f) - (A - 1.0f) * cs + beta * sn);
      b1 = 2.0f * A * ((A - 1.0f) - (A + 1.0f) * cs);
      b2 = A * ((A + 1.0f) - (A - 1.0f) * cs - beta * sn);
      a0 = (A + 1.0f) + (A - 1.0f) * cs + beta * sn;
      a1 = -2.0f * ((A - 1.0f) + (A + 1.0f) * cs);
      a2 = (A + 1.0f) + (A - 1.0f) * cs - beta * sn;
      break;
    case HSH:
      b0 = A * ((A + 1.0f) + (A - 1.0f) * cs + beta * sn);
      b1 = -2.0f * A * ((A - 1.0f) + (A + 1.0f) * cs);
      b2 = A * ((A + 1.0f) + (A - 1.0f) * cs - beta * sn);
      a0 = (A + 1.0f) - (A - 1.0f) * cs + beta * sn;
      a1 = 2.0f * ((A - 1.0f) - (A + 1.0f) * cs);
      a2 = (A + 1.0f) - (A - 1.0f) * cs - beta * sn;
      break;
  }

  a0 = 1.0f / a0;

  state->f[0] = b0 * a0;
  state->f[1] = b1 * a0;
  state->f[2] = b2 * a0;
  state->f[3] = a1 * a0;
  state->f[4] = a2 * a0;

  state->f[5] = state->f[6] = state->f[7] = state->f[8] = 0.0f;
}