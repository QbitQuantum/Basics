 virtual bool show(Qt::WindowFlags f, Qt::WindowModality m, QWindow *parent) {
     m_dialog.winId();
     QWindow *window = m_dialog.windowHandle();
     Q_ASSERT(window);
     window->setTransientParent(parent);
     window->setFlags(f);
     m_dialog.setWindowModality(m);
     m_dialog.show();
     return m_dialog.isVisible();
 }