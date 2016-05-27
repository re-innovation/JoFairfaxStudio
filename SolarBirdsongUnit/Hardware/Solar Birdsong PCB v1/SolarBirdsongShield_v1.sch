EESchema Schematic File Version 2
LIBS:SolarBirdsongShield_v1-rescue
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
LIBS:microchip
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
LIBS:matts_components
LIBS:uln-udn
LIBS:arduino
LIBS:w_connectors
LIBS:freetronics_schematic
LIBS:SolarBirdsongShield_v1-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
Title "Stepper Motor Controller"
Date "13 jul 2015"
Rev "2"
Comp "Jo Fairfax Studio"
Comment1 "Version 2"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_3 K?
U 1 1 55A40899
P 950 1100
F 0 "K?" V 900 1100 50  0000 C CNN
F 1 "PIR" V 1000 1100 40  0000 C CNN
F 2 "" H 950 1100 60  0000 C CNN
F 3 "" H 950 1100 60  0000 C CNN
	1    950  1100
	-1   0    0    1   
$EndComp
$Comp
L R-RESCUE-SolarBirdsongShield_v1 R?
U 1 1 55A408AD
P 900 3150
F 0 "R?" V 980 3150 40  0000 C CNN
F 1 "10k" V 907 3151 40  0000 C CNN
F 2 "~" V 830 3150 30  0000 C CNN
F 3 "~" H 900 3150 30  0000 C CNN
	1    900  3150
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-SolarBirdsongShield_v1 R?
U 1 1 55A408CB
P 900 2500
F 0 "R?" V 980 2500 40  0000 C CNN
F 1 "LDR" V 907 2501 40  0000 C CNN
F 2 "~" V 830 2500 30  0000 C CNN
F 3 "~" H 900 2500 30  0000 C CNN
	1    900  2500
	1    0    0    -1  
$EndComp
$Comp
L C-RESCUE-SolarBirdsongShield_v1 C?
U 1 1 55A408DA
P 1200 3150
F 0 "C?" H 1200 3250 40  0000 L CNN
F 1 "100n" H 1206 3065 40  0000 L CNN
F 2 "~" H 1238 3000 30  0000 C CNN
F 3 "~" H 1200 3150 60  0000 C CNN
	1    1200 3150
	1    0    0    -1  
$EndComp
$Comp
L NPN Q?
U 1 1 55A40ADD
P 8700 2900
F 0 "Q?" H 8700 2750 50  0000 R CNN
F 1 "NPN" H 8700 3050 50  0000 R CNN
F 2 "~" H 8700 2900 60  0000 C CNN
F 3 "~" H 8700 2900 60  0000 C CNN
	1    8700 2900
	1    0    0    -1  
$EndComp
$Comp
L R-RESCUE-SolarBirdsongShield_v1 R?
U 1 1 55A40AEC
P 7950 2900
F 0 "R?" V 8030 2900 40  0000 C CNN
F 1 "1k" V 7957 2901 40  0000 C CNN
F 2 "~" V 7880 2900 30  0000 C CNN
F 3 "~" H 7950 2900 30  0000 C CNN
	1    7950 2900
	0    -1   -1   0   
$EndComp
$Comp
L R-RESCUE-SolarBirdsongShield_v1 R?
U 1 1 55A40AFB
P 8350 3250
F 0 "R?" V 8430 3250 40  0000 C CNN
F 1 "100k" V 8357 3251 40  0000 C CNN
F 2 "~" V 8280 3250 30  0000 C CNN
F 3 "~" H 8350 3250 30  0000 C CNN
	1    8350 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 2900 8500 2900
Wire Wire Line
	8350 3000 8350 2900
Connection ~ 8350 2900
Wire Wire Line
	8350 3500 8350 3650
Wire Wire Line
	8350 3650 8800 3650
Wire Wire Line
	8800 3650 8800 3100
$Comp
L GND-RESCUE-SolarBirdsongShield_v1 #PWR?
U 1 1 55A40D42
P 8550 3750
F 0 "#PWR?" H 8550 3750 30  0001 C CNN
F 1 "GND" H 8550 3680 30  0001 C CNN
F 2 "" H 8550 3750 60  0000 C CNN
F 3 "" H 8550 3750 60  0000 C CNN
	1    8550 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 3750 8550 3650
Connection ~ 8550 3650
$Comp
L +BATT #PWR?
U 1 1 55A41814
P 8800 1150
F 0 "#PWR?" H 8800 1100 20  0001 C CNN
F 1 "+BATT" H 8800 1250 30  0000 C CNN
F 2 "" H 8800 1150 60  0000 C CNN
F 3 "" H 8800 1150 60  0000 C CNN
	1    8800 1150
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR?
U 1 1 55A41A46
P 1400 900
F 0 "#PWR?" H 1400 850 20  0001 C CNN
F 1 "+BATT" H 1400 1000 30  0000 C CNN
F 2 "" H 1400 900 60  0000 C CNN
F 3 "" H 1400 900 60  0000 C CNN
	1    1400 900 
	1    0    0    -1  
$EndComp
$Comp
L GND-RESCUE-SolarBirdsongShield_v1 #PWR?
U 1 1 55A41A55
P 1400 1300
F 0 "#PWR?" H 1400 1300 30  0001 C CNN
F 1 "GND" H 1400 1230 30  0001 C CNN
F 2 "" H 1400 1300 60  0000 C CNN
F 3 "" H 1400 1300 60  0000 C CNN
	1    1400 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 1200 1400 1200
Wire Wire Line
	1400 1200 1400 1300
Wire Wire Line
	1300 1000 1400 1000
Wire Wire Line
	1400 1000 1400 900 
Wire Wire Line
	900  2750 900  2900
Connection ~ 900  2800
Wire Wire Line
	1200 2950 1200 2800
Connection ~ 1200 2800
Wire Wire Line
	900  3400 900  3550
Wire Wire Line
	900  3550 1200 3550
Wire Wire Line
	1200 3550 1200 3350
Wire Wire Line
	900  2250 900  2100
Wire Wire Line
	1050 3550 1050 3600
Connection ~ 1050 3550
$Comp
L GND-RESCUE-SolarBirdsongShield_v1 #PWR?
U 1 1 55A41B7F
P 1050 3600
F 0 "#PWR?" H 1050 3600 30  0001 C CNN
F 1 "GND" H 1050 3530 30  0001 C CNN
F 2 "" H 1050 3600 60  0000 C CNN
F 3 "" H 1050 3600 60  0000 C CNN
	1    1050 3600
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR?
U 1 1 55A41B8E
P 900 2100
F 0 "#PWR?" H 900 2050 20  0001 C CNN
F 1 "+BATT" H 900 2200 30  0000 C CNN
F 2 "" H 900 2100 60  0000 C CNN
F 3 "" H 900 2100 60  0000 C CNN
	1    900  2100
	1    0    0    -1  
$EndComp
$Comp
L MOD1021 U?
U 1 1 55A4276E
P 9650 1750
F 0 "U?" H 9800 2350 70  0000 C CNN
F 1 "MOD1021" H 9650 1150 70  0000 C CNN
F 2 "~" H 9650 1650 60  0000 C CNN
F 3 "~" H 9650 1650 60  0000 C CNN
	1    9650 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 1400 8800 1400
Wire Wire Line
	8800 1400 8800 1150
Wire Wire Line
	8800 2000 8950 2000
$Comp
L CONN_2 P?
U 1 1 55A427D9
P 10550 2600
F 0 "P?" V 10500 2600 40  0000 C CNN
F 1 "SPK" V 10600 2600 40  0000 C CNN
F 2 "" H 10550 2600 60  0000 C CNN
F 3 "" H 10550 2600 60  0000 C CNN
	1    10550 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	10200 2500 8900 2500
Wire Wire Line
	8900 2500 8900 2100
Wire Wire Line
	8900 2100 8950 2100
Wire Wire Line
	10200 2700 10200 2550
Wire Wire Line
	10200 2550 8700 2550
Wire Wire Line
	8700 2550 8700 1900
Wire Wire Line
	8700 1900 8950 1900
Wire Wire Line
	10350 1400 10650 1400
Wire Wire Line
	8800 2400 10500 2400
Wire Wire Line
	10500 2400 10500 2000
Wire Wire Line
	10500 2000 10350 2000
Connection ~ 8800 2400
Text Label 10650 1400 0    60   ~ 0
MP3_BSY
Wire Wire Line
	1300 1100 1600 1100
Text Label 1600 1100 0    60   ~ 0
PIR_SIG
Text Label 700  6800 0    60   ~ 0
MP3_BSY
Text Label 700  6600 0    60   ~ 0
LDR_SIG
Text Label 700  6400 0    60   ~ 0
PIR_SIG
NoConn ~ 8950 1700
NoConn ~ 8950 1800
NoConn ~ 10350 1500
NoConn ~ 10350 1600
NoConn ~ 10350 1700
NoConn ~ 10350 1800
NoConn ~ 10350 1900
NoConn ~ 10350 2100
Wire Wire Line
	5000 4500 5200 4500
Wire Wire Line
	5200 1950 5500 1950
Wire Wire Line
	5200 1950 5200 2100
Wire Wire Line
	5200 2100 5250 2100
Connection ~ 5100 2800
Wire Wire Line
	5100 2800 5100 1850
Wire Wire Line
	5100 1850 5500 1850
Wire Wire Line
	6100 1950 6100 2000
Wire Wire Line
	6000 1950 6100 1950
Connection ~ 6300 5250
Wire Wire Line
	6300 5250 6150 5250
Wire Wire Line
	6150 5250 6150 5300
Wire Wire Line
	5850 4800 6400 4800
Wire Wire Line
	6250 5000 6400 5000
Wire Wire Line
	5000 4000 5150 4000
Wire Wire Line
	5000 2800 5250 2800
Wire Wire Line
	5000 2600 5250 2600
Wire Wire Line
	5000 4400 5200 4400
Wire Wire Line
	5200 4200 5000 4200
Wire Wire Line
	5500 4250 5900 4250
Wire Wire Line
	5000 3650 5200 3650
Connection ~ 5800 2550
Wire Wire Line
	5550 2550 5950 2550
Wire Wire Line
	5550 2550 5550 2900
Wire Wire Line
	5550 2900 5000 2900
Wire Wire Line
	6250 2550 6450 2550
Wire Wire Line
	6450 2550 6450 3350
Wire Wire Line
	6450 3350 6250 3350
Wire Wire Line
	5800 2550 5800 2650
Wire Wire Line
	2650 3650 2650 4600
Connection ~ 2950 2300
Wire Wire Line
	2950 2300 2950 3350
Wire Wire Line
	2800 4750 2800 4600
Connection ~ 2800 4600
Wire Wire Line
	2650 2300 2650 3350
Wire Wire Line
	2950 4600 2950 3650
Connection ~ 2950 4600
Wire Wire Line
	5800 3350 5800 3250
Wire Wire Line
	6600 2950 6600 2850
Wire Wire Line
	6600 2850 6450 2850
Connection ~ 6450 2850
Wire Wire Line
	5000 3000 5550 3000
Wire Wire Line
	5550 3000 5550 3350
Wire Wire Line
	5550 3350 5950 3350
Connection ~ 5800 3350
Wire Wire Line
	5800 4000 5800 4250
Connection ~ 5800 4250
Wire Wire Line
	6300 4000 6300 3950
Wire Wire Line
	5000 3550 5200 3550
Wire Wire Line
	5000 3750 5600 3750
Wire Wire Line
	5000 4100 5200 4100
Wire Wire Line
	5000 4300 5200 4300
Wire Wire Line
	5000 2500 5250 2500
Wire Wire Line
	5000 2700 5250 2700
Wire Wire Line
	5000 3900 5150 3900
Wire Wire Line
	6250 4900 6400 4900
Wire Wire Line
	6300 5300 6400 5300
Wire Wire Line
	6300 5200 6300 5300
Wire Wire Line
	6300 5200 6400 5200
Wire Wire Line
	6250 5200 6250 5100
Wire Wire Line
	6250 5100 6400 5100
Wire Wire Line
	6000 1750 6100 1750
Wire Wire Line
	6100 1750 6100 1700
Wire Wire Line
	5050 1750 5500 1750
Wire Wire Line
	5050 1750 5050 2700
Connection ~ 5050 2700
Wire Wire Line
	6000 1850 6200 1850
Wire Wire Line
	6200 1850 6200 2200
Wire Wire Line
	6200 2200 5150 2200
Wire Wire Line
	5150 2200 5150 2600
Connection ~ 5150 2600
Wire Wire Line
	3000 4600 3000 4500
Wire Wire Line
	3000 4500 3100 4500
Connection ~ 3000 4600
Wire Wire Line
	3100 2600 3000 2600
Wire Wire Line
	3000 2600 3000 2300
Connection ~ 3000 2300
Text GLabel 5200 4500 2    60   Input ~ 0
D6
Text GLabel 5250 2100 2    60   Output ~ 0
RESET
$Comp
L +5V #PWR?
U 1 1 5702F3E5
P 6100 1700
F 0 "#PWR?" H 6100 1790 20  0001 C CNN
F 1 "+5V" H 6100 1790 30  0000 C CNN
F 2 "" H 6100 1700 60  0001 C CNN
F 3 "" H 6100 1700 60  0001 C CNN
	1    6100 1700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5702F3EB
P 6100 2000
F 0 "#PWR?" H 6100 2000 30  0001 C CNN
F 1 "GND" H 6100 1930 30  0001 C CNN
F 2 "" H 6100 2000 60  0001 C CNN
F 3 "" H 6100 2000 60  0001 C CNN
F 4 "~" H 6100 2000 60  0001 C CNN "Description"
F 5 "~" H 6100 2000 60  0001 C CNN "Notes"
F 6 "~" H 6100 2000 60  0001 C CNN "Manufacturer"
F 7 "~" H 6100 2000 60  0001 C CNN "Manufacturer Part No"
F 8 "~" H 6100 2000 60  0001 C CNN "Supplier 1"
F 9 "~" H 6100 2000 60  0001 C CNN "Supplier 1 Part No"
F 10 "~" H 6100 2000 60  0001 C CNN "Supplier 2"
F 11 "~" H 6100 2000 60  0001 C CNN "Supplier 2 Part No"
F 12 "~" H 6100 2000 60  0001 C CNN "Cost"
	1    6100 2000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5702F3F1
P 6150 5300
F 0 "#PWR?" H 6150 5300 30  0001 C CNN
F 1 "GND" H 6150 5230 30  0001 C CNN
F 2 "" H 6150 5300 60  0001 C CNN
F 3 "" H 6150 5300 60  0001 C CNN
F 4 "~" H 6150 5300 60  0001 C CNN "Description"
F 5 "~" H 6150 5300 60  0001 C CNN "Notes"
F 6 "~" H 6150 5300 60  0001 C CNN "Manufacturer"
F 7 "~" H 6150 5300 60  0001 C CNN "Manufacturer Part No"
F 8 "~" H 6150 5300 60  0001 C CNN "Supplier 1"
F 9 "~" H 6150 5300 60  0001 C CNN "Supplier 1 Part No"
F 10 "~" H 6150 5300 60  0001 C CNN "Supplier 2"
F 11 "~" H 6150 5300 60  0001 C CNN "Supplier 2 Part No"
F 12 "~" H 6150 5300 60  0001 C CNN "Cost"
	1    6150 5300
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 5702F3F7
P 5150 5200
F 0 "#PWR?" H 5150 5290 20  0001 C CNN
F 1 "+5V" H 5150 5350 30  0000 C CNN
F 2 "" H 5150 5200 60  0001 C CNN
F 3 "" H 5150 5200 60  0001 C CNN
	1    5150 5200
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5702F3FD
P 5700 4800
F 0 "C?" H 5750 4900 50  0000 L CNN
F 1 "100nF" H 5750 4700 50  0000 L CNN
F 2 "matts_components:C1_wide_lg_pad" H 5700 4800 60  0001 C CNN
F 3 "" H 5700 4800 60  0001 C CNN
F 4 "~" H 5700 4800 60  0001 C CNN "Description"
F 5 "~" H 5700 4800 60  0001 C CNN "Notes"
F 6 "~" H 5700 4800 60  0001 C CNN "Manufacturer"
F 7 "~" H 5700 4800 60  0001 C CNN "Manufacturer Part No"
F 8 "~" H 5700 4800 60  0001 C CNN "Supplier 1"
F 9 "~" H 5700 4800 60  0001 C CNN "Supplier 1 Part No"
F 10 "~" H 5700 4800 60  0001 C CNN "Supplier 2"
F 11 "~" H 5700 4800 60  0001 C CNN "Supplier 2 Part No"
F 12 "~" H 5700 4800 60  0001 C CNN "Cost"
	1    5700 4800
	0    -1   -1   0   
$EndComp
Text GLabel 6250 4900 0    60   Output ~ 0
TxD
Text GLabel 6250 5000 0    60   Input ~ 0
RxD
Text GLabel 5150 3900 2    60   Input ~ 0
RxD
Text GLabel 5150 4000 2    60   Output ~ 0
TxD
Text Notes 6900 5300 0    60   ~ 0
1: RTS#\n2: Rx\n3: Tx\n4: Vcc\n5: CTS#\n6: GND
Text GLabel 5600 3750 2    60   Input ~ 0
RESET
Text Label 5000 4600 0    60   ~ 0
d7
Text Label 5000 4500 0    60   ~ 0
d6
Text Label 5000 4400 0    60   ~ 0
d5
Text Label 5000 4300 0    60   ~ 0
d4
Text Label 5000 4200 0    60   ~ 0
d3
Text Label 5000 4100 0    60   ~ 0
d2
Text Label 5000 4000 0    60   ~ 0
d1
Text Label 5000 3900 0    60   ~ 0
d0
Text Label 5000 3650 0    60   ~ 0
a5
Text Label 5000 3550 0    60   ~ 0
a4
Text Label 5000 3450 0    60   ~ 0
a3
Text Label 5000 3350 0    60   ~ 0
a2
Text Label 5000 3250 0    60   ~ 0
a1
Text Label 5000 3150 0    60   ~ 0
a0
Text Label 5000 2800 0    60   ~ 0
d13
Text Label 5000 2700 0    60   ~ 0
d12
Text Label 5000 2600 0    60   ~ 0
d11
Text Label 5000 2500 0    60   ~ 0
d10
Text Label 5000 2400 0    60   ~ 0
d9
Text Label 5000 2300 0    60   ~ 0
d8
Text GLabel 5200 4400 2    60   Input ~ 0
D5
Text GLabel 5200 4200 2    60   Input ~ 0
D3
Text GLabel 5200 4300 2    60   Input ~ 0
D4
Text GLabel 5250 2800 2    60   Output ~ 0
D13
Text GLabel 5250 2700 2    60   Output ~ 0
D12
Text GLabel 5250 2600 2    60   Output ~ 0
D11
Text GLabel 5250 2500 2    60   Output ~ 0
D10
Text GLabel 5200 4100 2    60   Input ~ 0
D2
Text GLabel 5200 3550 2    60   Input ~ 0
A4
Text GLabel 5200 3650 2    60   Input ~ 0
A5
$Comp
L +5V #PWR?
U 1 1 5702F436
P 2800 2150
F 0 "#PWR?" H 2800 2240 20  0001 C CNN
F 1 "+5V" H 2800 2240 30  0000 C CNN
F 2 "" H 2800 2150 60  0001 C CNN
F 3 "" H 2800 2150 60  0001 C CNN
	1    2800 2150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5702F43C
P 6900 4400
F 0 "#PWR?" H 6900 4400 30  0001 C CNN
F 1 "GND" H 6900 4330 30  0001 C CNN
F 2 "" H 6900 4400 60  0001 C CNN
F 3 "" H 6900 4400 60  0001 C CNN
F 4 "~" H 6900 4400 60  0001 C CNN "Description"
F 5 "~" H 6900 4400 60  0001 C CNN "Notes"
F 6 "~" H 6900 4400 60  0001 C CNN "Manufacturer"
F 7 "~" H 6900 4400 60  0001 C CNN "Manufacturer Part No"
F 8 "~" H 6900 4400 60  0001 C CNN "Supplier 1"
F 9 "~" H 6900 4400 60  0001 C CNN "Supplier 1 Part No"
F 10 "~" H 6900 4400 60  0001 C CNN "Supplier 2"
F 11 "~" H 6900 4400 60  0001 C CNN "Supplier 2 Part No"
F 12 "~" H 6900 4400 60  0001 C CNN "Cost"
	1    6900 4400
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR?
U 1 1 5702F442
P 6300 3950
F 0 "#PWR?" H 6300 4040 20  0001 C CNN
F 1 "+5V" H 6300 4040 30  0000 C CNN
F 2 "" H 6300 3950 60  0001 C CNN
F 3 "" H 6300 3950 60  0001 C CNN
	1    6300 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5702F448
P 6600 2950
F 0 "#PWR?" H 6600 2950 30  0001 C CNN
F 1 "GND" H 6600 2880 30  0001 C CNN
F 2 "" H 6600 2950 60  0001 C CNN
F 3 "" H 6600 2950 60  0001 C CNN
F 4 "~" H 6600 2950 60  0001 C CNN "Description"
F 5 "~" H 6600 2950 60  0001 C CNN "Notes"
F 6 "~" H 6600 2950 60  0001 C CNN "Manufacturer"
F 7 "~" H 6600 2950 60  0001 C CNN "Manufacturer Part No"
F 8 "~" H 6600 2950 60  0001 C CNN "Supplier 1"
F 9 "~" H 6600 2950 60  0001 C CNN "Supplier 1 Part No"
F 10 "~" H 6600 2950 60  0001 C CNN "Supplier 2"
F 11 "~" H 6600 2950 60  0001 C CNN "Supplier 2 Part No"
F 12 "~" H 6600 2950 60  0001 C CNN "Cost"
	1    6600 2950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5702F44E
P 2800 4750
F 0 "#PWR?" H 2800 4750 30  0001 C CNN
F 1 "GND" H 2800 4680 30  0001 C CNN
F 2 "" H 2800 4750 60  0001 C CNN
F 3 "" H 2800 4750 60  0001 C CNN
F 4 "~" H 2800 4750 60  0001 C CNN "Description"
F 5 "~" H 2800 4750 60  0001 C CNN "Notes"
F 6 "~" H 2800 4750 60  0001 C CNN "Manufacturer"
F 7 "~" H 2800 4750 60  0001 C CNN "Manufacturer Part No"
F 8 "~" H 2800 4750 60  0001 C CNN "Supplier 1"
F 9 "~" H 2800 4750 60  0001 C CNN "Supplier 1 Part No"
F 10 "~" H 2800 4750 60  0001 C CNN "Supplier 2"
F 11 "~" H 2800 4750 60  0001 C CNN "Supplier 2 Part No"
F 12 "~" H 2800 4750 60  0001 C CNN "Cost"
	1    2800 4750
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5702F454
P 2950 3500
F 0 "C?" H 3000 3600 50  0000 L CNN
F 1 "100nF" H 3000 3400 50  0000 L CNN
F 2 "matts_components:C1_wide_lg_pad" H 2950 3500 60  0001 C CNN
F 3 "" H 2950 3500 60  0001 C CNN
F 4 "~" H 2950 3500 60  0001 C CNN "Description"
F 5 "~" H 2950 3500 60  0001 C CNN "Notes"
F 6 "~" H 2950 3500 60  0001 C CNN "Manufacturer"
F 7 "~" H 2950 3500 60  0001 C CNN "Manufacturer Part No"
F 8 "~" H 2950 3500 60  0001 C CNN "Supplier 1"
F 9 "~" H 2950 3500 60  0001 C CNN "Supplier 1 Part No"
F 10 "~" H 2950 3500 60  0001 C CNN "Supplier 2"
F 11 "~" H 2950 3500 60  0001 C CNN "Supplier 2 Part No"
F 12 "~" H 2950 3500 60  0001 C CNN "Cost"
	1    2950 3500
	1    0    0    -1  
$EndComp
$Comp
L CP1 C?
U 1 1 5702F45B
P 2650 3500
F 0 "C?" H 2700 3600 50  0000 L CNN
F 1 "100uF" H 2700 3400 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D5_L6_P2.5" H 2650 3500 60  0001 C CNN
F 3 "" H 2650 3500 60  0001 C CNN
F 4 "~" H 2650 3500 60  0001 C CNN "Description"
F 5 "~" H 2650 3500 60  0001 C CNN "Notes"
F 6 "~" H 2650 3500 60  0001 C CNN "Manufacturer"
F 7 "~" H 2650 3500 60  0001 C CNN "Manufacturer Part No"
F 8 "~" H 2650 3500 60  0001 C CNN "Supplier 1"
F 9 "~" H 2650 3500 60  0001 C CNN "Supplier 1 Part No"
F 10 "~" H 2650 3500 60  0001 C CNN "Supplier 2"
F 11 "~" H 2650 3500 60  0001 C CNN "Supplier 2 Part No"
F 12 "~" H 2650 3500 60  0001 C CNN "Cost"
	1    2650 3500
	1    0    0    -1  
$EndComp
$Comp
L SPST SW?
U 1 1 5702F462
P 6400 4250
F 0 "SW?" H 6400 4350 70  0000 C CNN
F 1 "RESET" H 6400 4150 70  0000 C CNN
F 2 "matts_components:SW_PUSH_single_pins" H 6400 4250 60  0001 C CNN
F 3 "" H 6400 4250 60  0001 C CNN
	1    6400 4250
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5702F469
P 6100 3350
F 0 "C?" H 6150 3450 50  0000 L CNN
F 1 "22pF" H 6150 3250 50  0000 L CNN
F 2 "matts_components:C1_lg_pad" H 6100 3350 60  0001 C CNN
F 3 "" H 6100 3350 60  0001 C CNN
F 4 "~" H 6100 3350 60  0001 C CNN "Description"
F 5 "~" H 6100 3350 60  0001 C CNN "Notes"
F 6 "~" H 6100 3350 60  0001 C CNN "Manufacturer"
F 7 "~" H 6100 3350 60  0001 C CNN "Manufacturer Part No"
F 8 "~" H 6100 3350 60  0001 C CNN "Supplier 1"
F 9 "~" H 6100 3350 60  0001 C CNN "Supplier 1 Part No"
F 10 "~" H 6100 3350 60  0001 C CNN "Supplier 2"
F 11 "~" H 6100 3350 60  0001 C CNN "Supplier 2 Part No"
F 12 "~" H 6100 3350 60  0001 C CNN "Cost"
	1    6100 3350
	0    -1   -1   0   
$EndComp
$Comp
L C C?
U 1 1 5702F470
P 6100 2550
F 0 "C?" H 6150 2650 50  0000 L CNN
F 1 "22pF" H 6150 2450 50  0000 L CNN
F 2 "matts_components:C1_lg_pad" H 6100 2550 60  0001 C CNN
F 3 "" H 6100 2550 60  0001 C CNN
F 4 "~" H 6100 2550 60  0001 C CNN "Description"
F 5 "~" H 6100 2550 60  0001 C CNN "Notes"
F 6 "~" H 6100 2550 60  0001 C CNN "Manufacturer"
F 7 "~" H 6100 2550 60  0001 C CNN "Manufacturer Part No"
F 8 "~" H 6100 2550 60  0001 C CNN "Supplier 1"
F 9 "~" H 6100 2550 60  0001 C CNN "Supplier 1 Part No"
F 10 "~" H 6100 2550 60  0001 C CNN "Supplier 2"
F 11 "~" H 6100 2550 60  0001 C CNN "Supplier 2 Part No"
F 12 "~" H 6100 2550 60  0001 C CNN "Cost"
	1    6100 2550
	0    -1   -1   0   
$EndComp
$Comp
L R R?
U 1 1 5702F477
P 6050 4000
F 0 "R?" V 6130 4000 50  0000 C CNN
F 1 "10k" V 6050 4000 50  0000 C CNN
F 2 "REInnovationFootprint:TH_Resistor_1" H 6050 4000 60  0001 C CNN
F 3 "" H 6050 4000 60  0001 C CNN
F 4 "~" H 6050 4000 60  0001 C CNN "Description"
F 5 "~" H 6050 4000 60  0001 C CNN "Notes"
F 6 "~" H 6050 4000 60  0001 C CNN "Manufacturer"
F 7 "~" H 6050 4000 60  0001 C CNN "Manufacturer Part No"
F 8 "~" H 6050 4000 60  0001 C CNN "Supplier 1"
F 9 "~" H 6050 4000 60  0001 C CNN "Supplier 1 Part No"
F 10 "~" H 6050 4000 60  0001 C CNN "Supplier 2"
F 11 "~" H 6050 4000 60  0001 C CNN "Supplier 2 Part No"
F 12 "~" H 6050 4000 60  0001 C CNN "Cost"
	1    6050 4000
	0    -1   -1   0   
$EndComp
$Comp
L ATMEGA328P-P IC?
U 1 1 5702F47E
P 4000 3400
F 0 "IC?" H 3300 4650 50  0000 L BNN
F 1 "ATMEGA328P-P" H 4200 2000 50  0000 L BNN
F 2 "matts_components:DIP-28__300_ELL" H 3400 2050 50  0001 C CNN
F 3 "" H 4000 3400 60  0001 C CNN
F 4 "~" H 4000 3400 60  0001 C CNN "Description"
F 5 "~" H 4000 3400 60  0001 C CNN "Notes"
F 6 "~" H 4000 3400 60  0001 C CNN "Manufacturer"
F 7 "~" H 4000 3400 60  0001 C CNN "Manufacturer Part No"
F 8 "~" H 4000 3400 60  0001 C CNN "Supplier 1"
F 9 "~" H 4000 3400 60  0001 C CNN "Supplier 1 Part No"
F 10 "~" H 4000 3400 60  0001 C CNN "Supplier 2"
F 11 "~" H 4000 3400 60  0001 C CNN "Supplier 2 Part No"
F 12 "~" H 4000 3400 60  0001 C CNN "Cost"
	1    4000 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 3750 5500 4800
Connection ~ 5500 4250
Connection ~ 5500 3750
Wire Wire Line
	6900 4400 6900 4250
Text GLabel 5200 3350 2    60   Input ~ 0
A2
Text GLabel 5200 3450 2    60   Input ~ 0
A3
Text GLabel 5200 3150 2    60   Input ~ 0
A0
Text GLabel 5200 3250 2    60   Input ~ 0
A1
Wire Wire Line
	5200 3150 5000 3150
Wire Wire Line
	5000 3250 5200 3250
Wire Wire Line
	5200 3350 5000 3350
Wire Wire Line
	5000 3450 5200 3450
Wire Wire Line
	2650 4600 3100 4600
Wire Wire Line
	2650 2300 3100 2300
Wire Wire Line
	2800 2150 2800 2300
Connection ~ 2800 2300
Text GLabel 5200 4600 2    60   Input ~ 0
D7
Text GLabel 5300 2300 2    60   Input ~ 0
D8
Text GLabel 5300 2400 2    60   Input ~ 0
D9
Wire Wire Line
	5000 2300 5300 2300
Wire Wire Line
	5000 2400 5300 2400
Wire Wire Line
	5200 4600 5000 4600
$Comp
L D_Schottky D?
U 1 1 5702F4AB
P 5650 5200
F 0 "D?" H 5650 5300 50  0000 C CNN
F 1 "D_Schottky" H 5650 5100 50  0000 C CNN
F 2 "REInnovationFootprint:TH_Diode_2" H 5650 5200 60  0001 C CNN
F 3 "" H 5650 5200 60  0000 C CNN
	1    5650 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 5200 6250 5200
Wire Wire Line
	5500 5200 5150 5200
$Comp
L CRYSTAL_16MHz X?
U 1 1 5702F4B4
P 5800 2950
F 0 "X?" H 5800 3100 50  0000 C CNN
F 1 "16MHz" H 5800 2800 50  0000 C CNN
F 2 "matts_components:Xtal_small_matt" H 5800 2950 60  0001 C CNN
F 3 "" H 5800 2950 60  0000 C CNN
	1    5800 2950
	0    1    1    0   
$EndComp
$Comp
L CONN_01X06 P?
U 1 1 5702FEBF
P 6600 5050
F 0 "P?" H 6600 5400 50  0000 C CNN
F 1 "CONN_01X06" V 6700 5050 50  0000 C CNN
F 2 "" H 6600 5050 50  0000 C CNN
F 3 "" H 6600 5050 50  0000 C CNN
	1    6600 5050
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X03 P?
U 1 1 5702FFF2
P 5750 1850
F 0 "P?" H 5750 2050 50  0000 C CNN
F 1 "ISP" H 5750 1650 50  0000 C CNN
F 2 "" H 5750 650 50  0000 C CNN
F 3 "" H 5750 650 50  0000 C CNN
	1    5750 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 4000 5900 4000
Wire Wire Line
	6200 4000 6300 4000
Wire Wire Line
	5500 4800 5550 4800
NoConn ~ 3100 2900
Text Label 1400 2800 0    60   ~ 0
LDR_SIG
Wire Wire Line
	900  2800 1400 2800
Wire Wire Line
	7700 2900 7500 2900
$Comp
L R-RESCUE-SolarBirdsongShield_v1 R?
U 1 1 57032F8A
P 8350 1500
F 0 "R?" V 8430 1500 40  0000 C CNN
F 1 "1k" V 8357 1501 40  0000 C CNN
F 2 "~" V 8280 1500 30  0000 C CNN
F 3 "~" H 8350 1500 30  0000 C CNN
	1    8350 1500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8600 1500 8950 1500
Wire Wire Line
	9000 1600 7850 1600
Wire Wire Line
	8800 2000 8800 2700
$EndSCHEMATC
