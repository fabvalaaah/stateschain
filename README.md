# stateschain
A POC that executes tasks one after another with minimum amounts of time
garanteed between jumps, working on Linux.

This is a C NetBeans project, compiled with GCC 5.4.0 and tested with Ubuntu
Linux 16.04.5 LTS x64. No leak detected using Valgrind.

This piece of software is a POC that chains "states", each state referring to a
task, a function to execute. These jobs are executed one after another
(regarding their positions into the "states chain") and the conditions to jump
from a state to the next one are:
- The task of the current state is over.
- A minimum user defined amount of time for the current state has run out.
This project has been slightly adapted to be run on a PIC32, which was its
original purpose. Thats the reason why there's an "initialization" part and an
infinite loop to simulate the behavior of the microchip.

Usage example: "statechain".

DONATION:
As I share these sources for commercial use too, maybe you could consider
sending me a reward (even a tiny one) to my Ethereum wallet at the address
0x1fEaa1E88203cc13ffE9BAe434385350bBf10868
If so, I would be forever grateful to you and motivated to keep up the good work
for sure :oD Thanks in advance !

FEEDBACK:
You like my work? It helps you? You plan to use/reuse/transform it? You have
suggestions or questions about it? Just want to say "hi"? Let me know your
feedbacks by mail to the address fabvalaaah@laposte.net

DISCLAIMER:
I am not responsible in any way of any consequence of the usage of this piece of
software. You are warned, use it at your own risks.