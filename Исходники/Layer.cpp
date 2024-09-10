void Layer::onDraw(const sp<const DisplayDevice>& hw, const Region& clip) const
{
    ATRACE_CALL();

    if (CC_UNLIKELY(mActiveBuffer == 0)) {
        // the texture has not been created yet, this Layer has
        // in fact never been drawn into. This happens frequently with
        // SurfaceView because the WindowManager can't know when the client
        // has drawn the first time.

        // If there is nothing under us, we paint the screen in black, otherwise
        // we just skip this update.

        // figure out if there is something below us
        Region under;
        const SurfaceFlinger::LayerVector& drawingLayers(
                mFlinger->mDrawingState.layersSortedByZ);
        const size_t count = drawingLayers.size();
        for (size_t i=0 ; i<count ; ++i) {
            const sp<Layer>& layer(drawingLayers[i]);
            if (layer.get() == static_cast<Layer const*>(this))
                break;
            under.orSelf( hw->getTransform().transform(layer->visibleRegion) );
        }
        // if not everything below us is covered, we plug the holes!
        Region holes(clip.subtract(under));
        if (!holes.isEmpty()) {
            clearWithOpenGL(hw, holes, 0, 0, 0, 1);
        }
        return;
    }

    // Bind the current buffer to the GL texture, and wait for it to be
    // ready for us to draw into.
    status_t err = mSurfaceFlingerConsumer->bindTextureImage();
    if (err != NO_ERROR) {
        ALOGW("onDraw: bindTextureImage failed (err=%d)", err);
        // Go ahead and draw the buffer anyway; no matter what we do the screen
        // is probably going to have something visibly wrong.
    }

    bool canAllowGPU = false;
#ifdef QCOM_BSP
    if(isProtected()) {
        char property[PROPERTY_VALUE_MAX];
        if ((property_get("persist.gralloc.cp.level3", property, NULL) > 0) &&
                (atoi(property) == 1)) {
            canAllowGPU = true;
        }
    }
#endif

    bool blackOutLayer = isProtected() || (isSecure() && !hw->isSecure());

    RenderEngine& engine(mFlinger->getRenderEngine());

    if (!blackOutLayer || (canAllowGPU)) {
        // TODO: we could be more subtle with isFixedSize()
        const bool useFiltering = getFiltering() || needsFiltering(hw) || isFixedSize();

        // Query the texture matrix given our current filtering mode.
        float textureMatrix[16];
        mSurfaceFlingerConsumer->setFilteringEnabled(useFiltering);
        mSurfaceFlingerConsumer->getTransformMatrix(textureMatrix);

        if (mSurfaceFlingerConsumer->getTransformToDisplayInverse()) {

            /*
             * the code below applies the display's inverse transform to the texture transform
             */

            // create a 4x4 transform matrix from the display transform flags
            const mat4 flipH(-1,0,0,0,  0,1,0,0, 0,0,1,0, 1,0,0,1);
            const mat4 flipV( 1,0,0,0, 0,-1,0,0, 0,0,1,0, 0,1,0,1);
            const mat4 rot90( 0,1,0,0, -1,0,0,0, 0,0,1,0, 1,0,0,1);

            mat4 tr;
            uint32_t transform = hw->getOrientationTransform();
            if (transform & NATIVE_WINDOW_TRANSFORM_ROT_90)
                tr = tr * rot90;
            if (transform & NATIVE_WINDOW_TRANSFORM_FLIP_H)
                tr = tr * flipH;
            if (transform & NATIVE_WINDOW_TRANSFORM_FLIP_V)
                tr = tr * flipV;

            // calculate the inverse
            tr = inverse(tr);

            // and finally apply it to the original texture matrix
            const mat4 texTransform(mat4(static_cast<const float*>(textureMatrix)) * tr);
            memcpy(textureMatrix, texTransform.asArray(), sizeof(textureMatrix));
        }

        // Set things up for texturing.
        mTexture.setDimensions(mActiveBuffer->getWidth(), mActiveBuffer->getHeight());
        mTexture.setFiltering(useFiltering);
        mTexture.setMatrix(textureMatrix);

        engine.setupLayerTexturing(mTexture);
    } else {
        engine.setupLayerBlackedOut();
    }
    drawWithOpenGL(hw, clip);
    engine.disableTexturing();
}