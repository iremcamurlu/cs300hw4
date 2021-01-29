        #ifndef SORT_H_
        #define SORT_H_

#define merge Merge
#define swap Swap
#include <iostream>
#include <vector>
#include<cstdlib>
#include<ctime>
using namespace std;





      /**
         * Simple insertion sort.
         */
        template <class Comparable>
        void insertionSort( vector<Comparable> & a )
        {
/* 1*/      for( int p = 1; p < a.size( ); p++ )
            {
/* 2*/          Comparable tmp = a[ p ];

                int j;
/* 3*/          for( j = p; j > 0 && tmp.word < a[ j - 1 ].word; j-- )
/* 4*/              a[ j ] = a[ j - 1 ];
/* 5*/          a[ j ] = tmp;
            }
        }
       /**
         * Standard heapsort.
         */
        template <class Comparable>
        void heapsort( vector<Comparable> & a )
        {
/* 1*/      for( int i = a.size( ) / 2; i >= 0; i-- )  /* buildHeap */
/* 2*/          percDown( a, i, a.size( ) );
/* 3*/      for( int j = a.size( ) - 1; j > 0; j-- )
            {
/* 4*/          swap( a[ 0 ], a[ j ] );                  /* deleteMax */
/* 5*/          percDown( a, 0, j );
            }
        }

        /**
         * Internal method for heapsort.
         * i is the index of an item in the heap.
         * Returns the index of the left child.
         */
        inline int leftChild( int i )
        {
            return 2 * i + 1;
        }

        /**
         * Internal method for heapsort that is used in
         * deleteMax and buildHeap.
         * i is the position from which to percolate down.
         * n is the logical size of the binary heap.
         */
        template <class Comparable>
        void percDown( vector<Comparable> & a, int i, int n )
        {
            int child;
            Comparable tmp;

/* 1*/      for( tmp = a[ i ]; leftChild( i ) < n; i = child )
            {
/* 2*/          child = leftChild( i );
/* 3*/          if( child != n - 1 && a[ child ].word < a[ child + 1 ].word )
/* 4*/              child++;
/* 5*/          if( tmp.word < a[ child ].word )
/* 6*/              a[ i ] = a[ child ];
                else
/* 7*/              break;
            }
/* 8*/      a[ i ] = tmp;
        }
        /**
         * Mergesort algorithm (driver).
         */
        template <class Comparable>
        void mergeSort( vector<Comparable> & a )
        {
            vector<Comparable> tmpArray( a.size( ) );

            mergeSort( a, tmpArray, 0, a.size( ) - 1 );
        }

        /**
         * Internal method that makes recursive calls.
         * a is an array of Comparable items.
         * tmpArray is an array to place the merged result.
         * left is the left-most index of the subarray.
         * right is the right-most index of the subarray.
         */
        template <class Comparable>
        void mergeSort( vector<Comparable> & a,
                   vector<Comparable> & tmpArray, int left, int right )
        {
            if( left < right )
            {
                int center = ( left + right ) / 2;
                mergeSort( a, tmpArray, left, center );
                mergeSort( a, tmpArray, center + 1, right );
                merge( a, tmpArray, left, center + 1, right );
            }
        }

        /**
         * Internal method that merges two sorted halves of a subarray.
         * a is an array of Comparable items.
         * tmpArray is an array to place the merged result.
         * leftPos is the left-most index of the subarray.
         * rightPos is the index of the start of the second half.
         * rightEnd is the right-most index of the subarray.
         */
        template <class Comparable>
        void merge( vector<Comparable> & a, vector<Comparable> & tmpArray,
               int leftPos, int rightPos, int rightEnd )
        {
            int leftEnd = rightPos - 1;
            int tmpPos = leftPos;
            int numElements = rightEnd - leftPos + 1;

            // Main loop
            while( leftPos <= leftEnd && rightPos <= rightEnd )
                if( a[ leftPos ].word <= a[ rightPos ].word )
                    tmpArray[ tmpPos++ ] = a[ leftPos++ ];
                else
                    tmpArray[ tmpPos++ ] = a[ rightPos++ ];

            while( leftPos <= leftEnd )    // Copy rest of first half
                tmpArray[ tmpPos++ ] = a[ leftPos++ ];

            while( rightPos <= rightEnd )  // Copy rest of right half
                tmpArray[ tmpPos++ ] = a[ rightPos++ ];

            // Copy tmpArray back
            for( int i = 0; i < numElements; i++, rightEnd-- )
                a[ rightEnd ] = tmpArray[ rightEnd ];
        }

        /**
         * Quicksort algorithm (driver).
         */
        template <class Comparable>
        void quicksort( vector<Comparable> & a )
        {
            quicksort( a, 0, a.size( ) - 1 );
        }
		template <class Comparable>void quicksort_first(vector<Comparable>&a)
		{
			quicksort_first(a,0,a.size()-1);
			//quicksort_first(a,(a.size()/2),a.size()-1);
		}
		template <class Comparable>void quicksort_first(vector<Comparable>&a,int left,int right)
		{
			  if( left + 10 <= right )
            {
				int pivot_index = first_pivot( a, left, right );
/* 2*/          Comparable pivot =a[pivot_index];

                    // Begin partitioning
/* 3*/          int i = left, j = right - 1;
/* 4*/          for( ; ; )
                {
/* 5*/              while( a[ ++i ].word < pivot.word ) { }
/* 6*/              while( pivot.word < a[ --j ].word ) { }
/* 7*/              if( i < j )
/* 8*/                  swap( a[ i ], a[ j ] );
                    else
/* 9*/                  break;
                }

/*10*/          swap( a[ i ], a[ right - 1 ] );  // Restore pivot

/*11*/          quicksort_first( a, left, i - 1 );     // Sort small elements
/*12*/          quicksort_first( a, i + 1, right );    // Sort large elements
            }
            else  // Do an insertion sort on the subarray
/*13*/          insertionSort( a, left, right );


		}
		template <class Comparable>void quicksort_random(vector<Comparable>&a)
		{
			quicksort_random(a,0,a.size()-1);
		}
		template <class Comparable>void quicksort_random(vector<Comparable>&a,int left,int right)
		{
			      if( left + 10 <= right )
            {
				srand(time(NULL));
				int n=rand();
				int pvt = left + n%(right-left+1);
				swap(a[right], a[pvt]);
/* 2*/          Comparable pivot = partition_pivot( a, left, right );

                    // Begin partitioning
/* 3*/          int i = left, j = right - 1;
/* 4*/          for( ; ; )
                {
/* 5*/              while( a[ ++i ].word < pivot.word ) { }
/* 6*/              while( pivot.word < a[ --j ].word ) { }
/* 7*/              if( i < j )
/* 8*/                  swap( a[ i ], a[ j ] );
                    else
/* 9*/                  break;
                }

/*10*/          swap( a[ i ], a[ right - 1 ] );  // Restore pivot

/*11*/          quicksort_random( a, left, i - 1 );     // Sort small elements
/*12*/          quicksort_random( a, i + 1, right );    // Sort large elements
            }
            else  // Do an insertion sort on the subarray
/*13*/          insertionSort( a, left, right );
			//int index;

		}
        /**
         * Standard swap
         */
        template <class Comparable>
        inline void swap( Comparable & obj1, Comparable & obj2 )
        {
            Comparable tmp = obj1;
            obj1 = obj2;
            obj2 = tmp;
        }
		 template <class Comparable>
        void quicksort( vector<Comparable> & a, int left, int right )
        {
			      if( left + 10 <= right )
            {
/* 2*/          Comparable pivot = median3( a, left, right );

                    // Begin partitioning
/* 3*/          int i = left, j = right - 1;
/* 4*/          for( ; ; )
                {
/* 5*/              while( a[ ++i ].word < pivot.word ) { }
/* 6*/              while( pivot.word < a[ --j ].word ) { }
/* 7*/              if( i < j )
/* 8*/                  swap( a[ i ], a[ j ] );
                    else
/* 9*/                  break;
                }

/*10*/          swap( a[ i ], a[ right - 1 ] );  // Restore pivot

/*11*/          quicksort( a, left, i - 1 );     // Sort small elements
/*12*/          quicksort( a, i + 1, right );    // Sort large elements
            }
            else  // Do an insertion sort on the subarray
/*13*/          insertionSort( a, left, right );

		}

        /**
         * Return median of left, center, and right.
         * Order these and hide the pivot.
         */
		template<class Comparable> const Comparable & partition_pivot(vector<Comparable>&a,int left,int right)
		{
			int pivot,i;
			i=left;
			pivot=right;
			for(int x=left+1;x<=right;x++)//find where the pivot is
			{
				if(a[x].word<a[pivot].word)
				{
					swap(a[x],a[i]);
					i++;
				}

			}
			swap(a[pivot],a[i]);
			return a[i];
		}

		//template<class Comparable>int Random_pivot(vector <Comparable>&a,int low,int high)
		//{
		//	srand(time(NULL));
		//	int n=rand();
		//	int pvt = low + n%(high-low+1);
		//	swap(a[high], a[pvt]);
		//	return partition_pivot(a,low,high);
		//}
	template<class Comparable>int first_pivot(vector<Comparable>&a,int left,int right)
	{
		//Comparable t;
			int pivot,i;
			pivot=left;
			i=right;
			for(int x=left+1;x<=right;x++)//find where the pivot is
			{

				if(a[x].word<a[pivot].word)
				{
					swap(a[x],a[pivot+1]);
					swap(a[pivot],a[pivot+1]);
					pivot++;
				}

			}
			
			return pivot;
	}
	


        template <class Comparable>
        const Comparable & median3( vector<Comparable> & a, int left, int right )
        {
            int center = ( left + right ) / 2;
            if( a[ center ].word < a[ left ].word )
                swap( a[ left ], a[ center ] );
            if( a[ right ].word < a[ left ].word )
                swap( a[ left ], a[ right ] );
            if( a[ right ].word < a[ center ].word )
                swap( a[ center ], a[ right ] );

                // Place pivot at position right - 1
            swap( a[ center ], a[ right - 1 ] );
            return a[ right - 1 ];
        }

        /**
         * Internal quicksort method that makes recursive calls.
         * Uses median-of-three partitioning and a cutoff of 10.
         * a is an array of Comparable items.
         * left is the left-most index of the subarray.
         * right is the right-most index of the subarray.
         */
        

        /**
         * Internal insertion sort routine for subarrays
         * that is used by quicksort.
         * a is an array of Comparable items.
         * left is the left-most index of the subarray.
         * right is the right-most index of the subarray.
         */
        template <class Comparable>
        void insertionSort( vector<Comparable> & a, int left, int right )
        {
            for( int p = left + 1; p <= right; p++ )
            {
                Comparable tmp = a[ p ];
                int j;

                for( j = p; j > left && tmp.word < a[ j - 1 ].word; j-- )
                    a[ j ] = a[ j - 1 ];
                a[ j ] = tmp;
            }
        }

        /**
         * Quick selection algorithm.
         * Places the kth smallest item in a[k-1].
         * a is an array of Comparable items.
         * k is the desired rank (1 is minimum) in the entire array.
         */
        template <class Comparable>
        void quickSelect( vector<Comparable> & a, int k )
        {
            quickSelect( a, 0, a.size( ) - 1, k );
        }


        /**
         * Internal selection method that makes recursive calls.
         * Uses median-of-three partitioning and a cutoff of 10.
         * Places the kth smallest item in a[k-1].
         * a is an array of Comparable items.
         * left is the left-most index of the subarray.
         * right is the right-most index of the subarray.
         * k is the desired rank (1 is minimum) in the entire array.
         */
        template <class Comparable>
        void quickSelect( vector<Comparable> & a, int left, int right, int k )
        {
/* 1*/      if( left + 10 <= right )
            {
/* 2*/          Comparable pivot = median3( a, left, right );

                    // Begin partitioning
/* 3*/          int i = left, j = right - 1;
/* 4*/          for( ; ; )
                {
/* 5*/              while( a[ ++i ].word < pivot.word ) { }
/* 6*/              while( pivot.word < a[ --j ].word ) { }
/* 7*/              if( i < j )
/* 8*/                  swap( a[ i ], a[ j ] );
                    else
/* 9*/                  break;
                }

/*10*/          swap( a[ i ], a[ right - 1 ] );  // Restore pivot

                    // Recurse; only this part changes
/*11*/          if( k <= i )
/*12*/              quickSelect( a, left, i - 1, k );
/*13*/          else if( k > i + 1 )
/*14*/              quickSelect( a, i + 1, right, k );
            }
            else  // Do an insertion sort on the subarray
/*15*/          insertionSort( a, left, right );
        }

#endif