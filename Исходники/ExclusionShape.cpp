PassOwnPtr<ExclusionShape> ExclusionShape::createExclusionShape(const BasicShape* basicShape, const LayoutSize& logicalBoxSize, WritingMode writingMode, Length margin, Length padding)
{
    ASSERT(basicShape);

    bool horizontalWritingMode = isHorizontalWritingMode(writingMode);
    float boxWidth = horizontalWritingMode ? logicalBoxSize.width() : logicalBoxSize.height();
    float boxHeight = horizontalWritingMode ? logicalBoxSize.height() : logicalBoxSize.width();
    OwnPtr<ExclusionShape> exclusionShape;

    switch (basicShape->type()) {

    case BasicShape::BasicShapeRectangleType: {
        const BasicShapeRectangle* rectangle = static_cast<const BasicShapeRectangle*>(basicShape);
        FloatRect bounds(
            floatValueForLength(rectangle->x(), boxWidth),
            floatValueForLength(rectangle->y(), boxHeight),
            floatValueForLength(rectangle->width(), boxWidth),
            floatValueForLength(rectangle->height(), boxHeight));
        Length radiusXLength = rectangle->cornerRadiusX();
        Length radiusYLength = rectangle->cornerRadiusY();
        FloatSize cornerRadii(
            radiusXLength.isUndefined() ? 0 : floatValueForLength(radiusXLength, boxWidth),
            radiusYLength.isUndefined() ? 0 : floatValueForLength(radiusYLength, boxHeight));
        FloatRect logicalBounds = physicalRectToLogical(bounds, logicalBoxSize.height(), writingMode);

        exclusionShape = createExclusionRectangle(logicalBounds, physicalSizeToLogical(cornerRadii, writingMode));
        break;
    }

    case BasicShape::BasicShapeCircleType: {
        const BasicShapeCircle* circle = static_cast<const BasicShapeCircle*>(basicShape);
        float centerX = floatValueForLength(circle->centerX(), boxWidth);
        float centerY = floatValueForLength(circle->centerY(), boxHeight);
        float radius = floatValueForLength(circle->radius(), std::min(boxHeight, boxWidth));
        FloatPoint logicalCenter = physicalPointToLogical(FloatPoint(centerX, centerY), logicalBoxSize.height(), writingMode);

        exclusionShape = createExclusionCircle(logicalCenter, radius);
        break;
    }

    case BasicShape::BasicShapeEllipseType: {
        const BasicShapeEllipse* ellipse = static_cast<const BasicShapeEllipse*>(basicShape);
        float centerX = floatValueForLength(ellipse->centerX(), boxWidth);
        float centerY = floatValueForLength(ellipse->centerY(), boxHeight);
        float radiusX = floatValueForLength(ellipse->radiusX(), boxWidth);
        float radiusY = floatValueForLength(ellipse->radiusY(), boxHeight);
        FloatPoint logicalCenter = physicalPointToLogical(FloatPoint(centerX, centerY), logicalBoxSize.height(), writingMode);
        FloatSize logicalRadii = physicalSizeToLogical(FloatSize(radiusX, radiusY), writingMode);

        exclusionShape = createExclusionEllipse(logicalCenter, logicalRadii);
        break;
    }

    case BasicShape::BasicShapePolygonType: {
        const BasicShapePolygon* polygon = static_cast<const BasicShapePolygon*>(basicShape);
        const Vector<Length>& values = polygon->values();
        size_t valuesSize = values.size();
        ASSERT(!(valuesSize % 2));
        OwnPtr<Vector<FloatPoint> > vertices = adoptPtr(new Vector<FloatPoint>(valuesSize / 2));
        for (unsigned i = 0; i < valuesSize; i += 2) {
            FloatPoint vertex(
                floatValueForLength(values.at(i), boxWidth),
                floatValueForLength(values.at(i + 1), boxHeight));
            (*vertices)[i / 2] = physicalPointToLogical(vertex, logicalBoxSize.height(), writingMode);
        }

        exclusionShape = createExclusionPolygon(vertices.release(), polygon->windRule());
        break;
    }

    case BasicShape::BasicShapeInsetRectangleType: {
        const BasicShapeInsetRectangle* rectangle = static_cast<const BasicShapeInsetRectangle*>(basicShape);
        float left = floatValueForLength(rectangle->left(), boxWidth);
        float top = floatValueForLength(rectangle->top(), boxHeight);
        FloatRect bounds(
            left,
            top,
            boxWidth - left - floatValueForLength(rectangle->right(), boxWidth),
            boxHeight - top - floatValueForLength(rectangle->bottom(), boxHeight));
        Length radiusXLength = rectangle->cornerRadiusX();
        Length radiusYLength = rectangle->cornerRadiusY();
        FloatSize cornerRadii(
            radiusXLength.isUndefined() ? 0 : floatValueForLength(radiusXLength, boxWidth),
            radiusYLength.isUndefined() ? 0 : floatValueForLength(radiusYLength, boxHeight));
        FloatRect logicalBounds = physicalRectToLogical(bounds, logicalBoxSize.height(), writingMode);

        exclusionShape = createExclusionRectangle(logicalBounds, physicalSizeToLogical(cornerRadii, writingMode));
        break;
    }

    default:
        ASSERT_NOT_REACHED();
    }

    exclusionShape->m_writingMode = writingMode;
    exclusionShape->m_margin = floatValueForLength(margin, 0);
    exclusionShape->m_padding = floatValueForLength(padding, 0);

    return exclusionShape.release();
}