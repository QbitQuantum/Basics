/*!
    Show the snap line. fade-in animation is started on the line if the line is positioned at a different place.
    Before starting the fade-in animation, the fade-out animation is stoped if it is running.
*/
void HsSnapLine::showLine(const QLineF &snapLine)
{
    QLineF displayLine = snapLine;
    qreal angle = displayLine.angle();
    if (qAbs(angle) == 0.0 || qAbs(angle) == 180.0) { //this is a horizontal line
        //adding 1 is required below, as the line is 3 pixels wide and is translated by 1 point before displaying
        if (displayLine.y1() != (line().y1()+1.0) ) { //this horizontal line is at new position horizontally
            if (isFadeOutAnimationRunning()) { //if fade-out animation is running, stop it, animation is running at old position
                stopFadeOutAnimation();
            }
            //start fade-in animation at new position.
            startFadeInAnimation();
        }
        else { //this horizontal line is at the old position horizontally
            if (isFadeOutAnimationRunning()) { //if fade-out animation is running, stop it, animation is running at old position
                stopFadeOutAnimation();
                //start fade-in animation at the old position
                startFadeInAnimation();
            }
        }
        displayLine.translate(0.0, -1.0);
    }
    if (qAbs(angle) == 90.0 || qAbs(angle) == 270.0) { //this is a vertical line
        if (displayLine.x1() != (line().x1()+1)) { //this Vertical line is at different position vertically
            if (isFadeOutAnimationRunning()) {
                stopFadeOutAnimation();
            }
            startFadeInAnimation();
        }
        else {
            if (isFadeOutAnimationRunning()) {
                stopFadeOutAnimation();
                startFadeInAnimation();
            }
        }
        displayLine.translate(-1.0, 0.0);
    }

    QLinearGradient gradient(displayLine.p1(), displayLine.p2());
    gradient.setColorAt(0.0, Qt::white);
    QColor snapLineColor = HbColorScheme::color("qtc_hs_snapguide");
    if (!snapLineColor.isValid()) {
        //if valid color is not loaded from the theme, the darkCyan color is used as a backup.color
        snapLineColor = Qt::darkCyan;
    }
    gradient.setColorAt(0.4, snapLineColor);
    gradient.setColorAt(0.6, snapLineColor);
    gradient.setColorAt(1.0, Qt::white);
    QBrush brush(gradient);
    QPen pen;
    pen.setWidth(3);
    pen.setCapStyle(Qt::RoundCap);
    pen.setBrush(brush);
    setPen(pen);

    setLine(displayLine);
    show();
}