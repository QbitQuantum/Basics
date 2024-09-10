static void SelectNShapes (
            vec_SHAPE &Shapes,  // io
            vec_string &Tags,   // io: also shuffled, in step with Shapes
            int nWantedShapes,  // in: 0 means return all shapes
            int nSeed=0)        // in: 0 means no random selection; if any other
                                //     val select randomly with rand seed=nSeed
{
unsigned nShapes = Tags.size();
if (nWantedShapes == 0)
    nWantedShapes = nShapes;
nWantedShapes = MIN((unsigned)nWantedShapes, nShapes);
if (nSeed)
    {
    // generate a shuffled set of indices in iShuffledShapes

    vec_int iShuffledShapes(nShapes);
    unsigned iShape;
    for (iShape = 0; iShape < nShapes; iShape++)
        iShuffledShapes[iShape] = iShape;

    SeedRand(nSeed);

    // We use our own random shuffle here because different compilers
    // give different results which messes up regression testing.
    // (I think only Visual C 6.0 is incompatible with everyone else?)
    //
    // Following code is equivalent to
    //    random_shuffle(iShuffledShapes.begin(), iShuffledShapes.end(),
    //       pointer_to_unary_function<int,int>(Rand));

    vec_int::iterator pNext = iShuffledShapes.begin();
    for (int i = 2; ++pNext != iShuffledShapes.end(); ++i)
        iter_swap(pNext, iShuffledShapes.begin() + Rand(i));

    iShuffledShapes.resize(nWantedShapes);

    // sort the selected indices so we can do an in-place replacement in Shapes

    sort(iShuffledShapes.begin(), iShuffledShapes.end());

    // keep the first nWantedShapes in iShuffledShapes

    for (iShape = 0; iShape < unsigned(nWantedShapes); iShape++)
        {
        unsigned iOldShape = iShuffledShapes[iShape];
        if (iShape > 0 && Shapes[0].nrows() != Shapes[iOldShape].nrows())
            {
            static bool fIssuedWarning;
            if (!fIssuedWarning)
                {
                fIssuedWarning = true;
                WarnWithNewLine("different sized shapes (%s has %d rows, %s has %d rows)\n",
                     sGetBasenameFromTag(Tags[0].c_str()), Shapes[0].nrows(),
                     sGetBasenameFromTag(Tags[iOldShape].c_str()), Shapes[iOldShape].nrows());
                }
            }
        Shapes[iShape].assign(Shapes[iOldShape]);
        Tags[iShape] = Tags[iOldShape];
        }
    }
Shapes.resize(nWantedShapes);
Tags.resize(nWantedShapes);
}