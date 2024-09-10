int wait_for_iob_signal()
{
  if (iob_synchronized) {
    //std::cerr << "wait>" << std::endl;
    if (start_robothw) {
      // no wait
    }
    //std::cerr << "wait<" << std::endl;
    return 0;
  } else {
    //
    ros::Time rnow;
    ros::Duration tm = ros::Duration(0, g_period_ns);
    ros::WallDuration wtm = ros::WallDuration(0, 100000); // 0.1 ms
    while ((rnow = ros::Time::now()) < rg_ts) {
      wtm.sleep();
    }

    rg_ts += tm;
    if ((rg_ts - rnow).toSec() <= 0) {
      fprintf(stderr, "iob::overrun (%f[ms]), w:%f -> %f\n",
              (rnow - rg_ts).toSec()*1000, rnow.toSec(), rg_ts.toSec());
      do {
        rg_ts += tm;
      } while ((rg_ts - rnow).toSec() <= 0);
    }

    return 0;
  }

  return 0;
}