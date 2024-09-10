FloatRect FEDropShadow::mapEffect(const FloatSize& stdDeviation,
                                  const FloatPoint& offset,
                                  const FloatRect& rect) {
  FloatRect offsetRect = rect;
  offsetRect.moveBy(offset);
  FloatRect blurredRect = FEGaussianBlur::mapEffect(stdDeviation, offsetRect);
  return unionRect(blurredRect, rect);
}