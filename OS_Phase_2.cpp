// Phase-II
#include <bits/stdc++.h>
using namespace std;
int IC[2], VA, RA, PTR[4], EM=0, pi=0,si=0, ti=0;
string M[300][4], R[4], IR[4], buff;
vector<int> v;
bool C;
struct PCB{
    int job_id[4];
    int TTC[4];
    int LLC[4];
    int TTL[4];
    int TLL[4];
}p1;

ifstream myfile;
ofstream myWf;

void load();
void init();
void startExecution();
void MOS();
void READ();
void WRITE();
void TERMINATE(int);
void executeUserProgram();
int ALLOCATE();
void ADDRESS_MAP(int);
void SIMULATION();

void init()
{
    srand(time(0));
    for (int i = 0; i < 300; i++){
        for (int j = 0; j < 4; j++){
            M[i][j] = "*";
        }
    }
    for (int i = 0; i < 4; i++){
        R[i] = "*";
        IR[i] = "*";
        PTR[i] = 0;
    }
    IC[0] = 0;
    IC[1] = 0;
    C = false;
    EM=0;
    ti=0;
    si=0;
    pi=0;
    v.clear();
}

void load()
{
    int prgmc=0;
    while (getline(myfile, buff)){
        string s = buff.substr(0, 4);
        if (s == "$AMJ"){
            init();
            for(int i=0;i<4;i++){
                p1.job_id[i]=stoi(buff.substr(i+4,1));
                p1.TTL[i]=stoi(buff.substr(i+8,1));
                p1.TLL[i]=stoi(buff.substr(i+12,1));
            }
            for(int i=0;i<4;i++){
                p1.TTC[i]=0;
                p1.LLC[i]= 0; 
            }

            //PCB for checking results
            cout<<"\njob_id :: ";
            for(int i=0;i<4;i++)
                cout<<p1.job_id[i];
            cout<<"\nTTL :: ";
            for(int i=0;i<4;i++)
                cout<<p1.TTL[i];
            cout<<"\nTLL :: ";
            for(int i=0;i<4;i++)
                cout<<p1.TLL[i];
            cout<<"\nTTC :: ";
            for(int i=0;i<4;i++)
                cout<<p1.TTC[i];
            cout<<"\nLLC :: ";
            for(int i=0;i<4;i++)
                cout<<p1.LLC[i];

            if(p1.TTL[3]==0 && p1.TTL[2]==0 &&p1.TTL[1]==0 && p1.TTL[0]==0)
                TERMINATE(3);

            int randint=ALLOCATE();
            randint=randint*10;

            int ptrassist=randint;
            for(int i=0;i<10;i++){
                for(int j=0;j<4;j++){
                    M[randint][j]="#";
                }
                randint++;
            }
            for(int i=3;i>=0;i--){
                    PTR[i]=ptrassist%10;
                    
                    ptrassist=ptrassist/10;
            }

            //PTR Initiat
            cout<<"\n\nPTR :: ";
            for(int i=0;i<4;i++){
                cout<< PTR[i];
            }
            cout << endl;
        }
    
        else if(s=="$DTA"){
            startExecution();
        }
        else if (s == "$END")
        {
            prgmc=0;
            cout << "\nend of job ";
            for(int i=0;i<4;i++)
                cout << p1.job_id[i] << "";
            //cout << endl;
            cout << "\n----------------------------------------------------"<< endl;
        }
        else if (s!="$AMJ" && s!="$DTA" && s != "$END"){
            int PTRint=PTR[3]+PTR[2]*10+PTR[1]*100+PTR[0]*1000+prgmc;
            
            int Pframe=ALLOCATE();
            
            for(int i=3;i>=0;i--){
                M[PTRint][i]=Pframe%10+48;
                Pframe=Pframe/10;
            }
            
            int p=(stoi(M[PTRint][3])+stoi(M[PTRint][2])*10+stoi(M[PTRint][1])*100+stoi(M[PTRint][0])*1000)*10;

            int j=0;
            if(buff.size()>40){
                cout << "\nProgram card exceeded limit - 40 bytes";
                exit(0);
            }
            for (int i = 0; i < buff.size(); i++)
            {
                if(j==4){
                    j=0;
                    p++;
                }
                if(buff[i]=='H'){
                    int k=1;
                    M[p][j]=buff[i];
                    for(k=1;k<=3;k++){
                        M[p][k]='*';
                    }
                    j=k-1;
                }
                else 
                    M[p][j]=buff[i];
                j++;
            }
            prgmc++;
        }
        else{
            exit (0);
        }
    }
    exit(0);
}

int ALLOCATE(){
    int randint;
    
    randint = rand() % 30;
    if(find(v.begin(), v.end(), randint) != v.end())
        ALLOCATE();
    else{
        //cout << randint << "  ";
        v.push_back(randint);
    }
    return randint;
}

void ADDRESS_MAP(int VA){
    int PTRint=PTR[3]+PTR[2]*10+PTR[1]*100+PTR[0]*1000;
    int PTE=PTRint+VA/10;
    

    //Valid & Invalid
    if(M[PTE][2]+M[PTE][3]=="##"){
        
       pi=3;
       MOS();
       pi=0;
    //    if(IR[0]+IR[1]=="GD" || IR[0]+IR[1]=="SR"){
    //         int validframe=ALLOCATE();
    //         for(int i=3;i>=0;i--){
    //             M[PTE][i]=validframe%10+48;
    //             validframe=validframe/10;
    //         }
    //         SIMULATION();
    //    }
    //    else if(IR[0]+IR[1]=="PD" || IR[0]+IR[1]=="LR" || IR[0]+IR[1]=="SR" || IR[0]+IR[1]=="CR" || IR[0]+IR[1]=="BT"){
    //         TERMINATE(6);
    //    }
    //    else{
    //         pi=1;
    //         TERMINATE(4);
    //    }
       //pi=0;
    }
    //cout << "HII" << M[PTE][3] << " "<< M[PTE][2]<< endl;
    int p=stoi(M[PTE][3])+stoi(M[PTE][2])*10;
    cout << "=======> " << M[PTE][2] << M[PTE][3] << endl;
    RA=p*10+VA%10;
    
}

void SIMULATION(){
    if(p1.TTC[3]==9){
        p1.TTC[2]+=1;
        p1.TTC[3]=0;
    }
    else{
        p1.TTC[3]+=1;
    }
    
    if(p1.TTC[3]>=p1.TTL[3] && p1.TTC[2]>=p1.TTL[2] && p1.TTC[1]>=p1.TTL[1] && p1.TTC[0]>=p1.TTL[0]){
        ti=2;
    }
}

void startExecution(){
    IC[0]=0;
    IC[1]=0;
    executeUserProgram(); 
}

void executeUserProgram(){
    while(1){
        if(ti==0){
        
            int row=IC[0]*10+IC[1];
            VA=row;
            ADDRESS_MAP(VA);
            if(pi!=0){
                MOS();
                pi=0;
                // if(pi==1){
                //     TERMINATE(4);
                // }
                // if(pi==2){
                //     TERMINATE(5);
                // }
            }

            for(int i=0;i<4;i++)
                IR[i]=M[RA][i];
            
            string inst=IR[0]+""+IR[1];

            cout << "\nIR:: ";
            for (int i = 0; i < 4; i++){
                cout << "IR[" << i << "] " << IR[i] << "  ";
            }
            cout << "\nIC:: ";
            for (int i = 0; i < 2; i++){
                cout << "IC[" << i << "] " << IC[i] << "  ";
            }
            cout << endl;
            
            if(IC[1]==9){
                IC[0]=IC[0]+1;
                IC[1]=0;
            }
            else
                IC[1]=IC[1]+1;

            if(inst!="H*"){
                if(IR[2]=="0" || IR[2]=="1" || IR[2]=="2" || IR[2]=="3" || IR[2]=="4" || IR[2]=="5" || IR[2]=="6" || IR[2]=="7" || IR[2]=="8" || IR[2]=="9"){
                    if(IR[3]=="0" || IR[3]=="1" || IR[3]=="2" || IR[3]=="3" || IR[3]=="4" || IR[3]=="5" || IR[3]=="6" || IR[3]=="7" || IR[3]=="8" || IR[3]=="9"){
                        VA=stoi(IR[2])*10+stoi(IR[3]);
                        
                        ADDRESS_MAP(VA);
                        //cout << "HI" << endl;
                    }
                    else{
                        pi=2;
                    }
                }
                else{
                    pi=2;
                }
            }

            if(pi!=0){
                MOS();
                pi=0;
                // if(pi==1){
                //     TERMINATE(4);
                // }
                // if(pi==2){
                //     TERMINATE(5);
                // }
            }

            if(inst=="LR"){
                SIMULATION();
                for (int i = 0; i < 4; i++){
                    R[i] = M[RA][i];
                }
                
            }

            else if(inst == "SR"){
                SIMULATION();
                SIMULATION();
                for (int i = 0; i < 4; i++){
                    M[RA][i] = R[i];
                }
                
            }

            else if(inst == "CR"){
                SIMULATION();
                int flag = 0;
                for (int i = 0; i < 4; i++){
                    if (M[RA][i] == R[i])
                        flag++;
                }
                if (flag == 4){
                    C = true;
                }
                else
                    C = false;
                
            }

            else if(inst == "BT"){
                SIMULATION();
                if (C == true){
                    IC[0] = stoi(IR[2]);
                    IC[1] = stoi(IR[3]);
                }  
            }

            else if(inst == "GD"){
                si=1;
                SIMULATION();
                SIMULATION();
                MOS();  
            }
            else if(inst == "PD"){
                si=2;
                SIMULATION();
                
                if(p1.LLC[3]>=p1.TLL[3] && p1.LLC[2]>=p1.TLL[2] && p1.LLC[1]>=p1.TLL[1] && p1.LLC[0]>=p1.TLL[0]){
                    TERMINATE(2);
                }
                
                MOS();
                if(p1.LLC[3]==9){
                    p1.LLC[2]+=1;
                    p1.LLC[3]=0;
                }
                else{
                    p1.LLC[3]+=1;
                }
            }
            else if(inst == "H*"){
                si=3;
                SIMULATION();
                MOS();
            }
            else{
                pi=1;
            }
        }
        else
            TERMINATE(3);
        //cout << "ROHIT" << endl;
    }
}

void READ(){
    getline(myfile,buff);
    int x = RA;

    int j=0;
    string stre=buff.substr(0,4);
    if(stre=="$END"){
        cout << "\nOut of Data";
        TERMINATE(1);
    }
    
    if(buff.size()>40){
        cout << "\nData card exceeded limit - 40 bytes";
        exit(0);
    }
    for (int i = 0; i < buff.size(); i++){
        if(j==4){
            j=0;
            x++;
        }
        M[x][j]=buff[i];
        j++;
    }

    // if(ti==2 && si==1){
    //     TERMINATE(3);
    // }
    si=0;

}

void WRITE(){
    ofstream myWfile;
    ifstream myRfile;
    myRfile.open("output2.txt");
    myWfile.open("output2.txt",ios::app);
    if(myRfile.is_open())
        myWfile << "";
    
    int x = RA;
    
    for (int i = 0; i < 10; i++){
        for(int j=0;j<4;j++){
            myWfile << M[x][j];
        }
        x++;
    }
    myWfile<<endl;
    myRfile.close();
    myWfile.close();
    // if(ti==2 && si==2){
    //     TERMINATE(3);
    // }
    si=0;

}


void TERMINATE(int EM){
    for (int i = 0; i < 300; i++){
        cout << "M[" << i << "] : ";
        for(int j=0;j<4;j++){
            cout << M[i][j];
            //myWfile << M[x][j];
        }
        cout << endl;
        //x++;
    }
    myWf.open("output2.txt",ios::app);

    if(EM==0){
        cout << "---------Appropriate Termination of Program---------\n";
        cout << "---------NO ERROR---------\n";
        myWf<< "---------Appropriate Termination of Program---------\n";
        myWf<< "---------NO ERROR---------\n";
    }
    else if(EM==1){
        cout << "---------Inappropriate Termination of Program cause Error---------\n";
        cout << "---------OUT OF DATA---------\n";
        myWf << "---------Inappropriate Termination of Program cause Error---------\n";
        myWf << "---------OUT OF DATA---------\n";
    }
    else if(EM==2){
        cout << "---------Inappropriate Termination of Program cause Error---------\n";
        cout << "---------LINE LIMIT EXCEEDED---------\n";
        myWf << "---------Inappropriate Termination of Program cause Error---------\n";
        myWf << "---------LINE LIMIT EXCEEDED---------\n";
    }
    else if(EM==3){
        cout << "---------Inappropriate Termination of Program cause Error---------\n";
        cout << "---------TIME LIMIT EXCEEDED---------\n";
        myWf << "---------Inappropriate Termination of Program cause Error---------\n";
        myWf << "---------TIME LIMIT EXCEEDED---------\n";
    }
    else if(EM==4){
        cout << "---------Inappropriate Termination of Program cause Error---------\n";
        cout << "---------OPERATION CODE ERROR---------\n";
        myWf << "---------Inappropriate Termination of Program cause Error---------\n";
        myWf << "---------OPERATION CODE ERROR---------\n";
    }
    else if(EM==5){
        cout << "---------Inappropriate Termination of Program cause Error---------\n";
        cout << "---------OPERAND ERROR---------\n";
        myWf << "---------Inappropriate Termination of Program cause Error---------\n";
        myWf << "---------OPERAND ERROR---------\n";
    }
    else if(EM==6){
        cout << "---------Inappropriate Termination of Program cause Error---------\n";
        cout << "---------INVALID PAGE FAULT---------\n";
        myWf << "---------Inappropriate Termination of Program cause Error---------\n";
        myWf << "---------INVALID PAGE FAULT---------\n";
    }

    myWf << "IR:: ";
    for (int i = 0; i < 4; i++){
        myWf << "IR[" << i << "] " << IR[i] << "  ";
    }
    myWf << "\nIC:: ";
    for (int i = 0; i < 2; i++){
        myWf << "IC[" << i << "] " << IC[i] << "  ";
    }
    myWf<<"\njob_id :: ";
        for(int i=0;i<4;i++)
            myWf<<p1.job_id[i];
    myWf<<"\nTTC :: ";
        if(p1.TTC[3]!=0)
            p1.TTC[3]=p1.TTC[3];
        for(int i=0;i<4;i++)
            myWf<<p1.TTC[i];
    myWf<<"\nLLC :: ";
        for(int i=0;i<4;i++)
            myWf<<p1.LLC[i];
    
    myWf<<"\nTTL :: ";
        for(int i=0;i<4;i++)
            myWf<<p1.TTL[i];
    myWf<<"\nTLL :: "; 
        for(int i=0;i<4;i++)
            myWf<<p1.TLL[i];
    myWf << "\nINTERRUPTS :: ";
        myWf << "SI = " << si;
        myWf << ", PI = " << pi;
        myWf << ", TI = " << ti;
        myWf << endl;
    myWf<<"\n\n";
    myWf.close();
    
    load();
    exit(0);
}

void MOS(){
    if(ti==0){
        switch(pi){
            case 1:
                TERMINATE(4);
            break;
            case 2:
                TERMINATE(5);  
            break;
            case 3:
                int PTRint=PTR[3]+PTR[2]*10+PTR[1]*100+PTR[0]*1000;
                int PTE=PTRint+VA/10;
                if(IR[0]+IR[1]=="GD" || IR[0]+IR[1]=="SR"){
                    int validframe=ALLOCATE();
                    for(int i=3;i>=0;i--){
                        M[PTE][i]=validframe%10+48;
                        validframe=validframe/10;
                    }
                    //SIMULATION();
                }
                else if(IR[0]+IR[1]=="PD" || IR[0]+IR[1]=="LR" || IR[0]+IR[1]=="SR" || IR[0]+IR[1]=="CR" || IR[0]+IR[1]=="BT"){
                    TERMINATE(6);
                }
                else{
                    pi=1;
                    TERMINATE(4);
                }
                cout << "<=======> " << M[PTE][2] << M[PTE][3] << endl;
            break;
        }
        
        switch(si){
            case 1:
                READ();
            break;
            case 2:
                WRITE();   
            break;
            case 3:
                TERMINATE(EM);
            break;
        }
    }
    if (ti==2) {
        switch(pi){
            case 1:
                TERMINATE(4);
            break;
            case 2:
                TERMINATE(5);  
            break;
            case 3:
                TERMINATE(3);
            break;
        }
        
        switch(si){
            case 1:
                TERMINATE(3);
            break;
            case 2:
                WRITE();
                TERMINATE(3);   
            break;
            case 3:
                TERMINATE(EM);
            break;
        }
        TERMINATE(3);
    }
    // else
    //     TERMINATE(3);
}


int main()
{
    srand(time(0));
    myfile.open("input2.txt");

    ofstream myFfile;
    myFfile.open("output2.txt");
    myFfile<<"";
    myFfile.close();
    load();
    
    myfile.close();
}