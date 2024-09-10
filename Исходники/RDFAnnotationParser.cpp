bool 
RDFAnnotationParser::hasAdditionalRDFAnnotation(const XMLNode *annotation)
{
  if (annotation == NULL) 
    return false;

  bool hasAdditionalRDF = false;
  unsigned int n = 0;
  const XMLNode* rdf = NULL;

  if (!RDFAnnotationParser::hasRDFAnnotation(annotation))
  {
    return hasAdditionalRDF;
  }

  // get the RDF annotation
  while ( n < annotation->getNumChildren())
  {
    const string &name1 = annotation->getChild(n).getName();
    if (name1 == "RDF")
    {
      rdf = &(annotation->getChild(n));
      break;
    }
    n++;
  }

  // does it have more than one child
  if (rdf != NULL && rdf->getNumChildren() > 1)
  {
    hasAdditionalRDF = true;
  }
  else
  {
    // check whether the annotation relates to CVTerms
    List * tempCVTerms = new List();
    parseRDFAnnotation(annotation, tempCVTerms);
    if (tempCVTerms && tempCVTerms->getSize() == 0 && 
      !RDFAnnotationParser::hasHistoryRDFAnnotation(annotation))
    {
      hasAdditionalRDF = true;
    }
    else
    {
    }
    
    if (tempCVTerms != NULL)
    {
      unsigned int size = tempCVTerms->getSize();
      while (size--) delete static_cast<CVTerm*>( tempCVTerms->remove(0) );
    }
    delete tempCVTerms;
  }

  return hasAdditionalRDF;
}