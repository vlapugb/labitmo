#include <boost/process.hpp>
#include <iostream>
#include <chrono>
#include <boost/asio.hpp>
using namespace std;
namespace bp = boost::process;
namespace ba = boost::asio;
int main() 
{
    try {
        ba::io_service ioservice;
        auto start = chrono::high_resolution_clock::now();
        bp::child process2("./process2", ioservice, bp::std_out > stdout);
        bp::child process3("./process3", ioservice, bp::std_out > stdout);
        cout << "Запущены process2 и process3" << endl;
        process2.wait();
        process3.wait();
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end-start).count();
        cout << "Завершены process2 и process3" << endl;
        cout<<"Время выполнения программы: "<<duration<<" мкс."<<endl;
    } 
    catch (const bp::process_error& e) 
    {
        cerr << "Ошибка при запуске процесса: " << e.what() << endl;
        return 1;
    }
    return 0;
}