WorkerObject::~WorkerObject()
{
    shutDown();
    delete d;
}