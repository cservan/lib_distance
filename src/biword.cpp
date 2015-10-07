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

#include "biword.h"

using namespace std;
using namespace Tools;
// namespace bilingualDistance
// {
biWord::biWord(string s, vector<float> v)
{
    key = Tools::hashValueBoost(s);
    token = new string(s);
    embbeddings = new vector<float>(v);
    magnitude = Tools::magnitude(embbeddings);
    cscore = 0.0;
}
biWord::biWord(string s, vector<float> v, long int id)
{
    key = id;
    token = new string(s);
    embbeddings = new vector<float>(v);
    magnitude = Tools::magnitude(embbeddings);
    cscore = 0.0;
}
biWord::biWord(string * s, vector<float> * v, long int id)
{
    key = id;
    token = s;
    embbeddings = v;
    magnitude = Tools::magnitude(embbeddings);
    cscore = 0.0;
}

// biWord::biWord(biWord b)
// {
//     key = b.getKey();
//     token = b.getToken();
//     embbeddings = b.getEmbeddings();
//     magnitude = b.getMagnitude();
//     cscore = b.getCscore();
// }

biWord::biWord()
{
    key = -1;
    token = new string("");
    embbeddings = new vector<float>();
    magnitude = -1;
    cscore = -1;
}

void biWord::copy(biWord b)
{
    key = b.getKey();
    token = b.getToken();
    embbeddings = b.getEmbeddings();
    magnitude = b.getMagnitude();
    cscore = b.getCscore();
}

float biWord::cosine(biWord* foreignBiWord)
{
    return Tools::cosine(getEmbeddings(), foreignBiWord->getEmbeddings(), getMagnitude(),foreignBiWord->getMagnitude() );
}
float biWord::cosine(vector< float >* foreignEmbeddings)
{
    return Tools::cosine(getEmbeddings(), foreignEmbeddings);
}
vector< float >* biWord::getEmbeddings()
{
    return embbeddings;
}
size_t biWord::getKey()
{
    return key;
}
float biWord::getMagnitude()
{
    return magnitude;
}
string* biWord::getToken()
{
    return token;
}
biWord::~biWord()
{
    delete(token);
    delete(embbeddings);
}
void biWord::setCscore(float f)
{
    cscore = f;
}
float biWord::getCscore()
{
    return cscore;
}
string biWord::shortToString()
{
    stringstream to_return;
    to_return << (*token) << "\t" << cscore <<endl;
    return to_return.str();
}
string biWord::toString()
{
    stringstream to_return;
    to_return << (*token) << "\t" << cscore << "\t" << key <<endl;
    return to_return.str();
}


    
  
// }