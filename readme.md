# 7. Парсер пакетных команд

Создаем утилиту для парсинга и комплексного логгирования пакетных команд. Стремимся к снижению зависимостей между модулями.

### Разработать программу для пакетной обработки команд.

Команды считываются построчно из стандартного ввода и обрабатываются блоками по N команд. Одна команда - одна строка, конкретное значение роли не играет. Если данные закончились - блок завершается принудительно. Параметр N передается как единственный параметр командной строки в виде целого числа.

**Логика работы для статических блоков (в примере N == 3):**

cmd1<br>
cmd2<br>
cmd3<br>
-> bulk: cmd1, cmd2, cmd3 // блок завершён - выводим блок<br>
cmd4<br>
cmd5<br>
eof<br>
-> bulk: cmd4, cmd5 // конец ввода - выводим блок<br>

Размер блока можно изменить динамически, если перед началом блока и сразу после дать команды `{` и `}` соответственно. Предыдущий пакет при этом принудительно завершается. Такие блоки могут быть включены друг в друга при этом вложенные команды `{` и `}` игнорируются (но не сами блоки). Если данные закончились внутри динамического блока, весь динамический блок игнорируется.

**Логика работы для динамического размера блоков (в примере N == 3):**

cmd1<br>
cmd2<br>
{<br>
-> bulk: cmd1, cmd2 // начало динамического блока - досрочно выводим предыдущий<br>
cmd3<br>
cmd4<br>
}<br>
-> bulk: cmd3, cmd4 // конец динамического блока<br>
cmd5<br>
cmd6<br>
{ // вложенные блоки игнорируем<br>
cmd7<br>
cmd8<br>
} // вложенные блоки игнорируем<br>
cmd9<br>
}<br>
bulk: cmd5, cmd6, cmd7, cmd8, cmd9 // конец динамического блока<br>
{<br>
cmd10<br>
cmd11<br>
eof // конец ввода, игнорируем динамический блок, не выводим<br>

Вместе с выводом в консоль блоки должны сохранятся в отдельные файлы с именами
bulk1517223860.log , где 1517223860 - это время получения первой команды из блока. По одному файлу на блок.

- **Требования к реализации**
    
    Бинарный файл должен называться bulk.
    
- **Проверка**
    
    Задание считается выполненным успешно, если после установки пакета и запуска с тестовыми данными вывод соответствует описанию. Данные подаются на стандартный вход построчно с паузой в 1 секунду для визуального контроля.
    Будет отмечена низкая связанность обработки данных, накопления пачек команд, вывода в консоль и сохранения в файлы.