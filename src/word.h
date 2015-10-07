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

#ifndef __BILINGUAL_H__
#define __BILINGUAL_H__

#include "tools.h"
#include <string>



using namespace std;
using namespace Tools;

namespace bilingualDistance
{
    class biWord
    {
        private:
	  size_t * key;
	  string * token;
	  vector<double> * embbeddings;
        public:
      
	  biWord(string s, vector< double > v);
	  size_t * getKey();
	  string * getToken();
	  vector<double> * getEmbeddings();
	  double cosine(vector<double> * foreignEmbeddings);
	  double cosine(biWord * foreignBiWord);
    };
}


#endif
