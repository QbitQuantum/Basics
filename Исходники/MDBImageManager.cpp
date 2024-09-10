int
MDBImageManager::fillStudyVector(const MStudy& study, MStudyVector& v)
{
  char* searchCriteria[] = {
    "stuinsuid",
    // "studat",		// Comment out as we treat this for date range
    "stutim",
    "accnum",
    "stuid"
  };

  MCriteriaVector criteria;

  MString studyDate = study.studyDate();
  if (studyDate != "") {
    if (studyDate.containsCharacter('-')) {
      MString lower = studyDate.getToken('-', 0);
      MString upper = studyDate.getToken('-', 1);
      if (lower != "") {
	MCriteria p;
	p.attribute = "studat";
	p.oper = TBL_GREATER_EQUAL;
	p.value = lower;
	criteria.push_back(p);
      }
      if (upper != "") {
	MCriteria p;
	p.attribute = "studat";
	p.oper = TBL_LESS_EQUAL;
	p.value = upper;
	criteria.push_back(p);
      }
    } else {
      MCriteria p;
      p.attribute = "studat";
      p.oper = TBL_EQUAL;
      p.value = studyDate;
      criteria.push_back(p);
    }
  }


  int i;

  const MDomainMap& m = study.map();
  for(i = 0; i < (int)DIM_OF(searchCriteria); i++) {
    MDomainMap::const_iterator iDomain = m.find(searchCriteria[i]);
    if (iDomain == m.end())
      continue;

    MString s = (*iDomain).second;

    if (s != "") {
      TBL_OPERATOR oper = TBL_EQUAL;
      if (s.find("*") != string::npos) {
	s.substitute('*', '%');
	oper = TBL_LIKE;
      }
      MCriteria c;
      c.attribute = searchCriteria[i];
      c.oper = oper;
      c.value = s;
      criteria.push_back(c);
    }
  }
  MStudy s;
  mDBInterface->select(s, criteria, studyCallback, this);
  MStudyVector::iterator studyIterator = mStudyVector.begin();
  for (; studyIterator != mStudyVector.end(); studyIterator++)
    v.push_back(*studyIterator);

  return 0;
}