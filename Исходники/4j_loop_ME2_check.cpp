int main(void) {
        	
    unsigned int old_cw;
    fpu_fix_start(&old_cw);

    settings::use_setting("INTERFACE_MODE normal");
    settings::use_setting("USE_AUTOMATED_ASSEMBLY yes");
    settings::use_setting("USE_PARENT_FILES yes");
    settings::use_setting("USE_HIGHER_PRECISION no");
    settings::use_setting("SET_ALL_RAT_TO_ZERO no");
    settings::use_setting("COLOR_MODE full_color");  // can do full_color too...

// settings::use_setting("SAME_HELICITY_PROJECTION 0");
// settings::use_setting("INTERFACE_MODE gridWarmup");

#include "std_momenta.hpp"

string process_names[]={
  "ME2_6q_abc",  //1
  "ME2_6q_aab",  //2
  "ME2_6q_aaa",  //3
  "ME2_2g4q_ab", //4
  "ME2_2g4q_aa", //5
  "ME2_4g2q",    //6
  "ME2_6g"       //7
};

int process[]={
  //6q
  1,-1,2,-2,3,-3,   //1
  1,-1,1,-1,2,-2,   //2
  1,-1,1,-1,1,-1,   //3
  //2g4q
  1,-1,2,-2,21,21,  //4
  1,-1,1,-1,21,21,  //5
  //4g2q
  1,-1,21,21,21,21, //6
  //6g
  21,21,21,21,21,21 //7
};


bool check[]={
  true,  //1
  true,  //2
  true,  //3
  true,  //4
  true,  //5
  true,  //6
  true   //7
};


    int err(0);
    double tol=0.0000001;
    int target_number;

    std::cout<<setprecision(15);

    const int nparticles=6;
    
    BH_interface bhi;
    BH_Ampl* me2;
    
#include "constants.h"

    bhi.set("alpha_S",0.118000000);
    
    double p_a1[] = { 3490.61080006012,0,0,3490.61080006012};
    double p_a2[] = { 3221.74940955983,0,0,-3221.74940955983};
    double p_a3[] = { 2470.50305593186,1259.90166188355,-1920.18505340262,-910.451817748153};
    double p_a4[] = { 388.198860574184,185.023902306007,-255.653663742933,226.065731904168};
    double p_a5[] = { 2740.47219051162,-1512.34538509335,2280.26252219564,-152.977426519063};
    double p_a6[] = { 1113.18610260228,67.4198209037964,-104.423805050085,1106.22490286334};
    
    vector<double> p1(p_a1,p_a1+4), p2(p_a2,p_a2+4), p3(p_a3,p_a3+4), p4(p_a4,p_a4+4), p5(p_a5,p_a5+4), p6(p_a6,p_a6+4);
    double mu_momenta6pt(100.);
/*
	//keeping this PS point for testing
	vector<double> p1, p2, p3, p4, p5, p6;

	p1.push_back(-egz.p(1).E().real());p1.push_back(-egz.p(1).X().real());p1.push_back(-egz.p(1).Y().real());p1.push_back(-egz.p(1).Z().real());
	p2.push_back(-egz.p(2).E().real());p2.push_back(-egz.p(2).X().real());p2.push_back(-egz.p(2).Y().real());p2.push_back(-egz.p(2).Z().real());
	p3.push_back(egz.p(3).E().real());p3.push_back(egz.p(3).X().real());p3.push_back(egz.p(3).Y().real());p3.push_back(egz.p(3).Z().real());
	p4.push_back(egz.p(4).E().real());p4.push_back(egz.p(4).X().real());p4.push_back(egz.p(4).Y().real());p4.push_back(egz.p(4).Z().real());
	p5.push_back(egz.p(5).E().real());p5.push_back(egz.p(5).X().real());p5.push_back(egz.p(5).Y().real());p5.push_back(egz.p(5).Z().real());
	p6.push_back(egz.p(6).E().real());p6.push_back(egz.p(6).X().real());p6.push_back(egz.p(6).Y().real());p6.push_back(egz.p(6).Z().real());
	double mu_momenta6pt(6.);

	_MESSAGE("WARNING: Targets are not for this PS points!.")
*/

    vector<vector <double> > momenta6pt;
    momenta6pt.push_back(p1);    momenta6pt.push_back(p2);    momenta6pt.push_back(p3);
    momenta6pt.push_back(p4);    momenta6pt.push_back(p5);    momenta6pt.push_back(p6);

//    cout << "p1: " << p1 << endl;
//    cout << "p2: " << p2 << endl;
//    cout << "p3: " << p3 << endl;
//    cout << "p4: " << p4 << endl;
//    cout << "p5: " << p5 << endl;
//    cout << "p6: " << p6 << endl;

    C me2_born,me2_finite,me2_single_pole,me2_double_pole;

    vector<C> res_me2_born;
    vector<C> res_me2_dp_LC;
    vector<C> res_me2_sp_LC;
    vector<C> res_me2_f_LC; // results for born, double pole, single pole, finite

    vector<C> res_me2_dp_FC;
    vector<C> res_me2_sp_FC;
    vector<C> res_me2_f_FC; // results for born, double pole, single pole, finite

    // leading colour targets

 //     ME2_6q_abc:{1,-1,2,-2,3,-3}
      res_me2_f_LC.push_back(-240.7413323);
      res_me2_sp_LC.push_back(55.40316749);
      res_me2_dp_LC.push_back(-10.16869583);

//      ME2_6q_aab:{1,-1,1,-1,2,-2}
      res_me2_f_LC.push_back(-213.6635487);
      res_me2_sp_LC.push_back(48.43174035);
      res_me2_dp_LC.push_back(-9.241351448);

      //     ME2_6q_aaa:{1,-1,1,-1,1,-1}

      res_me2_f_LC.push_back(-213.458348);
      res_me2_sp_LC.push_back(52.44021912);
      res_me2_dp_LC.push_back(-9.733965272);

      //     ME2_2g4q_ab:{1,-1,2,-2,21,21}
      res_me2_f_LC.push_back(-217.0937375);
      res_me2_sp_LC.push_back(53.81811665);
      res_me2_dp_LC.push_back(-12.96893499);

      //     ME2_2g4q_aa:{1,-1,1,-1,21,21}
      res_me2_f_LC.push_back(-175.9847059);
      res_me2_sp_LC.push_back(47.17450055);
      res_me2_dp_LC.push_back(-12.29180813);

      //     ME2_4g2q:{1,-1,21,21,21,21}
      res_me2_f_LC.push_back(-208.5746866);
      res_me2_sp_LC.push_back(56.82551973);
      res_me2_dp_LC.push_back(-15);

      //     ME2_6g:{21,21,21,21,21,21}
      res_me2_f_LC.push_back(-253.6109107);
      res_me2_sp_LC.push_back(74.93713962);
      res_me2_dp_LC.push_back(-18);



    // full colour targets
    //   ME2_6q_abc:{1,-1,2,-2,3,-3}
    res_me2_born.push_back(6.504549029e-11);
    res_me2_f_FC.push_back(-191.4925462);
    res_me2_sp_FC.push_back(38.54167351);
    res_me2_dp_FC.push_back(-8);
      
      //   ME2_6q_aab:{1,-1,1,-1,2,-2}
      res_me2_born.push_back(9.50285442e-11);
      res_me2_f_FC.push_back(-180.8590428);
      res_me2_sp_FC.push_back(37.24574697);
      res_me2_dp_FC.push_back(-8);

      //   ME2_6q_aaa:{1,-1,1,-1,1,-1}
      res_me2_born.push_back(3.838428771e-10);
      res_me2_f_FC.push_back(-172.9069809);
      res_me2_sp_FC.push_back(38.61048961);
      res_me2_dp_FC.push_back(-8);

      //   ME2_2g4q_ab:{1,-1,2,-2,21,21}
      res_me2_born.push_back(1.00210522e-07);
      res_me2_f_FC.push_back(-196.2273097);
      res_me2_sp_FC.push_back(45.24346781);
      res_me2_dp_FC.push_back(-11.33333333);

      //   ME2_2g4q_aa:{1,-1,1,-1,21,21}
      res_me2_born.push_back(2.453491013e-07);
      res_me2_f_FC.push_back(-163.5334078);
      res_me2_sp_FC.push_back(42.0298159);
      res_me2_dp_FC.push_back(-11.33333333);

      //   ME2_4g2q:{1,-1,21,21,21,21}
      res_me2_born.push_back(9.533364118e-06);
      res_me2_f_FC.push_back(-211.19793716);
      res_me2_sp_FC.push_back(56.17442645);
      res_me2_dp_FC.push_back(-14.66666667);

      //   ME2_6g:{21,21,21,21,21,21}
      res_me2_born.push_back(0.008754601186);
      res_me2_f_FC.push_back(-253.7213543);
      res_me2_sp_FC.push_back(74.97732652);
      res_me2_dp_FC.push_back(-18);



    
    int nbr_points(1);
    clock_t before,after;
    for (int i=0; i<sizeof(check); i++){ 
      
     
      if(check[i]){
        _MESSAGE("====");
        vector<int> particles(process + nparticles*i, process + nparticles*(i+1));
        BHinput input(momenta6pt,mu_momenta6pt);
	
        clock_t before_constr = clock();
	me2 = bhi.new_ampl(particles);
	clock_t after_constr = clock();
        _MESSAGE("-----");
        _MESSAGE3(process_names[i],":\t",particles);
    	_MESSAGE3("\tconstr. time:\t",double(after_constr-before_constr)/double(CLOCKS_PER_SEC)," s");


	before = clock();
	for(int j=0;j<nbr_points;j++){ 
	  bhi.operator()(input);

#if HP
	  cout << "using higher precision HP" << endl;
	  me2_finite      = me2->get_finite_HP();
	  me2_single_pole = me2->get_single_pole_HP();
	  me2_double_pole = me2->get_double_pole_HP();
#else
	  me2_finite      = me2->get_finite();
	  me2_single_pole = me2->get_single_pole();
	  me2_double_pole = me2->get_double_pole();
#endif
	  me2_born        = me2->get_born();


	  _PRINT(me2_born);
	  _PRINT(me2_finite);
	  _PRINT(me2_single_pole);
	  _PRINT(me2_double_pole);

	}
	after = clock();
    }
    
      if(check[i]){ // we check each of the three colour cases
      _MESSAGE3("\teval time:    \t", double(after-before)/double(CLOCKS_PER_SEC)/double(nbr_points)," s");
      if (settings::BH_interface_settings::s_BH_color_mode==0){ //full colour
	_CHECK(res_me2_born[i],me2_born,tol,"\tborn:\t",err);
	_CHECK(res_me2_dp_FC[i],me2_double_pole,tol,"\tdouble:\t",err);
	_CHECK(res_me2_sp_FC[i],me2_single_pole,tol,"\tsingle:\t",err);
	_CHECK(res_me2_f_FC[i],me2_finite,tol,"\tfinite:\t",err);
      }
      if (settings::BH_interface_settings::s_BH_color_mode==1){ // leading colour
	_CHECK(res_me2_born[i],me2_born,tol,"\tborn:\t",err);
	_CHECK(res_me2_dp_LC[i],me2_double_pole,tol,"\tdouble:\t",err);
	_CHECK(res_me2_sp_LC[i],me2_single_pole,tol,"\tsingle:\t",err);
	_CHECK(res_me2_f_LC[i],me2_finite,tol,"\tfinite:\t",err);
	  }

      if (settings::BH_interface_settings::s_BH_color_mode==2){ // full_minus_leading
	_CHECK(res_me2_born[i],me2_born,tol,"\tborn:\t",err);
	_CHECK(res_me2_dp_FC[i]-res_me2_dp_LC[i],me2_double_pole,tol,"\tdouble:\t",err);
	_CHECK(res_me2_sp_FC[i]-res_me2_sp_LC[i],me2_single_pole,tol,"\tsingle:\t",err);
	_CHECK(res_me2_f_FC[i]-res_me2_f_LC[i],me2_finite,tol,"\tfinite:\t",err);
	  }
	}
 } // end of for loop
 
 
    cout<< "*********************************************"<<endl;
    cout<< "*                                           *"<<endl;
    cout<< "* total number of errors: "<<err<<"                *"  << endl;
    cout<< "*                                           *"<<endl;
    cout<< "*********************************************"<<endl;
 

//    BH::CachedOLHA::Cached_OLHA_factory::default_COLHA->print_state();
//    BH::CachedTHA::Cached_THA_factory::default_CTHA->print_state();
    
fpu_fix_end(&old_cw);

return err;
}