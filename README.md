# OldBedFixWithRemote
A relative of mine has an old motorized bed that has a controller that is connected with a wire to the bed. The wires broke, so they asked me if I could take a look. After a while I came up with an idea that involved a small Arduino, to control the bed, and an Android app
that would control the Arduino from a phone.

## Bed hardware
I came up with this diagram after doing a lot of tests with the wires of the remote, that connects to the bed. It became clear that I had to connect the red wire, from the bed, with another wire from the bed to activate the motor.

Different wire combinations for the motor:
- Red + Gray = Head Down
- Red + Green = Head Up
- Red + Yellow = Legs Down
- Red + Orange = Legs Up

Hardware used:
- Arduino Nano 33 IoT
- A relay module with 4 channels
- And other small parts, like wires etc
  </br><img src="https://raw.githubusercontent.com/tycho-mertens/OldBedFixWithRemote/main/Hardware%20Diagram.jpg" width="500em"/>

## Software side of things
We use an Arduino, that is connected to the local Wi-Fi (using 2.4GHz), to control the bed. To be able to control the Arduino, remotely, I decided to make a simple Android app that talks to the Arduino through Telnet. I chose Telnet because it had the fastest response times compared to other techonologies, in the test conditions.
</br><img src="https://raw.githubusercontent.com/tycho-mertens/OldBedFixWithRemote/main/Software_Diagram.png" width="500em"/>
