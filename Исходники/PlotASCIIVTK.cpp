PlotASCIIVTKCommand::PlotASCIIVTKCommand(const VField_Edge_t & EFD,
                                         const VField_Cell_t & HFD,
                                         const VField_Edge_t & JFD,
                                         const std::string & baseName):
    _EFD(EFD),
    _HFD(HFD),
    _JFD(JFD),
    _baseName(baseName),
    _dx(EFD.get_mesh().get_meshSpacing(0)),
    _dy(EFD.get_mesh().get_meshSpacing(1)),
    _iteration(0)
{
    _outputTimer = Timings::getTimer("ascii_vtk_output");

    FieldLayout<DIM> & FL = EFD.getLayout();
    Utils::getLocalDomains(FL, _lDoms);
    Utils::addGostCellToLocalDomains(FL, _lDoms);
    Utils::decreaseLocalDomainsLast(FL, _lDoms);
}