#include<stdio.h>
#include <stdlib.h>
#define NEW(p,n) {p = malloc((n)*sizeof(p[0]));}


typedef struct slobj_ {
  struct slobj_ *next;// 後の要素へのポインタ
  int j;// j 列目
  double v;// (i, j) 要素
}* slobj;

typedef struct {
  slobj head;// 先頭要素のポインタ
  slobj tail;// 末尾要素のポインタ
}* slist;


typedef struct {
 int n, m; // 行数,列数
 slist* A; // 行ベクトルを表すリストの配列
}* smatrix;

// OK
slist slist_new(){
  slist L;
  NEW(L,1);
  L->head = NULL;
  L->tail = NULL; // リストの要素が無いことを表す
  return L;
}


// O(N)
smatrix create_smatrix(int n, int m)
{
  int i;
  smatrix M;
  NEW(M,1);
  M->n =n;
  M->m =m;
  NEW(M->A, n);
  for (i = 0; i < n; i++) {
    M->A[i] = slist_new();
  }
  return M;
}


//O(N)
void slist_insert(slist L, slobj r){
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

// OK
slobj slobj_new(int a,double b)
{
  slobj p;
  NEW(p,1);
  p->j = a;
  p->v = b;
  p->next = NULL; // 必ず初期化しておく
  return p;
}

// O(N^2)?
smatrix read_smatrix(){
  int a,i,n;
  double v;
  scanf("%d %d",&n,&n );
  smatrix M=create_smatrix(n,n);
  smatrix O=create_smatrix(n,n);
  for (i = 0; i < n; i++) {
    while(scanf("%d",&a) !=EOF && a != -1) {
      scanf("%lf",&v);
      slobj B= slobj_new(a-1,v);
      slobj C= slobj_new(i,v);
      slist_insert(M->A[i],B);
      slist_insert(O->A[a-1],C);
    }
  }
  return O;
}


// O(N)
slobj slist_search(slist L, int k)
{
  slobj p;
  p = L->head;
  while (p != NULL && p->j != k) {
    p = p->next;
  }
  return p;
}


typedef double* row_vector;
typedef row_vector* matrix;

row_vector create_row_vector(int n)
{
int i;
row_vector V;
NEW(V, n);
for (i=0; i<n; i++) V[i] = 0.0;
return V;
}

// O(N)
matrix create_matrix(int n, int m)
{
  int i;
  matrix M;
  NEW(M, n);
    for (i=0; i<n; i++) {
      row_vector  V=create_row_vector(m);
      M[i]=V;
    }
    return M;
}

double slist_join(slist L1, slist L2){
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
  int a,i,n;
  double v;
  scanf("%d %d",&n,&n );
  smatrix M=create_smatrix(n,n);  //読み込みM
  smatrix O=create_smatrix(n,n);  //転置O
  for (i = 0; i < n; i++) {
    while(scanf("%d",&a) !=EOF && a != -1) {
      scanf("%lf",&v);
      slobj B= slobj_new(a-1,v);
      slobj C= slobj_new(i,v);
      slist_insert(M->A[i],B);
      slist_insert(O->A[a-1],C);
    }
  }
  printf("%d %d\n",n,n);
  for (int p = 0; p < n; p++) {
    for (int q = 0; q < n; q++) {
      double x=slist_join(M->A[p],O->A[q]);
      if(x!=0){
        printf("%d %lf ",q+1,x);
      }
    }
    printf("-1\n");
  }
  return 0;
}
