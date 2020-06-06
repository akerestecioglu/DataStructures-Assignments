//ALIHAN KERESTECIOGLU
//18.11.19

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

void OpenFiles(ifstream & reader, ofstream & writer){
    reader.open("compout");
    #ifdef DENEME
    if (!reader.fail()) {
        cout << "SUCCESSFULLY OPENED THE FILE" << endl;
    }
    #endif
    
    writer.open("decompout");
}

void CloseFiles(ifstream & reader, ofstream & writer){
    reader.close();
    writer.close();
}

void InitializeDictionary(string * dict){
    for (int i = 0; i < 256; i++) {
        char c = (char)i;
        string s = "";
        s += c;
        dict[i] = s;
    }
    for (int i = 256; i < 4096; i++) {
        dict[i] = "";
    }
}

void DecompressFile(ifstream & reader, ofstream & writer, string * dict){
    int code = 256;
    string compressed = "";
    char ch;
    while(!reader.eof()){
        reader.get(ch);
        compressed += ch;
    }
#ifdef DENEME
    cout << compressed << endl;
#endif
    int getCode;
    int prevCode;
    istringstream ss(compressed);
    ss >> getCode;
    prevCode = getCode;
    #ifdef DENEME
        cout << getCode << endl;
    #endif
    writer << dict[getCode];
    while (ss >> getCode) {
        if (getCode >= code) {
            string s = dict[prevCode] + dict[prevCode].at(0);
            writer << s;
            dict[code] = s;
            code++;
        }
        else {
            writer << dict[getCode];
            string s = dict[prevCode] + dict[getCode].at(0);
            dict[code] = s;
            code++;
        }
        prevCode = getCode;
    }
}

int main() {
    ifstream reader;
    ofstream writer;
    OpenFiles(reader, writer);
    string dictionary[4096];
    InitializeDictionary(dictionary);
    DecompressFile(reader, writer, dictionary);
    CloseFiles(reader, writer);
    
    return 0;
}

