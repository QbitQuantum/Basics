/*
  Render alphablending for the time elapsed.

  Show the blended widget and free all allocated source
  if the blending is finished.
*/
void QAlphaWidget::render()
{
    int tempel = checkTime.elapsed();
    if (elapsed >= tempel)
        elapsed++;
    else
        elapsed = tempel;

    if (duration != 0)
        alpha = tempel / double(duration);
    else
        alpha = 1;

#if defined(Q_OS_WIN)
    if (alpha >= 1 || !showWidget) {
        anim.stop();
        qApp->removeEventFilter(this);
        widget->setWindowOpacity(1);
        q_blend = 0;
        deleteLater();
    } else {
        widget->setWindowOpacity(alpha);
    }
#else
    if (alpha >= 1 || !showWidget) {
        anim.stop();
        qApp->removeEventFilter(this);

        if (widget) {
            if (!showWidget) {
#ifdef Q_WS_WIN
                setEnabled(true);
                setFocus();
#endif // Q_WS_WIN
                widget->hide();
            } else {
                //Since we are faking the visibility of the widget 
                //we need to unset the hidden state on it before calling show
                widget->setAttribute(Qt::WA_WState_Hidden, true);
                widget->show();
                lower();
            }
        }
        q_blend = 0;
        deleteLater();
    } else {
        alphaBlend();
        pm = QPixmap::fromImage(mixedImage);
        repaint();
    }
#endif // defined(Q_OS_WIN)
}