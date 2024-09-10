void frmViewCtrl::Init(){
  viewctrl = dv->viewctrl.get();
  lights   = dv->lights.get();

  CONNECT(ui->backgrnd,frmViewCtrl::backgrnd);
  CONNECT(ui->showtool,frmViewCtrl::showtool);
  CONNECT(ui->drawsimple,frmViewCtrl::drawsimple);
  CONNECT(ui->orthoprojection,frmViewCtrl::orthoprojection);
  CONNECT(ui->zoom_plus,frmViewCtrl::zoom_plus);
  CONNECT(ui->zoom_minus,frmViewCtrl::zoom_minus);
  CONNECT(ui->animmethod,frmViewCtrl::animmethod);
  CONNECT(ui->animstart,frmViewCtrl::anim_start);
  CONNECT(ui->light1,frmViewCtrl::light1);
  CONNECT(ui->light2,frmViewCtrl::light2);
  CONNECT(ui->reset,frmViewCtrl::reset);
}