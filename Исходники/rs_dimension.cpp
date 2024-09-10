/**
 * Creates a dimensioning line (line with one, two or no arrows and a text).
 *
 * @param forceAutoText Automatically reposition the text label.
 */
void RS_Dimension::updateCreateDimensionLine(const RS_Vector& p1,
        const RS_Vector& p2, bool arrow1, bool arrow2, bool forceAutoText) {

    // general scale (DIMSCALE)
    double dimscale = getGeneralScale();
    // text height (DIMTXT)
    double dimtxt = getTextHeight()*dimscale;
    // text distance to line (DIMGAP)
    double dimgap = getDimensionLineGap()*dimscale;

    // length of dimension line:
    double distance = p1.distanceTo(p2);
    // arrow size:
    double arrowSize = getArrowSize()*dimscale;

    // do we have to put the arrows outside of the line?
    bool outsideArrows = (distance<arrowSize*2.5);

    // arrow angles:
    double arrowAngle1, arrowAngle2;

    RS_Pen pen(getDimensionLineColor(),
           getDimensionLineWidth(),
           RS2::LineByBlock);

    // Create dimension line:
	RS_Line* dimensionLine = new RS_Line{this, p1, p2};
    dimensionLine->setPen(pen);
//    dimensionLine->setPen(RS_Pen(RS2::FlagInvalid));
	dimensionLine->setLayer(nullptr);
    addEntity(dimensionLine);

    if (outsideArrows==false) {
        arrowAngle1 = dimensionLine->getAngle2();
        arrowAngle2 = dimensionLine->getAngle1();
    } else {
        arrowAngle1 = dimensionLine->getAngle1();
        arrowAngle2 = dimensionLine->getAngle2();

        // extend dimension line outside arrows
		RS_Vector dir = RS_Vector::polar(arrowSize*2, arrowAngle2);
        dimensionLine->setStartpoint(p1 + dir);
        dimensionLine->setEndpoint(p2 - dir);
    }
double dimtsz=getTickSize()*dimscale;
if(dimtsz < 0.01) {
    //display arrow
    // Arrows:
    RS_SolidData sd;
    RS_Solid* arrow;

    if (arrow1) {
        // arrow 1
        arrow = new RS_Solid(this, sd);
        arrow->shapeArrow(p1,
                          arrowAngle1,
                          arrowSize);
//        arrow->setPen(RS_Pen(RS2::FlagInvalid));
        arrow->setPen(pen);
		arrow->setLayer(nullptr);
        addEntity(arrow);
    }

    if (arrow2) {
        // arrow 2:
        arrow = new RS_Solid(this, sd);
        arrow->shapeArrow(p2,
                          arrowAngle2,
                          arrowSize);
//        arrow->setPen(RS_Pen(RS2::FlagInvalid));
        arrow->setPen(pen);
		arrow->setLayer(nullptr);
        addEntity(arrow);
    }
}else{
    //display ticks
    // Arrows:

    RS_Line* tick;
	RS_Vector tickVector = RS_Vector::polar(dimtsz,arrowAngle1 + M_PI*0.25); //tick is 45 degree away

    if (arrow1) {
        // tick 1
        tick = new RS_Line(this, p1-tickVector, p1+tickVector);
        tick->setPen(pen);
//        tick->setPen(RS_Pen(RS2::FlagInvalid));
		tick->setLayer(nullptr);
        addEntity(tick);
    }

    if (arrow2) {
        // tick 2:
        tick = new RS_Line(this, p2-tickVector, p2+tickVector);
        tick->setPen(pen);
//        tick->setPen(RS_Pen(RS2::FlagInvalid));
		tick->setLayer(nullptr);
        addEntity(tick);
    }
}
    // Text label:
    RS_MTextData textData;
    RS_Vector textPos;

        double dimAngle1 = dimensionLine->getAngle1();
        double textAngle;
        bool corrected=false;
        if (getAlignText())
            textAngle =0.0;
        else
            textAngle = RS_Math::makeAngleReadable(dimAngle1, true, &corrected);

    if (data.middleOfText.valid && !forceAutoText) {
        textPos = data.middleOfText;
    } else {
        textPos = dimensionLine->getMiddlePoint();

        if (!getAlignText()) {
			// rotate text so it's readable from the bottom or right (ISO)
			// quadrant 1 & 4
			double const a = corrected?-M_PI_2:M_PI_2;
			RS_Vector distV = RS_Vector::polar(dimgap + dimtxt/2.0, dimAngle1+a);

            // move text away from dimension line:
            textPos+=distV;
        }
        //// the next update should still be able to adjust this
        ////   auto text position. leave it invalid
                data.middleOfText = textPos;
    }

    textData = RS_MTextData(textPos,
                           dimtxt, 30.0,
                           RS_MTextData::VAMiddle,
                           RS_MTextData::HACenter,
                           RS_MTextData::LeftToRight,
                           RS_MTextData::Exact,
                           1.0,
                           getLabel(),
                           getTextStyle(),
//                           "standard",
                           textAngle);

    RS_MText* text = new RS_MText(this, textData);

    // move text to the side:
    RS_Vector distH;
    if (text->getUsedTextWidth()>distance) {
        distH.setPolar(text->getUsedTextWidth()/2.0
                       +distance/2.0+dimgap, textAngle);
        text->move(distH);
    }
    text->setPen(RS_Pen(getTextColor(), RS2::WidthByBlock, RS2::SolidLine));
//    text->setPen(RS_Pen(RS2::FlagInvalid));
	text->setLayer(nullptr);
    //horizontal text, split dimensionLine
    if (getAlignText()) {
        double w =text->getUsedTextWidth()/2+dimgap;
        double h = text->getUsedTextHeight()/2+dimgap;
		RS_Vector v1 = textPos - RS_Vector{w, h};
		RS_Vector v2 = textPos + RS_Vector{w, h};
		RS_EntityContainer c;
		c.addRectangle(v1, v2);
		RS_VectorSolutions sol1;
		for(RS_Entity* e: c) {
			sol1.push_back(
						RS_Information::getIntersection(dimensionLine, e, true)
						);
		}

        //are text intersecting dimensionLine?
		if (sol1.size()>1) {
            //yes, split dimension line
			RS_Line* dimensionLine2 =
					static_cast<RS_Line*>(dimensionLine->clone());
            v1 = sol1.get(0);
			v2 = sol1.get(1);
            if (p1.distanceTo(v1) < p1.distanceTo(v2)) {
                dimensionLine->setEndpoint(v1);
                dimensionLine2->setStartpoint(v2);
            } else {
                dimensionLine->setEndpoint(v2);
                dimensionLine2->setStartpoint(v1);
            }
            addEntity(dimensionLine2);
        }
    }

    addEntity(text);
}