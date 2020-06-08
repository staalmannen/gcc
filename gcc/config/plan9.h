/* Operating system specific defines to be used when targeting GCC
   for Plan 9.

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

/* LPREFIX should be defined by default '.L' att.h style. But gas.h does
 * not define anything about that, and bsd.h has no option anymore since
 * GCC 3.4; so setting up it by hand.
 */

#undef LPREFIX
#define LPREFIX ".L"

/* The prefix to add for compiler private assembler symbols.  */

#undef LOCAL_LABEL_PREFIX
#define LOCAL_LABEL_PREFIX "."

/* This is how to store into the string BUF
   the symbol_ref name of an internal numbered label where
   PREFIX is the class of label and NUM is the number within the class.
   This is suitable for output with `assemble_name'.  */

#undef ASM_GENERATE_INTERNAL_LABEL
#define ASM_GENERATE_INTERNAL_LABEL(BUF,PREFIX,NUMBER)  \
  sprintf ((BUF), "%s%s%ld", LOCAL_LABEL_PREFIX, (PREFIX), (long)(NUMBER))

/* Define the syntax of labels and symbol definitions/declarations.
 * Overrides actual default in bsd.h; in previous GCC versions there was
 * an option.
 */

#undef USER_LABEL_PREFIX
#define USER_LABEL_PREFIX 	""

/* String containing the assembler's comment-starter.
 * Note the trailing space is necessary in case the character
 * that immediately follows the comment is '*'.  If this happens
 * and the space is not there the assembler will interpret this
 * as the start of a C-like slash-star comment and complain when
 * there is no terminator.
 * Overriding gas.h, from unix.h.
 */

#undef ASM_COMMENT_START
#define ASM_COMMENT_START "/ "

/* No separate math library (no -lm). It's in ape/libc/math :) */

#define MATH_LIBRARY ""

/*                          Plan9 POSIX threads                      *
 *                          *******************                      */

/* Added libbsd and libpthread as a part of standard library, both are
 * used by default. Check for shared because there are dummy shared flags
 * during bootstrap or into another packages of sources made with
 * autoconf.
 */
 
#undef  LIB_SPEC
#define LIB_SPEC "%{!shared:%{pthread:-lpthread}} -lbsd -lc"

/* Every program on Plan 9 compiled with GCC links against libpthread.a
 * which contains the pthread routines, so there's no need to explicitly
 * call out when doing threaded work (-fopenmp / -fgnu-tm options imply
 * pthreads in gcc.c).
 */

#undef GOMP_SELF_SPECS
#define GOMP_SELF_SPECS ""
#undef GTM_SELF_SPECS
#define GTM_SELF_SPECS ""

/* Need it by default unless you wan to type always -pthread option; libgcc,
 * gfortran, g++ and others libs will use it by default. Specified in
 * plan9.opt file. Default option removed except for AIX ad Solaris
 * since GCC 4.6. Perhaps more options would be added to that file.
 */

#define DRIVER_SELF_SPECS "-pthread"

/*                          END Plan9 POSIX threads                  *
 *                          ***********************                  */

/*                            Plan9 C++                              *
 *                            *********                              */

/* Plan 9 linking with libstdc++ requires libsupc++ as well. */

#define LIBSTDCXX_STATIC "supc++"

/* More g++, forcing cc1/cc1plus to run Global CTORS/DTORS.
 * If defined, 'main' will call '__main' despite the presence of
 * 'INIT_SECTION_ASM_OP'.
 * This macro should be defined for systems where the init section is
 * not actually run automatically, but is still useful for collecting
 * the lists of constructors and destructors.  */
 
#define INVOKE__main

/*                          END Plan9 C++                            *
 *                          *************                            */

/*                          Plan9 DBX Debug                          *
 *                          ***************                          */
 
/* When generating stabs debugging, use N_BINCL entries SunOS style.
 * --
 * This is designed for ELF systems (dbxelf.h), but is not the only
 * thing from dynamic linking that David Hogan included in his original
 * port. I Don't know if he was trying to emit native code from Plan9
 * for GNU binutils or planing a migration to ELF/dynamic linking some
 * day. Perhaps in future it will be useful.
 */

#define DBX_USE_BINCL

/* There is no limit to the length of stabs strings.  */

#define DBX_CONTIN_LENGTH 0

/* Generate a blank trailing N_SO to mark the end of the .o file, since
 * we can't depend upon the linker to mark .o file boundaries with
 * embedded stabs.
 */

#define DBX_OUTPUT_NULL_N_SO_AT_MAIN_SOURCE_FILE_END

/* .file at the begining of the assembler source file.
 * Default is false, but gas.h set to true. We return to false
 * as David Hogan did for his Plan 9 GCC 3.0 port.
 */

#undef TARGET_ASM_FILE_START_FILE_DIRECTIVE
#define TARGET_ASM_FILE_START_FILE_DIRECTIVE false

/*                      END Plan9 DBX Debug                          *
 *                      *******************                          */

/* Policy about Named Sections in gas has been changed since gcc-4.5 times:
 * http://gcc.gnu.org/ml/gcc-patches/2011-06/msg01642.html
 */

#define TARGET_HAVE_NAMED_SECTIONS false

/****************
 * EXPERIMENTAL *
 ****************/

/* We need this since G++ is the default compiler. Avoiding possible
 * issues about C++ system C headers compliance.
 */

#undef NO_IMPLICIT_EXTERN_C
#define NO_IMPLICIT_EXTERN_C

/* This was a warning with gcc 4.7, now things are more strict :(
 * http://gcc.gnu.org/bugzilla/show_bug.cgi?id=47099
 */

#undef ASM_DECLARE_FUNCTION_NAME
#define ASM_DECLARE_FUNCTION_NAME(FILE, NAME, DECL)                     \
  do {                                                                  \
    ASM_OUTPUT_FUNCTION_LABEL (FILE, NAME, DECL);                       \
  } while (0)

/* Trying to avoid General Protection Fault in libcpp/lex.c by illegals movdqa
 * in Plan 9.
 * See in libcpp/lex.c how to bypass search_line_* functions for
 * SSE2 and SSE4 (4.2).
 */

#undef ASM_QUAD

/* Don't default to pcc-struct-return, because gcc is the only compiler in its
 * environment, and we want to retain compatibility with older gcc versions.
 */

#define DEFAULT_PCC_STRUCT_RETURN 0

