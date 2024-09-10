void SendInfo::computeNSends(RScope* rscope, int bci) {
  GrowableArray<RScope*>* lst = rscope->subScopes(bci);
  nsends = 0;
  for (int i = lst->length() - 1; i >= 0; i--) {
    nsends += lst->at(i)->nsends;
  }
}