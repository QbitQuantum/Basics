SkPath ValueTraits<ShapeValue>::As<SkPath>(const ShapeValue& shape) {
    SkPath path;

    if (!shape.fVertices.empty()) {
        // conservatively assume all cubics
        path.incReserve(1 + SkToU32(shape.fVertices.size() * 3));

        path.moveTo(shape.fVertices.front().fVertex);
    }

    const auto& addCubic = [&](size_t from, size_t to) {
        const auto c0 = shape.fVertices[from].fVertex + shape.fVertices[from].fOutPoint,
                   c1 = shape.fVertices[to].fVertex   + shape.fVertices[to].fInPoint;

        if (c0 == shape.fVertices[from].fVertex &&
            c1 == shape.fVertices[to].fVertex) {
            // If the control points are coincident, we can power-reduce to a straight line.
            // TODO: we could also do that when the controls are on the same line as the
            //       vertices, but it's unclear how common that case is.
            path.lineTo(shape.fVertices[to].fVertex);
        } else {
            path.cubicTo(c0, c1, shape.fVertices[to].fVertex);
        }
    };

    for (size_t i = 1; i < shape.fVertices.size(); ++i) {
        addCubic(i - 1, i);
    }

    if (!shape.fVertices.empty() && shape.fClosed) {
        addCubic(shape.fVertices.size() - 1, 0);
        path.close();
    }

    path.setIsVolatile(shape.fVolatile);
    path.shrinkToFit();

    return path;
}