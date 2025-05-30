#pragma once

#define COORD_SCALE ((double)1000 / 0.43)

uint32 isqrt_impl(
    uint64 const n,
    uint64 const xk)
{
  uint64 const xk1 = (xk + n / xk) / 2;
  return (xk1 >= xk) ? xk : isqrt_impl(n, xk1);
}

uint32 isqrt(uint64 const n)
{
  if (n == 0) return 0;
  if (n == 18446744073709551615ULL) return 4294967295U;
  return isqrt_impl(n, n);
}

constexpr int gSinTable[900] =
{
  0,
  1,
  3,
  5,
  6,
  8,
  10,
  12,
  13,
  15,
  17,
  19,
  20,
  22,
  24,
  26,
  27,
  29,
  31,
  33,
  34,
  36,
  38,
  40,
  41,
  43,
  45,
  47,
  48,
  50,
  52,
  54,
  55,
  57,
  59,
  61,
  62,
  64,
  66,
  68,
  69,
  71,
  73,
  74,
  76,
  78,
  80,
  81,
  83,
  85,
  87,
  88,
  90,
  92,
  94,
  95,
  97,
  99,
  101,
  102,
  104,
  106,
  107,
  109,
  111,
  113,
  114,
  116,
  118,
  120,
  121,
  123,
  125,
  127,
  128,
  130,
  132,
  133,
  135,
  137,
  139,
  140,
  142,
  144,
  146,
  147,
  149,
  151,
  152,
  154,
  156,
  158,
  159,
  161,
  163,
  165,
  166,
  168,
  170,
  171,
  173,
  175,
  177,
  178,
  180,
  182,
  183,
  185,
  187,
  189,
  190,
  192,
  194,
  195,
  197,
  199,
  201,
  202,
  204,
  206,
  207,
  209,
  211,
  213,
  214,
  216,
  218,
  219,
  221,
  223,
  224,
  226,
  228,
  230,
  231,
  233,
  235,
  236,
  238,
  240,
  241,
  243,
  245,
  246,
  248,
  250,
  252,
  253,
  255,
  257,
  258,
  260,
  262,
  263,
  265,
  267,
  268,
  270,
  272,
  273,
  275,
  277,
  278,
  280,
  282,
  284,
  285,
  287,
  289,
  290,
  292,
  294,
  295,
  297,
  299,
  300,
  302,
  304,
  305,
  307,
  309,
  310,
  312,
  313,
  315,
  317,
  318,
  320,
  322,
  323,
  325,
  327,
  328,
  330,
  332,
  333,
  335,
  337,
  338,
  340,
  342,
  343,
  345,
  346,
  348,
  350,
  351,
  353,
  355,
  356,
  358,
  359,
  361,
  363,
  364,
  366,
  368,
  369,
  371,
  372,
  374,
  376,
  377,
  379,
  381,
  382,
  384,
  385,
  387,
  389,
  390,
  392,
  393,
  395,
  397,
  398,
  400,
  401,
  403,
  405,
  406,
  408,
  409,
  411,
  413,
  414,
  416,
  417,
  419,
  421,
  422,
  424,
  425,
  427,
  428,
  430,
  432,
  433,
  435,
  436,
  438,
  439,
  441,
  443,
  444,
  446,
  447,
  449,
  450,
  452,
  453,
  455,
  457,
  458,
  460,
  461,
  463,
  464,
  466,
  467,
  469,
  471,
  472,
  474,
  475,
  477,
  478,
  480,
  481,
  483,
  484,
  486,
  487,
  489,
  490,
  492,
  493,
  495,
  496,
  498,
  500,
  501,
  503,
  504,
  506,
  507,
  509,
  510,
  512,
  513,
  515,
  516,
  518,
  519,
  521,
  522,
  523,
  525,
  526,
  528,
  529,
  531,
  532,
  534,
  535,
  537,
  538,
  540,
  541,
  543,
  544,
  546,
  547,
  549,
  550,
  551,
  553,
  554,
  556,
  557,
  559,
  560,
  562,
  563,
  564,
  566,
  567,
  569,
  570,
  572,
  573,
  575,
  576,
  577,
  579,
  580,
  582,
  583,
  584,
  586,
  587,
  589,
  590,
  592,
  593,
  594,
  596,
  597,
  599,
  600,
  601,
  603,
  604,
  605,
  607,
  608,
  610,
  611,
  612,
  614,
  615,
  617,
  618,
  619,
  621,
  622,
  623,
  625,
  626,
  627,
  629,
  630,
  632,
  633,
  634,
  636,
  637,
  638,
  640,
  641,
  642,
  644,
  645,
  646,
  648,
  649,
  650,
  652,
  653,
  654,
  656,
  657,
  658,
  660,
  661,
  662,
  663,
  665,
  666,
  667,
  669,
  670,
  671,
  673,
  674,
  675,
  676,
  678,
  679,
  680,
  681,
  683,
  684,
  685,
  687,
  688,
  689,
  690,
  692,
  693,
  694,
  695,
  697,
  698,
  699,
  700,
  702,
  703,
  704,
  705,
  707,
  708,
  709,
  710,
  712,
  713,
  714,
  715,
  716,
  718,
  719,
  720,
  721,
  722,
  724,
  725,
  726,
  727,
  728,
  730,
  731,
  732,
  733,
  734,
  736,
  737,
  738,
  739,
  740,
  741,
  743,
  744,
  745,
  746,
  747,
  748,
  750,
  751,
  752,
  753,
  754,
  755,
  756,
  758,
  759,
  760,
  761,
  762,
  763,
  764,
  766,
  767,
  768,
  769,
  770,
  771,
  772,
  773,
  774,
  776,
  777,
  778,
  779,
  780,
  781,
  782,
  783,
  784,
  785,
  786,
  788,
  789,
  790,
  791,
  792,
  793,
  794,
  795,
  796,
  797,
  798,
  799,
  800,
  801,
  802,
  803,
  804,
  805,
  806,
  807,
  809,
  810,
  811,
  812,
  813,
  814,
  815,
  816,
  817,
  818,
  819,
  820,
  821,
  822,
  823,
  824,
  825,
  826,
  827,
  828,
  829,
  830,
  830,
  831,
  832,
  833,
  834,
  835,
  836,
  837,
  838,
  839,
  840,
  841,
  842,
  843,
  844,
  845,
  846,
  847,
  848,
  848,
  849,
  850,
  851,
  852,
  853,
  854,
  855,
  856,
  857,
  858,
  858,
  859,
  860,
  861,
  862,
  863,
  864,
  865,
  866,
  866,
  867,
  868,
  869,
  870,
  871,
  872,
  872,
  873,
  874,
  875,
  876,
  877,
  877,
  878,
  879,
  880,
  881,
  882,
  882,
  883,
  884,
  885,
  886,
  887,
  887,
  888,
  889,
  890,
  891,
  891,
  892,
  893,
  894,
  894,
  895,
  896,
  897,
  898,
  898,
  899,
  900,
  901,
  901,
  902,
  903,
  904,
  904,
  905,
  906,
  907,
  907,
  908,
  909,
  909,
  910,
  911,
  912,
  912,
  913,
  914,
  914,
  915,
  916,
  917,
  917,
  918,
  919,
  919,
  920,
  921,
  921,
  922,
  923,
  923,
  924,
  925,
  925,
  926,
  927,
  927,
  928,
  929,
  929,
  930,
  931,
  931,
  932,
  932,
  933,
  934,
  934,
  935,
  936,
  936,
  937,
  937,
  938,
  939,
  939,
  940,
  940,
  941,
  942,
  942,
  943,
  943,
  944,
  944,
  945,
  946,
  946,
  947,
  947,
  948,
  948,
  949,
  949,
  950,
  951,
  951,
  952,
  952,
  953,
  953,
  954,
  954,
  955,
  955,
  956,
  956,
  957,
  957,
  958,
  958,
  959,
  959,
  960,
  960,
  961,
  961,
  962,
  962,
  963,
  963,
  964,
  964,
  965,
  965,
  965,
  966,
  966,
  967,
  967,
  968,
  968,
  969,
  969,
  969,
  970,
  970,
  971,
  971,
  971,
  972,
  972,
  973,
  973,
  973,
  974,
  974,
  975,
  975,
  975,
  976,
  976,
  977,
  977,
  977,
  978,
  978,
  978,
  979,
  979,
  979,
  980,
  980,
  980,
  981,
  981,
  981,
  982,
  982,
  982,
  983,
  983,
  983,
  984,
  984,
  984,
  985,
  985,
  985,
  985,
  986,
  986,
  986,
  987,
  987,
  987,
  987,
  988,
  988,
  988,
  989,
  989,
  989,
  989,
  990,
  990,
  990,
  990,
  990,
  991,
  991,
  991,
  991,
  992,
  992,
  992,
  992,
  992,
  993,
  993,
  993,
  993,
  993,
  994,
  994,
  994,
  994,
  994,
  995,
  995,
  995,
  995,
  995,
  995,
  996,
  996,
  996,
  996,
  996,
  996,
  996,
  997,
  997,
  997,
  997,
  997,
  997,
  997,
  997,
  998,
  998,
  998,
  998,
  998,
  998,
  998,
  998,
  998,
  998,
  998,
  999,
  999,
  999,
  999,
  999,
  999,
  999,
  999,
  999,
  999,
  999,
  999,
  999,
  999,
  999,
  999,
  999,
  999,
  999,
  999,
  999,
  999,
  999,
  999,
  999
};
