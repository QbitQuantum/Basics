void QCastViewGL::getToolbars(CPtrVector<QToolBar>& toolbars)
{
   if (! pView) return;
   CPtrVector<cogx::display::CDisplayCamera> cameras;
   pView->getCameras(cameras);
   if (cameras.size() < 1) return;
   // pBar->parent will be reset in QViewContainer
   QToolBar *pBar = new QToolBar(QString::fromStdString(pView->m_id), this);
   if (pBar) {
      unsigned int nc = cameras.size();
      if (nc > 3) nc = 3;
      cogx::display::CDisplayCamera* pCamera;
      for (unsigned int i= 0; i < nc; i++) {
         QToolButton *pBut = new QToolButton(pBar);
         pCamera = cameras[i];
         QString text = QString::fromStdString(pCamera->name);
         QAction* pAct = new QAction(QIcon(":/toolButton/camera-photo.png"), text, pBut);
         pAct->setToolTip("Select Camera: " + text);
         pAct->setData(qVariantFromValue((void*)pCamera));
         pBut->setDefaultAction(pAct);
         pBar->addWidget(pBut);
         pBar->connect(pAct, SIGNAL(triggered()), this, SLOT(onCameraChangeAction()));

         // With more than 3 cameras things become complicated...
         if (i == 2 && cameras.size() > 2) {
            QAction *pPopAct;
            QMenu *pMenu = new QMenu(pBut); // parent MUST be button, see onCameraChangeAction
            pBut->setMenu(pMenu);
            pBut->setPopupMode(QToolButton::MenuButtonPopup);

            for (unsigned int j = 0; j < cameras.size(); j++) {
               if (i == j) {
                  pMenu->addAction(pAct);
                  pAct->setParent(pMenu);   // parent MUST be menu, see onCameraChangeAction
               }
               else {
                  pCamera = cameras[j];
                  text = QString::fromStdString(pCamera->name);
                  pPopAct = pMenu->addAction(QIcon(":/toolButton/camera-photo.png"), text);
                  pPopAct->setData(qVariantFromValue((void*)pCamera));
                  pPopAct->setToolTip("Select Camera: " + text);
                  pBar->connect(pPopAct, SIGNAL(triggered()), this, SLOT(onCameraChangeAction()));
               }
            }

            if (0) {
               text = "TODO: Configure camera buttons...";
               pPopAct = pMenu->addAction(QIcon(":/toolButton/camera-photo.png"), text);
               pBar->connect(pPopAct, SIGNAL(triggered()), this, SLOT(onActConfigureCameras()));
            }
         }
      }
      toolbars.push_back(pBar);
   }
}