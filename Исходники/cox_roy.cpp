template <class cCRNode> void  cTplCoxRoyAlgo<cCRNode>::SetStdCostRegul(double aCoeff,double aCste,int aVmin)
{
    for (int anX=X0(); anX<X1() ; anX++)
        for (int anY=Y0(); anY<Y1() ; anY++)
             for (int aZ = ZMin(anX,anY); aZ< ZMax(anX,anY) ; aZ++)
             {
                 cRoyPt    aP1 (anX,anY,aZ);
                 cCRNode & aS1 = NodeOfP(aP1);
                 int  aC1 = aS1.ResidualFlow(mDirZPlus);

                 for (int anEdg=0; anEdg<NbEdges() ; anEdg++)
                 {
                     if (aS1.EdgeIsValide(anEdg) && (!tabCRIsVertical[anEdg]))
                     {
                           cRoyPt aP2(aP1,anEdg);
                           cCRNode & aS2 = NodeOfP(aP2);
                           int aC2 = aS2.ResidualFlow(mDirZPlus);

                           double aCost = aCste + aCoeff*(aC1+aC2)/2.0;
                           if (Cnx8())
                               aCost *= tabCRIsArcV8[anEdg] ? 0.2928 : 0.4142 ;
                           int iCost = int(aCost+0.5);
                           if (iCost<aVmin)
                              iCost = aVmin;
                           aS1.SetResidualFlow(anEdg,iCost);
                     }
                 }
             }
}