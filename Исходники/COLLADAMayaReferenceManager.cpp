 bool isIn(const MDagPath & dagPath, const MObject & referenceNode)
 {
     MDagPathArray rootDagPaths;
     MObjectArray subReferences;
     ReferenceManager::getRootObjects(referenceNode, rootDagPaths, subReferences);
     for (unsigned int i = 0; i < rootDagPaths.length(); ++i) {
         if (rootDagPaths[i] == dagPath) {
             return true;
         }
     }
     for (unsigned int i = 0; i < subReferences.length(); ++i) {
         if (isIn(dagPath, subReferences[i])) {
             return true;
         }
     }
     return false;
 }