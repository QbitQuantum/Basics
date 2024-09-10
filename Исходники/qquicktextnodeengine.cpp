void QQuickTextNodeEngine::processCurrentLine()
{
    // No glyphs, do nothing
    if (m_currentLineTree.isEmpty())
        return;

    // 1. Go through current line and get correct decoration position for each node based on
    // neighbouring decorations. Add decoration to global list
    // 2. Create clip nodes for all selected text. Try to merge as many as possible within
    // the line.
    // 3. Add QRects to a list of selection rects.
    // 4. Add all nodes to a global processed list
    QVarLengthArray<int> sortedIndexes; // Indexes in tree sorted by x position
    BinaryTreeNode::inOrder(m_currentLineTree, &sortedIndexes);

    Q_ASSERT(sortedIndexes.size() == m_currentLineTree.size());

    SelectionState currentSelectionState = Unselected;
    QRectF currentRect;

    QQuickTextNode::Decorations currentDecorations = QQuickTextNode::NoDecoration;
    qreal underlineOffset = 0.0;
    qreal underlineThickness = 0.0;

    qreal overlineOffset = 0.0;
    qreal overlineThickness = 0.0;

    qreal strikeOutOffset = 0.0;
    qreal strikeOutThickness = 0.0;

    QRectF decorationRect = currentRect;

    QColor lastColor;
    QColor lastBackgroundColor;

    QVarLengthArray<TextDecoration> pendingUnderlines;
    QVarLengthArray<TextDecoration> pendingOverlines;
    QVarLengthArray<TextDecoration> pendingStrikeOuts;
    if (!sortedIndexes.isEmpty()) {
        QQuickDefaultClipNode *currentClipNode = m_hasSelection ? new QQuickDefaultClipNode(QRectF()) : 0;
        bool currentClipNodeUsed = false;
        for (int i=0; i<=sortedIndexes.size(); ++i) {
            BinaryTreeNode *node = 0;
            if (i < sortedIndexes.size()) {
                int sortedIndex = sortedIndexes.at(i);
                Q_ASSERT(sortedIndex < m_currentLineTree.size());

                node = m_currentLineTree.data() + sortedIndex;
            }

            if (i == 0)
                currentSelectionState = node->selectionState;

            // Update decorations
            if (currentDecorations != QQuickTextNode::NoDecoration) {
                decorationRect.setY(m_position.y() + m_currentLine.y());
                decorationRect.setHeight(m_currentLine.height());

                if (node != 0)
                    decorationRect.setRight(node->boundingRect.left());

                TextDecoration textDecoration(currentSelectionState, decorationRect, lastColor);
                if (currentDecorations & QQuickTextNode::Underline)
                    pendingUnderlines.append(textDecoration);

                if (currentDecorations & QQuickTextNode::Overline)
                    pendingOverlines.append(textDecoration);

                if (currentDecorations & QQuickTextNode::StrikeOut)
                    pendingStrikeOuts.append(textDecoration);

                if (currentDecorations & QQuickTextNode::Background)
                    m_backgrounds.append(qMakePair(decorationRect, lastBackgroundColor));
            }

            // If we've reached an unselected node from a selected node, we add the
            // selection rect to the graph, and we add decoration every time the
            // selection state changes, because that means the text color changes
            if (node == 0 || node->selectionState != currentSelectionState) {
                currentRect.setY(m_position.y() + m_currentLine.y());
                currentRect.setHeight(m_currentLine.height());

                if (currentSelectionState == Selected)
                    m_selectionRects.append(currentRect);

                if (currentClipNode != 0) {
                    if (!currentClipNodeUsed) {
                        delete currentClipNode;
                    } else {
                        currentClipNode->setIsRectangular(true);
                        currentClipNode->setRect(currentRect);
                        currentClipNode->update();
                    }
                }

                if (node != 0 && m_hasSelection)
                    currentClipNode = new QQuickDefaultClipNode(QRectF());
                else
                    currentClipNode = 0;
                currentClipNodeUsed = false;

                if (node != 0) {
                    currentSelectionState = node->selectionState;
                    currentRect = node->boundingRect;

                    // Make sure currentRect is valid, otherwise the unite won't work
                    if (currentRect.isNull())
                        currentRect.setSize(QSizeF(1, 1));
                }
            } else {
                if (currentRect.isNull())
                    currentRect = node->boundingRect;
                else
                    currentRect = currentRect.united(node->boundingRect);
            }

            if (node != 0) {
                if (node->selectionState == Selected) {
                    node->clipNode = currentClipNode;
                    currentClipNodeUsed = true;
                }

                decorationRect = node->boundingRect;

                // If previous item(s) had underline and current does not, then we add the
                // pending lines to the lists and likewise for overlines and strikeouts
                if (!pendingUnderlines.isEmpty()
                        && !(node->decorations & QQuickTextNode::Underline)) {
                    addTextDecorations(pendingUnderlines, underlineOffset, underlineThickness);

                    pendingUnderlines.clear();

                    underlineOffset = 0.0;
                    underlineThickness = 0.0;
                }

                // ### Add pending when overlineOffset/thickness changes to minimize number of
                // nodes
                if (!pendingOverlines.isEmpty()) {
                    addTextDecorations(pendingOverlines, overlineOffset, overlineThickness);

                    pendingOverlines.clear();

                    overlineOffset = 0.0;
                    overlineThickness = 0.0;
                }

                // ### Add pending when overlineOffset/thickness changes to minimize number of
                // nodes
                if (!pendingStrikeOuts.isEmpty()) {
                    addTextDecorations(pendingStrikeOuts, strikeOutOffset, strikeOutThickness);

                    pendingStrikeOuts.clear();

                    strikeOutOffset = 0.0;
                    strikeOutThickness = 0.0;
                }

                // Merge current values with previous. Prefer greatest thickness
                QRawFont rawFont = node->glyphRun.rawFont();
                if (node->decorations & QQuickTextNode::Underline) {
                    if (rawFont.lineThickness() > underlineThickness) {
                        underlineThickness = rawFont.lineThickness();
                        underlineOffset = rawFont.underlinePosition();
                    }
                }

                if (node->decorations & QQuickTextNode::Overline) {
                    overlineOffset = -rawFont.ascent();
                    overlineThickness = rawFont.lineThickness();
                }

                if (node->decorations & QQuickTextNode::StrikeOut) {
                    strikeOutThickness = rawFont.lineThickness();
                    strikeOutOffset = rawFont.ascent() / -3.0;
                }

                currentDecorations = node->decorations;
                lastColor = node->color;
                lastBackgroundColor = node->backgroundColor;
                m_processedNodes.append(*node);
            }
        }

        if (!pendingUnderlines.isEmpty())
            addTextDecorations(pendingUnderlines, underlineOffset, underlineThickness);

        if (!pendingOverlines.isEmpty())
            addTextDecorations(pendingOverlines, overlineOffset, overlineThickness);

        if (!pendingStrikeOuts.isEmpty())
            addTextDecorations(pendingStrikeOuts, strikeOutOffset, strikeOutThickness);
    }

    m_currentLineTree.clear();
    m_currentLine = QTextLine();
    m_hasSelection = false;
}