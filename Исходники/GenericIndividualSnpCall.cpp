void GenericIndividualSnpCall::simpleSnpCall(string &fastaObj, BamReader &bamObj, int chrID, int leftPosition, int rightPosition, vector<Allele> &variantCandidates, map<int,list<tuple<char,int,int,double>>> &bamData)
{
    set<int> BlockSnpPositions;
    vector<Allele> BlockSnpAlleles;

    // rewind
    bamObj.Rewind();
    // set region
    bamObj.SetRegion(chrID, leftPosition, chrID, rightPosition);

    BamAlignment al;
    // search SNP positions in the region
    while (bamObj.GetNextAlignment(al))
    {
        if (!GenericBamAlignmentTools::goodAlignment(al))
            continue;

        if (!al.HasTag("MD"))
            continue;

        vector<long> SnpInAlignment;
        GenericBamAlignmentTools::getBamAlignmentMismatches(al, SnpInAlignment);

        for (int i=0; i<SnpInAlignment.size(); i++)
        {
            BlockSnpPositions.insert(SnpInAlignment[i]);
        }
    }

    // pileup visitor
    SimpleSnpCallPileupVisitor visitor(&fastaObj, chrID, leftPosition, rightPosition, m_downSample, &BlockSnpPositions, &BlockSnpAlleles, &bamData);

    PileupEngine SimpleSnpCallPileupEngine;
    SimpleSnpCallPileupEngine.AddVisitor(&visitor);

    // rewind
    bamObj.Rewind();
    // set region
    bamObj.SetRegion(chrID, leftPosition, chrID, rightPosition);
    // load data
    while(bamObj.GetNextAlignment(al))
    {

        if (!GenericBamAlignmentTools::goodAlignment(al))
            continue;

        if (!GenericBamAlignmentTools::validMapQuality(al, m_minMapQuality))
            continue;

        if (!GenericBamAlignmentTools::validReadIdentity(al, m_maxMismatchFrac))
            continue;

        if (!GenericBamAlignmentTools::validReadLength(al, m_minReadLength))
            continue;

        if (!al.HasTag("MD"))
            continue;

        SimpleSnpCallPileupEngine.AddAlignment(al);
    }
    SimpleSnpCallPileupEngine.Flush();

    // Filter SNP candidiate
    for (int i=0; i<BlockSnpAlleles.size(); i++)
    {
        Allele allele = BlockSnpAlleles[i];

        if (allele.m_alleleDepth < m_minSnpRead)
            continue;
        if (allele.m_alleleDepth < m_minSnpFrac*allele.m_globalDepth)
            continue;

        variantCandidates.push_back(allele);
    }

}