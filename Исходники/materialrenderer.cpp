  void MaterialRenderer::renderFrame(const Ref<Camera>& camera, const Ref<BackendScene>& scene,  Ref<Film>& film)
  {
    /*! flush to zero and no denormals */
    _mm_setcsr(_mm_getcsr() | /*FTZ:*/ (1<<15) | /*DAZ:*/ (1<<6));

    /*! precompute some values */
    numTilesX = ((int)film->width +TILE_SIZE_X-1)/TILE_SIZE_X;
    numTilesY = ((int)film->height+TILE_SIZE_Y-1)/TILE_SIZE_Y;
    numTiles = numTilesX * numTilesY;
    rcpWidth  = 1.0f/float(film->width);
    rcpHeight = 1.0f/float(film->height);

    /*! render frame */
    double t = getSeconds();
    this->tileID = 0;
    this->atomicNumRays = 0;
    this->camera = camera;
    this->scene = scene;
    this->film = film;
    scheduler->addTask((Task::runFunction)&run_renderThread,this,scheduler->getNumThreads());
    scheduler->go();
    this->camera = null;
    this->scene = null;
    this->film = null;
    double dt = getSeconds()-t;

    /*! print framerate */
    std::cout << "MATERIAL RENDERED : " << 1.0f/dt << " fps, " << dt*1000.0f << " ms, " << atomicNumRays/dt*1E-6 << " Mrps" << std::endl;
  }