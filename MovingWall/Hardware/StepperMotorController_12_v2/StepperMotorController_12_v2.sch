EESchema Schematic File Version 2
LIBS:StepperMotorController_12_v2-rescue
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:StepperMotorController_12_v2-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 4
Title "Stepper Motor Controller"
Date "2015-10-14"
Rev "3"
Comp "Jo Fairfax Studio"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
NoConn ~ 6250 7050
Text Notes 6100 7250 0    60   ~ 0
PCB Size
$Sheet
S 8800 1650 800  950 
U 551AF81E
F0 "MotorDrivers1" 50
F1 "MotorDrivers.sch" 50
F2 "STEP_IN1" I L 8800 2000 60 
F3 "STEP_IN2" I L 8800 2100 60 
F4 "STEP_IN3" I L 8800 2200 60 
F5 "STEP_IN4" I L 8800 2300 60 
F6 "STEP_V+" I L 8800 1800 60 
$EndSheet
$Comp
L R-RESCUE-StepperMotorController_12_v2 R3
U 1 1 551B2385
P 8150 3200
F 0 "R3" V 8230 3200 40  0000 C CNN
F 1 "330" V 8157 3201 40  0000 C CNN
F 2 "reinnovation-footprints:R3-LARGE_PADS_0_8_hole" V 8080 3200 30  0001 C CNN
F 3 "~" H 8150 3200 30  0000 C CNN
F 4 "Value" H 8150 3200 60  0001 C CNN "Description"
F 5 "Value" H 8150 3200 60  0001 C CNN "Notes"
F 6 "Value" H 8150 3200 60  0001 C CNN "Manufacturer"
F 7 "Value" H 8150 3200 60  0001 C CNN "Manufacturer Part No"
F 8 "Value" H 8150 3200 60  0001 C CNN "Supplier 1"
F 9 "Value" H 8150 3200 60  0001 C CNN "Supplier 1 Part No"
F 10 "Value" H 8150 3200 60  0001 C CNN "Supplier 2"
F 11 "Value" H 8150 3200 60  0001 C CNN "Supplier 2 Part No"
	1    8150 3200
	1    0    0    -1  
$EndComp
$Comp
L LED-RESCUE-StepperMotorController_12_v2 D3
U 1 1 551B23C1
P 8150 2650
F 0 "D3" H 8150 2750 50  0000 C CNN
F 1 "LED" H 8400 2550 50  0000 C CNN
F 2 "reinnovation-footprints:led-LED3MM_matt" H 8150 2650 60  0001 C CNN
F 3 "~" H 8150 2650 60  0001 C CNN
F 4 "Value" H 8150 2650 60  0001 C CNN "Description"
F 5 "Value" H 8150 2650 60  0001 C CNN "Notes"
F 6 "Value" H 8150 2650 60  0001 C CNN "Manufacturer"
F 7 "Value" H 8150 2650 60  0001 C CNN "Manufacturer Part No"
F 8 "Value" H 8150 2650 60  0001 C CNN "Supplier 1"
F 9 "Value" H 8150 2650 60  0001 C CNN "Supplier 1 Part No"
F 10 "Value" H 8150 2650 60  0001 C CNN "Supplier 2"
F 11 "Value" H 8150 2650 60  0001 C CNN "Supplier 2 Part No"
	1    8150 2650
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-StepperMotorController_12_v2 R1
U 1 1 551B24DC
P 7950 3200
F 0 "R1" V 8030 3200 40  0000 C CNN
F 1 "330" V 7957 3201 40  0000 C CNN
F 2 "reinnovation-footprints:R3-LARGE_PADS_0_8_hole" V 7880 3200 30  0001 C CNN
F 3 "~" H 7950 3200 30  0000 C CNN
F 4 "Value" H 7950 3200 60  0001 C CNN "Description"
F 5 "Value" H 7950 3200 60  0001 C CNN "Notes"
F 6 "Value" H 7950 3200 60  0001 C CNN "Manufacturer"
F 7 "Value" H 7950 3200 60  0001 C CNN "Manufacturer Part No"
F 8 "Value" H 7950 3200 60  0001 C CNN "Supplier 1"
F 9 "Value" H 7950 3200 60  0001 C CNN "Supplier 1 Part No"
F 10 "Value" H 7950 3200 60  0001 C CNN "Supplier 2"
F 11 "Value" H 7950 3200 60  0001 C CNN "Supplier 2 Part No"
	1    7950 3200
	1    0    0    -1  
$EndComp
$Comp
L LED-RESCUE-StepperMotorController_12_v2 D1
U 1 1 551B24E2
P 7950 2650
F 0 "D1" H 7950 2750 50  0000 C CNN
F 1 "LED" H 7950 2550 50  0000 C CNN
F 2 "reinnovation-footprints:led-LED3MM_matt" H 7950 2650 60  0001 C CNN
F 3 "~" H 7950 2650 60  0001 C CNN
F 4 "Value" H 7950 2650 60  0001 C CNN "Description"
F 5 "Value" H 7950 2650 60  0001 C CNN "Notes"
F 6 "Value" H 7950 2650 60  0001 C CNN "Manufacturer"
F 7 "Value" H 7950 2650 60  0001 C CNN "Manufacturer Part No"
F 8 "Value" H 7950 2650 60  0001 C CNN "Supplier 1"
F 9 "Value" H 7950 2650 60  0001 C CNN "Supplier 1 Part No"
F 10 "Value" H 7950 2650 60  0001 C CNN "Supplier 2"
F 11 "Value" H 7950 2650 60  0001 C CNN "Supplier 2 Part No"
	1    7950 2650
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-StepperMotorController_12_v2 R7
U 1 1 551B2506
P 8550 3200
F 0 "R7" V 8630 3200 40  0000 C CNN
F 1 "330" V 8557 3201 40  0000 C CNN
F 2 "reinnovation-footprints:R3-LARGE_PADS_0_8_hole" V 8480 3200 30  0001 C CNN
F 3 "~" H 8550 3200 30  0000 C CNN
F 4 "Value" H 8550 3200 60  0001 C CNN "Description"
F 5 "Value" H 8550 3200 60  0001 C CNN "Notes"
F 6 "Value" H 8550 3200 60  0001 C CNN "Manufacturer"
F 7 "Value" H 8550 3200 60  0001 C CNN "Manufacturer Part No"
F 8 "Value" H 8550 3200 60  0001 C CNN "Supplier 1"
F 9 "Value" H 8550 3200 60  0001 C CNN "Supplier 1 Part No"
F 10 "Value" H 8550 3200 60  0001 C CNN "Supplier 2"
F 11 "Value" H 8550 3200 60  0001 C CNN "Supplier 2 Part No"
	1    8550 3200
	1    0    0    -1  
$EndComp
$Comp
L LED-RESCUE-StepperMotorController_12_v2 D7
U 1 1 551B250C
P 8550 2650
F 0 "D7" H 8550 2750 50  0000 C CNN
F 1 "LED" H 8800 2550 50  0000 C CNN
F 2 "reinnovation-footprints:led-LED3MM_matt" H 8550 2650 60  0001 C CNN
F 3 "~" H 8550 2650 60  0001 C CNN
F 4 "Value" H 8550 2650 60  0001 C CNN "Description"
F 5 "Value" H 8550 2650 60  0001 C CNN "Notes"
F 6 "Value" H 8550 2650 60  0001 C CNN "Manufacturer"
F 7 "Value" H 8550 2650 60  0001 C CNN "Manufacturer Part No"
F 8 "Value" H 8550 2650 60  0001 C CNN "Supplier 1"
F 9 "Value" H 8550 2650 60  0001 C CNN "Supplier 1 Part No"
F 10 "Value" H 8550 2650 60  0001 C CNN "Supplier 2"
F 11 "Value" H 8550 2650 60  0001 C CNN "Supplier 2 Part No"
	1    8550 2650
	0    1    1    0   
$EndComp
$Comp
L R-RESCUE-StepperMotorController_12_v2 R5
U 1 1 551B2512
P 8350 3200
F 0 "R5" V 8430 3200 40  0000 C CNN
F 1 "330" V 8357 3201 40  0000 C CNN
F 2 "reinnovation-footprints:R3-LARGE_PADS_0_8_hole" V 8280 3200 30  0001 C CNN
F 3 "~" H 8350 3200 30  0000 C CNN
F 4 "Value" H 8350 3200 60  0001 C CNN "Description"
F 5 "Value" H 8350 3200 60  0001 C CNN "Notes"
F 6 "Value" H 8350 3200 60  0001 C CNN "Manufacturer"
F 7 "Value" H 8350 3200 60  0001 C CNN "Manufacturer Part No"
F 8 "Value" H 8350 3200 60  0001 C CNN "Supplier 1"
F 9 "Value" H 8350 3200 60  0001 C CNN "Supplier 1 Part No"
F 10 "Value" H 8350 3200 60  0001 C CNN "Supplier 2"
F 11 "Value" H 8350 3200 60  0001 C CNN "Supplier 2 Part No"
	1    8350 3200
	1    0    0    -1  
$EndComp
$Comp
L LED-RESCUE-StepperMotorController_12_v2 D5
U 1 1 551B2518
P 8350 2650
F 0 "D5" H 8350 2750 50  0000 C CNN
F 1 "LED" H 8600 2550 50  0000 C CNN
F 2 "reinnovation-footprints:led-LED3MM_matt" H 8350 2650 60  0001 C CNN
F 3 "~" H 8350 2650 60  0001 C CNN
F 4 "Value" H 8350 2650 60  0001 C CNN "Description"
F 5 "Value" H 8350 2650 60  0001 C CNN "Notes"
F 6 "Value" H 8350 2650 60  0001 C CNN "Manufacturer"
F 7 "Value" H 8350 2650 60  0001 C CNN "Manufacturer Part No"
F 8 "Value" H 8350 2650 60  0001 C CNN "Supplier 1"
F 9 "Value" H 8350 2650 60  0001 C CNN "Supplier 1 Part No"
F 10 "Value" H 8350 2650 60  0001 C CNN "Supplier 2"
F 11 "Value" H 8350 2650 60  0001 C CNN "Supplier 2 Part No"
	1    8350 2650
	0    1    1    0   
$EndComp
$Comp
L GND-RESCUE-StepperMotorController_12_v2 #PWR01
U 1 1 551B255D
P 8250 3600
F 0 "#PWR01" H 8250 3600 30  0001 C CNN
F 1 "GND" H 8250 3530 30  0001 C CNN
F 2 "" H 8250 3600 60  0000 C CNN
F 3 "" H 8250 3600 60  0000 C CNN
	1    8250 3600
	1    0    0    -1  
$EndComp
$Sheet
S 2900 1450 1150 1000
U 551B28A0
F0 "PowerSupply" 50
F1 "PowerSupply.sch" 50
F2 "V_SUPPLY+" I L 2900 1750 60 
F3 "V_REG+" O R 4050 1950 60 
F4 "V_SUPPLY_GND" I L 2900 2150 60 
F5 "V_REG_GND" O R 4050 2300 60 
$EndSheet
$Comp
L CP1-RESCUE-StepperMotorController_12_v2 C3
U 1 1 551B33BA
P 6150 3200
F 0 "C3" H 6200 3300 50  0000 L CNN
F 1 "10uF" H 6200 3100 50  0000 L CNN
F 2 "reinnovation-footprints:C2V8_large_pads" H 6150 3200 60  0001 C CNN
F 3 "~" H 6150 3200 60  0000 C CNN
F 4 "Value" H 6150 3200 60  0001 C CNN "Description"
F 5 "Value" H 6150 3200 60  0001 C CNN "Notes"
F 6 "Value" H 6150 3200 60  0001 C CNN "Manufacturer"
F 7 "Value" H 6150 3200 60  0001 C CNN "Manufacturer Part No"
F 8 "Value" H 6150 3200 60  0001 C CNN "Supplier 1"
F 9 "Value" H 6150 3200 60  0001 C CNN "Supplier 1 Part No"
F 10 "Value" H 6150 3200 60  0001 C CNN "Supplier 2"
F 11 "Value" H 6150 3200 60  0001 C CNN "Supplier 2 Part No"
	1    6150 3200
	-1   0    0    1   
$EndComp
$Comp
L CONN_2-RESCUE-StepperMotorController_12_v2 P4
U 1 1 551B37F8
P 1450 1900
F 0 "P4" V 1400 1900 40  0000 C CNN
F 1 "POWER_IN" V 1500 1900 40  0000 C CNN
F 2 "reinnovation-footprints:SIL-2_screw_terminal" H 1450 1900 60  0001 C CNN
F 3 "" H 1450 1900 60  0000 C CNN
	1    1450 1900
	-1   0    0    1   
$EndComp
$Comp
L CONN_5 P6
U 1 1 551B3A23
P 5000 5300
F 0 "P6" V 4950 5300 50  0000 C CNN
F 1 "DETECT_IN1" V 5050 5300 50  0000 C CNN
F 2 "reinnovation-footprints:SIL-5_JST_5WAY" H 5000 5300 60  0001 C CNN
F 3 "" H 5000 5300 60  0000 C CNN
	1    5000 5300
	-1   0    0    1   
$EndComp
$Comp
L GND-RESCUE-StepperMotorController_12_v2 #PWR02
U 1 1 551B3CAB
P 4300 2550
F 0 "#PWR02" H 4300 2550 30  0001 C CNN
F 1 "GND" H 4300 2480 30  0001 C CNN
F 2 "" H 4300 2550 60  0000 C CNN
F 3 "" H 4300 2550 60  0000 C CNN
	1    4300 2550
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-StepperMotorController_12_v2 #PWR03
U 1 1 551B457F
P 5500 5650
F 0 "#PWR03" H 5500 5650 30  0001 C CNN
F 1 "GND" H 5500 5580 30  0001 C CNN
F 2 "" H 5500 5650 60  0000 C CNN
F 3 "" H 5500 5650 60  0000 C CNN
	1    5500 5650
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR04
U 1 1 551D3773
P 4550 1900
F 0 "#PWR04" H 4550 1990 20  0001 C CNN
F 1 "+5V" H 4550 1990 30  0000 C CNN
F 2 "" H 4550 1900 60  0000 C CNN
F 3 "" H 4550 1900 60  0000 C CNN
	1    4550 1900
	1    0    0    -1  
$EndComp
$Comp
L Arduino_Nano_Header J1
U 1 1 551D3DF3
P 5150 3700
F 0 "J1" H 5150 4500 60  0000 C CNN
F 1 "ARDUINO_NANO_HEADER" H 5150 2900 60  0000 C CNN
F 2 "reinnovation-footprints:DIP_30_600_NANO" H 5150 3700 60  0001 C CNN
F 3 "" H 5150 3700 60  0000 C CNN
	1    5150 3700
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-StepperMotorController_12_v2 #PWR06
U 1 1 551D4012
P 6400 3000
F 0 "#PWR06" H 6400 3000 30  0001 C CNN
F 1 "GND" H 6400 2930 30  0001 C CNN
F 2 "" H 6400 3000 60  0000 C CNN
F 3 "" H 6400 3000 60  0000 C CNN
	1    6400 3000
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR07
U 1 1 551D4021
P 6950 3400
F 0 "#PWR07" H 6950 3490 20  0001 C CNN
F 1 "+5V" H 6950 3490 30  0000 C CNN
F 2 "" H 6950 3400 60  0000 C CNN
F 3 "" H 6950 3400 60  0000 C CNN
	1    6950 3400
	1    0    0    -1  
$EndComp
$Sheet
S 8800 4100 800  1000
U 551E9614
F0 "MotorDrivers2" 50
F1 "MotorDrivers.sch" 50
F2 "STEP_IN1" I L 8800 4450 60 
F3 "STEP_IN2" I L 8800 4550 60 
F4 "STEP_IN3" I L 8800 4650 60 
F5 "STEP_IN4" I L 8800 4750 60 
F6 "STEP_V+" I L 8800 4250 60 
$EndSheet
$Comp
L CONN_3 K3
U 1 1 551EAB0E
P 3850 3150
F 0 "K3" V 3800 3150 50  0000 C CNN
F 1 "CONN_3" V 3900 3150 40  0000 C CNN
F 2 "reinnovation-footprints:SIL-3_SOLDER" H 3850 3150 60  0001 C CNN
F 3 "" H 3850 3150 60  0000 C CNN
	1    3850 3150
	0    -1   -1   0   
$EndComp
$Comp
L CONN_3 K4
U 1 1 551EAB1D
P 3850 3950
F 0 "K4" V 3800 3950 50  0000 C CNN
F 1 "CONN_3" V 3900 3950 40  0000 C CNN
F 2 "reinnovation-footprints:SIL-3_SOLDER" H 3850 3950 60  0001 C CNN
F 3 "" H 3850 3950 60  0000 C CNN
	1    3850 3950
	0    -1   -1   0   
$EndComp
$Comp
L CONN_3 K2
U 1 1 551EAB2C
P 3500 3950
F 0 "K2" V 3450 3950 50  0000 C CNN
F 1 "CONN_3" V 3550 3950 40  0000 C CNN
F 2 "reinnovation-footprints:SIL-3_SOLDER" H 3500 3950 60  0001 C CNN
F 3 "" H 3500 3950 60  0000 C CNN
	1    3500 3950
	0    -1   -1   0   
$EndComp
$Comp
L CONN_3 K1
U 1 1 551EAB3B
P 3500 3150
F 0 "K1" V 3450 3150 50  0000 C CNN
F 1 "CONN_3" V 3550 3150 40  0000 C CNN
F 2 "reinnovation-footprints:SIL-3_SOLDER" H 3500 3150 60  0001 C CNN
F 3 "" H 3500 3150 60  0000 C CNN
	1    3500 3150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7950 2950 7950 2850
Wire Wire Line
	8150 2950 8150 2850
Wire Wire Line
	8350 2950 8350 2850
Wire Wire Line
	8550 2950 8550 2850
Wire Wire Line
	7950 3450 7950 3550
Wire Wire Line
	7950 3550 8550 3550
Wire Wire Line
	8550 3550 8550 3450
Wire Wire Line
	8250 3600 8250 3550
Connection ~ 8250 3550
Wire Wire Line
	8150 3450 8150 3550
Connection ~ 8150 3550
Wire Wire Line
	8350 3450 8350 3550
Connection ~ 8350 3550
Wire Wire Line
	8550 2450 8550 2300
Wire Wire Line
	6050 2300 8800 2300
Wire Wire Line
	6000 2200 8800 2200
Wire Wire Line
	8350 2200 8350 2450
Wire Wire Line
	8150 2450 8150 2100
Wire Wire Line
	5950 2100 8800 2100
Wire Wire Line
	5900 2000 8800 2000
Wire Wire Line
	7950 2000 7950 2450
Wire Wire Line
	2350 1750 2900 1750
Wire Wire Line
	2700 2000 2700 2450
Wire Wire Line
	2700 2150 2900 2150
Wire Wire Line
	4300 2300 4300 2550
Wire Wire Line
	5400 5500 5500 5500
Wire Wire Line
	5500 5500 5500 5650
Wire Wire Line
	4050 1950 5000 1950
Wire Wire Line
	4550 1950 4550 1900
Wire Wire Line
	8800 1800 5000 1800
Wire Wire Line
	5000 1800 5000 1950
Connection ~ 4550 1950
Wire Wire Line
	5400 5100 6250 5100
Wire Wire Line
	5500 3300 5800 3300
Wire Wire Line
	5800 3300 5800 3450
Wire Wire Line
	5800 3450 6450 3450
Wire Wire Line
	6150 3450 6150 3400
Wire Wire Line
	5500 3100 5750 3100
Wire Wire Line
	5750 3100 5750 2950
Wire Wire Line
	5750 2950 6400 2950
Wire Wire Line
	6150 2950 6150 3000
Wire Wire Line
	6400 2950 6400 3000
Connection ~ 6150 2950
Connection ~ 6150 3450
Wire Wire Line
	5800 5400 5400 5400
Wire Wire Line
	5800 4100 5800 5400
Wire Wire Line
	5800 4100 5500 4100
Wire Wire Line
	5850 5300 5400 5300
Wire Wire Line
	5850 4000 5850 5300
Wire Wire Line
	5850 4000 5500 4000
Wire Wire Line
	5900 5200 5400 5200
Wire Wire Line
	5900 3900 5900 5200
Wire Wire Line
	5900 3900 5500 3900
Wire Wire Line
	4800 3700 4650 3700
Wire Wire Line
	4650 3700 4650 2750
Wire Wire Line
	4650 2750 5900 2750
Wire Wire Line
	5900 2750 5900 2000
Connection ~ 7950 2000
Wire Wire Line
	5950 2100 5950 2700
Wire Wire Line
	5950 2700 4600 2700
Wire Wire Line
	4600 2700 4600 3800
Wire Wire Line
	4600 3800 4800 3800
Connection ~ 8150 2100
Wire Wire Line
	4800 3900 4550 3900
Wire Wire Line
	4550 3900 4550 2650
Wire Wire Line
	4550 2650 6000 2650
Wire Wire Line
	6000 2650 6000 2200
Connection ~ 8350 2200
Wire Wire Line
	6050 2300 6050 2600
Wire Wire Line
	6050 2600 4500 2600
Wire Wire Line
	4500 2600 4500 4000
Wire Wire Line
	4500 4000 4800 4000
Connection ~ 8550 2300
Wire Wire Line
	4050 2300 4300 2300
Wire Wire Line
	6300 4450 8800 4450
Wire Wire Line
	6350 4550 8800 4550
Wire Wire Line
	6400 4650 8800 4650
Wire Wire Line
	3850 4750 8800 4750
Wire Wire Line
	8800 4250 7550 4250
Wire Wire Line
	7550 4250 7550 1800
Connection ~ 7550 1800
Wire Wire Line
	6300 4600 6300 4450
Wire Wire Line
	3200 4600 6300 4600
Wire Wire Line
	6350 4650 6350 4550
Wire Wire Line
	3250 4650 6350 4650
Wire Wire Line
	6400 4700 6400 4650
Wire Wire Line
	3500 4700 6400 4700
Wire Wire Line
	3200 4600 3200 3700
Wire Wire Line
	3200 3700 3500 3700
Wire Wire Line
	3500 3700 3500 3500
Wire Wire Line
	3250 4650 3250 3750
Wire Wire Line
	3250 3750 3850 3750
Wire Wire Line
	3850 3750 3850 3500
Wire Wire Line
	3500 4700 3500 4300
Wire Wire Line
	3850 4750 3850 4300
Wire Wire Line
	3950 4300 3950 4400
Wire Wire Line
	3950 4400 4800 4400
Wire Wire Line
	3600 4300 3600 4350
Wire Wire Line
	3600 4350 4600 4350
Wire Wire Line
	4600 4350 4600 4300
Wire Wire Line
	4600 4300 4800 4300
Wire Wire Line
	4800 4200 4050 4200
Wire Wire Line
	4050 4200 4050 3550
Wire Wire Line
	4050 3550 3950 3550
Wire Wire Line
	3950 3550 3950 3500
Wire Wire Line
	4800 4100 4150 4100
Wire Wire Line
	4150 4100 4150 3700
Wire Wire Line
	4150 3700 3600 3700
Wire Wire Line
	3600 3700 3600 3500
Wire Wire Line
	4650 3600 3400 3600
Wire Wire Line
	3400 3600 3400 3500
Connection ~ 4650 3600
Wire Wire Line
	4600 3650 3750 3650
Wire Wire Line
	3750 3650 3750 3500
Connection ~ 4600 3650
Wire Wire Line
	4550 3700 4200 3700
Wire Wire Line
	4200 3700 4200 4450
Wire Wire Line
	4200 4450 3400 4450
Wire Wire Line
	3400 4450 3400 4300
Connection ~ 4550 3700
Wire Wire Line
	4500 3750 4300 3750
Wire Wire Line
	4300 3750 4300 4550
Wire Wire Line
	4300 4550 3750 4550
Wire Wire Line
	3750 4550 3750 4300
Connection ~ 4500 3750
$Comp
L CONN_2-RESCUE-StepperMotorController_12_v2 P1
U 1 1 551EBCD3
P 2150 4150
F 0 "P1" V 2100 4150 40  0000 C CNN
F 1 "RESET_SW" V 2200 4150 40  0000 C CNN
F 2 "reinnovation-footprints:SIL-2_screw_terminal" H 2150 4150 60  0001 C CNN
F 3 "" H 2150 4150 60  0000 C CNN
	1    2150 4150
	-1   0    0    1   
$EndComp
$Comp
L CONN_2-RESCUE-StepperMotorController_12_v2 P2
U 1 1 551EBD0C
P 2150 4550
F 0 "P2" V 2100 4550 40  0000 C CNN
F 1 "SW1" V 2200 4550 40  0000 C CNN
F 2 "matts_components:SIL-2_lg_pad_1mm" H 2150 4550 60  0001 C CNN
F 3 "" H 2150 4550 60  0000 C CNN
	1    2150 4550
	-1   0    0    1   
$EndComp
$Comp
L CONN_2-RESCUE-StepperMotorController_12_v2 P3
U 1 1 551EBD1B
P 2150 4950
F 0 "P3" V 2100 4950 40  0000 C CNN
F 1 "SW2" V 2200 4950 40  0000 C CNN
F 2 "matts_components:SIL-2_lg_pad_1mm" H 2150 4950 60  0001 C CNN
F 3 "" H 2150 4950 60  0000 C CNN
	1    2150 4950
	-1   0    0    1   
$EndComp
Wire Wire Line
	2500 4250 2700 4250
Wire Wire Line
	2700 4250 2700 5200
Wire Wire Line
	2500 5050 2700 5050
Connection ~ 2700 5050
Wire Wire Line
	2500 4650 2700 4650
Connection ~ 2700 4650
Wire Wire Line
	2500 4850 3050 4850
Wire Wire Line
	3050 4850 3050 3800
Wire Wire Line
	3050 3800 2600 3800
Wire Wire Line
	2600 3800 2600 2950
Wire Wire Line
	4150 2950 4150 3550
Wire Wire Line
	4150 3550 4750 3550
Wire Wire Line
	4750 3550 4750 3600
Wire Wire Line
	4750 3600 4800 3600
Wire Wire Line
	4800 3500 4200 3500
Wire Wire Line
	4200 3500 4200 2900
Wire Wire Line
	2550 2900 2550 3850
Wire Wire Line
	2550 3850 3000 3850
Wire Wire Line
	3000 3850 3000 4450
Wire Wire Line
	3000 4450 2500 4450
Wire Wire Line
	2500 4050 2500 2850
Wire Wire Line
	4250 2850 4250 3400
Wire Wire Line
	4250 3400 4800 3400
$Comp
L GND-RESCUE-StepperMotorController_12_v2 #PWR08
U 1 1 551EBD74
P 2700 5200
F 0 "#PWR08" H 2700 5200 30  0001 C CNN
F 1 "GND" H 2700 5130 30  0001 C CNN
F 2 "" H 2700 5200 60  0000 C CNN
F 3 "" H 2700 5200 60  0000 C CNN
	1    2700 5200
	1    0    0    -1  
$EndComp
NoConn ~ 5500 3400
NoConn ~ 5500 3500
NoConn ~ 5500 3600
NoConn ~ 5500 3700
NoConn ~ 4800 3200
$Comp
L GND-RESCUE-StepperMotorController_12_v2 #PWR09
U 1 1 55A283C0
P 4700 3300
F 0 "#PWR09" H 4700 3300 30  0001 C CNN
F 1 "GND" H 4700 3230 30  0001 C CNN
F 2 "" H 4700 3300 60  0000 C CNN
F 3 "" H 4700 3300 60  0000 C CNN
	1    4700 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 3300 4700 3250
Wire Wire Line
	4700 3250 4750 3250
Wire Wire Line
	4750 3250 4750 3300
Wire Wire Line
	4750 3300 4800 3300
Wire Wire Line
	4400 3100 4800 3100
Wire Wire Line
	4450 3000 4800 3000
$Comp
L CONN_4 P5
U 1 1 55A28B66
P 1350 3100
F 0 "P5" V 1300 3100 50  0000 C CNN
F 1 "SERIAL" V 1400 3100 50  0000 C CNN
F 2 "reinnovation-footprints:SIL-4_large_pad" H 1350 3100 60  0001 C CNN
F 3 "" H 1350 3100 60  0000 C CNN
	1    1350 3100
	-1   0    0    1   
$EndComp
Wire Wire Line
	2600 2950 4150 2950
Wire Wire Line
	4200 2900 2550 2900
Wire Wire Line
	2500 2850 4250 2850
$Comp
L GND-RESCUE-StepperMotorController_12_v2 #PWR010
U 1 1 55A2A5A7
P 1800 3350
F 0 "#PWR010" H 1800 3350 30  0001 C CNN
F 1 "GND" H 1800 3280 30  0001 C CNN
F 2 "" H 1800 3350 60  0000 C CNN
F 3 "" H 1800 3350 60  0000 C CNN
	1    1800 3350
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR011
U 1 1 55A2A5B6
P 1800 2850
F 0 "#PWR011" H 1800 2940 20  0001 C CNN
F 1 "+5V" H 1800 2940 30  0000 C CNN
F 2 "" H 1800 2850 60  0000 C CNN
F 3 "" H 1800 2850 60  0000 C CNN
	1    1800 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 2950 1800 2950
Wire Wire Line
	1800 2950 1800 2850
Wire Wire Line
	1800 3350 1800 3250
Wire Wire Line
	1800 3250 1700 3250
Wire Wire Line
	4450 3000 4450 2650
Wire Wire Line
	4450 2650 1900 2650
Wire Wire Line
	1900 2650 1900 3050
Wire Wire Line
	1900 3050 1700 3050
Wire Wire Line
	1700 3150 1950 3150
Wire Wire Line
	1950 3150 1950 2700
Wire Wire Line
	1950 2700 4400 2700
Wire Wire Line
	4400 2700 4400 3100
$Comp
L CONN_1 MH1
U 1 1 516547CF
P 6400 7050
F 0 "MH1" H 6480 7050 40  0000 L CNN
F 1 "CONN_1" H 6400 7105 30  0001 C CNN
F 2 "reinnovation-footprints:PCB_85x120_4hole" H 6400 7050 60  0001 C CNN
F 3 "" H 6400 7050 60  0001 C CNN
	1    6400 7050
	1    0    0    -1  
$EndComp
$Comp
L DIODE D2
U 1 1 55C8DA5E
P 6650 3450
F 0 "D2" H 6650 3550 40  0000 C CNN
F 1 "1N4001" H 6650 3350 40  0000 C CNN
F 2 "matts_components:D3_lg_pad" H 6650 3450 60  0001 C CNN
F 3 "" H 6650 3450 60  0000 C CNN
	1    6650 3450
	-1   0    0    1   
$EndComp
Wire Wire Line
	6850 3450 6950 3450
Wire Wire Line
	6950 3450 6950 3400
$Comp
L CONN_2-RESCUE-StepperMotorController_12_v2 P19
U 1 1 55C90FE3
P 1450 2350
F 0 "P19" V 1400 2350 40  0000 C CNN
F 1 "POWER_OUT" V 1500 2350 40  0000 C CNN
F 2 "reinnovation-footprints:SIL-2_screw_terminal" H 1450 2350 60  0001 C CNN
F 3 "" H 1450 2350 60  0000 C CNN
F 4 "Value" H 1450 2350 60  0001 C CNN "Description"
F 5 "Value" H 1450 2350 60  0001 C CNN "Notes"
F 6 "Value" H 1450 2350 60  0001 C CNN "Manufacturer"
F 7 "Value" H 1450 2350 60  0001 C CNN "Manufacturer Part No"
F 8 "Value" H 1450 2350 60  0001 C CNN "Supplier 1"
F 9 "Value" H 1450 2350 60  0001 C CNN "Supplier 1 Part No"
F 10 "Value" H 1450 2350 60  0001 C CNN "Supplier 2"
F 11 "Value" H 1450 2350 60  0001 C CNN "Supplier 2 Part No"
	1    1450 2350
	-1   0    0    1   
$EndComp
Wire Wire Line
	2700 2450 1800 2450
Wire Wire Line
	2700 2000 1800 2000
Connection ~ 2700 2150
Wire Wire Line
	2350 1750 2350 2250
Wire Wire Line
	2350 2250 1800 2250
Wire Wire Line
	1800 1800 2350 1800
Connection ~ 2350 1800
$Comp
L R-RESCUE-StepperMotorController_12_v2 R4
U 1 1 55CB5CF0
P 2850 6750
F 0 "R4" V 2930 6750 40  0000 C CNN
F 1 "10k" V 2857 6751 40  0000 C CNN
F 2 "reinnovation-footprints:R3-LARGE_PADS_0_8_hole" V 2780 6750 30  0001 C CNN
F 3 "~" H 2850 6750 30  0000 C CNN
F 4 "Value" H 2850 6750 60  0001 C CNN "Description"
F 5 "Value" H 2850 6750 60  0001 C CNN "Notes"
F 6 "Value" H 2850 6750 60  0001 C CNN "Manufacturer"
F 7 "Value" H 2850 6750 60  0001 C CNN "Manufacturer Part No"
F 8 "Value" H 2850 6750 60  0001 C CNN "Supplier 1"
F 9 "Value" H 2850 6750 60  0001 C CNN "Supplier 1 Part No"
F 10 "Value" H 2850 6750 60  0001 C CNN "Supplier 2"
F 11 "Value" H 2850 6750 60  0001 C CNN "Supplier 2 Part No"
	1    2850 6750
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-StepperMotorController_12_v2 R2
U 1 1 55CB6599
P 2850 6000
F 0 "R2" V 2930 6000 40  0000 C CNN
F 1 "100k" V 2857 6001 40  0000 C CNN
F 2 "reinnovation-footprints:R3-LARGE_PADS_0_8_hole" V 2780 6000 30  0001 C CNN
F 3 "~" H 2850 6000 30  0000 C CNN
F 4 "Value" H 2850 6000 60  0001 C CNN "Description"
F 5 "Value" H 2850 6000 60  0001 C CNN "Notes"
F 6 "Value" H 2850 6000 60  0001 C CNN "Manufacturer"
F 7 "Value" H 2850 6000 60  0001 C CNN "Manufacturer Part No"
F 8 "Value" H 2850 6000 60  0001 C CNN "Supplier 1"
F 9 "Value" H 2850 6000 60  0001 C CNN "Supplier 1 Part No"
F 10 "Value" H 2850 6000 60  0001 C CNN "Supplier 2"
F 11 "Value" H 2850 6000 60  0001 C CNN "Supplier 2 Part No"
	1    2850 6000
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-StepperMotorController_12_v2 #PWR012
U 1 1 55CB6C0E
P 2850 7150
F 0 "#PWR012" H 2850 7150 30  0001 C CNN
F 1 "GND" H 2850 7080 30  0001 C CNN
F 2 "" H 2850 7150 60  0000 C CNN
F 3 "" H 2850 7150 60  0000 C CNN
	1    2850 7150
	1    0    0    -1  
$EndComp
$Comp
L DIODESCH D4
U 1 1 55CB6CA8
P 3200 6750
F 0 "D4" H 3200 6850 40  0000 C CNN
F 1 "DIODESCH" H 3200 6650 40  0000 C CNN
F 2 "matts_components:D3_lg_pad" H 3200 6750 60  0001 C CNN
F 3 "" H 3200 6750 60  0000 C CNN
	1    3200 6750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2850 7150 2850 7000
Wire Wire Line
	2850 7050 3200 7050
Wire Wire Line
	3200 7050 3200 6950
Connection ~ 2850 7050
Wire Wire Line
	3200 6550 3200 6350
Wire Wire Line
	2850 6350 6100 6350
Wire Wire Line
	2850 6250 2850 6500
Connection ~ 2850 6350
Wire Wire Line
	2850 5750 2850 5650
Wire Wire Line
	2850 5650 1900 5650
Wire Wire Line
	1900 5650 1900 3450
Wire Wire Line
	1900 3450 2250 3450
Wire Wire Line
	2250 3450 2250 2250
Connection ~ 2250 2250
Wire Wire Line
	5500 3800 6100 3800
Wire Wire Line
	6100 3800 6100 6350
Connection ~ 3200 6350
Wire Wire Line
	6250 5100 6250 3450
Connection ~ 6250 3450
$EndSCHEMATC
