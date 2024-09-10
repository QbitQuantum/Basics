static void populatebyrow (IloModel model, IloNumVarArray x, IloRangeArray c) {
  
  IloEnv env = model.getEnv();
  IloNumArray costs(env);
  IloNumArray time(env);
IloNumArray product(env);

  int costs_array[]  = {1,1,1,10,1,12,2,2,5,10};
  int time_array[]  = {10,1,7,3,2,3,2,3,7,1};
  int product_array[]  = {0,3,1,2,-2,0,0,0,0,0};
  

  for(int i=0;i<10;i++)
    costs.add(costs_array[i]);

  for(int i=0;i<10;i++)
    time.add(time_array[i]);

  for(int i=0;i<10;i++)
    product.add(product_array[i]);



  x.add(IloBoolVar(env,"x12")); //0
  x.add(IloBoolVar(env,"x24")); //1
  x.add(IloBoolVar(env,"x46")); //2
  x.add(IloBoolVar(env,"x13")); //3
  x.add(IloBoolVar(env,"x32")); //4
  x.add(IloBoolVar(env,"x35")); //5
  x.add(IloBoolVar(env,"x56")); //6
  x.add(IloBoolVar(env,"x25")); //7
  x.add(IloBoolVar(env,"x34")); //8
  x.add(IloBoolVar(env,"x45")); //9


x.add(IloNumVar(env,0,IloInfinity,ILOINT,"s2")); //10
x.add(IloNumVar(env,0,IloInfinity,ILOINT,"s3")); //11
x.add(IloNumVar(env,0,IloInfinity,ILOINT,"s4")); //12
x.add(IloNumVar(env,0,IloInfinity,ILOINT,"s5")); //13
x.add(IloNumVar(env,0,IloInfinity,ILOINT,"s1")); //14
x.add(IloNumVar(env,0,IloInfinity,ILOINT,"s6")); //15

x.add(IloNumVar(env,0,IloInfinity,ILOINT,"q2")); //16
x.add(IloNumVar(env,0,IloInfinity,ILOINT,"q3")); //17
x.add(IloNumVar(env,0,IloInfinity,ILOINT,"q4")); //18
x.add(IloNumVar(env,0,IloInfinity,ILOINT,"q5")); //19
x.add(IloNumVar(env,0,IloInfinity,ILOINT,"q1")); //20
x.add(IloNumVar(env,0,IloInfinity,ILOINT,"q6")); //21



  
  model.add(IloMinimize(env, costs[0]*x[0] + costs[1]*x[1] + costs[2]*x[2] + costs[3]*x[3] + costs[4]*x[4] + costs[5]*x[5] + costs[6]*x[6] + costs[7]*x[7] + costs[8]*x[8] + costs[9]*x[9]));
  c.add(x[0]+ x[3] == 1); // arcs sortant du noeud de depart
  c.add(x[2]+ x[6] == 1); // arcs entrant au noeud d arrivee
  c.add(x[1]+ x[7] - x[0] - x[4] == 0);
  c.add(x[8]+ x[5] + x[4] - x[3] == 0);
  c.add(x[9]+ x[2] - x[1] - x[8] == 0);
  c.add(x[6]- x[7] - x[5] - x[9] == 0);
  c.add(time[0]*x[0] + time[1]*x[1] + time[2]*x[2] + time[3]*x[3] + time[4]*x[4] + time[5]*x[5] + time[6]*x[6] + time[7]*x[7] + time[8]*x[8] + time[9]*x[9] <= 14);
//c.add(product[0]*x[0] + product[1]*x[1] + product[2]*x[2] + product[3]*x[3] + product[4]*x[4] + product[5]*x[5] + product[6]*x[6] + product[7]*x[7] + product[8]*x[8] + product[9]*x[9] <= 4);

c.add(x[14]+time[0]-1000*(1-x[0]) - x[10]<= 0);
c.add(x[20]+product[0]-1000*(1-x[0]) - x[16]<= 0);


c.add(x[10]+time[1]-1000*(1-x[1]) - x[12]<= 0);
c.add(x[16]+product[1]-1000*(1-x[1]) - x[18]<= 0);
c.add(x[18]-product[1]-1000*(1-x[1]) - x[16]<= 0);


c.add(x[12]+time[2]-1000*(1-x[2]) - x[15]<= 0);
c.add(x[18]+product[2]-1000*(1-x[2]) - x[21]<= 0);
c.add(x[21]-product[2]-1000*(1-x[2]) - x[18]<= 0);


c.add(x[14]+time[3]-1000*(1-x[3]) - x[11]<= 0);
c.add(x[20]+product[3]-1000*(1-x[3]) - x[17]<= 0);
c.add(x[17]-product[3]-1000*(1-x[3]) - x[20]<= 0);

c.add(x[13]+time[6]-1000*(1-x[6]) - x[15]<= 0);
c.add(x[19]+product[6]-1000*(1-x[6]) - x[21]<= 0);

c.add(x[10]+time[7]-1000*(1-x[7]) - x[13]<= 0);
c.add(x[16]+product[7]-1000*(1-x[7]) - x[19]<= 0);

c.add(x[12]+time[9]-1000*(1-x[9]) - x[13]<= 0);
c.add(x[18]+product[9]-1000*(1-x[9]) - x[19]<= 0);

c.add(x[11]+time[4]-1000*(1-x[4]) - x[10] <=0);
c.add(x[17]+product[4]-1000*(1-x[4]) - x[16]<= 0);
c.add(x[16]-product[4]-1000*(1-x[4]) - x[17]<= 0);


c.add(x[11]+time[8]-1000*(1-x[8]) - x[12]<= 0);
c.add(x[17]+product[8]-1000*(1-x[8]) - x[18]<= 0);

c.add(x[11]+time[5]-1000*(1-x[5]) - x[13]<= 0);
c.add(x[17]+product[5]-1000*(1-x[5]) - x[19]<= 0);



c.add(5 <= x[10] <= 7);
c.add(2 <= x[11] <= 5);
c.add(5 <= x[12] <= 9);
c.add(0 <= x[13] <= 20);
c.add(0 <= x[14] <= 0);
c.add(0 <= x[15] <= 14);

/*
c.add(2 <= x[17] <= 4);
c.add(0 <= x[16] <= 2);
c.add(3 <= x[18] <= 4);

c.add(0 <= x[19] <= 1000);
//c.add(0 <= x[20] <= 0);*/
c.add(3 <= x[21] <= 4);

c.add( x[20] == 1);









  model.add(c);
}