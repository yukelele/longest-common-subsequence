// Yuki Mano, ysm@umail.ucsb.edu

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>

using namespace std;

struct Matrix {
  vector<vector<int>> length_LCS;
  vector<vector<char>> direction_LCS;
};

// function prototypes
Matrix find_LCS_length(vector<vector<int>> c, vector<vector<char>> b, string x, string y, int row, int col); // return a pair matrix of the LCS length and the LCS direction
void print_LCS(vector<vector<char>> b, string x, int row, int col); // print out the given string's LCS
vector<vector<pair<int,int>>> find_all_LCS(vector<vector<int>> c, string x, string y, int row, int col); // find all LCS in the given strings

// run
int main(int argc, char* argv[]){

  bool all_LCS = false;
  if(argc == 2){
    string all = argv[1];
    if(all == "-all")
       all_LCS = true;
  }

  int round;
  cin >> round; 
  while(round>0){
    
    string x,y;
    cin >> x;
    cin >> y;
    int row = x.length()+1;
    int col = y.length()+1;

    vector<vector<int>> m_length;
    m_length.resize(row, vector<int>(col, 0));

    vector<vector<char>> m_direction;
    m_direction.resize(row, vector<char>(col, '_'));

    Matrix matrix = find_LCS_length(m_length,m_direction,x,y,row,col);

    if(all_LCS){

      vector<vector<pair<int,int>>> m = find_all_LCS(matrix.length_LCS,x,y,row,col); 

      set<vector<pair<int,int>>> sim (make_move_iterator(m.begin()), make_move_iterator(m.end()));

      string result = "";
      for(auto f : sim){
        result += "(";
        for(auto g : f){
          result += "<" + to_string(g.first) + ", " + to_string(g.second) + ">, "; 
        }
        result.pop_back();
        result.pop_back();
        result += ")\n";
      }
      cout << result << endl;
    }

    else{
      cout << matrix.length_LCS[row-1][col-1] << " ";
      print_LCS(matrix.direction_LCS,x,row,col);
      cout << endl;
    }
    
/*
//print out table 
   //cout << "row = " << row << endl;
   //cout << "col = " << col << endl;
   for(int i=0; i<row; i++){
      for(int j=0; j<col; j++){
        cout << matrix.length_LCS[i][j]; 
      }
      cout << "       ";
      for(int j=0; j<col; j++){
        cout << matrix.direction_LCS[i][j]; 
      }
      cout << endl;
    }
    cout << endl;
//////////////
*/

 

  round--;
  }

  return 0;
}

// return a pair matrix of the LCS length and the LCS direction
Matrix find_LCS_length(vector<vector<int>> c, vector<vector<char>> b, string x, string y, int row, int col){

  Matrix m;



  
  for(int i=1; i<row; i++){
    for(int j=1; j<col; j++){
      if(x.at(i-1) == y.at(j-1)){
        c[i][j] = c[i-1][j-1] + 1;
        b[i][j] = 'D';
      }
      else if(c[i-1][j] >= c[i][j-1]){
        c[i][j] = c[i-1][j];
        b[i][j] = 'U';
      }
      else{
        c[i][j] = c[i][j-1];
        b[i][j] = 'L';
      }
    }
  }  
  m.length_LCS = c;
  m.direction_LCS = b;
  return m;
}

// print out the given string's LCS
void print_LCS(vector<vector<char>> b, string x, int row, int col){
  
  if(row<=0 || col<=0)
    return;

  if(b[row-1][col-1] == 'D'){
    print_LCS(b,x,row-1,col-1);
    cout << x.at(row-2);
  }
  else if(b[row-1][col-1] == 'U'){
    print_LCS(b,x,row-1,col);
  }
  else{
    print_LCS(b,x,row,col-1);
  }
} 

// find all LCS in the given strings
vector<vector<pair<int,int>>> find_all_LCS(vector<vector<int>> c, string x, string y, int row, int col){

  if(row<=1 || col<=1){
    vector<vector<pair<int,int>>> v(1);
    return v;
  }

  if(x.at(row-2) == y.at(col-2)){
    
    vector<vector<pair<int,int>>> lcs = find_all_LCS(c,x,y,row-1,col-1);

    vector<vector<pair<int,int>>> top;
    if(c[row-2][col-1] > c[row-1][col-2]){
      top = find_all_LCS(c,x,y,row-1,col);
    }
    vector<vector<pair<int,int>>> left;
    if(c[row-2][col-1] < c[row-1][col-2]){
      left = find_all_LCS(c,x,y,row,col-1);
    }
    top.insert(top.end(), left.begin(), left.end());

    vector<vector<pair<int,int>>>::iterator it = lcs.begin();
    for(it; it!=lcs.end(); ++it){
      pair<int,int> p = make_pair(row-1, col-1);
      it->push_back(p);
    }
    lcs.insert(lcs.end(),top.begin(),top.end());

    return lcs;
  }
    
  if(c[row-2][col-1] > c[row-1][col-2]){
    return find_all_LCS(c,x,y,row-1,col);
  }
  else if(c[row-2][col-1] < c[row-1][col-2]){
    return find_all_LCS(c,x,y,row,col-1);
  }
  else{
    vector<vector<pair<int,int>>> top = find_all_LCS(c,x,y,row-1,col);
    vector<vector<pair<int,int>>> left = find_all_LCS(c,x,y,row,col-1);
    top.insert(top.end(), left.begin(), left.end());
    return top; 
  }
}