    /**
     * Update lighting contribution for the specified contributor @a index.
     *
     * @param index          Unique index of the contributor.
     * @param point          Point in the map to evaluate.
     * @param normalAtPoint  Surface normal at @a point.
     * @param bspRoot        Root BSP element for the map.
     */
    void updateContribution(int index, Vector3d const &point,
        Vector3f const &normalAtPoint, MapElement &bspRoot)
    {
        DENG_ASSERT(tracker != 0);

        BiasSource const &source = tracker->contributor(index);
        Vector3f &casted = contribution(index);

        /// @todo LineSightTest should (optionally) perform this test.
        SectorCluster *cluster = source.bspLeafAtOrigin().clusterPtr();
        if(!cluster)
        {
            // This affecting source does not contribute any light.
            casted = Vector3f();
            return;
        }

        if((!cluster->visFloor().surface().hasSkyMaskedMaterial() &&
                source.origin().z < cluster->visFloor().heightSmoothed()) ||
           (!cluster->visCeiling().surface().hasSkyMaskedMaterial() &&
                source.origin().z > cluster->visCeiling().heightSmoothed()))
        {
            casted = Vector3f();
            return;
        }

        Vector3d sourceToPoint = source.origin() - point;
        double distance = sourceToPoint.length();
        double dot = sourceToPoint.normalize().dot(normalAtPoint);

        // The point faces away from the light?
        if(dot < 0)
        {
            casted = Vector3f();
            return;
        }

        if(devUseSightCheck &&
           !LineSightTest(source.origin(), point + sourceToPoint / 100)
                        .trace(bspRoot))
        {
            // LOS fail.
            casted = Vector3f();
            return;
        }

        // Apply light casted from this source.
        float strength = dot * source.evaluateIntensity() / distance;
        casted = source.color() * de::clamp(0.f, strength, 1.f);
    }