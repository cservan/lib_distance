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
#include "distance.h"
#include "tools.h"
using namespace std;
namespace word2vecdistance
{
    vector< string > splitLine(const char *line)
    {
      vector< string > item;
      int start=0;
      int i=0;
//       char st[max_size];
      for(; line[i] != '\0'; i++) {
	if (line[i] == ' ' &&
	    line[i+1] == '|' &&
	    line[i+2] == '|' &&
	    line[i+3] == '|' &&
	    line[i+4] == ' ') {
	  if (start > i) start = i; // empty item
	  item.push_back( string( line+start, i-start ).c_str() );
// 	  item.push_back(st);
	  start = i+5;
	  i += 3;
	}
      }
      item.push_back( string( line+start, i-start ).c_str() );
//       item.push_back(st);
      return item;
    }


    vector< string > splitNgrams(const char *ngram)
    {
      vector< string > item;
      int start=0;
      int i=0;
//       char st[max_size];
      for(; ngram[i] != '\0'; i++) {
	if (ngram[i] == ' ' ){
	  if (start > i) start = i; // empty item
	  item.push_back( string( ngram+start, i-start ).c_str() );
// 	  strcpy(st,string( ngram+start, i-start ).c_str());
// 	  item.push_back(st);
	  start = i+1;
	  i = i+1;
	}
      }
      item.push_back( string( ngram+start, i-start ).c_str() );
//       strcpy(st,string( ngram+start, i-start ).c_str());
//       item.push_back(st);
      return item;
    }

  distance::distance(string filename)
  {
    float len;
    int a, b;
    strcpy(file_name, filename.c_str());
    f = fopen(file_name, "rb");
    if (f == NULL) {
      printf("Input file not found\n");
      exit(-1);
    }
    fscanf(f, "%lld", &words);
    fscanf(f, "%lld", &size);
    vocab = (char *)malloc((long long)words * max_w * sizeof(char));
    for (a = 0; a < N; a++) bestw[a] = (char *)malloc(max_size * sizeof(char));
    M = (float *)malloc((long long)words * (long long)size * sizeof(float));
    if (M == NULL) {
      printf("Cannot allocate memory: %lld MB    %lld  %lld\n", (long long)words * size * sizeof(float) / 1048576, words, size);
      exit(-1);
    }
    printf("Allocation of memory: %lld MB    %lld  %lld\n", (long long)words * size * sizeof(float) / 1048576, words, size);
    for (b = 0; b < words; b++) {
      a = 0;
      while (1) {
	vocab[b * max_w + a] = fgetc(f);
	if (feof(f) || (vocab[b * max_w + a] == ' ')) break;
	if ((a < max_w) && (vocab[b * max_w + a] != '\n')) a++;
      }
      vocab[b * max_w + a] = 0;
      for (a = 0; a < size; a++) fread(&M[a + b * size], sizeof(float), 1, f);
      len = 0;
      for (a = 0; a < size; a++) len += M[a + b * size] * M[a + b * size];
      len = sqrt(len);
//       if (strcmp(vocab[b * max_w]))
// 	cout << &vocab[b * max_w] << b <<endl;
//       for (a = 0; a < size; a++) 
//       {
// 	cout << M[a + b * size] << "\t" ; 
//       }
//       cout << endl; 
//       for (a = 0; a < size; a++) 
//       {
// 	cout <<  Tools::floatToHex(M[a + b * size]) << "\t" ; 
//       }
//       cout << endl; 
//       cout << len << endl; 

      for (a = 0; a < size; a++) M[a + b * size] /= len;
    }
    fclose(f);
    fillHash();
  }


  vector< pair< string, float > > distance::recherche(string s)
  {
    vector< pair< string, float > > to_return;
    float vec[max_size];
    float len;
    float dist;
    int a, b, c, d, cn, bi[10];
    for (a = 0; a < N; a++) bestd[a] = 0;
    for (a = 0; a < N; a++) bestw[a][0] = 0;
//     printf("Enter word or sentence (EXIT to break): ");
    a = 0;
//     while (1) {
//       st1[a] = fgetc(stdin);
//       if ((st1[a] == '\n') || (a >= max_size - 1)) {
//         st1[a] = 0;
//         break;
//       }
//       a++;
//     }
    char st1[max_size];
    strcpy(st1, s.c_str());
//     st1 = s.c_str();
//     if (!strcmp(st1, "EXIT")) break;
    cn = 0;
    b = 0;
    c = 0;
    while (1) {
      st[cn][b] = st1[c];
      b++;
      c++;
      st[cn][b] = 0;
      if (st1[c] == 0) break;
      if (st1[c] == ' ') {
        cn++;
        b = 0;
        c++;
      }
    }
    cn++;
    for (a = 0; a < cn; a++) {
      for (b = 0; b < words; b++) if (!strcmp(&vocab[b * max_w], st[a])) break;
      if (b == words) b = -1;
      bi[a] = b;
//       printf("\nWord: %s  Position in vocabulary: %lld\n", st[a], bi[a]);
      if (b == -1) {
	printf("%s: Out of dictionary word!\n",st[a]);
        return to_return;
      }
    }
    if (b == -1) return to_return;
//     printf("\n                                              Word       Cosine distance\n------------------------------------------------------------------------\n");
    for (a = 0; a < size; a++) vec[a] = 0;
    for (b = 0; b < cn; b++) {
      if (bi[b] == -1) continue;
      for (a = 0; a < size; a++) vec[a] += M[a + bi[b] * size];
    }
    len = 0;
    for (a = 0; a < size; a++) len += vec[a] * vec[a];
    len = sqrt(len);
    for (a = 0; a < size; a++) vec[a] /= len;
    for (a = 0; a < N; a++) bestd[a] = -1;
    for (a = 0; a < N; a++) bestw[a][0] = 0;
    for (c = 0; c < words; c++) {
      a = 0;
      for (b = 0; b < cn; b++) if (bi[b] == c) a = 1;
      if (a == 1) continue;
      dist = 0;
      for (a = 0; a < size; a++) dist += vec[a] * M[a + c * size];
      for (a = 0; a < N; a++) {
        if (dist > bestd[a]) {
          for (d = N - 1; d > a; d--) {
            bestd[d] = bestd[d - 1];
            strcpy(bestw[d], bestw[d - 1]);
          }
          bestd[a] = dist;
          strcpy(bestw[a], &vocab[c * max_w]);
          break;
        }
      }
    }
    
//       for (a = 0; a < N && a < 10 ; a++) 
// 	printf("%50s\t\t%f\n", bestw[a], bestd[a]);
    for (a = 0; a < N; a++) 
    {
      pair<string,float> l_p( string(bestw[a]), bestd[a]);
//       printf("%50s\t\t%f\n", bestw[a], bestd[a]);
      to_return.push_back(l_p);
    }
    return to_return;
  }
/*  
  float distance::getSimilarity(string s1, string s2)
  {
    float vec1[max_size];
    float vec2[max_size];
    float len;
    float dist;
    int a, b, cn, bi[10];
  //     vector< pair< string, float > > to_return;
      for (a = 0; a < N; a++) bestd[a] = 0;
      for (a = 0; a < N; a++) bestw[a][0] = 0;
//       printf("Enter word or sentence (EXIT to break): ");
      a = 0;
      char st1[max_size];
      char st2[max_size];
      strcpy(st1, s1.c_str());
      strcpy(st2, s2.c_str());
      cn = 0;
      b = 0;
      c = 0;
      int pos1, pos2;
      // supression des espaces 
      while (1) {
	st[cn][b] = st1[c];
	b++;
	c++;
	st[cn][b] = 0;
	if (st1[c] == 0) break;
	if (st1[c] == ' ') {
	  cn++;
	  b = 0;
	  c++;
	}
      }
      cn++;
      // supression des espaces 
      for (a = 0; a < cn; a++) {
	for (b = 0; b < words; b++) if (!strcmp(&vocab[b * max_w], st[a])) break;
	if (b == words) b = -1;
	bi[a] = b;
// 	printf("\nWord: %s  Position in vocabulary: %lld\n", st[a], bi[a]);
	pos1=bi[a];
	if (b == -1) {
	  printf("%s: Out of dictionary word!\n",st[a]);
	  return 0.0;
	}
      }
      cn = 0;
      b = 0;
      c = 0;
      // supression des espaces 
      while (1) {
	st[cn][b] = st2[c];
	b++;
	c++;
	st[cn][b] = 0;
	if (st2[c] == 0) break;
	if (st2[c] == ' ') {
	  cn++;
	  b = 0;
	  c++;
	}
      }
      cn++;
      for (a = 0; a < cn; a++) {
//       cerr << a << " " << cn << endl;
      // Verification de la présence dans le vocab
	for (b = 0; b < words; b++) if (!strcmp(&vocab[b * max_w], st[a])) break;
	if (b == words) b = -1;
	bi[a] = b;
	pos2=bi[a];
// 	printf("\nWord: %s  Position in vocabulary: %lld\n", st[a], bi[a]);
	if (b == -1) {
	  printf("%s: Out of dictionary word!\n",st[a]);
	  return 0.0;
	}
      }
      
      if (b == -1) return 0.0;
  //     printf("\n                                              Word       Cosine distance\n------------------------------------------------------------------------\n");
      for (a = 0; a < size; a++) vec1[a] = 0;
      for (b = 0; b < cn; b++) {
	if (pos1 == -1) continue;
	for (a = 0; a < size; a++) vec1[a] += M[a + pos1 * size];
      }
      len = 0;
      for (a = 0; a < size; a++) len += vec1[a] * vec1[a];
      len = sqrt(len);
      for (a = 0; a < size; a++) vec1[a] /= len;

      for (a = 0; a < size; a++) vec2[a] = 0;
      for (b = 0; b < cn; b++) {
	if (pos2 == -1) continue;
	for (a = 0; a < size; a++) vec2[a] += M[a + pos2 * size];
      }
      len = 0;
      for (a = 0; a < size; a++) len += vec2[a] * vec2[a];
      len = sqrt(len);
      for (a = 0; a < size; a++) vec2[a] /= len;
      dist = 0;
      for (a = 0; a < size; a++) dist += vec1[a] * vec2[a];
      return dist;

//       for (a = 0; a < N; a++) bestd[a] = -1;
//       for (a = 0; a < N; a++) bestw[a][0] = 0;
//       for (c = 0; c < words; c++) {
// 	a = 0;
// 	for (b = 0; b < cn; b++) if (bi[b] == c) a = 1;
// 	if (a == 1) continue;
// 	dist = 0;
// 	for (a = 0; a < size; a++) dist += vec[a] * M[a + c * size];
// 	for (a = 0; a < N; a++) {
// 	  if (dist > bestd[a]) {
// 	    for (d = N - 1; d > a; d--) {
// 	      bestd[d] = bestd[d - 1];
// 	      strcpy(bestw[d], bestw[d - 1]);
// 	    }
// 	    bestd[a] = dist;
// 	    
// 	    strcpy(bestw[a], &vocab[c * max_w]);
// 	    break;
// 	  }
// 	}
//       }
//       for (a = 0; a < N && a < 2 ; a++) 
//       {
// 	pair<string,float> l_p( string(bestw[a]), bestd[a]);
// 	printf("%50s\t\t%f\n", bestw[a], bestd[a]);
//       }
//       return 1.0;
  }
  */
    float distance::getSimilarity(char * st1, char * st2)
    {
//       float vec1[max_size];
//       float vec2[max_size];
//       float len1=0;
//       float len2=0;
//       char st1[max_w];
//       char st2[max_w];
//       strcpy(st1, s1v.c_str());
//       strcpy(st2, s2.c_str());
//       float len;
      float dist;
      int a;
      cerr << "Words"<< endl;
      int pos1 = -1; 
      int pos2 = -1;
//       b = 0;
      pos1 = searchVocab(st1);
      if (pos1 == -1) 
      {
	return 0.0;
      }
      pos2 = searchVocab(st2);
      if (pos2 == -1) 
      {
	return 0.0;
      }
      dist = 0;
      for (a = 0; a < size; a++) 
      {
	  dist += M[a + pos1 * size] * M[a + pos2 * size] ;
      }
      return dist;
  }
  
    vector<float> distance::getWord(char *word)
    {
//       float vec1[max_size];
//       float vec2[max_size];
//       float len1=0;
//       float len2=0;
//       char st1[max_w];
//       char st2[max_w];
//       strcpy(st1, s1v.c_str());
//       strcpy(st2, s2.c_str());
//       float len;
      vector<float> to_return(size,0.0);
      float dist;
      int a;
//       cerr << "Words"<< endl;
      int pos1 = -1; 
      int pos2 = -1;
//       b = 0;
      pos1 = searchVocab(word);
      if (pos1 == -1) 
      {
	to_return;
      }
      for (a = 0; a < size; a++) 
      {
	  to_return.at(a)=M[a + pos1 * size];
      }
      cout << "Position\t"<< pos1 << endl;
      return to_return;
  }
    float distance::getSimilarityNgrams(char * ng1, char * ng2)
  {
//       float len;
      float dist;
      int a;
      float vec1[size];
      float vec2[size];
      float len1=0;
      float len2=0;
      char st1[max_size];
      char st2[max_size];
      int size1 = 0;
      int size2 = 0;
      cerr << "Ngram"<< endl;
//       cerr << ng1 << "\t"<< ng2 << endl;
      vector<string> vs1 = splitNgrams(ng1);
//       cerr << Tools::vectorToString(vs1," ", vs1.size());
      vector<string> vs2 = splitNgrams(ng2);
//       cerr << vs1.at(0) << endl;
//       cerr << vs2.at(0) << endl;
//       char st1[max_w];
//       char st2[max_w];
//       strcpy(st1, s1.c_str());
//       strcpy(st2, s2.c_str());
      int i;
      int pos1 = -1; 
      int pos2 = -1;
//       b = 0;
      for (a = 0; a < size; a++) 
      {
	  vec1[a]=0.0;
	  vec2[a]=0.0;
      }
      bool trouve = false;
      for (i=0 ; i < (int)vs1.size(); i++)
      {
// 	  cerr << vs1.at(i) << endl;
	  strcpy(st1,vs1.at(i).c_str());
	  pos1 = searchVocab(st1);
	  if (pos1 != -1) 
	  {
	      trouve = true;
	      size1++;
// 	      cerr << pos1 <<endl;
	      for (a = 0; a < size; a++) 
	      {
		  vec1[a] += M[a + pos1 * size];
	      }
// 	      cerr << endl;
	  }
	  else
	  {
	      for (a = 0; a < size; a++) 
	      {
		  vec1[a] += 1;
// 		  cerr << vec2[a] << " ";
	      }
// 	      cerr << endl;
	  }
// 	return 0.0;
      }
      if (!trouve) return 0.0;
      trouve = false;
      for (i=0 ; i < (int)vs2.size(); i++)
      {
// 	  cerr << vs2.at(i) << endl;
	  strcpy(st2,vs2.at(i).c_str());
	  pos2 = searchVocab(st2);
	  if (pos2 != -1) 
	  {
// 	      cerr << pos2 <<endl;
	      trouve = true;
	      size2++;
	      for (a = 0; a < size; a++) 
	      {
		  vec2[a] += M[a + pos2 * size];
// 		  cerr << vec2[a] << " ";
	      }
	  }
	  else
	  {
	      for (a = 0; a < size; a++) 
	      {
		  vec2[a] += 1;
// 		  cerr << vec2[a] << " ";
	      }
// 	      cerr << endl;
	  }
// 	return 0.0;
      }
      if (!trouve) return 0.0;
      dist = 0;
      len1 = 0.0;
      len2 = 0.0;
      for (a = 0; a < size; a++) 
      {
	  len1 += vec1[a]*vec1[a];
	  len2 += vec2[a]*vec2[a];
// 	  dist += (vec1[a]/size1) * (vec2[a]/size2) ;
	  dist += (vec1[a]) * (vec2[a]) ;
// 		  cerr << vec1[a] << " " << vec2[a] << endl;;
      }
//       cerr << len1 <<"\t"<< len2 << endl;
//       cerr << Tools::vectorToString(vec1," ") <<endl;
//       cerr << Tools::vectorToString(vec2," ") <<endl;
      
//       return dist;
      return dist/(sqrt(len1)*sqrt(len2));
  }
  
    float distance::getSimilarityNgramsFixed(char * ng1, char * ng2)
  {
//       float len;
      float dist;
      int a;
      float vec1[size];
      float vec2[size];
      float len1=0;
      float len2=0;
      char st1[max_size];
      char st2[max_size];
      int size1 = 0;
      int size2 = 0;
      vector<string> vs1 = splitNgrams(ng1);
      vector<string> vs2 = splitNgrams(ng2);
      cerr << "NgramFixed"<< endl;
      if ( vs1.size() != vs2.size() )
      {
	  cerr << "Error: vector sizes are different!" <<endl;
	  return 0.0;
      }
      int i;
      int pos1 = -1; 
      int pos2 = -1;
//       b = 0;
      for (a = 0; a < size; a++) 
      {
	  vec1[a]=0.0;
	  vec2[a]=0.0;
      }
      bool trouve = false;
      for (i=0 ; i < (int)vs1.size(); i++)
      {
// 	  cerr << vs1.at(i) << endl;
	  strcpy(st1,vs1.at(i).c_str());
	  pos1 = searchVocab(st1);
	  if (pos1 != -1) 
	  {
	      trouve = true;
	      size1++;
// 	      cerr << pos1 <<endl;
	      for (a = 0; a < size; a++) 
	      {
		  vec1[a] += M[a + pos1 * size];
	      }
	  }
	  else
	  {
	      for (a = 0; a < size; a++) 
	      {
		  vec1[a] += 1;
	      }
	  }
      }
      if (!trouve) return 0.0;
      trouve = false;
      for (i=0 ; i < (int)vs2.size(); i++)
      {
// 	  cerr << vs2.at(i) << endl;
	  strcpy(st2,vs2.at(i).c_str());
	  pos2 = searchVocab(st2);
	  if (pos2 != -1) 
	  {
// 	      cerr << pos2 <<endl;
	      trouve = true;
	      size2++;
	      for (a = 0; a < size; a++) 
	      {
		  vec2[a] += M[a + pos2 * size];
	      }
	  }
	  else
	  {
	      for (a = 0; a < size; a++) 
	      {
		  vec2[a] += 1;
	      }
	  }
      }
      if (!trouve) return 0.0;
      dist = 0;
      len1 = 0.0;
      len2 = 0.0;
      for (a = 0; a < size; a++) 
      {
	  len1 += vec1[a]*vec1[a];
	  len2 += vec2[a]*vec2[a];
	  dist += (vec1[a]) * (vec2[a]) ;
      }
//       cerr << len1 <<"\t"<< len2 << endl;
      return dist/(sqrt(len1)*sqrt(len2));
  }

    float distance::getSimilarityNgramsFixedOrdered(char * ng1, char * ng2)
  {
//       float len;
      float dist;
      int a;
      char st1[max_size];
      char st2[max_size];
      if (strcmp(ng1,ng2) == 0) return 1.0;
      vector<string> vs1 = splitNgrams(ng1);
      vector<string> vs2 = splitNgrams(ng2);
      cerr << "NgramFixedOrdered"<< endl;
      if ( vs1.size() != vs2.size() )
      {
	  cerr << "Error: vector sizes are different!" <<endl;
	  return 0.0;
      }
      int i;
      int pos1 = -1; 
      int pos2 = -1;
//       b = 0;
      dist = 0.0;
      for (i=0 ; i < (int)vs1.size(); i++)
      {
	  float l_dist = 0.0;
	  strcpy(st1,vs1.at(i).c_str());
	  strcpy(st2,vs2.at(i).c_str());
	  if (strcmp(st1,st2) == 0) 
	  {
	      l_dist=1.0;
	  }
	  else
	  {
	      pos1 = searchVocab(st1);
	      pos2 = searchVocab(st2);
	      if ((pos2 != -1) && (pos1 != -1)) 
	      {
		  for (a = 0; a < size; a++) 
		  {
		      l_dist += M[a + pos1 * size] * M[a + pos2 * size];
		  }
	      }
	  }
	  dist += l_dist;
      }
      dist = dist / (float)vs1.size();
      return dist;
  }
  bool distance::strcompare(char* c1, char* c2)
  {
      int l1 = strlen(c1);
      if (l1 != (int)strlen(c2))
      {
	  return false;
      }
      for (int i = 0; i < l1; i++)
      {
	  if (c1[i] != c2[i]) return false;
      }
      return true;
  }
        /* Returns hash value of a word */
  int distance::getWordHash(char *word) 
  {
      unsigned long long a, hash = 0;
      for (a = 0; a < strlen(word); a++) hash = hash * 257 + word[a];
      hash = hash % vocab_hash_size;
      return hash;
  }

  /* Returns position of a word in the vocabulary; if the word is not found, 
  * returns -1 */
  int distance::searchVocab(char *word) 
  {
      unsigned int hash = getWordHash(word);
      int l_b;
      while (1) 
      {
	  if (vocab_hash[hash] == -1) return -1;
// 	  if (!strcmp(word, vocab[vocab_hash[hash]].word)) return vocab_hash[hash];
	  l_b = vocab_hash[hash];
	  if (!strcmp(&vocab[l_b * max_w], word)) return vocab_hash[hash];
	  hash = (hash + 1) % vocab_hash_size;
      }
      return -1;
  }
  /* Adds a word to the vocabulary */
  void distance::addWordToHash(char *word, int l_pos) {    
    unsigned int hash = getWordHash(word);
    while (vocab_hash[hash] != -1) hash = (hash + 1) % vocab_hash_size;
    vocab_hash[hash] = l_pos;
//     return l_pos;
  }
  void distance::fillHash()
  {
      int c;
      vocab_hash = (int*)calloc(vocab_hash_size, sizeof(int));
//       cerr << "Size of hash vocab : " << vocab_hash_size <<endl;
      for (c = 0; c < vocab_hash_size; c++)
      {
	  vocab_hash[c] = -1;
      }
//       cerr << "Size of vocab : " << words <<endl;
      for (c = 0; c < words; c++)
      {
	 addWordToHash(&vocab[c * max_w], c);
// 	cerr << ".";
// 	 if (c % (words / 100) == 0)
// 	   cerr << "|";
      }
//       cerr << endl;
  }
  float distance::getSimilarity(const char* s1, const char* s2)
  {
      char st1[max_size];
      char st2[max_size];
      strcpy(st1,s1);
      strcpy(st2,s2);
      return getSimilarity(st1,st2);
  }
  float distance::getSimilarity(string s1, string s2)
  {
      char st1[max_size];
      char st2[max_size];
      strcpy(st1,s1.c_str());
      strcpy(st2,s2.c_str());
      return getSimilarity(st1,st2);
  }
  float distance::getSimilarityNgrams(const char* ng1, const char* ng2)
  {
      char st1[max_size];
      char st2[max_size];
      strcpy(st1,ng1);
      strcpy(st2,ng2);
      return getSimilarityNgrams(st1,st2);

  }
  float distance::getSimilarityNgramsFixed(const char* ng1, const char* ng2)
  {
      char st1[max_size];
      char st2[max_size];
      strcpy(st1,ng1);
      strcpy(st2,ng2);
      return getSimilarityNgramsFixed(st1,st2);

  }
  float distance::getSimilarityNgramsFixedOrdered(const char* ng1, const char* ng2)
  {
      char st1[max_size];
      char st2[max_size];
      strcpy(st1,ng1);
      strcpy(st2,ng2);
      return getSimilarityNgramsFixedOrdered(st1,st2);

  }
float distance::getDistance(const char* s1, const char* s2)
{
    return 1.0-getSimilarity(s1,s2);
}
float distance::getDistance(char* s1, char* s2)
{
    return 1.0-getSimilarity(s1,s2);
}
float distance::getDistanceNgrams(char* ng1, char* ng2)
{
    return 1.0-getSimilarityNgrams(ng1,ng2);
}
float distance::getDistanceNgrams(const char* ng1, const char* ng2)
{
    return 1.0-getSimilarityNgrams(ng1,ng2);
}
float distance::getDistanceNgramsFixed(char* ng1, char* ng2)
{
    return 1.0-getDistanceNgramsFixed(ng1,ng2);
}
float distance::getDistanceNgramsFixed(const char* ng1, const char* ng2)
{
    return 1.0-getDistanceNgramsFixed(ng1,ng2);
}
float distance::getDistanceNgramsFixedOrdered(char* ng1, char* ng2)
{
    return 1.0-getSimilarityNgramsFixedOrdered(ng1,ng2);
}
float distance::getDistanceNgramsFixedOrdered(const char* ng1, const char* ng2)
{
    return 1.0-getSimilarityNgramsFixedOrdered(ng1,ng2);
}
  vector<float> distance::getWord(const char* word)
  {
      char st1[max_size];
      strcpy(st1,word);
      return getWord(st1);
  }
vector< float > distance::getWord(string word)
{
      char st1[max_size];
      strcpy(st1,word.c_str());
      return getWord(st1);

}
  
}