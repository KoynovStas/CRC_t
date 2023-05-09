#include <cstdlib>
#include <unistd.h>

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <atomic>

#include "ThreadPool.h"
#include "crc_list.h"






class ProgressBar
{
    public:
        explicit ProgressBar(size_t width = 60):
            m_width(width),
            m_placeholder(width, '=')
            {}

        void set_pos(float curr_pos)
        {
            int lpad = (curr_pos/100.0)*m_width;
            int rpad = m_width - lpad;

            printf("\r[%.*s%*s] %.2f%%", lpad, m_placeholder.c_str(), rpad, "", curr_pos);
            fflush(stdout);
        }

        void finish()
        {
            set_pos(100);//all done
            printf("\n");
        }

    private:
        size_t            m_width;
        const std::string m_placeholder;
};




class TestSpeed
{
    public:
        explicit TestSpeed(size_t threads = 8);

        void run();

        static const size_t DATA_LEN = 1024*1024*1024; /// one gigabyte

    private:
        ThreadPool pool;
        std::vector< std::future<double> > results;
        std::atomic<size_t> cnt_results{0};

        char *data;

        void init();
        void create_workers();
        void wait_all_results();
        void print_table();
};




TestSpeed::TestSpeed(size_t threads):
    pool(threads)
{
    init();
}



void TestSpeed::run()
{
    create_workers();
    wait_all_results();
    print_table();
}



void TestSpeed::init()
{
    uint32_t randomNumber = 0x27121978;

    data = new char[DATA_LEN];
    for(size_t i = 0; i < DATA_LEN; i++)
    {
        data[i] = char(randomNumber & 0xFF);
        // simple LCG, see http://en.wikipedia.org/wiki/Linear_congruential_generator
        randomNumber = 1664525 * randomNumber + 1013904223;
    }
}



void TestSpeed::create_workers()
{
    for(size_t i = 0; i < CRC_List.size(); ++i) {
        results.emplace_back(
            pool.enqueue([i, this] {
                auto start = std::chrono::steady_clock::now();

                CRC_List[i]->get_crc(data, DATA_LEN);

                auto end  = std::chrono::steady_clock::now();
                auto diff = end - start;
                cnt_results++;

                return std::chrono::duration<double>(diff).count();
            })
        );
    }
}



void TestSpeed::wait_all_results()
{
    ProgressBar bar;

    while(cnt_results < CRC_List.size())
    {
        bar.set_pos(((float)cnt_results/CRC_List.size())*100.0);
        sleep(1);
    }

    bar.finish();
}



void TestSpeed::print_table()
{
    const int    NAME_WIDTH = 24;
    const int    IMPL_WIDTH = 10;

    std::cout << std::left;

    //print header
    std::cout << '|' << std::setw(NAME_WIDTH) << "Name/Impl";
    for(size_t i = 0; i < CNT_IMPL; i++)
        std::cout << '|' << std::setw(IMPL_WIDTH) << CRC_List[i]->impl_name;

    std::cout << std::endl;

    std::cout << std::setfill('-') << '|' << std::setw(NAME_WIDTH) << '-';
    for(size_t i = 0; i < CNT_IMPL; i++)
        std::cout << '|' << std::setw(IMPL_WIDTH) << '-';

    std::cout << std::endl;


    //print result
    std::cout << std::setfill(' ') << std::fixed << std::setprecision(2);

    for(size_t i = 0; i < CRC_List.size(); i += CNT_IMPL)
    {

        std::cout << '|' << std::setw(NAME_WIDTH) << CRC_List[i]->crc_name;

        for(size_t j = 0; j < CNT_IMPL; j++)
        {
            double speed = (DATA_LEN/(1024*1024))/results[i+j].get(); //speed in MB/sec
            std::cout << '|' << std::setw(IMPL_WIDTH) << speed;
        }

        std::cout << std::endl;
    }
}




int main()
{
    TestSpeed test;

    test.run();

    return 0;
}
