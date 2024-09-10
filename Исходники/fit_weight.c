double grad_descent_step_mt(DataPoint *datapoints, long int n_dp, Weights *weights, double alpha){

  long int bounds[TH_NUM + 1];

  int th; int interval = n_dp/4;
  for(th = 0; th < TH_NUM; th++){
    bounds[th] = interval * th;
  }
  bounds[th] = n_dp;

  double deriv_sqr[TH_NUM];
  
  global_datapoints = datapoints;
  global_bounds = bounds;
  global_deriv_sqr = deriv_sqr;
  global_n_dp = n_dp;
  global_alpha = alpha;
  
  global_confcount = malloc(sizeof(ConfigCounter));
  memset(global_confcount, 0, sizeof(ConfigCounter));
  long int i;
  for(i = 0; i < n_dp; i++){
    increment_confcount(global_confcount, datapoints[i].board);
  }

  pthread_t tids[TH_NUM];
  Weights *section_delta[TH_NUM];
  for(th = 0; th < TH_NUM; th++){
    pthread_create(&(tids[th]), NULL, grad_descent_step_thread, &bounds[th]);
  }
  for(th = 0; th < TH_NUM; th++){
    pthread_join(tids[th], (void *)&section_delta[th]);
  }

  for(th = 0; th < TH_NUM; th++){
    uint32_t white, black;
    for(white = 0; white < 256; white++){
      for(black = 0; black < 256; black++){
	if(white & black){
	  continue;
	}
	weights->row_1[white][black] += section_delta[th]->row_1[white][black];
	weights->row_2[white][black] += section_delta[th]->row_2[white][black];
	weights->row_3[white][black] += section_delta[th]->row_3[white][black];
	weights->row_4[white][black] += section_delta[th]->row_4[white][black];

	weights->diag_8[white][black] += section_delta[th]->diag_8[white][black];
      }
    }
    for(white = 0; white < 128; white++){
      for(black = 0; black < 128; black++){
	if(white & black){
	  continue;
	}
	weights->diag_7[white][black] += section_delta[th]->diag_7[white][black];
      }
    }
    for(white = 0; white < 64; white++){
      for(black = 0; black < 64; black++){
	if(white & black){
	  continue;
	}
	weights->diag_6[white][black] += section_delta[th]->diag_6[white][black];
      }
    }
    for(white = 0; white < 32; white++){
      for(black = 0; black < 32; black++){
	if(white & black){
	  continue;
	}
	weights->diag_5[white][black] += section_delta[th]->diag_5[white][black];
      }
    }
    for(white = 0; white < 16; white++){
      for(black = 0; black < 16; black++){
	if(white & black){
	  continue;
	}
	weights->diag_4[white][black] += section_delta[th]->diag_4[white][black];
      }
    }
    for(white = 0; white < 512; white++){
      for(black = 0; black < 512; black++){
	if(white & black){
	  continue;
	}
	int index = offset_19683[white] + _pext_u32(black, ~white);
	weights->corner_33[index] += section_delta[th]->corner_33[index];
      }
    }
    for(white = 0; white < 1024; white++){
      for(black = 0; black < 1024; black++){
	if(white & black){
	  continue;
	}
	int index = offset_59049[white] + _pext_u32(black, ~white);
	weights->corner_25[index] += section_delta[th]->corner_25[index];
	weights->edge_xx[index] += section_delta[th]->edge_xx[index];
      }
    }
  }

  for(th = 0; th < TH_NUM; th++){
    free(section_delta[th]);
  }
  
  double total_deriv = 0;
  for(th = 0; th < TH_NUM; th++){
    total_deriv += global_deriv_sqr[th];
  }
  total_deriv = sqrt(total_deriv);

  return total_deriv;
}