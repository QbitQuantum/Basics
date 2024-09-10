void ChangesNotifier::OnAutomatismEdited(gd::Project & game, gd::Layout * scene, gd::Object & object, gd::Automatism & automatism) const
{
    if ( scene )
        scene->SetRefreshNeeded();
    else //Scene pointer is not NULL: Update shared data of all scenes
    {
        for (unsigned int i = 0;i<game.GetLayoutsCount();++i)
            game.GetLayout(i).SetRefreshNeeded();
    }
}