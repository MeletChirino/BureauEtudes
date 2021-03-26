# Bureau D'Etudes
Nous avons ete nomees STM31_25
## TP1 Blinky
Make main Led of the board blink 
## TP2 Connecter l'ecran LCD
Connect LCD Screen and see some strings
## TP3 Connecter l'ecran LCD + Capteur de temperadure
Use SHT31 sensor to measure temperature and show it on LCD Screen previously used.
[SHT31 Arduino's library](https://github.com/Seeed-Studio/Grove_SHT31_Temp_Humi_Sensor "Arduino's Library")
## Bureau d'etudes project
Our project consists to create a IoT device to improve the RU in covid Times
### Introduction
Main RU in Paul Sabatier University is always full and it makes students spend a lot of time in a waiting line. Restaurant works as an assembly line where the student wait its turn in the line and then it chooses what it wants. This system spends a lost of time while choosing and paying time(there is always someone who cant make a quick decision). Our idea is that students can see the menu, choose what they want and pay from their cell phone and then wait for a email that says that their food is ready to pick up. For this we will use a nucleo 152l-RE development board, a Wifi module (esp8266), a regular LCD which works via I2C and a web server powered by Django (python).
### Improved Process 
The process will optimize time of students and kitchen staff. Students could take advantage of their waiting time by studying or doing something else the would not be able to do if they were in a waiting line. They will also be capable of checking the menu since very early in the morning so they can take their time to choose as slow as they want without slowing down the line. 
Kitchen staff time will also be optimized since they are only dealing with a little screen that says what to do. Kitchen staff will also be capable of changing the menu as food runs out.

![alt text](/uml/use_case.png)

![alt text](/uml/regarder_menu.png)
![alt text](/uml/commander_formule.png)
![alt text](/uml/modifier_menu.png)
