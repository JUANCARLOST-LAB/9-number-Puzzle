//This is a program that is going to be able to solve the 9 number puzzle, in which there are the numbers from 1 to 8 in a board, each once
//And you have to move pieces to the empty space and to arrange them in order, that is, to have the numbers 1 to 8 in order
// from left to right and from top to bottom
// 1 2 3
// 4 5 6
// 7 8 E  (E is the empty square)
// Each possible configuration of the board I interpreted it as a node and if we can reach one configuration form another one 
// by moving one piece then there is an edge between those nodes
// I used bfs to ensure that it does it in the least number of moves
// If it is not possible to solve the board introduced it displays a message saying its impossible

#include <bits/stdc++.h>
#include <unordered_map>

#define lli long long

using namespace std;


//Structure that keeps a state, the index of that state or node and what move to do to move to the next state
struct Node{
    int n, first_position, final_position;

    void init(int n, int f, int s){
        n = n;
        first_position = f;
        final_position = s;
    }
};

struct Graph{
    unordered_map<string,Node> mp;
    string actual;
    Node nodo_inicial;
    int idx;
    void init(){
        idx = 1;
        string aux;
        actual = "";
        //Generates the final state and then from there it will reach all other states with bfs
        for(int i = 1;i<=8;i++){
            aux = to_string(i);
            if(aux.size()==1) aux = '0'+aux;
            actual+=aux;
        }
        actual+="00";
        nodo_inicial.init(idx++, -1, -1);
    }
    //Function that starts at final position and uses Breadth First Search to search over all possible states (boards)
    void bfs(){
        queue<pair<string,Node> > q;
        q.push(make_pair(actual, nodo_inicial));
        while(!q.empty()){
            pair<string,Node> p = q.front();q.pop();
            if(mp.count(p.first)) continue;
            mp[p.first] = p.second;
            int zero_index;
            for(int i = 0;i<9;i++){
                if(p.first[2*i+1]=='0' && p.first[2*i]=='0'){
                    zero_index = 2*i;
                    break;
                }
            }
            add_board_up(q, p.first, zero_index);
            add_board_down(q, p.first, zero_index);
            add_board_left(q, p.first, zero_index);
            add_board_right(q, p.first, zero_index);
        }

    }

    //If it is possible to move a piece from the top to the empty space inserts that node (board) to the queue
    void add_board_up(queue<pair<string,Node> >& q, string board, int zero_index){
        if(zero_index<6) return;
        int exchange = zero_index - 6;
        add_node(q, board, zero_index, exchange);
    }

    //If it is possible to move a piece from the right to the empty space inserts that node (board) to the queue
    void add_board_right(queue<pair<string,Node> >& q, string board, int zero_index){
        if(zero_index%6>=4) return;
        int exchange = zero_index + 2;
        add_node(q, board, zero_index, exchange);
    }
    //If it is possible to move a piece from the left to the empty space inserts that node (board) to the queue
    void add_board_left(queue<pair<string,Node> >& q, string board, int zero_index){
        if(zero_index%6==0) return;
        int exchange = zero_index - 2;
        add_node(q, board, zero_index, exchange);
    }
    //If it is possible to move a piece from the bottom to the empty space inserts that node (board) to the queue
    void add_board_down(queue<pair<string,Node> >& q, string board, int zero_index){
        if(zero_index>=12) return;
        int exchange = zero_index + 6;
        add_node(q, board, zero_index, exchange);
    }


    //If that state or board (configuration) hasn't been visited or processed then it inserts it in the queue
    void add_node(queue<pair<string,Node> >& q, string board, int zero_index, int exchange){
        swap(board[zero_index], board[exchange]);
        swap(board[zero_index+1], board[exchange+1]);
        if(mp.count(board)) return;
        Node node;
        node.init(idx++, zero_index, exchange);
        q.push(make_pair(board, node));
    }

    //Receives a string, the board introduced by user and stores the moves to solve it
    void solve(string board){
        if(!mp.count(board)){
            cout<<"Is not possible to solve"<<endl;
        }else{
            cout<<"It is possible to solve"<<endl;
            Node node = mp[board];
            string aux1 = "", aux2 = "";
            vector<int> moves;
            while(node.final_position!=-1){
                int f = node.first_position, s = node.final_position;
                moves.push_back(board[f+1]-'0');
                swap(board[f], board[s]);
                swap(board[f+1], board[s+1]);
                node = mp[board];
            }
            //Prints the minimum required number of moves and which moves to make
            cout<<"Minimum number of moves: "<<moves.size()<<endl;
            for(auto it: moves){
                cout<<"Move "<<it<<endl;
            }
        }
    }


};

int main(){
    Graph graph;
    //Initializes and does bfs
    graph.init();
    graph.bfs();
    string s = "";
    int num;
    cout<<"Introduce the numbers in their order by row and column, for the empty space introduce a 0"<<endl;
    for(int i = 0;i<9;i++){
        cin >> num;
        s+="0";
        s+=num+'0';
    }
    graph.solve(s);
}