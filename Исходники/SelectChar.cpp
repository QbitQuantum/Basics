void SelectChar::loadButtons()
{
  AObject *b = new DisplayButton();

  b = new DisplayButton();
  b->initialize(_texManag.getTexture("1ia"));
  b->translate(glm::vec3(0, -0.39, 0));
  _buttons["1ia"] = b;

  b = new DisplayButton();
  b->initialize(_texManag.getTexture("5ia"));
  b->translate(glm::vec3(0, -0.39, 0));
  _buttons["5ia"] = b;

  b = new DisplayButton();
  b->initialize(_texManag.getTexture("10ia"));
  b->translate(glm::vec3(0, -0.39, 0));
  _buttons["10ia"] = b;

  b = new DisplayButton();
  b->initialize(_texManag.getTexture("15ia"));
  b->translate(glm::vec3(0, -0.39, 0));
  _buttons["15ia"] = b;

  b = new DisplayButton();
  b->initialize(_texManag.getTexture("20ia"));
  b->translate(glm::vec3(0, -0.39, 0));
  _buttons["20ia"] = b;

  b = new DisplayButton();
  b->initialize(_texManag.getTexture("1P"));
  b->translate(glm::vec3(0.4, -0.39, 0));
  _buttons["1P"] = b;

  b = new DisplayButton();
  b->initialize(_texManag.getTexture("2P"));
  b->translate(glm::vec3(0.4, -0.39, 0));
  _buttons["2P"] = b;

  b = new DisplayButton();
  b->initialize(_texManag.getTexture("Map1"));
  b->translate(glm::vec3(-0.42, -0.39, 0));
  _buttons["Map1"] = b;

  b = new DisplayButton();
  b->initialize(_texManag.getTexture("Map2"));
  b->translate(glm::vec3(-0.42, -0.39, 0));
  _buttons["Map2"] = b;

  b = new DisplayButton();
  b->initialize(_texManag.getTexture("Map3"));
  b->translate(glm::vec3(-0.42, -0.39, 0));
  _buttons["Map3"] = b;

  b = new DisplayButton();
  b->initialize(_texManag.getTexture("Map4"));
  b->translate(glm::vec3(-0.42, -0.39, 0));
  _buttons["Map4"] = b;

  b = new DisplayButton();
  b->initialize(_texManag.getTexture("Map5"));
  b->translate(glm::vec3(-0.42, -0.39, 0));
  _buttons["Map5"] = b;

  b = new DisplayButton();
  b->initialize(_texManag.getTexture("Map6"));
  b->translate(glm::vec3(-0.42, -0.39, 0));
  _buttons["Map6"] = b;
}