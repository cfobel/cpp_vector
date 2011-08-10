#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <time.h>
#include <boost/foreach.hpp>
using namespace std;

struct timespec diff(struct timespec start, struct timespec end);

typedef map<string, double> duration_map_t;

struct foo_t {
    int x;
    int y;
    int z;
};


struct bar_t {
    vector<int> x;
    vector<int> y;
    vector<int> z;

    bar_t(int size)
        : x(vector<int>(size)), y(vector<int>(size)), z(vector<int>(size)) {}
};


int main() {
    duration_map_t durations;
    struct timespec start, end, delta;
    const int BIG = 500000;
    const int BIGGER = 500;

    vector<foo_t> foo_v(BIG);
    bar_t bar(BIG);

    {
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for(int k = 0; k < BIGGER; k++) {
        for(int i = 0; i < BIG; i++) {
            bar.x[i] = i;
            bar.y[i] = i + 1;
            bar.z[i] = i + 2;
        }
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    delta = diff(start, end);
    durations["struct of vectors"] = delta.tv_sec + delta.tv_nsec * 1e-9;
    }

    {
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);

    for(int k = 0; k < BIGGER; k++) {
        for(int i = 0; i < BIG; i++) {
            foo_v[i].x = i;
            foo_v[i].y = i + 1;
            foo_v[i].z = i + 2;
        }
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    delta = diff(start, end);
    durations["vector of structs"] = delta.tv_sec + delta.tv_nsec * 1e-9;
    }

    BOOST_FOREACH(duration_map_t::value_type &item, durations) {
        cout << item.first << ": " << item.second << endl;
    }

    return 0;
}


struct timespec diff(struct timespec start, struct timespec end) {
    struct timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}
