///<summary>
/// CGameProcess_t:: RenderDebugInfo() : muestra la información del pitch, yaw, position y número de caras de los objetos estáticos y dinámicos.
///</summary>
///<param name=""></param>
///<returns name=""></returns>
void CGameProcess_t::RenderDebugInfo()
{
  CProcess::RenderDebugInfo();

  CFontManager* fm = CORE->GetFontManager();
  CTimer *t = CORE->GetTimer();
  uint32 l_iFontId = fm->GetTTF_Id("arial");

  //fm->DrawText(10,75,colWHITE,l_iFontId,"Pitch: %f",CORE->GetCameraManager()->GetCamera()->GetObject3D()->GetPitch());
  //fm->DrawText(10,95,colWHITE,l_iFontId,"Yaw: %f",CORE->GetCameraManager()->GetCamera()->GetObject3D()->GetYaw());
  //fm->DrawText(10,115,colWHITE,l_iFontId,"Position: [%f,%f,%f]",CORE->GetCameraManager()->GetCamera()->GetObject3D()->GetPosition().x,CORE->GetCameraManager()->GetCamera()->GetObject3D()->GetPosition().y,CORE->GetCameraManager()->GetCamera()->GetObject3D()->GetPosition().z);

  CStaticMeshManager* sm= CORE->GetStaticMeshManager();
  fm->DrawTextA(10,135,colYELLOW,l_iFontId,"Num of Faces (Static Meshes): %ld",sm->GetTotalObjectsFaces());
  CAnimatedModelManager* am=CORE->GetAnimatedModelManager();
  fm->DrawTextA(10,155,colYELLOW,l_iFontId,"Num of Faces (Dinamic Meshes): %ld",am->GetTotalNumFaces());
  fm->DrawTextA(10,185,colYELLOW,l_iFontId,g_CollitionObject.c_str());
  std::string temp = CORE->GetCameraManager()->GetCamera()->GetName();
  fm->DrawTextA(10,205,colYELLOW,l_iFontId,temp.c_str());

  fm->DrawTextA(10, 215, colCYAN, l_iFontId, m_pPlayer->m_sDebug.c_str());

  /*fm->DrawTextA(10,300,colBLUE,l_iFontId,"A* - Ctrl izq.+ (1-9)");
  fm->DrawTextA(10,320,colBLUE,l_iFontId,"Dijsktra - Ctrl der.+ (1-9)");

  fm->DrawTextA(10,360,colWHITE,l_iFontId,"Check Actions: %ld",m_CheckActions);
  fm->DrawTextA(10,380,colWHITE,l_iFontId,"Move Mouse: %ld",m_MoveMouse);
  fm->DrawTextA(10,400,colWHITE,l_iFontId,"LUA: %ld",m_UpdateLua);
  fm->DrawTextA(10,420,colWHITE,l_iFontId,"Mov Player: %ld",m_MovPlayer);
  fm->DrawTextA(10,440,colWHITE,l_iFontId,"Particles: %ld",mParticles);
  fm->DrawTextA(10,460,colWHITE,l_iFontId,"PhysX: %ld",m_PhysX);
  fm->DrawTextA(10,480,colWHITE,l_iFontId,"IA: %ld",m_IA);*/
}