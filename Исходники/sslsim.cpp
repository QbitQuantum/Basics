 Field(const FieldGeometry *f)
     : ground_ci{{0, 0, 1}, 0.0}, ceil_ci{{0, 0, -1}, -10.0},
       left_wall_ci{{1, 0, 0}, -field_limit_x(f)},
       right_wall_ci{{-1, 0, 0}, -field_limit_x(f)},
       top_wall_ci{{0, 1, 0}, -field_limit_y(f)},
       bottom_wall_ci{{0, -1, 0}, -field_limit_y(f)},
       goal_ci{f->goal_width, f->goal_depth, f->goal_height,
               f->goal_wall_width},
       ground_body{ground_ci}, ceil_body{ceil_ci},
       left_wall_body{left_wall_ci}, right_wall_body{right_wall_ci},
       top_wall_body{top_wall_ci}, bottom_wall_body{bottom_wall_ci},
       left_goal_body{goal_ci}, right_goal_body{goal_ci} {
   auto trans1 = btTransform({0, 0, 0, 1}, {-f->field_length / 2, 0, 0});
   left_goal_body.setWorldTransform(trans1);
   auto trans2 = btTransform({0, 0, 1, 0}, {f->field_length / 2, 0, 0});
   right_goal_body.setWorldTransform(trans2);
 }