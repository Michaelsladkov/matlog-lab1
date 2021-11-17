# Задание:

Написать программу, которая читает логическую формулу, содержащую произвольное число переменных, операции: отрицание, конъюнкцию, дизъбнкцию, импликацию и скобки, разбирает эту формулу в дерево, и анализирует, является ли формула: противоречием, выполнимой формулой, общезначимой формулой

# Идеи по реализации 
0. Удаляем все пробельные символы
1. Превращаем строку с формулой в список лексем следующих типов: 
    
    а) переменная 
    
    б) символ "!" 
    
    в) символ "(" 
    
    г) символ ")" 
    
    д) символ "|" 
    
    е) символ "&" 
    
    ж) "->"
2. Находим наименее приоритетный оператор с учётом скобок (то есть тот, который должен быть применён последним).
3. Делим список лексем на две части: до найденного оператора и после.
4. Если в списке справа последовательность скобок неправильная, удаляем первую встретившуюся "("
5. Если в списке слева последовательность скобок неправильная, удаляем последнюю встретившуюся ")"
6. Создаём узел дерева с типом операции, соответствующем оператору на шаге 2 и двумя дочерними узлами (если оператор !, то дочерний узел один - левый).
7. Рекурсивно создаём дочерние узлы, повторяя шаги со второго для полученных правой и левой частей списка лексем.
8. Когда доходим в разборе выражения до того, что в каждом подсписке осталась только одна лексема, эта лексема - переменная. Создаём для неё специальный узел и указатель на него засовываем в список указателей на переменные.
9. Вычисляем длину полученного списка и преобразуем его в массив.
10. Подставляем в переменные все возможные комбинации значений и для каждой вычисяем формулу
11. Если ни разу не был получен 0 - формула общезначима, если ни разу не была получена 1 - формула невыполнима, иначе, формула выполнима
12. **PROFIT**