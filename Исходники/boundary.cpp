void Boundary::bcsToImpose(FieldContainer<GlobalIndexType> &globalIndices,
                           FieldContainer<Scalar> &globalValues, TBC<Scalar> &bc,
                           DofInterpreter* dofInterpreter)
{
  set< GlobalIndexType > rankLocalCells = _mesh->cellIDsInPartition();
  map< GlobalIndexType, double> bcGlobalIndicesAndValues;

  for (GlobalIndexType cellID : rankLocalCells)
  {
    bcsToImpose(bcGlobalIndicesAndValues, bc, cellID, dofInterpreter);
  }
  singletonBCsToImpose(bcGlobalIndicesAndValues, bc, dofInterpreter);
  
  // ****** New, tag-based BC imposition follows ******
  map< GlobalIndexType, double> bcTagGlobalIndicesAndValues;
  
  map< int, vector<pair<VarPtr, TFunctionPtr<Scalar>>>> tagBCs = bc.getDirichletTagBCs(); // keys are tags
  
  MeshTopology* meshTopo = dynamic_cast<MeshTopology*>(_mesh->getTopology().get());
  
  TEUCHOS_TEST_FOR_EXCEPTION(!meshTopo, std::invalid_argument, "pure MeshTopologyViews are not yet supported by new tag-based BC imposition");
  
  for (auto tagBC : tagBCs)
  {
    int tagID = tagBC.first;
    
    vector<EntitySetPtr> entitySets = meshTopo->getEntitySetsForTagID(DIRICHLET_SET_TAG_NAME, tagID);
    for (EntitySetPtr entitySet : entitySets)
    {
      // get rank-local cells that match the entity set:
      set<IndexType> matchingCellIDs = entitySet->cellIDsThatMatch(_mesh->getTopology(), rankLocalCells);
      for (IndexType cellID : matchingCellIDs)
      {
        ElementTypePtr elemType = _mesh->getElementType(cellID);
        BasisCachePtr basisCache = BasisCache::basisCacheForCell(_mesh, cellID);
        
        for (auto varFunctionPair : tagBC.second)
        {
          VarPtr var = varFunctionPair.first;
          FunctionPtr f = varFunctionPair.second;
          
          vector<int> sideOrdinals = elemType->trialOrderPtr->getSidesForVarID(var->ID());
          
          for (int sideOrdinal : sideOrdinals)
          {
            BasisPtr basis = elemType->trialOrderPtr->getBasis(var->ID(), sideOrdinal);
            bool isVolume = basis->domainTopology()->getDimension() == _mesh->getDimension();
            for (int d=0; d<_mesh->getDimension(); d++)
            {
              vector<unsigned> matchingSubcells;
              if (isVolume)
                matchingSubcells = entitySet->subcellOrdinals(_mesh->getTopology(), cellID, d);
              else
              {
                CellTopoPtr cellTopo = elemType->cellTopoPtr;
                int sideDim = cellTopo->getDimension() - 1;
                vector<unsigned> matchingSubcellsOnSide = entitySet->subcellOrdinalsOnSide(_mesh->getTopology(), cellID, sideOrdinal, d);
                for (unsigned sideSubcellOrdinal : matchingSubcellsOnSide)
                {
                  unsigned cellSubcellOrdinal = CamelliaCellTools::subcellOrdinalMap(cellTopo, sideDim, sideOrdinal, d, sideSubcellOrdinal);
                  matchingSubcells.push_back(cellSubcellOrdinal);
                }
              }
              
              if (matchingSubcells.size() == 0) continue; // nothing to impose
              
              /*
               What follows - projecting the function onto the basis on the whole domain - is more expensive than necessary,
               in the general case: we can do the projection on just the matching subcells, and if we had a way of taking the
               restriction of a basis to a subcell of the domain, then we could avoid computing the whole basis as well.
               
               But for now, this should work, and it's simple to implement.
               */
              BasisCachePtr basisCacheForImposition = isVolume ? basisCache : basisCache->getSideBasisCache(sideOrdinal);
              int numCells = 1;
              FieldContainer<double> basisCoefficients(numCells,basis->getCardinality());
              Projector<double>::projectFunctionOntoBasisInterpolating(basisCoefficients, f, basis, basisCacheForImposition);
              basisCoefficients.resize(basis->getCardinality());
              
              set<GlobalIndexType> matchingGlobalIndices;
              for (unsigned matchingSubcell : matchingSubcells)
              {
                set<GlobalIndexType> subcellGlobalIndices = dofInterpreter->globalDofIndicesForVarOnSubcell(var->ID(),cellID,d,matchingSubcell);
                matchingGlobalIndices.insert(subcellGlobalIndices.begin(),subcellGlobalIndices.end());
              }
              
              FieldContainer<double> globalData;
              FieldContainer<GlobalIndexType> globalDofIndices;
//              dofInterpreter->interpretLocalBasisCoefficients(cellID, var->ID(), sideOrdinal, basisCoefficientsToImpose, globalData, globalDofIndices);
              dofInterpreter->interpretLocalBasisCoefficients(cellID, var->ID(), sideOrdinal, basisCoefficients, globalData, globalDofIndices);
              for (int globalDofOrdinal=0; globalDofOrdinal<globalDofIndices.size(); globalDofOrdinal++)
              {
                GlobalIndexType globalDofIndex = globalDofIndices(globalDofOrdinal);
                if (matchingGlobalIndices.find(globalDofIndex) != matchingGlobalIndices.end())
                  bcTagGlobalIndicesAndValues[globalDofIndex] = globalData(globalDofOrdinal);
              }
            }
          }
        }
      }
    }
  }
  
  // merge tag-based and legacy BC maps
  double tol = 1e-15;
  for (auto tagEntry : bcTagGlobalIndicesAndValues)
  {
    if (bcGlobalIndicesAndValues.find(tagEntry.first) != bcGlobalIndicesAndValues.end())
    {
      // then check that they match, within tolerance
      double diff = abs(bcGlobalIndicesAndValues[tagEntry.first] - tagEntry.second);
      TEUCHOS_TEST_FOR_EXCEPTION(diff > tol, std::invalid_argument, "Incompatible BC entries encountered");
    }
    else
    {
      bcGlobalIndicesAndValues[tagEntry.first] = tagEntry.second;
    }
  }
  
  globalIndices.resize(bcGlobalIndicesAndValues.size());
  globalValues.resize(bcGlobalIndicesAndValues.size());
  globalIndices.initialize(0);
  globalValues.initialize(0.0);
  int entryOrdinal = 0;
  for (auto bcEntry : bcGlobalIndicesAndValues)
  {
    globalIndices[entryOrdinal] = bcEntry.first;
    globalValues[entryOrdinal] = bcEntry.second;
    entryOrdinal++;
  }
}