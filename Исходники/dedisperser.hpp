 void set_killmask(std::vector<int> killmask_in)
 {
   killmask.swap(killmask_in);
   dedisp_error error = dedisp_set_killmask(plan,&killmask[0]);
   ErrorChecker::check_dedisp_error(error,"set_killmask");
 }