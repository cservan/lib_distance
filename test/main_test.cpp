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
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <boost/thread/thread.hpp>
// #include <boost/thread/thread_group.hpp>

void print_somme(int x,int y, int j)
{
    int l_x=(int)x; 
    int l_y=(int)y; 
    std::cout << "lancé " << j <<std::endl;
	sleep(j);
    std::cout<<l_x<<" + "<<l_y<<" = "<<(l_x+l_y)<<std::endl;
}
int main()
{
  
    int i;
    boost::thread_group group;
    
    for (i =0; i<10; i++)
    {
	boost::thread *t;
	t = new boost::thread(&print_somme,i,i+1,i);
	group.add_thread(t);
    }
    group.join_all();
}