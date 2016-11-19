#ifndef IO_H
#define IO_H

#include <fstream>

class IO
{
private:
    std::ofstream file;

public:
    IO(const char *filename);
    ~IO();

    void open(const char *filename);
    void close();
    void saveState(class System &system);
};

#endif // IO_H
