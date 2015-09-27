import java.io.*;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Lib_distance
{
	public long max_size = 2000;         // max length of strings
	public long N = 40;                  // number of closest words that will be shown
	public long max_w = 50;              // max length of vocabulary entries
	public int vocab_hash_size = 30000000;
//    private char[] bestw[N];
//    private char file_name[max_size], st[100][max_size];
//    private float dist, len, bestd[N];
//    private long words, size, a, b, c, d, cn, bi[100];
	private long words, size, a, b, c, d, cn;
    private char ch;
    private float[] M;
    private char[] vocab;
    private float[] D;
    private float[] L;
//     struct vocab_word *vocab;
    private int[] vocab_hash;

	  public Lib_distance(String filename) throws IOException
	  {
		  
//		  FileInputStream fis = new FileInputStream(filename);  
		  //BufferedInputStream bin = new BufferedInputStream(fis);
		  //BufferedReader reader = Files.newBufferedReader(Paths.get(filename), StandardCharsets.UTF_8);
//		  String line;
//		  System.out.println(reader.read());
		  Charset charset = StandardCharsets.UTF_8;
		  String content = new String(Files.readAllBytes(Paths.get(filename)), charset);
		  
		  //System.out.println(content);
//		  System.out.println(content.substring(0,300));
		  String contentTab[]=content.substring(0,300).split("\\s+");
		  words =  Integer.parseInt(contentTab[0]);
		  size =  Integer.parseInt(contentTab[1]);
		  int tmpLength=contentTab[0].length()+1+contentTab[1].length()+1;
		  int cpt=0;
		  String tmpcontent=content.substring(tmpLength);
//		  while (tmpLength < content.length() && cpt < 5)
//		  {
		  
			  String output = tmpcontent.substring(0,tmpcontent.indexOf(" "));
			  String data = tmpcontent.substring(tmpcontent.indexOf(" "),(int)(size+1)*2);
			  System.out.println(output);
			  System.out.println(data);
			  
			  cpt++;
//		  }
	//      BufferedReader reader = Files.newBufferedReader(Paths.get(filename), StandardCharsets.UTF_8);
//	      System.out.println(reader.readLine());
	      
			  
//		  System.out.println("0 "+contentTab[0]);
//		  System.out.println("1 "+contentTab[1]);
		  System.out.println("2 "+contentTab[2]);
		  System.out.println("3 "+contentTab[3]);
		  System.out.println("4 "+contentTab[4]);
		  System.out.println("5 "+contentTab[5]);
              //System.out.println(line);
		  FileInputStream inputBinaryFile = new FileInputStream (filename);        // Fichier binaire    
		  DataInputStream inputBinaryData = new DataInputStream (inputBinaryFile);    // Le même fichier via stream
		  //0.198994        0.219711        -0.190422       -0.162968       0.0679395       0.150194        0.0467748       0.0105065       -0.179149       0.110292        -0.216578       0.0621211       -0.0373531      -0.0475865      -0.164842       -0.0935723      0.128232      0.150406 0.147607        0.079417        0.0767998       -0.189049       -0.203621       0.247066        0.18898 0.153622        -0.0300251      0.199639        -0.0246087      0.0365262       -0.00741903     -0.148312       0.0652389       -0.0664906      -0.190179     0.236354 0.217716        -0.0544441      -0.0112423      0.0253142       -0.180848       -0.199214       0.22644 0.00313298      -0.128384       -0.15124        -0.152947       0.084363        0.0100134       0.066172

		  System.out.println(inputBinaryData.readLine());
		  System.out.println(inputBinaryData.read());
		  System.out.println(inputBinaryData.read());
		  System.out.println(inputBinaryData.read());
		  System.out.println(inputBinaryData.read());
		  System.out.println(inputBinaryData.read());
		  System.out.print(inputBinaryData.read());
		  /*
		  int NbDonneesLues=0;         
		  for(;;){                
		   
		  TabNum [NbDonneesLues] = (long)inputBinaryData.readInt ();
		  NbDonneesLues++;                                            
		  }
*/
		  final String original = "Mémé dans les orties";

	        final byte[] encoded = original.getBytes(charset);
    //      while ((line = reader.readLine()) != null) {
  //            System.out.println(line);
//          }
/*
		  int length = 1; 

		  System.out.println("1st: "); 
		  byte[] tempId = new byte[8];
		  bin.read(tempId); 
		  String id = new String ( tempId, "US-ASCII" ); 
		  System.out.println( " out = " + id ); 

		  System.out.println("2nd: "); 
		  int size1 = 8; 
		  byte[] tempId2 = new byte[size1];
		  bin.read(tempId2, 0, size1); 
		  String id2 = new String ( tempId2, "US-ASCII"); 
		  System.out.println( " out = " + id2 ); 



		  for(int j = 0; j < 20; j++) 
		  {
		       int size = 2; 
		       byte[] tempId3 = new byte[size];
		       bin.read(tempId3, 0, size); 
		       String id3 = new String ( tempId3, "US-ASCII" ); 
		       System.out.println( " out = " + id3 );                  
		  }*/
	  }
	  /*
		  
	    strcpy(file_name, filename.c_str());
	    f = fopen(file_name, "rb");
	    if (f == NULL) 
	    {
	      printf("Word2Vec Model file not found\n");
	      exit(-1);
	    }
	    fscanf(f, "%lld", &words);
	    fscanf(f, "%lld", &size);
	    vocab = (char *)malloc((long long)words * max_w * sizeof(char));
	    for (a = 0; a < N; a++) bestw[a] = (char *)malloc(max_size * sizeof(char));
	    M = (float *)malloc((long long)words * (long long)size * sizeof(float));
//	     D = (float *)malloc((long long)words * (long long)words * sizeof(float));
//	     L = (float *)malloc((long long)words * sizeof(float));
	    if (M == NULL) 
	    {
	      printf("Cannot allocate memory: %lld MB    %lld  %lld\n", (long long)words * size * sizeof(float) / 1048576, words, size);
	      exit(-1);
	    }
	    cerr << "Loading word2vec model...";
//	     printf("Allocation of memory: %lld MB    %lld  %lld\n", (long long)words * size * sizeof(float) / 1048576, words, size);
	    for (b = 0; b < words; b++) 
	    {
	      a = 0;
	      while (1) 
	      {
		vocab[b * max_w + a] = fgetc(f);
		if (feof(f) || (vocab[b * max_w + a] == ' ')) break;
		if ((a < max_w) && (vocab[b * max_w + a] != '\n')) a++;
	      }
	      vocab[b * max_w + a] = 0;
	      for (a = 0; a < size; a++) fread(&M[a + b * size], sizeof(float), 1, f);
	      len = 0;
	      for (a = 0; a < size; a++) len += M[a + b * size] * M[a + b * size];
	      len = sqrt(len);
	      for (a = 0; a < size; a++) M[a + b * size] /= len;
	    }
	    fclose(f);
	    
//	     mvocab = new multimap < String, int >;
//	     for (b = 0; b < words; b++) 
//	     {
	// // 	pair < String, int > p(String(&vocab[b * max_w]),b);
//	  	mvocab->insert(make_pair < String, int > (String(&vocab[b * max_w]),b));
//	     }
	    
//	     for (b = 0; b < words; b++) 
//	     {
//	 	len = 0;
//	 	for (a = 0; a < size; a++) len += M[a + b * size] * M[a + b * size];
//	 	L[b] = sqrt(len);
//	     }
//	     for (b = 0; b < words; b++) 
//	     {
//	 	for (c = 0; c <= b; c++) 
//	 	{
//	 	    D[b*c] = 0.0;
//	 	    for (a = 0; a < size; a++) 
//	 	    {
//	 		D[b*c] += (M[a + b * size] / L[b]) * (M[a + c * size] / L[c]);
//	 	    }
//	 	}
//	     }

//	     cerr << mvocab->size() <<endl;
	    fillHash();
	    cerr << "finished!" <<endl;
	  }


	  vector< pair< String, float > > recherche(String s)
	  {
	    vector< pair< String, float > > to_return;
	    float vec[max_size];
	    for (a = 0; a < N; a++) bestd[a] = 0;
	    for (a = 0; a < N; a++) bestw[a][0] = 0;
//	     printf("Enter word or sentence (EXIT to break): ");
	    a = 0;
//	     while (1) {
//	       st1[a] = fgetc(stdin);
//	       if ((st1[a] == '\n') || (a >= max_size - 1)) {
//	         st1[a] = 0;
//	         break;
//	       }
//	       a++;
//	     }
	    char st1[max_size];
	    strcpy(st1, s.c_str());
//	     st1 = s.c_str();
//	     if (!strcmp(st1, "EXIT")) break;
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
//	       printf("\nWord: %s  Position in vocabulary: %lld\n", st[a], bi[a]);
	      if (b == -1) {
//	 	printf("%s: Out of dictionary word!\n",st[a]);
	        return to_return;
	      }
	    }
	    if (b == -1) return to_return;
//	     printf("\n                                              Word       Cosine distance\n------------------------------------------------------------------------\n");
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
	    
//	       for (a = 0; a < N && a < 10 ; a++) 
//	 	printf("%50s\t\t%f\n", bestw[a], bestd[a]);
	    for (a = 0; a < N; a++) 
	    {
	      pair<String,float> l_p( String(bestw[a]), bestd[a]);
//	       printf("%50s\t\t%f\n", bestw[a], bestd[a]);
	      to_return.push_back(l_p);
	    }
	    return to_return;
	  }
	  float getSimilarity(String s1, String s2)
	  {
	    float vec1[max_size];
	    float vec2[max_size];
	  //     vector< pair< String, float > > to_return;
	      for (a = 0; a < N; a++) bestd[a] = 0;
	      for (a = 0; a < N; a++) bestw[a][0] = 0;
//	       printf("Enter word or sentence (EXIT to break): ");
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
//	 	printf("\nWord: %s  Position in vocabulary: %lld\n", st[a], bi[a]);
		pos1=bi[a];
		if (b == -1) {
//	 	  printf("%s: Out of dictionary word!\n",st[a]);
		  return 0.0;
		}
	      }
	      // Verification de la présence dans le vocab
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
//	       cerr << a << " " << cn << endl;
		for (b = 0; b < words; b++) if (!strcmp(&vocab[b * max_w], st[a])) break;
		if (b == words) b = -1;
		bi[a] = b;
		pos2=bi[a];
//	 	printf("\nWord: %s  Position in vocabulary: %lld\n", st[a], bi[a]);
		if (b == -1) {
//	 	  printf("%s: Out of dictionary word!\n",st[a]);
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

//	       for (a = 0; a < N; a++) bestd[a] = -1;
//	       for (a = 0; a < N; a++) bestw[a][0] = 0;
//	       for (c = 0; c < words; c++) {
//	 	a = 0;
//	 	for (b = 0; b < cn; b++) if (bi[b] == c) a = 1;
//	 	if (a == 1) continue;
//	 	dist = 0;
//	 	for (a = 0; a < size; a++) dist += vec[a] * M[a + c * size];
//	 	for (a = 0; a < N; a++) {
//	 	  if (dist > bestd[a]) {
//	 	    for (d = N - 1; d > a; d--) {
//	 	      bestd[d] = bestd[d - 1];
//	 	      strcpy(bestw[d], bestw[d - 1]);
//	 	    }
//	 	    bestd[a] = dist;
//	 	    
//	 	    strcpy(bestw[a], &vocab[c * max_w]);
//	 	    break;
//	 	  }
//	 	}
//	       }
//	       for (a = 0; a < N && a < 2 ; a++) 
//	       {
//	 	pair<String,float> l_p( String(bestw[a]), bestd[a]);
//	 	printf("%50s\t\t%f\n", bestw[a], bestd[a]);
//	       }
//	       return 1.0;
	  }
	  float getSimilarityTest(String &s1, String &s2)
	  {
//	       float vec1[max_size];
//	       float vec2[max_size];
//	       float len1=0;
//	       float len2=0;
	      char st1[max_w];
	      char st2[max_w];
	      strcpy(st1, s1.c_str());
	      strcpy(st2, s2.c_str());
	      int pos1 = -1; 
	      int pos2 = -1;
	      b = 0;
	      for (b = 0; b < words; b++)
	      {
		if (!strcmp(&vocab[b * max_w], st1)) 
		{
		  pos1=b;
		  break;
		}
	      }
	      if (pos1 == -1) 
	      {
		return 0.0;
	      }
	      for (c = 0; c < words; c++)
	      {
		if (!strcmp(&vocab[c * max_w], st2)) 
		{
		  pos2=c;
		  break;
		}
	      }
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
	  float getSimilarity(char * st1, char * st2)
	  {
//	       float vec1[max_size];
//	       float vec2[max_size];
//	       float len1=0;
//	       float len2=0;
	      int pos1 = -1; 
	      int pos2 = -1;
	      b = 0;
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
	  float getDistance(char * st1, char * st2)
	  {
	      return (1.0-getSimilarity(st1,st2));
	  }
	  float getDistance(String st1, String st2)
	  {
	      return (1.0-getSimilarity(st1,st2));
	  }
	 
	  
	  bool strcompare(char* c1, char* c2)
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
	        // Returns hash value of a word 
	  int getWordHash(char *word) 
	  {
	      unsigned long long a, hash = 0;
	      for (a = 0; a < strlen(word); a++) hash = hash * 257 + word[a];
	      hash = hash % vocab_hash_size;
	      return hash;
	  }

	  // Returns position of a word in the vocabulary; if the word is not found, 
	  // returns -1 
	  int searchVocab(char *word) 
	  {
	      unsigned int hash = getWordHash(word);
	      int l_b;
	      while (1) 
	      {
		  if (vocab_hash[hash] == -1) return -1;
//	 	  if (!strcmp(word, vocab[vocab_hash[hash]].word)) return vocab_hash[hash];
		  l_b = vocab_hash[hash];
		  if (!strcmp(&vocab[l_b * max_w], word)) return vocab_hash[hash];
		  hash = (hash + 1) % vocab_hash_size;
	      }
	      return -1;
	  }
	  // Adds a word to the vocabulary 
	  void addWordToHash(char *word, int l_pos) {    
	    unsigned int hash = getWordHash(word);
	    while (vocab_hash[hash] != -1) hash = (hash + 1) % vocab_hash_size;
	    vocab_hash[hash] = l_pos;
	  }
	  void fillHash()
	  {
	      int c;
	      vocab_hash = (int*)calloc(vocab_hash_size, sizeof(int));
	      for (c = 0; c < vocab_hash_size; c++)
	      {
		  vocab_hash[c] = -1;
	      }
	      for (c = 0; c < words; c++)
	      {
		 addWordToHash(&vocab[c * max_w], c);
	      }
	  }
	*/

}