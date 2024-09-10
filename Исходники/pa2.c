int main(void)
{
  double y[EQ_N][2];
  double (*func[EQ_N])();
  double parameter[PARTICLE_N][PARA_N], parameter_memory[PARA_N], resampled_parameter[PARTICLE_N][PARA_N];
  double ref_parameter[PARA_N];
  double time_point[TIME_POINT_N];
  double ref_time_point[TIME_POINT_N];

  int i, j, k, l, m;
  int mcmc_num, pa_num, integral_num, particle_num, rk_num, timepoint_num, parameter_num, equation_num;
  
  int x_flag = 0;
  double dt;

  double probability_before, probability_after, probability_ratio;
  int move_count = 0;

  double weight[PARTICLE_N], weight_tmp[PARTICLE_N];
  double total_weight = 0, power_total_weight, partial_total_weight, upper_weight, lower_weight;
  double log_weight[PARTICLE_N], log_weight_tmp[PARTICLE_N];
  double total_likelihood[PARTICLE_N], total_likelihood_previous[PARTICLE_N];
  double log_likelihood[PARTICLE_N], total_log_likelihood;
  double epsilon[POPULATION_N] = {1.5, 1.0, 0.75, 0.5, 0.25, 0.1, 0.09, 0.08, 0.07, 0.06, 0.05, 0.04, 0.03, 0.02, 0.01};
  double ess;
  int sampling_num;
  int resampling_count = 0;
  int weighten_particle_num[POPULATION_N] = {0, 0, 0, 0, 0}, last_weighten_particle_num = 0;
  int resampling_flag[POPULATION_N] = {0, 0, 0, 0, 0};

  double effective_particle_num = 0, total_effective_particle_num = 0;
  double weighten_particle_multiplier = 1;

  int mcmc_step;

  double unit_r, chosen_num;

  FILE *fp1, *fp2, *fp3, *fp4, *fp5, *fp6, *fp7, *fin;

  clock_t start, end;

  dt = 0.001;


  function_set(func);


/*** 計算開始 **********************************************************************************************************************************/

  /* 時間を計る */
  start = clock();
  
  /* 乱数の初期化 */
  init_genrand(2);

  /* ファイル設定 */
  fp1 = fopen("information2.data","w");

  /* 実験データの読み込み */
  fin = fopen("ref_time_point.data","r");

  for(timepoint_num=0;timepoint_num<TIME_POINT_N;timepoint_num++){
    fscanf(fin, "%lf", &ref_time_point[timepoint_num]);
  }

  fclose(fin);
  /* 実験データの読み込み終了 */


  /* 参照パラメータ値設定 */
  parameter_set(ref_parameter);

  /* サンプル番号初期化 */
  sampling_num = 0;

  printf("0 th population\n");

  /* ランダムサンプリングによる 粒子数個のパラメータセットの発生 **************************************************************************************/
  for( ; ; ){
    /* パラメータを発生させる */
    parameter_set(parameter[sampling_num]);
    parameter_generation(parameter[sampling_num], ref_parameter);

    sampling_num++;
    
    if(sampling_num == PARTICLE_N) break; 
  }


  /* 重みを初期化 正規化 */
  for(particle_num=0;particle_num<PARTICLE_N;particle_num++){
    weight[particle_num] = 1.0/PARTICLE_N;
  }
  /* ランダムサンプリングによる初期パラメータ発生 終了 ************************************************************************************************/









  
  /* Population annealing 開始 *****************************************************************************************************************/
  for(pa_num=0;pa_num<POPULATION_N;pa_num++){

    printf("%d th population\n", pa_num+1);
    
    /* 各粒子ごとに尤度の計算 */
    for(particle_num=0;particle_num<PARTICLE_N;particle_num++){
      total_likelihood[particle_num] = 0; /* 初期化 */
      total_likelihood_previous[particle_num] = 0; /* 初期化 */
    }


    /* 中間分布の計算 */
    for(particle_num=0;particle_num<PARTICLE_N;particle_num++){

      /* time point データの発生 */
      initial_condition_set(y);
      rk_search(1, dt, func, y, parameter[particle_num], time_point);

      /* 尤度の計算 */
      total_likelihood[particle_num] = indicator_function(time_point, ref_time_point, epsilon[pa_num]);

      if(pa_num==0){
        total_likelihood_previous[particle_num] = 1;
      }
      else{
        total_likelihood_previous[particle_num] = indicator_function(time_point, ref_time_point, epsilon[pa_num-1]);
      }

    }
    /* 中間分布の計算終了 */


    /* 重みの計算 */
    for(particle_num=0;particle_num<PARTICLE_N;particle_num++){
      weight[particle_num] = weight[particle_num] * total_likelihood[particle_num]/total_likelihood_previous[particle_num];
      if(total_likelihood[particle_num]==0 || total_likelihood_previous[particle_num]==0) weight[particle_num] = 0.0;
    }

    total_weight = 0.0;

    for(particle_num=0;particle_num<PARTICLE_N;particle_num++){
      total_weight = total_weight + weight[particle_num];
    }
    for(particle_num=0;particle_num<PARTICLE_N;particle_num++){
      weight[particle_num] = weight[particle_num]/total_weight;
    }


    /* 重みを持つ粒子数の計算 */
    for(particle_num=0;particle_num<PARTICLE_N;particle_num++){
      if(weight[particle_num]!=0) weighten_particle_num[pa_num]++;
    }
    fprintf(fp1, "weighten particle num = %d\n", weighten_particle_num[pa_num]);





    /* 各粒子ごとに */
    for(particle_num=0;particle_num<PARTICLE_N;particle_num++){

      /* 重みが0なら飛ばす */
      if(weight[particle_num]==0) continue;

      /* フラグの初期化 */
      x_flag = 0;


      /* MCMC 計算 */
      for(mcmc_num=0;mcmc_num<MCMC_MAX_STEP;mcmc_num++){
 
        /* 許容されなければ、元のままのパラメータ */
        if(x_flag == 1){
          for(parameter_num=0;parameter_num<PARA_N;parameter_num++){
            parameter[particle_num][parameter_num] = parameter_memory[parameter_num];
          }
        }


        /* 確率の初期化 */
        probability_before = 1.0;
        probability_after = 1.0;
    

        /* フラグの初期化 */
        x_flag = 0;


        /* 新候補の計算前の値を記憶 */
        for(parameter_num=0;parameter_num<PARA_N;parameter_num++){
          parameter_memory[parameter_num] = parameter[particle_num][parameter_num];
        }


        /* 移動前の確率を計算 */
        probability_before = probability_before*pdf_uniform_parameter(parameter[particle_num], ref_parameter); /* 事前分布を乗じる */

        
        total_likelihood[particle_num] = 0.0; /* 初期化 */

        /* time point データの発生 */
        initial_condition_set(y);
        rk_search(1, dt, func, y, parameter[particle_num], time_point);

        /* 尤度の計算 */
        total_likelihood[particle_num] = indicator_function(time_point, ref_time_point, epsilon[pa_num]);

        probability_before = probability_before * total_likelihood[particle_num]; /* 移動前の確率 */  


        /* 新候補を計算 パラメータの中から1つだけ動かす */
        parameter_sampler(parameter[particle_num]);


        /* 移動後の確率を計算 : 一様事前分布を乗じる */
        probability_after = probability_after*pdf_uniform_parameter(parameter[particle_num], ref_parameter); /* 事前分布を乗じる */
        

        if(probability_after == 0.0){
          x_flag = 1;
          for(parameter_num=0;parameter_num<PARA_N;parameter_num++){
            parameter[particle_num][parameter_num] = parameter_memory[parameter_num];
          }
          continue;
        }



        /* 移動後の確率を計算 */
        total_likelihood[particle_num] = 0.0; /* 初期化 */

        /* time point データの発生 */
        initial_condition_set(y);
        rk_search(1, dt, func, y, parameter[particle_num], time_point);

        /* 尤度の計算 */
        total_likelihood[particle_num] = indicator_function(time_point, ref_time_point, epsilon[pa_num]);

        probability_after = probability_after * total_likelihood[particle_num]; /* 移動後の確率 */


        if(probability_after == 0.0){
          x_flag = 1;
          for(parameter_num=0;parameter_num<PARA_N;parameter_num++){
            parameter[particle_num][parameter_num] = parameter_memory[parameter_num];
          }
          continue;
        }



        /* 移動前と移動後の確率の比の計算 */
        probability_ratio = probability_after/probability_before;

        /* [0,1) 単位乱数の発生 */
        unit_r = genrand_real2();   


        /* 移動の判定 */
        if(probability_ratio > unit_r){ 
          move_count++;
        }
        else{
          x_flag = 1;
          for(parameter_num=0;parameter_num<PARA_N;parameter_num++){
            parameter[particle_num][parameter_num] = parameter_memory[parameter_num];
          }
          continue;
        }
    
      }
      /* particle_num 番目の粒子の MCMC 終了 */
    }
    /* 全粒子の MCMC 終了 */
 




 
    /* リサンプリング ********************************************************/
    power_total_weight = 0.0;
    ess = 0.0;

    for(particle_num=0;particle_num<PARTICLE_N;particle_num++){
      power_total_weight = power_total_weight + pow(weight[particle_num], 2);
    }


    /* Effective Sample Size の計算 */
    ess = 1.0/power_total_weight;
    //if(pa_num==4) ess = 0.0;

    fprintf(fp1, "%d th population", pa_num);
    fprintf(fp1, "ESS = %f\t particle_num/2 = %f\n\n", ess, PARTICLE_N/2.0);
    

    /* リサンプリングの判定と実行 */
    if(ess < PARTICLE_N/2){

      fprintf(fp1, "resampling\n");
      resampling_count++;
      resampling_flag[pa_num] = 1;
      fprintf(fp1, "resampling flag = %d\n", resampling_flag[pa_num]);
      
      /* 粒子数個リサンプリングする 重複可 */
      for(m=0;m<PARTICLE_N;m++){

        /* [0,1) 乱数発生 */
        unit_r = genrand_real2();

        partial_total_weight = 0.0;

        /* l 番目の粒子が選ばれる */
        for(l=0;l<PARTICLE_N;l++){
          partial_total_weight = partial_total_weight + weight[l];

          upper_weight = partial_total_weight;
          lower_weight = partial_total_weight - weight[l];

          if((unit_r >= lower_weight) && (unit_r < upper_weight)){
            for(i=0;i<PARA_N;i++){
              resampled_parameter[m][i] = parameter[l][i];
            }
            break;
          }
        }

      }
      /* 粒子数個リサンプリング終了 */



      /* リサンプル後のパラメータと活性化時間の再設定 */
      for(l=0;l<PARTICLE_N;l++){
        for(i=0;i<PARA_N;i++){
          parameter[l][i] = resampled_parameter[l][i];
        }
      }



      /* リサンプル後の重みを初期化 正規化 */
      for(l=0;l<PARTICLE_N;l++){
        weight[l] = 1.0/PARTICLE_N;
      }


    }
    /* リサンプリングの判定と実行 終了 */
    /* リサンプリング終了 ****************************************************/

  }
  /* Population annealing 終了 *****************************************************************************************************************/
  

  for(pa_num=0;pa_num<POPULATION_N;pa_num++){
    if(resampling_flag[pa_num]==1){
      weighten_particle_multiplier = weighten_particle_multiplier * weighten_particle_num[pa_num]/PARTICLE_N;
    }
  }

  /* 重みを持つ粒子数の計算 */
  last_weighten_particle_num = 0;
  for(particle_num=0;particle_num<PARTICLE_N;particle_num++){
    if(weight[particle_num]!=0) last_weighten_particle_num++;
  }
  effective_particle_num = last_weighten_particle_num*weighten_particle_multiplier;
  
  fprintf(fp1, "effective particle number = %f\n", effective_particle_num);



  /* 移動回数、 リサンプリング回数、 モデル数を出力 */
  fprintf(fp1, "%d times move\n", move_count);
  fprintf(fp1, "%d times resampling\n", resampling_count);
  end = clock();
  /* 計算時間の出力 */
  fprintf(fp1, "%f min\n", (double)(end - start)/CLOCKS_PER_SEC/60.0);



  fclose(fp1);

  return 0;
}