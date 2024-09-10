void TextView::Interpret (Command* cmd) {
    if (cmd->IsA(ALIGNTOGRID_CMD)) {
        Transformer total;
        GetGraphic()->TotalTransformation(total);

        float tx0, ty0;
        total.Transform(0., 0., tx0, ty0);
        ((AlignToGridCmd*) cmd)->Align(this, tx0, ty0);

    } else {
        GraphicView::Interpret(cmd);
    }
}