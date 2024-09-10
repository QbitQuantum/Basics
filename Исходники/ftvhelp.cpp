static void generateBriefDoc(QTextStream &t, QSharedPointer<Definition> def)
{
   QString brief = def->briefDescription(true);

/* ( save for testing )

   if (brief.isEmpty()) {
      SortedList<QSharedPointer<GroupDef>> *groups = def->partOfGroups();

      if (groups) { 
         for (auto gd : *groups) {
            brief = gd->briefDescription(true);

            if (! brief.isEmpty()) {
               break;
            }
         }
      }
   }
*/
 
   if (! brief.isEmpty()) {

      DocNode *root = validatingParseDoc(def->briefFile(), def->briefLine(),
                  def, QSharedPointer<MemberDef>(), brief, false, false, "", true, true);

      QString relPath = relativePathToRoot(def->getOutputFileBase());

      HtmlCodeGenerator htmlGen(t, relPath);
      HtmlDocVisitor *visitor = new HtmlDocVisitor(t, htmlGen, def);
      root->accept(visitor);

      delete visitor;
      delete root;
   }
}