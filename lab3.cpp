#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>


using namespace std;

const unsigned int str = 154;
const unsigned int stolb = 14;
double h = 0.1;
int a = 0, b = 11;


double my_lagrange(int a, int b, double x, double x_arr[], double* z) {
	double sum = 0;
	for (int i = a; i <= b; i++) {
		double l = 1;
		for (int j = a; j <= b; j++)
			if (j != i)
				l *= (x - x_arr[j]) / (x_arr[i] - x_arr[j]);
		sum += z[i] * l;
	}
	ofstream Tochky;
	Tochky.open("Tochki.txt");
	for (int i = 0; i < 12; i++) Tochky << x_arr[i] << " " << z[i] << endl;
	Tochky.close();
	return sum;
	
	return sum;
}

double d1(double m0, double m1) {
	return m1 - m0;

}
double d2(double m0, double m1, double m2) {

	return m2 - 2 * m1 + m0;
}

double d3(double m0, double m1, double m2, double m3) {

	return m3 - 3 * m2 + 3 * m1 - m0;
}

double d4(double m0, double m1, double m2, double m3, double m4) {

	return m4 - 4 * m3 + 6 * m2 - 4 * m1 + m0;
}
double d5(double m0, double m1, double m2, double m3, double m4, double m5) {

	return m5 - 5 * m4 + 10 * m3 - 10 * m2 + 5 * m1 - m0;
}
double d6(double m0, double m1, double m2, double m3, double m4, double m5, double m6) {

	return m6 - 6 * m5 + 15 * m4 - 20 * m3 + 15 * m2 - 6 * m1 + m0;
}

int factor(int n)
{
	int k = 1;
	for (int i = 2; i <= n; i++) k *= i;
	return k;
}
double delta(double i, double j, int n, double* y)
{
	if (n == 0) return i - j;
	else if (n == 1) return (y[(int)i] - y[(int)j]);
	else return delta(delta(i + 1, j + 1, n - 1, y), delta(i, j, n - 1, y), 0, y);
}
double firstNewton(double x, int y1, int y2, int month, double** tempmonth)
{
	int* yearind = new int[y2 - y1 + 1]; 
	for (int i = y1; i <= y2; i++)  yearind[i - y1] = i - y1;
	double* temp = new double[y2 - y1 + 1]; 
	for (int i = y1; i <= y2; i++) temp[i - y1] = tempmonth[i][month];
	double sum = 0.0;
	double fx;
	for (int i = 0; i <= 5; i++)
	{
		if (i == 0) { sum += temp[0]; }
		else
		{
			fx = 1;
			for (int j = 0; j < i; j++) fx *= (x - (double)yearind[j]);
			fx /= factor(i);
			fx *= delta(1, 0, i, temp);
		}
		sum += fx;
	}
	ofstream Tochky;
	Tochky.open("Tochki2.txt");
	for (int i = 0; i < 6; i++) Tochky << yearind[i] << " " << temp[i] << endl;
	Tochky.close();
	return sum;
}
double secondNewton(double x, int y1, int y2, int month, double** tempmonth)
{
	int* yearind = new int[y2 - y1 + 1]; /// индекс строки года
	for (int i = y1; i <= y2; i++)  yearind[i - y1] = i - y1;
	double* temp = new double[y2 - y1 + 1]; ///значения температур в выбранном месяце
	for (int i = y1; i <= y2; i++) temp[i - y1] = tempmonth[i][month];
	double sum = 0.0;
	double fx;
	for (int i = 0; i <= 5; i++)
	{
		fx = 1;
		if (i == 0) { sum += temp[5]; }
		else {
			for (int j = 5; j >= 5 - i + 1; j--)  fx *= (x - (double)yearind[j]);
			fx /= factor(i);
			fx *= delta(5 - i + 1, 5 - i, i, temp);
			sum += fx;
		}
	}
	ofstream Tochky;
	Tochky.open("Tochki3.txt");
	for (int i = 0; i < 6; i++) Tochky << yearind[i] << " " << temp[i] << endl;
	Tochky.close();
	return sum;
}
double Steppolinom(double x, int s,  double** koef)
{
double y=0.0; 
for (int i=0; i<=s; i++)  y+=koef[i][0]*pow(x, i);
return y;
}
void inversion(double **A, int N)
{double temp;
 double **E = new double *[N];
   for (int i = 0; i < N; i++)
     E[i] = new double [N];
   for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
     {E[i][j] = 0.0;
       if (i == j)
        E[i][j] = 1.0;
        }
   for (int k = 0; k < N; k++)
    {temp = A[k][k];
       for (int j = 0; j < N; j++)
        {A[k][j] /= temp;
         E[k][j] /= temp;}
   for (int i = k + 1; i < N; i++)
      {temp = A[i][k];
         for (int j = 0; j < N; j++)
            {A[i][j] -= A[k][j] * temp;
             E[i][j] -= E[k][j] * temp;}
       }
     }
 
   for (int k = N - 1; k > 0; k--)
    {for (int i = k - 1; i >= 0; i--)
      {temp = A[i][k];
          for (int j = 0; j < N; j++)
            {A[i][j] -= A[k][j] * temp;
                E[i][j] -= E[k][j] * temp;}
      }
    }
 
   for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      A[i][j] = E[i][j];
  for (int i = 0; i < N; i++)
        delete [] E[i];
 
    delete [] E;
}
void multiply(double**A, double**B,double**C, int c, int d, int f)
{
 for (int i=0; i<c; i++)
 { for (int j=0; j<f; j++)
	 {for( int r=0; r<d; r++)
		C[i][j]+=A[i][r]*B[r][j];
	 }
}
}

void print(double** temp, int n, int k)
{for (int i=0; i<n; i++)
{cout<<i<<"\t |";
for (int j=0; j<k; j++) cout<<temp[i][j]<<"\t |";
cout<<endl;}
}

int main() {
	
	double ip;
int j;
string line1;
double** temp = new double*[154];
for (int i=0; i<154; i++)  
temp[i] = new double[14];  
	
for (int i=0; i<154; i++) 
for (int j=0; j<14; j++) 
temp[i][j]=0;
int n =0;
ifstream file;
file.open("21.csv");
if(!file.is_open())
cout<<"Dont open"<<endl;
else {
while (!file.eof())
{ getline(file,line1);
	if (n!=0)
	{
	 for (long long unsigned int i=0; i<line1.size(); i++) 
	 { if (line1[i]==',') line1[i]=' ';};
	 stringstream ss(line1);
	 j=0;
	 while ((ss >> ip) && j<14)
	  {temp[n-1][j]=ip;
       j++;}
     }
    n++;
}
 n=277;
          }
          
          
	fstream fin;
	fin.open("21.csv", ios::in);

	double** y_arr = new double* [str];
	for (int count = 0; count < 154; count++)
		y_arr[count] = new double[stolb];

	string line, word;
	getline(fin, line);
	for (int count_row = 0; count_row < 154; count_row++) {
		getline(fin, line);
		stringstream s(line);
		for (int count_column = 0; count_column < 14; count_column++) {
			getline(s, word, ',');
			y_arr[count_row][count_column] = atof(word.c_str());
		}
	}

	ofstream fout;
	fout.open("Lagr.txt");

	int c;
	cout << "Choose the stolb" << endl;
	cin >> c;
	int count9 = 0;
	for (int i = 0; i < 154; i++) {
		if (y_arr[i][c] > 900)
			count9++;
	}

	double* z = new double[154 - count9];

	int p = 0;
	for (int i = 0; i < 154; i++) {
		if (y_arr[i][c] < 999.9) {
			z[p] = y_arr[i][c];
			p++;
		}
	}
	
	double x_arr[str];


	for (int l = 0; l < 154; l++) {
		x_arr[l] = l;
	}
	for (double x = a; x <= b; x += h) {
		cout << "f(" << x << ") = "
			<< my_lagrange(a, b, x, x_arr, z) << endl;
		fout << x << " " << my_lagrange(a, b, x, x_arr, z) << endl;
	}
	ofstream fout3;
	fout3.open("Tochki4.txt");
	for (int x = 0; x < 141; x++) {
		fout3 << x << " " << z[x] << endl;
	}
	cout << endl << endl;
	ofstream fout1;
	fout1.open("1Newton.txt");
	for (double i = 0; i <= 5; i += 0.1)
	{
		double f;
		int m=7;
		f = firstNewton(i, 120, 150, m, temp);
		fout1 << i << "\t " << f << endl;
	}
	fout1.close();

	cout << endl << endl;
	ofstream fout2;
	fout2.open("2Newton.txt");
	for (double i = 0; i <= 5; i += 0.1)
	{
		double f;
		int m=7;
		f = secondNewton(i, 19, 100, m, temp);
		fout2 << i << "\t " << f << endl;
	}
	fout2.close();
	
	//5
	ofstream file2;
file2.open("pol.txt");
int s,month=c;
cout<<"Enter power of polinom (do 5): ";
cin>>s;


vector<double>  temperature;
vector<int> stroki;
int nstrok=0;
for (int i=0; i<154; i++) if (temp[i][month]!= 999.9) { temperature.push_back(temp[i][month]); nstrok++; stroki.push_back(nstrok); }
cout<<"Amount prav temp: "<<temperature.size()<<endl;
int n1 = stroki.size();

double**  secondmat=new double*[s+1];
for(int i=0; i<s+1; i++) secondmat[i]= new double[1];
for(int i=0; i<s+1; i++) secondmat[i][0]= 0;
for (int i=0; i<s+1; i++)
{for (int j=0; j<n1; j++) secondmat[i][0]+=temperature[j]*pow(stroki[j], i);}

double** firstmat = new double*[s+1];
for (int i=0; i<s+1; i++) firstmat[i]=new double[s+1];
for (int i=0; i<s+1; i++) 
{
for (int j=0; j<s+1; j++)
{
if (i==0 && j==0) firstmat[i][j]=n1;
else {for(int k=0; k<n1; k++) firstmat[i][j]+=pow(stroki[k], i+j);}
}}

double** koef = new double*[s+1];
for (int i=0; i<s+1; i++) koef[i] =new double[1];
for (int i=0; i<s+1; i++) koef[i][0] =0.0;

inversion(firstmat, s+1);

multiply(firstmat, secondmat, koef, s+1, s+1, 1);
cout<<"Matrix coef.: "<<endl;
print(koef, s+1, 1);
cout<<endl;
int k =stroki[n1-1];
for (double i=0; i<k; i+=0.1)
 file2<<i<<"\t  "<<Steppolinom(i,s, koef)<<endl;
file2.close();

	fout.close();
	fout1.close();
	fout2.close();
	fout3.close();
	delete[] * y_arr;
	delete[] z;
	return 0;

}
