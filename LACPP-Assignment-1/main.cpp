#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

float sum = 0.0;
mutex m;

float f(float x) {
    return 4.0 / (1.0 + x*x);
}

void area(float a,float b,float c) {
    m.lock();
    sum += (a + b) * c / 2.0;
    m.unlock();
}

int main(int argc, const char * argv[]) {
    cout << "Enter the number of trapezes: ";
    int trapezes; cin >> trapezes;
    cout << "Enter the number of threads: ";
    int threads; cin >> threads;
    
    vector<thread> th;
    
    float h = 1.0 / (float)trapezes;
    
    for (float i = 0.0; i < 1.0; i += h) {
        th.push_back(thread(area,f(i),f(i+h),h));
    }
    
    for (auto &t : th) {
        t.join();
    }
    
    cout << "Sum = " << sum << endl;
    
    return 0;
} 