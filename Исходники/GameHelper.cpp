float CGameHelper::GuiTraceRayFeature(const float3& start, const float3& dir, float length, CFeature*& feature)
{
    float nearHit = length;

    GML_RECMUTEX_LOCK(quad); // GuiTraceRayFeature

    std::vector<int> quads = qf->GetQuadsOnRay(start, dir, length);
    std::vector<int>::iterator qi;

    for (qi = quads.begin(); qi != quads.end(); ++qi) {
        const CQuadField::Quad& quad = qf->GetQuad(*qi);
        std::list<CFeature*>::const_iterator ui;

        // NOTE: switch this to custom volumes fully?
        // (not used for any LOF checks, maybe wasteful)
        for (ui = quad.features.begin(); ui != quad.features.end(); ++ui) {
            CFeature* f = *ui;

            if (!gu->spectatingFullView && !f->IsInLosForAllyTeam(gu->myAllyTeam)) {
                continue;
            }
            if (f->noSelect) {
                continue;
            }

            CollisionVolume* cv = f->collisionVolume;
            const float3& midPosOffset = cv? cv->GetOffsets(): ZeroVector;
            const float3 dif = (f->midPos + midPosOffset) - start;
            float closeLength = dif.dot(dir);

            if (closeLength < 0)
                continue;
            if (closeLength > nearHit)
                continue;

            float3 closeVect = dif - dir * closeLength;
            if (closeVect.SqLength() < f->sqRadius) {
                nearHit = closeLength;
                feature = f;
            }
        }
    }

    return nearHit;
}