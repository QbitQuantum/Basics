void StitcherView::scaleScene(qreal new_scale){
  if(new_scale * transform().m11() > 0.01 && new_scale * transform().m11() < 100){
    scale(new_scale,new_scale);
  }
}