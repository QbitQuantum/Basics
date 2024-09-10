    void handleBlock(BlockIndex blockIndex)
    {
        BasicBlock* block = m_graph.block(blockIndex);
        if (!block)
            return;

        m_map.clear();

        // First we collect Ranges. If operations within the range have enough redundancy,
        // we hoist. And then we remove additions and checks that fall within the max range.

        for (unsigned nodeIndex = 0; nodeIndex < block->size(); ++nodeIndex) {
            Node* node = block->at(nodeIndex);
            RangeKeyAndAddend data = rangeKeyAndAddend(node);
            if (verbose)
                dataLog("For ", node, ": ", data, "\n");
            if (!data)
                continue;

            Range& range = m_map[data.m_key];
            if (verbose)
                dataLog("    Range: ", range, "\n");
            if (range.m_count) {
                if (data.m_addend > range.m_maxBound) {
                    range.m_maxBound = data.m_addend;
                    range.m_maxOrigin = node->origin.semantic;
                } else if (data.m_addend < range.m_minBound) {
                    range.m_minBound = data.m_addend;
                    range.m_minOrigin = node->origin.semantic;
                }
            } else {
                range.m_maxBound = data.m_addend;
                range.m_minBound = data.m_addend;
                range.m_minOrigin = node->origin.semantic;
                range.m_maxOrigin = node->origin.semantic;
            }
            range.m_count++;
            if (verbose)
                dataLog("    New range: ", range, "\n");
        }

        for (unsigned nodeIndex = 0; nodeIndex < block->size(); ++nodeIndex) {
            Node* node = block->at(nodeIndex);
            RangeKeyAndAddend data = rangeKeyAndAddend(node);
            if (!data)
                continue;
            Range range = m_map[data.m_key];
            if (!isValid(data.m_key, range))
                continue;

            // Do the hoisting.
            if (!range.m_hoisted) {
                switch (data.m_key.m_kind) {
                case Addition: {
                    if (range.m_minBound < 0) {
                        insertAdd(
                            nodeIndex, NodeOrigin(range.m_minOrigin, node->origin.forExit),
                            data.m_key.m_source, range.m_minBound);
                    }
                    if (range.m_maxBound > 0) {
                        insertAdd(
                            nodeIndex, NodeOrigin(range.m_maxOrigin, node->origin.forExit),
                            data.m_key.m_source, range.m_maxBound);
                    }
                    break;
                }

                case ArrayBounds: {
                    Node* minNode;
                    Node* maxNode;

                    if (!data.m_key.m_source) {
                        minNode = 0;
                        maxNode = m_insertionSet.insertConstant(
                            nodeIndex, range.m_maxOrigin, jsNumber(range.m_maxBound));
                    } else {
                        minNode = insertAdd(
                            nodeIndex, NodeOrigin(range.m_minOrigin, node->origin.forExit),
                            data.m_key.m_source, range.m_minBound, Arith::Unchecked);
                        maxNode = insertAdd(
                            nodeIndex, NodeOrigin(range.m_maxOrigin, node->origin.forExit),
                            data.m_key.m_source, range.m_maxBound, Arith::Unchecked);
                    }

                    if (minNode) {
                        m_insertionSet.insertNode(
                            nodeIndex, SpecNone, CheckInBounds, node->origin,
                            Edge(minNode, Int32Use), Edge(data.m_key.m_key, Int32Use));
                    }
                    m_insertionSet.insertNode(
                        nodeIndex, SpecNone, CheckInBounds, node->origin,
                        Edge(maxNode, Int32Use), Edge(data.m_key.m_key, Int32Use));
                    break;
                }

                default:
                    RELEASE_ASSERT_NOT_REACHED();
                }

                m_changed = true;
                m_map[data.m_key].m_hoisted = true;
            }

            // Do the elimination.
            switch (data.m_key.m_kind) {
            case Addition:
                node->setArithMode(Arith::Unchecked);
                m_changed = true;
                break;

            case ArrayBounds:
                node->remove();
                m_changed = true;
                break;

            default:
                RELEASE_ASSERT_NOT_REACHED();
            }
        }

        m_insertionSet.execute(block);
    }