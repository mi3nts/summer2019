# Daily Notes

## Monday June 24, 2019

### Task 1: Disassembling Of Particulate Matter Sensor

Today's work consisted of disassembling particulate matter (PM) sensors. There were two sections within these sensors:

- A portion containing the sensor itself (Optical Particle Counter) and an Argon Arduino Board to manage it.
- A portion containing a GPS, camera module, and the processing units

#### 1.1: Processing Portion (Interior)

**Main Components:**

- G-Mouse GPS Module
- USB 3 Power Hub
- 5.0 MP USB Camera Module
- Linux Computer - Odroid XU4 - central computing unit
- PCB (Argon)
- C1+ Module (Argon) - encrypts data to be sent
- Light Sensor Module

**Dismantling Process**

1. Remove box lid
2. Remove 3D printed frame and all components from box
3. Remove USBs and Ethernet cables
4. Remove USB hub and Ethernet-USB converter
5. Remove wires attached to terminal blocks in PCB
5. Unscrew all circuit boards (XU4 is on underside; PCB is on top; camera and light sensor on side.)
6. Remove GPS module

#### 1.2: Sensor Portion (Exterior)

**Main Components:**

- Steven Sunshields
- Optical Particle Counter (OPC)
- PCB (Manage OPC)

**Dismantling Process:**
1. Free wires from the lid of the interior portion
3. Unscrew and remove all steven sunshields except the base one
4. Unscrew PCB
5. Unplug all wires and cut zipties

**Homework:**
- ~~Obtain basic familiarization with github~~
- ~~Finish daily notes~~
- ~~Chapter 2 Problems of C.M. book~~

___

## Tuesday June 25, 2019

### Task 2: Construction of Main Processing Unit For Shinyei Sensors

Work for today consisted of soldering and wiring circuit boards which would serve as the central management unit for the complete Shinyei<sup>[1]</sup> sensor.

The processes of soldering, applying heat shrinks, and stripping wires was learned today. Adam was expecting to have 5 of these 'guts' (as he referred to them) for the Shinyei built today betweeen the two of us, but we managed to produce 10 before we were burnt out.

Experience was acquired soldering & dealing with construction of permanent circuitry instead of the breadboard stuff done at home.


**Main Components:**
- Seeduino Microcontroleer
- Seeduino Base Shield - interfacing with sensors and OLED display
- Single Cell LiPO Charger (Sunny Buddy) - manages charging of battery from solar panel
- INA219 DC current sensor ([math]\times[\math] 2) - current and voltage sensor, one for each of battery and solar panel
- Molex Connector (4-pin)
- Molex Connector (2-pin) (x2)
- Terminal Block (2-pin) (x2)

#### 2.1: Solder Connections From Seeduino To INA219s

1. Solder a 2-pin terminal block to each of two INA219 current sensors.
2. Cut a 4-pin Molex to Molex connecter in half and attach one end to the outermost Molex receiver on the Seeduino.
3. Split each of the four wires coing from the Molex connecter attached to the Seeduino by soldering two wires onto each of the aforementioned four wires.
4. Solder a red split wire to VCC on an INA219.
5. Solder a black split wire to Gnd on the same INA219.
6. Solder a yellow split wire to Scl on the same INA219.
7. Solder a white split wire to Sda on the same INA219.
8. Repeat the previous four steps with the other INA219.

#### 2.2: Solder Connections From Single Cell LiPO Charger (Sunny Buddy)

9. Cut off a 2-pin Molex connecter from a LiPO battery.
10. Attach the Molex end to the Molex receiver on the Sunny Buddy.
11. Solder the black wire on the Molex wire to "Solar -" on the Sunny Buddy.
12. Solder a wire to "Solar -" from above the circuit board of the Sunny Buddy /9the other end is loose and will act as a central Gnd).
13. Connect the red wire from the 2-pin Molex to Vin- on an INA219.
14. Connect "Solar +" from the Sunny Buddy to Vin- on the other INA219

#### 2.3: Conclusing Steps 

15. Push the Seeduino Base Shield onto the Seeduino and verify that the power switch is set to 3.3V.
16. Solder A0 on the INA219 to which "Solar +" was connected to change the address of an INA219 to have Seeduino be able to distinguish between the INA219s

**Homework:**
- Finish Daily Notes
- Chapter 2 Problems of C.M. Book
- Learn C++ Syntax
- Start TensorFlow Learning

**[1]:** These are cheap air quality sensors that Lakitha and Adam intend on calibrating with machine learning to achieve the same level of accuracy as more expensive sensors. They plan on acquiring data from the expensive sensors and using it to train various ML models. Whichever performs most desirably will be used with the Shinyei sensor data to yield high accuracy with a low cost hardware.
