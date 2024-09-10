void WebProcessTest::assertObjectIsDeletedWhenTestFinishes(GObject* object)
{
    s_watchedObjects.add(object);
    g_object_weak_ref(object, [](gpointer, GObject* finalizedObject) {
        s_watchedObjects.remove(finalizedObject);
    }, nullptr);
}