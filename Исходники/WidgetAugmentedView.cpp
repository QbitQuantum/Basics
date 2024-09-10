bool WidgetAugmentedView::render()
{
    if (!stream) return false;
    stream->getColorFrame(colorFrame);
    stream->getDepthFrame(depthFrame);

    // Correct the depth map
    if (depthCorrector == nullptr) depthBuffer = depthFrame;
    else depthCorrector->correct(depthFrame, depthBuffer);

    // Setup perspective
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovY, float(ColorFrame::WIDTH) / float(ColorFrame::HEIGHT), zNear, zFar);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    glEnable(GL_DEPTH_TEST);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);


    //
    // Draw real world (2D color image)
    //

    glDepthFunc(GL_ALWAYS);

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, textureColor);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, ColorFrame::WIDTH, ColorFrame::HEIGHT,
        GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)colorFrame.pixels);

    glActiveTexture(GL_TEXTURE1);

    glBindTexture(GL_TEXTURE_2D, textureDepth);

    KinectStream* kinect = dynamic_cast<KinectStream*>(stream.obj);
    if (kinect != nullptr) {
        kinect->mapColorFrameToDepthFrame(depthBuffer, OUT mapping);

        const NUI_DEPTH_IMAGE_POINT* src = mapping;
        GLushort* dest = textureDepthBuffer;
        GLushort* end = textureDepthBuffer + ColorFrame::SIZE;

        #define SRC(i) static_cast<short>(static_cast<unsigned short>((src + i)->depth))

        #ifndef NOT_VECTORIZED
            // Vectorized assuming ColorFrame::SIZE % 8 == 0
            __m128i min = _mm_set1_epi16(static_cast<short>(DepthFrame::MIN_DEPTH));
            __m128i max = _mm_set1_epi16(static_cast<short>(DepthFrame::MAX_DEPTH));
            __m128i _0 = _mm_setzero_si128();
            for (; dest < end; dest += 8, src += 8) {
                __m128i v = _mm_set_epi16(SRC(7), SRC(6), SRC(5), SRC(4), SRC(3), SRC(2), SRC(1), SRC(0));
                v = _mm_max_epu16(min, _mm_min_epu16(max, v));
                v = _mm_blendv_epi8(v, max, _mm_cmpeq_epi16(_0, v));
                _mm_store_si128((__m128i*)dest, v);
            }
        #else
            for (; dest < end; ++dest, ++src) {
                unsigned short s = SRC(0);
                s = (s > DepthFrame::MAX_DEPTH) ? DepthFrame::MAX_DEPTH : s;
                s = (s < DepthFrame::MIN_DEPTH) ? DepthFrame::MIN_DEPTH : s;
                *dest = static_cast<GLushort>(s);
            }
        #endif

        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, ColorFrame::WIDTH, ColorFrame::HEIGHT,
            GL_RED_INTEGER, GL_UNSIGNED_SHORT, (GLvoid*)textureDepthBuffer);
    }

    glActiveTexture(GL_TEXTURE0);

    shader2D.bind();

    RenderUtils::drawRect(-1.0f, 1.0f, 2.0f, -2.0f);

    shader2D.release();

    //
    // Draw augmented world
    //

    glDepthFunc(GL_LESS);

    glScalef(1.0f, 1.0f, -1.0f); // Invert Z axis so that +Z is in front of the camera

    // A plane to test occlusion
    /*glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(-0.5f, -0.5f, 0.5f);
        glVertex3f(-0.5f, 0.5f, 2.5f);
        glVertex3f(0.5f, -0.5f, 2.5f);
        glVertex3f(0.5f, 0.5f, 4.5f);
    glEnd();*/

    glEnable(GL_LIGHTING);

    // Draw the objects
    world.render(renderManager);

    glDisable(GL_LIGHTING);

    return true;
}