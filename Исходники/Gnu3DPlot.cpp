RTC::ReturnCode_t Gnu3DPlot::onDeactivated(RTC::UniqueId ec_id)
{
	fprintf(m_gp, "exit\n"); // gnuplotの終了
	fflush(m_gp);
	_pclose(m_gp); // パイプを閉じる
  return RTC::RTC_OK;
}