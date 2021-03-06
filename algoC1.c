#include<stdio.h>
#include <stdlib.h>
#define NEW(p,n) {p = malloc((n)*sizeof(p[0]));}


typedef struct slobj_ {
  struct slobj_ *next;// 後の要素へのポインタ
  int j;// j 列目
  double v;// 行列の(i, j) 要素
}* slobj;

typedef struct {
  slobj head;// 先頭要素のポインタ
  slobj tail;// 末尾要素のポインタ
}* slist;


typedef struct {
 int n, m; // 行数,列数
 slist* A; // 行ベクトルを表すリストの配列
}* smatrix;

slist slist_new(){  //空のリストの作成
  slist L;
  NEW(L,1);
  L->head = NULL;
  L->tail = NULL; // リストの要素が無いことを表す
  return L;
}

smatrix create_smatrix(int n, int m){ //行列のメモリ確保
  int i;
  smatrix M;
  NEW(M,1);   //一次元配列を用意
  M->n =n;
  M->m =m;
  NEW(M->A, n);  //各行に非ゼロ要素のリストを用意
  for (i = 0; i < n; i++) {
    M->A[i] = slist_new();
  }
  return M;
}

void slist_insert(slist L, slobj r){  //rをLに挿入
  slobj f;
  if (L->head==NULL){
    L->head=r;
  }
  else{
    if(r->j <= (L->head)->j){
      r->next = L->head;
      L->head = r;
    }
        else{
      f=L->head;
      slobj p;
      while( f != NULL && r->j > f->j){
        p=f;
        f=f->next;
      }
      r->next = f;
      p->next = r;
    }
  }
}

slobj slobj_new(int a,double b){  //リストの要素の作成
  slobj p;
  NEW(p,1);
  p->j = a;
  p->v = b;
  p->next = NULL; // 必ず初期化しておく
  return p;
}

double slist_join(slist L1, slist L2){  //二つのリスト（行列の計算する列）から同じ物を取り出す。
  double x=0;
    slobj p1=L1->head;
    slobj p2=L2->head;
    while (p1!=NULL && p2!=NULL) {
      if (p1->j!=p2->j) {
        if(p1->j<p2->j){
          p1=p1->next;
        }else{
          p2=p2->next;
        }
      }else{
        double a=(p1->v)*(p2->v);
        slobj p= slobj_new(p1->j,a);
        x+=p->v;
        p1=p1->next;
        p2=p2->next;
        }
    }
    return x;
}


int main(){
  int a,i,n,m;
  double v;
  scanf("%d %d",&n,&m );   //行列のサイズ n行m列
  smatrix M=create_smatrix(n,m);  //読み込みM
  for (i = 0; i < n; i++) {
    while(scanf("%d",&a) !=EOF && a != -1) {   //行列の読み込みは列数の後に要素を入力し最後の要素の後に-1を入力
      scanf("%lf",&v);
      slobj B= slobj_new(a-1,v);
      slist_insert(M->A[i],B);
    }
  }
  smatrix O=create_smatrix(m,n); //転置O
  for (i = 0; i < m; i++) {
    while(scanf("%d",&a) !=EOF && a != -1) {
      scanf("%lf",&v);
      slobj C= slobj_new(i,v);
      slist_insert(O->A[a-1],C);
    }
  }
  printf("%d %d\n",n,n);
  for (int p = 0; p < n; p++) {
    for (int q = 0; q < m; q++) {
      double x=slist_join(M->A[p],O->A[q]);
      if(x!=0){
        printf("%d %lf ",q+1,x);
      }
    }
    printf("-1\n");
  }
  return 0;
}
