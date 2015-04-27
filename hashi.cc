#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

vector<vector<int> > V;
vector<vector<int> > zero;
vector<vector<int> > one; 
vector<vector<int> > two; 
vector<vector<int> > three; 
vector<vector<int> > four; 
vector<vector<int> > five;
vector<vector<int> > six;
vector<vector<int> > seven;
vector<vector<int> > eight;
int numberOfIsland, connectedIsland;

struct Neighbor{
		int left [3];
		int up [3];
		int right [3];
		int down [3];
};

struct island{
		int number;
		bool isOccupied;
		vector<int> state;
		vector<vector<int> >* possib;
		Neighbor neighbor;
		island() {                //<--needs change
				number = 0;
				state = zero[0];
				isOccupied = false;
		}
};


void getNeighbor(island (&hashi)[15][15], int x, int y){
		for (int i=x-1; i>=0; i--){
				if(hashi[i][y].number != 0){
					int newarr [] = {1,i,y};
					copy(newarr, newarr+3, hashi[x][y].neighbor.up); break;}
		}
		for (int i=x+1; i<15; i++){
				if(hashi[i][y].number != 0){
					int newarr [] = {1,i,y};
					copy(newarr, newarr+3, hashi[x][y].neighbor.down); break;}
		}
		for (int j=y-1; j>=0; j--){
				if(hashi[x][j].number != 0){
					int newarr [] = {1, x, j};
					copy(newarr, newarr+3, hashi[x][y].neighbor.left); break;}				
		}
		for (int j=y+1; j<15; j++){
				if(hashi[x][j].number != 0){
					int newarr [] = {1,x,j};
					copy(newarr, newarr+3, hashi[x][y].neighbor.right); break;} 
		}
}

void nextIsland(int current, int &next_x, int &next_y){
	if(current<V.size()-1){
	next_x = V[current+1][0];
	next_y = V[current+1][1];
	}else{
		next_x = V[current][0];
		next_y = V[current][1];
	}
} 

void connect (island (&hashi)[15][15], int x, int y, vector<int>& history){
			vector<int>& state = hashi[x][y].state;
			Neighbor& neighbor = hashi[x][y].neighbor;
			if(state[0] != 0 && (history)[0] == 0){
					for(int i=y-1; i>(neighbor.left)[2]; i--){
						hashi[x][i].isOccupied = true;
					}
					(hashi[(neighbor.left)[1]][(neighbor.left)[2]].state)[2] = state[0];
			}
			if(state[1] != 0 && (history)[1] == 0){
					for(int i=x-1; i>(neighbor.up)[1]; i--){
						hashi[i][y].isOccupied = true;
					}
					(hashi[(neighbor.up)[1]][(neighbor.up)[2]].state)[3] = state[1];
			}
			if(state[2] != 0 && (history)[2] == 0){
					for(int i=y+1; i<(neighbor.right)[2]; i++){
						hashi[x][i].isOccupied = true;
					}
					(hashi[(neighbor.right)[1]][(neighbor.right)[2]].state)[0] = state[2];
			}
			if(state[3] != 0 && (history)[3] == 0){
					for(int i=x+1; i<(neighbor.down)[1]; i++){
						hashi[i][y].isOccupied = true;
					}
					(hashi[(neighbor.down)[1]][(neighbor.down)[2]].state)[1] = state[3];
			}
}

void undo(island (&hashi)[15][15], int x, int y, vector<int>& history){
		vector<int>& state = hashi[x][y].state;
		Neighbor& neighbor = hashi[x][y].neighbor;
		if (state[0] !=0 && history[0] == 0){
				for(int i=y-1; i>(neighbor.left)[2]; i--){
						hashi[x][i].isOccupied = false;
				}
				(hashi[(neighbor.left)[1]][(neighbor.left)[2]].state)[2] = 0;
		}
		if (state[1] != 0 && history[1] == 0){
				for(int i=x-1; i>(neighbor.up)[1]; i--){
						hashi[i][y].isOccupied = false;
				}
				(hashi[(neighbor.up)[1]][(neighbor.up)[2]].state)[3] = 0;
		}
		if(state[2] != 0 && history[2] == 0){
				for(int i=y+1; i<(neighbor.right)[2];i++){
						hashi[x][i].isOccupied = false;
				}
				(hashi[(neighbor.right)[1]][(neighbor.right)[2]].state)[0] = 0;
		}
		if(state[3] != 0 && history[3] == 0){
				for (int i=x+1; i<(neighbor.down)[1]; i++){
						hashi[i][y].isOccupied = false;
				}
				(hashi[(neighbor.down)[1]][(neighbor.down)[2]].state)[1] = 0;
		}

}

void printHashi(island (&hashi)[15][15]){
	for (int i=0; i<V.size(); i++){
			cout<<V[i][0]<<" "<<V[i][1]<<" ";
			for (int j=0;j<4;j++){
					cout<<(hashi[V[i][0]][V[i][1]].state)[j];
			}
			cout << endl;
	}
}


int bridgeRmn(island (&hashi)[15][15], int x, int y){
		int sum=0;
		for(int i=0;i<4;i++){
				sum += (hashi[x][y].state)[i];
		}
		return hashi[x][y].number - sum;

}

bool isInterconnected(island (&hashi)[15][15], int x, int y, string from){
		if (connectedIsland == V.size()) {
				printHashi(hashi);
				exit(0);
		}
		if (from != "left" && (hashi[x][y].state)[0] != 0){
				connectedIsland ++;
				isInterconnected(hashi, (hashi[x][y].neighbor.left)[1], (hashi[x][y].neighbor.left)[2], "right");
		}
		if (from != "up" && (hashi[x][y].state)[1] != 0){
				connectedIsland ++;
				isInterconnected(hashi, (hashi[x][y].neighbor.up)[1], (hashi[x][y].neighbor.up)[2], "down");
		}
		if (from !="right" && (hashi[x][y].state)[2] != 0){
				connectedIsland ++;
				isInterconnected(hashi, (hashi[x][y].neighbor.right)[1], (hashi[x][y].neighbor.right)[2], "left");
		}
		if (from !="down" && (hashi[x][y].state)[3] != 0){
				connectedIsland ++;
				isInterconnected(hashi, (hashi[x][y].neighbor.down)[1], (hashi[x][y].neighbor.down)[2], "up");
		}
		return false;
}

bool is_working(island (&hashi)[15][15], int x, int y, vector<int>& history){
	vector<int>& state = hashi[x][y].state;
	Neighbor& neighbor = hashi[x][y].neighbor;
	vector<int>& left_state = (hashi[(neighbor.left)[1]][(neighbor.left)[2]].state);
	vector<int>& up_state = (hashi[(neighbor.up)[1]][(neighbor.up)[2]].state);
	vector<int>& right_state = (hashi[(neighbor.right)[1]][(neighbor.right)[2]].state);
	vector<int>& down_state = (hashi[(neighbor.down)[1]][(neighbor.down)[2]].state);

	if((state[0] != 0 && (neighbor.left)[0] == 0) || (state[1] != 0 && (neighbor.up)[0] == 0) || (state[2] != 0 && (neighbor.right)[0] == 0) || (state[3] != 0 && (neighbor.down)[0] == 0)  )  return false;
	if(left_state[2] != state[0] &&  bridgeRmn(hashi, (neighbor.left)[1], (neighbor.left)[2]) < state[0]) return false;
	if(up_state[3] != state[1] &&  bridgeRmn(hashi, (neighbor.up)[1], (neighbor.up)[2]) < state[1]) return false;
	if(right_state[0] != state[2] &&  bridgeRmn(hashi, (neighbor.right)[1], (neighbor.right)[2]) <  state[2]) return false;
	if(down_state[1] != state[3] &&  bridgeRmn(hashi, (neighbor.down)[1], (neighbor.down)[2]) < state[3]) return false;
	if(state[0] != 0 && (history)[0] == 0){
			for (int i=y-1; i>(neighbor.left)[2]; i--){
					if (hashi[x][i].isOccupied == true) return false;
			}
			if (bridgeRmn(hashi, (neighbor.left)[1], (neighbor.left)[2]) < state[0]) return false;
	}
	if(state[1] != 0 && (history)[1] == 0){
			for (int i=x-1; i>(neighbor.up)[1]; i--){
					if(hashi[i][y].isOccupied == true) return false;
			}
			if (bridgeRmn(hashi, (neighbor.up)[1], (neighbor.up)[2]) < state[1] ) return false;
	}
	if(state[2] != 0 && (history)[2] == 0){
			for (int i=y+1; i<(neighbor.right)[2]; i++){
					if(hashi[x][i].isOccupied == true) return false;
			}
			if (bridgeRmn(hashi, (neighbor.right)[1], (neighbor.right)[2]) < state[2]) return false;
	}
	if(state[3] != 0 && (history)[3] == 0){
			for (int i=x+1; i<(neighbor.down)[1]; i++){
					if(hashi[i][y].isOccupied == true) return false;
			}
			if (bridgeRmn(hashi, (neighbor.down)[1], (neighbor.down)[2]) < state[3]) return false;
	}

	return true;
}

bool satisfyCondition(vector<int>& history, vector<int>& a){
		for(int i=0; i<4; i++){
				if ((history)[i] != 0 && (history)[i] != a[i]) return false;
		}
		return true;
}

void Process(island (&hashi)[15][15], int x, int y, int current){
	if (current == numberOfIsland) {
		connectedIsland = 1;
		if (isInterconnected(hashi, x, y, "")){
			printHashi(hashi);
			exit (0);
		}
		return;
	}
	int Rmn = bridgeRmn(hashi, x, y), next_x, next_y, k=0;
	nextIsland(current, next_x, next_y);
	if(Rmn == 0) Process(hashi, next_x, next_y, current+1);
	else {
		vector<vector<int> >& possibList = *(hashi[x][y].possib);
		vector<int> history = hashi[x][y].state;
		for (int k=0; k < (hashi[x][y].possib)->size(); k++){
			if(satisfyCondition(history, possibList[k])){
				hashi[x][y].state = possibList[k];
				if (is_working(hashi, x, y, history)){
						connect(hashi, x, y, history);
						Process(hashi, next_x, next_y, current+1);
						undo(hashi,x,y,history);
				}
				hashi[x][y].state = history;
			}
		}
	}
	return;
} 

void addPossib(vector<vector<int> >*v, int x, int y, int z, int p){
		vector<int> a (4);
		a[0] = x; a[1] = y; a[2] = z; a[3] = p;
		v->push_back(a);
}
/*void printPossib(vector<vector<int> >& v){
		for (int i=0; i<v.size(); i++){
				for (int j = 0; j<4; j++){
						cout << v[i][j] << " ";
				}
				cout << " ";
		}
}*/

void calculatePossib(int num){
		vector<vector<int> >* v;
		if (num == 0) v = &zero;
		else if (num == 1) v = &one;
		else if(num == 2) v = &two;
		else if(num == 3) v = &three;
		else if(num == 4) v = &four;
		else if(num == 5) v = &five;
		else if(num == 6) v = &six;
		else if(num == 7) v = &seven;
		else if(num == 8) v = &eight;
		for (int x=0; x<3; x++){
				if (x==num){
						addPossib(v,x,0,0,0);
						break;
				}
				for (int y=0; y<3; y++){
					    if(num-x>6) break;
						if(x+y==num ){
							addPossib(v,x,y,0,0);
							break;
						}
						for (int z=0; z<3; z++){
							    if(num-x-y>4) break;
								if(x+y+z==num){
										addPossib(v,x,y,z,0);
										break;
								}
								int p = num-x-y-z;
								if(p <= 2) addPossib(v,x,y,z,p);
						}
				}
				
		}
}

int main(){
		int x, y, n;
		while (cin >> x >> y >> n){
			vector<int> a (3);
			a[0] = x; a[1] = y; a[2] = n;
			V.push_back(a);
		}

		for (int i=0; i<=8; i++){
			calculatePossib(i);
		}
		numberOfIsland = V.size();
		island hashi[15][15];
		for (int i = 0; i < V.size(); i++){
				hashi[V[i][0]][V[i][1]].number = V[i][2];
		}
		for (int i = 0; i<V.size(); i++){
				int number = hashi[V[i][0]][V[i][1]].number;
				vector<vector<int> >*& possib = hashi[V[i][0]][V[i][1]].possib;
				getNeighbor(hashi, V[i][0], V[i][1]);
				if(number == 0)	possib = &zero;
				else if(number == 1) possib = &one;
				else if(number == 2) possib = &two;
				else if(number == 3) possib = &three;
				else if(number == 4) possib = &four;
				else if(number == 5) possib = &five;
				else if(number == 6) possib = &six;
				else if(number == 7) possib = &seven;
				else if(number == 8) possib = &eight;

		}
		Process(hashi, V[0][0], V[0][1], 0);
		return 0;

}
