int main(void) {
        	
    unsigned int old_cw;
    fpu_fix_start(&old_cw);

settings::use_setting("USE_AUTOMATED_ASSEMBLY yes");
settings::use_setting("REAL_ASSEMBLY_ONLY yes");


string process_names[]={
   "ME2_distinct_quarks_4q2g",
   "ME2_identical_up_quarks_4q2g", 
   "ME2_identical_down_quarks 4q2g", 
   "ME2_2q4g",
   "ME2_6g",
   "ME2_6q_11",  
   "ME2_6q_22",
   "ME2_6q_21",
   "ME2_6q_33",
   "ME2_6q_34",
   "ME2_6q_23",
   "ME2_6q_31"};

int process[]={
   2,-2, 4,-4,21,21,//ME2_distinct_quarks_4q2g
   1,-1, 1,-1,21,21,//ME2_identical_up_quarks_4q2g 
   2,-2, 2,-2,21,21,//ME2_identical_down_quarks 4q2g 
   2,-2,21,21,21,21,//ME2_2q4g
  21,21,21,21,21,21,//ME2_6g
   1,-1, 3,-3, 5,-5,//ME2_6q_11  
   1,-1, 2,-2, 3,-3,//ME2_6q_22
   2,-2, 2,-2, 1,-1,//ME2_6q_21
   2,-2, 2,-2, 3,-3,//ME2_6q_33
   2,-2, 2,-2, 4,-4,//ME2_6q_34
   2,-2, 2,-2, 2,-2,//ME2_6q_23
   1,-1, 1,-1, 1,-1};//ME2_6q_31


bool check[]={
  true,//ME2_distinct_quarks_4q2g
  true,//ME2_identical_up_quarks_4q2g 
  true,//ME2_identical_down_quarks 4q2g 
  true,//ME2_2q4g
  true,//ME2_6g
  true,//ME2_6_11  
  true,//ME2_6q_22
  true,//ME2_6q_21
  true,//ME2_6q_33
  true,//ME2_6q_34
  true,//ME2_6q_23
  true};//ME2_6q_31



    int err(0);
    double tol(0.00001);
    int target_number;

    std::cout<<setprecision(5);

	double mu_momenta6pt(7.);
    vector<vector <double> > momenta6pt;

	BH_interface bhi;
	BH_Ampl* me2;

	bhi.set("W_mass",80.4190000);
 	bhi.set("W_width",2.04759951);
	bhi.set("alpha_S",0.118000000);
	bhi.set("alpha_QED",1./132.506980);
	double sin_th_2=1.-pow(80.419/91.188,2);
	bhi.set("sin_th_2",sin_th_2);
	bhi.set("sin_2th",sin(2.*asin(sqrt(sin_th_2))));
	double GF=1.16639*pow(10.,-5);
	double alpha_QED=sqrt(2.)*GF*pow(80.419,2)*sin_th_2/3.141592653589793;

  double p_a1[] = { 0.5000000E+03,  0.0000000E+00,  0.0000000E+00,  0.5000000E+03};//  0.0000000E+00
  double p_a2[] = { 0.5000000E+03,  0.0000000E+00,  0.0000000E+00, -0.5000000E+03};//  0.0000000E+00
  double p_a3[] = { 0.8855133E+02, -0.2210069E+02,  0.4008035E+02, -0.7580543E+02};//  0.3015783E-05
  double p_a4[] = { 0.3283294E+03, -0.1038496E+03, -0.3019338E+03,  0.7649492E+02};//  0.2132481E-05
  double p_a5[] = { 0.1523581E+03, -0.1058810E+03, -0.9770964E+02,  0.4954839E+02};//  0.2523185E-05
  double p_a6[] = { 0.4307611E+03,  0.2318313E+03,  0.3595630E+03, -0.5023788E+02};// 



    vector<double> p1(p_a1,p_a1+4), p2(p_a2,p_a2+4), p3(p_a3,p_a3+4), p4(p_a4,p_a4+4), p5(p_a5,p_a5+4), p6(p_a6,p_a6+4);
     momenta6pt.push_back(p1);
     momenta6pt.push_back(p2);
     momenta6pt.push_back(p3);
     momenta6pt.push_back(p4);
     momenta6pt.push_back(p5);
     momenta6pt.push_back(p6);

    C me2_born=C(0,0);
    vector<C> res_me2_born;

    double normalization; 
    res_me2_born.clear();
    // ME2 distinct quarks 4q2g 
    normalization=6.*6.*(2); 
    res_me2_born.push_back(C(normalization*9.50066944E-08,0)); //u u~ > c c~ g g QED=0 @0
    // ME2 identical quarks 4q2g 
    res_me2_born.push_back(C(normalization*4.01072037E-07,0)); //d d~ > d d~ g g QED=0 @1
    // ME2 identical anti-quarks 4q2g 
    res_me2_born.push_back(C(normalization*4.01072037E-07,0)); //u u~ > u u~ g g QED=0 @2
    // ME2 2q4g
    normalization=6.*6.*(4.*3.*2); 
    res_me2_born.push_back(C(normalization*2.9711906E-06,0)); //u u~ > g g g g QED=0 @3
    // ME2 6g
    normalization=16.*16.*(4.*3.*2); 
    res_me2_born.push_back(C(normalization*0.000159299258,0));// g > g g g g QED=0 @4
    // ME2 6q_11 - 4 
    normalization=6.*6.; 
    // not sure where this number is from 
    res_me2_born.push_back(C(normalization*5.8936084E-10,0));//d d~ > s s~ c c~  QED=0 @5
    //ME2 6q_22 - 5 
    res_me2_born.push_back(C(normalization*5.8936084E-10,0));
    //ME2 6q_21 - 6
    res_me2_born.push_back(C(normalization*1.26088795E-09,0));//u u~ > u u~ s s~  QED=0 @7
    //ME2 6q_33 - 7
    res_me2_born.push_back(C(normalization*1.26088795E-09,0));//u u~ > u u~ s s~  QED=0 @7
    //res_me2_born.push_back(C(4*normalization*0,0));
    //ME2 6q_34 - 8
    res_me2_born.push_back(C(normalization*1.26088795E-09,0));//u u~ > u u~ s s~  QED=0 @7
    //res_me2_born.push_back(C(normalization*0,0));
    //ME2 6q_23 - 9
    res_me2_born.push_back(C(4*normalization*1.61559443E-08,0));//u u~ > u u~ u u~  QED=0 @10
    //ME2 6q1g_31 - 10
    res_me2_born.push_back(C(4*normalization*1.61559443E-08,0));//u u~ > u u~ u u~  QED=0 @10

    clock_t before, after, before_c, after_c;
    int nbr_points(10);


for (int i=0; i<12; i++){ 
    if(check[i]){
        _MESSAGE("====");
        vector<int> particles(process+6*i,process+6*(i+1));
        BHinput input(momenta6pt,mu_momenta6pt);
       

        //if(i==3) settings::use_setting("USE_AUTOMATED_ASSEMBLY no");
        //else settings::use_setting("USE_AUTOMATED_ASSEMBLY yes");
        before_c=clock();
            me2=bhi.new_tree_ampl(particles);
        after_c=clock();
        _MESSAGE("-----");
        _MESSAGE3(process_names[i],":\t",particles);
    	_MESSAGE3("\tconstr. time:\t",double(after_c-before_c)/double(CLOCKS_PER_SEC)," s");

    {
        // quick fix for avoiding HP-computation
        for(int j=0;j<10;j++){ 
            bhi.operator()(input);
        	me2_born=me2->get_born();
        }

       before=clock();
        for(int j=0;j<nbr_points;j++){ 
            bhi.operator()(input);
        	me2_born=me2->get_born();
        }
        after=clock();
    }
    }
    if(check[i]){
        _MESSAGE3("\teval time:    \t", double(after-before)/double(CLOCKS_PER_SEC)/double(nbr_points)," s");
        _CHECK(res_me2_born[i],me2_born,tol,"\tmatch target:\t",err) 
    }
}
    cout<< "*********************************************"<<endl;
    cout<< "*                                           *"<<endl;
    cout<< "* total number of errors: "<<err<<"                *"  << endl;
    cout<< "*                                           *"<<endl;
    cout<< "*********************************************"<<endl;
 
    fpu_fix_end(&old_cw);


return err;
}