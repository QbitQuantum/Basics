void MiniMapInterface::annotateObjectives( Surface &map_surface )
{
    iRect world_rect, map_rect;
    unsigned char objective_disposition;
    PIX color;

    ObjectiveInterface::startObjectivePositionEnumeration();

    while( ObjectiveInterface::objectivePositionEnumeration( &world_rect, &objective_disposition, 0 ) ) {
        switch( objective_disposition ) {
        case _objective_disposition_unoccupied :
            color = Color::white;
            break;

        case _objective_disposition_player :
            color = player_objective_color;
            break;

        case _objective_disposition_allie :
            color = allie_objective_color;
            break;

        case _objective_disposition_enemy :
            color = enemy_objective_color;
            break;
        } // ** switch

        map_rect.min.x = int(float(world_rect.min.x) / scale_factor.x);
        map_rect.min.y = int(float(world_rect.min.y) / scale_factor.y);
        map_rect.max.x = int(float(world_rect.max.x) / scale_factor.x);
        map_rect.max.y = int(float(world_rect.max.y) / scale_factor.y);

        // Removed black borders to the text.
        if (GameConfig::getMiniMapObjectiveDrawMode() == _mini_map_objective_draw_mode_solid_rect) {
            map_surface.fillRect( map_rect, color);
        } else if (GameConfig::getMiniMapObjectiveDrawMode() == _mini_map_objective_draw_mode_outline_rect) {
            map_surface.drawRect( map_rect, color);
            map_surface.drawRect( iRect(map_rect.min.x + 1, map_rect.min.y + 1, map_rect.max.x - 1, map_rect.max.y - 1), color );
            //}
            //else if (GameConfig::getMiniMapObjectiveDrawMode() == _mini_map_objective_draw_mode_player_flag)
            //{
            //map_surface.fillRect( map_rect, color );
        } else {
            assert(false);
        }
    } // ** while
}