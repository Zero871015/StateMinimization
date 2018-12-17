# StateMinimization

## Digital Logic Design Project 2 – State Minimization
## Due: 23:55, Dec. 24, 2018
>> In sequential circuit, the time sequence of inputs, states, and outputs can be graphically
represented in a state diagram, a.k.a. state transition graph (STG). In a STG, states are
represented by circles/vertices and the transitions between two states are indicated by directed
lines/edges. According to the input condition, each directed line/edge is originated at a
"present state" and terminated at a "next state". Since the number of states is correlated with
the number of required state flip-flops in a sequential circuit, minimizing the number of states
could reduce the number of state flip-flops as well as hardware cost. In this project, you are
going to process a completely specified STG (i.e., STG without don't cares) in KISS format
and derive its minimum STG in KISS format and output your STG in DOT format.

---
## What is fortest.cpp?
* Just a program to generate test data.
 * You can ignore it.

## How to use it in Liunx?
* Download the file in your computer(OS:Linux).
* Type "g++ main.cpp -std=c++11" in your CMD.
  * Remember you need to use cd change your directory where main.cpp is.
  * If it succeed, you will see a.out added in the folder.
* And type "./a.out input.kiss" to execute the program.
* If it works, you will see the result on CMD, and there are files named output.kiss and output.dot in the folder.

## Contact
* If there is any bug or question, you can use email contact me:
  * zero871015@gmail.com

Thank you.</br>
-Zero871015 12/18/2018
