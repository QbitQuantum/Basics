/**
 * @brief リスタート時の瞬時値ファイル読み込み
 * @param [in]  fp   ファイルポインタ
 * @param [out] flop 浮動小数点演算数
 */
void FFV::RestartInstantaneous(FILE* fp, double& flop)
{
  double time, r_time;
  const unsigned step = C.Restart_step;
  std::string fname;
  std::string fmt(C.file_fmt_ext);

  REAL_TYPE bp = ( C.Unit.Prs == Unit_Absolute ) ? C.BasePrs : 0.0;
  REAL_TYPE refD = C.RefDensity;
  REAL_TYPE refV = C.RefVelocity;
  
  // ガイド出力
  int gs = C.GuideOut;
  
  // dummy
  unsigned i_dummy=0;
  double f_dummy=0.0;

  
  const int* m_div = paraMngr->GetDivNum();
  
  // 自身の領域終点インデックス
  int tail[3];
  for (int i=0;i<3;i++) tail[i]=head[i]+size[i]-1;
  
  
  // Pressure
  if ( DFI_IN_PRS->ReadData(d_p,
                            step,
                            guide,
                            G_size,
                            (int *)m_div,
                            head,
                            tail,
                            r_time,
                            true,
                            i_dummy,
                            f_dummy) != CIO::E_CIO_SUCCESS ) Exit(0);
  
  if ( d_p == NULL ) Exit(0);
  time = r_time;
  
  // 有次元の場合，無次元に変換する
  if ( C.Unit.File == DIMENSIONAL )
  {
    REAL_TYPE bp = ( C.Unit.Prs == Unit_Absolute ) ? C.BasePrs : 0.0;
    U.convArrayPrsD2ND(d_p, size, guide, bp, C.RefDensity, C.RefVelocity, flop);
  }
  
  Hostonly_ printf     ("\tPressure has read :\tstep=%d  time=%e [%s]\n",
                        step, time, (C.Unit.File == DIMENSIONAL)?"sec.":"-");
  Hostonly_ fprintf(fp, "\tPressure has read :\tstep=%d  time=%e [%s]\n",
                    step, time, (C.Unit.File == DIMENSIONAL)?"sec.":"-");

  
  // ここでタイムスタンプを得る
  if (C.Unit.File == DIMENSIONAL) time /= C.Tscale;
  CurrentStep = step;
  CurrentTime = time;
  
  // v00[]に値をセット
  copyV00fromRF(time);
  
  
  
  if ( DFI_IN_VEL->ReadData(d_wo,
                            step,
                            guide,
                            G_size,
                            (int *)m_div,
                            head,
                            tail,
                            r_time,
                            true,
                            i_dummy,
                            f_dummy) != CIO::E_CIO_SUCCESS ) Exit(0);
  
  if( d_wo == NULL ) Exit(0);
  
  REAL_TYPE refv = (C.Unit.File == DIMENSIONAL) ? refV : 1.0;
  REAL_TYPE u0[4];
  u0[0] = v00[0];
  u0[1] = v00[1];
  u0[2] = v00[2];
  u0[3] = v00[3];
  
  Hostonly_ printf     ("\tVelocity has read :\tstep=%d  time=%e [%s]\n",
                        step, time, (C.Unit.File == DIMENSIONAL)?"sec.":"-");
  Hostonly_ fprintf(fp, "\tVelocity has read :\tstep=%d  time=%e [%s]\n",
                    step, time, (C.Unit.File == DIMENSIONAL)?"sec.":"-");
  
  time = r_time;
  
  if (C.Unit.File == DIMENSIONAL) time /= C.Tscale;
  
  if ( time != CurrentTime )
  {
    Hostonly_ printf     ("\n\tTime stamp is different between files\n");
    Hostonly_ fprintf(fp, "\n\tTime stamp is different between files\n");
    Exit(0);
  }
  
  // indexの変換と無次元化
  fb_vin_nijk_(d_v, size, &guide, d_wo, u0, &refv, &flop);
  

  
  if ( !C.isHeatProblem() ) return;
  
  
  
  // Instantaneous Temperature fields
  if ( DFI_IN_TEMP->ReadData(d_ws,
                             C.Restart_step,
                             guide,
                             G_size,
                             (int *)m_div,
                             head,
                             tail,
                             r_time,
                             true,
                             i_dummy,
                             f_dummy) != CIO::E_CIO_SUCCESS ) Exit(0);
  
  if( d_ws == NULL ) Exit(0);
  
  time = r_time;
  
  if (C.Unit.File == DIMENSIONAL) time /= C.Tscale;
  
  Hostonly_ printf     ("\tTemperature has read :\tstep=%d  time=%e [%s]\n",
                        step, time, (C.Unit.File == DIMENSIONAL)?"sec.":"-");
  Hostonly_ fprintf(fp, "\tTemperature has read :\tstep=%d  time=%e [%s]\n",
                    step, time, (C.Unit.File == DIMENSIONAL)?"sec.":"-");
  
  if ( time != CurrentTime )
  {
    Hostonly_ printf     ("\n\tTime stamp is different between files\n");
    Hostonly_ fprintf(fp, "\n\tTime stamp is different between files\n");
    Exit(0);
  }
  
  if (C.Unit.File == DIMENSIONAL)
  {
    U.convArrayTmp2IE(d_ie, size, guide, d_ws, d_bcd, mat_tbl, C.BaseTemp, C.DiffTemp, true, flop);
  }
  else
  {
    U.convArrayTmp2IE(d_ie, size, guide, d_ws, d_bcd, mat_tbl, C.BaseTemp, C.DiffTemp, false, flop);
  }
  
}