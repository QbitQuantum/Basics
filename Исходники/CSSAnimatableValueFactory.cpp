// FIXME: Generate this function.
PassRefPtr<AnimatableValue> CSSAnimatableValueFactory::create(CSSPropertyID property, const RenderStyle& style)
{
    switch (property) {
    case CSSPropertyBackgroundColor:
        return createFromColor(property, style);
    case CSSPropertyBackgroundImage:
        return createFromFillLayers<CSSPropertyBackgroundImage>(style.backgroundLayers(), style);
    case CSSPropertyBackgroundPositionX:
        return createFromFillLayers<CSSPropertyBackgroundPositionX>(style.backgroundLayers(), style);
    case CSSPropertyBackgroundPositionY:
        return createFromFillLayers<CSSPropertyBackgroundPositionY>(style.backgroundLayers(), style);
    case CSSPropertyBackgroundSize:
    case CSSPropertyWebkitBackgroundSize:
        return createFromFillLayers<CSSPropertyBackgroundSize>(style.backgroundLayers(), style);
    case CSSPropertyBaselineShift:
        return AnimatableSVGLength::create(style.baselineShiftValue());
    case CSSPropertyBorderBottomColor:
        return createFromColor(property, style);
    case CSSPropertyBorderBottomLeftRadius:
        return createFromLengthSize(style.borderBottomLeftRadius(), style);
    case CSSPropertyBorderBottomRightRadius:
        return createFromLengthSize(style.borderBottomRightRadius(), style);
    case CSSPropertyBorderBottomWidth:
        return createFromDouble(style.borderBottomWidth());
    case CSSPropertyBorderImageOutset:
        return createFromBorderImageLengthBox(style.borderImageOutset(), style);
    case CSSPropertyBorderImageSlice:
        return createFromLengthBox(style.borderImageSlices(), style);
    case CSSPropertyBorderImageSource:
        return createFromStyleImage(style.borderImageSource());
    case CSSPropertyBorderImageWidth:
        return createFromBorderImageLengthBox(style.borderImageWidth(), style);
    case CSSPropertyBorderLeftColor:
        return createFromColor(property, style);
    case CSSPropertyBorderLeftWidth:
        return createFromDouble(style.borderLeftWidth());
    case CSSPropertyBorderRightColor:
        return createFromColor(property, style);
    case CSSPropertyBorderRightWidth:
        return createFromDouble(style.borderRightWidth());
    case CSSPropertyBorderTopColor:
        return createFromColor(property, style);
    case CSSPropertyBorderTopLeftRadius:
        return createFromLengthSize(style.borderTopLeftRadius(), style);
    case CSSPropertyBorderTopRightRadius:
        return createFromLengthSize(style.borderTopRightRadius(), style);
    case CSSPropertyBorderTopWidth:
        return createFromDouble(style.borderTopWidth());
    case CSSPropertyBottom:
        return createFromLength(style.bottom(), style);
    case CSSPropertyBoxShadow:
    case CSSPropertyWebkitBoxShadow:
        return AnimatableShadow::create(style.boxShadow());
    case CSSPropertyClip:
        if (style.hasClip())
            return createFromLengthBox(style.clip(), style);
        return AnimatableUnknown::create(CSSPrimitiveValue::create(CSSValueAuto));
    case CSSPropertyColor:
        return createFromColor(property, style);
    case CSSPropertyFillOpacity:
        return createFromDouble(style.fillOpacity());
    case CSSPropertyFill:
        return AnimatableSVGPaint::create(style.svgStyle()->fillPaintType(), style.svgStyle()->fillPaintColor(), style.svgStyle()->fillPaintUri());
    case CSSPropertyFlexGrow:
        return createFromDouble(style.flexGrow(), AnimatableDouble::InterpolationIsNonContinuousWithZero);
    case CSSPropertyFlexShrink:
        return createFromDouble(style.flexShrink(), AnimatableDouble::InterpolationIsNonContinuousWithZero);
    case CSSPropertyFlexBasis:
        return createFromLength(style.flexBasis(), style);
    case CSSPropertyFloodColor:
        return createFromColor(property, style);
    case CSSPropertyFloodOpacity:
        return createFromDouble(style.floodOpacity());
    case CSSPropertyFontSize:
        // Must pass a specified size to setFontSize if Text Autosizing is enabled, but a computed size
        // if text zoom is enabled (if neither is enabled it's irrelevant as they're probably the same).
        // FIXME: Should we introduce an option to pass the computed font size here, allowing consumers to
        // enable text zoom rather than Text Autosizing? See http://crbug.com/227545.
        return createFromDouble(style.specifiedFontSize());
    case CSSPropertyHeight:
        return createFromLength(style.height(), style);
    case CSSPropertyKerning:
        return AnimatableSVGLength::create(style.kerning());
    case CSSPropertyLightingColor:
        return createFromColor(property, style);
    case CSSPropertyListStyleImage:
        return createFromStyleImage(style.listStyleImage());
    case CSSPropertyLeft:
        return createFromLength(style.left(), style);
    case CSSPropertyLetterSpacing:
        return createFromDouble(style.letterSpacing());
    case CSSPropertyLineHeight:
        return createFromLineHeight(style.specifiedLineHeight(), style);
    case CSSPropertyMarginBottom:
        return createFromLength(style.marginBottom(), style);
    case CSSPropertyMarginLeft:
        return createFromLength(style.marginLeft(), style);
    case CSSPropertyMarginRight:
        return createFromLength(style.marginRight(), style);
    case CSSPropertyMarginTop:
        return createFromLength(style.marginTop(), style);
    case CSSPropertyMaxHeight:
        return createFromLength(style.maxHeight(), style);
    case CSSPropertyMaxWidth:
        return createFromLength(style.maxWidth(), style);
    case CSSPropertyMinHeight:
        return createFromLength(style.minHeight(), style);
    case CSSPropertyMinWidth:
        return createFromLength(style.minWidth(), style);
    case CSSPropertyObjectPosition:
        return createFromLengthPoint(style.objectPosition(), style);
    case CSSPropertyOpacity:
        return createFromDouble(style.opacity());
    case CSSPropertyOrphans:
        return createFromDouble(style.orphans());
    case CSSPropertyOutlineColor:
        return createFromColor(property, style);
    case CSSPropertyOutlineOffset:
        return createFromDouble(style.outlineOffset());
    case CSSPropertyOutlineWidth:
        return createFromDouble(style.outlineWidth());
    case CSSPropertyPaddingBottom:
        return createFromLength(style.paddingBottom(), style);
    case CSSPropertyPaddingLeft:
        return createFromLength(style.paddingLeft(), style);
    case CSSPropertyPaddingRight:
        return createFromLength(style.paddingRight(), style);
    case CSSPropertyPaddingTop:
        return createFromLength(style.paddingTop(), style);
    case CSSPropertyRight:
        return createFromLength(style.right(), style);
    case CSSPropertyStrokeWidth:
        return AnimatableSVGLength::create(style.strokeWidth());
    case CSSPropertyStopColor:
        return createFromColor(property, style);
    case CSSPropertyStopOpacity:
        return createFromDouble(style.stopOpacity());
    case CSSPropertyStrokeDasharray:
        return AnimatableStrokeDasharrayList::create(style.strokeDashArray());
    case CSSPropertyStrokeDashoffset:
        return AnimatableSVGLength::create(style.strokeDashOffset());
    case CSSPropertyStrokeMiterlimit:
        return createFromDouble(style.strokeMiterLimit());
    case CSSPropertyStrokeOpacity:
        return createFromDouble(style.strokeOpacity());
    case CSSPropertyStroke:
        return AnimatableSVGPaint::create(style.svgStyle()->strokePaintType(), style.svgStyle()->strokePaintColor(), style.svgStyle()->strokePaintUri());
    case CSSPropertyTextDecorationColor:
        return createFromColor(property, style);
    case CSSPropertyTextIndent:
        return createFromLength(style.textIndent(), style);
    case CSSPropertyTextShadow:
        return AnimatableShadow::create(style.textShadow());
    case CSSPropertyTop:
        return createFromLength(style.top(), style);
    case CSSPropertyWebkitBorderHorizontalSpacing:
        return createFromDouble(style.horizontalBorderSpacing());
    case CSSPropertyWebkitBorderVerticalSpacing:
        return createFromDouble(style.verticalBorderSpacing());
    case CSSPropertyWebkitClipPath:
        return AnimatableClipPathOperation::create(style.clipPath());
    case CSSPropertyWebkitColumnCount:
        return createFromDouble(style.columnCount());
    case CSSPropertyWebkitColumnGap:
        return createFromDouble(style.columnGap());
    case CSSPropertyWebkitColumnRuleColor:
        return createFromColor(property, style);
    case CSSPropertyWebkitColumnRuleWidth:
        return createFromDouble(style.columnRuleWidth());
    case CSSPropertyWebkitColumnWidth:
        return createFromDouble(style.columnWidth());
    case CSSPropertyWebkitFilter:
        return AnimatableFilterOperations::create(style.filter());
    case CSSPropertyWebkitMaskBoxImageOutset:
        return createFromBorderImageLengthBox(style.maskBoxImageOutset(), style);
    case CSSPropertyWebkitMaskBoxImageSlice:
        return createFromLengthBoxAndBool(style.maskBoxImageSlices(), style.maskBoxImageSlicesFill(), style);
    case CSSPropertyWebkitMaskBoxImageSource:
        return createFromStyleImage(style.maskBoxImageSource());
    case CSSPropertyWebkitMaskBoxImageWidth:
        return createFromBorderImageLengthBox(style.maskBoxImageWidth(), style);
    case CSSPropertyWebkitMaskImage:
        return createFromFillLayers<CSSPropertyWebkitMaskImage>(style.maskLayers(), style);
    case CSSPropertyWebkitMaskPositionX:
        return createFromFillLayers<CSSPropertyWebkitMaskPositionX>(style.maskLayers(), style);
    case CSSPropertyWebkitMaskPositionY:
        return createFromFillLayers<CSSPropertyWebkitMaskPositionY>(style.maskLayers(), style);
    case CSSPropertyWebkitMaskSize:
        return createFromFillLayers<CSSPropertyWebkitMaskSize>(style.maskLayers(), style);
    case CSSPropertyWebkitPerspective:
        return createFromDouble(style.perspective());
    case CSSPropertyWebkitPerspectiveOriginX:
        return createFromLength(style.perspectiveOriginX(), style);
    case CSSPropertyWebkitPerspectiveOriginY:
        return createFromLength(style.perspectiveOriginY(), style);
    case CSSPropertyShapeInside:
        return AnimatableShapeValue::create(style.shapeInside());
    case CSSPropertyShapeOutside:
        return AnimatableShapeValue::create(style.shapeOutside());
    case CSSPropertyShapeMargin:
        return createFromLength(style.shapeMargin(), style);
    case CSSPropertyWebkitTextStrokeColor:
        return createFromColor(property, style);
    case CSSPropertyWebkitTransform:
        return AnimatableTransform::create(style.transform());
    case CSSPropertyWebkitTransformOriginX:
        return createFromLength(style.transformOriginX(), style);
    case CSSPropertyWebkitTransformOriginY:
        return createFromLength(style.transformOriginY(), style);
    case CSSPropertyWebkitTransformOriginZ:
        return createFromDouble(style.transformOriginZ());
    case CSSPropertyWidows:
        return createFromDouble(style.widows());
    case CSSPropertyWidth:
        return createFromLength(style.width(), style);
    case CSSPropertyWordSpacing:
        return createFromDouble(style.wordSpacing());
    case CSSPropertyVisibility:
        return AnimatableVisibility::create(style.visibility());
    case CSSPropertyZIndex:
        return createFromDouble(style.zIndex());
    case CSSPropertyZoom:
        return createFromDouble(style.zoom());
    default:
        ASSERT_WITH_MESSAGE(!CSSAnimations::isAnimatableProperty(property), "Web Animations not yet implemented: Create AnimatableValue from render style: %s", getPropertyNameString(property).utf8().data());
        ASSERT_NOT_REACHED();
        // This return value is to avoid a release crash if possible.
        return AnimatableUnknown::create(0);
    }
}