bool GameObjectModel::Relocate(const GameObject& go)
{
    if (!iModel)
        return false;

    ModelList::const_iterator it = model_list.find(go.GetDisplayId());
    if (it == model_list.end())
        return false;

    G3D::AABox mdl_box(it->second.bound);
    // ignore models with no bounds
    if (mdl_box == G3D::AABox::zero())
    {
        VMAP_ERROR_LOG("misc", "GameObject model %s has zero bounds, loading skipped", it->second.name.c_str());
        return false;
    }

    iPos = Vector3(go.GetPositionX(), go.GetPositionY(), go.GetPositionZ());

    G3D::Matrix3 iRotation = G3D::Matrix3::fromEulerAnglesZYX(go.GetOrientation(), 0, 0);
    iInvRot = iRotation.inverse();
    // transform bounding box:
    mdl_box = AABox(mdl_box.low() * iScale, mdl_box.high() * iScale);
    AABox rotated_bounds;
    for (int i = 0; i < 8; ++i)
        rotated_bounds.merge(iRotation * mdl_box.corner(i));

    iBound = rotated_bounds + iPos;
#ifdef SPAWN_CORNERS
    // test:
    for (int i = 0; i < 8; ++i)
    {
        Vector3 pos(iBound.corner(i));
        go.SummonCreature(1, pos.x, pos.y, pos.z, 0, TEMPSUMMON_MANUAL_DESPAWN);
    }
#endif

    return true;
}