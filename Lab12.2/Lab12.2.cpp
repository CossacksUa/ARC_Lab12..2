#include <iostream>
#define M_PI 3.14159265358979323846

int main() {
    double x = 12.0;     // Початкове значення x в градусах
    double step = 8.0;   // Крок для зміни x в градусах
    double y;            // Змінна для збереження результату
    const double base = 3.0;   // Основа степеня

    for (int i = 0; i < 6; i++) {
        double radians = (2 - 5.1 * x) * M_PI / 180.0; // Конвертація в радіани

        __asm {
            fld radians      // Завантажуємо radians у стек FPU
            fcos             // Обчислюємо cos(radians)
            fld base         // Завантажуємо основу (3.0) у стек FPU
            fyl2x            // Обчислюємо log2(base) * cos(radians), що еквівалентно log3(cos)
            fld1             // Завантажуємо 1 у стек
            f2xm1            // Обчислюємо 2^x - 1 для поточного значення в стеку
            faddp st(1), st  // Додаємо 1, отримуємо 3^cos(radians)
            fstp y           // Зберігаємо результат в y
        }

        std::cout << "x = " << x << ", y = " << y << std::endl;
        x += step; // Збільшуємо x на крок
    }

    return 0;
}
