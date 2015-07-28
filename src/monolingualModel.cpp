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

#include "monolingualModel.h"
#include <iostream>
#include <fstream>
#include <boost/thread/thread.hpp>
namespace ublas = boost::numeric::ublas;
// #include <thread>
// #include <boost/lockfree/queue.hpp>

using namespace std;
using namespace Tools;

monolingualModel::monolingualModel()
{
      ms = new multimap< size_t, biWord* >();
      m_nthreads = 12;
      m_threshold = 0.4;
}
multimap< size_t, biWord* >* monolingualModel::getMS()
{
    return ms;
}
monolingualModel::~monolingualModel()
{
    delete(ms);
}
monolingualModel::monolingualModel(string FileNameMS, int nb_threads, float limit_threshold)
{
    ms = new multimap< size_t, biWord* >();
    mapS = new multimap< string, size_t >();
    m_nthreads = nb_threads;
    m_threshold = limit_threshold;
    ifstream fichierMS; 
    fichierMS.open( FileNameMS.c_str());
    string line="";
    vector<int> l_data;
    vector<string> l_data_str;
    int vocab_size_src=0;
    int vector_size=0;
    biWord * l_biWord;
    int l_cpt=0;
    m_nbest=10;
    if (! fichierMS)
    {
	cerr << "Error while opening " << FileNameMS <<endl;
	exit(1);
    }
    getline ( fichierMS, line );
    l_data=stringToVectorInt(line," ");
    if ((int)l_data.size() < 2)
    {
	cerr << "Error while extracting data: " << FileNameMS <<endl;
	exit(1);
    }
    vocab_size_src=l_data.at(0);
    vector_size=l_data.at(1);
    cerr << vocab_size_src << "\t" << vector_size << endl;
    pair<size_t, biWord*> * p;
    pair<string, size_t> * p_bis;
    while (getline ( fichierMS, line ))
    {
	l_data_str=stringToVector(line," ");
	l_biWord = new biWord(l_data_str.at(0), copyVectorFloat(l_data_str,1,vector_size + 1), l_cpt);
	p = new pair<size_t, biWord*>(l_biWord->getKey(),l_biWord);
	p_bis = new pair<string, size_t>((*l_biWord->getToken()),l_biWord->getKey());
	mapS->insert((*p_bis));
	ms->insert((*p));
	l_cpt++;
	if ((l_cpt % (vocab_size_src/100)) == 0) 
	{
	    cerr <<".";
	}
	delete(p);
	delete(p_bis);
    }
    cerr <<".OK!"<<endl;
    l_cpt=0;
//     distance = new multimap< size_t, multimap< size_t, float  >* > ();
    multimap< size_t, biWord* >::iterator l_iter_src;
    float l_score = 0.0;
    l_iter_src=ms->begin();
    l_cpt=0;
    boost::thread_group * group;
    vector<boost::thread*> g_threads;
    sparse_d_scores = new ublas::compressed_matrix<float> (vocab_size_src,vocab_size_src);
    d_scores = new vector< vector<float> >();
    vector<float> v (vocab_size_src + 1,0.0);
    for (l_cpt=0; l_cpt < m_nthreads ; l_cpt++)
    {
	d_scores->push_back(v);
	if ((l_cpt % (vocab_size_src/100)) == 0) 
	{
	    cerr <<".";
	}
    }
    int l_inc_score=0;
    cerr << ".OK" <<endl;
    boost::thread *t;
    group = new boost::thread_group();
    int cpt_threads=0;
    l_cpt=0;
    int l_inc_i,l_inc_j;
    while (l_iter_src != ms->end())
    {
	l_cpt++;
	t = new boost::thread(boost::bind(&monolingualModel::subprocess,this,(*l_iter_src).second,cpt_threads));
	cpt_threads++;
// 	t = new boost::thread(monolingualModel subprocess,(*l_iter_src).second));
// 	multimap< size_t, float  >* l_multimap = new multimap< size_t, float  >();
// 	multimap< size_t, biWord* >::iterator l_iter_tgt;
// 	float l_score=0.0;
// 	vector<float> v_scores(vocab_size_tgt+1,0.0);
// 	    t = new boost::thread(&
// 	subprocess((*l_iter_src).second);
// 	    Tools::cosine((*(l_iter_src)).second->getEmbeddings(),(*(l_iter_tgt)).second->getEmbeddings(),  (*l_iter_src).second->getMagnitude(), (*l_iter_tgt).second->getMagnitude(), d_scores->at(l_inc_score));
	group->add_thread(t);
	if (l_cpt % m_nthreads == 0)
	{
// 		cerr<< ".";
	    group->join_all();
	    for (l_inc_i=0; l_inc_i < cpt_threads ; l_inc_i ++)
	    {
// 		cerr << l_inc_i << "\t" << l_cpt-cpt_threads+l_inc_i << "\t" << cpt_threads << endl;
		for (l_inc_j=0; l_inc_j < (int)d_scores->at(l_inc_i).size() ; l_inc_j++)
		{
		    if (d_scores->at(l_inc_i).at(l_inc_j) > m_threshold)
		    {
			sparse_d_scores->insert_element(l_cpt-cpt_threads+l_inc_i,l_inc_j,d_scores->at(l_inc_i).at(l_inc_j));
		    }
		}
	    }
	    cpt_threads=0;
	    delete(group);
	    group = new boost::thread_group();
//     	    exit(0);
	}
// 	group.join_all();
// 	l_iter_tgt=mt->begin();
// 	l_inc_score=0;
	l_iter_src++;
// 	cerr <<".";
	if ((l_cpt % (vocab_size_src/100)) == 0) 
	{
	    cerr <<".";
// 	    exit(0);
	}
    }
    group->join_all();
    delete(group);
    for (l_inc_i=0; l_inc_i < cpt_threads ; l_inc_i ++)
    {
// 	cerr << l_inc_i << "\t" << l_cpt-cpt_threads+l_inc_i << "\t" << cpt_threads << endl;
	for (l_inc_j=0; l_inc_j < (int)d_scores->at(l_inc_i).size() ; l_inc_j++)
	{
	    if (d_scores->at(l_inc_i).at(l_inc_j) > m_threshold)
	    {
		sparse_d_scores->insert_element(l_cpt-cpt_threads+l_inc_i,l_inc_j,d_scores->at(l_inc_i).at(l_inc_j));
	    }
	}
    }
//     return;
//     while (l_iter_src != ms->end())
//     {
// 	l_cpt++;
// // 	boost::thread *t;
// // 	t = new boost::thread(&subprocess,l_iter_src);
// 	multimap< size_t, float  >* l_multimap = new multimap< size_t, float  >();
// 	multimap< size_t, biWord* >::iterator l_iter_tgt;
// // 	float l_score=0.0;
// // 	vector<float> v_scores(vocab_size_tgt+1,0.0);
// 	l_iter_tgt=mt->begin();
// 	while (l_iter_tgt != mt->end())
// 	{
// 	    pair<size_t, float> pt((*l_iter_tgt).first,(float)d_scores->at(l_inc_score));
// 	    l_multimap->insert(pt);
// 	    l_iter_tgt++;
// 	    l_inc_score++;
// 	}
// 	pair<size_t, multimap< size_t, float  >*> ps((*l_iter_src).first,l_multimap);
// 	distance->insert(ps);
// 	delete(l_multimap);
//       
//     }

    cerr <<".OK!"<<endl;
//     cerr << "Populating Sparse Matrix" << endl;
//     int l_inc_i, l_inc_j;
//     for (l_inc_i=0; l_inc_i < vocab_size_src +1 ; l_inc_i ++)
//     {
// 	for (l_inc_j=0; l_inc_j < (int)d_scores->at(l_inc_i).size() ; l_inc_j++)
// 	{
// 	    if (d_scores->at(l_inc_i).at(l_inc_j) > m_threshold)
// 	    {
// 		sparse_d_scores->insert_element(l_inc_i,l_inc_j,d_scores->at(l_inc_i).at(l_inc_j));
// 	    }
// 	}
// 	d_scores->at(l_inc_i).clear();
// 	if ((l_inc_i % (vocab_size_src/100)) == 0) 
// 	{
// 	    cerr <<".";
// 	}
//     }
//     cerr <<".OK!"<<endl;
    delete(d_scores);
//     cerr <<"Delete d_scores!"<<endl;
//     sleep(10);

}

void monolingualModel::subprocess(biWord* l_bi_word,int l_thread_nbr)
{
// 	vector<float> * v_scores = new vector<float> ((int)ms->size()+1,0.0);
	multimap< size_t, biWord* >::iterator l_iter_src;
// 	long long int l_inc_score=0;
	l_iter_src=ms->begin();
	float l_score = 0.0;
	while (l_iter_src != ms->end())
	{
	    Tools::cosineWeighted(l_bi_word->getEmbeddings(),(*(l_iter_src)).second->getEmbeddings(),  l_bi_word->getMagnitude(), (*l_iter_src).second->getMagnitude(),d_scores->at(l_thread_nbr).at((*l_iter_src).second->getKey()));
// 	    if (l_score > m_threshold)
// 	    {
// 		if ((*(l_iter_src)).second->getKey() >= l_bi_word->getKey())
// 		{
//     // 	    cerr << d_scores->at(l_bi_word->getKey()).at((*l_iter_tgt).second->getKey()) << endl;
// // 		  m_mutex.lock();
// 		  d_scores->at((l_bi_word->getKey())).at((*l_iter_src).second->getKey()) = l_score; 
// // 		  m_mutex.unlock();
// 		}
// 	    }
// 	    l_inc_score++;
	    l_iter_src++;
	}
}

bool mySortingFunctionMono ( const pair<float, int>& i, const pair<float, int>& j )
{
    if ( i.first > j.first ) return true;
    else return false;
//       
//     if ( j.first >= i.first ) return false;
//     return true;
// 	return j.second < i.second;
}

vector<biWord> * monolingualModel::recherche(string s)
{
	size_t src_id=-1;
	vector<biWord> * to_retrun = new vector< biWord >;
// 	to_retrun = new biWord();
	multimap< string, size_t  >::iterator mapS_iter = mapS->find(s);
	multimap< size_t , biWord* >::iterator found_iter ;
	if (mapS->find(s) == mapS->end())
	{
	    cerr << "Attention mot non trouvé : " << s << endl;
	    return NULL;
	}
	src_id=(*mapS_iter).second;
	vector< pair <float, int > > * resultats = new vector< pair <float, int > >();
	int l_inc;
	pair <float, int > p(0.0,-1);
	
// 	cerr << d_scores->size() << endl;
// 	cerr << d_scores->at(src_id).size() << endl;
	for (l_inc = 0; l_inc < (int)mapS->size(); l_inc++)
	{
	    float * l_score = sparse_d_scores->find_element(src_id,l_inc);
	    if ( l_score != NULL)
	    {
		p.first = (*l_score);
	    }
	    else
	    {
		l_score = sparse_d_scores->find_element(l_inc, src_id);
		if ( l_score != NULL)
		{
		    p.first = (*l_score);
		}
		else
		{
		    p.first = 0.0;
		}
	    }
	    p.second = l_inc;
	    if ( p.first > 0.0 )
	    {
		resultats->push_back(p);
	    }
// 	    resultats->push_back(p);
	}
	cerr << "Taille résultat " << resultats->size() <<endl;
	sort ( resultats->begin(), resultats->end() , mySortingFunctionMono );
	cerr << "Taille résultat Trié " << resultats->size() <<endl;
// 	for (l_inc = 0; l_inc < m_nbest && l_inc < (int)resultats->size(); l_inc++)
// 	{
// 	    cerr << resultats->at(l_inc).first << "\t" << resultats->at(l_inc).second << endl;
// 	}
	for (l_inc = 0; l_inc < m_nbest && l_inc < (int)resultats->size(); l_inc++)
	{
	    cerr << resultats->at(l_inc).first << "\t" << resultats->at(l_inc).second ;
	    found_iter=ms->find(resultats->at(l_inc).second);
	    cerr << "\t" << (*(*found_iter).second->getToken());
	    cerr << "\t" << (*(*found_iter).second).toString() << endl;
	}
	return to_retrun;
// 	return to_retrun;
// 	for (l_inc = 0; l_inc < m_nbest && l_inc < (int)resultats->size(); l_inc++)
// 	{
// 	    found_iter=ms->find(resultats->at(l_inc).second);
// 	    cerr << l_inc << "\t" << resultats->at(l_inc).first << "\t"<<  resultats->at(l_inc).second << endl;
// 	    string l_tok=(*(*found_iter).second->getToken());
// 	    vector<float> l_f = (*(*found_iter).second->getEmbeddings());
// 	    int l_id = (*found_iter).second->getKey();
// 	    biWord l_b;
// 	    l_b.copy((*(*found_iter).second));
// 	    biWord b((*(*found_iter).second->getToken()), (*(*found_iter).second->getEmbeddings()), (*found_iter).second->getKey());
// 	    b.setCscore(resultats->at(l_inc).first);
// 	    to_retrun->push_back(b);
// 	    cerr << b.toString() <<endl;
// 	    resultats->at(l_inc).first;
// 	    resultats->at(l_inc).second;
// 	}
	return to_retrun;
}
vector<biWord> * monolingualModel::recherche(string s, int nbest)
{
	size_t src_id=-1;
	vector<biWord> * to_retrun = new vector< biWord >;
// 	to_retrun = new biWord();
	multimap< string, size_t  >::iterator mapS_iter = mapS->find(s);
	multimap< size_t , biWord* >::iterator found_iter ;
	if (mapS->find(s) == mapS->end())
	{
	    cerr << "Attention mot non trouvé : " << s << endl;
	    return NULL;
	}
	src_id=(*mapS_iter).second;
	vector< pair <float, int > > * resultats = new vector< pair <float, int > >();
	int l_inc;
	pair <float, int > p(0.0,-1);
	
	cerr << sparse_d_scores->nnz() << endl;
// 	cerr << d_scores->at(src_id).size() << endl;
	for (l_inc = 0; l_inc < (int)mapS->size(); l_inc++)
	{
	    float * l_score = sparse_d_scores->find_element(src_id,l_inc);
	    if ( l_score != NULL)
	    {
		p.first = (*l_score);
	    }
	    else
	    {
		l_score = sparse_d_scores->find_element(l_inc, src_id);
		if ( l_score != NULL)
		{
		    p.first = (*l_score);
		}
		else
		{
		    p.first = 0.0;
		}
	    }
	    p.second = l_inc;
	    if ( p.first > 0.0 )
	    {
		resultats->push_back(p);
	    }
// 	    cerr << l_inc << "\t" << d_scores->at(src_id).at(l_inc) << endl;
	}
	for (l_inc = 0; l_inc < nbest; l_inc++)
	{
	    cerr << resultats->at(l_inc).first << "\t" << resultats->at(l_inc).second << endl;
	}
	cerr << "Taille résultat " << resultats->size() <<endl;
	sort ( resultats->begin(), resultats->end() , mySortingFunctionMono );
	cerr << "Taille résultat Trié " << resultats->size() <<endl;
	for (l_inc = 0; l_inc < nbest; l_inc++)
	{
	    cerr << resultats->at(l_inc).first << "\t" << resultats->at(l_inc).second ;
	    found_iter=ms->find(resultats->at(l_inc).second);
	    cerr << "\t" << (*found_iter).second->getKey() << "\t" << (*(*found_iter).second->getToken()) << endl;
// 	    cerr << "\t" << (*(*found_iter).second).toString() << endl;
	}
// 	return to_retrun;
// 	for (l_inc = 0; l_inc < nbest; l_inc++)
// 	{
// 	    found_iter=ms->find(resultats->at(l_inc).second);
// 	    cerr << l_inc << "\t" << resultats->at(l_inc).first << "\t"<<  resultats->at(l_inc).second << endl;
// 	    string l_tok=(*(*found_iter).second->getToken());
// 	    vector<float> l_f = (*(*found_iter).second->getEmbeddings());
// 	    int l_id = (*found_iter).second->getKey();
// 	    biWord l_b;
// 	    l_b.copy((*(*found_iter).second));
// 	    biWord b((*(*found_iter).second->getToken()), (*(*found_iter).second->getEmbeddings()), (*found_iter).second->getKey());
// 	    b.setCscore(resultats->at(l_inc).first);
// 	    to_retrun->push_back(b);
// 	    cerr << b.toString() <<endl;
// 	    resultats->at(l_inc).first;
// 	    resultats->at(l_inc).second;
// 	}
	return to_retrun;
}
float monolingualModel::crossCosine(string s, string t)
{
	multimap< string, size_t  >::iterator mapS_iter = mapS->find(s);
	multimap< string, size_t  >::iterator mapT_iter = mapS->find(t);
	size_t src_id=-1;
	size_t tgt_id=-1;
	if (mapS->find(s) == mapS->end())
	{
	    cerr << "Attention mot non trouvé : " << s << endl;
	    return 0.0;
	}
	if (mapS->find(t) == mapS->end())
	{
	    cerr << "Attention mot non trouvé : " << t << endl;
	    return 0.0;
	}
	src_id=(*mapS_iter).second;
	tgt_id=(*mapT_iter).second;
	if ( src_id > tgt_id )
	  return (*sparse_d_scores->find_element(tgt_id,src_id));
	return (*sparse_d_scores->find_element(src_id,tgt_id));
}

void monolingualModel::oneToOneAlignment(string src, string tgt)
{
	vector<string> v_src = stringToVector(src," ");
	vector<string> v_tgt = stringToVector(tgt," ");
	int i,j;
	float l_norm = 0.0;
	for (i=0; i<(int)v_src.size(); i++)
	{
		cout << v_src.at(i) <<endl;
		l_norm = 0.0 ;
		for (j=0; j<(int)v_tgt.size(); j++)
		{
		      //cout << "\t\t- " << v_tgt.at(j) << "\t" << crossCosine(v_src.at(i),v_tgt.at(j)) <<endl;
		      l_norm = l_norm + crossCosine(v_src.at(i),v_tgt.at(j)); 
		}
		for (j=0; j<(int)v_tgt.size(); j++)
                {
                      cout << "\t\t- " << v_tgt.at(j) << "\t" << crossCosine(v_src.at(i),v_tgt.at(j)) << "\t" << crossCosine(v_src.at(i),v_tgt.at(j))/l_norm<<endl;
                }
	}
}
vector< alignmentData > monolingualModel::oneToManyAlignment(string src, string tgt)
{
	vector<string> v_src = stringToVector(src," ");
	vector<string> v_tgt = stringToVector(tgt," ");
// 	vector< vector< pair< int, float > > > 
	vector< alignmentData > to_retrun;
	int i,j;
	float l_norm = 0.0;
	for (i=0; i<(int)v_src.size(); i++)
	{
		cout << v_src.at(i) <<endl;
		alignmentData l_a;
		
		l_norm = 0.0 ;
		for (j=0; j<(int)v_tgt.size(); j++)
		{
		      //cout << "\t\t- " << v_tgt.at(j) << "\t" << crossCosine(v_src.at(i),v_tgt.at(j)) <<endl;
		      l_norm = l_norm + crossCosine(v_src.at(i),v_tgt.at(j)); 
		}
		for (j=0; j<(int)v_tgt.size(); j++)
                {
                      cout << "\t\t- " << v_tgt.at(j) << "\t" << crossCosine(v_src.at(i),v_tgt.at(j)) << "\t" << crossCosine(v_src.at(i),v_tgt.at(j))/l_norm<<endl;
                }
	}
	return to_retrun;
}

