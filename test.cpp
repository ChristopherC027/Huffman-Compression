/*====================================================================
 * test.cpp
 * Authors: Bobby Craig, Ansel Schiavone, Chris Castillo
 * Proj4
 * CS271 - Dr. Jessen Havill
 *====================================================================*/

#include "MPQ.h"
#include <assert.h>
using namespace std;

void test_default_constructor()
{
	
}

void test_non_default()
{
	
}

void test_copy()
{
	MinPriorityQueue<int> H1(10);
	MinPriorityQueue<int> H2(H1);
	assert(H1.toString()==H2.toString()&& "Copy");
}

void test_min()
{
	MinPriorityQueue<int> H1(10);
	int * int2 = new int;
	*int2=2;
	int *int1 = new int;
	*int1=1;
	H1.insert(int2);
	H1.insert(int1);
	try
	{
		assert(*H1.minimum()==1 && "Min");
	}
	catch(EmptyError exception)
	{
		cerr<<"Error; Cannot find minimum of an empty MPQ"<<endl;
	}
	
}

void test_extract_min()
{
	MinPriorityQueue<int> H1;
	int * int3 = new int;
	*int3=3;
	int *int4 = new int;
	*int4=4;
	int *int1 = new int;
	*int1=1;
	H1.insert(int3);
	H1.insert(int4);
	H1.insert(int1);
	
	try
	{
	int minimumNum = *H1.extractMin();
	assert(*H1.minimum()==3);
	assert(minimumNum==1);
	}
	catch(EmptyError exception)
	{
		cerr<<"Error; Cannot find minimum of an empty MPQ"<<endl;
	}
}

void test_decrease_key()
{
	MinPriorityQueue<int> H1;
	int * int3 = new int;
	*int3=3;
	int *int4 = new int;
	*int4=4;
	int *int1 = new int;
	*int1=1;
	H1.insert(int3);
	H1.insert(int4);
	H1.insert(int1);
	
	int *int0 = new int;
	*int0=0;
	int *int2 = new int;
	*int2=2;

	try
	{
		H1.decreaseKey(0,int0);
		H1.decreaseKey(1,int2);
		assert(*H1.extractMin()==0 && "Decrease Key");
		assert(*H1.extractMin()==2 && "Decrease Key");

	}
	catch(EmptyError exception)
	{
		cerr<<"Error; Empty MPQ"<<endl;
	}
	catch(KeyError exception)
	{
		cerr<<"Error; New key must be smaller than original"<<endl;

	}
}

void test_insert()
{
	
	MinPriorityQueue<int> H1;
	int * int3 = new int;
	*int3=3;
	H1.insert(int3);
	try
	{
		assert(*H1.minimum()==3 && "Insert");
	}
	catch(FullError exception)
	{
		cerr<<"Error: MPQ is at capacity. Cannot insert"<<endl;
	}

}

void test_empty()
{
	MinPriorityQueue<int> H1;
	assert(H1.empty()==true && "Empty");
	
}


int main()
{
	test_default_constructor();
	test_non_default();
	test_copy();
	test_min();
	test_extract_min();
	//test_decrease_key();
	//test_insert();
	//test_empty();
	return 0;
}

