osg::Matrix AntiSquish::computeUnSquishedMatrix(const osg::Matrix& LTW, bool& flag)
{
    osg::Vec3d t, s;
    osg::Quat r, so;

    if (LTW == _cachedLocalToWorld && _dirty == false)
    {
        flag = false;
        return osg::Matrix::identity();
    }

    _cachedLocalToWorld = LTW;

    LTW.decompose(t, r, s, so);

    // Let's take an average of the scale.
    double av = (s[0] + s[1] + s[2])/3.0;
    s[0] = av; s[1] = av; s[2]=av;

    if (av == 0)
    {
        flag = false;
        return osg::Matrix::identity();
    }

    osg::Matrix unsquished;

    //
    // Final Matrix: [-Pivot][SO]^[S][SO][R][T][Pivot][LOCALTOWORLD]^[position]
    // OR [SO]^[S][SO][R][T][LOCALTOWORLD]^
    //
    if (_usePivot)
    {
        unsquished.postMultTranslate(-_pivot);

        osg::Matrix tmps, invtmps;
        so.get(tmps);
        if (!invtmps.invert(tmps))
        {
            flag = false;
            return osg::Matrix::identity();
        }

        //SO^
        unsquished.postMult(invtmps);
        //S
        unsquished.postMultScale(s);
        //SO
        unsquished.postMult(tmps);
        //R
        unsquished.postMultRotate(r);
        //T
        unsquished.postMultTranslate(t);

        osg::Matrix invltw;
        if (!invltw.invert(LTW))
        {
            flag = false;
            return osg::Matrix::identity();
        }
        // LTW^
        unsquished.postMult( invltw );

        // Position
        if (_usePosition)
            unsquished.postMultTranslate(_position);
        else
            unsquished.postMultTranslate(_pivot);
    }
    else
    {
        osg::Matrix tmps, invtmps;
        so.get(tmps);
        if (!invtmps.invert(tmps))
        {
            flag = false;
            return osg::Matrix::identity();
        }
        unsquished.postMult(invtmps);
        unsquished.postMultScale(s);
        unsquished.postMult(tmps);
        unsquished.postMultRotate(r);
        unsquished.postMultTranslate(t);
        osg::Matrix invltw;
        if (!invltw.invert(LTW))
        {
            flag = false;
            return osg::Matrix::identity();
        }
        unsquished.postMult( invltw );
    }

    if (unsquished.isNaN())
    {
        flag = false;
        return  osg::Matrix::identity();
    }

    flag = true;
    _dirty = false;
    return unsquished;
}