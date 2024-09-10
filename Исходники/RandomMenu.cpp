void RandomMenu::displayY(int nb)
{
   std::stringstream ss;
  AObject* letter;
  int i = 0;
  int x = -30, y = -15;

  std::string s = std::to_string(nb);
  char const *nbStr = s.c_str();
  _yMap.clear();
  while (nbStr[i])
    {
      ss.str("");
      ss.clear();
      ss << "./images/fonts/";
      ss << nbStr[i];
      ss << ".tga";
      std::cout << "ss : " << ss.str() << std::endl;
      letter = new Letters();
      letter->initialize(ss.str());
      letter->translate(glm::vec3(-0.06 * (i + 1) + x * 0.01,
				   0 + y * 0.01, 0));
      _yMap.push_back(letter);
      i++;
    }
}