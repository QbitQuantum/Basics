 void
 NodeStatInspector::node(const VisualNode::NodeAllocator& na,
                         VisualNode* n, const Statistics&, bool) {
   if (isVisible()) {
     int nd = -1;
     for (VisualNode* p = n; p != NULL; p = p->getParent(na))
       nd++;
     nodeDepthLabel->setPlainText(QString("%1").arg(nd));;
     StatCursor sc(n,na);
     PreorderNodeVisitor<StatCursor> pnv(sc);
     pnv.run();
     
     subtreeDepthLabel->setPlainText(
       QString("%1").arg(pnv.getCursor().depth));
     solvedLabel->setPlainText(QString("%1").arg(pnv.getCursor().solved));
     solvedLabel->setPos(78-solvedLabel->document()->size().width()/2,120);
     failedLabel->setPlainText(QString("%1").arg(pnv.getCursor().failed));
     failedLabel->setPos(44-failedLabel->document()->size().width(),120);
     choicesLabel->setPlainText(QString("%1").arg(pnv.getCursor().choice));
     choicesLabel->setPos(66-choicesLabel->document()->size().width(),57);
     openLabel->setPlainText(QString("%1").arg(pnv.getCursor().open));
   }
 }