/* static */
Maybe<ComputedTimingFunction>
AnimationUtils::TimingFunctionToComputedTimingFunction(
    const TimingFunction& aTimingFunction) {
  switch (aTimingFunction.type()) {
    case TimingFunction::Tnull_t:
      return Nothing();
    case TimingFunction::TCubicBezierFunction: {
      CubicBezierFunction cbf = aTimingFunction.get_CubicBezierFunction();
      return Some(ComputedTimingFunction::CubicBezier(cbf.x1(), cbf.y1(),
                                                      cbf.x2(), cbf.y2()));
    }
    case TimingFunction::TStepFunction: {
      StepFunction sf = aTimingFunction.get_StepFunction();
      StyleStepPosition pos = static_cast<StyleStepPosition>(sf.type());
      return Some(ComputedTimingFunction::Steps(sf.steps(), pos));
    }
    default:
      MOZ_ASSERT_UNREACHABLE("Function must be null, bezier, step or frames");
      break;
  }
  return Nothing();
}