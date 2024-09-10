 void Float4Widget::setValue(Vector4f v) {
     comboSlider1->blockSignals(true);
     comboSlider2->blockSignals(true);
     comboSlider3->blockSignals(true);
     comboSlider4->blockSignals(true);
     comboSlider1->setValue(v.x());
     comboSlider2->setValue(v.y());
     comboSlider3->setValue(v.z());
     comboSlider3->setValue(v.w());
     comboSlider1->blockSignals(false);
     comboSlider2->blockSignals(false);
     comboSlider3->blockSignals(false);
     comboSlider4->blockSignals(false);
 }