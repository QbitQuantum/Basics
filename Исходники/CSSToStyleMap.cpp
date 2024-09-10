void CSSToStyleMap::mapAnimationTimingFunction(Animation* animation, CSSValue* value)
{
    if (value->isInitialValue()) {
        animation->setTimingFunction(Animation::initialAnimationTimingFunction());
        return;
    }

    if (value->isPrimitiveValue()) {
        CSSPrimitiveValue* primitiveValue = static_cast<CSSPrimitiveValue*>(value);
        switch (primitiveValue->getValueID()) {
        case CSSValueLinear:
            animation->setTimingFunction(LinearTimingFunction::create());
            break;
        case CSSValueEase:
            animation->setTimingFunction(CubicBezierTimingFunction::create());
            break;
        case CSSValueEaseIn:
            animation->setTimingFunction(CubicBezierTimingFunction::create(CubicBezierTimingFunction::EaseIn));
            break;
        case CSSValueEaseOut:
            animation->setTimingFunction(CubicBezierTimingFunction::create(CubicBezierTimingFunction::EaseOut));
            break;
        case CSSValueEaseInOut:
            animation->setTimingFunction(CubicBezierTimingFunction::create(CubicBezierTimingFunction::EaseInOut));
            break;
        case CSSValueStepStart:
            animation->setTimingFunction(StepsTimingFunction::create(1, true));
            break;
        case CSSValueStepEnd:
            animation->setTimingFunction(StepsTimingFunction::create(1, false));
            break;
        default:
            break;
        }
        return;
    }

    if (value->isCubicBezierTimingFunctionValue()) {
        CSSCubicBezierTimingFunctionValue* cubicTimingFunction = static_cast<CSSCubicBezierTimingFunctionValue*>(value);
        animation->setTimingFunction(CubicBezierTimingFunction::create(cubicTimingFunction->x1(), cubicTimingFunction->y1(), cubicTimingFunction->x2(), cubicTimingFunction->y2()));
    } else if (value->isStepsTimingFunctionValue()) {
        CSSStepsTimingFunctionValue* stepsTimingFunction = static_cast<CSSStepsTimingFunctionValue*>(value);
        animation->setTimingFunction(StepsTimingFunction::create(stepsTimingFunction->numberOfSteps(), stepsTimingFunction->stepAtStart()));
    } else if (value->isLinearTimingFunctionValue())
        animation->setTimingFunction(LinearTimingFunction::create());
}