/* Target definitions for Intel 386 CPU running Plan 9

Copyright (C) 1989, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999,
   2000, 2001, 2002, 2003, 2004, 2005, 2007, 2008, 2009, 2010, 2011
   Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

/* Names to predefine in the preprocessor for this target machine.  */

#undef TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS() \
  do							\
    {							\
	builtin_define ("Plan9");					\
	builtin_define ("PLAN9");					\
	builtin_define ("__LITTLE_ENDIAN__");		\
	builtin_define ("_POSIX_SOURCE");			\
	builtin_define ("_LIMITS_EXTENSION");		\
	builtin_define ("_BSD_EXTENSION");			\
	builtin_define ("_SUSV2_SOURCE");			\
	builtin_define ("_RESEARCH_SOURCE");		\
	builtin_assert ("system=plan9");			\
    }							\
  while (0)

 
/* If hosted on Plan 9, set standard directory paths accordingly.
 * These definitions are target-specific.
 */

/* Looking for right place for c++ headers. Horrible hack, it should be
 * specified at configure time, but I'm always forgetting it :(.
 */

#undef GPLUSPLUS_INCLUDE_DIR
#define GPLUSPLUS_INCLUDE_DIR "/usr/pkg/include/c++/4.8.3"

#undef LOCAL_INCLUDE_DIR
#define LOCAL_INCLUDE_DIR "/usr/pkg/include"

#undef NATIVE_SYSTEM_HEADER_DIR
#define NATIVE_SYSTEM_HEADER_DIR "/sys/include/ape"

#undef STANDARD_STARTFILE_PREFIX
#define STANDARD_STARTFILE_PREFIX "/usr/pkg/lib/"

/* The host-specific ones are here */

#undef STANDARD_EXEC_PREFIX
#define STANDARD_EXEC_PREFIX "/usr/pkg/bin/"

#undef STANDARD_BINDIR_PREFIX
#define STANDARD_BINDIR_PREFIX "/usr/pkg/bin/"

#define MD_EXEC_PREFIX		"/usr/pkg/bin/"

#undef TOOLDIR_BASE_PREFIX
#define TOOLDIR_BASE_PREFIX "../../../usr/pkg/"

