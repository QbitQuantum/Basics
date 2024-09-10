void EnhancedTagAttributeTree::deleteNode()
{
  QuantaView *view = ViewManager::ref()->activeView();
  if(!curNode || !view->document())
    return;

  Node *oldCurNode, *oldCurNodeParent, *child;
  QTag *oldCurNodeParentQTag;
  int curLine, curCol;
  long offset;
  DOM::Node domNode;
  QValueList<int> loc;
  NodeModifsSet *modifs;

  //Save the cursor position in kafka/quanta
  if(view->hadLastFocus() == QuantaView::SourceFocus)
    curNode->tag->beginPos(curLine, curCol);
  else
  {
    KafkaDocument::ref()->getKafkaWidget()->getCurrentNode(domNode, offset);
    if(!domNode.previousSibling().isNull())
      domNode = domNode.previousSibling();
    else if(!domNode.parentNode().isNull())
      domNode = domNode.parentNode();
    else
      domNode = KafkaDocument::ref()->getKafkaWidget()->document();
    if(domNode.nodeType() == DOM::Node::TEXT_NODE)
      offset = domNode.nodeValue().length();
    else
     offset = 0;
    loc = kafkaCommon::getLocation(domNode);
  }

  //remove the Nodes
  oldCurNode = curNode;
  oldCurNodeParent = curNode->parent;
  curNode = 0L;
  attrTree->setCurrentNode(curNode);

  modifs = new NodeModifsSet();
  kafkaCommon::extractAndDeleteNode(oldCurNode, modifs, false);

  //Then we see if the new parent - child relationships are valid, and if not, delete the child and restart
  if(oldCurNodeParent)
  {
    oldCurNodeParentQTag = QuantaCommon::tagFromDTD(oldCurNodeParent);
    if(oldCurNodeParentQTag)
    {
      child = oldCurNodeParent->child;
      while(child)
      {
        if(!oldCurNodeParentQTag->isChild(child))
        {
          kafkaCommon::extractAndDeleteNode(child, modifs, false);
          //too lazy to get the real next node ;-)
          child = oldCurNodeParent->child;
        }
        else
          child = child->next;
      }
    }
  }

  view->document()->docUndoRedo->addNewModifsSet(modifs, undoRedo::NodeTreeModif);

  //set the cursor position in kafka/quanta
  if(view->hadLastFocus() == QuantaView::SourceFocus)
    view->document()->viewCursorIf->setCursorPositionReal((uint)curLine, (uint)curCol);
  else
  {
    domNode = kafkaCommon::getNodeFromLocation(loc,
    KafkaDocument::ref()->getKafkaWidget()->document());
    KafkaDocument::ref()->getKafkaWidget()->setCurrentNode(domNode, offset);
  }

}