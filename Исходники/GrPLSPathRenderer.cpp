    void onPrepareDraws(Target* target) const override {
        int instanceCount = fGeoData.count();

        SkMatrix invert;
        if (this->usesLocalCoords() && !this->viewMatrix().invert(&invert)) {
            SkDebugf("Could not invert viewmatrix\n");
            return;
        }

        // Setup GrGeometryProcessors
        SkAutoTUnref<GrPLSGeometryProcessor> triangleProcessor(
                PLSAATriangleEffect::Create(invert, this->usesLocalCoords()));
        SkAutoTUnref<GrPLSGeometryProcessor> quadProcessor(
                PLSQuadEdgeEffect::Create(invert, this->usesLocalCoords()));

        GrResourceProvider* rp = target->resourceProvider();
        for (int i = 0; i < instanceCount; ++i) {
            const Geometry& args = fGeoData[i];
            SkRect bounds = args.fPath.getBounds();
            args.fViewMatrix.mapRect(&bounds);
            bounds.fLeft = SkScalarFloorToScalar(bounds.fLeft);
            bounds.fTop = SkScalarFloorToScalar(bounds.fTop);
            bounds.fRight = SkScalarCeilToScalar(bounds.fRight);
            bounds.fBottom = SkScalarCeilToScalar(bounds.fBottom);
            triangleProcessor->setBounds(bounds);
            quadProcessor->setBounds(bounds);

            // We use the fact that SkPath::transform path does subdivision based on
            // perspective. Otherwise, we apply the view matrix when copying to the
            // segment representation.
            const SkMatrix* viewMatrix = &args.fViewMatrix;

            // We avoid initializing the path unless we have to
            const SkPath* pathPtr = &args.fPath;
            SkTLazy<SkPath> tmpPath;
            if (viewMatrix->hasPerspective()) {
                SkPath* tmpPathPtr = tmpPath.init(*pathPtr);
                tmpPathPtr->setIsVolatile(true);
                tmpPathPtr->transform(*viewMatrix);
                viewMatrix = &SkMatrix::I();
                pathPtr = tmpPathPtr;
            }

            GrVertices grVertices;

            PLSVertices triVertices;
            PLSVertices quadVertices;
            if (!get_geometry(*pathPtr, *viewMatrix, triVertices, quadVertices, rp, bounds)) {
                continue;
            }

            if (triVertices.count()) {
                const GrVertexBuffer* triVertexBuffer;
                int firstTriVertex;
                size_t triStride = triangleProcessor->getVertexStride();
                PLSVertex* triVerts = reinterpret_cast<PLSVertex*>(target->makeVertexSpace(
                        triStride, triVertices.count(), &triVertexBuffer, &firstTriVertex));
                if (!triVerts) {
                    SkDebugf("Could not allocate vertices\n");
                    return;
                }
                for (int i = 0; i < triVertices.count(); ++i) {
                    triVerts[i] = triVertices[i];
                }
                grVertices.init(kTriangles_GrPrimitiveType, triVertexBuffer, firstTriVertex, 
                                triVertices.count());
                target->initDraw(triangleProcessor, this->pipeline());
                target->draw(grVertices);
            }

            if (quadVertices.count()) {
                const GrVertexBuffer* quadVertexBuffer;
                int firstQuadVertex;
                size_t quadStride = quadProcessor->getVertexStride();
                PLSVertex* quadVerts = reinterpret_cast<PLSVertex*>(target->makeVertexSpace(
                        quadStride, quadVertices.count(), &quadVertexBuffer, &firstQuadVertex));
                if (!quadVerts) {
                    SkDebugf("Could not allocate vertices\n");
                    return;
                }
                for (int i = 0; i < quadVertices.count(); ++i) {
                    quadVerts[i] = quadVertices[i];
                }
                grVertices.init(kTriangles_GrPrimitiveType, quadVertexBuffer, firstQuadVertex, 
                                quadVertices.count());
                target->initDraw(quadProcessor, this->pipeline());
                target->draw(grVertices);
            }

            SkAutoTUnref<GrGeometryProcessor> finishProcessor(
                    PLSFinishEffect::Create(this->color(), 
                                            pathPtr->getFillType() == 
                                                                SkPath::FillType::kEvenOdd_FillType,
                                            invert, 
                                            this->usesLocalCoords()));
            const GrVertexBuffer* rectVertexBuffer;
            size_t finishStride = finishProcessor->getVertexStride();
            int firstRectVertex;
            static const int kRectVertexCount = 6;
            SkPoint* rectVerts = reinterpret_cast<SkPoint*>(target->makeVertexSpace(
                    finishStride, kRectVertexCount, &rectVertexBuffer, &firstRectVertex));
            if (!rectVerts) {
                SkDebugf("Could not allocate vertices\n");
                return;
            }
            rectVerts[0] = { bounds.fLeft, bounds.fTop };
            rectVerts[1] = { bounds.fLeft, bounds.fBottom };
            rectVerts[2] = { bounds.fRight, bounds.fBottom };
            rectVerts[3] = { bounds.fLeft, bounds.fTop };
            rectVerts[4] = { bounds.fRight, bounds.fTop };
            rectVerts[5] = { bounds.fRight, bounds.fBottom };

            grVertices.init(kTriangles_GrPrimitiveType, rectVertexBuffer, firstRectVertex, 
                            kRectVertexCount);
            target->initDraw(finishProcessor, this->pipeline());
            target->draw(grVertices);
        }
    }