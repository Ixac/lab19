#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,  vector<string> &names, vector<int> &scores,vector<char> &grades){
    ifstream fin(filename);
    string textline;
    while(getline(fin,textline)){
    char name[100];
    int a,b,c;
    char z[] = "%[^:]: %d %d %d";
    sscanf(textline.c_str(),z,name,&a,&b,&c);
    names.push_back(name);
    scores.push_back(a+b+c);
    grades.push_back(score2grade(a+b+c));
    }
}

void getCommand(string &command,string &key){
string line;
char commandz[100];
char keyz[100];
char z[] = "%s %[^\n]";
cout << "Please input your command: ";
getline(cin , line);
sscanf(line.c_str() , z, commandz, keyz);
command = commandz;
key = keyz;
}

void searchName(vector<string> names, vector<int> scores,vector<char> grades , string key){
cout << "---------------------------------\n";
int fak = -1 ;
for(unsigned int i=0 ; i<names.size() ; i++){
    if (toUpperStr( names.at(i)) == key ) fak =i ;
}
if(fak != -1){
    cout << names.at(fak) << "'s score = "<< scores.at(fak) << "\n";
    cout << names.at(fak) << "'s grade = "<< grades.at(fak) << "\n";
}else{
    cout << "Cannot found.\n";
}
cout << "---------------------------------\n";
}

void searchGrade(vector<string> names, vector<int> scores,vector<char> grades , string key){
cout << "---------------------------------\n";
for (unsigned int i=0 ; i<grades.size() ; i++){
    if(grades.at(i) == *key.c_str()){
        cout << names.at(i) << " (" << scores.at(i) << ")\n";
    }
}
cout << "---------------------------------\n";
}
int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}