#include <iostream>
#include <fstream>
#include <thread>
#include <string>

using namespace std;

long getFileSize(const string& filename) {
    ifstream file(filename, ios::binary | ios::ate);
    if (!file.is_open()) {
        return -1;
    }
    return file.tellg();
}

string readFileContents(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return "";
    }
    string contents((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    return contents;
}

int main() {
    setlocale(LC_ALL, "rus");
    string filename = "C:/Users/Andrew/Desktop/test.txt";

    long last_size = getFileSize(filename);
    string last_content = readFileContents(filename);

    if (last_size == -1) {
        cerr << "Ошибка: файл не найден!" << endl;
        return 1;
    }

    cout << "Начальный размер файла: " << last_size << " байт" << endl;

    while (true) {
        long current_size = getFileSize(filename);
        string current_content = readFileContents(filename);

        if (current_size != last_size) {
            cout << "Файл изменился! Новый размер: " << current_size << " байт" << endl;

            if (current_content.size() > last_content.size()) {
                cout << "Добавлено: " << current_content.substr(last_content.size()) << endl;
            }
            else if (current_content.size() < last_content.size()) {
                cout << "Удалено: " << last_content.substr(current_content.size()) << endl;
            }

            last_size = current_size;
            last_content = current_content;
        }

        this_thread::sleep_for(chrono::milliseconds(500));
    }

    return 0;
}
