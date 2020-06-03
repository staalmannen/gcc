/* Target definitions for GNU compiler for Intel x86 CPU running Plan 9
   Copyright (C) 1993, 1995, 1996, 1999 Free Software Foundation, Inc.

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

#include "i386-aout.h"          //new include
#include "gas.h"                //changed path
#include "../plan9port.h"       //changed path

/* Names to predefine in the preprocessor for this target machine.  */

/* old style, "poisoned" */
//#undef	CPP_PREDEFINES
//#define CPP_PREDEFINES "-Di386 -DPlan9 -D__LITTLE_ENDIAN__ -D_POSIX_SOURCE -D_LIMITS_EXTENSION -D_BSD_EXTENSION -D__ARCHITECTURE__=\"i386\" -Asystem(plan9)"

#undef TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS()                \
do                                              \
    {                                           \
        builtin_assert ("system=plan9");        \
        builtin_define ("Plan9");               \
        builtin_define ("_POSIX_SOURCE");       \
        builtin_define ("_LIMITS_EXTENSION");   \
        builtin_define ("_BSD_EXTENSION");      \
    }                                           \
while (0)
 
#ifdef Plan9
#undef	INCLUDE_DEFAULTS
#define INCLUDE_DEFAULTS				\
  {							\
    { "/386/include/gnu", 0, 0, 0 },		\
    { "/sys/include/gnu", 0, 0, 0 },		\
    { 0, 0, 0, 0 }				       	\
  }

#undef STANDARD_STARTFILE_PREFIX
#define STANDARD_STARTFILE_PREFIX "/386/lib/gnu/"

#endif
