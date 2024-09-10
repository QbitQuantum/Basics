void ViewResource::RenderLinearPath(const LinearPathResource* rc,Real pathTime)
{
  if(pathViewer.robot==NULL) {
    printf("ViewResource: Robot is NULL\n");
    return;
  }
  Config oldq = pathViewer.robot->q;
  if(rc->times.empty()) {
  }
  else if(rc->times.front() == rc->times.back()) {
    pathViewer.robot->UpdateConfig(rc->milestones[0]);
    pathViewer.Draw();
  }
  else {
    //TODO: faster tracking using upper_bound?
    Assert(rc->times.size()==rc->milestones.size());
    Assert(rc->times.back() > rc->times.front());
    Real normalizedPathTime = pathTime;
    //looping behavior
    /*
      while(normalizedPathTime < rc->times.front()) 
      normalizedPathTime += rc->times.back()-rc->times.front();
      while(normalizedPathTime > rc->times.back()) 
      normalizedPathTime -= rc->times.back()-rc->times.front();
      pathTime = normalizedPathTime;
    */
    //bouncing behavior
    double cnt = (pathTime-rc->times.front())/(rc->times.back()-rc->times.front());
    int n = (int)Floor(cnt);
    if(n%2==0)
      normalizedPathTime = (cnt-n)*(rc->times.back()-rc->times.front());
    else
      normalizedPathTime = rc->times.back()-(cnt-n)*(rc->times.back()-rc->times.front());
    bool drawn=false;
    for(size_t i=0;i+1<rc->times.size();i++) {
      Assert(rc->milestones[i].n == oldq.n);
      Assert(rc->milestones[i+1].n == oldq.n);
      if(rc->times[i] <= normalizedPathTime && normalizedPathTime <= rc->times[i+1]) {
	Real u=(normalizedPathTime-rc->times[i])/(rc->times[i+1]-rc->times[i]);
	Vector q;
	Interpolate(*pathViewer.robot,rc->milestones[i],rc->milestones[i+1],u,q);
	pathViewer.robot->UpdateConfig(q);
	pathViewer.Draw();
	drawn=true;
	break;
      }
    }
  }
  pathViewer.robot->UpdateConfig(oldq);
}