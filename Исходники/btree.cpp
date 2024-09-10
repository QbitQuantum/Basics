 void BTree::removeCore(Key key, std::vector<int>& trace) {
     Node *parent;
     PageDB::PageWriteSession parentSession = pgdb->GetWriteSession(file, trace.back());
     parent = reinterpret_cast<Node*>(parentSession.buf());
     int sp;
     int idx = parent->findIndex(key);
     for (sp = trace.size() - 1; sp > 0; sp--) {
         Node* child = parent;
         child->Remove(idx);
         if (child->size >= MinChild) {
             break;
         }
         PageDB::PageWriteSession childSession = std::move(parentSession);
         parentSession = pgdb->GetWriteSession(file, trace[sp - 1]);
         parent = reinterpret_cast<Node*>(parentSession.buf());
         idx = parent->findIndex(child->children[0].less);
         if (idx > 0) {
             //Left
             PageDB::PageWriteSession siblingSession = pgdb->GetWriteSession(file, parent->children[idx - 1].loc.Offset);
             Node* sibling = reinterpret_cast<Node*>(siblingSession.buf());
             if (sibling->size > MinChild) {
                 auto item = sibling->children[sibling->size - 1];
                 child->Insert(item.less, item.loc);
                 sibling->Remove(sibling->size - 1);
                 parent->children[idx].less = child->children[0].less;
                 break;
             }
             //Merge
             sibling->Merge(*child);
             childSession.Release();
             pgdb->RemovePage(file, trace[sp]);
         } else {
             //Right
             PageDB::PageWriteSession siblingSession = pgdb->GetWriteSession(file, parent->children[idx + 1].loc.Offset);
             Node* sibling = reinterpret_cast<Node*>(siblingSession.buf());
             if (sibling->size > MinChild) {
                 auto item = sibling->children[0];
                 child->Insert(item.less, item.loc);
                 sibling->Remove(0);
                 parent->children[idx + 1].less = sibling->children[0].less;
                 break;
             }
             //Merge
             child->Merge(*sibling);
             siblingSession.Release();
             pgdb->RemovePage(file, parent->children[idx + 1].loc.Offset);
             idx++;
         }
     }
     if (sp == 0) {
         parent->Remove(idx);
         if (parent->size == 1 && parent->children[0].loc.Page == 0) {
             rootPage() = parent->children[0].loc.Offset;
             parentSession.Release();
             entrySession.flush();
         }
     }
 }