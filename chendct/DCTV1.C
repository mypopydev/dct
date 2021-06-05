/*
	dctv1.c - fast dct by Xinjian Chen, implemented by DanShu, version 1.
	Copyright (C) 2004 Xinjian Chen and DanShu
	for help please send mail to <steade@163.net> 
	
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>

#define PI 3.14159265359

static int testvalue[64]=
{

 140,144,147,140,140,155,179,175,
 144,152,140,147,140,148,167,179,
 152,155,136,167,163,162,152,172,
 168,145,156,160,152,155,136,160,
 162,148,156,148,140,136,147,162,
 147,167,140,155,155,140,136,162,
 136,156,123,167,162,144,140,147,
 148,155,136,155,152,147,147,136

};


static int o[64] =
{
		20,40,43,42,44, 8,82,47,
		21,80,  4, 6,12,9,15,29,
		23,84, 2,30,72,11,89,70,
		22, 7,33,36,64,26,90,75,
		28,88,49,48, 0,16,91, 3,
		68,69,52,41,76,17,79,58,
		38,95,85,86,54,19,87,78,
		31,45,61,56,24,46,94,59

};

static int oo1[64]=
{
		 0, 1, 2, 3, 4, 5, 6, 7,32,33,34,35,36,37,38,39,
		16,17,18,19,20,21,22,23,40,41,42,43,44,45,46,47,
		 8, 9,10,11,12,13,14,15,48,49,50,51,52,53,54,55,
		24,25,26,27,28,29,30,31,56,57,58,59,60,61,62,63

		
};
static int oo2[64]=
{
		 0, 4, 2, 5, 1, 6, 3, 7,
		 8,12,10,13, 9,14,11,15,
		16,20,18,21,17,22,19,23,
		24,28,26,29,25,30,27,31,
		32,36,34,37,33,38,35,39,
		40,44,42,45,41,46,43,47,
		48,52,50,53,49,54,51,55,
		56,60,58,61,57,62,59,63

};

static double sub;
static double add;
static double r4,r2;

double* a;

double r(short k){
  return cos(k*PI/16.0);
}


	
void init_fdct_enc()
{
	sub=r(6)- r(2);
	add=r(6)+ r(2);
	r4 =r(4);
	r2 =r(2);

	a=malloc(sizeof(double)*96);
}

void end_fdct(){

	free(a);
}




#define VERSIONLOW

#ifdef VERSIONLOW

void fdct_enc(block)
short *block;
{

int i,k,j;
int m,n;
//a=malloc(sizeof(double)*96);
//b=malloc(sizeof(double)*64);

for(i=0;i<64;i++){//memcpy?
 a[i] = block[i];
}
/*
for(i=64;i<96;i++){
 a[i] = 0.0;
}
*/
///*
k=64,m=0,n=56;
for(i=0;i<8;i++){
	a[k++] = a[m++] + a[n++];
}
n=48;
for(i=0;i<8;i++){
	a[k++] = a[m++] + a[n++];
}
n=40;
for(i=0;i<8;i++){
	a[k++] = a[m++] + a[n++];
}
n=32;
for(i=0;i<8;i++){
	a[k++] = a[m++] + a[n++];
}

k=0,m=0,n=56;
for(i=0;i<8;i++){
	a[k++] = a[m++] - a[n++];
}
n=48;
for(i=0;i<8;i++){
	a[k++] = a[m++] - a[n++];
}
n=40;
for(i=0;i<8;i++){
	a[k++] = a[m++] - a[n++];
}
n=32;
for(i=0;i<8;i++){
	a[k++] = a[m++] - a[n++];
}
//*/
//R3

k=32;m=64;n=71;
for(i=0;i<4;i++){
	a[k++] = a[m++] + a[n--];
}
m=72;n=79;
for(i=0;i<4;i++){
	a[k++] = a[m++] + a[n--];
}
m=80;n=87;
for(i=0;i<4;i++){
	a[k++] = a[m++] + a[n--];
}
m=88;n=95;
for(i=0;i<4;i++){
	a[k++] = a[m++] + a[n--];
}
m=0; n=7;
for(i=0;i<4;i++){
	a[k++] = a[m++] + a[n--];
}
m=8; n=15;
for(i=0;i<4;i++){
	a[k++] = a[m++] + a[n--];
}
m=16;n=23;
for(i=0;i<4;i++){
	a[k++] = a[m++] + a[n--];
} 
m=24;n=31;
for(i=0;i<4;i++){
	a[k++] = a[m++] + a[n--];
}

k=0;/*m=0;*/n=7;
for(i=0;i<4;i++){
	//a[k++] = a[m++] - a[n--];
	a[k++]-=a[n--];
}
k=8;n=15;
for(i=0;i<4;i++){
	a[k++]-=a[n--];
}
k=16;n=23;
for(i=0;i<4;i++){
	a[k++]-=a[n--];
}
k=24;n=31;
for(i=0;i<4;i++){
	a[k++]-=a[n--];
}

k=64;n=71;
for(i=0;i<4;i++){
	a[k++]-=a[n--];
}
k=72;n=79;
for(i=0;i<4;i++){
	a[k++]-=a[n--];
}
k=80;n=87;
for(i=0;i<4;i++){
	a[k++]-=a[n--];
}
k=88;n=95;
for(i=0;i<4;i++){
	a[k++]-=a[n--];
}

//R3t

k=4;m=32;n=44;
for(i=0;i<4;i++){
	a[k++] = a[m++] + a[n++];
}
k=12;m=64;n=88;
for(i=0;i<4;i++){
	a[k++] = a[m++] + a[n++];
}
k=20;m=36;n=40;
for(i=0;i<4;i++){
	a[k++] = a[m++] + a[n++];
}
k=28;m=72;n=80;
for(i=0;i<4;i++){
	a[k++] = a[m++] + a[n++];
}
k=32;/*m=*/n=44;
for(i=0;i<4;i++){
	a[k++] -= a[n++];
}
/*k=36;*/n=40;
for(i=0;i<4;i++){
	a[k++] -= a[n++];
}
k=64;n=88;
for(i=0;i<4;i++){
	a[k++] -= a[n++];
}
k=72;n=80;
for(i=0;i<4;i++){
	a[k++] -= a[n++];
}
//R2

//k=80;m=4;n=7;
//for(i=0;i<2;i++)
a[80] = a[4] + a[7];
a[81] = a[5] + a[6];

a[82] = a[20] + a[23];
a[83] = a[21] + a[22];

a[84] = a[32] + a[35];
a[85] = a[33] + a[34];

a[86] = a[36] + a[39];
a[87] = a[37] + a[38];

a[88] = a[48] + a[51];
a[89] = a[49] + a[50];

a[90] = a[52] + a[55];
a[91] = a[53] + a[54];

a[92] = a[56] + a[59];
a[93] = a[57] + a[58];

a[94] = a[60] + a[63];
a[95] = a[61] + a[62];


a[4] -= a[7];
a[5] -= a[6];

a[20] -= a[23];
a[21] -= a[22];

a[32] -= a[35];
a[33] -= a[34];

a[36] -= a[39];
a[37] -= a[38];

a[48] -= a[51];
a[49] -= a[50];

a[52] -= a[55];
a[53] -= a[54];

a[56] -= a[59];
a[57] -= a[58];

a[60] -= a[63];
a[61] -= a[62];

//R2t


//--R1 begin
/*k=40;m=*/
a[40] = a[80] + a[82];
a[41] = a[81] + a[83];
a[42] = a[4 ] + a[20];
a[43] = a[5 ] + a[21];

a[44] = a[12] + a[28];
a[45] = a[13] + a[29];
a[46] = a[14] + a[30];
a[47] = a[15] + a[31];

a[4]  -= a[20];
a[5]  -= a[21];

a[12] -= a[28];
a[13] -= a[29];
a[14] -= a[30];
a[15] -= a[31];

a[80] -= a[82];
a[81] -= a[83];

//R1--end

//R1t--begin
a[20] = a[40] + a[41];
a[21] = a[80] + a[81];
a[22] = a[84] + a[85];
a[23] = a[86] + a[87];

a[28] = a[88] + a[89];
a[29] = a[90] + a[91];
a[30] = a[92] + a[93];
a[31] = a[94] + a[95];

a[40] -= a[41];
a[80] -= a[81];
a[84] -= a[85];
a[86] -= a[87];

a[88] -= a[89];
a[90] -= a[91];
a[92] -= a[93];
a[94] -= a[95];

//R1t--end

//Un-named 1 --begin
a[38] = a[28] + a[29];
a[39] = a[88] + a[90];

a[50] = a[48] + a[52];
a[51] = a[49] + a[53];

a[54] = a[0] + a[8];
a[55] = a[1] + a[9];

a[58] = a[2] + a[10];
a[59] = a[3] + a[11];

a[68] = a[29] + a[30];
a[69] = a[90] + a[92];
a[70] = a[52] + a[56];
a[71] = a[53] + a[57];

a[76] = a[8] + a[16];
a[77] = a[9] + a[17];
a[78] = a[10] + a[18];
a[79] = a[11] + a[19];

a[24] = -a[16] -a[24];
a[25] = -a[17] -a[25];
a[26] = -a[18] -a[26];
a[27] = -a[19] -a[27];

a[31] = -a[30] - a[31];
a[60] = -a[56] - a[60];
a[61] = -a[57] - a[61];
a[95] = -a[92] - a[94];//DUAL big big mistakes!!!! !!!!

//Un-name1 --end

//Un-name1t --begin
a[8] = a[45] + a[46];
a[9] = a[13] + a[14];
a[10] = a[73] + a[74];
a[11] = a[65] + a[66];

a[16] = a[1] + a[2];
a[17] = a[77] + a[78];
a[18] = a[55] + a[58];//this is normal
a[19] = a[25] + a[26];

a[82] = a[44] + a[45];
a[83] = a[12] + a[13];

a[89] = a[72] + a[73];
a[90] = a[64] + a[65];
a[91] = a[0]  + a[1];
a[92] = a[76] + a[77];
a[93] = a[54] + a[55];
a[94] = a[24] + a[25];

a[3]  = -a[2]  - a[3];
a[15] = -a[14] - a[15];
a[27] = -a[26] - a[27];
a[47] = -a[46] - a[47];
a[59] = -a[58] - a[59];
a[67] = -a[66] - a[67];
a[75] = -a[74] - a[75];
a[79] = -a[78] - a[79];


/*
bug repair intention!!!
*/
a[52]=a[70];a[53] = a[71];
a[56]=a[50];a[57] = a[51];
/*

*/


//Un-name1t--end

//Pt--begin--end

//Qt--begin--end

//R4--begin
a[6]  = a[5]  + a[4];
a[29] = a[83] + a[15];
a[41] = a[52] + a[53];//big mistake ever!!!
a[58] = a[92] + a[79];

a[7]  = a[84] + a[86];
a[26] = a[10] + a[11];
a[45] = a[39] + a[95];
a[46] = a[18] + a[19];

a[4]  = a[5]  - a[4];
a[15] = a[83] - a[15];
a[52] = a[53] - a[52];//big mistake ever!!!
a[79] = a[92] - a[79];

a[11] = a[10] - a[11];
a[19] = a[18] - a[19];
a[84] = a[86] - a[84];
a[95] = a[39] - a[95];


a[13] = a[36] - a[33];
a[34] = a[75] - a[90];
a[50] = a[56] - a[61];
a[62] = a[59] - a[94];

a[14] = a[32] + a[37];//big mistake ever!!!!
a[35] = a[89] + a[67];
a[51] = a[57] + a[60];
a[63] = a[93] + a[27];


a[25] = a[32] - a[37];
a[36] = a[36] + a[33];
a[33] = -a[36] + a[25];//this order is IMPORTANT!!same below;
a[36] += a[25];

a[30] = a[67] - a[89];
a[75] += a[90];
a[90] = -a[75] + a[30];
a[75] += a[30];

a[55] = a[60] - a[57];
a[56] += a[61];
a[61] = -a[56] + a[55];
a[56] += a[55];

a[65] = a[27] - a[93];
a[59] += a[94];
a[94] = -a[59] + a[65];
a[59] += a[65];
//R4--end

//At--begin--end

//Q2t--begin--end

//K4I4 begin---    ******** this is 4-point DCT core ******** ----------
a[8]  *= r4;
a[12] *= r4;
a[16] *= r4;
a[21] *= r4;

a[33] *= r4;
a[36] *= r4;
a[40] *= r4;
a[56] *= r4;

a[59] *= r4;
a[61] *= r4;
a[68] *= r4;
a[75] *= r4;

a[76] *= r4;
a[88] *= r4;
a[90] *= r4;
a[94] *= r4;

a[1]  = (a[43] + a[42])*r2;
a[2]  = (a[6]  + a[4]) *r2;
a[5]  = (a[23] + a[22])*r2;
a[10] = (a[7]  + a[84])*r2;

a[18] = (a[82] + a[47])*r2;
a[25] = (a[29] + a[15])*r2;
a[27] = (a[72] + a[64])*r2;
a[30] = (a[11] + a[26])*r2;

a[32] = (a[48] + a[49])*r2;
a[37] = (a[41] + a[52])*r2;
a[39] = (a[38] + a[31])*r2;
a[53] = (a[45] + a[95])*r2;

a[55] = (a[3]  + a[91])*r2;
a[57] = (a[58] + a[79])*r2;
a[65] = (a[54] + a[24])*r2;
a[66] = (a[19] + a[46])*r2;


a[6]  = a[6] *sub + a[2];
a[7]  = a[7] *sub + a[10];
a[23] = a[23]*sub + a[5];
a[26] = a[26]*sub + a[30];

a[3]  = a[3] *add - a[55];
a[4]  = a[4] *add - a[2];
a[11] = a[11]*add - a[30];
a[15] = a[15]*add - a[25];

a[29] = a[29]*sub + a[25];
a[38] = a[38]*sub + a[39];
a[41] = a[41]*sub + a[37];
a[43] = a[43]*sub + a[1];

a[19] = a[19]*add - a[66];
a[22] = a[22]*add - a[5];
a[24] = a[24]*add - a[65];
a[31] = a[31]*add - a[39];

a[45] = a[45]*sub + a[53];
a[46] = a[46]*sub + a[66];
a[49] = a[49]*sub + a[32];
a[54] = a[54]*sub + a[65];

a[42] = a[42]*add - a[1];
a[47] = a[47]*add - a[18];
a[48] = a[48]*add - a[32];
a[52] = a[52]*add - a[37];

a[58] = a[58]*sub + a[57];
a[72] = a[72]*sub + a[27];
a[82] = a[82]*sub + a[18];
a[91] = a[91]*sub + a[55];

a[64] = a[64]*add - a[27];
a[79] = a[79]*add - a[57];
a[84] = a[84]*add - a[10];
a[95] = a[95]*add - a[53];


//K4I4--end ----- that is the DCT core computation finished.-----

//Q2--begin--end

//S -- begin -- the negation may possibly be included in some other part.
//*(-1/2)

a[4]  = -((int)a[4]>>1);
a[6]  = -((int)a[6]>>1);
a[7]  = -((int)a[7]>>1);
a[11] = -((int)a[11]>>1);

a[15] = -((int)(a[15])>>1);
a[19] = -((int)(a[19])>>1);
a[26] = -((int)(a[26])>>1);
a[29] = -((int)(a[29])>>1);

a[41] = -((int)(a[41])>>1);
a[45] = -((int)(a[45])>>1);
a[46] = -((int)(a[46])>>1);//Big Mistake Ever!!!!!!!
a[52] = -((int)(a[52])>>1);

a[58] = -((int)(a[58])>>1);//Big Mistake Ever!!!!
a[79] = -((int)(a[79])>>1);
a[84] = -((int)(a[84])>>1);
a[95] = -((int)(a[95])>>1);






//*(1/2)

a[9]  = (int)(a[9])>>1;
a[13] = (int)(a[13])>>1;
a[14] = (int)(a[14])>>1;
a[17] = (int)(a[17])>>1;
a[33] = (int)(a[33])>>1;

a[34] = (int)(a[34])>>1;
a[35] = (int)(a[35])>>1;
a[36] = (int)(a[36])>>1;
a[50] = (int)(a[50])>>1;
a[51] = (int)(a[51])>>1;

a[56] = (int)(a[56])>>1;
a[59] = (int)(a[59])>>1;
a[61] = (int)(a[61])>>1;
a[62] = (int)(a[62])>>1;
a[63] = (int)(a[63])>>1;

a[69] = (int)(a[69])>>1;
a[75] = (int)(a[75])>>1;
a[80] = (int)(a[80])>>1;
a[90] = (int)(a[90])>>1;
a[94] = (int)(a[94])>>1;


//S --end


//A--begin--end

//Un-named 2 (or logically,3)--begin
a[2]  = a[14] + a[36];
a[85] = a[51] + a[56];
a[87] = a[63] + a[59];
a[89] = a[35] + a[75];

a[30] = a[13] + a[33];
a[70] = a[34] + a[90];
a[78] = a[62] + a[94];
a[86] = a[50] + a[61];

a[36] = a[14] - a[36];
a[56] = a[51] - a[56];
a[59] = a[63] - a[59];
a[75] = a[35] - a[75];

a[33] -= a[13];
a[61] -= a[50];
a[90] -= a[34];
a[94] -= a[62];

//Un-named 2 --end

//Q--begin--end

//P--begin--end

//Un-named 3(,or logically,4)--begin
a[39] = a[28] + a[68];//t1
a[27] = a[88] + a[69];//t2
a[37] = a[49] + a[52];//...
a[35] = a[48] + a[41];
a[34] = a[0]  + a[76];
a[32] = a[16] + a[17];
a[55] = a[91] + a[79];
a[73] = a[3]  + a[58];

a[1]  = a[28] - a[68];
a[74] = a[88] - a[69];
a[93] = a[49] - a[52];
a[92] = a[48] - a[41];
a[77] = a[0]  - a[76];
a[5]  = a[16] - a[17];
a[83] = a[91] - a[79];
a[81] = a[3]  - a[58];

a[28] = a[39] - a[31];
a[88] = a[27] - a[45];
a[49] = a[37] - a[61];
a[48] = a[35] - a[56];
a[0]  = a[34] - a[24];
a[16] = a[32] - a[46];
a[91] = a[55] - a[94];
a[3]  = a[73] - a[59];

a[31] += a[39];
a[45] += a[27];
a[61] += a[37];
a[56] += a[35];
a[24] += a[34];
a[46] += a[32];
a[94] += a[55];
a[59] += a[73];


a[68] = a[1]  + a[38];
a[69] = a[74] + a[95];
a[52] = a[93] + a[85];
a[41] = a[92] + a[86];
a[76] = a[77] + a[54];
a[17] = a[5]  + a[19];
a[79] = a[83] + a[87];
a[58] = a[81] + a[78];

a[38] = a[1]  - a[38];
a[95] = a[74] - a[95];
a[85] = a[93] - a[85];
a[86] = a[92] - a[86];
a[54] = a[77] - a[54];
a[19] = a[5]  - a[19];
a[87] = a[83] - a[87];
a[78] = a[81] - a[78];

//Un-named 3 --end

//Un-named 3t --begin
a[39] = a[44] + a[8];//t1
a[27] = a[12] + a[9];//t2
a[37] = a[72] + a[11];//t3
a[35] = a[64] + a[26];//...
a[34] = a[0] + a[16];
a[32] = a[76] + a[17];
a[55] = a[54] + a[19];
a[73] = a[24] + a[46];

a[1]  = a[44] - a[8];//t9
a[74] = a[12] - a[9];//t10
a[93] = a[72] - a[11];//...
a[92] = a[64] - a[26];
a[77] = a[0]  - a[16];
a[5]  = a[76] - a[17];
a[83] = a[54] - a[19];
a[81] = a[24] - a[46];

a[44] = a[39] - a[47];
a[12] = a[27] - a[29];
a[72] = a[37] - a[70];
a[64] = a[35] - a[75];
a[0]  = a[34] - a[3];
a[76] = a[32] - a[58];
a[54] = a[55] - a[78];
a[24] = a[73] - a[59];

a[47] = a[39] + a[47];//copied here ,you could write as "+=" like.
a[29] = a[27] + a[29];
a[70] = a[37] + a[70];
a[75] = a[35] + a[75];
a[3]  = a[34] + a[3];
a[58] = a[32] + a[58];
a[78] = a[55] + a[78];
a[59] = a[73] + a[59];

a[8]  = a[1]  + a[82];
a[9]  = a[74] + a[15];
a[11] = a[93] + a[89];
a[26] = a[92] + a[90];
a[16] = a[77] + a[91];
a[17] = a[5]  + a[79];
a[19] = a[83] + a[87];
a[46] = a[81] + a[94];

a[82] = a[1]  - a[82];
a[15] = a[74] - a[15];
a[89] = a[93] - a[89];
a[90] = a[92] - a[90];
a[91] = a[77] - a[91];
a[79] = a[5]  - a[79];
a[87] = a[83] - a[87];
a[94] = a[81] - a[94];

//Un-named 3t --end

//for(i=0;i<64;i++)
//	b[i] = a[o[i]];



//******************************* 

printf("the result without quantization part..\n");
for(i=0;i<64;i++)
	block[i]=(int)floor(a[o[i]]+0.40);//(int)x[i];//(int)floor(s+0.499999)

	for (i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			printf("%6d ",block[8*i+j]);
		}
		printf("\n");
	}
		printf("\n");
}

#endif  //earlier version






void main(){

	int		i,j,m,x,y;
	double	CM[8],qq[64],C[8],tt;
	int		qcoeff[64],t[64];
	short	block[64];


	for(i = 1; i < 8 ; i++){//DS: for compare use below
		C[i] = 1.0;
	}
	C[0] = 1.0/sqrt(2.0);

	//the CM is M matrix plus the constant "factor" factor omitted in CXJ's paper.(that stands for the above 'C' ?)
	CM[0]=0.50/sqrt(2.0);	CM[1]=CM[2]=CM[3]=0.50;	
	CM[4]=0.250/r(1);		CM[5]=0.250/r(3);
	CM[6]=0.250/r(5);		CM[7]=0.250/r(7);

	for(i = 0; i < 8 ; i++){
		m=i<<3;
		for(j =0; j <8; j++)
			qq[m+j] = CM[i] * CM[j] ;
	}


	for(i = 0; i < 64 ; i++)
		block[i] = testvalue[i];


	
	init_fdct_enc();
#ifdef VERSIONLOW
	fdct_enc(block);
	printf("first version used.\n");
#else
	fdct_enc2(block); 
	printf("latest version used.\n");
#endif
	end_fdct();
	
#define QUANT
//#undef QUANT

	
	for (i = 0; i < 64; i++)
		qcoeff[i] = block[i] ;


#ifdef QUANT
	//below be the quantization part
	qcoeff[0] = (int) ((double)block[0] * qq[0]);//in MPEG-4,the DC coefficient is dealt separately.
	for (i = 1; i < 64; i++) qcoeff[i] = (int) ((double)block[i] * qq[i]);

	for (i = 0; i < 64; i++) t[i] = qcoeff[oo1[i]];
	for (i = 0; i < 64; i++) qcoeff[i] = t[oo2[i]];
	printf("the result complete..\n");
#else
	printf("still the result without quantization part..\n");
#endif

	for (i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			printf("%6d ",qcoeff[8*i+j]);
		}
		printf("\n");
	}
		printf("\n");


#define STANDARDRESULT
//#undef STANDARDRESULT
#ifdef STANDARDRESULT


	printf("the standard formula result..\n");
	for (i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			tt = 0;
			for (x = 0; x < 8; x++){
				for(y = 0; y < 8; y++){

					tt += (double)testvalue[8*x+y]								\
								*cos( (double)((2*x+1)*i)*PI/(double)(2*8) )	\
								*cos( (double)((2*y+1)*j)*PI/(double)(2*8) );

				}
			}

			t[8*i+j] = (int)(tt*C[i]*C[j]/4.0);

		}

	}

	for (i = 0; i < 8; i++){
		for(j = 0; j < 8; j++){
			printf("%6d ",t[8*i+j]);
		}
		printf("\n");
	}
		printf("\n");
#endif //compare


}











