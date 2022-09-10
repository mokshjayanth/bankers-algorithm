#include<iostream>
using namespace std;

//Matrix class
class Matrix{
    public: 
    int** arrayPtr;
    int m,n;

    public:
    Matrix(int j,int k)  //Parametized Dynamic Constructor
    {
        m=j;n=k;
        arrayPtr= new int*[m];
        for(int i=0;i<m;i++)
        arrayPtr[i]=new int [n];
        for(int i=0;i<m;i++)
        {
        for(int j=0;j<n;j++)
        arrayPtr[i][j]=0;
        }
    }
    friend istream& operator>>(istream& ,Matrix);
    friend ostream& operator<<(ostream& ,Matrix);
    Matrix operator-(Matrix);    
};                                                //END OF CLASS

//1.For overloading >> Operator
istream& operator>>(istream& in,Matrix obj){
    for(int i=0;i<obj.m;i++){
        cout<<'P'<<'['<<(i+1)<<']'<<':';
        for(int j=0;j<obj.n;j++){
            in>>obj.arrayPtr[i][j];
            if(obj.arrayPtr[i][j]<0)throw "YOU HAVE TO ENTER POSITVE VALUE ONLY, PLEASE RUN THE PROGRAM AGAIN AND GIVE A POSTIVE VALUE.\n";
            }
    }
    return(in);
}
//2.For overloading << Operator
ostream& operator<<(ostream& out,Matrix obj){
    for(int i=0;i<obj.m;i++){
        for(int i=0;i<obj.n;i++)out<<"-----------------";out<<"\n"; // For table design
        out<<"|";
        for(int j=0;j<obj.n;j++){
            out<<"\t"<<obj.arrayPtr[i][j]<<"\t"<<"|";
            }
        out<<"\n";
    }
    for(int i=0;i<obj.n;i++)out<<"-----------------";out<<"\n"; // For table design
    return(out);
}
//3. For overloading - operator
Matrix Matrix :: operator-(Matrix obj){
    Matrix temp(m, n);
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++)temp.arrayPtr[i][j]=arrayPtr[i][j]-obj.arrayPtr[i][j];
    }
    return temp;
}
