void ReentrantLock::lock() 
{
    // Если текущий фибер уже владеет блокировкой, 
    // то увеличиваем счетчик, иначе ожидаем освобождения блокировки.
    if (owner == GetCurrentFiber()) {
        holdCount++;
    } else {
        SimpleLock::lock();
        initNewOwner();
    }
}