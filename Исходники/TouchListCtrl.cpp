/**
 * DrawItemFocusRect()
 *
 * 指定されたアイテムにフォーカス矩形を表示する
 * ・XORで描画するので2回呼べば矩形を消す
 *   ここは描画か消去か意識できないので呼び出し側で管理すること
 * ・アイテムがスクロールされたら消される
 *
 */
void CTouchListCtrl::DrawItemFocusRect( const int nItem )
{
	CRect rcItem;
	GetItemRect( nItem , rcItem , LVIR_BOUNDS);
	CDC* pdc = GetDC();
	pdc->DrawFocusRect( rcItem );
	ReleaseDC(pdc);
}