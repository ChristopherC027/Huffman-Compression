#include <iostream>
#include <sstream>
using namespace std; 

/*Preconditions: a MinHeap instance must be declared
with a specified template type.

Postconditions: an array of size n*Keytype is dynamically
allocated, and capacity is set equal to n. heapSize is assigned
the value of 0 becuase no heap has been created.*/

template <class KeyType>
MinHeap<KeyType>::MinHeap(int n)//default constructor
{
	A = new KeyType* [n];
	capacity = n;
	heapSize = 0;
}

/*Preconditions:a MinHeap instance must be declared
with a specified template type,and an array and matching
n value passed as parameters. (NOTE: n MUST be the size
of the array being passed).

Postconditions:an array of size n*Keytype is dynamically
allocated, and capacity is set equal to n.All elements in 
the array parameter are assined to the newly allocated 
array, A.heapSize is assigned the value of 0 becuase no heap
has been created.*/
template <class KeyType>
MinHeap<KeyType>::MinHeap(KeyType* initA[], int n)//construct heap from array
{
	A = new KeyType* [n];
	for(int i=0; i<n; i++)
	{
		A[i]=initA[i];
	}
	capacity = n;
	heapSize = 0;
}

/*Preconditions: a MinHeap instance must be declared
with a specified template type and a previously declared
MinHeap instance of matching template type passed in parameter.

Postconditions:The MinHeap instance utilizing the copy constructor
will be exactly the same as the MinHeap passed into the parameter.*/
template <class KeyType>
MinHeap<KeyType>::MinHeap(const MinHeap<KeyType>& heap)//copy constructor
{
	copy(heap);
}

/*Preconditions: a MinHeap instance must have been previously
declared with a specified template type.

Postcondition: The memory that was dynamically allocated for the
MinHeap is deallocated and returned to the heap.*/
template <class KeyType>
MinHeap<KeyType>::~MinHeap()
{
	destroy();
}


/*Preconditions: a MinHeap instance must have been previously
declared with a specified template type. This MinHeap instance
must then call heapify with an integer index parameter.

Postcondition:The index parameter is now the root of a
complete MinHeap.*/
template <class KeyType>
void MinHeap<KeyType>::heapify(int index)
{
	int left, right, smallest;
	left = leftChild(index);
	right = rightChild(index);
	if(left < heapSize && *(A[left]) < *(A[index]))
		smallest = left;
	else
		smallest = index;
	if(right<heapSize && *(A[right])<*(A[smallest]))
		smallest=right;
	if(smallest != index)
	{
		swap(index, smallest);
		heapify(smallest);
	}
}

/*Precondition: a MinHeap instance must have been previously
declared with a specified template type. This MinHeap instance
must then call buildHeap. 

Postcondition: the MinHeap array value A is now a complete
MinHeap.*/
template <class KeyType>
void MinHeap<KeyType>::buildHeap()
{
	heapSize=capacity;
	for(int i=(capacity/2)-1;i>=0;i--)
	{
		heapify(i);
	}
}


/*Precondition:a MinHeap instance must have been previously
declared with a specified template type. This MinHeap instance
must then call heapSort, with a previously declared array of 
matching KeyType as a parameter. 

Postcondition: The array sorted[] will now be in sorted descending
order.*/
template <class KeyType>
void MinHeap<KeyType>::heapSort(KeyType* sorted[])
{
	buildHeap();
	for(int i = (capacity-1);i>=1; i--)
	{
		swap(0, i);
		heapSize--;
		heapify(0);
	}
	for(int j=0; j<capacity; j++)
	{
		sorted[j]=A[j];
	}
}

/*Precondition: two MinHeap instances must have been previously
declared with matching specified template types. One of these 
instances must then be assigned to the other in the form of 
H1=H2

Postcondition: H1 will now be exactly identical to H2, because
the assignment operator will return a copy of H2 to H1.*/
template <class KeyType>   
MinHeap<KeyType>& MinHeap<KeyType>::operator=(const MinHeap<KeyType>& heap)
{
	if(this != &heap)
	{
		destroy();
		copy(heap);
	}
	return *this;
}


/*Precondition: a MinHeap instance must have been previously
declared with a specified template type.

Postcondition: a string value "string_heap" will be returned 
that depicts the format of array A.*/
template <class KeyType>
string MinHeap<KeyType>::toString() const
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

/*Precondition: two MinHeap instances of matching types
must have been previously declared. copy must then be called
by another member function(because it is private) with H2 as
a parameter.

Postcondition: H1 will now have the exact same representation
as H2.*/
template <class KeyType>
void MinHeap<KeyType>::copy(const MinHeap<KeyType>& heap)
{
	A = new KeyType* [heap.capacity];
	for(int i=0; i<heap.capacity; i++)
	{
		*A[i]=*heap.A[i];
	}
	capacity=heap.capacity;
	heapSize=heap.heapSize;
		
}

/*Precondition: a MinHeap instance must have been previously
declared with a specified template type. A member function must
then call the swap method with two inbound integer indexes passed
as parameters (because it is a private method).

Postcondition: the elements in MinHeap's A, A[index1] and
A[index2] will be swapped.*/
template <class KeyType>
void MinHeap<KeyType>::swap(int index1, int index2)
{
	KeyType* temp;
	temp = A[index1];
	A[index1]=A[index2];
	A[index2]=temp;
	
}
/*Precondition: a MinHeap instance must have been previously
declared with a specified template type. A member function must
then call the destroy method (because it is a private method)

Postcondition: the dynamically allocated array A of the MinHeap
instance will be deallocated.*/
template <class KeyType>
void MinHeap<KeyType>::destroy()
{
	delete []A;
}

/*Precondition: a MinHeap instance must have been previously
declared with a specified template type.

Postcondition: a string representation of MinHeap's A array 
will be returned to stream and subsequently outputted to 
the terminal.*/
template <class KeyType>
ostream& operator<<(ostream& stream, const MinHeap<KeyType>& heap)
{
	stream<<heap.toString();
	return stream;
}

