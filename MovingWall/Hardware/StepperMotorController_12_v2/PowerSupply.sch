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
LIBS:matts_components
LIBS:uln-udn
LIBS:arduino
LIBS:w_connectors
LIBS:StepperMotorController_12_v2-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 4
Title "Stepper Motor Controller"
Date "2015-10-14"
Rev "3"
Comp "Jo Fairfax Studio"
Comment1 "Version 2"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 3600 2700 0    60   Input ~ 0
V_SUPPLY+
Text HLabel 3600 2950 0    60   Input ~ 0
V_SUPPLY_GND
Text HLabel 6100 2700 2    60   Output ~ 0
V_REG+
Wire Wire Line
	3600 2700 4250 2700
Wire Wire Line
	5250 2700 6100 2700
Wire Wire Line
	3600 2950 4250 2950
Text HLabel 6100 2950 2    60   Output ~ 0
V_REG_GND
Wire Wire Line
	5250 2950 6100 2950
$Comp
L DC-DC_GENERIC DCDC1
U 1 1 55A2E0CA
P 4850 2750
F 0 "DCDC1" H 4650 2950 50  0000 C CNN
F 1 "DC-DC_GENERIC" H 5050 2400 50  0000 C CNN
F 2 "reinnovation-footprints:DC-DC-5V-2A" H 4850 2750 60  0000 C CNN
F 3 "~" H 4850 2750 60  0000 C CNN
	1    4850 2750
	1    0    0    -1  
$EndComp
$EndSCHEMATC
