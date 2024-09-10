// react to keys
void keyboard(unsigned char k, int , int )
{
    switch(k)
    {
        case 27:
            onExit();
            OSG::osgExit();
            exit(0);
        break;
        case 'f':
            g_mgr->setNavigationMode(OSG::Navigator::FLY);
        break;
        case 't':
            g_mgr->setNavigationMode(OSG::Navigator::TRACKBALL);
        break;
        case 'q':
            g_mgr->setStatistics(true);
        break;
        case 'w':
            g_mgr->setStatistics(false);
        break;
        case 'r':
        {
            bool useTrav = !g_mgr->getUseTraversalAction();
            g_mgr->setUseTraversalAction(useTrav);
            printf("Using %s action.\n", useTrav ? "render traversal" : "render");
        }
        break;
    }
}