void NGC_Exporter::export_layer(shared_ptr<Layer> layer, string of_name)
{
    string layername = layer->get_name();
    shared_ptr<RoutingMill> mill = layer->get_manufacturer();
    bool bAutolevelNow;
    vector<shared_ptr<icoords> > toolpaths = layer->get_toolpaths();
    vector<unsigned int> bridges;
    vector<unsigned int>::const_iterator currentBridge;

    double xoffsetTot;
    double yoffsetTot;
    Tiling tiling( tileInfo, cfactor );
    tiling.setGCodeEnd(string("\nG04 P0 ( dwell for no time -- G64 should not smooth over this point )\n")
        + (bZchangeG53 ? "G53 " : "") + "G00 Z" + str( format("%.3f") % ( mill->zchange * cfactor ) ) + 
        " ( retract )\n\n" + postamble + "M5 ( Spindle off. )\nG04 P" +
        to_string(mill->spindown_time) +
        "\nM9 ( Coolant off. )\n"
        "M2 ( Program end. )\n\n" );

    tiling.initialXOffsetVar = globalVars.getUniqueCode();
    tiling.initialYOffsetVar = globalVars.getUniqueCode();

    // open output file
    std::ofstream of;
    of.open(of_name.c_str());

    // write header to .ngc file
    for ( string s : header )
    {
        of << "( " << s << " )\n";
    }

    if( ( bFrontAutoleveller && layername == "front" ) ||
        ( bBackAutoleveller && layername == "back" ) )
        bAutolevelNow = true;
    else
        bAutolevelNow = false;

    if( bAutolevelNow || ( tileInfo.enabled && tileInfo.software != CUSTOM ) )
        of << "( Gcode for " << getSoftwareString(tileInfo.software) << " )\n";
    else
        of << "( Software-independent Gcode )\n";

    of.setf(ios_base::fixed);      //write floating-point values in fixed-point notation
    of.precision(5);              //Set floating-point decimal precision

    of << "\n" << preamble;       //insert external preamble

    if (bMetricoutput)
    {
        of << "G94 ( Millimeters per minute feed rate. )\n"
           << "G21 ( Units == Millimeters. )\n\n";
    }
    else
    {
        of << "G94 ( Inches per minute feed rate. )\n"
           << "G20 ( Units == INCHES. )\n\n";
    }

    of << "G90 ( Absolute coordinates. )\n"
       << "S" << left << mill->speed << " ( RPM spindle speed. )\n";

    if (mill->explicit_tolerance)
        of << "G64 P" << mill->tolerance * cfactor << " ( set maximum deviation from commanded toolpath )\n";

    of << "F" << mill->feed * cfactor << " ( Feedrate. )\n\n";

    if( bAutolevelNow )
    {
        if( !leveller->prepareWorkarea( toolpaths ) )
        {
            std::cerr << "Required number of probe points (" << leveller->requiredProbePoints() <<
                      ") exceeds the maximum number (" << leveller->maxProbePoints() << "). "
                      "Reduce either al-x or al-y." << std::endl;
            exit(EXIT_FAILURE);
        }

        leveller->header( of );
    }

    of << "F" << mill->feed * cfactor << " ( Feedrate. )\n"
       << "M3 ( Spindle on clockwise. )\n"
       << "G04 P" << mill->spinup_time << "\n";
    
    tiling.header( of );

    for( unsigned int i = 0; i < tileInfo.forYNum; i++ )
    {
        yoffsetTot = yoffset - i * tileInfo.boardHeight;
        
        for( unsigned int j = 0; j < tileInfo.forXNum; j++ )
        {
            xoffsetTot = xoffset - ( i % 2 ? tileInfo.forXNum - j - 1 : j ) * tileInfo.boardWidth;

            if( tileInfo.enabled && tileInfo.software == CUSTOM )
                of << "( Piece #" << j + 1 + i * tileInfo.forXNum << ", position [" << j << ";" << i << "] )\n\n";

            // contours
            for ( shared_ptr<icoords> path : toolpaths )
            {
                // retract, move to the starting point of the next contour
                of << "G04 P0 ( dwell for no time -- G64 should not smooth over this point )\n";
                of << "G00 Z" << mill->zsafe * cfactor << " ( retract )\n\n";
                of << "G00 X" << ( path->begin()->first - xoffsetTot ) * cfactor << " Y"
                   << ( path->begin()->second - yoffsetTot ) * cfactor << " ( rapid move to begin. )\n";

                /* if we're cutting, perhaps do it in multiple steps, but do isolations just once.
                 * i know this is partially repetitive, but this way it's easier to read
                 */
                shared_ptr<Cutter> cutter = dynamic_pointer_cast<Cutter>(mill);

                if (cutter && cutter->do_steps)
                {

                    //--------------------------------------------------------------------
                    //cutting (outline)

                    const unsigned int steps_num = ceil(-mill->zwork / cutter->stepsize);

                    if( bBridges )
                        if( i == 0 && j == 0 )  //Compute the bridges only the 1st time
                            bridges = layer->get_bridges( path );

                    for (unsigned int i = 0; i < steps_num; i++)
                    {
                        const double z = mill->zwork / steps_num * (i + 1);

                        of << "G01 Z" << z * cfactor << " F" << mill->vertfeed * cfactor << " ( plunge. )\n";
                        of << "G04 P0 ( dwell for no time -- G64 should not smooth over this point )\n";
                        of << "F" << mill->feed * cfactor << "\n";
                        of << "G01 ";

                        icoords::iterator iter = path->begin();
                        icoords::iterator last = path->end();      // initializing to quick & dirty sentinel value

                        if (bBridges)
                            currentBridge = bridges.begin();

                        while (iter != path->end())
                        {

                            of << "X" << ( iter->first - xoffsetTot ) * cfactor << " Y"
                               << ( iter->second - yoffsetTot ) * cfactor << '\n';

                            if (bBridges && currentBridge != bridges.end())
                            {
                                if (z < cutter->bridges_height)
                                {
                                    if (*currentBridge == iter - path->begin())
                                        of << "Z" << cutter->bridges_height * cfactor << '\n';
                                    else if (*currentBridge == last - path->begin())
                                    {
                                        of << "Z" << z * cfactor << " F" << cutter->vertfeed * cfactor << '\n';
                                        of << "F" << cutter->feed * cfactor << '\n';
                                        of << "G01 ";
                                    }
                                }

                                if (*currentBridge == last - path->begin())
                                    ++currentBridge;
                            }

                            last = iter;
                            ++iter;
                        }
                    }
                }
                else
                {
                    //--------------------------------------------------------------------
                    // isolating (front/backside)
                    of << "F" << mill->vertfeed * cfactor << '\n';

                    if( bAutolevelNow )
                    {
                        leveller->setLastChainPoint( icoordpair( ( path->begin()->first - xoffsetTot ) * cfactor,
                                                     ( path->begin()->second - yoffsetTot ) * cfactor ) );
                        of << leveller->g01Corrected( icoordpair( ( path->begin()->first - xoffsetTot ) * cfactor,
                                                      ( path->begin()->second - yoffsetTot ) * cfactor ) );
                    }
                    else
                        of << "G01 Z" << mill->zwork * cfactor << "\n";

                    of << "G04 P0 ( dwell for no time -- G64 should not smooth over this point )\n";
                    of << "F" << mill->feed * cfactor << '\n';

                    if (!bAutolevelNow)
                        of << "G01 ";

                    icoords::iterator iter = path->begin();

                    while (iter != path->end())
                    {
                        if( bAutolevelNow )
                            of << leveller->addChainPoint( icoordpair( ( iter->first - xoffsetTot ) * cfactor,
                                                                           ( iter->second - yoffsetTot ) * cfactor ) );
                        else
                            of << "X" << ( iter->first - xoffsetTot ) * cfactor << " Y"
                               << ( iter->second - yoffsetTot ) * cfactor << '\n';
                        ++iter;
                    }
                }
            }
        }
    }
    
    tiling.footer( of );

    if( bAutolevelNow )
    {
        leveller->footer( of );
    }

    of.close();
}