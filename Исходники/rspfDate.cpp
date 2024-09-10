void rspfLocalTm::setTimeGivenEpoc(time_t ticks)
{
   *this = *localtime(&ticks);
}