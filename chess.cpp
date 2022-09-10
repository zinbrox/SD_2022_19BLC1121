#include<bits/stdc++.h>
using namespace std;
class Chess {
    //Grid
    vector<vector<pair<string, pair<int,int>>>> grid;
    //Start and End of grid (0-indexed)
    int start, end;
    bool turn;
    vector<string> action;
    string actionInput;
    
    int countA, countB;
    
    public:
    Chess() {
        for(int i=0;i<5;++i) {
            vector<pair<string, pair<int, int>>> temp(5, {"___", {-1,-1}});
            grid.push_back(temp);
        }
        start = 0, end = 4;
        turn = 0;
        countA = 5, countB=5;
    }
    
    void getInput() {
        system("clear");
        string input;
        int hero;
        cout<<"Choose your characters and names, User 1: "<<endl;
        cout<<"For each enter the value: Pawn: 0, Hero1: 1"<<endl;
        for(int i=0;i<5;++i) {
            cout<<"Enter Character Type: ";
                cin>>hero;
            if(hero<0 || hero>1) {
                cout<<"Invalid hero"<<endl;
                i-=1;
                continue;
            }
            cout<<"Name: ";
            cin>>input;
            auto it = find_if(grid[0].begin(), grid[0].end(), [input](const pair<string, pair<int, int>>& p){
                return p.first == input;
            }); 
            if(it != grid[0].end()){
                cout<<"Name already exists. Please enter a new name"<<endl;
                i-=1;
                continue;
            }
            grid[0][i] = {input, {hero, 0}};
        }
        
        system("clear");
        cout<<"Choose your characters and names, User 2: "<<endl;
        for(int i=0;i<5;++i) {
            cout<<"Enter Character Type: ";
                cin>>hero;
            if(hero<0 || hero>1) {
                cout<<"Invalid hero"<<endl;
                i-=1;
                continue;
            }
            cout<<"Name: ";
            cin>>input;
            auto it = find_if(grid[4].begin(), grid[4].end(), [input](const pair<string, pair<int, int>>& p){
                return p.first == input;
            }); 
            if(it != grid[4].end()){
                cout<<"Name already exists. Please enter a new name"<<endl;
                i-=1;
                continue;
            }
            grid[4][i] = {input, {hero, 1}};
        }
    }
    
    void printGrid() {
        system("clear");
        for(int i=0;i<5;++i) {
            for(int j=0;j<5;++j) {
                if(grid[i][j].first=="___")
                    cout<<grid[i][j].first<<"\t";
                else
                    cout<<grid[i][j].first<<"H"<<grid[i][j].second.first<<"\t";
            }
            cout<<endl<<endl;
        }
    }
    vector<string> getAction(string s) {
        size_t pos = 0;
        string token;
        vector<string> action;
        while ((pos = s.find(":")) != std::string::npos) {
            token = s.substr(0, pos);
            action.push_back(token);
            s.erase(0, pos + 1);
        }
        action.push_back(s);
        return action;
    }
    
    void play() {
        prev: 
        cout<<"User "<<turn<<", enter your action: ";
        cin>>actionInput;
        action = getAction(actionInput);
        
        int curX=0, curY=0, hero=-1;
        char move = action[1].c_str()[0];
        for(int i=start;i<=end;++i)
            for(int j=start;j<=end;++j)
                if(grid[i][j].first == action[0]) {
                    curX = i;
                    curY = j;
                    hero = grid[i][j].second.first;
                }
                
        if(hero==1)
            if(hero1Play(curX, curY, move, hero) == -1)
                goto prev;
        
        bool b;
        switch(move) {
            case 'l':
            case 'L':   if(curY-1 < start) {
                            cout<<"Out of Bounds. Invalid Move!"<<endl;
                            goto prev;
                        }           
                            
                        if(grid[curX][curY-1].second.second == turn) {
                            cout<<"Same player character. Invalid Move!"<<endl;
                            goto prev;
                        }
                         
                        b = grid[curX][curY-1].second.second == !turn; 
                        grid[curX][curY-1] = {grid[curX][curY].first, {hero, turn}};
                        grid[curX][curY] = {"___", {-1,-1}};
                        printGrid();  
                        
                        if(b) {
                            cout<<"User "<<turn<<" has killed!"<<endl;
                            turn? countA-- : countB--;
                        }
                      
                        break;
             
            case 'r':           
            case 'R':   if(curY+1 > end) {
                            cout<<"Out of Bounds. Invalid Move!"<<endl;
                            goto prev;
                        }       
                            
                        if(grid[curX][curY+1].second.second == turn) {
                            cout<<"Same player character. Invalid Move!"<<endl;
                            goto prev;
                        }
                          
                        b = grid[curX][curY+1].second.second == !turn;
                        grid[curX][curY+1] = {grid[curX][curY].first, {hero, turn}};
                        grid[curX][curY] = {"___", {-1,-1}};
                        printGrid();    
                        
                        if(b) {
                            cout<<"User "<<turn<<" has killed!"<<endl;
                            turn? countA-- : countB--;
                        }
                            
                        break;
              
            case 'f':          
            case 'F':   if(curX-1 < start) {
                            cout<<"Out of Bounds. Invalid Move!"<<endl;
                            goto prev;
                        }
                            
                        if(grid[curX-1][curY].second.second == turn) {
                            cout<<"Same player character. Invalid Move!"<<endl;
                            goto prev;
                        }
                          
                        b = grid[curX-1][curY].second.second == !turn;
                        grid[curX-1][curY] = {grid[curX][curY].first, {hero, turn}};
                        grid[curX][curY] = {"___", {-1,-1}};  
                        printGrid(); 
                        
                        if(b) {
                            cout<<"User "<<turn<<" has killed!"<<endl;
                            turn? countA-- : countB--;
                        }
                        
                        break;
            
            case 'b':            
            case 'B':   if(curX-+1 > end) {
                            cout<<"Out of Bounds. Invalid Move!"<<endl;
                            goto prev;
                        }
                            
                        if(grid[curX+1][curY].second.second == turn) {
                            cout<<"Same player character. Invalid Move!"<<endl;
                            goto prev;
                        }
                        
                        b = grid[curX+1][curY].second.second == !turn;
                        grid[curX+1][curY] = {grid[curX][curY].first, {hero, turn}};
                        grid[curX][curY] = {"___", {-1,-1}};
                        printGrid();    
                        
                        if(b) {
                            cout<<"User "<<turn<<" has killed!"<<endl;
                            turn? countA-- : countB--;
                        }
                        
                        break;
        }
        if(countA == 0) {
            cout<<"Congratulations! Player 2 has won the game.";
            exit(0);
        }
        else if(countB == 0) {
            cout<<"Congratulations! Player 1 has won the game.";
            exit(0);
        }
        
        turn = !turn;
        goto prev;
        
    }
    
    int hero1Play(int curX, int curY, char move, int hero) {
        int b;
        switch(move) {
            case 'l':
            case 'L':   if(curY-2 < start) {
                            cout<<"Out of Bounds. Invalid Move!"<<endl;
                            return -1;
                        }           
                            
                        if(grid[curX][curY-2].second.second == turn || grid[curX][curY-1].second.second == turn) {
                            cout<<"Same player character. Invalid Move!"<<endl;
                            return -1;
                        }
                         
                        b = (grid[curX][curY-2].second.second == !turn)? 1 : 0 +  (grid[curX][curY-1].second.second == !turn)? 1 : 0; 
                        grid[curX][curY-2] = {grid[curX][curY].first, {hero, turn}};
                        grid[curX][curY] = {"___", {-1,-1}};
                        grid[curX][curY-1] = {"___", {-1,-1}};
                        printGrid();  
                        
                        if(b) {
                            cout<<"User "<<turn<<" has killed!"<<endl;
                            turn? countA-=b : countB-=b;
                        }
                      
                        break;
             
            case 'r':           
            case 'R':   if(curY+2 > end) {
                            cout<<"Out of Bounds. Invalid Move!"<<endl;
                            return -1;
                        }       
                            
                        if(grid[curX][curY+2].second.second == turn || grid[curX][curY+1].second.second == turn) {
                            cout<<"Same player character. Invalid Move!"<<endl;
                            return -1;
                        }
                          
                        b = (grid[curX][curY+2].second.second == !turn)? 1 : 0 + (grid[curX][curY+1].second.second == !turn)? 1 : 0;
                        grid[curX][curY+2] = {grid[curX][curY].first, {hero, turn}};
                        grid[curX][curY] = {"___", {-1,-1}};
                        grid[curX][curY+1] = {"___", {-1,-1}};
                        printGrid();    
                        
                        if(b) {
                            cout<<"User "<<turn<<" has killed!"<<endl;
                            turn? countA-=b : countB-=b;
                        }
                            
                        break;
              
            case 'f':          
            case 'F':   if(curX-1 < start) {
                            cout<<"Out of Bounds. Invalid Move!"<<endl;
                            return -1;
                        }
                            
                        if(grid[curX-2][curY].second.second == turn || grid[curX-1][curY].second.second == turn) {
                            cout<<"Same player character. Invalid Move!"<<endl;
                            return -1;
                        }
                          
                        b = (grid[curX-2][curY].second.second == !turn)? 1 : 0 || (grid[curX-1][curY].second.second == !turn)? 1 : 0;
                        grid[curX-2][curY] = {grid[curX][curY].first, {hero, turn}};
                        grid[curX][curY] = {"___", {-1,-1}};  
                        grid[curX-1][curY] = {"___", {-1,-1}};  
                        printGrid(); 
                        
                        if(b) {
                            cout<<"User "<<turn<<" has killed!"<<endl;
                            turn? countA-=b : countB-=b;
                        }
                        
                        break;
            
            case 'b':            
            case 'B':   if(curX-+2 > end) {
                            cout<<"Out of Bounds. Invalid Move!"<<endl;
                            return -1;
                        }
                            
                        if(grid[curX+2][curY].second.second == turn || grid[curX+1][curY].second.second == turn) {
                            cout<<"Same player character. Invalid Move!"<<endl;
                            return -1;
                        }
                        
                        b = (grid[curX+2][curY].second.second == !turn)? 1 : 0 + (grid[curX+1][curY].second.second == !turn)? 1 : 0;
                        grid[curX+2][curY] = {grid[curX][curY].first, {hero, turn}};
                        grid[curX][curY] = {"___", {-1,-1}};
                        grid[curX+1][curY] = {"___", {-1,-1}};
                        printGrid();    
                        
                        if(b) {
                            cout<<"User "<<turn<<" has killed!"<<endl;
                            turn? countA-=b : countB-=b;
                        }
                        
                        break;
        }
        if(countA == 0) {
            cout<<"Congratulations! Player 2 has won the game.";
            exit(0);
        }
        else if(countB == 0) {
            cout<<"Congratulations! Player 1 has won the game.";
            exit(0);
        }
        
        turn = !turn;
        return -1;
        
    }
};
int main() {
    Chess g;
    g.getInput();
    g.printGrid();
    g.play();
}