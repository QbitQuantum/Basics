void DepthOfField::computeCoC
(RenderDevice*                  rd,
 const shared_ptr<Texture>&     color,
 const shared_ptr<Texture>&     depth,
 const shared_ptr<Camera>&      camera,
 Vector2int16                   trimBandThickness) {

    rd->push2D(m_packedFramebuffer);
    {
        rd->clear();

        shared_ptr<Shader> shader;
        if (camera->depthOfFieldSettings().model() == DepthOfFieldModel::ARTIST) {
            shader = m_artistCoCShader;
        } else {
            shader = m_physicalCoCShader;
        }

        Args args;

        args.setUniform("projInfo",     camera->projection().reconstructFromDepthProjInfo(depth->width(), depth->height()));
        args.setUniform("clipInfo",     camera->projection().reconstructFromDepthClipInfo());
        args.setUniform("color",        color);
        args.setUniform("depth",        depth);
        args.setUniform("trimBandThickness", trimBandThickness);

        if (camera->depthOfFieldSettings().model() == DepthOfFieldModel::ARTIST) {

            args.setUniform("nearBlurryPlaneZ", camera->depthOfFieldSettings().nearBlurryPlaneZ());
            args.setUniform("nearSharpPlaneZ",  camera->depthOfFieldSettings().nearSharpPlaneZ());
            args.setUniform("farSharpPlaneZ",   camera->depthOfFieldSettings().farSharpPlaneZ());
            args.setUniform("farBlurryPlaneZ",  camera->depthOfFieldSettings().farBlurryPlaneZ());

            const float maxRadiusFraction =
                max(max(camera->depthOfFieldSettings().nearBlurRadiusFraction(), camera->depthOfFieldSettings().farBlurRadiusFraction()), 0.001f);

            // This is a positive number
            const float nearNormalize =
                (1.0f / (camera->depthOfFieldSettings().nearBlurryPlaneZ() - camera->depthOfFieldSettings().nearSharpPlaneZ())) *
                (camera->depthOfFieldSettings().nearBlurRadiusFraction() / maxRadiusFraction);
            alwaysAssertM(nearNormalize >= 0.0f, "Near normalization must be a non-negative factor");
            args.setUniform("nearNormalize", nearNormalize);

            // This is a positive number
            const float farNormalize =
                (1.0f / (camera->depthOfFieldSettings().farSharpPlaneZ() - camera->depthOfFieldSettings().farBlurryPlaneZ())) *
                (camera->depthOfFieldSettings().farBlurRadiusFraction() / maxRadiusFraction);
            alwaysAssertM(farNormalize >= 0.0f, "Far normalization must be a non-negative factor");
            args.setUniform("farNormalize", farNormalize);

        } else {
            const float scale =
                camera->imagePlanePixelsPerMeter(rd->viewport()) * camera->depthOfFieldSettings().lensRadius() /
                (camera->depthOfFieldSettings().focusPlaneZ() * maxPhysicalBlurRadius(camera, color->rect2DBounds()));
            args.setUniform("focusPlaneZ", camera->depthOfFieldSettings().focusPlaneZ());
            args.setUniform("scale", scale);

        }
        args.setRect(rd->viewport());
        LAUNCH_SHADER_PTR(shader, args);

    }
    rd->pop2D();
}