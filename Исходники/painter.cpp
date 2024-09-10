 void Painter::pushTransform(iXY translate)
 {
     transforms.push(Transform(translate));
     currentTransform += transforms.top();
 }