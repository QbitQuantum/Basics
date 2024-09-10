void ObjectsPropgridHelper::UpdateBehaviorsSharedData(gd::Project & project, gd::Layout * scene) const
{
    if ( scene )
        scene->UpdateBehaviorsSharedData(project);
    else //Scene pointer is NULL: Update shared data of all scenes
    {
        for (std::size_t i = 0;i<project.GetLayoutsCount();++i)
            project.GetLayout(i).UpdateBehaviorsSharedData(project);
    }
}