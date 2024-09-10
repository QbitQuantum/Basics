Node* Semester::AddChild(Node *parent, Course *child, unsigned int index){
  Node *retnode = new Node(child);
  parent->SetChild(retnode, index);
  retnode->SetParent(parent);
  return retnode;
}//AddChild