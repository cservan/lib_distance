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
import java.io.IOException;

public class Main_launch
{
	  public static void main(String[] args) throws IOException, InterruptedException
	  { 
		  String fileName= new String ("models/model.bin.ep7-nc10-refs.lc.cbow_1.size_50.window_5.hs_0.negative_20.mincount_2.en");
		  Lib_distance test = new Lib_distance(fileName);
		  String w1 = "yes";
		  String w2 = "no";
		  System.out.println("Example of the cosine similarity score obtained with the two words "+w1 +" and "+w2+":");
		  System.out.println(test.getSimilarity(w1,w2));
		  System.out.println("Example of the 50 closest words to "+w1+":");
		  System.out.println(test.getClosest(w1));
		  System.out.println("Example of the 50 closest words to "+w2+":");
		  System.out.println(test.getClosest(w2));
//		  System.out.println(test.getDistance("</s>","</s>"));
//		  Thread.sleep(1000);
		  fileName= new String ("models/model.txt.ep7-nc10.lc.cbow_1.size_50.window_5.hs_0.negative_20.mincount_2.en");
		  Lib_distance test2 = new Lib_distance(fileName,"UTF8");
		  System.out.println("Example of the cosine similarity score obtained with the two words "+w1 +" and "+w2+":");
		  System.out.println(test2.getSimilarity(w1,w2));
		  System.out.println("Example of the 50 closest words to "+w1+":");
		  System.out.println(test2.getClosest(w1));
		  System.out.println("Example of the 50 closest words to "+w2+":");
		  System.out.println(test2.getClosest(w2));
		  
		  
	  }
}