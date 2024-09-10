Translation Robot::com(const Link& startLink, const Frame& referenceFrame,
                       Explorer::policy p) const
{
    Translation fcom;
    double fmass = 0, lmass = 0;

    _crawler.reset(startLink, p);
    const Link* current = _crawler.nextLink();
    while(current != NULL)
    {
        lmass = current->mass();
        fcom += lmass*current->com(referenceFrame);
        fmass += lmass;

        for(size_t i=0; i<current->numManips(); ++i)
        {
            const Manipulator& manip_ = current->manip(i);
            lmass = manip_.mass();
            fcom += lmass*manip_.com(referenceFrame);
            fmass += lmass;
        }

        current = _crawler.nextLink();
    }

//    if( verb.Assert(fmass > 0, verbosity::ASSERT_CASUAL,
//                    "Center of Mass requested for Robot '"+name()+"' starting at Link '"
//                    +startLink.name()+"', but there was no mass at all!") )
    if( fmass > 0 )
        fcom = fcom/fmass;
    else
        fcom.setZero();

    return fcom;
}