#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

/* CPU class simulates a simple processor with 6 registers and 100 bytes of memory */
class CPU {
    private:
    unsigned char memory[100]; /* Memory array holds 100 unsigned bytes with values 0-255 */
    int R[6] = {0,0,0,0,0,0}; /* Six integer registers R1 to R6 represented as array index 0 to 5 */

    public:
    /* Constructor initializes all memory locations to zero */
    CPU(){
        for(int i = 0;i<100;i++){
            memory[i] = 0;
        }
    }

    void print_registers() const;
    void print_memory() const;

    /* MOV R1, R2 - Copy value from first register to second register */
    void move1(int register_index1 , int register_index2){
        R[register_index2] = R[register_index1];
    }

    /* MOV R1, constant - Load constant value into register */
    void move2(int register_index, int number) {
        R[register_index] = number;
    }

    /* MOV R1, #address - Store register value into memory location */
    void move3(int register_index, int memory_index){
        memory[memory_index] = R[register_index];
    }

    /* MOV #address, R1 - Load memory value into register */
    void move4(int memory_index, int register_index) {
        R[register_index] = (int)memory[memory_index];
    }

    /* MOV #address, constant - Store constant value into memory location */
    void move5(int memory_index, int number) {
        memory[memory_index] = number;
    }

    /* ADD R1, R2 - Add second register value to first register */
    void add1(int register_index1 , int register_index2) {
        R[register_index1] += R[register_index2];
    }

    /* ADD R1, constant - Add constant value to register */
    void add2(int register_index, int number){
        R[register_index] += number;
    }

    /* ADD R1, #address - Add memory value to register */
    void add3(int register_index, int memory_index){
        R[register_index] += (int)memory[memory_index];
    }

    /* SUB R1, R2 - Subtract second register from first register */
    void sub1(int register_index1, int register_index2){
        R[register_index1] -= R[register_index2];
    }

    /* SUB R1, constant - Subtract constant from register */
    void sub2(int register_index, int number){
        R[register_index] -= number;
    }

    /* SUB R1, #address - Subtract memory value from register */
    void sub3(int register_index, int memory_index){
        R[register_index] -= (int)memory[memory_index];
    }

    /* JMP R1, line - Jump to line number if register equals zero */
    int jmp(int register_index, int line_number, int& current_line){
        if(R[register_index] == 0) {
            current_line = line_number;
            return 1; /* Return 1 if jump occurred */
        }
        return 0; /* Return 0 if jump did not occur */
    }

    /* JMP line - Unconditional jump to line number */
    void jmp(int line_number, int& current_line){
        current_line = line_number;
    }

    /* JPN R1, line - Jump to line number if register is zero or negative */
    int jpn1(int register_index, int line_number, int& current_line){
        if(R[register_index] <= 0) {
            current_line = line_number;
            return 1; /* Return 1 if jump occurred */
        }
        return 0; /* Return 0 if jump did not occur */
    }

    /* JPN R1, #address - Jump to line stored in memory if register is zero or negative */
    int jpn2(int register_index, int memory_index, int& current_line, int line_num){
        if(R[register_index] <= 0) {
            if((int)memory[memory_index] < 0 || (int)memory[memory_index] > line_num ){ cout << "Memory has invalid value for line number." << endl; exit(1);}
            current_line = (int)memory[memory_index];
            return 1; /* Return 1 if jump occurred */
        }
        return 0; /* Return 0 if jump did not occur */
    }

    /* PRN R1 - Print register value with label */
    void prn1(int register_index){
        cout<< "R" << register_index + 1 << " : " << R[register_index] << endl;
    }

    /* PRN constant - Print constant number value */
    void prn2(int number){
        cout << "The number is "<< number << endl; 
    }

    /* PRN #address - Print memory location value */
    void prn3(int memory_index){
        cout << "Memory location #"<<memory_index<< " has a value of " << (int)memory[memory_index] << endl;
    }

    /* INP R1 - Read character from user and store ASCII value in register */
    void INP(int register_index){
    char ch;
    cout<<"Please enter a character: ";
    cin >> ch;
    R[register_index] = ch; /* Store ASCII value of character */
}

    /* HLT - Halt program and display all registers and memory contents */
    void HLT(){
    cout<< "The program is closing.."<< endl;
    print_registers();
    print_memory();
    exit(1);
}
};

/* Display all six register values in single line */
void CPU::print_registers() const{
    cout << "R1=" << R[0];
    cout << ", R2=" << R[1];
    cout << ", R3=" << R[2];
    cout << ", R4=" << R[3];
    cout << ", R5=" << R[4];
    cout << ", R6=" << R[5] << endl;
}

/* Display all 100 memory locations with their values */
void CPU::print_memory() const {
    for (int i = 0; i< 100;i++){
        cout<< "#"<< i << ": "<< (int)memory[i]; /* Cast to int to display numeric value not character */
        if(i != 99){
            cout<< ", ";
        }else{
            cout<< endl;
        }
    }
}


/* Main function handles file reading and instruction execution */
int main(int argc, char *argv[]) {

    /* Check command line arguments for filename and option */
    if (argc != 3) {
        cout << "Usage: ./cpuSim filename option" << endl;
        return 1;
    }
    string filename = argv[1]; /* Input file containing CPU instructions */
    int option = stoi(argv[2]); /* Option 0 runs silently, 1 shows registers, 2 shows registers and memory */

    /* Open instruction file */
    ifstream file (filename);
    if (!file.is_open()) {
        cout << "File not found." << endl;
        return 1;
    }

    CPU my_cpu; /* Create CPU instance */

    vector<string> inst; /* Store all instruction lines */
    string line;
    int inst_number = 0;

    /* Read all instructions from file into vector */
    while(getline(file,line)) {
        if(line.empty()) {
            cout<<"A empty line was dedected. The program is exiting."<< endl;
            exit(0);
        }
        inst.push_back(line);
        inst_number++;
    }

    file.close();

    /* Check if instruction count exceeds limit */
    if(inst_number > 500){
        cout << "You have exceeded the 500-line command limit. The program is closing..." << endl;
        exit(0);
    }

    int current_line = 1; /* Current line being executed starts at 1 */
    string command;

    /* Main execution loop processes each instruction */
    while(current_line <= inst.size() && current_line > 0) {
        line = inst[current_line-1]; /* Get instruction line using 0-based index */

        /* Remove comments from line */
        int comment_pos = line.find(';');
        if(comment_pos != string::npos) {
        line = line.substr(0, comment_pos);
        }

        /* Trim whitespace from beginning and end of line */
        line.erase(0,line.find_first_not_of(" \t")); 
        line.erase(line.find_last_not_of(" \t") + 1);

        /* Split line into command and arguments */
        int space_index = line.find(" ");

    string command;
    string args;
    if(space_index != string::npos){
        command = line.substr(0, space_index); /* Extract command part */
        args = line.substr(space_index+1); /* Extract arguments part */
    } else {
        command = line; /* Line has only command no arguments */
        args = "";
    }


    /* Parse and execute MOV instruction with various operand combinations */
    if(command == "MOV") {
        /* Find comma separating two operands */
        int comma_index = args.find(',');
        if(comma_index == string::npos) { cout << "MOV syntax error\n"; exit(1); }

        /* Split operands and trim whitespace */
        string reg1 = args.substr(0, comma_index);
        string reg2 = args.substr(comma_index + 1);

        reg1.erase(0, reg1.find_first_not_of(" \t"));
        reg1.erase(reg1.find_last_not_of(" \t")+1);
        reg2.erase(0, reg2.find_first_not_of(" \t"));
        reg2.erase(reg2.find_last_not_of(" \t")+1);

        /* Validate first operand is either register or memory location */
        if(reg1[0] != 'R' || stoi(reg1.substr(1)) < 1 || stoi(reg1.substr(1)) > 6) {
            if(reg1[0] != '#' || stoi(reg1.substr(1)) < 0 || stoi(reg1.substr(1)) > 99) {
             cout << "Invalid register or memory: " << reg1 << endl; exit(1); 
            }
        }

        /* Handle case when first operand is register */
        if(reg1[0] == 'R') {
        int first_register_index = stoi(reg1.substr(1)) - 1; /* Convert to 0-based index */

        if(reg2[0]=='R') { 
            /* MOV R1, R2 - Copy register to register */
            int second_register_index = stoi(reg2.substr(1)) - 1;
            if(second_register_index < 0 || second_register_index > 5) { cerr << "Invalid register: " << reg2 << endl; exit(0); }
            my_cpu.move1(first_register_index,second_register_index);
        } else { 

            if(reg2[0] == '#') {
                /* MOV R1, #address - Store register value to memory */
                int memory_index = stoi(reg2.substr(1));
                if(memory_index < 0 || memory_index > 99) { cerr << "Invalid memory location: " << reg2 << endl; exit(0); }
                my_cpu.move3(first_register_index,memory_index);

            }else {
            /* MOV R1, constant - Load constant to register */
            int value = stoi(reg2);
            my_cpu.move2(first_register_index,value);
        }
        }

    }else{
        /* Handle case when first operand is memory location */
        if(reg1[0] == '#'){
        int first_memory_index = stoi(reg1.substr(1));

        if(reg2[0] == 'R'){
            /* MOV #address, R1 - Load memory value to register */
            int register_index = stoi(reg2.substr(1)) - 1;
            if(register_index < 0 || register_index > 5) { cerr << "Invalid register: " << reg2 << endl; exit(0); }
            my_cpu.move4(first_memory_index,register_index);
        }else{
            /* MOV #address, constant - Store constant to memory */
            int value = stoi(reg2);
            my_cpu.move5(first_memory_index,value);
        }

        }
    }

    } else if(command == "ADD") {
        /* Parse ADD instruction with register and second operand */
        int comma_index = args.find(',');
        if(comma_index == string::npos) { cout << "ADD syntax error\n"; exit(1); }

        string reg1 = args.substr(0, comma_index);
        string reg2 = args.substr(comma_index + 1);

        /* Trim whitespace from operands */
        reg1.erase(0, reg1.find_first_not_of(" \t"));
        reg1.erase(reg1.find_last_not_of(" \t")+1);
        reg2.erase(0, reg2.find_first_not_of(" \t"));
        reg2.erase(reg2.find_last_not_of(" \t")+1);

        /* First operand must be register for ADD instruction */
        if(reg1[0] != 'R' || stoi(reg1.substr(1)) < 1 || stoi(reg1.substr(1)) > 6)
            { cout << "Invalid register: " << reg1 << endl; exit(1); }

        int first_register_index = stoi(reg1.substr(1)) - 1;

        if(reg2[0]=='R') { 
            /* ADD R1, R2 - Add register to register */
            int second_register_index = stoi(reg2.substr(1)) - 1;
            if(second_register_index < 0 || second_register_index > 5) { cerr << "Invalid register: " << reg2 << endl; exit(1); }
            my_cpu.add1(first_register_index,second_register_index);
        } else { 
            if(reg2[0] == '#') {
                /* ADD R1, #address - Add memory value to register */
                int memory_index = stoi(reg2.substr(1));
                if(memory_index < 0 || memory_index > 99) { cerr << "Invalid memory location: " << reg2 << endl; exit(0); }
                my_cpu.add3(first_register_index,memory_index);

            }else{
            /* ADD R1, constant - Add constant to register */
            int value = stoi(reg2);
            my_cpu.add2(first_register_index,value);
            }
        }

    } else if(command == "SUB") {
        /* Parse SUB instruction with register and second operand */
        int comma_index = args.find(',');
        if(comma_index == string::npos) { cout << "SUB syntax error\n"; exit(1); }

        string reg1 = args.substr(0, comma_index);
        string reg2 = args.substr(comma_index + 1);

        /* Trim whitespace from operands */
        reg1.erase(0, reg1.find_first_not_of(" \t"));
        reg1.erase(reg1.find_last_not_of(" \t")+1);
        reg2.erase(0, reg2.find_first_not_of(" \t"));
        reg2.erase(reg2.find_last_not_of(" \t")+1);

        /* First operand must be register for SUB instruction */
        if(reg1[0] != 'R' || stoi(reg1.substr(1)) < 1 || stoi(reg1.substr(1)) > 6)
            { cout << "Invalid register: " << reg1 << endl; exit(1); }

        int first_register_index = stoi(reg1.substr(1)) - 1;

        if(reg2[0]=='R') { 
            /* SUB R1, R2 - Subtract register from register */
            int second_register_index = stoi(reg2.substr(1)) - 1;
            if(second_register_index < 0 || second_register_index > 5) { cerr << "Invalid register: " << reg2 << endl; exit(1); }
            my_cpu.sub1(first_register_index,second_register_index);
        } else { 
            if(reg2[0] == '#') {
                /* SUB R1, #address - Subtract memory value from register */
                int memory_index = stoi(reg2.substr(1));
                if(memory_index < 0 || memory_index > 99) { cerr << "Invalid memory location: " << reg2 << endl; exit(0); }
                my_cpu.sub3(first_register_index,memory_index);

            }else{
            /* SUB R1, constant - Subtract constant from register */
            int value = stoi(reg2);
            my_cpu.sub2(first_register_index,value);
            }
        }

    }else if(command == "PRN") {
        /* Parse PRN instruction to print register, memory or constant */
        args.erase(0, args.find_first_not_of(" \t"));
        args.erase(args.find_last_not_of(" \t")+1);

        if(args[0]=='R') {
            /* PRN R1 - Print register value */
            int register_index = stoi(args.substr(1)) - 1;
            if(register_index < 0 || register_index > 5) { cout << "Invalid register: " << args << endl; exit(1);}
            my_cpu.prn1(register_index);
        } else {
            if(args[0] == '#'){
                /* PRN #address - Print memory location value */
                int memory_index = stoi(args.substr(1));
                if(memory_index < 0 || memory_index > 99) { cerr << "Invalid memory location: " << args << endl; exit(0); }
                my_cpu.prn3(memory_index);
            }else{
                /* PRN constant - Print constant number */
                my_cpu.prn2(stoi(args));
            }
        }

    }else if(command == "INP") {
        /* Parse INP instruction to read character into register */
        args.erase(0, args.find_first_not_of(" \t"));
        args.erase(args.find_last_not_of(" \t")+1);

        if(args[0]!='R') { cout << "INP requires a register" << endl; exit(1);}
        int register_index = stoi(args.substr(1)) - 1;
        if(register_index < 0 || register_index > 5) { cout << "Invalid register" << endl; exit(1);}
        my_cpu.INP(register_index);

    }else if(command == "JMP") {

        /* Parse JMP instruction for conditional or unconditional jump */
        int comma_index = args.find(',');
        if(comma_index == string::npos) {
            /* JMP line - Unconditional jump to line number */
            args.erase(0, args.find_first_not_of(" \t"));
            args.erase(args.find_last_not_of(" \t")+1);
            if(stoi(args) < 1 || stoi(args) > inst.size()) { cout<< "Invalid line number: " << args << endl; exit(1);}
            my_cpu.jmp(stoi(args),current_line);
            continue; /* Skip line increment at end of loop */
        }

        /* JMP R1, line - Jump if register is zero */
        string reg1 = args.substr(0, comma_index);
        string reg2 = args.substr(comma_index + 1);

        reg1.erase(0, reg1.find_first_not_of(" \t"));
        reg1.erase(reg1.find_last_not_of(" \t")+1);
        reg2.erase(0, reg2.find_first_not_of(" \t"));
        reg2.erase(reg2.find_last_not_of(" \t")+1);

        /* Validate register operand */
        if(reg1[0] != 'R' || stoi(reg1.substr(1)) < 1 || stoi(reg1.substr(1)) > 6) {
        cout << "Invalid register: " << reg1 << endl; exit(1); 
        }

        /* Validate line number is within program bounds */
        if(stoi(reg2) < 1 || stoi(reg2) > inst.size()) { cout<< "Invalid line number: " << reg2 << endl; exit(1);}
        int change = my_cpu.jmp(stoi(reg1.substr(1))-1 , stoi(reg2),current_line);

        if(change) {continue;} /* Skip line increment if jump occurred */

    } else if(command == "JPN" ) {

        /* Parse JPN instruction for jump if negative or zero */
        int comma_index = args.find(',');
        if(comma_index == string::npos) {cout << "JPN syntax error\n"; exit(1);}

        string reg1 = args.substr(0, comma_index);
        string reg2 = args.substr(comma_index + 1);

        reg1.erase(0, reg1.find_first_not_of(" \t"));
        reg1.erase(reg1.find_last_not_of(" \t")+1);
        reg2.erase(0, reg2.find_first_not_of(" \t"));
        reg2.erase(reg2.find_last_not_of(" \t")+1);

        /* Validate register operand */
        if(reg1[0] != 'R' || stoi(reg1.substr(1)) < 1 || stoi(reg1.substr(1)) > 6) {
        cout << "Invalid register: " << reg1 << endl; exit(1); 
        }

        if(reg2[0] == '#') {
            /* JPN R1, #address - Jump to line stored in memory if register is negative or zero */
            if(stoi(reg2.substr(1)) < 0 || stoi(reg2.substr(1)) > 99) { cout<< "Invalid memory location: " << reg2 << endl; exit(1);}
        int change = my_cpu.jpn2(stoi(reg1.substr(1))-1 , stoi(reg2.substr(1)),current_line,inst.size());
        if(change) {continue;} /* Skip line increment if jump occurred */

        }else{
        /* JPN R1, line - Jump to line number if register is negative or zero */
        if(stoi(reg2) < 1 || stoi(reg2) > inst.size()) { cout<< "Invalid line number: " << reg2 << endl; exit(1);}
        int change = my_cpu.jpn1(stoi(reg1.substr(1))-1 , stoi(reg2),current_line);
        if(change) {continue;} /* Skip line increment if jump occurred */
        }


    }else if(command == "HLT") {
        /* HLT - Halt program execution and display final state */
        my_cpu.HLT();

    }else {
        /* Unknown command encountered */
        cout << "Unknown command: " << command << endl;
        exit(1);
    }

    /* Display execution trace based on option setting */
    if(option == 1){
                /* Option 1 shows instruction and register state */
                cout<< line <<" - ";
                my_cpu.print_registers();
            }
            if(option == 2){
                /* Option 2 shows instruction, register state and memory state */
                cout<< line <<" - ";
                my_cpu.print_registers();
                my_cpu.print_memory();
            }

    /* Move to next instruction line */
    current_line++;

    }

return 0;

}