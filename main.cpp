#include "functions.h"
#include<unistd.h>

int main(){
system("clear"); //Clears the console

    int pros, resources, choice=1;
    header(cout);                //Adds a header to the console
    try{
    cout<<"ENTER THE NUMBER OF PROCESSES:\t";                      //Accepting User input
    cin>>pros;                
    if(pros<=0){throw "YOU HAVE TO ENTER POSITVE VALUE ONLY, PLEASE RUN THE PROGRAM AGAIN AND GIVE A POSITIVE VALUE.\n";}  //Exception                                                          
    cout<<"ENTER THE NUMBER OF TYPES OF RESOURCES('A', 'B', 'C', ...) AVAILABLE:\t";  
    cin>>resources;
    if(resources<=0){throw "YOU HAVE TO ENTER POSITVE VALUE ONLY, PLEASE RUN THE PROGRAM AGAIN AND GIVE A POSTIVE VALUE.\n";} //Exception
    }catch(const char* inputMsg){
        cerr<<inputMsg<<endl;return 0;
    }

    Matrix allocationMatrix(pros, resources);           //Creating Matrix Objects
    Matrix maxMatrix(pros, resources);
    Matrix availableMatrix(1, resources);
    Matrix needMatrix(pros, resources);

    try{                                                //Exception
    cout<<"ENTER THE ELEMENTS FOR ALLOCATION MATRIX:\n";
    cin>>allocationMatrix;
    cout<<"ENTER THE ELEMENTS FOR MAX MATRIX:\n";
    cin>>maxMatrix;
    cout<<"ENTER THE ELEMENTS FOR AVAILABLE MATRIX:\n";
    cin>>availableMatrix;
    }catch(const char* matrixMsg){
        cerr<<matrixMsg<<endl;return 0;
    }
    while(choice){                                      //Bigger and outermost loop
    cout<<"DISPLAYING YOUR PROBLEM'S DATA:\n";
    cout<<"AVAILABLE MATRIX:\n";
    cout<<availableMatrix;
    cout<<"ALLOCATION MATRIX:\n";
    cout<<allocationMatrix;
    cout<<"MAX MATRIX:\n";
    cout<<maxMatrix;
    cout<<"NEED MATRIX:\n";
    needMatrix = maxMatrix - allocationMatrix;   //Calculating Need matrix
    cout<<needMatrix;
try{
    //Check whether the system is in DeadLock State, if not generate safe sequence.
    checkSafety(allocationMatrix, needMatrix, availableMatrix,pros,resources);
}catch (const char* msg) {
     cerr << msg << endl;
     return 0;
   }
    //Here the Resource Request Algorithm starts
    cout<<"DO YOU WISH TO MAKE CHANGES TO PROCESS'S REQUEST? ENTER 1 TO PROCEED OR ENTER 0 TO QUIT.\n";
    cin>>choice;
    if(choice){

        int val,proNum;
        cout<<"----------------------------------------\n";
		cout<<"\n\nSELECT THE BELOW OPERATIONS:\n\n";
		cout<<"1.CHANGE MAX OF THE PROCESS: \n";
		cout<<"2.CHANGE ALLOCATION OF THE PROCESS\n";
		cout<<"3.CHANGE THE INTIAL AVAILABLE RESOURCES\n";
		cout<<"4.EXIT\n\n";
        cout<<"----------------------------------------\n";

        do{
            cout<<"ENTER YOUR NUMBER: ";
            cin>>val;
        switch(val){
		case 1:
		{
			cout<<"\n\nEnter Process No: ";
			cin>>proNum;
			cout<<"\nEnter New Max for P["<<proNum<<"]: ";
			for(int i=0;i<resources;i++)
                cin>>maxMatrix.arrayPtr[proNum][i];
                break;
		}
		case 2:
		{
			cout<<"\n\nEnter Process No: ";
			cin>>proNum;
			cout<<"\nEnter New Allocation for P["<<proNum<<"]: ";
			for(int i=0;i<resources;i++)
                cin>>allocationMatrix.arrayPtr[proNum][i];
                break;
		}
		case 3:
		{
			cout<<"\nEnter Initial Available Resources: ";
			for(int i=0;i<resources;i++)
                cin>>availableMatrix.arrayPtr[0][i];
                break;
		}
		case 4: break;
        default: cout<<"ENTER A VALID CHOICE.\n";
        }
    }while(val!=4);
    }
    else if (!choice) break;
    else {cout<<"PLEASE ENTER A VALID CHOICE.\n";break;}
    }

    //writing all the contents and results to BankersFile
    writeToFile(availableMatrix, allocationMatrix, maxMatrix, needMatrix);

    footer(cout);           //Adds a Footer to the console.

    return 0; //END OF THE MAIN FUNTION
}