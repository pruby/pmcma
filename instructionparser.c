
#line 1 "instructionparser.rl"
/*
*
*          Post memory corruption memory analyzer
*
*
*
*   Copyright 2011 Toucan System SARL
*
*   Licensed under the Apache License, Version 2.0 (the "License");
*   you may not use this file except in compliance with the License.
*   You may obtain a copy of the License at
*
*       http://www.apache.org/licenses/LICENSE-2.0
*
*   Unless required by applicable law or agreed to in writing, software
*   distributed under the License is distributed on an "AS IS" BASIS,
*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*   See the License for the specific language governing permissions and
*   limitations under the License.
*
*
*/

/*
* Trivial x86 intel syntax instruction parser
*
* determine if it is a read,
* write, or unkown operation
*
* Jonathan Brossard // endrazine@gmail.com
*/

#include <stdio.h>

extern int read_op;
extern int write_op;
extern FILE *stdout;


#line 88 "instructionparser.rl"



#line 47 "instructionparser.c"
static const short _x86instr_key_offsets[] = {
	0, 0, 27, 40, 52, 63, 75, 87, 
	102, 117, 136, 154, 166, 170, 182, 194, 
	206, 225, 239, 243, 255, 267, 279, 291, 
	303, 315, 329, 343, 357, 376, 390, 403, 
	417, 431, 445, 459, 473, 487, 506, 521, 
	535, 555, 569, 583, 597, 611, 625, 646, 
	661, 675, 690, 704, 718, 737, 751, 765, 
	784, 804, 818, 832, 846, 863, 883, 899, 
	913, 927, 947, 964, 978, 992, 1006, 1020, 
	1040, 1054, 1068, 1082, 1096, 1110, 1124, 1138, 
	1152, 1168, 1182, 1196, 1211, 1225, 1239, 1253, 
	1269, 1284, 1298, 1324, 1339, 1353, 1368, 1387, 
	1401, 1416, 1430, 1445, 1459, 1476, 1491, 1505, 
	1524, 1539, 1553, 1567, 1581, 1601, 1617, 1631, 
	1645, 1659, 1673, 1687, 1701, 1715, 1729, 1745, 
	1760, 1774, 1788, 1802, 1816, 1830, 1849, 1863, 
	1877, 1891, 1906, 1923, 1938, 1957, 1971, 1985, 
	1999, 2013, 2027, 2041, 2056, 2071
};

static const char _x86instr_trans_keys[] = {
	9, 32, 44, 97, 99, 100, 102, 105, 
	108, 109, 110, 111, 112, 114, 115, 118, 
	120, 10, 13, 42, 45, 48, 57, 65, 
	90, 98, 122, 9, 32, 44, 10, 13, 
	42, 45, 48, 57, 65, 90, 97, 122, 
	32, 44, 9, 13, 42, 45, 48, 57, 
	65, 90, 97, 122, 9, 32, 44, 42, 
	45, 48, 57, 65, 90, 97, 122, 9, 
	32, 45, 91, 42, 43, 48, 57, 65, 
	90, 97, 122, 9, 32, 45, 93, 42, 
	43, 48, 57, 65, 90, 97, 122, 9, 
	32, 44, 100, 110, 10, 13, 42, 45, 
	48, 57, 65, 90, 97, 122, 9, 32, 
	44, 99, 100, 10, 13, 42, 45, 48, 
	57, 65, 90, 97, 122, 9, 32, 44, 
	91, 98, 100, 112, 113, 119, 10, 13, 
	42, 45, 48, 57, 65, 90, 97, 122, 
	32, 44, 91, 98, 100, 112, 113, 119, 
	9, 13, 42, 45, 48, 57, 65, 90, 
	97, 122, 9, 32, 45, 93, 42, 43, 
	48, 57, 65, 90, 97, 122, 32, 44, 
	9, 13, 9, 32, 44, 121, 42, 45, 
	48, 57, 65, 90, 97, 122, 9, 32, 
	44, 116, 42, 45, 48, 57, 65, 90, 
	97, 122, 9, 32, 44, 101, 42, 45, 
	48, 57, 65, 90, 97, 122, 9, 32, 
	44, 91, 98, 100, 112, 113, 119, 10, 
	13, 42, 45, 48, 57, 65, 90, 97, 
	122, 9, 32, 44, 91, 10, 13, 42, 
	45, 48, 57, 65, 90, 97, 122, 32, 
	91, 9, 13, 9, 32, 44, 119, 42, 
	45, 48, 57, 65, 90, 97, 122, 9, 
	32, 44, 111, 42, 45, 48, 57, 65, 
	90, 97, 122, 9, 32, 44, 114, 42, 
	45, 48, 57, 65, 90, 97, 122, 9, 
	32, 44, 100, 42, 45, 48, 57, 65, 
	90, 97, 122, 9, 32, 44, 116, 42, 
	45, 48, 57, 65, 90, 97, 122, 9, 
	32, 44, 114, 42, 45, 48, 57, 65, 
	90, 97, 122, 9, 32, 44, 121, 10, 
	13, 42, 45, 48, 57, 65, 90, 97, 
	122, 9, 32, 44, 116, 10, 13, 42, 
	45, 48, 57, 65, 90, 97, 122, 9, 
	32, 44, 101, 10, 13, 42, 45, 48, 
	57, 65, 90, 97, 122, 9, 32, 44, 
	91, 98, 100, 112, 113, 119, 10, 13, 
	42, 45, 48, 57, 65, 90, 97, 122, 
	9, 32, 44, 91, 10, 13, 42, 45, 
	48, 57, 65, 90, 97, 122, 32, 44, 
	91, 9, 13, 42, 45, 48, 57, 65, 
	90, 97, 122, 9, 32, 44, 119, 10, 
	13, 42, 45, 48, 57, 65, 90, 97, 
	122, 9, 32, 44, 111, 10, 13, 42, 
	45, 48, 57, 65, 90, 97, 122, 9, 
	32, 44, 114, 10, 13, 42, 45, 48, 
	57, 65, 90, 97, 122, 9, 32, 44, 
	100, 10, 13, 42, 45, 48, 57, 65, 
	90, 97, 122, 9, 32, 44, 116, 10, 
	13, 42, 45, 48, 57, 65, 90, 97, 
	122, 9, 32, 44, 114, 10, 13, 42, 
	45, 48, 57, 65, 90, 97, 122, 9, 
	32, 44, 91, 98, 100, 112, 113, 119, 
	10, 13, 42, 45, 48, 57, 65, 90, 
	97, 122, 9, 32, 44, 115, 116, 10, 
	13, 42, 45, 48, 57, 65, 90, 97, 
	122, 9, 32, 44, 100, 10, 13, 42, 
	45, 48, 57, 65, 90, 97, 122, 9, 
	32, 44, 91, 98, 100, 110, 112, 113, 
	119, 10, 13, 42, 45, 48, 57, 65, 
	90, 97, 122, 9, 32, 44, 112, 10, 
	13, 42, 45, 48, 57, 65, 90, 97, 
	122, 9, 32, 44, 115, 10, 13, 42, 
	45, 48, 57, 65, 90, 97, 122, 9, 
	32, 44, 109, 10, 13, 42, 45, 48, 
	57, 65, 90, 97, 122, 9, 32, 44, 
	111, 10, 13, 42, 45, 48, 57, 65, 
	90, 97, 122, 9, 32, 44, 118, 10, 
	13, 42, 45, 48, 57, 65, 90, 97, 
	122, 9, 32, 44, 98, 103, 110, 111, 
	112, 115, 10, 13, 42, 45, 48, 57, 
	65, 90, 97, 99, 100, 122, 9, 32, 
	44, 103, 115, 10, 13, 42, 45, 48, 
	57, 65, 90, 97, 122, 9, 32, 44, 
	101, 10, 13, 42, 45, 48, 57, 65, 
	90, 97, 122, 9, 32, 44, 101, 105, 
	10, 13, 42, 45, 48, 57, 65, 90, 
	97, 122, 9, 32, 44, 99, 10, 13, 
	42, 45, 48, 57, 65, 90, 97, 122, 
	9, 32, 44, 118, 10, 13, 42, 45, 
	48, 57, 65, 90, 97, 122, 9, 32, 
	44, 97, 99, 100, 105, 109, 115, 10, 
	13, 42, 45, 48, 57, 65, 90, 98, 
	122, 9, 32, 44, 100, 10, 13, 42, 
	45, 48, 57, 65, 90, 97, 122, 9, 
	32, 44, 100, 10, 13, 42, 45, 48, 
	57, 65, 90, 97, 122, 9, 32, 44, 
	91, 98, 100, 112, 113, 119, 10, 13, 
	42, 45, 48, 57, 65, 90, 97, 122, 
	9, 32, 44, 91, 98, 100, 112, 113, 
	116, 119, 10, 13, 42, 45, 48, 57, 
	65, 90, 97, 122, 9, 32, 44, 109, 
	10, 13, 42, 45, 48, 57, 65, 90, 
	97, 122, 9, 32, 44, 111, 10, 13, 
	42, 45, 48, 57, 65, 90, 97, 122, 
	9, 32, 44, 118, 10, 13, 42, 45, 
	48, 57, 65, 90, 97, 122, 9, 32, 
	44, 98, 101, 110, 117, 10, 13, 42, 
	45, 48, 57, 65, 90, 97, 122, 9, 
	32, 44, 91, 98, 100, 101, 112, 113, 
	119, 10, 13, 42, 45, 48, 57, 65, 
	90, 97, 122, 9, 32, 44, 98, 101, 
	117, 10, 13, 42, 45, 48, 57, 65, 
	90, 97, 122, 9, 32, 44, 105, 10, 
	13, 42, 45, 48, 57, 65, 90, 97, 
	122, 9, 32, 44, 118, 10, 13, 42, 
	45, 48, 57, 65, 90, 97, 122, 9, 
	32, 44, 91, 98, 100, 112, 113, 114, 
	119, 10, 13, 42, 45, 48, 57, 65, 
	90, 97, 122, 9, 32, 44, 97, 100, 
	109, 115, 10, 13, 42, 45, 48, 57, 
	65, 90, 98, 122, 9, 32, 44, 100, 
	10, 13, 42, 45, 48, 57, 65, 90, 
	97, 122, 9, 32, 44, 100, 10, 13, 
	42, 45, 48, 57, 65, 90, 97, 122, 
	9, 32, 44, 105, 10, 13, 42, 45, 
	48, 57, 65, 90, 97, 122, 9, 32, 
	44, 118, 10, 13, 42, 45, 48, 57, 
	65, 90, 97, 122, 9, 32, 44, 91, 
	98, 100, 112, 113, 114, 119, 10, 13, 
	42, 45, 48, 57, 65, 90, 97, 122, 
	9, 32, 44, 117, 10, 13, 42, 45, 
	48, 57, 65, 90, 97, 122, 9, 32, 
	44, 108, 10, 13, 42, 45, 48, 57, 
	65, 90, 97, 122, 9, 32, 44, 117, 
	10, 13, 42, 45, 48, 57, 65, 90, 
	97, 122, 9, 32, 44, 98, 10, 13, 
	42, 45, 48, 57, 65, 90, 97, 122, 
	9, 32, 44, 117, 10, 13, 42, 45, 
	48, 57, 65, 90, 97, 122, 9, 32, 
	44, 108, 10, 13, 42, 45, 48, 57, 
	65, 90, 97, 122, 9, 32, 44, 117, 
	10, 13, 42, 45, 48, 57, 65, 90, 
	97, 122, 9, 32, 44, 98, 10, 13, 
	42, 45, 48, 57, 65, 90, 97, 122, 
	9, 32, 44, 100, 109, 110, 10, 13, 
	42, 45, 48, 57, 65, 90, 97, 122, 
	9, 32, 44, 105, 10, 13, 42, 45, 
	48, 57, 65, 90, 97, 122, 9, 32, 
	44, 118, 10, 13, 42, 45, 48, 57, 
	65, 90, 97, 122, 9, 32, 44, 101, 
	111, 10, 13, 42, 45, 48, 57, 65, 
	90, 97, 122, 9, 32, 44, 97, 10, 
	13, 42, 45, 48, 57, 65, 90, 98, 
	122, 9, 32, 44, 100, 10, 13, 42, 
	45, 48, 57, 65, 90, 97, 122, 9, 
	32, 44, 115, 10, 13, 42, 45, 48, 
	57, 65, 90, 97, 122, 9, 32, 44, 
	98, 100, 119, 10, 13, 42, 45, 48, 
	57, 65, 90, 97, 122, 9, 32, 44, 
	111, 117, 10, 13, 42, 45, 48, 57, 
	65, 90, 97, 122, 9, 32, 44, 118, 
	10, 13, 42, 45, 48, 57, 65, 90, 
	97, 122, 9, 32, 44, 91, 97, 98, 
	100, 104, 108, 110, 112, 113, 115, 117, 
	119, 122, 10, 13, 42, 45, 48, 57, 
	65, 90, 99, 121, 9, 32, 44, 104, 
	112, 10, 13, 42, 45, 48, 57, 65, 
	90, 97, 122, 9, 32, 44, 116, 10, 
	13, 42, 45, 48, 57, 65, 90, 97, 
	122, 9, 32, 44, 105, 112, 10, 13, 
	42, 45, 48, 57, 65, 90, 97, 122, 
	9, 32, 44, 98, 100, 10, 13, 42, 
	45, 48, 57, 65, 90, 97, 118, 119, 
	120, 121, 122, 9, 32, 44, 120, 10, 
	13, 42, 45, 48, 57, 65, 90, 97, 
	122, 9, 32, 44, 101, 111, 10, 13, 
	42, 45, 48, 57, 65, 90, 97, 122, 
	9, 32, 44, 103, 10, 13, 42, 45, 
	48, 57, 65, 90, 97, 122, 9, 32, 
	44, 112, 116, 10, 13, 42, 45, 48, 
	57, 65, 90, 97, 122, 9, 32, 44, 
	114, 10, 13, 42, 45, 48, 57, 65, 
	90, 97, 122, 9, 32, 44, 97, 109, 
	115, 120, 10, 13, 42, 45, 48, 57, 
	65, 90, 98, 122, 9, 32, 44, 100, 
	110, 10, 13, 42, 45, 48, 57, 65, 
	90, 97, 122, 9, 32, 44, 100, 10, 
	13, 42, 45, 48, 57, 65, 90, 97, 
	122, 9, 32, 44, 98, 100, 113, 115, 
	117, 119, 10, 13, 42, 45, 48, 57, 
	65, 90, 97, 122, 9, 32, 44, 98, 
	119, 10, 13, 42, 45, 48, 57, 65, 
	90, 97, 122, 9, 32, 44, 115, 10, 
	13, 42, 45, 48, 57, 65, 90, 97, 
	122, 9, 32, 44, 98, 10, 13, 42, 
	45, 48, 57, 65, 90, 97, 122, 9, 
	32, 44, 100, 10, 13, 42, 45, 48, 
	57, 65, 90, 97, 122, 9, 32, 44, 
	91, 98, 100, 110, 112, 113, 119, 10, 
	13, 42, 45, 48, 57, 65, 90, 97, 
	122, 9, 32, 44, 97, 111, 117, 10, 
	13, 42, 45, 48, 57, 65, 90, 98, 
	122, 9, 32, 44, 100, 10, 13, 42, 
	45, 48, 57, 65, 90, 97, 122, 9, 
	32, 44, 100, 10, 13, 42, 45, 48, 
	57, 65, 90, 97, 122, 9, 32, 44, 
	119, 10, 13, 42, 45, 48, 57, 65, 
	90, 97, 122, 9, 32, 44, 118, 10, 
	13, 42, 45, 48, 57, 65, 90, 97, 
	122, 9, 32, 44, 109, 10, 13, 42, 
	45, 48, 57, 65, 90, 97, 122, 9, 
	32, 44, 115, 10, 13, 42, 45, 48, 
	57, 65, 90, 97, 122, 9, 32, 44, 
	107, 10, 13, 42, 45, 48, 57, 65, 
	90, 97, 122, 9, 32, 44, 108, 10, 
	13, 42, 45, 48, 57, 65, 90, 97, 
	122, 9, 32, 44, 104, 108, 117, 10, 
	13, 42, 45, 48, 57, 65, 90, 97, 
	122, 9, 32, 44, 117, 119, 10, 13, 
	42, 45, 48, 57, 65, 90, 97, 122, 
	9, 32, 44, 119, 10, 13, 42, 45, 
	48, 57, 65, 90, 97, 122, 9, 32, 
	44, 100, 10, 13, 42, 45, 48, 57, 
	65, 90, 97, 122, 9, 32, 44, 113, 
	10, 13, 42, 45, 48, 57, 65, 90, 
	97, 122, 9, 32, 44, 117, 10, 13, 
	42, 45, 48, 57, 65, 90, 97, 122, 
	9, 32, 44, 98, 10, 13, 42, 45, 
	48, 57, 65, 90, 97, 122, 9, 32, 
	44, 98, 100, 113, 115, 117, 119, 10, 
	13, 42, 45, 48, 57, 65, 90, 97, 
	122, 9, 32, 44, 115, 10, 13, 42, 
	45, 48, 57, 65, 90, 97, 122, 9, 
	32, 44, 111, 10, 13, 42, 45, 48, 
	57, 65, 90, 97, 122, 9, 32, 44, 
	111, 10, 13, 42, 45, 48, 57, 65, 
	90, 97, 122, 9, 32, 44, 108, 114, 
	10, 13, 42, 45, 48, 57, 65, 90, 
	97, 122, 9, 32, 44, 97, 104, 116, 
	117, 10, 13, 42, 45, 48, 57, 65, 
	90, 98, 122, 9, 32, 44, 108, 114, 
	10, 13, 42, 45, 48, 57, 65, 90, 
	97, 122, 9, 32, 44, 91, 98, 100, 
	112, 113, 119, 10, 13, 42, 45, 48, 
	57, 65, 90, 97, 122, 9, 32, 44, 
	111, 10, 13, 42, 45, 48, 57, 65, 
	90, 97, 122, 9, 32, 44, 98, 10, 
	13, 42, 45, 48, 57, 65, 90, 97, 
	122, 9, 32, 44, 112, 10, 13, 42, 
	45, 48, 57, 65, 90, 97, 122, 9, 
	32, 44, 97, 10, 13, 42, 45, 48, 
	57, 65, 90, 98, 122, 9, 32, 44, 
	100, 10, 13, 42, 45, 48, 57, 65, 
	90, 97, 122, 9, 32, 44, 100, 10, 
	13, 42, 45, 48, 57, 65, 90, 97, 
	122, 9, 32, 44, 100, 119, 10, 13, 
	42, 45, 48, 57, 65, 90, 97, 122, 
	9, 32, 44, 97, 111, 10, 13, 42, 
	45, 48, 57, 65, 90, 98, 122, 0
};

static const char _x86instr_single_lengths[] = {
	0, 17, 3, 2, 3, 4, 4, 5, 
	5, 9, 8, 4, 2, 4, 4, 4, 
	9, 4, 2, 4, 4, 4, 4, 4, 
	4, 4, 4, 4, 9, 4, 3, 4, 
	4, 4, 4, 4, 4, 9, 5, 4, 
	10, 4, 4, 4, 4, 4, 9, 5, 
	4, 5, 4, 4, 9, 4, 4, 9, 
	10, 4, 4, 4, 7, 10, 6, 4, 
	4, 10, 7, 4, 4, 4, 4, 10, 
	4, 4, 4, 4, 4, 4, 4, 4, 
	6, 4, 4, 5, 4, 4, 4, 6, 
	5, 4, 16, 5, 4, 5, 5, 4, 
	5, 4, 5, 4, 7, 5, 4, 9, 
	5, 4, 4, 4, 10, 6, 4, 4, 
	4, 4, 4, 4, 4, 4, 6, 5, 
	4, 4, 4, 4, 4, 9, 4, 4, 
	4, 5, 7, 5, 9, 4, 4, 4, 
	4, 4, 4, 5, 5, 0
};

static const char _x86instr_range_lengths[] = {
	0, 5, 5, 5, 4, 4, 4, 5, 
	5, 5, 5, 4, 1, 4, 4, 4, 
	5, 5, 1, 4, 4, 4, 4, 4, 
	4, 5, 5, 5, 5, 5, 5, 5, 
	5, 5, 5, 5, 5, 5, 5, 5, 
	5, 5, 5, 5, 5, 5, 6, 5, 
	5, 5, 5, 5, 5, 5, 5, 5, 
	5, 5, 5, 5, 5, 5, 5, 5, 
	5, 5, 5, 5, 5, 5, 5, 5, 
	5, 5, 5, 5, 5, 5, 5, 5, 
	5, 5, 5, 5, 5, 5, 5, 5, 
	5, 5, 5, 5, 5, 5, 7, 5, 
	5, 5, 5, 5, 5, 5, 5, 5, 
	5, 5, 5, 5, 5, 5, 5, 5, 
	5, 5, 5, 5, 5, 5, 5, 5, 
	5, 5, 5, 5, 5, 5, 5, 5, 
	5, 5, 5, 5, 5, 5, 5, 5, 
	5, 5, 5, 5, 5, 0
};

static const short _x86instr_index_offsets[] = {
	0, 0, 23, 32, 40, 48, 57, 66, 
	77, 88, 103, 117, 126, 130, 139, 148, 
	157, 172, 182, 186, 195, 204, 213, 222, 
	231, 240, 250, 260, 270, 285, 295, 304, 
	314, 324, 334, 344, 354, 364, 379, 390, 
	400, 416, 426, 436, 446, 456, 466, 482, 
	493, 503, 514, 524, 534, 549, 559, 569, 
	584, 600, 610, 620, 630, 643, 659, 671, 
	681, 691, 707, 720, 730, 740, 750, 760, 
	776, 786, 796, 806, 816, 826, 836, 846, 
	856, 868, 878, 888, 899, 909, 919, 929, 
	941, 952, 962, 984, 995, 1005, 1016, 1029, 
	1039, 1050, 1060, 1071, 1081, 1094, 1105, 1115, 
	1130, 1141, 1151, 1161, 1171, 1187, 1199, 1209, 
	1219, 1229, 1239, 1249, 1259, 1269, 1279, 1291, 
	1302, 1312, 1322, 1332, 1342, 1352, 1367, 1377, 
	1387, 1397, 1408, 1421, 1432, 1447, 1457, 1467, 
	1477, 1487, 1497, 1507, 1518, 1529
};

static const unsigned char _x86instr_indicies[] = {
	1, 1, 3, 4, 5, 6, 7, 8, 
	9, 10, 11, 12, 13, 14, 15, 16, 
	17, 2, 1, 1, 1, 1, 0, 1, 
	1, 3, 2, 1, 1, 1, 1, 0, 
	2, 3, 2, 18, 18, 18, 18, 0, 
	18, 18, 3, 18, 18, 18, 18, 0, 
	3, 3, 3, 19, 3, 3, 3, 3, 
	0, 19, 19, 19, 20, 19, 19, 19, 
	19, 0, 1, 1, 3, 21, 22, 2, 
	1, 1, 1, 1, 0, 1, 1, 3, 
	23, 24, 2, 1, 1, 1, 1, 0, 
	23, 23, 3, 26, 27, 28, 29, 28, 
	30, 25, 1, 1, 1, 1, 0, 25, 
	3, 26, 31, 32, 33, 32, 34, 25, 
	18, 18, 18, 18, 0, 26, 26, 26, 
	35, 26, 26, 26, 26, 0, 35, 36, 
	35, 0, 18, 18, 3, 37, 18, 18, 
	18, 18, 0, 18, 18, 3, 38, 18, 
	18, 18, 18, 0, 18, 18, 3, 39, 
	18, 18, 18, 18, 0, 40, 39, 3, 
	26, 31, 32, 33, 32, 34, 41, 18, 
	18, 18, 18, 0, 40, 40, 3, 26, 
	41, 18, 18, 18, 18, 0, 41, 26, 
	41, 0, 18, 18, 3, 34, 18, 18, 
	18, 18, 0, 18, 18, 3, 42, 18, 
	18, 18, 18, 0, 18, 18, 3, 43, 
	18, 18, 18, 18, 0, 18, 18, 3, 
	39, 18, 18, 18, 18, 0, 18, 18, 
	3, 44, 18, 18, 18, 18, 0, 18, 
	18, 3, 39, 18, 18, 18, 18, 0, 
	1, 1, 3, 45, 2, 1, 1, 1, 
	1, 0, 1, 1, 3, 46, 2, 1, 
	1, 1, 1, 0, 1, 1, 3, 47, 
	2, 1, 1, 1, 1, 0, 48, 47, 
	3, 26, 27, 28, 29, 28, 30, 49, 
	1, 1, 1, 1, 0, 48, 48, 3, 
	26, 49, 1, 1, 1, 1, 0, 49, 
	3, 26, 49, 18, 18, 18, 18, 0, 
	1, 1, 3, 30, 2, 1, 1, 1, 
	1, 0, 1, 1, 3, 50, 2, 1, 
	1, 1, 1, 0, 1, 1, 3, 51, 
	2, 1, 1, 1, 1, 0, 1, 1, 
	3, 47, 2, 1, 1, 1, 1, 0, 
	1, 1, 3, 52, 2, 1, 1, 1, 
	1, 0, 1, 1, 3, 47, 2, 1, 
	1, 1, 1, 0, 23, 23, 3, 26, 
	27, 28, 53, 28, 30, 25, 1, 1, 
	1, 1, 0, 1, 1, 3, 23, 52, 
	2, 1, 1, 1, 1, 0, 1, 1, 
	3, 54, 2, 1, 1, 1, 1, 0, 
	23, 23, 3, 26, 27, 28, 55, 53, 
	28, 30, 25, 1, 1, 1, 1, 0, 
	1, 1, 3, 56, 2, 1, 1, 1, 
	1, 0, 1, 1, 3, 23, 2, 1, 
	1, 1, 1, 0, 1, 1, 3, 57, 
	2, 1, 1, 1, 1, 0, 1, 1, 
	3, 58, 2, 1, 1, 1, 1, 0, 
	1, 1, 3, 59, 2, 1, 1, 1, 
	1, 0, 1, 1, 3, 1, 23, 60, 
	23, 61, 23, 2, 1, 1, 1, 23, 
	1, 0, 1, 1, 3, 23, 23, 2, 
	1, 1, 1, 1, 0, 1, 1, 3, 
	23, 2, 1, 1, 1, 1, 0, 1, 
	1, 3, 62, 63, 2, 1, 1, 1, 
	1, 0, 1, 1, 3, 23, 2, 1, 
	1, 1, 1, 0, 1, 1, 3, 24, 
	2, 1, 1, 1, 1, 0, 1, 1, 
	3, 64, 65, 66, 67, 68, 69, 2, 
	1, 1, 1, 1, 0, 1, 1, 3, 
	70, 2, 1, 1, 1, 1, 0, 1, 
	1, 3, 71, 2, 1, 1, 1, 1, 
	0, 23, 23, 3, 26, 27, 28, 72, 
	28, 30, 25, 1, 1, 1, 1, 0, 
	23, 23, 3, 26, 27, 28, 29, 28, 
	52, 30, 25, 1, 1, 1, 1, 0, 
	1, 1, 3, 73, 2, 1, 1, 1, 
	1, 0, 1, 1, 3, 74, 2, 1, 
	1, 1, 1, 0, 1, 1, 3, 75, 
	2, 1, 1, 1, 1, 0, 1, 1, 
	3, 76, 23, 77, 23, 2, 1, 1, 
	1, 1, 0, 23, 23, 3, 26, 27, 
	28, 23, 29, 28, 30, 25, 1, 1, 
	1, 1, 0, 1, 1, 3, 76, 23, 
	23, 2, 1, 1, 1, 1, 0, 1, 
	1, 3, 78, 2, 1, 1, 1, 1, 
	0, 1, 1, 3, 79, 2, 1, 1, 
	1, 1, 0, 23, 23, 3, 26, 27, 
	28, 72, 28, 71, 30, 25, 1, 1, 
	1, 1, 0, 1, 1, 3, 80, 81, 
	82, 83, 2, 1, 1, 1, 1, 0, 
	1, 1, 3, 84, 2, 1, 1, 1, 
	1, 0, 1, 1, 3, 23, 2, 1, 
	1, 1, 1, 0, 1, 1, 3, 85, 
	2, 1, 1, 1, 1, 0, 1, 1, 
	3, 86, 2, 1, 1, 1, 1, 0, 
	23, 23, 3, 26, 27, 28, 29, 28, 
	23, 30, 25, 1, 1, 1, 1, 0, 
	1, 1, 3, 87, 2, 1, 1, 1, 
	1, 0, 1, 1, 3, 23, 2, 1, 
	1, 1, 1, 0, 1, 1, 3, 88, 
	2, 1, 1, 1, 1, 0, 1, 1, 
	3, 86, 2, 1, 1, 1, 1, 0, 
	1, 1, 3, 89, 2, 1, 1, 1, 
	1, 0, 1, 1, 3, 71, 2, 1, 
	1, 1, 1, 0, 1, 1, 3, 90, 
	2, 1, 1, 1, 1, 0, 1, 1, 
	3, 79, 2, 1, 1, 1, 1, 0, 
	1, 1, 3, 91, 82, 62, 2, 1, 
	1, 1, 1, 0, 1, 1, 3, 92, 
	2, 1, 1, 1, 1, 0, 1, 1, 
	3, 23, 2, 1, 1, 1, 1, 0, 
	1, 1, 3, 93, 94, 2, 1, 1, 
	1, 1, 0, 1, 1, 3, 23, 2, 
	1, 1, 1, 1, 0, 1, 1, 3, 
	95, 2, 1, 1, 1, 1, 0, 1, 
	1, 3, 96, 2, 1, 1, 1, 1, 
	0, 1, 1, 3, 23, 23, 23, 2, 
	1, 1, 1, 1, 0, 1, 1, 3, 
	97, 87, 2, 1, 1, 1, 1, 0, 
	1, 1, 3, 98, 2, 1, 1, 1, 
	1, 0, 23, 23, 3, 26, 55, 27, 
	28, 55, 99, 100, 29, 23, 101, 55, 
	30, 102, 25, 1, 1, 1, 1, 0, 
	1, 1, 3, 55, 56, 2, 1, 1, 
	1, 1, 0, 1, 1, 3, 103, 2, 
	1, 1, 1, 1, 0, 1, 1, 3, 
	23, 56, 2, 1, 1, 1, 1, 0, 
	1, 1, 3, 23, 23, 2, 1, 1, 
	1, 1, 23, 1, 0, 1, 1, 3, 
	23, 2, 1, 1, 1, 1, 0, 1, 
	1, 3, 104, 105, 2, 1, 1, 1, 
	1, 0, 1, 1, 3, 23, 2, 1, 
	1, 1, 1, 0, 1, 1, 3, 23, 
	23, 2, 1, 1, 1, 1, 0, 1, 
	1, 3, 23, 2, 1, 1, 1, 1, 
	0, 1, 1, 3, 106, 107, 108, 109, 
	2, 1, 1, 1, 1, 0, 1, 1, 
	3, 110, 111, 2, 1, 1, 1, 1, 
	0, 1, 1, 3, 112, 2, 1, 1, 
	1, 1, 0, 1, 1, 3, 23, 23, 
	23, 113, 114, 23, 2, 1, 1, 1, 
	1, 0, 1, 1, 3, 23, 23, 2, 
	1, 1, 1, 1, 0, 1, 1, 3, 
	115, 2, 1, 1, 1, 1, 0, 1, 
	1, 3, 23, 2, 1, 1, 1, 1, 
	0, 1, 1, 3, 116, 2, 1, 1, 
	1, 1, 0, 23, 23, 3, 26, 27, 
	28, 23, 29, 28, 30, 25, 1, 1, 
	1, 1, 0, 1, 1, 3, 117, 118, 
	119, 2, 1, 1, 1, 1, 0, 1, 
	1, 3, 120, 2, 1, 1, 1, 1, 
	0, 1, 1, 3, 121, 2, 1, 1, 
	1, 1, 0, 1, 1, 3, 84, 2, 
	1, 1, 1, 1, 0, 1, 1, 3, 
	122, 2, 1, 1, 1, 1, 0, 1, 
	1, 3, 123, 2, 1, 1, 1, 1, 
	0, 1, 1, 3, 124, 2, 1, 1, 
	1, 1, 0, 1, 1, 3, 115, 2, 
	1, 1, 1, 1, 0, 1, 1, 3, 
	125, 2, 1, 1, 1, 1, 0, 1, 
	1, 3, 126, 127, 128, 2, 1, 1, 
	1, 1, 0, 1, 1, 3, 127, 23, 
	2, 1, 1, 1, 1, 0, 1, 1, 
	3, 23, 2, 1, 1, 1, 1, 0, 
	1, 1, 3, 129, 2, 1, 1, 1, 
	1, 0, 1, 1, 3, 23, 2, 1, 
	1, 1, 1, 0, 1, 1, 3, 130, 
	2, 1, 1, 1, 1, 0, 1, 1, 
	3, 131, 2, 1, 1, 1, 1, 0, 
	1, 1, 3, 23, 23, 23, 113, 132, 
	23, 2, 1, 1, 1, 1, 0, 1, 
	1, 3, 113, 2, 1, 1, 1, 1, 
	0, 1, 1, 3, 12, 2, 1, 1, 
	1, 1, 0, 1, 1, 3, 133, 2, 
	1, 1, 1, 1, 0, 1, 1, 3, 
	23, 23, 2, 1, 1, 1, 1, 0, 
	1, 1, 3, 12, 134, 135, 136, 2, 
	1, 1, 1, 1, 0, 1, 1, 3, 
	137, 137, 2, 1, 1, 1, 1, 0, 
	23, 23, 3, 26, 27, 23, 29, 28, 
	30, 25, 1, 1, 1, 1, 0, 1, 
	1, 3, 95, 2, 1, 1, 1, 1, 
	0, 1, 1, 3, 24, 2, 1, 1, 
	1, 1, 0, 1, 1, 3, 138, 2, 
	1, 1, 1, 1, 0, 1, 1, 3, 
	139, 2, 1, 1, 1, 1, 0, 1, 
	1, 3, 140, 2, 1, 1, 1, 1, 
	0, 1, 1, 3, 141, 2, 1, 1, 
	1, 1, 0, 1, 1, 3, 23, 23, 
	2, 1, 1, 1, 1, 0, 1, 1, 
	3, 80, 12, 2, 1, 1, 1, 1, 
	0, 0, 0
};

static const unsigned char _x86instr_trans_targs[] = {
	0, 2, 3, 5, 7, 43, 49, 52, 
	80, 83, 88, 96, 99, 100, 128, 130, 
	135, 140, 4, 6, 141, 8, 39, 9, 
	37, 10, 11, 25, 31, 35, 32, 13, 
	19, 23, 20, 12, 141, 14, 15, 16, 
	17, 18, 21, 22, 24, 26, 27, 28, 
	29, 30, 33, 34, 36, 38, 40, 41, 
	42, 44, 45, 46, 47, 48, 50, 51, 
	53, 57, 63, 66, 76, 78, 54, 55, 
	56, 58, 59, 60, 61, 62, 64, 65, 
	67, 69, 72, 74, 68, 70, 71, 73, 
	75, 77, 79, 81, 82, 84, 85, 86, 
	87, 89, 90, 91, 92, 94, 95, 93, 
	97, 98, 101, 109, 123, 127, 102, 107, 
	103, 104, 105, 106, 108, 110, 113, 117, 
	111, 112, 114, 115, 116, 118, 119, 120, 
	121, 122, 124, 125, 126, 129, 131, 133, 
	134, 132, 136, 137, 138, 139
};

static const char _x86instr_trans_actions[] = {
	1, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 2, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 3, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0
};

static const char _x86instr_eof_actions[] = {
	0, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 0
};

static const int x86instr_start = 1;
static const int x86instr_first_final = 141;
static const int x86instr_error = 0;

static const int x86instr_en_main = 1;


#line 91 "instructionparser.rl"

int scan_instruction(char *data) {
	char* p;
        p = data;
	char* pe = -1; /* No end to buffer - very nerve-wracking */
	char* eof = -1;
	int cs;

	// reset flags
	read_op=0;
	write_op=0;

	
#line 673 "instructionparser.c"
	{
	cs = x86instr_start;
	}

#line 104 "instructionparser.rl"

	
#line 681 "instructionparser.c"
	{
	int _klen;
	const char *_keys;
	int _trans;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	_keys = _x86instr_trans_keys + _x86instr_key_offsets[cs];
	_trans = _x86instr_index_offsets[cs];

	_klen = _x86instr_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _x86instr_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += ((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _x86instr_indicies[_trans];
	cs = _x86instr_trans_targs[_trans];

	if ( _x86instr_trans_actions[_trans] == 0 )
		goto _again;

	switch ( _x86instr_trans_actions[_trans] ) {
	case 1:
#line 52 "instructionparser.rl"
	{
    /* Called if we can't match the pattern for either a read or write */
    fprintf(stderr, "ERROR: Not a recognised instruction format: %s\n", data);
    return 1;
  }
	break;
	case 2:
#line 42 "instructionparser.rl"
	{
    read_op = 1;
    write_op = 0;
  }
#line 58 "instructionparser.rl"
	{
    {p++; goto _out; }
  }
	break;
	case 3:
#line 47 "instructionparser.rl"
	{
    read_op = 0;
    write_op = 1;
  }
#line 58 "instructionparser.rl"
	{
    {p++; goto _out; }
  }
	break;
#line 778 "instructionparser.c"
	}

_again:
	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	switch ( _x86instr_eof_actions[cs] ) {
	case 1:
#line 52 "instructionparser.rl"
	{
    /* Called if we can't match the pattern for either a read or write */
    fprintf(stderr, "ERROR: Not a recognised instruction format: %s\n", data);
    return 1;
  }
	break;
#line 798 "instructionparser.c"
	}
	}

	_out: {}
	}

#line 106 "instructionparser.rl"

	return 0;
}


