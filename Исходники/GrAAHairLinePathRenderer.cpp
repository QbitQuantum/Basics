bool GrAAHairLinePathRenderer::createGeom(
            const SkPath& path,
            const GrVec* translate,
            GrDrawTarget* target,
            GrDrawState::StageMask stageMask,
            int* lineCnt,
            int* quadCnt,
            GrDrawTarget::AutoReleaseGeometry* arg) {
    const GrDrawState& drawState = target->getDrawState();
    int rtHeight = drawState.getRenderTarget()->height();

    GrIRect clip;
    if (target->getClip().hasConservativeBounds()) {
        GrRect clipRect =  target->getClip().getConservativeBounds();
        clipRect.roundOut(&clip);
    } else {
        clip.setLargest();
    }


    GrVertexLayout layout = GrDrawTarget::kEdge_VertexLayoutBit;
    GrMatrix viewM = drawState.getViewMatrix();

    PREALLOC_PTARRAY(128) lines;
    PREALLOC_PTARRAY(128) quads;
    IntArray qSubdivs;
    static const GrVec gZeroVec = {0, 0};
    if (NULL == translate) {
        translate = &gZeroVec;
    }
    *quadCnt = generate_lines_and_quads(path, viewM, *translate, clip,
                                        &lines, &quads, &qSubdivs);

    *lineCnt = lines.count() / 2;
    int vertCnt = kVertsPerLineSeg * *lineCnt + kVertsPerQuad * *quadCnt;

    GrAssert(sizeof(Vertex) == GrDrawTarget::VertexSize(layout));

    if (!arg->set(target, layout, vertCnt, 0)) {
        return false;
    }

    Vertex* verts = reinterpret_cast<Vertex*>(arg->vertices());

    const GrMatrix* toDevice = NULL;
    const GrMatrix* toSrc = NULL;
    GrMatrix ivm;

    if (viewM.hasPerspective()) {
        if (viewM.invert(&ivm)) {
            toDevice = &viewM;
            toSrc = &ivm;
        }
    }

    for (int i = 0; i < *lineCnt; ++i) {
        add_line(&lines[2*i], rtHeight, toSrc, &verts);
    }

    int unsubdivQuadCnt = quads.count() / 3;
    for (int i = 0; i < unsubdivQuadCnt; ++i) {
        GrAssert(qSubdivs[i] >= 0);
        add_quads(&quads[3*i], qSubdivs[i], toDevice, toSrc, &verts);
    }

    return true;
}