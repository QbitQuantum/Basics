void Executor::timerEvent(QTimerEvent *)
{
   TimerKiller killer(this, timer_id_, interval_);
   //ищем топовое окно заданного класса
   static const QString psClass = "TfrmTable";
   static const int minFoldHue = 15;
   static const int maxFoldHue = 30;
   static const int minCallHue = 60;
   static const int maxCallHue = 70;
   static const int minCheckHue = 42;
   static const int maxCheckHue = 58;

   //смотрим топовое окно
   WId FgWnd = GetForegroundWindow();
   char clName[MAX_WND_TEXT];
   GetClassNameA(FgWnd, clName, MAX_WND_TEXT);
   QString sClass(clName);
   if (!sClass.contains(psClass))
   {
      return;
   }

   //область кнопок
   QRect checkRect;
   QRect foldRect;
   bool hasCheck = false;
   bool hasFold  = false;
   bool hasCall  = false;

   int btnHeight = 110;
   int btnWidth = 0;
   WId BtnWnd = FindWindowEx(FgWnd, NULL, L"TAniLayer", NULL); 
   if (BtnWnd)
   {
      RECT btnRect;
      //GetClientRect(BtnWnd, &btnRect);
      GetWindowRect(BtnWnd, &btnRect);
      btnHeight = btnRect.bottom - btnRect.top;
      btnWidth = btnRect.right - btnRect.left;
      btnWidth = btnWidth >> 1;
      HwndToTop(FgWnd);

      //делаем скрин области кнопок
      QPixmap pixBtn = QPixmap::grabWindow(BtnWnd, btnWidth, 0, btnWidth, btnHeight);
      QImage imgBtn  = pixBtn.toImage();
      //imgBtn.save("btn.bmp");
      
      QPoint ptFold, ptCall, ptCheck;
      //здесь нужна обработка нашего хода
      static const int rectMin = 10;
      //Начинаем поиск с кнопки Чек
      //если она есть то однозначно наш ход
      hasCheck = Proc770::checkHueButton(imgBtn, minCheckHue, maxCheckHue, 
         rectMin, checkRect);
      if (!hasCheck)
      {
         //ищем кнопку Fold и Call
         hasFold = Proc770::checkHueButton(imgBtn, minFoldHue, maxFoldHue, 
            rectMin, foldRect);
         hasCall = Proc770::checkHueButton(imgBtn, minCallHue, maxCallHue, rectMin);

         if (hasFold && hasCall)
         {
            //qDebug() << "FOLD is avail";
         }
         else
         {
            return;
         }
      }
      else
      {
         //qDebug() << "CHECK is avail";
      }
   }

   //здесь наш ход
   QPixmap pixRoom = QPixmap::grabWindow(FgWnd);
   QRect rectRoom = pixRoom.rect();
   rectRoom.setHeight(rectRoom.height() - btnHeight);
   QImage imgRoom = pixRoom.copy(rectRoom).toImage();
   
   // устанавливаем изображение для обработки
   cardProc_->setImage(imgRoom);
   // если стадия префлопа 
   if (cardProc_->isPreflop())
   {
      //qDebug() << "Preflop!";
      // получить карманные карты
      bool ok = false;
      QPair<QRect, QRect> holeCards = cardProc_->getHoleCards(&ok);
      if (!ok)
         return;

      /// Debugging {
      //uint num = 0;
      //num = QDateTime::currentDateTime().toTime_t();
      //imgRoom.save(QString("test/table_%1.bmp").arg(num));
      //imgBtn.save(QString("test/btns_%1.bmp").arg(num));
      //imgRoom.copy(holeCards.first).save(QString("test/first_%1.bmp").arg(num));
      //imgRoom.copy(holeCards.second).save(QString("test/second_%1.bmp").arg(num));
      /// } Debugging

      if (holeCards.first.isEmpty() || holeCards.second.isEmpty() ||
          holeCards.first.isNull() || holeCards.second.isNull())
          return;

      QImage firstImg  = imgRoom.copy(holeCards.first);
      QImage secondImg = imgRoom.copy(holeCards.second);

      QString card1 = cardFromImage(firstImg);
      QString card2 = cardFromImage(secondImg);

      if (card1.length() != 2 || card2.length() != 2)
         return;

      //qDebug() << card1 << card2;
      
      //сохранить карты в кэш
      QString joined = card1 + card2;
      if (joined == cache_ && !lastIsFold_)
      {
         //хорошие карты - человек думает, не мешать
         return;
      } 
      else
      {
         cache_ = joined;
      }
      
      QString range = cardRangeFromHoles(card1, card2);
      //qDebug() << range;
      if (playingCard_.contains(range))
      {
         //panic!
         lastIsFold_ = false;
         if (data_.visualAlert)
         {
            alarm_->highlight(joined, FgWnd);
         }
         if (data_.turnBeep)
         {
            QString appExe = qApp->applicationDirPath();
            QSound::play(appExe + "/sounds/turn.wav");
         }
      }
      else
      {
         if (data_.advisorMode)
         {
            QString advice = tr("Fold/Check this hand: %1")
               .arg(card1 + " " + card2);
            cbFun(advice.toStdString().c_str());
            return;
         }
         
         //foldOrCheck(FgWnd);
         //qDebug() << "Check Rect" << checkRect;
         int w = checkRect.width();
         int h = checkRect.height();
         checkRect.setX(btnWidth + checkRect.x());
         checkRect.setY(imgRoom.height() + checkRect.y());
         checkRect.setWidth(w);
         checkRect.setHeight(h);
         //qDebug() << "New Check Rect" << checkRect;

         //qDebug() << "Fold Rect" << foldRect;
         w = foldRect.width();
         h = foldRect.height();
         foldRect.setX(btnWidth + foldRect.x());
         foldRect.setY(imgRoom.height() + foldRect.y());
         foldRect.setWidth(w);
         foldRect.setHeight(h);
         //qDebug() << "New Fold Rect" << foldRect;
         if (hasCheck)
         {
            if (data_.checkBeep)
            {
               QString appExe = qApp->applicationDirPath();
               QSound::play(appExe + "/sounds/check.wav");
            }
            
            clickTo(FgWnd, checkRect);
            
            if (data_.showFolded)
            {
               QString sAction = tr("This hand has been checked: ");
               cbFun(QString(sAction + card1 + " " + card2).toStdString().c_str());
            }

            //обнулить кэш
            cache_.clear();
            lastIsFold_ = false;
         }
         else if (hasFold)
         {
            lastIsFold_ = true;
            if (data_.foldBeep)
            {
               QString appExe = qApp->applicationDirPath();
               QSound::play(appExe + "/sounds/fold.wav");
            }

            clickTo(FgWnd, foldRect);
            
            if (data_.showFolded)
            {
               QString sAction = tr("This hand has been folded: ");
               cbFun(QString(sAction + card1 + " " + card2).toStdString().c_str());
            }
         }
      }
   }
//код для набивки базы карт
/*
   qDebug() << "Check Rect" << checkRect;
   int w = checkRect.width();
   int h = checkRect.height();
   checkRect.setX(btnWidth + checkRect.x());
   checkRect.setY(imgRoom.height() + checkRect.y());
   checkRect.setWidth(w);
   checkRect.setHeight(h);
   qDebug() << "New Check Rect" << checkRect;

   qDebug() << "Fold Rect" << foldRect;
   w = foldRect.width();
   h = foldRect.height();
   foldRect.setX(btnWidth + foldRect.x());
   foldRect.setY(imgRoom.height() + foldRect.y());
   foldRect.setWidth(w);
   foldRect.setHeight(h);
   qDebug() << "New Fold Rect" << foldRect;

   if (cardProc_->isPreflop())
   {
      if (hasCheck)
      {
         clickTo(FgWnd, checkRect);
      }
      else if (hasFold && hasCall)
      {
         clickTo(FgWnd, foldRect);
      }
   }
   else
   {
      clickTo(FgWnd, foldRect);
      clickTo(FgWnd, checkRect);

      qDebug() << "Flop at least!";
      return;
   }
*/
}