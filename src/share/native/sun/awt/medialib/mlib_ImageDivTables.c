/*
 * Copyright 1998-2003 Sun Microsystems, Inc.  All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.  Sun designates this
 * particular file as subject to the "Classpath" exception as provided
 * by Sun in the LICENSE file that accompanied this code.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa Clara,
 * CA 95054 USA or visit www.sun.com if you need additional information or
 * have any questions.
 */
  

#ifdef __SUNPRO_C
#pragma ident	"@(#)mlib_ImageDivTables.c	1.20	02/03/07 SMI"
#endif /* __SUNPRO_C */

/*
 * DESCRIPTION:
 *
 *   mlib_u16 mlib_div6_tab[x] = 0xff00/6/x;
 *   mlib_u16 mlib_div1_tab[x] = 0xff00/x;
 *   mlib_d64 mlib_U82D64[x] = (mlib_d64)x;
 *   mlib_f32 mlib_U82F32[x] = (mlib_f32)x;
 *   mlib_f32 mlib_HSL2RGB_L2[x] = x/255.0 for x<128, and (255-x)/255.0 for x >= 128;
 *   mlib_f32 mlib_HSL2RGB_F[x] = 1.0 - fabs(fraction(x*3/256.) * 4.0f - 2.0)
 *
 * REFERENCING:
 *   mlib_div* tables are used to exclude dividing in functions
 *     mlib_ImageColorRGB2HSV
 *     mlib_ImageColorRGB2HSL
 *     mlib_ImageDivAlpha
 *
 *   table mlib_U82D64 is used to exclude conversion unsigned
 *   byte to double in functions
 *     mlib_ImageColorConvert...
 *     mlib_ImageDataTypeConvert
 *     mlib_ImageAffine
 *     mlib_ImageAffineTable
 *     mlib_ImageZoomTranslate
 *     mlib_ImageZoomTranslateTable
 *     mlib_ImageGridWarp
 *     mlib_ImagePolynomialWarp
 *     mlib_ImageCrossCorrel
 *     mlib_ImageMoment2
 *     mlib_ImageStdDev
 *     mlib_ImageFourierTransform
 *
 *   table mlib_U82F32 is used to exclude conversion unsigned
 *   byte to float in functions
 *     mlib_ImageBlend
 *     mlib_ImageDivShift
 *     mlib_ImageMulAlpha
 *     mlib_ImageMulAlpha_Inp
 *     mlib_ImageMulShift
 *     mlib_ImageBlend_BDST_BSRC
 *     mlib_ImageColorHSL2RGB
 *     mlib_ImageColorHSV2RGB
 *     mlib_ImageDataTypeConvert
 *     mlib_ImageAffine
 *     mlib_ImageAffineTable
 *     mlib_ImageZoomTranslate
 *     mlib_ImageZoomTranslateTable
 *     mlib_ImageConvMxN
 *     mlib_ImageSobel
 *     mlib_ImageGradient3x3
 *     mlib_ImageGradientMxN
 *
 *   tables mlib_HSL2RGB_* are used to exclude conversion unsigned
 *   byte to float in functions with some computations
 *     mlib_ImageColorHSL2RGB
 */

#include "mlib_image.h"
#define __DIV_TABLE_DEFINED
#include "mlib_ImageDivTables.h"

/***************************************************************/
/* *INDENT-OFF* */

const mlib_u16 mlib_div6_tab[] = {
 32767, 10880,  5440,  3627,  2720,  2176,  1813,  1554,
  1360,  1209,  1088,   989,   907,   837,   777,   725,
   680,   640,   604,   573,   544,   518,   495,   473,
   453,   435,   418,   403,   389,   375,   363,   351,
   340,   330,   320,   311,   302,   294,   286,   279,
   272,   265,   259,   253,   247,   242,   237,   231,
   227,   222,   218,   213,   209,   205,   201,   198,
   194,   191,   188,   184,   181,   178,   175,   173,
   170,   167,   165,   162,   160,   158,   155,   153,
   151,   149,   147,   145,   143,   141,   139,   138,
   136,   134,   133,   131,   130,   128,   127,   125,
   124,   122,   121,   120,   118,   117,   116,   115,
   113,   112,   111,   110,   109,   108,   107,   106,
   105,   104,   103,   102,   101,   100,    99,    98,
    97,    96,    95,    95,    94,    93,    92,    91,
    91,    90,    89,    88,    88,    87,    86,    86,
    85,    84,    84,    83,    82,    82,    81,    81,
    80,    79,    79,    78,    78,    77,    77,    76,
    76,    75,    75,    74,    74,    73,    73,    72,
    72,    71,    71,    70,    70,    69,    69,    68,
    68,    68,    67,    67,    66,    66,    66,    65,
    65,    64,    64,    64,    63,    63,    63,    62,
    62,    61,    61,    61,    60,    60,    60,    59,
    59,    59,    58,    58,    58,    58,    57,    57,
    57,    56,    56,    56,    56,    55,    55,    55,
    54,    54,    54,    54,    53,    53,    53,    53,
    52,    52,    52,    52,    51,    51,    51,    51,
    50,    50,    50,    50,    49,    49,    49,    49,
    49,    48,    48,    48,    48,    48,    47,    47,
    47,    47,    46,    46,    46,    46,    46,    46,
    45,    45,    45,    45,    45,    44,    44,    44,
    44,    44,    44,    43,    43,    43,    43,    43
};

/***************************************************************/

const mlib_u16 mlib_div1_tab[] = {
 65280, 65280, 32640, 21760, 16320, 13056, 10880,  9326,
  8160,  7253,  6528,  5935,  5440,  5022,  4663,  4352,
  4080,  3840,  3627,  3436,  3264,  3109,  2967,  2838,
  2720,  2611,  2511,  2418,  2331,  2251,  2176,  2106,
  2040,  1978,  1920,  1865,  1813,  1764,  1718,  1674,
  1632,  1592,  1554,  1518,  1484,  1451,  1419,  1389,
  1360,  1332,  1306,  1280,  1255,  1232,  1209,  1187,
  1166,  1145,  1126,  1106,  1088,  1070,  1053,  1036,
  1020,  1004,   989,   974,   960,   946,   933,   919,
   907,   894,   882,   870,   859,   848,   837,   826,
   816,   806,   796,   787,   777,   768,   759,   750,
   742,   733,   725,   717,   710,   702,   694,   687,
   680,   673,   666,   659,   653,   646,   640,   634,
   628,   622,   616,   610,   604,   599,   593,   588,
   583,   578,   573,   568,   563,   558,   553,   549,
   544,   540,   535,   531,   526,   522,   518,   514,
   510,   506,   502,   498,   495,   491,   487,   484,
   480,   476,   473,   470,   466,   463,   460,   457,
   453,   450,   447,   444,   441,   438,   435,   432,
   429,   427,   424,   421,   418,   416,   413,   411,
   408,   405,   403,   400,   398,   396,   393,   391,
   389,   386,   384,   382,   380,   377,   375,   373,
   371,   369,   367,   365,   363,   361,   359,   357,
   355,   353,   351,   349,   347,   345,   344,   342,
   340,   338,   336,   335,   333,   331,   330,   328,
   326,   325,   323,   322,   320,   318,   317,   315,
   314,   312,   311,   309,   308,   306,   305,   304,
   302,   301,   299,   298,   297,   295,   294,   293,
   291,   290,   289,   288,   286,   285,   284,   283,
   281,   280,   279,   278,   277,   275,   274,   273,
   272,   271,   270,   269,   268,   266,   265,   264,
   263,   262,   261,   260,   259,   258,   257,   256
};

/***************************************************************/

const mlib_f32 mlib_HSL2RGB_L2[] = {
 0.000000f, 0.003922f, 0.007843f, 0.011765f, 0.015686f, 0.019608f, 0.023529f, 0.027451f,
 0.031373f, 0.035294f, 0.039216f, 0.043137f, 0.047059f, 0.050980f, 0.054902f, 0.058824f,
 0.062745f, 0.066667f, 0.070588f, 0.074510f, 0.078431f, 0.082353f, 0.086275f, 0.090196f,
 0.094118f, 0.098039f, 0.101961f, 0.105882f, 0.109804f, 0.113725f, 0.117647f, 0.121569f,
 0.125490f, 0.129412f, 0.133333f, 0.137255f, 0.141176f, 0.145098f, 0.149020f, 0.152941f,
 0.156863f, 0.160784f, 0.164706f, 0.168627f, 0.172549f, 0.176471f, 0.180392f, 0.184314f,
 0.188235f, 0.192157f, 0.196078f, 0.200000f, 0.203922f, 0.207843f, 0.211765f, 0.215686f,
 0.219608f, 0.223529f, 0.227451f, 0.231373f, 0.235294f, 0.239216f, 0.243137f, 0.247059f,
 0.250980f, 0.254902f, 0.258824f, 0.262745f, 0.266667f, 0.270588f, 0.274510f, 0.278431f,
 0.282353f, 0.286275f, 0.290196f, 0.294118f, 0.298039f, 0.301961f, 0.305882f, 0.309804f,
 0.313725f, 0.317647f, 0.321569f, 0.325490f, 0.329412f, 0.333333f, 0.337255f, 0.341176f,
 0.345098f, 0.349020f, 0.352941f, 0.356863f, 0.360784f, 0.364706f, 0.368627f, 0.372549f,
 0.376471f, 0.380392f, 0.384314f, 0.388235f, 0.392157f, 0.396078f, 0.400000f, 0.403922f,
 0.407843f, 0.411765f, 0.415686f, 0.419608f, 0.423529f, 0.427451f, 0.431373f, 0.435294f,
 0.439216f, 0.443137f, 0.447059f, 0.450980f, 0.454902f, 0.458824f, 0.462745f, 0.466667f,
 0.470588f, 0.474510f, 0.478431f, 0.482353f, 0.486275f, 0.490196f, 0.494118f, 0.498039f,
 0.498039f, 0.494118f, 0.490196f, 0.486275f, 0.482353f, 0.478431f, 0.474510f, 0.470588f,
 0.466667f, 0.462745f, 0.458824f, 0.454902f, 0.450980f, 0.447059f, 0.443137f, 0.439216f,
 0.435294f, 0.431373f, 0.427451f, 0.423529f, 0.419608f, 0.415686f, 0.411765f, 0.407843f,
 0.403922f, 0.400000f, 0.396078f, 0.392157f, 0.388235f, 0.384314f, 0.380392f, 0.376471f,
 0.372549f, 0.368627f, 0.364706f, 0.360784f, 0.356863f, 0.352941f, 0.349020f, 0.345098f,
 0.341176f, 0.337255f, 0.333333f, 0.329412f, 0.325490f, 0.321569f, 0.317647f, 0.313725f,
 0.309804f, 0.305882f, 0.301961f, 0.298039f, 0.294118f, 0.290196f, 0.286275f, 0.282353f,
 0.278431f, 0.274510f, 0.270588f, 0.266667f, 0.262745f, 0.258824f, 0.254902f, 0.250980f,
 0.247059f, 0.243137f, 0.239216f, 0.235294f, 0.231373f, 0.227451f, 0.223529f, 0.219608f,
 0.215686f, 0.211765f, 0.207843f, 0.203922f, 0.200000f, 0.196078f, 0.192157f, 0.188235f,
 0.184314f, 0.180392f, 0.176471f, 0.172549f, 0.168627f, 0.164706f, 0.160784f, 0.156863f,
 0.152941f, 0.149020f, 0.145098f, 0.141176f, 0.137255f, 0.133333f, 0.129412f, 0.125490f,
 0.121569f, 0.117647f, 0.113725f, 0.109804f, 0.105882f, 0.101961f, 0.098039f, 0.094118f,
 0.090196f, 0.086275f, 0.082353f, 0.078431f, 0.074510f, 0.070588f, 0.066667f, 0.062745f,
 0.058824f, 0.054902f, 0.050980f, 0.047059f, 0.043137f, 0.039216f, 0.035294f, 0.031373f,
 0.027451f, 0.023529f, 0.019608f, 0.015686f, 0.011765f, 0.007843f, 0.003922f, 0.000000f
};

/***************************************************************/

const mlib_f32 mlib_HSL2RGB_F[] = {
 -1.000000f, -0.953125f, -0.906250f, -0.859375f, -0.812500f, -0.765625f, -0.718750f, -0.671875f,
 -0.625000f, -0.578125f, -0.531250f, -0.484375f, -0.437500f, -0.390625f, -0.343750f, -0.296875f,
 -0.250000f, -0.203125f, -0.156250f, -0.109375f, -0.062500f, -0.015625f,  0.031250f,  0.078125f,
  0.125000f,  0.171875f,  0.218750f,  0.265625f,  0.312500f,  0.359375f,  0.406250f,  0.453125f,
  0.500000f,  0.546875f,  0.593750f,  0.640625f,  0.687500f,  0.734375f,  0.781250f,  0.828125f,
  0.875000f,  0.921875f,  0.968750f,  0.984375f,  0.937500f,  0.890625f,  0.843750f,  0.796875f,
  0.750000f,  0.703125f,  0.656250f,  0.609375f,  0.562500f,  0.515625f,  0.468750f,  0.421875f,
  0.375000f,  0.328125f,  0.281250f,  0.234375f,  0.187500f,  0.140625f,  0.093750f,  0.046875f,
  0.000000f, -0.046875f, -0.093750f, -0.140625f, -0.187500f, -0.234375f, -0.281250f, -0.328125f,
 -0.375000f, -0.421875f, -0.468750f, -0.515625f, -0.562500f, -0.609375f, -0.656250f, -0.703125f,
 -0.750000f, -0.796875f, -0.843750f, -0.890625f, -0.937500f, -0.984375f, -0.968750f, -0.921875f,
 -0.875000f, -0.828125f, -0.781250f, -0.734375f, -0.687500f, -0.640625f, -0.593750f, -0.546875f,
 -0.500000f, -0.453125f, -0.406250f, -0.359375f, -0.312500f, -0.265625f, -0.218750f, -0.171875f,
 -0.125000f, -0.078125f, -0.031250f,  0.015625f,  0.062500f,  0.109375f,  0.156250f,  0.203125f,
  0.250000f,  0.296875f,  0.343750f,  0.390625f,  0.437500f,  0.484375f,  0.531250f,  0.578125f,
  0.625000f,  0.671875f,  0.718750f,  0.765625f,  0.812500f,  0.859375f,  0.906250f,  0.953125f,
  1.000000f,  0.953125f,  0.906250f,  0.859375f,  0.812500f,  0.765625f,  0.718750f,  0.671875f,
  0.625000f,  0.578125f,  0.531250f,  0.484375f,  0.437500f,  0.390625f,  0.343750f,  0.296875f,
  0.250000f,  0.203125f,  0.156250f,  0.109375f,  0.062500f,  0.015625f, -0.031250f, -0.078125f,
 -0.125000f, -0.171875f, -0.218750f, -0.265625f, -0.312500f, -0.359375f, -0.406250f, -0.453125f,
 -0.500000f, -0.546875f, -0.593750f, -0.640625f, -0.687500f, -0.734375f, -0.781250f, -0.828125f,
 -0.875000f, -0.921875f, -0.968750f, -0.984375f, -0.937500f, -0.890625f, -0.843750f, -0.796875f,
 -0.750000f, -0.703125f, -0.656250f, -0.609375f, -0.562500f, -0.515625f, -0.468750f, -0.421875f,
 -0.375000f, -0.328125f, -0.281250f, -0.234375f, -0.187500f, -0.140625f, -0.093750f, -0.046875f,
  0.000000f,  0.046875f,  0.093750f,  0.140625f,  0.187500f,  0.234375f,  0.281250f,  0.328125f,
  0.375000f,  0.421875f,  0.468750f,  0.515625f,  0.562500f,  0.609375f,  0.656250f,  0.703125f,
  0.750000f,  0.796875f,  0.843750f,  0.890625f,  0.937500f,  0.984375f,  0.968750f,  0.921875f,
  0.875000f,  0.828125f,  0.781250f,  0.734375f,  0.687500f,  0.640625f,  0.593750f,  0.546875f,
  0.500000f,  0.453125f,  0.406250f,  0.359375f,  0.312500f,  0.265625f,  0.218750f,  0.171875f,
  0.125000f,  0.078125f,  0.031250f, -0.015625f, -0.062500f, -0.109375f, -0.156250f, -0.203125f,
 -0.250000f, -0.296875f, -0.343750f, -0.390625f, -0.437500f, -0.484375f, -0.531250f, -0.578125f,
 -0.625000f, -0.671875f, -0.718750f, -0.765625f, -0.812500f, -0.859375f, -0.906250f, -0.953125f
};

/***************************************************************/

const mlib_f32 mlib_U82F32[] = {
    0.0f,   1.0f,   2.0f,   3.0f,   4.0f,   5.0f,   6.0f,   7.0f,
    8.0f,   9.0f,  10.0f,  11.0f,  12.0f,  13.0f,  14.0f,  15.0f,
   16.0f,  17.0f,  18.0f,  19.0f,  20.0f,  21.0f,  22.0f,  23.0f,
   24.0f,  25.0f,  26.0f,  27.0f,  28.0f,  29.0f,  30.0f,  31.0f,
   32.0f,  33.0f,  34.0f,  35.0f,  36.0f,  37.0f,  38.0f,  39.0f,
   40.0f,  41.0f,  42.0f,  43.0f,  44.0f,  45.0f,  46.0f,  47.0f,
   48.0f,  49.0f,  50.0f,  51.0f,  52.0f,  53.0f,  54.0f,  55.0f,
   56.0f,  57.0f,  58.0f,  59.0f,  60.0f,  61.0f,  62.0f,  63.0f,
   64.0f,  65.0f,  66.0f,  67.0f,  68.0f,  69.0f,  70.0f,  71.0f,
   72.0f,  73.0f,  74.0f,  75.0f,  76.0f,  77.0f,  78.0f,  79.0f,
   80.0f,  81.0f,  82.0f,  83.0f,  84.0f,  85.0f,  86.0f,  87.0f,
   88.0f,  89.0f,  90.0f,  91.0f,  92.0f,  93.0f,  94.0f,  95.0f,
   96.0f,  97.0f,  98.0f,  99.0f, 100.0f, 101.0f, 102.0f, 103.0f,
  104.0f, 105.0f, 106.0f, 107.0f, 108.0f, 109.0f, 110.0f, 111.0f,
  112.0f, 113.0f, 114.0f, 115.0f, 116.0f, 117.0f, 118.0f, 119.0f,
  120.0f, 121.0f, 122.0f, 123.0f, 124.0f, 125.0f, 126.0f, 127.0f,
  128.0f, 129.0f, 130.0f, 131.0f, 132.0f, 133.0f, 134.0f, 135.0f,
  136.0f, 137.0f, 138.0f, 139.0f, 140.0f, 141.0f, 142.0f, 143.0f,
  144.0f, 145.0f, 146.0f, 147.0f, 148.0f, 149.0f, 150.0f, 151.0f,
  152.0f, 153.0f, 154.0f, 155.0f, 156.0f, 157.0f, 158.0f, 159.0f,
  160.0f, 161.0f, 162.0f, 163.0f, 164.0f, 165.0f, 166.0f, 167.0f,
  168.0f, 169.0f, 170.0f, 171.0f, 172.0f, 173.0f, 174.0f, 175.0f,
  176.0f, 177.0f, 178.0f, 179.0f, 180.0f, 181.0f, 182.0f, 183.0f,
  184.0f, 185.0f, 186.0f, 187.0f, 188.0f, 189.0f, 190.0f, 191.0f,
  192.0f, 193.0f, 194.0f, 195.0f, 196.0f, 197.0f, 198.0f, 199.0f,
  200.0f, 201.0f, 202.0f, 203.0f, 204.0f, 205.0f, 206.0f, 207.0f,
  208.0f, 209.0f, 210.0f, 211.0f, 212.0f, 213.0f, 214.0f, 215.0f,
  216.0f, 217.0f, 218.0f, 219.0f, 220.0f, 221.0f, 222.0f, 223.0f,
  224.0f, 225.0f, 226.0f, 227.0f, 228.0f, 229.0f, 230.0f, 231.0f,
  232.0f, 233.0f, 234.0f, 235.0f, 236.0f, 237.0f, 238.0f, 239.0f,
  240.0f, 241.0f, 242.0f, 243.0f, 244.0f, 245.0f, 246.0f, 247.0f,
  248.0f, 249.0f, 250.0f, 251.0f, 252.0f, 253.0f, 254.0f, 255.0f,
  256.0f
};

/***************************************************************/

const mlib_d64 mlib_U82D64[] = {
    0.0,   1.0,   2.0,   3.0,   4.0,   5.0,   6.0,   7.0,
    8.0,   9.0,  10.0,  11.0,  12.0,  13.0,  14.0,  15.0,
   16.0,  17.0,  18.0,  19.0,  20.0,  21.0,  22.0,  23.0,
   24.0,  25.0,  26.0,  27.0,  28.0,  29.0,  30.0,  31.0,
   32.0,  33.0,  34.0,  35.0,  36.0,  37.0,  38.0,  39.0,
   40.0,  41.0,  42.0,  43.0,  44.0,  45.0,  46.0,  47.0,
   48.0,  49.0,  50.0,  51.0,  52.0,  53.0,  54.0,  55.0,
   56.0,  57.0,  58.0,  59.0,  60.0,  61.0,  62.0,  63.0,
   64.0,  65.0,  66.0,  67.0,  68.0,  69.0,  70.0,  71.0,
   72.0,  73.0,  74.0,  75.0,  76.0,  77.0,  78.0,  79.0,
   80.0,  81.0,  82.0,  83.0,  84.0,  85.0,  86.0,  87.0,
   88.0,  89.0,  90.0,  91.0,  92.0,  93.0,  94.0,  95.0,
   96.0,  97.0,  98.0,  99.0, 100.0, 101.0, 102.0, 103.0,
  104.0, 105.0, 106.0, 107.0, 108.0, 109.0, 110.0, 111.0,
  112.0, 113.0, 114.0, 115.0, 116.0, 117.0, 118.0, 119.0,
  120.0, 121.0, 122.0, 123.0, 124.0, 125.0, 126.0, 127.0,
  128.0, 129.0, 130.0, 131.0, 132.0, 133.0, 134.0, 135.0,
  136.0, 137.0, 138.0, 139.0, 140.0, 141.0, 142.0, 143.0,
  144.0, 145.0, 146.0, 147.0, 148.0, 149.0, 150.0, 151.0,
  152.0, 153.0, 154.0, 155.0, 156.0, 157.0, 158.0, 159.0,
  160.0, 161.0, 162.0, 163.0, 164.0, 165.0, 166.0, 167.0,
  168.0, 169.0, 170.0, 171.0, 172.0, 173.0, 174.0, 175.0,
  176.0, 177.0, 178.0, 179.0, 180.0, 181.0, 182.0, 183.0,
  184.0, 185.0, 186.0, 187.0, 188.0, 189.0, 190.0, 191.0,
  192.0, 193.0, 194.0, 195.0, 196.0, 197.0, 198.0, 199.0,
  200.0, 201.0, 202.0, 203.0, 204.0, 205.0, 206.0, 207.0,
  208.0, 209.0, 210.0, 211.0, 212.0, 213.0, 214.0, 215.0,
  216.0, 217.0, 218.0, 219.0, 220.0, 221.0, 222.0, 223.0,
  224.0, 225.0, 226.0, 227.0, 228.0, 229.0, 230.0, 231.0,
  232.0, 233.0, 234.0, 235.0, 236.0, 237.0, 238.0, 239.0,
  240.0, 241.0, 242.0, 243.0, 244.0, 245.0, 246.0, 247.0,
  248.0, 249.0, 250.0, 251.0, 252.0, 253.0, 254.0, 255.0,
  256.0
};

/***************************************************************/

const mlib_u32 mlib_FlipAndFixRotateTable[] = {
  0x00000000, 0x00000000, 0x00000000, 0x00000080,
  0x00000000, 0x00008000, 0x00000000, 0x00008080,
  0x00000000, 0x00800000, 0x00000000, 0x00800080,
  0x00000000, 0x00808000, 0x00000000, 0x00808080,
  0x00000000, 0x80000000, 0x00000000, 0x80000080,
  0x00000000, 0x80008000, 0x00000000, 0x80008080,
  0x00000000, 0x80800000, 0x00000000, 0x80800080,
  0x00000000, 0x80808000, 0x00000000, 0x80808080,
  0x00000080, 0x00000000, 0x00000080, 0x00000080,
  0x00000080, 0x00008000, 0x00000080, 0x00008080,
  0x00000080, 0x00800000, 0x00000080, 0x00800080,
  0x00000080, 0x00808000, 0x00000080, 0x00808080,
  0x00000080, 0x80000000, 0x00000080, 0x80000080,
  0x00000080, 0x80008000, 0x00000080, 0x80008080,
  0x00000080, 0x80800000, 0x00000080, 0x80800080,
  0x00000080, 0x80808000, 0x00000080, 0x80808080,
  0x00008000, 0x00000000, 0x00008000, 0x00000080,
  0x00008000, 0x00008000, 0x00008000, 0x00008080,
  0x00008000, 0x00800000, 0x00008000, 0x00800080,
  0x00008000, 0x00808000, 0x00008000, 0x00808080,
  0x00008000, 0x80000000, 0x00008000, 0x80000080,
  0x00008000, 0x80008000, 0x00008000, 0x80008080,
  0x00008000, 0x80800000, 0x00008000, 0x80800080,
  0x00008000, 0x80808000, 0x00008000, 0x80808080,
  0x00008080, 0x00000000, 0x00008080, 0x00000080,
  0x00008080, 0x00008000, 0x00008080, 0x00008080,
  0x00008080, 0x00800000, 0x00008080, 0x00800080,
  0x00008080, 0x00808000, 0x00008080, 0x00808080,
  0x00008080, 0x80000000, 0x00008080, 0x80000080,
  0x00008080, 0x80008000, 0x00008080, 0x80008080,
  0x00008080, 0x80800000, 0x00008080, 0x80800080,
  0x00008080, 0x80808000, 0x00008080, 0x80808080,
  0x00800000, 0x00000000, 0x00800000, 0x00000080,
  0x00800000, 0x00008000, 0x00800000, 0x00008080,
  0x00800000, 0x00800000, 0x00800000, 0x00800080,
  0x00800000, 0x00808000, 0x00800000, 0x00808080,
  0x00800000, 0x80000000, 0x00800000, 0x80000080,
  0x00800000, 0x80008000, 0x00800000, 0x80008080,
  0x00800000, 0x80800000, 0x00800000, 0x80800080,
  0x00800000, 0x80808000, 0x00800000, 0x80808080,
  0x00800080, 0x00000000, 0x00800080, 0x00000080,
  0x00800080, 0x00008000, 0x00800080, 0x00008080,
  0x00800080, 0x00800000, 0x00800080, 0x00800080,
  0x00800080, 0x00808000, 0x00800080, 0x00808080,
  0x00800080, 0x80000000, 0x00800080, 0x80000080,
  0x00800080, 0x80008000, 0x00800080, 0x80008080,
  0x00800080, 0x80800000, 0x00800080, 0x80800080,
  0x00800080, 0x80808000, 0x00800080, 0x80808080,
  0x00808000, 0x00000000, 0x00808000, 0x00000080,
  0x00808000, 0x00008000, 0x00808000, 0x00008080,
  0x00808000, 0x00800000, 0x00808000, 0x00800080,
  0x00808000, 0x00808000, 0x00808000, 0x00808080,
  0x00808000, 0x80000000, 0x00808000, 0x80000080,
  0x00808000, 0x80008000, 0x00808000, 0x80008080,
  0x00808000, 0x80800000, 0x00808000, 0x80800080,
  0x00808000, 0x80808000, 0x00808000, 0x80808080,
  0x00808080, 0x00000000, 0x00808080, 0x00000080,
  0x00808080, 0x00008000, 0x00808080, 0x00008080,
  0x00808080, 0x00800000, 0x00808080, 0x00800080,
  0x00808080, 0x00808000, 0x00808080, 0x00808080,
  0x00808080, 0x80000000, 0x00808080, 0x80000080,
  0x00808080, 0x80008000, 0x00808080, 0x80008080,
  0x00808080, 0x80800000, 0x00808080, 0x80800080,
  0x00808080, 0x80808000, 0x00808080, 0x80808080,
  0x80000000, 0x00000000, 0x80000000, 0x00000080,
  0x80000000, 0x00008000, 0x80000000, 0x00008080,
  0x80000000, 0x00800000, 0x80000000, 0x00800080,
  0x80000000, 0x00808000, 0x80000000, 0x00808080,
  0x80000000, 0x80000000, 0x80000000, 0x80000080,
  0x80000000, 0x80008000, 0x80000000, 0x80008080,
  0x80000000, 0x80800000, 0x80000000, 0x80800080,
  0x80000000, 0x80808000, 0x80000000, 0x80808080,
  0x80000080, 0x00000000, 0x80000080, 0x00000080,
  0x80000080, 0x00008000, 0x80000080, 0x00008080,
  0x80000080, 0x00800000, 0x80000080, 0x00800080,
  0x80000080, 0x00808000, 0x80000080, 0x00808080,
  0x80000080, 0x80000000, 0x80000080, 0x80000080,
  0x80000080, 0x80008000, 0x80000080, 0x80008080,
  0x80000080, 0x80800000, 0x80000080, 0x80800080,
  0x80000080, 0x80808000, 0x80000080, 0x80808080,
  0x80008000, 0x00000000, 0x80008000, 0x00000080,
  0x80008000, 0x00008000, 0x80008000, 0x00008080,
  0x80008000, 0x00800000, 0x80008000, 0x00800080,
  0x80008000, 0x00808000, 0x80008000, 0x00808080,
  0x80008000, 0x80000000, 0x80008000, 0x80000080,
  0x80008000, 0x80008000, 0x80008000, 0x80008080,
  0x80008000, 0x80800000, 0x80008000, 0x80800080,
  0x80008000, 0x80808000, 0x80008000, 0x80808080,
  0x80008080, 0x00000000, 0x80008080, 0x00000080,
  0x80008080, 0x00008000, 0x80008080, 0x00008080,
  0x80008080, 0x00800000, 0x80008080, 0x00800080,
  0x80008080, 0x00808000, 0x80008080, 0x00808080,
  0x80008080, 0x80000000, 0x80008080, 0x80000080,
  0x80008080, 0x80008000, 0x80008080, 0x80008080,
  0x80008080, 0x80800000, 0x80008080, 0x80800080,
  0x80008080, 0x80808000, 0x80008080, 0x80808080,
  0x80800000, 0x00000000, 0x80800000, 0x00000080,
  0x80800000, 0x00008000, 0x80800000, 0x00008080,
  0x80800000, 0x00800000, 0x80800000, 0x00800080,
  0x80800000, 0x00808000, 0x80800000, 0x00808080,
  0x80800000, 0x80000000, 0x80800000, 0x80000080,
  0x80800000, 0x80008000, 0x80800000, 0x80008080,
  0x80800000, 0x80800000, 0x80800000, 0x80800080,
  0x80800000, 0x80808000, 0x80800000, 0x80808080,
  0x80800080, 0x00000000, 0x80800080, 0x00000080,
  0x80800080, 0x00008000, 0x80800080, 0x00008080,
  0x80800080, 0x00800000, 0x80800080, 0x00800080,
  0x80800080, 0x00808000, 0x80800080, 0x00808080,
  0x80800080, 0x80000000, 0x80800080, 0x80000080,
  0x80800080, 0x80008000, 0x80800080, 0x80008080,
  0x80800080, 0x80800000, 0x80800080, 0x80800080,
  0x80800080, 0x80808000, 0x80800080, 0x80808080,
  0x80808000, 0x00000000, 0x80808000, 0x00000080,
  0x80808000, 0x00008000, 0x80808000, 0x00008080,
  0x80808000, 0x00800000, 0x80808000, 0x00800080,
  0x80808000, 0x00808000, 0x80808000, 0x00808080,
  0x80808000, 0x80000000, 0x80808000, 0x80000080,
  0x80808000, 0x80008000, 0x80808000, 0x80008080,
  0x80808000, 0x80800000, 0x80808000, 0x80800080,
  0x80808000, 0x80808000, 0x80808000, 0x80808080,
  0x80808080, 0x00000000, 0x80808080, 0x00000080,
  0x80808080, 0x00008000, 0x80808080, 0x00008080,
  0x80808080, 0x00800000, 0x80808080, 0x00800080,
  0x80808080, 0x00808000, 0x80808080, 0x00808080,
  0x80808080, 0x80000000, 0x80808080, 0x80000080,
  0x80808080, 0x80008000, 0x80808080, 0x80008080,
  0x80808080, 0x80800000, 0x80808080, 0x80800080,
  0x80808080, 0x80808000, 0x80808080, 0x80808080,
};

/* *INDENT-ON* */
/***************************************************************/
