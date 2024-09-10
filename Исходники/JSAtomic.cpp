static int js_atomic_destroy(duk_context* ctx)
{
    if (!duk_is_object(ctx, 0))
        return 0;

    Object* obj = js_to_class_instance<Object>(ctx, 0, 0);

    if (!obj)
        return 0;

    JSVM* vm = JSVM::GetJSVM(ctx);

    if (obj->GetType() == Node::GetTypeStatic())
    {

        Node* node = (Node*) obj;

        if (node->JSGetHeapPtr())
        {
            int top = duk_get_top(ctx);
            duk_push_global_stash(ctx);
            duk_get_prop_index(ctx, -1, JS_GLOBALSTASH_INDEX_NODE_REGISTRY);
            duk_push_pointer(ctx, node->JSGetHeapPtr());
            duk_del_prop(ctx, -2);
            duk_pop_2(ctx);
            assert(top = duk_get_top(ctx));
        }

        const Vector<SharedPtr<Component> >& components = node->GetComponents();

        for (unsigned i = 0; i < components.Size(); i++)
        {
             Component* component = components[i];

             if (component->GetType() == JSComponent::GetTypeStatic())
             {
                 JSComponent* jscomponent = (JSComponent*) component;
                 jscomponent->SetDestroyed();
             }

             component->UnsubscribeFromAllEvents();
        }

        node->RemoveAllComponents();
        node->UnsubscribeFromAllEvents();

        assert(node->Refs() >= 2);

        node->Remove();

        return 0;
    }
    else if (obj->GetType() == JSComponent::GetTypeStatic())
    {
        assert(0);
        JSComponent* component = (JSComponent*) obj;
        component->UnsubscribeFromAllEvents();
        component->Remove();
        return 0;
    }

    return 0;
}