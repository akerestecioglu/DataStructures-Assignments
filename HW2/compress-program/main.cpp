//ALIHAN KERESTECIOGLU
//15.11.19
#include <iostream>
#include <string>
#include <fstream>
#include "HashTable.h"
#include "HashNode.h"
using namespace std;

void OpenFiles(ifstream & reader, ofstream & writer){
    reader.open("compin");
    #ifdef DENEME
    if (!reader.fail()) {
        cout << "SUCCESSFULLY OPENED THE FILE" << endl;
    }
    #endif
    
    writer.open("compout");
}

void CloseFiles(ifstream & reader, ofstream & writer){
    reader.close();
    writer.close();
}

void InitializeDictionary(HashTable<HashNode<string>> & dict){
    for (int i = 0; i < 256; i++) {
        char c = i;
        string s = "";
        s += c;
        HashNode<string> singleChar(i, s);
        dict.insert(singleChar, singleChar.hashFunc(dict.Size()));
    }
}

int returnCode(string toBePrinted, HashTable<HashNode<string>> & dict){
    HashNode<string> toBeSearched(0, toBePrinted);
    return (dict.find(toBeSearched, toBeSearched.hashFunc(dict.Size()))).Code();
}

void CompressFile(ifstream & reader, ofstream & writer, HashTable<HashNode<string>> & dict, const HashNode<string> & notFound){
    char ch;
    char backUp = (char) 0;
    int code = 256;    //THE FIRST CODE TO BE ASSIGNED IS 256
    while (!reader.eof()){
        string newKey = "";
        if(backUp == (char) 0){   //IF IT IS THE FIRST ITERATION
            reader.get(ch);
            newKey += ch;
        }
        else{
            newKey += backUp;
        }
        HashNode<string> newNode(code, newKey);
        while (!reader.eof() && (dict.find(newNode, newNode.hashFunc(dict.Size())) != notFound)) {   //BU SATIR DEĞİŞTİ!!!!!!!!!!!!!!!!!!!!!! //FIND THE LONGEST SEQUENCE IN THE DICTIONARY AND ADD IT ONE MORE CHARACTER
            reader.get(ch);
            newKey += ch;
            newNode.updateNode(code, newKey);
        }
        if(!dict.isFull()){
            dict.insert(newNode, newNode.hashFunc(dict.Size()));
            code++;
        }
        
        string toBePrinted = newKey.substr(0, newKey.size() -1);   //PRINT THE LONGEST SEQUENCE IN THE DICTIONARY
        
        writer << returnCode(toBePrinted, dict) << " ";   //WRITE IT TO THE OUTPUT FILE
        
        backUp = newKey.at(newKey.length() - 1);   //SET BACKUP TO THE CHARACTER AFTER THE STRING THAT WAS PRINTED
    }
}


int main() {
    ifstream reader;
    ofstream writer;
    OpenFiles(reader, writer);
    HashNode<string> notFound(-1, "NOT FOUND");
    HashTable<HashNode<string>> dictionary(notFound, 4096);
    InitializeDictionary(dictionary);
    CompressFile(reader, writer, dictionary, notFound);
    CloseFiles(reader, writer);
    
    return 0;
}
