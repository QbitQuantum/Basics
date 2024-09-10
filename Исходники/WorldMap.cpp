void
Worldmap::on_primary_button_press(int x, int y)
{
  Vector2f click_pos = gc_state.screen2world(Vector2i(x, y));

  if (globals::developer_mode)
  {
    FileWriter writer(std::cout);
    writer.begin_mapping("leveldot");
    writer.write_string("levelname", "");
    writer.begin_mapping("dot");
    writer.write_string("name", "leveldot_X");
    writer.write_vector("position", click_pos);
    writer.end_mapping();
    writer.end_mapping();
    std::cout << std::endl;
    std::cout << std::endl;
  }

  Dot* dot = path_graph->get_dot(click_pos.x, click_pos.y);
  if (dot)
  {
    if (globals::developer_mode)
      log_info("Worldmap: Clicked on: %1%", dot->get_name());

    if (path_graph->lookup_node(dot->get_name()) == pingus->get_node())
    {
      if (globals::developer_mode)
        log_info("Worldmap: Pingu is on node, issue on_click()");
      dot->on_click();
    }
    else
    {
      if (dot->accessible())
      {
        if (!pingus->walk_to_node(path_graph->lookup_node(dot->get_name())))
        {
          if (globals::developer_mode)
            log_info("Worldmap: NO PATH TO NODE FOUND!");
        }
        else
        {
          StatManager::instance()->set_string(worldmap.get_short_name() + "-current-node", dot->get_name());
        }
      }
      else
      {
        Sound::PingusSound::play_sound("chink");
      }
    }
  }
}