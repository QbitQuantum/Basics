GLBox::GLBox( QWidget* parent, const QGLWidget* shareWidget )
    : QGLWidget( parent,  shareWidget )
{
    scale = 100;
    m_texID = 0;
    m_winWidth = 700;
    m_winHeight = 700;
    m_Ygravity = 1.0;
    m_Xgravity = 0.2;
    double m_focus = 0; //Brennweite, distance Viewer to Bildfläche

    // Initialize the texture buffer.
    m_buffer = new unsigned char[3*TEX_RES];

    // Set new Clock
    m_clock = Clock(Vec3d(-1.0,1.0,1.0),100);

    // Set the timeout to 50 milliseconds, corresponding to 20 FPS.
    m_timeout = 50; // 50 msecs
    m_timer = new QTimer(this);
    // Connect the timeout signal of the timer to the animate slot.
    connect(m_timer, SIGNAL(timeout()), this, SLOT(animate()));
    // Start the timer.
    m_timer->start(m_timeout);
    m_elapsed = 0;

}