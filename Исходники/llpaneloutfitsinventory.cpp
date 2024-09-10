 virtual void onOpen(const LLSD& key)
 {
     LLLineEditor* edit = getChild<LLLineEditor>("name ed");
     if (edit)
     {
         edit->setFocus(TRUE);
         edit->selectAll();
     }
 }