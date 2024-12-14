#include "fileObserver.h"
#include <filesystem> 

FileObserver::FileObserver(const std::string& filename) {
    logFile.open(filename, std::ios::app); 
    if (logFile.is_open()) {
        std::cout << "Файл успешно открыт для логов: " << filename << std::endl;
        std::cerr << "Рабочая директория: " << std::filesystem::current_path() << std::endl;
    } else {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
    }
}

FileObserver::~FileObserver() {
    if (logFile.is_open()) {
        logFile.close(); 
        std::cout << "Файл логов закрыт." << std::endl;
    }
}

void FileObserver::notify(const std::string& message) {
    if (logFile.is_open()) {
        logFile << message << std::endl; 
        logFile.flush(); 
        std::cout << "Запись в лог: " << message << std::endl; 
    } else {
        std::cerr << "Ошибка: файл логов закрыт или недоступен." << std::endl;
    }
}
