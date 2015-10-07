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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <fstream>
#include <iostream>
#include <string.h>
#include <vector>
#include "tools.h"
#include "bilingualModel.h"
#include "distance.h"
#include "monolingualModel.h"



using namespace std;
using namespace Tools;


void usage();

void readCommandLineArguments ( unsigned int argc, char *argv[] , param & p)
{
    p.debugMode=false;
    p.debugLevel=-1;
    p.caseOn=false;
    p.noPunct=false;
    p.normalize=false;
    p.tercomLike=false;
    p.sgmlInputs=false;
    p.noTxtIds=false;
    p.verbose=false;
    p.count_verbose=false;
    p.printAlignments = false;
    p.printAlignmentsTrack = false;
    p.threads = 24;
    p.threshold = 0.5;
    p.WER=false;
    p.model_source="";     // path to the resources
    p.model_target="";     // path to the configuration files
    p.outputFileExtension="";
    p.outputFileName="";
    p.matchCost=0.0;
    p.insCost=1.0;
    p.delCost=1.0;
    p.subCost=1.0;
    p.shiftCost=1.0;
    p.ids = false;
    p.ngrams = false;
    p.ngramsFixed = false;
    p.ngramsFixedOrdered = false;

    string s ( "" );
    string infos ("");
    for ( unsigned int i = 1; i < argc; i++ )
    {
	s= argv[i];
        // Command line string
        if (i < argc-1)
        {
            infos = argv[i+1];
        }

        // Configuration files
        if ( s.compare ( "-r" ) == 0 )
        {
            p.referenceFile = infos;
        }
        else if ( s.compare ( "--debugLevel" ) == 0 )
        {
            p.debugLevel = atoi(infos.c_str());
        }
        else if ( s.compare ( "-ms" ) == 0 )
        {
            p.model_source = infos;
        }
        else if ( s.compare ( "-mt" ) == 0 )
        {
            p.model_target = infos;
        }
        else if ( s.compare ( "-t" ) == 0 )
        {
            p.threads = atoi(infos.c_str());
        }
        else if ( s.compare ( "-th" ) == 0 )
        {
            p.threshold = atof(infos.c_str());
        }
        else if ( s.compare ( "--debugMode" ) == 0 )
        {
            p.debugMode = true;
        }
        else if ( s.compare ( "--ids" ) == 0 )
        {
            p.ids = true;
        }
        else if ( s.compare ( "--ngrams" ) == 0 )
        {
            p.ngrams = true;
            p.ngramsFixed = false;
            p.ngramsFixedOrdered = false;
        }
        else if ( s.compare ( "--ngramsFixed" ) == 0 )
        {
            p.ngrams = false;
            p.ngramsFixed = true;
            p.ngramsFixedOrdered = false;
        }
        else if ( s.compare ( "--ngramsFixedOrdered" ) == 0 )
        {
            p.ngrams = false;
            p.ngramsFixed = false;
            p.ngramsFixedOrdered = true;
        }
        else if ( s.compare ( "--help" ) == 0 )
        {
            usage();
        }
        else if ( s.compare ( "--" ) == 0 )
        {
	    cerr << "ERROR : tercpp: unknown option :" << s <<endl;
            usage();
        }
    }
    if (p.outputFileName.length() == 0)
    {
       p.outputFileName=p.hypothesisFile;
    }
}

void usage()
{

  cerr<<"Usage : "<<endl<<"\tdistance -ms model_source \n\n\t\t -ms\t: source model\n\t\t --help \t: print this help message.\n "<<endl;
    exit(0);
}

void toString(vector < pair < string, float > > resultats)
{
    int l_inc;
    for (l_inc = 0; l_inc < (int) resultats.size(); l_inc ++)
    {
	cout << l_inc+1 << "\t" << resultats.at(l_inc).first << "\t" << resultats.at(l_inc).second << "\t" << endl;
    }
  
}


int main ( int argc, char *argv[] )
{
    param myParams;
    readCommandLineArguments ( argc,argv, myParams);
    if (((int)myParams.model_source.size()==0))
    {
        cerr << "ERROR : main : models file are not set !" << endl;
        usage();
    }
    cerr << myParams.ngrams << endl;
    cerr << myParams.ngramsFixed << endl;
    word2vecdistance::distance l_d(myParams.model_source);
    cerr << "System launched!" <<endl << "Entrer words to be compared like this: \"word1 ||| word2\"" <<endl;
    string line;
    while (getline(cin,line))
    {
	vector<string> data = splitLine(line.c_str());
	cerr << "You ask for "<< line <<endl;
	if (data.size() == 1) 
	{
	    cout<< vectorToString(l_d.getWord(data.at(0).c_str()),"\t")<< endl;
// 	    cout << "error" << endl;
	}
	else 
	if (data.size() == 2) 
	{
	  if ( myParams.ngrams ) cout<< l_d.getSimilarityNgrams(data.at(0).c_str(),data.at(1).c_str()) <<endl;
	  if ( myParams.ngramsFixed ) cout<< l_d.getSimilarityNgramsFixed(data.at(0).c_str(),data.at(1).c_str()) <<endl;
	  if ( myParams.ngramsFixedOrdered ) cout<< l_d.getSimilarityNgramsFixedOrdered(data.at(0).c_str(),data.at(1).c_str()) <<endl;
	  if ( !myParams.ngrams && !myParams.ngramsFixed && !myParams.ngramsFixedOrdered ) cout<< l_d.getSimilarity(data.at(0).c_str(),data.at(1).c_str()) <<endl;
	}
	else if (data.size() == 3) 
	{
	  if ( myParams.ngrams ) cout<< data.at(0) << " " << l_d.getSimilarityNgrams(data.at(1).c_str(),data.at(2).c_str()) <<endl;
	  if ( myParams.ngramsFixed ) cout<< data.at(0) << " " << l_d.getSimilarityNgramsFixed(data.at(1).c_str(),data.at(2).c_str()) <<endl;
	  if ( myParams.ngramsFixedOrdered ) cout<< data.at(0) << " " << l_d.getSimilarityNgramsFixedOrdered(data.at(1).c_str(),data.at(2).c_str()) <<endl;
	  if ( !myParams.ngrams && !myParams.ngramsFixed && !myParams.ngramsFixedOrdered ) cout<< data.at(0) << " " << l_d.getSimilarity(data.at(1).c_str(),data.at(2).c_str()) <<endl;
	}
	else 
	{
	  cerr << "Input error!" <<endl;
	  cout << "0.0" <<endl;
	}
    }
    return EXIT_SUCCESS;
}
