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

#ifndef __BILINGTOOLS_H__
#define __BILINGTOOLS_H__


#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <boost/xpressive/xpressive.hpp>
#include <boost/functional/hash.hpp>
#include <assert.h>

using namespace std;

namespace Tools
{
    typedef vector<double> vecDouble;
    typedef vector<char> vecChar;
    typedef vector<int> vecInt;
    typedef vector<float> vecFloat;
    typedef vector<size_t> vecSize_t;
    typedef vector<string> vecString;
    typedef vector<string> alignmentElement;
    typedef vector<alignmentElement> WERalignment;


struct param
{
    bool debugMode;
    string referenceFile;     // path to the resources
    string hypothesisFile;     // path to the configuration files
    string outputFileExtension;
    string outputFileName;
    string model_target;
    string model_source;
    bool noPunct;
    bool caseOn;
    bool normalize;
    bool tercomLike;
    bool sgmlInputs;
    bool verbose;
    bool count_verbose;
    bool noTxtIds;
    bool printAlignments;
    bool printAlignmentsTrack;
    bool WER;
    int debugLevel;
    float matchCost;
    float delCost;
    float insCost;
    float subCost;
    float shiftCost;
    int threads;
    float threshold;
    bool ids;
    bool ngrams;
    bool ngramsFixed;
    bool ngramsFixedOrdered;
    
};
// param = { false, "","","","" };

// class tools{
// private:
// public:

    string vectorToString ( vector<string> vec );
    string vectorToString ( vector<char> vec );
    string vectorToString ( vector<int> vec );
    string vectorToString ( vector<float> vec );
    string vectorToString ( vector<string> vec, string s );
    string vectorToString ( vector<char> vec, string s );
    string vectorToString ( vector< int >& vec, string s );
    string vectorToString ( vector<float> vec, string s );
    string vectorToString ( vector<bool> vec, string s );
    string vectorToString ( char* vec, string s, int taille );
    string vectorToString ( int* vec, string s , int taille );
    string vectorToString ( bool* vec, string s , int taille );
    string vectorToString ( vector< char >& vec, string s, int taille );
    string vectorToString ( vector<char>* vec, string s, int taille );
    string vectorToString ( vector< int >* vec, string s, int taillele );
    string vectorToString ( vector< bool >* vec, string s, int taille );
    vector<string> subVector ( vector< string >& vec, int start, int end );
    vector<int> subVector ( vector< int >& vec, int start, int end );
    vector<float> subVector ( vector< float >& vec, int start, int end );
    vector<string> copyVector ( vector< string >& vec );
    vector<string> copyVector ( vector<string> v , int start, int end);
    vector< double > copyVectorDouble(vector< string > v, int start, int end);
    vector< float > copyVectorFloat(vector< string > v, int start, int end);
    vector<int> copyVector ( vector< int >& vec );
    vector<float> copyVector ( vector< float >& vec );
    vector<string> stringToVector ( string& s, string tok );
    vector<string> stringToVector ( char s, string tok );
    vector<string> stringToVector ( int s, string tok );
    vector<int> stringToVectorInt ( string& s, string tok );
    vector<double> vectorStringToVectorDouble (vector<string> v);
    vector<float> vectorStringToVectorFloat (vector<string> v);
    vector<float> stringToVectorFloat ( string& s, string tok );
    string lowerCase(string& str);
    string removePunct(string& str);
    string tokenizePunct(string& str);
    string removePunctTercom(string& str);
    string normalizeStd(string& str);
    string printParams(Tools::param& p);
    string join ( string& delim, vector< string >& arr );
    double dotProduct(vector<double> * v1 , vector< double> * v2);
    double dotProduct(vector<double> * v1 , vector< double> * v2, double m1, double m2);
    double cosine(vector<double> * v1 , vector< double> * v2);
    double cosine(vector<double> * v1 , vector< double> * v2);
    double cosine(vector<double> * v1 , vector< double> * v2, double m1, double m2);
    void cosine(vector<double> * v1 , vector< double> * v2, double m1, double m2, float & result);
    void cosineWeighted(vector<double> * v1 , vector< double> * v2, double m1, double m2, float & result);

    float dotProduct(vector<float> * v1 , vector< float> * v2);
    float dotProduct(vector<float> * v1 , vector<float> * v2, float m1, float m2);
    float cosine(vector<float> * v1 , vector< float> * v2);
    float cosine(vector<float> * v1 , vector< float> * v2);
    float cosine(vector<float> * v1 , vector< float> * v2, float m1, float m2);
    void cosine(vector<float> * v1 , vector< float> * v2, float m1, float m2, float & result);
    void cosineWeighted(vector<float> * v1 , vector<float> * v2, float m1, float m2, float & result);
    float cosineWeighted(vector<float> * v1 , vector<float> * v2, float m1, float m2);

    double magnitude(vector<double> * v);
    float magnitude(vector<float> * v);
// };
    param copyParam(Tools::param& p);    
    size_t hashValueBoost(string s);
    vector< string > splitNgrams(const char *line);
    vector< string > splitLine(const char *ngram);
    string floatToHex( float f );

     
}
#endif
