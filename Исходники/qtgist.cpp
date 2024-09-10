/// TODO
void
Gist::on_canvas_statusChanged(VisualNode* n, const Statistics& stats,
                              bool finished) {

    nodeStatInspector->node(execution->getNA(),n,stats,finished); /// for single node stats

    if (!finished) {
        showNodeStats->setEnabled(false);
        // stop-> setEnabled(true);
        // reset->setEnabled(false);

        navNextSol->setEnabled(false);
        navPrevSol->setEnabled(false);

        // searchNext->setEnabled(false);
        // searchAll->setEnabled(false);
        toggleHidden->setEnabled(false);
        hideFailed->setEnabled(false);
        // hideSize->setEnabled(false);

        // labelBranches->setEnabled(false);
        // labelPath->setEnabled(false);

        // toggleStop->setEnabled(false);
        // unstopAll->setEnabled(false);

        center->setEnabled(false); /// ??
        exportPDF->setEnabled(false);
        exportWholeTreePDF->setEnabled(false);
        print->setEnabled(false);
        // printSearchLog->setEnabled(false);

        bookmarkNode->setEnabled(false);
        bookmarksGroup->setEnabled(false);
    } else {
        // stop->setEnabled(false);
        // reset->setEnabled(true);

        if ( (n->isOpen() || n->hasOpenChildren()) && (!n->isHidden()) ) {
            // searchNext->setEnabled(true);
            // searchAll->setEnabled(true);
        } else {
            // searchNext->setEnabled(false);
            // searchAll->setEnabled(false);
        }
        if (n->getNumberOfChildren() > 0) {

            toggleHidden->setEnabled(true);
            hideFailed->setEnabled(true);
            // hideSize->setEnabled(true);
            // unstopAll->setEnabled(true);
        } else {
            toggleHidden->setEnabled(false);
            hideFailed->setEnabled(false);
            // hideSize->setEnabled(false);
            // unhideAll->setEnabled(false);
            // unstopAll->setEnabled(false);
        }

        toggleStop->setEnabled(n->getStatus() == STOP ||
                               n->getStatus() == UNSTOP);

        showNodeStats->setEnabled(true);
        labelPath->setEnabled(true);

        VisualNode* root = n;
        while (!root->isRoot()) {
            root = root->getParent(execution->getNA());
        }
        NextSolCursor nsc(n, false, execution->getNA());

        PreorderNodeVisitor<NextSolCursor> nsv(nsc);
        nsv.run();
        navNextSol->setEnabled(nsv.getCursor().node() != root);

        NextSolCursor psc(n, true, execution->getNA());

        PreorderNodeVisitor<NextSolCursor> psv(psc);
        psv.run();
        navPrevSol->setEnabled(psv.getCursor().node() != root);

        center->setEnabled(true);
        exportPDF->setEnabled(true);
        exportWholeTreePDF->setEnabled(true);
        print->setEnabled(true);
        printSearchLog->setEnabled(true);

        bookmarkNode->setEnabled(true);
        bookmarksGroup->setEnabled(true);
    }
    emit statusChanged(stats,finished);
}