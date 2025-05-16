// push code to github

#include <bits/stdc++.h>
using namespace std;

int n, m, Br; // K�ch thu?c ma tr?n
int a[100][100], d[101][101]={0}; // Ma tr?n d?u v�o
int dx[4] = {0, -1, 0, 1}; // Hu?ng di chuy?n: T�y, B?c, ��ng, Nam
int dy[4] = {-1, 0, 1, 0};
int sx = -1, sy = -1; // T?a d? b?t d?u
bool vis[100][100] = {0}; // Ma tr?n d�nh d?u c�c � d� tham
int b=0; // Nang lu?ng ban d?u c?a robot
int rx =-1, ry =-1;

stack<pair<int, int>> F; // Stack d? duy?t DFS
//map<pair<int, int>, pair<int, int>> parent; // Luu cha c?a m?i � trong c�y DFS
pair<int, int> pa[100][100]; // Luu cha c?a m?i � trong c�y DFS

bool runoff = true; // Bi?n ki?m tra xem c� tho�t kh?i ma tr?n hay kh�ng
bool isEn = true;
vector<pair<int, int>> path[100];
int cntroute=0;

void printf(){
    cout<<"=============="<<endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << d[i][j] << " "; // In ra ma tr?n kho?ng c�ch
        }
        cout << endl;
    }
}

void printPath(int x, int y) {
    if (x == sx && y == sy) {
        //cout << "(" << x << ", " << y << ")";
        return;
    }
    cout<<pa[x][y].first<<" "<<pa[x][y].second<<endl;
    printPath(pa[x][y].first, pa[x][y].second); // G?i d? quy cho cha c?a � hi?n t?i
}
void printroute() {
    cout<<"Route "<<cntroute<<endl;
    for (int i = 0; i < path[cntroute].size(); i++) {
        cout << "(" << path[cntroute][i].first << ", " << path[cntroute][i].second << ")"<<endl;
    }
    int tx = path[cntroute][path[cntroute].size()-1].first;
    int ty = path[cntroute][path[cntroute].size()-1].second;
    while (tx != sx || ty != sy) {
        tx = pa[tx][ty].first;
        ty = pa[tx][ty].second;
        cout << "(" << tx << ", " << ty << ")"<<endl;
        
    }
}

void insertroute( int x, int y) {
    path[cntroute].push_back({x, y});
    int tx = x;
    int ty = y;
    while (tx != sx || ty != sy) {
        tx = pa[tx][ty].first;
        ty = pa[tx][ty].second;
        path[cntroute].push_back({tx, ty});
    }
    reverse(path[cntroute].begin(), path[cntroute].end());
    
}

void vien1(int x, int y){
    if (d[x][y] == 0 && (x != sx || y != sy)) return;

    for ( int k =3; k>=0;k--){
        int nx = x + dx[k]; // T�nh t?a d? � ti?p theo
        int ny = y + dy[k]; // T�nh t?a d? � ti?p theo

        if (nx>=0 && nx<n && ny>=0 && ny<m && a[nx][ny] != 1 && (nx != sx || ny != sy) ){
            if (d[nx][ny]==0){
                if (d[x][y]+1 > Br/2) continue;
                d[nx][ny] = d[x][y] + 1; // C?p nh?t kho?ng c�ch t? � b?t d?u
              //  F.push({nx, ny}); // Th�m � v�o stack
                pa[nx][ny] = {x,y}; // Luu cha c?a � hi?n t?i
            }
            else if (d[nx][ny] > d[x][y] + 1) {
                d[nx][ny] = d[x][y] + 1; // C?p nh?t kho?ng c�ch t? � b?t d?u
              //  F.push({nx, ny}); // Th�m � v�o stack
                pa[nx][ny] = {x,y}; // Luu cha c?a � hi?n t?i
            }
            else if (d[nx][ny] == d[x][y] + 1) {
                // N?u kho?ng c�ch b?ng nhau, kh�ng l�m g� c?
                pa[nx][ny] = {x,y}; // Luu cha c?a � hi?n t?i 
                }
             else if (d[nx][ny] != 0 && (d[nx][ny] < d[x][y]-1)) {
             	d[x][y]= d[nx][ny]+1;
             	pa[x][y] = {nx,ny};
             	vien1(x,y);
			 }
        }
    }
  //  printf(); // In ra ma tr?n kho?ng c�ch
}
void dfs(int x, int y){

  
   // path[cntroute].push_back({x,y});
    cout<<"xet "<<x<<" "<<y<<" "<<d[x][y]<<"  "<<" "<<b<<endl;

   

    if ( x != sx && y !=sy && vis[pa[x][y].first][pa[x][y].second] == 0) {
        //b++;
        return;
    } // N?u � d� tham th� d?ng l?i
    //if (x == sx && y ==sy) continue;

   // cout<<"xet "<<x<<" "<<y<<" "<<b<<endl;
    vis[x][y] = 1; // ��nh d?u � hi?n t?i l� d� tham
    vien1(x,y);

    //duy?t cac duong vien

    for ( int k =3; k>=0;k--){
        int nx = x + dx[k]; // T�nh t?a d? � ti?p theo
        int ny = y + dy[k]; // T�nh t?a d? � ti?p theo

        if (nx>=0 && nx<n && ny>=0 && ny<m && a[nx][ny] != 1 ){
           // d[nx][ny] = d[x][y] + 1; // C?p nh?t kho?ng c�ch t? � b?t d?u
          
            vien1(nx,ny); // G?i d? quy cho � ti?p theo
        }
     
    }
   // printf();

     if ( b + d[x][y] >= Br) {
        // in route 
        cout<<"Route "<<cntroute<<endl;
        //printroute();
        isEn = false;
        cntroute++;
      // return;
    }

    //duyet o
    for (int k = 0; k < 4; k++) {
    
        int nx = x + dx[k]; // T�nh t?a d? � ti?p theo
        int ny = y + dy[k]; // T�nh t?a d? � ti?p theo

        if (nx >= 0 && nx < n && ny >= 0 && ny < m && a[nx][ny] != 1 && (vis[nx][ny] == 0  || d[nx][ny] > d[x][y]+1)) {
          	if (x != rx || y != ry ) 
            if (isEn) {
                b++;
               // path[cntroute].push_back({x,y});
            }
            
            if (d[nx][ny] < d[x][y]) {
               // b++;
                return;
            }
            if (!isEn) {
                b = d[nx][ny];
                insertroute(nx,ny);
                isEn = true;
            }
           // b++;
            rx = x, ry = y; // Luu t?a d? � hi?n t?i
            dfs(nx, ny); // G?i d? quy cho � ti?p theo
        }
    }
    


}



int main() {
    //freopen("grid_matrix.txt", "r", stdin);
    cin >> n >> m >> Br; // �?c k�ch thu?c ma tr?n v� nang lu?ng ban d?u
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            if (a[i][j] == 2) {
                sx = i;
                sy = j; // Luu t?a d? b?t d?u
            }
        }
    }

    vis[sx][sy] = 1; // ��nh d?u � b?t d?u l� d� tham
    dfs(sx,sy);
    printf(); // In ra ma tr?n kho?ng c�ch


    return 0;
}
