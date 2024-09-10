// Fill DF with evenly distributed rot & tilt =================================
void make_even_distribution(std::vector<double> &rotList, std::vector<double> &tiltList,
							double sampling, SymList &SL, bool include_mirror)
{
    int rot_nstep, tilt_nstep = ROUND(180. / sampling) + 1;
    double rot_sam, tilt, tilt_sam;
    bool append;
    tilt_sam = (180. / tilt_nstep);

    // Create evenly distributed angles
    rotList.clear();
    tiltList.clear();
    rotList.reserve(20000);  // Normally there are many less directions than 20000
    tiltList.reserve(20000); // Set to 20000 to avoid resizing
    Matrix2D<double> L(3,3),R(3,3);
    for (int tilt_step = 0; tilt_step < tilt_nstep; tilt_step++)
    {
        tilt = ((double)tilt_step / (tilt_nstep - 1)) * 180.;
        if (tilt > 0)
            rot_nstep = CEIL(360. * sin(DEG2RAD(tilt)) / sampling);
        else
            rot_nstep = 1;
        rot_sam = 360. / (double)rot_nstep;
        for (double rot = 0.; rot < 360.; rot += rot_sam)
        {
            // Check whether by symmetry or mirror the angle has been included already
            append = true;
            size_t imax=rotList.size();
            double *ptrRot=NULL;
            double *ptrTilt=NULL;
            if (imax>0)
            {
            	ptrRot=&rotList[0];
            	ptrTilt=&tiltList[0];
            }
            for (size_t i=0; i<imax; ++i, ++ptrRot, ++ptrTilt)
            {
                if (!directions_are_unique(rot, tilt, *ptrRot, *ptrTilt, rot_sam, tilt_sam, SL,
                                           include_mirror, L, R))
                {
                    append = false;
                    break;
                }
            }
            if (append)
            {
            	rotList.push_back(rot);
            	tiltList.push_back(tilt);
            }
        }
    }
}