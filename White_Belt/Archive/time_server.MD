
Вам дана функция string AskTimeServer(), про которую известно следующее:

-   в процессе своей работы она обращается по сети к удалённому серверу, запрашивая текущее время;
-   если обращение к серверу прошло успешно, функция возвращает текущее время в виде строки;
-   если в процессе обращения к серверу возникла сетевая проблема, функция выбрасывает исключение system_error;
-   функция может выбрасывать другие исключения, чтобы сообщить о других проблемах.

Используя функцию AskTimeServer, напишите класс TimeServer со следующим интерфейсом:

    class TimeServer {
    public:
      string GetCurrentTime();
    private:
      string last_fetched_time = "00:00:00";
    };

Метод GetCurrentTime должен вести себя так:

-   он должен вызвать функцию AskTimeServer, записать её результат в поле last_fetched_time и вернуть значение этого поля;
-   если AskTimeServer выбросила исключение system_error, метод GetCurrentTime должен его поймать и вернуть текущее значение поля last_fetched_time. Таким образом мы скрываем от пользователя сетевые проблемы, возвращая значение, которое было получено при последнем успешном обращении к серверу;
-   если AskTimeServer выбросила другое исключение, метод GetCurrentTime должен пробросить его дальше, потому что в рамках класса TimeServer мы не знаем, как обрабатывать проблемы, не связанные со сбоями сети.

## Как выполнять задание

Вам дан файл, содержащий заготовку класса TimeServer. В нём вам надо реализовать метод GetCurrentTime так, как описано выше. Файл содержит пустую функцию AskTimeServer. Для тестирования своей реализации вы можете пробовать добавлять разные команды в её тело:

-   возврат строки;
-   выброс исключения system_error (класс system_error принимает в конструкторе параметр типа error_code, поэтому самый простой способ выбросить это исключение — throw system_error(error_code());, подробнее см.  [https://en.cppreference.com/w/cpp/error/system_error](https://en.cppreference.com/w/cpp/error/system_error)  );
-   выброс других исключений.

[time_server.cpp](https://d3c33hcgiwev3.cloudfront.net/kjUumNJWEem1wRICcqBpcA_a5ec3a928d2e4d4e90c110498ea0fce4_time_server.cpp?Expires=1596240000&Signature=iUw3R84E7wmuFZD68Q~Iov98xbEBR4T3w9fz27LT1Yr3JATfu5fyWrjZGY~XRyeCxHFk8AWRGY0512TFlEh~Pe84MhBocksLZbik4M6zprodLWqrdHbZJiUykkssORNlpLI3ue3k60i2IZmB3x4d59k6OOtoexPUwUHyV-BYGHg_&Key-Pair-Id=APKAJLTNE6QMUY6HBC5A)

