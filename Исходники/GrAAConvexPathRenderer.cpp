bool GrAAConvexPathRenderer::onDrawPath(const SkPath& origPath,
                                        GrPathFill fill,
                                        const GrVec* translate,
                                        GrDrawTarget* target,
                                        GrDrawState::StageMask stageMask,
                                        bool antiAlias) {

    const SkPath* path = &origPath;
    if (path->isEmpty()) {
        return true;
    }
    GrDrawTarget::AutoStateRestore asr(target,
                                       GrDrawTarget::kPreserve_ASRInit);
    GrDrawState* drawState = target->drawState();

    GrMatrix vm = drawState->getViewMatrix();
    if (NULL != translate) {
        vm.postTranslate(translate->fX, translate->fY);
    }
    GrMatrix ivm;
    if (vm.invert(&ivm)) {
        drawState->preConcatSamplerMatrices(stageMask, ivm);
    }
    drawState->viewMatrix()->reset();

    GrVertexLayout layout = 0;
    for (int s = 0; s < GrDrawState::kNumStages; ++s) {
        if ((1 << s) & stageMask) {
            layout |= GrDrawTarget::StagePosAsTexCoordVertexLayoutBit(s);
        }
    }
    layout |= GrDrawTarget::kEdge_VertexLayoutBit;

    // We use the fact that SkPath::transform path does subdivision based on
    // perspective. Otherwise, we apply the view matrix when copying to the
    // segment representation.
    SkPath tmpPath;
    if (vm.hasPerspective()) {
        origPath.transform(vm, &tmpPath);
        path = &tmpPath;
        vm.reset();
    }

    QuadVertex *verts;
    uint16_t* idxs;

    int vCount;
    int iCount;
    enum {
        kPreallocSegmentCnt = 512 / sizeof(Segment),
    };
    SkSTArray<kPreallocSegmentCnt, Segment, true> segments;
    SkPoint fanPt;

    if (!get_segments(*path, vm, &segments, &fanPt, &vCount, &iCount)) {
        return false;
    }

    GrDrawTarget::AutoReleaseGeometry arg(target, layout, vCount, iCount);
    if (!arg.succeeded()) {
        return false;
    }
    verts = reinterpret_cast<QuadVertex*>(arg.vertices());
    idxs = reinterpret_cast<uint16_t*>(arg.indices());

    create_vertices(segments, fanPt, verts, idxs);

    drawState->setVertexEdgeType(GrDrawState::kQuad_EdgeType);
    target->drawIndexed(kTriangles_PrimitiveType,
                        0,        // start vertex
                        0,        // start index
                        vCount,
                        iCount);
    return true;
}