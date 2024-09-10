void PrinterVisitor::beginVisitFlworWhereClause( PlanIterator const &i ) {
  thePrinter.startBeginVisit( "WhereClause", ++theId );
  thePrinter.endBeginVisit( theId );
  i.accept( *this );
}