void PlotBinaryVTKCommand::execute(const double & t,
                                   const PartBunch & bunch,
                                   Inform & msg)
{
    NDIndex<DIM> elem;
    const NDIndex<DIM> & localDomain = _lDoms[Ippl::myNode()];
    std::stringstream fname;

    _timesteps.push_back(t);

    Timings::startTimer(_outputTimer);

    fname << "Data/" << _baseName << "_";
    fname << std::setw(4) << std::setfill('0') << _iteration;

    BinaryVtkFile newStep;
    newStep.addVectorField(_EFD, "E-Field");
    newStep.addVectorField(_JFD, "J-Field");

    boost::shared_ptr<SField_Cell_t> HField = Utils::getScalarCellField(_HFD);

    for (int j = localDomain[1].first(); j <= localDomain[1].last(); ++ j) {
        elem[1] = Index(j,j);
        for (int i = localDomain[0].first() ; i <= localDomain[0].last(); ++ i) {
            elem[0] = Index(i,i);
            Vector_t hfd = _HFD.localElement(elem);
            HField->localElement(elem) = hfd(0) + hfd(1);
        }
    }
    newStep.addScalarField(*HField, "H-Field");

    newStep.writeFile(fname.str());

    Timings::stopTimer(_outputTimer);

    ++_iteration;
}