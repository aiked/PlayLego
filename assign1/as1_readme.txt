- Assignment 1
		for: hy428
		due: 25/02/2014

- Team Members
		Ntegiannis Dimitris		2731	deyannis@cs.uoc.gr
		Athanasakis Michalis	2562	michath@csd.uoc.gr

- Answers
	
	--2.1
	The Lego NXT contains 2 processors. 
	The main processor is an 32-bit ARM processor, AT91SAM7S256 at 48 Mhz.
	The co-processor is an 8-bit AVR processor, ATmega48 at 8Mhz.
	
	--2.2
	The ARM processor has 64 KB RAM and 256 KB Flash memory.
	The AVR processor has 512 byte RAM and 4 KB Flash memory.

	--2.3
	The Lego Kit contains the following 6 sensors:
	- Light: AVR Processor
	- Rotation: AVR Processor
	- Touch: AVR Processor
	- Sound: AVR Processor
	- Temperature: AVR Processor
	- Ultrasonic: ARM Processor

	--2.4
	Some sensors(digital) requires high-speed communication and thus they 
	are connected to the ARM processor.

	--4.1
	The main function is located inside the as1_helloworld directory and
	the file named "firmware.c"

	--4.2
	The files display.h and led.h are located in the same folder the 
	firmware.c file is located. The rest .h files are located inside
	the toolchain folder and specifically inside the directory
	/toolchain/arm/include/

	--4.3
	The gcc compiler is located inside the /toolchain/arm/bin folder.
	The include files are located inside /toolchain/arm/include/*.
	The library files are located inside /toolchain/arm/lib/*.
	
	--4.4
	
	--6.7
	Volatile is a qualifier that is applied to a variable when it is 
	declared. It tells the compiler the variable might change without
	any action taken by the code the compiler finds nearby. So, the 
	compiler is forced to disable some possible optimization and thus
	intoducing a perfomance penalty on the compiled code.
		This is the case here, volatime counting variable disable 
	optimal code production and increasing the size of .text of the 
	function from 168 bytes to 192 bytes. This creates perfomance
	penalty and the "Hello world" and LED blinking is going slower.
	To measure function size we used /toolchain/arm/bin/arm-elf-objdump

-- EOF

