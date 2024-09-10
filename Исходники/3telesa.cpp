  Rovnice() :
    d1( Sqrt((x+Mi)*(x+Mi) + y*y) ),
    d2( Sqrt((x-MiC)*(x-MiC) +y*y) ),
    x1 ( x
       + 2*y1
       - MiC / (d1*d1*d1) * (x+Mi)
       - Mi / (d2*d2*d2) * (x-MiC),
       0 // poŸ. podm¡nka
       ),
    y1(  y
       -2*x1
       -MiC*y / (d1*d1*d1)
       -Mi*y / (d2*d2*d2),
//       -2.00158510637908255224053786224 // poŸ. podm¡nka
       -2.0317326295573368357302057924 // poŸ. podm¡nka
     ),
    x(x1,0.994),
    y(y1)

    {}