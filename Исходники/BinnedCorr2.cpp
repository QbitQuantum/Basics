 static void ProcessXi(
     const Cell<NData,C>& c1, const Cell<KData,C>& c2, const double ,
     XiData<NData,KData>& xi, int k)
 { xi.xi[k] += c1.getW() * c2.getData().getWK(); }