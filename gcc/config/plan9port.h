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

/* When generating stabs debugging, use N_BINCL entries.  */

#undef  DBX_USE_BINCL
#define DBX_USE_BINCL

/* There is no limit to the length of stabs strings.  */

#ifndef DBX_CONTIN_LENGTH
#define DBX_CONTIN_LENGTH 0
#endif

/* When using stabs, gcc2_compiled must be a stabs entry, not an
   ordinary symbol, or gdb won't see it.  Furthermore, since gdb reads
   the input piecemeal, starting with each N_SO, it's a lot easier if
   the gcc2 flag symbol is *after* the N_SO rather than before it.  So
   we emit an N_OPT stab there.  */

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

#undef	ASM_FILE_START
#define	ASM_FILE_START(FILE)
