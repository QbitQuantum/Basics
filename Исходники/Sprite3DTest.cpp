void Sprite3DWithOBBPerfromanceTest::onTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{
    for (auto touch: touches)
    {
        auto location = touch->getLocationInView();
        auto obbSize = _obb.size();
        if(obbSize)
        {
            _intersetList.clear();
            Ray ray;
            calculateRayByLocationInView(&ray,location);
            for(decltype(obbSize) i = 0; i < obbSize; i++)
            {
                if(ray.intersects(_obb[i]))
                {
                    _intersetList.insert((int)i);
                    return;
                }
            }
        }
    }
}