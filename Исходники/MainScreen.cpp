void MainScreen::UpdatePhysics(float dt)
{
    (void) dt;

    auto& scene = mScene;
    SceneNode* teapot = mScene->FindNodeByUuid("teapot_1");
    for(auto& p : scene->GetNodes())
    {
        SceneNode* cur = p.second.get();
        if(cur->GetUUID() == teapot->GetUUID())
            continue;

        if(Intersects(teapot->GetAABB(), cur->GetAABB()))
            scene->Move(teapot, CalcCollisionResponce(teapot->GetAABB(), cur->GetAABB()));
    }
}