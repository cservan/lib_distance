import java.io.IOException;

public class Main_launch
{
	  public static void main(String[] args) throws IOException
	  { 
		  String fileName= new String ("/local/eclipse/workspace/lib_distance/models/model.bin.ep7-nc10-refs.lc.cbow_1.size_50.window_5.hs_0.negative_20.mincount_2.en");
		  Lib_distance test = new Lib_distance(fileName);
		  String w1 = "to";
		  String w2 = "a";
		  System.out.println(test.getSimilarity(w1,w2));
//		  System.out.println(test.getDistance("</s>","</s>"));
	  }
}