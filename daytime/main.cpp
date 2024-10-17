#include <iostream>
#include <cstdlib>  // exit() - для закрытия программы
#include <cstring>  // strcpy() - для копирования строки, strlen() - для определения длины строки
#include <unistd.h> // close() - для закрытия сокета
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

void errHandler(const char *why, int exitCode = 1) {
    cerr << why << endl;
    exit(exitCode);
}

int main() {
    // Структура с адресом (клиент)
    sockaddr_in selfAddr{};
    selfAddr.sin_family = AF_INET; 
    selfAddr.sin_port = 0; // Локальный порт может быть 0 (выбор системы)
    selfAddr.sin_addr.s_addr = INADDR_ANY; // Любой локальный адрес

    // Структура с адресом (сервер)
    sockaddr_in remoteAddr{};
    remoteAddr.sin_family = AF_INET;
    remoteAddr.sin_port = htons(12345); // Используйте нужный порт сервера
    remoteAddr.sin_addr.s_addr = inet_addr("172.16.40.1"); // IP-адрес сервера

    // Буфер обмена для передачи и приема данных
    char buf[256];
    strcpy(buf, "Жижлик - Это Георгий Бусыгин"); // Копируем строку
    int msgLen = strlen(buf); // Вычисляем длину строки

    // Создание сокета
    int mySocket = socket(AF_INET, SOCK_STREAM, 0);
    if (mySocket == -1) {
        errHandler("Error opening socket", 11);
    }

    // Связывание сокета с адресом
    if (bind(mySocket, (const sockaddr*)&selfAddr, sizeof(sockaddr_in)) == -1) {
        close(mySocket);
        errHandler("Error binding socket to local address", 12);
    }

    // Установка соединения
    if (connect(mySocket, (const sockaddr*)&remoteAddr, sizeof(sockaddr_in)) == -1) {
        close(mySocket);
        errHandler("Error connecting socket to remote server", 13);
    }

    // Передача данных
    if (send(mySocket, buf, msgLen, 0) == -1) {
        close(mySocket);
        errHandler("Error sending message", 14);
    }
    cout << "Жижа " << buf << endl;

    // Прием данных
    int bytesReceived = recv(mySocket, buf, sizeof(buf) - 1, 0);
    if (bytesReceived == -1) {
        close(mySocket);
        errHandler("Error receiving answer", 15);
    }
    
    buf[bytesReceived] = '0'; // Завершаем строку нулевым символом
    cout << "Жижлик " << buf << endl;

    // Закрытие сокета
    close(mySocket);

    return 0;
}
