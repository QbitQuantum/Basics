    /**
     * @todo パフォーマンス悪いので改善する。
     * 例えば、以下の改善策がある。
     * (1) 矩形内にアイテムが一つもなかった場合は、特に何もしない
     */
    void PianorollTrackView::updateSelectedItem() {
        const VSQ_NS::Sequence *sequence = controllerAdapter->getSequence();
        if (!sequence) {
            return;
        }

        // 選択状態を最初の状態に戻す
        ItemSelectionManager *manager = controllerAdapter->getItemSelectionManager();
        manager->revertSelectionStatusTo(mouseStatus.itemSelectionStatusAtFirst);

        // 矩形に入っているアイテムを、選択状態とする。
        // ただし、矩形選択直前に選択状態となっているものは選択状態を解除する
        QRect rect = mouseStatus.rect();
        const VSQ_NS::Event::List *list = sequence->track(trackIndex)->events();
        int count = list->size();
        std::set<const VSQ_NS::Event *> add;
        std::set<const VSQ_NS::Event *> remove;
        for (int i = 0; i < count; i++) {
            const VSQ_NS::Event *item = list->get(i);
            if (item->type != VSQ_NS::EventType::NOTE) continue;
            QRect itemRect = getNoteItemRect(item);
            if (itemRect.right() < rect.left()) continue;
            if (rect.right() < itemRect.left()) break;

            if (rect.intersects(itemRect)) {
                if (mouseStatus.itemSelectionStatusAtFirst.isContains(item)) {
                    remove.insert(item);
                } else {
                    add.insert(item);
                }
            }
        }
        manager->add(add);
        manager->remove(remove);
    }