# IDE. Cmake.

## VS Code

В сравнении с другими популярными аналогами выделяется:
* Простотой настройки remote developing
* Легковесность
* Большой магазин плагинов под разработку для различных языков, например, я в VS code пишу под C++, Python, Go, Rust

Полезные ссылки: 
* [Гайд по настройке remote developing](https://code.visualstudio.com/docs/remote/remote-overview)
* [C++ developer pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack)

## Cmake

Более высокоуровневый язык для сборки проекта. Позволяет описывать сборку проекта и выдывать Makefile на основе высокоуровневых правил.
Правила описываются в CMakeLists.txt.

* Задать имя проекта `project(cpp_course)`
* Установить версию cmake `cmake_minimum_required(VERSION 3.10)`
* Инструкция для выставления внутренних переменных `set(VARIABLE_NAME VALUE)`. Полезные built-in переменные: CMAKE_CXX_STANDARD, CMAKE_MODULE_PATH, CMAKE_RUNTIME_OUTPUT_DIRECTORY, CMAKE_LIBRARY_OUTPUT_DIRECTORY, CMAKE_EXPORT_COMPILE_COMMANDS.
* CMAKE_BINARY_DIR - путь до того где будут бинарники (откуда запускаем cmake), CMAKE_SOURCE_DIR - расположение корневого cmake файла
* Добавить исполняемый таргет для сборки `add_executable(TARGET_NAME SOURCE)`. Например, часто используются вспомогательные переменные: `set(SOURCE main.cpp); add_executable(target ${SOURCE});`
* Добавить библиотеку для сборки `add_library(LIBRARY_NAME SOURCE)`
* Прилинковать библиотеку `target_link_libraries(TARGET TYPE LIB_NAME)`, где TYPE может быть PUBLIC, PRIVATE, INTERFACE
* Добавить путь до headers `target_include_directories(TARGET TYPE PATH)`, в основном legacy
* Подключить cmake файл `include(file.cmake)`
* Подключить cmake директорию `add_subdirectory(subdir)`
* Проверить наличие библиотеки `find_package(package)`

Есть альтернативные build-системы, например, [ninja](https://ninja-build.org).
Есть также пакетный менеджер для C++ библиотек, например, [conan](https://conan.io).