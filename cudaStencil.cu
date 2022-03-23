#include <iostream>
#include <ctime>

const int N = 10;
using namespace std;

// N mora biti parametar jer GPU ne vidi konstante iz memorije
__global__ void stancil(float *in, float *out, int N)
{
  	// Nadopisati kod ovdje
	// Id niti
	int tid = threadIdx.x;
}

int main()
{
        std::clock_t start;
        double duration;
        start = std::clock();

        float *d_in, *d_out;
        float *h_in, *h_out;

        size_t size = N * sizeof(float);

        h_in = (float *) malloc(size);
        h_out = (float *) malloc(size);

        if ((h_in == NULL) || (h_out == NULL))
        {
                cout << "Greska prilikom stvaranja host vektora." << endl;
                return -1;
        }

        for (int i = 0; i < N; i++)
        {
                h_in[i] = i+1;
                h_out[i] = 0;
        }

        cudaMalloc (&d_in, size);
        cudaMalloc (&d_out, size);

        cudaMemcpy (d_in, h_in, size, cudaMemcpyHostToDevice);
        stancil<<<(N/512+1),512>>>(d_in, d_out, N);
        cudaMemcpy(h_out, d_out, size, cudaMemcpyDeviceToHost);

        cout << "Rjesenje: " << endl;
        for (int i = 0; i < N; i++)
        {
                cout << h_in[i] << " " << h_out[i] << " " << endl;
        }

        cudaFree (d_in);
        cudaFree (d_out);

        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        cout << "Vrijeme izvrsavanja: "<< duration << endl;

        return 0;
}


