#include <iostream>
#include <vector>
using namespace std;

#define RR 729
#define CC 324
struct node{
		int r, c;
		node* up;
		node* down;
		node* left;
		node* right;
} H;
vector<node> col (CC);
vector<node> row (RR);
vector<int> solution;
inline void remove(int r){
		for(node* t=row[r].right; t!=&row[r]; t=t->right){
				for(node* tt=t->down; tt!=t; tt=tt->down){
					if(tt!=&col[t->c]){
						for(node* ttt=tt->right; ttt!=tt; ttt=ttt->right){
							ttt->up->down = ttt->down;
							ttt->down->up = ttt->up;
						}
					}
				}
				col[t->c].left->right = col[t->c].right;
				col[t->c].right->left = col[t->c].left;

		}
}

inline void recover(int r){
		for(node* t=row[r].right; t!=&row[r]; t=t->right){
				col[t->c].left->right = &col[t->c];
				col[t->c].right->left = &col[t->c];
				for(node* tt=t->down; tt!=t; tt=tt->down){
					if(tt!=&col[t->c]){
						for(node* ttt=tt->right; ttt!=tt; ttt=ttt->right){
								ttt->up->down = ttt;
								ttt->down->up = ttt;
						}
					}
				}
		}	
}

bool solve(){
		if(H.right == &H)
			return true;
		node* t;
		for (t=H.right->down; t!=H.right; t=t->down){
			remove(t->r);
			solution.push_back(t->r);
			if(solve()) return true;

			solution.pop_back();
			recover(t->r);
		}
		return false;
}

void link(int r, int c){
		node* newnode = new node;
		newnode->r=r;
		newnode->c=c;
		newnode->down = col[c].down;
		newnode->up = &col[c];
		newnode->down->up = newnode;
		newnode->up->down = newnode;
		newnode->right = row[r].right;
		newnode->left = &row[r];
		newnode->right->left = newnode;
		newnode->left->right = newnode;
}


int main(){
	    int r, c, n;
		for (int i=0; i<RR; i++){
				row[i].r=i;
				row[i].c=CC;
				if(i == RR-1) row[i].down = &H;
				else row[i].down = &row[i+1];
				if(i == 0) row[i].up = &H;
				else row[i].up = &row[i-1];
				row[i].left = &row[i];
				row[i].right = &row[i];
		}
		for (int i=CC-1; i>=0; i--){
				col[i].c = i;
				col[i].r = RR;
				if(i == CC-1) col[i].right = &H;
				else col[i].right = &col[i+1];
				if(i == 0) col[i].left = &H;
				else col[i].left = &col[i-1];
				col[i].down = &col[i];
				col[i].up = &col[i];
				if(i<81){
					for(int j=8; j>=0; j--)
						link((i/9%9)*81+j*9+i%9, i);	
				}
				else if(i<162){
					int box=(i-81)/9%9, num=(i-81)%9;
					for (int k=(box/3%3)*3+2; k>=(box/3%3)*3; k--)
						for (int j=box%3*3+2; j>=box%3*3; j--)
							link(k*81+j*9+num,i);
					
				}
				else if(i<243){
					for(int j=8; j>=0; j--)
						link(j*81+(i-162)/9%9*9+(i-162)%9, i);
				}
				else 
					for(int j=8; j>=0; j--)
						link((i-243)/9%9*81+(i-243)%9*9+j, i);
		}
		H.right = &col[0];
		H.left = &col[CC-1];
		H.up = &row[RR-1];
		H.down = &row[0];
		H.c = CC;
		H.r = RR;
		while(cin >> r >> c >> n){
			remove(r*81+c*9+(n-1));
			solution.push_back(r*81+c*9+(n-1));
		}
		if (!solve()) cerr << "invalid input" << endl;
		int answer[9][9];
		for (int i=0; i<solution.size(); i++){
				answer[solution[i]/9/9%9][solution[i]/9%9] = solution[i]%9+1;
		}
		for (int i=0; i<9; i++){
				for(int j=0; j<9; j++)
					cout << answer[i][j] << " ";
				cout << "\n";
		}

		return 0;
		
}
