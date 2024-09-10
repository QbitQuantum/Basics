void DefaultConstructionSetsController::onRemoveObject(openstudio::model::ModelObject modelObject)
{
  boost::optional<model::DefaultConstructionSet> dcs = modelObject.optionalCast<model::DefaultConstructionSet>();
  if (dcs){
    boost::optional<model::DefaultSurfaceConstructions> dsc = dcs->defaultExteriorSurfaceConstructions();
    if (dsc && (dsc->directUseCount(true) == 1)){
      dsc->remove();
    }

    dsc = dcs->defaultInteriorSurfaceConstructions();
    if (dsc && (dsc->directUseCount(true) == 1)){
      dsc->remove();
    }

    dsc = dcs->defaultGroundContactSurfaceConstructions();
    if (dsc && (dsc->directUseCount(true) == 1)){
      dsc->remove();
    }

    boost::optional<model::DefaultSubSurfaceConstructions> dssc = dcs->defaultExteriorSubSurfaceConstructions();
    if (dssc && (dssc->directUseCount(true) == 1)){
      dssc->remove();
    }

    dssc = dcs->defaultInteriorSubSurfaceConstructions();
    if (dssc && (dssc->directUseCount(true) == 1)){
      dssc->remove();
    }
  }

  modelObject.remove();
}