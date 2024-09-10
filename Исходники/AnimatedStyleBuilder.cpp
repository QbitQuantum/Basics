// FIXME: Generate this function.
void AnimatedStyleBuilder::applyProperty(CSSPropertyID property, StyleResolverState& state, const AnimatableValue* value)
{
    ASSERT(CSSPropertyMetadata::isAnimatableProperty(property));
    if (value->isUnknown()) {
        StyleBuilder::applyProperty(property, state, toAnimatableUnknown(value)->toCSSValue().get());
        return;
    }
    RenderStyle* style = state.style();
    switch (property) {
    case CSSPropertyBackgroundColor:
        style->setBackgroundColor(toAnimatableColor(value)->color());
        return;
    case CSSPropertyBackgroundImage:
        setOnFillLayers<CSSPropertyBackgroundImage>(style->accessBackgroundLayers(), value, state);
        return;
    case CSSPropertyBackgroundPositionX:
        setOnFillLayers<CSSPropertyBackgroundPositionX>(style->accessBackgroundLayers(), value, state);
        return;
    case CSSPropertyBackgroundPositionY:
        setOnFillLayers<CSSPropertyBackgroundPositionY>(style->accessBackgroundLayers(), value, state);
        return;
    case CSSPropertyBackgroundSize:
        setOnFillLayers<CSSPropertyBackgroundSize>(style->accessBackgroundLayers(), value, state);
        return;
    case CSSPropertyBorderBottomColor:
        style->setBorderBottomColor(toAnimatableColor(value)->color());
        return;
    case CSSPropertyBorderBottomLeftRadius:
        style->setBorderBottomLeftRadius(animatableValueToLengthSize(value, state, ValueRangeNonNegative));
        return;
    case CSSPropertyBorderBottomRightRadius:
        style->setBorderBottomRightRadius(animatableValueToLengthSize(value, state, ValueRangeNonNegative));
        return;
    case CSSPropertyBorderBottomWidth:
        style->setBorderBottomWidth(animatableValueRoundClampTo<unsigned>(value));
        return;
    case CSSPropertyBorderImageOutset:
        style->setBorderImageOutset(animatableValueToBorderImageLengthBox(value, state));
        return;
    case CSSPropertyBorderImageSlice:
        style->setBorderImageSlices(animatableValueToLengthBox(value, state, ValueRangeNonNegative));
        return;
    case CSSPropertyBorderImageSource:
        style->setBorderImageSource(state.styleImage(property, toAnimatableImage(value)->toCSSValue()));
        return;
    case CSSPropertyBorderImageWidth:
        style->setBorderImageWidth(animatableValueToBorderImageLengthBox(value, state));
        return;
    case CSSPropertyBorderLeftColor:
        style->setBorderLeftColor(toAnimatableColor(value)->color());
        return;
    case CSSPropertyBorderLeftWidth:
        style->setBorderLeftWidth(animatableValueRoundClampTo<unsigned>(value));
        return;
    case CSSPropertyBorderRightColor:
        style->setBorderRightColor(toAnimatableColor(value)->color());
        return;
    case CSSPropertyBorderRightWidth:
        style->setBorderRightWidth(animatableValueRoundClampTo<unsigned>(value));
        return;
    case CSSPropertyBorderTopColor:
        style->setBorderTopColor(toAnimatableColor(value)->color());
        return;
    case CSSPropertyBorderTopLeftRadius:
        style->setBorderTopLeftRadius(animatableValueToLengthSize(value, state, ValueRangeNonNegative));
        return;
    case CSSPropertyBorderTopRightRadius:
        style->setBorderTopRightRadius(animatableValueToLengthSize(value, state, ValueRangeNonNegative));
        return;
    case CSSPropertyBorderTopWidth:
        style->setBorderTopWidth(animatableValueRoundClampTo<unsigned>(value));
        return;
    case CSSPropertyBottom:
        style->setBottom(animatableValueToLength(value, state));
        return;
    case CSSPropertyBoxShadow:
    case CSSPropertyWebkitBoxShadow:
        style->setBoxShadow(toAnimatableShadow(value)->shadowList());
        return;
    case CSSPropertyClip:
        style->setClip(animatableValueToLengthBox(value, state));
        return;
    case CSSPropertyColor:
        style->setColor(toAnimatableColor(value)->color());
        return;
    case CSSPropertyFlexGrow:
        style->setFlexGrow(clampTo<float>(toAnimatableDouble(value)->toDouble(), 0));
        return;
    case CSSPropertyFlexShrink:
        style->setFlexShrink(clampTo<float>(toAnimatableDouble(value)->toDouble(), 0));
        return;
    case CSSPropertyFlexBasis:
        style->setFlexBasis(animatableValueToLength(value, state, ValueRangeNonNegative));
        return;
    case CSSPropertyFontSize:
        style->setFontSize(clampTo<float>(toAnimatableDouble(value)->toDouble(), 0));
        return;
    case CSSPropertyFontStretch:
        style->setFontStretch(animatableValueToFontStretch(value));
        return;
    case CSSPropertyFontWeight:
        style->setFontWeight(animatableValueToFontWeight(value));
        return;
    case CSSPropertyHeight:
        style->setHeight(animatableValueToLength(value, state, ValueRangeNonNegative));
        return;
    case CSSPropertyLeft:
        style->setLeft(animatableValueToLength(value, state));
        return;
    case CSSPropertyLineHeight:
        if (value->isLength())
            style->setLineHeight(animatableValueToLength(value, state, ValueRangeNonNegative));
        else
            style->setLineHeight(Length(clampTo<float>(toAnimatableDouble(value)->toDouble(), 0), Percent));
        return;
    case CSSPropertyLetterSpacing:
        style->setLetterSpacing(clampTo<float>(toAnimatableDouble(value)->toDouble()));
        return;
    case CSSPropertyMarginBottom:
        style->setMarginBottom(animatableValueToLength(value, state));
        return;
    case CSSPropertyMarginLeft:
        style->setMarginLeft(animatableValueToLength(value, state));
        return;
    case CSSPropertyMarginRight:
        style->setMarginRight(animatableValueToLength(value, state));
        return;
    case CSSPropertyMarginTop:
        style->setMarginTop(animatableValueToLength(value, state));
        return;
    case CSSPropertyMaxHeight:
        style->setMaxHeight(animatableValueToLength(value, state, ValueRangeNonNegative));
        return;
    case CSSPropertyMaxWidth:
        style->setMaxWidth(animatableValueToLength(value, state, ValueRangeNonNegative));
        return;
    case CSSPropertyMinHeight:
        style->setMinHeight(animatableValueToLength(value, state, ValueRangeNonNegative));
        return;
    case CSSPropertyMinWidth:
        style->setMinWidth(animatableValueToLength(value, state, ValueRangeNonNegative));
        return;
    case CSSPropertyObjectPosition:
        style->setObjectPosition(animatableValueToLengthPoint(value, state));
        return;
    case CSSPropertyOpacity:
        // Avoiding a value of 1 forces a layer to be created.
        style->setOpacity(clampTo<float>(toAnimatableDouble(value)->toDouble(), 0, nextafterf(1, 0)));
        return;
    case CSSPropertyOutlineColor:
        style->setOutlineColor(toAnimatableColor(value)->color());
        return;
    case CSSPropertyOutlineOffset:
        style->setOutlineOffset(animatableValueRoundClampTo<int>(value));
        return;
    case CSSPropertyOutlineWidth:
        style->setOutlineWidth(animatableValueRoundClampTo<unsigned short>(value));
        return;
    case CSSPropertyPaddingBottom:
        style->setPaddingBottom(animatableValueToLength(value, state, ValueRangeNonNegative));
        return;
    case CSSPropertyPaddingLeft:
        style->setPaddingLeft(animatableValueToLength(value, state, ValueRangeNonNegative));
        return;
    case CSSPropertyPaddingRight:
        style->setPaddingRight(animatableValueToLength(value, state, ValueRangeNonNegative));
        return;
    case CSSPropertyPaddingTop:
        style->setPaddingTop(animatableValueToLength(value, state, ValueRangeNonNegative));
        return;
    case CSSPropertyRight:
        style->setRight(animatableValueToLength(value, state));
        return;
    case CSSPropertyTextDecorationColor:
        style->setTextDecorationColor(toAnimatableColor(value)->color());
        return;
    case CSSPropertyTextIndent:
        style->setTextIndent(animatableValueToLength(value, state));
        return;
    case CSSPropertyTextShadow:
        style->setTextShadow(toAnimatableShadow(value)->shadowList());
        return;
    case CSSPropertyTop:
        style->setTop(animatableValueToLength(value, state));
        return;
    case CSSPropertyWebkitBackgroundSize:
        setOnFillLayers<CSSPropertyWebkitBackgroundSize>(style->accessBackgroundLayers(), value, state);
        return;
    case CSSPropertyWebkitBorderHorizontalSpacing:
        style->setHorizontalBorderSpacing(animatableValueRoundClampTo<unsigned short>(value));
        return;
    case CSSPropertyWebkitBorderVerticalSpacing:
        style->setVerticalBorderSpacing(animatableValueRoundClampTo<unsigned short>(value));
        return;
    case CSSPropertyWebkitClipPath:
        style->setClipPath(toAnimatableClipPathOperation(value)->clipPathOperation());
        return;
    case CSSPropertyFilter:
        style->setFilter(toAnimatableFilterOperations(value)->operations());
        return;
    case CSSPropertyPerspective:
        style->setPerspective(clampTo<float>(toAnimatableDouble(value)->toDouble()));
        return;
    case CSSPropertyPerspectiveOrigin: {
        const AnimatableLengthPoint* animatableLengthPoint = toAnimatableLengthPoint(value);
        style->setPerspectiveOriginX(animatableValueToLength(animatableLengthPoint->x(), state));
        style->setPerspectiveOriginY(animatableValueToLength(animatableLengthPoint->y(), state));
        return;
    }
    case CSSPropertyWebkitTextStrokeColor:
        style->setTextStrokeColor(toAnimatableColor(value)->color());
        return;
    case CSSPropertyTransform: {
        const TransformOperations& operations = toAnimatableTransform(value)->transformOperations();
        // FIXME: This normalization (handling of 'none') should be performed at input in AnimatableValueFactory.
        style->setTransform(operations.size() ? operations : TransformOperations(true));
        return;
    }
    case CSSPropertyTransformOrigin: {
        const AnimatableLengthPoint3D* animatableLengthPoint3D = toAnimatableLengthPoint3D(value);
        style->setTransformOriginX(animatableValueToLength(animatableLengthPoint3D->x(), state));
        style->setTransformOriginY(animatableValueToLength(animatableLengthPoint3D->y(), state));
        style->setTransformOriginZ(clampTo<float>(toAnimatableDouble(animatableLengthPoint3D->z())->toDouble()));
        return;
    }
    case CSSPropertyWidth:
        style->setWidth(animatableValueToLength(value, state, ValueRangeNonNegative));
        return;
    case CSSPropertyWordSpacing:
        style->setWordSpacing(clampTo<float>(toAnimatableDouble(value)->toDouble()));
        return;
    case CSSPropertyVerticalAlign:
        style->setVerticalAlignLength(animatableValueToLength(value, state));
        return;
    case CSSPropertyZIndex:
        style->setZIndex(animatableValueRoundClampTo<unsigned>(value));
        return;
    default:
        ASSERT_NOT_REACHED();
    }
}