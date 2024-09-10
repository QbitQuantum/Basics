void NGLScene::writeKey()
{
  std::cout << "KEY!" << std::endl;
  ngl::Vec3 translation(0,0,0);
  for(unsigned int i=0; i<m_geo.size(); i++ ){
    m_rotHistory.push_back(m_geo[i]->m_rotation);
    m_localRotHistory.push_back(m_geo[i]->m_localRotation);
    if(i>0){
      translation += m_geo[i-1]->getTopTranslation();
    }
    else{
      translation.set(0,0,0);
    }
    m_transHistory.push_back(m_geo[i]->getTopTranslation());
  }
  if(m_rotHistory.size()/4 == Data::instance()->animLength){
    //exit(writeOut());
    m_buttons.clear();

    std::cout << "adding" << std::endl;

    ngl::Vec2 buttonPos;
    ngl::Vec2 buttonSize;
    float borderX = 50.0;
    float borderY = 50.0;

    borderX = borderX/m_width;
    borderY = borderY/m_height;

    float keyX = borderX * 2 - 1.0;
    float keyY = borderY * 2 - 1.0;

    float keyX2 = (keyX * -1);

    buttonPos.set(keyX, keyY);
    buttonSize.set(0.5, 0.55);

    if(Data::instance()->mode == Data::TOUCHSMALL_R){
      buttonPos.m_x *= -1;
      buttonPos.m_x -= buttonSize.m_x;
    }

    addButton(buttonPos, buttonSize, Data::instance()->baseColor, Button::Action::FINISH);

    updateButtonArrays();
    m_finished = true;
    m_timer2 = startTimer(1000/Data::instance()->fps);
  }
  else if(m_rotHistory.size()/4 > Data::instance()->animLength){
    std::cerr << "ERROR, size of history too large" << std::endl;
  }
  m_frame++;
  ngl::ShaderLib::instance()->use("progressShader");
  ngl::ShaderLib::instance()->setRegisteredUniform("frame", m_frame);
}