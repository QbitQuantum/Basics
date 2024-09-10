int main()
{
  // Disable deprecation warning for getenv call.
#ifdef CHAISCRIPT_MSVC
#ifdef max // Why Microsoft? why?
#undef max
#endif
#pragma warning(push)
#pragma warning(disable : 4996)
#endif

  const char *usepath = getenv("CHAI_USE_PATH");
  const char *modulepath = getenv("CHAI_MODULE_PATH");

#ifdef CHAISCRIPT_MSVC
#pragma warning(pop)
#endif

  std::vector<std::string> usepaths;
  usepaths.push_back("");
  if (usepath)
  {
    usepaths.push_back(usepath);
  }

  std::vector<std::string> modulepaths;
  modulepaths.push_back("");
  if (modulepath)
  {
    modulepaths.push_back(modulepath);
  }

  chaiscript::ChaiScript chai(modulepaths,usepaths);

  std::vector<std::shared_ptr<std::thread> > threads;

  // Ensure at least two, but say only 7 on an 8 core processor
  int num_threads = std::max(std::thread::hardware_concurrency() - 1, 2u);

  for (int i = 0; i < num_threads; ++i)
  {
    threads.push_back(std::shared_ptr<std::thread>(new std::thread(do_work, std::ref(chai), i)));
  }

  for (int i = 0; i < num_threads; ++i)
  {
    threads[i]->join();
  }



  for (int i = 0; i < num_threads; ++i)
  {
    std::stringstream ss;
    ss << i;
    if (chai.eval<int>("getvalue(" + ss.str() + ")") != expected_value(4000))
    {
      return EXIT_FAILURE;
    }

    if (chai.eval<int>("getid(" + ss.str() + ")") != i)
    {
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}