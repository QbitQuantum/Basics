void WorkerList::addWorker(boost::shared_ptr<ClientSocket> socket) {
    list.push_back(socket);
    socket->send("Mandelbrot");
    socket->send("50.0 30 \t -2.5 -1.25 1.0 1.25 0.25 0.25");
}