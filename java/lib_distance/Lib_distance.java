import java.io.*;
import java.lang.reflect.Array;
import java.nio.*;
import java.nio.channels.FileChannel;
import java.nio.channels.FileChannel.MapMode;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Vector;

public class Lib_distance
{
	private int vocab_hash_size = 30000000;
	private int vocab_size, vector_size;
    private String[] vocab;
    private float[][] embeddings;
    private int[] vocab_hash = new int[vocab_hash_size];
    private HashMap<String, Integer> myHashMap;
    public String concatHexValues(String s1, String s2, String s3, String s4)
    {
    		String toReturn = "";
    		if (s1.length() < 2)
    		{
    			toReturn = toReturn+"0"+s1;  
    		}
    		else toReturn = toReturn+s1;
    		if (s2.length() < 2)
    		{
    			toReturn = toReturn+"0"+s2;  
    		}
    		else toReturn = toReturn+s2;
    		if (s3.length() < 2)
    		{
    			toReturn = toReturn+"0"+s3;  
    		}
    		else toReturn = toReturn+s3;
    		if (s4.length() < 2)
    		{
    			toReturn = toReturn+"0"+s4;  
    		}
    		else toReturn = toReturn+s4;
    		return toReturn;
    	
    }

	public Lib_distance(String filename) throws IOException
	  {
		  
		  FileInputStream inputBinaryFile = new FileInputStream (filename);	  // Fichier binaire    
		  DataInputStream inputBinaryData = new DataInputStream (inputBinaryFile);    // Le même fichier via stream

		  System.out.println();
		  String infos = inputBinaryData.readLine().toString();
		  String[] vInfos = infos.split(" ");
		  vocab_size = Integer.parseInt(vInfos[0]);
		  vector_size = Integer.parseInt(vInfos[1]);
		  vocab= new String[(int)vocab_size];
		  //Initialize all the values of the hash array to -1
		  Arrays.fill(vocab_hash,-1);
		  String l_word="";
		  int wordCount=0;
		  myHashMap = new HashMap<String, Integer>(vocab_hash_size);
		  System.out.print("Vocabulary size: ");
		  System.out.println(vocab_size);
		  System.out.print("Vector size: ");
		  System.out.println(vector_size);
		  embeddings = new float[(int)vocab_size][(int)vector_size];
		  int colCount=0;
		  while (wordCount<vocab_size)
		  {
			  char[] l_c=Character.toChars((int)inputBinaryData.read());
			  l_word="";
			  while (l_c[0] != ' ')
			  {
				  l_word=l_word+String.copyValueOf(l_c);
				  l_c=Character.toChars((int)inputBinaryData.read());
			  }
			  colCount=0;
			  vocab[wordCount]=l_word;
			  myHashMap.put(new String(l_word), wordCount);
			  float l_length=0;
			  while(colCount < vector_size)
			  {
				  String hex3 = Integer.toHexString(inputBinaryData.read()).toUpperCase();
				  String hex2 = Integer.toHexString(inputBinaryData.read()).toUpperCase();
				  String hex1 = Integer.toHexString(inputBinaryData.read()).toUpperCase();
				  String hex0 = Integer.toHexString(inputBinaryData.read()).toUpperCase();
				  String hex=concatHexValues(hex0, hex1, hex2, hex3);
			  	  Long lI = Long.parseLong(hex, 16);
				  Float lF = Float.intBitsToFloat(lI.intValue());
				  embeddings[wordCount][colCount]=lF;
				  l_length=l_length+(lF*lF);
				  colCount++;
			  }
			  colCount = 0;
			  l_length=(float) Math.sqrt(l_length);
			  while(colCount < vector_size)
			  {
				  embeddings[wordCount][colCount]=embeddings[wordCount][colCount]/l_length;
				  colCount++;
			  }
			  inputBinaryData.read();
			  wordCount++;
			  if (wordCount % (vocab_size/100) == 0) System.out.print(".");
		  if (wordCount % (vocab_size/10) == 0) System.out.print("|");
		  }
		  System.out.println();
	  }
	public float[] getVector(String word)
	{
		float[] toReturn= new float[(int)vector_size];
		Arrays.fill(toReturn,0);
		if ( myHashMap.containsKey(word) )
		{
			int wordIndex = (int)myHashMap.get(word);
			toReturn = embeddings[wordIndex];
		}
		return toReturn;
	}
	public float getSimilarity(String w1, String w2)
	{
		  if ( !myHashMap.containsKey(w1) )
		  {
			  //System.err.println(w1 + " not founded!");
			  return 0;
		  }
		  if ( !myHashMap.containsKey(w2) )
		  {
			  //System.err.println(w2 + " not founded!");
			  return 0;
		  }
		  float[] v1 = getVector(w1);
		  float[] v2 = getVector(w2);
		  //float[] vfinal = new float[(int)vector_size];
		  float sim = 0;
		  int colCount = 0;
		  while(colCount < vector_size)
		  {
			  sim = sim + v1[colCount]*v2[colCount];
			  colCount++;
		  }
		  return sim;
		  
	}
	public float getDistance(String w1, String w2)
	{
		  return 1-getSimilarity(w1, w2);
	}
}