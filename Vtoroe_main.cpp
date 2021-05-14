#include <iostream>
#include <string>
#include <cstdlib> //exit()
#include <cstring> // strpy()
#include <unistd.h> //close()
#include <netinet/in.h> 
#include <arpa/inet.h>
использование пространства имен std;
void Exception(const string & why, const int exitCode ) // Исключения (возможные ошибки)
{
 cout << "ErrorCode:"<<ExitCode <<endl<< why <;
    exit(ExitCode);
}
int main()
{
    
    // структура с адресом нашей программы (клиента)
 sockaddr_in * selfAddr = new (sockaddr_in);
 selfAddr->sin_family = AF_INET; // интернет протокол IPv4
 selfAddr->sin_port = 0; // любой порт на усмотрение ОС
 selfAddr->sin_addr.s_addr = 0; 

    // структура с адресом "на той стороне" (сервера)
 sockaddr_in * remoteAddr = new (sockaddr_in);
 remoteAddr->sin_family = AF_INET; // интернет протокол IPv4
 remoteAddr->>sin_port = htons(7); // порт 7
 remoteAddr->sin_addr.s_addr = inet_addr("82.179.90.12"); // адрес 
    
    // буфер для передачи и приема данных
    char *buffer = новый char[4096];
    strcpy(буфер,"Привет, Мир, меня зовут Некит!"); //копируем строку
    int msgLen = strlen(buffer); //вычисляем длину строки
   
    // создаём сокет
    int mySocket = socket(AF_INET, SOCK_STREAM, 0); //tcp протокол
    если (mySocket == -1) {
        закрыть(mySocket);
        Исключение("Ошибка открытого сокета",11);
    }
    //связываем сокет с адрессом
    int rc = bind(mySocket,(const sockaddr *) selfAddr, sizeof(sockaddr_in));
    если (rc == -1) {
        закрыть(mySocket);
        Исключение("Ошибка привязки сокета с локальным адресом",12);
        }

    //установливаем соединение
 rc = connect(mySocket, (const sockaddr*) remoteAddr, sizeof(sockaddr_in));
    если (rc == -1) {
        закрыть(mySocket);
        Исключение("Ошибка подключения сокета к удаленному серверу", 13);
    }

    // передаём сообщение из буффера
 rc = send(mySocket, buffer, msgLen, 0);
    если (rc == -1) {
        закрыть(mySocket);
        Исключение("Сообщение об ошибке отправки", 14);
    }
 cout << "Мы посылаем:" << буфер <; 
      
    // принимаем ответ в буффер
 rc = recv(mySocket, буфер, 4096, 0);
    if (rc == -1) {
        закрыть(mySocket);
       Исключение("Ошибка получения ответа", 15);
    }
    buffer[rc] = '\0'; // конец принятой строки
    cout << "We receive: " << buffer << endl; // вывод полученного сообщения от сервера
    // закрыем сокет
    close(mySocket);

    delete selfAddr;
    delete remoteAddr;
    delete[] buffer;
    return 0
