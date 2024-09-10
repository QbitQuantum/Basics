 void DequeueResponse(Message &aMessage)
 {
     mQueue.Dequeue(aMessage);
     aMessage.Free();
 }