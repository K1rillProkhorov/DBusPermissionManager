# DBus Permission Manager
**DBus Permission Manager** - DBus сервис предназначенный для управления разрешениями.

## Структура проекта
- `PermissionService(com.system.permissions)` - Сервис для выполнения запроса разрешение и проверки наличия определённого разрешения.
- `TimeService(com.system.time)` - Сервис для получения системного времени.
- `Application` - Приложение, которые обращается к `com.system.time` для получения системного времени, в случае отказа в разрешении, обращается к `com.system.permissions` для запроса разрешения.

## Сборка проекта
Для сборки используется `qmake`.\
Перед сборкой нужно установить `qt5-qmake` и `qtdeclarative5-dev`.
```
sudo apt install qt5-qmake qtdeclarative5-dev
```
**Два варианта сборки:**
1. *Сборка в ручную каждого `.pro` файла*.
    ```
    cd ./src/ProjectFolder
    qmake ProjectName.pro
    make
    ```
2. *Сборка при помощи `build_file` файла*.
   ```
   chmod +x ./build_file
   ./build_file
   ```
В результате сборки создастся папка *build* в которой будут находится 3 исполняемых файла.
## Использование PermissionService
Переходим в папку *build* и запускаем файл *Permission*.\
Сервис подключается к *sessionBus* по имени `com.system.permissions`, его функционал представляется двумя методами:
- `void RequestPermission(permissionEnumCode: int)` - выдается разрешение запрашиваемому приложению, в случае корректного запроса, в случае ошибки - возвращает ошибку.\
  **Пример использования:**
  ```
  gdbus call -e -d com.system.permissions -o / -m com.system.permissions.RequestPermission 0
  ```
- `bool CheckApplicationHasPermission(applicationExecPath: String, permissionEnumCode: int)` - возвращает *true* в случае наличия разрешения у приложения и *false* - в случае отсутствия, в случае ошибки - возвращает ошибку.\
  **Пример использования:**
  ```
  gdbus call -e -d com.system.permissions -o / -m com.system.permissions.CheckApplicationHasPermission /usr/bin/com.example.example 0
  ```
## Использование TimeService
Переходим в папку *build* запускаем файл и *Time*, предварительно должен быть запущен `PermissionService`.\
Сервис подключается к sessionBus по имени `com.system.time`, уго функционал представляется одним методом:
- `uint64 GetSystemTime()` - возвращает текущее системное время в милисекундах в случае наличия разрешения на просмотр системного времени (`permissionEnumCode = 0`) у вызвавшего приложения, в случае отсутствия прав - возвращает ошибку `Access denied` и сообщение `Unauthorized Access`, в случае ошибку - возвращает ошибку.\
  **Пример использования**
  ```
  gdbus call -e -d com.system.time -o / -m com.system.time.GetSystemTime
  ```
## Использование Application
Переходим в папку *build* запускае файл *Application*, предварительно должны быть запущены `PermissionService` и `TimeService`.
Приложение обращается к `com.system.time` и выводит текущее время в стандарте *ISO 8601* при условии, что у приложения имеется разрешения на просмотр системного времени, в случае отсутствия данного разрешения - обращается к `com.system.permissions` для получения разрешения и выводит время, если разрешения было получено.