
#ifndef __PGM_PARSER__
#define __PGM_PARSER__
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <sstream>
#include <vector>

using namespace std;


// int main()
// {

// char filt[100];
// char comment[1000] = " ";
// int R,C,bits;
// vector < vector <int> > img;
// int vals1[3];

// img  = read_pgm_image("l.pgm",filt,comment,R,C,bits);   /*read the PGM image*/
// vector< vector <int> > fxn(R+2, vector <int> (C+2, 0));
// vector< vector <int> > res(R, vector <int> (C, 0));
// vals1[0] = C;
// vals1[1] = R;
// vals1[2] = bits;

// for(int i = 0; i < R; i++)                               /*zero padding*/
// {
// for(int j = 0; j < C; j++)
// {

//     fxn[i+1][j+1] = img[i][j];

// }

// }

// for(int i = 1; i < R+1; i++)                            /*3x3 block averaging : Smoothing to remove Gaussian noise*/
// {
// for(int j = 1; j < C+1; j++)
// {
// res[i-1][j-1] =  (fxn[i][j] + fxn[i-1][j-1]+fxn[i-1][j]+fxn[i][j-1]+fxn[i+1][j+1]+fxn[i+1][j]+fxn[i][j+1]+fxn[i-1][j+1]+fxn[i+1][j-1]) / 9;
// }
// }

// write_pgm_image("result.pgm",filt,res,vals1);           /*Writing the PGM in Binary (P5) format*/

// return 1;
// }
#endif