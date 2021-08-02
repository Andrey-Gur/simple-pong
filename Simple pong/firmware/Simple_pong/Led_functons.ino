void updateLeds() {                                             //Функция обновления индикации проиграных раундов
#ifdef common_andoe
  digitalWrite(first_rgb_red, HIGH);                            //Выключение всех цветных светодиодов
  digitalWrite(first_rgb_green, HIGH);
  digitalWrite(first_rgb_blue, HIGH);
  digitalWrite(second_rgb_red, HIGH);
  digitalWrite(second_rgb_green, HIGH);
  digitalWrite(second_rgb_blue, HIGH);
#endif

#ifdef common_cathode
  digitalWrite(first_rgb_red, LOW);                            //Выключение всех цветных светодиодов
  digitalWrite(first_rgb_green, LOW);
  digitalWrite(first_rgb_blue, LOW);
  digitalWrite(second_rgb_red, LOW);
  digitalWrite(second_rgb_green, LOW);
  digitalWrite(second_rgb_blue, LOW);
#endif

#ifdef common_andoe
  switch (lostRoundsFirstPlayer) {                              //Проврка количства проигранных раундов первого игрока
    case 1:                                                     //Если один проигранный раунд
      digitalWrite(first_rgb_green, LOW);                       //Включаеться зеленый светодиод
      break;
    case 2:                                                     //Если два проиграных раунда
      digitalWrite(first_rgb_blue, LOW);                        //Вклюяается синий светодиод
      break;
    case 3:                                                     //Если 3 проигранных раунда
      digitalWrite(first_rgb_red, LOW);                         //Включаеться красный светодиод
      break;
  }

  switch (lostRoundsSecondPlayer) {                             //То же самое для второго игрока
    case 1:
      digitalWrite(second_rgb_green, LOW);
      break;
    case 2:
      digitalWrite(second_rgb_blue, LOW);
      break;
    case 3:
      digitalWrite(second_rgb_red, LOW);
      break;
  }
#endif

#ifdef common_cathode
  switch (lostRoundsFirstPlayer) {                              //Проврка количства проигранных раундов первого игрока
    case 1:                                                     //Если один проигранный раунд
      digitalWrite(first_rgb_green, HIGH);                       //Включаеться зеленый светодиод
      break;
    case 2:                                                     //Если два проиграных раунда
      digitalWrite(first_rgb_blue, HIGH);                        //Вклюяается синий светодиод
      break;
    case 3:                                                     //Если 3 проигранных раунда
      digitalWrite(first_rgb_red, HIGH);                         //Включаеться красный светодиод
      break;
  }

  switch (lostRoundsSecondPlayer) {                             //То же самое для второго игрока
    case 1:
      digitalWrite(second_rgb_green, HIGH);
      break;
    case 2:
      digitalWrite(second_rgb_blue, HIGH);
      break;
    case 3:
      digitalWrite(second_rgb_red, HIGH);
      break;
  }
#endif
}

void Blink(int q) {                                             //Функция чтобы моргать светодиодами
  for (int i = 0; i < q; i++) {
    for (int z = led_1; z <= led_5; z++)  digitalWrite(z, HIGH);//Включение всех светодиодов
    delay(1000);                                                //Ожидание
    for (int z = led_1; z <= led_5; z++)  digitalWrite(z, LOW); //Выключение всех светодиодов
    delay(1000);                                                //Ожидание
  }
}

void Blink(int q, boolean a) {                                  //Та же функция что и выше, но с двумя аргументами
  if (a) {                                                      //Если аргумент w равен 1 то моргаем всеми светодиодами
    for (int i = 0; i < q; i++) {
      for (int z = led_1; z <= led_5; z++) digitalWrite(z, HIGH);
#ifdef common_andoe
      digitalWrite(second_rgb_red, LOW);
      digitalWrite(first_rgb_red, LOW);
#endif

#ifdef common_cathode
      digitalWrite(second_rgb_red, HIGH);
      digitalWrite(first_rgb_red, HIGH);
#endif
      delay(1000);
      for (int z = led_1; z <= led_5; z++)  digitalWrite(z, LOW);
#ifdef common_andoe
      digitalWrite(second_rgb_red, HIGH);
      digitalWrite(first_rgb_red, HIGH);
#endif

#ifdef common_cathode
      digitalWrite(second_rgb_red, LOW);
      digitalWrite(first_rgb_red, LOW);
#endif
      delay(1000);
    }
  }
}
