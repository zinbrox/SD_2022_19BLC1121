#include<bits/stdc++.h>
using namespace std;
class Chess {
    //Grid
    vector<vector<pair<string, int>>> grid;
    //Start and End of grid (0-indexed)
    int start, end;
    bool turn;
    vector<string> action;
    string actionInput;
    
    int count1, count2;
    
    public:
    Chess() {
        for(int i=0;i<5;++i) {
            vector<pair<string, int>> temp(5, {"__", -1});
            grid.push_back(temp);
        }
        start = 0, end = 4;
        turn = 0;
        count1 = 5, count2=5;
    }
    
    void getInput() {
        system("clear");
        string input;
        cout<<"Enter your character names for pawns, User 1: "<<endl;
        for(int i=0;i<5;++i) {
            cout<<"Pawn "<<i+1<<": ";
            cin>>input;
            auto it = find_if(grid[0].begin(), grid[0].end(), [input](const pair<string, int>& p){
                return p.first == input;
            }); 
            if(it != grid[0].end()){
                cout<<"Name already exists. Please enter a new name"<<endl;
                i-=1;
                continue;
            }
            grid[0][i] = {input, 0};
        }
        
        system("clear");
        cout<<"Enter your character names for pawns, User 2: "<<endl;
        for(int i=0;i<5;++i) {
            cout<<"Pawn "<<i+1<<": ";
            cin>>input;
            auto it = find_if(grid[4].begin(), grid[4].end(), [input](const pair<string, int>& p){
                return p.first == input;
            }); 
            if(it != grid[4].end()){
                cout<<"Name already exists. Please enter a new name"<<endl;
                i-=1;
                continue;
            }
            grid[4][i] = {input, 1};
        }
    }
    
    void printGrid() {
        system("clear");
        for(int i=0;i<5;++i) {
            for(int j=0;j<5;++j)
                cout<<grid[i][j].first<<" ";
            cout<<endl;
        }
    }
    vector<string> getAction(string s) {
        size_t pos = 0;
        string token;
        vector<string> action;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            action.push_back(token);
            s.erase(0, pos + delimiter.length());
        }
        action.push_back(s);
        return action;
    }
    
    void play() {
        cout<<"User "<<turn<<", enter your action: ";
        cin>>actionInput;
        action = getAction(actionInput);
        
        int curX=0, curY=0;
        for(int i=start;i<=end;++i)
            for(int i=start;i<=end;++i)
                if(grid[i][j].first == action[0]) {
                    curX = i;
                    curY = j;
                }
        switch(action[1]) {
            case 'L':   if(curY-1 < start)
                            cout<<"Error move";
                            //go back here
                            
                        if(grid[curX][curY-1].second == turn)
                            cout<<"Same player character. Invalid Move!";
                            
                        if(grid[curX][curY-1].second == !turn)
                            cout<<"User "<<turn<<" has killed!";
                            //check if same also
                            
                            
                        grid[curX][curY-1] = {grid[curX][curY].first, turn};
                        grid[curX][curY] = {"__", -1};
                        break;
            case 'R':   if(curY+1 > end)
                            cout<<"Error move";
                            //go back here
                            
                        if(grid[curX][curY-1].second == turn)
                            cout<<"Same player character. Invalid Move!";
                            
                        if(grid[curX][curY+1].second == !turn)
                            cout<<"User "<<turn<<" has killed!";
                            
                            
                        grid[curX][curY+1] = {grid[curX][curY].first, turn};
                        grid[curX][curY] = {"__", -1};
                        break;
            case 'F':   if(curX-1 < start)
                            cout<<"Error move";
                            //go back here
                            
                        if(grid[curX][curY-1].second == turn)
                            cout<<"Same player character. Invalid Move!";
                            
                        if(grid[curX-1][curY].second == !turn)
                            cout<<"User "<<turn<<" has killed!";
                            
                        grid[curX-1][curY] = {grid[curX][curY].first, turn};
                        grid[curX][curY] = {"__", -1};
                        break;
            case 'L':   if(curX-+1 > end)
                            cout<<"Error move";
                            //go back here
                            
                        if(grid[curX][curY-1].second == turn)
                            cout<<"Same player character. Invalid Move!";
                            
                        if(grid[curX][curY].second == !turn)
                            cout<<"User "<<turn<<" has killed!";
                        grid[curX+1][curY] = {grid[curX][curY].first, turn};
                        grid[curX][curY] = {"__", -1};
                        break;
        }
        
        
    }
};
int main() {
    Chess g;
    g.getInput();
    g.printGrid();
    g.play();
}