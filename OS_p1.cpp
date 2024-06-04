// Phase-1
#include <bits/stdc++.h>
using namespace std;
int IC[2];
string main_memory[100][4], R[4], IR[4], buff;
bool C;
ifstream myfile;
//ofstream myWfile;

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
    //string buff;
    // ifstream myRFile;
    // myfile.open("input.txt");
    // myRFile.open("input.txt");
    // myRFile << "$AMJ000100030001" << endl;
    // myRFile << "GD10PD10H" << endl;
    // myRFile << "$DTA" << endl;
    // myRFile << "Hello" << endl;
    // myRFile << "$$END0001" << endl;
    int mem_row = 0;
    while (myfile){
        getline(myfile, buff);
        string s = buff.substr(0, 4);
        if (s == "$AMJ"){
            // cout << s;
            init();
        }
        //getline(myfile,buff);
        //s=buff.substr(0,4);
        else if(s=="$DTA"){
            // getline(myfile,buff);
            // for(int i=0;i<buff.size();i++){
            //     cout << buff[i];
            // }
            startExecution();
        }
        //getline(myfile, buff);
        //s = buff.substr(0, 4);
        else if (s == "$END")
        {
            //cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nHI";
            init();
            // getline(myfile,buff);
            // if(buff=="")
            //     exit (0);
            // end-while loop
        }
        else if (s!="$AMJ" && s!="$DTA" && s != "$END"){
            //getline(myfile, buff);
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
                // if (buff[i] != 'H')
                // {
                //     main_memory[x][0] = buff[i];
                //     main_memory[x][1] = buff[i + 1];
                //     main_memory[x][2] = buff[i + 2];
                //     main_memory[x][3] = buff[i + 3];
                //     x++;
                //     i += 3;
                // }
                // else
                // {
                //     main_memory[x][0] = buff[i];
                //     x++;
                // }
            }
            mem_row=mem_row+1;
            // for (int i = 0; i < 4; i++){
            //     cout << "IR[" << i << "] " << IR[i] << "  ";
            // }
            // cout << endl;
            // for (int i = 0; i < 100; i++)
            // {
            //     cout << "M[" << i << "] ";
            //     for (int j = 0; j < 4; j++)
            //     {
            //         cout << main_memory[i][j] << " ";
            //     }
            //     cout << '\n';
            // }
        }
        else 
            exit (0);
    }
    // myfile.close();
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
            //int x = stoi(IR[2])*10;
            //int j=0;
            for (int i = 0; i < 4; i++){
                R[i] = main_memory[stoi(IR[2])*10+stoi(IR[3])][i];
                //j++;
            }
        }

        else if(inst == "SR"){
            //int j=0;
            for (int i = 0; i < 4; i++){
                main_memory[stoi(IR[2])*10+stoi(IR[3])][i] = R[i];
                //j++;
            }
        }

        else if(inst == "CR"){
            int flag = 0;
            for (int i = 0; i < 4; i++){
                if (main_memory[stoi(IR[2])*10+stoi(IR[3])][i] == R[i])
                    flag++;
                //cout << R[i] << "<---->" << main_memory[stoi(IR[2])*10][stoi(IR[3])+j] <<endl;

                //j++;
            }
            //cout << "\n" << flag << endl;
            if (flag == 4){
                //cout << "HIHIHI";
                C = true;
            }
            else
                C = false;
        }

        else if(inst == "BT"){
            if (C == true){
                //cout << "HIHIHIHIHIHIHIHIHI";
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
    int x = stoi(IR[2])*10;

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

    //cout << "ROHIT";
}

void WRITE(){
    //cout << "JADHAV\n";
    ofstream myWfile;
    ifstream myRfile;
    myRfile.open("output.txt");
    myWfile.open("output.txt",ios::app);
    if(myRfile.is_open())
        myWfile << "";

    //myWfile << "";
    
    IR[3]='0';
    //getline(myfile,buff);
    int x = stoi(IR[2])*10;
    //cout<<"HI" << " " << x;
    //int j=0;
    //cout << x<<endl;
    cout << endl;
    for (int i = 0; i < 10; i++){
        for(int j=0;j<4;j++){
            cout << main_memory[x][j];
            myWfile << main_memory[x][j];
        }
        cout << endl;
        
        x++;
        // if(j==4){
        // j=0;
        // x++;
        // }
        // main_memory[x][j]=buff[i];
        // j++;
    }
    //myWfile.close();

    // ofstream myf;
    // myf.open("output.txt",ios::app);
    // myf<<"\n\n\nrohit this is done";
    // myf.close();
    myWfile<<endl;
    myRfile.close();
    myWfile.close();
}

void TERMINATE(){
    //cout << "\n\n\n\nHI\n\n\n\n\n";
    //myWfile.open("output.txt");
    //myWfile << "\n\n";
    // for (int i = 0; i < 4; i++){
    //             cout << "IR[" << i << "] " << IR[i] << "  ";
    //         }
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
    // ifstream myWFile;
    // myWFile.open("output.txt");
    // myWFile.write("\n\n");
    // myWFile.close();
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

    // for (int i = 0; i < 4; i++){
    //             cout << "IR[" << i << "] " << IR[i] << "  ";
    //         }
    // for (int i = 0; i < 100; i++)
    //         {
    //             cout << "M[" << i << "] ";
    //             for (int j = 0; j < 4; j++)
    //             {
    //                 cout << main_memory[i][j] << " ";
    //             }
    //             cout << '\n';
    //         }
    // cout << "hi" <<si;
}


int main()
{
    // ofstream myFile;
    // myFile.open("output.txt");
    // myFile.close();
    myfile.open("input.txt");
    //myWfile.open("output.txt");

    ofstream myFfile;
    myFfile.open("output.txt");
    myFfile<<"";
    myFfile.close();
    load();
    //cout << "\n\n\n\nHI\n\n\n\n\n";

    // for (int i = 0; i < 4; i++){
    //             cout << "IR[" << i << "] " << IR[i] << "  ";
    //         }
    // for (int i = 0; i < 100; i++)
    //         {
    //             cout << "M[" << i << "] ";
    //             for (int j = 0; j < 4; j++)
    //             {
    //                 cout << main_memory[i][j] << " ";
    //             }
    //             cout << '\n';
    //         }

    // print all components
    // cout << "\nMain Memory::" << endl;
    // for (int i = 0; i < 100; i++)
    // {
    //     cout << "M[" << i << "] ";
    //     for (int j = 0; j < 4; j++)
    //     {
    //         cout << main_memory[i][j] << " ";
    //     }
    //     cout << '\n';
    // }
    // cout << "\nR::" << endl;
    // for (int i = 0; i < 4; i++)
    // {
    //     cout << "R[" << i << "] " << R[i] << "   ";
    // }
    // cout << "\nIR::" << endl;
    // for (int i = 0; i < 4; i++)
    // {
    //     cout << "IR[" << i << "] " << IR[i] << "  ";
    // }
    // cout << "\nIC::" << endl;
    // for (int i = 0; i < 2; i++)
    // {
    //     cout << "IC[" << i << "] " << IC[i] << "  ";
    // }
    // cout << "\nIC::" << endl;
    // cout << C << endl;
    // cout << "\nBuffer::" << endl;
    // for (int i = 0; i < buff.size(); i++)
    // {
    //     cout << "Buffer[" << i << "] " << buff[i] << "  ";
    // }

    myfile.close();
}