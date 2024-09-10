void oEvent::generatePreReport(gdioutput &gdi)
{
  CurrentSortOrder=SortByName;
  Runners.sort();

  int lVacId = getVacantClub();

  oRunnerList::iterator r_it;
  oTeamList::iterator t_it;

  //BIB, START, NAME, CLUB, RANK, SI
  int dx[6]={0, 0, 70, 300, 470, 470};

  bool withrank = hasRank();
  bool withbib = hasBib(true, true);
  int i;

  if (withrank) dx[5]+=50;
  if (withbib) for(i=1;i<6;i++) dx[i]+=40;

  int y=gdi.getCY();
  int x=gdi.getCX();
  int lh=gdi.getLineHeight();

  gdi.addStringUT(2, lang.tl("Rapport inför: ") + getName());

  gdi.addStringUT(1, getDate());
  gdi.dropLine();
  char bf[256];

  list<pRunner> no_card;
  list<pRunner> no_start;
  list<pRunner> no_class;
  list<pRunner> no_course;
  list<pRunner> no_club;

  for (r_it=Runners.begin(); r_it != Runners.end(); ++r_it){
    if (r_it->isRemoved())
      continue;

    bool needStartTime = true;
    bool needCourse = true;

    pClass pc = r_it->Class;
    if (pc) {
      LegTypes lt = pc->getLegType(r_it->tLeg);
      if (lt == LTIgnore) {
        needStartTime = false;
        needCourse = false;
      }
      if (pc->hasDirectResult())
        needCourse = false;

      StartTypes st = pc->getStartType(r_it->tLeg);

      if (st != STTime && st != STDrawn)
        needStartTime = false;

      if (pc->hasFreeStart())
        needStartTime = false;
    }
    if ( r_it->getClubId() != lVacId) {
      if (needCourse && r_it->getCardNo()==0)
        no_card.push_back(&*r_it);
      if (needStartTime && r_it->getStartTime()==0)
        no_start.push_back(&*r_it);
      if (r_it->getClubId()==0)
        no_club.push_back(&*r_it);
    }

    if (r_it->getClassId()==0)
      no_class.push_back(&*r_it);
    else if (needCourse && r_it->getCourse(false)==0)
      no_course.push_back(&*r_it);
  }

  list<pRunner> si_duplicate;

  if (Runners.size()>1){
    Runners.sort(oRunner::CompareSINumber);

    r_it=Runners.begin();
    while (++r_it != Runners.end()){
      oRunnerList::iterator r_it2=r_it;
      r_it2--;

      if (r_it2->getCardNo() && r_it2->getCardNo()==r_it->getCardNo()){

        if (si_duplicate.size()==0 || si_duplicate.back()->getId()!=r_it2->getId())
          si_duplicate.push_back(&*r_it2);

        si_duplicate.push_back(&*r_it);
      }
    }
  }

  const string Ellipsis="[ ... ]";

  sprintf_s(bf, lang.tl("Löpare utan klass: %d.").c_str(), no_class.size());
  gdi.addStringUT(1, bf);
  i=0;

  while(!no_class.empty() && ++i<20){
    pRunner r=no_class.front();
    no_class.pop_front();
    sprintf_s(bf, "%s (%s)", r->getName().c_str(), r->getClub().c_str());
    gdi.addStringUT(0, bf);
  }
  if (!no_class.empty()) gdi.addStringUT(1, Ellipsis);

  gdi.dropLine();
  sprintf_s(bf, lang.tl("Löpare utan bana: %d.").c_str(), no_course.size());
  gdi.addStringUT(1, bf);
  i=0;

  while(!no_course.empty() && ++i<20){
    pRunner r=no_course.front();
    no_course.pop_front();
    sprintf_s(bf, "%s: %s (%s)", r->getClass().c_str(), r->getName().c_str(), r->getClub().c_str());
    gdi.addStringUT(0, bf);
  }
  if (!no_course.empty()) gdi.addStringUT(1, Ellipsis);

  if (oe->getMeOSFeatures().hasFeature(MeOSFeatures::Clubs)) {
    gdi.dropLine();
    sprintf_s(bf, lang.tl("Löpare utan klubb: %d.").c_str(), no_club.size());
    gdi.addStringUT(1, bf);
    i=0;

    while(!no_club.empty() && ++i<20){
      pRunner r=no_club.front();
      no_club.pop_front();
      sprintf_s(bf, "%s: %s", r->getClass().c_str(), r->getName().c_str());
      gdi.addStringUT(0, bf);
    }
    if (!no_club.empty()) gdi.addStringUT(1, Ellipsis);
  }

  gdi.dropLine();
  sprintf_s(bf, lang.tl("Löpare utan starttid: %d.").c_str(), no_start.size());
  gdi.addStringUT(1, bf);
  i=0;

  while(!no_start.empty() && ++i<20){
    pRunner r=no_start.front();
    no_start.pop_front();
    sprintf_s(bf, "%s: %s (%s)", r->getClass().c_str(), r->getName().c_str(), r->getClub().c_str());
    gdi.addStringUT(0, bf);
  }
  if (!no_start.empty()) gdi.addStringUT(1, Ellipsis);

  gdi.dropLine();
  sprintf_s(bf, lang.tl("Löpare utan SI-bricka: %d.").c_str(), no_card.size());
  gdi.addStringUT(1, bf);
  i=0;

  while(!no_card.empty() && ++i<20){
    pRunner r=no_card.front();
    no_card.pop_front();
    sprintf_s(bf, "%s: %s (%s)", r->getClass().c_str(), r->getName().c_str(), r->getClub().c_str());
    gdi.addStringUT(0, bf);
  }
  if (!no_card.empty()) gdi.addStringUT(1, Ellipsis);


  gdi.dropLine();
  sprintf_s(bf, lang.tl("SI-dubbletter: %d.").c_str(), si_duplicate.size());
  gdi.addStringUT(1, bf);
  i=0;

  while(!si_duplicate.empty() && ++i<20){
    pRunner r=si_duplicate.front();
    si_duplicate.pop_front();
    sprintf_s(bf, "%s: %s (%s) SI=%d", r->getClass().c_str(),
              r->getName().c_str(), r->getClub().c_str(), r->getCardNo());
    gdi.addStringUT(0, bf);
  }
  if (!si_duplicate.empty()) gdi.addStringUT(1, Ellipsis);


  //List all competitors not in a team.
  if (oe->hasTeam()) {
    for (r_it=Runners.begin(); r_it != Runners.end(); ++r_it)
      r_it->_objectmarker=0;

    for (t_it=Teams.begin(); t_it != Teams.end(); ++t_it){
      pClass pc=getClass(t_it->getClassId());

      if (pc){
        for(unsigned i=0;i<pc->getNumStages();i++){
          pRunner r=t_it->getRunner(i);
          if (r) r->_objectmarker++;
        }
      }
    }

    gdi.dropLine();
    gdi.addString("", 1, "Löpare som förekommer i mer än ett lag:");
    bool any = false;
    for (r_it=Runners.begin(); r_it != Runners.end(); ++r_it){
      if (r_it->_objectmarker>1){
        sprintf_s(bf, "%s: %s (%s)", r_it->getClass().c_str(), r_it->getName().c_str(), r_it->getClub().c_str());
        gdi.addStringUT(0, bf);
        any = true;
      }
    }
    if (!any)
      gdi.addStringUT(1, "0");
  }
  sortRunners(ClassStartTime);

  gdi.dropLine();
  gdi.addString("", 1, "Individuella deltagare");

  y=gdi.getCY();
  int tab[5]={0, 100, 350, 420, 550};
  for (r_it=Runners.begin(); r_it != Runners.end(); ++r_it){
    if (r_it->_objectmarker==0){ //Only consider runners not in a team.
      gdi.addStringUT(y, x+tab[0], 0, r_it->getClass(), tab[1]-tab[0]);
      gdi.addStringUT(y, x+tab[1], 0, r_it->getName()+" ("+r_it->getClub()+")", tab[2]-tab[1]);
      gdi.addStringUT(y, x+tab[2], 0, itos(r_it->getCardNo()), tab[3]-tab[2]);
      gdi.addStringUT(y, x+tab[3], 0, r_it->getCourseName(), tab[4]-tab[3]);
      y+=lh;
      pCourse pc=r_it->getCourse(true);

      if (pc){
        vector<string> res = pc->getCourseReadable(101);
        for (size_t k = 0; k<res.size(); k++) {
          gdi.addStringUT(y, x+tab[1], 0, res[k]);
          y+=lh;
        }
      }
    }
  }

  gdi.dropLine();
  gdi.addString("", 1, "Lag(flera)");

  for (t_it=Teams.begin(); t_it != Teams.end(); ++t_it){
    pClass pc=getClass(t_it->getClassId());

    gdi.addStringUT(0, t_it->getClass() + ": " + t_it->getName() + "  " +t_it->getStartTimeS());

    if (pc){
      for(unsigned i=0;i<pc->getNumStages();i++){
        pRunner r=t_it->getRunner(i);
        if (r){
          gdi.addStringUT(0, r->getName()+ " SI: " +itos(r->getCardNo()));

          pCourse pcourse=r->getCourse(true);

          if (pcourse){
            y = gdi.getCY();
            vector<string> res = pcourse->getCourseReadable(101);
            for (size_t k = 0; k<res.size(); k++) {
              gdi.addStringUT(y, x+tab[1], 0, res[k]);
              y+=lh;
            }
          }
        }
        else
          gdi.addString("", 0, "Löpare saknas");
      }
    }
    gdi.dropLine();
  }

  gdi.updateScrollbars();
}