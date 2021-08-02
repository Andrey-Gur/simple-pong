void pinInit() {                                                //Функция инициализации пинов
  pinMode(player_one_btn, INPUT_PULLUP);                        //Кнопки - вход с полтяжкой пина
  pinMode(player_two_btn, INPUT_PULLUP);

  pinMode(first_rgb_blue, OUTPUT);                              //Контакты первого RGB светодиода - выход
  pinMode(first_rgb_green, OUTPUT);
  pinMode(first_rgb_red, OUTPUT);

  pinMode(second_rgb_blue, OUTPUT);                             //Контакты второго RGB светодиода - выход
  pinMode(second_rgb_green, OUTPUT);
  pinMode(second_rgb_red, OUTPUT);

  for (int i = led_1; i <= led_5; i++) {                        //Светодиоды - выход
    pinMode(i, OUTPUT);
  }
#ifdef common_anode
  digitalWrite(13, HIGH);                                       //Выключение всех светодиодов
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);

  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
#endif

#ifdef common_cathode
  digitalWrite(13, HIGH);                                       //Выключение всех светодиодов
  digitalWrite(12, HIGH);
  digitalWrite(11, HIGH);

  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
#endif
  for (int i = led_1; i <= led_5; i++) {
    digitalWrite(i, LOW);
  }
}
