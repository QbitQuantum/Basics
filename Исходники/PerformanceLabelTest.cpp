void LabelMenuLayer::showCurrentTest()
{
    auto scene = (LabelMainScene*) getParent();
    scene->autoShowLabelTests(_curCase,LabelMainScene::AUTO_TEST_NODE_NUM);
}