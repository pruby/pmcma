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

%%{
  machine x86instr;

  action is_read {
    read_op = 1;
    write_op = 0;
  }
  
  action is_write {
    read_op = 0;
    write_op = 1;
  }
  
  action error {
    /* Called if we can't match the pattern for either a read or write */
    fprintf(stderr, "ERROR: Not a recognised instruction format: %s\n", data);
    return 1;
  }
  
  action complete {
    fbreak;
  }
  
  memmove = "stosb"|"stosd"|"stosw"|"lodsb"|"lodsd"|"lodsw";
  move = "cmova"|"cmovc"|"cmovg"|"cmovng"|"cmovns"|"cmovo"|"cmovpe"|"cmovs"|"fcmovb"|"fcmovbe"|"fcmove"|"fcmovnb"|"fcmovnbe"|"fcmovne"|"fcmovnu"|"fcmovu"|"mov"|"movaps"|"movhps"|"movlhps"|"movlps"|"movnti"|"movntps"|"movq"|"movsb"|"movsd"|"movsw"|"movsx"|"movups"|"movzx"|"pmovmskb"|"lea";

  ands = "and"|"andnps"|"andps"|"pand"|"pandn";
  xors = "pxor"|"xor";
  otherlogics = "neg"|"nop"|"not"|"or";
  logic = ands|xors|otherlogics;

  adds = "add"|"adc"|"addps"|"fadd"|"faddp"|"fiadd"|"paddb"|"paddd"|"paddq"|"paddsb"|"paddsw"|"paddusb"|"paddw"|"pmaddwd"|"vpaddd"|"vpaddw"|"xadd";
  subs = "fisub"|"fisubr"|"fsub"|"fsubp"|"fsubr"|"fsubrp"|"psubb"|"psubd"|"psubq"|"psubsb"|"psubsw"|"psubusb"|"psubusw"|"psubw"|"sub"|"subps";
  muls = "fimul"|"fmul"|"fmulp"|"imul"|"mul"|"pmulhuw"|"pmulhw"|"pmullw"|"pmuludq";
  divs = "div"|"divps"|"fdiv"|"fdivp"|"fdivr"|"fdivrp"|"fidiv"|"fidivr"|"idiv";
  otherarithmetics = "inc"|"dec"|"shl"|"shld"|"shr"|"shrd"|"rol"|"ror"|"sar";
  arithmetic = adds|subs|muls|divs|otherarithmetics;

  iwrite = memmove|move|arithmetic|logic;

  emptykeyword = " "|"byte"|"ptr"|"word"|"dword"|"qword";
  
  asm_char = ("a".."z") | ("0".."9") | ("A".."Z") | "\t" | " " | "+" | "-" | "*";

  write_op = iwrite space* emptykeyword* <: space* "[" asm_char* "]" space* "," @is_write;

  read_op = asm_char* space* asm_char* "," asm_char* "[" asm_char* "]" @is_read;

  main := ((read_op | write_op) @complete) $!error;
}%%

%% write data;

int scan_instruction(char *data) {
	char* p;
        p = data;
	char* pe = -1; /* No end to buffer - very nerve-wracking */
	char* eof = -1;
	int cs;

	// reset flags
	read_op=0;
	write_op=0;

	%% write init;

	%% write exec;

	return 0;
}


