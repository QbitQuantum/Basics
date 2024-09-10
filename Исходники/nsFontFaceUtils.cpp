/* static */ void
nsFontFaceUtils::MarkDirtyForFontChange(nsIFrame* aSubtreeRoot,
                                        const gfxUserFontEntry* aFont)
{
  AutoTArray<nsIFrame*, 4> subtrees;
  subtrees.AppendElement(aSubtreeRoot);

  nsIPresShell* ps = aSubtreeRoot->PresContext()->PresShell();

  // check descendants, iterating over subtrees that may include
  // additional subtrees associated with placeholders
  do {
    nsIFrame* subtreeRoot = subtrees.ElementAt(subtrees.Length() - 1);
    subtrees.RemoveElementAt(subtrees.Length() - 1);

    // Check all descendants to see if they use the font
    AutoTArray<nsIFrame*, 32> stack;
    stack.AppendElement(subtreeRoot);

    do {
      nsIFrame* f = stack.ElementAt(stack.Length() - 1);
      stack.RemoveElementAt(stack.Length() - 1);

      // if this frame uses the font, mark its descendants dirty
      // and skip checking its children
      if (FrameUsesFont(f, aFont)) {
        ScheduleReflow(ps, f);
      } else {
        if (f->GetType() == nsGkAtoms::placeholderFrame) {
          nsIFrame* oof = nsPlaceholderFrame::GetRealFrameForPlaceholder(f);
          if (!nsLayoutUtils::IsProperAncestorFrame(subtreeRoot, oof)) {
            // We have another distinct subtree we need to mark.
            subtrees.AppendElement(oof);
          }
        }

        nsIFrame::ChildListIterator lists(f);
        for (; !lists.IsDone(); lists.Next()) {
          nsFrameList::Enumerator childFrames(lists.CurrentList());
          for (; !childFrames.AtEnd(); childFrames.Next()) {
            nsIFrame* kid = childFrames.get();
            stack.AppendElement(kid);
          }
        }
      }
    } while (!stack.IsEmpty());
  } while (!subtrees.IsEmpty());
}