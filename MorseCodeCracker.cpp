#include <iostream>
#include "CodeCracker.h"


int main()
{
	//The encoded message
	int code[45] = { 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0,
				   0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 };

	/*int code[45] = { 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1,
					 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1 };*/

	//int code[6] = { 1,0,0,0,0,1 };

	int length = sizeof(code) / sizeof(int);

	//Make an instance of the code cracking class
	CodeCracker test;

	test.transliterateMorse(code, length);

	test.findLetterCombos();

    return 0;
}

/*

- dash = 1
. dot = 0

A = 01
B = 1000
C = 1010
D = 100
E = 0
F = 0010
G = 110
H = 0000
I = 00
J = 0111
K = 101
L = 0100
M = 11
N = 10
O = 111
P = 0110
Q = 1101
R = 010
S = 000
T = 1
U = 001
V = 0001
W = 011
X = 1001
Y = 1011
Z = 1100

The message:

110001110100010110010111101111111011101110111

or

001110001011101001101000010000000100010001000

Test array:

DU

100001


Most common german letters: 'E', 'N', 'I'

*/