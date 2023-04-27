#include <stdio.h>

int A[] = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};
int n = 12;

int main(){
    partition();
}

// 基準となるx以下の要素がpからiまでの範囲(iを含む)
// xより大きな要素がi+1からjまでの範囲(jを含まない)
int partition(int p, int r) {
    
    // 基準値は最後方要素
    int x = A[r];
    // グループ1(x以下の要素)中の最大Idx
    int i = p - 1;
    // グループ2(xより大きい要素)中の最大Idx-1
    int j;
    
    // 毎回の計算ステップでは必ずjを+1してA[j]をどちらのグループに属するか判定
    int t;
    for (j = p; j < r; j++) {
        // A[j]がx以下の場合、A[j]とA[i]を交換
        if (A[j] <= x) {
            i++;
            t = A[i];
            A[i] = A[j];
            A[j] = t;
        }
        
        // A[j]がxよりも大きい場合、要素の移動はなし
    }
    t = A[i + 1], A[i + 1] = A[r]; A[r] = t;
    return i + 1;
}