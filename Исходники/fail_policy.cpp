void fail_policy::operator()(const nyan::fail &fail_arg) const
{
#if NYAN_CAN_HAS_YAML
   YAML::Emitter y;
   y << fail_arg;
   if (y.good())
   {
      std::cerr << "# unexpected fail is unexpected; the yaml speaks:\n";
      std::cerr << y.c_str();
   }
   else
   {
      std::cerr << "# unexpected fail is unexpected. std::fail::what() says, \""
            << fail_arg.what() << ".\"\n";
      std::cerr
         << "# unfortunately, i failed to provide details; the yaml emitter says, \""
         << y.GetLastError() << "\"\n";
   }
#else
   std::cerr << "# unexpected fail is unexpected. std::fail::what() says, \""
         << fail_arg.what()
         << ".\"\n# if you'd like more details, please consider compiling libnyan with yaml support enabled.\n";
#endif
}