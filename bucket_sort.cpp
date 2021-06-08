#include <bits/stdc++.h>

using namespace std;

const int bucket_count = 10000; // 10 mil baldes..

//insertion_sort inicio
void insertion_sort(vector<int>& arr) {
    int aux, i, len = arr.size();
    for (int j = 1; j < len; j++) {
        aux = arr[j];
        i = j-1;
        while ((i >= 0) && (arr[i] > aux)) {
            arr[i+1] = arr[i];
            i = i - 1;
        }
        arr[i+1] = aux;
    }
}
//insertion_sort fim

 // heap_sort inicio
void heap_down(vector<int>& arr, int i) {
    int l = i*2+1;
    int r = i*2+2;

    int temp = i;   
    // short-circuit, se o elemento for uma folha ele não vai entrar 
    // em nenhum desses if's e a recursão vai parar.
    if(r < arr.size() && arr[temp] < arr[r])
        temp = r;
    if(l < arr.size() && arr[temp] < arr[l])
        temp = l;

    if(temp != i) {
        swap(arr[temp], arr[i]);
        heap_down(arr, temp);
    }
}
   
void heap_sort(vector<int>& arr) {
    int len = arr.size();
    // no intervalo [len/2, len] só há folhas, não precisamos chamar heap_down pra folhas, elas já são heaps,
    // por definição.
    for(int i = len/2; i >= 0; i--)
        heap_down(arr, i);

    // dá pra fazer sem esse temporario, mas prefiro assim
    vector<int> temp(arr.size());

    for(int i = len-1; i >= 0; i--) {
        // jogos os maiores caras da heap na parte de trás do array
        temp[i] = arr[0];
        // boto o último elemento da heap no inicio e chamo heap_down pra 
        // obter uma heap novamente..
        swap(arr[0], arr.back());
        arr.pop_back();
        heap_down(arr, 0);
    }

    arr = temp;
}
 // heap_sort fim

 //quick_sort inicio
 int Partition(vector<int>& arr, int low, int high) {
    int pivot, idx;
    idx   = low;
    pivot = high;

    for(int i=low; i < high; i++) {
        if(arr[i] < arr[pivot]) {
            swap(arr[i], arr[idx]);
            idx++;
        }
    }

    // troca o valor do pivor com o primeiro cara da esquerda pra direita que é maior que o pivor.
    swap(arr[pivot], arr[idx]);
    return idx;
}
 
void quick_sort(vector<int>& arr, int low, int high) {
    int idx;

    if(low < high) {
        idx = Partition(arr, low, high);

        // chama quick_sort recurisvamente para as duas metades do intervalo
        quick_sort(arr, low, idx-1);
        quick_sort(arr, idx+1, high);
    }
}
//quick_sort fim

//merge_sort inicio
void merge(vector<int>& arr, int l, int m, int r)
{
    int len1 = m - l + 1; // tamanho do primeiro array
    int len2 = r - m;     // tamanho do segundo array, com arr[m] não incluso.

    int left[len1], right[len2];

    for (int i = 0; i < len1; i++)
        left[i] = arr[l + i];
    
    for (int j = 0; j < len2; j++)
        right[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < len1 && j < len2) {
        if (left[i] <= right[j])
            arr[k] = left[i++];
        else
            arr[k] = right[j++];
        k++;
    }

    while (i < len1)
        arr[k++] = left[i++];

    while (j < len2)
        arr[k++] = right[j++];
}

// os comentários no mergesort foram todos provados informalmente por mim..
void merge_sort(vector<int>& arr, int l, int r) {
    // l nunca é maior que r.
    if(l>=r)
        return;
    // m nunca é menor que l
    int m = (l+r)/2;
    
    // l - m - r
    
    // o intervalo que será passado em cada um dos mergesorts seguintes
    // podem diferir em tamanho, no máximo, em 1.
    merge_sort(arr, l, m);
    merge_sort(arr, m+1, r);

    // o primeiro merge sempre terá [0..1] como intervalo
    merge(arr, l, m, r);
}
//merge_sort fim

//bucket_sort inicio
void bucket_sort(vector<int>& arr) {
    int max_e = *max_element(arr.begin(), arr.end());

    vector<vector<int>> buckets(bucket_count+1);

    for(int e : arr) {
        buckets[bucket_count * e/max_e].push_back(e);
    }

    // ordena os buckets
    for(auto& vet : buckets) {
        // coloque seu algoritmo de ordenação aqui
        
        // descomente o algoritmo abaixo que deseja testar
        
        //heap_sort(vet);
        //quick_sort(vet, 0, vet.size()-1);
        //insertion_sort(vet); //esse deve ter a melhor performance..
        //merge_sort(vet, 0, vet.size()-1);
    }

    int idx = 0;
    for(auto& vet : buckets) {
        for(int e : vet) {
            arr[idx++] = e;
        }
    }
}
//bucket_sort fim

int main() {
    int tam;
    cout << "Digite o tamanho do vetor" << endl;
    cin >> tam;

    srand(time(NULL));
    vector<int> arr(tam);

    for(int i = 0; i < tam; i++) arr[i] = rand() % 10000000;

    cout << "start" << endl;

    clock_t t = clock();

    bucket_sort(arr);

    t = clock() - t;

    cout << "Tempo de execucao: " << ((double)t)/((CLOCKS_PER_SEC)) << " milisegundos" << endl;

    return 0;
}