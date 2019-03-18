#ifndef OPTGEN_H
#define OPTGEN_H

using namespace std;

#include <vector>
#define OPTGEN_SIZE 128

struct optgen{
    vector<unsigned int> liveness_intervals;
    uint64_t num_cache;
    uint64_t access;
    uint64_t cache_size;

    void init(uint64_t size){
        num_cache = 0;
        access = 0;
        cache_size = size;
        liveness_intervals.resize(OPTGEN_SIZE, 0);
    }

    uint64_t get_optgen_hits(){
        return num_cache;
    }

    void set_access(uint64_t val){
        access++;
        liveness_intervals[val] = 0;
    }

    void set_fetch(uint64_t val){
        liveness_intervals[val] = 0;
    }

    bool is_Cache(uint64_t val, uint64_t endVal){
        bool cache = true;
        unsigned int count = endVal;
        while (count != val){
            if(liveness_intervals[count] >= cache_size){
                cache = false;
                break;
            }
            count = (count+1) % liveness_intervals.size();
        }

        if(cache){
            count = endVal;
            while(count != val){
                liveness_intervals[count]++;
                count = (count+1) % liveness_intervals.size();
            }
            num_cache++;
        }
        return cache;
    }
};

#endif