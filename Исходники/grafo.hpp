void grafo::KRUSKAL(void)
{
 // pesquisa entre as arestas não ligadas a com menor peso e que não gere loop
 vector<bool> AuX(size());
 vector<vector<bool> > AUX(size());

 num N=size();

 for( num k=0; k<size()-1; k++) {
  AUX[k]=vector<bool>(size());
  for( num t=k+1; t<size(); t++)
   if(connected(k,t)) {
    AUX[k][t]=AUX[t][k]=AuX[k]=AuX[t]=true;
    N-=2;
   }
 }

 while(N>0)
// for( num s=0; s<100*199; s++)
 { 
  vector<bool> Aux(size());
  weight aux=INF;
  vertex v=0, w=0;

  for( num i=0; i<size()-1; i++)
   for( num j=i+1; j<size(); j++)
    if( !AUX[i][j] & getw(i,j) < aux) {
     aux=getw(i,j);
     v=i; w=j;
   }
//  cout << v << "->" << w << " " << aux << endl;

  if(aux==INF) return;

  AUX[v][w]=AUX[w][v]=true;
  insert(v, w);
//  cout << endl << "check loop" << endl;
  if(in_loop(v, v, v, Aux) ) {
//  if( !AuX[v] | !AuX[w]) 
//   insert(v,w);
//   cout << "loop" << endl;
   remove(v,w);
  }
//  else
//   continue;
//  cout << endl << "end ckeck loop" << endl;
  if( !AuX[v]) N--;
  if( !AuX[w]) N--;
  AuX[v]=AuX[w]=true;
//  for( num s=0; s<size(); s++)
//   cout << AuX[s];
//  cout << endl;
//  cout << k << endl;
 }
}