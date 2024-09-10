void
RenamePickLabelAction::Execute()
{
    GetWindow()->RenamePickLabel(args.GetStringArg1(), args.GetStringArg2());
}