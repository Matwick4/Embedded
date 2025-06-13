# Embedded Software for the Internet of Things
<br>

<h2>📋 TO-DO LIST (segnalate qui eventuali problemi o cose da fare)</h2>
<ol>
  <li>Aggiungere i movimenti del player 2 sia con i pulsanti, per ora rimane fermo (mentre la CPU funziona)</li>
  <li>Quando il gioco funziona, trovare il modo per far comparire il punteggio a schermo (in alto va bene) </li>
  <li>Giunti alla schermata di fine gioco aggiungere comando per tornare al menù principale</li>
  <li>Trovare le librerie per far funzionare Buzzer e Led RGB e, se esistono, importarle nel progetto e capire come funzioano</li>
  <li>Aggiungere Buzzer (quando la pallina rimbalaza o il giocatore segna punto parte un suono)</li>
  <li>Aggiungere LED RGB (nel menu led arcobaleno che cicla i colori, nel gioco si colora di rosso se segna player left, di rosso se segna player right)</li>
</ol>
<br>
<br>

<h2>❓ What is this repository?</h2>
This repository contains the final project for the course <em>Embedded Software for the Internet of Things</em>  held in University of Trento by professor Kasım Sinan Yıldırım during academic year 2024/2025.
<br>
<br>

<h2> 🎮 What this project is about?</h2>
> *Note: This is a preliminary description and may be updated upon project completion.*

This project aims to recreate a **mini portable retro-style game console** using the **MSP432P401R development board** by Texas Instruments. The board is well-suited for this purpose thanks to its integrated peripherals, which include:

- A display
- Buttons
- An analog stick
- A buzzer
- On-board LEDs

The console runs two classic arcade-inspired games: **Pong** and **Snake**, taking cues from the iconic style and simplicity of 1970s arcade machines.
<br>
<br>

### 🕹️ Pong
Pong leverages both the left analog stick and the two right-side buttons on the MSP432 board. The paddle (i.e., the vertical bar that players move to hit the ball) can be controlled using either input method, supporting intuitive "UP" and "DOWN" movements.

- **Single Player Mode**: Play against a basic CPU opponent.
- **Two Player Mode**: Challenge a friend using shared controls.

This setup allows for both accessible gameplay and a faithful recreation of the original arcade experience.
<br>
<br>

### 🐍 Snake
Snake fully utilizes the analog stick, enabling smooth movement in all four cardinal directions. The implementation showcases the potential of the MSP432 board’s input capabilities.

---

This project combines embedded systems programming with retro game design to deliver a fun and educational hands-on application of the MSP432 platform.
<br>
<br>

<h2>⚙️ Hardware Platform </h2>
This project has been developed for the MSP432P401R board and the BoosterPack MKII by Texas Instruments.<br>
Besides this, hardware-dependent code is isolated in its own folder so that porting to other platforms does not require rewrting the application logic.
<br>
<br>

<h2>🔧 Tools used </h2>
Code Composer Studio has been used for developing, uploading the software to the platform and debugging. .
To communicate with the peripherals we have also used libraries provided by Texas Instruments in the MSP432 SDK.
<br>
<br>

<h2>👤 Team members </h2>
<ui>
<li>Lorenzo Cortese</li>
<li>Matteo Cornacchia</li>
<li>Luca Moretto</li>
<li>Matteo Ferrari</li>

