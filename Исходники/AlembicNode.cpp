double AlembicNode::computeRetime(const double inputTime,
                                  const double firstTime,
                                  const double lastTime,
                                  const short playStyle)
{
    const double playTime = lastTime - firstTime;
    static const double eps = 0.001;
    double retime = inputTime;

    switch (playStyle)
    {
      case PLAYTYPE_HOLD:
          break;
      case PLAYTYPE_LOOP:
          if (inputTime < (firstTime - eps) || inputTime > (lastTime + eps))
          {
              const double timeOffset = inputTime - firstTime;
              const double playOffset = floor(timeOffset/playTime);
              const double fraction = fabs(timeOffset/playTime - playOffset);

              retime = firstTime + playTime * fraction;
          }
          break;
      case PLAYTYPE_REVERSE:
          if (inputTime > (firstTime + eps) && inputTime < (lastTime - eps))
          {
              const double timeOffset = inputTime - firstTime;
              const double playOffset = floor(timeOffset/playTime);
              const double fraction = fabs(timeOffset/playTime - playOffset);

              retime = lastTime - playTime * fraction;
          }
          else if (inputTime < (firstTime + eps))
          {
              retime = lastTime;
          }
          else
          {
              retime = firstTime;
          }
          break;
      case PLAYTYPE_BOUNCE:
          if (inputTime < (firstTime - eps) || inputTime > (lastTime + eps))
          {
              const double timeOffset = inputTime - firstTime;
              const double playOffset = floor(timeOffset/playTime);
              const double fraction = fabs(timeOffset/playTime - playOffset);

              // forward loop
              if (fmod(playOffset, 2.0)==0.0)
              {
                  retime = firstTime + playTime * fraction;
              }
              // backward loop
              else
              {
                  retime = lastTime - playTime * fraction;
              }
          }
          break;
    }

    return retime;
}