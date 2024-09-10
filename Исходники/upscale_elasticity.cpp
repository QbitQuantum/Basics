int run(Params& p)
{
  try {
    static const int dim = 3;

    Opm::time::StopWatch watch;
    watch.start();

    GridType grid;
    if (p.file == "uniform") {
      std::array<int,3> cells;
      cells[0] = p.cellsx;
      cells[1] = p.cellsy;
      cells[2] = p.cellsz;
      std::array<double,3> cellsize;
      cellsize[0] = p.max[0] > -1?p.max[0]/cells[0]:1.0;
      cellsize[1] = p.max[1] > -1?p.max[1]/cells[1]:1.0;
      cellsize[2] = p.max[2] > -1?p.max[2]/cells[2]:1.0;
      grid.createCartesian(cells,cellsize);
    } else {
        Opm::ParseContext parseContext;
        Opm::ParserPtr parser(new Opm::Parser());
        Opm::DeckConstPtr deck(parser->parseFile(p.file , parseContext));
        Opm::EclipseGrid inputGrid(deck);
        grid.processEclipseFormat(inputGrid, false);
    }
    ElasticityUpscale<GridType, AMG> upscale(grid, p.ctol, p.Emin, p.file,
                                             p.rocklist, p.verbose);

    if (p.max[0] < 0 || p.min[0] < 0) {
      std::cout << "determine side coordinates..." << std::endl;
      upscale.findBoundaries(p.min,p.max);
      std::cout << "  min " << p.min[0] << " " << p.min[1] << " " << p.min[2] << std::endl;
      std::cout << "  max " << p.max[0] << " " << p.max[1] << " " << p.max[2] << std::endl;
    }
    if (p.n1 == -1 || p.n2 == -1) {
      p.n1 = grid.logicalCartesianSize()[0];
      p.n2 = grid.logicalCartesianSize()[1];
    }
    if (p.linsolver.zcells == -1) {
      double lz = p.max[2]-p.min[2];
      int nz = grid.logicalCartesianSize()[2];
      double hz = lz/nz;
      double lp = sqrt((double)(p.max[0]-p.min[0])*(p.max[1]-p.min[1]));
      int np = std::max(grid.logicalCartesianSize()[0],
                        grid.logicalCartesianSize()[1]);
      double hp = lp/np;
      p.linsolver.zcells = (int)(2*hp/hz+0.5);
    }
    std::cout << "logical dimension: " << grid.logicalCartesianSize()[0]
              << "x"                   << grid.logicalCartesianSize()[1]
              << "x"                   << grid.logicalCartesianSize()[2]
              << std::endl;

    if (p.inspect == "mesh")
      return 0;

    if (p.linsolver.pre == UNDETERMINED) {
      double hx = (p.max[0]-p.min[0])/grid.logicalCartesianSize()[0];
      double hy = (p.max[1]-p.min[1])/grid.logicalCartesianSize()[1];
      double hz = (p.max[2]-p.min[2])/grid.logicalCartesianSize()[2];
      double aspect = sqrt(hx*hy)/hz;
      std::cout << "Estimated cell aspect ratio: " << aspect;
      if (aspect > 80) {
        p.linsolver.pre = TWOLEVEL;
        std::cout << " => Using two level preconditioner" << std::endl;
      } else {
        p.linsolver.pre = Opm::Elasticity::AMG;
        std::cout << " => Using AMG preconditioner" << std::endl;
      }
    }

    if (p.method == UPSCALE_MPC) {
      std::cout << "using MPC couplings in all directions..." << std::endl;
      upscale.periodicBCs(p.min, p.max);
      std::cout << "preprocessing grid..." << std::endl;
      upscale.A.initForAssembly();
    } else if (p.method == UPSCALE_MORTAR) {
      std::cout << "using Mortar couplings.." << std::endl;
      upscale.periodicBCsMortar(p.min, p.max, p.n1, p.n2,
                                p.lambda[0], p.lambda[1]);
    } else if (p.method == UPSCALE_NONE) {
      std::cout << "no periodicity approach applied.." << std::endl;
      upscale.fixCorners(p.min, p.max);
      upscale.A.initForAssembly();
    }

    Dune::FieldMatrix<double,6,6> C;
    Opm::Elasticity::Vector field[6];
    std::cout << "assembling elasticity operator..." << "\n";
    upscale.assemble(-1,true);
    std::cout << "setting up linear solver..." << std::endl;
    upscale.setupSolvers(p.linsolver);

    if (p.inspect == "load")
      Dune::storeMatrixMarket(upscale.A.getOperator(), "A.mtx");

    // the uzawa solver cannot run multithreaded
#ifdef HAVE_OPENMP
    if (p.linsolver.uzawa) {
      std::cout << "WARNING: disabling multi-threaded solves due to uzawa" << std::endl;
      omp_set_num_threads(1);
    }
#endif

#pragma omp parallel for schedule(static)
    for (int i=0;i<6;++i) {
      std::cout << "processing case " << i+1 << "..." << std::endl;
      if (p.inspect == "results") {
        char temp[1024];
        sprintf(temp, p.resultfilename.c_str(), "x", i+1);
        Dune::loadMatrixMarket(upscale.u[i], temp);
      } else {
        std::cout << "\tassembling load vector..." << std::endl;
        upscale.assemble(i,false);
        if (p.inspect == "load") {
          char temp[1024];
          sprintf(temp, p.resultfilename.c_str(), "b", i+1);
          Dune::storeMatrixMarket(upscale.b[i], temp);
        }
        std::cout << "\tsolving..." << std::endl;
        upscale.solve(i);
        if (p.inspect == "load") {
          char temp[1024];
          sprintf(temp, p.resultfilename.c_str(), "x", i+1);
          Dune::storeMatrixMarket(upscale.u[i], temp);
        }
      }
      upscale.A.expandSolution(field[i],upscale.u[i]);
#define CLAMP(x) (fabs(x)<1.e-4?0.0:x)
      for (size_t j=0;j<field[i].size();++j) {
        double val = field[i][j];
        field[i][j] = CLAMP(val);
      }
      Dune::FieldVector<double,6> v;
      upscale.averageStress(v,upscale.u[i],i);
      for (int j=0;j<6;++j)
        C[i][j] = CLAMP(v[j]);
    }

    if (!p.vtufile.empty()) {
      Dune::VTKWriter<typename GridType::LeafGridView> vtkwriter(grid.leafGridView());

      for (int i=0;i<6;++i) {
        std::stringstream str;
        str << "sol " << i+1;
        vtkwriter.addVertexData(field[i], str.str().c_str(), dim);
      }
      vtkwriter.write(p.vtufile);
    }

    Dune::FieldVector<double,3> speeds;
    if (upscale.upscaledRho > -1) {
      speeds = Opm::Elasticity::waveSpeeds(C, p.dip, p.azimuth, 1.0);
      std::cout << "Wave speeds: " << speeds << std::endl;
    }

    // voigt notation
    for (int j=0;j<6;++j)
      std::swap(C[3][j],C[5][j]);
    for (int j=0;j<6;++j)
      std::swap(C[j][3],C[j][5]);
    std::cout << "---------" << std::endl;
    std::cout << C << std::endl;
    if (!p.output.empty())
      writeOutput(p, watch, grid.size(0), upscale.volumeFractions,
                  upscale.bySat, C, upscale.upscaledRho, speeds);

    return 0;
  }
  catch (Dune::Exception &e) {
    throw e;
  }
  catch (...) {
    throw;
  }
  return 1;
}