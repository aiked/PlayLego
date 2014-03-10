- Assignment 2
		for: hy428
		due: 12/03/2014

- Team Members
		Ntegiannis Dimitris		2731	deyannis@cs.uoc.gr
		Athanasakis Michalis	858		michath@csd.uoc.gr

- Answers
	
	--2.1
		Communication between ARM and the LCD display happens over a SPI
		(Serial Peripheral Interface) bus running at 2Mhz. The LCD-controller
		is a UltraChip 1601 updating the LCD every 17ms.

	--2.2
		Updating the LCD does not require any interrupts because the LCD
		controller updates it every 17ms regardless if any changes have 
		happened. If ARM wants to alter the display it has to store the updated
		values inside the specific array the LCD-controller listens and then
		wait for it to fetch the new data and display them.

	--2.3
		Updating the screen is happening by changing values to a 100x64 array.
		For the rest functionality responsible are is firmware and the LCD 
		controller which have to transfer the array from ARM to the display.
		The updating process is continuously happening and is not dependent
		from any event.

	--3.2
		PIT provides a 20-bit CPIV and a 12-bit PICNT. Both counters work
		at a Master Clock/16 frequency. The CPIV register provides how 
		many cycles produce an overflow to the PICNT. The maximum value of
		CPIV is 0xFFFFF which is equivalent to 0.346 sec or 346 msec.

	--4.1
		Edge triggered interrupts are signalled when the system detects a 
		spike on the interrupt line, either a high to low or low to high 
		change.
		Level triggered interrupts are signalled when the maintained signal
		line is changed to its active level(high or low). The system samples
		the line and when a interrupt is received is handled depending its
		priority.
		We choose to use a level triggered system in order to be manipulate
		in the best way the interrupts coming from the SSC and the Periodic
		Interval Timer without losing neither of them.

		--5.2
		As stated in question 3.2 the maximum value we can put to CPIV is
		0xFFFFF due to 20-bit limitation. That being said, the PICNT is 
		increased every 1048575 cycles or every 0.346 seconds at a frequency
		of 2.89 Hz. So, the minimum possible frequency is 2.89 Hz.

	--6.4
		// TO DO TEXT

	--7.*
		// OPTIONAL
		// TO DO TEXT

-- EOF
