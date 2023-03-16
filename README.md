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
  - [Konzept](#konzept)
  - [Setup](#setup)
    - [Nano 33 Setup](#nano-33-setup)
      - [Hardware](#hardware)
      - [Software](#software)
    - [ESP32 + LED Matrix Setup](#esp32--led-matrix-setup)
      - [Hardware](#hardware-1)
      - [Software](#software-1)
      - [Bauanleitung](#bauanleitung)
  - [Matrix GIFs](#matrix-gifs)
    - [GIF Erstellung](#gif-erstellung)
    - [Phase 1](#phase-1)
    - [Phase 2](#phase-2)
    - [Phase 3](#phase-3)
    - [Phase 4](#phase-4)
    - [Verwendete Tools](#verwendete-tools)
    - [Was sollte beachtet werden?](#was-sollte-beachtet-werden)
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

<img src="/pics/impulse-learning.png" width="70%"/>

#### Image

Für den Schritt _Image_ wird als einziger Parameter _Color depth_ "Grayscaling" festgelegt. Das ist gut um TODO

#### Transfer Learning
TODO Erklärung was ist Transfer Learning; Was haben wir eingestellt

<img src="/pics/transfer-learning.png" height="50%"/>

## Konzept

Für das Projekt gibt es ein Konzept, welches die verschiedenen Komponenten und die Kommunikation zwischen ihnen darstellt. Das ist in der folgenden Abbildung zu sehen.

<img src="/pics/konzept.png"/>

Zu sehen sind der _Nano_ und _ESP32_ als Hauptkomponenten. Der _Nano_ ist mit einer Kamera, der OV7675, verbunden. Diese soll jede Sekunde ein Bild der Umgebung aufnehmen. Diese Umgebung sollte eine Hand enthalten die eine der Gesten _Schere_, _Stein_ oder _Papier_ macht. Dieses Bild wird auf dem _Nano_ dann vom trainierten Klassifizierungsmodell klassifiziert und per BLE an den ESP32 gesendet. Das Senden erfolgt erst wenn zwei mal die gleiche Geste erkannt wurde. Zu den Gesten zählen:

- scissors (Schere)
- stone (Stein)
- paper (Papier)
- nothing (Leerer Hintergrund)
- uncertain (Wenn sich das Modell nicht zu über 50% sicher ist)

Die Werte werden dabei in Bytes gemapped, um diese über BLE senden zu können. Der _ESP32_ empfängt den Wert und wählt für den Computer einen eigenen Wert. Das Ergebnis wird dann mithilfe von vorher erstellten GIFs auf der Matrix LED dargestellt.

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
TODO

**Anpassungen Loop**
TODO

### ESP32 + LED Matrix Setup

#### Hardware 

#### Software

#### Bauanleitung

## Matrix GIFs

### GIF Erstellung
Die Erstellung von GIFs sollte in vier Phasen unterteilt werden. 
In der 1. Phase sollten Ideen gefunden werden. Es empfiehlt sich für ein GIF mehrere Ideen zu haben und diese auch zu erstellen, um am Ende die Möglichkeit zu haben sich für die beste Idee zu entscheiden. 
In der 2. Phase sollten die Layer erstellt werden. Ein Layer sollte im Ideal Fall nur ein Element eines Bildes enthalten. 
Nach dem alle Layer erstellt wurden, können diese in der 3. Phase zu einem Bild zusammengefügt werden. 
In der 4. Phase werden die GIFs erstellt. Hierbei werden die zuvor erstellten Bilder, mit der zugehörigen Zeit nach einander abgespielt. 

Im weiteren Verlauf wird näher auf die Phasen eingegangen. Hierzu wird der Verlauf der beispielhaft an einem GIF erläutert. 

### Phase 1
Um Ideen für GIFs zu finden können verschiedene Methoden verwendet werden. Ein gesamt Überblick, über das Projekt könnte große Hilfe leisten. Dadurch kann entschieden werden, welche Fragen beantwortet oder welche Schritte des Projektes visualisiert werden sollen.
Im nächsten Schritt können innerhalb der Gruppe ersten Ideen diskutiert werden und aufgeschrieben werden.
Sollte keine Inspiration vorhanden sein lohnt es sich im Internet nach ähnlichen Projekten zu suchen, um die Ideenfindung zu vereinfachen. 

### Phase 2
Nach dem die Ideenfindung abgeschlossen ist sollten die einzelnen Elemente der GIFs identifiziert werden und in alleinstehende Layer eingefügt werden. 
Gehen wir von dem Szenario aus, dass Stein gegen Schere spielt und gewinnt. Die Schere sollte in einem Layer sein und jede Position sollte ebenfalls ein Layer sein. Zudem sollte der Stein in einem Layer sein und auch jede Position des Steins sollte jeweils in einem Layer sein. 
So sind in den folgenden Abbildungen die Layer der Schere und der jeweiligen Positionen zu sehen.

<p align="center">
    <img src="/pics/gif_doc/scissors_layer.png" width="30%"/> 
</p>


Nach dem gleichen Prozess werden die Layer der Steine erstellt, die wie folgt abgebildet werden. 

<p align="center">
    <img src="/pics/gif_doc/rock_layer.png" width="30%"/> 
</p>

Nach dem Layer der Hände erstellt wurden, werden die einzelnen Layer des Übergangs zum Ergebnisstatus und das Layer des Ergebnisstatus erstellt. 

<p align="center">
    <img src="/pics/gif_doc/übergangs_ergebnis_layer.png" width="30%"/> 
</p>

### Phase 3
In der 3. Phase werden die Layer, die nur einzelne Elemente von Bildern enthalten zu Bilder zusammengefügt. 
Nach dem die einzelnen Layer der Hände erstellt sind, werden die Layer der jeweiligen Positionen zusammengefügt. 

<p align="center">
    <img src="/pics/gif_doc/rock_scissors.png" width="30%"/> 
</p>

Im Anschluss kann der Hintergrund hinzugefügt werden. Gegebenenfalls können die Farben der einzelnen Elemente mit der Hintergrundfarbe neu abgestimmt werden. 

<p align="center">
    <img src="/pics/gif_doc/rock_scissors_farbe.png" width="30%"/> 
</p>

### Phase 4
Im letzten Schritt werden die Bilder in die richtige Reihenfolge mit den jeweiligen Zeiten gebracht, um das fertige GIF zu erstellen.

<p align="center">
    <img src="/pics/gif_doc/rock_scissors_gif.png" width="30%"/> 
</p>

### Verwendete Tools
Zur Erstellung der Layer, Bilder und GIFs wurde die Webseite www.pixilart.com verwendet. 

Alternativ kann zum Erstellen der Layer und Bilder die Webseite www.piskelapp.com genutzt werden. Zum Erstellen des GIFs kann alternativ die Webseite imgflip.com/gif-maker genutzt werden. 

### Was sollte beachtet werden?
**Allgemein:**
-	Alle Layer sollten dupliziert werden, bevor sie mit anderen zusammengefügt werden. Dadurch können sie in anderen Bilder wieder verwendet werde. 
-	Gleichmäßige Abstände zum Rand.
-	Gleichmäßige Größen ähnlicher Elemente, um ein stimmiges Gesamtbild zu erlangen. 
-	Den Layern sollten knappe und beschreibenden Namenskonventionen gegeben werden. 


**Pixilart spezifisch:**
-	Die maximal Anzahl an Layer ist 75
-	www.pixilart.com hat für die Zeiten der einzelnen Bilder nach die der Millisekunde 500 als nächstes 1 Sekunde. Wenn jedoch 700 Millisekunden gebraucht werden, kann das jeweiligen Bild dupliziert werden, um dem ersten 500 Millisekunden und dem zweiten Bild 200 Millisekunden zu geben. 

<p align="center">
    <img src="/pics/gif_doc/zeit_gifs.png" width="30%"/> 
</p>

## Projektergebnisse
TODO 
- Bilder einfügen/Gifs
## Troubleshooting
TODO
- Nicht genug RAM -> ArduinoIDE vermutlich liegt das am Compiler
- fehlende Libraries HUB75 Matrizen
- Störsignale
- Konnektivitätsprobleme innerhalb BLE -> Hardware fehlerhaft -> Beide Komponenten weiter zusammen
- Speicherprobleme -> ?

## Lessons Learned
TODO
- Awareness für begrenzte Ressourcen -> BLE verbraucht wohl gut RAM; ML muss daher mit einem geringeren Modell auskommen
- Datensätze mit einfarbigen Hintergrund verlangen dann auch einen simplen Hintergrund zum Erkennen
- verschiedene IDEs optimieren Code anders -> ArduinoIDE hat Ram mehr optimiert als von VSCode
- Man braucht viele Daten mit verschiedenen Arten von Gestenmöglichkeiten
- Farben der GIFs sollten angepasst werden auf die Farben der LED Matrix
