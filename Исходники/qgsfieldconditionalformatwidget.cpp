QList<QgsConditionalStyle> QgsFieldConditionalFormatWidget::defaultPresets() const
{
  QList<QgsConditionalStyle> styles;
  QgsConditionalStyle style = QgsConditionalStyle();
  style.setBackgroundColor( QColor( 154, 216, 113 ) );
  styles.append( style );
  style = QgsConditionalStyle();
  style.setBackgroundColor( QColor( 251, 193, 78 ) );
  styles.append( style );
  style = QgsConditionalStyle();
  style.setBackgroundColor( QColor( 251, 154, 153 ) );
  styles.append( style );
  style = QgsConditionalStyle();
  style.setTextColor( QColor( 154, 216, 113 ) );
  styles.append( style );
  style = QgsConditionalStyle();
  style.setTextColor( QColor( 251, 193, 78 ) );
  styles.append( style );
  style = QgsConditionalStyle();
  style.setTextColor( QColor( 251, 154, 153 ) );
  styles.append( style );
  return styles;
}