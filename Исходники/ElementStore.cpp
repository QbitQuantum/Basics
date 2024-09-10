bool ElementStore::store(const Element& element, const LodRange& range, const StyleProvider& styleProvider, const Visitor& visitor)
{
    BoundingBoxVisitor bboxVisitor;
    using namespace std::placeholders;
    ElementGeometryClipper geometryClipper(std::bind(&ElementStore::storeImpl, this, _1, _2));
    bool wasStored = false;
    double size = -1; // match all by default
    for (int lod = range.start; lod <= range.end; ++lod) {
        if (!styleProvider.hasStyle(element, lod))
            continue;
        Style style = styleProvider.forElement(element, lod);
        if (style.has(skipKeyId_, "true")) continue;

        // initialize bounding box and size only once
        if (!bboxVisitor.boundingBox.isValid()) {
            element.accept(bboxVisitor);
            // read size if present
            if (style.has(sizeKeyId_))
                size = style.getValue(sizeKeyId_, 1, bboxVisitor.boundingBox.center());
        }

         utymap::utils::GeoUtils::visitTileRange(bboxVisitor.boundingBox, lod,
                                                 [&](const QuadKey& quadKey, const BoundingBox& quadKeyBbox) {
             if (!visitor(bboxVisitor.boundingBox, quadKeyBbox) ||
                 !checkSize(quadKeyBbox, bboxVisitor.boundingBox, size)) // can be optimized (quadkey widht is const for lod)
                 return;

            if (style.has(clipKeyId_, "true"))
                geometryClipper.clipAndCall(element, quadKey, quadKeyBbox);
            else
                storeImpl(element, quadKey);

            wasStored = true;
        });

    }

    // NOTE still might be clipped and then skipped
    return wasStored;
}