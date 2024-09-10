void GridAARayIterator::raysForPixel(int i, int j, std::vector<Ray>& res)
{
    res.clear();

    float tanX = tan (_fieldOfView)*_aspectRatio;
    float tanY = tan (_fieldOfView);

    for (int k = 0; k < gridSize; k++) {
        for(int l = 0; l < gridSize; l++)
        {
            Vec3Df stepX = (float (k+gridSize*i) - gridSize*_screenWidth/2.f)/(gridSize * _screenWidth) * tanX * _rightVector;
            Vec3Df stepY = (float (l+gridSize*j) - gridSize*_screenHeight/2.f)/(gridSize * _screenHeight) * tanY * _upVector;
            Vec3Df step = stepX + stepY;
            Vec3Df dir = _direction + step;
            dir.normalize ();
            res.push_back(Ray(_camPos, dir));

        }
    }
}