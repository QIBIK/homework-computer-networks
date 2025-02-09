#include <iostream>
#include <fstream>
#include <thread>

using namespace std;

long getFileSize(const string& filename) {
    ifstream file(filename, ios::binary | ios::ate); // Открываем файл в бинарном режиме и переводим каретку в конец
    if (!file.is_open()) { // Проверяем, открыт ли файл
        return -1;
    }
    return file.tellg(); // Возвращаем текующую позицию курсора и это будет наш размера файла
}

int main() {
    setlocale(LC_ALL, "rus");
    string filename = "test.txt";

    long last_size = getFileSize(filename);
    if (last_size == -1) {
        cerr << "Ошибка: файл не найден!" << endl;
        return 1;
    }

    cout << "Начальный размер файла: " << last_size << " байт" << endl;

    while (true) {
        long current_size = getFileSize(filename);
        if (current_size != last_size) {
            cout << "Файл изменился! Новый размер: " << current_size << " байт" << endl;
            last_size = current_size;
        }
        this_thread::sleep_for(chrono::milliseconds(500)); // Проверка каждые 500 мс
    }

    return 0;
}
