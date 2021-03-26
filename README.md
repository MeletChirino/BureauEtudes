# Bureau D'Etudes
Nous avons ete nomees STM31_25
## TP1 Blinky
Make main Led of the board blink 
## TP2 Connecter l'ecran LCD
Connect LCD Screen and see some strings
## TP3 Connecter l'ecran LCD + Capteur de temperadure
Use SHT31 sensor to measure temperature and show it on LCD Screen previously used.
## Bureau d'etudes project
Our project consists to create a IoT device to improve the RU in covid Times
### Introduction
Main RU in Paul Sabatier University is always full and it makes students spend a lot of time in a waiting line. Restaurant works as an assembly line where the student wait its turn in the line and then it chooses what it wants. This system spends a lost of time while choosing and paying time(there is always someone who cant make a quick decision). Our idea is that students can see the menu, choose what they want and pay from their cell phone and then wait for a email that says that their food is ready to pick up. For this we will use a nucleo 152l-RE development board, a Wifi module (esp8266), a regular LCD which works via I2C and a web server powered by Django (python).
### Improved Process 
![alt text](/uml/use_case.png)
Use both LCD Screen and temperature sensor but also add a wifi module to build an IoT device thats sends information through internet.

[SHT31 Arduino's library](https://github.com/Seeed-Studio/Grove_SHT31_Temp_Humi_Sensor "Arduino's Library")
