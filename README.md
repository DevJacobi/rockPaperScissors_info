# Projektdokumentation *Nano RPS*

- [Projektdokumentation *Nano RPS*](#projektdokumentation-nano-rps)
  - [Einführung](#einführung)
    - [Motivation](#motivation)
    - [Zielstellung](#zielstellung)
    - [Vorhergehensweise](#vorhergehensweise)
  - [Edge Impulse](#edge-impulse)
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

## Setup

### Nano 33 Setup

#### Hardware

#### Software

### ESP32 + LED Matrix Setup

#### Hardware 

#### Software

#### Bauanleitung

## Matrix GIFs

## Projektergebnisse

## Troubleshooting

## Lessons Learned