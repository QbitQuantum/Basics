//-----------------------------------------------------------------------------
//
//   calcChainedFollowPos.    Modify the previously calculated followPos sets
//                            to implement rule chaining.  NOT described by Aho
//
//-----------------------------------------------------------------------------
void RBBITableBuilder::calcChainedFollowPos(RBBINode *tree) {

    UVector         endMarkerNodes(*fStatus);
    UVector         leafNodes(*fStatus);
    int32_t         i;

    if (U_FAILURE(*fStatus)) {
        return;
    }

    // get a list of all endmarker nodes.
    tree->findNodes(&endMarkerNodes, RBBINode::endMark, *fStatus);

    // get a list all leaf nodes
    tree->findNodes(&leafNodes, RBBINode::leafChar, *fStatus);
    if (U_FAILURE(*fStatus)) {
        return;
    }

    // Get all nodes that can be the start a match, which is FirstPosition()
    // of the portion of the tree corresponding to user-written rules.
    // See the tree description in bofFixup().
    RBBINode *userRuleRoot = tree;
    if (fRB->fSetBuilder->sawBOF()) {
        userRuleRoot = tree->fLeftChild->fRightChild;
    }
    U_ASSERT(userRuleRoot != NULL);
    UVector *matchStartNodes = userRuleRoot->fFirstPosSet;


    // Iteratate over all leaf nodes,
    //
    int32_t  endNodeIx;
    int32_t  startNodeIx;

    for (endNodeIx=0; endNodeIx<leafNodes.size(); endNodeIx++) {
        RBBINode *tNode   = (RBBINode *)leafNodes.elementAt(endNodeIx);
        RBBINode *endNode = NULL;

        // Identify leaf nodes that correspond to overall rule match positions.
        //   These include an endMarkerNode in their followPos sets.
        for (i=0; i<endMarkerNodes.size(); i++) {
            if (tNode->fFollowPos->contains(endMarkerNodes.elementAt(i))) {
                endNode = tNode;
                break;
            }
        }
        if (endNode == NULL) {
            // node wasn't an end node.  Try again with the next.
            continue;
        }

        // We've got a node that can end a match.

        // Line Break Specific hack:  If this node's val correspond to the $CM char class,
        //                            don't chain from it.
        // TODO:  Add rule syntax for this behavior, get specifics out of here and
        //        into the rule file.
        if (fRB->fLBCMNoChain) {
            UChar32 c = this->fRB->fSetBuilder->getFirstChar(endNode->fVal);
            if (c != -1) {
                // c == -1 occurs with sets containing only the {eof} marker string.
                ULineBreak cLBProp = (ULineBreak)u_getIntPropertyValue(c, UCHAR_LINE_BREAK);
                if (cLBProp == U_LB_COMBINING_MARK) {
                    continue;
                }
            }
        }


        // Now iterate over the nodes that can start a match, looking for ones
        //   with the same char class as our ending node.
        RBBINode *startNode;
        for (startNodeIx = 0; startNodeIx<matchStartNodes->size(); startNodeIx++) {
            startNode = (RBBINode *)matchStartNodes->elementAt(startNodeIx);
            if (startNode->fType != RBBINode::leafChar) {
                continue;
            }

            if (endNode->fVal == startNode->fVal) {
                // The end val (character class) of one possible match is the
                //   same as the start of another.

                // Add all nodes from the followPos of the start node to the
                //  followPos set of the end node, which will have the effect of
                //  letting matches transition from a match state at endNode
                //  to the second char of a match starting with startNode.
                setAdd(endNode->fFollowPos, startNode->fFollowPos);
            }
        }
    }
}