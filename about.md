1.1. Introduction:

- The cooler is one of the most useful things to keep food cold while traveling. It was originally invented by an American farmer called Thomas Moore in 1802. He used it to transport butter from his home to local markets, this allowed him to sell firm butter instead of soft, melted butter, giving it an edge over its competitors those days. It was originally used with a large block of ice and sawdust to keep the ice from melting too quickly. The ice was separated into a different compartment and zinc or tin was used for better heat transfer from one compartment to another. This helped prevent water from melting ice from reaching the butter and ruining it before selling it at market. But to this day, the only things that keep a cooler cool are either blocks of ice or a motor that connects to a car battery. We wanted to make this more practical and portable. So, to do this, we added a controlled feedback system to the product with a set temperature and powering the cooler with electricity from outside the car using a rechargeable battery.
  This means that our system will depend on:

- A rechargeable battery
- A temperature control with a set goal.

  1.2. The requirements:

- The cooler must be able to be powered by a rechargeable battery
- We must be able to see the consumption of the cooler live and the total energy
  consumption of the system.
- We must be able to enter a temperature setpoint in an HIM.
- The cooler must be able to act on the temperature to acquire the setpoint
  requested by the user (slave / asservissed system).

To carry out this project, we had a lot of choice in terms of components that we wanted to use to implement a certain number of solutions:

- For temperature we chose a TMP36 because of its measurement capabilities. It can measure anywhere between -40°C and +125°C with an output of 750mV for 25°C. The technical documentation is available here; https://www.analog.com/media/en/technical-documentation/data-sheets/TMP35_36_37.pdf
- For the current sensor, we chose the MR362 based on an ACS714 allowing us to measure a current from -5 A to +5 A with an analog output which is proportional to the measured current (2.5 V for 0 HAS). The technical documentation is available here; hBp://www.microbot.it/documents/mr003-006-2_datasheet.pdf
- For the voltage sensor we chose to make a voltage divider with two resistors to be able to make an analog reading of the voltage entering the micro-controller and with a mathematical formula, it is possible to have the voltage real that the system uses.
- 12V rechargeable battery that will replace the need for a car. (For the demonstration and simulation we used two 12V to 2.5A generator until testing period.)

To simulate our program, we used TinkerCad to verify our entire system with a few small modifications. (Formulas, Sensors, Pins etc...).
This simulation allowed us to test the Amperage sensor and all the energy balance formulas in the serial monitor. We replaced the intensity sensor with a potentiometer for the sole reason that there is no Amperage sensor in TinkerCad.
