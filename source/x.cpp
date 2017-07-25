#include<regex>
#include<string>
#include<iostream>
#include<sstream>
#include<vector>
using namespace std;

int main(){
    string g = "GET /job/id";
    string pu = "PUT /job";
    char *po = "POST /job/id/status";

    smatch match;
    regex match_exp("./.");
    if(regex_match(g,match, match_exp)){
        for(int i=0; i<match.size(); i++){
            cout << "match[i]" << match[i] << " ;";
        }
    }
    stringstream  data(po);
    vector<string> result;
    string line;
    while(std::getline(data,line,'/'))
    {
        cout << "strings = " << line << " " ;
        result.push_back(line); // Note: You may get a couple of blank lines
        // When multiple underscores are beside each other.
        //     }
    }
    cout << endl;
    return 0;
}
