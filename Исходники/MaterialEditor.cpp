void MaterialEditor::renderConnection(Connection* connection)
{
   NVGcontext* vg = Link.Graphics.dglGetNVGContext();
	if (vg)
	{
      Point2F mStart;
      Point2F mEnd;

      if ( connection->outputToMouse )
         mEnd.set(lastMousePoint.x, lastMousePoint.y);
      else {
         Node* endNode = findNode(connection->inputNodeName);
         if ( !endNode || connection->inputIndex >= endNode->inputs.size() ) 
            return;
         mEnd.set(endNode->inputs[connection->inputIndex].lastPosition.x, endNode->inputs[connection->inputIndex].lastPosition.y);
      }

      if ( connection->inputToMouse )
         mStart.set(lastMousePoint.x, lastMousePoint.y);
      else {
         Node* startNode = findNode(connection->outputNodeName);
         if ( !startNode || connection->outputIndex >= startNode->outputs.size() ) 
            return;
         mStart.set(startNode->outputs[connection->outputIndex].lastPosition.x, startNode->outputs[connection->outputIndex].lastPosition.y);
      }

      Point2F mControlPointA(mStart.x + 50, mStart.y);
      Point2F mControlPointB(mEnd.x - 50, mEnd.y);

      F32 diff = (mEnd.y - mStart.y) * 0.25f;
      mControlPointA.y -= diff;
      mControlPointB.y += diff;

		Link.NanoVG.nvgBeginPath(vg);
		Link.NanoVG.nvgMoveTo(vg, mStart.x, mStart.y);
		Link.NanoVG.nvgBezierTo(vg, mControlPointA.x, mControlPointA.y, 
                                  mControlPointB.x, mControlPointB.y, 
                                  mEnd.x, mEnd.y);
		Link.NanoVG.nvgStrokeColor(vg, Link.NanoVG.nvgRGBA(255, 255, 255, 200));
		Link.NanoVG.nvgStrokeWidth(vg, 5.0f);
		Link.NanoVG.nvgStroke(vg);
   }
}