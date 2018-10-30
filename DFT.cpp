//----------------------------------------------------------
//program:DFT()discrete fourier transform
//author:Renzhi Xue
//course:cs 427
//date: 2018/10/29
//assignment: #2
//description: this program takes a dat file with wave infomation 
//             by using discrete fourier transform to find out what  
//             is the main frequency.
//----------------------------------------------------------




#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <complex>
#include <valarray>
using namespace std;


const double PI = 3.14159265359;

int main()
{
	string filename;
	int n, k, N; // indices for time and frequency domains
	int sample_rate; // sample rate
	ifstream infile; // file input
	size_t found1, found2; // var for dat file process
	string raw_data, first_number,second_number; // var for .dat file 
	//cout << "enter the sample name(.dat) :" << endl;
	//cin >> filename;
	//infile.open(filename);
	infile.open("sample.dat");
	//find the sample rate in the .dat file
	getline(infile, raw_data); 
	found1 = raw_data.find_last_of(" "); 
	sample_rate = stoi(raw_data.substr(found1));

	N = sample_rate / 2 ; // Nyquist frequency point
	double *time = new double[N];          // time 
	double *Amplitude = new double[N];    // amplitude of the wave
	getline(infile, raw_data); // seconed line not important (channels)

	for (int i = 0; i < N; i++){
		
		getline(infile, raw_data); // get one line data
		found1 = raw_data.find_first_of("0123456789");  // break down the data in to useful number 
		raw_data = raw_data.substr(found1);
		found1 = raw_data.find_first_of(" ");
		first_number = raw_data.substr(0, found1);
		raw_data = raw_data.substr(found1);
		found2 = raw_data.find_first_of("0123456789");
		raw_data = raw_data.substr(found2);
		found2 = raw_data.find_first_of(" ");
		second_number = raw_data.substr(0, found2); // end of the break down 
		
		Amplitude[i] = stod(second_number); //write the amplitude number into array
		
	}
	// based on the youtube video https://www.youtube.com/watch?v=mkGsMWi_j4Q 
	double *X_re = new double[N]; // X real number in DFT formular
	double *X_im= new double[N]; // X imaginary number in the DFT formular
	double *X = new double[N]; // the magnitudes of frequency
	double angle;
	for (k = 1; k < N; ++k) 
	{
		
		X_re[k] = 0;
		X_im[k] = 0;
		for (n = 0; n < N; ++n)
		{
			angle = n * k * PI * 2 / N; 
			X_re[k] += Amplitude[n] * cos(angle); //calculate real part of X[k]
			X_im[k] += Amplitude[n] * sin(angle); //calculate Imaginary part of X[k]


		}
		//magnitudes of kth frequency 
		X[k] = sqrt( pow(X_re[k],2)  + pow(X_im[k],2));
		
		if (X[k]> 1)
		{

			cout <<"the frequency is:"<< k << " the amplitude :" << X[k]/sample_rate << endl;

		}
		
	}
	
	infile.close();
	system("pause");
	return 0;
}

