bool
CAI302Device::WriteNavpoint(unsigned id, const Waypoint &wp,
                            OperationEnvironment &env)
{
  if (!DownloadMode(env))
    return false;

  char name[64], remark[64];
  ToASCII(name, ARRAY_SIZE(name), wp.name.c_str());
  ToASCII(remark, ARRAY_SIZE(remark), wp.comment.c_str());

  if (!CAI302::DownloadNavpoint(port, wp.location, (int)wp.elevation, id,
                                wp.IsTurnpoint(), wp.IsAirport(), false,
                                wp.IsLandable(), wp.IsStartpoint(),
                                wp.IsFinishpoint(), wp.flags.home,
                                false, wp.IsTurnpoint(), false,
                                name, remark, env)) {
    mode = Mode::UNKNOWN;
    return false;
  }

  return true;
}