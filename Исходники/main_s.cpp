float Random_Floorplanning(Clo_Red_Graph &fp,int times, int& A, int& W){
  Solution Best;  
  Normalize(fp, A, W);
  fp.contour_packing();
  fp.compute_wire_length(); 
  fp.compute_cost(alpha, beta, A, W); 
  fp.get_solution(Best);
   
  double total_cost=0.0, pre_cost, cost;
  int t = 0;
  int N = times;
  pre_cost = fp.get_cost();
  do{
      for(int i=0; i < N; i++){
        fp.perturbate1();
        fp.contour_packing();
        fp.compute_wire_length();
        fp.compute_cost(alpha, beta, A, W);

        cost = fp.get_cost();
        //cout<<"cost="<<cost<<endl;
        if(cost-pre_cost > 0.0){
          total_cost+= (cost-pre_cost);
          t++;
          pre_cost = cost;
        }
       
        if(cost <= Best.Cost){
          fp.get_solution(Best);
          //if(alpha!=0.0&&beta!=0.0){
          //  cout << "cost="<< Best.Cost<<", < Area, Wire > = " <<  Best.Area <<
          //      ", " << Best.Wire <<" >" << endl;                           
          //}else{ 
          //  cout << "==> Cost=" << Best.Cost << endl;
          //}
        }

//        if((double(fp.getWireLength()/W))<1){
//           W=fp.getWireLength();
//           fp.compute_cost(alpha, beta, A, W);
//           pre_cost=fp.get_cost();
//           double best_cost=0.5*(((double)(Best.Area))/A+
//                                ((double)(Best.Wire))/W);
//           if(pre_cost < best_cost){
//              fp.get_solution(Best);
//              cout<<"Tuing Wire"<<endl;
//              cout<<"************************************"<<endl;
//              cout << "   ==> < Area, Wire > = " <<  Best.Area <<
//                ", " << Best.Wire <<" >" << endl;                                 
//              cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;  
//           }
//        }
//      }

//      if(((double(fp.getArea()))/(double(A))<0.9)){
//         //cout<<"Tuning Area"<<endl;
//         A=fp.getArea();
//         fp.compute_cost(alpha, beta, A, W);
//         pre_cost=fp.get_cost();
//         double best_cost=0.5*(((double)(Best.Area))/A+
//                              ((double)(Best.Wire))/W);
//         if(pre_cost < best_cost){
//            fp.get_solution(Best);
           // cout<<"best cost="<<best_cost<<endl;
           // cout<<"************************************"<<endl;
           // cout << "   ==> < Area, Wire > = " <<  Best.Area <<
           //      ", " << Best.Wire <<" >" << endl;                                 
           // cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;  
//         }
      }
  }while(total_cost==0.0);
  fp.recover(Best); 
  A=fp.getArea();
  W=fp.getWireLength();
//  W=Best.Area;
//  fp.compute_cost(alpha, beta, A, W);
  return (total_cost/t);
}