#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int shared_data = 0;
mutex mtx;

void writer_thread() {
    for (int i = 0; i < 100; ++i) {
        mtx.lock();
        shared_data++;
        cout << "Writer: " << shared_data << endl;
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // 10 ms
    }
}

void reader_thread() {
    for (int i = 0; i < 100; ++i) {
        mtx.lock();
        int value = shared_data;
        cout << "Reader: " << value << endl;
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Задержка 10 ms
    }
}

int main() {
    thread writer(writer_thread);
    thread reader(reader_thread);

    writer.join();
    reader.join();

    return 0;
}
