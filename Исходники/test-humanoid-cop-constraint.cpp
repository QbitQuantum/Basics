  virtual void SetUp()
  {
    using namespace MPCWalkgen;

    int nbSamples = 3;
    Real samplingPeriod = 1.0;
    bool autoCompute = true;
    VectorX variable;
    variable.setZero(2*nbSamples);
    Real feedbackPeriod = 0.5;

    vectorOfVector2 p(3);
    p[0] = Vector2(1.0, 1.0);
    p[1] = Vector2(-1.0, 1.0);
    p[2] = Vector2(1.0, -1.0);

    HumanoidFeetSupervisor<Real> feetSupervisor(nbSamples,
                                                samplingPeriod);
    feetSupervisor.setLeftFootCopConvexPolygon(ConvexPolygon<Real>(p));
    feetSupervisor.setRightFootCopConvexPolygon(ConvexPolygon<Real>(p));


    feetSupervisor.updateTimeline(variable, feedbackPeriod);

    LIPModel<Real> lip(nbSamples, samplingPeriod, autoCompute);
    lip.setFeedbackPeriod(feedbackPeriod);

    HumanoidCopConstraint<Real> copCtr(lip, feetSupervisor);

    VectorX x0 = VectorX::Zero(6);

    function_ = copCtr.getFunction(x0);
    gradient_ = copCtr.getGradient(x0.rows());
    supBounds_ = copCtr.getSupBounds(x0);
    infBounds_ = copCtr.getInfBounds(x0);
  }