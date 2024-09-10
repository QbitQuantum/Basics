void Foam::pairPotentialList::readPairPotentialDict
(
    const List<word>& idList,
    const dictionary& pairPotentialDict,
    const polyMesh& mesh
)
{
    Info<< nl << "Building pair potentials." << endl;

    rCutMax_ = 0.0;

    for (label a = 0; a < nIds_; ++a)
    {
        word idA = idList[a];

        for (label b = a; b < nIds_; ++b)
        {
            word idB = idList[b];

            word pairPotentialName;

            if (a == b)
            {
                if (pairPotentialDict.found(idA + "-" + idB))
                {
                    pairPotentialName = idA + "-" + idB;
                }
                else
                {
                    FatalErrorInFunction
                        << "Pair pairPotential specification subDict "
                        << idA << "-" << idB << " not found"
                        << nl << abort(FatalError);
                }
            }
            else
            {
                if (pairPotentialDict.found(idA + "-" + idB))
                {
                    pairPotentialName = idA + "-" + idB;
                }

                else if (pairPotentialDict.found(idB + "-" + idA))
                {
                    pairPotentialName = idB + "-" + idA;
                }

                else
                {
                    FatalErrorInFunction
                        << "Pair pairPotential specification subDict "
                        << idA << "-" << idB << " or "
                        << idB << "-" << idA << " not found"
                        << nl << abort(FatalError);
                }

                if
                (
                    pairPotentialDict.found(idA+"-"+idB)
                 && pairPotentialDict.found(idB+"-"+idA)
                )
                {
                    FatalErrorInFunction
                        << "Pair pairPotential specification subDict "
                        << idA << "-" << idB << " and "
                        << idB << "-" << idA << " found multiple definition"
                        << nl << abort(FatalError);
                }
            }

            (*this).set
            (
                pairPotentialIndex(a, b),
                pairPotential::New
                (
                    pairPotentialName,
                    pairPotentialDict.subDict(pairPotentialName)
                )
            );

            if ((*this)[pairPotentialIndex(a, b)].rCut() > rCutMax_)
            {
                rCutMax_ = (*this)[pairPotentialIndex(a, b)].rCut();
            }

            if ((*this)[pairPotentialIndex(a, b)].writeTables())
            {
                fileHandler().mkDir(mesh.time().path());
                autoPtr<Ostream> ppTabFile
                (
                    fileHandler().NewOFstream
                    (
                        mesh.time().path()/pairPotentialName
                    )
                );

                if
                (
                    !(*this)[pairPotentialIndex(a, b)].writeEnergyAndForceTables
                    (
                        ppTabFile()
                    )
                )
                {
                    FatalErrorInFunction
                        << "Failed writing to "
                        << ppTabFile().name() << nl
                        << abort(FatalError);
                }
            }
        }
    }

    if (!pairPotentialDict.found("electrostatic"))
    {
        FatalErrorInFunction
            << "Pair pairPotential specification subDict electrostatic"
            << nl << abort(FatalError);
    }

    electrostaticPotential_ = pairPotential::New
    (
        "electrostatic",
        pairPotentialDict.subDict("electrostatic")
    );

    if (electrostaticPotential_->rCut() > rCutMax_)
    {
        rCutMax_ = electrostaticPotential_->rCut();
    }

    if (electrostaticPotential_->writeTables())
    {
        fileHandler().mkDir(mesh.time().path());
        autoPtr<Ostream> ppTabFile
        (
            fileHandler().NewOFstream
            (
                mesh.time().path()/"electrostatic"
            )
        );

        if (!electrostaticPotential_->writeEnergyAndForceTables(ppTabFile()))
        {
            FatalErrorInFunction
                << "Failed writing to "
                << ppTabFile().name() << nl
                << abort(FatalError);
        }
    }

    rCutMaxSqr_ = rCutMax_*rCutMax_;
}