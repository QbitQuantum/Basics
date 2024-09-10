bool TransformBuilder::createTransformOperations(CSSValue* inValue, RenderStyle* style, RenderStyle* rootStyle, TransformOperations& outOperations)
{
    if (!inValue || !inValue->isValueList()) {
        outOperations.clear();
        return false;
    }

    float zoomFactor = style ? style->effectiveZoom() : 1;
    TransformOperations operations;
    for (CSSValueListIterator i = inValue; i.hasMore(); i.advance()) {
        CSSValue* currValue = i.value();

        if (!currValue->isCSSTransformValue())
            continue;

        CSSTransformValue* transformValue = static_cast<CSSTransformValue*>(i.value());
        if (!transformValue->length())
            continue;

        bool haveNonPrimitiveValue = false;
        for (unsigned j = 0; j < transformValue->length(); ++j) {
            if (!transformValue->itemWithoutBoundsCheck(j)->isPrimitiveValue()) {
                haveNonPrimitiveValue = true;
                break;
            }
        }
        if (haveNonPrimitiveValue)
            continue;

        CSSPrimitiveValue* firstValue = toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(0));

        switch (transformValue->operationType()) {
        case CSSTransformValue::ScaleTransformOperation:
        case CSSTransformValue::ScaleXTransformOperation:
        case CSSTransformValue::ScaleYTransformOperation: {
            double sx = 1.0;
            double sy = 1.0;
            if (transformValue->operationType() == CSSTransformValue::ScaleYTransformOperation)
                sy = firstValue->getDoubleValue();
            else {
                sx = firstValue->getDoubleValue();
                if (transformValue->operationType() != CSSTransformValue::ScaleXTransformOperation) {
                    if (transformValue->length() > 1) {
                        CSSPrimitiveValue* secondValue = toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(1));
                        sy = secondValue->getDoubleValue();
                    } else
                        sy = sx;
                }
            }
            operations.operations().append(ScaleTransformOperation::create(sx, sy, 1.0, getTransformOperationType(transformValue->operationType())));
            break;
        }
        case CSSTransformValue::ScaleZTransformOperation:
        case CSSTransformValue::Scale3DTransformOperation: {
            double sx = 1.0;
            double sy = 1.0;
            double sz = 1.0;
            if (transformValue->operationType() == CSSTransformValue::ScaleZTransformOperation)
                sz = firstValue->getDoubleValue();
            else if (transformValue->operationType() == CSSTransformValue::ScaleYTransformOperation)
                sy = firstValue->getDoubleValue();
            else {
                sx = firstValue->getDoubleValue();
                if (transformValue->operationType() != CSSTransformValue::ScaleXTransformOperation) {
                    if (transformValue->length() > 2) {
                        CSSPrimitiveValue* thirdValue = toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(2));
                        sz = thirdValue->getDoubleValue();
                    }
                    if (transformValue->length() > 1) {
                        CSSPrimitiveValue* secondValue = toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(1));
                        sy = secondValue->getDoubleValue();
                    } else
                        sy = sx;
                }
            }
            operations.operations().append(ScaleTransformOperation::create(sx, sy, sz, getTransformOperationType(transformValue->operationType())));
            break;
        }
        case CSSTransformValue::TranslateTransformOperation:
        case CSSTransformValue::TranslateXTransformOperation:
        case CSSTransformValue::TranslateYTransformOperation: {
            Length tx = Length(0, Fixed);
            Length ty = Length(0, Fixed);
            if (transformValue->operationType() == CSSTransformValue::TranslateYTransformOperation)
                ty = convertToFloatLength(firstValue, style, rootStyle, zoomFactor);
            else {
                tx = convertToFloatLength(firstValue, style, rootStyle, zoomFactor);
                if (transformValue->operationType() != CSSTransformValue::TranslateXTransformOperation) {
                    if (transformValue->length() > 1) {
                        CSSPrimitiveValue* secondValue = toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(1));
                        ty = convertToFloatLength(secondValue, style, rootStyle, zoomFactor);
                    }
                }
            }

            if (tx.isUndefined() || ty.isUndefined())
                return false;

            operations.operations().append(TranslateTransformOperation::create(tx, ty, Length(0, Fixed), getTransformOperationType(transformValue->operationType())));
            break;
        }
        case CSSTransformValue::TranslateZTransformOperation:
        case CSSTransformValue::Translate3DTransformOperation: {
            Length tx = Length(0, Fixed);
            Length ty = Length(0, Fixed);
            Length tz = Length(0, Fixed);
            if (transformValue->operationType() == CSSTransformValue::TranslateZTransformOperation)
                tz = convertToFloatLength(firstValue, style, rootStyle, zoomFactor);
            else if (transformValue->operationType() == CSSTransformValue::TranslateYTransformOperation)
                ty = convertToFloatLength(firstValue, style, rootStyle, zoomFactor);
            else {
                tx = convertToFloatLength(firstValue, style, rootStyle, zoomFactor);
                if (transformValue->operationType() != CSSTransformValue::TranslateXTransformOperation) {
                    if (transformValue->length() > 2) {
                        CSSPrimitiveValue* thirdValue = toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(2));
                        tz = convertToFloatLength(thirdValue, style, rootStyle, zoomFactor);
                    }
                    if (transformValue->length() > 1) {
                        CSSPrimitiveValue* secondValue = toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(1));
                        ty = convertToFloatLength(secondValue, style, rootStyle, zoomFactor);
                    }
                }
            }

            if (tx.isUndefined() || ty.isUndefined() || tz.isUndefined())
                return false;

            operations.operations().append(TranslateTransformOperation::create(tx, ty, tz, getTransformOperationType(transformValue->operationType())));
            break;
        }
        case CSSTransformValue::RotateTransformOperation: {
            double angle = firstValue->computeDegrees();
            operations.operations().append(RotateTransformOperation::create(0, 0, 1, angle, getTransformOperationType(transformValue->operationType())));
            break;
        }
        case CSSTransformValue::RotateXTransformOperation:
        case CSSTransformValue::RotateYTransformOperation:
        case CSSTransformValue::RotateZTransformOperation: {
            double x = 0;
            double y = 0;
            double z = 0;
            double angle = firstValue->computeDegrees();

            if (transformValue->operationType() == CSSTransformValue::RotateXTransformOperation)
                x = 1;
            else if (transformValue->operationType() == CSSTransformValue::RotateYTransformOperation)
                y = 1;
            else
                z = 1;
            operations.operations().append(RotateTransformOperation::create(x, y, z, angle, getTransformOperationType(transformValue->operationType())));
            break;
        }
        case CSSTransformValue::Rotate3DTransformOperation: {
            if (transformValue->length() < 4)
                break;
            CSSPrimitiveValue* secondValue = toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(1));
            CSSPrimitiveValue* thirdValue = toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(2));
            CSSPrimitiveValue* fourthValue = toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(3));
            double x = firstValue->getDoubleValue();
            double y = secondValue->getDoubleValue();
            double z = thirdValue->getDoubleValue();
            double angle = fourthValue->computeDegrees();
            operations.operations().append(RotateTransformOperation::create(x, y, z, angle, getTransformOperationType(transformValue->operationType())));
            break;
        }
        case CSSTransformValue::SkewTransformOperation:
        case CSSTransformValue::SkewXTransformOperation:
        case CSSTransformValue::SkewYTransformOperation: {
            double angleX = 0;
            double angleY = 0;
            double angle = firstValue->computeDegrees();
            if (transformValue->operationType() == CSSTransformValue::SkewYTransformOperation)
                angleY = angle;
            else {
                angleX = angle;
                if (transformValue->operationType() == CSSTransformValue::SkewTransformOperation) {
                    if (transformValue->length() > 1) {
                        CSSPrimitiveValue* secondValue = toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(1));
                        angleY = secondValue->computeDegrees();
                    }
                }
            }
            operations.operations().append(SkewTransformOperation::create(angleX, angleY, getTransformOperationType(transformValue->operationType())));
            break;
        }
        case CSSTransformValue::MatrixTransformOperation: {
            if (transformValue->length() < 6)
                break;
            double a = firstValue->getDoubleValue();
            double b = toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(1))->getDoubleValue();
            double c = toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(2))->getDoubleValue();
            double d = toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(3))->getDoubleValue();
            double e = zoomFactor * toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(4))->getDoubleValue();
            double f = zoomFactor * toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(5))->getDoubleValue();
            operations.operations().append(MatrixTransformOperation::create(a, b, c, d, e, f));
            break;
        }
        case CSSTransformValue::Matrix3DTransformOperation: {
            if (transformValue->length() < 16)
                break;
            TransformationMatrix matrix(toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(0))->getDoubleValue(),
                                        toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(1))->getDoubleValue(),
                                        toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(2))->getDoubleValue(),
                                        toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(3))->getDoubleValue(),
                                        toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(4))->getDoubleValue(),
                                        toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(5))->getDoubleValue(),
                                        toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(6))->getDoubleValue(),
                                        toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(7))->getDoubleValue(),
                                        toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(8))->getDoubleValue(),
                                        toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(9))->getDoubleValue(),
                                        toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(10))->getDoubleValue(),
                                        toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(11))->getDoubleValue(),
                                        zoomFactor * toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(12))->getDoubleValue(),
                                        zoomFactor * toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(13))->getDoubleValue(),
                                        toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(14))->getDoubleValue(),
                                        toCSSPrimitiveValue(transformValue->itemWithoutBoundsCheck(15))->getDoubleValue());
            operations.operations().append(Matrix3DTransformOperation::create(matrix));
            break;
        }
        case CSSTransformValue::PerspectiveTransformOperation: {
            Length p = Length(0, Fixed);
            if (firstValue->isLength())
                p = convertToFloatLength(firstValue, style, rootStyle, zoomFactor);
            else {
                // This is a quirk that should go away when 3d transforms are finalized.
                double val = firstValue->getDoubleValue();
                p = val >= 0 ? Length(clampToPositiveInteger(val), Fixed) : Length(Undefined);
            }

            if (p.isUndefined())
                return false;

            operations.operations().append(PerspectiveTransformOperation::create(p));
            break;
        }
        case CSSTransformValue::UnknownTransformOperation:
            ASSERT_NOT_REACHED();
            break;
        }
    }

    outOperations = operations;
    return true;
}