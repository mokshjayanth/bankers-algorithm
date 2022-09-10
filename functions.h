#include "class.h"
#include<fstream>

//Global Variables
int checkSafetyFlag, pros;
int safeSeq[15]; // To store safe sequence 

//1. A function to display header in the console
ostream& header(ostream& out){
    out<<"--------------------*A MINI PROJECT ON IMPLEMENTATION OF BANKER'S ALGORITHM*--------------------\n\n";
    out<<"/* QUICK NOTE: ROWS IN TABLE REPRESENT PROCESSES(P0, P1, P2, ...., Pm) AND THE COLUMNS REPRESENT THE RESOURCES (R0, R1, R2, ....., Rn) */\n\n\n";
    out<<"/*THIS TABLE IS JUST FOR REFERENCE,THE TABLE IS FOR 3 PROCESSES AND 3 RESOURCES.*/\n\n";

    //Design Reference Table
    int i =0;
        out<<"\tR1\t\tR2\t\tR3\t\n";
      for(i=0;i<3;i++){
        out<<"   ----------------------------------------------\nP"<<(i+1);
        out<<"|";
        for(int j=0;j<3; j++) {out<<"\t\t|";}
        out<<"\n";
    }
    out<<"   ----------------------------------------------\n";
    out<<"\n\n";
    return out;
}

//2. A fuction to display footer in the console
ostream& footer(ostream& out){
    out<<"\n\n--------------------*THANK YOU AND HAVE A GREAT DAY*--------------------\n\n";
    return out;
}

// 3. Function to find the system is in safe state or not 
void checkSafety(Matrix allocationMatrix, Matrix needMatrix, Matrix availableMatrix,int process,int resources) 
{ 
    pros=process;
    //Initializing checkSafetyFlag to 0.
    checkSafetyFlag=0;
    
    // Mark all processes as infinish 
    bool finish[pros] ;for(int i=0;i<pros;i++)finish[i]=0;
  
  
    // Make a copy of available resources i.e WORK = AVAILABLE
    int work[resources]; 
    for (int i = 0; i < resources ; i++) 
        work[i] = availableMatrix.arrayPtr[0][i]; 
  
    // While all processes are not finished 
    // or system is not in safe state. 
    int count = 0; 
    while (count < pros) 
    { 
        // Find a process which is not finish and 
        // whose needs can be satisfied with current 
        // work[] resources. 
        bool found = false; 
        for (int p = 0; p < pros; p++) 
        { 
            // First check if a process is finished, 
            // if no, go for next condition 
            if (finish[p] == 0) 
            { 
                // Check if for all resources of 
                // current P need is less 
                // than work 
                int j; 
                for (j = 0; j < resources; j++) 
                    if (needMatrix.arrayPtr[p][j] > work[j]) 
                        break; 
  
                // If all needs of p were satisfied. 
                if (j == resources) 
                { 
                    // Add the allocated resources of 
                    // current P to the available/work 
                    // resources i.e.free the resources 
                    for (int k = 0 ; k < resources ; k++) 
                        work[k] += allocationMatrix.arrayPtr[p][k]; 
  
                    // Add this process to safe sequence. 
                    safeSeq[count++] = p; 
  
                    // Mark this p as finished 
                    finish[p] = 1; 
  
                    found = true; 
                } 
            } 
        } 
  
        // If we could not find a next process in safe 
        // sequence. 
        if (found == false) 
        { 
            throw "THERE IS A DEADLOCK POSSIBILITY. THE SYSTEM IS NOT IN SAFE STATE.\n";//Exception
            return;
        } 
    } 
  
    // If system is in safe state then 
    // safe sequence will be as below 
    cout << "SYSTEM IS IN SAFE STATE.\nSAFE"
         " SEQUENCE IS => "; 
    int i;
    for (i = 0; i < pros-1 ; i++) 
        cout <<"P"<<"["<< (safeSeq[i]+1)<< "]"<<" -> "; 
     cout <<"P"<<"["<< (safeSeq[i]+1) << "]"<<endl;
    //Initailizing checkSafetyFlag to 1.
    checkSafetyFlag=1;
}

// 4. A Function to write data to a file.

void writeToFile(Matrix availableMatrix, Matrix allocationMatrix, Matrix maxMatrix, Matrix needMatrix){
    fstream BankersFile;
    BankersFile.open("BankersFile.txt", ios::out);
    if (!BankersFile) {
		cout << "Error: Failed To Open BankersFile.\n ";
        return;
	}

    header(BankersFile);                                    //Adds HeaderTemplate to the file
    BankersFile<< "AVAILABLE MATRIX:\n"<< availableMatrix;
    BankersFile<<"ALLOCATION MATRIX:\n"<< allocationMatrix;
    BankersFile<<"MAX MATRIX:\n"<<maxMatrix;
    BankersFile<<"NEED MATRIX:\n"<<needMatrix;
   

    if(checkSafetyFlag){

        BankersFile << "SYSTEM IS IN SAFE STATE.\nSAFE"
         " SEQUENCE IS => "; 
         int i;
         for (i = 0; i < pros-1 ; i++) 
            BankersFile <<"P"<<"["<< (safeSeq[i]+1) << "]"<<" -> "; 
        BankersFile <<"P"<<"["<< (safeSeq[i]+1) << "]"<<endl;
         
    }
    else BankersFile<<"THERE IS NO POSSIBLE SAFE SEQUENCE, HENCE THE SYSTEM WILL IN THE STATE OF  DEADLOCK.\n";

    footer(BankersFile);                //Adds FooterTemplate to the file

    BankersFile.close();
}