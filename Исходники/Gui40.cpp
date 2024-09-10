void
Gui::renderSelectedNode()
{
    NodeGraph* graph = getLastSelectedGraph();

    if (!graph) {
        return;
    }

    NodesGuiList selectedNodes = graph->getSelectedNodes();

    if ( selectedNodes.empty() ) {
        Dialogs::warningDialog( tr("Render").toStdString(), tr("You must select a node to render first!").toStdString() );

        return;
    }
    std::list<AppInstance::RenderWork> workList;
    bool useStats = getApp()->isRenderStatsActionChecked();
    for (NodesGuiList::const_iterator it = selectedNodes.begin();
         it != selectedNodes.end(); ++it) {
        NodePtr internalNode = (*it)->getNode();
        if (!internalNode) {
            continue;
        }
        EffectInstPtr effect = internalNode->getEffectInstance();
        if (!effect) {
            continue;
        }
        if ( effect->isWriter() ) {
            if ( !effect->areKnobsFrozen() ) {
                //if ((*it)->getNode()->is)
                ///if the node is a writer, just use it to render!
                AppInstance::RenderWork w;
                w.writer = dynamic_cast<OutputEffectInstance*>( effect.get() );
                assert(w.writer);
                w.firstFrame = INT_MIN;
                w.lastFrame = INT_MAX;
                w.frameStep = INT_MIN;
                w.useRenderStats = useStats;
                workList.push_back(w);
            }
        } else {
            if (selectedNodes.size() == 1) {
                ///create a node and connect it to the node and use it to render
#ifndef NATRON_ENABLE_IO_META_NODES
                NodePtr writer = createWriter();
#else
                NodeGraph* graph = selectedNodes.front()->getDagGui();
                NodePtr writer = getApp()->createWriter( "", eCreateNodeReasonInternal, graph->getGroup() );
#endif
                if (writer) {
                    AppInstance::RenderWork w;
                    w.writer = dynamic_cast<OutputEffectInstance*>( writer->getEffectInstance().get() );
                    assert(w.writer);
                    w.firstFrame = INT_MIN;
                    w.lastFrame = INT_MAX;
                    w.frameStep = INT_MIN;
                    w.useRenderStats = useStats;
                    workList.push_back(w);
                }
            }
        }
    }
    _imp->_appInstance->startWritersRendering(false, workList);
} // Gui::renderSelectedNode