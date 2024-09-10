TaskList XmlSerializationTests::tasksToTest()
{
    // set up test candidates:
    TaskList tasks;
    Task task;
    task.setName( "A task" );
    task.setId( 42 );
    task.setParent( 4711 );
    task.setSubscribed( true );
    task.setValidFrom( QDateTime::currentDateTime() );
    Task task2;
    task2.setName( "Another task" );
    task2.setId( -1 );
    task2.setParent( 1000000000 );
    task2.setSubscribed( false );
    task2.setValidUntil( QDateTime::currentDateTime() );
    Task task3;

    tasks << Task() << task << task2;
    return tasks;
}