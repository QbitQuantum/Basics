void BindDialog::setSceneData(osg::ref_ptr<osg::Node> pModel)
{
    NodeVisitor visitor( ui->nodeTree->invisibleRootItem() );
    pModel->accept(visitor);
    ui->nodeTree->expandAll();
}