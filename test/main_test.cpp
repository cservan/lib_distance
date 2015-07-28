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