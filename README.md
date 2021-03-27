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
### LCD Module
The LCD module is a standard screen of 2 rows and 16 columns that works via I2C. For communicating with this screen we have used a library provided by our teacher wich works fine, because its initializing process is kind of complicated to implement line by line. This screen will show kitchen staff orders in a chronological order. 
### Web server
The web server was depployed using the framework Django, written in python. This framework allow us to use python scripts to manage database and network communication while using regular HTTP requests to communicate with IoT device.
The regular flow of this framework accepts a HTTP request, executes a python script, checks a database and finally render a response (usually a http response) to show a website or any information requested.
Since this is a academic project, this web server has been deployed in a local deveplopment server, which means, the server cant handle more than 1000 requests at same time and its been linked to a domain via port forwarding. Basically, this server works in my computer and it have to be activated and deactivated for testing. IT IS NOT HOSTED OVER THE INTERNET.
As domain we have chose [this](http://projetbe.serveblog.net) free temporary one. In this project we have declared 3 main pages: landing page, administration page and api page.
#### Landing page
This is the page accesed by students to order their food, its pretty simple and user friendly. It checks the database of the menu every single time it is requested and then show this info in th frontend.
This page have a direct link to admin page.
#### Administration Page
This is the page that shows the database and menu info. It is not a complicated one but Django allows scalability if necessary. This framework offers, as well, a pretty safe authetication middleware so we did not worry about safety of data at this level.
We are using a simple sqlite3 database but it can be changed to a Postgress one to offer a more robust web application.
#### API
This API page will not work from a web browser, it is meant to receive communication from the wifi module and executes a python script to notify the student about their food and then sends back the data of waiting line (if there is any). Right now it sends information directly to the IP of wifi module over TCP protocol, so static IP of wifi module must be configured before.
This API uses a email stmp service to send notifications to students.
### Wifi Module
This wifi module is the ESP8266 which is a microcontroller itself and communicates via Serial Communication. In order to interact with it there are some commands that can be used to input and output information over the network. Those commands can be programmed directly to the module with a TTL to Serial converter or a arduino board to connect to wifi and get some raw information, but our goal is to make it work with stm32 board. For security reasons in this project we are not going to set any password authentication. 
This Wifi module supports UDP and TCP communication protocols, the last one chosen for this project. Setting up, communication and authentication algorithms are shown below.
![alt text](/uml/flowchart.png)
![alt text](/uml/flowchart_send.png)
### STM32 Serial protocol
Since we use STM32 with CubeIDE we must use HAL handlers for communication protocols. Those handlers simplify a lot the code but the handlers for UART needs a specified length of the string they are going to read and it creates a problem because the wifi module we use do not always send the same amount of data and it can create mistakes.
In order to solve this we used the handler with interrupts every single byte received in Serial buffer. It reads every byte and paste it in a string until reads a '\n'. Then it raises a flag that says we can use the string read in serial buffer.
