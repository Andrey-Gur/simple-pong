#define player_one_btn 2                                        //Пин кнопки первого игрока
#define player_two_btn 3                                        //Пин кнопки второго игрока

#define common_anode                                            //Тип цветных светодиодов (Расскоментировать нужное) 
//#define common_cathode

#define first_rgb_blue 13                                       //Первый пин первого RGB светодиода
#define first_rgb_green 12                                      //Второй пин первого RGB светодиода
#define first_rgb_red 11                                        //Третий пин первого RGB светодиода

#define second_rgb_blue A0                                      //Первый пин второго RGB светодиода                                               
#define second_rgb_green A1                                     //Второй пин второго RGB светодиода
#define second_rgb_red A2                                       //Третий пин второго RGB светодиода

#define led_1 4                                                 //Первый светодиод
#define led_2 5                                                 //Второй светодиод
#define led_3 6                                                 //Третий свтодиод
#define led_4 7                                                 //Четвертый светодиод
#define led_5 8                                                 //Пятый светодиод

#define left true                                               //Для удобства true = left
#define right false                                             //А false = right

int lostRoundsFirstPlayer = 0;                                  //Количество проигранных раундов первым игроком
int lostRoundsSecondPlayer = 0;                                 //Количество проигранных раундов вторым игроком
int ledPosition = 4;                                            //Позиция светодиода
boolean Direction;                                              //Напраление
boolean gameRun = false;                                        //Идет ли игра
boolean roundStartFlag = 0;                                     //Нажата ли кнопка для начала игры
boolean roundOverFlag = 0;                                      //Проиграна ли игра
