void DespeckleOperation::executePixel(float output[4], int x, int y, void * /*data*/)
{
  float w = 0.0f;
  float color_org[4];
  float color_mid[4];
  float color_mid_ok[4];
  float in1[4];
  int x1 = x - 1;
  int x2 = x;
  int x3 = x + 1;
  int y1 = y - 1;
  int y2 = y;
  int y3 = y + 1;
  CLAMP(x1, 0, getWidth() - 1);
  CLAMP(x2, 0, getWidth() - 1);
  CLAMP(x3, 0, getWidth() - 1);
  CLAMP(y1, 0, getHeight() - 1);
  CLAMP(y2, 0, getHeight() - 1);
  CLAMP(y3, 0, getHeight() - 1);
  float value[4];
  this->m_inputValueOperation->read(value, x2, y2, NULL);
  // const float mval = 1.0f - value[0];

  this->m_inputOperation->read(color_org, x2, y2, NULL);

#define TOT_DIV_ONE 1.0f
#define TOT_DIV_CNR (float)M_SQRT1_2

#define WTOT (TOT_DIV_ONE * 4 + TOT_DIV_CNR * 4)

#define COLOR_ADD(fac) \
  { \
    madd_v4_v4fl(color_mid, in1, fac); \
    if (color_diff(in1, color_org, this->m_threshold)) { \
      w += fac; \
      madd_v4_v4fl(color_mid_ok, in1, fac); \
    } \
  }

  zero_v4(color_mid);
  zero_v4(color_mid_ok);

  this->m_inputOperation->read(in1, x1, y1, NULL);
  COLOR_ADD(TOT_DIV_CNR)
  this->m_inputOperation->read(in1, x2, y1, NULL);
  COLOR_ADD(TOT_DIV_ONE)
  this->m_inputOperation->read(in1, x3, y1, NULL);
  COLOR_ADD(TOT_DIV_CNR)
  this->m_inputOperation->read(in1, x1, y2, NULL);
  COLOR_ADD(TOT_DIV_ONE)

#if 0
  this->m_inputOperation->read(in2, x2, y2, NULL);
  madd_v4_v4fl(color_mid, in2, this->m_filter[4]);
#endif

  this->m_inputOperation->read(in1, x3, y2, NULL);
  COLOR_ADD(TOT_DIV_ONE)
  this->m_inputOperation->read(in1, x1, y3, NULL);
  COLOR_ADD(TOT_DIV_CNR)
  this->m_inputOperation->read(in1, x2, y3, NULL);
  COLOR_ADD(TOT_DIV_ONE)
  this->m_inputOperation->read(in1, x3, y3, NULL);
  COLOR_ADD(TOT_DIV_CNR)

  mul_v4_fl(color_mid, 1.0f / (4.0f + (4.0f * (float)M_SQRT1_2)));
  // mul_v4_fl(color_mid, 1.0f / w);

  if ((w != 0.0f) && ((w / WTOT) > (this->m_threshold_neighbor)) &&
      color_diff(color_mid, color_org, this->m_threshold)) {
    mul_v4_fl(color_mid_ok, 1.0f / w);
    interp_v4_v4v4(output, color_org, color_mid_ok, value[0]);
  }
  else {
    copy_v4_v4(output, color_org);
  }
}