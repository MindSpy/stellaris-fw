#include "SensorTest.hpp"
#include "ProtocolTest.hpp"

#include <cpptest.h>

using namespace mindspy::test;

int main( int argc, char **argv)
{
    Test::Suite ts;
    ts.add(std::auto_ptr<Test::Suite>(new SensorTest));
    ts.add(std::auto_ptr<Test::Suite>(new ProtocolTest));

    Test::TextOutput output(Test::TextOutput::Verbose);
    return !ts.run(output);
}
