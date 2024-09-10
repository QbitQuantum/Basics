// ---------------------------------------------------------------------------
// CFepUiLayoutRootCtrl::IsValidDestination
// Test whether the rect conflicts with other controls
// (other items were commented in a header).
// ---------------------------------------------------------------------------
//    
TBool CFepUiLayoutRootCtrl::IsValidDestination(const TRect& aRect,
                                               CDragBar* aDragBar,
                                               TBool& aVInfo,
                                               TBool& aHInfo)
    {    
    aVInfo = EFalse;
    aHInfo = EFalse;
    if(!Rect().Contains(aRect.iTl) || !Rect().Contains(aRect.iBr)) //outside of the ui layout
        return EFalse;   
     
    CFepUiBaseCtrl* ctrl;

    for(TInt i = iCtrlList.Count()-1; i >= 0;i--)
        {
        ctrl = iCtrlList[i];            
        TBool bIsDragingComponent = EFalse;
        if(aDragBar)
            {
            if(aDragBar->IsDraggingComponent(ctrl))
                bIsDragingComponent = ETrue;
            }
  
        
        if(!bIsDragingComponent && aRect.Intersects(ctrl->Rect()))   //conflicts with others
            {
            //is the control one of the dragbar component.
           
            if(!ctrl->AllowOverlap()) 
                {                    
                //if the control not allow overlapping, then it's invalid pos
                return EFalse;
                }
                
            }
        }
    
    return ETrue;
}    