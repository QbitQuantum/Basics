  void
  TreeCanvas::inspectCurrentNode(bool fix, int inspectorNo) {
    QMutexLocker locker(&mutex);

    if (currentNode->isHidden()) {
      toggleHidden();
      return;
    }

    int failedInspectorType = -1;
    int failedInspector = -1;
    bool needCentering = false;
    try {
      switch (currentNode->getStatus()) {
      case UNDETERMINED:
          {
            unsigned int kids =  
              currentNode->getNumberOfChildNodes(*na,curBest,stats,c_d,a_d);
            int depth = -1;
            for (VisualNode* p = currentNode; p != NULL; p=p->getParent(*na))
              depth++;
            if (kids > 0) {
              needCentering = true;
              depth++;
            }
            stats.maxDepth =
              std::max(stats.maxDepth, depth);
            if (currentNode->getStatus() == SOLVED) {
              assert(currentNode->hasCopy());
              emit solution(currentNode->getWorkingSpace());
              currentNode->purge(*na);
            }
            emit statusChanged(currentNode,stats,true);
            for (int i=0; i<moveInspectors.size(); i++) {
              if (moveInspectors[i].second) {
                failedInspectorType = 0;
                failedInspector = i;
                moveInspectors[i].first->
                  inspect(*currentNode->getWorkingSpace());
                failedInspectorType = -1;
              }
            }
          }
          break;
      case FAILED:
      case STOP:
      case UNSTOP:
      case BRANCH:
      case SOLVED:
        {
          // SizeCursor sc(currentNode);
          // PreorderNodeVisitor<SizeCursor> pnv(sc);
          // int nodes = 1;
          // while (pnv.next()) { nodes++; }
          // std::cout << "sizeof(VisualNode): " << sizeof(VisualNode)
          //           << std::endl;
          // std::cout << "Size: " << (pnv.getCursor().s)/1024 << std::endl;
          // std::cout << "Nodes: " << nodes << std::endl;
          // std::cout << "Size / node: " << (pnv.getCursor().s)/nodes
          //           << std::endl;

          Space* curSpace;
        
          if (fix) {
            if (currentNode->isRoot() && currentNode->getStatus() == FAILED)
              break;
            curSpace = currentNode->getSpace(*na,curBest,c_d,a_d);
            if (currentNode->getStatus() == SOLVED &&
                curSpace->status() != SS_SOLVED) {
              // in the presence of weakly monotonic propagators, we may have to
              // use search to find the solution here
              Space* dfsSpace = Gecode::dfs(curSpace);
              delete curSpace;
              curSpace = dfsSpace;
            }          
          } else {
            if (currentNode->isRoot())
              break;
            VisualNode* p = currentNode->getParent(*na);
            curSpace = p->getSpace(*na,curBest,c_d,a_d);
            switch (curSpace->status()) {
            case SS_SOLVED:
            case SS_FAILED:
              break;
            case SS_BRANCH:
              curSpace->commit(*p->getChoice(), 
                               currentNode->getAlternative(*na));
              break;
            default:
              GECODE_NEVER;
            }
          }

          if (inspectorNo==-1) {
            for (int i=0; i<doubleClickInspectors.size(); i++) {
              if (doubleClickInspectors[i].second) {
                failedInspectorType = 1;
                failedInspector = i;
                doubleClickInspectors[i].first->inspect(*curSpace);
                failedInspectorType = -1;
              }
            }
          } else {
            failedInspectorType = 1;
            failedInspector = inspectorNo;
            doubleClickInspectors[inspectorNo].first->inspect(*curSpace);
            failedInspectorType = -1;
          }
          delete curSpace;
        }
        break;
      }
    } catch (Exception e) {
      switch (failedInspectorType) {
      case 0:
        std::cerr << "Exception in move inspector "
                  << failedInspector;
        break;
      case 1:
        std::cerr << "Exception in double-click inspector "
                  << failedInspector;
        break;
      default:
        std::cerr << "Exception ";
        break;
      }
      std::cerr << ": " << e.what() << "." << std::endl;
      std::cerr << "Stopping..." << std::endl;
      std::exit(EXIT_FAILURE);
    }

    currentNode->dirtyUp(*na);
    update();
    if (needCentering)
      centerCurrentNode();
  }