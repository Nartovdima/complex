# Комплексные числа

Необходимо реализовать класс комплексного числа, предоставляющий следующие операции:

- Конструирование без аргументов
- Конструирование от вещественной части
- Конструирование от вещественной и мнимой частей
- Вещественная часть: `double real()`
- Мнимая часть: `double imag()`
- Модуль: `double abs()`
- Перевод в строку: `std::string str()`
- Сложение: `+`, `+=`
- Вычитание: `-`, `-=`
- Умножение: `*`, `*=`
- Деление: `/`, `/=`
- Унарный минус: `-`
- Комплексное сопряжённое: `~`
- Сравнение на равенство: `==`, `!=`
- Вывод в поток: `<<`

Обработка ошибок не требуется, однако операции стоит реализовывать так, чтобы минимизировать вероятность переполнения.

Допустимо добавление в публичный интерфейс дополнительных методов, если они семантически действительно должны быть
публичными.

# Арифметические выражения

Необходимо организовать иерархию классов для работы с вычислимыми арифметическими выражениями над типом `Complex`.

Виды выражений:

- `Const` (в конструкторе передаётся значение)
- `Variable` (в конструкторе передаётся имя переменной)
- `Negate` (унарный минус)
- `Conjugate` (комплексное сопряжённое)
- `Add` (сложение)
- `Subtract` (вычитание)
- `Multiply` (умножение)
- `Divide` (деление)

Все эти классы должны (необязательно напрямую) наследоваться от `Expression`.

Пример конструирования выражения `2 * x + 1`:

```cpp
const Add expr(Multiply(Const(2), Variable("x")), Const(1));
```

Над выражениями должны быть реализованы соответствующие арифметические операторы.
Таким образом, предыдущий пример можно было бы записать так:

```cpp
const Add expr = Const(2) * Variable("x") + Const(1);
```

Аргументом методу `eval` передаётся отображение из имени переменной в её значение.
Он возвращает результат выражения, используя переданные значения вместо переменных.

```cpp
const Complex result = expr.eval({
    {"x", Complex(100)}
    {"y", Complex(42)}
}); // 201
```

Вспомогательный метод `clone` должен возвращать указатель на такое же выражение, как то, на котором он вызван,
однако владение над указателем принадлежит вызвавшему метод.

Для класса `Expression` должен быть реализован оператор вывода в поток.

В этой части задания также не требуется обрабатывать ошибки.

# Написание своих тестов.

Тесты необходимо написать на catch2, они должны покрывать все операции и запускаться автоматически на github.
