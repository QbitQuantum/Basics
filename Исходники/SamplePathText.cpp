 void onDrawContent(SkCanvas* canvas) override {
     if (fDoClip) {
         SkPath deviceSpaceClipPath = fClipPath;
         deviceSpaceClipPath.transform(SkMatrix::MakeScale(this->width(), this->height()));
         canvas->save();
         canvas->clipPath(deviceSpaceClipPath, SkClipOp::kDifference, true);
         canvas->clear(SK_ColorBLACK);
         canvas->restore();
         canvas->clipPath(deviceSpaceClipPath, SkClipOp::kIntersect, true);
     }
     this->drawGlyphs(canvas);
 }