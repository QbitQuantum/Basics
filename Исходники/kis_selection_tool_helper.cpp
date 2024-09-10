void KisSelectionToolHelper::selectPixelSelection(KisPixelSelectionSP selection, SelectionAction action)
{
    KisViewManager* view = m_canvas->viewManager();

    if (selection->selectedExactRect().isEmpty()) {
        m_canvas->viewManager()->selectionManager()->deselect();
        return;
    }

    KisProcessingApplicator applicator(view->image(),
                                       0 /* we need no automatic updates */,
                                       KisProcessingApplicator::SUPPORTS_WRAPAROUND_MODE,
                                       KisImageSignalVector() << ModifiedSignal,
                                       m_name);

    applicator.applyCommand(new LazyInitGlobalSelection(view));

    struct ApplyToPixelSelection : public KisTransactionBasedCommand {
        ApplyToPixelSelection(KisViewManager *view,
                              KisPixelSelectionSP selection,
                              SelectionAction action) : m_view(view),
                                                        m_selection(selection),
                                                        m_action(action) {}
        KisViewManager *m_view;
        KisPixelSelectionSP m_selection;
        SelectionAction m_action;

        KUndo2Command* paint() override {

            KisPixelSelectionSP pixelSelection = m_view->selection()->pixelSelection();
            KIS_ASSERT_RECOVER(pixelSelection) { return 0; }

            bool hasSelection = !pixelSelection->isEmpty();

            KisSelectionTransaction transaction(pixelSelection);

            if (!hasSelection && m_action == SELECTION_SUBTRACT) {
                pixelSelection->invert();
            }

            pixelSelection->applySelection(m_selection, m_action);

            const QRect imageBounds = m_view->image()->bounds();
            QRect selectionExactRect = m_view->selection()->selectedExactRect();

            if (!imageBounds.contains(selectionExactRect)) {
                pixelSelection->crop(imageBounds);
                if (pixelSelection->outlineCacheValid()) {
                    QPainterPath cache = pixelSelection->outlineCache();
                    QPainterPath imagePath;
                    imagePath.addRect(imageBounds);
                    cache &= imagePath;
                    pixelSelection->setOutlineCache(cache);
                }
                selectionExactRect &= imageBounds;
            }

            QRect dirtyRect = imageBounds;
            if (hasSelection && m_action != SELECTION_REPLACE && m_action != SELECTION_INTERSECT) {
                dirtyRect = m_selection->selectedRect();
            }
            m_view->selection()->updateProjection(dirtyRect);

            KUndo2Command *savedCommand = transaction.endAndTake();
            pixelSelection->setDirty(dirtyRect);

            if (selectionExactRect.isEmpty()) {
                KisCommandUtils::CompositeCommand *cmd = new KisCommandUtils::CompositeCommand();
                cmd->addCommand(savedCommand);
                cmd->addCommand(new KisDeselectGlobalSelectionCommand(m_view->image()));
                savedCommand = cmd;
            }

            return savedCommand;
        }
    };

    applicator.applyCommand(new ApplyToPixelSelection(view, selection, action));
    applicator.end();
}