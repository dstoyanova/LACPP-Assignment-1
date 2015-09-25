#include <iostream>
#include <cmath>
#include <thread>
#include <mutex>
#include <vector>
#include <ctime>

using namespace std;

// Holds the final result
float sum = 0.0;
mutex m;
clock_t t;

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
    int trapezes, threads;
    do {
        cout << "Enter the number of trapezes: ";
        cin >> trapezes;
        cout << "Enter the number of threads: ";
        cin >> threads;
    } while (threads > trapezes);
    
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
    
    t = clock();
    for (auto &t : th) {
        t.join();
    }
    t = clock() - t;
    
    cout << "Sum = " << sum << endl;
    cout << "It takes " << (float)t / CLOCKS_PER_SEC << endl;
    
    return 0;
} 