int main ()
{
  printf ("Results of animation2_test:\n");
  
  try
  {  
    AnimationManager manager;
    
    manager.LoadResource ("data/test.xanim");

    Node::Pointer node = Node::Create (), target1 = Node::Create (), target2 = Node::Create ();
    
    target1->SetName ("target1");
    target2->SetName ("target2");

    target1->BindToParent (*node);
    target2->BindToParent (*node);

    Animation animation = manager.PlayAnimation ("animation1", *node, &event_handler);
    
    animation.RegisterEventHandler (AnimationEvent_OnPlay, &event_handler);
    animation.RegisterEventHandler (AnimationEvent_OnPause, &event_handler);
    animation.RegisterEventHandler (AnimationEvent_OnStop, &event_handler);
    animation.RegisterEventHandler (AnimationEvent_OnUpdate, &event_handler);
    animation.RegisterEventHandler (AnimationEvent_OnDestroy, &event_handler);
    
    printf ("animation duration: %.2f\n", animation.Duration ());

    node->Update (TimeValue (2, 1));
    node->Update (TimeValue (3, 1));
    
    animation.Pause ();
    animation.Pause ();
    
    node->Update (TimeValue (4, 1));
    
    printf ("animation offset %.2f\n", animation.Tell ());
    
    animation.Play ();
    animation.Play ();
    
    node->Update (TimeValue (5, 1));
    
    printf ("animation offset %.2f\n", animation.Tell ());    
    
    animation.Stop ();
    
    node->Update (TimeValue (6, 1));    
    
    printf ("animation offset %.2f\n", animation.Tell ());
  }
  catch (std::exception& e)
  {
    printf ("%s\n", e.what ());
  }

  return 0;
}