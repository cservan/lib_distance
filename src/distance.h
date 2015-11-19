/*********************************
 * lib-distance: an open-source library to use the word2vec models.
 *
 * Copyright 2015, Christophe Servan, GETALP-LIG, University of Grenoble, France
 * Contact: christophe.servan@gmail.com
 *
 * The library lib-distance is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by 
 * the Free Software Foundation, either version 2.1 of the licence, or
 * (at your option) any later version.
 *
 * This program and library are distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * **********************************/
#ifndef __WORD2VECDISTANCE_H__
#define __WORD2VECDISTANCE_H__

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>

const long long max_size = 2000;         // max length of strings
const long long N = 40;                  // number of closest words that will be shown
const long long max_w = 50;              // max length of vocabulary entries
using namespace std;
const int vocab_hash_size = 30000000;

namespace word2vecdistance
{
    vector< string > splitNgrams(const char *line);
    vector< string > splitLine(const char *ngram);
  
class distance
{
    private:
      FILE *f;
      char *bestw[N];
      char file_name[max_size], st[100][max_size];
      float bestd[N];
      long long words, size;
//       , a, b, c, d, cn, bi[100];
      char ch;
      float *M;
      char *vocab;
      int *vocab_hash;
      float lengen;
    public:
      distance(string filename);
      vector < pair < string, float > > recherche(string s);
      float getSimilarity(string s1,string s2);
      float getSimilarity(char * s1,char * s2);
      float getSimilarity(const char * s1,const char * s2);
      float getSimilarityNgrams(const char * ng1,const char * ng2);
      float getSimilarityNgrams(char * ng1,char * ng2);
      float getSimilarityNgramsFixed(const char * ng1,const char * ng2);
      float getSimilarityNgramsFixed(char * ng1,char * ng2);
      float getSimilarityNgramsFixedOrdered(const char * ng1,const char * ng2);
      float getSimilarityNgramsFixedOrdered(char * ng1,char * ng2);
      float getClosest(string s1,vector <string> vs);
      float getClosest(string s1);
      float getDistance(string s1,string s2);
      float getDistance(char * s1,char * s2);
      float getDistance(const char * s1,const char * s2);
      float getDistanceNgrams(const char * ng1,const char * ng2);
      float getDistanceNgrams(char * ng1,char * ng2);
      float getDistanceNgramsFixed(const char * ng1,const char * ng2);
      float getDistanceNgramsFixed(char * ng1,char * ng2);
      float getDistanceNgramsFixedOrdered(const char * ng1,const char * ng2);
      float getDistanceNgramsFixedOrdered(char * ng1,char * ng2);
      bool strcompare(char * c1, char * c2);
      int getWordHash(char *word);
      vector<float> getWord(char *word);
      vector<float> getWord(const char *word);
      vector<float> getWord(string word);
      int searchVocab(char *word);
      void addWordToHash(char *word, int l_pos);
      void fillHash();
};
}      
#endif

