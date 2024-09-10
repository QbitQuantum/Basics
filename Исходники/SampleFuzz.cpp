static void do_fuzz(SkCanvas* canvas) {
    SkPath path;
    SkPaint paint;
    paint.setAntiAlias(true);

  for (int i=0;i<100;i++) {
  switch (R(33)) {

    case 0:
          paint.setColor(make_fill());
      break;

    case 1:
      paint.setAlpha(gRand.nextU() & 0xFF);
      break;

      case 2: {
          SkXfermode::Mode mode;
          switch (R(3)) {
            case 0: mode = SkXfermode::kSrc_Mode; break;
            case 1: mode = SkXfermode::kXor_Mode; break;
            case 2:
            default:  // silence warning
              mode = SkXfermode::kSrcOver_Mode; break;
          }
          paint.setXfermodeMode(mode);
      }
      break;

    case 3:
      switch (R(2)) {
          case 0: paint.setStrokeCap(SkPaint::kRound_Cap); break;
        case 1: paint.setStrokeCap(SkPaint::kButt_Cap); break;
      }
      break;

    case 4:
      switch (R(2)) {
          case 0: paint.setStrokeJoin(SkPaint::kRound_Join); break;
        case 1: paint.setStrokeJoin(SkPaint::kMiter_Join); break;
      }
      break;

    case 5:
      paint.setStrokeWidth(make_number());
      break;

    case 6:
      paint.setStrokeMiter(make_number());
      break;

    case 7:
      if (quick == true) break;
          SkSafeUnref(paint.setMaskFilter(SkBlurMaskFilter::Create(kNormal_SkBlurStyle,
                                                                   make_number())));
      break;

    case 8:
      if (quick == true) break;
      //ctx.shadowColor = make_fill();
      break;

    case 9:
      if (quick == true) break;
      //ctx.shadowOffsetX = make_number();
      //ctx.shadowOffsetY = make_number();
      break;

    case 10:
      canvas->restore();
      break;

    case 11:
      canvas->rotate(make_number());
      break;

    case 12:
      canvas->save();
      break;

    case 13:
      canvas->scale(-1,-1);
      break;

    case 14:

      if (quick == true) break;

      if (transval == 0) {
        transval = make_number();
        canvas->translate(transval,0);
      } else {
        canvas->translate(-transval,0);
        transval = 0;
      }

      break;

          case 15: {
              SkRect r;
              r.set(make_number(),make_number(),make_number(),make_number());
              SkPaint::Style s = paint.getStyle();
              paint.setStyle(SkPaint::kFill_Style);
              canvas->drawRect(r, paint);
              paint.setStyle(s);
              // clearrect
          } break;

    case 16:
      if (quick == true) break;
//      ctx.drawImage(imgObj,make_number(),make_number(),make_number(),make_number(),make_number(),make_number(),make_number(),make_number());
      break;

          case 17: {
          SkRect r;
          r.set(make_number(),make_number(),make_number(),make_number());
              SkPaint::Style s = paint.getStyle();
              paint.setStyle(SkPaint::kFill_Style);
          canvas->drawRect(r, paint);
              paint.setStyle(s);
          } break;

    case 18:
          path.reset();
      break;

    case 19:
      // ctx.clip() is evil.
      break;

    case 20:
          path.close();
      break;

          case 21: {
          SkPaint::Style s = paint.getStyle();
          paint.setStyle(SkPaint::kFill_Style);
          canvas->drawPath(path, paint);
          paint.setStyle(s);
          } break;

          case 22: {
              SkPaint::Style s = paint.getStyle();
              paint.setStyle(SkPaint::kFill_Style);
              canvas->drawPath(path, paint);
              paint.setStyle(s);
          } break;

          case 23: {
              SkRect r;
              r.set(make_number(),make_number(),make_number(),make_number());
              SkPaint::Style s = paint.getStyle();
              paint.setStyle(SkPaint::kStroke_Style);
              canvas->drawRect(r, paint);
              paint.setStyle(s);
          } break;

    case 24:
      if (quick == true) break;
      //ctx.arc(make_number(),make_number(),make_number(),make_number(),make_number(),true);
      break;

    case 25:
      if (quick == true) break;
      //ctx.arcTo(make_number(),make_number(),make_number(),make_number(),make_number());
      break;

    case 26:
      if (quick == true) break;
      //ctx.bezierCurveTo(make_number(),make_number(),make_number(),make_number(),make_number(),make_number());
      break;

    case 27:
      path.lineTo(make_number(),make_number());
      break;

    case 28:
      path.moveTo(make_number(),make_number());
      break;

    case 29:
      if (quick == true) break;
      path.quadTo(make_number(),make_number(),make_number(),make_number());
      break;

          case 30: {
      if (quick == true) break;
              SkMatrix matrix;
      set2x3(&matrix, make_number(),make_number(),make_number(),make_number(),make_number(),make_number());
              canvas->concat(matrix);
          } break;

          case 31: {
      if (quick == true) break;
          SkMatrix matrix;
          set2x3(&matrix, make_number(),make_number(),make_number(),make_number(),make_number(),make_number());
          canvas->setMatrix(matrix);
          } break;

    case 32:

      if (scale_large == true) {

        switch (scval) {
          case 0: canvas->scale(-1000000000,1);
                  canvas->scale(-1000000000,1);
                  scval = 1; break;
          case 1: canvas->scale(-.000000001f,1); scval = 2; break;
          case 2: canvas->scale(-.000000001f,1); scval = 0; break;
        }

      }

      break;



  }
  }

}