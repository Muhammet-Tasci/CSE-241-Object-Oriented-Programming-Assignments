#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

//I have defined the functions for printing the registers and the command functions below.
void print_registers(int R[]){
    cout << "R1=" << R[0];
    cout << ", R2=" << R[1];
    cout << ", R3=" << R[2];
    cout << ", R4=" << R[3];
    cout << ", R5=" << R[4];
    cout << ", R6=" << R[5] << endl;
}


void move(int &a, int &b){
    a = b;
}

void add(int &a, int &b){
    a += b;
}

void sub(int &a, int &b){
    a -= b;
}

void jump(int line_number,int &current_line) {
    current_line = line_number;

}

int jump(int a, int line_number,int &current_line) {
    if(a == 0){
    current_line = line_number;
    return 1;
    }

    return 0;
}

void prn(int value){

    cout<< value << endl;

}

void INP(int &r){
    char ch;
    cout<<"Please enter a character: ";
    cin >> ch;
    r = int(ch);

}

void HLT(int R[]){
    cout<< "The program is closing.."<< endl;
    print_registers(R);
    exit(1);
}



int main(int argc, char* argv[]) {

    if (argc != 3) {
        cout << "Usage: ./cpuSim filename option" << endl;
        return 1;
    }
    string filename = argv[1];
    int option = stoi(argv[2]);

    ifstream file (filename);
     if (!file.is_open()) {
        cout << "File not found." << endl;
        return 1;
    }

    //I have created the vector that will store the strings read line by line from the file. 
    //Thanks to this vector, I will be able to keep track of the order of the lines using indices. I have also created the array that will hold the registers.
    vector<string> inst;
    int R[6] = {0,0,0,0,0,0};
    string line;

    while(getline(file,line)) {
        if(line.empty()) {
            cout<<"A empty line was dedected. The program is exiting."<< endl;
            exit(0);
        }
        inst.push_back(line);
    }

    file.close();

    int current_line = 1;
    string command;

    //Each iteration of this while loop corresponds to the processing of a single command.
    while(current_line <= inst.size() && current_line > 0) {
        line = inst[current_line-1];

        int comment_pos = line.find(';');
        if(comment_pos != string::npos) {
        line = line.substr(0, comment_pos);
        }

        //The line is split into parts in order to be examined from the necessary aspects and executed appropriately.

        int comment_index = line.find(" ");
        line.erase(0,line.find_first_not_of(" \t")); 
        line.erase(line.find_last_not_of(" \t") + 1);

        int space_index = line.find(" ");

    string command;
    string args;
    if(space_index != string::npos){
        command = line.substr(0, space_index);
        args = line.substr(space_index+1); 
    } else {
        command = line;
        args = "";
    }


    //Below, for each command match, the split parts are checked to see if they conform to the command's syntax. 
    //If they do, the necessary values are passed to the corresponding functions; if not, an error is raised and the program exits.
    if(command == "MOV") {
        int comma_index = args.find(',');
        if(comma_index == string::npos) { cout << "MOV syntax error\n"; exit(1); }

        string reg1 = args.substr(0, comma_index);
        string reg2 = args.substr(comma_index + 1);


        reg1.erase(0, reg1.find_first_not_of(" \t"));
        reg1.erase(reg1.find_last_not_of(" \t")+1);
        reg2.erase(0, reg2.find_first_not_of(" \t"));
        reg2.erase(reg2.find_last_not_of(" \t")+1);

        if(reg1[0] != 'R' || stoi(reg1.substr(1)) < 1 || stoi(reg1.substr(1)) > 6)
            { cout << "Invalid register: " << reg1 << endl; exit(1); }

        int first_register_index = stoi(reg1.substr(1)) - 1;

        if(reg2[0]=='R') { 
            int second_register_index = stoi(reg2.substr(1)) - 1;
            if(second_register_index < 0 || second_register_index > 5) { cerr << "Invalid register: " << reg2 << endl; exit(1); }
            move(R[first_register_index], R[second_register_index]);
            if(option == 1){
                cout<< line <<" - ";
                print_registers(R);
            }
        } else { 
            int value = stoi(reg2);
            move(R[first_register_index],value);
            if(option == 1){
                cout<< line <<" - ";
                print_registers(R);
            }
        }

    } else if(command == "ADD") {
        int comma_index = args.find(',');
        if(comma_index == string::npos) { cout << "ADD syntax error\n"; exit(1); }

        string reg1 = args.substr(0, comma_index);
        string reg2 = args.substr(comma_index + 1);


        reg1.erase(0, reg1.find_first_not_of(" \t"));
        reg1.erase(reg1.find_last_not_of(" \t")+1);
        reg2.erase(0, reg2.find_first_not_of(" \t"));
        reg2.erase(reg2.find_last_not_of(" \t")+1);

        if(reg1[0] != 'R' || stoi(reg1.substr(1)) < 1 || stoi(reg1.substr(1)) > 6)
            { cout << "Invalid register: " << reg1 << endl; exit(1); }

        int first_register_index = stoi(reg1.substr(1)) - 1;

        if(reg2[0]=='R') { 
            int second_register_index = stoi(reg2.substr(1)) - 1;
            if(second_register_index < 0 || second_register_index > 5) { cerr << "Invalid register: " << reg2 << endl; exit(1); }
            add(R[first_register_index], R[second_register_index]);
            if(option == 1){
                cout<< line <<" - ";
                print_registers(R);
            }
        } else { 
            int value = stoi(reg2);
            add(R[first_register_index],value);
            if(option == 1){
                cout<< line <<" - ";
                print_registers(R);
            }
        }

    } else if(command == "SUB") {
        int comma_index = args.find(',');
        if(comma_index == string::npos) { cout << "SUB syntax error\n"; exit(1); }

        string reg1 = args.substr(0, comma_index);
        string reg2 = args.substr(comma_index + 1);

        reg1.erase(0, reg1.find_first_not_of(" \t"));
        reg1.erase(reg1.find_last_not_of(" \t")+1);
        reg2.erase(0, reg2.find_first_not_of(" \t"));
        reg2.erase(reg2.find_last_not_of(" \t")+1);

        if(reg1[0] != 'R' || stoi(reg1.substr(1)) < 1 || stoi(reg1.substr(1)) > 6)
            { cout << "Invalid register: " << reg1 << endl; exit(1); }

        int first_register_index = stoi(reg1.substr(1)) - 1;

        if(reg2[0]=='R') { 
            int second_register_index = stoi(reg2.substr(1)) - 1;
            if(second_register_index < 0 || second_register_index > 5) { cerr << "Invalid register: " << reg2 << endl; exit(1); }
            sub(R[first_register_index], R[second_register_index]);
            if(option == 1){
                cout<< line <<" - ";
                print_registers(R);
            }
        } else { 
            int value = stoi(reg2);
            sub(R[first_register_index],value);
            if(option == 1){
                cout<< line <<" - ";
                print_registers(R);
            }
        }

    }else if(command == "PRN") {
        args.erase(0, args.find_first_not_of(" \t"));
        args.erase(args.find_last_not_of(" \t")+1);

        if(args[0]=='R') {
            int register_index = stoi(args.substr(1)) - 1;
            if(register_index < 0 || register_index > 5) { cout << "Invalid register: " << args << endl; exit(1);}
            prn(R[register_index]);
            if(option == 1){
                cout<< line <<" - ";
                print_registers(R);
            }
        } else {
            prn(stoi(args));
            if(option == 1){
                cout<< line <<" - ";
                print_registers(R);
            }
        }

    }else if(command == "INP") {
        args.erase(0, args.find_first_not_of(" \t"));
        args.erase(args.find_last_not_of(" \t")+1);

        if(args[0]!='R') { cout << "INP requires a register" << endl; exit(1);}
        int register_index = stoi(args.substr(1)) - 1;
        if(register_index < 0 || register_index > 5) { cout << "Invalid register" << endl; exit(1);}
        INP(R[register_index]);
        if(option == 1){
                cout<< line <<" - ";
                print_registers(R);
            }

    }else if(command == "JMP") {

        //Specifically for the jump command, when the jump command is executed, the while loop immediately moves to the next iteration 
        //because at the end of each loop there is a section that regularly increments the current line.
        
        int comma_index = args.find(',');
        if(comma_index == string::npos) {
            if(stoi(args) < 1 || stoi(args) > inst.size()) { cout<< "Invalid line number: " << args << endl; exit(1);}
             jump(stoi(args),current_line);
             if(option == 1){
                cout<< line <<" - ";
                print_registers(R);
            }
             continue;
        }

        string reg1 = args.substr(0, comma_index);
        string reg2 = args.substr(comma_index + 1);

        reg1.erase(0, reg1.find_first_not_of(" \t"));
        reg1.erase(reg1.find_last_not_of(" \t")+1);
        reg2.erase(0, reg2.find_first_not_of(" \t"));
        reg2.erase(reg2.find_last_not_of(" \t")+1);

        if(reg1[0] != 'R' || stoi(reg1.substr(1)) < 1 || stoi(reg1.substr(1)) > 6) {
        cout << "Invalid register: " << reg1 << endl; exit(1); 
        }

        if(stoi(reg2) < 1 || stoi(reg2) > inst.size()) { cout<< "Invalid line number: " << reg2 << endl; exit(1);}
        int change = jump(R[stoi(reg1.substr(1))-1],stoi(reg2),current_line);
        if(option == 1){
                cout<< line <<" - ";
                print_registers(R);
            }

        if(change) {continue;}

    } else if(command == "HLT") {
        HLT(R);

    }else {
        //Lines that do not match any command name directly cause an error and the program exits
        cout << "Unknown command: " << command << endl;
        exit(1);
    }

    //At the end of each loop, the current line counter is incremented to move to the next command line.
    current_line++;

    }

    return 0;

}