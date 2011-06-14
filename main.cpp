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

int main() {
    duration_map_t durations;
    struct timespec start, end, delta;
    const int BIG = 500000000;
    vector <int> v;
    for ( int i = 0; i < BIG; i++ ) {
        v.push_back( i );
    }

    /* Run once to prime cache before taking timings. */
    int n = 0;
    for(vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
        n += *it;
    }

    n = 0;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    vector<int>::iterator iend = v.end();
    for(vector<int>::iterator it = v.begin(); it != iend; ++it) {
        n += *it;
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    delta = diff(start, end);
    durations["iterator"] = delta.tv_sec + delta.tv_nsec * 1e-9;

    n = 0;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    for(size_t i = 0; i < v.size(); ++i) {
        n += v[i];
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    delta = diff(start, end);
    durations["index"] = delta.tv_sec + delta.tv_nsec * 1e-9;

    n = 0;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    BOOST_FOREACH(int i, v) {
        n += i;
    }
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    delta = diff(start, end);
    durations["foreach"] = delta.tv_sec + delta.tv_nsec * 1e-9;

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
