void grabVertexDown(int x, int y)
{
  int mods = glutGetModifiers();
  ETexMesh::Vertex *v = pickVertex(x,y);
  
  //Clear selection if clicked out
  if (v == NULL) {
    clearSelection();
    return;
  }

  //Is shift key pressed?
  if (mods & GLUT_ACTIVE_SHIFT) {

    //Toggle vertex selection
    if (!v->selected) {
      v->selected = true;
      selection.pushBack(v);
    }else{
      v->selected = false;
      selection.remove(v);
    }

  }else{

    //Switch to single vertex if unselected
    if (!v->selected) {
      clearSelection();
      selectVertex(v); }
  }
}