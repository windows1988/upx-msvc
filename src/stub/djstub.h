/*
; Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details
; Copyright (C) 1997 DJ Delorie, see COPYING.DJ for details
; Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details
; Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details
; -*- asm -*-
;
; KLUDGE-WARNING!
;
; So you say you want to change this file, right?  Are you really sure
; that's a good idea?  Let me tell you a bit about the pitfalls here:
;
; * Some code runs in protected mode, some in real-mode, some in both.
; * Some code must run on a 8088 without crashing it.
; * Registers and flags may be expected to survive for a long time.
; * The code is optimized for size, not for speed or readability.
; * Some comments are parsed by other programs.
;
; You still want to change it?  Oh well, go ahead, but don't come
; crying back saying you weren't warned.
;
;-----------------------------------------------------------------------------
;  djgpp extender-less stub loader
;
;  (C) Copyright 1993-1995 DJ Delorie
;
;  Redistribution and use in source and binary forms are permitted
;  provided that: (1) source distributions retain this entire copyright
;  notice and comment, (2) distributions including binaries display
;  the following acknowledgement:  ``This product includes software
;  developed by DJ Delorie and contributors to the djgpp project''
;  in the documentation or other materials provided with the distribution
;  and in all advertising materials mentioning features or use of this
;  software, and (3) binary distributions include information sufficient
;  for the binary user to obtain the sources for the binary and utilities
;  required to built and use it. Neither the name of DJ Delorie nor the
;  names of djgpp's contributors may be used to endorse or promote
;  products derived from this software without specific prior written
;  permission.
;
;  THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
;  IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
;  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
;
;  Revision history:
;
;  93/12/05 DJ Delorie  Initial version v2.00, requires DPMI 0.9
;  94/10/13 CW Sandmann v2.01, accumlated changes: 60K load bug, limits, cwsdpmi, optimization
;  94/10/29 CW Sandmann v2.03, M Welinder changes; cwsdpmi load anywhere, size decrease
;
*/

#define STUBIFY_STUB_ADLER32 0x57f49e02

unsigned char stubify_stub[2048] = {
 77, 90,  0,  0,  4,  0,  0,  0, 32,  0, 39,  0,255,255,  0,  0,   /* 0x   0 */
 96,  7,  0,  0, 84,  0,  0,  0,  0,  0,  0,  0, 13, 10,115,116,   /* 0x  10 */
117, 98, 46,104, 32,103,101,110,101,114, 97,116,101,100, 32,102,   /* 0x  20 */
114,111,109, 32,115,116,117, 98, 46, 97,115,109, 32, 98,121, 32,   /* 0x  30 */
100,106, 97,115,109, 44, 32,111,110, 32, 84,104,117, 32, 68,101,   /* 0x  40 */
 99, 32, 32, 57, 32, 49, 48, 58, 53, 57, 58, 51, 49, 32, 49, 57,   /* 0x  50 */
 57, 57, 13, 10, 84,104,101, 32, 83, 84, 85, 66, 46, 69, 88, 69,   /* 0x  60 */
 32,115,116,117, 98, 32,108,111, 97,100,101,114, 32,105,115, 32,   /* 0x  70 */
 67,111,112,121,114,105,103,104,116, 32, 40, 67, 41, 32, 49, 57,   /* 0x  80 */
 57, 51, 45, 49, 57, 57, 53, 32, 68, 74, 32, 68,101,108,111,114,   /* 0x  90 */
105,101, 46, 32, 13, 10, 80,101,114,109,105,115,115,105,111,110,   /* 0x  a0 */
 32,103,114, 97,110,116,101,100, 32,116,111, 32,117,115,101, 32,   /* 0x  b0 */
102,111,114, 32, 97,110,121, 32,112,117,114,112,111,115,101, 32,   /* 0x  c0 */
112,114,111,118,105,100,101,100, 32,116,104,105,115, 32, 99,111,   /* 0x  d0 */
112,121,114,105,103,104,116, 32, 13, 10,114,101,109, 97,105,110,   /* 0x  e0 */
115, 32,112,114,101,115,101,110,116, 32, 97,110,100, 32,117,110,   /* 0x  f0 */
109,111,100,105,102,105,101,100, 46, 32, 13, 10, 84,104,105,115,   /* 0x 100 */
 32,111,110,108,121, 32, 97,112,112,108,105,101,115, 32,116,111,   /* 0x 110 */
 32,116,104,101, 32,115,116,117, 98, 44, 32, 97,110,100, 32,110,   /* 0x 120 */
111,116, 32,110,101, 99,101,115,115, 97,114,105,108,121, 32,116,   /* 0x 130 */
104,101, 32,119,104,111,108,101, 32,112,114,111,103,114, 97,109,   /* 0x 140 */
 46, 10, 13, 10, 36, 73,100, 58, 32,115,116,117, 98, 46, 97,115,   /* 0x 150 */
109, 32, 98,117,105,108,116, 32, 49, 50, 47, 48, 57, 47, 57, 57,   /* 0x 160 */
 32, 49, 48, 58, 53, 57, 58, 51, 49, 32, 98,121, 32,100,106, 97,   /* 0x 170 */
115,109, 32, 36, 10, 13, 10, 64, 40, 35, 41, 32,115,116,117, 98,   /* 0x 180 */
 46, 97,115,109, 32, 98,117,105,108,116, 32, 49, 50, 47, 48, 57,   /* 0x 190 */
 47, 57, 57, 32, 49, 48, 58, 53, 57, 58, 51, 49, 32, 98,121, 32,   /* 0x 1a0 */
100,106, 97,115,109, 10, 13, 10, 26,  0,  0,  0,  0,  0,  0,  0,   /* 0x 1b0 */
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   /* 0x 1c0 */
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   /* 0x 1d0 */
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   /* 0x 1e0 */
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   /* 0x 1f0 */
103,111, 51, 50,115,116,117, 98, 44, 32,118, 32, 50, 46, 48, 50,   /* 0x 200 */
 84,  0,  0,  0,  0,  0,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,   /* 0x 210 */
  0, 64,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   /* 0x 220 */
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   /* 0x 230 */
  0,  0,  0,  0, 67, 87, 83, 68, 80, 77, 73, 46, 69, 88, 69,  0,   /* 0x 240 */
  0,  0,  0,  0, 14, 31,140, 30, 36,  0,140,  6, 96,  7,252,180,   /* 0x 250 */
 48,205, 33, 60,  3,115,  8,176,109,186,167,  5,233,212,  3,162,   /* 0x 260 */
105,  8,190, 32,  0,139,  4,  9,192,117,  2,180,254,187,112,  8,   /* 0x 270 */
 57,195,115,  2,137,195,137, 28,254,199,185,  4,255,211,235,180,   /* 0x 280 */
 74,205, 33,115,  8,211,227,254,207,137, 28,235,216, 38,142,  6,   /* 0x 290 */
 44,  0, 49,255, 48,192,169,242,174, 38,129, 61, 80, 65,117, 21,   /* 0x 2a0 */
175, 38,129, 61, 84, 72,117, 13,175, 38,128, 61, 61,117,  6, 71,   /* 0x 2b0 */
137, 62,140,  4, 79,174,117,223,175,180, 62,187, 19,  0,205, 33,   /* 0x 2c0 */
180, 62,187, 18,  0,205, 33,  6, 87, 49,201,116, 18,176,110,186,   /* 0x 2d0 */
126,  5,233, 94,  3,  9,201,117,244, 65,232,161,  3,114,238,184,   /* 0x 2e0 */
135, 22,205, 47,  9,192,117,237,128,227,  1,116,232,137, 62,  0,   /* 0x 2f0 */
  6,140,  6,  2,  6,137, 54,  4,  6, 95,  7,232,211,  2,137, 62,   /* 0x 300 */
 42,  0,137, 54, 98,  7,128, 62, 44,  0,  0,116, 35,185,  8,  0,   /* 0x 310 */
191, 44,  0,138,  5, 71,  8,192,116,  5,136,  7, 67,226,244,102,   /* 0x 320 */
199,  7, 46, 69, 88, 69,131,195,  4,198,  7,  0,137, 30, 98,  7,   /* 0x 330 */
184,  0, 61,186,100,  7,205, 33, 15,130,179,  2,163,  6,  6,137,   /* 0x 340 */
195,185,  6,  0,186,181,  7,180, 63,205, 33, 49,210, 49,201,161,   /* 0x 350 */
181,  7, 61, 76,  1,116, 27, 61, 77, 90, 15,133,152,  2,139, 22,   /* 0x 360 */
185,  7,193,226,  9,139, 30,183,  7,  9,219,116,  5,128,238,  2,   /* 0x 370 */
  1,218,137, 22,187,  7,137, 14,189,  7,184,  0, 66,139, 30,  6,   /* 0x 380 */
  6,205, 33,185,168,  0,186,191,  7,180, 63,205, 33, 61,168,  0,   /* 0x 390 */
117,  6,129, 62,191,  7, 76,  1, 15,133, 97,  2,102,161,227,  7,   /* 0x 3a0 */
102,163, 16,  6,102,139, 14,187,  7,102,161,  3,  8,102,  1,200,   /* 0x 3b0 */
102,163,  8,  6,102,161, 43,  8,102,  1,200,102,163, 12,  6,102,   /* 0x 3c0 */
139, 30, 75,  8,102,161, 79,  8,102,  1,195,102,184,  1,  0,  1,   /* 0x 3d0 */
  0,102, 57,195,115,  3,102,137,195,102,129,195,255,255,  0,  0,   /* 0x 3e0 */
 49,219,102,137, 30, 28,  0,232,245,  2,139, 30,  4,  6,  9,219,   /* 0x 3f0 */
116, 10,180, 72,205, 33, 15,130, 21,  2,142,192,232,  8,  3,184,   /* 0x 400 */
  1,  0,255, 30,  0,  6, 15,130, 15,  2,140,  6, 38,  0,140, 14,   /* 0x 410 */
 40,  0,140,216,163, 34,  0,142,192, 49,192,185,  1,  0,205, 49,   /* 0x 420 */
114,  7,163, 20,  6, 49,192,205, 49, 15,130,243,  1,163, 22,  6,   /* 0x 430 */
102,139, 14, 28,  0,184,  1,  5,139, 30, 30,  0,205, 49, 15,130,   /* 0x 440 */
229,  1,137, 30, 26,  6,137, 14, 24,  6,137, 54, 26,  0,137, 62,   /* 0x 450 */
 24,  0,184,  7,  0,139, 30, 20,  6,139, 14, 26,  6,139, 22, 24,   /* 0x 460 */
  6,205, 49,184,  9,  0,140,201,131,225,  3,193,225,  5, 81,129,   /* 0x 470 */
201,155,192,205, 49,184,  8,  0,139, 14, 30,  0, 73,186,255,255,   /* 0x 480 */
205, 49,184,  7,  0,139, 30, 22,  6,139, 14, 26,  6,139, 22, 24,   /* 0x 490 */
  6,205, 49,184,  9,  0, 89,129,201,147,192,205, 49,184,  8,  0,   /* 0x 4a0 */
139, 14, 30,  0, 73,186,255,255,205, 49,184,  0,  1,187,  0, 15,   /* 0x 4b0 */
205, 49,115, 16, 61,  8,  0, 15,133,115,  1,184,  0,  1,205, 49,   /* 0x 4c0 */
 15,130,106,  1,163, 28,  6,137, 22, 30,  6,193,227,  4,137, 30,   /* 0x 4d0 */
 32,  6,102,139, 54,  8,  6,102,139, 62,251,  7,102,139, 14,255,   /* 0x 4e0 */
  7,232, 73,  0,102,139, 54, 12,  6,102,139, 62, 35,  8,102,139,   /* 0x 4f0 */
 14, 39,  8,232, 55,  0,142,  6, 22,  6,102,139, 62, 75,  8,102,   /* 0x 500 */
139, 14, 79,  8,102, 49,192,102,193,233,  2,103,243,102,171,180,   /* 0x 510 */
 62,139, 30,  6,  6,205, 33,184,  1,  1,139, 22, 30,  6,205, 49,   /* 0x 520 */
 30, 15,161,142, 30, 22,  6,102,100,255, 46, 16,  6,102,137,240,   /* 0x 530 */
102, 37,255,  1,  0,  0,102,  1,193, 41,198,102, 41,199,102,137,   /* 0x 540 */
 14, 38,  6,102,137, 62, 34,  6,232, 15,  1,137, 54, 62,  6,102,   /* 0x 550 */
193,238, 16,137, 54, 66,  6,139, 30,  6,  6,137, 30, 58,  6,199,   /* 0x 560 */
  6, 70,  6,  0, 66,232,  3,  1,161, 28,  6,163, 78,  6,199,  6,   /* 0x 570 */
 62,  6,  0,  0,198,  6, 71,  6, 63,161, 40,  6,  9,192,117,  9,   /* 0x 580 */
161, 38,  6, 59,  6, 32,  6,118,  3,161, 32,  6,163, 66,  6,232,   /* 0x 590 */
217,  0,102, 49,201,139, 14, 70,  6,102,139, 62, 34,  6,102,  1,   /* 0x 5a0 */
 14, 34,  6,102, 41, 14, 38,  6,102, 49,246,193,233,  2, 30,  6,   /* 0x 5b0 */
142,  6, 22,  6,142, 30, 30,  6,103,243,102,165,  7, 31,102,  3,   /* 0x 5c0 */
 14, 38,  6,117,175,195, 60, 58,116,  6, 60, 47,116,  2, 60, 92,   /* 0x 5d0 */
195,190,100,  7,137,243, 38,138,  5, 71,136,  4, 56,224,116, 14,   /* 0x 5e0 */
  8,192,116, 10, 70,232,222,255,117,236,137,243,116,232,195,176,   /* 0x 5f0 */
102,186, 72,  5,235, 12,176,103,186, 85,  5,235,  5,176,104,186,   /* 0x 600 */
 95,  5, 82,139, 30, 98,  7,198,  7, 36,187,100,  7,235, 40,232,   /* 0x 610 */
245,  0,176,105,186,153,  5,235, 26,176,106,186,178,  5,235, 19,   /* 0x 620 */
176,107,186,196,  5,235, 12,176,108,186,214,  5,235,  5,176,105,   /* 0x 630 */
186,153,  5, 82,187, 59,  5,232, 21,  0, 91,232, 17,  0,187,103,   /* 0x 640 */
  4,232, 11,  0,180, 76,205, 33, 67, 80,180,  2,205, 33, 88,138,   /* 0x 650 */
 23,128,250, 36,117,242,195, 13, 10, 36, 80, 81, 87, 49,192,191,   /* 0x 660 */
 42,  6,185, 25,  0,243,171, 95, 89, 88,195,184,  0,  3,187, 33,   /* 0x 670 */
  0, 49,201,102,191, 42,  6,  0,  0,205, 49,195,  0,  0, 48,228,   /* 0x 680 */
232, 78,255,137,222,139, 62,140,  4,235, 23,180, 59,232, 65,255,   /* 0x 690 */
129,254,100,  7,116, 18,138, 68,255,232, 42,255,116,  4,198,  4,   /* 0x 6a0 */
 92, 70,232,  3,  0,114,228,195,232, 52,  0,187, 68,  0,138,  7,   /* 0x 6b0 */
136,  4, 67, 70,  8,192,117,246,  6, 87, 30,  7,232,155,255,187,   /* 0x 6c0 */
 42,  6,140, 95,  4,137, 95,  2,186,100,  7,184,  0, 75,205, 33,   /* 0x 6d0 */
 95,  7,114,  9,180, 77,205, 33, 45,  0,  3,247,216,235, 40,128,   /* 0x 6e0 */
 62,105,  8,  5,114, 32,184,  0, 88,205, 33,162,103,  8,184,  2,   /* 0x 6f0 */
 88,205, 33,162,104,  8,184,  1, 88,187,128,  0,205, 33,184,  3,   /* 0x 700 */
 88,187,  1,  0,205, 33,195,156,128, 62,105,  8,  5,114, 26, 80,   /* 0x 710 */
 83,184,  3, 88,138, 30,104,  8, 48,255,205, 33,184,  1, 88,138,   /* 0x 720 */
 30,103,  8, 48,255,205, 33, 91, 88,157,195, 76,111, 97,100, 32,   /* 0x 730 */
101,114,114,111,114, 58, 32, 36, 58, 32, 99, 97,110, 39,116, 32,   /* 0x 740 */
111,112,101,110, 36, 58, 32,110,111,116, 32, 69, 88, 69, 36, 58,   /* 0x 750 */
 32,110,111,116, 32, 67, 79, 70, 70, 32, 40, 67,104,101, 99,107,   /* 0x 760 */
 32,102,111,114, 32,118,105,114,117,115,101,115, 41, 36,110,111,   /* 0x 770 */
 32, 68, 80, 77, 73, 32, 45, 32, 71,101,116, 32, 99,115,100,112,   /* 0x 780 */
109,105, 42, 98, 46,122,105,112, 36,110,111, 32, 68, 79, 83, 32,   /* 0x 790 */
109,101,109,111,114,121, 36,110,101,101,100, 32, 68, 79, 83, 32,   /* 0x 7a0 */
 51, 36, 99, 97,110, 39,116, 32,115,119,105,116, 99,104, 32,109,   /* 0x 7b0 */
111,100,101, 36,110,111, 32, 68, 80, 77, 73, 32,115,101,108,101,   /* 0x 7c0 */
 99,116,111,114,115, 36,110,111, 32, 68, 80, 77, 73, 32,109,101,   /* 0x 7d0 */
109,111,114,121, 36,144,144,144,144,144,144,144,144,144,144,144,   /* 0x 7e0 */
144,144,144,144,144,144,144,144,144,144,144,144,144,144,144,144    /* 0x 7f0 */
};