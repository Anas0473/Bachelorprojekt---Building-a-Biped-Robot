# Bachelorprojekt – Building a Biped Robot
To-benet robot der efterligner menneskelig gang ved hjælp af 3D-printede komponenter, Arduino-baseret servostyring og billedgenkendelse. Raspberry Pi anvendes til håndsporing via kamera, som sender serielle kommandoer til Arduino for at udløse gangbevægelse.

## Projektoversigt  
3D-printet robot inspireret af det open-source Modular Biped-projekt. Servoer styrer ben og hoved, mens Raspberry Pi registrerer hånden og aktiverer bevægelse gennem billedbehandling i Python. Projektet omfatter design, montering, integration og softwareudvikling.

## Funktionalitet og struktur
- Arduino Nano styrer 9x MG90S servoer via bevægelsessekvenser  
- Raspberry Pi 5 anvender MediaPipe og Picamera2 til håndregistrering  
- Seriel USB-kommunikation med `isMoving`-logik for at undgå overlap  
- Robotten går fremad ét trin, når en hånd detekteres inden for 40 cm

## Hardware og elektronik
- Arduino Nano + specialdesignet PCB (servostyring + strømforsyning)  
- Raspberry Pi 5 monteret i hovedet, tilsluttet via GPIO og USB  
- Servoer initialiseres til 90° og testes individuelt med visuelle markører  
- USB-C PD-modul leverer 15V til to buck converters (5V & 5.1V)  

## Inkluderede filer

- Bachelor_Thesis__Building_a_Biped_Robot.pdf – Fuld rapport med formål, iterativ udviklingsproces og resultater
- Source_code/ – Indeholder al projektkode til både Arduino (bevægelsessekvenser) og Raspberry Pi (håndregistrering)
- `hand_detection.py` – Python-script til håndsporing med MediaPipe (Raspberry Pi)
- `robot_movement/` — Arduino-kode med samlet gangsekvens (udløses ved håndregistrering)  
- `1.right_leg_forward/` – første trin  
- `2.Shift_robot_weight/` – vægtforskydning  
- `3.left_foot_forward/` – venstre fod frem  
- `4.return_to_neutral/` – tilbage til neutral  
