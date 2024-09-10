void WatchFieldGraphics::drawBounds()
{
    double FIELD_MAIN_LENGHT = 7400;
    double FIELD_MAIN_WIDTH = 5400;
    scene.setSceneRect(-FIELD_MAIN_LENGHT/2, -FIELD_MAIN_WIDTH/2, FIELD_MAIN_LENGHT, FIELD_MAIN_WIDTH);
//    scene.setSceneRect(-FIELD_MAIN_LENGHT/2, -FIELD_MAIN_WIDTH/2, FIELD_MAIN_LENGHT, FIELD_MAIN_WIDTH);

    scene.addRect(-FIELD_MAIN_LENGHT/2, -FIELD_MAIN_WIDTH/2,
                  FIELD_MAIN_LENGHT, FIELD_MAIN_WIDTH,QPen(Qt::green),QBrush(Qt::green));

    QPen drawBoundsPen(Qt::white);
    scene.addLine(-FIELD_LENGTH/2, -FIELD_WIDTH/2, -FIELD_LENGTH/2, FIELD_WIDTH/2, drawBoundsPen);
    scene.addLine(FIELD_LENGTH/2, -FIELD_WIDTH/2, FIELD_LENGTH/2, FIELD_WIDTH/2, drawBoundsPen);
    scene.addLine(-FIELD_LENGTH/2, -FIELD_WIDTH/2, FIELD_LENGTH/2, -FIELD_WIDTH/2, drawBoundsPen);
    scene.addLine(-FIELD_LENGTH/2, FIELD_WIDTH/2, FIELD_LENGTH/2, FIELD_WIDTH/2, drawBoundsPen);

    // half-field line
    scene.addLine(0, -FIELD_WIDTH/2, 0, FIELD_WIDTH/2, drawBoundsPen);
    scene.addEllipse(-FIELD_CENTER_RADIUS, -FIELD_CENTER_RADIUS, FIELD_CENTER_RADIUS*2, FIELD_CENTER_RADIUS*2, drawBoundsPen);

    QPainterPath leftPenaltyArea;
    leftPenaltyArea.moveTo(-FIELD_LENGTH/2, -FIELD_PENALTY_AREA_RADIUS - FIELD_PENALTY_AREA_WIDTH/2);
    leftPenaltyArea.arcTo(-FIELD_LENGTH/2 - FIELD_PENALTY_AREA_RADIUS, -FIELD_PENALTY_AREA_WIDTH/2-FIELD_PENALTY_AREA_RADIUS,
                       2*FIELD_PENALTY_AREA_RADIUS,2*FIELD_PENALTY_AREA_RADIUS,90,-90);
    leftPenaltyArea.arcTo(-FIELD_LENGTH/2-FIELD_PENALTY_AREA_RADIUS,FIELD_PENALTY_AREA_WIDTH/2-FIELD_PENALTY_AREA_RADIUS,
                       2*FIELD_PENALTY_AREA_RADIUS,2*FIELD_PENALTY_AREA_RADIUS,0,-90);
    scene.addPath(leftPenaltyArea, drawBoundsPen);

    QPainterPath Goal1;
    Goal1.moveTo(-FIELD_LENGTH/2,-FIELD_GOAL_WIDTH/2);
    Goal1.lineTo(-FIELD_LENGTH/2-180,-FIELD_GOAL_WIDTH/2);
    Goal1.lineTo(-FIELD_LENGTH/2-180,FIELD_GOAL_WIDTH/2);
    Goal1.lineTo(-FIELD_LENGTH/2,FIELD_GOAL_WIDTH/2);
    scene.addPath(Goal1,QPen(QColor(Qt::black),20));

    QPainterPath rightPenaltyArea;
    rightPenaltyArea.moveTo(FIELD_LENGTH/2, -FIELD_PENALTY_AREA_RADIUS - FIELD_PENALTY_AREA_WIDTH/2);
    rightPenaltyArea.arcTo(FIELD_LENGTH/2 - FIELD_PENALTY_AREA_RADIUS, -FIELD_PENALTY_AREA_WIDTH/2-FIELD_PENALTY_AREA_RADIUS,
                       2*FIELD_PENALTY_AREA_RADIUS,2*FIELD_PENALTY_AREA_RADIUS,90,90);
    rightPenaltyArea.arcTo(FIELD_LENGTH/2-FIELD_PENALTY_AREA_RADIUS,FIELD_PENALTY_AREA_WIDTH/2-FIELD_PENALTY_AREA_RADIUS,
                       2*FIELD_PENALTY_AREA_RADIUS,2*FIELD_PENALTY_AREA_RADIUS,180,90);
    scene.addPath(rightPenaltyArea, drawBoundsPen);

    QPainterPath Goal2;
    Goal2.moveTo(FIELD_LENGTH/2,-FIELD_GOAL_WIDTH/2);
    Goal2.lineTo(FIELD_LENGTH/2+180,-FIELD_GOAL_WIDTH/2);
    Goal2.lineTo(FIELD_LENGTH/2+180,FIELD_GOAL_WIDTH/2);
    Goal2.lineTo(FIELD_LENGTH/2,FIELD_GOAL_WIDTH/2);
    scene.addPath(Goal2,QPen(QColor(Qt::black),20));
}