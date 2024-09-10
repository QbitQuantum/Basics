//----------------------------------------------------------------------------
void GelatinCube::CreateSprings ()
{
    // The inner 4-by-4-by-4 particles are used as the control points of a
    // B-spline volume.  The outer layer of particles are immovable to
    // prevent the cuboid from collapsing into itself.
    int iSlices = 6;
    int iRows = 6;
    int iCols = 6;

    // Viscous forces applied.  If you set viscosity to zero, the cuboid
    // wiggles indefinitely since there is no dissipation of energy.  If
    // the viscosity is set to a positive value, the oscillations eventually
    // stop.  The length of time to steady state is inversely proportional
    // to the viscosity.
#ifdef _DEBUG
    float fStep = 0.1f;
#else
    float fStep = 0.01f;  // simulation needs to run slower in release mode
#endif
    float fViscosity = 0.01f;
    m_pkModule = new PhysicsModule(iSlices,iRows,iCols,fStep,fViscosity);

    // The initial cuboid is axis-aligned.  The outer shell is immovable.
    // All other masses are constant.
    float fSFactor = 1.0f/(float)(iSlices-1);
    float fRFactor = 1.0f/(float)(iRows-1);
    float fCFactor = 1.0f/(float)(iCols-1);
    int iSlice, iRow, iCol;
    for (iSlice = 0; iSlice < iSlices; iSlice++)
    {
        for (iRow = 0; iRow < iRows; iRow++)
        {
            for (iCol = 0; iCol < iCols; iCol++)
            {
                m_pkModule->Position(iSlice,iRow,iCol) =
                    Vector3f(iCol*fCFactor,iRow*fRFactor,iSlice*fSFactor);

                if ( 1 <= iSlice && iSlice < iSlices-1
                &&   1 <= iRow && iRow < iRows-1
                &&   1 <= iCol && iCol < iCols-1 )
                {
                    m_pkModule->SetMass(iSlice,iRow,iCol,1.0f);
                    m_pkModule->Velocity(iSlice,iRow,iCol) =
                        0.1f*Vector3f(Mathf::SymmetricRandom(),
                        Mathf::SymmetricRandom(),Mathf::SymmetricRandom());
                }
                else
                {
                    m_pkModule->SetMass(iSlice,iRow,iCol,Mathf::MAX_REAL);
                    m_pkModule->Velocity(iSlice,iRow,iCol) = Vector3f::ZERO;
                }
            }
        }
    }

    // springs are at rest in the initial configuration
    const float fConstant = 10.0f;
    Vector3f kDiff;

    for (iSlice = 0; iSlice < iSlices-1; iSlice++)
    {
        for (iRow = 0; iRow < iRows; iRow++)
        {
            for (iCol = 0; iCol < iCols; iCol++)
            {
                m_pkModule->ConstantS(iSlice,iRow,iCol) = fConstant;
                kDiff = m_pkModule->Position(iSlice+1,iRow,iCol) -
                    m_pkModule->Position(iSlice,iRow,iCol);
                m_pkModule->LengthS(iSlice,iRow,iCol) = kDiff.Length();
            }
        }
    }

    for (iSlice = 0; iSlice < iSlices; iSlice++)
    {
        for (iRow = 0; iRow < iRows-1; iRow++)
        {
            for (iCol = 0; iCol < iCols; iCol++)
            {
                m_pkModule->ConstantR(iSlice,iRow,iCol) = fConstant;
                kDiff = m_pkModule->Position(iSlice,iRow+1,iCol) -
                    m_pkModule->Position(iSlice,iRow,iCol);
                m_pkModule->LengthR(iSlice,iRow,iCol) = kDiff.Length();
            }
        }
    }

    for (iSlice = 0; iSlice < iSlices; iSlice++)
    {
        for (iRow = 0; iRow < iRows; iRow++)
        {
            for (iCol = 0; iCol < iCols-1; iCol++)
            {
                m_pkModule->ConstantC(iSlice,iRow,iCol) = fConstant;
                kDiff = m_pkModule->Position(iSlice,iRow,iCol+1) -
                    m_pkModule->Position(iSlice,iRow,iCol);
                m_pkModule->LengthC(iSlice,iRow,iCol) = kDiff.Length();
            }
        }
    }
}