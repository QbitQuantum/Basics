  //! \return whether partial charges were successfully assigned to this molecule
  bool EQEqCharges::ComputeCharges(OBMol &mol)
  {
    int i, j, a, c, N = mol.NumAtoms();
    double cellVolume;
    VectorXf chi(N), J(N), b(N), x(N);
    MatrixXf J_ij(N, N), A(N, N);
    OBUnitCell *obuc;
    matrix3x3 unitcell, fourier;
    vector3 dx;
    int numNeighbors[3];
    OBAtom *atom;

    // If parameters have not yet been loaded, do that
    if (!_paramFileLoaded)
    {
      if (ParseParamFile())
      {
        _paramFileLoaded = true;
      } else
      {
        return false;
      }
    }

    // Calculate atomic properties based around their ionic charge
    for (i = 0; i < N; i++)
    {
      atom = mol.GetAtom(i + 1);
      a = atom->GetAtomicNum();
      c = _chargeCenter[a];

      // Fail if ionization data is missing for any atom in the molecule
      if (_ionizations[a][c + 1] == -1 || _ionizations[a][c] == -1 || a > TABLE_OF_ELEMENTS_SIZE)
      {
        obErrorLog.ThrowError(__FUNCTION__, "Insufficient ionization data for atoms in the given molecule. Update `data/eqeqIonizations.txt` with missing information and re-run this function.", obError);
        return false;
      }

      J(i) = _ionizations[a][c + 1] - _ionizations[a][c];
      chi(i) = 0.5 * (_ionizations[a][c + 1] + _ionizations[a][c]) - (a == 1? 0 : c * J(i));
    }

    // If a unit cell is defined, use the periodic Ewald calculation
    if (mol.HasData(OBGenericDataType::UnitCell))
    {
      // Get unit cell and calculate its Fourier transform + volume
      obuc = (OBUnitCell *) mol.GetData(OBGenericDataType::UnitCell);
      unitcell = obuc->GetCellMatrix();
      fourier = (2 * PI * unitcell.inverse()).transpose();
      cellVolume = obuc->GetCellVolume();

      // Get the number of radial unit cells to use in x, y, and z
      numNeighbors[0] = int(ceil(minCellLength / (2.0 * (obuc->GetA())))) - 1;
      numNeighbors[1] = int(ceil(minCellLength / (2.0 * (obuc->GetB())))) - 1;
      numNeighbors[2] = int(ceil(minCellLength / (2.0 * (obuc->GetC())))) - 1;

      for (i = 0; i < N; i++)
      {
        atom = mol.GetAtom(i + 1);
        for (j = 0; j < N; j++)
        {
          dx = atom->GetVector() - (mol.GetAtom(j + 1))->GetVector();
          J_ij(i, j) = GetPeriodicEwaldJij(J(i), J(j), dx, (i == j), unitcell, fourier, cellVolume, numNeighbors);
        }
      }
    // If no unit cell, use the simplified nonperiodic calculation
    } else
    {
      for (i = 0; i < N; i++)
      {
        atom = mol.GetAtom(i + 1);
        for (j = 0; j < N; j++)
        {
          J_ij(i, j) = GetNonperiodicJij(J(i), J(j), atom->GetDistance(j + 1), (i == j));
        }
        return false;
      }
    }

    // Formulate problem as A x = b, where x is the calculated partial charges
    // First equation is a simple overall balance: sum(Q) = 0
    A.row(0) = VectorXf::Ones(N);
    b(0) = 0;

    // Remaining equations are based off of the fact that, at equilibrium, the
    // energy of the system changes equally for a change in any charge:
    //     dE/dQ_1 = dE/dQ_2 = ... = dE/dQ_N
    A.block(1, 0, N - 1, N) = J_ij.block(0, 0, N - 1, N) - J_ij.block(1, 0, N - 1, N);
    b.tail(N - 1) = chi.tail(N - 1) - chi.head(N - 1);

    // The solution is a list of charges in the system
    x = A.colPivHouseholderQr().solve(b);

    // Now we are done calculating, pass all this back to OpenBabel molecule
    mol.SetPartialChargesPerceived();
    OBPairData *dp = new OBPairData;
    dp->SetAttribute("PartialCharges");
    dp->SetValue("EQEq");
    dp->SetOrigin(perceived);
    mol.SetData(dp);

    m_partialCharges.clear();
    m_partialCharges.reserve(N);
    m_formalCharges.clear();
    m_formalCharges.reserve(N);

    for (i = 0; i < N; i ++)
    {
      atom = mol.GetAtom(i + 1);
      atom->SetPartialCharge(x(i));
      m_partialCharges.push_back(x(i));
      m_formalCharges.push_back(atom->GetFormalCharge());
    }

    obErrorLog.ThrowError(__FUNCTION__, "EQEq charges successfully assigned.", obInfo);
    return true;
  }