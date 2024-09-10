void Widget3D::show_hide_actor(QListWidgetItem * itemDuble){

  itemDuble->setSelected(true);

  bool visible = m_source_list.at(m_actor_list->row(itemDuble))->getRepresentation(this->m_RenderView)->isVisible();

  for(int i=0;i<m_actor_list->selectedItems().size();++i)
  {
      QListWidgetItem * item = m_actor_list->selectedItems().at(i);

      //if actor is visible
      if(visible){
        //Hide actor/region : Change icon and text color
        item->setTextColor(Qt::gray);
        item->setIcon(QIcon(":/paraview_icons/pqEyeballd16.png"));
      }else{
        //Show actor/region : Change icon and text color
        item->setTextColor(Qt::black);
        item->setIcon(QIcon(":/paraview_icons/pqEyeball16.png"));
      }

      //Set actor/region visibility
      m_source_list.at(m_actor_list->selectionModel()->selectedRows().at(i).row())
          ->getRepresentation(this->m_RenderView)->setVisible(!visible);

  }

  //be sure the mesh is updated
  m_RenderView->getWidget()->update();
  reset_camera();

}