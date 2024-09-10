css_dim_t measure(void *context, float width) {
  const char *text = context;
  css_dim_t dim;
  if (width != width) {
    width = 1000000;
  }
  if (strcmp(text, SMALL_TEXT) == 0) {
    dim.dimensions[CSS_WIDTH] = fminf(SMALL_WIDTH, width);
    dim.dimensions[CSS_HEIGHT] = SMALL_HEIGHT;
    return dim;
  }
  if (strcmp(text, LONG_TEXT) == 0) {
    dim.dimensions[CSS_WIDTH] = width >= BIG_WIDTH ? BIG_WIDTH : fmaxf(BIG_MIN_WIDTH, width);
    dim.dimensions[CSS_HEIGHT] = width >= BIG_WIDTH ? SMALL_HEIGHT : BIG_HEIGHT;
    return dim;
  }

  // Should not go here
  dim.dimensions[CSS_WIDTH] = CSS_UNDEFINED;
  dim.dimensions[CSS_HEIGHT] = CSS_UNDEFINED;
  return dim;
}