LLPanel* LLFloaterSidePanelContainer::openChildPanel(const std::string& panel_name, const LLSD& params)
{
    LLView* view = findChildView(panel_name, true);
    if (!view) return NULL;

    if (!getVisible())
    {
        openFloater();
    }

    LLPanel* panel = NULL;

    LLSideTrayPanelContainer* container = dynamic_cast<LLSideTrayPanelContainer*>(view->getParent());
    if (container)
    {
        LLSD new_params = params;
        new_params[LLSideTrayPanelContainer::PARAM_SUB_PANEL_NAME] = panel_name;
        container->onOpen(new_params);

        panel = container->getCurrentPanel();
    }
    else if ((panel = dynamic_cast<LLPanel*>(view)) != NULL)
    {
        panel->onOpen(params);
    }

    return panel;
}