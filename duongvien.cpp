#include <bits/stdc++.h>
using namespace std;

int n, m; // Kï¿½ch thu?c ma tr?n
int a[100][100], d[101][101]={0}; // Ma tr?n d?u vï¿½o
int dx[4] = {0, -1, 0, 1}; // Hu?ng di chuy?n: Tï¿½y, B?c, ï¿½ï¿½ng, Nam
int dy[4] = {-1, 0, 1, 0};
int sx = -1, sy = -1; // T?a d? b?t d?u
bool vis[100][100] = {0}; // Ma tr?n dï¿½nh d?u cï¿½c ï¿½ dï¿½ tham
int Br =30, b=0; // Nang lu?ng ban d?u c?a robot
int rx =-1, ry =-1;
int lastx =-1, lasty =-1; // T?a d? cu?i c?a robot

stack<pair<int, int>> F; // Stack d? duy?t DFS
//map<pair<int, int>, pair<int, int>> parent; // Luu cha c?a m?i ï¿½ trong cï¿½y DFS
pair<int, int> pa[100][100]; // Luu cha c?a m?i ï¿½ trong cï¿½y DFS

bool runoff = true; // Bi?n ki?m tra xem cï¿½ thoï¿½t kh?i ma tr?n hay khï¿½ng
bool isEn = true;
bool isIn = true;
vector<pair<int, int>> path[100];
int cntroute=0;

void printf(){
    cout<<"=============="<<endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << d[i][j] << " "; // In ra ma tr?n kho?ng cï¿½ch
        }
        cout << endl;
    }
}


void printroute() {

    for (int i = 0; i < path[cntroute].size(); i++) {
        cout << "(" << path[cntroute][i].first << "," << path[cntroute][i].second << ")"<<endl;
    }

    pair<int,int> p = path[cntroute][path[cntroute].size()-1];
    cout<<"\n Go back the source "<<endl;
    while (p.first != sx || p.second != sy) {

        p = pa[p.first][p.second];

        cout << "(" << p.first << "," << p.second << ")"<<endl;
        
    }

}

void insertroute( int x, int y) {
    path[cntroute].clear();
   //   path[cntroute].push_back({x, y});
    pair<int,int> p ={x,y};
   
    while (p.first != sx || p.second != sy) {

        p = pa[p.first][p.second];
       path[cntroute].push_back({p.first, p.second});
        
    }
 
//  cout<<"Insert route"<<endl;
//     for (auto it : path[cntroute]) {
//         cout << "(" << it.first << "," << it.second << ")"<<endl;
//     }

    reverse(path[cntroute].begin(), path[cntroute].end());
   
    
}

void vien1(int x, int y){
    if (d[x][y] == 0 && (x != sx || y != sy)) return;

    for ( int k =0; k<4;k++){
        int nx = x + dx[k]; // Tï¿½nh t?a d? ï¿½ ti?p theo
        int ny = y + dy[k]; // Tï¿½nh t?a d? ï¿½ ti?p theo

        if (nx>=0 && nx<n && ny>=0 && ny<m && a[nx][ny] != 1 && (nx != sx || ny != sy) ){
            if (d[nx][ny]==0){
                if (d[x][y]+1 > Br/2) continue;
                d[nx][ny] = d[x][y] + 1; // C?p nh?t kho?ng cï¿½ch t? ï¿½ b?t d?u
              //  F.push({nx, ny}); // Thï¿½m ï¿½ vï¿½o stack
                pa[nx][ny] = {x,y}; // Luu cha c?a ï¿½ hi?n t?i
            }
            else if (d[nx][ny] > d[x][y] + 1) {
                d[nx][ny] = d[x][y] + 1; // C?p nh?t kho?ng cï¿½ch t? ï¿½ b?t d?u
              //  F.push({nx, ny}); // Thï¿½m ï¿½ vï¿½o stack
                pa[nx][ny] = {x,y}; // Luu cha c?a ï¿½ hi?n t?i
            }
            else 
            // if (d[nx][ny] == d[x][y] + 1) {
            //     // N?u kho?ng cï¿½ch b?ng nhau, khï¿½ng lï¿½m gï¿½ c?
            //     pa[nx][ny] = {x,y}; // Luu cha c?a ï¿½ hi?n t?i 
            //     }
            //  else 
             if (d[nx][ny] != 0 && (d[nx][ny] < d[x][y]-1)) {
             	d[x][y]= d[nx][ny]+1;
             	pa[x][y] = {nx,ny};
             	vien1(x,y);
			 }
        }
    }
  //  printf(); // In ra ma tr?n kho?ng cï¿½ch
}
void dfs(int x, int y){

  if (isIn)
   path[cntroute].push_back({x,y});
    //cout<<"xet "<<x<<" "<<y<<" "<<d[x][y]<<"  "<<" "<<b<<endl;
    lastx = x;
    lasty = y;
   

    if ( x != sx && y !=sy && vis[pa[x][y].first][pa[x][y].second] == 0) {
        cout<<x<<" "<<y<<endl;
        //b++;
        return;
    } // N?u ï¿½ dï¿½ tham thï¿½ d?ng l?i
    //if (x == sx && y ==sy) continue;

   // cout<<"xet "<<x<<" "<<y<<" "<<b<<endl;
    vis[x][y] = 1; // ï¿½ï¿½nh d?u ï¿½ hi?n t?i lï¿½ dï¿½ tham
    vien1(x,y);

    //duy?t cac duong vien

    for ( int k =0; k<4;k++){
        int nx = x + dx[k]; // Tï¿½nh t?a d? ï¿½ ti?p theo
        int ny = y + dy[k]; // Tï¿½nh t?a d? ï¿½ ti?p theo

        if (nx>=0 && nx<n && ny>=0 && ny<m && a[nx][ny] != 1 ){
           // d[nx][ny] = d[x][y] + 1; // C?p nh?t kho?ng cï¿½ch t? ï¿½ b?t d?u
          
            vien1(nx,ny); // G?i d? quy cho ï¿½ ti?p theo
        }
     
    }
   // printf();

     if ( b + d[x][y] >= Br) {
        // in route 
        cout<<"Route "<<cntroute<<endl;
        printroute();
        isEn = false;
        isIn = false;
        cntroute++;
      // return;
    }

    //duyet o
    for (int k = 0; k < 4; k++) {
    
        int nx = x + dx[k]; // Tï¿½nh t?a d? ï¿½ ti?p theo
        int ny = y + dy[k]; // Tï¿½nh t?a d? ï¿½ ti?p theo

        if (nx >= 0 && nx < n && ny >= 0 && ny < m && a[nx][ny] != 1 && (vis[nx][ny] == 0  || d[nx][ny] > d[x][y]+1)) {
          	if (x != rx || y != ry ) 
            if (isEn) {
                b++;
               // path[cntroute].push_back({x,y});
            }
            
            if (d[nx][ny] < d[x][y]) {
               // b++;
               if (lastx != x || lasty != y ) 
              path[cntroute].push_back({x,y});
               //cout<<"back : "<<x<<" "<<y<<endl;
                return;
            }
            if (!isEn) {
                b = d[nx][ny];
                isIn = true;
                cout<<"Insert "<< nx<<" "<<ny<<endl;
                insertroute(nx,ny);
                isEn = true;
            }
           // b++;
            rx = x, ry = y; // Luu t?a d? ï¿½ hi?n t?i
            dfs(nx, ny); // G?i d? quy cho ï¿½ ti?p theo
        }
    }
    


}



int main() {
   // freopen("grid_matrix.txt", "r", stdin);
    cin >> n >> m ; // ï¿½?c kï¿½ch thu?c ma tr?n vï¿½ nang lu?ng ban d?u
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            if (a[i][j] == 2) {
                sx = i;
                sy = j; // Luu t?a d? b?t d?u
            }
        }
    }

    vis[sx][sy] = 1; // ï¿½ï¿½nh d?u ï¿½ b?t d?u lï¿½ dï¿½ tham
    dfs(sx,sy);
    printroute();
    printf(); // In ra ma tr?n kho?ng cï¿½ch
    cout<<"====================="<<endl;
    for ( int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout<<"("<<pa[i][j].first<<","<<pa[i][j].second<<")";
        }
        cout << endl;
    }

    return 0;
}
