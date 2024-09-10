EXPORT_C TBool CAknAnimationData::DrawNextAnimationStep(CBitmapContext& aGc)
{
    if (Count() == 0)
    {
        // Call the user animation step
        TAnimStep step;
        TAnimMultiStep nullStep(step);
        nullStep.iDrawStep.SetType(EAnimNullStep);
        nullStep.iSubStep = (TUint16)iCurrentDrawStep;
        TBool done = DrawUserAnimationStep(aGc, nullStep);
        iCurrentDrawStep++;
        return done;
    }

    if (iCurrentDrawStep < Count())
    {
        TInt drawSteps = (*iDrawStepsPerAnimStep)[iCurrentAnimStep];
        TInt startingDrawStep = iCurrentDrawStep;
        TBool repeatAnimStep = EFalse;

        for (TInt ii=0; ii<drawSteps; ii++)
        {
            TAnimStep* drawStep = &(At(iCurrentDrawStep));

            switch (drawStep->Type())
            {
            case EAnimBlitPreviousView:
            {
                TAnimBlitStep* step = drawStep->BlitStep();
                aGc.BitBlt(TPoint(step->iDestX, step->iDestY), iOldBitmap);
            }
            break;
            case EAnimBlitNewView:
            {
                TAnimBlitStep* step = drawStep->BlitStep();
                aGc.BitBlt(TPoint(step->iDestX, step->iDestY), iViewBitmap);
            }
            break;
            case EAnimBlitPartPreviousView:
            {
                TAnimBlitStep* step = drawStep->BlitStep();
                aGc.BitBlt(TPoint(step->iDestX, step->iDestY), iOldBitmap,
                           TRect(TPoint(step->iSrcX, step->iSrcY), TSize(step->iWidth, step->iHeight)));
            }
            break;
            case EAnimBlitPartNewView:
            {
                TAnimBlitStep* step = drawStep->BlitStep();
                aGc.BitBlt(TPoint(step->iDestX, step->iDestY), iViewBitmap,
                           TRect(TPoint(step->iSrcX, step->iSrcY), TSize(step->iWidth, step->iHeight)));
            }
            break;
            case EAnimDrawLine:
            case EAnimRevealPartNewViewFromLeft:
            case EAnimRevealPartNewViewFromRight:
            case EAnimRevealPartNewViewFromTop:
            case EAnimRevealPartNewViewFromBottom:
            case EAnimBlitSlideNewView:
            case EAnimBlitSlideNewViewClearBehind:
            {
                // Make this a pending step. Cancel the animation if the append fails
                TRAPD(err, iPendingSteps->AppendL(TAnimMultiStep(*drawStep)));
                if (err != KErrNone)
                    return ETrue;
            }
            break;
            case EAnimSetColor:
            {
                TAnimSetColorStep* step = drawStep->SetColorStep();
                iDrawColor = TRgb(step->iRed, step->iGreen, step->iBlue);
            }
            break;
            case EAnimDrawRect:
            {
                TAnimLineDrawStep* step = drawStep->LineDrawStep();
                aGc.SetPenColor(iDrawColor);
                aGc.SetPenStyle(CGraphicsContext::ESolidPen);
                aGc.DrawRect(TRect(TPoint(step->iStartX, step->iStartY),TPoint(step->iEndX, step->iEndY)));
            }
            break;
            case EAnimDrawFilledRect:
            {
                TAnimLineDrawStep* step = drawStep->LineDrawStep();
                aGc.SetBrushColor(iDrawColor);
                aGc.SetBrushStyle(CGraphicsContext::ESolidBrush);
                aGc.SetPenStyle(CGraphicsContext::ENullPen);
                aGc.DrawRect(TRect(TPoint(step->iStartX, step->iStartY),TPoint(step->iEndX, step->iEndY)));
            }
            break;
            case EAnimWait:
            {
                TAnimWaitStep* step = drawStep->WaitStep();
                repeatAnimStep = ETrue;
                if (step->iSteps > 0)
                {
                    step->iSteps--;
                    if (step->iSteps == 0)
                        repeatAnimStep = EFalse;
                }
            }
            break;
            case EAnimWaitUntilComplete:
                if (iPendingSteps->Count())
                    repeatAnimStep = ETrue;
                break;
            default:
                // Type is user-defined, so add to the pending steps
                TRAPD(err, iPendingSteps->AppendL(TAnimMultiStep(*drawStep)));
                if (err != KErrNone)
                    return ETrue;
                break;
            }
            iCurrentDrawStep++;
        }

        // If this step needs to be repeated, reset the draw step counter
        // otherwise increment the current animation step
        if (repeatAnimStep)
        {
            iCurrentDrawStep = startingDrawStep;
        }
        else
        {
            iCurrentAnimStep++;
        }
    }


    TInt done = DrawPendingAnimationSteps(aGc);

    if (iCurrentDrawStep == Count() && done)
        return ETrue;

    return EFalse;
}