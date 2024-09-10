int hpx_main()
{
    BMP SetImage;
    SetImage.SetBitDepth(24);
    SetImage.SetSize(sizeX * 2, sizeY);
    hpx::util::high_resolution_timer t;

    {
        using namespace std;

        using hpx::future;
        using hpx::async;
        using hpx::wait_all;

        int const max_iteration = 255;

        vector<future<int> > iteration;
        iteration.reserve(sizeX*sizeY);

        hpx::cout << "Initial setup completed in "
                  << t.elapsed()
                  << "s. Initializing and running futures...\n"
                  << hpx::flush;
        t.restart();

        {
            hpx::threads::executors::local_queue_executor exec;

            for (int i = 0; i < sizeX; ++i)
            {
                for (int j = 0; j < sizeY; ++j)
                {
                    float x0 = (float)i * 3.5f / (float)sizeX - 2.5f;
                    float y0 = (float)j * 2.0f / (float)sizeY - 1.0f;

                    iteration.push_back(async(exec, &fractal_pixel_value,
                        x0, y0, max_iteration));
                }
            }

            // the executor's destructor will wait for all spawned tasks to
            // finish executing
        }

        hpx::cout << sizeX*sizeY << " calculations run in "
                  << t.elapsed()
                  << "s. Transferring from futures to general memory...\n"
                  << hpx::flush;
        t.restart();

        for (int i = 0; i < sizeX; ++i)
        {
            for (int j = 0; j < sizeY; ++j)
            {
                int it = iteration[i*sizeX + j].get();
                for (int k = 0; k < 2; ++k)
                {
                    int p = (it * 255) / max_iteration;
                    SetImage.SetPixel(i * 2 + k, j, RGBApixel(p, p, p));
                }
            }
        }
    }

    hpx::cout << "Transfer process completed in "
              << t.elapsed() << "s. Writing to hard disk...\n"
              << hpx::flush;
    t.restart();

    SetImage.WriteToFile("out.bmp");

    hpx::cout << "Fractal image written to file \"out.bmp\" from memory in "
              << t.elapsed() << "s.\nShutting down process.\n"
              << hpx::flush;

    return hpx::finalize(); // Handles HPX shutdown
}