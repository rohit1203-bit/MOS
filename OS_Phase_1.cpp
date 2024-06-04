// Phase-I
#include <bits/stdc++.h>
using namespace std;
int IC[2];
string main_memory[100][4], R[4], IR[4], buff;
bool C;
ifstream myfile;

void load();
void init();
void startExecution();
void MOS(int);
void READ();
void WRITE();
void TERMINATE();
void executeUserProgram();

void init()
{
    for (int i = 0; i < 100; i++){
        for (int j = 0; j < 4; j++){
            main_memory[i][j] = "*";
        }
    }
    for (int i = 0; i < 4; i++){
        R[i] = "*";
        IR[i] = "*";
    }
    IC[0] = 0;
    IC[1] = 0;
    C = false;
}

void load()
{
    int mem_row = 0;
    while (myfile){
        getline(myfile, buff);
        string s = buff.substr(0, 4);
        if (s == "$AMJ"){
            init();
        }
        else if(s=="$DTA"){
            startExecution();
        }
        else if (s == "$END")
        {
            init();
        }
        else if (s!="$AMJ" && s!="$DTA" && s != "$END"){
            //int mem_row = 0;
            int j=0;
            if(buff.size()>40){
                cout << "Program card exceeded limit - 40 bytes";
                exit(0);
            }
            for (int i = 0; i < buff.size(); i++)
            {
                if(j==4){
                    j=0;
                    mem_row++;
                }
                if(buff[i]=='H'){
                    int k=1;
                    main_memory[mem_row][j]=buff[i];
                    for(k=1;k<=3;k++){
                        main_memory[mem_row][k]='*';
                    }
                    j=k-1;
                }
                else 
                    main_memory[mem_row][j]=buff[i];
                j++;
            }
            mem_row=mem_row+1;
        }
        else
            exit (0);
    }
}

void startExecution(){
    IC[0]=0;
    IC[1]=0;
    executeUserProgram();
    
}

void executeUserProgram(){
    int si=0;
    
    while(1){
        int row=IC[0]*10+IC[1];
        for(int i=0;i<4;i++)
            IR[i]=main_memory[row][i];


        for (int i = 0; i < 4; i++){
            cout << "IR[" << i << "] " << IR[i] << "  ";
        }
        cout << "\nIC:: ";
        for (int i = 0; i < 2; i++){
            cout << "IC[" << i << "] " << IC[i] << "  ";
        }
        cout << "\n\n";
        
        if(IC[1]==9){
            IC[0]=IC[0]+1;
            IC[1]=0;
        }
        else
            IC[1]=IC[1]+1;
        

        string inst=IR[0]+""+IR[1];

        if(inst=="LR"){
            for (int i = 0; i < 4; i++){
                R[i] = main_memory[stoi(IR[2])*10+stoi(IR[3])][i];
            }
        }

        else if(inst == "SR"){
            for (int i = 0; i < 4; i++){
                main_memory[stoi(IR[2])*10+stoi(IR[3])][i] = R[i];
            }
        }

        else if(inst == "CR"){
            int flag = 0;
            for (int i = 0; i < 4; i++){
                if (main_memory[stoi(IR[2])*10+stoi(IR[3])][i] == R[i])
                    flag++;
            }
            if (flag == 4)
                C = true;
            else
                C = false;
        }

        else if(inst == "BT"){
            if (C == true){
                IC[0] = stoi(IR[2]);
                IC[1] = stoi(IR[3]);
            }
            
        }

        else if(inst == "GD"){
            //getline(myfile,buff);
            si=1;
            MOS(si);
        }
        else if(inst == "PD"){
            si=2;
            MOS(si);   
        }
        else if(inst == "H*"){
            
            si=3;
            MOS(si);
        }
        else
            break;
        //break;

    }
}

void READ(){
    IR[3]='0';
    getline(myfile,buff);
    int x = stoi(IR[2])*10+stoi(IR[3]);

    int j=0;
    //cout << x<<endl;
    if(buff.size()>40){
        cout << "Data card exceeded limit - 40 bytes";
        exit(0);
    }
    for (int i = 0; i < buff.size(); i++){
        if(j==4){
        j=0;
        x++;
        }
        main_memory[x][j]=buff[i];
        j++;
    }
}

void WRITE(){
    ofstream myWfile;
    ifstream myRfile;
    myRfile.open("output.txt");
    myWfile.open("output.txt",ios::app);
    if(myRfile.is_open())
        myWfile << "";
    
    IR[3]='0';
    int x = stoi(IR[2])*10+stoi(IR[3]);
    cout << endl;
    for (int i = 0; i < 10; i++){
        for(int j=0;j<4;j++){
            cout << main_memory[x][j];
            myWfile << main_memory[x][j];
        }
        cout << endl;
        
        x++;
    }
    myWfile<<endl;
    myRfile.close();
    myWfile.close();
}

void TERMINATE(){
    cout << endl;
    for (int i = 0; i < 100; i++){
        cout << "M[" << i << "] ";
        for (int j = 0; j < 4; j++){
            cout << main_memory[i][j] << " ";
        }
        cout << endl;
    }
    ofstream myWf;
    myWf.open("output.txt",ios::app);
    myWf<<"\n\n";
    myWf.close();
    load();
}

void MOS(int si){
    switch(si){
        case 1:
            READ();
        break;
        case 2:
            WRITE();   
        break;
        case 3:
            TERMINATE();
        break;
    }
}


int main()
{
    myfile.open("input.txt");

    ofstream myFfile;
    myFfile.open("output.txt");
    myFfile<<"";
    myFfile.close();
    load();

    myfile.close();
}