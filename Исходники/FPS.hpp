    float step()
    {
        ++mySteps;

        float time(myClock.getElapsedTime().asSeconds());

        if (time >= 1.f)
        {
            std::ostringstream str; str.precision(4);
            str<<mySteps/time;
            setString(str.str());
            mySteps = 0;
            myClock.restart();
        }
        return time;
    }