void Puppeteer::draw()
{
    // ----------------------------debug

    if (Constants::Debug::DRAW_PUPPETEER_BOUNDS) {
        Vec3f origin = Vec3f::zero();
        PolyLine<Vec3f> boundsL;
        boundsL.push_back(origin - axisVert * armLenL);
        boundsL.push_back(origin - axisVert * armLenL + axisHoriz * armLenL);
        boundsL.push_back(origin + axisVert * armLenL + axisHoriz * armLenL);
        boundsL.push_back(origin + axisVert * armLenL);
        boundsL.push_back(origin - axisVert * armLenL);
        boundsL.push_back(origin - axisVert * armLenL + normal * armLenL); //
        boundsL.push_back(origin - axisVert * armLenL + normal * armLenL + axisHoriz * armLenL);
        boundsL.push_back(origin + axisVert * armLenL + normal * armLenL + axisHoriz * armLenL);
        boundsL.push_back(origin + axisVert * armLenL + normal * armLenL);
        boundsL.push_back(origin - axisVert * armLenL + normal * armLenL);

        PolyLine<Vec3f> boundsR;
        boundsR.push_back(origin - axisVert * armLenR);
        boundsR.push_back(origin - axisVert * armLenR - axisHoriz * armLenR);
        boundsR.push_back(origin + axisVert * armLenR - axisHoriz * armLenR);
        boundsR.push_back(origin + axisVert * armLenR);
        boundsR.push_back(origin - axisVert * armLenR);
        boundsR.push_back(origin - axisVert * armLenR + normal * armLenR); //
        boundsR.push_back(origin - axisVert * armLenR + normal * armLenR - axisHoriz * armLenR);
        boundsR.push_back(origin + axisVert * armLenR + normal * armLenR - axisHoriz * armLenR);
        boundsR.push_back(origin + axisVert * armLenR + normal * armLenR);
        boundsR.push_back(origin - axisVert * armLenR + normal * armLenR);

        gl::pushMatrices();

        MayaCamUI* mayaCam = Constants::mayaCam();
        gl::setMatrices(mayaCam->getCamera());

        float scale = 1.0f;
        // original bounding boxes
        gl::color(Color(0.5f, 0.5f, 0.5f));
        gl::pushModelView();
        gl::translate(shoulderL);
        gl::draw(boundsL);
        gl::popModelView();

        gl::pushModelView();
        gl::translate(shoulderR);
        gl::draw(boundsR);
        gl::popModelView();

        // normalized bound boxes
        gl::color(Color(0, 0, 1));
        gl::pushModelView();
        gl::translate(-.5f, 0, 0);
        gl::scale(scale, scale, scale);
        gl::rotate( Quatf(normalizationMatrix) );
        gl::draw(boundsL);
        gl::popModelView();

        gl::pushModelView();
        gl::translate(-.5f, 0, 0);
        gl::scale(scale, scale, scale);
        gl::drawCube(handL, Vec3f(0.1f, 0.1f, 0.1f));
        gl::popModelView();

        gl::color(Color(0, 1, 0));
        gl::pushModelView();
        gl::translate(.5f, 0, 0);
        gl::scale(scale, scale, scale);
        gl::rotate( Quatf(normalizationMatrix) );
        gl::draw(boundsR);
        gl::popModelView();

        gl::pushModelView();
        gl::translate(.5f, 0, 0);
        gl::scale(scale, scale, scale);
        gl::drawCube(handR, Vec3f(0.1f, 0.1f, 0.1f));
        gl::popModelView();

        gl::popMatrices();

        gl::color( Color(1, 1, 1));
    }

    arduino->draw();
}