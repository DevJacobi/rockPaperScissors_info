# Projektdokumentation *Nano RPS*

- [Projektdokumentation *Nano RPS*](#projektdokumentation-nano-rps)
  - [Einführung](#einführung)
    - [Motivation](#motivation)
    - [Zielstellung](#zielstellung)
    - [Vorhergehensweise](#vorhergehensweise)
  - [Edge Impuls](#edge-impuls)
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
- Wollten uns in TinyML, LED Matrix und BLE einarbeiten. Wie man damit zusammenarbeiten kann. RPS hat sich angeboten.

### Zielstellung
- Eine Kamera soll erkennen was wir im Spiel Schere-Stein-Papier für eine Handgeste machen
- Das Erkennen soll geschehen durch ein trainiertes Modell in Edge Impuls
- Die erkannte Geste soll über BLE an einen ESP32 gesendet werden, welcher für den CPU eine Entscheidung trifft und eine Animation für jeden Outcome an der Matrix ausgeben soll

### Vorhergehensweise
- Erstellen des Modells in Edge Impuls
- Zuerst mit eigenen Daten (eigene Hände) genutzt mit jeweils 30 Daten für jede Geste und jeweils 10 Testdatensätze
- Dann haben wir Datensätze benutzt (2 verschiedene)
- Das Modell auf Nano 33 gespielt und getestet
- LED Matrix
- BLE zur Kommunikation

## Edge Impuls

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