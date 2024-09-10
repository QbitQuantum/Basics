void SynthesizeRemovalConsumer::processDeclContext(DeclContext *DC)
{  
  for(auto I = DC->decls_begin(), E = DC->decls_end(); I != E; ++I) {
    if (auto D = dyn_cast<ObjCMethodDecl>(*I)) {
      // handle methods
      if (auto B = D->getBody()) {
        processStmt(B, D);
      }
    }
    else if (auto D = dyn_cast<BlockDecl>(*I)) {
      // handle blocks in a method; find the parent context first
      DeclContext *P = D->getParent();
      while (P) {
        if (dyn_cast<ObjCMethodDecl>(P)) {
          break;
        }
        P = P->getParent();
      }
      
      // only when P is a ObjCMethodDecl can me proceed
      if (P) {
        if (auto B = D->getBody()) {
          processStmt(B, P);
        }      
      }
    }

    // descend into the next level (for namespace, blocks, etc.)    
    if (auto innerDC = dyn_cast<DeclContext>(*I)) {
      processDeclContext(innerDC);
    }
  }
}