inline double
TaskLeg::GetScoredDistance(const GeoPoint &ref) const
{
  if (!GetOrigin())
    return 0;

  switch (destination.GetActiveState()) {
  case OrderedTaskPoint::BEFORE_ACTIVE:
    // this leg totally included
    return fdim(GetOrigin()->GetLocationScored().Distance(destination.GetLocationScored()),
                GetOrigin()->ScoreAdjustment()-destination.ScoreAdjustment());

  case OrderedTaskPoint::CURRENT_ACTIVE:
    // this leg partially included
    if (destination.HasEntered()) {
      return fdim(GetOrigin()->GetLocationScored().Distance(destination.GetLocationScored()),
                  GetOrigin()->ScoreAdjustment()-destination.ScoreAdjustment());
    } else if (ref.IsValid())
      return fdim(ref.ProjectedDistance(GetOrigin()->GetLocationScored(),
                                        destination.GetLocationScored()),
                  GetOrigin()->ScoreAdjustment());
    else
      return 0;

  case OrderedTaskPoint::AFTER_ACTIVE:
    // this leg may be partially included
    if (GetOrigin()->HasEntered() && ref.IsValid()) {
      return fdim(memo_travelled.calc(GetOrigin()->GetLocationScored(),
                                      ref).distance,
                  GetOrigin()->ScoreAdjustment());
    }

    return 0;
  }

  gcc_unreachable();
  assert(false);
  return 0;
}