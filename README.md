# Projektdokumentation *Nano RPS*

- [Projektdokumentation *Nano RPS*](#projektdokumentation-nano-rps)
  - [Einführung](#einführung)
    - [Motivation](#motivation)
    - [Zielstellung](#zielstellung)
    - [Vorhergehensweise](#vorhergehensweise)
  - [Edge Impulse](#edge-impulse)
    - [Datenacquisation](#datenacquisation)
    - [Impulse Learning](#impulse-learning)
      - [Image](#image)
      - [Transfer Learning](#transfer-learning)
  - [Setup](#setup)
    - [Nano 33 Setup](#nano-33-setup)
      - [Hardware](#hardware)
      - [Software](#software)
    - [ESP32 + LED Matrix Setup](#esp32--led-matrix-setup)
      - [Hardware](#hardware-1)
      - [Software](#software-1)
      - [Bauanleitung](#bauanleitung)
  - [Matrix GIFs](#matrix-gifs)
  - [Projektergebnisse](#projektergebnisse)
  - [Troubleshooting](#troubleshooting)
  - [Lessons Learned](#lessons-learned)
---

## Einführung

### Motivation
Im Rahmen des Moduls "Wissensmanagement" an der HTW Berlin gab es die Möglichkeit in zwei Wochen ein Machinelearning Projekt mit Arduinobauteilen aufzusetzen. Dafür haben wir uns für Bilderkennung, LED Matrizen und der Kommunikation verschiedener Boards über Bluetooth Low Energy (BLE) interessiert. TODO noch mehr ergänzen

### Zielstellung
Durch eine Kamera sollen die Handgesten _Schere_, _Stein_ und _Papier_ aufgenommen werden. Diese sollen dann richtig klassifiziert werden. Das Modell für die Klassifizierung soll in Edge Impulse mit verschiedenen Datensätzen trainiert werden. Die dann richtig erkannte Geste soll über BLE an einen ESP32 gesendet werden. Dieser wählt für den Computer zufällig eine Geste aus und entscheidet, wer gewinnt. Die Auswahl vom Mensch und Computer sowie das Ergebnis sollen dann grafisch auf einer LED-Matrix dargestellt werden.

### Vorhergehensweise
- Erstellen des Modells in Edge Impulse
- Zuerst mit eigenen Daten (eigene Hände) genutzt mit jeweils 30 Daten für jede Geste und jeweils 10 Testdatensätze
- Dann haben wir Datensätze benutzt (2 verschiedene)
- Das Modell auf Nano 33 gespielt und getestet
- LED Matrix
- BLE zur Kommunikation

## Edge Impulse
TODO Erklärung zu Edge Impulse

### Datenacquisation
Für die Daten wurden zuerst eigenständig Bilder von unseren Händen erstellt. Das hat aber zu einer nicht zufriedenstellendem Ergebnis geführt. Daraufhin wurden zwei verschiedene Datenquellen benutzt. Diese wiesen bereits geordnet für jede Geste viele hunderte Daten auf. Ein Datensatz basiert auf echten Händen auf einem grünen Hintergrund. Der andere basiert auf CGI Händen auf einem weißen Hintergrund. Es wurden weitere eigene Bilder hinzugefügt, die einen leeren Hintergrund zeigen. Damit soll das Modell einen leeren Hintergrund erkennen können und später auch so ausgeben. Es wurden 4 Label festgelegt _rock_, _paper_, _scissors_, _nothing_. Jedes Bild hat ein Label korrekt zugewiesen bekommen. Damit ergeben sich folgende Zahlen für die Daten:

- Bilder insgesamt: 3895
- Schere (scissors): 1291
- Stein (stone): 1284
- Papier (paper): 1266
- Bilder mit leerem Hintergrund (nothing): 54

Die Daten wurden aufgeteilt nach 80% Training und 20% Test.
![Datenacquisation](/pics/data-acquisition.png)

TODO Vorteile/Nachteile der Datensätze erklären

Beispiele aus den Datensätzen sehen wie folgt aus:

| Datensatz          | Geste        | Bild                                                                 |
|--------------------|--------------|----------------------------------------------------------------------|
| Grüner Hintergrund | Schere       | <img src="/pics/scissors-green-background-example.png" width="30%"/> |
| Grüner Hintergrund | Stein        | <img src="/pics/stone-green-background-example.png" width="30%"/>    |
| Grüner Hintergrund | Papier       | <img src="/pics/paper-green-background-example.png" width="30%"/>    |
| CGI                | Schere       | <img src="/pics/scissors-cgi-example.png" width="30%"/>              |
| CGI                | Stein        | <img src="/pics/stone-cgi-example.png" width="30%"/>                 |
| CGI                | Papier       | <img src="/pics/paper-cgi-example.png" width="30%"/>                 |
| Eigen              | Hintergrund  | <img src="/pics/nothing-example.png" width="30%"/>                   |

### Impulse Learning
TODO Erklärung was ist Impulse Learning

![Impulse Learning](/pics/impulse-learning.png)

#### Image

Für den Schritt _Image_ wird als einziger Parameter _Color depth_ "Grayscaling" festgelegt. Das ist gut um TODO

#### Transfer Learning
TODO Erklärung was ist Transfer Learning; Was haben wir eingestellt

![Transfer Learning](/pics/transfer-learning.png)
## Setup

### Nano 33 Setup

#### Hardware
- Arduino Nano 33 BLE Sense Lite Board
- Arduino Tiny Machine Learning Shield
- ArduCam OV7675
- USB A to USB Micro B Kabel (1 Meter)

Verwendet wurde zwar ein _Arduino Nano 33 BLE Sense Lite Board_ aber es ist keine _Sense_ Version benötigt, da keiner der Sensoren benutzt wird.

#### Software
Benötigt wird für diesen Teil folgendes:

- Arduino Bibliothek aus _Edge Impulse_ (bereitgestellt im TODO Repo)
- Die TODO.ino Datei aus dem TODO Repo
- ArduinoIDE (auch eine andere IDE möglich) zum Flashen

Die _TODO.ino_ Datei muss in der ArduinoIDE geöffnet werden. Dann sollte über **Sketch > Include Library > Add .ZIP Library** geschen. Dabei sollte die TODO Bibliothek ausgewählt werden.

![Bibliothek hinzufügen](pics/add-library.png)

Zusätzlich müssen noch die öffentlichen Bibliotheken _Arduino_OV767X_ und _ArduinoBLE_ hinzugefügt werden. Das sollte über den _Library Manager_ gemacht werden.

Daraufhin kann die Datei kompiliert und der Arduino geflasht werden. Dafür muss erstmalig der richtige Boardmanager installiert werden und der Port eingestellt werden. Der Boardmanager _Arduino Mbed OS Nano_ wird installiert über **Tools > Board > Board Manager**

![Board Manager](pics/install-board-manager.png)

Somit kann der Port eingestellt werden indem der Nano eingesteckt ist, kompiliert und geflasht werden.

### ESP32 + LED Matrix Setup

#### Hardware 

#### Software

#### Bauanleitung

## Matrix GIFs

## Projektergebnisse

## Troubleshooting

## Lessons Learned