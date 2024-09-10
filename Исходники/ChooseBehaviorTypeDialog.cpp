bool ChooseBehaviorTypeDialog::ChooseAndAddBehaviorToObject(wxWindow * parent, gd::Project & project, gd::Object * object, gd::Layout * layout, bool isGlobalObject)
{
    gd::ChooseBehaviorTypeDialog dialog(parent, project);
    if ( dialog.ShowModal() == 1)
    {
        //Find behavior metadata
        std::shared_ptr<gd::PlatformExtension> extension = std::shared_ptr<gd::PlatformExtension> ();
        std::vector < std::shared_ptr<gd::PlatformExtension> > extensions = project.GetCurrentPlatform().GetAllPlatformExtensions();
        for (std::size_t i = 0;i<extensions.size();++i)
        {
            std::vector<gd::String> behaviorsTypes = extensions[i]->GetBehaviorsTypes();
            if ( find(behaviorsTypes.begin(), behaviorsTypes.end(), dialog.GetSelectedBehaviorType()) != behaviorsTypes.end() )
                extension = extensions[i];
        }
        gd::BehaviorMetadata metadata = extension->GetBehaviorMetadata(dialog.GetSelectedBehaviorType());

        //Add behavior to object
        gd::String autoName = metadata.GetDefaultName();
        for (std::size_t j = 2;object->HasBehaviorNamed(autoName);++j)
            autoName = metadata.GetDefaultName()+gd::String::From(j);

        object->AddNewBehavior(project, dialog.GetSelectedBehaviorType(), autoName);

        //Let the scene know about the new behavior
        if ( isGlobalObject && layout )
            layout->UpdateBehaviorsSharedData(project);
        else //Scene pointer is NULL: Update shared data of all layouts
        {
            for (std::size_t i = 0;i<project.GetLayoutsCount();++i)
                project.GetLayout(i).UpdateBehaviorsSharedData(project);
        }

        for (std::size_t j = 0; j < project.GetUsedPlatforms().size();++j)
            project.GetUsedPlatforms()[j]->GetChangesNotifier().OnBehaviorAdded(project, isGlobalObject ? NULL : layout, *object, object->GetBehavior(autoName));

        return true;
    }

    return false;
}