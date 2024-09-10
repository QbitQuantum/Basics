void
NodeGraph::checkForHints(bool shiftdown,
                         bool controlDown,
                         const NodeGuiPtr& selectedNode,
                         const QRectF& visibleSceneR)
{
    NodePtr internalNode = selectedNode->getNode();
    bool doMergeHints = shiftdown && controlDown;
    bool doConnectionHints = appPTR->getCurrentSettings()->isConnectionHintEnabled();

    //Ignore hints for backdrops
    BackdropGui* isBd = dynamic_cast<BackdropGui*>( selectedNode.get() );

    if (isBd) {
        return;
    }

    if (!doMergeHints) {
        ///for nodes already connected don't show hint
        if ( ( internalNode->getMaxInputCount() == 0) && internalNode->hasOutputConnected() ) {
            doConnectionHints = false;
        } else if ( ( internalNode->getMaxInputCount() > 0) && internalNode->hasAllInputsConnected() && internalNode->hasOutputConnected() ) {
            doConnectionHints = false;
        }
    }

    if (!doConnectionHints) {
        return;
    }

    QRectF selectedNodeBbox = selectedNode->boundingRectWithEdges(); //selectedNode->mapToParent( selectedNode->boundingRect() ).boundingRect();
    double tolerance = 10;
    selectedNodeBbox.adjust(-tolerance, -tolerance, tolerance, tolerance);

    NodeGuiPtr nodeToShowMergeRect;
    NodePtr selectedNodeInternalNode = selectedNode->getNode();
    bool selectedNodeIsReader = selectedNodeInternalNode->getEffectInstance()->isReader() || selectedNodeInternalNode->getMaxInputCount() == 0;
    Edge* edge = 0;
    std::set<NodeGui*> nodesWithinRect;
    getNodesWithinViewportRect(visibleWidgetRect(), &nodesWithinRect);

    {
        for (std::set<NodeGui*>::iterator it = nodesWithinRect.begin(); it != nodesWithinRect.end(); ++it) {
            bool isAlreadyAnOutput = false;
            const NodesWList& outputs = internalNode->getGuiOutputs();
            for (NodesWList::const_iterator it2 = outputs.begin(); it2 != outputs.end(); ++it2) {
                NodePtr node = it2->lock();
                if (!node) {
                    continue;
                }
                if ( node == (*it)->getNode() ) {
                    isAlreadyAnOutput = true;
                    break;
                }
            }
            if (isAlreadyAnOutput) {
                continue;
            }
            QRectF nodeBbox = (*it)->boundingRectWithEdges();
            if ( ( (*it) != selectedNode.get() ) && (*it)->isVisible() && nodeBbox.intersects(visibleSceneR) ) {
                if (doMergeHints) {
                    //QRectF nodeRect = (*it)->mapToParent((*it)->boundingRect()).boundingRect();

                    NodePtr internalNode = (*it)->getNode();


                    if ( !internalNode->isOutputNode() && nodeBbox.intersects(selectedNodeBbox) ) {
                        bool nHasInput = internalNode->hasInputConnected();
                        int nMaxInput = internalNode->getMaxInputCount();
                        bool selectedHasInput = selectedNodeInternalNode->hasInputConnected();
                        int selectedMaxInput = selectedNodeInternalNode->getMaxInputCount();
                        double nPAR = internalNode->getEffectInstance()->getAspectRatio(-1);
                        double selectedPAR = selectedNodeInternalNode->getEffectInstance()->getAspectRatio(-1);
                        double nFPS = internalNode->getEffectInstance()->getFrameRate();
                        double selectedFPS = selectedNodeInternalNode->getEffectInstance()->getFrameRate();
                        bool isValid = true;

                        if ( (selectedPAR != nPAR) || (std::abs(nFPS - selectedFPS) > 0.01) ) {
                            if (nHasInput || selectedHasInput) {
                                isValid = false;
                            } else if ( !nHasInput && (nMaxInput == 0) && !selectedHasInput && (selectedMaxInput == 0) ) {
                                isValid = false;
                            }
                        }
                        if (isValid) {
                            nodeToShowMergeRect = (*it)->shared_from_this();
                        }
                    } else {
                        (*it)->setMergeHintActive(false);
                    }
                } else { //!doMergeHints
                    edge = (*it)->hasEdgeNearbyRect(selectedNodeBbox);

                    ///if the edge input is the selected node don't continue
                    if ( edge && ( edge->getSource() == selectedNode) ) {
                        edge = 0;
                    }

                    if ( edge && edge->isOutputEdge() ) {
                        if (selectedNodeIsReader) {
                            continue;
                        }
                        int prefInput = selectedNodeInternalNode->getPreferredInputForConnection();
                        if (prefInput == -1) {
                            edge = 0;
                        } else {
                            Node::CanConnectInputReturnValue ret = selectedNodeInternalNode->canConnectInput(edge->getSource()->getNode(),
                                                                   prefInput);
                            if (ret != Node::eCanConnectInput_ok) {
                                edge = 0;
                            }
                        }
                    }

                    if ( edge && !edge->isOutputEdge() ) {
                        if ( (*it)->getNode()->getEffectInstance()->isReader() ||
                                ( (*it)->getNode()->getMaxInputCount() == 0 ) ) {
                            edge = 0;
                            continue;
                        }

                        if ( (*it)->getNode()->getEffectInstance()->isInputRotoBrush( edge->getInputNumber() ) ) {
                            edge = 0;
                            continue;
                        }

                        //Check that the edge can connect to the selected node
                        {
                            Node::CanConnectInputReturnValue ret = edge->getDest()->getNode()->canConnectInput( selectedNodeInternalNode, edge->getInputNumber() );
                            if ( (ret == Node::eCanConnectInput_inputAlreadyConnected) &&
                                    !selectedNodeIsReader ) {
                                ret = Node::eCanConnectInput_ok;
                            }

                            if (ret != Node::eCanConnectInput_ok) {
                                edge = 0;
                            }
                        }

                        //Check that the selected node can connect to the input of the edge

                        if (edge) {
                            NodeGuiPtr edgeHasSource = edge->getSource();
                            if (edgeHasSource) {
                                int prefInput = selectedNodeInternalNode->getPreferredInputForConnection();
                                if (prefInput != -1) {
                                    Node::CanConnectInputReturnValue ret = selectedNodeInternalNode->canConnectInput(edgeHasSource->getNode(), prefInput);
                                    if ( (ret == Node::eCanConnectInput_inputAlreadyConnected) &&
                                            !selectedNodeIsReader ) {
                                        ret = Node::eCanConnectInput_ok;
                                    }

                                    if (ret != Node::eCanConnectInput_ok) {
                                        edge = 0;
                                    }
                                }
                            }
                        }
                    }

                    if (edge) {
                        edge->setUseHighlight(true);
                        break;
                    }
                } // doMergeHints
            }
        }
    } // QMutexLocker l(&_imp->_nodesMutex);

    if ( _imp->_highLightedEdge && ( _imp->_highLightedEdge != edge) ) {
        _imp->_highLightedEdge->setUseHighlight(false);
        _imp->_hintInputEdge->hide();
        _imp->_hintOutputEdge->hide();
    }

    _imp->_highLightedEdge = edge;

    if ( edge && edge->getSource() && edge->getDest() ) {
        ///setup the hints edge

        ///find out if the node is already connected to what the edge is connected
        bool alreadyConnected = false;
        const std::vector<NodeWPtr > & inpNodes = selectedNode->getNode()->getGuiInputs();
        for (std::size_t i = 0; i < inpNodes.size(); ++i) {
            if ( inpNodes[i].lock() == edge->getSource()->getNode() ) {
                alreadyConnected = true;
                break;
            }
        }

        if ( !_imp->_hintInputEdge->isVisible() ) {
            if (!alreadyConnected) {
                int prefInput = selectedNode->getNode()->getPreferredInputForConnection();
                _imp->_hintInputEdge->setInputNumber(prefInput != -1 ? prefInput : 0);
                _imp->_hintInputEdge->setSourceAndDestination(edge->getSource(), selectedNode);
                _imp->_hintInputEdge->setVisible(true);
            }
            _imp->_hintOutputEdge->setInputNumber( edge->getInputNumber() );
            _imp->_hintOutputEdge->setSourceAndDestination( selectedNode, edge->getDest() );
            _imp->_hintOutputEdge->setVisible(true);
        } else {
            if (!alreadyConnected) {
                _imp->_hintInputEdge->initLine();
            }
            _imp->_hintOutputEdge->initLine();
        }
    } else if (edge) {
        ///setup only 1 of the hints edge

        if ( _imp->_highLightedEdge && !_imp->_hintInputEdge->isVisible() ) {
            if ( edge->isOutputEdge() ) {
                int prefInput = selectedNode->getNode()->getPreferredInputForConnection();
                _imp->_hintInputEdge->setInputNumber(prefInput != -1 ? prefInput : 0);
                _imp->_hintInputEdge->setSourceAndDestination(edge->getSource(), selectedNode);
            } else {
                _imp->_hintInputEdge->setInputNumber( edge->getInputNumber() );
                _imp->_hintInputEdge->setSourceAndDestination( selectedNode, edge->getDest() );
            }
            _imp->_hintInputEdge->setVisible(true);
        } else if ( _imp->_highLightedEdge && _imp->_hintInputEdge->isVisible() ) {
            _imp->_hintInputEdge->initLine();
        }
    } else if (nodeToShowMergeRect) {
        nodeToShowMergeRect->setMergeHintActive(true);
        selectedNode->setMergeHintActive(true);
        _imp->_mergeHintNode = nodeToShowMergeRect;
    } else {
        selectedNode->setMergeHintActive(false);
        _imp->_mergeHintNode.reset();
    }
} // NodeGraph::checkForHints