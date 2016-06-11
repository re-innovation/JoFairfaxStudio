""" serial_repeater

Usage:
	serial_repeater <port> <baudrate> <period> <start_delay>

"""

import sys
import docopt
import serial
import logging
import time

if __name__ == "__main__":
	
	args = docopt.docopt(__doc__)

	logging.basicConfig(level=logging.INFO)

	port = args['<port>']
	baudrate = int(args['<baudrate>'])
	period = int(args['<period>'])
	start_delay = int(args['<start_delay>'])

	to_repeat = sys.stdin.readline().strip().encode('utf-8')

	logging.getLogger(__name__).info("Sending '{}' to {} every {} seconds.".format(to_repeat, port, period))

	ser = serial.Serial(port, baudrate, timeout=1)
	time.sleep(start_delay)

	while True:
		ser.write(to_repeat)
		stop = time.time()+period
		while time.time() < stop:
			reply = ser.readline().decode('utf-8').strip()
			if len(reply):
				print(reply)