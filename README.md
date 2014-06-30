playlego
=====

**playlego** is a collection of projects using the embedded system of [Lego NXT][1]. The purpose was to implement simple utilities on a custom firmware in order to use all the modules the system provides. This includes the monitor, sensors and motors.

The projects are separated into 5 parts:

 1. A simple hello world program. The goal is to use the existing firmware in order to print a simple hello world on the screen.

 2. Implementation of a digital clock. This projects utilises interrupts and it requires from the programmer to connect peripherals and setup clocks and interrupts timers.

 3. Implementation of a analog clock. Now that we know how to use the system's timers we can try to utilise the monitor more. We implement a simple API with simple math equations basic shapes like point, lines and cycles. In the end, we design a simple analog clock.

 4. Sensors and motors. Lego NXT provides a collection of sensors for the user which include microphone, light & colour detector, buttons and pressure sensors along with a ultrasonic sensors. Many of these sensors are connected with a co-processor and there is a bus to offer communication between the two processors. We implement this communication path and we use it to inform the user the state of each sensors and create simple handlers.

 5. The final projects utilises all the above knowledge in order to implement a simple alarm system with a FSM logic between a relaxed and an alarmed state.


In all of the above projects we used the Lego NXT manuals and we builded each firmware around a code core that exists in each project with minor changes that depends in each project. Under the directory of *`/papers`*
you can find all the necessary manuals.

BONUS: With any relation to the above projects there is a simple virtualization patch for QEMU in order to count memory I/O.
  [1]: http://mindstorms.lego.com