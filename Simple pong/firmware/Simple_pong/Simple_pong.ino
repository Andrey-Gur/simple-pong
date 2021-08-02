#include "defines.h"                                            //Подключение файла с переменными и константами


//=====НАСТРОЙКИ=====

#define HARD                                                    //Сложность (при HARD при клике в центре раунд будет закончен, при ином знчении ничего не будет)
#define SPEED 250                                               //Скорость переключения свтеодиодов
#define DEBUG                                                   //Если объявлено то будут выводиться сообщения в порт

//=====НАСТРОЙКИ=====

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
  Serial.println("Start");
#endif
  pinInit();                                                    //Функция инициализации пинов
  attachInterrupt(INT0, firstPlayerClick, FALLING);             //Инициализация прерывания кнопки первого игрока
  attachInterrupt(INT1, secondPlayerClick, FALLING);            //Инициализация прерывания кнопки второго игрока
  randomSeed(analogRead(A0));
}

void firstPlayerClick() {                                       //Обработчик прерывания первого игрока
#ifdef DEBUG
  Serial.println("сf");                                         //cf = Первый игрок нажал на кнопку
#endif
  if (gameRun && Direction == left) {                           //Проверка направления и идет ли игра
    if (ledPosition == 7 || ledPosition == 8) {                 //Если позиция "Мяча" равна двум крайним положениям то
      Direction = right;                                        //Изменение напрвление
      ledPosition = 8;                                          //Сброс позиции "Мяча"
    }
#ifdef HARD                                                     //Проверяем сложность
    else if (ledPosition == 6 && Direction == left) {           //Если позиция "Мяча" в центре то
      roundOverFlag = 1;                                        //Поднимаем флаг
    }
#endif
  } else if (!gameRun) {                                        //Если игра игра не начата то
    roundStartFlag = 1;                                         //Запцск функции начала игры
    roundOverFlag = 0;                                          //Сброс флага
  }
}

void secondPlayerClick() {                                      //Обработчик прерывания второго игрока
#ifdef DEBUG
  Serial.println("сs");                                         //сs = Второй игрок нажал кнопку
#endif
  if (gameRun && Direction == right) {                          //Проверка направления и идет ли игра
    if (ledPosition == 5 || ledPosition == 4) {                 //Если позиция "Мяча" равна двум крайним положениям то
      Direction = left;                                         //Меняем напрвление
      ledPosition = 4;                                          //Сброс позиции "Мяча"
    }
#ifdef HARD                                                     //Проверяем сложность
    else if (ledPosition == 6 && Direction == right) {          //Если позиция "Мяча" в центре то
      roundOverFlag = 1;                                        //Поднимаем флаг
    }
#endif
  } else if (!gameRun) {                                        //Если игра игра не начата то
    roundStartFlag = 1;                                         //Поднимаем флаг roundStartFlag
    roundOverFlag = 0;                                          //Сброс флага roundOverFlag
  }
}

void loop() {                                                   //Бесконечный цикл
  if (gameRun) {                                                //Если игра идет                                                   //Моргаем один раз
    updateLeds();                                               //Обновление индикации проиграных раундов
    if (Direction == left) {                                    //Проверка направления
      for (int i = led_1; i <= led_5; i++) {                    //Цикл
#ifdef DEBUG
        Serial.println(ledPosition);                            //Вывод позиции "Мяча"
#endif
        if (gameRun) {                                          //Проверка флага
          ledPosition == 9 ? ledPosition = 4 : ledPosition++;   //Перемещение "Мяча"
          if (!gameRun) {                                       //Если игра не идет выход из цикла
            break;
          }
          digitalWrite(i, HIGH);                                //Обновление светодиода
          delay(SPEED);
          digitalWrite(i, LOW);
          if (ledPosition == 9                                  //Если светодиод дошел до края,
              && Direction == left
              || roundOverFlag) {                               //Или флаг равен 1 то
            roundOver(1);                                       //Запуск функции roundOver
            break;                                              //Выход из цикла
          }
        } else {                                                //Если игра не идет выход из цикла
          break;
        }
      }
    }
    else if (Direction == right) {                              //Проверка направления
      for (int w = led_5; w >= led_1; w--) {                    //Цикл
#ifdef DEBUG
        Serial.println(ledPosition);                            //Вывод позиции "Мяча"
#endif
        if (gameRun) {                                          //Проверка флага
          if (!gameRun) {                                       //Если игра не идет выход из цикла
            break;
          }
          ledPosition == 3 ? ledPosition = 8 : ledPosition--;   //Перемещение "Мяча"
          digitalWrite(w, HIGH);                                //Обновление светодиода
          delay(SPEED);
          digitalWrite(w, LOW);
          if (ledPosition == 3                                  //Если светодиод дошел до края,
              && Direction == right
              || roundOverFlag) {                               //Или флаг равен 1 то
            roundOver(2);                                       //Запуск функции roundOver
            break;                                              //Выход из цикла
          }
        } else {                                                //Если игра не идет выход из цикла
          break;
        }
      }
    }
  } else if (roundStartFlag) {                                  //Если игра не илет а флаг roundStartFlag равен 1
    roundStart();                                               //Запуск игры
    roundStartFlag = 0;                                         //Сброс флага
  }
}

void roundStart() {                                             //Функция запуска игры
#ifdef DEBUG
  Serial.println("rs");                                         //rs = round start
#endif
  Blink(1);                                                     //Индикация старта игры
  getDirection();                                               //Функция получения направления
  gameRun = 1;                                                  //Поднимаем флаг
}

void roundOver(int player) {                                    //Функция проигрыша раунда
#ifdef DEBUG
  Serial.println("ro");                                         //ro = round over
#endif
  if (player == 1) {                                            //Если проиграл первый игрок
    if (lostRoundsFirstPlayer < 3) lostRoundsFirstPlayer++;     //Если количество проиграных раундов меньше 4 то добавляем 1
    else gameOver();                                            //Иначе запуск функции проигрыша игры
  }
  else if (player == 2) {                                       //Если проиграл второй игрок
    if (lostRoundsSecondPlayer < 3) lostRoundsSecondPlayer++;   //Если количество проиграных раундов меньше 4 то добавляем 1
    else gameOver();                                            //Иначе запуск функции проигрыша игры
  }

  gameRun = 0;                                                  //Сброс флага
  getDirection();                                               //Получение напраления
  updateLeds();                                                 //Обновление индикации проиграных раундов
  Blink(1);                                                     //Моргаем светодиодами один раз
  delay(200);                                                   //Ожидание
}

void gameOver() {                                               //Функция проигриша игры
#ifdef DEBUG
  Serial.println("go");                                         //go = game over
#endif
  getDirection();                                               //Получаем нарпраление

  lostRoundsFirstPlayer = 0;                                    //Сброс переменных с количестом проигранных раундов
  lostRoundsSecondPlayer = 0;

  updateLeds();                                                 //Обновление индикации проиграных раундов

  Blink(3, 1);                                                  //Моргаем светодиодами
}

void getDirection() {                                           //Функция получения направления
  int e = random(0, 1000);                                      //Получаем случайное число
  if (e < 500) {                                                //Если оно меньше пятиста
    Direction = left;                                           //Напраление влево
    ledPosition = led_1;                                        //Позиция светодиода справа
  }
  if (e > 500) {                                                //Если больше
    Direction = right;                                          //Направление вправо
    ledPosition = led_5;                                        //Позиция слева
  }
}
