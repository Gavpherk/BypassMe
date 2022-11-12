#define _CRT_SECURE_NO_WARNINGS
#define ARRAY_SIZE 1024
#include <iostream>
#include <windows.h>
#include <fstream>
#include <shtypes.h>
#include <Windows.h>
#include <string.h>
#include <vector>
#include "md5.h"
#include "sha1.h"
#include "stdio.h"
#include "direct.h"
#include <Psapi.h>
#include <TlHelp32.h>
#include <comdef.h>
#include <obfuscate.h>
#include "time.h"

using namespace std;
string convertToString(char* a, int size);
bool WriteBufferToFile = false; // initialize debug/dev bools
bool WriteHashToFile = false;
bool DevMode = false;
bool PrintBuffer = false;
bool detected = true;

int main(int argc, char** argv) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (DevMode == true) {
        SetConsoleTextAttribute(h, 3);
        cout << AY_OBFUSCATE("Starting Timer...") << endl;
        SetConsoleTextAttribute(h, 7);
    }
    SetConsoleTextAttribute(h, 3);
    cout << AY_OBFUSCATE("Deploying Countermeasures.. This may take a few seconds.") << endl;
    SetConsoleTextAttribute(h, 15);
    //Beginning of my homemade debugger/breakpoint check measuring elapsed time between key steps involved in integrity checking
    double sum = 0;
    double add = 1;

    // Start measuring time
    long long int begin = GetTickCount64();
    int iterations = 1000 * 1000 * 1000;
    for (int i = 0; i < iterations; i++) {
        sum += add;
        add /= 2.0;
    }
    PROCESSENTRY32 pe32 = {
      sizeof(PROCESSENTRY32)
    }; //vanilla cheat engine check
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    bool detected = false;

    if (Process32First(hSnapshot, &pe32)) {
        do {
            _bstr_t b(pe32.szExeFile);
            const char* c = b;
            if ((strcmp(c, AY_OBFUSCATE("cheatengine-i386.exe")) == 0) || (strcmp(c, AY_OBFUSCATE("cheatengine-x86_64.exe")) == 0) || strcmp(c, AY_OBFUSCATE("aesopengine-x86_64.exe")) == 0 || (strcmp(c, AY_OBFUSCATE("aesopengine-x86_64-SSE4-AVX2.exe")) == 0) || (strcmp(c, AY_OBFUSCATE("aesopengine-x86_64-SSE4-AVX2.vmp.exe")) == 0)) {
                CloseHandle(hSnapshot);
                detected = true;
            }
        } while (Process32Next(hSnapshot, &pe32));
    }

    CloseHandle(hSnapshot);
    if (detected == true) {
        SetConsoleTextAttribute(h, 4);
        cout << AY_OBFUSCATE("Cheat Engine Detected, Cheat Engine is for noobs") << endl;
        SetConsoleTextAttribute(h, 7);
        system("pause");
        return 1;
    }
    string ExecutablePath = argv[0]; // Grabs Path&Name of the Executable
    if (DevMode == true) {
        cout << ExecutablePath << endl; // Prints Current Working Dirw
        system("pause");
    } //debug

    ifstream Binary; // initalize ifstream object for reading 
    Binary.open(ExecutablePath, ifstream::binary); // Open Executable, and prepare to read it in a Binary format.
    if (Binary.fail()) //Checks to See if we could get a handle to the executable or not
    {
        SetConsoleTextAttribute(h, 4);
        cerr << AY_OBFUSCATE("An error occured, restart the program.") << endl; // If you think this isnt cheating you are a disgrace to people who do real Reverse Engineering
        SetConsoleTextAttribute(h, 7);
        system("pause");
        return 1;
    }

    Binary.seekg(0, Binary.end); // get length of file
    int length = Binary.tellg();
    Binary.seekg(0, Binary.beg);
    char* buffer = new char[length]; // store length into Char Array
    if (DevMode == true) {
        SetConsoleTextAttribute(h, 3);
        cout << AY_OBFUSCATE("Reading ") << length << AY_OBFUSCATE(" characters of Binary Data ") << endl;
        SetConsoleTextAttribute(h, 7);
    } //debug

    Binary.read(buffer, length); // read data as a block

    if (Binary) // if read was succesful
    {
        if (DevMode == true) {
            SetConsoleTextAttribute(h, 3);
            cout << AY_OBFUSCATE("Buffer Generated") << endl;
            SetConsoleTextAttribute(h, 7);
        }
    } //debug
    else {
        SetConsoleTextAttribute(h, 4);
        cerr << AY_OBFUSCATE("An error occurred, restart the program. ") << endl; // literally
        SetConsoleTextAttribute(h, 7);
        if (DevMode == true) {
            SetConsoleTextAttribute(h, 4);
            cerr << AY_OBFUSCATE("error: only ") << Binary.gcount() << AY_OBFUSCATE(" could be read") << endl; // couldnt read the executable
        }
        SetConsoleTextAttribute(h, 7);
        //debug
        Binary.close(); // close the executable - free up memory
    }

    if (WriteBufferToFile == true) //debug
    {
        int num = 1024;
        char buffer3[1024]; // Get Current Working Dir
        _getcwd(buffer3, num); // store working dir into char array buffer
        convertToString(buffer3, (num)); // convert working dir char to a string
        if (_getcwd(buffer3, num) == NULL) // Checks to see if we got the Current Working Dir
        {
            SetConsoleTextAttribute(h, 4);
            cerr << AY_OBFUSCATE("An error occurred, try doing this in another directory, like your Desktop.") << endl;
            SetConsoleTextAttribute(h, 7);
            system("pause");
            return 1;
        }

        string BufferWriteDir = buffer3; // store buffer3 into a string
        BufferWriteDir += AY_OBFUSCATE("\\Buffer.txt"); // append the string with the filename you want to write too.
        SetConsoleTextAttribute(h, 3);
        cout << BufferWriteDir << endl;
        SetConsoleTextAttribute(h, 7);
        ofstream Buffer; // create ofstream obj for writing
        Buffer.open(BufferWriteDir); //put buffer.txt in scope to be worked on
        if (Buffer.fail()) // checks to see if we can get a handle to the file above
        {
            SetConsoleTextAttribute(h, 4);
            cerr << AY_OBFUSCATE("Cannot Open Or Find Buffer.txt.. We also couldn't create one, this is most likely your own fault. Maybe the directory is restricted?") << endl;
            int i;
            for (i = 0; i > 5; i++) {
                cout << AY_OBFUSCATE("Restart Your Game") << endl;
            }
            SetConsoleTextAttribute(h, 7);
            system("pause");
            return 1;
        }

        string s_a = convertToString(buffer, length); //convert buffer into string
        s_a.resize(length); //Resize string to be able to fit the buffer
        system("pause");
        //  cout << s_a;	// prints the entire buffer (in string form) to console - for debugging the BufferWriter.
        SetConsoleTextAttribute(h, 3);
        cout << AY_OBFUSCATE("Writing Buffer Size: ") << length << endl;
        SetConsoleTextAttribute(h, 7);
        system("pause");
        Buffer << s_a; //Write Buffer to file 
        Buffer.close(); //close ofstream obj - free up memory
    }

    SHA1 HashSHA1; // Create SHA1 Hash Object
    MD5 HashMD5; // Create MD5 Hash Object
    string InstanceHashMD5 = HashMD5(buffer, length); // store hash into string
    string InstanceHashSHA1 = HashSHA1(buffer, length); //store hash into string
    if (DevMode == true) {
        SetConsoleTextAttribute(h, 3);
        std::cout << AY_OBFUSCATE("Executables SHA1 Hash: ") << InstanceHashSHA1 << std::endl;
        std::cout << AY_OBFUSCATE("Executables MD5 Hash: ") << InstanceHashMD5 << std::endl;
        SetConsoleTextAttribute(h, 7);

        if (WriteHashToFile == true) {
            ofstream BuildHashWriter; // Initilize ofstream object for writing 
            string path = getenv(AY_OBFUSCATE("appdata")); // Get Local Environment Variable %APPDATA%
            path += AY_OBFUSCATE("\\BuildHash.txt"); //Appends the variable with \BuildHash.txt 
            BuildHashWriter.open(path.c_str()); // Open BuildHash.txt
            if (BuildHashWriter.fail()) //checks to see if the previous statement was succesful
            {
                SetConsoleTextAttribute(h, 4);
                cout << AY_OBFUSCATE("An Error Occured Writing Hashes to file") << endl;
                SetConsoleTextAttribute(h, 7);
                system("pause");
            }

            SetConsoleTextAttribute(h, 3);
            cout << AY_OBFUSCATE("BuildHash Location: ") << path << endl;
            SetConsoleTextAttribute(h, 7);

            BuildHashWriter << InstanceHashSHA1 << endl; //write SHA1 to file
            BuildHashWriter << InstanceHashMD5 << endl; //write MD5 to file

            SetConsoleTextAttribute(h, 3);
            cout << AY_OBFUSCATE("Build Hashes Written to Disk") << endl;
            SetConsoleTextAttribute(h, 7);
            system("pause");
            BuildHashWriter.close(); // close BuildHash.txt - free up memory
        }
    }

    string path2 = getenv(AY_OBFUSCATE("appdata")); // Get Local Environment Variable %APPDATA%
    path2 += AY_OBFUSCATE("\\BuildHash.txt"); //Appends the variable with \BuildHash.txt 
    ifstream GetBuildHashes; //initialize ifstream object for reading hashes
    GetBuildHashes.open(path2); // open hash file
    if (GetBuildHashes.fail()) // check if the operation was a success 
    {
        SetConsoleTextAttribute(h, 4);
        cerr << AY_OBFUSCATE("Unable to locate Build-Hashes, make sure you run the Installer first.") << endl;
        SetConsoleTextAttribute(h, 7);
        system("pause");
        return 1;
    }

    string SHA1BUILDHASH; // initialize SHA1 String
    string MD5BUILDHASH; // initialize md5 string
    GetBuildHashes >> SHA1BUILDHASH >> MD5BUILDHASH; // read hashes into strings 
    if (DevMode == true) {
        SetConsoleTextAttribute(h, 3);
        cout << AY_OBFUSCATE("Succesfully got BuildHashes from file") << endl;
        SetConsoleTextAttribute(h, 7);
        cout << SHA1BUILDHASH << endl;
        cout << MD5BUILDHASH << endl;
    }
    GetBuildHashes.close(); // close BuildHashes - free memory

    string BuildHashSHA1 = SHA1BUILDHASH; //initialize buildhash variables
    string BuildHashMD5 = MD5BUILDHASH;

    if (strcmp(InstanceHashSHA1.c_str(), BuildHashSHA1.c_str()) != 0) //integrity check
    {
        if (strcmp(InstanceHashMD5.c_str(), BuildHashMD5.c_str()) != 0) {
            SetConsoleTextAttribute(h, 4);
            cerr << AY_OBFUSCATE("Integrity Violation") << endl;
            SetConsoleTextAttribute(h, 7);
            system("pause");
            return 1;
        }
    }
    else {
        int status = 0;
        cout << AY_OBFUSCATE("Welcome To HotPockets Bypass Me V1") << endl;
        SetConsoleTextAttribute(h, 2);
        cout << AY_OBFUSCATE("You Have Passed Your Integrity Check.") << endl;
        SetConsoleTextAttribute(h, 7);

        status = _unlink(AY_OBFUSCATE("BypassMeAnticheatInstaller.exe")); // deletes the anticheat without sending it to recycling bin (unrecoverable)
        if ((status == 0) && (DevMode == true)) {
            SetConsoleTextAttribute(h, 3);
            cout << AY_OBFUSCATE("File Deleted Successfully!") << endl;
            SetConsoleTextAttribute(h, 7);
        }

    }

    // Stop measuring time and calculate the elapsed time
    long long int end = GetTickCount64();
    double elapsed = (end - begin) * 1e-3;
    if (elapsed > (double)8) //checks to see if the integrity check took longer than 8 seconds
    {
        SetConsoleTextAttribute(h, 4);
        cout << AY_OBFUSCATE("Hey.. That took way too long.. Did you set a breakpoint somewhere?") << endl;
        SetConsoleTextAttribute(h, 7);
        system("pause");
        return 1;
    }
    system("pause");
    delete[] buffer; // free up memory as buffer usually contains 200K+ Elements

    //game:

    float health = 100;
    float nexthealth = 90;
    float checker = 10;
    int
        var = 9;
    if (health != (nexthealth + 10)) // these checks see if people are scanning for the INT with CE or using Pointer Scans to change the health Variable.
    {
        SetConsoleTextAttribute(h, 4);
        cout << AY_OBFUSCATE("Sorry, but your gonna have to find another way, you have been detected.") << endl;
        SetConsoleTextAttribute(h, 7);
        system("pause");
        return 1;
    }

    if (health == 100) {
        SetConsoleTextAttribute(h, 15);
        cout << AY_OBFUSCATE("You Have ") << health << AY_OBFUSCATE(" Health. Everytime You Press A Button You Lose 10 Health") << endl;
        SetConsoleTextAttribute(h, 7);
    }

    if (health > 100) {
        SetConsoleTextAttribute(h, 4);
        cerr << AY_OBFUSCATE("Sorry, but your gonna have to find another way, you have been detected.") << endl;
        SetConsoleTextAttribute(h, 7);
        system("pause");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        health = nexthealth;
        nexthealth -= 10;
        system("pause");
        if (health != (nexthealth + 10) || (health != (checker *
            var))) {
            SetConsoleTextAttribute(h, 4);
            cerr << AY_OBFUSCATE("Sorry, but your gonna have to find another way, you have been detected.") << endl;
            SetConsoleTextAttribute(h, 7);
            system("pause");
            return 1;
        }
        if ((health == 0) || (checker == 0)) {
            checker = (checker + 10);
            checker = (checker / 2);
        }
        if ((health < 1) || (checker < 1) || (nexthealth < -5)) {
            SetConsoleTextAttribute(h, 4);
            cout << AY_OBFUSCATE("You Have Died, Better Luck Next Time.") << endl;
            SetConsoleTextAttribute(h, 15);
        }
        else {
            SetConsoleTextAttribute(h, 15);
            cout << AY_OBFUSCATE("You Have ") << health << AY_OBFUSCATE(" health, tread carefully.") << endl;
            SetConsoleTextAttribute(h, 7);
        }
        var = (var - 1);

        if (IsDebuggerPresent() == true) {
            SetConsoleTextAttribute(h, 4);
            cout << AY_OBFUSCATE("There is currently a debugger attached to the process. Get a better Debugger.") << endl; // Shitty Debugger Checks
            SetConsoleTextAttribute(h, 7);
        }
    }

    if (health > 0) {
        SetConsoleTextAttribute(h, 15);
        cout << AY_OBFUSCATE("Oppenent: What is this Trickery, it can't be!") << endl;
        SetConsoleTextAttribute(h, 7);
        system("pause");
        SetConsoleTextAttribute(h, 15);
        cout << AY_OBFUSCATE("*Opponent Flees in Fear*") << endl;
        SetConsoleTextAttribute(h, 7);
        system("pause");
        SetConsoleTextAttribute(h, 2);
        cout << AY_OBFUSCATE("If you made it here you won, I am impressed. Heres a cookie.") << endl;
        SetConsoleTextAttribute(h, 7);
    }
    system("pause");
}

string convertToString(char* a, int size) // converts char array to string
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        // iterate through all elements and build a string out of them
        s = s + a[i];
    }

    return s;
}