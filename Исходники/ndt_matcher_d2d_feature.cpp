//DEPRECATED???
double
NDTMatcherFeatureD2D::scoreNDT(std::vector<NDTCell*> &sourceNDT, NDTMap &targetNDT,
        Eigen::Transform<double,3,Eigen::Affine,Eigen::ColMajor>& T)
{
    NUMBER_OF_ACTIVE_CELLS = 0;
    double score_here = 0;
    double det = 0;
    bool exists = false;
    NDTCell *cell;
    Eigen::Matrix3d covCombined, icov;
    Eigen::Vector3d meanFixed;
    Eigen::Vector3d meanMoving;
    Eigen::Matrix3d R = T.rotation();
    std::vector<std::pair<unsigned int, double> > scores;
    for(unsigned int j=0; j<_corr.size(); j++)
    {
        unsigned int i = _corr[j].second;
        if (_corr[j].second >= (int)sourceNDT.size())
        {
            std::cout << "second correspondance : " << _corr[j].second << ", " << sourceNDT.size() << std::endl;
        }
        if (sourceNDT[i] == NULL)
        {
            std::cout << "sourceNDT[i] == NULL!" << std::endl;
        }
        meanMoving = T*sourceNDT[i]->getMean();

        cell = targetNDT.getCellIdx(_corr[j].first);
        {

            if(cell == NULL)
            {
                std::cout << "cell== NULL!!!" << std::endl;
            }
            else
            {
                if(cell->hasGaussian_)
                {
                    meanFixed = cell->getMean();
                    covCombined = cell->getCov() + R.transpose()*sourceNDT[i]->getCov()*R;
                    covCombined.computeInverseAndDetWithCheck(icov,det,exists);
                    if(!exists) continue;
                    double l = (meanMoving-meanFixed).dot(icov*(meanMoving-meanFixed));
                    if(l*0 != 0) continue;
                    if(l > 120) continue;

                    double sh = -lfd1*(exp(-lfd2*l/2));

                    if(fabsf(sh) > 1e-10)
                    {
                        NUMBER_OF_ACTIVE_CELLS++;
                    }
                    scores.push_back(std::pair<unsigned int, double>(j, sh));
                    score_here += sh;
                    //score_here += l;
                }
            }
        }
    }

    if (_trimFactor == 1.)
    {
        return score_here;
    }
    else
    {
        // Determine the score value
        if (scores.empty()) // TODO, this happens(!), why??!??
            return score_here;

        score_here = 0.;
        unsigned int index = static_cast<unsigned int>(_trimFactor * (scores.size() - 1));
        //	std::nth_element (scores.begin(), scores.begin()+index, scores.end(), sort_scores()); //boost::bind(&std::pair<unsigned int, double>::second, _1) < boost::bind(&std::pair<unsigned int, double>::second, _2));
        std::nth_element (scores.begin(), scores.begin()+index, scores.end(), boost::bind(&std::pair<unsigned int, double>::second, _1) < boost::bind(&std::pair<unsigned int, double>::second, _2));
        std::fill(_goodCorr.begin(), _goodCorr.end(), false);
        //	std::cout << "_goodCorr.size() : " << _goodCorr.size() << " scores.size() : " << scores.size() << " index : " << index << std::endl;
        for (unsigned int i = 0; i < _goodCorr.size(); i++)
        {
            if (i <= index)
            {
                score_here += scores[i].second;
                _goodCorr[scores[i].first] = true;
            }
        }
        return score_here;
    }
}