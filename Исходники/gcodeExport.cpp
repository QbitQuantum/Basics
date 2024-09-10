void GCodeExport::writeMove(int x, int y, int z, double speed, double extrusion_mm3_per_mm)
{
    if (currentPosition.x == x && currentPosition.y == y && currentPosition.z == z)
        return;
    
    assert(speed < 200 && speed > 1); // normal F values occurring in UM2 gcode (this code should not be compiled for release)
    assert((Point3(x,y,z) - currentPosition).vSize() < MM2INT(300)); // no crazy positions (this code should not be compiled for release)
    
    if (extrusion_mm3_per_mm < 0)
        logWarning("Warning! Negative extrusion move!");
    
    double extrusion_per_mm = extrusion_mm3_per_mm;
    if (!is_volumatric)
    {
        extrusion_per_mm = extrusion_mm3_per_mm / getFilamentArea(current_extruder);
    }
    
    Point gcode_pos = getGcodePos(x,y, current_extruder);

    if (flavor == EGCodeFlavor::BFB)
    {
        //For Bits From Bytes machines, we need to handle this completely differently. As they do not use E values but RPM values.
        float fspeed = speed * 60;
        float rpm = extrusion_per_mm * speed * 60;
        const float mm_per_rpm = 4.0; //All BFB machines have 4mm per RPM extrusion.
        rpm /= mm_per_rpm;
        if (rpm > 0)
        {
            if (isRetracted)
            {
                if (currentSpeed != double(rpm))
                {
                    //fprintf(f, "; %f e-per-mm %d mm-width %d mm/s\n", extrusion_per_mm, lineWidth, speed);
                    //fprintf(f, "M108 S%0.1f\r\n", rpm);
                    *output_stream << "M108 S" << std::setprecision(1) << rpm << "\r\n";
                    currentSpeed = double(rpm);
                }
                //Add M101 or M201 to enable the proper extruder.
                *output_stream << "M" << int((current_extruder + 1) * 100 + 1) << "\r\n";
                isRetracted = false;
            }
            //Fix the speed by the actual RPM we are asking, because of rounding errors we cannot get all RPM values, but we have a lot more resolution in the feedrate value.
            // (Trick copied from KISSlicer, thanks Jonathan)
            fspeed *= (rpm / (roundf(rpm * 100) / 100));

            //Increase the extrusion amount to calculate the amount of filament used.
            Point3 diff = Point3(x,y,z) - getPosition();
            
            extrusion_amount += extrusion_per_mm * diff.vSizeMM();
        }else{
            //If we are not extruding, check if we still need to disable the extruder. This causes a retraction due to auto-retraction.
            if (!isRetracted)
            {
                *output_stream << "M103\r\n";
                isRetracted = true;
            }
        }
        *output_stream << std::setprecision(3) << 
            "G1 X" << INT2MM(gcode_pos.X) << 
            " Y" << INT2MM(gcode_pos.Y) << 
            " Z" << INT2MM(z) << std::setprecision(1) << " F" << fspeed << "\r\n";
    }
    else
    {
        //Normal E handling.
        
        if (extrusion_mm3_per_mm > 0.000001)
        {
            Point3 diff = Point3(x,y,z) - getPosition();
            if (isZHopped > 0)
            {
                // TinyG G1: Straight feed
                *output_stream << std::setprecision(3) << "G1 Z" << INT2MM(currentPosition.z) << "\n";
                isZHopped = 0;
            }
            extrusion_amount += (is_volumatric) ? last_coasted_amount_mm3 : last_coasted_amount_mm3 / getFilamentArea(current_extruder);   
            if (isRetracted)
            {
                if (flavor == EGCodeFlavor::ULTIGCODE || flavor == EGCodeFlavor::REPRAP_VOLUMATRIC)
                {
                    *output_stream << "G11\n"; //TODO try this code and see what happens
                    //Assume default UM2 retraction settings.
                    if (last_coasted_amount_mm3 > 0)
                    {
                        *output_stream << "G1 F" << (retractionPrimeSpeed * 60) << " " << extruder_attr[current_extruder].extruderCharacter << std::setprecision(5) << extrusion_amount << "\n";
                    }
                    estimateCalculator.plan(TimeEstimateCalculator::Position(INT2MM(currentPosition.x), INT2MM(currentPosition.y), INT2MM(currentPosition.z), extrusion_amount), 25.0);
                }else{
                    // TinyG checked
                    *output_stream << "G1 F" << (retractionPrimeSpeed * 60) << " " << extruder_attr[current_extruder].extruderCharacter << std::setprecision(5) << extrusion_amount << "\n";
                    currentSpeed = retractionPrimeSpeed;
                    estimateCalculator.plan(TimeEstimateCalculator::Position(INT2MM(currentPosition.x), INT2MM(currentPosition.y), INT2MM(currentPosition.z), extrusion_amount), currentSpeed);
                }
                if (getExtrusionAmountMM3(current_extruder) > 10000.0) //According to https://github.com/Ultimaker/CuraEngine/issues/14 having more then 21m of extrusion causes inaccuracies. So reset it every 10m, just to be sure.
                    resetExtrusionValue();
                isRetracted = false;
            }
            else 
            {
                if (last_coasted_amount_mm3 > 0)
                {
                    *output_stream << "G1 F" << (retractionPrimeSpeed * 60) << " " << extruder_attr[current_extruder].extruderCharacter << std::setprecision(5) << extrusion_amount << "\n";
                    estimateCalculator.plan(TimeEstimateCalculator::Position(INT2MM(currentPosition.x), INT2MM(currentPosition.y), INT2MM(currentPosition.z), extrusion_amount), currentSpeed);
                }
            }
            last_coasted_amount_mm3 = 0;
            extrusion_amount += extrusion_per_mm * diff.vSizeMM();
            // TinyG TODO: add one axis
            *output_stream << "G1";
        }else{
            *output_stream << "G0";
                    
            if (commandSocket) {
                // we should send this travel as a non-retraction move
                cura::Polygons travelPoly;
                PolygonRef travel = travelPoly.newPoly();
                travel.add(Point(currentPosition.x, currentPosition.y));
                travel.add(Point(x, y));
                commandSocket->sendPolygons(isRetracted ? MoveRetractionType : MoveCombingType, layer_nr, travelPoly, isRetracted ? MM2INT(0.2) : MM2INT(0.1));
            }                    
        }

        if (currentSpeed != speed)
        {
            *output_stream << " F" << (speed * 60);
            currentSpeed = speed;
        }

        *output_stream << std::setprecision(3) << 
            " X" << INT2MM(gcode_pos.X) << 
            " Y" << INT2MM(gcode_pos.Y);
        if (z != currentPosition.z)
            *output_stream << " Z" << INT2MM(z + isZHopped);
        if (extrusion_mm3_per_mm > 0.000001)
            *output_stream << " " << extruder_attr[current_extruder].extruderCharacter << std::setprecision(5) << extrusion_amount;
        *output_stream << "\n";
    }
    
    currentPosition = Point3(x, y, z);
    startPosition = currentPosition;
    estimateCalculator.plan(TimeEstimateCalculator::Position(INT2MM(currentPosition.x), INT2MM(currentPosition.y), INT2MM(currentPosition.z), extrusion_amount), speed);
}