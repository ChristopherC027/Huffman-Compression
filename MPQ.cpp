/*====================================================================
 * MPQ.cpp
 * Authors: Bobby Craig, Ansel Schiavone, Chris Castillo
 * Proj4
 * CS271 - Dr. Jessen Havill
 *====================================================================*/

using namespace std; 

template <class KeyType>
MinPriorityQueue<KeyType>::MinPriorityQueue()
{
	A = new KeyType* [100];
	capacity = 100;
	heapSize = 0;	
}

template <class KeyType>
MinPriorityQueue<KeyType>::MinPriorityQueue(int n)
{
	A = new KeyType* [n];
	capacity = n;
	heapSize = 0;
	
}

template <class KeyType>
MinPriorityQueue<KeyType>::MinPriorityQueue(const MinPriorityQueue<KeyType>& pq)
{
	A = new KeyType* [pq.capacity];
	for(int i=0; i<pq.capacity; i++)
	{
		A[i]=pq.A[i];
	}
	capacity=pq.capacity;
	heapSize=pq.heapSize;
}

template <class KeyType>
KeyType* MinPriorityQueue<KeyType>::minimum()
{
	if(heapSize<=0)
		throw EmptyError();
	else
	{
		return A[0];
	}
}

template <class KeyType>
KeyType* MinPriorityQueue<KeyType>::extractMin()
{
	if(heapSize<=0)
		throw EmptyError();

	else
	{
		KeyType* min = A[0];
		A[0]=A[heapSize-1];
		heapSize--;
		heapify(0);
		return min;
	}
	
	
}

template <class KeyType>
void MinPriorityQueue<KeyType>::decreaseKey(int index, KeyType* key)
{
	if(heapSize<=0)
		throw EmptyError();
	else if(*key>*A[index])
		throw KeyError();

	else
	{
		A[index]=key;
		while((index>=0)&&(*(A[index])<*(A[parent(index)])))
		{
			swap(index, parent(index));
			index=parent(index);
		}
	}
}

template <class KeyType>
void MinPriorityQueue<KeyType>::insert(KeyType* key)
{
	if(heapSize==capacity)
		throw FullError();

	else
	{
		A[heapSize]=key;
		heapSize++;
		int index=heapSize-1;
		while((index>=0)&&(*(A[index])<*(A[parent(index)])))
		{
			swap(index, parent(index));
			index=parent(index);
		}
	}
}

template <class KeyType>
bool MinPriorityQueue<KeyType>::empty() const
{
	if(heapSize==0)
		return true;
}

template <class KeyType>
int MinPriorityQueue<KeyType>::length() const
{
	return heapSize;
}

template <class KeyType>
string MinPriorityQueue<KeyType>::toString() const
{
	string string_heap;
	KeyType temp;
	string_heap = "[";
	for(int i=0; i<capacity; i++)
	{
		ostringstream convert;
		temp = *A[i];
		convert << temp;
		string_heap+=convert.str();
		if(i!=(heapSize-1))
		{
			if(i!=(capacity-1))
				string_heap+=", ";
		}
		if(i==(heapSize-1))
		{
			string_heap+="|";
		}
	}
	string_heap+="]";
	return string_heap;
}

template <class KeyType>
ostream& operator<<(ostream& stream, const MinPriorityQueue<KeyType>& pq)
{
	stream<<pq.toString();
	return stream;
}

