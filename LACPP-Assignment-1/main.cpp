#include <iostream>
#include <cmath>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

// Holds the final result
float sum = 0.0;
mutex m;

float f(float x) {
    return 4.0 / (1.0 + x*x);
}

void func(float start,float end,float height) {
    for (float i = start; i < end; i += height) {
        m.lock();
        sum += (f(i) + f(i + height)) * height / 2.0;
        m.unlock();
    }
}

int main(int argc, const char * argv[]) {
    cout << "Enter the number of trapezes: ";
    int trapezes; cin >> trapezes;
    cout << "Enter the number of threads: ";
    int threads; cin >> threads;
    
    vector<thread> th;
    
    // Calculates the number of trapezes per thread
    float temp = floor((float)trapezes / (float)threads);
    
    float h = 1.0 / (float)trapezes;
    
    int br = 0;
    
    for (float i = 0.0; i < 1.0; i += temp * h) {
        // Our final thread will calculate the rest of the trapezes we have
        if (br == threads - 1) {
            th.push_back(thread(func,i,1.0,h));
            br++;
        }
        else {
            th.push_back(thread(func,i,temp*h,h));
            br++;
        }
    }
    
    for (auto &t : th) {
        t.join();
    }
    
    cout << "Sum = " << sum << endl;
    
    return 0;
} 