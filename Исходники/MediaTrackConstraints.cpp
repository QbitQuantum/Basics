bool
NormalizedConstraintSet::StringRange::Merge(const StringRange& aOther)
{
  if (!Intersects(aOther)) {
    return false;
  }
  Intersect(aOther);

  ValueType unioned;
  set_union(mIdeal.begin(), mIdeal.end(),
            aOther.mIdeal.begin(), aOther.mIdeal.end(),
            std::inserter(unioned, unioned.begin()));
  mIdeal = unioned;
  return true;
}