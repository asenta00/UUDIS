#include <iostream>
#include <ctime>
// broj niti koje �elimo koristiti
const int N = 10;
// kernel: funkcija koju izvr�avaju niti grafi�ke kartice
__global__ void add (int *a, int *b, int *c)
{
int tid = threadIdx.x;
c[tid] = a[tid] + b[tid];
}
int main()
{
// inicijaliziramo sat da mo�emo pratiti vrijeme izvr�avanja
 std::clock_t start;
 double duration;
 start = std::clock();
int a[N], b[N], c[N];
//pokaziva�i na memoriju na grafi�koj kartici
 int *dev_a, *dev_b, *dev_c;
// alociranje memorije na grafi�koj kartici
 cudaMalloc( (void**)&dev_a, N * sizeof(int) );
 cudaMalloc( (void**)&dev_b, N * sizeof(int) );
 cudaMalloc( (void**)&dev_c, N * sizeof(int) );

// popunjavanje nizova a i b u glavnoj memoriji
 for (int i = 0; i < N; i++)
{
 a[i] = i;
b[i] = i;
 }
// kopiranje vrijednosti sa glavne memorije na memoriju grafi�ke kartice
 cudaMemcpy ( dev_a, a, N * sizeof(int), cudaMemcpyHostToDevice );
 cudaMemcpy ( dev_b, b, N * sizeof(int), cudaMemcpyHostToDevice );
// poziv kernela
// <<< broj blokova, broj niti po bloku>>>
// broj niti po bloku je maksimalno 512 zbog fizi�kih ograni�enja
 add<<<1,N>>>(dev_a, dev_b, dev_c);
 cudaMemcpy ( c, dev_c, N * sizeof(int), cudaMemcpyDeviceToHost );
 for (int i = 0; i < N; i++)
{
 std::cout << a[i] <<" "<< b[i] <<" "<< c[i] <<std::endl;
 }
 cudaFree (dev_a);
cudaFree (dev_b);
cudaFree (dev_c);
// sat
 duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
 std::cout << "Time taken: " << duration << '\n';
 return 0;
}