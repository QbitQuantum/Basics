TTaskResult CBeep::Execute(CRobot * Robot, CExecutableRWGraphicObjectList * ExecutableObjectList, bool & result)
{
    if (Robot->GetSoftwareRevision() <= 1.06)   /*Do the tune as beeps for robots before version 1.07*/
    {
        Robot->AddBeepToInstructions(GetFrequency(), GetDuration());
        CFlowZap *FZ = (CFlowZap*)m_fc;
        CBeep* LastBeep = this;
        CInstruction *Next = FZ->GetNextInstructionInList(this);

        //	Next = FZ->GetNextExecutableInstruction(Next);
        while (Next->IsKindOf(RUNTIME_CLASS(CBeep)))
        {
            LastBeep = (CBeep*)Next;
            Robot->AddBeepToInstructions(LastBeep->GetFrequency(), LastBeep->GetDuration());
            Next = FZ->GetNextInstructionInList(Next);
            //		Next = FZ->GetNextExecutableInstruction(Next);
        }

        FZ->SetCueToInstruction(LastBeep);
        FZ->RedrawWindow();
    }
    else
    {
        unsigned int NumberOfNotes = 1;
        CArray<short, short> FrequencyList;
        FrequencyList.SetSize(20, 20);
        CArray<int, int> DurationList;
        DurationList.SetSize(20, 20);
        FrequencyList[0] = GetFrequency();
        DurationList[0] = GetDuration();
        CFlowZap *FZ = (CFlowZap*)m_fc;
        CBeep* LastBeep = this;
        CInstruction *Next = FZ->GetNextInstructionInList(this);

        //	Next = FZ->GetNextExecutableInstruction(Next);
        while (Next->IsKindOf(RUNTIME_CLASS(CBeep)))
        {
            LastBeep = (CBeep*)Next;
            FrequencyList[NumberOfNotes] = LastBeep->GetFrequency();
            DurationList[NumberOfNotes] = LastBeep->GetDuration();
            NumberOfNotes++;
            Next = FZ->GetNextInstructionInList(Next);
            //		Next = FZ->GetNextExecutableInstruction(Next);
        }

        FrequencyList[NumberOfNotes] = -1;
        DurationList[NumberOfNotes] = 0;
        NumberOfNotes++;
        Robot->AddTuneToInstructions(FrequencyList.GetData(), DurationList.GetData(), NumberOfNotes);

        FZ->SetCueToInstruction(LastBeep);
        FZ->RedrawWindow();
    }

    TTaskResult TaskResult;
    TaskResult = Robot->FollowInstructions(true, true, IR_InstructionComplete);
    return TaskResult;
}