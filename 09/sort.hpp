#include <cstdint>
#include <cstddef>
#include <string>
#include <mutex>
#include <functional>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <cstdio>
#include <thread>

enum {
    SIZE = 1024 * 1024 * 8 / sizeof(size_t)
};

void one_file_split_sort(std::ifstream &fin, std::mutex &file_m, size_t &num, std::mutex &num_m) {
    auto *v = new uint64_t[SIZE]();
    size_t sz = 0;
    size_t cur_num;
    while (true) {
        sz = 0;
        for (size_t i = 0; i < SIZE; i++) {
            std::unique_lock <std::mutex> unique(file_m);
            uint64_t tmp;
            if (!fin.read((char *) &tmp, sizeof(tmp))) {
                break;
            }
            unique.unlock();
            v[sz++] = tmp;
        }
        if (sz == 0) {
            delete[](v);
            return;
        } else {
            std::lock_guard <std::mutex> guard(num_m);
            cur_num = num;
            num++;
        }
        std::sort(v, v + sz);
        std::stringstream my_out;
        my_out << "test" << cur_num << ".bin";
        std::ofstream fout(my_out.str(), std::ios::binary | std::ios::out);
        for (size_t i = 0; i < sz; i++) {
            fout.write((char *) &v[i], sizeof(v[i]));
        }
    }
}

void ultra_sort(const std::string &name_in, const std::string &name_out) {
    std::mutex m1, m2;
    std::vector <std::string> files_queue;
    std::ifstream fin(name_in, std::ios::binary | std::ios::in);
    size_t cnt_parts = 0;

    std::thread t1(one_file_split_sort, ref(fin), ref(m1), std::ref(cnt_parts), ref(m2));
    std::thread t2(one_file_split_sort, ref(fin), ref(m1), std::ref(cnt_parts), ref(m2));
    t1.join();
    t2.join();
    fin.close();

    for (size_t i = 0; i < cnt_parts; i++) {
        std::stringstream my_out;
        my_out << "test" << i << ".bin";
        files_queue.push_back(my_out.str());
    }

    std::ofstream fout(name_out, std::ios::binary | std::ios::out);
    std::vector <std::ifstream> file_range;
    std::priority_queue < std::pair < uint64_t, size_t >, std::vector < std::pair < uint64_t, size_t >>, std::greater<> > queue;

    file_range.reserve(files_queue.size());
    for (auto &name : files_queue) {
        file_range.emplace_back(name, std::ios::binary | std::ios::in);
    }

    for (size_t i = 0; i < file_range.size(); i++) {
        if (file_range[i].is_open()) {
            uint64_t tmp;
            if (file_range[i].read((char *) &tmp, sizeof(tmp))) {
                queue.push(std::make_pair(tmp, i));
            }
        }
    }

    while (true) {
        if (queue.empty()) {
            break;
        }
        uint64_t tmp;
        size_t i;
        std::tie(tmp, i) = queue.top();
        queue.pop();
        fout.write((char *) &tmp, sizeof(tmp));
        if (file_range[i].read((char *) &tmp, sizeof(tmp))) {
            queue.push(std::make_pair(tmp, i));
        }
    }

    fout.close();

    for (const auto &i : files_queue) {
        remove(i.c_str());
    }
}