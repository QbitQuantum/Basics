bool 
RDFAnnotationParser::hasCVTermRDFAnnotation(const XMLNode *annotation)
{
  bool hasCVTermRDF = false;

  if (!RDFAnnotationParser::hasRDFAnnotation(annotation))
  {
    return hasCVTermRDF;
  }

  // check whether the annotation relates to CVTerms
  List * tempCVTerms = new List();
  parseRDFAnnotation(annotation, tempCVTerms);
  if (tempCVTerms && tempCVTerms->getSize() > 0)
  {
    hasCVTermRDF = true;
  }

  if (tempCVTerms)
  {
    unsigned int size = tempCVTerms->getSize();
    while (size--) delete static_cast<CVTerm*>( tempCVTerms->remove(0) );
  }
  delete tempCVTerms;


  return hasCVTermRDF;
}