/*********************************
 * tercpp: an open-source Translation Edit Rate (TER) scorer tool for Machine Translation.
 *
 * Copyright 2010-2013, Christophe Servan, LIUM, University of Le Mans, France
 * Copyright 2015, Christophe Servan, GETALP-LIG, University of Grenoble, France
 * Contact: christophe.servan@gmail.com
 *
 * The tercpp tool and library are free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by 
 * the Free Software Foundation, either version 3 of the licence, or
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
#include "biword.h"
#include "alignmentData.h"



using namespace std;
using namespace Tools;

class bilingualModel
{
    private:
      multimap< size_t, biWord*  > * ms;
      multimap< size_t, biWord*  > * mt;
      multimap< string, size_t  > * mapS;
      multimap< string, size_t  > * mapT;
//       multimap< size_t, multimap< size_t, double  >* > * distance;
      int nthreads;
      vector< vector<float> > * d_scores;
      int nbest;
    public:
      bilingualModel();
      bilingualModel(string FileNameMS, string FileNameMT);
      ~bilingualModel();
      multimap< size_t, biWord*  > * getMS();
      multimap< size_t, biWord*  > * getMT();
      void subprocess(biWord* l_bi_word);
      vector<biWord> * recherche(string s);
      float crossCosine(string s, string t);
      void oneToOneAlignment(string src, string tgt);
      vector< alignmentData > oneToManyAlignment(string src, string tgt);

};


#endif
