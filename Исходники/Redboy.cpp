// fire charge
void Redboy::skill1() {
  Random rd;
  if(rd.rand() % 2 == 0)
    play_sound("dark_laugh");
  int total_p_num = Model_state::get_instance()->get_player_list_ptr()->size();
  int player_num = randomer.rand_lt(total_p_num);
  if (total_p_num > 1) {
      while (players[player_num] == target) {
        player_num = randomer.rand_lt(total_p_num);
      }
  }
  
  fire_charge_tar_loc = players[player_num]->get_location();
  set_orientation(fire_charge_tar_loc - get_location());
  set_speed((fire_charge_tar_loc - get_location()).magnitude() / 0.8f);
  fire_charge_render_list.clear();
  fire_charge_last_shadow_time = 0.0f;
  fire_charge_main_body_stop = false;
  fire_charge_speed = get_current_speed();
  fire_charge_ori = get_current_orientation();
  fire_charge_start_loc = get_location();
}