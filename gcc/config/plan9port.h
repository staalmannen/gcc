/* Operating system specific defines to be used when targeting GCC
   for Plan 9.

   Copyright (C) 1989, 90-93, 1996, 1997 Free Software Foundation, Inc.

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* The GNU tools operate better with stabs.  Since we don't have
   any native tools to be compatible with, default to stabs.  */

#include "dbx.h"
#include "../dbxout.h"          //new include

/* When generating stabs debugging, use N_BINCL entries.  */

#undef  DBX_USE_BINCL
#define DBX_USE_BINCL

/* There is no limit to the length of stabs strings.  */

#ifndef DBX_CONTIN_LENGTH
#define DBX_CONTIN_LENGTH 0
#endif

/* copied ... */
/* many things from gcc 3.0 config/i386/freebsd-aout.h
 * TODO: put those things under i386/plan9.h later */
#define YES_UNDERSCORES
#define DWARF2_UNWIND_INFO 0

#undef ASM_COMMENT_START
#define ASM_COMMENT_START "#"
#define ASM_APP_ON "#APP\n"
#define ASM_APP_OFF "#NO_APP\n"
#define TYPE_OPERAND_FMT	"@%s"

#define TYPE_ASM_OP	"\t.type\t"
#define SIZE_ASM_OP	"\t.size\t"
#define ASM_BYTE "\t.byte\t"
#define ASM_SHORT "\t.value\t"
#define ASM_LONG "\t.long\t"
#define ASM_QUAD "\t.quad\t"  /* Should not be used for 32bit compilation.  */

#define SET_ASM_OP	"\t.set\t"
#define GLOBAL_ASM_OP	"\t.globl\t"
#define TEXT_SECTION_ASM_OP "\t.text"
#define DATA_SECTION_ASM_OP "\t.data"
#define BSS_SECTION_ASM_OP "\t.bss"
#define GLOBAL_ASM_OP "\t.globl\t"

#ifndef ASM_DECLARE_RESULT
#define ASM_DECLARE_RESULT(FILE, RESULT)
#endif

#define ASM_OUTPUT_SKIP(FILE,SIZE)  \
  fprintf ((FILE), "\t.set .,.+%u\n", (int)(SIZE))
  
#define ASM_OUTPUT_LABEL(FILE,NAME)	\
  (assemble_name (FILE, NAME), fputs (":\n", FILE))

#define ASM_DECLARE_FUNCTION_NAME(FILE, NAME, DECL)			\
  do {									\
    fprintf (FILE, "%s", TYPE_ASM_OP);					\
    assemble_name (FILE, NAME);						\
    putc (',', FILE);							\
    fprintf (FILE, TYPE_OPERAND_FMT, "function");			\
    putc ('\n', FILE);							\
    ASM_DECLARE_RESULT (FILE, DECL_RESULT (DECL));			\
    ASM_OUTPUT_LABEL(FILE, NAME);					\
  } while (0)

#define ASM_DECLARE_OBJECT_NAME(FILE, NAME, DECL)			\
  do {									\
    fprintf (FILE, "%s", TYPE_ASM_OP);					\
    assemble_name (FILE, NAME);						\
    putc (',', FILE);							\
    fprintf (FILE, TYPE_OPERAND_FMT, "object");				\
    putc ('\n', FILE);							\
    size_directive_output = 0;						\
    if (!flag_inhibit_size_directive && DECL_SIZE (DECL))		\
      {									\
        size_directive_output = 1;					\
	fprintf (FILE, "%s", SIZE_ASM_OP);				\
	assemble_name (FILE, NAME);					\
	fprintf (FILE, ",%d\n",  int_size_in_bytes (TREE_TYPE (DECL)));	\
      }									\
    ASM_OUTPUT_LABEL(FILE, NAME);					\
  } while (0)
  
  
#define ASM_OUTPUT_LOCAL(FILE, NAME, SIZE, ROUNDED)  \
( fputs (".lcomm ", (FILE)),			\
  assemble_name ((FILE), (NAME)),		\
  fprintf ((FILE), ",%u\n", (int)(ROUNDED)))
  
#define TARGET_ASM_FILE_START_FILE_DIRECTIVE true

#define ASM_OUTPUT_COMMON(FILE, NAME, SIZE, ROUNDED)  \
( fputs (".comm ", (FILE)),			\
  assemble_name ((FILE), (NAME)),		\
  fprintf ((FILE), ",%u\n", (int)(ROUNDED)))
      
/* back to the original file */

/* When using stabs, gcc2_compiled must be a stabs entry, not an
   ordinary symbol, or gdb won't see it.  Furthermore, since gdb reads
   the input piecemeal, starting with each N_SO, it's a lot easier if
   the gcc2 flag symbol is *after* the N_SO rather than before it.  So
   we emit an N_OPT stab there.  */

/*
 * Removed and poisoned by GCC developers. 
#define ASM_IDENTIFY_GCC(FILE)						\
do									\
  {									\
    if (write_symbols != DBX_DEBUG)					\
      fputs ("gcc2_compiled.:\n", FILE);				\
  }									\
while (0)

#define ASM_IDENTIFY_GCC_AFTER_SOURCE(FILE)				\
do									\
  {									\
    if (write_symbols == DBX_DEBUG)					\
      fputs ("\t.stabs\t\"gcc2_compiled.\", 0x3c, 0, 0, 0\n", FILE);	\
  }									\
while (0)
*/

    
/* Generate a blank trailing N_SO to mark the end of the .o file, since
   we can't depend upon the linker to mark .o file boundaries with
   embedded stabs.  */

#undef  DBX_OUTPUT_MAIN_SOURCE_FILE_END
#define DBX_OUTPUT_MAIN_SOURCE_FILE_END(FILE, FILENAME)			\
  asm_fprintf (FILE,							\
	       "\t.text\n\t.stabs \"\",%d,0,0,%LLetext\n%LLetext:\n", N_SO)

/* being lazy; should build APE with different options (-g etc) */
#undef	LIB_SPEC
#define LIB_SPEC "-lc"

/* no separate math library */
#define MATH_LIBRARY ""

/* The '*' protects our label from being mangled by assemble_name() and dbxout_init() */
#undef ASM_GENERATE_INTERNAL_LABEL
#define ASM_GENERATE_INTERNAL_LABEL(BUF,PREFIX,NUMBER)	\
    sprintf ((BUF), "*.%s%d", (PREFIX), (NUMBER))

#define LPREFIX "L"    

//#undef	ASM_FILE_START
//#define	ASM_FILE_START(FILE) 

