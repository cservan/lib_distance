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
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <fstream>
#include <iostream>
// #include <stdio.h>
// #include <stdlib.h>
#include <string.h>
#include <vector>
// #include "tools.h"
// #include "tercalc.h"
// #include "hashMapStringInfos.h"
// #include "hashMapStringInfos.h"
// #include "../src/hashmap.h"
// #include "../src/stringhasher.h"
// #include <boost/algorithm/string.hpp>
// #include <boost/xpressive/xpressive.hpp>
// #include "tercalc.h"
// #include "stringInfosHasher.h"
// #include "sgmlDocument.h"
// #include "multiTxtDocument.h"
// #include "xmlStructure.h"
#include "tools.h"
#include "bilingualModel.h"
#include "distance.h"
#include "monolingualModel.h"
// #include "multiEvaluation.h"



// using namespace TERCpp;
using namespace std;
// using namespace HashMapSpace;
// using namespace boost::xpressive;


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
// 	cerr<<"tercpp [-N] [-s] [-P] -r ref -h hyp [-a alter_ref] [-b beam_width] [-S trans_span_prefix] [-o out_format -n out_pefix] [-d max_shift_distance] [-M match_cost] [-D delete_cost] [-B substitute_cost] [-I insert_cost] [-T shift_cost]"<<endl;
    cerr<<"Usage : "<<endl<<"\tbidistance -ms model_source -mt model_target :\n\n\t\t -ms\t: source model\n\t\t -mt\t: target model\n --debugMode \t: print debug messages \n\t\t --debugLevel \t: print debug messages regarding the level\n\t\t --help \t: print this help message.\n "<<endl;
    exit(0);
// 	System.exit(1);

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
    if (((int)myParams.model_source.size()==0) || ((int)myParams.model_target.size()==0))
    {
        cerr << "ERROR : main : models file are not set !" << endl;
        usage();
    }
    word2vecdistance::distance l_d(myParams.model_source);
//     monolingualModel l_bm(myParams.model_source, myParams.threads, myParams.threshold);
    string s="comptes";
    string s2="véhicules";
    vector < pair < string, float > > resultats;
//     while (s.compare("EXIT") != 0)
//     {
// 	resultats = new vector< biWord>;
        
// 	cout << "Entrez le mot à rechercher:"<<endl;
// 	cin >> s ;
// 	cout << "Nous cherchons :"<< s <<endl;
// 	resultats = l_d.recherche(s);
// 	toString(resultats);
// 	s="chien";
// 	cout << "Nous cherchons :"<< s <<endl;
//         resultats = l_d.recherche(s);
// 	toString(resultats);
// 	s="directives";
// 	cout << "Nous cherchons :"<< s <<endl;
//         resultats = l_d.recherche(s);
// 	toString(resultats);
// 	s="paris";
// 	cout << "Nous cherchons :"<< s <<endl;
//         resultats = l_d.recherche(s);
	s="voitures";
	cout << "Nous cherchons :"<< s <<endl;
        resultats = l_d.recherche(s);	
	toString(resultats);
        s2="véhicules";
	cout << "Nous comparons :"<< s << " et "<< s2<<endl;
        cout<< l_d.getDistance(s.c_str(),s2.c_str()) <<endl;
        s2="camionnettes";
	cout << "Nous comparons :"<< s << " et "<< s2<<endl;
        cout<< l_d.getDistance(s.c_str(),s2.c_str()) <<endl;
        s2="utilitaires";
	cout << "Nous comparons :"<< s << " et "<< s2<<endl;
        cout<< l_d.getDistance(s.c_str(),s2.c_str()) <<endl;
        s2="automobiles";
	cout << "Nous comparons :"<< s << " et "<< s2<<endl;
        cout<< l_d.getDistance(s.c_str(),s2.c_str()) <<endl;
        s2="voitures";
	cout << "Nous comparons :"<< s << " et "<< s2<<endl;
        cout<< l_d.getDistance(s.c_str(),s2.c_str()) <<endl;
	
// 	toString(resultats);
	
// 	l_bm.oneToOneAlignment("ceci est un test !","this is a test !");
// 	cerr << "Deuxieme recherche:"<<endl;
// 	l_bm.oneToOneAlignment("reprise de la session","resumption of the session");

//	if (s.compare("EXIT") == 0)
//	{
//	    return EXIT_SUCCESS;
//	}
//	int i;
	/*for (i = 0 ; i < (int)resultats->size(); i++)
	{
	    cout << resultats->at(i).shortToString();
	  
	}*/
//     }
    return EXIT_SUCCESS;
}
