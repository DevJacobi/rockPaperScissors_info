# Projektdokumentation *Nano RPS*

- [Projektdokumentation *Nano RPS*](#projektdokumentation-nano-rps)
  - [1 Einführung](#1-einführung)
    - [1.1 Motivation](#11-motivation)
    - [1.2 Zielstellung](#12-zielstellung)
    - [1.3 Vorgehensweise](#13-vorgehensweise)
  - [2 Edge Impulse](#2-edge-impulse)
    - [2.1 Datenacquisation](#21-datenacquisation)
    - [2.2 Impulse Design](#22-impulse-design)
      - [2.2.1 Image](#221-image)
      - [2.2.2 Transfer Learning](#222-transfer-learning)
      - [2.3 Deploy](#23-deploy)
  - [3 Konzept](#3-konzept)
  - [4 Setup](#4-setup)
    - [4.1 Nano 33 Setup](#41-nano-33-setup)
      - [4.1.1 Hardware](#411-hardware)
      - [4.1.2 Software](#412software)
    - [4.2 ESP32 + LED Matrix Setup](#42-esp32--led-matrix-setup)
      - [4.2.1 Hardware](#421-hardware-1)
      - [4.2.2 Software](#422-software-1)
      - [4.2.3 Bauanleitung](#423-bauanleitung)
  - [5 Matrix GIFs](#5-matrix-gifs)
    - [5.1 GIF Erstellung](#51-gif-erstellung)
    - [5.2 Phase 1](#52-phase-1)
    - [5.3 Phase 2](#53-phase-2)
    - [5.4 Phase 3](#54-phase-3)
    - [5.5 Phase 4](#55-phase-4)
    - [5.6 Verwendete Tools](#56-verwendete-tools)
    - [5.7 Was sollte beachtet werden?](#57-was-sollte-beachtet-werden)
  - [6 Projektergebnisse](#6-projektergebnisse)
  - [7 Troubleshooting](#7-troubleshooting)
  - [8 Lessons Learned](#8-lessons-learned)
    - [8.1 Begrenzte Ressourcen](#81-begrenzte-ressourcen)
    - [8.2 Einfarbiger Hintergrund](#82-einfarbiger-hintergrund)
    - [8.3 Verschiedene IDEs](#83-verschiedene-ides)
    - [8.4 Viele Datensätze](#84-viele-datensätze)  
---

## 1 Einführung

### 1.1 Motivation
Im Rahmen des Moduls "Wissensmanagement" an der HTW Berlin hatten wir die Aufgabe in zwei Wochen ein Machine Learning Projekt mit Arduino Bauteilen umzusetzen. Bei der Projektfindung haben wir uns für Bildklassifizierung, LED Matrizen und der Kommunikation zwischen Mikrocontrollern über Bluetooth Low Energy (BLE) interessiert. Nach etwas Brainstomrming kamen wir auf die Idee die verschidenen Aspekte in einen Schere, Stein, Papier Computer zu integrieren. TODO noch mehr ergänzen

### 1.2 Zielstellung
Durch eine Kamera sollen die Handgesten _Schere_, _Stein_ und _Papier_ aufgenommen werden. Diese sollen dann richtig klassifiziert werden. Das Modell für die Klassifizierung soll in Edge Impulse mit verschiedenen Datensätzen trainiert werden. Die dann richtig erkannte Geste soll über BLE an einen ESP32 gesendet werden. Dieser wählt für den Computer zufällig eine Geste aus und entscheidet, wer gewinnt. Die Auswahl vom Mensch und Computer sowie das Ergebnis sollen dann grafisch auf einer LED-Matrix dargestellt werden.

### 1.3 Vorgehensweise
Das Projekt wurde in drei Arbeitspakete unterteilt:

1. Machinelearning Modell trainieren
2. Modell als Bibliothek auf dem Nano einbinden und Bilder erstellen lassen
3. BLE Verbindung herstellen und Grafiken erstellen und anzeigen

Zuerst wurde sämtliche Hardware zusammengesteckt. Daraufhin wurde mithilfe von Edge Impulse ein Modell zur Bilderklassifikation trainiert. Genauers dazu ist in im Kapitel [Impulse Learning](#impulse-learning) erläutert. Hier wurde das Modell über mehrere Iterationen verfeinert und verkleinert, um später mit BLE gut zu harmonieren. Genutzt wurden für die Datensätze, nach anfänglichen Schwierigkeiten mit eigenen Daten, bereits existierende Datensätze aus dem Internet.
Matrix TODO (vielleicht Konsti ein paar Worte dazu)

## 2 Edge Impulse
Edge Impulse ist eine Entwicklungsplattform für KI-Modelle, die speziell für Edge-Geräte wie Mikrocontroller und Sensoren optimiert sind. Die Plattform bietet eine integrierte Umgebung zum Sammeln von Daten, zum Erstellen von Modellen und zum Bereitstellen von Inferenz-Engines direkt auf den Edge-Geräten. Dadurch können Entwickler und Ingenieure schnell und einfach Edge-Modelle für eine Vielzahl von Anwendungen erstellen, darunter Bilderkennung, Spracherkennung, Vibrationserkennung und mehr. Edge Impulse unterstützt eine breite Palette von Edge-Hardware-Plattformen und bietet auch eine Reihe von Entwicklungs-Tools und Bibliotheken für die Integration in bestehende Systeme.

Wir haben diese Platform genutzt, um unser Modell mit Daten zu trainieren und zu optimieren.

### 2.1 Datenacquisation
Für die Daten wurden zuerst eigenständig Bilder von unseren Händen erstellt. Das hat aber zu einer nicht zufriedenstellendem Ergebnis geführt. Daraufhin wurden zwei verschiedene Datenquellen benutzt. Diese wiesen, bereits geordnet für jede Geste, viele hunderte Daten auf. Ein Datensatz basiert auf echten Händen auf einem grünen Hintergrund [(Quelle)](https://www.kaggle.com/datasets/drgfreeman/rockpaperscissors). Der andere basiert auf CGI Händen auf einem weißen Hintergrund [(Quelle)](https://www.kaggle.com/datasets/eng0mohamed0nabil/rock-paper-scissors-dataset). Es wurden weitere eigene Bilder hinzugefügt, die einen leeren Hintergrund zeigen. Damit soll das Modell einen leeren Hintergrund erkennen können und später auch so ausgeben. Es wurden 4 Label festgelegt _rock_, _paper_, _scissors_, _nothing_. Jedes Bild hat ein Label korrekt zugewiesen bekommen. Damit ergeben sich folgende Zahlen für die Daten:

- Bilder insgesamt: 3895
- Schere (scissors): 1291
- Stein (stone): 1284
- Papier (paper): 1266
- Bilder mit leerem Hintergrund (nothing): 54

Die Daten wurden aufgeteilt nach 80% Training und 20% Test.
![Datenacquisation](/pics/data-acquisition.png)

**Vor- und Nachteile der Datensätze**
| Datensatz | Vorteile | Nachteile |
| - | - | - |
| Anfängliche eigene Daten | Keine Vorteile | Zu wenig Daten, zu wenig Variation in den Winkeln, Hintergrund nicht einfarbig |
| Grüner Hintergrund | Große Varianz der Daten | Nur die Hand von einer Person. Könnte zu overfitting für weiße männliche Hände führen |
| CGI Hände | Verschiedene "Personen" und große Varianz | Manchmal uneindeutige Gesten |
| Neue eigene Daten | Leere Hintergründe jetzt trainierbar | Keine Nachteile |

**Beispiele**

| Datensatz          | Geste        | Bild                                                                 |
|--------------------|--------------|----------------------------------------------------------------------|
| Grüner Hintergrund | Schere       | <img src="/pics/scissors-green-background-example.png" width="30%"/> |
| Grüner Hintergrund | Stein        | <img src="/pics/stone-green-background-example.png" width="30%"/>    |
| Grüner Hintergrund | Papier       | <img src="/pics/paper-green-background-example.png" width="30%"/>    |
| CGI                | Schere       | <img src="/pics/scissors-cgi-example.png" width="30%"/>              |
| CGI                | Stein        | <img src="/pics/stone-cgi-example.png" width="30%"/>                 |
| CGI                | Papier       | <img src="/pics/paper-cgi-example.png" width="30%"/>                 |
| Eigen              | Hintergrund  | <img src="/pics/nothing-example.png" width="30%"/>                   |

### 2.2 Impulse Design
In Edge Impulse lässt sich mit den hinterlegten Daten ein sogennanter "Impulse" konfigurieren bei dem, abhängig von den Datentypen, verschiedene Einstellungen zur Vorverarbeitung vorgenommen werden können. Im Fall von Bildern z.B. die Vereinheitlichung der Größe der Bilder. Weiter wird die Feature Extraktion und die Benennug der Variablen hier vorgenommen. Anschließend wird der Learning Schritt festgelegt und die Input und Output Feature definiert.

<img src="/pics/impulse-learning.png" width="70%"/>

#### 2.2.1 Image

Für den Schritt _Image_ wird als einziger Parameter _Color depth_ "Grayscaling" festgelegt. Das ist gut um TODO

#### 2.2.2 Transfer Learning
TODO Erklärung was ist Transfer Learning; Was haben wir eingestellt

<img src="/pics/transfer-learning.png" height="50%"/>

### 2.3 Deploy
TODO
## 3 Konzept

Für das Projekt gibt es ein Konzept, welches die verschiedenen Komponenten und die Kommunikation zwischen ihnen darstellt. Das ist in der folgenden Abbildung zu sehen.

<img src="/pics/konzept.png"/>

Zu sehen sind der _Nano_ und _ESP32_ als Hauptkomponenten. Der _Nano_ ist mit einer Kamera, der OV7675, verbunden. Diese soll jede Sekunde ein Bild der Umgebung aufnehmen. Diese Umgebung sollte eine Hand enthalten die eine der Gesten _Schere_, _Stein_ oder _Papier_ macht. Dieses Bild wird auf dem _Nano_ dann vom trainierten Klassifizierungsmodell klassifiziert und per BLE an den ESP32 gesendet. Das Senden erfolgt erst wenn zwei mal die gleiche Geste erkannt wurde. Zu den Gesten zählen:

- scissors (Schere)
- stone (Stein)
- paper (Papier)
- nothing (Leerer Hintergrund)
- uncertain (Wenn sich das Modell nicht zu über 50% sicher ist)

Die Werte werden dabei in Bytes gemapped, um diese über BLE senden zu können. Der _ESP32_ empfängt den Wert und wählt für den Computer einen eigenen Wert. Das Ergebnis wird dann mithilfe von vorher erstellten GIFs auf der Matrix LED dargestellt.

## 4 Setup

### 4.1 Nano 33 Setup

#### 4.1.1Hardware
- Arduino Nano 33 BLE Sense Lite Board
- Arduino Tiny Machine Learning Shield
- ArduCam OV7675
- USB A to USB Micro B Kabel (1 Meter)

Verwendet wurde zwar ein _Arduino Nano 33 BLE Sense Lite Board_ aber es ist keine _Sense_ Version benötigt, da keiner der Sensoren benutzt wird.

#### 4.1.2 Software
Benötigt wird für diesen Teil folgendes:

- Arduino Bibliothek aus _Edge Impulse_ (bereitgestellt im TODO Repo)
- Die TODO.ino Datei aus dem TODO Repo
- ArduinoIDE (auch eine andere IDE möglich) zum Flashen

Die _TODO.ino_ Datei muss in der ArduinoIDE geöffnet werden. Dann sollte über **Sketch > Include Library > Add .ZIP Library** geschen. Dabei sollte die TODO Bibliothek ausgewählt werden.

<img src="/pics/add-library.png" width="50%"/>

Zusätzlich müssen noch die öffentlichen Bibliotheken _Arduino_OV767X_ und _ArduinoBLE_ hinzugefügt werden. Das sollte über den _Library Manager_ gemacht werden.

Daraufhin kann die Datei kompiliert und der Arduino geflasht werden. Dafür muss erstmalig der richtige Boardmanager installiert werden und der Port eingestellt werden. Der Boardmanager _Arduino Mbed OS Nano_ wird installiert über **Tools > Board > Board Manager**

<img src="/pics/install-board-manager.png" width="50%"/>

Somit kann der Port eingestellt werden indem der Nano eingesteckt ist, kompiliert und geflasht werden.

Die Datei _TODO.ino_ besteht zum Großen Teil aus vorgenerierten Code aus einem Example der exportierten Bibliothen aus Edge Impulse. Diese wurde daraufhin von uns erweitert. Das umfasst drei Teile:

- CircularBuffer Klasse
- Erweiterung der loop- und setup-Methode
- Einführung der Methode _mapHandToByte_

**CircularBuffer**

Die _CircularBuffer_ Klasse wurde als Hilfsklasse geschrieben, um sich die letzten _n_ Gesten zu merken und automatisch aus dem Buffer zu schmeißen beim Hinzufügen neuer Werte. Sind alle Werte gleich gibt die _allEqual_ Methode true aus. Mit _push_ lassen sich neue Gesten eintragen und mit _clear_ alle Werte löschen.

<img src="/pics/cirular-buffer.png" height="50%"/>

**mapHandToByte**

Das ist eine Hilfsmethode, welche ein _const char *_ entgegennimmt und ein byte zurückliefert. Der eingehende Parameter stellt dabei die Geste als string dar. Dieser kann sein:

- nothing
- uncertain
- rock
- paper
- scissors

Die Methode wird benötigt, um über BLE Bytes zu versenden. Dabei werden im ESP32 diese Werte wieder zurückgemapped.

<img src="/pics/mapHandToByte.png" width="40%"/>

**Anpassungen Setup**
Im Setup gibt es nur die Anpassung zum vorgenerierten Code, dass eine BLE Verbindung aktiviert und aufgebaut wird. Dafür wird die Methode _connectToPeripheral_ aufgerufen, welche den Service vom ESP aufruft und zu ihm verbindet.

**Anpassungen Loop**
Die Loop-Methode wurde zum Größtenteil vorgeneriert. Wir haben an dem Punkt angesetzt, wo die Klassifizierung ausgegeben wird. Hier hinzugefügt wurden Variablen, um festzlegen wie hoch der Wert eines Labels sein muss, um als erkannt zu gelten (_UNCERTAIN_BORDER_). Es wird zuerst herausgefunden, welche der Werte der höchste ist, und ob dieser die _UNCERTAIN_BORDER_ überschreitet. Wird zwei mal die gleiche Geste erkannt, wird diese über _BLE_ versendet. Dabei wird geprüft, ob noch eine Verbindung besteht und eine neue Verbindung bei Bedarf aufgebaut. 

<img src="/pics/loop-code.png" width="50%">

**Ausgabe**
Die Ausgabe, die über den Serial-Monitor zu betrachten ist, gibt Informationen über die Klassifizierung aus und die Konnektivität zum _ESP32_. Bei der Klassifizierung ist möglich _nothing_, _paper_, _rock_ und _scissors_. Ist eine der Werte nicht höher als _0.5_ wird _uncertain_ ausgegeben. Die Ausgabe informiert zu aller erst jedoch über die Konnektivität zum _ESP32_. Danach wird ausgegeben, wenn ein Foto aufgenommen wird. Danach der Klassifizierungsstand. Sollte zwei mal der gleiche Wert gelesen werden, wird auch das ausgegeben. Da hierbei geprüft wird, ob noch eine Verbindung besteht, wird der Stand über die Konnektivität wieder ausgegeben.

<img src="/pics/detection-output.png" width="50%">

### 4.2 ESP32 + LED Matrix Setup

#### 4.2.1 Hardware 
| Komponente | Produktname | Hersteller | Link | Preis |
|------------|-------------|------------|------|-------|
| LED Matrix | 32x32 RGB LED MATRIX – 5MM Pitch | Adafruit Industries LLC | https://www.digikey.de/de/products/detail/adafruit-industries-llc/2026/7035028?s=N4IgTCBcDaIIwFYwA4C0Y6NQOQCIgF0BfIA | 32,69 € |
| Microcontroller | ESP32WROOM32E | Espressif Systems | https://www.digikey.de/de/products/detail/espressif-systems/ESP32-DEVKITC-32E/12091810 | 9,35 € |
| Jumper-Kabel | Jumper Wire Kabel 40 STK. je 20 cm F2F Female to Female | AZ-Delivery | https://www.kaufland.de/product/342455919/?utm_source=shopping&utm_medium=non-paid&utm_campaign=pricecomparison&sid=42345840 | 5,29 € (40 Stück) |
| Netzteil | AC-Adapter (Output: 5V, 3A) | Leicke | https://www.otto.de/p/leicke-ull-netzteil-15w-5v-3a-netzteil-besonders-leicht-kurzschluss-ueberspannungs-und-ueberhitzungsschutz-S0C1G0DZ/\#variationId=S0C1G0DZBSMT | 8,99 € |
| Micro-USB-Kabel | Micro-USB-Kabel | Liour | https://amzn.to/3qPDoVF | 4,99 € |
| Stromkabel LED Matrix | Power Cable | Adafruit Industries LLC | Im Lieferumfang der LED-Matrix enthalten | - |
| DC-Buchse | DC Buchse Stecker 5,5 x 2,1mm | LitaElek | https://www.amazon.de/dp/B019HAC6V4/ | 6,49 € (5 Paar) |
| - | - | - | - | Summe: 67,80 € |

#### 4.2.2 Software
Bibliotheken:
* https://github.com/mrfaptastic/ESP32-HUB75-MatrixPanel-DMA
* https://github.com/bitbank2/image_to_c
* https://github.com/bitbank2/AnimatedGIF
* https://github.com/arduino-libraries/ArduinoBLE
* https://github.com/adafruit/Adafruit-GFX-Library 

Code zur BLE Verbindung abgewandelt von https://docs.arduino.cc/tutorials/nano-33-ble-sense/ble-device-to-device

Board Manger für ESP32 bei verwendung der Arduino IDE: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

#### 4.2.3 Bauanleitung
Für das empfangen der Daten über BLE und die Steuerung der LED Matrix kommt ein ESP32 Entwicklungsboard zum Einsatz. Dafür wurden Pins des ESPs mit Jumper Kabeln auf den HUB75 Stecker der LED Matrix verbunden und  im Code entsprechend konfiguriert (genauere Anleitung siehe https://github.com/mrfaptastic/ESP32-HUB75-MatrixPanel-DMA#1-library-installation und Abbildung)

<img src="/pics/esp32_hub75-wiring-graph.png"/>

<img src="/pics/hub75-wiring-picture.png" width="300px"/>

Um die LED Matrix, sowie den ESP mit Strom zu versorgen wird ein Netzteil verwendet. Hierfür wurde das bei der Matrix beigefügte Stromkabel sowie ein Micro-USB Kabel aufgeschnitten und die Enden in einer Klinkenbuchse terminiert.

<img src="/pics/power-adapter-soldering-1.png" width="300px"/>

<img src="/pics/power-adapter-soldering-2.png" width="300px"/>

<img src="/pics/led_matrix-power-adapter.png" width="300px"/>

## 5 Matrix GIFs

### 5.1 GIF Erstellung
Die Erstellung von GIFs sollte in vier Phasen unterteilt werden. 
In der ersten Phase sollten Ideen gefunden werden. Es empfiehlt sich für ein GIF mehrere Ideen zu haben und diese auch umzusetzen, um am Ende die Möglichkeit zu haben sich für die beste Idee zu entscheiden. 
In der zweiten Phase sollten die Layer erstellt werden, wobei jedes Element eines Bildes  idealerweise in einem Layer platziert werden sollte.
Nach dem alle Layer erstellt wurden, können diese in der 3. Phase zu einem Gesamtbild zusammengefügt werden. 
Schließlich werden die Bilder in der 4. Phase in die richtige Reihenfolge gebracht und den passenden Zeitabständen zusammengefügt.

Im weiteren Verlauf wird näher auf die Phasen eingegangen. Hierzu wird der Verlauf beispielhaft an einem GIF erläutert. 

### 5.2 Phase 1
Um Ideen für GIFs zu finden können verschiedene Methoden, wie Brainstorming verwendet werden. Ein Gesamtüberblick des Projektes könnte große Hilfe leisten. Dadurch kann entschieden werden, welche Fragen beantwortet oder welche Schritte des Projektes visualisiert werden sollen.
Im nächsten Schritt können innerhalb der Gruppe erste Ideen diskutiert werden.
Sollte keine Inspiration vorhanden sein lohnt es sich im Internet nach ähnlichen Projekten zu suchen, um die Ideenfindung zu vereinfachen. 

### 5.3 Phase 2
Nach dem die Ideenfindung abgeschlossen ist sollten die einzelnen Elemente der Bilder identifiziert und in alleinstehende Layer platziert werden. 
Gehen wir von dem Szenario aus, dass Stein gegen Schere spielt und gewinnt. Die Schere sollte in einem alleinstehenden Layer sein. Zudem sollte jede Position, der Schere ebenfalls in einem alleinstehenden Layer sein. Das selbe Prinzip sollte für den Stein angewandt werden.
So sind in den folgenden Abbildungen die Layer der Schere und der jeweiligen Positionen zu sehen.

<img src="/pics/gif_doc/scissors_layer.png" width="30%"/> 

Nach dem gleichen Prozess werden die Layer der Steine erstellt, die wie folgt abgebildet werden. 

  <img src="/pics/gif_doc/rock_layer.png" width="30%"/> 

Nachdem die Layer der Hände erstellt wurden, werden die einzelnen Layer des Übergangs zum Ergebnisstatus und das Layer des Ergebnisstatus erstellt. 

  <img src="/pics/gif_doc/übergangs_ergebnis_layer.png" width="30%"/> 


### 5.4 Phase 3
In der 3. Phase werden die Layer  zu Bildern zusammengefügt. 
Nach dem die einzelnen Layer der Hände erstellt sind, werden die Layer der jeweils zugehörigen Positionen zusammengefügt. 


  <img src="/pics/gif_doc/rock_scissors.png" width="30%"/> 


Im Anschluss kann der Hintergrund hinzugefügt werden. Gegebenenfalls können die Farben der einzelnen Elemente mit der Hintergrundfarbe neu abgestimmt werden. 

  <img src="/pics/gif_doc/rock_scissors_farbe.png" width="30%"/> 

### 5.5 Phase 4
Im letzten Schritt werden die Bilder in die richtige Reihenfolge gebracht und ihnen werden die passenden Zeitabständen gegeben, um das fertige GIF zu erstellen.

  <img src="/pics/gif_doc/rock_scissors_gif.png" width="50%"/> 

### 5.6 Verwendete Tools
Zur Erstellung der Layer, Bilder und GIFs wurde die Webseite [pixelart](https://www.pixilart.com/) verwendet. 

Alternativ kann zum Erstellen der Layer und Bilder die Webseite [piskelapp](https://www.piskelapp.com/) genutzt werden. Zum Erstellen des GIFs kann alternativ die Webseite [imgflip](https://imgflip.com/gif-maker) genutzt werden. 

### 5.7 Was sollte beachtet werden?
**Allgemein:**
-	Alle Layer sollten dupliziert werden, bevor sie mit anderen zusammengefügt werden. Dadurch können sie in anderen Bilder wieder verwendet werde. 
-	Gleichmäßige Abstände zum Rand.
-	Gleichmäßige Größen ähnlicher Elemente, um ein stimmiges Gesamtbild zu erlangen. 
-	Den Layern sollten knappe und beschreibenden Namenskonventionen gegeben werden.  

**Pixilart spezifisch:**
-	Die maximal Anzahl an Layer ist 75
-	[pixelart](https://www.pixilart.com/) hat für die Zeiten der einzelnen Bilder nach die der Millisekunde 500 als nächstes 1 Sekunde. Wenn jedoch 700 Millisekunden gebraucht werden, kann das jeweiligen Bild dupliziert werden, um dem ersten 500 Millisekunden und dem zweiten Bild 200 Millisekunden zu geben. 

<p align="center">
    <img src="/pics/gif_doc/zeit_gifs.png" width="50%"/> 
</p>

## 6 Projektergebnisse

Das Projektergebnis umfasst ein trainiertes Modell zur Erkennung von Schere, Stein, Papier als Handgesten vor einem einfarbigen Hintergrund. Dieses Modell läuft auf einen _Arduino Nano 33 BLE Sense_. Das Ergebnis wird erfolgreich auf eine sehr kleine Entfernung über _BLE_ an einen _ESP32_ gesendet, welcher eine _LED Matrix_ ansteuert, um GIFs für jedes Spielergebnis darzustellen. Dabei wird für den CPU zufällig eine Handgeste ausgewählt. Die LED Matrix stellt dabei manchmal die Bilder verzerrt da. Durch den kleinen Speicherplatz ist unser trainiertes Modell nicht gut im Erkennen der Geste _Schere_. Der Rest kann sehr gut erkannt werden.

![](/gifs/setup-gif.gif)
<img src="/pics/setup-idle.jpeg" width="300px"/>
<img src="/pics/setup-above.jpeg" width="300px"/>
<img src="/pics/abschlusspräsi-1.jpeg" width="300px"/>
<img src="/pics/abschlusspräsi-2.jpeg" width="300px"/>
<img src="/pics/abschlusspräsi-3.jpeg" width="300px"/>
<img src="/pics/abschlusspräsi-4.jpeg" width="300px"/>

## 7 Troubleshooting

### 7.1 Speicherprobleme
BLE und und das Klassifizieren von Bildern zieht beträchtlich RAM. Das kann dazu führen, dass nach der Aufnahme eines Bildes nicht genug Ram für das Klassifizierung bereitssteht. Im Laufe des Projekts wurde daher das Trainingsmodell auf das mit der geringsten RAM-Nutzung zurückgegriffen. Wir konnten herausfinden, dass die Programmierumgebung einen Einfluss auf die Optimierung des Codes hat und somit auf die RAM-Nutzung. Anfänglich haben wir mit VSCode gearbeitet, sind dann aber testweise auf die ArduinoIDE gewechselt. Hier wird wahrscheinlich ein anderer Compiler benutzt, der anders optimiert. Wir empfehlen daher bei RAM-Problemen die ArduinoIDE zu verwenden bzw. andere Compieler auszuprobieren.

Zusätlich kann es helfen auf zusätzliche Print-Commands innerhalb des Codes zu verzichten, da auch diese RAM fressen.

### 7.2 TODO Konsti fehlende Libraries HUB75 Matrizen

### 7.3 TODO Konsti Störsignale

### 7.4 Verbindungsabbrüche zwischen Nano und ESP32
Wir sind auf Problemen mit der Konnektivität zwischen dem Nano und dem ESP32 gestoßen wenn wir BLE genutzt haben. Im Normalfall sollte eine stabile Verbindung auf mehrere Meter gehalten werden können. Bei uns war das nicht der Fall und es kam zu vielen Abbrüchen und wir mussten die Komponenten nah beieinander halten. Wir empfehlen also bei Konnektivitätsproblemen die Komponenten nah beieinander zu halten. Der Code der Komponenten wurde so geschrieben, dass auf dieses Problem geachtet wird. Bei jedem Senden einer Handgeste wird solange eine Verbindung versucht aufzubauen bis es klappt.

### 7.5 Gesten werden nicht richtig erkannt
Das Modell wurde auf Datensätzen mit einem simplen Hintergrund trainiert. Das sollte auch nicht auf kompliziertere Hintergrunde angepasst werden. Dafür reicht der Nano nicht aus. Werden die Gesten nicht richtig erkannt, sollte darauf geachtet werden ein einfarbigen Hintergrund zu nehmen.

## 8 Lessons Learned

### 8.1 Begrenzte Ressourcen
BLE verbraucht mehr Ressourcen als gedacht. Das zusammen mit genauso hungrigen Prozessen wie der Klassifizierung von Bildern zu verbinden ist bei wenig RAM-Verfügbarkeit keine gute Idee. Es sollte für solche Projekte auf Komponenten mit ausreichend RAM zurückgegriffen werden. Die Konsequenz davon ist, dass ein anderes Trainingsmodell für die Daten von Nöten ist.

### 8.2 Einfarbiger Hintergrund
Ein einfarbiger Hintergrund lässt das Modell deutlich leichter Gesten erkennen, da die Hand das einzige auf dem Bild ist, welches vom Hintergrund abweichen kann. Das ist für eine speicherschwache Komponente, wie dem Nano, eine sehr gute Wahl.

### 8.3 Verschiedene IDEs
Wir konnten herausfinden, dass VSCode grundsätzlich mehr Speicher verbrauchen lässt bei den Komponenten als wenn der Code mit beispielweise der ArduinoIDE kompiliert wurde. Wir schließen daraus, das verschiedene Compiler genutzt werden. Es gilt also Herauszufinden, welche Compiler wirklich geeignet sind für das Kompilieren von Arduino-Programmen.

### 8.4 Viele Datensätze
Am Anfang des Projekts haben wir mit wenig Daten (~100 Bildern) gearbeitet und schlechte Ergebnisse erzielt. Nach dem Verwenden von neuen Datenquellen (~fast 4000) Bildern konnte das Modell viel besser klassifizieren. Diese Daten haben verschiedene Winkel und Handtypen vereint.

### 8.5 Möglichkeiten der LED-Matrix beachten
Beim Erstellen der GIFs ist aufgefallen, dass nicht alle Farben genauso gut auf der Matrix aussehen wie beim Erstellen. Die Farbtiefe der Matrix ist eingeschränkt. Dabei sollte auf Kontraste geachtet werden.
