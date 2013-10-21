#include <iostream>
#include <fstream>
#include <exception>
#include <omp.h>
#include <sstream>
#include <string>

using namespace std;

void bubbleSort(int ar[], int size)
{
    int temp;
    for(int i = 0; i < size; i++)
        for(int j = 0; j < size - i - 1; j++)
            if(ar[j] > ar[j + 1])
            {
                temp = ar[j];
                ar[j] = ar[j + 1];
                ar[j + 1] = temp;
            }
}

void insertionSort(int ar[], int size)
{
	int a[100];
	a[0] = ar[0];
	for (int i = 1; i < size; i++)
	{
		int temp = ar[i];
		int j = i - 1;
		while (( a[j] > temp) && (j>=0))
		{
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = temp;
	}

	for (int k = 0; k < size; k++)
	{
		ar[k] = a[k];
	}
}

void merge(int *a, int *b, int low, int pivot, int high)
{
    int h,i,j,k;
    h=low;
    i=low;
    j=pivot+1;
 
    while((h<=pivot)&&(j<=high))
    {
        if(a[h]<=a[j])
        {
            b[i]=a[h];
            h++;
        }
        else
        {
            b[i]=a[j];
            j++;
        }
        i++;
    }
    if(h>pivot)
    {
        for(k=j; k<=high; k++)
        {
            b[i]=a[k];
            i++;
        }
    }
    else
    {
        for(k=h; k<=pivot; k++)
        {
            b[i]=a[k];
            i++;
        }
    }
    for(k=low; k<=high; k++) a[k]=b[k];
}
void mergeSort(int *a, int*b, int low, int high)
{
    int pivot;
    if(low<high)
    {
        pivot=(low+high)/2;
        mergeSort(a,b,low,pivot);
        mergeSort(a,b,pivot+1,high);
        merge(a,b,low,pivot,high);
    }
}

void selectionSort(int *a,int length)
{
	int i,j,min,minat;
	for(i=0;i<(length-1);i++)
	{
		minat=i;
		min=a[i];
		for(j=i+1;j<(length);j++) 
		{
			if(min>a[j])
			{
				minat=j; 
				min=a[j];
			}
		}
		int temp=a[i];
		a[i]=a[minat]; 
		a[minat]=temp;		
	}
}

void radixSort(int arr[],int n)
{
	int bucket[100][100], buck_count[100];
	int i,j,k,r,no_of_passes=0,divisor=1,largest,pass_no;

	largest=arr[0];

	for(i=1;i<n;i++)
	{
		if(arr[i] > largest)
			largest=arr[i];
	}

	while(largest > 0) 
	{
		no_of_passes++;
		largest /= 10000;
	}

	for(pass_no=0; pass_no < no_of_passes; pass_no++){

		for(k=0; k<100; k++)
			buck_count[k]=0; 

		for(i=0;i<n;i++){
			r=(arr[i]/divisor) % 100;
			bucket[r][buck_count[r]++]=arr[i];
		}
		i=0; 

		for(k=0; k<100; k++){
			for(j=0; j<buck_count[k]; j++)
				arr[i++] = bucket[k][j];
		}

		divisor *= 100;
	}
}

void swap(int *x, int *y)
{
	int temp;
	temp=*x;
	*x = *y;
	*y = temp;
}
void heapSort(int a[],int n)
{
	int i,s,f;
	for(i=1;i< n;++i)
	{
		s=i;
		f=(s-1)/2;
		while( a[f]< a[s])
		{
			swap(&a[f],&a[s]);
			s=f;
			if(s==0)
				break;
			f=(s-1)/2;
		}
	}
	for(i=n-1;i>=1;--i)
	{
		swap(&a[0],&a[i]);
		f=0;
		s=1;
		if(i==1)
			break;
		if(i>2)if(a[2]>a[1])s=2;
		while( a[f]< a[s] )
		{ 
			swap(&a[f],&a[s]);
			f=s;
			s=2*f+1;
			if(i>s+1 )if(a[s+1]>a[s])s=s+1;
			if (s>=i)
				break;
		}
	}
}

int main()
{
	cout << "Welcome to SortPlus. Please Select an Option." << endl;
	cout << endl;
	int *arrayToSort;
    int size;

level1:
	cout << "Enter number of items you wish to sort. The maximum is 100:" << endl;

	cin >> size;
	if(cin.fail())
	{
		cin.clear();
		cin.ignore(10000,'\n');
		cout << "Please enter a valid Integer value!" << endl;
		goto level1;
	}
	
	if(size < 2 || size > 100)
	{
		cin.clear();
		cin.ignore(10000,'\n');
		cout << "The Minimum Size is 2 and Maximum Size is 100. Please specify a different size!" << endl;
		cout << endl;
		goto level1;
	}

    arrayToSort = new int[size];
	cout << endl;

level6:
	cout << "Do you wish to enter the Unsorted Numbers by yourself? Y for Yes anything else for No" << endl;
	char resp;
	cin >> resp;
	if(cin.fail()) 
	{
		cout << "Invalid Response" << endl;
		goto level6;
	}

	if(resp == 'Y' || resp == 'y')
	{
		for (int x = 0; x < size; x++)
		{
level2:
			cout << "Enter value for Unordered Item " << x + 1 << ": ";
			cin >> arrayToSort[x];
			if(cin.fail())
			{
				cin.clear();
				cin.ignore(10000,'\n');
				cout << "Please enter a Integer value!" << endl;
				goto level2;
			}
		}
	}
	else
	{
		for (int x = 0; x < size; x++)
		{
level5:
			arrayToSort[x] = rand();
		}
	}     

    cout << endl;

	ofstream myfile;
	double tm = omp_get_wtime();

	std::stringstream ss;
	ss << "Output_" << tm << ".txt";
	std::string s = ss.str();

	myfile.open (s);

    cout << "Before sorting: " << endl;

    myfile << "OUTPUT " << tm << endl;
    myfile << endl;
    myfile << "Before sorting: " << endl;
    
	for (int i = 0; i < size; i++)
    {
        if (i == (size - 1))
		{
            cout << arrayToSort[i];
			myfile << arrayToSort[i];
		}
        else
		{
            cout << arrayToSort[i] << ", ";
            myfile << arrayToSort[i] << ", ";
		}
    }	
	cout << endl;
	myfile << endl;

level4:
	cout << endl;
	cout << "Select a Sort Method" << endl;
	cout << "1. Bubble Sort" << endl;
	cout << "2. Insertion Sort" << endl;
	cout << "3. Merge Sort" << endl;
	cout << "4. Selection Sort" << endl;
	cout << "5. Radix Sort" << endl;
	cout << "6. Heap Sort" << endl;
	cout << endl;

level3:
	int option;
	cin >> option;
	if(cin.fail())
	{
		cin.clear();
		cin.ignore(10000,'\n');
		cout << "Please enter a Digit!" << endl;
		goto level3;
	}

	double start = omp_get_wtime();
	if (option == 1)
	{
		cout << "Utilizing Bubble Sort" << endl;
		myfile << "Utilizing Bubble Sort" << endl;
		bubbleSort(arrayToSort, size);
	}
	else if (option == 2)
	{
		cout << "Utilizing Insertion Sort" << endl;
		myfile << "Utilizing Insertion Sort" << endl;
		insertionSort(arrayToSort, size);
	}
	else if (option == 3)
	{
		cout << "Utilizing Merge Sort" << endl;
		myfile << "Utilizing Merge Sort" << endl;
		int *b;
		b = new int[size];
		mergeSort(arrayToSort,b,0,size-1);
	}
	else if (option == 4)
	{
		cout << "Utilizing Selection Sort" << endl;
		myfile << "Utilizing Selection Sort" << endl;
		selectionSort(arrayToSort, size);
	}
	else if (option == 5)
	{
		cout << "Utilizing Radix Sort" << endl;
		myfile << "Utilizing Radix Sort" << endl;
		radixSort(arrayToSort, size);
	}
	else if (option == 6)
	{
		cout << "Utilizing Heap Sort" << endl;
		myfile << "Utilizing Heap Sort" << endl;
		heapSort(arrayToSort, size);
	}
	else
	{
		cout << "Invalid Option. Please try again." << endl;
		goto level4;
	}
	double end = omp_get_wtime();

    cout << "\nAfter sorting: " << endl;
    myfile << "\nAfter sorting: " << endl;
    for (int j = 0; j < size; j++)
    {
        if (j == (size - 1))
		{
            cout << arrayToSort[j];
			myfile << arrayToSort[j];
		}
        else
		{
            cout << arrayToSort[j] << ", ";
            myfile << arrayToSort[j] << ", ";
		}
    }

	double elapsed = end - start;
	cout << endl;
	cout << "Time elapsed: " << elapsed << "ms";
	cout << endl;
	cout << "Output File Name: " << s;

	myfile << endl;
	myfile << "Time elapsed: " << elapsed << "ms";
	myfile.close();

    cin.ignore();
    cin.get();
    delete arrayToSort;
	cout << "Do you wish to Continue? Press Y for Yes and any other key to Close" << endl;
	char res;
	cin >> res;
	if(res == 'Y' || res == 'y')
	{
		cout << endl;
		cout << endl;
		
		goto level1;
	}
	else
		return 0;
}