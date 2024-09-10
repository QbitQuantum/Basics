void __stdcall RVExtension(char *output, int outputSize, const char *function)
{
    ZERO_OUTPUT();
    std::stringstream outputStr;
    if (!strcmp(function, "version")) {
        strncpy_s(output, outputSize, ACE_FULL_VERSION_STR, _TRUNCATE);
        EXTENSION_RETURN();
    }

    char* input = _strdup(function);
    char* token = NULL;
    char* next_token = NULL;
    char* mode = strtok_s(input, ":", &next_token);

    if (!strcmp(mode, "retard")) {
        double ballisticCoefficient = 1.0;
        int dragModel = 1;
        double velocity = 0.0;
        double retard = 0.0;

        dragModel = strtol(strtok_s(NULL, ":", &next_token), NULL, 10);
        ballisticCoefficient = strtod(strtok_s(NULL, ":", &next_token), NULL);
        velocity = strtod(strtok_s(NULL, ":", &next_token), NULL);

        retard = calculateRetard(dragModel, ballisticCoefficient, velocity);
        // int n = sprintf(output,  "%f", retard);

        outputStr << retard;
        strncpy_s(output, outputSize, outputStr.str().c_str(), _TRUNCATE);

        EXTENSION_RETURN();
    } else if (!strcmp(mode, "atmosphericCorrection")) {
        double ballisticCoefficient = 1.0;
        double temperature = 15.0;
        double pressure = 1013.25;
        double humidity = 0.0;
        char* atmosphereModel;

        ballisticCoefficient = strtod(strtok_s(NULL, ":", &next_token), NULL);
        temperature = strtod(strtok_s(NULL, ":", &next_token), NULL);
        pressure = strtod(strtok_s(NULL, ":", &next_token), NULL);
        humidity = strtod(strtok_s(NULL, ":", &next_token), NULL);
        atmosphereModel = strtok_s(NULL, ":", &next_token);

        ballisticCoefficient = calculateAtmosphericCorrection(ballisticCoefficient, temperature, pressure, humidity, atmosphereModel);
        //int n = sprintf(output,  "%f", ballisticCoefficient);
        outputStr << ballisticCoefficient;
        strncpy_s(output, outputSize, outputStr.str().c_str(), _TRUNCATE);
        EXTENSION_RETURN();
    } else if (!strcmp(mode, "new")) {
        unsigned int index = 0;
        double airFriction = 0.0;
        char* ballisticCoefficientArray;
        char* ballisticCoefficient;
        std::vector<double> ballisticCoefficients;
        char* velocityBoundaryArray;
        char* velocityBoundary;
        std::vector<double> velocityBoundaries;
        char* atmosphereModel;
        int dragModel = 1;
        double stabilityFactor = 1.5;
        int twistDirection = 1;
        double transonicStabilityCoef = 1;
        double muzzleVelocity = 850;
        char* originArray;
        char* originEntry;
        std::vector<double> origin;
        double latitude = 0.0;
        double temperature = 0.0;
        double altitude = 0.0;
        double humidity = 0.0;
        double overcast = 0.0;
        double tickTime = 0.0;

        index = strtol(strtok_s(NULL, ":", &next_token), NULL, 10);
        airFriction = strtod(strtok_s(NULL, ":", &next_token), NULL);
        ballisticCoefficientArray = strtok_s(NULL, ":", &next_token);
        ballisticCoefficientArray++;
        ballisticCoefficientArray[strlen(ballisticCoefficientArray) - 1] = 0;
        ballisticCoefficient = strtok_s(ballisticCoefficientArray, ",", &token);
        while (ballisticCoefficient != NULL) {
            ballisticCoefficients.push_back(strtod(ballisticCoefficient, NULL));
            ballisticCoefficient = strtok_s(NULL, ",", &token);
        }
        velocityBoundaryArray = strtok_s(NULL, ":", &next_token);
        velocityBoundaryArray++;
        velocityBoundaryArray[strlen(velocityBoundaryArray) - 1] = 0;
        velocityBoundary = strtok_s(velocityBoundaryArray, ",", &token);
        while (velocityBoundary != NULL) {
            velocityBoundaries.push_back(strtod(velocityBoundary, NULL));
            velocityBoundary = strtok_s(NULL, ",", &token);
        }
        atmosphereModel = strtok_s(NULL, ":", &next_token);
        dragModel = strtol(strtok_s(NULL, ":", &next_token), NULL, 10);
        stabilityFactor = strtod(strtok_s(NULL, ":", &next_token), NULL);
        twistDirection = strtol(strtok_s(NULL, ":", &next_token), NULL, 10);
        muzzleVelocity = strtod(strtok_s(NULL, ":", &next_token), NULL);
        transonicStabilityCoef = strtod(strtok_s(NULL, ":", &next_token), NULL);
        originArray = strtok_s(NULL, ":", &next_token);
        originArray++;
        originArray[strlen(originArray) - 1] = 0;
        originEntry = strtok_s(originArray, ",", &token);
        while (originEntry != NULL) {
            origin.push_back(strtod(originEntry, NULL));
            originEntry = strtok_s(NULL, ",", &token);
        }
        latitude = strtod(strtok_s(NULL, ":", &next_token), NULL);
        temperature = strtod(strtok_s(NULL, ":", &next_token), NULL);
        altitude = strtod(strtok_s(NULL, ":", &next_token), NULL);
        humidity = strtod(strtok_s(NULL, ":", &next_token), NULL);
        overcast = strtod(strtok_s(NULL, ":", &next_token), NULL);
        tickTime = strtod(strtok_s(NULL, ":", &next_token), NULL);
        tickTime += strtod(strtok_s(NULL, ":", &next_token), NULL);

        while (index >= bulletDatabase.size()) {
            Bullet bullet;
            bulletDatabase.push_back(bullet);
        }

        bulletDatabase[index].airFriction = airFriction;
        bulletDatabase[index].ballisticCoefficients = ballisticCoefficients;
        bulletDatabase[index].velocityBoundaries = velocityBoundaries;
        bulletDatabase[index].atmosphereModel = atmosphereModel;
        bulletDatabase[index].dragModel = dragModel;
        bulletDatabase[index].stabilityFactor = stabilityFactor;
        bulletDatabase[index].twistDirection = twistDirection;
        bulletDatabase[index].transonicStabilityCoef = transonicStabilityCoef;
        bulletDatabase[index].muzzleVelocity = muzzleVelocity;
        bulletDatabase[index].origin = origin;
        bulletDatabase[index].latitude = latitude / 180 * M_PI;
        bulletDatabase[index].temperature = temperature;
        bulletDatabase[index].altitude = altitude;
        bulletDatabase[index].humidity = humidity;
        bulletDatabase[index].overcast = overcast;
        bulletDatabase[index].startTime = tickTime;
        bulletDatabase[index].lastFrame = tickTime;
        bulletDatabase[index].bcDegradation = 1.0;
        bulletDatabase[index].randSeed = 0;

        strncpy_s(output, outputSize, "", _TRUNCATE);
        EXTENSION_RETURN();
    } else if (!strcmp(mode, "simulate")) {
        // simulate:0:[-0.109985,542.529,-3.98301]:[3751.57,5332.23,214.252]:[0.598153,2.38829,0]:28.6:0:0.481542:0:215.16
        unsigned int index = 0;
        char* velocityArray;
        double velocity[3] = { 0.0, 0.0, 0.0 };
        char* positionArray;
        double position[3] = { 0.0, 0.0, 0.0 };
        char* windArray;
        double wind[3];
        double heightAGL = 0.0;
        double tickTime = 0.0;

        index = strtol(strtok_s(NULL, ":", &next_token), NULL, 10);
        velocityArray = strtok_s(NULL, ":", &next_token);
        velocityArray++;
        velocityArray[strlen(velocityArray) - 1] = 0;
        velocity[0] = strtod(strtok_s(velocityArray, ",", &token), NULL);
        velocity[1] = strtod(strtok_s(NULL, ",", &token), NULL);
        velocity[2] = strtod(strtok_s(NULL, ",", &token), NULL);
        positionArray = strtok_s(NULL, ":", &next_token);
        positionArray++;
        positionArray[strlen(positionArray) - 1] = 0;
        position[0] = strtod(strtok_s(positionArray, ",", &token), NULL);
        position[1] = strtod(strtok_s(NULL, ",", &token), NULL);
        position[2] = strtod(strtok_s(NULL, ",", &token), NULL);
        windArray = strtok_s(NULL, ":", &next_token);
        windArray++;
        windArray[strlen(windArray) - 1] = 0;
        wind[0] = strtod(strtok_s(windArray, ",", &token), NULL);
        wind[1] = strtod(strtok_s(NULL, ",", &token), NULL);
        wind[2] = strtod(strtok_s(NULL, ",", &token), NULL);
        heightAGL = strtod(strtok_s(NULL, ":", &next_token), NULL);
        tickTime = strtod(strtok_s(NULL, ":", &next_token), NULL);
        tickTime += strtod(strtok_s(NULL, ":", &next_token), NULL);

        if (bulletDatabase[index].randSeed == 0) {
            int angle = (int)round(atan2(velocity[0], velocity[1]) * 360 / M_PI);
            bulletDatabase[index].randSeed = (unsigned)(720 + angle) % 720;
            bulletDatabase[index].randSeed *= 3;
            bulletDatabase[index].randSeed += (unsigned)round(abs(velocity[2]) / 2);
            bulletDatabase[index].randSeed *= 3;
            bulletDatabase[index].randSeed += (unsigned)round(abs(bulletDatabase[index].origin[0] / 2));
            bulletDatabase[index].randSeed *= 3;
            bulletDatabase[index].randSeed += (unsigned)round(abs(bulletDatabase[index].origin[1] / 2));
            bulletDatabase[index].randSeed *= 3;
            bulletDatabase[index].randSeed += (unsigned)abs(bulletDatabase[index].temperature) * 10;
            bulletDatabase[index].randSeed *= 3;
            bulletDatabase[index].randSeed += (unsigned)abs(bulletDatabase[index].humidity) * 10;
            bulletDatabase[index].randGenerator.seed(bulletDatabase[index].randSeed);
        }

        double ballisticCoefficient = 1.0;
        double dragRef = 0.0;
        double drag = 0.0;
        double accelRef[3] = { 0.0, 0.0, 0.0 };
        double accel[3] = { 0.0, 0.0, 0.0 };
        double TOF = 0.0;
        double deltaT = 0.0;
        double bulletSpeed;
        double trueVelocity[3] = { 0.0, 0.0, 0.0 };
        double trueSpeed = 0.0;
        double temperature = 0.0;
        double pressure = 1013.25;
        double windSpeed = 0.0;
        double windAttenuation = 1.0;
        double velocityOffset[3] = { 0.0, 0.0, 0.0 };

        TOF = tickTime - bulletDatabase[index].startTime;

        deltaT = tickTime - bulletDatabase[index].lastFrame;
        bulletDatabase[index].lastFrame = tickTime;

        bulletSpeed = sqrt(pow(velocity[0], 2) + pow(velocity[1], 2) + pow(velocity[2], 2));

        windSpeed = sqrt(pow(wind[0], 2) + pow(wind[1], 2) + pow(wind[2], 2));
        if (windSpeed > 0.1) {
            double windSourceTerrain[3];

            windSourceTerrain[0] = position[0] - wind[0] / windSpeed * 100;
            windSourceTerrain[1] = position[1] - wind[1] / windSpeed * 100;
            windSourceTerrain[2] = position[2] - wind[2] / windSpeed * 100;

            int gridX = (int)floor(windSourceTerrain[0] / 50);
            int gridY = (int)floor(windSourceTerrain[1] / 50);
            int gridCell = gridX * map->mapGrids + gridY;

            if (gridCell >= 0 && (std::size_t)gridCell < map->gridHeights.size() && (std::size_t)gridCell < map->gridBuildingNums.size()) {
                double gridHeight = map->gridHeights[gridCell];

                if (gridHeight > position[2]) {
                    double angle = atan((gridHeight - position[2]) / 100);
                    windAttenuation *= pow(abs(cos(angle)), 2);
                }
            }
        }

        if (windSpeed > 0.1) {
            double windSourceObstacles[3];

            windSourceObstacles[0] = position[0] - wind[0] / windSpeed * 25;
            windSourceObstacles[1] = position[1] - wind[1] / windSpeed * 25;
            windSourceObstacles[2] = position[2] - wind[2] / windSpeed * 25;

            if (heightAGL > 0 && heightAGL < 20) {
                double roughnessLength = calculateRoughnessLength(windSourceObstacles[0], windSourceObstacles[1]);
                windAttenuation *= abs(log(heightAGL / roughnessLength) / log(20 / roughnessLength));
            }
        }

        if (windAttenuation < 1) {
            wind[0] *= windAttenuation;
            wind[1] *= windAttenuation;
            wind[2] *= windAttenuation;
            windSpeed = sqrt(pow(wind[0], 2) + pow(wind[1], 2) + pow(wind[2], 2));
        }

        trueVelocity[0] = velocity[0] - wind[0];
        trueVelocity[1] = velocity[1] - wind[1];
        trueVelocity[2] = velocity[2] - wind[2];
        trueSpeed = sqrt(pow(trueVelocity[0], 2) + pow(trueVelocity[1], 2) + pow(trueVelocity[2], 2));

        double speedOfSound = 331.3 + (0.6 * temperature);
        double transonicSpeed = 394 + (0.6 * temperature);
        if (bulletDatabase[index].transonicStabilityCoef < 1.0f && bulletSpeed < transonicSpeed && bulletSpeed > speedOfSound) {
            std::uniform_real_distribution<double> distribution(-10.0, 10.0);
            double coef = 1.0f - bulletDatabase[index].transonicStabilityCoef;

            trueVelocity[0] += distribution(bulletDatabase[index].randGenerator) * coef;
            trueVelocity[1] += distribution(bulletDatabase[index].randGenerator) * coef;
            trueVelocity[2] += distribution(bulletDatabase[index].randGenerator) * coef;
            double speed = sqrt(pow(trueVelocity[0], 2) + pow(trueVelocity[1], 2) + pow(trueVelocity[2], 2));

            trueVelocity[0] *= trueSpeed / speed;
            trueVelocity[1] *= trueSpeed / speed;
            trueVelocity[2] *= trueSpeed / speed;

            bulletDatabase[index].bcDegradation *= pow(0.993, coef);
        };

        temperature = bulletDatabase[index].temperature - 0.0065 * position[2];
        pressure = (1013.25 - 10 * bulletDatabase[index].overcast) * pow(1 - (0.0065 * (bulletDatabase[index].altitude + position[2])) / (273.15 + temperature + 0.0065 * bulletDatabase[index].altitude), 5.255754495);

        if (bulletDatabase[index].ballisticCoefficients.size() == bulletDatabase[index].velocityBoundaries.size() + 1) {
            dragRef = deltaT * bulletDatabase[index].airFriction * bulletSpeed * bulletSpeed;

            accelRef[0] = (velocity[0] / bulletSpeed) * dragRef;
            accelRef[1] = (velocity[1] / bulletSpeed) * dragRef;
            accelRef[2] = (velocity[2] / bulletSpeed) * dragRef;

            velocityOffset[0] -= accelRef[0];
            velocityOffset[1] -= accelRef[1];
            velocityOffset[2] -= accelRef[2];

            ballisticCoefficient = bulletDatabase[index].ballisticCoefficients[0];
            for (int i = (int)bulletDatabase[index].velocityBoundaries.size() - 1; i >= 0; i = i - 1) {
                if (bulletSpeed < bulletDatabase[index].velocityBoundaries[i]) {
                    ballisticCoefficient = bulletDatabase[index].ballisticCoefficients[i + 1];
                    break;
                }
            }

            ballisticCoefficient = calculateAtmosphericCorrection(ballisticCoefficient, temperature, pressure, bulletDatabase[index].humidity, bulletDatabase[index].atmosphereModel);
            ballisticCoefficient *= bulletDatabase[index].bcDegradation;
            drag = deltaT * calculateRetard(bulletDatabase[index].dragModel, ballisticCoefficient, trueSpeed);
            accel[0] = (trueVelocity[0] / trueSpeed) * drag;
            accel[1] = (trueVelocity[1] / trueSpeed) * drag;
            accel[2] = (trueVelocity[2] / trueSpeed) * drag;

            velocityOffset[0] -= accel[0];
            velocityOffset[1] -= accel[1];
            velocityOffset[2] -= accel[2];
        } else {
            double airDensity = calculateAirDensity(temperature, pressure, bulletDatabase[index].humidity);
            double airFriction = bulletDatabase[index].airFriction * airDensity / STD_AIR_DENSITY_ICAO;

            if (airFriction != bulletDatabase[index].airFriction || windSpeed > 0) {
                dragRef = deltaT * bulletDatabase[index].airFriction * bulletSpeed * bulletSpeed;

                accelRef[0] = (velocity[0] / bulletSpeed) * dragRef;
                accelRef[1] = (velocity[1] / bulletSpeed) * dragRef;
                accelRef[2] = (velocity[2] / bulletSpeed) * dragRef;

                velocityOffset[0] -= accelRef[0];
                velocityOffset[1] -= accelRef[1];
                velocityOffset[2] -= accelRef[2];

                drag = deltaT * airFriction * trueSpeed * trueSpeed;
                accel[0] = (trueVelocity[0] / trueSpeed) * drag;
                accel[1] = (trueVelocity[1] / trueSpeed) * drag;
                accel[2] = (trueVelocity[2] / trueSpeed) * drag;

                velocityOffset[0] += accel[0];
                velocityOffset[1] += accel[1];
                velocityOffset[2] += accel[2];
            }
        }

        if (TOF > 0) {
            double bulletDir = atan2(velocity[0], velocity[1]);
            double spinAccel = bulletDatabase[index].twistDirection * (0.0482251 * (bulletDatabase[index].stabilityFactor + 1.2)) / pow(TOF, 0.17);
            velocityOffset[0] += sin(bulletDir + M_PI / 2) * spinAccel * deltaT;
            velocityOffset[1] += cos(bulletDir + M_PI / 2) * spinAccel * deltaT;
        }

        double lat = bulletDatabase[index].latitude;
        accel[0] = 2 * EARTH_ANGULAR_SPEED * +(velocity[1] * sin(lat) - velocity[2] * cos(lat));
        accel[1] = 2 * EARTH_ANGULAR_SPEED * -(velocity[0] * sin(lat));
        accel[2] = 2 * EARTH_ANGULAR_SPEED * +(velocity[0] * cos(lat));

        velocityOffset[0] += accel[0] * deltaT;
        velocityOffset[1] += accel[1] * deltaT;
        velocityOffset[2] += accel[2] * deltaT;

        outputStr << "_bullet setVelocity (_bulletVelocity vectorAdd [" << velocityOffset[0] << "," << velocityOffset[1] << "," << velocityOffset[2] << "]);";
        strncpy_s(output, outputSize, outputStr.str().c_str(), _TRUNCATE);
        EXTENSION_RETURN();
    } else if (!strcmp(mode, "set")) {
        int height = 0;
        int numObjects = 0;
        int surfaceIsWater = 0;

        height = strtol(strtok_s(NULL, ":", &next_token), NULL, 10);
        numObjects = strtol(strtok_s(NULL, ":", &next_token), NULL, 10);
        surfaceIsWater = strtol(strtok_s(NULL, ":", &next_token), NULL, 10);

        map->gridHeights.push_back(height);
        map->gridBuildingNums.push_back(numObjects);
        map->gridSurfaceIsWater.push_back(surfaceIsWater);

        strncpy_s(output, outputSize, outputStr.str().c_str(), _TRUNCATE);
        EXTENSION_RETURN();
    } else if (!strcmp(mode, "init")) {
        int mapSize = 0;
        int mapGrids = 0;
        unsigned int gridCells = 0;

        worldName = strtok_s(NULL, ":", &next_token);
        mapSize = strtol(strtok_s(NULL, ":", &next_token), NULL, 10);

        mapGrids = (int)ceil((double)mapSize / 50.0) + 1;
        gridCells = mapGrids * mapGrids;

        map = &mapDatabase[worldName];
        if (map->gridHeights.size() == gridCells) {
            outputStr << "Terrain already initialized";
            strncpy_s(output, outputSize, outputStr.str().c_str(), _TRUNCATE);
            EXTENSION_RETURN();
        }

        map->mapSize = mapSize;
        map->mapGrids = mapGrids;
        map->gridHeights.clear();
        map->gridBuildingNums.clear();
        map->gridSurfaceIsWater.clear();
        map->gridHeights.reserve(gridCells);
        map->gridBuildingNums.reserve(gridCells);
        map->gridSurfaceIsWater.reserve(gridCells);

        strncpy_s(output, outputSize, outputStr.str().c_str(), _TRUNCATE);
        EXTENSION_RETURN();
    } else if (!strcmp(mode, "zeroAngleVanilla")) {
        double zeroRange = strtod(strtok_s(NULL, ":", &next_token), NULL);
        double initSpeed = strtod(strtok_s(NULL, ":", &next_token), NULL);
        double airFriction = strtod(strtok_s(NULL, ":", &next_token), NULL);
        double boreHeight = strtod(strtok_s(NULL, ":", &next_token), NULL);

        double zeroAngle = calculateVanillaZeroAngle(zeroRange, initSpeed, airFriction, boreHeight);

        outputStr << DEGREES(zeroAngle);
        strncpy_s(output, outputSize, outputStr.str().c_str(), _TRUNCATE);
        EXTENSION_RETURN();
    } else if (!strcmp(mode, "zeroAngle")) {
        double zeroRange = strtod(strtok_s(NULL, ":", &next_token), NULL);
        double muzzleVelocity = strtod(strtok_s(NULL, ":", &next_token), NULL);
        double boreHeight = strtod(strtok_s(NULL, ":", &next_token), NULL);
        double temperature = strtod(strtok_s(NULL, ":", &next_token), NULL);
        double pressure = strtod(strtok_s(NULL, ":", &next_token), NULL);
        double humidity = strtod(strtok_s(NULL, ":", &next_token), NULL);
        double ballisticCoefficient = strtod(strtok_s(NULL, ":", &next_token), NULL);
        int dragModel = strtol(strtok_s(NULL, ":", &next_token), NULL, 10);
        char* atmosphereModel = strtok_s(NULL, ":", &next_token);

        double zeroAngle = calculateZeroAngle(zeroRange, muzzleVelocity, boreHeight, temperature, pressure, humidity, ballisticCoefficient, dragModel, atmosphereModel);

        outputStr << DEGREES(zeroAngle);
        strncpy_s(output, outputSize, outputStr.str().c_str(), _TRUNCATE);
        EXTENSION_RETURN();
    }
    strncpy_s(output, outputSize, outputStr.str().c_str(), _TRUNCATE);
    EXTENSION_RETURN();
}