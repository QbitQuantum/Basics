void RS_ActionBlocksAttributes::trigger() {
    RS_DEBUG->print("editing block attributes");

    if (graphic!=NULL && RS_DIALOGFACTORY!=NULL) {
        RS_Block* block = graphic->getActiveBlock();
        RS_BlockList* blockList = graphic->getBlockList();
        if (blockList!=NULL && block!=NULL) {
            QString oldName = block->getName();

            RS_BlockData d;
            d = RS_DIALOGFACTORY->requestBlockAttributesDialog(
                    blockList);

            if (d.isValid()) {

                QString newName = d.name;
                blockList->rename(block, newName);

                // update the name of all inserts:
                graphic->renameInserts(oldName, newName);

                graphic->addBlockNotification();
            }
        }

    }
    finish();
}