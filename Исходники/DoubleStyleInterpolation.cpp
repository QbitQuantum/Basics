PassRefPtrWillBeRawPtr<CSSValue> DoubleStyleInterpolation::interpolableValueToDouble(InterpolableValue* value, ClampRange clamp)
{
    ASSERT(value->isNumber());
    double doubleValue = toInterpolableNumber(value)->value();
    if (clamp == ClampOpacity) {
        doubleValue = clampTo<float>(doubleValue, 0, nextafterf(1, 0));
    }
    return CSSPrimitiveValue::create(doubleValue, CSSPrimitiveValue::CSS_NUMBER);
}