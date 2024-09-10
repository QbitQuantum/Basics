float MessageLog::performUnaryOperation(float input) {
  return (input <= 0.0f) ? 0.0f : logf(input);
}