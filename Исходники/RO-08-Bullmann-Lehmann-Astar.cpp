void Astar::expandNode(Node & currentNode) {
  Node successorNode;
  for (int i = 0; i < 4; i++) {
    switch(i) {
      case 0: successorNode = Node(currentNode.getX()-1, currentNode.getY());
              break;
      case 1: successorNode = Node(currentNode.getX()+1, currentNode.getY());
              break;
      case 2: successorNode = Node(currentNode.getX(), currentNode.getY()-1);
              break;
      case 3: successorNode = Node(currentNode.getX(), currentNode.getY()+1);
              break;
    }
    if(std::find(obstacles.begin(), obstacles.end(), successorNode) != obstacles.end()) {
      //this node is an obstacle, so don't go there biatch
      continue;
    }
    if (closedList.count(successorNode) == 1) {
      continue;
    } else {
      //setting cost from parent plus way from parent to current
      successorNode.setCostSoFar(currentNode.getCostSoFar()+1);
      successorNode.setHeuristicEstimate(std::abs(goalNode.getX()-successorNode.getX())+std::abs(goalNode.getY()-successorNode.getY()));
      if (openList.count(successorNode) == 1) {
        Node oldSuccessorNode = *openList.find(successorNode);
        if (successorNode.getCompleteCost() >= oldSuccessorNode.getCompleteCost()) {
          continue;
        }
      }
      Parent temp = Parent();
      temp.x = currentNode.getX();
      temp.y = currentNode.getY();
      successorNode.setParent(temp);
      successorNode.setPaint(OPEN);
      if (openList.count(successorNode) == 1) {
        openList.erase(openList.find(successorNode));
      }
      openList.insert(successorNode);
    }
  }
}