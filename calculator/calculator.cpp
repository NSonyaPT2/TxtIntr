#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

void printHelp() {
    std::cout << "Использование: calculator [OPTIONS] [OPERANDS...]\n"
              << "Опции:\n"
              << "  -o, --operation <multiply|divide>  Выбор операции (умножение или деление)\n"
              << "  -h, --help                         Показать эту справку\n\n"
              << "Примеры:\n"
              << "  calculator -o multiply 2 3 4        # Умножение: 2 * 3 * 4 = 24\n"
              << "  calculator --operation divide 100 2 5  # Деление: 100 / 2 / 5 = 10\n\n"
              << "Требования:\n"
              << "  - Количество операндов: от 3 до 5\n"
              << "  - Операция обязательна\n";
}

double multiply(const std::vector<double>& operands) {
    double result = 1.0;
    for (double op : operands) {
        result *= op;
    }
    return result;
}

double divide(const std::vector<double>& operands) {
    if (operands.empty()) return 0.0;
    
    double result = operands[0];
    for (size_t i = 1; i < operands.size(); ++i) {
        if (operands[i] == 0) {
            std::cerr << "Ошибка: деление на ноль!" << std::endl;
            return 0.0;
        }
        result /= operands[i];
    }
    return result;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printHelp();
        return 1;
    }

    std::string operation;
    std::vector<double> operands;

    // Парсинг аргументов командной строки
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "-h" || arg == "--help") {
            printHelp();
            return 0;
        }
        else if (arg == "-o" || arg == "--operation") {
            if (i + 1 < argc) {
                operation = argv[++i];
            } else {
                std::cerr << "Ошибка: после -o/--operation должно следовать имя операции" << std::endl;
                return 1;
            }
        }
        else {
            // Пытаемся преобразовать в число
            try {
                operands.push_back(std::stod(arg));
            } catch (const std::invalid_argument&) {
                std::cerr << "Ошибка: неверный аргумент '" << arg << "'" << std::endl;
                return 1;
            }
        }
    }

    // Проверка минимальных требований
    if (operation.empty()) {
        std::cerr << "Ошибка: операция не указана!" << std::endl;
        printHelp();
        return 1;
    }

    if (operands.size() < 3 || operands.size() > 5) {
        std::cerr << "Ошибка: количество операндов должно быть от 3 до 5" << std::endl;
        std::cerr << "Получено: " << operands.size() << " операндов" << std::endl;
        return 1;
    }

    // Выполнение операции
    double result = 0.0;
    
    if (operation == "multiply") {
        result = multiply(operands);
        std::cout << "Результат умножения: ";
    }
    else if (operation == "divide") {
        result = divide(operands);
        std::cout << "Результат деления: ";
    }
    else {
        std::cerr << "Ошибка: неизвестная операция '" << operation << "'" << std::endl;
        std::cerr << "Допустимые операции: multiply, divide" << std::endl;
        return 1;
    }

    // Вывод результата
    std::cout << std::fixed << std::setprecision(6);
    
    // Выводим выражение
    std::cout << operands[0];
    for (size_t i = 1; i < operands.size(); ++i) {
        std::cout << (operation == "multiply" ? " * " : " / ");
        std::cout << operands[i];
    }
    
    std::cout << " = " << result << std::endl;

    return 0;
}