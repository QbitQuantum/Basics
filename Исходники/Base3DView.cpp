void Base3DView::frameAll()
{
    Vector3F coi = sceneCenter();
    Vector3F eye = coi + Vector3F(0.f, 0.f, 100.f);
    
    getCamera()->lookFromTo(eye, coi);
}